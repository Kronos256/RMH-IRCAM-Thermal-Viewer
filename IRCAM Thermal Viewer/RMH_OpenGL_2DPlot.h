#pragma once

/*
 *  RMH_OpenGL_2DPlot.h
 *
 *  Author: Rune Mark Hansen
 *  Date: Marts 2023
 *
 */

// Inkluderede Biblioteker
#include <windows.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include <iostream>
#include "RMH_Winforms_Library.h"
#include "RMH_MathConversions_Library.h"
#include "GlobalObjectsAndVariables.h"

// Tilhørende Name spaces
using namespace System;
using namespace System::Windows::Forms;
using namespace std;

// Generalle 2D Plot Konfigurations Macroer
#define _2DPlotMaxNumberOfDataSets       10

// 2D Plot X Akse konfigurations Macro
#define _2DPlotXAxesLength               1000

// 2D Plot Y Akse konfigurations Macro
#define _2DPlotYAxesMaximumRangeResetValue   -10000.0
#define _2DPlotYAxesMinimumRangeResetValue    10000.0

// 2D Plot Padding Konfigurations Macroer
#define _2DPlotTopPixelPadding           40
#define _2DPlotBottomPixelPadding        10
#define _2DPlotLeftPixelPadding          75
#define _2DPlotRightPixelPadding         30

// 2D Plot Yderligere Offset positions Macroer
#define _2DPlotTitleYOffsetValue         15
#define _2DPlotTitleXOffsetValue         30
#define _2DPlotXAxesLabelOffset          25
#define _2DPlotYAxesLabelOffset          60

// 2D Plot Linje Tykkelse Konfigurations Macroer
#define _2DPlotTickLinePixelLength       5
#define _2DPlotAxesAndBoxLineWidth       1
#define _2DPlotTickLineWidth             1

// 2D Plot Data logging indicator konfiguration Macroer
#define _2DPlotIndicatorLabelYOffset     5

// 2D Plot DataSet Struktur Format
struct PlotDataSet {

	// 2D Plot DataSet Struktur
	GLfloat PlotDataPoints[_2DPlotXAxesLength];
	GLfloat MaximumDataValue = _2DPlotYAxesMaximumRangeResetValue;
	GLfloat MinimumDataValue = _2DPlotYAxesMinimumRangeResetValue;
	unsigned int PlotLineDataIndexRenderOffset = _2DPlotXAxesLength;

};

// Globale Statiske klasse objekter og variabler
static bool EnabledPlotDataSets[_2DPlotMaxNumberOfDataSets];
static PlotDataSet PlotDataSets[_2DPlotMaxNumberOfDataSets];
static unsigned char PlotDataSetLineColorR[_2DPlotMaxNumberOfDataSets];
static unsigned char PlotDataSetLineColorG[_2DPlotMaxNumberOfDataSets];
static unsigned char PlotDataSetLineColorB[_2DPlotMaxNumberOfDataSets];
static GLfloat PlotDataSetLineWidth[_2DPlotMaxNumberOfDataSets];
static unsigned char PlotDataSetRenderingOrder[_2DPlotMaxNumberOfDataSets];
static unsigned char DataLoggingDisplayStringChar[] = {'D','a','t','a',' ','L','o','g','g','i','n','g',' ', '-',' ','D','u','r','a','t','i','o','n',':',' ','0','0','0',':','0','0',':','0','0',':','0','0','0'};

// OpenGL Klasse definition
namespace OpenGL2DPlot {

	// ---------------------------------- Globale Klasse Struktur Objekter --------------------------------- //

	// Format til Akse-Til-Pixel kordinater
	struct AxesToPixelCoordFormat {

		// Strukktur Variabler
		GLfloat XAxesPixelResolution = 0.0;
		GLfloat YAxesPixelResolution = 0.0;
		GLfloat XPixelCoordinate = 0.0;
		GLfloat YPixelCoordinate = 0.0;

	};

	// ------------------------- Privat Custom Winforms Gennemsigtigt Panel Klasse ------------------------- //

	// Tilhørende lokalt klasse Name space objekt
	namespace NativeForm = System::Windows::Forms;

	// Gennemsigtig overlay panel klasse til billede rendererings panel
	private ref class TextureOverlayPanel : System::Windows::Forms::Panel {

		// Lokale klasse objekter
		protected: System::Drawing::Graphics^ graphics;

		protected: virtual property NativeForm::CreateParams^ CreateParams {

			// Overskriv panelets konfigurations parametere
			NativeForm::CreateParams^ get() override {

				// Læs panelets kontrol parametere
				NativeForm::CreateParams^ PanalParams = __super::CreateParams;
				// Panelets udviddet style skal være gennemsigtid
				PanalParams->ExStyle |= WS_EX_TRANSPARENT;

				// Retuner Panalets config parametere
				return PanalParams;

			}

		}

		public: TextureOverlayPanel() {

			// Gennemsigtig overlay panel klasse konstruktor

		}

		virtual void OnPaintBackground(PaintEventArgs^ e) override {

				// Ingen baggrund skal tegnes

		}

		protected: virtual void OnPaint(PaintEventArgs^ e) override {

			// Ingen yderligere grafik skal genereres til panelet 

		}

	};

	// ----------------------------------------------------------------------------------------------------- //

	public ref class RMHOpenGL2DPlot : public System::Windows::Forms::NativeWindow {

	private:

		// Private Globale klasse objekter og variabler
		private: HDC m_hDC;
		private: HGLRC m_hglrc;
		private: GLuint BaseFont;
		private: GLint iPixelFormat;
		private: unsigned int OpenGLWindowWidth;
		private: unsigned int OpenGLWindowHeight;
		private: bool OverlayPanelIsClick = false;
		private: GLdouble CurrentTexturePanelWidth;
		private: GLdouble CurrentTexturePanelHeight;
		private: GLfloat TextureToPanelWidthOffset = 0.0;
		private: GLfloat TextureToPanelHeightOffset = 0.0;
		private: CreateParams^ ControlParams = gcnew CreateParams;
		private: TextureOverlayPanel^ OverlayPanel = gcnew TextureOverlayPanel();

		// Tilhørende 2D Plot variabler og objekter
		private: GLfloat XAxesLineX0 = 0.0;
		private: GLfloat XAxesLineY0 = 0.0;
		private: GLfloat XAxesLineX1 = 0.0;
		private: GLfloat XAxesLineY1 = 0.0;
		private: GLfloat YAxesLineX0 = 0.0;
		private: GLfloat YAxesLineY0 = 0.0;
		private: GLfloat YAxesLineX1 = 0.0;
		private: GLfloat YAxesLineY1 = 0.0;
		private: GLfloat XAxesLinePixelLength = 0.0;
		private: GLfloat YAxesLinePixelLength = 0.0;
		private: GLfloat XAxesTickSpacing = 0.0;
		private: GLfloat YAxesTickSpacing = 0.0;
		private: GLdouble XDataMaxMinSpacing = 0.0;
		private: GLdouble YDataMaxMinSpacing = 0.0;
		private: GLdouble XDataLabelValue = 0.0;
		private: GLdouble YDataLabelValue = 0.0;
		private: GLfloat PlotYAxesMaximumRangeValue = _2DPlotYAxesMaximumRangeResetValue;
		private: GLfloat PlotYAxesMinimumRangeValue = _2DPlotYAxesMinimumRangeResetValue;
		private: GLfloat PlotXAxesMaximumRangeValue = 0.0;
		private: GLfloat PlotXAxesMinimumRangeValue = 0.0;
		private: bool Show2DPlotBoxFlag = true;
		private: bool Show2DPlotGridFlag = true;
		private: bool DataLoggingFLag = false;
		private: unsigned char XAxesNumberOfTicks = 25;
		private: unsigned char YAxesNumberOfTicks = 10;
		private: unsigned short RenderingLoopIterationLength = 0;
		private: unsigned long LoggingTimerLabelMilliSecValue = 0;
		private: GLfloat MousePointerXPosition = 0;
		private: GLfloat MousePointerYPosition = 0;
		private: bool EnablePlotMouseCursorDataFlag = false;
		private: GLfloat MouseCursorDataLabelXOffset = 12.0;
		private: GLfloat MouseCursorDataLabelYOffset = -10.0;

		// 2D Plot Farve konfigurations variabler 
		private: unsigned char PlotAxesColorR = 100;
		private: unsigned char PlotAxesColorG = 100;
		private: unsigned char PlotAxesColorB = 100;
		private: unsigned char PlotBoxColorR = 100;
		private: unsigned char PlotBoxColorG = 100;
		private: unsigned char PlotBoxColorB = 100;
		private: unsigned char PlotGridLinesColorR = 60;
		private: unsigned char PlotGridLinesColorG = 60;
		private: unsigned char PlotGridLinesColorB = 60;
		private: unsigned char PlotTickLinesColorR = 100;
		private: unsigned char PlotTickLinesColorG = 100;
		private: unsigned char PlotTickLinesColorB = 100;
		private: unsigned char PlotTitleColorR = 255;
		private: unsigned char PlotTitleColorG = 255;
		private: unsigned char PlotTitleColorB = 255;
		private: unsigned char MouseCursorDataLabelColorR = 255;
		private: unsigned char MouseCursorDataLabelColorG = 255;
		private: unsigned char MouseCursorDataLabelColorB = 255;

	public:

		// ------------------------- 2D Plot Konstruktur Routiner -------------------------- //

		RMHOpenGL2DPlot(System::Windows::Forms::Panel^ TexturePanel, unsigned char WidthScaleFactor, unsigned char HeightScaleFactor) {

			// Sæt positionen af kontrol klassen
			ControlParams->X = 0;
			ControlParams->Y = 0;
			ControlParams->Width = (GLdouble)TexturePanel->Width * WidthScaleFactor;
			ControlParams->Height = (GLdouble)TexturePanel->Height * HeightScaleFactor;

			// Læs OpenGL vinduets Pixel bredde og højde
			OpenGLWindowWidth = ControlParams->Width;
			OpenGLWindowHeight = ControlParams->Height;

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
				// Initialisere OpenGL
				RMH_OpenGL_Init();

			}

			// Tilføj et overlejede gennemsigtigt panel til textur panalet
			RMH_OpenGL_AddOverlayPanelToMainTexturePanel(TexturePanel);

			// Nulstil 2D plottets Data Sæt aktiverings array
			RMH_OpenGL_ResetPlotDataSetEnableArray();
			// Nulstil 2D plottets Linje tykkelses array 
			RMH_OpenGL_ResetPlotLineWidthArray();

			// Indstil Data sæts default linje farver
			RMH_OpenGL_SetDataSetLineColor(0, 255, 0, 0);
			RMH_OpenGL_SetDataSetLineColor(1, 0, 0, 255);
			RMH_OpenGL_SetDataSetLineColor(2, 50, 205, 50);
			RMH_OpenGL_SetDataSetLineColor(3, 255, 255, 0);
			RMH_OpenGL_SetDataSetLineColor(4, 255, 128, 0);
			RMH_OpenGL_SetDataSetLineColor(5, 255, 0, 255);
			RMH_OpenGL_SetDataSetLineColor(6, 0, 255, 255);
			RMH_OpenGL_SetDataSetLineColor(7, 255, 255, 255);
			RMH_OpenGL_SetDataSetLineColor(8, 128, 128, 128);
			RMH_OpenGL_SetDataSetLineColor(9, 128, 255, 128);

		}

		// ----------- Textur Overlejede Gennemsigtigt Panel Opsætnings Routine ------------ //

		private: GLvoid RMH_OpenGL_AddOverlayPanelToMainTexturePanel(System::Windows::Forms::Panel^ TexturePanel) {

			// Routinen tilføjer et overlejede gennemsigtigt panel til textur panalet
			// Dette overlejede panel benyttes til manipulerer objekter på billede texturen

			// Overlejede panel skal ikke have nogen margin eller padding
			OverlayPanel->Margin = System::Windows::Forms::Padding(0, 0, 0, 0);
			OverlayPanel->Padding = System::Windows::Forms::Padding(0, 0, 0, 0);

			// Det overlejede gennemsigtigt panel skal fylde hele textur panelet
			OverlayPanel->Dock = System::Windows::Forms::DockStyle::Fill;

			// Tilføj det overlejede gennemsigtigt panel som et "Child" til textur panelet
			TexturePanel->Controls->Add(OverlayPanel);

			// Aktiver Mus handler events til det gennemsigtige panel
			OverlayPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGL2DPlot::TexturePanel_MouseDown);
			OverlayPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGL2DPlot::TexturePanel_MouseUp);
			OverlayPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGL2DPlot::TexturePanel_MouseMove);
			OverlayPanel->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGL2DPlot::TexturePanel_MouseWheel);

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
			gluPerspective(PlaneFieldOfView, PlaneAspectRatio, 0.01f, 2000.0);
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

		private: GLvoid RMH_OpenGL_glPrintUnsigned(unsigned char* CharArray, unsigned int CharArrayLength) {

			// Routinen Renderer et sæt karakterer på et OpenGL textur 

			// Tilføj FONT Liste Egenskaber
			glPushAttrib(GL_LIST_BIT);
			// Benyt FONT Base List
			glListBase(BaseFont - 32);
			// Eksikver og renderer karakterer på textur
			glCallLists(CharArrayLength, GL_UNSIGNED_BYTE, CharArray);
			// Genopret Liste Egenskaber
			glPopAttrib();

		}

		private: GLvoid RMH_OpenGL_RenderStringOnTextureChar(GLfloat StringX, GLfloat StringY, unsigned char *DisplayString, unsigned int CharArrayLength, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen rendererer et givet string på et OpenGL Textur

			// Konfigurer Textens Farve
			glColor3ub(ColorR, ColorG, ColorB);
			// Indstil textens position på textur
			glRasterPos2f(StringX, StringY);

			// Render givet string på textur
			RMH_OpenGL_glPrintUnsigned(DisplayString, CharArrayLength);

		}

		// ---------- 2D Plot Koordinat Og Data Formaterings/Håndterings Routiner ---------- //

		private: AxesToPixelCoordFormat RMH_OpenGL_2DPLotConvertXYAxesCoordinatesToPixelCoordinates(GLfloat XCoordinate, GLfloat YCoordinate, GLfloat XAxesMaxRange, GLfloat XAxesMinRange, GLfloat YAxesMaxRange, GLfloat YAxesMinRange) {

			// Routinen konverterer et givet sæt af X/Y akse koordinater til aktuelle pixel koordinater

			// Lokale varaibler
			AxesToPixelCoordFormat XYPixelCoords;
			
			// Udregn X Aksens pixel opløsning
			XYPixelCoords.XAxesPixelResolution = (XAxesMaxRange - XAxesMinRange) / XAxesLinePixelLength;
			// Udregn den aktuelle X Pixel kordinat værdi
			XYPixelCoords.XPixelCoordinate = (XCoordinate - XAxesMinRange) / XYPixelCoords.XAxesPixelResolution;

			// Udregn X Aksens pixel opløsning
			XYPixelCoords.YAxesPixelResolution = (YAxesMaxRange - YAxesMinRange) / YAxesLinePixelLength;
			// Udregn den aktuelle X Pixel kordinat værdi
			XYPixelCoords.YPixelCoordinate = (YAxesMaxRange - YCoordinate) / XYPixelCoords.YAxesPixelResolution;

			// Konpenser for 3D Plottets Padding
			XYPixelCoords.XPixelCoordinate = (XYPixelCoords.XPixelCoordinate + _2DPlotLeftPixelPadding);
			XYPixelCoords.YPixelCoordinate = (XYPixelCoords.YPixelCoordinate + _2DPlotTopPixelPadding);

			// Retuner pixel coordinater
			return XYPixelCoords;

		}

		private: GLvoid RMH_OpenGL_ResetPlotDataSetEnableArray() {

			// Routinen nulstiller 2D plottets Data Sæt aktiverings array 

			// Loop til og med det maksimale antal 2D Plot Data sæts
			for (unsigned int i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

				// Nulstil 2D plottets Data Sæt aktiverings array
				EnabledPlotDataSets[i] = false;

			}

		}

		private: GLvoid RMH_OpenGL_ResetPlotLineWidthArray() {

			// Routinen nulstiller 2D plottets Linje tykkelses array 

			// Loop til og med det maksimale antal 2D Plot Data sæts
			for (unsigned int i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

				// Nulstil 2D plottets Data Sæt linje tykkelse array
				PlotDataSetLineWidth[i] = 1.0;

			}

		}

		// ----------------- 2D Plot Textur Rendererings Og Plot Routiner ------------------ //

		private: GLvoid RMH_OpenGL_ClearTextureBuffer() {

			// Routinen rydder tilhørende textur buffere

			// Ryd Textur farve og bit buffere
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

		private: GLvoid RMH_OpenGL_Render2DPlotBaseStructure(unsigned int PlotPanelWidth, unsigned int PlotPanelHeight, unsigned int NmbOfXAxesTicks, unsigned int NmbOfYAxesTicks, GLdouble YAxesMaxRange, GLdouble YAxesMinRange, bool Show2DPlorBox, bool Show2DPlotGrid, std::string PlotTitleString, System::String^ TempUnitString) {

			// Routinen rendererer 2D plottets X og Y akse linjer, ticks, Grid linjer, tick labels og akse beskriveler

			// Indstil koordinaterne for 2D plottets X/Y akser 
			XAxesLineX0 = _2DPlotLeftPixelPadding;
			XAxesLineY0 = PlotPanelHeight - _2DPlotBottomPixelPadding;
			XAxesLineX1 = PlotPanelWidth - _2DPlotRightPixelPadding;
			XAxesLineY1 = PlotPanelHeight - _2DPlotBottomPixelPadding;
			YAxesLineX0 = _2DPlotLeftPixelPadding;
			YAxesLineY0 = _2DPlotTopPixelPadding;
			YAxesLineX1 = _2DPlotLeftPixelPadding;
			YAxesLineY1 = PlotPanelHeight - _2DPlotBottomPixelPadding;

			// Indstil Y data start label værdier til range minimum
			YDataLabelValue = YAxesMaxRange;

			// Udregn 2D plottets X og Y aksers pixel længde
			XAxesLinePixelLength = XAxesLineX1 - XAxesLineX0;
			YAxesLinePixelLength = YAxesLineY1 - YAxesLineY0;

			// Udregn afstande imellem hver tick linje på X og Y akserne
			XAxesTickSpacing = XAxesLinePixelLength / (GLfloat)NmbOfXAxesTicks;
			YAxesTickSpacing = YAxesLinePixelLength / (GLfloat)NmbOfYAxesTicks;

			// Udregn Y akse data fordelingen imellem hver Y ticks 
			YDataMaxMinSpacing = (YAxesMaxRange - YAxesMinRange) / (GLdouble)NmbOfYAxesTicks;

			// Render 2D plot title
			RMH_OpenGL_RenderStringOnTexture((XAxesLinePixelLength / 2.0) - _2DPlotTitleXOffsetValue, _2DPlotTopPixelPadding - _2DPlotTitleYOffsetValue, PlotTitleString, PlotTitleColorR, PlotTitleColorG, PlotTitleColorB);

			// Render 2D Plot X-Akse linje
			RMH_OpenGL_RenderLine(XAxesLineX0, XAxesLineY0, XAxesLineX1, XAxesLineY1, _2DPlotAxesAndBoxLineWidth, PlotAxesColorR, PlotAxesColorG, PlotAxesColorB);
			// Render 2D Plot Y-Akse linje
			RMH_OpenGL_RenderLine(YAxesLineX0, YAxesLineY0, YAxesLineX1, YAxesLineY1, _2DPlotAxesAndBoxLineWidth, PlotAxesColorR, PlotAxesColorG, PlotAxesColorB);

			// Skal 2D plottets Box vises
			if (Show2DPlorBox == true) {

				// Renderer 2D Plot omsluttende box
				RMH_OpenGL_RenderLine(XAxesLineX1, XAxesLineY0, XAxesLineX1, _2DPlotTopPixelPadding, _2DPlotAxesAndBoxLineWidth, PlotBoxColorR, PlotBoxColorG, PlotBoxColorB);
				RMH_OpenGL_RenderLine(_2DPlotLeftPixelPadding, _2DPlotTopPixelPadding, XAxesLineX1, _2DPlotTopPixelPadding, _2DPlotAxesAndBoxLineWidth, PlotBoxColorR, PlotBoxColorG, PlotBoxColorB);

			}

			// Kontroller hvilken akse som skal have rendereret flest ticks
			if (NmbOfXAxesTicks > NmbOfYAxesTicks) {

				// Indstil rendererings inerations længden til maksimale X antal ticks
				RenderingLoopIterationLength = NmbOfXAxesTicks;

			}
			else {

				// Indstil rendererings inerations længden til maksimale Y antal ticks
				RenderingLoopIterationLength = NmbOfYAxesTicks;

			}

			// ----------------------------------- Render 2D Plot Tick Labels ------------------------------------ //

			// Loop til og med det maksimale antal ticks for en givet akse
			for (unsigned int i = 0; i < RenderingLoopIterationLength + 1; i++) {

				// Renderer til og med antallet af Y tick linjer
				if (i <= NmbOfYAxesTicks) {

					// Render X-Akse Labels
					RMH_OpenGL_RenderStringOnTexture(YAxesLineX0 - _2DPlotYAxesLabelOffset, YAxesLineY0, RMH_Conversion_SystemStringToStdString(YDataLabelValue.ToString("F2") + " " + TempUnitString), PlotTitleColorR, PlotTitleColorG, PlotTitleColorB);

					// Render hver X-Akse tick linje med udregnede afstand
					YAxesLineY0 = YAxesLineY0 + YAxesTickSpacing;

					// Formater Y label tick data fra data spacing differens
					YDataLabelValue = YDataLabelValue - YDataMaxMinSpacing;

				}

			}

			// Gen-Indstil koordinaterne for 2D plottets X/Y akser 
			XAxesLineX0 = _2DPlotLeftPixelPadding;
			XAxesLineY0 = PlotPanelHeight - _2DPlotBottomPixelPadding;
			XAxesLineX1 = PlotPanelWidth - _2DPlotRightPixelPadding;
			XAxesLineY1 = PlotPanelHeight - _2DPlotBottomPixelPadding;
			YAxesLineX0 = _2DPlotLeftPixelPadding;
			YAxesLineY0 = _2DPlotTopPixelPadding;
			YAxesLineX1 = _2DPlotLeftPixelPadding;
			YAxesLineY1 = PlotPanelHeight - _2DPlotBottomPixelPadding;

			// ------------------------------------- Render 2D Plot Struktur ------------------------------------- //

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil Tick linjernes tykkelse
			glLineWidth(_2DPlotTickLineWidth);

			// Render linjer på textur
			glBegin(GL_LINES);

			// Loop til og med det maksimale antal ticks for en givet akse
			for (unsigned int i = 0; i < RenderingLoopIterationLength + 1; i++) {

				// Renderer til og med antallet af X tick linjer
				if (i <= NmbOfXAxesTicks) {

					// Skal 2D Plottets Grid Vises
					if (Show2DPlotGrid == true && i > 0 && i < NmbOfXAxesTicks) {

						// Indstil Grid linjens farve
						glColor3ub(PlotGridLinesColorR, PlotGridLinesColorG, PlotGridLinesColorB);

						// Render Y aksens Tick linjer - med grid længde
						glVertex2f(XAxesLineX0, _2DPlotTopPixelPadding);
						glVertex2f(XAxesLineX0, XAxesLineY0 + _2DPlotTickLinePixelLength);

					}

					// Indstil tick linjens farve
					glColor3ub(PlotTickLinesColorR, PlotTickLinesColorG, PlotTickLinesColorB);

					// Render Y aksens Tick linjer - uden grid længde
					glVertex2f(XAxesLineX0, XAxesLineY0);
					glVertex2f(XAxesLineX0, XAxesLineY0 + _2DPlotTickLinePixelLength);

					// Render hver Y-Akse tick linje med udregnede afstand
					XAxesLineX0 = XAxesLineX0 + XAxesTickSpacing;

				}

				// Renderer til og med antallet af Y tick linjer
				if (i <= NmbOfYAxesTicks) {

					// Skal 2D Plottets Grid Vises
					if (Show2DPlotGrid == true && i > 0 && i < NmbOfYAxesTicks) {

						// Indstil Grid linjens farve
						glColor3ub(PlotGridLinesColorR, PlotGridLinesColorG, PlotGridLinesColorB);

						// Render X aksens Tick linjer
						glVertex2f(XAxesLineX1, YAxesLineY0);
						glVertex2f(YAxesLineX0 - _2DPlotTickLinePixelLength, YAxesLineY0);

					}

					// Indstil tick linjens farve
					glColor3ub(PlotTickLinesColorR, PlotTickLinesColorG, PlotTickLinesColorB);

					// Render X aksens Tick linjer
					glVertex2f(YAxesLineX0, YAxesLineY0);
					glVertex2f(YAxesLineX0 - _2DPlotTickLinePixelLength, YAxesLineY0);

					// Render hver X-Akse tick linje med udregnede afstand
					YAxesLineY0 = YAxesLineY0 + YAxesTickSpacing;

				}

			}

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

			// --------------------------------------------------------------------------------------------------- //

		}

		private: GLvoid RMH_OpenGL_PlotDataSet(unsigned char DataSetIndex, GLfloat XAxesMaxRange, GLfloat XAxesMinRange, GLfloat YAxesMaxRange, GLfloat YAxesMinRange, GLfloat LineWidth, GLubyte LineColorR, GLubyte LineColorG, GLubyte LineColorB) {

			// Routinen plotter en serie af data sæt på 2D plottet

			// Lokale variabler
			GLfloat FirstDataValue = 0.0;
			GLfloat SecondDataValue = 0.0;
			AxesToPixelCoordFormat FirstDataPointCoords;
			AxesToPixelCoordFormat SecondDataPointCoords;

			// Nulstil 2D Plottets Y-Akse Max/Min Range varaibler
			PlotDataSets[DataSetIndex].MaximumDataValue = _2DPlotYAxesMaximumRangeResetValue;
			PlotDataSets[DataSetIndex].MinimumDataValue = _2DPlotYAxesMinimumRangeResetValue;

			// Loop til og med længden af data arrayet
			for (unsigned int i = PlotDataSets[DataSetIndex].PlotLineDataIndexRenderOffset; i < XAxesMaxRange - 1; i++) {

				// Læs første og anden input data værdier
				FirstDataValue = PlotDataSets[DataSetIndex].PlotDataPoints[i];
				SecondDataValue = PlotDataSets[DataSetIndex].PlotDataPoints[i + 1];

				// Opdater 2D Plottets Maximum og Minimum Y Range variabler fra dataens Max/Min værdier
				if (FirstDataValue > PlotDataSets[DataSetIndex].MaximumDataValue) { PlotDataSets[DataSetIndex].MaximumDataValue = FirstDataValue; }
				if (FirstDataValue < PlotDataSets[DataSetIndex].MinimumDataValue) { PlotDataSets[DataSetIndex].MinimumDataValue = FirstDataValue; }

				// Konverter Plot punkt data koordinater til pixel punkt koordinater
				FirstDataPointCoords = RMH_OpenGL_2DPLotConvertXYAxesCoordinatesToPixelCoordinates(i, FirstDataValue, XAxesMaxRange, XAxesMinRange, YAxesMaxRange, YAxesMinRange);
				SecondDataPointCoords = RMH_OpenGL_2DPLotConvertXYAxesCoordinatesToPixelCoordinates(i + 1, SecondDataValue, XAxesMaxRange, XAxesMinRange, YAxesMaxRange, YAxesMinRange);

				// Plot data linje med valgte tykkelse og farve
				RMH_OpenGL_RenderLine(FirstDataPointCoords.XPixelCoordinate, FirstDataPointCoords.YPixelCoordinate, SecondDataPointCoords.XPixelCoordinate, SecondDataPointCoords.YPixelCoordinate, LineWidth, LineColorR, LineColorG, LineColorB);

			}

			// Kontroller om værdien af Linje rendering index offsettet er 0
			if (PlotDataSets[DataSetIndex].PlotLineDataIndexRenderOffset != 0) {

				// Inkrementer Linje rendering index offsettet
				PlotDataSets[DataSetIndex].PlotLineDataIndexRenderOffset = PlotDataSets[DataSetIndex].PlotLineDataIndexRenderOffset - 1;

			}

		}

		private: GLvoid RMH_OpenGL_PlotDataSets() {

			// Routinen plotter aktiverede Plot data sæts

			// Lokale variabler
			unsigned int RenderingOrderIndex = 0;

			// Loop til og med det maksimale antal 2D Plot Data sæts
			for (unsigned int i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

				// Er data sættet aktiverede og skal plottes
				if (EnabledPlotDataSets[i] == true) {

					// Plot Data sættet med valgte linje tykkelse og linje farve
					RMH_OpenGL_PlotDataSet(i, _2DPlotXAxesLength, 0, PlotYAxesMaximumRangeValue, PlotYAxesMinimumRangeValue, PlotDataSetLineWidth[i], PlotDataSetLineColorR[i], PlotDataSetLineColorG[i], PlotDataSetLineColorB[i]);

					// Læs 2D Plottets Data Set rendererings orden
					PlotDataSetRenderingOrder[RenderingOrderIndex] = i;

					// Inkrementer Renderings Orden index
					RenderingOrderIndex = RenderingOrderIndex + 1;

				}

			}

		}

		private: GLvoid RMH_OpenGL_RenderDataLoggingIndicatorLabelWithTimer(GLfloat LabelX, GLfloat LabelY, unsigned long MilliSecondsValue, bool LoggingDataFlag) {

			// Routinen rendererer en data logging indikator

			// Lokale variabler
			unsigned int HoursValue = 0;
			unsigned int MinutesValue = 0;
			unsigned int SecondsValue = 0;
			unsigned int MilliSecValue = 0;

			// Kontroller om data logging er aktiv
			if (LoggingDataFlag == true) {

				// Konverter Millisek til timer
				HoursValue = ((MilliSecondsValue / 3600000) % 720);
				// Konverter Millisek til Minutter
				MinutesValue = ((MilliSecondsValue / 60000) % 60);
				// Konverter Millisek til Sekunder
				SecondsValue = ((MilliSecondsValue / 1000) % 60);
				// Konverter Millisek til Millisek
				MilliSecValue = MilliSecondsValue % 1000;

				// Konverter Timer, Minutter, Sekundter og millisekundter til unsigned char
				DataLoggingDisplayStringChar[25] = (HoursValue / 100) % 10 + 48;
				DataLoggingDisplayStringChar[26] = (HoursValue / 10) % 10 + 48;
				DataLoggingDisplayStringChar[27] = HoursValue % 10 + 48;
				DataLoggingDisplayStringChar[29] = (MinutesValue / 10) % 10 + 48;
				DataLoggingDisplayStringChar[30] = MinutesValue % 10 + 48;
				DataLoggingDisplayStringChar[32] = (SecondsValue / 10) % 10 + 48;
				DataLoggingDisplayStringChar[33] = SecondsValue % 10 + 48;
				DataLoggingDisplayStringChar[35] = (MilliSecValue / 100) % 10 + 48;
				DataLoggingDisplayStringChar[36] = (MilliSecValue / 10) % 10 + 48;
				DataLoggingDisplayStringChar[37] = MilliSecValue % 10 + 48;

				// Render aktiv data logging label
				RMH_OpenGL_RenderStringOnTextureChar(LabelX, LabelY, DataLoggingDisplayStringChar, 38, 50, 205, 50);

			}
			else {

				// Render inaktiv data logging label
				RMH_OpenGL_RenderStringOnTextureChar(LabelX, LabelY, DataLoggingDisplayStringChar, 38, 60, 60, 60);

			}

		}

		// ----------------- Samlede 2D Plot Grafiske Rendererings Routine ----------------- //

		public: GLvoid RMH_OpenGL_Enable2DPlotBox(bool BoxLinesEnableFlag) {

			// Routinen aktiverer eller deaktiverer 2D plottets Box linjer

			// Opdater 2D Plottets Box linjers flag
			Show2DPlotBoxFlag = BoxLinesEnableFlag;

		}

		public: GLvoid RMH_OpenGL_Enable2DPlotGridLines(bool GridLinesEnableFlag) {

			// Routinen aktiverer eller deaktiverer 2D plottets Grid linjer

			// Opdater 2D Plottets Grid linjers flag
			Show2DPlotGridFlag = GridLinesEnableFlag;

		}

		public: GLvoid RMH_OpenGL_Set2DPlotNumberOfXTicks(System::Object^ sender) {

			// Routinen indstiller antallet af 2D plottets X Ticks

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ NumberOfXticks = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag
			unsigned char NewNumberOfXticks = Convert::ToInt16(NumberOfXticks->Tag);

			// Opdater antallet af X Ticks
			XAxesNumberOfTicks = NewNumberOfXticks;

		}

		public: GLvoid RMH_OpenGL_Set2DPlotNumberOfYTicks(System::Object^ sender) {

			// Routinen indstiller antallet af 2D plottets Y Ticks

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ NumberOfYticks = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag
			unsigned char NewNumberOfYticks = Convert::ToInt16(NumberOfYticks->Tag);

			// Opdater antallet af Y Ticks
			YAxesNumberOfTicks = NewNumberOfYticks;

		}

		public: GLvoid RMH_OpenGL_SetDataSetLineWidth(unsigned char DataSetIndex, GLfloat DataSetLineWidth) {

			// Routinen indstiller det valgte data sæts linje tykkelse ved plotning

			// Kontroller om input index værdien er indenfor det maksimale antal Plot data sæts
			if (DataSetIndex < 0 || DataSetIndex > _2DPlotMaxNumberOfDataSets) {}
			else {

				// Indstil Linje tykkelse for data sættet
				PlotDataSetLineWidth[DataSetIndex] = DataSetLineWidth;

			}

		}

		public: GLvoid RMH_OpenGL_SetDataSetLineColor(unsigned char DataSetIndex, GLubyte LineColorR, GLubyte LineColorG, GLubyte LineColorB) {

			// Routinen indstiller det valgte data sæts linje tykkelse ved plotning

			// Kontroller om input index værdien er indenfor det maksimale antal Plot data sæts
			if (DataSetIndex < 0 || DataSetIndex > _2DPlotMaxNumberOfDataSets) {}
			else {

				// Indstil Linje farven for data sættet
				PlotDataSetLineColorR[DataSetIndex] = LineColorR;
				PlotDataSetLineColorG[DataSetIndex] = LineColorG;
				PlotDataSetLineColorB[DataSetIndex] = LineColorB;

			}

		}

		public: GLvoid RMH_OpenGL_AddDataPointToPlotDataSet(GLfloat PointData, unsigned char DataSetIndex) {

			// Routinen Tilføjer en måling til valgte Plot Data Sæt ved at shifte det ind på sidste plads i buffer arrayet
	
			// Er det valgte data sæt aktiverede til plotning
			if (EnabledPlotDataSets[DataSetIndex] == true) {

				// Kontroller om input index værdien er indenfor det maksimale antal Plot data sæts
				if (DataSetIndex < 0 || DataSetIndex > _2DPlotMaxNumberOfDataSets) {}
				else {

					// Shift alle buffer arrayets dataer en position til venstre
					for (unsigned int i = 0; i < _2DPlotXAxesLength - 1; i++) {

						// Shift index en gang til venstre
						PlotDataSets[DataSetIndex].PlotDataPoints[i] = PlotDataSets[DataSetIndex].PlotDataPoints[i + 1];

					}

					// Tilføj nyeste data til buffer arrayets sidste index position
					PlotDataSets[DataSetIndex].PlotDataPoints[_2DPlotXAxesLength - 1] = PointData;

				}

			}

		}

		public: GLvoid RMH_OpenGL_EnablePlotOfDataSetx(unsigned char DataSetIndex, bool EnablePlotFlag) {

			// Routinen aktiver Plotningen af en valgt DataSæt index

			// Kontroller om input index værdien er indenfor det maksimale antal Plot data sæts
			if (DataSetIndex < 0 || DataSetIndex > _2DPlotMaxNumberOfDataSets) {}
			else {

				// Aktiver Data sæt index
				EnabledPlotDataSets[DataSetIndex] = EnablePlotFlag;

			}

		}

		public: GLvoid RMH_OpenGL_ReadDataSetsMaxMinDataRangeValues() {

			// Routinen læser Maximum og Minimums værdien for alle aktive data sæt og indstiller plottets Y-Akse Range varaibler
			// Kan kaldes i seperat process...

			// Nulstil 2D plottets Y-Akse Range varaibler til start værdier
			PlotYAxesMaximumRangeValue = _2DPlotYAxesMaximumRangeResetValue;
			PlotYAxesMinimumRangeValue = _2DPlotYAxesMinimumRangeResetValue;

			// Loop til og med det maksimale antal 2D Plot Data sæts
			for (unsigned char i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

				// Er data sættet aktiverede og skal plottes
				if (EnabledPlotDataSets[i] == true) {

					// Læs data sættets maksimale data værdi, Hvis denne er højere end den nuværendelæste
					if (PlotDataSets[i].MaximumDataValue > PlotYAxesMaximumRangeValue) {

						// Indstil plottets maksimale Y-akse range værdi 
						PlotYAxesMaximumRangeValue = PlotDataSets[i].MaximumDataValue;

					}

					// Læs data sættets minimale data værdi, Hvis denne er lavere end den nuværende læste
					if (PlotDataSets[i].MinimumDataValue < PlotYAxesMinimumRangeValue) {

						// Indstil plottets minimale Y-akse range værdi 
						PlotYAxesMinimumRangeValue = PlotDataSets[i].MinimumDataValue;

					}

				}

			}

		}

		public: GLvoid RMH_OpenGL_ResetDataSetLineDataIndexRenderOffset(unsigned char DataSetIndex) {

			// Routinen nulstiller det valgte data sæts linje data rendererings index offset værdi

			// Kontroller om input index værdien er indenfor det maksimale antal Plot data sæts
			if (DataSetIndex < 0 || DataSetIndex > _2DPlotMaxNumberOfDataSets) {}
			else {

				// Aktiver Data sæt index
				PlotDataSets[DataSetIndex].PlotLineDataIndexRenderOffset = _2DPlotXAxesLength;

			}

		}

		public: GLvoid RMH_OpenGL_Clear2DPlot() {

			// Routinen nulstiller 2D plottets data og rydder 2D plottet

			// Nulstil 2D plottets Y-Akse Range varaibler til start værdier
			PlotYAxesMaximumRangeValue = _2DPlotYAxesMaximumRangeResetValue;
			PlotYAxesMinimumRangeValue = _2DPlotYAxesMinimumRangeResetValue;

			// Loop til og med det maksimale antal 2D Plot Data sæts
			for (unsigned char i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

				// NUlstil Data sæts Max/Min Data Værdier
				PlotDataSets[i].MaximumDataValue = PlotYAxesMaximumRangeValue;
				PlotDataSets[i].MinimumDataValue = PlotYAxesMinimumRangeValue;

				// Nulstil data sæt linje data rendererings index offset værdi
				RMH_OpenGL_ResetDataSetLineDataIndexRenderOffset(i);

			}

		}

		public: GLvoid RMH_OpenGL_Get2DPlotDataSetRenderingOrder(unsigned char *DataSetRenderingOrder) {

			// Routinen retunerer 2D Plottets Rendererings ordens index array som pointer

			// Peg på Rendererings ordens index arrayet
			DataSetRenderingOrder = &PlotDataSetRenderingOrder[0];

		}

		public: GLboolean RMH_OpenGL_ReadPlotDataSetEnabledState(unsigned char DataSetIndex) {

			// Routinen læser om den valgte Plot Data Set er aktiverede eller deaktiverede

			// Lokale variabler
			bool DataSetEnableFlag = false;

			// Kontroller om input index værdien er indenfor det maksimale antal Plot data sæts
			if (DataSetIndex < 0 || DataSetIndex > _2DPlotMaxNumberOfDataSets) {}
			else {

				// Læs Plot Data Sæt AKtiverings flag
				DataSetEnableFlag = EnabledPlotDataSets[DataSetIndex];

			}

			// Retuner Plot Data Sæt AKtiverings flag
			return DataSetEnableFlag;

		}

		public: GLvoid RMH_OpenGL_SetDataLoggingLabelStateAndTimer(bool DataLoggingActiveFlag, unsigned long MilliSecondsValue) {

			// Routinen opdaterer stadiet for 2D Plottets data logging label
			// Om aktiv data loggging er aktiverede eller deaktiverede

			// Opdater data logging flag
			DataLoggingFLag = DataLoggingActiveFlag;

			// Opdater private klasse logging timer variabler
			LoggingTimerLabelMilliSecValue = MilliSecondsValue;

		}
		
		public: GLvoid  RMH_2DPlot_EnablePlotMouseCursorPointData(System::Object^ sender) {

			// Routinen aktiverer eller deaktiverer Mus Cursorens Plot punkt dataen

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ EnableDisableTagValue = (System::Windows::Forms::ToolStripMenuItem^)sender;
			// Læs Sub Context Menu identifikations tag
			unsigned int MouseCursorDataFlag = Convert::ToInt32(EnableDisableTagValue->Tag);

			// Aktiverer eller deaktiver Mus Cursorens Plot punkt datae rendereringen
			EnablePlotMouseCursorDataFlag = (bool)MouseCursorDataFlag;

		}

		private: GLvoid RMH_2DPlot_RenderPlotMouseCursorPointData(unsigned int PlotPanelWidth, unsigned int PlotPanelHeight, System::String^ TempUnitString) {

			// Routinen rendererer Mus Cursorens Plot punkt dataen som et label 
			
			// Lokale varaibler
			System::String^ LabelString;
			GLfloat PlotAreaPixelHeight = 0.0;	
			GLfloat MouseCursorYTemperature = 0.0;
			GLfloat MouseCursorPlotYCoordinate = 0.0;
			GLfloat PlotYAxesPixelTemperatureStep = 0.0;
			
			// Skal Mus Cursorens Plot punkt data rendereres
			if (EnablePlotMouseCursorDataFlag == true) {

				// Kontroller om Mus Cursoren er inden for X-aksens grænser
				if (MousePointerXPosition > _2DPlotLeftPixelPadding && MousePointerXPosition < PlotPanelWidth - _2DPlotRightPixelPadding) {
					
					// Kontroller om Mus Cursoren er inden for Y-aksens grænser
					if (PlotPanelHeight - MousePointerYPosition >= _2DPlotBottomPixelPadding && PlotPanelHeight - MousePointerYPosition <= PlotPanelHeight - _2DPlotTopPixelPadding) {

						// Udregn 2D plottets aktuelle pixel højde
						PlotAreaPixelHeight = (PlotPanelHeight - _2DPlotBottomPixelPadding) - _2DPlotTopPixelPadding;
						// Udregn 2D Plottets Y-Akses Pixel Temperatur Step Opløsnings værdi
						PlotYAxesPixelTemperatureStep = (PlotYAxesMaximumRangeValue - PlotYAxesMinimumRangeValue) / PlotAreaPixelHeight;
						// Udregn Mus Cursorens Aktuelle 2D Plot Y-Akse Pixel Koordinat
						MouseCursorPlotYCoordinate = (PlotPanelHeight - MousePointerYPosition) - _2DPlotBottomPixelPadding;
						// Udregn Mus Cursorens Aktuelle Plot Y Positions Temperatur værdi 
						MouseCursorYTemperature = (MouseCursorPlotYCoordinate * PlotYAxesPixelTemperatureStep) + PlotYAxesMinimumRangeValue;

						// Konverter udregnede temperatur værdi til string
						LabelString = "Temperature: " + MouseCursorYTemperature.ToString("F2") + " " + TempUnitString;
					
					}
					else {

						// Opdater Rendereret String (Udenfor plot arealet)
						LabelString = "Temperature: N/A " + TempUnitString;

					}

				}
				else {

					// Opdater Rendereret String (Udenfor plot arealet)
					LabelString = "Temperature: N/A " + TempUnitString;

				}

				// Renderer Mus Cursorens Plot punkt data label
				RMH_OpenGL_RenderStringOnTexture(MousePointerXPosition + MouseCursorDataLabelXOffset, MousePointerYPosition + MouseCursorDataLabelYOffset, RMH_Conversion_SystemStringToStdString(LabelString), MouseCursorDataLabelColorR, MouseCursorDataLabelColorG, MouseCursorDataLabelColorB);

			}

		}

		public: GLvoid RMH_OpenGL_Render2DPlot(unsigned int PlotPanelWidth, unsigned int PlotPanelHeight, System::String^ TempUnitString) {

			// Routinen rendererer et 2 dimensionelt X/Y plot fra givet input data

			// Læs Nuværende textur Panels pixel højde og bredde
			CurrentTexturePanelWidth = (GLfloat)PlotPanelWidth;
			CurrentTexturePanelHeight = (GLfloat)PlotPanelHeight;

			// Udregn Pixel offsettet imellem textur området og tilhørende GUI panel
			TextureToPanelWidthOffset = OpenGLWindowWidth - CurrentTexturePanelWidth;
			TextureToPanelHeightOffset = OpenGLWindowHeight - CurrentTexturePanelHeight;

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();
			// Ryd Textur farve og bit buffere
			RMH_OpenGL_ClearTextureBuffer();
			// Opdater Textur Field Of View
			RMH_OpenGL_UpdateTextureFieldOfView(CurrentTexturePanelWidth, CurrentTexturePanelHeight);

			// Opdater Textur View port til midten af surface plottet
			glViewport(0, TextureToPanelHeightOffset, CurrentTexturePanelWidth, CurrentTexturePanelHeight);

			// Roter Textur Til at matche korrekt billede orientation
			glTranslatef(0.0f, (GLfloat)CurrentTexturePanelHeight, 0.0f);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

			// ------------------------------------ Render 2D Plot ------------------------------------ //

			// Renderer 2D plottets X og Y akse linjer, ticks, Grid linjer, tick labels og akse beskriveler
			RMH_OpenGL_Render2DPlotBaseStructure(PlotPanelWidth, PlotPanelHeight, XAxesNumberOfTicks, YAxesNumberOfTicks, PlotYAxesMaximumRangeValue, PlotYAxesMinimumRangeValue, Show2DPlotBoxFlag, Show2DPlotGridFlag, "2D Temperature Measurements Plot", TempUnitString);

			// Plot aktiverede data sæts
			RMH_OpenGL_PlotDataSets();

			// Render Data Logging indikator label
			RMH_OpenGL_RenderDataLoggingIndicatorLabelWithTimer(_2DPlotLeftPixelPadding, (_2DPlotTopPixelPadding / 2.0) + _2DPlotIndicatorLabelYOffset, LoggingTimerLabelMilliSecValue, DataLoggingFLag);

			// Renderer Mus Cursorens Plot punkt dataen som et label
			RMH_2DPlot_RenderPlotMouseCursorPointData(PlotPanelWidth, PlotPanelHeight, TempUnitString);

			// ---------------------------------------------------------------------------------------- //

			// Marker enden på en OpenGL rendererins sekvens
			RMH_OpenGL_RenderingFinishedMark();

		}

		// ------------ Textur Panel Interaktions Cursor Event Callback Routiner ----------- //

		private: GLvoid TexturePanel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Opdater overlay panel click flag
			OverlayPanelIsClick = true;

			// Kontroller om Venstre Mus Knap er blevet trykket
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {

				// Toggel Mus Cursorens Plot punkt datae rendereringen
				EnablePlotMouseCursorDataFlag = EnablePlotMouseCursorDataFlag ^ 1;

			}

		}

		private: GLvoid TexturePanel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Opdater overlay panel click flag
			OverlayPanelIsClick = false;

		}

		private: GLvoid TexturePanel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Læs Mus Cursor Positionen
			MousePointerXPosition = e->X;
			MousePointerYPosition = e->Y;

			// Hvis der endnu ikke er blevet klippet på panalet
			if (OverlayPanelIsClick == false) {

				// Fortsæt ikke
				return;

			}

		}

		private: GLvoid TexturePanel_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {



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

		}

		// --------------------------------------------------------------------------------- //

		private:

		// ------------- Yderligerer OpenGL Håndterings Og Opsætnings Routiner ------------- //

		~RMHOpenGL2DPlot(GLvoid) {

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