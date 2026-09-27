#pragma once

/*
 *  RMH_OpenGL_Winforms.h
 *
 *  Author: Rune Mark Hansen
 *  Date: January 2023
 *
 */

// Inkluderede Biblioteker
#include "RMH_MathConversions_Library.h"
#include <windows.h>
#include <glew.h>
#include <glfw3.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include <iostream>
#include <math.h>
#include "RMH_Winforms_Library.h"

// Rendereret Objekters Z-Ordens Indstillings Macroer
#define _ZOrden_CrosshairsInFront	      0
#define _ZOrden_RectanglesInFront	      1
#define _ZOrden_LinesInFront			  2

// Globale Faste Konfigurations Macroer
#define _MaxNumberOfMovableRectangles     12   // 10x ROI + 1x Palette ROI + 1x Zoom ROI
#define _NumberOfNonMainLiveViewROIs      2    // 1x Palette ROI + 1x Zoom ROI
#define _MaxNumberOfMovableCrosshairs     10 
#define _MaxNumberOfMovableLines          5 
#define _MovableLinesMaxPixelLength       680 

// Statiske Globale Klasse variabler
static GLdouble RectX0[_MaxNumberOfMovableRectangles + 1];
static GLdouble RectY0[_MaxNumberOfMovableRectangles + 1];
static GLdouble RectWidth[_MaxNumberOfMovableRectangles + 1];
static GLdouble RectHeight[_MaxNumberOfMovableRectangles + 1];
static unsigned short RectOrderIndex[_MaxNumberOfMovableRectangles + 1];
static bool RectFixedAspectRatioFlags[_MaxNumberOfMovableRectangles + 1];
static GLdouble CrosshairX0[_MaxNumberOfMovableCrosshairs + 1];
static GLdouble CrosshairY0[_MaxNumberOfMovableCrosshairs + 1];
static unsigned short CrosshairOrderIndex[_MaxNumberOfMovableCrosshairs + 1];
static GLdouble MovableLineX0[_MaxNumberOfMovableLines + 1];
static GLdouble MovableLineY0[_MaxNumberOfMovableLines + 1];
static GLdouble MovableLineX1[_MaxNumberOfMovableLines + 1];
static GLdouble MovableLineY1[_MaxNumberOfMovableLines + 1];
static unsigned short MovableLineOrderIndex[_MaxNumberOfMovableLines + 1];

// Tilhørende Name spaces
using namespace System;
using namespace System::Windows::Forms;
using namespace std;

// Klasse Positions Justerbar Rektangel Enum
enum RectangelSizableSides {

	TopLine,
	LeftLine,
	RightLine,
	BottomLine,
	None

};

// Klasse Positions Justerbar Crosshair Enum
enum CrosshairSizableSides {

	Crosshair,
	Default

};

// Klasse Positions Justerbar Linje Enum
enum LineMovableSides {

	LeftSide,
	Middle,
	RightSide,
	Outside

};

// OpenGL Klasse definition
namespace OpenGLWinForms {

	// ---------------------------------- Globale Klasse Struktur Objekter --------------------------------- //

	// Rektangel Positions Data Klasse struktur
	class RectangelPosition {
	public:

		// Rektangel Positions parametere
		GLdouble RectangleX0Pos = 0.0;
		GLdouble RectangleY0Pos = 0.0;
		GLdouble RectangleWidth = 0.0;
		GLdouble RectangleHeight = 0.0;

	};

	// Crosshair med Label Positions Data Klasse struktur
	class CrosshairWLabelPosition {
	public:

		// Crosshair Positions parametere
		GLfloat CrosshairX0Pos = 0.0;
		GLfloat CrosshairY0Pos = 0.0;

	};

	// Mus Cursor Positions Data Klasse struktur
	class MouseCursorPosition {
	public:

		// Mus Cursor Positions parametere
		GLdouble CursorXPos = 0.0;
		GLdouble CursorYPos = 0.0;

	};

	// Linje Spesifikations Data Klasse struktur
	class LineSpecsPosition {
	public:

		// Linje Spesifikations parametere
		unsigned short LineType = 0;
		GLfloat LineSlope = 0.0;
		unsigned short LinePixelLength = 0;
		GLfloat LineXOffset = 0.0;
		GLfloat LineYOffset = 0.0;
		GLfloat LineX0Pos = 0.0;
		GLfloat LineY0Pos = 0.0;
		GLfloat LineX1Pos = 0.0;
		GLfloat LineY1Pos = 0.0;
		GLfloat LineXCordinates[_MovableLinesMaxPixelLength];
		GLfloat LineYCordinates[_MovableLinesMaxPixelLength];

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

	// --------------------------------------- Primære OpenGL Klasse --------------------------------------- //
	
	public ref class RMHOpenGLWF : public System::Windows::Forms::NativeWindow {

	private:

		// OpenGL & Textur Rendererings variabler
		private: HDC m_hDC;
		private: HGLRC m_hglrc;
		private: GLuint BaseFont;
		private: unsigned int TextureWidth;
		private: unsigned int TextureHeight;
		private: GLint iPixelFormat;
		private: GLuint* ImageTecture;
		private: GLdouble LiveViewPosX0 = 0.0;
		private: GLdouble LiveViewPosY0 = 0.0;
		private: GLdouble LiveViewPosX1 = 0.0;
		private: GLdouble LiveViewPosY1 = 0.0;
		private: GLdouble InitialTextureWidth;
		private: GLdouble InitialTextureHeight;
		private: GLdouble TextureResScaleFactor;
		private: GLdouble AspectRatioWidthOffSet;
		private: GLdouble AspectRatioHeightOffSet;
		private: GLdouble CurrentTexturePanelWidth;
		private: GLdouble CurrentTexturePanelHeight;
		private: GLdouble TotalTextureScalableWidth;
		private: GLdouble TotalTextureScalableHeight;
		private: GLdouble CurrentPanelWidthFixedAspect;
		private: GLdouble CurrentPanelHeightFixedAspect;
		private: CreateParams^ ControlParams = gcnew CreateParams;
		private: GLdouble ImageDataPixelWidth;
		private: GLdouble ImageDataPixelHeight;
		private: GLdouble ImageDataPixelAspectRatio;
		private: GLdouble ImageDataPixelAspectRatioReciprok;
		private: TextureOverlayPanel^ OverlayPanel = gcnew TextureOverlayPanel();
		private: bool OverlayPanelIsClick = false;
		private: bool LocalAspectRatioFlag = false;
		private: bool ClassEnableInterpolationFlag = false;
		private: unsigned short TextureRotation = 0;
		private: unsigned short MovableObjectsRenderZOrder = _ZOrden_RectanglesInFront;
		private: GLdouble LiveViewRotationDegrees = 0.0;
		private: bool LiveViewMouseScrollWheelRotationEnablFlag = false;
		private: bool LiveViewRotationChangedFlag = false;
		private: GLfloat UltraResolutionFrameOffsetValue = 0.5;
		private: unsigned int UltraResolutionTextureScaleFactor = 2;
			   
		// Mus Curcor Trackings variabler
		private: bool CursorTrackingEnableFlag = false;
		private: GLdouble CursorTrackTextureXPos = 0.0f;
		private: GLdouble CursorTrackTextureYPos = 0.0f;
		private: GLdouble CursorTrackXPos = 0.0f;
		private: GLdouble CursorTrackYPos = 0.0f;
		private: GLfloat MouseLabelQuadrant1LabelXOffset = -17.0;
		private: GLfloat MouseLabelQuadrant1LabelYOffset = 3.0;
		private: GLfloat MouseLabelQuadrant4LabelXOffset = -17.0;
		private: GLfloat MouseLabelQuadrant4LabelYOffset = -2.0;

		// Positions justerbar Rektangel variabler
		private: RectangelSizableSides SelectedRectSide = RectangelSizableSides::None;
		private: GLdouble ClickRectXPositionOffset;
		private: GLdouble ClickRectYPositionOffset;
		private: GLdouble ClickRectXPosition;
		private: GLdouble ClickRectYPosition;
		private: GLdouble ClickRectWidthPosition;
		private: GLdouble ClickRectHeightPosition;
		private: unsigned short SelectedRectTagIndex = 0;
		private: unsigned short NmbOfActiveRects = 0;
		private: unsigned short OldNmbOfActiveRects = 0;
		private: unsigned int RenderedRectanglesCounter = 0;
		private: bool RectangleMoveFlag = false;

		// Positions justerbar Crosshair Med Label variabler
		private: CrosshairSizableSides SelectedCrosshairSide = CrosshairSizableSides::Default;
		private: GLdouble ClickCrosshairXPositionOffset;
		private: GLdouble ClickCrosshairYPositionOffset;
		private: unsigned int RenderedCrosshairCounter = 0;
		private: unsigned short SelectedCrosshairTagIndex = 0;
		private: unsigned short NmbOfActiveCrosshairs = 0;
		private: unsigned short OldNmbOfActiveCrosshairs = 0;
		private: bool CrosshairMoveFlag = false;

		// Positions justerbar Linje variabler
		private: LineMovableSides SelectedLineSide = LineMovableSides::Outside;
		private: GLdouble ClickLineX0PositionOffset;
		private: GLdouble ClickLineY0PositionOffset;
		private: GLdouble ClickLineX1PositionOffset;
		private: GLdouble ClickLineY1PositionOffset;
		private: unsigned int RenderedLineCounter = 0;
		private: unsigned short SelectedLineTagIndex = 0;
		private: unsigned short NmbOfActiveLines = 0;
		private: unsigned short OldNmbOfActiveLines = 0;
		private: bool LineMoveFlag = false;
	
		// Default Positions justerbar Rektangel Konfigurations parameter
		public: GLdouble MinimumRectHeight = 20.0;
		public: GLdouble MinimumRectWidth = 20.0;
		private: GLdouble InitialRectHeight = 0.0;
		private: GLdouble InitialRectWidth = 48.0;
		public: GLdouble DefaultRectLineWidth = 1.0;
		private: GLdouble CursorChangeOffset = 2.0;
		private: GLdouble RectTextureBorderPadding = 5.0;
		private: GLdouble ROIIdentifierLabelXPixelOffset = 1.0;
		private: GLdouble ROIIdentifierLabelYPixelOffset = 2.0;
		private: GLdouble ROIRectangleLiveViewBorderPixelPadding = 2.0;

		// Default Positions justerbar Crosshair Konfigurations parameter
		private: GLfloat CrosshairSize = 2.0;
		private: GLfloat CrosshairInsideAreaPadding = 5.0;
		private: unsigned short CrosshairLineWidth = 2;
		private: GLfloat MovableLineQuadrant1LabelXOffset = -10.0;
		private: GLfloat MovableLineQuadrant1LabelYOffset = 3.0;
		private: GLfloat MovableLineQuadrant2LabelXOffset = 2.0;
		private: GLfloat MovableLineQuadrant2LabelYOffset = 3.0;
		private: GLfloat MovableLineQuadrant3LabelXOffset = 2.0;
		private: GLfloat MovableLineQuadrant3LabelYOffset = -2.0;
		private: GLfloat MovableLineQuadrant4LabelXOffset = -10.0;
		private: GLfloat MovableLineQuadrant4LabelYOffset = -2.0;

		// Default Crosshair Med Center Label Konfigurations parameter
		private: GLfloat ChrosshairWithCenterLabelXOffset = -4.0;
		private: GLfloat ChrosshairWithCenterLabelYOffset = 2.8;

		// Default Positions justerbar linje Konfigurations parameter
		private: unsigned char MovableLineCursorOffset = 4;
		private: unsigned short MovableLineCurnerToMiddleOffset = 4;
		private: unsigned short MovableLineMinimumLength = 10;
		private: unsigned short LineTextureBorderPadding = 3;

		// Text Label og label Baggrunds Konfigurations parameter
		private: bool EnableLabelBackgroundFlag = true;
		private: GLfloat LabelBackgroundXOffset = 0.2;
		private: GLfloat LabelBackgroundYOffset = 1.1;
		private: GLfloat LabelBackgroundWidth = 8.5;
		private: GLfloat LabelBackgroundHeight = 1.5;
		private: GLfloat CenterLabelBackgroundXOffset = 0.3;
		private: GLfloat CenterLabelBackgroundYOffset = 1.1;
		private: GLfloat CenterLabelBackgroundWidth = 9.8;
		private: GLfloat CenterLabelBackgroundHeight = 1.5;
		private: GLfloat MouseLabelBackgroundXOffset = 0.3;
		private: GLfloat MouseLabelBackgroundYOffset = 1.1;
		private: GLfloat MouseLabelBackgroundWidth = 16.2;
		private: GLfloat MouseLabelBackgroundHeight = 1.5;
		private: GLubyte LabelBackgroundColorR = 35;
		private: GLubyte LabelBackgroundColorG = 35;
		private: GLubyte LabelBackgroundColorB = 35;
		private: GLubyte CommonLabelColorR = 255;
		private: GLubyte CommonLabelColorG = 255;
		private: GLubyte CommonLabelColorB = 255;
		private: GLubyte CommonLabelBackgroundAlpha = 180;

	public:

		// ------------------------------- OpenGL Textur Objekt Konstruktur Routiner ------------------------------- //

		RMHOpenGLWF(System::Windows::Forms::Panel^ TexturePanel, unsigned char ResolutionScaleFactor) {

			// Routinen opsætter et OpenGL Supporterede grafisk område til renderering
			// Et Winforms Panel er givet som det fysiske textur areal.

			// Sæt Textur initielle parametere
			InitialTextureWidth = (GLdouble)TexturePanel->Width;
			InitialTextureHeight = (GLdouble)TexturePanel->Height;
			TextureResScaleFactor = (GLdouble)ResolutionScaleFactor;

			// Udregn den totale skallerbar textur hæjde og bredde
			TotalTextureScalableWidth = 1.0 / (InitialTextureWidth * TextureResScaleFactor);
			TotalTextureScalableHeight = 1.0 / (InitialTextureHeight * TextureResScaleFactor);

			// Sæt positionen af Formen
			ControlParams->X = 0;
			ControlParams->Y = 0;
			ControlParams->Width = InitialTextureWidth * TextureResScaleFactor;
			ControlParams->Height = InitialTextureHeight * TextureResScaleFactor;

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

			// Tilføj et overlejede gennemsigtigt panel til textur panalet
			RMH_OpenGL_AddOverlayPanelToMainTexturePanel(TexturePanel);

		}

		GLvoid RMH_OpenGL_InitArray(GLdouble *Array, unsigned short ArraySize, GLdouble Value) {

			// Routinen Skriver en givet værdi "value" til alle positioner i et givet array

			// Loop igennem hele arrayet
			for (unsigned short i = 0; i < ArraySize; i++) {

				// Skriv værdi til array index positioner
				*(Array + i) = Value;

			}

		}

		GLvoid RMH_OpenGL_InitArray(bool *Array, unsigned short ArraySize, bool Value) {

			// Routinen Skriver en givet værdi "value" til alle positioner i et givet array

			// Loop igennem hele arrayet
			for (unsigned short i = 0; i < ArraySize; i++) {

				// Skriv værdi til array index positioner
				*(Array + i) = Value;

			}

		}

		GLvoid RMH_OpenGL_InitArray(unsigned short *Array, unsigned short ArraySize, unsigned short Value) {

			// Routinen Skriver en givet værdi "value" til alle positioner i et givet array

			// Loop igennem hele arrayet
			for (unsigned short i = 0; i < ArraySize; i++) {

				// Skriv værdi til array index positioner
				*(Array + i) = Value;

			}

		}

		GLvoid RMH_OpenGL_InitializeGlobalVariabelsAndArrays(unsigned int FrameWidth, unsigned int FrameHeight) {

			// Routinen Initiliserer forskellige Klasse arrays og variabler med start værdier

			// Lokale Variabler
			GLdouble CenterTextureWidth = (GLdouble)FrameWidth * 0.5;
			GLdouble CenterTextureHeight = (GLdouble)FrameHeight * 0.5;

			// Udregn rektalglernes default start pixel højde
			InitialRectHeight = InitialRectWidth * (1.0 / ((GLdouble)FrameWidth / (GLdouble)FrameHeight));

			// Initiliser Globale Arrays med start værdier - Postions Justerbar Rektangler
			RMH_OpenGL_InitArray(&RectX0[0], _MaxNumberOfMovableRectangles + 1, 10);
			RMH_OpenGL_InitArray(&RectY0[0], _MaxNumberOfMovableRectangles + 1, 10);
			RMH_OpenGL_InitArray(&RectWidth[0], _MaxNumberOfMovableRectangles + 1, InitialRectWidth);
			RMH_OpenGL_InitArray(&RectHeight[0], _MaxNumberOfMovableRectangles + 1, InitialRectHeight);
			RMH_OpenGL_InitArray(&RectOrderIndex[0], _MaxNumberOfMovableRectangles + 1, 0);
			RMH_OpenGL_InitArray(&RectFixedAspectRatioFlags[0], _MaxNumberOfMovableRectangles + 1, false);

			// Initiliser Globale Arrays med start værdier - Postions Justerbar Crosshair Med Label
			RMH_OpenGL_InitArray(&CrosshairX0[0], _MaxNumberOfMovableCrosshairs + 1, CenterTextureWidth);
			RMH_OpenGL_InitArray(&CrosshairY0[0], _MaxNumberOfMovableCrosshairs + 1, CenterTextureHeight);
			RMH_OpenGL_InitArray(&CrosshairOrderIndex[0], _MaxNumberOfMovableCrosshairs + 1, 0);

			// Initiliser Globale Arrays med start værdier - Postions Justerbar linje
			RMH_OpenGL_InitArray(&MovableLineX0[0], _MaxNumberOfMovableLines + 1, CenterTextureWidth - 50);
			RMH_OpenGL_InitArray(&MovableLineY0[0], _MaxNumberOfMovableLines + 1, CenterTextureHeight);
			RMH_OpenGL_InitArray(&MovableLineX1[0], _MaxNumberOfMovableLines + 1, CenterTextureWidth + 50);
			RMH_OpenGL_InitArray(&MovableLineY1[0], _MaxNumberOfMovableLines + 1, CenterTextureHeight);
			RMH_OpenGL_InitArray(&MovableLineOrderIndex[0], _MaxNumberOfMovableLines + 1, 0);

		}

		// ----------------------- Textur Overlejede Gennemsigtigt Panel Opsætnings Routine ------------------------ //

		GLvoid RMH_OpenGL_AddOverlayPanelToMainTexturePanel(System::Windows::Forms::Panel^ TexturePanel) {

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
			OverlayPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLWF::TexturePanel_MouseDown);
			OverlayPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLWF::TexturePanel_MouseUp);
			OverlayPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLWF::TexturePanel_MouseMove);
			OverlayPanel->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLWF::TexturePanel_MouseWheel);

		}

		// ---------------------------- Textur Panel Til Textur Konverterings Routiner ----------------------------- //

		GLdouble RMH_OpenGL_TranslateOverlayPanelMouseXPosToTextureXPos(System::Windows::Forms::MouseEventArgs^ OverlayPanelMouseEvent) {

			// Routinen oversætter overlejede panel Mus positioner til aktuel Textur Panel Mus Positioner

			// Lokale Variabler
			GLdouble MouseTextureXPos = 0.0;
			GLdouble PanelsWidthDifference = 0.0;

			// Udregn Pixel Differensen imellem overlejede panel og textur panelet 
			PanelsWidthDifference = CurrentTexturePanelWidth - OverlayPanel->Width;

			// Kontroller valgt indstilling for Aspect Ratio
			if (LocalAspectRatioFlag == true) {

				// Hvis der skal kompenseres for horizontal Aspect ratio
				if (LiveViewPosX0 <= 0.0) {

					// Konverter overlejede panel Mus position til aktuel Textur Panel Mus Position
					MouseTextureXPos = (OverlayPanelMouseEvent->X + PanelsWidthDifference) * (ImageDataPixelWidth / CurrentTexturePanelWidth);
					
				}
				else {

					// Konverter overlejede panel Mus position til aktuel Textur Panel Mus Position - Fast Aspect Ratio Mode
					MouseTextureXPos = ImageDataPixelWidth * ((GLdouble)OverlayPanelMouseEvent->X + PanelsWidthDifference - 0.5f * CurrentTexturePanelWidth + 0.5f * CurrentPanelWidthFixedAspect) / CurrentPanelWidthFixedAspect;
					
				}

			}
			else {

				// Konverter overlejede panel Mus position til aktuel Textur Panel Mus Position
				MouseTextureXPos = (OverlayPanelMouseEvent->X + PanelsWidthDifference) * (ImageDataPixelWidth / CurrentTexturePanelWidth);

			}

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

		GLdouble RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(System::Windows::Forms::MouseEventArgs^ OverlayPanelMouseEvent) {

			// Routinen oversætter overlejede panel Mus positioner til aktuel Textur Panel Mus Positioner

			// Lokale Variabler
			GLdouble MouseTextureYPos = 0.0;
			GLdouble PanelsHeightDifference = 0.0;

			// Udregn Pixel Differensen imellem overlejede panel og textur panelet 
			PanelsHeightDifference = CurrentTexturePanelHeight - OverlayPanel->Height;

			// Kontroller valgt indstilling for Aspect Ratio
			if (LocalAspectRatioFlag == true) {

				// Hvis der skal kompenseres for horizontal Aspect ratio
				if (LiveViewPosX0 <= 0.0) {

					// Konverter overlejede panel Mus position til aktuel Textur Panel Mus Position - Fast Aspect Ratio Mode
					MouseTextureYPos = ImageDataPixelHeight * ((GLdouble)OverlayPanelMouseEvent->Y + PanelsHeightDifference - 0.5f * CurrentTexturePanelHeight + 0.5f * CurrentPanelHeightFixedAspect) / CurrentPanelHeightFixedAspect;

				}
				else {

					// Konverter overlejede panel Mus position til aktuel Textur Panel Mus Position
					MouseTextureYPos = (OverlayPanelMouseEvent->Y + PanelsHeightDifference) * (ImageDataPixelHeight / CurrentTexturePanelHeight);

				}

			}
			else {

				// Konverter overlejede panel Mus position til aktuel Textur Panel Mus Position
				MouseTextureYPos = (OverlayPanelMouseEvent->Y + PanelsHeightDifference) * (ImageDataPixelHeight / CurrentTexturePanelHeight);

			}

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

		// -------------------------- Billede Textur Genererings Og Rendererings Routiner -------------------------- //

		GLvoid RMH_OpenGL_MakeRenderContextCurrent() {

			// Routinen Gør Tilhørende Render kontekst det nuværende render kontekst

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			wglMakeCurrent(m_hDC, m_hglrc);

		}

		GLvoid RMH_OpenGL_MakeRenderContextNULL() {

			// Routinen nulstiller tilhørende Render kontekst

			// Nulstil Render kontekst
			wglMakeCurrent(NULL, NULL);

		}

		GLvoid RMH_OpenGL_EnableTextureLinearInterpolation(bool EnableInterpolationFlag) {

			// Routinen aktiverer eller deaktiverer Linear Textur interpolation

			// Opdater globalt klasse flag
			ClassEnableInterpolationFlag = EnableInterpolationFlag;

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();

			// Aktiver OpenGL 2D Texture
			glEnable(GL_TEXTURE_2D);

			// Bind Texturen som et 2D textur
			glBindTexture(GL_TEXTURE_2D, ImageTecture[0]);

			// Skal Linear Interpolation aktiveres
			if (EnableInterpolationFlag == true) {

				// Konfigurer Textur parametere
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			}
			else {

				// Konfigurer Textur parametere
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			}

			// Deaktiver Texture
			glDisable(GL_TEXTURE_2D);

		}

		GLvoid RMH_OpenGL_SetGraphicsElementsPixelParameters(unsigned int FrameWidth, unsigned int FrameHeight) {

			// Routinen indstiller pixels størrelse for klassens grafiske elementer og objekter

			// Reference Opløsning, som værdierne er blivet dimensionerede til ->
			GLfloat ReferenceFrameWidth = 384.0;
			GLfloat ReferenceFrameHeight = 288.0;
			GLfloat RefFrameWidthToCurrentRatio = (FrameWidth / ReferenceFrameWidth);
			GLfloat RefFrameHeightToCurrentRatio = (FrameHeight / ReferenceFrameHeight);

			// Nulstil og opdater default Positions justerbar Rektangel Konfigurations parameter
			MinimumRectHeight = 20.0 * RefFrameHeightToCurrentRatio;
			MinimumRectWidth = 20.0 * RefFrameWidthToCurrentRatio;
			InitialRectWidth = 48.0 * ((RefFrameWidthToCurrentRatio + RefFrameHeightToCurrentRatio) * 0.5);
			DefaultRectLineWidth = 1.0 * RefFrameWidthToCurrentRatio;
			CursorChangeOffset = 2.0 * ((RefFrameWidthToCurrentRatio + RefFrameHeightToCurrentRatio) * 0.5);
			RectTextureBorderPadding = 5.0 * ((RefFrameWidthToCurrentRatio + RefFrameHeightToCurrentRatio) * 0.5);
			ROIIdentifierLabelXPixelOffset = 1.0 * RefFrameWidthToCurrentRatio;
			ROIIdentifierLabelYPixelOffset = 2.0 * RefFrameHeightToCurrentRatio;

			// Nulstil og opdater default Positions justerbar Crosshair Konfigurations parameter
			CrosshairSize = 2.0 * ((RefFrameWidthToCurrentRatio + RefFrameHeightToCurrentRatio) * 0.5); // Chrosshair Størrelsen
			CrosshairLineWidth = 2.0; // Linjens Tykkelse - 2 for alle opløsninger
			MovableLineQuadrant1LabelXOffset = -10.0 * RefFrameWidthToCurrentRatio;
			MovableLineQuadrant1LabelYOffset = 3.0 * RefFrameHeightToCurrentRatio;
			MovableLineQuadrant2LabelXOffset = 2.0 * RefFrameWidthToCurrentRatio;
			MovableLineQuadrant2LabelYOffset = 3.0 * RefFrameHeightToCurrentRatio;
			MovableLineQuadrant3LabelXOffset = 2.0 * RefFrameWidthToCurrentRatio;
			MovableLineQuadrant3LabelYOffset = -2.0 * RefFrameHeightToCurrentRatio;
			MovableLineQuadrant4LabelXOffset = -10.0 * RefFrameWidthToCurrentRatio;
			MovableLineQuadrant4LabelYOffset = -2.0 * RefFrameHeightToCurrentRatio;

			// Nulstil og opdater default Crosshair Med Center Label Konfigurations parameter
			ChrosshairWithCenterLabelXOffset = -4.0 * RefFrameWidthToCurrentRatio;
			ChrosshairWithCenterLabelYOffset = 2.8 * RefFrameHeightToCurrentRatio;

			// Nulstil og opdater default Positions justerbar linje Konfigurations parameter
			MovableLineCursorOffset = 4.0 * ((RefFrameWidthToCurrentRatio + RefFrameHeightToCurrentRatio) * 0.5);
			MovableLineCurnerToMiddleOffset = 4.0 * ((RefFrameWidthToCurrentRatio + RefFrameHeightToCurrentRatio) * 0.5);
			MovableLineMinimumLength = 10.0 * ((RefFrameWidthToCurrentRatio + RefFrameHeightToCurrentRatio) * 0.5);
			LineTextureBorderPadding = 3.0 * ((RefFrameWidthToCurrentRatio + RefFrameHeightToCurrentRatio) * 0.5);

			// Nulstil og opdater default text label baggrunds Konfigurations parameter
			LabelBackgroundXOffset = 0.2 * RefFrameWidthToCurrentRatio;
			LabelBackgroundYOffset = 1.1 * RefFrameHeightToCurrentRatio;
			LabelBackgroundWidth = 8.5 * RefFrameWidthToCurrentRatio;
			LabelBackgroundHeight = 1.5 * RefFrameHeightToCurrentRatio;

			// Nulstil og opdater default center text label baggrunds Konfigurations parameter
			CenterLabelBackgroundXOffset = 0.3 * RefFrameWidthToCurrentRatio;
			CenterLabelBackgroundYOffset = 1.1 * RefFrameHeightToCurrentRatio;
			CenterLabelBackgroundWidth = 9.8 * RefFrameWidthToCurrentRatio;
			CenterLabelBackgroundHeight = 1.5 * RefFrameHeightToCurrentRatio;

			// Nulstil og opdater default mus text label baggrunds Konfigurations parameter
			MouseLabelBackgroundXOffset = 0.3 * RefFrameWidthToCurrentRatio;
			MouseLabelBackgroundYOffset = 1.1 * RefFrameHeightToCurrentRatio;
			MouseLabelBackgroundWidth = 16.2 * RefFrameWidthToCurrentRatio;
			MouseLabelBackgroundHeight = 1.5 * RefFrameHeightToCurrentRatio;
			MouseLabelQuadrant1LabelXOffset = -17.0 * RefFrameWidthToCurrentRatio;
			MouseLabelQuadrant1LabelYOffset = 3.0 * RefFrameHeightToCurrentRatio;
			MouseLabelQuadrant4LabelXOffset = -17.0 * RefFrameWidthToCurrentRatio;
			MouseLabelQuadrant4LabelYOffset = -2.0 * RefFrameHeightToCurrentRatio;

		}

		GLvoid RMH_OpenGL_InitImageTexture(unsigned int FrameWidth, unsigned int FrameHeight) {

			// Routinen benyttes til at opsætte en OpenGL textur til grafisk renderering

			// Sæt Textur Parameter - Width og Height skal være et multiplum af 2
			TextureWidth = FrameWidth;
			TextureHeight = FrameHeight;
			ImageTecture = new GLuint[1];

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();

			// Indstil pixels størrelse for klassens grafiske elementer og objekter
			RMH_OpenGL_SetGraphicsElementsPixelParameters(FrameWidth, FrameHeight);

			// Initiliser Klasse arrays og variabler med start værdier
			RMH_OpenGL_InitializeGlobalVariabelsAndArrays(FrameWidth, FrameHeight);

			// Bug Texturen som skal rendererer Billede data
			glGenTextures(1, ImageTecture);

			// Aktiver OpenGL 2D Texture
			glEnable(GL_TEXTURE_2D);

			// Aktiver Textur Blending
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Bind Texturen som et 2D textur
			glBindTexture(GL_TEXTURE_2D, ImageTecture[0]);

			// Konfigurer Textur parametere (FrameWidth * UltraResolutionTextureScaleFactor, FrameHeight * UltraResolutionTextureScaleFactor - Ultra Opløsning)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, FrameWidth * UltraResolutionTextureScaleFactor, FrameHeight * UltraResolutionTextureScaleFactor, 0, GL_RGB, GL_UNSIGNED_SHORT, NULL);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			// Er Linear Interpolation aktiverede
			if (ClassEnableInterpolationFlag == true) {

				// Indstil interpolerings metode - linear
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			}
			else {

				// Indstil interpolerings metode - nærest
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			}
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			// Deaktiver Texture
			glDisable(GL_TEXTURE_2D);

		}

		GLvoid RMH_OpenGL_WriteImageDataToTexture(unsigned short* FrameData, unsigned int FrameWidth, unsigned int FrameHeight) {

			// Routinen skriver billede data til genereret Textur
			
			// Opdater Textur data med billede data
			glBindTexture(GL_TEXTURE_2D, ImageTecture[0]);
			
			// Upload the image data to the texture
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, FrameWidth, FrameHeight, GL_RGB, GL_UNSIGNED_SHORT, FrameData);

		}

		GLvoid RMH_OpenGL_UpdateTextureFieldOfView(unsigned int FrameWidth, unsigned int FrameHeight) {

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
			gluPerspective(PlaneFieldOfView, PlaneAspectRatio, 0.1, 500.0);
			gluLookAt(PlaneXLook, PlaneYLook, PlaneDistance * 0.5, PlaneXLook, PlaneYLook, 0, 0, 1, 0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

		}
		
		// ------------------------------ Label Rendererings Og Håndterings Routiner ------------------------------- //

		GLvoid RMH_OpenGL_glPrint(const char* CharArray) {

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

		GLvoid RMH_OpenGL_RenderStringOnTexture(GLfloat StringX, GLfloat StringY, std::string DisplayString, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen rendererer et givet string på et OpenGL Textur

			// Konfigurer Textens Farve
			glColor3ub(ColorR, ColorG, ColorB);

			// Indstil textens position på textur
			glRasterPos2f(StringX, StringY);

			// Render givet string på textur
			RMH_OpenGL_glPrint(DisplayString.c_str());

		}

		// ------------------------------ Linje Rendererings Og Håndterings Routiner ------------------------------- //

		GLvoid RMH_OpenGL_RenderLine(GLfloat LineX0, GLfloat LineY0, GLfloat LineX1, GLfloat LineY1, GLfloat LineWidth, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen renderer en linje på texturen med givet input kordinater

			// Kontroller valgt indstilling for Aspect Ratio
			if (LocalAspectRatioFlag == true) {

				// Hvis der skal kompenseres for horizontal Aspect ratio
				if (LiveViewPosX0 <= 0.0) {

					// Udregn Linjens X0/X1 Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					LineX0 = ((GLfloat)LineX0 * CurrentTexturePanelWidth * TotalTextureScalableWidth);
					LineX1 = ((GLfloat)LineX1 * CurrentTexturePanelWidth * TotalTextureScalableWidth);

					// Udregn Linjens X0/X1 Kordinat ved skallering af textur vinduet - fast aspect ratio mode
					LineY0 = ((GLfloat)LineY0 * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight);
					LineY1 = ((GLfloat)LineY1 * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight);
					LineY0 = LineY0 + AspectRatioHeightOffSet;
					LineY1 = LineY1 + AspectRatioHeightOffSet;

				}
				else {

					// Udregn Linjens Y0/Y1 Kordinat ved skallering af textur vinduet
					LineY0 = ((GLfloat)LineY0 * CurrentTexturePanelHeight * TotalTextureScalableHeight);
					LineY1 = ((GLfloat)LineY1 * CurrentTexturePanelHeight * TotalTextureScalableHeight);

					// Udregn Linjens X0/X1 Kordinat ved skallering af textur vinduet - fast aspect ratio mode
					LineX0 = ((GLfloat)LineX0 * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth);
					LineX1 = ((GLfloat)LineX1 * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth);
					LineX0 = LineX0 + AspectRatioWidthOffSet;
					LineX1 = LineX1 + AspectRatioWidthOffSet;

				}

			}
			else {

				// Udregn Linjens Y0/Y1 Kordinat ved skallering af textur vinduet
				LineY0 = ((GLfloat)LineY0 * CurrentTexturePanelHeight * TotalTextureScalableHeight);
				LineY1 = ((GLfloat)LineY1 * CurrentTexturePanelHeight * TotalTextureScalableHeight);

				// Udregn Linjens X0/X1 Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
				LineX0 = ((GLfloat)LineX0 * CurrentTexturePanelWidth * TotalTextureScalableWidth);
				LineX1 = ((GLfloat)LineX1 * CurrentTexturePanelWidth * TotalTextureScalableWidth);

			}

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil linjens Farve
			glColor3ub(ColorR, ColorG, ColorB);

			// Indstil Linjens tykkelse
			glLineWidth(LineWidth);

			// Render Linje på textur
			glBegin(GL_LINES);

			// Render linje med givet kordinater
			glVertex2f(LineX0, LineY0);
			glVertex2f(LineX1, LineY1);

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

			// Renderer Linje Identifikations Label
			RMH_OpenGL_RenderStringOnTexture((LineX0 + LineX1) * 0.5, (LineY0 + LineY1) * 0.5, "L" + RMH_Conversion_IntToStdString(RenderedLineCounter + 1), 255 - ColorR, 255 - ColorG, 255 - ColorB);

		}

		// -------------------- Positions Justerbar Linje Rendererings Og Håndterings Routiner --------------------- //

		LineSpecsPosition RMH_OpenGL_ReadLineType(GLfloat LineX0, GLfloat LineY0, GLfloat LineX1, GLfloat LineY1) {

			// Routinen kontrollerer om en linje, med givet kordinater, er en Type 1 linje

			// Lokale variabler
			LineSpecsPosition LineParameters;

			// Nulstil Linjens Pixel længde parameter
			LineParameters.LinePixelLength = 0;
			// Nulstil Linjens Type parameter
			LineParameters.LineType = 0;
			// Nulstil Linjens hældnings parameter
			LineParameters.LineSlope = 0;

			// ------------------------------ Linje Type 1 ------------------------------ //

			// Kontroller linje typen
			if ((LineX0 < LineX1) && (LineY0 < LineY1)) {

				// Opdater Linjens Type parameter
				LineParameters.LineType = 1;

				// Kontroller hvilket kordinat sæt har størst længde
				if ((LineX1 - LineX0) >= (LineY1 - LineY0)) {

					// Udregn Linje pixel længden
					LineParameters.LinePixelLength = LineX1 - LineX0;

					// Udregn Linjens Hældning
					LineParameters.LineSlope = (LineY1 - LineY0) / (LineX1 - LineX0);

					// Indstil Linjens X/Y Offsets
					LineParameters.LineXOffset = 1;
					LineParameters.LineYOffset = LineParameters.LineSlope;

				}
				else {

					// Udregn Linje pixel længden
					LineParameters.LinePixelLength = LineY1 - LineY0;

					// Udregn Linjens Hældning
					LineParameters.LineSlope = (LineX0 - LineX1) / (LineY1 - LineY0);

					// Indstil Linjens X/Y Offsets
					LineParameters.LineXOffset = -LineParameters.LineSlope;
					LineParameters.LineYOffset = 1;

				}
				
			}

			// ------------------------------ Linje Type 2 ------------------------------ //

			// Kontroller linje typen
			if ((LineX0 > LineX1) && (LineY0 < LineY1)) {

				// Opdater Linjens Type parameter
				LineParameters.LineType = 2;

				// Kontroller hvilket kordinat sæt har størst længde
				if ((LineX0 - LineX1) >= (LineY1 - LineY0)) {

					// Udregn Linje pixel længden
					LineParameters.LinePixelLength = LineX0 - LineX1;

					// Udregn Linjens Hældning
					LineParameters.LineSlope = (LineY1 - LineY0) / (LineX0 - LineX1);

					// Indstil Linjens X/Y Offsets
					LineParameters.LineXOffset = -1;
					LineParameters.LineYOffset = LineParameters.LineSlope;

				}
				else {

					// Udregn Linje pixel længden
					LineParameters.LinePixelLength = LineY1 - LineY0;

					// Udregn Linjens Hældning
					LineParameters.LineSlope = (LineX1 - LineX0) / (LineY1 - LineY0);

					// Indstil Linjens X/Y Offsets
					LineParameters.LineXOffset = LineParameters.LineSlope;
					LineParameters.LineYOffset = 1;

				}

			}

			// ------------------------------ Linje Type 3 ------------------------------ //

			// Kontroller linje typen
			if ((LineX0 > LineX1) && (LineY0 > LineY1)) {

				// Opdater Linjens Type parameter
				LineParameters.LineType = 3;

				// Kontroller hvilket kordinat sæt har størst længde
				if ((LineX0 - LineX1) >= (LineY0 - LineY1)) {

					// Udregn Linje pixel længden
					LineParameters.LinePixelLength = LineX0 - LineX1;

					// Udregn Linjens Hældning
					LineParameters.LineSlope = (LineY0 - LineY1) / (LineX0 - LineX1);

					// Indstil Linjens X/Y Offsets
					LineParameters.LineXOffset = -1;
					LineParameters.LineYOffset = -LineParameters.LineSlope;

				}
				else {

					// Udregn Linje pixel længden
					LineParameters.LinePixelLength = LineY0 - LineY1;

					// Udregn Linjens Hældning
					LineParameters.LineSlope = (LineX1 - LineX0) / (LineY0 - LineY1);

					// Indstil Linjens X/Y Offsets
					LineParameters.LineXOffset = LineParameters.LineSlope;
					LineParameters.LineYOffset = -1;

				}

			}

			// ------------------------------ Linje Type 4 ------------------------------ //

			// Kontroller linje typen
			if ((LineX0 < LineX1) && (LineY0 > LineY1)) {

				// Opdater Linjens Type parameter
				LineParameters.LineType = 4;

				// Kontroller hvilket kordinat sæt har størst længde
				if ((LineX1 - LineX0) >= (LineY0 - LineY1)) {

					// Udregn Linje pixel længden
					LineParameters.LinePixelLength = LineX1 - LineX0;

					// Udregn Linjens Hældning
					LineParameters.LineSlope = (LineY0 - LineY1) / (LineX1 - LineX0);

					// Indstil Linjens X/Y Offsets
					LineParameters.LineXOffset = 1;
					LineParameters.LineYOffset = -LineParameters.LineSlope;

				}
				else {

					// Udregn Linje pixel længden
					LineParameters.LinePixelLength = LineY0 - LineY1;

					// Udregn Linjens Hældning
					LineParameters.LineSlope = (LineX0 - LineX1) / (LineY0 - LineY1);

					// Indstil Linjens X/Y Offsets
					LineParameters.LineXOffset = -LineParameters.LineSlope;
					LineParameters.LineYOffset = -1;

				}

			}

			// ------------------------------ Linje Type 5 ------------------------------ //

			// Kontroller linje typen
			if ((LineY0 == LineY1) && (LineX0 < LineX1)) {

				// Opdater Linjens Type parameter
				LineParameters.LineType = 5;

				// Udregn Linje pixel længden
				LineParameters.LinePixelLength = LineX1 - LineX0;

				// Udregn Linjens Hældning
				LineParameters.LineSlope = 1;

				// Indstil Linjens X/Y Offsets
				LineParameters.LineXOffset = 1;
				LineParameters.LineYOffset = 0;

			}

			// ------------------------------ Linje Type 6 ------------------------------ //

			// Kontroller linje typen
			if ((LineY0 == LineY1) && (LineX0 > LineX1)) {

				// Opdater Linjens Type parameter
				LineParameters.LineType = 6;

				// Udregn Linje pixel længden
				LineParameters.LinePixelLength = LineX0 - LineX1;

				// Udregn Linjens Hældning
				LineParameters.LineSlope = 1;

				// Indstil Linjens X/Y Offsets
				LineParameters.LineXOffset = -1;
				LineParameters.LineYOffset = 0;

			}

			// ------------------------------ Linje Type 7 ------------------------------ //

			// Kontroller linje typen
			if ((LineX0 == LineX1) && (LineY0 < LineY1)) {

				// Opdater Linjens Type parameter
				LineParameters.LineType = 7;

				// Udregn Linje pixel længden
				LineParameters.LinePixelLength = LineY1 - LineY0;

				// Udregn Linjens Hældning
				LineParameters.LineSlope = 1;

				// Indstil Linjens X/Y Offsets
				LineParameters.LineXOffset = 0;
				LineParameters.LineYOffset = 1;

			}

			// ------------------------------ Linje Type 8 ------------------------------ //

			// Kontroller linje typen
			if ((LineX0 == LineX1) && (LineY0 > LineY1)) {

				// Opdater Linjens Type parameter
				LineParameters.LineType = 8;

				// Udregn Linje pixel længden
				LineParameters.LinePixelLength = LineY0 - LineY1;

				// Udregn Linjens Hældning
				LineParameters.LineSlope = 1;

				// Indstil Linjens X/Y Offsets
				LineParameters.LineXOffset = 0;
				LineParameters.LineYOffset = -1;

			}

			// -------------------------------------------------------------------------- //

			// Retuner linjens parametere
			return LineParameters;

		}
		
		LineSpecsPosition RMH_OpenGL_ReadLinePixelCoordinates(GLfloat LineX0, GLfloat LineY0, GLfloat LineX1, GLfloat LineY1) {

			// Routinen Udregner og lager hvilke pixels linjen berører 

			// Lokale variabler
			LineSpecsPosition LineParameters;

			// Læs Linjens Parametere - Type, Hældning og X/Y Offset
			LineParameters = RMH_OpenGL_ReadLineType(LineX0, LineY0, LineX1, LineY1);

			// Læs Linjens positions kordinater
			LineParameters.LineX0Pos = LineX0;
			LineParameters.LineY0Pos = LineY0;
			LineParameters.LineX1Pos = LineX1;
			LineParameters.LineY1Pos = LineY1;

			// Loop til og med den udregnede linje pixel længde
			for (unsigned int i = 0; i < LineParameters.LinePixelLength; i++) {

				// Læs og lager linjens pixels i klasse array
				LineParameters.LineXCordinates[i] = RMH_Math_Round(LineX0);
				LineParameters.LineYCordinates[i] = RMH_Math_Round(LineY0);
				
				// Inkrementer linjens X0/Y0 kordinater med linjens X/Y hældning
				LineX0 = LineX0 + LineParameters.LineXOffset;
				LineY0 = LineY0 + LineParameters.LineYOffset;

			}

			// Retuner Linjens pixel længde
			return LineParameters;

		}

		bool RMH_OpenGL_IsCursorInsideLine(GLdouble MouseXPosition, GLdouble MouseYPosition, GLfloat LineX0, GLfloat LineY0, GLfloat LineX1, GLfloat LineY1) {

			// Routinen kontrolerer om Mus Cursoren er indenfor CrossHair arealet

			// Lokale variabler
			LineSpecsPosition LineParameters;
			bool IsInsideStatus = false;

			// Læs Hvilke pixels linjen berører
			LineParameters = RMH_OpenGL_ReadLinePixelCoordinates(LineX0, LineY0, LineX1, LineY1);

			// Loop til og med den udregnede linje pixel længde
			for (unsigned int i = 0; i < LineParameters.LinePixelLength; i++) {

				// Kontroller om Mus Cursoren er inde i linjens areal. For X positionen 
				if (MouseXPosition >= LineParameters.LineXCordinates[i] - MovableLineCursorOffset &&
					MouseXPosition <= LineParameters.LineXCordinates[i] + MovableLineCursorOffset) {

					// Kontroller om Mus Cursoren er inde i linjens areal. For Y positionen
					if (MouseYPosition >= LineParameters.LineYCordinates[i] - MovableLineCursorOffset &&
						MouseYPosition <= LineParameters.LineYCordinates[i] + MovableLineCursorOffset) {

						//cout << "Inside" << endl;

						// Opdater Cursor positions status
						IsInsideStatus = true;

						// bryd for loop
						break;

					}

				}

			}

			// Retuner Cursor positions status
			return IsInsideStatus;

		}

		LineMovableSides RMH_OpenGL_GetSellectedLineMovableSide(GLdouble MouseXPosition, GLdouble MouseYPosition, unsigned short LineTag) {

			// Routinen læser og retunerer hvilken siden af linjen som Musen er positionerede ved.

			// Lokale variabler
			LineSpecsPosition LineParameters;
			LineMovableSides ReturnedSide = LineMovableSides::Outside;

			// Læs Hvilke pixels linjen berører
			LineParameters = RMH_OpenGL_ReadLinePixelCoordinates(
				MovableLineX0[LineTag], MovableLineY0[LineTag], 
				MovableLineX1[LineTag], MovableLineY1[LineTag]);

			// Loop til og med den udregnede linje pixel længde
			for (unsigned int i = 0; i < LineParameters.LinePixelLength; i++) {

				// Kontroller om Mus Cursoren er inde i linjens areal. For X positionen 
				if (MouseXPosition >= LineParameters.LineXCordinates[i] - MovableLineCursorOffset &&
					MouseXPosition <= LineParameters.LineXCordinates[i] + MovableLineCursorOffset) {

					// Kontroller om Mus Cursoren er inde i linjens areal. For Y positionen
					if (MouseYPosition >= LineParameters.LineYCordinates[i] - MovableLineCursorOffset &&
						MouseYPosition <= LineParameters.LineYCordinates[i] + MovableLineCursorOffset) {

						// Opdater Retunerede valgt linje enum værdi
						ReturnedSide = LineMovableSides::Middle;

						// bryd for loop
						break;

					}

				}

			}

			// Kontroller om Mus Cursoren er inde i linjens venstre areal - X0 positionen
			if (MouseXPosition >= MovableLineX0[LineTag] - (GLfloat)MovableLineCursorOffset &&
				MouseXPosition <= MovableLineX0[LineTag] + (GLfloat)MovableLineCursorOffset) {

				// Kontroller om Mus Cursoren er inde i linjens venstre areal - X0 positionen
				if (MouseYPosition >= MovableLineY0[LineTag] - (GLfloat)MovableLineCursorOffset &&
					MouseYPosition <= MovableLineY0[LineTag] + (GLfloat)MovableLineCursorOffset) {

					// Opdater Retunerede valgt linje enum værdi
					ReturnedSide = LineMovableSides::LeftSide;

				}

			}

			// Kontroller om Mus Cursoren er inde i linjens højre areal - X1 positionen
			if (MouseXPosition >= MovableLineX1[LineTag] - (GLfloat)MovableLineCursorOffset &&
				MouseXPosition <= MovableLineX1[LineTag] + (GLfloat)MovableLineCursorOffset) {

				// Kontroller om Mus Cursoren er inde i linjens højre areal - X1 positionen
				if (MouseYPosition >= MovableLineY1[LineTag] - (GLfloat)MovableLineCursorOffset &&
					MouseYPosition <= MovableLineY1[LineTag] + (GLfloat)MovableLineCursorOffset) {

					// Opdater Retunerede valgt linje enum værdi
					ReturnedSide = LineMovableSides::RightSide;

				}

			}

			// Retuner linje enum værdi
			return ReturnedSide;

		}

		System::Windows::Forms::Cursor^ RMH_OpenGL_GetLineCursor(LineMovableSides LineSide) {

			// Routinen retunerer relavant tilhørende cursor til givet linje position 

			// Valg af linje side
			switch (LineSide) {

				// Retuner relavant cursor
				case LineMovableSides::LeftSide: return Cursors::SizeAll;
				case LineMovableSides::Middle: return Cursors::SizeAll;
				case LineMovableSides::RightSide: return Cursors::SizeAll;
				default: return Cursors::Default;

			}

		}

		GLvoid RMH_OpenGL_ChangeLineCursor(GLdouble MouseXPosition, GLdouble MouseYPosition, unsigned short LineTag) {

			// Routinen Opdaterer det overlejede panels Cursor, afhængigt af hvilken linje siden musen rør

			// Opdater overlejede panels Cursor
			OverlayPanel->Cursor = RMH_OpenGL_GetLineCursor(RMH_OpenGL_GetSellectedLineMovableSide(MouseXPosition, MouseYPosition, LineTag));

		}

		GLvoid RMH_OpenGL_HandleLineMouseDownEvents(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer events og stadier når det klikkes på en positions justerbar linje

			// Nulstil Valgte Crosshair Index værdi
			SelectedLineTagIndex = 0;

			// Hvis er Rendereret Rektangel eller crosshair ikke er valgt
			if (RectangleMoveFlag == false && CrosshairMoveFlag == false) {

				// Loop Igennem alle aktive Linjer 
				for (unsigned short i = 0; i < NmbOfActiveLines; i++) {

					// Kontroller om Mus Cursoren er inde i aktiv Line arealet
					// Hæjeste ordens prioritets Line vil altid blive valgt først i lag 
					if (RMH_OpenGL_IsCursorInsideLine(MouseXPosition, MouseYPosition,
						MovableLineX0[MovableLineOrderIndex[i]], MovableLineY0[MovableLineOrderIndex[i]], 
						MovableLineX1[MovableLineOrderIndex[i]], MovableLineY1[MovableLineOrderIndex[i]])) {

						// Opdater Linjens Move flag
						LineMoveFlag = true;

						// Lager Valgte linje Tag Index
						SelectedLineTagIndex = MovableLineOrderIndex[i];

						// Bryd For Loop
						break;

					}

				}

			}

			// Opdater "Old State" Antal Rendereret linjer variabel
			OldNmbOfActiveLines = NmbOfActiveLines;

			// Nulstil Valgte linje side enum
			SelectedLineSide = LineMovableSides::Outside;
			// Læs hvilken side af linjen er blevet valgt
			SelectedLineSide = RMH_OpenGL_GetSellectedLineMovableSide(MouseXPosition, MouseYPosition, SelectedLineTagIndex);

			// Læs nuværende rectangel kordinater/positioner ved nyt klick
			ClickLineX0PositionOffset = MouseXPosition - MovableLineX0[SelectedLineTagIndex];
			ClickLineY0PositionOffset = MouseYPosition - MovableLineY0[SelectedLineTagIndex];
			ClickLineX1PositionOffset = MouseXPosition - MovableLineX1[SelectedLineTagIndex];
			ClickLineY1PositionOffset = MouseYPosition - MovableLineY1[SelectedLineTagIndex];

		}

		GLvoid RMH_OpenGL_HandleLineMouseMoveEvents(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer events og stadier når en Klikkede positions justerbar linje skal bevære sig

			// Lokale variabler
			GLdouble LineXPosition = 0;
			GLdouble LineYPosition = 0;

			// Kontroller Antallet af aktive linjer og Valgte Index
			if (NmbOfActiveLines > 0 && SelectedLineTagIndex != 0) {

				// Opdater Det Overlejede Panels Cursor Type
				RMH_OpenGL_ChangeLineCursor(MouseXPosition, MouseYPosition, SelectedLineTagIndex);

				// Hvis der endnu ikke er blevet klippet på panalet
				if (OverlayPanelIsClick == false) {

					// Fortsæt ikke
					return;

				}

				// Hvilken Linje side position skal opdateres
				switch (SelectedLineSide) {

					// Venstre Linje hjørne
					case LineMovableSides::LeftSide:

						// Læs nye Linje Venstre hjørne position
						LineXPosition = MouseXPosition - ClickLineX0PositionOffset;
						LineYPosition = MouseYPosition - ClickLineX0PositionOffset;

						if (LineXPosition >= MovableLineX1[SelectedLineTagIndex] - MovableLineMinimumLength &&
							LineXPosition <= MovableLineX1[SelectedLineTagIndex] + MovableLineMinimumLength) {

							if (LineYPosition >= MovableLineY1[SelectedLineTagIndex] - MovableLineMinimumLength &&
								LineYPosition <= MovableLineY1[SelectedLineTagIndex] + MovableLineMinimumLength) {

								// Break case (Opdater ikke position)
								break;

							}

						}

						// Opdater Linjens Venstre hjørne position
						MovableLineX0[SelectedLineTagIndex] = LineXPosition;
						MovableLineY0[SelectedLineTagIndex] = LineYPosition;

					break;

					// Midt På Linje
					case LineMovableSides::Middle:

						// Skal hele linjen besæge sig
						if (LineMoveFlag == true) {

							// Opdater Linjens Venstre og Højre hjørne position
							MovableLineX0[SelectedLineTagIndex] = MouseXPosition - ClickLineX0PositionOffset;
							MovableLineY0[SelectedLineTagIndex] = MouseYPosition - ClickLineY0PositionOffset;
							MovableLineX1[SelectedLineTagIndex] = MouseXPosition - ClickLineX1PositionOffset;
							MovableLineY1[SelectedLineTagIndex] = MouseYPosition - ClickLineY1PositionOffset;

						}

					break;

					// Højre Linje hjørne
					case LineMovableSides::RightSide:

						// Læs nye Linje højre hjørne position
						LineXPosition = MouseXPosition - ClickLineX1PositionOffset;
						LineYPosition = MouseYPosition - ClickLineX1PositionOffset;

						if (LineXPosition >= MovableLineX0[SelectedLineTagIndex] - MovableLineMinimumLength &&
							LineXPosition <= MovableLineX0[SelectedLineTagIndex] + MovableLineMinimumLength) {

							if (LineYPosition >= MovableLineY0[SelectedLineTagIndex] - MovableLineMinimumLength &&
								LineYPosition <= MovableLineY0[SelectedLineTagIndex] + MovableLineMinimumLength) {

								// Break case (Opdater ikke position)
								break;

							}

						}

						// Opdater Linjens højre hjørne position
						MovableLineX1[SelectedLineTagIndex] = LineXPosition;
						MovableLineY1[SelectedLineTagIndex] = LineYPosition;

					break;

				}

				// Begræns Positionen af linjen til textur området
				if (MovableLineX0[SelectedLineTagIndex] <= LineTextureBorderPadding) MovableLineX0[SelectedLineTagIndex] = LineTextureBorderPadding;
				if (MovableLineX0[SelectedLineTagIndex] > ImageDataPixelWidth - LineTextureBorderPadding) MovableLineX0[SelectedLineTagIndex] = (ImageDataPixelWidth) - LineTextureBorderPadding;
				if (MovableLineY0[SelectedLineTagIndex] <= LineTextureBorderPadding) MovableLineY0[SelectedLineTagIndex] = LineTextureBorderPadding;
				if (MovableLineY0[SelectedLineTagIndex] > ImageDataPixelHeight - LineTextureBorderPadding) MovableLineY0[SelectedLineTagIndex] = (ImageDataPixelHeight) - LineTextureBorderPadding;
				if (MovableLineX1[SelectedLineTagIndex] <= LineTextureBorderPadding) MovableLineX1[SelectedLineTagIndex] = LineTextureBorderPadding;
				if (MovableLineX1[SelectedLineTagIndex] > ImageDataPixelWidth - LineTextureBorderPadding) MovableLineX1[SelectedLineTagIndex] = (ImageDataPixelWidth) - LineTextureBorderPadding;
				if (MovableLineY1[SelectedLineTagIndex] <= LineTextureBorderPadding) MovableLineY1[SelectedLineTagIndex] = LineTextureBorderPadding;
				if (MovableLineY1[SelectedLineTagIndex] > ImageDataPixelHeight - LineTextureBorderPadding) MovableLineY1[SelectedLineTagIndex] = (ImageDataPixelHeight) - LineTextureBorderPadding;

			}

		}

		LineSpecsPosition RMH_OpenGL_RenderMovableLine(unsigned short OrderPriority, GLfloat LineWidth, GLubyte SelectedColorR, GLubyte SelectedColorG, GLubyte SelectedColorB, GLubyte PassiveColorR, GLubyte PassiveColorG, GLubyte PassiveColorB) {

			// Routinen renderere en positions justerbar linje

			// Lokale variabler
			LineSpecsPosition RenderedLinePosition;

			// Kontroller for maximalt tag ordens værdi
			if (OrderPriority < 1 || OrderPriority > _MaxNumberOfMovableCrosshairs) {

				// Skriv Status Meddelse I Terminal
				cout << "Order Must Be Higher Then 0 And Less That Max" << endl;

			}
			else {

				// Læs linjens positions parametere 
				RenderedLinePosition = RMH_OpenGL_ReadLinePixelCoordinates(
					MovableLineX0[OrderPriority], MovableLineY0[OrderPriority], 
					MovableLineX1[OrderPriority], MovableLineY1[OrderPriority]);
				
				// Lager linjens rendererings Orden
				MovableLineOrderIndex[RenderedLineCounter] = OrderPriority;

				// Er Denne Rendereret linje Den sidst valgte linje
				if (OrderPriority == SelectedLineTagIndex) {

					// Render Linje på textur
					RMH_OpenGL_RenderLine(
						RenderedLinePosition.LineX0Pos,
						RenderedLinePosition.LineY0Pos,
						RenderedLinePosition.LineX1Pos,
						RenderedLinePosition.LineY1Pos, LineWidth,
						SelectedColorR, SelectedColorG, SelectedColorB);
				}
				else {

					// Render Linje på textur
					RMH_OpenGL_RenderLine(
						RenderedLinePosition.LineX0Pos,
						RenderedLinePosition.LineY0Pos,
						RenderedLinePosition.LineX1Pos,
						RenderedLinePosition.LineY1Pos, LineWidth,
						PassiveColorR, PassiveColorG, PassiveColorB);

				}
				
				// Inkrementer linje rendererings tæller variabel
				RenderedLineCounter = RenderedLineCounter + 1;

			}

			// Retuner Rektanglens position
			return RenderedLinePosition;

		}

		// ---------------------------- CrossHair Rendererings Og Håndterings Routiner ----------------------------- //

		GLvoid RMH_OpenGL_EnableLabelBackground(bool EnableFlag) {

			// Routinen aktiverer rendereringen af en baggrunds rektangel til alle rendererede text labels

			// Opdater Label Baggrunds aktiverings flag
			EnableLabelBackgroundFlag = EnableFlag;

		}

		GLvoid RMH_OpenGL_ChangeRenderedLabelsColor(GLubyte LabelColorR, GLubyte LabelColorG, GLubyte LabelColorB) {

			// Routinen opdaterer farven for alle rendereret text labels
		
			// Opdater farven for alle rendereret text labels
			CommonLabelColorR = LabelColorR;
			CommonLabelColorG = LabelColorG;
			CommonLabelColorB = LabelColorB;

		}

		GLvoid RMH_OpenGL_ChangeLabelBackgroundColor(GLubyte BackgroundColorR, GLubyte BackgroundColorG, GLubyte BackgroundColorB) {

			// Routinen opdaterer label baggrundens farve

			// Indstil label baggrundens farve
			LabelBackgroundColorR = BackgroundColorR;
			LabelBackgroundColorG = BackgroundColorG;
			LabelBackgroundColorB = BackgroundColorB;

		}

		GLvoid RMH_OpenGL_RenderCrossHairWithLabel(GLfloat X, GLfloat Y, bool EnableLabel, System::String^ LabelString, GLubyte CrosshairColorR, GLubyte CrosshairColorG, GLubyte CrosshairColorB) {

			// Routinen Rendererer et Crosshair på Texturen, med eller uden tilhørende label

			// Lokale variabler
			GLfloat QuadrantXOffset = 0.0;
			GLfloat QuadrantYOffset = 0.0;

			// Skal en laben tilføjes til crosshairet
			if (EnableLabel == true) {

				// Kontroller om positionen er i kvardrant 1
				if (X >= ((GLfloat)ImageDataPixelWidth * 0.5) && Y <= ((GLfloat)ImageDataPixelHeight * 0.5)) {

					// Kontroller Live View Roterings Indstillingen
					if (LiveViewRotationDegrees == 0) {

						// Opdater Kvardrant Offset værdier - 0 grader rotation
						QuadrantXOffset = MovableLineQuadrant1LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant1LabelYOffset;

					}
					if (LiveViewRotationDegrees == 90) {

						// Opdater Kvardrant Offset værdier - 90 grader rotation
						QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant2LabelYOffset;

					}
					if (LiveViewRotationDegrees == 180) {

						// Opdater Kvardrant Offset værdier - 180 grader rotation
						QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant3LabelYOffset;

					}
					if (LiveViewRotationDegrees == 270) {

						// Opdater Kvardrant Offset værdier - 270 grader rotation
						QuadrantXOffset = MovableLineQuadrant4LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant4LabelYOffset;

					}

				}

				// Kontroller om positionen er i kvardrant 2
				if (X <= ((GLfloat)ImageDataPixelWidth * 0.5) && Y <= ((GLfloat)ImageDataPixelHeight * 0.5)) {
	
					// Kontroller Live View Roterings Indstillingen
					if (LiveViewRotationDegrees == 0) {

						// Opdater Kvardrant Offset værdier - 0 grader rotation
						QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant2LabelYOffset;

					}
					if (LiveViewRotationDegrees == 90) {

						// Opdater Kvardrant Offset værdier - 90 grader rotation
						QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant3LabelYOffset;

					}
					if (LiveViewRotationDegrees == 180) {

						// Opdater Kvardrant Offset værdier - 180 grader rotation
						QuadrantXOffset = MovableLineQuadrant4LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant4LabelYOffset;

					}
					if (LiveViewRotationDegrees == 270) {

						// Opdater Kvardrant Offset værdier - 1270 grader rotation
						QuadrantXOffset = MovableLineQuadrant1LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant1LabelYOffset;

					}

				}

				// Kontroller om positionen er i kvardrant 3
				if (X <= ((GLfloat)ImageDataPixelWidth * 0.5) && Y >= ((GLfloat)ImageDataPixelHeight * 0.5)) {

					// Kontroller Live View Roterings Indstillingen
					if (LiveViewRotationDegrees == 0) {

						// Opdater Kvardrant Offset værdier - 0 grader rotation
						QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant3LabelYOffset;

					}
					if (LiveViewRotationDegrees == 90) {

						// Opdater Kvardrant Offset værdier - 90 grader rotation
						QuadrantXOffset = MovableLineQuadrant4LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant4LabelYOffset;

					}
					if (LiveViewRotationDegrees == 180) {

						// Opdater Kvardrant Offset værdier - 180 grader rotation
						QuadrantXOffset = MovableLineQuadrant1LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant1LabelYOffset;

					}
					if (LiveViewRotationDegrees == 270) {

						// Opdater Kvardrant Offset værdier - 270 grader rotation
						QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant2LabelYOffset;

					}

				}

				// Kontroller om positionen er i kvardrant 4
				if (X >= ((GLfloat)ImageDataPixelWidth * 0.5) && Y >= ((GLfloat)ImageDataPixelHeight * 0.5)) {
	
					// Kontroller Live View Roterings Indstillingen
					if (LiveViewRotationDegrees == 0) {

						// Opdater Kvardrant Offset værdier - 0 grader rotation
						QuadrantXOffset = MovableLineQuadrant4LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant4LabelYOffset;

					}
					if (LiveViewRotationDegrees == 90) {

						// Opdater Kvardrant Offset værdier - 90 grader rotation
						QuadrantXOffset = MovableLineQuadrant1LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant1LabelYOffset;

					}
					if (LiveViewRotationDegrees == 180) {

						// Opdater Kvardrant Offset værdier - 180 grader rotation
						QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant2LabelYOffset;

					}
					if (LiveViewRotationDegrees == 270) {

						// Opdater Kvardrant Offset værdier - 270 grader rotation
						QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
						QuadrantYOffset = MovableLineQuadrant3LabelYOffset;

					}

				}

			}

			// Kontroller valgt indstilling for Aspect Ratio
			if (LocalAspectRatioFlag == true) {

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewRotationDegrees == 0) {

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewPosX0 <= 0.0) {

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
				if (LiveViewRotationDegrees == 90) {

					// Skaller X/Y koordinater
					X = X / ImageDataPixelAspectRatio;
					Y = Y * ImageDataPixelAspectRatio;

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewPosX0 <= 0.0) {

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
					X = LiveViewPosY1 - X;

				}
				if (LiveViewRotationDegrees == 180) {

					// Skaller X/Y koordinater
					Y = ImageDataPixelHeight - Y;
					X = ImageDataPixelWidth - X;

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewPosX0 <= 0.0) {

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
				if (LiveViewRotationDegrees == 270) {

					// Skaller X/Y koordinater
					X = (ImageDataPixelWidth - X) / ImageDataPixelAspectRatio;
					Y = (ImageDataPixelHeight - Y) * ImageDataPixelAspectRatio;

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewPosX0 <= 0.0) {

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
					X = LiveViewPosY1 - X;

				}

			}
			else {

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewRotationDegrees == 0) {

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					Y = Y * CurrentTexturePanelHeight * TotalTextureScalableHeight;

					// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					X = X * CurrentTexturePanelWidth * TotalTextureScalableWidth;

				}
				if (LiveViewRotationDegrees == 90) {

					// Skaller X/Y koordinater
					X = X / ImageDataPixelAspectRatio;
					Y = Y * ImageDataPixelAspectRatio;

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					Y = Y * CurrentTexturePanelWidth * TotalTextureScalableWidth;

					// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					X = X * CurrentTexturePanelHeight * TotalTextureScalableHeight;

					// Juster X Koordinat
					X = LiveViewPosY1 - X;

				}
				if (LiveViewRotationDegrees == 180) {

					// Skaller X/Y koordinater
					Y = ImageDataPixelHeight - Y;
					X = ImageDataPixelWidth - X;

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					Y = Y * CurrentTexturePanelHeight * TotalTextureScalableHeight;

					// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					X = X * CurrentTexturePanelWidth * TotalTextureScalableWidth;

				}
				if (LiveViewRotationDegrees == 270) {

					// Skaller X/Y koordinater
					X = (ImageDataPixelWidth - X) / ImageDataPixelAspectRatio;
					Y = (ImageDataPixelHeight - Y) * ImageDataPixelAspectRatio;

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					Y = Y * CurrentTexturePanelWidth * TotalTextureScalableWidth;

					// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					X = X * CurrentTexturePanelHeight * TotalTextureScalableHeight;

					// Juster X Koordinat
					X = LiveViewPosY1 - X;

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
				if (LiveViewRotationDegrees == 0) {

					// Render label rektanglens positioner
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset, (Y + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (Y + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (Y + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset, (Y + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);

				}
				if (LiveViewRotationDegrees == 90) {

					// Render label rektanglens positioner
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset, (X + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (X + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (X + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);
					glVertex2f((Y + QuadrantXOffset) - LabelBackgroundXOffset, (X + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);

				}
				if (LiveViewRotationDegrees == 180) {

					// Render label rektanglens positioner
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset, (Y + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (Y + QuadrantYOffset) - LabelBackgroundYOffset);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset + LabelBackgroundWidth, (Y + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);
					glVertex2f((X + QuadrantXOffset) - LabelBackgroundXOffset, (Y + QuadrantYOffset) - LabelBackgroundYOffset + LabelBackgroundHeight);

				}
				if (LiveViewRotationDegrees == 270) {

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
				if (LiveViewRotationDegrees == 0) {

					// Tilføj Label til crosshair
					RMH_OpenGL_RenderStringOnTexture(X + QuadrantXOffset, Y + QuadrantYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

				}
				if (LiveViewRotationDegrees == 90) {

					// Tilføj Label til crosshair
					RMH_OpenGL_RenderStringOnTexture(Y + QuadrantXOffset, X + QuadrantYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

				}
				if (LiveViewRotationDegrees == 180) {

					// Tilføj Label til crosshair
					RMH_OpenGL_RenderStringOnTexture(X + QuadrantXOffset, Y + QuadrantYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

				}
				if (LiveViewRotationDegrees == 270) {

					// Tilføj Label til crosshair
					RMH_OpenGL_RenderStringOnTexture(Y + QuadrantXOffset, X + QuadrantYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

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
			if (LiveViewRotationDegrees == 0) {

				// Vertikale Linje
				glVertex2f(X, Y - (CrosshairSize * 0.5));
				glVertex2f(X, Y + (CrosshairSize * 0.5));

				// Horisontal Linje
				glVertex2f(X - (CrosshairSize * 0.5), Y);
				glVertex2f(X + (CrosshairSize * 0.5), Y);

			}
			if (LiveViewRotationDegrees == 90) {

				// Vertikale Linje
				glVertex2f(Y - (CrosshairSize * 0.5), X);
				glVertex2f(Y + (CrosshairSize * 0.5), X);

				// Horisontal Linje
				glVertex2f(Y, X - (CrosshairSize * 0.5));
				glVertex2f(Y, X + (CrosshairSize * 0.5));

			}
			if (LiveViewRotationDegrees == 180) {

				// Vertikale Linje
				glVertex2f(X, Y - (CrosshairSize * 0.5));
				glVertex2f(X, Y + (CrosshairSize * 0.5));

				// Horisontal Linje
				glVertex2f(X - (CrosshairSize * 0.5), Y);
				glVertex2f(X + (CrosshairSize * 0.5), Y);

			}
			if (LiveViewRotationDegrees == 270) {

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

		GLvoid RMH_OpenGL_RenderCrossHairCenterLabel(GLfloat X, GLfloat Y, System::String^ LabelString, GLubyte CrosshairColorR, GLubyte CrosshairColorG, GLubyte CrosshairColorB) {

			// Routinen Rendererer et Crosshair på Texturen, hvor tilhørende label er centreret i bunden

			// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
			Y = ((GLfloat)Y * CurrentTexturePanelHeight * TotalTextureScalableHeight);

			// Kontroller valgt indstilling for Aspect Ratio
			if (LocalAspectRatioFlag == true) {

				// Udregn Crosshair X Kordinat ved skallering af textur vinduet - fast aspect ratio mode
				X = ((GLfloat)X * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth);
				X = X + AspectRatioWidthOffSet;
			}
			else {

				// Udregn Crosshair X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
				X = ((GLfloat)X * CurrentTexturePanelWidth * TotalTextureScalableWidth);

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

				// Render label rektanglens positioner
				glVertex2f((X + ChrosshairWithCenterLabelXOffset) - CenterLabelBackgroundXOffset, (Y + ChrosshairWithCenterLabelYOffset) - CenterLabelBackgroundYOffset);
				glVertex2f((X + ChrosshairWithCenterLabelXOffset) - CenterLabelBackgroundXOffset + CenterLabelBackgroundWidth, (Y + ChrosshairWithCenterLabelYOffset) - CenterLabelBackgroundYOffset);
				glVertex2f((X + ChrosshairWithCenterLabelXOffset) - CenterLabelBackgroundXOffset + CenterLabelBackgroundWidth, (Y + ChrosshairWithCenterLabelYOffset) - CenterLabelBackgroundYOffset + CenterLabelBackgroundHeight);
				glVertex2f((X + ChrosshairWithCenterLabelXOffset) - CenterLabelBackgroundXOffset, (Y + ChrosshairWithCenterLabelYOffset) - CenterLabelBackgroundYOffset + CenterLabelBackgroundHeight);

				// Konfiguration Slut
				glEnd();
				// Deaktiver 1D Texture
				glDisable(GL_TEXTURE_1D);
				glDisable(GL_BLEND);

			}

			// Tilføj Label til crosshair
			RMH_OpenGL_RenderStringOnTexture(X + ChrosshairWithCenterLabelXOffset, Y + ChrosshairWithCenterLabelYOffset, RMH_Conversion_SystemStringToStdString(LabelString), CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil Crosshair Farve
			glColor3ub(CrosshairColorR, CrosshairColorG, CrosshairColorB);

			// Indstil CrossHair Linje tykkelsen
			glLineWidth(CrosshairLineWidth);

			// Render Linje på textur
			glBegin(GL_LINES);

			// Vertikale Linje
			glVertex2f(X, Y - (CrosshairSize * 0.5));
			glVertex2f(X, Y + (CrosshairSize * 0.5));

			// Horisontal Linje
			glVertex2f(X - (CrosshairSize * 0.5), Y);
			glVertex2f(X + (CrosshairSize * 0.5), Y);

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

		}

		// ---------------------- Positions Justerbar CrossHair Og Label Håndterings Routiner ---------------------- //

		bool RMH_OpenGL_IsCursorInsideCrosshair(GLdouble MouseXPosition, GLdouble MouseYPosition, GLdouble CrossHairX0, GLdouble CrossHairY0) {

			// Routinen kontrolerer om Mus Cursoren er indenfor CrossHair arealet
			
			// Lokale variabler
			bool IsInsideStatus = false;

			// Kontroller om Mus Cursoren er inde i CrossHair areal - X positionen
			if (MouseXPosition >= CrossHairX0 - (CrosshairSize + CrosshairInsideAreaPadding) &&
				MouseXPosition <= CrossHairX0 + (CrosshairSize + CrosshairInsideAreaPadding)) {

				// Kontroller om Mus Cursoren er inde i CrossHair areal - X positionen
				if (MouseYPosition >= CrossHairY0 - (CrosshairSize + CrosshairInsideAreaPadding) &&
					MouseYPosition <= CrossHairY0 + (CrosshairSize + CrosshairInsideAreaPadding)) {

					// Opdater Cursor positions status
					IsInsideStatus = true;

				}

			}

			// Retuner Cursor positions status
			return IsInsideStatus;

		}

		CrosshairSizableSides RMH_OpenGL_GetSellectedCrosshairSizableSide(GLdouble MouseXPosition, GLdouble MouseYPosition, unsigned short CrosshairTag) {

			// Routinen læser og retunerer hvilken siden af Crosshairet Musen er positionerede ved.

			// Lokale variabler
			CrosshairSizableSides ReturnedSide = CrosshairSizableSides::Default;

			// Kontroller om Mus Cursoren er inde i CrossHair areal - X positionen
			if (MouseXPosition >= CrosshairX0[CrosshairTag] - (CrosshairSize + CrosshairInsideAreaPadding) &&
				MouseXPosition <= CrosshairX0[CrosshairTag] + (CrosshairSize + CrosshairInsideAreaPadding)) {

				// Kontroller om Mus Cursoren er inde i CrossHair areal - X positionen
				if (MouseYPosition >= CrosshairY0[CrosshairTag] - (CrosshairSize + CrosshairInsideAreaPadding) &&
					MouseYPosition <= CrosshairY0[CrosshairTag] + (CrosshairSize + CrosshairInsideAreaPadding)) {

					// Opdater Retunerede valgt linje enum værdi
					ReturnedSide = CrosshairSizableSides::Crosshair;

				}

			}
			
			// Retuner CrossHair enum værdi
			return ReturnedSide;

		}

		System::Windows::Forms::Cursor^ RMH_OpenGL_GetCrosshairCursor(CrosshairSizableSides CrosshairSide) {

			// Routinen retunerer relavant tilhørende cursor til givet Crosshair position 

			// Valg af Crosshair side
			switch (CrosshairSide) {

				// Retuner relavant cursor
				case CrosshairSizableSides::Crosshair: return Cursors::SizeAll;
				default: return Cursors::Default;

			}

		}

		GLvoid RMH_OpenGL_ChangeCrosshairCursor(GLdouble MouseXPosition, GLdouble MouseYPosition, unsigned short CrosshairTag) {

			// Routinen Opdaterer det overlejede panels Cursor, afhængigt af hvilken Croshair siden musen rør

			// Opdater overlejede panels Cursor
			OverlayPanel->Cursor = RMH_OpenGL_GetCrosshairCursor(RMH_OpenGL_GetSellectedCrosshairSizableSide(MouseXPosition, MouseYPosition, CrosshairTag));

		}

		GLvoid RMH_OpenGL_HandleCrosshairMouseDownEvents(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer events og stadier når det klikkes på en positions justerbar Crosshair

			// Nulstil Valgte Crosshair Index værdi
			SelectedCrosshairTagIndex = 0;

			// Hvis er Rendereret Rektangel ikke er valgt
			if (RectangleMoveFlag == false && LineMoveFlag == false) {

				// Loop Igennem alle aktive Crosshairs 
				for (unsigned short i = 0; i < NmbOfActiveCrosshairs; i++) {

					// Kontroller om Mus Cursoren er inde i aktiv Crosshair arealet
					// Hæjeste ordens prioritets Crosshairs vil altid blive valgt først i lag 
					if (RMH_OpenGL_IsCursorInsideCrosshair(MouseXPosition, MouseYPosition,
						CrosshairX0[CrosshairOrderIndex[i]], CrosshairY0[CrosshairOrderIndex[i]])) {

						// Opdater Crosshair Move flag
						CrosshairMoveFlag = true;

						// Lager Valgte Regtangel Tag Index
						SelectedCrosshairTagIndex = CrosshairOrderIndex[i];

						// Bryd For Loop
						break;

					}

				}

			}

			// Opdater "Old State" Antal Rendereret Crosshairs variabel
			OldNmbOfActiveCrosshairs = NmbOfActiveCrosshairs;

			// Læs nuværende rectangel kordinater/positioner ved nyt klick
			ClickCrosshairXPositionOffset = MouseXPosition - CrosshairX0[SelectedCrosshairTagIndex];
			ClickCrosshairYPositionOffset = MouseYPosition - CrosshairY0[SelectedCrosshairTagIndex];

		}

		GLvoid RMH_OpenGL_HandleCrosshairMouseMoveEvents(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer events og stadier når en Klikkede positions justerbar Crosshair skal bevære sig

			// Tilføj Rektangel Klik Offset Til Mus Positionen
			MouseXPosition = MouseXPosition - ClickCrosshairXPositionOffset;
			MouseYPosition = MouseYPosition - ClickCrosshairYPositionOffset;

			// Kontroller Antallet af aktive Crosshairs og Valgte Index
			if (NmbOfActiveCrosshairs > 0 && SelectedCrosshairTagIndex != 0) {

				// Opdater Det Overlejede Panels Cursor Type
				RMH_OpenGL_ChangeCrosshairCursor(MouseXPosition + ClickCrosshairXPositionOffset, MouseYPosition + ClickCrosshairYPositionOffset, SelectedCrosshairTagIndex);

				// Hvis der endnu ikke er blevet klippet på panalet
				if (OverlayPanelIsClick == false) {

					// Fortsæt ikke
					return;

				}

				// Skal hele rektanglen bevæge sig
				if (CrosshairMoveFlag == true) {

					// Opdater rektangel X og Y kordinater
					CrosshairX0[SelectedCrosshairTagIndex] = MouseXPosition;
					CrosshairY0[SelectedCrosshairTagIndex] = MouseYPosition;

				}

			}

			// Begræns Positionen af Crosshair til textur området
			if (CrosshairX0[SelectedCrosshairTagIndex] <= 1.0) CrosshairX0[SelectedCrosshairTagIndex] = 1.0;
			if (CrosshairY0[SelectedCrosshairTagIndex] <= 1.0) CrosshairY0[SelectedCrosshairTagIndex] = 1.0;
			if (CrosshairX0[SelectedCrosshairTagIndex] > ImageDataPixelWidth) CrosshairX0[SelectedCrosshairTagIndex] = (ImageDataPixelWidth) + 1.0;
			if (CrosshairY0[SelectedCrosshairTagIndex] > ImageDataPixelHeight) CrosshairY0[SelectedCrosshairTagIndex] = (ImageDataPixelHeight) + 1.0;

		}

		CrosshairWLabelPosition RMH_OpenGL_RenderMovableCrossHairWithLabel(unsigned short OrderPriority, System::String^ LabelString, GLubyte CrosshairSelectedColorR, GLubyte CrosshairSelectedColorG, GLubyte CrosshairSelectedColorB, GLubyte CrosshairPassiveColorR, GLubyte CrosshairPassiveColorG, GLubyte CrosshairPassiveColorB) {

			// Routinen renderere et positions justerbar Crosshair, med tilhørende Label

			// Lokale variabler
			CrosshairWLabelPosition RenderedCrossWLabelPosition;

			// Kontroller for maximalt tag ordens værdi
			if (OrderPriority < 1 || OrderPriority > _MaxNumberOfMovableCrosshairs) {

				// Skriv Status Meddelse I Terminal
				cout << "Order Must Be Higher Then 0 And Less That Max" << endl;

			}
			else {

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewRotationDegrees == 0) {

					// Læs Crosshair positions parametere til retunering - Konpenser For Live VIew Rotering
					RenderedCrossWLabelPosition.CrosshairX0Pos = CrosshairX0[OrderPriority];
					RenderedCrossWLabelPosition.CrosshairY0Pos = CrosshairY0[OrderPriority];

				}
				if (LiveViewRotationDegrees == 90) {

					// Læs Crosshair positions parametere til retunering - Konpenser For Live VIew Rotering
					RenderedCrossWLabelPosition.CrosshairX0Pos = (ImageDataPixelHeight - CrosshairY0[OrderPriority]) * ImageDataPixelAspectRatio;
					RenderedCrossWLabelPosition.CrosshairY0Pos = CrosshairX0[OrderPriority] / ImageDataPixelAspectRatio;

				}
				if (LiveViewRotationDegrees == 180) {

					// Læs Crosshair positions parametere til retunering - Konpenser For Live VIew Rotering
					RenderedCrossWLabelPosition.CrosshairX0Pos = ImageDataPixelWidth - CrosshairX0[OrderPriority];
					RenderedCrossWLabelPosition.CrosshairY0Pos = ImageDataPixelHeight - CrosshairY0[OrderPriority];
					
				}
				if (LiveViewRotationDegrees == 270) {

					// Læs Crosshair positions parametere til retunering - Konpenser For Live VIew Rotering
					RenderedCrossWLabelPosition.CrosshairX0Pos = CrosshairY0[OrderPriority] * ImageDataPixelAspectRatio;
					RenderedCrossWLabelPosition.CrosshairY0Pos = (ImageDataPixelWidth - CrosshairX0[OrderPriority]) / ImageDataPixelAspectRatio;

				}

				// Lager Crosshair med label rendererings Orden
				CrosshairOrderIndex[RenderedCrosshairCounter] = OrderPriority;

				// Er Denne Rendereret Regtangel Den sidst valgte Regtangel
				if (OrderPriority == SelectedCrosshairTagIndex) {

					// Render Crosshair med label på textur
					RMH_OpenGL_RenderCrossHairWithLabel(RenderedCrossWLabelPosition.CrosshairX0Pos, RenderedCrossWLabelPosition.CrosshairY0Pos, true, LabelString, CrosshairSelectedColorR, CrosshairSelectedColorG, CrosshairSelectedColorB);

				}
				else {

					// Render Crosshair med label på textur
					RMH_OpenGL_RenderCrossHairWithLabel(RenderedCrossWLabelPosition.CrosshairX0Pos, RenderedCrossWLabelPosition.CrosshairY0Pos, true, LabelString, CrosshairPassiveColorR, CrosshairPassiveColorG, CrosshairPassiveColorB);

				}

				// Inkrementer Crosshair rendererings tæller variabel
				RenderedCrosshairCounter = RenderedCrosshairCounter + 1;

			}

			// Retuner Rektanglens position
			return RenderedCrossWLabelPosition;

		}

		// ------------------------- Textur Mus Cursor label Trackings Håndterings Routiner ------------------------ //

		GLvoid RMH_OpenGL_EnableMouseCursorTrackingWLabel(bool EnableFlag) {

			// Routinen aktiverer eller deaktiverer Mus cursor label tracking

			// Opdater globalt variabel
			CursorTrackingEnableFlag = EnableFlag;

		}

		GLvoid RMH_OpenGL_UpdateCursorTrackingPosition(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer opdateringen af cursor label positionen, hvis featuren er aktiverede

			// Lokale variabler
			GLfloat QuadrantXOffset = 0.0;
			GLfloat QuadrantYOffset = 0.0;

			// Er Mus Cursor Tracking aktiverede
			if (CursorTrackingEnableFlag == true) {

				// Læs Mus Cursor X og Y Positionen
				CursorTrackXPos = MouseXPosition;
				CursorTrackYPos = MouseYPosition;

				// Kontroller om positionen er i kvardrant 1
				if (MouseXPosition >= ((GLfloat)ImageDataPixelWidth * 0.5) && MouseYPosition <= ((GLfloat)ImageDataPixelHeight * 0.5)) {
					// Opdater Kvardrant Offset værdier
					QuadrantXOffset = MouseLabelQuadrant1LabelXOffset;
					QuadrantYOffset = MouseLabelQuadrant1LabelYOffset;
				}

				// Kontroller om positionen er i kvardrant 2
				if (MouseXPosition <= ((GLfloat)ImageDataPixelWidth * 0.5) && MouseYPosition <= ((GLfloat)ImageDataPixelHeight * 0.5)) {
					// Opdater Kvardrant Offset værdier
					QuadrantXOffset = MovableLineQuadrant2LabelXOffset;
					QuadrantYOffset = MovableLineQuadrant2LabelYOffset;
				}

				// Kontroller om positionen er i kvardrant 3
				if (MouseXPosition <= ((GLfloat)ImageDataPixelWidth * 0.5) && MouseYPosition >= ((GLfloat)ImageDataPixelHeight * 0.5)) {
					// Opdater Kvardrant Offset værdier
					QuadrantXOffset = MovableLineQuadrant3LabelXOffset;
					QuadrantYOffset = MovableLineQuadrant3LabelYOffset;
				}

				// Kontroller om positionen er i kvardrant 4
				if (MouseXPosition >= ((GLfloat)ImageDataPixelWidth * 0.5) && MouseYPosition >= ((GLfloat)ImageDataPixelHeight * 0.5)) {
					// Opdater Kvardrant Offset værdier
					QuadrantXOffset = MouseLabelQuadrant4LabelXOffset;
					QuadrantYOffset = MouseLabelQuadrant4LabelYOffset;
				}

				// Kontroller valgt indstilling for Aspect Ratio
				if (LocalAspectRatioFlag == true) {

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewPosX0 <= 0.0) {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						MouseYPosition = ((GLfloat)MouseYPosition * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight);
						MouseYPosition = MouseYPosition + AspectRatioHeightOffSet;
						
						// Udregn label X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
						MouseXPosition = ((GLfloat)MouseXPosition * CurrentTexturePanelWidth * TotalTextureScalableWidth);

					}
					else {

						// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
						MouseYPosition = ((GLfloat)MouseYPosition * CurrentTexturePanelHeight * TotalTextureScalableHeight);

						// Udregn label X Kordinat ved skallering af textur vinduet - fast aspect ratio mode
						MouseXPosition = ((GLfloat)MouseXPosition * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth);
						MouseXPosition = MouseXPosition + AspectRatioWidthOffSet;

					}

				}
				else {

					// Udregn Crosshair Y Kordinat ved skallering af textur vinduet
					MouseYPosition = ((GLfloat)MouseYPosition * CurrentTexturePanelHeight * TotalTextureScalableHeight);

					// Udregn label X Kordinat ved skallering af textur vinduet - Auto aspect ratio mode
					MouseXPosition = ((GLfloat)MouseXPosition * CurrentTexturePanelWidth * TotalTextureScalableWidth);

				}

				// Opdater globale positions variabler
				CursorTrackTextureXPos = MouseXPosition + QuadrantXOffset;
				CursorTrackTextureYPos = MouseYPosition + QuadrantYOffset;

			}

		}

		MouseCursorPosition RMH_OpenGL_RenderMouseCursorLabel(System::String^ DisplayString, GLubyte LabelColorR, GLubyte LabelColorG, GLubyte LabelColorB) {

			// Routinen rendererer et Label Lige over Mus Cursor Positionen

			// Lokale variabler
			MouseCursorPosition NewCursorPos;

			// Skal der rendereres en baggrund til lablen
			if (EnableLabelBackgroundFlag == true) {

				// Aktiver OpenGL 1D Texture
				glEnable(GL_TEXTURE_1D);
				glEnable(GL_BLEND);

				// Indstil Label baggrundens Farve
				glColor4ub(LabelBackgroundColorR, LabelBackgroundColorG, LabelBackgroundColorB, CommonLabelBackgroundAlpha);

				// Render rektangel på textur
				glBegin(GL_QUADS);

				// Render label rektanglens positioner
				glVertex2f(CursorTrackTextureXPos - MouseLabelBackgroundXOffset, CursorTrackTextureYPos - MouseLabelBackgroundYOffset);
				glVertex2f(CursorTrackTextureXPos - MouseLabelBackgroundXOffset + MouseLabelBackgroundWidth, CursorTrackTextureYPos - MouseLabelBackgroundYOffset);
				glVertex2f(CursorTrackTextureXPos - MouseLabelBackgroundXOffset + MouseLabelBackgroundWidth, CursorTrackTextureYPos - MouseLabelBackgroundYOffset + MouseLabelBackgroundHeight);
				glVertex2f(CursorTrackTextureXPos - MouseLabelBackgroundXOffset, CursorTrackTextureYPos - MouseLabelBackgroundYOffset + MouseLabelBackgroundHeight);

				// Konfiguration Slut
				glEnd();
				// Deaktiver 1D Texture
				glDisable(GL_TEXTURE_1D);
				glDisable(GL_BLEND);

			}

			// Er Mus Cursor Tracking aktiverede
			if (CursorTrackingEnableFlag == true) {

				// Renderer Label Lige over Mus Cursor Positionen
				RMH_OpenGL_RenderStringOnTexture(CursorTrackTextureXPos, CursorTrackTextureYPos, RMH_Conversion_SystemStringToStdString(DisplayString) + ": X: " + RMH_Conversion_IntToStdString(CursorTrackXPos) + " Y: " + RMH_Conversion_IntToStdString(CursorTrackYPos), LabelColorR, LabelColorG, LabelColorB);

			}

			// Kontroller Live View Roterings Indstillingen
			if (LiveViewRotationDegrees == 0) {

				// Læs Mus Cursor X og Y Positionen
				NewCursorPos.CursorXPos = CursorTrackXPos;
				NewCursorPos.CursorYPos = CursorTrackYPos;

			}
			if (LiveViewRotationDegrees == 90) {

				// Læs Mus Cursor X og Y Positionen
				NewCursorPos.CursorXPos = ImageDataPixelWidth - CursorTrackYPos * ImageDataPixelAspectRatio;
				NewCursorPos.CursorYPos = CursorTrackXPos / ImageDataPixelAspectRatio;

			}
			if (LiveViewRotationDegrees == 180) {

				// Læs Mus Cursor X og Y Positionen
				NewCursorPos.CursorXPos = ImageDataPixelWidth - CursorTrackXPos;
				NewCursorPos.CursorYPos = ImageDataPixelHeight - CursorTrackYPos;

			}
			if (LiveViewRotationDegrees == 270) {

				// Læs Mus Cursor X og Y Positionen
				NewCursorPos.CursorXPos = CursorTrackYPos * ImageDataPixelAspectRatio;
				NewCursorPos.CursorYPos = ImageDataPixelHeight - CursorTrackXPos / ImageDataPixelAspectRatio;

			}

			// Retuner Mus Cursor Positionen
			return NewCursorPos;

		}

		// ---------------------------- Rektangel Rendererings Og Håndterings Routiner ----------------------------- //

		bool RMH_OpenGL_IsCursorInsideRectangle(GLdouble MouseXPosition, GLdouble MouseYPosition, GLdouble RectX0, GLdouble RectY0, GLdouble RectWidth, GLdouble RectHeight) {

			// Routinen kontrolerer om Mus Cursoren er indenfor rektangel arealet

			// Lokale variabler
			bool IsInsideStatus = false;

			// Kontroller om Mus Cursoren er inde i rektanglens areal - Width
			if (MouseXPosition >= RectX0 - CursorChangeOffset &&
				MouseXPosition <= RectX0 + RectWidth + CursorChangeOffset) {

				// Kontroller om Mus Cursoren er inde i rektanglens areal - Height
				if (MouseYPosition >= RectY0 - CursorChangeOffset &&
					MouseYPosition <= RectY0 + RectHeight + CursorChangeOffset) {

					// Opdater Cursor positions status
					IsInsideStatus = true;

				}

			}

			// Retuner Cursor positions status
			return IsInsideStatus;

		}

		RectangelSizableSides RMH_OpenGL_GetSellectedRectangelSizableSide(GLdouble MouseXPosition, GLdouble MouseYPosition, unsigned short RectTag) {

			// Routinen læser og retunerer hvilken siden af rektangelen Musen er positionerede ved.

			// Lokale variabler
			RectangelSizableSides ReturnedSide = RectangelSizableSides::None;

			// Kontroller om top Rektangel linje er valgt
			if (MouseYPosition >= RectY0[RectTag] - CursorChangeOffset &&
				MouseYPosition <= RectY0[RectTag] + CursorChangeOffset &&
				MouseXPosition >= RectX0[RectTag] &&
				MouseXPosition <= RectX0[RectTag] + RectWidth[RectTag]) {

				// Opdater Retunerede valgt linje enum værdi
				ReturnedSide = RectangelSizableSides::TopLine;

			}

			// Kontroller om nedereste Rektangel linje er valgt
			if (MouseYPosition >= (RectY0[RectTag] + RectHeight[RectTag]) - CursorChangeOffset &&
				MouseYPosition <= (RectY0[RectTag] + RectHeight[RectTag]) + CursorChangeOffset &&
				MouseXPosition + RectHeight[RectTag] >= RectX0[RectTag] + RectHeight[RectTag] &&
				MouseXPosition + RectHeight[RectTag] <= RectX0[RectTag] + RectHeight[RectTag] + RectWidth[RectTag]) {

				// Opdater Retunerede valgt linje enum værdi
				ReturnedSide = RectangelSizableSides::BottomLine;

			}

			// Kontroller om venstre Rektangel linje er valgt
			if (MouseXPosition >= RectX0[RectTag] - CursorChangeOffset &&
				MouseXPosition <= RectX0[RectTag] + CursorChangeOffset &&
				MouseYPosition >= RectY0[RectTag] &&
				MouseYPosition <= RectY0[RectTag] + RectHeight[RectTag]) {

				// Opdater Retunerede valgt linje enum værdi
				ReturnedSide = RectangelSizableSides::LeftLine;

			}

			// Kontroller om højre Rektangel linje er valgt
			if (MouseXPosition >= (RectX0[RectTag] + RectWidth[RectTag]) - CursorChangeOffset &&
				MouseXPosition <= (RectX0[RectTag] + RectWidth[RectTag]) + CursorChangeOffset &&
				MouseYPosition + RectWidth[RectTag] >= RectY0[RectTag] + RectWidth[RectTag] &&
				MouseYPosition + RectWidth[RectTag] <= RectY0[RectTag] + RectHeight[RectTag] + RectWidth[RectTag]) {

				// Opdater Retunerede valgt linje enum værdi
				ReturnedSide = RectangelSizableSides::RightLine;

			}

			// Retuner linje enum værdi
			return ReturnedSide;

		}

		System::Windows::Forms::Cursor^ RMH_OpenGL_GetRectangelCursor(RectangelSizableSides RectangelSide) {

			// Routinen retunerer relavant tilhørende cursor til givet rektangel side 

			// Valg af rektangel side
			switch (RectangelSide) {

				// Retuner relavant cursor
				case RectangelSizableSides::TopLine: return Cursors::SizeNS;
				case RectangelSizableSides::BottomLine: return Cursors::SizeNS;
				case RectangelSizableSides::LeftLine: return Cursors::SizeWE;
				case RectangelSizableSides::RightLine: return Cursors::SizeWE;
				default: return Cursors::Default;

			}

		}

		GLvoid RMH_OpenGL_ChangeRectangelCursor(GLdouble MouseXPosition, GLdouble MouseYPosition, unsigned short RectTag) {

			// Routinen Opdaterer det overlejede panels Cursor, afhængigt af hvilken rektangel siden musen rør

			// Opdater overlejede panels Cursor
			OverlayPanel->Cursor = RMH_OpenGL_GetRectangelCursor(RMH_OpenGL_GetSellectedRectangelSizableSide(MouseXPosition, MouseYPosition, RectTag));

		}

		GLvoid RMH_OpenGL_HandleRectangleMouseDownEvents(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer events og stadier når det klikkes på en positions justerbar rektangel

			// Nulstil Valgte Rektangel Index værdi
			SelectedRectTagIndex = 0;

			// Hvis er Rendereret Crosshair ikke er valgt
			if (CrosshairMoveFlag == false && LineMoveFlag == false) {

				// Loop Igennem alle aktive rektangler
				for (unsigned short i = 0; i < NmbOfActiveRects; i++) {

					// Kontroller om Mus Cursoren er inde i aktiv rektanglens areal 
					// Hæjeste ordens prioritets rektangel vil altid blive valgt først i lag 
					if (RMH_OpenGL_IsCursorInsideRectangle(MouseXPosition, MouseYPosition, RectX0[RectOrderIndex[i]], RectY0[RectOrderIndex[i]], RectWidth[RectOrderIndex[i]], RectHeight[RectOrderIndex[i]])) {

						// Opdater Rektangel panel Move flag
						RectangleMoveFlag = true;

						// Lager Valgte Regtangel Tag Index
						SelectedRectTagIndex = RectOrderIndex[i];

						// Bryd For Loop
						break;

					}

				}
			}

			// Opdater "Old State" Antal Rendereret Rektangler variabel
			OldNmbOfActiveRects = NmbOfActiveRects;

			// Nulstil Valgte rektangel side enum
			SelectedRectSide = RectangelSizableSides::None;
			// Læs hvilken side af rektanglen er blevet valgt
			SelectedRectSide = RMH_OpenGL_GetSellectedRectangelSizableSide(MouseXPosition, MouseYPosition, SelectedRectTagIndex);

			// Læs nuværende rectangel kordinater/positioner ved nyt klick
			ClickRectXPosition = RectX0[SelectedRectTagIndex];
			ClickRectYPosition = RectY0[SelectedRectTagIndex];
			ClickRectWidthPosition = RectWidth[SelectedRectTagIndex];
			ClickRectHeightPosition = RectHeight[SelectedRectTagIndex];
			ClickRectXPositionOffset = MouseXPosition - RectX0[SelectedRectTagIndex];
			ClickRectYPositionOffset = MouseYPosition - RectY0[SelectedRectTagIndex];

		}

		GLvoid RMH_OpenGL_HandleRectangleMouseMoveEvents(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer events og stadier når en Klikkede rektangel skal bevære sig

			// Tilføj Rektangel Klik Offset Til Mus Positionen
			MouseXPosition = MouseXPosition - ClickRectXPositionOffset;
			MouseYPosition = MouseYPosition - ClickRectYPositionOffset;

			// Opdater cursor hvis intet aktivt objekt er i musens fokus
			if (OldNmbOfActiveRects != NmbOfActiveRects) {

				// Opdater Det Overlejede Panels Cursor Type
				RMH_OpenGL_ChangeRectangelCursor(MouseXPosition + ClickRectXPositionOffset, MouseYPosition + ClickRectYPositionOffset, 0);

				// Opdater "Old State" Antal Rendereret Rektangler variabel
				OldNmbOfActiveRects = NmbOfActiveRects;

				// Nulstil Valgte Rektangel Index værdi
				SelectedRectTagIndex = 0;

			}

			// Kontroller Antallet af aktive Raktangler og Valgte Index
			if (NmbOfActiveRects > 0 && SelectedRectTagIndex != 0) {

				// Opdater Det Overlejede Panels Cursor Type
				RMH_OpenGL_ChangeRectangelCursor(MouseXPosition + ClickRectXPositionOffset, MouseYPosition + ClickRectYPositionOffset, SelectedRectTagIndex);

				// Hvis der endnu ikke er blevet klippet på panalet
				if (OverlayPanelIsClick == false) {

					// Fortsæt ikke
					return;

				}

				// Hvilken rektangel side position skal opdateres
				switch (SelectedRectSide) {

					// -------------------------------------------------------------------------------------- //

					// Opdater Top Linje Positionen
					case RectangelSizableSides::TopLine:

						// Opdater Rektangelens Y position
						RectY0[SelectedRectTagIndex] = MouseYPosition;
						// Opdater Rektangelens højde værdi fra ny Y position
						RectHeight[SelectedRectTagIndex] = ClickRectHeightPosition + (ClickRectYPosition - RectY0[SelectedRectTagIndex]);

						// Skal rektangelen indstillede til fast aspect ratio
						if (RectFixedAspectRatioFlags[SelectedRectTagIndex] == true) {

							// Opdater Rektangelens bredde værdi fra ny X position
							RectWidth[SelectedRectTagIndex] = RectHeight[SelectedRectTagIndex] * ImageDataPixelAspectRatio;

							// Begræns størrelsen til den minimale rektangel størrelse
							if (RectWidth[SelectedRectTagIndex] <= MinimumRectWidth) {

								// Sæt Rektangel højden til den minimale højde
								RectWidth[SelectedRectTagIndex] = MinimumRectWidth;

							}

						}
		
						// Begræns størrelsen til den minimale rektangel størrelse
						if (RectY0[SelectedRectTagIndex] >= (RectY0[SelectedRectTagIndex] + RectHeight[SelectedRectTagIndex]) - MinimumRectHeight) {

							// Opdater Rektangelens Y position ved minimal størrelsen
							RectY0[SelectedRectTagIndex] = (RectY0[SelectedRectTagIndex] + RectHeight[SelectedRectTagIndex]) - MinimumRectHeight;
							// Opdater Rektangelens højde værdi fra minimal Y position
							RectHeight[SelectedRectTagIndex] = ClickRectHeightPosition + (ClickRectYPosition - RectY0[SelectedRectTagIndex]);

						}

					break;

					// -------------------------------------------------------------------------------------- //

					// Opdater Bund Linje Positionen
					case RectangelSizableSides::BottomLine:

						// Opdater Rektangelens højde 
						RectHeight[SelectedRectTagIndex] = ClickRectHeightPosition - (ClickRectYPosition - MouseYPosition);

						// Skal rektangelen indstillede til fast aspect ratio
						if (RectFixedAspectRatioFlags[SelectedRectTagIndex] == true) {

							// Opdater Rektangelens højde 
							RectWidth[SelectedRectTagIndex] = RectHeight[SelectedRectTagIndex] * ImageDataPixelAspectRatio;

							// Begræns størrelsen til den minimale rektangel størrelse
							if (RectWidth[SelectedRectTagIndex] <= MinimumRectWidth) {

								// Sæt Rektangel højden til den minimale højde
								RectWidth[SelectedRectTagIndex] = MinimumRectWidth;

							}

						}
						
						// Begræns størrelsen til den minimale rektangel størrelse
						if (RectHeight[SelectedRectTagIndex] <= MinimumRectHeight) {

							// Sæt Rektangel højden til den minimale højde
							RectHeight[SelectedRectTagIndex] = MinimumRectHeight;

						}

					break;

					// -------------------------------------------------------------------------------------- //

					// Opdater venstre Linje Positionen
					case RectangelSizableSides::LeftLine:

						// Opdater Rektangelens X position
						RectX0[SelectedRectTagIndex] = MouseXPosition;
						// Opdater Rektangelens bredde værdi fra ny X position
						RectWidth[SelectedRectTagIndex] = ClickRectWidthPosition + (ClickRectXPosition - RectX0[SelectedRectTagIndex]);

						// Skal rektangelen indstillede til fast aspect ratio
						if (RectFixedAspectRatioFlags[SelectedRectTagIndex] == true) {

							// Opdater Rektangelens bredde 
							RectHeight[SelectedRectTagIndex] = RectWidth[SelectedRectTagIndex] * ImageDataPixelAspectRatioReciprok;

							// Begræns størrelsen til den minimale rektangel størrelse
							if (RectHeight[SelectedRectTagIndex] <= MinimumRectHeight) {

								// Sæt Rektangel højden til den minimale højde
								RectHeight[SelectedRectTagIndex] = MinimumRectHeight;

							}

						}
		
						// Begræns størrelsen til den minimale rektangel størrelse
						if (RectX0[SelectedRectTagIndex] >= (RectX0[SelectedRectTagIndex] + RectWidth[SelectedRectTagIndex]) - MinimumRectWidth) {

							// Opdater Rektangelens X position ved minimal størrelsen
							RectX0[SelectedRectTagIndex] = (RectX0[SelectedRectTagIndex] + RectWidth[SelectedRectTagIndex]) - MinimumRectWidth;
							// Opdater Rektangelens bredde værdi fra minimal X position
							RectWidth[SelectedRectTagIndex] = ClickRectWidthPosition + (ClickRectXPosition - RectX0[SelectedRectTagIndex]);

						}

					break;

					// -------------------------------------------------------------------------------------- //

					// Opdater højre Linje Positionen
					case RectangelSizableSides::RightLine:

						// Opdater Rektangelens bredde 
						RectWidth[SelectedRectTagIndex] = ClickRectWidthPosition - (ClickRectXPosition - MouseXPosition);

						// Skal rektangelen indstillede til fast aspect ratio
						if (RectFixedAspectRatioFlags[SelectedRectTagIndex] == true) {

							// Opdater Rektangelens bredde 
							RectHeight[SelectedRectTagIndex] = RectWidth[SelectedRectTagIndex] * ImageDataPixelAspectRatioReciprok;

							// Begræns størrelsen til den minimale rektangel størrelse
							if (RectHeight[SelectedRectTagIndex] <= MinimumRectHeight) {

								// Sæt Rektangel højden til den minimale højde
								RectHeight[SelectedRectTagIndex] = MinimumRectHeight;

							}

						}
		
						// Begræns størrelsen til den minimale rektangel størrelse
						if (RectWidth[SelectedRectTagIndex] <= MinimumRectWidth) {

							// Sæt Rektangel bredde til den minimale bredde
							RectWidth[SelectedRectTagIndex] = MinimumRectWidth;

						}
				
					break;

					// -------------------------------------------------------------------------------------- //

					// Opdater hele rektangel Positionen
					default:

						// Skal hele rektanglen bevæge sig
						if (RectangleMoveFlag == true) {

							// Opdater rektangel X og Y kordinater
							RectX0[SelectedRectTagIndex] = MouseXPosition;
							RectY0[SelectedRectTagIndex] = MouseYPosition;

						}

					break;

					// -------------------------------------------------------------------------------------- //

				}

				// Begræns Positionen af rektangelen til textur området
				if (RectX0[SelectedRectTagIndex] <= ROIRectangleLiveViewBorderPixelPadding) RectX0[SelectedRectTagIndex] = ROIRectangleLiveViewBorderPixelPadding;
				if (RectY0[SelectedRectTagIndex] <= ROIRectangleLiveViewBorderPixelPadding) RectY0[SelectedRectTagIndex] = ROIRectangleLiveViewBorderPixelPadding;
				if (RectWidth[SelectedRectTagIndex] <= ROIRectangleLiveViewBorderPixelPadding) RectWidth[SelectedRectTagIndex] = ROIRectangleLiveViewBorderPixelPadding;
				if (RectHeight[SelectedRectTagIndex] <= ROIRectangleLiveViewBorderPixelPadding) RectHeight[SelectedRectTagIndex] = ROIRectangleLiveViewBorderPixelPadding;
				if (RectWidth[SelectedRectTagIndex] >= ImageDataPixelWidth - ROIRectangleLiveViewBorderPixelPadding) RectWidth[SelectedRectTagIndex] = ImageDataPixelWidth - ROIRectangleLiveViewBorderPixelPadding;
				if (RectHeight[SelectedRectTagIndex] >= ImageDataPixelHeight - ROIRectangleLiveViewBorderPixelPadding) RectHeight[SelectedRectTagIndex] = ImageDataPixelHeight - ROIRectangleLiveViewBorderPixelPadding;
				if (RectX0[SelectedRectTagIndex] + RectWidth[SelectedRectTagIndex] >= ImageDataPixelWidth) RectX0[SelectedRectTagIndex] = (ImageDataPixelWidth - ROIRectangleLiveViewBorderPixelPadding) - RectWidth[SelectedRectTagIndex];
				if (RectY0[SelectedRectTagIndex] + RectHeight[SelectedRectTagIndex] >= ImageDataPixelHeight) RectY0[SelectedRectTagIndex] = (ImageDataPixelHeight - ROIRectangleLiveViewBorderPixelPadding) - RectHeight[SelectedRectTagIndex];

			}

		}

		RectangelPosition RMH_OpenGL_RenderMovableRectangle(unsigned short OrderPriority, std::string RectangleTitle, GLubyte SelectedColorR, GLubyte SelectedColorG, GLubyte SelectedColorB,GLubyte PassiveColorR, GLubyte PassiveColorG, GLubyte PassiveColorB, bool FixedAspectRatioFlag) {

			// Routinen renderere en positions justerbar rektangel
		
			// Lokale variabler
			RectangelPosition RenderedRectPosition;

			// Kontroller for maximalt tag ordens værdi
			if (OrderPriority < 1 || OrderPriority > _MaxNumberOfMovableRectangles) {

				// Skriv Status Meddelse I Terminal
				cout << "Order Must Be Higher Then 0 And Less Than Max" << endl;

			}
			else {

				// Læs Rektanglens positions parametere til retunering - før renderering
				RenderedRectPosition.RectangleX0Pos = RectX0[OrderPriority];
				RenderedRectPosition.RectangleY0Pos = RectY0[OrderPriority];
				RenderedRectPosition.RectangleWidth = RectWidth[OrderPriority];
				RenderedRectPosition.RectangleHeight = RectHeight[OrderPriority];

				// Lager Regtanglens rendererings Orden
				RectOrderIndex[RenderedRectanglesCounter] = OrderPriority;
				// Lager Regtanglens fast aspect ratio aktiverings flag
				RectFixedAspectRatioFlags[OrderPriority] = FixedAspectRatioFlag;

				// Kontroller valgt indstilling for Aspect Ratio
				if (LocalAspectRatioFlag == true) {

					// Hvis der skal kompenseres for horizontal Aspect ratio
					if (LiveViewPosX0 <= 0.0) {

						// Udregn Rektangel Kordinater ved skallering af textur vinduet
						RenderedRectPosition.RectangleX0Pos = RenderedRectPosition.RectangleX0Pos * CurrentTexturePanelWidth * TotalTextureScalableWidth;
						RenderedRectPosition.RectangleWidth = RenderedRectPosition.RectangleX0Pos + (RenderedRectPosition.RectangleWidth * CurrentTexturePanelWidth * TotalTextureScalableWidth);

						// Udregn Fælles Rektangel Kordinater ved skallering af textur vinduet - fast aspect ratio mode
						RenderedRectPosition.RectangleY0Pos = RenderedRectPosition.RectangleY0Pos * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight;
						RenderedRectPosition.RectangleHeight = RenderedRectPosition.RectangleY0Pos + (RenderedRectPosition.RectangleHeight * CurrentPanelHeightFixedAspect * TotalTextureScalableHeight);
						RenderedRectPosition.RectangleY0Pos = RenderedRectPosition.RectangleY0Pos + AspectRatioHeightOffSet;
						RenderedRectPosition.RectangleHeight = RenderedRectPosition.RectangleHeight + AspectRatioHeightOffSet;

					}
					else {

						// Udregn Fælles Rektangel Kordinater ved skallering af textur vinduet
						RenderedRectPosition.RectangleY0Pos = RenderedRectPosition.RectangleY0Pos * CurrentTexturePanelHeight * TotalTextureScalableHeight;
						RenderedRectPosition.RectangleHeight = RenderedRectPosition.RectangleY0Pos + (RenderedRectPosition.RectangleHeight * CurrentTexturePanelHeight * TotalTextureScalableHeight);

						// Udregn Rektangel Kordinater ved skallering af textur vinduet - fast aspect ratio mode
						RenderedRectPosition.RectangleX0Pos = RenderedRectPosition.RectangleX0Pos * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth;
						RenderedRectPosition.RectangleWidth = RenderedRectPosition.RectangleX0Pos + (RenderedRectPosition.RectangleWidth * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth);
						RenderedRectPosition.RectangleX0Pos = RenderedRectPosition.RectangleX0Pos + AspectRatioWidthOffSet;
						RenderedRectPosition.RectangleWidth = RenderedRectPosition.RectangleWidth + AspectRatioWidthOffSet;

					}

				}
				else {

					// Udregn Fælles Rektangel Kordinater ved skallering af textur vinduet
					RenderedRectPosition.RectangleY0Pos = RenderedRectPosition.RectangleY0Pos * CurrentTexturePanelHeight * TotalTextureScalableHeight;
					RenderedRectPosition.RectangleHeight = RenderedRectPosition.RectangleY0Pos + (RenderedRectPosition.RectangleHeight * CurrentTexturePanelHeight * TotalTextureScalableHeight);

					// Udregn Rektangel Kordinater ved skallering af textur vinduet - Auto aspect ratio mode
					RenderedRectPosition.RectangleX0Pos = RenderedRectPosition.RectangleX0Pos * CurrentTexturePanelWidth * TotalTextureScalableWidth;
					RenderedRectPosition.RectangleWidth = RenderedRectPosition.RectangleX0Pos + (RenderedRectPosition.RectangleWidth * CurrentTexturePanelWidth * TotalTextureScalableWidth);

				}

				// Aktiver OpenGL 1D Texture
				glEnable(GL_TEXTURE_1D);

				// Er Denne Rendereret Regtangel Den sidst valgte Regtangel
				if (OrderPriority == SelectedRectTagIndex) {

					// Opdater Rektanglens Farve Til "Selected" Farve
					glColor3ub(SelectedColorR, SelectedColorG, SelectedColorB);

					// Display Og Opdater Rektangel ID Text Og Text Farve
					RMH_OpenGL_RenderStringOnTexture(RenderedRectPosition.RectangleX0Pos + ROIIdentifierLabelXPixelOffset, RenderedRectPosition.RectangleY0Pos + ROIIdentifierLabelYPixelOffset, RectangleTitle, SelectedColorR, SelectedColorG, SelectedColorB);

				}
				else {

					// Opdater Rektanglens Farve Til "Default" Farve
					glColor3ub(PassiveColorR, PassiveColorG, PassiveColorB);

					// Display Og Opdater Rektangel ID Text Og Text Farve
					RMH_OpenGL_RenderStringOnTexture(RenderedRectPosition.RectangleX0Pos + ROIIdentifierLabelXPixelOffset, RenderedRectPosition.RectangleY0Pos + ROIIdentifierLabelYPixelOffset, RectangleTitle, PassiveColorR, PassiveColorG, PassiveColorB);

				}

				// Sæt Regtangel Linje tykkelsen
				glLineWidth(DefaultRectLineWidth);

				// Render Linje på textur
				glBegin(GL_LINES);

				// Top Regtangel Linjer
				glVertex2f(RenderedRectPosition.RectangleX0Pos, RenderedRectPosition.RectangleY0Pos);
				glVertex2f(RenderedRectPosition.RectangleWidth, RenderedRectPosition.RectangleY0Pos);
				// Højre Regtangel Linjer
				glVertex2f(RenderedRectPosition.RectangleWidth, RenderedRectPosition.RectangleY0Pos);
				glVertex2f(RenderedRectPosition.RectangleWidth, RenderedRectPosition.RectangleHeight);
				// Bund Regtangel Linjer
				glVertex2f(RenderedRectPosition.RectangleWidth, RenderedRectPosition.RectangleHeight);
				glVertex2f(RenderedRectPosition.RectangleX0Pos, RenderedRectPosition.RectangleHeight);
				// Venstre Regtangel Linjer
				glVertex2f(RenderedRectPosition.RectangleX0Pos, RenderedRectPosition.RectangleHeight);
				glVertex2f(RenderedRectPosition.RectangleX0Pos, RenderedRectPosition.RectangleY0Pos);

				// Konfiguration Slut
				glEnd();
				// Deaktiver 1D Texture
				glDisable(GL_TEXTURE_1D);
		
				// Kontroller Live View Roterings Indstillingen
				if (LiveViewRotationDegrees == 0) {

					// Opdater Positions Koordinat værdier
					RenderedRectPosition.RectangleX0Pos = RectX0[OrderPriority];
					RenderedRectPosition.RectangleY0Pos = RectY0[OrderPriority];
					RenderedRectPosition.RectangleWidth = RectWidth[OrderPriority];
					RenderedRectPosition.RectangleHeight = RectHeight[OrderPriority];

				}
				if (LiveViewRotationDegrees == 90) {

					// Opdater Positions Koordinat værdier
					RenderedRectPosition.RectangleX0Pos = ImageDataPixelWidth - ((RectY0[OrderPriority] + RectHeight[OrderPriority]) * ImageDataPixelAspectRatio);
					RenderedRectPosition.RectangleY0Pos = RectX0[OrderPriority] / ImageDataPixelAspectRatio;
					RenderedRectPosition.RectangleWidth = RectHeight[OrderPriority] * ImageDataPixelAspectRatio;
					RenderedRectPosition.RectangleHeight = RectWidth[OrderPriority] / ImageDataPixelAspectRatio;

				}
				if (LiveViewRotationDegrees == 180) {

					// Opdater Positions Koordinat værdier
					RenderedRectPosition.RectangleX0Pos = (ImageDataPixelWidth - RectX0[OrderPriority]) - RectWidth[OrderPriority];
					RenderedRectPosition.RectangleY0Pos = (ImageDataPixelHeight - RectY0[OrderPriority]) - RectHeight[OrderPriority];
					RenderedRectPosition.RectangleWidth = RectWidth[OrderPriority];
					RenderedRectPosition.RectangleHeight = RectHeight[OrderPriority];

				}
				if (LiveViewRotationDegrees == 270) {
					
					// Opdater Positions Koordinat værdier
					RenderedRectPosition.RectangleX0Pos = RectY0[OrderPriority] * ImageDataPixelAspectRatio;
					RenderedRectPosition.RectangleY0Pos = ImageDataPixelHeight - (RectX0[OrderPriority] + RectWidth[OrderPriority]) / ImageDataPixelAspectRatio;
					RenderedRectPosition.RectangleWidth = RectHeight[OrderPriority] * ImageDataPixelAspectRatio;
					RenderedRectPosition.RectangleHeight = RectWidth[OrderPriority] / ImageDataPixelAspectRatio;

				}

				// Rund Positions parameterene Op til nårmeste hele pixel integer værdi
				RenderedRectPosition.RectangleHeight = RMH_Math_Round(RenderedRectPosition.RectangleHeight);
				RenderedRectPosition.RectangleWidth = RMH_Math_Round(RenderedRectPosition.RectangleWidth);
				RenderedRectPosition.RectangleX0Pos = RMH_Math_Round(RenderedRectPosition.RectangleX0Pos);
				RenderedRectPosition.RectangleY0Pos = RMH_Math_Round(RenderedRectPosition.RectangleY0Pos);
				
				// Inkrementer Rektangel rendererings tæller variabel
				RenderedRectanglesCounter = RenderedRectanglesCounter + 1;

			}

			// Retuner Rektanglens position
			return RenderedRectPosition;

		}

		// ----------------------------- Billed Rendererings Og Håndterings Routiner ------------------------------- //

		GLvoid RMH_OpenGL_RotateLiveViewCCW() {

			// Routinen indstiller roterings værdien for Live View billedet fra 0 til 360 grader - Counter Clock Wise.

			// Inkrementer live view billede roteringen med 90 grader
			LiveViewRotationDegrees = LiveViewRotationDegrees + 90.0;

			// Hvis live view billede roteringen er over 270 grader
			if (LiveViewRotationDegrees > 270.0) {

				// Nulstil live view billede roteringen
				LiveViewRotationDegrees = 0.0;

			}

			// Opdater Live View Rotering er blevet ændret flaget
			LiveViewRotationChangedFlag = true;

		}

		GLvoid RMH_OpenGL_RotateLiveViewCW() {

			// Routinen indstiller roterings værdien for Live View billedet fra 0 til 360 grader - Clock Wise.

			// Inkrementer live view billede roteringen med 90 grader
			LiveViewRotationDegrees = LiveViewRotationDegrees - 90.0;

			// Hvis live view billede roteringen er lig 0  grader
			if (LiveViewRotationDegrees < 0.0) {

				// Nulstil live view billede roteringen
				LiveViewRotationDegrees = 270.0;

			}

			// Opdater Live View Rotering er blevet ændret flaget
			LiveViewRotationChangedFlag = true;

		}

		bool RMH_LiveView_HasRotationChanged() {

			// Routinen retunerer et status flag som indikerer som Live View Roteringen har ændret sig

			// Har Live View Roteringen ændret sig
			if (LiveViewRotationChangedFlag == true) {

				// Nulstil Live View Rotering er blevet ændret flaget
				LiveViewRotationChangedFlag = false;

				// Retuner Status
				return true;

			}
			else {

				// Retuner Status
				return false;

			}

		}

		GLdouble RMH_LiveView_GetRotation() {

			// Routinen læser og retunerer den nuværende Live View rotering i grader
			 
			// Retuner den nuværende Live View rotering i grader
			return LiveViewRotationDegrees;

		}

		GLdouble RMH_LiveView_GetNativeImageWidth() {

			// Routinen retunerer Live view billedets native pixel bredde
			return ImageDataPixelWidth;

		}

		GLdouble RMH_LiveView_GetNativeImageHeight() {

			// Routinen retunerer Live view billedets native pixel højde
			return ImageDataPixelHeight;

		}

		GLdouble RMH_LiveView_GetNativeImageAspectRatio() {

			// Routinen retunerer Live view billedets native pixel højde
			return ImageDataPixelAspectRatio;

		}

		GLvoid RMH_LiveView_EnableScrollWheelRotation(bool EnableFlag) {

			// Routinen benyttes til at aktiverer eller deaktiverer live view billede rotering ved brug af Mus Scrol-Hjulet

			// Aktiver eller deaktiver live view billede rotering ved brug af Mus Scrol-Hjulet
			LiveViewMouseScrollWheelRotationEnablFlag = EnableFlag;

		}

		GLvoid RMH_LiveViewStream_UltraResolutionMode(bool EnableExtremeResolutionFlag) {

			// Routinen indstiller og aktiverer/deaktiverer Live View Streamens "Ultra Opløsnings" Mode

			// Aktiver Ultra Opløsnings Featuren
			if (EnableExtremeResolutionFlag == true) {

				// Indstil Ultra opløsnings modets live view frame offset værdi
				UltraResolutionFrameOffsetValue = 1.0;

			}
			else {

				// Indstil Ultra opløsnings modets live view frame offset værdi
				UltraResolutionFrameOffsetValue = 0.5;

			}

		}

		GLvoid RMH_OpenGL_RenderImageTexture(GLdouble TexturePanelWidth, GLdouble TexturePanelHeight, GLdouble FrameWidth, GLdouble FrameHeight, bool FixedAspectRatio) {

			// Routinen Renderer den konfigureret Textur i et givet område af den totale allokerede textur

			// Nulstil Live view stream billede kordinater
			LiveViewPosX0 = 0.0;
			LiveViewPosY0 = 0.0;
			LiveViewPosX1 = 0.0;
			LiveViewPosY1 = 0.0;

			// Nulstil Aspect-Ratio Offset parameter
			AspectRatioWidthOffSet = 0.0;
			// Opdater lokale klasse Aspect ratio status flag
			LocalAspectRatioFlag = FixedAspectRatio;

			// Læs Nuværende textur Panels pixel højde og bredde 
			CurrentTexturePanelHeight = TexturePanelHeight;
			CurrentTexturePanelWidth = TexturePanelWidth;

			// Opdater Billede dataens pixel højde, bredde og Aspect Forholdet
			ImageDataPixelWidth = FrameWidth;
			ImageDataPixelHeight = FrameHeight;
			ImageDataPixelAspectRatio = ImageDataPixelWidth / ImageDataPixelHeight;
			ImageDataPixelAspectRatioReciprok = 1.0 / ImageDataPixelAspectRatio;

			// Udregn billedets Y1 positionen til at udfylde textur vinduet
			LiveViewPosY1 = (FrameHeight * CurrentTexturePanelHeight * TotalTextureScalableHeight);

			// Kontroller valgt indstilling for Aspect Ratio
			if (FixedAspectRatio == true) {

				// Kontroller Live View Roterings Indstillingen
				if (LiveViewRotationDegrees == 90 || LiveViewRotationDegrees == 270) {

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
				LiveViewPosX1 = (FrameWidth * CurrentPanelWidthFixedAspect * TotalTextureScalableWidth) + AspectRatioWidthOffSet;

				// Tilføj X0 aspect ratio margin i venstre side at textur vinduet
				LiveViewPosX0 = AspectRatioWidthOffSet;

				// Kompenser for fast aspect ratio i horizontal retning
				if (LiveViewPosX0 <= 0.0) {

					// Nulstil X0 position
					LiveViewPosX0 = 0.0;
					// Fjern aspect ratio margin i højre side at textur vinduet
					LiveViewPosX1 = LiveViewPosX1 + AspectRatioWidthOffSet;

					// Tilføj Y1 aspect ratio margin i bunden at textur vinduet
					LiveViewPosY1 = LiveViewPosY1 - AspectRatioHeightOffSet;
					// Tilføj Y0 aspect ratio margin i Toppen at textur vinduet
					LiveViewPosY0 = AspectRatioHeightOffSet;

				}

			}
			else {

				// Udregn billedets X1 positionen til at udfylde textur vinduet
				LiveViewPosX1 = (FrameWidth * CurrentTexturePanelWidth * TotalTextureScalableWidth);

			}

			// Ryd Textur farve og bit buffere
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Aktiver OpenGL 2D Texture
			glEnable(GL_TEXTURE_2D);
			// Bind Texturen som et 2D textur
			glBindTexture(GL_TEXTURE_2D, ImageTecture[0]);

			// Roter Textur Til at matche korrekt billede orientation
			glTranslatef(0.0f, FrameHeight, 0.0f);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

			// Begynd Renderering
			glBegin(GL_QUADS);

			// Kontroller Live View Roterings Indstillingen
			if (LiveViewRotationDegrees == 0) {

				// Opdater renderede textur kordinater - 0 Grader Rotering
				glTexCoord2f(0.0, 0.0);
				glVertex2f(LiveViewPosX0, LiveViewPosY0);
				glTexCoord2f(UltraResolutionFrameOffsetValue, 0.0);
				glVertex2f(LiveViewPosX1, LiveViewPosY0);
				glTexCoord2f(UltraResolutionFrameOffsetValue, UltraResolutionFrameOffsetValue);
				glVertex2f(LiveViewPosX1, LiveViewPosY1);
				glTexCoord2f(0.0, UltraResolutionFrameOffsetValue);
				glVertex2f(LiveViewPosX0, LiveViewPosY1);

			}
			else if (LiveViewRotationDegrees == 90) {

				// Opdater renderede textur kordinater - 90 Grader Rotering
				glTexCoord2f(0.0, 0.0);
				glVertex2f(LiveViewPosX0, LiveViewPosY1);
				glTexCoord2f(UltraResolutionFrameOffsetValue, 0.0);
				glVertex2f(LiveViewPosX0, LiveViewPosY0);
				glTexCoord2f(UltraResolutionFrameOffsetValue, UltraResolutionFrameOffsetValue);
				glVertex2f(LiveViewPosX1, LiveViewPosY0);
				glTexCoord2f(0.0, UltraResolutionFrameOffsetValue);
				glVertex2f(LiveViewPosX1, LiveViewPosY1);
		
			}
			else if (LiveViewRotationDegrees == 180) {
				
				// Opdater renderede textur kordinater - 180 Grader Rotering
				glTexCoord2f(0.0, 0.0);
				glVertex2f(LiveViewPosX1, LiveViewPosY1);
				glTexCoord2f(UltraResolutionFrameOffsetValue, 0.0);
				glVertex2f(LiveViewPosX0, LiveViewPosY1);
				glTexCoord2f(UltraResolutionFrameOffsetValue, UltraResolutionFrameOffsetValue);
				glVertex2f(LiveViewPosX0, LiveViewPosY0);
				glTexCoord2f(0.0, UltraResolutionFrameOffsetValue);
				glVertex2f(LiveViewPosX1, LiveViewPosY0);

			}
			else {

				// Opdater renderede textur kordinater - 270 Grader Rotering
				glTexCoord2f(0.0, 0.0);
				glVertex2f(LiveViewPosX1, LiveViewPosY0);
				glTexCoord2f(UltraResolutionFrameOffsetValue, 0.0);
				glVertex2f(LiveViewPosX1, LiveViewPosY1);
				glTexCoord2f(UltraResolutionFrameOffsetValue, UltraResolutionFrameOffsetValue);
				glVertex2f(LiveViewPosX0, LiveViewPosY1);
				glTexCoord2f(0.0, UltraResolutionFrameOffsetValue);
				glVertex2f(LiveViewPosX0, LiveViewPosY0);

			}

			// Konfiguration Slut
			glEnd();
			// Deaktiver 2D Texture
			glDisable(GL_TEXTURE_2D);

		}
		
		GLvoid RMH_OpenGL_RenderGrayscale16BitImageData(unsigned int TexturePanelWidth, unsigned int TexturePanelHeight, unsigned short* FrameData, unsigned int FrameWidth, unsigned int FrameHeight, bool FixedAspectRatio) {

			// Routinen håndterer OpenGL rendereringen af billede dataen til textur handler objektet
			
			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();

			// Skriv Billede data til Textur
			RMH_OpenGL_WriteImageDataToTexture(FrameData, FrameWidth, FrameHeight);
			// Konfigurer Texturens Opløsning og FOV
			RMH_OpenGL_UpdateTextureFieldOfView(FrameWidth, FrameHeight);
			// Render Textur Billede Data
			RMH_OpenGL_RenderImageTexture(TexturePanelWidth, TexturePanelHeight, FrameWidth, FrameHeight, FixedAspectRatio);

		}

		GLvoid RMH_OpenGL_RenderGrayscaleUltraResolutionImageData(unsigned int TexturePanelWidth, unsigned int TexturePanelHeight, unsigned short* FrameData, unsigned int NativeFrameWidth, unsigned int NativeFrameHeight, unsigned int UltraFrameWidth, unsigned int UltraFrameHeight, bool FixedAspectRatio) {

			// Routinen håndterer OpenGL rendereringen af Ultra Opløsnings billede dataen til textur handler objektet

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();

			// Skriv Billede data til Textur
			RMH_OpenGL_WriteImageDataToTexture(FrameData, UltraFrameWidth, UltraFrameHeight);
			// Konfigurer Texturens Opløsning og FOV
			RMH_OpenGL_UpdateTextureFieldOfView(NativeFrameWidth, NativeFrameHeight);
			// Render Textur Billede Data
			RMH_OpenGL_RenderImageTexture(TexturePanelWidth, TexturePanelHeight, NativeFrameWidth, NativeFrameHeight, FixedAspectRatio);

		}

		// ----------------------- Textur Panel Interaktions Cursor Event Callback Routiner ------------------------ //

		GLvoid RMH_OpenGL_UpdateRenderedObjectsZOrder(unsigned short ZOrden) {

			// Routinen indstiller objekt rendererings Z-ordnen for Positions justerbare Rektangler og Crosshairs

			/*
			 *  Tilhørende Macroer ->
			 * 
			 *  // Rendereret Objekters Z-Ordens Indstillings Macroer
			 *  #define _ZOrden_CrosshairsInFront	      0
			 *  #define _ZOrden_RectanglesInFront	      1
			 *  #define _ZOrden_LinesInFront			  2
			 * 
			 */

			// Opdater rendererings Z-ordnen
			MovableObjectsRenderZOrder = ZOrden;

		}

		GLvoid TexturePanel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Læs Mus Cursor Positionen
			GLdouble MouseXPosition = RMH_OpenGL_TranslateOverlayPanelMouseXPosToTextureXPos(e);
			GLdouble MouseYPosition = RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(e);

			// Opdater overlay panel click flag
			OverlayPanelIsClick = true;

			// Valg Af Rendererings Orden (Z-Orden)
			switch (MovableObjectsRenderZOrder) {

				// Crosshairs er i fronten
				case _ZOrden_CrosshairsInFront:

					// Håndterer Events når der klikkes på et positions justerbar Crosshair
					RMH_OpenGL_HandleCrosshairMouseDownEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når der klikkes på et positions justerbar rektangel
					RMH_OpenGL_HandleRectangleMouseDownEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når der klikkes på et positions justerbar linje
					RMH_OpenGL_HandleLineMouseDownEvents(MouseXPosition, MouseYPosition);

				break;

				// Rektangler er i fronten
				case _ZOrden_RectanglesInFront:

					// Håndterer Events når der klikkes på et positions justerbar rektangel
					RMH_OpenGL_HandleRectangleMouseDownEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når der klikkes på et positions justerbar Crosshair
					RMH_OpenGL_HandleCrosshairMouseDownEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når der klikkes på et positions justerbar linje
					RMH_OpenGL_HandleLineMouseDownEvents(MouseXPosition, MouseYPosition);

				break;

				// Linjer er i fronten
				case _ZOrden_LinesInFront:

					// Håndterer Events når der klikkes på et positions justerbar linje
					RMH_OpenGL_HandleLineMouseDownEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når der klikkes på et positions justerbar rektangel
					RMH_OpenGL_HandleRectangleMouseDownEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når der klikkes på et positions justerbar Crosshair
					RMH_OpenGL_HandleCrosshairMouseDownEvents(MouseXPosition, MouseYPosition);

				break;

			}

		}

		GLvoid TexturePanel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Opdater overlay panel click flag
			OverlayPanelIsClick = false;

			// Nulstil Rektangel Move flag
			RectangleMoveFlag = false;

			// Nulstil Crosshair Move flag
			CrosshairMoveFlag = false;

			// Nulstil Linjernes Move flag
			LineMoveFlag = false;

		}

		GLvoid TexturePanel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Læs Mus Cursor Positionen
			GLdouble MouseXPosition = RMH_OpenGL_TranslateOverlayPanelMouseXPosToTextureXPos(e);
			GLdouble MouseYPosition = RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(e);

			// Nulstil Overlay Panel Cursor
			OverlayPanel->Cursor = Cursors::Default;

			// Opdater cursor label positionen, hvis feature er aktiverede
			RMH_OpenGL_UpdateCursorTrackingPosition(MouseXPosition, MouseYPosition);

			// Valg Af Rendererings Orden (Z-Orden)
			switch (MovableObjectsRenderZOrder) {

				// Crosshairs er i fronten
				case _ZOrden_CrosshairsInFront:

					// Håndterer Events når et positions justerbar Crosshair skal bevæges
					RMH_OpenGL_HandleCrosshairMouseMoveEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når en positions justerbar rektangel skal bevæges
					RMH_OpenGL_HandleRectangleMouseMoveEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når en positions justerbar linje skal bevæges
					RMH_OpenGL_HandleLineMouseMoveEvents(MouseXPosition, MouseYPosition);

				break;

				// Rektangler er i fronten
				case _ZOrden_RectanglesInFront:

					// Håndterer Events når en positions justerbar rektangel skal bevæges
					RMH_OpenGL_HandleRectangleMouseMoveEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når et positions justerbar Crosshair skal bevæges
					RMH_OpenGL_HandleCrosshairMouseMoveEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når en positions justerbar linje skal bevæges
					RMH_OpenGL_HandleLineMouseMoveEvents(MouseXPosition, MouseYPosition);

				break;

				// Linjer er i fronten
				case _ZOrden_LinesInFront:

					// Håndterer Events når en positions justerbar linje skal bevæges
					RMH_OpenGL_HandleLineMouseMoveEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når en positions justerbar rektangel skal bevæges
					RMH_OpenGL_HandleRectangleMouseMoveEvents(MouseXPosition, MouseYPosition);

					// Håndterer Events når et positions justerbar Crosshair skal bevæges
					RMH_OpenGL_HandleCrosshairMouseMoveEvents(MouseXPosition, MouseYPosition);

				break;

			}

		}

		GLvoid TexturePanel_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Kontroller om Mus Scroll-Hjul Live View rotering er aktiverede
			if (LiveViewMouseScrollWheelRotationEnablFlag == true) {

				// Kontroller Mus hjulets drejnings polaritet
				if (e->Delta < 0.0) {

					// Roter Live View Billeder 90 Grader Med Uret
					RMH_OpenGL_RotateLiveViewCW();

				}
				else {

					// Roter Live View Billeder 90 Grader Mod Uret
					RMH_OpenGL_RotateLiveViewCCW();

				}

			}

		}

		// -------------------------------- OpenGL Renderering Slut Punkts Routiner -------------------------------- //
		
		GLvoid RMH_OpenGL_SwapOpenGLBuffers(GLvoid) {

			// Routinen bytter rundt på Front/Backend bufferene

			// Byt Rundt på buffere
			SwapBuffers(m_hDC);

		}

		GLvoid RMH_OpenGL_RenderingFinishedMark(GLvoid) {

			// Routinen markerer enden på en OpenGL rendererins sekvens
			// Og skal altid kaldes til sidst, når alle objekt rendereringer er blevet eksikverede

			// Læs det totale antal rendererede Rektangler
			NmbOfActiveRects = RenderedRectanglesCounter;
			// Nulstil Rektangel rendererings tæller variabel
			RenderedRectanglesCounter = 0;

			// Læs det totale antal rendererede Crosshairs
			NmbOfActiveCrosshairs = RenderedCrosshairCounter;
			// Nulstil Crosshair rendererings tæller variabel
			RenderedCrosshairCounter = 0;

			// Læs det totale antal rendererede Linjer
			NmbOfActiveLines = RenderedLineCounter;
			// Nulstil Linje rendererings tæller variabel
			RenderedLineCounter = 0;

			// Swap Textur buffere
			RMH_OpenGL_SwapOpenGLBuffers();

			// Nulstil Render kontekst
			//RMH_OpenGL_MakeRenderContextNULL();

		}
		
		// --------------------------------------------------------------------------------------------------------- //

	private:

		// ------------------------- Yderligerer OpenGL Håndterings Og Opsætnings Routiner ------------------------- //

		~RMHOpenGLWF(GLvoid) {

			// Slet OpenGL Context
			DeleteOpenGL();

			// Destruer OpenGL Handler objekt
			this->DestroyHandle();

			// Garbage Collect managed data
			System::GC::Collect();

		}

		GLvoid DeleteOpenGL(GLvoid)	{

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

		bool RMH_OpenGL_SetTexturePixelFormat(HDC hdc) {

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

		GLvoid RMH_OpenGL_ResizeOpenGLWinformsScene(unsigned int TotalTextureWidth, unsigned int TotalTextureHeight) {

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

		GLvoid RMH_OpenGL_BuildFont(GLvoid) {

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

		bool RMH_OpenGL_Init(GLvoid) {

			// Routinen Initialisere OpenGL I Winforms C++/CLR

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

		// --------------------------------------------------------------------------------------------------------- //

	};

}