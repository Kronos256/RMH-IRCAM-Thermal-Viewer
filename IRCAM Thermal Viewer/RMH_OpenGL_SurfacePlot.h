#pragma once

/*
 *  RMH_OpenGL_SurfacePlot.h
 *
 *  Author: Rune Mark Hansen
 *  Date: Februar 2023
 *
 */

// Inkluderede Biblioteker
#include "RMH_MathConversions_Library.h"
#include <windows.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include <iostream>
#include "RMH_Winforms_Library.h"

// Surface Plot Default Start Position Macroer 
#define _SurfacePlotStartDefault_XPos     0
#define _SurfacePlotStartDefault_YPos     0
#define _SurfacePlotStartDefault_ZPos     0
#define _SurfacePlotStartAngle_XAngle     0
#define _SurfacePlotStartAngle_YAngle     0

// 3D Surface plottets maksimale Z højde konfig Macroer
#define _SurfacePlotDefaultMaximumZHeight    0.5   // 50% af panelets højde

// Tilhørende Name spaces
using namespace System;
using namespace System::Windows::Forms;
using namespace std;

// OpenGL Klasse definition
namespace OpenGLSurfacePlot {

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

	public ref class RMHOpenGLSurfacePlot : public System::Windows::Forms::NativeWindow {

	private:

		// Private Globale klasse objekter og variabler
		private: HDC m_hDC;
		private: HGLRC m_hglrc;
		private: GLuint BaseFont;
		private: GLint iPixelFormat;
		private: GLuint* SurfacePlotTexture;
		private: GLdouble ImageDataPixelWidth;
		private: GLdouble ImageDataPixelHeight;
		private: unsigned int OpenGLWindowWidth;
		private: unsigned int OpenGLWindowHeight;
		private: bool OverlayPanelIsClick = false;
		private: GLdouble CurrentTexturePanelWidth;
		private: GLdouble CurrentTexturePanelHeight;
		private: GLfloat TextureToPanelWidthOffset = 0.0;
		private: GLfloat TextureToPanelHeightOffset = 0.0;
		private: CreateParams^ ControlParams = gcnew CreateParams;
		private: TextureOverlayPanel^ OverlayPanel = gcnew TextureOverlayPanel();

		// Generalle Surface Plot Objekter Og Variabler
		private: GLdouble SurfacePlotAspectRatio = 0.0;
		private: GLdouble AspectRatioCompensatedWidth = 0.0;
		private: GLdouble TranstaledYSurfacePlotValue = 0.0;
		private: GLfloat SurfaceZDataToZHeightScaleFactor = 0.0;
		private: bool RightMouseButtonClicked = false;
		private: bool MouseWheelButtonClicked = false;
		private: bool LeftMouseButtonClicked = false;
		private: bool XAxesMouseMoveZRotationStateFlag = true;
		private: GLdouble SurfacePlotXTranstaledPosClickOffset;
		private: GLdouble SurfacePlotYTranstaledPosClickOffset;
		private: GLdouble SurfacePlotYXTranstaledPosClickOffset;
		private: GLfloat SurfacePlotXAngleClickOffset = 0.0;
		private: GLfloat SurfacePlotYAngleClickOffset = 0.0;
		private: GLfloat CurrentSurfacePlotXTranstaledPos = 0.0;
		private: GLfloat CurrentSurfacePlotYTranstaledPos = 0.0;
		private: GLfloat CurrentSurfacePlotZTranstaledPos = 0.0;
		private: GLfloat CurrentSurfacePlotYAngle = 0.0;
		private: GLfloat CurrentSurfacePlotXAngle = 0.0;
		private: GLfloat CurrentSurfacePlotYXAngle = 0.0;
		private: GLfloat SurfacePlotMaxZHeight = _SurfacePlotDefaultMaximumZHeight;
		private: GLfloat SurfacePlotXTranstaledPos = _SurfacePlotStartDefault_XPos;
		private: GLfloat SurfacePlotYTranstaledPos = _SurfacePlotStartDefault_YPos;
		private: GLfloat SurfacePlotZTranstaledPos = _SurfacePlotStartDefault_ZPos;
		private: GLfloat SurfacePlotXAngle = _SurfacePlotStartAngle_XAngle;
		private: GLfloat SurfacePlotYAngle = _SurfacePlotStartAngle_YAngle;
		private: GLfloat SurfacePlotYXAngle = _SurfacePlotStartAngle_XAngle;
		private: GLfloat PointPolygonModePointSize = 1.0;
		private: GLfloat LinePolygonModeLineSize = 1.0;

	public:

		// ----------------------- Surface Plot Konstruktur Routiner ----------------------- //

		RMHOpenGLSurfacePlot(System::Windows::Forms::Panel^ TexturePanel, unsigned char WidthScaleFactor, unsigned char HeightScaleFactor) {

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
			OverlayPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLSurfacePlot::TexturePanel_MouseDown);
			OverlayPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLSurfacePlot::TexturePanel_MouseUp);
			OverlayPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLSurfacePlot::TexturePanel_MouseMove);
			OverlayPanel->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLSurfacePlot::TexturePanel_MouseWheel);

		}

		// ---------------- Textur Panel Til Textur Konverterings Routiner ----------------- //

		private: GLdouble RMH_OpenGL_TranslateOverlayPanelMouseXPosToTextureXPos(System::Windows::Forms::MouseEventArgs^ OverlayPanelMouseEvent) {

			// Routinen oversætter overlejede panel Mus positioner til aktuel Textur Panel Mus Positioner

			// Lokale Variabler
			GLdouble MouseTextureXPos = 0.0;
			GLdouble PanelsWidthDifference = 0.0;

			// Udregn Pixel Differensen imellem overlejede panel og textur panelet 
			PanelsWidthDifference = CurrentTexturePanelWidth - OverlayPanel->Width;

			// Konverter overlejede panel Mus position til aktuel Textur Panel Mus Position
			MouseTextureXPos = (OverlayPanelMouseEvent->X + PanelsWidthDifference) * (ImageDataPixelWidth / CurrentTexturePanelWidth);

			// Håndtering ved minimum textur Mus Position 
			if (MouseTextureXPos <= 0) {
				// Sæt Mus position til minimum værdi
				MouseTextureXPos = 0;
			}

			// Håndtering ved maksimal textur Mus Position 
			if (MouseTextureXPos >= ImageDataPixelWidth) {
				// Sæt Mus position til maksimal værdi
				MouseTextureXPos = ImageDataPixelWidth;
			}

			// Rund Mus position op til nærmeste integer
			MouseTextureXPos = RMH_Math_Round(MouseTextureXPos);

			// Retuner aktuel Textur Panel Mus Position
			return MouseTextureXPos;

		}

		private: GLdouble RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(System::Windows::Forms::MouseEventArgs^ OverlayPanelMouseEvent) {

			// Routinen oversætter overlejede panel Mus positioner til aktuel Textur Panel Mus Positioner

			// Lokale Variabler
			GLdouble MouseTextureYPos = 0.0;
			GLdouble PanelsHeightDifference = 0.0;

			// Udregn Pixel Differensen imellem overlejede panel og textur panelet 
			PanelsHeightDifference = CurrentTexturePanelHeight - OverlayPanel->Height;

			// Konverter overlejede panel Mus position til aktuel Textur Panel Mus Position
			MouseTextureYPos = (OverlayPanelMouseEvent->Y + PanelsHeightDifference) * (ImageDataPixelHeight / CurrentTexturePanelHeight);

			// Håndtering ved minimum textur Mus Position 
			if (MouseTextureYPos <= 0) {
				// Sæt Mus position til minimum værdi
				MouseTextureYPos = 0;
			}

			// Håndtering ved maksimal textur Mus Position 
			if (MouseTextureYPos >= ImageDataPixelHeight) {
				// Sæt Mus position til maksimal værdi
				MouseTextureYPos = ImageDataPixelHeight;
			}

			// Rund Mus position op til nærmeste integer
			MouseTextureYPos = RMH_Math_Round(MouseTextureYPos);

			// Retuner aktuel Textur Panel Mus Position
			return MouseTextureYPos;

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
			gluPerspective(PlaneFieldOfView, PlaneAspectRatio, 5.0f, 10000.0);
			gluLookAt(PlaneXLook, PlaneYLook, PlaneDistance * 0.5, PlaneXLook, PlaneYLook, 0, 0, 1, 0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

		}

		// ------------------- Surface Plot Textur Rendererings Routiner ------------------- //

		private: GLvoid RMH_OpenGL_ClearTextureBuffer() {

			// Routinen rydder tilhørende textur buffere

			// Ryd Textur farve og bit buffere
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}

		private: GLvoid RMH_OpenGL_RenderSurfacePlotPolygons(unsigned int TexturePanelWidth, unsigned int TexturePanelHeight, unsigned int NmbOfHorizontalPolyGons, unsigned int NmbOfVerticalPolyGons, unsigned short* SurfacePolygonPixelData, unsigned short* SurfaceZData, GLfloat MaxZDataValue, GLfloat MinZDataValue) {

			// Routinen Rendererer surface plottets pixel polygoner

			// Lokale variabler
			register GLfloat PolygonZ0Pos1 = 0.0;
			register GLfloat PolygonZ0Pos2 = 0.0;
			register GLfloat PolygonZ0Pos3 = 0.0;
			register GLfloat PolygonZ0Pos4 = 0.0;
			register GLfloat PolygonZ0Pos5 = 0.0;
			register GLfloat PolygonZ0Pos6 = 0.0;
			register GLfloat PolygonZ0Pos7 = 0.0;
			register GLfloat PolygonZ0Pos8 = 0.0;
			register GLfloat PolygonZ1Pos1 = 0.0;
			register GLfloat PolygonZ1Pos2 = 0.0;
			register GLfloat PolygonZ1Pos3 = 0.0;
			register GLfloat PolygonZ1Pos4 = 0.0;
			register GLfloat PolygonZ1Pos5 = 0.0;
			register GLfloat PolygonZ1Pos6 = 0.0;
			register GLfloat PolygonZ1Pos7 = 0.0;
			register GLfloat PolygonZ1Pos8 = 0.0;
			register GLfloat PolygonZ2Pos1 = 0.0;
			register GLfloat PolygonZ2Pos2 = 0.0;
			register GLfloat PolygonZ2Pos3 = 0.0;
			register GLfloat PolygonZ2Pos4 = 0.0;
			register GLfloat PolygonZ2Pos5 = 0.0;
			register GLfloat PolygonZ2Pos6 = 0.0;
			register GLfloat PolygonZ2Pos7 = 0.0;
			register GLfloat PolygonZ2Pos8 = 0.0;
			register GLfloat PolygonZ3Pos1 = 0.0;
			register GLfloat PolygonZ3Pos2 = 0.0;
			register GLfloat PolygonZ3Pos3 = 0.0;
			register GLfloat PolygonZ3Pos4 = 0.0;
			register GLfloat PolygonZ3Pos5 = 0.0;
			register GLfloat PolygonZ3Pos6 = 0.0;
			register GLfloat PolygonZ3Pos7 = 0.0;
			register GLfloat PolygonZ3Pos8 = 0.0;
			GLdouble ConversionFactor = 0.00001525902190; // 1 / 2^16

			// Udregn ZAksens skallerings faktor
			GLfloat ZAxesScaleFactor = 1.0 / ((MaxZDataValue - MinZDataValue) * (1.0 / (CurrentTexturePanelHeight * SurfacePlotMaxZHeight)));

			// Udregn Surface plot polygonernes højde og bredde i pixels
			register GLfloat SurfacePolygonWidth = (GLfloat)TexturePanelWidth / (GLfloat)NmbOfHorizontalPolyGons;
			register GLfloat SurfacePolygonHeight = (GLfloat)TexturePanelHeight / (GLfloat)NmbOfVerticalPolyGons;
			
			// Nulstil start polygonens X0 og Y0 koordinater inden rederering
			register GLfloat SurfacePolygonX0 = -((GLfloat)TexturePanelWidth * 0.5);
			register GLfloat SurfacePolygonY0 = -((GLfloat)TexturePanelHeight * 0.5);

			// Nulstil antallet af rendereret polygoner
			register unsigned int RenderedHorizontalPolygons = 0;
			register unsigned int RenderedVerticalPolygons = 0;

			// Render Polygoner på textur
			glBegin(GL_QUADS);

			// Render antal givet polygoner
			for (unsigned int i = 0, j = 0; i < (NmbOfHorizontalPolyGons * NmbOfVerticalPolyGons); i += 8, j += 24) {

				// Renderer ikke første Y polygon
				if (RenderedHorizontalPolygons != 0) {

					// Indstil polygon farven til tilhørende pixel farve
					glColor3f(*(SurfacePolygonPixelData + j + 0) * ConversionFactor, *(SurfacePolygonPixelData + j + 1) * ConversionFactor, *(SurfacePolygonPixelData + j + 2) * ConversionFactor);

					// Render surface plot Rektanglernes linjer
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0, -PolygonZ0Pos1);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0, -PolygonZ1Pos1);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ2Pos1);
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ3Pos1);

					// Opdater næste polygons X0 koordinat
					SurfacePolygonX0 = SurfacePolygonX0 + SurfacePolygonWidth;

					// Indstil polygon farven til tilhørende pixel farve
					glColor3f(*(SurfacePolygonPixelData + j + 3) * ConversionFactor, *(SurfacePolygonPixelData + j + 4) * ConversionFactor, *(SurfacePolygonPixelData + j + 5) * ConversionFactor);

					// Render surface plot Rektanglernes linjer
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0, -PolygonZ0Pos2);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0, -PolygonZ1Pos2);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ2Pos2);
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ3Pos2);

					// Opdater næste polygons X0 koordinat
					SurfacePolygonX0 = SurfacePolygonX0 + SurfacePolygonWidth;

					// Indstil polygon farven til tilhørende pixel farve
					glColor3f(*(SurfacePolygonPixelData + j + 6) * ConversionFactor, *(SurfacePolygonPixelData + j + 7) * ConversionFactor, *(SurfacePolygonPixelData + j + 8) * ConversionFactor);

					// Render surface plot Rektanglernes linjer
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0, -PolygonZ0Pos3);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0, -PolygonZ1Pos3);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ2Pos3);
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ3Pos3);

					// Opdater næste polygons X0 koordinat
					SurfacePolygonX0 = SurfacePolygonX0 + SurfacePolygonWidth;

					// Indstil polygon farven til tilhørende pixel farve
					glColor3f(*(SurfacePolygonPixelData + j + 9) * ConversionFactor, *(SurfacePolygonPixelData + j + 10) * ConversionFactor, *(SurfacePolygonPixelData + j + 11) * ConversionFactor);

					// Render surface plot Rektanglernes linjer
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0, -PolygonZ0Pos4);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0, -PolygonZ1Pos4);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ2Pos4);
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ3Pos4);

					// Opdater næste polygons X0 koordinat
					SurfacePolygonX0 = SurfacePolygonX0 + SurfacePolygonWidth;

					// Indstil polygon farven til tilhørende pixel farve
					glColor3f(*(SurfacePolygonPixelData + j + 12) * ConversionFactor, *(SurfacePolygonPixelData + j + 13) * ConversionFactor, *(SurfacePolygonPixelData + j + 14) * ConversionFactor);

					// Render surface plot Rektanglernes linjer
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0, -PolygonZ0Pos5);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0, -PolygonZ1Pos5);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ2Pos5);
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ3Pos5);

					// Opdater næste polygons X0 koordinat
					SurfacePolygonX0 = SurfacePolygonX0 + SurfacePolygonWidth;

					// Indstil polygon farven til tilhørende pixel farve
					glColor3f(*(SurfacePolygonPixelData + j + 15) * ConversionFactor, *(SurfacePolygonPixelData + j + 16) * ConversionFactor, *(SurfacePolygonPixelData + j + 17) * ConversionFactor);

					// Render surface plot Rektanglernes linjer
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0, -PolygonZ0Pos6);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0, -PolygonZ1Pos6);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ2Pos6);
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ3Pos6);

					// Opdater næste polygons X0 koordinat
					SurfacePolygonX0 = SurfacePolygonX0 + SurfacePolygonWidth;

					// Indstil polygon farven til tilhørende pixel farve
					glColor3f(*(SurfacePolygonPixelData + j + 18) * ConversionFactor, *(SurfacePolygonPixelData + j + 19) * ConversionFactor, *(SurfacePolygonPixelData + j + 20) * ConversionFactor);

					// Render surface plot Rektanglernes linjer
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0, -PolygonZ0Pos7);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0, -PolygonZ1Pos7);
					glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ2Pos7);
					glVertex3f(SurfacePolygonX0, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ3Pos7);

					// Opdater næste polygons X0 koordinat
					SurfacePolygonX0 = SurfacePolygonX0 + SurfacePolygonWidth;

					// Renderer ikke sidste horizontale polygon - Data overflow grundet rendererings struktur
					if (RenderedHorizontalPolygons < NmbOfHorizontalPolyGons - 8) {

						// Indstil polygon farven til tilhørende pixel farve
						glColor3f(*(SurfacePolygonPixelData + j + 21) * ConversionFactor, *(SurfacePolygonPixelData + j + 22) * ConversionFactor, *(SurfacePolygonPixelData + j + 23) * ConversionFactor);

						// Render surface plot Rektanglernes linjer
						glVertex3f(SurfacePolygonX0, SurfacePolygonY0, -PolygonZ0Pos8);
						glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0, -PolygonZ1Pos8);
						glVertex3f(SurfacePolygonX0 + SurfacePolygonWidth, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ2Pos8);
						glVertex3f(SurfacePolygonX0, SurfacePolygonY0 + SurfacePolygonHeight, -PolygonZ3Pos8);

						// Opdater næste polygons X0 koordinat
						SurfacePolygonX0 = SurfacePolygonX0 + SurfacePolygonWidth;

					}

				}

				// Inkrementer antallet af horisontale rendereret Polygoner
				RenderedHorizontalPolygons = RenderedHorizontalPolygons + 8;

				// Er antallet af rendereret horisontale Polygoner nåede 
				if (RenderedHorizontalPolygons >= NmbOfHorizontalPolyGons) {

					// Inkrementer antallet af vertikale rendereret Polygoner rækker
					RenderedVerticalPolygons = RenderedVerticalPolygons + 1;
					// Nulstil antallet af horisontale rendereret Polygoner
					RenderedHorizontalPolygons = 0;

					// Nulstil start polygonens X0 koordinat
					SurfacePolygonX0 = -((GLfloat)TexturePanelWidth * 0.5);
					// Opdater næste polygon rækkes Y0 koordinat
					SurfacePolygonY0 = SurfacePolygonY0 + SurfacePolygonHeight;

				}

				// Opdater Polygonets X0/Y0 Z-koordinater (Sidste række kompenserede) - Loop Unroll Part 1
				PolygonZ0Pos1 = ((*(SurfaceZData + i + 0 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ1Pos1 = ((*(SurfaceZData + i + 1 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ1Pos2 = ((*(SurfaceZData + i + 2 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ1Pos3 = ((*(SurfaceZData + i + 3 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ1Pos4 = ((*(SurfaceZData + i + 4 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ0Pos2 = PolygonZ1Pos1;
				PolygonZ0Pos3 = PolygonZ1Pos2;
				PolygonZ0Pos4 = PolygonZ1Pos3;

				// Opdater Polygonets X0/Y0 Z-koordinater (Sidste række kompenserede) - Loop Unroll Part 2
				PolygonZ0Pos5 = ((*(SurfaceZData + i + 4 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ1Pos5 = ((*(SurfaceZData + i + 5 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ1Pos6 = ((*(SurfaceZData + i + 6 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ1Pos7 = ((*(SurfaceZData + i + 7 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ1Pos8 = ((*(SurfaceZData + i + 8 + 8)) - MinZDataValue) * ZAxesScaleFactor;
				PolygonZ0Pos6 = PolygonZ1Pos5;
				PolygonZ0Pos7 = PolygonZ1Pos6;
				PolygonZ0Pos8 = PolygonZ1Pos7;

				// Hvis sidste vertikale polygon række er nåede
				if (RenderedVerticalPolygons >= NmbOfVerticalPolyGons - 1) {
	
					// Opdater Polygonets X0/Y0 Z-koordinater (Sidste række kompenserede) - For første polygon - Loop Unroll Part 1
					PolygonZ2Pos1 = PolygonZ1Pos1;
					PolygonZ2Pos2 = PolygonZ1Pos2;
					PolygonZ2Pos3 = PolygonZ1Pos3;
					PolygonZ2Pos4 = PolygonZ1Pos4;
					PolygonZ3Pos1 = PolygonZ0Pos1;
					PolygonZ3Pos2 = PolygonZ0Pos2;
					PolygonZ3Pos3 = PolygonZ0Pos3;
					PolygonZ3Pos4 = PolygonZ0Pos4;

					// Opdater Polygonets X0/Y0 Z-koordinater (Sidste række kompenserede) - For første polygon - Loop Unroll Part 2
					PolygonZ2Pos5 = PolygonZ1Pos5;
					PolygonZ2Pos6 = PolygonZ1Pos6;
					PolygonZ2Pos7 = PolygonZ1Pos7;
					PolygonZ2Pos8 = PolygonZ1Pos8;
					PolygonZ3Pos5 = PolygonZ0Pos5;
					PolygonZ3Pos6 = PolygonZ0Pos6;
					PolygonZ3Pos7 = PolygonZ0Pos7;
					PolygonZ3Pos8 = PolygonZ0Pos8;
					
				}		
				else {
					
					// Opdater Polygonets X0/Y0 Z-koordinater - For første polygon - Loop Unroll Part 1
					PolygonZ2Pos1 = ((*(SurfaceZData + i + 1 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ2Pos2 = ((*(SurfaceZData + i + 2 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ2Pos3 = ((*(SurfaceZData + i + 3 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ2Pos4 = ((*(SurfaceZData + i + 4 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ3Pos1 = ((*(SurfaceZData + i + 0 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ3Pos2 = PolygonZ2Pos1;
					PolygonZ3Pos3 = PolygonZ2Pos2;
					PolygonZ3Pos4 = PolygonZ2Pos3;

					// Opdater Polygonets X0/Y0 Z-koordinater - For første polygon - Loop Unroll Part 2			
					PolygonZ2Pos5 = ((*(SurfaceZData + i + 5 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ2Pos6 = ((*(SurfaceZData + i + 6 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ2Pos7 = ((*(SurfaceZData + i + 7 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ2Pos8 = ((*(SurfaceZData + i + 8 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ3Pos5 = ((*(SurfaceZData + i + 4 + 8 + NmbOfHorizontalPolyGons)) - MinZDataValue) * ZAxesScaleFactor;
					PolygonZ3Pos6 = PolygonZ2Pos5;
					PolygonZ3Pos7 = PolygonZ2Pos6;
					PolygonZ3Pos8 = PolygonZ2Pos7;

				}

			}

			// Konfiguration Slut
			glEnd();

		}

		// -------------- Samlede Surface Plot Grafiske Rendererings Routine --------------- //

		public: GLvoid RMH_OpenGL_ResetSurfacePlotView() {

			// Routinen nustiller 3D surface plottets synsvinel til start positionen

			// Nulstil surface plottets synsvinel tilbage til start positionen
			SurfacePlotXTranstaledPos = _SurfacePlotStartDefault_XPos;
			SurfacePlotYTranstaledPos = _SurfacePlotStartDefault_YPos;
			SurfacePlotZTranstaledPos = _SurfacePlotStartDefault_ZPos;
			SurfacePlotXAngle = _SurfacePlotStartAngle_XAngle;
			SurfacePlotYAngle = _SurfacePlotStartAngle_YAngle;
			SurfacePlotYXAngle = _SurfacePlotStartAngle_YAngle;

		}

		public: GLvoid RMH_OpenGL_UpdateSurfacePlotMaxZHeight(System::Object^ sender) {

			// Routinen opdaterer surface plottets maksimale Z højde i pixels

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ TagSurfaceZHeight = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag (Surface Plot Scale Faktor Værdi)
			GLfloat SurfaceZHeight = Convert::ToDouble(TagSurfaceZHeight->Tag);

			// Opdater Surface plottets maksimale z pixel højde i procent
			SurfacePlotMaxZHeight = (GLfloat)SurfaceZHeight;

		}
		
		public: GLvoid RMH_OpenGL_SetSurfacePlotPolygonMode(System::Object^ sender) {

			// Routinen indstiller imellem de tilgængelige Polygon rendererings modes

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ TagSurfacePolygonMode = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag 
			unsigned char SurfacePolygonMode = Convert::ToDouble(TagSurfacePolygonMode->Tag);

			// Valg af Surface Plot polygon mode
			switch (SurfacePolygonMode) {

				// Indstil Surface Plottets polygon mode og størrelses parameter
				case 0: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); glPointSize(PointPolygonModePointSize);    break;
				case 1: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  glLineWidth(LinePolygonModeLineSize);    break;
				case 2: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); glPointSize(0); glLineWidth(0); break;

			}

		}

		public: GLvoid RMH_OpenGL_SetSurfacePlotPolygonModePointSize(System::Object^ sender) {

			// Routinen indstiller Punkt størrelsen i "GL_POINT" Polygon renderings Mode

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ TagPointPolygonMode = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag 
			unsigned char PointPolygonModeSizeValue = Convert::ToDouble(TagPointPolygonMode->Tag);

			// Opdater tilhørende private klasse variable
			PointPolygonModePointSize = PointPolygonModeSizeValue;

			// Indstil punkt størrelsen for polygon modet
			glPointSize(PointPolygonModePointSize);

		}

		public: GLvoid RMH_OpenGL_SetSurfacePlotPolygonModeLineSize(System::Object^ sender) {

			// Routinen indstiller Linje størrelsen i "GL_LINE" Polygon renderings Mode

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ TagLinePolygonMode = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag 
			unsigned char LinePolygonModeSizeValue = Convert::ToDouble(TagLinePolygonMode->Tag);

			// Opdater tilhørende private klasse variable
			LinePolygonModeLineSize = LinePolygonModeSizeValue;

			// Indstil linje størrelsen for polygon modet
			glLineWidth(LinePolygonModeLineSize);

		}

		public: GLvoid RMH_OpenGL_RenderSurfacePlot(unsigned int SurfacePlotPanelWidth, unsigned int SurfacePlotPanelHeight, unsigned short *SurfacePolygonPixelData, unsigned int SurfaceDataWidth, unsigned int SurfaceDataHeight, unsigned short* SurfaceZData, GLfloat MaxZDataValue, GLfloat MinZDataValue) {

			// Routinen Rendererer alle grafiske objekter som Histogrammet består af

			// Læs Nuværende textur Panels pixel højde og bredde
			CurrentTexturePanelWidth = (GLdouble)SurfacePlotPanelWidth;
			CurrentTexturePanelHeight = (GLdouble)SurfacePlotPanelHeight;

			// Læs Givet surface plot billede data pixel bredde og højde
			ImageDataPixelWidth = SurfaceDataWidth;
			ImageDataPixelHeight = SurfaceDataHeight;

			// Udregn Pixel offsettet imellem textur området og tilhørende GUI panel
			TextureToPanelWidthOffset = OpenGLWindowWidth - CurrentTexturePanelWidth;
			TextureToPanelHeightOffset = OpenGLWindowHeight - CurrentTexturePanelHeight;

			// Udregn Surface Plottets Aspect Ratio
			SurfacePlotAspectRatio = (GLdouble)SurfaceDataWidth / (GLdouble)SurfaceDataHeight;
			// Udregn Surface Plot rendererings kompenserede aspect ratio width
			AspectRatioCompensatedWidth = SurfacePlotAspectRatio * CurrentTexturePanelHeight;
			// Udregn Surface Plottets Translated Y Position - Relativt til aspect ratio mm
			TranstaledYSurfacePlotValue = (GLfloat)OpenGLWindowHeight - CurrentSurfacePlotYTranstaledPos - TextureToPanelHeightOffset - (SurfacePlotPanelHeight * 0.5);
			
			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();
			// Ryd Textur farve og bit buffere
			RMH_OpenGL_ClearTextureBuffer();
			// Opdater Textur Field Of View
			RMH_OpenGL_UpdateTextureFieldOfView(CurrentTexturePanelWidth, CurrentTexturePanelHeight);

			// Opdater Textur View port til midten af surface plottet
			glViewport(0, TextureToPanelHeightOffset, CurrentTexturePanelWidth, CurrentTexturePanelHeight);

			// Læs Surface plottets nuværende positions parametere
			CurrentSurfacePlotXTranstaledPos = SurfacePlotXTranstaledPos;
			CurrentSurfacePlotYTranstaledPos =  SurfacePlotYTranstaledPos;
			CurrentSurfacePlotZTranstaledPos = SurfacePlotZTranstaledPos;
			CurrentSurfacePlotYAngle = SurfacePlotYAngle;
			CurrentSurfacePlotXAngle = SurfacePlotXAngle;
			CurrentSurfacePlotYXAngle = SurfacePlotYXAngle;
	
			// Opdater synsvinkelen for surface plottet 
			glTranslatef(((GLfloat)SurfacePlotPanelWidth * 0.5) + CurrentSurfacePlotXTranstaledPos, TranstaledYSurfacePlotValue, CurrentSurfacePlotZTranstaledPos);
			glRotatef(180.0f + CurrentSurfacePlotYAngle, 1.0f, 0.0f, 0.0f);

			// Roter om Surface plottets Z-Akse for Mus Bevægelse på X-aksen - venstra klip
			glRotatef(-CurrentSurfacePlotXAngle, 0.0f, 0.0f, 1.0f);
			// Roter om Surface plottets Y-Akse for Mus Bevægelse på X-aksen - højre klip
			glRotatef(-CurrentSurfacePlotYXAngle, 0.0f, 1.0f, 0.0f);

			// --------------------------------- Render Surface Plot ---------------------------------- //

			// Renderer 3D Surface Plot Polygoner
			RMH_OpenGL_RenderSurfacePlotPolygons(AspectRatioCompensatedWidth, CurrentTexturePanelHeight, SurfaceDataWidth, SurfaceDataHeight, SurfacePolygonPixelData, SurfaceZData, MaxZDataValue, MinZDataValue);

			// ---------------------------------------------------------------------------------------- //

			// Marker enden på en OpenGL rendererins sekvens
			RMH_OpenGL_RenderingFinishedMark();

		}
		
		// ------------ Textur Panel Interaktions Cursor Event Callback Routiner ----------- //

		private: GLvoid TexturePanel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Læs Mus Cursor Positionen
			GLdouble MouseXPosition = RMH_OpenGL_TranslateOverlayPanelMouseXPosToTextureXPos(e);
			GLdouble MouseYPosition = RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(e);

			// Opdater overlay panel click flag
			OverlayPanelIsClick = true;

			// Nulstil Mus Knap Flag
			RightMouseButtonClicked = false;
			MouseWheelButtonClicked = false;
			LeftMouseButtonClicked = false;

			// Hvilken Mus Knap er blever trykket
			switch (e->Button) {

				// Højre Musse knap
				case System::Windows::Forms::MouseButtons::Right:

					// Opdater Mus Knap Flag
					RightMouseButtonClicked = true;

					// Læs mus cursorens positions offset
					SurfacePlotYXTranstaledPosClickOffset = MouseXPosition - CurrentSurfacePlotYXAngle;

				break;

				// Mouse-Wheel knap
				case System::Windows::Forms::MouseButtons::Middle:

					// Opdater Mus Knap Flag
					MouseWheelButtonClicked = true;

					// Læs mus cursorens positions offset
					SurfacePlotXTranstaledPosClickOffset = MouseXPosition - CurrentSurfacePlotXTranstaledPos;
					SurfacePlotYTranstaledPosClickOffset = MouseYPosition - CurrentSurfacePlotYTranstaledPos;

				break;

				// Venstre Musse knap
				case System::Windows::Forms::MouseButtons::Left:

					// Opdater Mus Knap Flag
					LeftMouseButtonClicked = true;

					// Læs mus cursorens positions offset
					SurfacePlotXAngleClickOffset = MouseXPosition - CurrentSurfacePlotXAngle;
					SurfacePlotYAngleClickOffset = MouseYPosition - CurrentSurfacePlotYAngle;

				break;

			}

		}

		private: GLvoid TexturePanel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Opdater overlay panel click flag
			OverlayPanelIsClick = false;

		}

		private: GLvoid TexturePanel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Læs Mus Cursor Positionen
			GLdouble MouseXPosition = RMH_OpenGL_TranslateOverlayPanelMouseXPosToTextureXPos(e);
			GLdouble MouseYPosition = RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(e);

			// Hvis der endnu ikke er blevet klippet på panalet
			if (OverlayPanelIsClick == false) {

				// Fortsæt ikke
				return;

			}

			// Er Højre Musse knap trykket
			if (RightMouseButtonClicked == true) {

				// Opdater Surface plottets Y transformerede positioner
				SurfacePlotYXAngle = MouseXPosition - SurfacePlotYXTranstaledPosClickOffset;

			}
			// Er Mouse-Wheel knap trykket
			if (MouseWheelButtonClicked == true) {

				// Opdater Surface plottets X of Y transformerede positioner
				SurfacePlotXTranstaledPos = MouseXPosition - SurfacePlotXTranstaledPosClickOffset;
				SurfacePlotYTranstaledPos = MouseYPosition - SurfacePlotYTranstaledPosClickOffset;

			}
			// Er Venstre Musse knap trykket
			if (LeftMouseButtonClicked == true) {

				// Opdater Surface plottets X of Y Vingel positioner
				SurfacePlotXAngle = MouseXPosition - SurfacePlotXAngleClickOffset;
				SurfacePlotYAngle = MouseYPosition - SurfacePlotYAngleClickOffset;

			}
			
		}

		private: GLvoid TexturePanel_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Kontroller Mus hjulets drejnings polaritet
			if (e->Delta < 0.0) {

				// For negativ polaritet - Reducer Z position
				SurfacePlotZTranstaledPos = SurfacePlotZTranstaledPos - 25.0;

			}
			else {

				// For positiv polaritet - Inkrementr Z position
				SurfacePlotZTranstaledPos = SurfacePlotZTranstaledPos + 25.0;

			}

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

		~RMHOpenGLSurfacePlot(GLvoid) {

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
			// Aktiver OpenGL "Depth Testing"
			glEnable(GL_DEPTH_TEST);
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