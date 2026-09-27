#pragma once

/*
 *  RMH_OpenGL_Histogram.h
 *
 *  Author: Rune Mark Hansen
 *  Date: January 2023
 *  Updated: 20-07-2024
 *
 */

// Inkluderede Biblioteker
#include <windows.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include <iostream>
#include "RMH_ThermalCameraSupport_Library.h"
#include "RMH_Winforms_Library.h"

 // Tilhørende Name spaces
using namespace System::Windows::Forms;
using namespace std;

// Statiske Globale Klasse variabler
static unsigned int HistDistributionData[16384];

// OpenGL Klasse definition
namespace OpenGLHistogram {

	public ref class RMHOpenGLHistogram : public System::Windows::Forms::NativeWindow {

	private:

		// Histogram Konfigurations Parametere
		private: unsigned int NumberOfHistogramBins = 256;
		private: unsigned int HistgramColorPaletteResolution = 16384;
		private: unsigned int HistgramColorPaletteResolutionRange = 65535;

		// Private Globale klasse objekter og variabler
		private: HDC m_hDC;
		private: HGLRC m_hglrc;
		private: GLuint BaseFont;
		private: GLint iPixelFormat;
		private: GLuint* HistogramTexture;
		private: unsigned int TextureWidth;
		private: unsigned int TextureHeight;
		private: GLdouble CurrentTexturePanelWidth;
		private: GLdouble CurrentTexturePanelHeight;
		private: GLdouble TextureToPanelScaleWidthFactor;
		private: GLdouble TextureToPanelScaleHeightFactor;
		private: CreateParams^ ControlParams = gcnew CreateParams;

		// Diverse Histogram variabler
		private: unsigned int TexturePanelTopButMargin = 22;
		private: unsigned int RefLineRightPanelOffset = 12;
		private: unsigned int HistogramX0 = 0;
		private: unsigned int HistogramY0 = 0;
		private: unsigned int HistogramY1 = 0;
		private: unsigned int HistogramMaxBinLength = 0;
		private: unsigned int HistogramHeight = 0;
		private: unsigned short (*HistogramPalettePtr)[16384];
		private: unsigned int HistHighestBinValue = 0;
		private: GLfloat HistBinDataFitScaleFactor = 1.0;
		private: bool HistogramColorPaletteInvertFlag = false;
		private: GLfloat ColorPaletteBinIndexOffsetValue = 0;

	public:

		// ------------------------ Histogram Konstruktur Routiner ------------------------- //

		RMHOpenGLHistogram(System::Windows::Forms::Panel^ TexturePanel, unsigned char HeightScaleFactor) {

			// Sæt positionen af kontrol klassen
			ControlParams->X = 0;
			ControlParams->Y = 0;
			ControlParams->Width = (GLdouble)TexturePanel->Width;
			ControlParams->Height = (GLdouble)TexturePanel->Height * HeightScaleFactor;

			// Konfigurer Textur parent handler
			ControlParams->Parent = TexturePanel->Handle;
			// Skab "Child" af valgte "parent" og gør denne OpenGL compliant
			ControlParams->Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

			// Generer tekstur vindue handler
			this->CreateHandle(ControlParams);

			// Pointer til textur handler
			m_hDC = GetDC((HWND)this->Handle.ToPointer());

			// Er denne handler aktiv
			if (m_hDC) {

				// Konfigurer Textur Pixel format
				RMH_OpenGL_SetTexturePixelFormat(m_hDC);
				// Konfigurer texturens størrelse
				RMH_OpenGL_ResizeOpenGLWinformsScene(ControlParams->Width, ControlParams->Height);
				// Initialisere OpenGL for Winforms C++
				RMH_OpenGL_Init();

			}

			// Opsæt Histogram textur området til grafisk renderering
			RMH_OpenGL_InitHistogramTexture(ControlParams->Width, ControlParams->Height);

		}

		// ----------------- Textur Initiliserings Og Håndterings Routiner ----------------- //

		private: GLvoid RMH_OpenGL_MakeRenderContextCurrent() {

			// Routinen Gør Tilhørende Render kontekst det nuværende render kontekst

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			wglMakeCurrent(m_hDC, m_hglrc);

		}

		private: GLvoid RMH_OpenGL_MakeRenderContextNULL() {

			// Routinen nulstiller tilhørende Render kontekst

			// Nulstil Render kontekst
			wglMakeCurrent(NULL, NULL);

		}

		private: GLvoid RMH_OpenGL_InitHistogramTexture(unsigned int HistogramTextureWidth, unsigned int HistogramTextureHeight) {

			// Routinen benyttes til at opsætte en OpenGL textur til grafisk renderering

			// Sæt Textur Parameter2
			HistogramTexture = new GLuint[1];
			TextureWidth = HistogramTextureWidth;
			TextureHeight = HistogramTextureHeight;

			// Brug Texturen som skal rendererer Histogrammets data
			glGenTextures(1, HistogramTexture);

			// Aktiver OpenGL 2D Texture
			glEnable(GL_TEXTURE_2D);

			// Bind Texturen som et 2D textur
			glBindTexture(GL_TEXTURE_2D, HistogramTexture[0]);

			// Konfigurer Textur parametere
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, HistogramTextureWidth, HistogramTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			// Deaktiver Texture
			glDisable(GL_TEXTURE_2D);

		}

		private: GLvoid RMH_OpenGL_UpdateTextureFieldOfView(unsigned int TextureWidth, unsigned int TextureHeight) {

			// Routinen indstiller texturens syns vinkel for display i control handler komponentet

			// Lokale Variabler
			GLdouble PlaneXLook = 0.0;
			GLdouble PlaneYLook = 0.0;
			GLdouble PlaneFieldOfView = 60.0;
			GLdouble HalfFieldOfView = 0.5235986291;   // 3.141592654 * PlaneFieldOfView * (1 / 360); 
			GLdouble TanHalfFieldOfView = 1.732051393; // tanf(HalfFieldOfView);
			GLdouble PlaneDistance = 0.0;
			GLdouble PlaneAspectRatio = 0.0;

			// Læs data framens højde og bredde
			PlaneXLook = (GLdouble)TextureWidth * 0.5;
			PlaneYLook = (GLdouble)TextureHeight * 0.5;

			// Udregn textur Aspect ratio
			PlaneAspectRatio = ((GLdouble)TextureWidth / (GLdouble)TextureHeight);

			// Udregn affstanden imellem Frame data planet og textur planet
			PlaneDistance = (GLdouble)TextureHeight * TanHalfFieldOfView;

			// Opdater Texturens syns vinkel
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(PlaneFieldOfView, PlaneAspectRatio, 0.01f, 2250.0);
			gluLookAt(PlaneXLook, PlaneYLook, PlaneDistance * 0.5, PlaneXLook, PlaneYLook, 0, 0, 1, 0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

		}

		// ------------------ Label Rendererings Og Håndterings Routiner ------------------- //

		private: GLvoid RMH_OpenGL_glPrint(const char* CharArray) {

			// Routinen Renderer et sæt karakterer på et OpenGL textur 

			// Tilføj FONT Liste Egenskaber
			glPushAttrib(GL_LIST_BIT);
			// Benyt FONT Base List
			glListBase(BaseFont - 32);
			// Eksikver og renderer karakterer på textur
			glCallLists(strlen(CharArray), GL_UNSIGNED_BYTE, CharArray);
			// Genopret Liste Egenskaber
			glPopAttrib();

		}

		private: GLvoid RMH_OpenGL_RenderStringOnTexture(GLfloat StringX, GLfloat StringY, std::string DisplayString, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen rendererer et givet string på et OpenGL Textur

			// Konfigurer Textens Farve
			glColor3ub(ColorR, ColorG, ColorB);
			// Indstil textens position på textur
			glRasterPos2f(StringX, StringY);

			// Render givet string på textur
			RMH_OpenGL_glPrint(DisplayString.c_str());

		}

		// -------------------- Histogram Textur Rendererings Routiner --------------------- //

		private: GLvoid RMH_OpenGL_ClearTextureBuffer() {

			// Routinen rydder tilhørende textur buffere

			// Ryd Textur farve og bit buffere
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}

		private: GLvoid RMH_OpenGL_StartHistogramRender() {

			// Routinen er start tilstande af OpenGL Histogram Rendereringen

			// Roter Textur Til at matche korrekt billede orientation
			glTranslatef(0.0f, (GLdouble)TextureHeight, 0.0f);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

		}

		private: GLvoid RMH_OpenGL_RenderLine(GLfloat LineX0, GLfloat LineY0, GLfloat LineX1, GLfloat LineY1, GLfloat LineWidth, GLfloat ColorR, GLfloat ColorG, GLfloat ColorB) {

			// Routinen rendererer en simpel linje med givet input parametere

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil pilens Farve
			glColor3ub(ColorR, ColorG, ColorB);
			// Indstil pilens Linjens tykkelse
			glLineWidth(LineWidth);

			// Render linjer på textur
			glBegin(GL_LINES);

			// Render pilens primære linje
			glVertex2f(LineX0, LineY0);
			glVertex2f(LineX1, LineY1);

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

		}

		private: GLvoid RMH_OpenGL_RenderHistogramBin(GLfloat BinX0, GLfloat BinY0, GLfloat BinHeight, GLfloat BinLength, GLfloat ColorR, GLfloat ColorG, GLfloat ColorB) {
			   
			// Routinen renderer et histogram bin rektangel

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil polygon Farve
			glColor3f(ColorR / (GLfloat)HistgramColorPaletteResolutionRange, ColorG / (GLfloat)HistgramColorPaletteResolutionRange, ColorB / (GLfloat)HistgramColorPaletteResolutionRange);

			// Indstil polygon Linjens tykkelse
			glLineWidth(1);

			// Render Polygon på textur
			glBegin(GL_POLYGON);

			// Render Polygon rektangel linjer
			glVertex2f(BinX0, BinY0);
			glVertex2f(BinX0, BinY0 + BinHeight);
			glVertex2f(BinX0, BinY0);
			glVertex2f(BinX0 - BinLength, BinY0);
			glVertex2f(BinX0, BinY0 + BinHeight);
			glVertex2f(BinX0 - BinLength, BinY0 + BinHeight);
			glVertex2f(BinX0 - BinLength, BinY0);
			glVertex2f(BinX0 - BinLength, BinY0 + BinHeight);

			// Konfiguration Slut
			glEnd();

			// Linje Rendererings Mode
			/*glBegin(GL_LINES);
			glVertex2f(BinX0, BinY0);
			glVertex2f(BinX0, BinY0 + BinHeight);
			glVertex2f(BinX0, BinY0);
			glVertex2f(BinX0 - BinLength, BinY0);
			glVertex2f(BinX0 - BinLength, BinY0);
			glVertex2f(BinX0 - BinLength, BinY0 + BinHeight);
			glVertex2f(BinX0 - BinLength, BinY0 + BinHeight);
			glVertex2f(BinX0, BinY0 + BinHeight);
			glEnd();*/

			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);
  
		}
		
		private: GLvoid RMH_OpenGL_RenderHistogramBins(unsigned int *BinData) {

			// Routinen Renderer Histrogrammets forskellige Bins fra givet input parametre

			// Lokale variabler
			GLfloat HistogramBinHeight = 0.0;
			register GLfloat HistogramNextBinPos1 = 0.0;
			register GLfloat HistogramNextBinPos2 = 0.0;
			register GLfloat HistogramNextBinPos3 = 0.0;
			register GLfloat HistogramNextBinPos4 = 0.0;
			register GLfloat HistogramBinLengthData1 = 0.0;
			register GLfloat HistogramBinLengthData2 = 0.0;
			register GLfloat HistogramBinLengthData3 = 0.0;
			register GLfloat HistogramBinLengthData4 = 0.0;
			register unsigned int IntvertedIndex1 = 0;
			register unsigned int IntvertedIndex2 = 0;
			register unsigned int IntvertedIndex3 = 0;
			register unsigned int IntvertedIndex4 = 0;
			register unsigned int ColorPaletteBinIndexValue1 = 0;
			register unsigned int ColorPaletteBinIndexValue2 = 0;
			register unsigned int ColorPaletteBinIndexValue3 = 0;
			register unsigned int ColorPaletteBinIndexValue4 = 0;

			// Udregn Histogram Bin Højden for hvert Bin
			HistogramBinHeight = (GLfloat)HistogramHeight / (GLfloat)NumberOfHistogramBins;

			// Udregn Histogrammets Colorpalette Index Offset Værdi
			ColorPaletteBinIndexOffsetValue = (GLfloat)HistgramColorPaletteResolution / (GLfloat)NumberOfHistogramBins;

			// Loop til og med antallet af histogram bins
			for (unsigned int i = 0; i < NumberOfHistogramBins; i += 4) {

				// Læs histogram bin længde dataen
				HistogramBinLengthData1 = *(BinData + ((NumberOfHistogramBins - 1) - (i + 0)));
				HistogramBinLengthData2 = *(BinData + ((NumberOfHistogramBins - 1) - (i + 1)));
				HistogramBinLengthData3 = *(BinData + ((NumberOfHistogramBins - 1) - (i + 2)));
				HistogramBinLengthData4 = *(BinData + ((NumberOfHistogramBins - 1) - (i + 3)));
			
				// Skaller Histogram bin Dataen. Fit dataen til histogram Y aksen
				HistogramBinLengthData1 = HistogramBinLengthData1 * HistBinDataFitScaleFactor;
				HistogramBinLengthData2 = HistogramBinLengthData2 * HistBinDataFitScaleFactor;
				HistogramBinLengthData3 = HistogramBinLengthData3 * HistBinDataFitScaleFactor;
				HistogramBinLengthData4 = HistogramBinLengthData4 * HistBinDataFitScaleFactor;

				// Udregn Næste Histogram Bin Position
				HistogramNextBinPos1 = (GLfloat)HistogramY0 + (HistogramBinHeight * (GLfloat)(i + 0));
				HistogramNextBinPos2 = (GLfloat)HistogramY0 + (HistogramBinHeight * (GLfloat)(i + 1));
				HistogramNextBinPos3 = (GLfloat)HistogramY0 + (HistogramBinHeight * (GLfloat)(i + 2));
				HistogramNextBinPos4 = (GLfloat)HistogramY0 + (HistogramBinHeight * (GLfloat)(i + 3));

				// Udregn den aktuelle Colorpalette Index Værdi Til Histogrammet Bin
				ColorPaletteBinIndexValue1 = (unsigned int)((ColorPaletteBinIndexOffsetValue * ((GLfloat)(i + 0) + 1.0)) - 1.0);
				ColorPaletteBinIndexValue2 = (unsigned int)((ColorPaletteBinIndexOffsetValue * ((GLfloat)(i + 1) + 1.0)) - 1.0);
				ColorPaletteBinIndexValue3 = (unsigned int)((ColorPaletteBinIndexOffsetValue * ((GLfloat)(i + 2) + 1.0)) - 1.0);
				ColorPaletteBinIndexValue4 = (unsigned int)((ColorPaletteBinIndexOffsetValue * ((GLfloat)(i + 3) + 1.0)) - 1.0);

				// Indstil Histogramets Minimale Bin Størrelse
				if (HistogramBinLengthData1 <= 1) { HistogramBinLengthData1 = 1; }
				if (HistogramBinLengthData2 <= 1) { HistogramBinLengthData2 = 1; }
				if (HistogramBinLengthData3 <= 1) { HistogramBinLengthData3 = 1; }
				if (HistogramBinLengthData4 <= 1) { HistogramBinLengthData4 = 1; }

				// Skal histogrammets color palette inverteres
				if (HistogramColorPaletteInvertFlag == true) {

					// Render Histogram Bin Rektangler vertikalt
					RMH_OpenGL_RenderHistogramBin(HistogramX0, HistogramNextBinPos1, HistogramBinHeight, HistogramBinLengthData1, HistogramPalettePtr[0][ColorPaletteBinIndexValue1], HistogramPalettePtr[1][ColorPaletteBinIndexValue1], HistogramPalettePtr[2][ColorPaletteBinIndexValue1]);
					RMH_OpenGL_RenderHistogramBin(HistogramX0, HistogramNextBinPos2, HistogramBinHeight, HistogramBinLengthData2, HistogramPalettePtr[0][ColorPaletteBinIndexValue2], HistogramPalettePtr[1][ColorPaletteBinIndexValue2], HistogramPalettePtr[2][ColorPaletteBinIndexValue2]);
					RMH_OpenGL_RenderHistogramBin(HistogramX0, HistogramNextBinPos3, HistogramBinHeight, HistogramBinLengthData3, HistogramPalettePtr[0][ColorPaletteBinIndexValue3], HistogramPalettePtr[1][ColorPaletteBinIndexValue3], HistogramPalettePtr[2][ColorPaletteBinIndexValue3]);
					RMH_OpenGL_RenderHistogramBin(HistogramX0, HistogramNextBinPos4, HistogramBinHeight, HistogramBinLengthData4, HistogramPalettePtr[0][ColorPaletteBinIndexValue4], HistogramPalettePtr[1][ColorPaletteBinIndexValue4], HistogramPalettePtr[2][ColorPaletteBinIndexValue4]);

				}
				else {

					// Udregn Den inverterede Colorpalettes index
					IntvertedIndex1 = (HistgramColorPaletteResolution - 1) - ColorPaletteBinIndexValue1;
					IntvertedIndex2 = (HistgramColorPaletteResolution - 1) - ColorPaletteBinIndexValue2;
					IntvertedIndex3 = (HistgramColorPaletteResolution - 1) - ColorPaletteBinIndexValue3;
					IntvertedIndex4 = (HistgramColorPaletteResolution - 1) - ColorPaletteBinIndexValue4;

					// Render Histogram Bin Rektangler vertikalt
					RMH_OpenGL_RenderHistogramBin(HistogramX0, HistogramNextBinPos1, HistogramBinHeight, HistogramBinLengthData1, HistogramPalettePtr[0][IntvertedIndex1], HistogramPalettePtr[1][IntvertedIndex1], HistogramPalettePtr[2][IntvertedIndex1]);
					RMH_OpenGL_RenderHistogramBin(HistogramX0, HistogramNextBinPos2, HistogramBinHeight, HistogramBinLengthData2, HistogramPalettePtr[0][IntvertedIndex2], HistogramPalettePtr[1][IntvertedIndex2], HistogramPalettePtr[2][IntvertedIndex2]);
					RMH_OpenGL_RenderHistogramBin(HistogramX0, HistogramNextBinPos3, HistogramBinHeight, HistogramBinLengthData3, HistogramPalettePtr[0][IntvertedIndex3], HistogramPalettePtr[1][IntvertedIndex3], HistogramPalettePtr[2][IntvertedIndex3]);
					RMH_OpenGL_RenderHistogramBin(HistogramX0, HistogramNextBinPos4, HistogramBinHeight, HistogramBinLengthData4, HistogramPalettePtr[0][IntvertedIndex4], HistogramPalettePtr[1][IntvertedIndex4], HistogramPalettePtr[2][IntvertedIndex4]);

				}
				
			}

		}

		// ---------------- Samlede Histogram Grafiske Rendererings Routine ---------------- //

		public: GLvoid RMH_OpenGL_LoadHistogramColorPalette(unsigned short (*HistogramPalette)[16384]) {

			// Routinen loader en givet histogram color palette

			// Opdater histogram color palette pointer
			HistogramPalettePtr = HistogramPalette;

		}

		public: GLvoid RMH_OpenGL_InvertHistogramColorPalette(bool FlagState) {

			// Routinen opdaterer histogrammets color palette inverterings flag

			// Opdater histogrammets color palette inverterings flag
			HistogramColorPaletteInvertFlag = FlagState;

		}

		public: void RMH_OpenGL_FormatHistogramBinDataRaw(unsigned short* RawThermalData, unsigned int DataLength, unsigned short MaxBinVal, unsigned short MinBinVal) {

			// Routinen fordeler givet input data til tilhørende histogram data bins

			// Lokale variabler
			GLfloat BinWidth, BinIndex;

			// Nulstil Højeste Histogram Bin variabel
			HistHighestBinValue = 0;

			// Nulstil histogram fordelings værdier inden næste iteration
			for (unsigned int i = 0; i < NumberOfHistogramBins; i++) {

				// Nulstil histogram fordelings værdier
				HistDistributionData[i] = 0;

			}

			// Udregn Histogram Bin data bredden
			BinWidth = ((GLfloat)MaxBinVal - (GLfloat)MinBinVal) / ((GLfloat)NumberOfHistogramBins - 1.0);

			// Fordel Givet Data Til tilhørende Histogram Bins 
			for (unsigned int i = 0; i < DataLength; i++) {

				// Udregn Dataens Histogram Bin Indeks værdi
				BinIndex = (RawThermalData[i] - MinBinVal) / BinWidth;

				// Begræns Histogram bin indeks værdien
				// Til at matche den rækkevidden af antal Histogram Bins
				if (BinIndex > NumberOfHistogramBins - 1 || BinIndex < 0) {}
				else {

					// Inkrementer histogram Bin indeks fordelings værdi
					HistDistributionData[(unsigned int)BinIndex] = HistDistributionData[(unsigned int)BinIndex] + 1;

					// Læs værdien af den største histogram Bin 
					if (HistDistributionData[(unsigned int)BinIndex] > HistHighestBinValue) {

						// Opdater Højeste Histogram Bin værdi
						HistHighestBinValue = HistDistributionData[(unsigned int)BinIndex];

					}

				}

			}

			// Udregn Bin data skallerings faktoren, til at fitte dataen til histogram Y aksen
			HistBinDataFitScaleFactor = ((GLfloat)HistogramMaxBinLength / (GLfloat)HistHighestBinValue);

		}

		public: void RMH_OpenGL_FormatHistogramBinDataTemp(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short* RawThermalData, unsigned int DataLength, GLfloat MaxBinVal, GLfloat MinBinVal, GLfloat TempUnitScaleFactor , GLfloat TempUnitOffsetFactor, unsigned short SupportedCameraPool) {

			// Routinen fordeler givet input data til tilhørende histogram data bins

			// Lokale variabler
			GLfloat BinWidth, BinIndex;
			GLfloat PixlTemperatureValue = 0.0f;

			// Nulstil Højeste Histogram Bin variabel
			HistHighestBinValue = 0;

			// Nulstil histogram fordelings værdier inden næste iteration
			for (unsigned int i = 0; i < NumberOfHistogramBins; i++) {

				// Nulstil histogram fordelings værdier
				HistDistributionData[i] = 0;

			}

			// Udregn Histogram Bin data bredden
			BinWidth = (MaxBinVal - MinBinVal) / ((GLfloat)NumberOfHistogramBins - 1.0);

			// Fordel Givet Data Til tilhørende Histogram Bins 
			for (unsigned int i = 0; i < DataLength; i++) {

				// Læs Pixel data temperatur værdien
				PixlTemperatureValue = RMH_IRThermalCamera_ReadPixelTemperature(IRCamera, RawThermalData[i], SupportedCameraPool);

				// Kompenser for temperatur enhed
				PixlTemperatureValue = (PixlTemperatureValue * TempUnitScaleFactor) + TempUnitOffsetFactor;

				// Udregn Dataens Histogram Bin Indeks værdi
				BinIndex = (PixlTemperatureValue - MinBinVal) / BinWidth;

				// Begræns Histogram bin indeks værdien
				// Til at matche den rækkevidden af antal Histogram Bins
				if (BinIndex > NumberOfHistogramBins - 1 || BinIndex < 0) {}
				else {

					// Inkrementer histogram Bin indeks fordelings værdi
					HistDistributionData[(unsigned int)BinIndex] = HistDistributionData[(unsigned int)BinIndex] + 1;

					// Læs værdien af den største histogram Bin 
					if (HistDistributionData[(unsigned int)BinIndex] > HistHighestBinValue) {

						// Opdater Højeste Histogram Bin værdi
						HistHighestBinValue = HistDistributionData[(unsigned int)BinIndex];

					}

				}

			}

			// Udregn Bin data skallerings faktoren, til at fitte dataen til histogram Y aksen
			HistBinDataFitScaleFactor = ((GLfloat)HistogramMaxBinLength / (GLfloat)HistHighestBinValue);

		}

		public: void RMH_OpenGL_FormatHistogramBinDataLine(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short* RawThermalData, GLfloat *LineXCordinates, GLfloat *LineYCordinates, unsigned int LineLength, GLfloat MaxBinVal, GLfloat MinBinVal, GLfloat TempUnitScaleFactor, GLfloat TempUnitOffsetFactor) {

			// Routinen fordeler givet input data til tilhørende histogram data bins

			// Lokale variabler
			GLfloat BinWidth, BinIndex;
			GLfloat PixlTemperatureValue = 0.0f;

			// Nulstil Højeste Histogram Bin variabel
			HistHighestBinValue = 0;

			// Nulstil histogram fordelings værdier inden næste iteration
			for (unsigned int i = 0; i < NumberOfHistogramBins; i++) {

				// Nulstil histogram fordelings værdier
				HistDistributionData[i] = 0;

			}

			// Udregn Histogram Bin data bredden
			BinWidth = (MaxBinVal - MinBinVal) / ((GLfloat)NumberOfHistogramBins - 1.0);

			// Fordel Givet Data Til tilhørende Histogram Bins 
			for (unsigned int i = 0; i < LineLength; i++) {

				// Læs Pixel data temperatur værdien
				PixlTemperatureValue = RMH_IRThermalCamera_ReadFramePixelTemperature(IRCamera, RawThermalData, LineXCordinates[i], LineYCordinates[i], IRCamera->ThermalCameraSupportPool);

				// Kompenser for temperatur enhed
				PixlTemperatureValue = (PixlTemperatureValue * TempUnitScaleFactor) + TempUnitOffsetFactor;

				// Udregn Dataens Histogram Bin Indeks værdi
				BinIndex = (PixlTemperatureValue - MinBinVal) / BinWidth;

				// Begræns Histogram bin indeks værdien
				// Til at matche den rækkevidden af antal Histogram Bins
				if (BinIndex > NumberOfHistogramBins - 1 || BinIndex < 0) {}
				else {

					// Inkrementer histogram Bin indeks fordelings værdi
					HistDistributionData[(unsigned int)BinIndex] = HistDistributionData[(unsigned int)BinIndex] + 1;

					// Læs værdien af den største histogram Bin 
					if (HistDistributionData[(unsigned int)BinIndex] > HistHighestBinValue) {

						// Opdater Højeste Histogram Bin værdi
						HistHighestBinValue = HistDistributionData[(unsigned int)BinIndex];

					}

				}

			}

			// Udregn Bin data skallerings faktoren, til at fitte dataen til histogram Y aksen
			HistBinDataFitScaleFactor = ((GLfloat)HistogramMaxBinLength / (GLfloat)HistHighestBinValue);

		}

		public: void RMH_OpenGL_SetHistogramNumberOfBins(System::Object^ sender) {

			// Routinen indstiller histogrammets rendereret antal bins

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ BinsTagValue = (System::Windows::Forms::ToolStripMenuItem^)sender;
			// Læs Sub Context Menu identifikations tag
			unsigned int NumberOfBins = Convert::ToInt32(BinsTagValue->Tag);

			// Indstil antal af rendereret Bins
			NumberOfHistogramBins = NumberOfBins;

		}

		public: GLvoid RMH_OpenGL_RenderHistogram(unsigned int TexturePanelWidth, unsigned int TexturePanelHeight) {

			// Routinen Rendererer alle grafiske objekter som Histogrammet består af

			// Læs Nuværende textur Panels pixel højde og bredde
			CurrentTexturePanelWidth = (GLdouble)TexturePanelWidth;
			CurrentTexturePanelHeight = (GLdouble)TexturePanelHeight;

			// Udregn Histogrammets start positioner og tilhørende textur parametre
			HistogramX0 = CurrentTexturePanelWidth - RefLineRightPanelOffset;
			HistogramY0 = TexturePanelTopButMargin;
			HistogramY1 = CurrentTexturePanelHeight - TexturePanelTopButMargin;
			HistogramMaxBinLength = HistogramX0;
			HistogramHeight = HistogramY1 - HistogramY0;

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();
			// Ryd Textur farve og bit buffere
			RMH_OpenGL_ClearTextureBuffer();
			// Opdater Textur Field Of View
			RMH_OpenGL_UpdateTextureFieldOfView(TextureWidth, TextureHeight);

			// Bind OpenGL textur og Start OpenGL renderering
			RMH_OpenGL_StartHistogramRender();

			// ----------------------------------- Render Histogram ----------------------------------- //
			
			// Render Historam Reference Linje (X akse)
			RMH_OpenGL_RenderLine(HistogramX0, HistogramY0, HistogramX0, HistogramY1, 1, 0, 0, 0);

			// Renderer Histogram Bins
			RMH_OpenGL_RenderHistogramBins(&HistDistributionData[0]);

			// ---------------------------------------------------------------------------------------- //

			// Marker enden på en OpenGL rendererins sekvens
			RMH_OpenGL_RenderingFinishedMark();

		}

		// -------------------- OpenGL Renderering Slut Punkts Routiner -------------------- //

		private: GLvoid RMH_OpenGL_SwapOpenGLBuffers(GLvoid) {

			// Routinen bytter rundt på Front/Backend bufferene

			// Byt Rundt på buffere
			SwapBuffers(m_hDC);

		}

		private: GLvoid RMH_OpenGL_RenderingFinishedMark(GLvoid) {

			// Routinen markerer enden på en OpenGL rendererins sekvens
			// Og skal altid kaldes til sidst, når alle objekt rendereringer er blevet eksikverede

			// Swap Textur buffere
			RMH_OpenGL_SwapOpenGLBuffers();

			// Nulstil Render kontekst
			//this->RMH_OpenGL_MakeRenderContextNULL();

		}

		// --------------------------------------------------------------------------------- //

	private:

		// ------------- Yderligerer OpenGL Håndterings Og Opsætnings Routiner ------------- //

		~RMHOpenGLHistogram(GLvoid) {

			// Slet OpenGL Context
			DeleteOpenGL();

			// Destruer OpenGL Handler objekt
			this->DestroyHandle();

			// Garbage Collect managed data
			System::GC::Collect();

		}

		private: GLvoid DeleteOpenGL(GLvoid) {

			// Routinen sletter alt OpenGL Context

			// Lokale variabler
			HGLRC hglrc;
			HDC  hdc;

			// Læs Thread Context
			hglrc = wglGetCurrentContext();
			// Læs tilhørende Device Context 
			hdc = wglGetCurrentDC();
			// Gør render contexten den nuværende context
			wglMakeCurrent(NULL, NULL);
			// Frigiv Device context
			ReleaseDC(NULL, hdc);
			// Slet Render Context
			wglDeleteContext(hglrc);

			// Nulstil Context variabler
			m_hglrc = nullptr;
			m_hDC = nullptr;

		}

		private: bool RMH_OpenGL_SetTexturePixelFormat(HDC hdc) {

			// Routinen konfigurerer Texturens Pixel format

			// Formatet fortæller windows hvordan textur dataen skal oversættes
			PIXELFORMATDESCRIPTOR pfd = {

				sizeof(PIXELFORMATDESCRIPTOR),				// Størrelse af denne pixel format beskrivelse
				1,											// Formatets Versions Nummer 
				PFD_DRAW_TO_WINDOW |						// Formatet skal supporterer Windows
				PFD_SUPPORT_OPENGL |						// Formatet skal supporterer OpenGL
				PFD_DOUBLEBUFFER,							// Formatet skal supporterer "Double Buffering"
				PFD_TYPE_RGBA,								// Anmod om et RGBa Format
				16,										    // Vælg "Color Depth" (16Bit)
				0, 0, 0, 0, 0, 0,							// Farve Bits skal Ignoreres
				0,											// Ingen "Alpha Buffer"
				0,											// Shift Bit skal Ignoreres
				0,											// Ingen "Accumulation Buffer"
				0, 0, 0, 0,									// Accumulator Bits skal Ignoreres
				16,											// 16Bit Z-Buffer (Buffer dybde)  
				0,											// Ingen "Stencil Buffer"
				0,											// Ingen "Auxiliary Buffer"
				PFD_MAIN_PLANE,								// Sæt som det primære "Drawing" lag
				0,											// Reserved
				0, 0, 0										// Lag "Masks" skal Ignoreres

			};

			// Vælg pixel formatet til control handler
			if ((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0) {
				// Skriv fejl meddelse - hvis fejl er registreret
				MessageBox::Show("ChoosePixelFormat Failed");
				// Retuner Fejl
				return false;
			}

			// Sæt pixel formatet til control handler 
			if (SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE) {
				// Skriv fejl meddelse - hvis fejl er registreret
				MessageBox::Show("SetPixelFormat Failed");
				// Retuner Fejl
				return false;
			}

			if ((m_hglrc = wglCreateContext(hdc)) == NULL) {
				// Skriv fejl meddelse - hvis fejl er registreret
				MessageBox::Show("wglCreateContext Failed");
				// Retuner Fejl
				return false;
			}

			if ((wglMakeCurrent(hdc, m_hglrc)) == NULL) {
				// Skriv fejl meddelse - hvis fejl er registreret
				MessageBox::Show("wglMakeCurrent Failed");
				// Retuner Fejl
				return false;
			}

			// Retuner Status OK
			return true;
		}

		private: GLvoid RMH_OpenGL_ResizeOpenGLWinformsScene(unsigned int TotalTextureWidth, unsigned int TotalTextureHeight) {

			// Formater Størrelsen og Initialisere OpenGL Vinduet i Winforms

			// Forhindre division med '0'
			if (TotalTextureHeight == 0) {
				// Piel højden er altid mindst '1'
				TotalTextureHeight = 1;
			}

			// Nulstil nuværende "Viewport"
			glViewport(0, 0, TotalTextureWidth, TotalTextureHeight);
			// Vælg Projektions matricen
			glMatrixMode(GL_PROJECTION);
			// Nulstil Projektions matricen
			glLoadIdentity();
			// Udregn vinduets aspect ratio
			gluPerspective(60.0f, (GLfloat)TotalTextureWidth / (GLfloat)TotalTextureHeight, 0.01f, 10000.0f);
			// Vælg "Model View" matricen
			glMatrixMode(GL_MODELVIEW);
			// Nulstil "Model View" matricen
			glLoadIdentity();

		}

		private: GLvoid RMH_OpenGL_BuildFont(GLvoid) {

			// Routinen Generer FONT til display i OpenGL Textur

			// Lokale variabler
			HFONT TextureFont;

			// Opdater Font Liste
			BaseFont = glGenLists(96);

			// Generer Strutureret Font Objekt
			TextureFont = CreateFont(
				-12,                            // nHeight
				0,								// nWidth
				0,								// nEscapement
				0,				     			// nOrientation
				FW_BOLD,						// nWeight
				FALSE,							// bItalic
				FALSE,							// bUnderline
				FALSE,							// cStrikeOut
				ANSI_CHARSET,					// nCharSet
				OUT_TT_PRECIS,					// nOutPrecision
				CLIP_DEFAULT_PRECIS,			// nClipPrecision
				ANTIALIASED_QUALITY,			// nQuality
				FF_ROMAN | DEFAULT_PITCH,		// nPitchAndFamily
				L"Arial");				        // lpszFacename

			// Indstil FONT Til OpenGL Objekt Struktur
			SelectObject(m_hDC, TextureFont);
			// Generer Bitmap Display FONT Liste
			wglUseFontBitmaps(m_hDC, 32, 96, BaseFont);

		}

		private: bool RMH_OpenGL_Init(GLvoid) {

			// Routinen Initialisere OpenGL I Winforms C++/CLR

			// Aktiver "Flat Shader" Mode
			glShadeModel(GL_SMOOTH);
			// Default Baggrund farve
			glClearColor(0.13725f, 0.13725f, 0.13725f, 1.0f);
			// Opsætning af "Depth Buffer"
			glClearDepth(1.0f);
			// Deaktiver OpenGL "Depth Testing"
			glDisable(GL_DEPTH_TEST);
			// For perspektiv - Fortag "Very Nice" udregniner
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

			// Generer FONT Objekt
			RMH_OpenGL_BuildFont();

			// Retuner "OpenGl Opsætning" Færdig flag
			return true;

		}

		// --------------------------------------------------------------------------------- //

	};

	// ------------------------------------------------------------------------------------- //

}