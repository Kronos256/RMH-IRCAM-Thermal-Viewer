#pragma once

/*
 *  RMH_LiveView_ZoomWindow.h
 *
 *  Author: Rune Mark Glendorf
 *  Date: September 2024
 *
 */

// Inkluderede Biblioteker
#include <windows.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include <glfw3.h>
#include <iostream>
#include "RMH_Winforms_Library.h"
#include "RMH_MathConversions_Library.h"
#include "GlobalObjectsAndVariables.h"

// Tilhørende Name spaces
using namespace System;
using namespace System::Windows::Forms;
using namespace std;

// Global statisk PBO Buffere ID varaibel
static GLuint PBOIDs[2];

// OpenGL Klasse definition
namespace LiveViewZoomWindow {

	// ---------------------------------- Globale Klasse Struktur Objekter --------------------------------- //

	// ----------------------------------------------------------------------------------------------------- //

	public ref class RMHLiveViewZoomWindow : public System::Windows::Forms::NativeWindow {

	private:

		// Private Globale klasse objekter og variabler
		private: HDC m_hDC;
		private: HGLRC m_hglrc;
		private: GLuint BaseFont;
		private: GLint iPixelFormat;
		private: GLuint* LiveViewZoomTexture;
		private: GLdouble CurrentTexturePanelWidth;
		private: GLdouble CurrentTexturePanelHeight;
		private: GLfloat TextureToPanelWidthOffset = 0.0;
		private: GLfloat TextureToPanelHeightOffset = 0.0;
		private: CreateParams^ ControlParams = gcnew CreateParams;

		// Live View Zoom vindue Rendererings Positions Variabler
		private: GLdouble TextureResScaleFactor = 32;
		private: GLdouble LiveViewZoomWindowPosX0 = 0.0;
		private: GLdouble LiveViewZoomWindowPosY0 = 0.0;
		private: GLdouble LiveViewZoomWindowPosX1 = 0.0;
		private: GLdouble LiveViewZoomWindowPosY1 = 0.0;
		private: GLdouble TotalTextureScalableWidth;
		private: GLdouble TotalTextureScalableHeight;
		private: GLdouble LiveViewZoomWindowRotationDegrees = 0.0;
		private: GLdouble AspectRatioWidthOffSet;
		private: GLdouble AspectRatioHeightOffSet;
		private: GLdouble CurrentPanelWidthFixedAspect;
		private: GLdouble CurrentPanelHeightFixedAspect;
		private: unsigned int LiveViewZoomTextureWidth;
		private: unsigned int LiveViewZoomTextureHeight;
		private: unsigned int UltraResolutionTextureScaleFactor = 2;
		private: bool UntraResolutionModeEnabledFlag = false;

			   

		private: GLdouble ImageDataPixelWidth;
		private: GLdouble ImageDataPixelHeight;
		private: GLfloat MovableLineQuadrant1LabelXOffset = -10.0;
		private: GLfloat MovableLineQuadrant1LabelYOffset = 3.0;
		private: GLfloat MovableLineQuadrant2LabelXOffset = 2.0;
		private: GLfloat MovableLineQuadrant2LabelYOffset = 3.0;
		private: GLfloat MovableLineQuadrant3LabelXOffset = 2.0;
		private: GLfloat MovableLineQuadrant3LabelYOffset = -2.0;
		private: GLfloat MovableLineQuadrant4LabelXOffset = -10.0;
		private: GLfloat MovableLineQuadrant4LabelYOffset = -2.0;
		private: bool LocalAspectRatioFlag = false;
		private: GLdouble ImageDataPixelAspectRatio;
		private: bool EnableLabelBackgroundFlag = true;
		private: GLubyte CommonLabelBackgroundAlpha = 180;
		private: GLubyte LabelBackgroundColorR = 35;
		private: GLubyte LabelBackgroundColorG = 35;
		private: GLubyte LabelBackgroundColorB = 35;
		private: GLfloat LabelBackgroundXOffset = 0.2;
		private: GLfloat LabelBackgroundYOffset = 1.1;
		private: GLfloat LabelBackgroundWidth = 8.5;
		private: GLfloat LabelBackgroundHeight = 1.5;
		private: GLfloat CrosshairSize = 2.0;
		private: unsigned short CrosshairLineWidth = 2;
		private: GLubyte CommonLabelColorR = 255;
		private: GLubyte CommonLabelColorG = 255;
		private: GLubyte CommonLabelColorB = 255;
	



	public:

		// ------------------------- 2D Plot Konstruktur Routiner -------------------------- //

		RMHLiveViewZoomWindow(System::Windows::Forms::Panel^ TexturePanel) {

			// Routinen er Initiliserings Routinen for klassen
			
			// Udregn den totale skallerbar textur hæjde og bredde
			TotalTextureScalableWidth = 1.0 / ((GLdouble)TexturePanel->Width * TextureResScaleFactor);
			TotalTextureScalableHeight = 1.0 / ((GLdouble)TexturePanel->Height * TextureResScaleFactor);

			// Sæt positionen af kontrol klassen
			ControlParams->X = 0;
			ControlParams->Y = 0;
			ControlParams->Width = (GLdouble)TexturePanel->Width * TextureResScaleFactor;
			ControlParams->Height = (GLdouble)TexturePanel->Height * TextureResScaleFactor;
	
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

		private: GLvoid RMH_OpenGL_ClearTextureBuffer() {

			// Routinen rydder tilhørende textur buffere

			// Ryd Textur farve og bit buffere
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}

		private: GLvoid RMH_OpenGL_UpdateTextureFieldOfView(unsigned int FrameWidth, unsigned int FrameHeight) {

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
			PlaneXLook = (GLdouble)LiveViewZoomTextureWidth * 0.5;
			PlaneYLook = (GLdouble)LiveViewZoomTextureHeight * 0.5;

			// Udregn textur Aspect ratio
			PlaneAspectRatio = ((GLdouble)LiveViewZoomTextureWidth / (GLdouble)LiveViewZoomTextureHeight);

			// Udregn affstanden imellem Frame data planet og textur planet
			PlaneDistance = (GLdouble)LiveViewZoomTextureHeight * TanHalfFieldOfView;

			// Opdater Texturens syns vinkel
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(PlaneFieldOfView, PlaneAspectRatio, 0.1, 500.0);
			gluLookAt(PlaneXLook, PlaneYLook, PlaneDistance * 0.5, PlaneXLook, PlaneYLook, 0, 0, 1, 0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

		}

		public: GLvoid RMH_OpenGL_InitLiveViewZoomWindow(unsigned int FrameWidth, unsigned int FrameHeight) {

			// Routinen benyttes til at opsætte en OpenGL textur til grafisk renderering

			// Sæt Textur Parameter og reference varaibler
			LiveViewZoomTexture = new GLuint[1];
			LiveViewZoomTextureWidth = FrameWidth;
			LiveViewZoomTextureHeight = FrameHeight;

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();

			//Generer Textur ID
			glGenTextures(1, LiveViewZoomTexture);

			// Bind Texturen til genereret textus ID
			glBindTexture(GL_TEXTURE_2D, LiveViewZoomTexture[0]);

			// Alloker hukommelse til textur generering (FrameWidth * UltraResolutionTextureScaleFactor, FrameHeight * UltraResolutionTextureScaleFactor - Ultra Opløsning)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, FrameWidth * UltraResolutionTextureScaleFactor, FrameHeight * UltraResolutionTextureScaleFactor, 0, GL_RGB, GL_UNSIGNED_SHORT, nullptr);

			// Konfigurer textur wrapping og filter indstillinger
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Afbind textuxen, forhindre ændring af textur
			glBindTexture(GL_TEXTURE_2D, 0);

			// ------------------------------------ Generer Og Bind PBO (Pixel Buffer Object) ------------------------------------ //

			// Generer PBOernes (Pixel Buffer Object) IDer
			__glewGenBuffers(2, PBOIDs);

			// Loop igennem begge genereret PBO Buffere (Double Buffer Objekt)
			for (int i = 0; i < 2; ++i) {

				// Bind buffer til tilhørende PBO ID
				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PBOIDs[i]);

				// Generer nyt data lager for begge PBO buffere (GL_RGB Format W * H * RGB * Size)
				glBufferData(GL_PIXEL_UNPACK_BUFFER, (FrameWidth * UltraResolutionTextureScaleFactor) * (FrameHeight * UltraResolutionTextureScaleFactor) * 3 * sizeof(unsigned short), nullptr, GL_STREAM_DRAW);

			}

			// Afbind Pixel Buffer Objecter
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

			// ------------------------------------------------------------------------------------------------------------------- //

		}

		// ---------------- CrossHair Rendererings Og Håndterings Routiner ----------------- //
	
		private: GLvoid RMH_LiveView_glPrint(const char* CharArray) {

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

		private: GLvoid RMH_LiveView_RenderStringOnTexture(GLfloat StringX, GLfloat StringY, std::string DisplayString, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen rendererer et givet string på et OpenGL Textur

			// Konfigurer Textens Farve
			glColor3ub(ColorR, ColorG, ColorB);

			// Indstil textens position på textur
			glRasterPos2f(StringX, StringY);

			// Render givet string på textur
			RMH_LiveView_glPrint(DisplayString.c_str());

		}
		
		public: GLvoid RMH_LiveView_EnableLabelBackground(bool EnableFlag) {

			// Routinen aktiverer rendereringen af en baggrunds rektangel til alle rendererede text labels

			// Opdater Label Baggrunds aktiverings flag
			EnableLabelBackgroundFlag = EnableFlag;

		}

		public: GLvoid RMH_LiveView_ChangeRenderedLabelsColor(GLubyte LabelColorR, GLubyte LabelColorG, GLubyte LabelColorB) {

			// Routinen opdaterer farven for alle rendereret text labels

			// Opdater farven for alle rendereret text labels
			CommonLabelColorR = LabelColorR;
			CommonLabelColorG = LabelColorG;
			CommonLabelColorB = LabelColorB;

		}

		public: GLvoid RMH_LiveView_ChangeLabelBackgroundColor(GLubyte BackgroundColorR, GLubyte BackgroundColorG, GLubyte BackgroundColorB) {

			// Routinen opdaterer label baggrundens farve

			// Indstil label baggrundens farve
			LabelBackgroundColorR = BackgroundColorR;
			LabelBackgroundColorG = BackgroundColorG;
			LabelBackgroundColorB = BackgroundColorB;

		}

		public: GLvoid RMH_LiveView_RenderCrossHairWithLabel(GLfloat X, GLfloat Y, bool EnableLabel, System::String^ LabelString, GLubyte CrosshairColorR, GLubyte CrosshairColorG, GLubyte CrosshairColorB) {

			// Routinen Rendererer et Crosshair på Texturen, med eller uden tilhørende label

			// Lokale variabler
			GLfloat QuadrantXOffset = 0.0;
			GLfloat QuadrantYOffset = 0.0;

			// Skal en laben tilføjes til crosshairet
			if (EnableLabel == true) {

				// Kontroller om positionen er i kvardrant 1
				if (X >= ((GLfloat)ImageDataPixelWidth * 0.5) && Y <= ((GLfloat)ImageDataPixelHeight * 0.5)) {

					// Kontroller Live View Roterings Indstillingen
					if (LiveViewZoomWindowRotationDegrees == 0) {

						// Opdater Kvardrant Offset værdier - 0 grader rotation
						QuadrantXOffset = MovableLineQuadrant1LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant1LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 90) {

						// Opdater Kvardrant Offset værdier - 90 grader rotation
						QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant2LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 180) {

						// Opdater Kvardrant Offset værdier - 180 grader rotation
						QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant3LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 270) {

						// Opdater Kvardrant Offset værdier - 270 grader rotation
						QuadrantXOffset = MovableLineQuadrant4LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant4LabelYOffset;

					}

				}

				// Kontroller om positionen er i kvardrant 2
				if (X <= ((GLfloat)ImageDataPixelWidth * 0.5) && Y <= ((GLfloat)ImageDataPixelHeight * 0.5)) {

					// Kontroller Live View Roterings Indstillingen
					if (LiveViewZoomWindowRotationDegrees == 0) {

						// Opdater Kvardrant Offset værdier - 0 grader rotation
						QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant2LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 90) {

						// Opdater Kvardrant Offset værdier - 90 grader rotation
						QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant3LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 180) {

						// Opdater Kvardrant Offset værdier - 180 grader rotation
						QuadrantXOffset = MovableLineQuadrant4LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant4LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 270) {

						// Opdater Kvardrant Offset værdier - 1270 grader rotation
						QuadrantXOffset = MovableLineQuadrant1LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant1LabelYOffset;

					}

				}

				// Kontroller om positionen er i kvardrant 3
				if (X <= ((GLfloat)ImageDataPixelWidth * 0.5) && Y >= ((GLfloat)ImageDataPixelHeight * 0.5)) {

					// Kontroller Live View Roterings Indstillingen
					if (LiveViewZoomWindowRotationDegrees == 0) {

						// Opdater Kvardrant Offset værdier - 0 grader rotation
						QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant3LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 90) {

						// Opdater Kvardrant Offset værdier - 90 grader rotation
						QuadrantXOffset = MovableLineQuadrant4LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant4LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 180) {

						// Opdater Kvardrant Offset værdier - 180 grader rotation
						QuadrantXOffset = MovableLineQuadrant1LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant1LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 270) {

						// Opdater Kvardrant Offset værdier - 270 grader rotation
						QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant2LabelYOffset;

					}

				}

				// Kontroller om positionen er i kvardrant 4
				if (X >= ((GLfloat)ImageDataPixelWidth * 0.5) && Y >= ((GLfloat)ImageDataPixelHeight * 0.5)) {

					// Kontroller Live View Roterings Indstillingen
					if (LiveViewZoomWindowRotationDegrees == 0) {

						// Opdater Kvardrant Offset værdier - 0 grader rotation
						QuadrantXOffset = MovableLineQuadrant4LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant4LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 90) {

						// Opdater Kvardrant Offset værdier - 90 grader rotation
						QuadrantXOffset = MovableLineQuadrant1LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant1LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 180) {

						// Opdater Kvardrant Offset værdier - 180 grader rotation
						QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant2LabelYOffset;

					}
					if (LiveViewZoomWindowRotationDegrees == 270) {

						// Opdater Kvardrant Offset værdier - 270 grader rotation
						QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant3LabelYOffset;

					}

				}

			}

			// Kontroller valgt indstilling for Aspect Ratio
			if (LocalAspectRatioFlag == true) {

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewZoomWindowRotationDegrees == 0) {

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewZoomWindowPosX0 <= 0.0) {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						Y = Y * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight;
						Y = Y + AspectRatioHeightOffSet;

						// Udregn Crosshair X Kordinat ved skallering af textur vinduet
						X = X * CurrentTexturePanelWidth * TotalTextureScalableWidth;

					}
					else {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
						Y = Y * CurrentTexturePanelHeight * TotalTextureScalableHeight;

						// Udregn Crosshair X Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						X = X * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth;
						X = X + AspectRatioWidthOffSet;

					}

				}
				if (LiveViewZoomWindowRotationDegrees == 90) {

					// Skaller X/Y koordinater
					X = X / ImageDataPixelAspectRatio;
					Y = Y * ImageDataPixelAspectRatio;

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewZoomWindowPosX0 <= 0.0) {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						X = X * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight;

						// Udregn Crosshair X Kordinat ved skallering af textur vinduet
						Y = Y * CurrentTexturePanelWidth * TotalTextureScalableWidth;

					}
					else {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
						X = X * CurrentTexturePanelHeight * TotalTextureScalableHeight;

						// Udregn Crosshair X Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						Y = Y * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth;
						Y = Y + AspectRatioWidthOffSet;

					}

					// Juster X Koordinat
					X = LiveViewZoomWindowPosY1 - X;

				}
				if (LiveViewZoomWindowRotationDegrees == 180) {

					// Skaller X/Y koordinater
					Y = ImageDataPixelHeight - Y;
					X = ImageDataPixelWidth - X;

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewZoomWindowPosX0 <= 0.0) {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						Y = Y * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight;
						Y = Y + AspectRatioHeightOffSet;

						// Udregn Crosshair X Kordinat ved skallering af textur vinduet
						X = X * CurrentTexturePanelWidth * TotalTextureScalableWidth;

					}
					else {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
						Y = Y * CurrentTexturePanelHeight * TotalTextureScalableHeight;

						// Udregn Crosshair X Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						X = X * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth;
						X = X + AspectRatioWidthOffSet;

					}

				}
				if (LiveViewZoomWindowRotationDegrees == 270) {

					// Skaller X/Y koordinater
					X = (ImageDataPixelWidth - X) / ImageDataPixelAspectRatio;
					Y = (ImageDataPixelHeight - Y) * ImageDataPixelAspectRatio;

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewZoomWindowPosX0 <= 0.0) {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						X = X * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight;

						// Udregn Crosshair X Kordinat ved skallering af textur vinduet
						Y = Y * CurrentTexturePanelWidth * TotalTextureScalableWidth;

					}
					else {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
						X = X * CurrentTexturePanelHeight * TotalTextureScalableHeight;

						// Udregn Crosshair X Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						Y = Y * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth;
						Y = Y + AspectRatioWidthOffSet;

					}

					// Juster X Koordinat
					X = LiveViewZoomWindowPosY1 - X;

				}

			}
			else {

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewZoomWindowRotationDegrees == 0) {

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					Y = Y * CurrentTexturePanelHeight * TotalTextureScalableHeight;

					// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					X = X * CurrentTexturePanelWidth * TotalTextureScalableWidth;

				}
				if (LiveViewZoomWindowRotationDegrees == 90) {

					// Skaller X/Y koordinater
					X = X / ImageDataPixelAspectRatio;
					Y = Y * ImageDataPixelAspectRatio;

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					Y = Y * CurrentTexturePanelWidth * TotalTextureScalableWidth;

					// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					X = X * CurrentTexturePanelHeight * TotalTextureScalableHeight;

					// Juster X Koordinat
					X = LiveViewZoomWindowPosY1 - X;

				}
				if (LiveViewZoomWindowRotationDegrees == 180) {

					// Skaller X/Y koordinater
					Y = ImageDataPixelHeight - Y;
					X = ImageDataPixelWidth - X;

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					Y = Y * CurrentTexturePanelHeight * TotalTextureScalableHeight;

					// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					X = X * CurrentTexturePanelWidth * TotalTextureScalableWidth;

				}
				if (LiveViewZoomWindowRotationDegrees == 270) {

					// Skaller X/Y koordinater
					X = (ImageDataPixelWidth - X) / ImageDataPixelAspectRatio;
					Y = (ImageDataPixelHeight - Y) * ImageDataPixelAspectRatio;

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					Y = Y * CurrentTexturePanelWidth * TotalTextureScalableWidth;

					// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					X = X * CurrentTexturePanelHeight * TotalTextureScalableHeight;

					// Juster X Koordinat
					X = LiveViewZoomWindowPosY1 - X;

				}

			}

			// Skal der rendereres en baggrund til lablen
			if (EnableLabelBackgroundFlag == true) {

				// Aktiver OpenGL 1D Texture
				glEnable(GL_TEXTURE_1D);
				glEnable(GL_BLEND);

				// Indstil Label baggrundens Farve
				glColor4ub(LabelBackgroundColorR, LabelBackgroundColorG, LabelBackgroundColorB, CommonLabelBackgroundAlpha);

				// Render rektangel på textur
				glBegin(GL_QUADS);

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewZoomWindowRotationDegrees == 0) {

					// Render label rektanglens positioner
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset, (Y + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (Y + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (Y + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset, (Y + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);

				}
				if (LiveViewZoomWindowRotationDegrees == 90) {

					// Render label rektanglens positioner
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset, (X + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (X + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (X + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset, (X + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);

				}
				if (LiveViewZoomWindowRotationDegrees == 180) {

					// Render label rektanglens positioner
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset, (Y + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (Y + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (Y + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset, (Y + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);

				}
				if (LiveViewZoomWindowRotationDegrees == 270) {

					// Render label rektanglens positioner
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset, (X + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (X + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (X + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset, (X + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);

				}

				// Konfiguration Slut
				glEnd();
				// Deaktiver 1D Texture
				glDisable(GL_TEXTURE_1D);
				glDisable(GL_BLEND);

			}

			// Skal en label tilføjes til crosshairet
			if (EnableLabel == true) {

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewZoomWindowRotationDegrees == 0) {

					// Tilføj Label til crosshair
					RMH_LiveView_RenderStringOnTexture(X + QuadrantXOffset, Y + QuadrantYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

				}
				if (LiveViewZoomWindowRotationDegrees == 90) {

					// Tilføj Label til crosshair
					RMH_LiveView_RenderStringOnTexture(Y + QuadrantXOffset, X + QuadrantYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

				}
				if (LiveViewZoomWindowRotationDegrees == 180) {

					// Tilføj Label til crosshair
					RMH_LiveView_RenderStringOnTexture(X + QuadrantXOffset, Y + QuadrantYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

				}
				if (LiveViewZoomWindowRotationDegrees == 270) {

					// Tilføj Label til crosshair
					RMH_LiveView_RenderStringOnTexture(Y + QuadrantXOffset, X + QuadrantYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

				}
			}

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil Crosshair Farve
			glColor3ub(CrosshairColorR, CrosshairColorG, CrosshairColorB);

			// Indstil CrossHair Linje tykkelsen
			glLineWidth(CrosshairLineWidth);

			// Render Linje på textur
			glBegin(GL_LINES);

			// Kontroller Live View Roterings Indstillingen
			if (LiveViewZoomWindowRotationDegrees == 0) {

				// Vertikale Linje
				glVertex2f(X, Y - (CrosshairSize * 0.5));
				glVertex2f(X, Y + (CrosshairSize * 0.5));

				// Horisontal Linje
				glVertex2f(X - (CrosshairSize * 0.5), Y);
				glVertex2f(X + (CrosshairSize * 0.5), Y);

			}
			if (LiveViewZoomWindowRotationDegrees == 90) {

				// Vertikale Linje
				glVertex2f(Y - (CrosshairSize * 0.5), X);
				glVertex2f(Y + (CrosshairSize * 0.5), X);

				// Horisontal Linje
				glVertex2f(Y, X - (CrosshairSize * 0.5));
				glVertex2f(Y, X + (CrosshairSize * 0.5));

			}
			if (LiveViewZoomWindowRotationDegrees == 180) {

				// Vertikale Linje
				glVertex2f(X, Y - (CrosshairSize * 0.5));
				glVertex2f(X, Y + (CrosshairSize * 0.5));

				// Horisontal Linje
				glVertex2f(X - (CrosshairSize * 0.5), Y);
				glVertex2f(X + (CrosshairSize * 0.5), Y);

			}
			if (LiveViewZoomWindowRotationDegrees == 270) {

				// Vertikale Linje
				glVertex2f(Y - (CrosshairSize * 0.5), X);
				glVertex2f(Y + (CrosshairSize * 0.5), X);

				// Horisontal Linje
				glVertex2f(Y, X - (CrosshairSize * 0.5));
				glVertex2f(Y, X + (CrosshairSize * 0.5));

			}

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

		}

		// -------------- Live View Zoom Vindue Grafiske Rendererings Routine -------------- //

		private: GLvoid RMH_LiveView_WriteImageDataToZoomWindow(unsigned short* FrameData, unsigned int FrameWidth, unsigned int FrameHeight) {

			// Routinen skriver billede data til genereret Textur
			// PBO (Pixel Buffer Object) double buffer inplementering

			// Bind buffer til tilhørende PBO ID
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PBOIDs[0]);

			// Mapping af buffer data lageret til spesifik addresse rum
			void* AddressSpacePointer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);

			// Kontroller om addresse un pointer er gyldig
			if (AddressSpacePointer) {

				// Kopier "FrameData" til pointer addresse rum
				memcpy(AddressSpacePointer, FrameData, FrameWidth * FrameHeight * 3 * sizeof(unsigned short));

				// Afmapping af buffer data lageret fra spesifik addresse rum
				glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

			}

			// Bind texturen til texturets ID
			glBindTexture(GL_TEXTURE_2D, LiveViewZoomTexture[0]);
			// Opdater texturen med data fra PBO objekt
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, FrameWidth, FrameHeight, GL_RGB, GL_UNSIGNED_SHORT, nullptr);

			// Afbind Pixel Buffer Objecter
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

			// Swap imellem PBOer (Pixel Buffer Objecter) for næste iteration
			std::swap(PBOIDs[0], PBOIDs[1]);

		}

		public: GLvoid RMH_LiveView_RenderZoomWindowTexture(GLdouble TexturePanelWidth, GLdouble TexturePanelHeight, GLdouble FrameWidth, GLdouble FrameHeight, bool FixedAspectRatio, GLfloat ZoomROIX0, GLfloat ZoomROIY0, GLfloat ZoomROIWidth, GLfloat ZoomROIHeight) {

			// Routinen Renderer den konfigureret Textur i et givet område af den totale allokerede textur

			// Lokale varaibler
			GLfloat TextureZoomX0 = 0.0;
			GLfloat TextureZoomY0 = 0.0;
			GLfloat TextureZoomX1 = 0.0;
			GLfloat TextureZoomY1 = 0.0;

			// Nulstil Live view stream billede kordinater
			LiveViewZoomWindowPosX0 = 0.0;
			LiveViewZoomWindowPosY0 = 0.0;
			LiveViewZoomWindowPosX1 = 0.0;
			LiveViewZoomWindowPosY1 = 0.0;

			// Nulstil Aspect-Ratio Offset parameter
			AspectRatioWidthOffSet = 0.0;

			// Læs Nuværende textur og data Panels pixel højde og bredde
			ImageDataPixelWidth = FrameWidth;
			ImageDataPixelHeight = FrameHeight;
			CurrentTexturePanelWidth = TexturePanelWidth;
			CurrentTexturePanelHeight = TexturePanelHeight;
			ImageDataPixelAspectRatio = ImageDataPixelWidth / ImageDataPixelHeight;

			// Opdater lokale klasse Aspect ratio status flag
			LocalAspectRatioFlag = FixedAspectRatio;

			// Udregn billedets Y1 positionen til at udfylde textur vinduet
			LiveViewZoomWindowPosY1 = (FrameHeight * CurrentTexturePanelHeight * TotalTextureScalableHeight);

			// Kontroller valgt indstilling for Aspect Ratio
			if (FixedAspectRatio == true) {

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewZoomWindowRotationDegrees == 90 || LiveViewZoomWindowRotationDegrees == 270) {

					// Udregn Aspect-Ratio kompenserede textur Panels pixel bredde og højde - For 90 og 270 Grader Rotering
					CurrentPanelWidthFixedAspect = (FrameHeight * CurrentTexturePanelHeight) / FrameWidth;
					CurrentPanelHeightFixedAspect = (FrameWidth * CurrentTexturePanelWidth) / FrameHeight;

				}
				else {

					// Udregn Aspect-Ratio kompenserede textur Panels pixel bredde og højde 
					CurrentPanelWidthFixedAspect = (FrameWidth * CurrentTexturePanelHeight) / FrameHeight;
					CurrentPanelHeightFixedAspect = (FrameHeight * CurrentTexturePanelWidth) / FrameWidth;

				}

				// Skaller Aspect ratio bredde/højde Offset til aktuel frame data aspect ratio offset - Divider med 2 for samlede højre og venstre margin billede offset
				AspectRatioWidthOffSet = (FrameWidth * (CurrentTexturePanelWidth - CurrentPanelWidthFixedAspect) * TotalTextureScalableWidth) * 0.5;
				AspectRatioHeightOffSet = (FrameHeight * (CurrentTexturePanelHeight - CurrentPanelHeightFixedAspect) * TotalTextureScalableHeight) * 0.5;

				// Udregn billedets X1 positionen til at udfylde textur vinduet i fast Aspectratio mode - Tilføj X1 aspect ratio margin i højre side at textur vinduet
				LiveViewZoomWindowPosX1 = (FrameWidth * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth) + AspectRatioWidthOffSet;

				// Tilføj X0 aspect ratio margin i venstre side at textur vinduet
				LiveViewZoomWindowPosX0 = AspectRatioWidthOffSet;

				// Kompenser for fast aspect ratio i horizontal retning
				if (LiveViewZoomWindowPosX0 <= 0.0) {

					// Nulstil X0 position
					LiveViewZoomWindowPosX0 = 0.0;
					// Fjern aspect ratio margin i højre side at textur vinduet
					LiveViewZoomWindowPosX1 = LiveViewZoomWindowPosX1 + AspectRatioWidthOffSet;

					// Tilføj Y1 aspect ratio margin i bunden at textur vinduet
					LiveViewZoomWindowPosY1 = LiveViewZoomWindowPosY1 - AspectRatioHeightOffSet;
					// Tilføj Y0 aspect ratio margin i Toppen at textur vinduet
					LiveViewZoomWindowPosY0 = AspectRatioHeightOffSet;

				}

			}
			else {

				// Udregn billedets X1 positionen til at udfylde textur vinduet
				LiveViewZoomWindowPosX1 = (FrameWidth * CurrentTexturePanelWidth * TotalTextureScalableWidth);

			}

			// Udregn Textur Zoom parametere - Normaliseret
			TextureZoomX0 = ZoomROIX0 / FrameWidth;
			TextureZoomY0 = ZoomROIY0 / FrameHeight;
			TextureZoomX1 = (ZoomROIX0 + ZoomROIWidth) / FrameWidth;
			TextureZoomY1 = (ZoomROIY0 + ZoomROIHeight) / FrameHeight;

			// Hvis Ultra Opløsnings Mode ikke er aktiverede
			if (UntraResolutionModeEnabledFlag == false) {

				// Skaller Zoom parametere til Ultra Opløsning
				TextureZoomX0 = TextureZoomX0 * 0.5;
				TextureZoomY0 = TextureZoomY0 * 0.5;
				TextureZoomX1 = TextureZoomX1 * 0.5;
				TextureZoomY1 = TextureZoomY1 * 0.5;

			}	

			// Ryd Textur farve og bit buffere
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Aktiver OpenGL 2D Texture
			glEnable(GL_TEXTURE_2D);
			// Bind Texturen som et 2D textur
			glBindTexture(GL_TEXTURE_2D, LiveViewZoomTexture[0]);

			// Roter Textur Til at matche korrekt billede orientation
			glTranslatef(0.0f, FrameHeight, 0.0f);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

			// Begynd Renderering
			glBegin(GL_QUADS);

			// Kontroller Live View Roterings Indstillingen
			if (LiveViewZoomWindowRotationDegrees == 0) {

				// Opdater renderede textur kordinater - 0 Grader Rotering
				glTexCoord2f(TextureZoomX0, TextureZoomY0);
				glVertex2f(LiveViewZoomWindowPosX0, LiveViewZoomWindowPosY0);
				glTexCoord2f(TextureZoomX1, TextureZoomY0);
				glVertex2f(LiveViewZoomWindowPosX1, LiveViewZoomWindowPosY0);
				glTexCoord2f(TextureZoomX1, TextureZoomY1);
				glVertex2f(LiveViewZoomWindowPosX1, LiveViewZoomWindowPosY1);
				glTexCoord2f(TextureZoomX0, TextureZoomY1);
				glVertex2f(LiveViewZoomWindowPosX0, LiveViewZoomWindowPosY1);

			}
			else if (LiveViewZoomWindowRotationDegrees == 90) {

				// Opdater renderede textur kordinater - 90 Grader Rotering
				glTexCoord2f(TextureZoomX0, TextureZoomY0);
				glVertex2f(LiveViewZoomWindowPosX0, LiveViewZoomWindowPosY1);
				glTexCoord2f(TextureZoomX1, TextureZoomY0);
				glVertex2f(LiveViewZoomWindowPosX0, LiveViewZoomWindowPosY0);
				glTexCoord2f(TextureZoomX1, TextureZoomY1);
				glVertex2f(LiveViewZoomWindowPosX1, LiveViewZoomWindowPosY0);
				glTexCoord2f(TextureZoomX0, TextureZoomY1);
				glVertex2f(LiveViewZoomWindowPosX1, LiveViewZoomWindowPosY1);

			}
			else if (LiveViewZoomWindowRotationDegrees == 180) {

				// Opdater renderede textur kordinater - 180 Grader Rotering
				glTexCoord2f(TextureZoomX0, TextureZoomY0);
				glVertex2f(LiveViewZoomWindowPosX1, LiveViewZoomWindowPosY1);
				glTexCoord2f(TextureZoomX1, TextureZoomY0);
				glVertex2f(LiveViewZoomWindowPosX0, LiveViewZoomWindowPosY1);
				glTexCoord2f(TextureZoomX1, TextureZoomY1);
				glVertex2f(LiveViewZoomWindowPosX0, LiveViewZoomWindowPosY0);
				glTexCoord2f(TextureZoomX0, TextureZoomY1);
				glVertex2f(LiveViewZoomWindowPosX1, LiveViewZoomWindowPosY0);

			}
			else {

				// Opdater renderede textur kordinater - 270 Grader Rotering
				glTexCoord2f(TextureZoomX0, TextureZoomY0);
				glVertex2f(LiveViewZoomWindowPosX1, LiveViewZoomWindowPosY0);
				glTexCoord2f(TextureZoomX1, TextureZoomY0);
				glVertex2f(LiveViewZoomWindowPosX1, LiveViewZoomWindowPosY1);
				glTexCoord2f(TextureZoomX1, TextureZoomY1);
				glVertex2f(LiveViewZoomWindowPosX0, LiveViewZoomWindowPosY1);
				glTexCoord2f(TextureZoomX0, TextureZoomY1);
				glVertex2f(LiveViewZoomWindowPosX0, LiveViewZoomWindowPosY0);

			}

			// Konfiguration Slut
			glEnd();
			// Deaktiver 2D Texture
			glDisable(GL_TEXTURE_2D);

		}

		public: GLvoid RMH_LiveView_RenderZoomWindow(unsigned int LiveViewZoomPanelWidth, unsigned int LiveViewZoomPanelHeight, unsigned short* FrameData, unsigned int FrameDataWidth, unsigned int FrameDataHeight, bool FixedAspectRatio, GLfloat ZoomROIX0, GLfloat ZoomROIY0, GLfloat ZoomROIWidth, GLfloat ZoomROIHeight, GLdouble LiveViewRotation) {

			// Routinen Rendererer Live View Zoom Winduet

			// Opdater Live View Zoom Roteringen
			LiveViewZoomWindowRotationDegrees = LiveViewRotation;

			// Nulstil lokalt "Ultra opløsnings mode" er aktiveret flaget
			UntraResolutionModeEnabledFlag = false;

			// ----------------------------- Render Live View Zoom Vindue ----------------------------- //
			
			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();
			// Skriv Billede data til Textur
			RMH_LiveView_WriteImageDataToZoomWindow(FrameData, FrameDataWidth, FrameDataHeight);
			// Opdater Textur Field Of View
			RMH_OpenGL_UpdateTextureFieldOfView(FrameDataWidth, FrameDataHeight);
			// Render Textur Billede Data
			RMH_LiveView_RenderZoomWindowTexture(LiveViewZoomPanelWidth, LiveViewZoomPanelHeight, FrameDataWidth, FrameDataHeight, FixedAspectRatio, ZoomROIX0, ZoomROIY0, ZoomROIWidth, ZoomROIHeight);

			// ---------------------------------------------------------------------------------------- //

		}

		public: GLvoid RMH_LiveView_RenderZoomWindowUltraResolution(unsigned int LiveViewZoomPanelWidth, unsigned int LiveViewZoomPanelHeight, unsigned short* FrameData, unsigned int NativeFrameWidth, unsigned int NativeFrameHeight, unsigned int UltraFrameWidth, unsigned int UltraFrameHeight, bool FixedAspectRatio, GLfloat ZoomROIX0, GLfloat ZoomROIY0, GLfloat ZoomROIWidth, GLfloat ZoomROIHeight, GLdouble LiveViewRotation) {

			// Routinen Rendererer Live View Zoom Winduet

			// Opdater Live View Zoom Roteringen
			LiveViewZoomWindowRotationDegrees = LiveViewRotation;

			// Opdater lokalt "Ultra opløsnings mode" er aktiveret flaget
			UntraResolutionModeEnabledFlag = true;

			// ----------------------------- Render Live View Zoom Vindue ----------------------------- //

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();
			// Skriv Billede data til Textur
			RMH_LiveView_WriteImageDataToZoomWindow(FrameData, UltraFrameWidth, UltraFrameHeight);
			// Konfigurer Texturens Opløsning og FOV
			RMH_OpenGL_UpdateTextureFieldOfView(NativeFrameWidth, NativeFrameHeight);
			// Render Textur Billede Data
			RMH_LiveView_RenderZoomWindowTexture(LiveViewZoomPanelWidth, LiveViewZoomPanelHeight, NativeFrameWidth, NativeFrameHeight, FixedAspectRatio, ZoomROIX0, ZoomROIY0, ZoomROIWidth, ZoomROIHeight);

			// ---------------------------------------------------------------------------------------- //

		}

		// -------------------- OpenGL Renderering Slut Punkts Routiner -------------------- //

		private: GLvoid RMH_OpenGL_SwapOpenGLBuffers(GLvoid) {

			// Routinen bytter rundt på Front/Backend bufferene

			// Byt Rundt på buffere
			SwapBuffers(m_hDC);

		}

		public: GLvoid RMH_OpenGL_RenderingFinishedMark(GLvoid) {

			// Routinen markerer enden på en OpenGL rendererins sekvens
			// Og skal altid kaldes til sidst, når alle objekt rendereringer er blevet eksikverede

			// Swap Textur buffere
			RMH_OpenGL_SwapOpenGLBuffers();

		}

		// --------------------------------------------------------------------------------- //

	private:

		// ------------- Yderligerer OpenGL Håndterings Og Opsætnings Routiner ------------- //

		~RMHLiveViewZoomWindow(GLvoid) {

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
			gluPerspective(60.0f, (GLfloat)TotalTextureWidth / (GLfloat)TotalTextureHeight, 0.1, 500.0);
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

			// Konfigurer Og Initiliser GLEW
			glewInit();

			// Aktiver "Flat Shader" Mode
			glShadeModel(GL_FLAT);
			// Default Baggrund farve
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
