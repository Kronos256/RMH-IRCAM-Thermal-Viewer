#pragma once

/*
 *  RMH_OpenGL_ColorBar.h
 *
 *  Author: Rune Mark Hansen
 *  Date: January 2023
 *
 */

// Inkluderede Biblioteker
#include <windows.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include <iostream>

 // Tilhørende Name spaces
using namespace System::Windows::Forms;
using namespace std;

// Klasse konfigurations macroer
#define _ColorBarMaxNumberOfTicks       20 // Major Ticks + Minor Ticks
#define _NumberOfMovableTags            2

// Statiske Globale arrays og variabler
static GLfloat MinorTickLabelXPos[_ColorBarMaxNumberOfTicks];
static GLfloat MinorTickLabelYPos[_ColorBarMaxNumberOfTicks];
static unsigned short FirstColorPaletteData[16384 * 4];
static unsigned short SecondColorPaletteData[16384 * 4];
static GLdouble MovableTagY0[_NumberOfMovableTags + 1];
static std::string MaximumTagStdString = "MAX";
static std::string MinimumTagStdString = "MIN";

// OpenGL Klasse definition
namespace OpenGLColorBar {

	// ------------------------- Globale Klasse Struktur Objekter -------------------------- //

	// ColorBar Tag Positions Data Klasse struktur
	class ColorBarTagPosition {
	public:

		// Tag Positions parametere
		unsigned short MaximumTagPos = 0;
		unsigned short MinimumTagPos = 16384;

	};

	// ColorBar Manual Range Max/Min temperatur Klasse struktur
	class ColorBarManualRangeTemps {
	public:

		// Tag Positions parametere
		GLfloat ManualMaxRangeTemp = 0.0f;
		GLfloat ManualMinRangeTemp = 0.0f;

	};

	// ----------------- Privat Custom Winforms Gennemsigtigt Panel Klasse ----------------- //

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

	// --------------------------- Primære OpenGL ColorBar Klasse -------------------------- //

	public ref class RMHOpenGLColorBar : public System::Windows::Forms::NativeWindow {

	private:

		// ------------------------ Lokale Form Reference Struktur ------------------------- //

		// Lokale Reference struktur
		ref struct PrivateLocals {

			// ColorBar Major Og Minor tick Label array
			static cli::array<System::String^>^ ColorBarTickLabels = gcnew cli::array<System::String^>(_ColorBarMaxNumberOfTicks);

		};

		// --------------------------------------------------------------------------------- //

	private:

		// ColorBar Konfigurations Parametere
		private: GLfloat ColorBarPixelWidth = 1;
		private: GLfloat ColorBarPixelHeight = 256;
		private: unsigned int ColorBarPaletteResolution = 16384;
		private: unsigned int ColorBarPaletteIntegerRange = 65535;

		// Private Globale klasse objekter og variabler
		private: HDC m_hDC;
		private: HGLRC m_hglrc;
		private: GLuint BaseFont;
		private: GLint iPixelFormat;
		private: GLuint* ColorBarTexture;
		private: GLfloat ColorBarTexture_t;
		private: GLfloat ColorBarTexture_u;
		private: unsigned int TextureWidth;
		private: unsigned int TextureHeight;
		private: GLdouble InitialTextureWidth;
		private: GLdouble InitialTextureHeight;
		private: GLdouble TextureResScaleFactor;
		private: bool OverlayPanelIsClick = false;
		private: GLdouble CurrentTexturePanelWidth;
		private: GLdouble CurrentTexturePanelHeight;
		private: GLdouble TotalTextureScalableWidth;
		private: GLdouble TotalTextureScalableHeight;
		private: GLdouble TextureToPanelScaleWidthFactor;
		private: GLdouble TextureToPanelScaleHeightFactor;
		private: CreateParams^ ControlParams = gcnew CreateParams;
		private: TextureOverlayPanel^ OverlayPanel = gcnew TextureOverlayPanel();

		// ColorBar Panel, Textur, Tick Linje Og Positions konfigurations variabler
		private: GLfloat ColorBarPanelTextureWidth = 24;
		private: GLfloat ColorBarPanelTexturePadding = 8;
		private: GLfloat ColorBarX0TexturePos = 9;
		private: GLfloat ColorBarTextureWidth = 4;
		private: GLfloat TickLineColorBarOffset = 1;
		private: GLfloat ColorBarMajorTickLength = 0.5;
		private: GLfloat ColorBarMinorTickLength = 0.3;
		private: GLfloat TickLabelXOffset = 0.5;
		private: GLfloat TickLabelYOffset = 0.8;

		// Positions justerbar Tag konfigurations variabler
		private: unsigned char MaxTagID = 1;
		private: unsigned char MinTagID = 2;
		private: GLfloat MaxMinTagX0Pos = 9;
		private: GLfloat MaxMinTagX0Offset = 1;
		private: GLfloat MaxMinTagArrowLength = 2;
		private: GLfloat MaxMinTagHeight = 8;
		private: GLfloat MaxMinTagLength = 6;
		private: GLfloat TagLabelXOffset = 4;
		private: GLfloat TagLabelYOffset = 0.7;

		// Diverse ColorBar Variabler
		private: GLfloat ColorBarAreaX0;
		private: GLfloat ColorBarAreaY0;
		private: GLfloat ColorBarAreaWidth;
		private: GLfloat ColorBarAreaHeight;
		private: unsigned char NmbOfColorBarTicks = 0;
		private: GLfloat MinorTickPixelRes = 0.0f;
		private: GLfloat ColorBarMaxTickXPos = 0.0f;
		private: GLfloat ColorBarMaxTickYPos = 0.0f;
		private: GLfloat ColorBarMinTickXPos = 0.0f;
		private: GLfloat ColorBarMinTickYPos = 0.0f;
		private: GLfloat MajorTickLinePixelSize = 0.0f;
		private: unsigned short SelectedTagIndex = 0;
		private: bool TagMoveFlag = false;
		private: GLdouble ClickTagYPositionOffset;
		private: bool ColorBarTagMoveEnableFlag = true;
		private: System::String^ MaximumTagSystemString;
		private: System::String^ MinimumTagSystemString;
		private: bool BarManualRangeFlag = false;
		private: bool BarManualHighRangeFlag = false;
		private: bool BarManualLowRangeFlag = false;
		private: GLfloat ColorBarMaxArrowYPos = 0.0f;
		private: GLfloat ColorBarMinArrowYPos = 0.0f;
		private: GLfloat ColorBarCntArrowYPos = 0.0f;
		private: GLfloat ColorBarMaxTempRange = 0.0f;
		private: GLfloat ColorBarMinTempRange = 0.0f;
		private: GLfloat MouseWheelScrollPolarity = 0.0f;
		private: GLfloat MouseWheelStepSize = 1;
		private: GLfloat ColorBarMaxRangeOffsetValue = 0.0f;
		private: GLfloat ColorBarMinRangeOffsetValue = 0.0f;
		private: bool ShowTopOutsideIndicatorFlag = false;
		private: bool ShowButOutsideIndicatorFlag = false;
		private: bool InvertFirstPaletteFlag = false;
		private: bool InvertSecondPaletteFlag = false;

		// Globale ColorBar Farve Variabler (Sæt til Default farve værdier)
		private: GLubyte TickLineColorR = 255;
		private: GLubyte TickLineColorG = 255;
		private: GLubyte TickLineColorB = 255;
		private: GLubyte MaxTagColorR = 90;
		private: GLubyte MaxTagColorG = 90;
		private: GLubyte MaxTagColorB = 90;
		private: GLubyte MinTagColorR = 90;
		private: GLubyte MinTagColorG = 90;
		private: GLubyte MinTagColorB = 90;
		private: GLubyte MaxTrackArrowColorR = 255;
		private: GLubyte MaxTrackArrowColorG = 255;
		private: GLubyte MaxTrackArrowColorB = 255;
		private: GLubyte MinTrackArrowColorR = 255;
		private: GLubyte MinTrackArrowColorG = 255;
		private: GLubyte MinTrackArrowColorB = 255;
		private: GLubyte CntTrackArrowColorR = 255;
		private: GLubyte CntTrackArrowColorG = 255;
		private: GLubyte CntTrackArrowColorB = 255;
		private: GLubyte MaxTrackArrowLabelColorR = 255;
		private: GLubyte MaxTrackArrowLabelColorG = 255;
		private: GLubyte MaxTrackArrowLabelColorB = 255;
		private: GLubyte MinTrackArrowLabelColorR = 255;
		private: GLubyte MinTrackArrowLabelColorG = 255;
		private: GLubyte MinTrackArrowLabelColorB = 255;
		private: GLubyte CntTrackArrowLabelColorR = 255;
		private: GLubyte CntTrackArrowLabelColorG = 255;
		private: GLubyte CntTrackArrowLabelColorB = 255;
		private: GLubyte ColorBarMaxLabelColorR = 255;
		private: GLubyte ColorBarMaxLabelColorG = 255;
		private: GLubyte ColorBarMaxLabelColorB = 255;
		private: GLubyte ColorBarMinLabelColorR = 255;
		private: GLubyte ColorBarMinLabelColorG = 255;
		private: GLubyte ColorBarMinLabelColorB = 255;

	public:

		// ------------------------- ColorBar Konstruktur Routiner ------------------------- //

		RMHOpenGLColorBar(System::Windows::Forms::Panel^ TexturePanel, unsigned char ResolutionScaleFactor) {

			// Routinen opsætter et OpenGL Supporterede grafisk område til renderering
			// Et Winforms Panel er givet som det fysiske textur areal.

			// Initialiser Colorbar Tick Labels array med start strings
			RMH_OpenGL_InitCliArray(PrivateLocals::ColorBarTickLabels, "N/A");

			// Indstil start værdier for Max/Min Tag Y-Positioner
			MovableTagY0[MaxTagID] = ColorBarPanelTexturePadding;
			MovableTagY0[MinTagID] = ColorBarPixelHeight + ColorBarPanelTexturePadding;

			// Indstil start værdier for Colorbarent Max/Min/Center Pilenes Y-Positioner
			ColorBarMaxArrowYPos = ColorBarPanelTexturePadding;
			ColorBarMinArrowYPos = ColorBarPixelHeight + ColorBarPanelTexturePadding;
			ColorBarCntArrowYPos = ((ColorBarPixelHeight + ColorBarPanelTexturePadding) - ColorBarPanelTexturePadding) / 2.0f;

			// Sæt Textur initielle parametere
			InitialTextureWidth = (GLdouble)TexturePanel->Width;
			InitialTextureHeight = (GLdouble)TexturePanel->Height;
			TextureResScaleFactor = (GLdouble)ResolutionScaleFactor;

			// Udregn den totale skallerbar textur hæjde og bredde
			TotalTextureScalableWidth = InitialTextureWidth * TextureResScaleFactor;
			TotalTextureScalableHeight = InitialTextureHeight * TextureResScaleFactor;

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
				// Initialisere OpenGL for Winforms C++
				RMH_OpenGL_Init();

			}

			// Tilføj et overlejede gennemsigtigt panel til textur panalet
			RMH_OpenGL_AddOverlayPanelToMainTexturePanel(TexturePanel);

			// Opsæt ColorBar textur området til grafisk renderering
			RMH_OpenGL_InitColorBarTexture(ColorBarPanelTextureWidth, ColorBarPanelTexturePadding + ColorBarPixelHeight + ColorBarPanelTexturePadding);

		}

		private: GLvoid RMH_OpenGL_InitCliArray(cli::array<System::String^>^ InputArray, System::String^ InitString) {

			// Routinen initialiserer givet array med start værdier

			// Loop til og med arrayets maksimale længde
			for (unsigned int i = 0; i < _ColorBarMaxNumberOfTicks; i++) {

				// Skriv string til array index
				InputArray[i] = InitString;

			}

		}

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
			OverlayPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLColorBar::TexturePanel_MouseDown);
			OverlayPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLColorBar::TexturePanel_MouseUp);
			OverlayPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLColorBar::TexturePanel_MouseMove);
			OverlayPanel->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &RMHOpenGLColorBar::TexturePanel_MouseWheel);

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
			MouseTextureXPos = (OverlayPanelMouseEvent->X + PanelsWidthDifference) * (TextureWidth / CurrentTexturePanelWidth);

			// Håndtering ved minimum textur Mus Position 
			if (MouseTextureXPos <= 0) {
				// Sæt Mus position til minimum værdi
				MouseTextureXPos = 0;
			}

			// Håndtering ved maksimal textur Mus Position 
			if (MouseTextureXPos >= TextureWidth) {
				// Sæt Mus position til maksimal værdi
				MouseTextureXPos = TextureWidth;
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
			MouseTextureYPos = (OverlayPanelMouseEvent->Y + PanelsHeightDifference) * (TextureHeight / CurrentTexturePanelHeight);

			// Håndtering ved minimum textur Mus Position 
			if (MouseTextureYPos <= 0) {
				// Sæt Mus position til minimum værdi
				MouseTextureYPos = 0;
			}

			// Håndtering ved maksimal textur Mus Position 
			if (MouseTextureYPos >= TextureHeight) {
				// Sæt Mus position til maksimal værdi
				MouseTextureYPos = TextureHeight;
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

		private: GLvoid RMH_OpenGL_InitColorBarTexture(unsigned int ColorBarTextureWidth, unsigned int ColorBarTextureHeight) {

			// Routinen benyttes til at opsætte en OpenGL textur til grafisk renderering

			// Sæt Textur Parameter - Width og Height skal være et multiplum af 2
			ColorBarTexture = new GLuint[1];
			TextureWidth = ColorBarTextureWidth;
			TextureHeight = ColorBarTextureHeight;
			ColorBarTexture_t = (GLfloat)ColorBarPixelWidth / (GLfloat)TextureWidth;
			ColorBarTexture_u = (GLfloat)ColorBarPaletteResolution / ((ColorBarPanelTexturePadding + (GLfloat)ColorBarPaletteResolution) + ColorBarPanelTexturePadding);

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			wglMakeCurrent(m_hDC, m_hglrc);

			// Brug Texturen som skal rendererer Colorbarens data
			glGenTextures(1, ColorBarTexture);

			// Aktiver OpenGL 2D Texture
			glEnable(GL_TEXTURE_2D);

			// Aktiver Textur Blending
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Bind Texturen som et 2D textur
			glBindTexture(GL_TEXTURE_2D, ColorBarTexture[0]);

			// Konfigurer Textur parametere
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, ColorBarPixelWidth, ColorBarPaletteResolution, 0, GL_RGBA, GL_UNSIGNED_SHORT, NULL);
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

		private: GLvoid RMH_OpenGL_RenderStringOnTextureCompensated(GLfloat StringX, GLfloat StringY, std::string DisplayString, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen rendererer et givet string på et OpenGL Textur

			// Udregn String Position ved skallering af textur vinduet
			StringX = StringX * TextureToPanelScaleWidthFactor;
			StringY = StringY * TextureToPanelScaleHeightFactor;

			// Konfigurer Textens Farve
			glColor3ub(ColorR, ColorG, ColorB);
			// Indstil textens position på textur
			glRasterPos2f(StringX, StringY);

			// Render givet string på textur
			RMH_OpenGL_glPrint(DisplayString.c_str());

		}

		// --------------------- ColorBar Textur Rendererings Routiner --------------------- //

		private: GLvoid RMH_OpenGL_ClearTextureBuffer() {

			// Routinen rydder tilhørende textur buffere

			// Ryd Textur farve og bit buffere
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}

		private: GLvoid RMH_OpenGL_StartColorBarRender() {

			// Routinen er start tilstande af OpenGL colorbar Rendereringen

			// Roter Textur Til at matche korrekt billede orientation
			glTranslatef(0.0f, (GLdouble)TextureHeight, 0.0f);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

		}
		
		private: GLvoid RMH_OpenGL_RenderColorBarPalette(GLfloat ColorBarX0, GLfloat ColorBarY0, GLfloat ColorBarWidth, GLfloat ColorBarHeight, unsigned short* PaletteData, bool InvertColorPalette) {

			// Routinen Render en givet colorbar palette

			// Lager X/Y/W/H i globale variabler
			ColorBarAreaX0 = (GLfloat)ColorBarX0 * TextureToPanelScaleWidthFactor;
			ColorBarAreaY0 = (GLfloat)ColorBarY0 * TextureToPanelScaleHeightFactor;
			ColorBarAreaWidth = (GLfloat)ColorBarWidth * TextureToPanelScaleWidthFactor;
			ColorBarAreaHeight = (GLfloat)ColorBarHeight * TextureToPanelScaleHeightFactor;

			// Opdater Textur data med billede data
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBindTexture(GL_TEXTURE_2D, ColorBarTexture[0]);

			// Skriv Color Palette data til textur
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ColorBarPixelWidth, ColorBarPaletteResolution, GL_RGBA, GL_UNSIGNED_SHORT, PaletteData);
			
			// Begynd Renderering
			glBegin(GL_QUADS);

			// Skal visningen af color paletten inverteres
			if (InvertColorPalette == true) {

				// Opdater render textur kordinater - inverterede
				glTexCoord2f(ColorBarTexture_t, ColorBarTexture_u);
				glVertex2f(ColorBarAreaX0 + ColorBarAreaWidth, ColorBarAreaY0 + ColorBarAreaHeight);
				glTexCoord2f(0.0, ColorBarTexture_u);
				glVertex2f(ColorBarAreaX0, ColorBarAreaY0 + ColorBarAreaHeight);
				glTexCoord2f(0.0, 0.0);
				glVertex2f(ColorBarAreaX0, ColorBarAreaY0);
				glTexCoord2f(ColorBarTexture_t, 0.0);
				glVertex2f(ColorBarAreaX0 + ColorBarAreaWidth, ColorBarAreaY0);

			}
			else {

				// Opdater render textur kordinater - ikke inverterede
				glTexCoord2f(0.0, 0.0);
				glVertex2f(ColorBarAreaX0 + ColorBarAreaWidth, ColorBarAreaY0 + ColorBarAreaHeight);
				glTexCoord2f(ColorBarTexture_t, 0.0);
				glVertex2f(ColorBarAreaX0, ColorBarAreaY0 + ColorBarAreaHeight);
				glTexCoord2f(ColorBarTexture_t, ColorBarTexture_u);
				glVertex2f(ColorBarAreaX0, ColorBarAreaY0);
				glTexCoord2f(0.0, ColorBarTexture_u);
				glVertex2f(ColorBarAreaX0 + ColorBarAreaWidth, ColorBarAreaY0);

			}

			// Konfiguration Slut
			glEnd();

			// Deaktiver 2D Texture
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);	

		}

		private: GLvoid RMH_OpenGL_RenderColorBarTickLinesAndLabels(GLfloat TickLineX0, GLfloat TickLineY0, GLfloat TickLineHeight, unsigned int NmbOfMinorTicks, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen renderer en tick linje på højre side af colorbaren, samt tilhørende givet antal minor ticks

			// Lokale variabler
			unsigned int i = 0;

			// Hvis givet antal minor ticks er højere end tiladte antal colorbar ticks - 2
			if (NmbOfMinorTicks > _ColorBarMaxNumberOfTicks - 2) {

				// Brgræns til Maximale tiladte antal minor colorbar ticks
				NmbOfMinorTicks = _ColorBarMaxNumberOfTicks - 2;

			}

			// Formater ColorBar Tick Linje Max/Min Tick Linje Positioner - skaller med textur vinduet
			ColorBarMaxTickXPos = TickLineX0 * TextureToPanelScaleWidthFactor;
			ColorBarMaxTickYPos = TickLineY0 * TextureToPanelScaleHeightFactor;
			ColorBarMinTickXPos = TickLineX0 * TextureToPanelScaleWidthFactor;
			ColorBarMinTickYPos = (TickLineY0 + TickLineHeight) * TextureToPanelScaleHeightFactor;

			// Lager Antal ColorBar Ticks globalt i klasse
			NmbOfColorBarTicks = NmbOfMinorTicks + 2;

			// Inkrementer givet input Antal ticks 
			NmbOfMinorTicks = NmbOfMinorTicks + 1;
			// Udregn Major Tick Linjens Længde
			MajorTickLinePixelSize = ColorBarMinTickYPos - ColorBarMaxTickYPos;
			// Udregn Minor Tick Linjernes Y positions opløsning
			MinorTickPixelRes = MajorTickLinePixelSize / NmbOfMinorTicks;

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil linjens Farve
			glColor3ub(ColorR, ColorG, ColorB);
			// Indstil Linjens tykkelse
			glLineWidth(1);

			// Render Linje på textur
			glBegin(GL_LINES);

			// Render Primære ColorBar Tick Linje
			glVertex2f(ColorBarMaxTickXPos, ColorBarMaxTickYPos);
			glVertex2f(ColorBarMaxTickXPos, ColorBarMinTickYPos);

			// Render Top Max ColorBar Tick Linje
			glVertex2f(ColorBarMaxTickXPos, ColorBarMaxTickYPos);
			glVertex2f(ColorBarMaxTickXPos + ColorBarMajorTickLength, ColorBarMaxTickYPos);

			// Lager Major Maximum Label positioner i arrays
			MinorTickLabelXPos[0] = ColorBarMaxTickXPos + ColorBarMajorTickLength + TickLabelXOffset;
			MinorTickLabelYPos[0] = ColorBarMaxTickYPos + TickLabelYOffset;

			// Render Minor colorbar Tick linjer
			for (i = 0; i < NmbOfMinorTicks - 1; i++) {

				// Udregn Y position for minor tick linje
				ColorBarMaxTickYPos = ColorBarMaxTickYPos + MinorTickPixelRes;

				// Render minor ColorBar Tick Linje
				glVertex2f(ColorBarMaxTickXPos, ColorBarMaxTickYPos);
				glVertex2f(ColorBarMaxTickXPos + ColorBarMinorTickLength, ColorBarMaxTickYPos);

				// Lager Minor Ticks positioner i arrays
				MinorTickLabelXPos[i + 1] = ColorBarMaxTickXPos + ColorBarMinorTickLength + TickLabelXOffset;
				MinorTickLabelYPos[i + 1] = ColorBarMaxTickYPos + TickLabelYOffset;

			}

			// Lager Major Minimum Label Positioner i arrays
			MinorTickLabelXPos[i + 1] = ColorBarMinTickXPos + ColorBarMajorTickLength + TickLabelXOffset;
			MinorTickLabelYPos[i + 1] = ColorBarMinTickYPos + TickLabelYOffset;

			// Render Bund Min ColorBar Tick Linje
			glVertex2f(ColorBarMinTickXPos, ColorBarMinTickYPos);
			glVertex2f(ColorBarMinTickXPos + ColorBarMajorTickLength, ColorBarMinTickYPos);

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

			// Render Colorbarens temperatur labels
			RMH_OpenGL_RenderColorBarLabels(NmbOfMinorTicks, ColorR, ColorG, ColorB);

		}

		private: GLvoid RMH_OpenGL_RenderColorBarLabels(unsigned int NmbOfMinorTicks, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen renderer Colorbarens temperatur labels

			// Lokale variabler
			unsigned int i = 0;

			// Render Colorbarens Maximums temperatur label
			RMH_OpenGL_RenderStringOnTexture(MinorTickLabelXPos[0], MinorTickLabelYPos[0] + 1, 
				RMH_Conversion_SystemStringToStdString(PrivateLocals::ColorBarTickLabels[0]), ColorR, ColorG, ColorB);

			// Loop igennem antallet af Minor colorbar ticks
			for (i = 0; i < NmbOfMinorTicks - 1; i++) {

				// Render Colorbarens minor tick labels
				RMH_OpenGL_RenderStringOnTexture(MinorTickLabelXPos[i + 1], MinorTickLabelYPos[i + 1], 
					RMH_Conversion_SystemStringToStdString(PrivateLocals::ColorBarTickLabels[i + 1]), ColorR, ColorG, ColorB);

			}

			// Render Colorbarens Minimums temperatur label
			RMH_OpenGL_RenderStringOnTexture(MinorTickLabelXPos[i + 1], MinorTickLabelYPos[i + 1] - 1, 
				RMH_Conversion_SystemStringToStdString(PrivateLocals::ColorBarTickLabels[i + 1]), ColorR, ColorG, ColorB);

		}

		private: GLvoid RMH_OpenGL_RenderColorBarLimitTag(GLfloat TagX0, GLfloat TagY0, GLfloat TagLength, GLfloat TagHeight, GLfloat ArrowLength, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen Rendererer et Color Bar Tag på givet position

			// Lokale variabler
			GLfloat TagPos1 = 0.0f;
			GLfloat TagPos2 = 0.0f;
			GLfloat TagPos3 = 0.0f;
			GLfloat TagPos4 = 0.0f;

			// Udregn Tag størrelse ved skallering af textur vinduet
			TagX0 = TagX0 * TextureToPanelScaleWidthFactor;
			TagY0 = TagY0 * TextureToPanelScaleHeightFactor;
			ArrowLength = ArrowLength * TextureToPanelScaleWidthFactor;
			TagLength = TagLength * TextureToPanelScaleWidthFactor;
			TagHeight = TagHeight * TextureToPanelScaleHeightFactor;

			// Udregn Tag polygon linjers positioner
			TagPos1 = (TagX0 - ArrowLength);
			TagPos2 = (TagX0 - ArrowLength - TagLength);
			TagPos3 = (TagY0 - (TagHeight * 0.5));
			TagPos4 = (TagY0 + (TagHeight * 0.5));

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil polygon Farve
			glColor3ub(ColorR, ColorG, ColorB);
			// Indstil polygon Linjens tykkelse
			glLineWidth(1);

			// Render Polygon på textur
			glBegin(GL_POLYGON);

			// Render Tag Polygon linjer
			glVertex2f(TagX0, TagY0);
			glVertex2f(TagPos1, TagPos3);
			glVertex2f(TagX0, TagY0);
			glVertex2f(TagPos1, TagPos4);
			glVertex2f(TagPos1, TagPos3);
			glVertex2f(TagPos2, TagPos3);
			glVertex2f(TagPos1, TagPos4);
			glVertex2f(TagPos2, TagPos4);
			glVertex2f(TagPos2, TagPos3);
			glVertex2f(TagPos2, TagPos4);

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

		}

		private: GLvoid RMH_OpenGL_RenderArrowWithLabel(GLfloat ArrowX0, GLfloat ArrowY0, GLfloat ArrowLength, GLfloat ArrowHeadFactor, std::string ArrowLabel, GLubyte LineColorR, GLubyte LineColorG, GLubyte LineColorB, GLubyte LabelColorR, GLubyte LabelColorG, GLubyte LabelColorB) {

			// Routinen renderer en højre orinterede horinzontal pil, med et tilhørende label

			// Udregn Pilens parameter ved skallering af textur vinduet
			ArrowX0 = ArrowX0 * TextureToPanelScaleWidthFactor;
			ArrowY0 = ArrowY0 * TextureToPanelScaleHeightFactor;
			ArrowLength = ArrowLength * TextureToPanelScaleWidthFactor;

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil pilens Farve
			glColor3ub(LineColorR, LineColorG, LineColorB);
			// Indstil pilens Linjens tykkelse
			glLineWidth(1);

			// Render linjer på textur
			glBegin(GL_LINES);

			// Render pilens primære linje
			glVertex2f(ArrowX0, ArrowY0);
			glVertex2f(ArrowX0 - ArrowLength, ArrowY0);
			
			// Render pilens retnings linjer
			glVertex2f(ArrowX0, ArrowY0);
			glVertex2f(ArrowX0 - (ArrowLength / ArrowHeadFactor), ArrowY0 - 1);
			glVertex2f(ArrowX0, ArrowY0);
			glVertex2f(ArrowX0 - (ArrowLength / ArrowHeadFactor), ArrowY0 + 1);

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

			// Render Pilens tilhørende label
			RMH_OpenGL_RenderStringOnTexture(ArrowX0 - ArrowLength, ArrowY0 - 0.5, ArrowLabel, LabelColorR, LabelColorG, LabelColorB);

		}

		private: GLvoid RMH_OpenGL_RenderMaxArrowOutsideIndicator(GLfloat X0Pos, GLfloat Y0Pos, GLfloat Height, GLfloat Width, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen renderer en indikator som indikerer om Maximum track pilen er udenfor colorbar arealet

			// Udregn indikatorens parameter ved skallering af textur vinduet
			X0Pos = X0Pos * TextureToPanelScaleWidthFactor;
			Y0Pos = Y0Pos * TextureToPanelScaleHeightFactor;
			Width = Width * TextureToPanelScaleWidthFactor;
			Height = Height * TextureToPanelScaleHeightFactor;

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil polygon Farve
			glColor3ub(ColorR, ColorG, ColorB);
			// Indstil polygon Linjens tykkelse
			glLineWidth(1);

			// Render Polygon på textur
			glBegin(GL_POLYGON);

			// Render Indikator Polygon linjer
			glVertex2f(X0Pos, Y0Pos);
			glVertex2f(X0Pos + (Width * 0.5), Y0Pos + Height);
			glVertex2f(X0Pos, Y0Pos);
			glVertex2f(X0Pos - (Width * 0.5), Y0Pos + Height);
			glVertex2f(X0Pos + (Width * 0.5), Y0Pos + Height);
			glVertex2f(X0Pos - (Width * 0.5), Y0Pos + Height);

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

		}

		private: GLvoid RMH_OpenGL_RenderMinArrowOutsideIndicator(GLfloat X0Pos, GLfloat Y0Pos, GLfloat Height, GLfloat Width, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen renderer en indikator som indikerer om Maximum track pilen er udenfor colorbar arealet

			// Udregn indikatorens parameter ved skallering af textur vinduet
			X0Pos = X0Pos * TextureToPanelScaleWidthFactor;
			Y0Pos = Y0Pos * TextureToPanelScaleHeightFactor;
			Width = Width * TextureToPanelScaleWidthFactor;
			Height = Height * TextureToPanelScaleHeightFactor;

			// Aktiver OpenGL 1D Texture
			glEnable(GL_TEXTURE_1D);

			// Indstil polygon Farve
			glColor3ub(ColorR, ColorG, ColorB);
			// Indstil polygon Linjens tykkelse
			glLineWidth(1);

			// Render Polygon på textur
			glBegin(GL_POLYGON);

			// Render Indikator Polygon linjer
			glVertex2f(X0Pos, Y0Pos);
			glVertex2f(X0Pos + (Width * 0.5), Y0Pos - Height);
			glVertex2f(X0Pos, Y0Pos);
			glVertex2f(X0Pos - (Width * 0.5), Y0Pos - Height);
			glVertex2f(X0Pos + (Width * 0.5), Y0Pos - Height);
			glVertex2f(X0Pos - (Width * 0.5), Y0Pos - Height);

			// Konfiguration Slut
			glEnd();
			// Deaktiver 1D Texture
			glDisable(GL_TEXTURE_1D);

		}

		// ------------- Positions Justerbar Colorbar Tag Håndterings Routiner ------------- //

		private: bool RMH_OpenGL_IsCursorInsideTag(GLdouble MouseXPosition, GLdouble MouseYPosition, GLfloat TagX0, GLfloat TagY0, GLfloat TagLength, GLfloat TagHeight, GLfloat ArrowLength) {

			// Routinen kontrolerer om Mus Cursoren er indenfor Tag arealet

			// Lokale variabler
			bool IsInsideStatus = false;

			// Kontroller om Mus Cursoren er inde i Tag areal - X Koordinat
			if (MouseXPosition >= TagX0 - ArrowLength - TagLength && MouseXPosition <= TagX0) {

				// Kontroller om Mus Cursoren er inde i Tag areal - Y Koordinat
				if (MouseYPosition >= TagY0 - (TagHeight / 2.0) && 
					MouseYPosition <= TagY0 + (TagHeight / 2.0)) {

					// Opdater Cursor positions status
					IsInsideStatus = true;

				}

			}

			// Retuner Cursor positions status
			return IsInsideStatus;

		}

		private: GLvoid RMH_OpenGL_HandleTagMouseDownEvents(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer events og stadier når det klikkes på et positions justerbar Tag

			// Er Tag Bevægelse ikke aktiverede 
			if (ColorBarTagMoveEnableFlag == false) {

				// Fortsæt ikke
				return;

			}

			// Nulstil Valgte Tag Index værdi
			SelectedTagIndex = 0;

			// Loop Igennem alle aktive Tags
			for (unsigned short i = 0; i < _NumberOfMovableTags + 1; i++) {

				// Kontroller om Mus Cursoren er inde i aktiv Tag areal 
				if (RMH_OpenGL_IsCursorInsideTag(MouseXPosition, MouseYPosition, MaxMinTagX0Pos - MaxMinTagX0Offset,
					MovableTagY0[i], MaxMinTagLength, MaxMinTagHeight, MaxMinTagArrowLength)) {

					// Opdater Tag Move flag
					TagMoveFlag = true;

					// Lager Valgte Tag Index
					SelectedTagIndex = i;

					// Bryd For Loop
					break;

				}

			}

			// Læs nuværende Tag kordinater/positioner ved nyt klick
			ClickTagYPositionOffset = MouseYPosition - MovableTagY0[SelectedTagIndex];

		}

		private: GLvoid RMH_OpenGL_HandleTagMouseMoveEvents(GLdouble MouseXPosition, GLdouble MouseYPosition) {

			// Routinen håndterer events og stadier når et Klikkede Tag skal bevære sig

			// Tilføj Tag Klik Offset Til Mus Positionen
			MouseYPosition = MouseYPosition - ClickTagYPositionOffset;

			// Hvis der endnu ikke er blevet klippet på panalet, eller hvis Tag Bevægelse ikke er aktiverede 
			if (OverlayPanelIsClick == false || ColorBarTagMoveEnableFlag == false) {

				// Fortsæt ikke
				return;

			}

			// Skal ColorBar Taget bevæge sig
			if (TagMoveFlag == true) {

				// Opdater Tagets X og Y kordinater
				MovableTagY0[SelectedTagIndex] = MouseYPosition;

			}

			// Begræns Positionen af Taget til colorbar området og håndter fælles positionering
			if (MovableTagY0[SelectedTagIndex] <= ColorBarPanelTexturePadding) { MovableTagY0[SelectedTagIndex] = ColorBarPanelTexturePadding; }
			if (MovableTagY0[SelectedTagIndex] >= ColorBarPixelHeight + ColorBarPanelTexturePadding) { MovableTagY0[SelectedTagIndex] = ColorBarPixelHeight + ColorBarPanelTexturePadding; }
			if ((MovableTagY0[MaxTagID] + (MaxMinTagHeight / 2) >= MovableTagY0[MinTagID] - (MaxMinTagHeight / 2)) && SelectedTagIndex == MinTagID) {
				MovableTagY0[MaxTagID] = MovableTagY0[MinTagID] - MaxMinTagHeight;
				if (MovableTagY0[MaxTagID] <= ColorBarPanelTexturePadding) {
					MovableTagY0[MaxTagID] = ColorBarPanelTexturePadding;
					MovableTagY0[MinTagID] = ColorBarPanelTexturePadding + MaxMinTagHeight;
				}
			}
			if ((MovableTagY0[MinTagID] - (MaxMinTagHeight / 2) <= MovableTagY0[MaxTagID] + (MaxMinTagHeight / 2)) && SelectedTagIndex == MaxTagID) {
				MovableTagY0[MinTagID] = MovableTagY0[MaxTagID] + MaxMinTagHeight;
				if (MovableTagY0[MinTagID] >= ColorBarPixelHeight + ColorBarPanelTexturePadding) {
					MovableTagY0[MinTagID] = ColorBarPixelHeight + ColorBarPanelTexturePadding;
					MovableTagY0[MaxTagID] = (ColorBarPixelHeight + ColorBarPanelTexturePadding) - MaxMinTagHeight;
				}
			}

		}

		private: GLvoid RMH_OpenGL_RenderMovableColorBarTag(GLfloat TagX0, GLfloat TagXOffset, GLfloat TagLength, GLfloat TagHeight, GLfloat ArrowLength, unsigned char TagID, GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen renderer et positions justerbar colorbar tag

			// Render Colorbar Tag
			RMH_OpenGL_RenderColorBarLimitTag(TagX0 - TagXOffset, MovableTagY0[TagID], TagLength, TagHeight, ArrowLength, ColorR, ColorG, ColorB);

		}

		// ----------- Textur Panel Interaktions Cursor Event Callback Routiner ------------ //

		private: GLvoid TexturePanel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Læs Mus Cursor Positionen
			GLdouble MouseXPosition = RMH_OpenGL_TranslateOverlayPanelMouseXPosToTextureXPos(e);
			GLdouble MouseYPosition = RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(e);
			
			// Opdater overlay panel click flag
			OverlayPanelIsClick = true;

			// Håndter events når det klikkes på et positions justerbar Tag
			RMH_OpenGL_HandleTagMouseDownEvents(MouseXPosition, MouseYPosition);

		}

		private: GLvoid TexturePanel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Opdater overlay panel click flag
			OverlayPanelIsClick = false;

			// Nulstil Tag Move flag
			TagMoveFlag = false;
		
		}

		private: GLvoid TexturePanel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Læs Mus Cursor Positionen
			GLdouble MouseXPosition = RMH_OpenGL_TranslateOverlayPanelMouseXPosToTextureXPos(e);
			GLdouble MouseYPosition = RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(e);

			// Håndterer events når et Klikkede Tag skal bevære sig
			RMH_OpenGL_HandleTagMouseMoveEvents(MouseXPosition, MouseYPosition);

		}

		private: GLvoid TexturePanel_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Lokale variabler
			bool MouseWheelPolNegativeFlag = false;
			GLfloat ColorBarPanelHeight = ColorBarPixelHeight + (ColorBarPanelTexturePadding * 2.0f);
			GLfloat ColorBarPanelMiddle = ColorBarPanelHeight / 2.0f;

			// Kontroller polariteten at scroll retningen
			if (e->Delta > 0) {

				// Positiv polaritet
				MouseWheelScrollPolarity = MouseWheelStepSize;
				// Opdater Mus Hjulets polaritets flag
				MouseWheelPolNegativeFlag = false;

			}
			else {

				// Negativ polaritet
				MouseWheelScrollPolarity = -MouseWheelStepSize;
				// Opdater Mus Hjulets polaritets flag
				MouseWheelPolNegativeFlag = true;

			}

			// Kontroller om Musen er i øvereste eller nedereste del af colorbar panelet
			if (RMH_OpenGL_TranslateOverlayPanelMouseYPosToTextureYPos(e) > ColorBarPanelMiddle) {

				// Er Mus Hjulets polaritet positiv
				if (MouseWheelPolNegativeFlag == false) {

					// Er color barens Min temp range indstilling lavere end Max temp indstillingen
					if (ColorBarMinTempRange < ColorBarMaxTempRange) {

						// Opdater Colorbarens Minimum Temperatur offset værdi fra læst poloritet
						ColorBarMinRangeOffsetValue = ColorBarMinRangeOffsetValue + MouseWheelScrollPolarity;

					}
					else {

						// Indstil Min Range værdien til Max Range værdien
						ColorBarMinTempRange = ColorBarMaxTempRange;

					}
	
				}
				else {

					// Opdater Colorbarens Minimum Temperatur offset værdi fra læst poloritet
					ColorBarMinRangeOffsetValue = ColorBarMinRangeOffsetValue + MouseWheelScrollPolarity;

				}

			}
			else {

				// Er Mus Hjulets polaritet negativt
				if (MouseWheelPolNegativeFlag == true) {

					// Er color barens Max temp range indstilling højere end Min temp indstillingen
					if (ColorBarMaxTempRange > ColorBarMinTempRange) {

						// Opdater Colorbarens Maximum Temperatur offset værdi fra læst poloritet
						ColorBarMaxRangeOffsetValue = ColorBarMaxRangeOffsetValue + MouseWheelScrollPolarity;

					}
					else {

						// Indstil Max Range værdien til Min Range værdien
						ColorBarMaxTempRange = ColorBarMinTempRange;

					}

				}
				else {

					// Opdater Colorbarens Maximum Temperatur offset værdi fra læst poloritet
					ColorBarMaxRangeOffsetValue = ColorBarMaxRangeOffsetValue + MouseWheelScrollPolarity;

				}

			}

		}

		// ---------------------- ColorBar Data Håndterings Routiner ----------------------- //
		
		public: GLvoid RMH_OpenGL_LoadFirstColorPalettesData(unsigned short ColorPalette[3][16384]) {

			// Routinen loader givet color palette data til globale color palette array

			// Loop til og med størrelsen af givet color palettes
			for (unsigned int i = 0, j = 0; j < ColorBarPaletteResolution; i += 32, j += 8) {
	
				// Skriv første color palette data til globalt palette array
				FirstColorPaletteData[i + 0] = ColorPalette[0][j];
				FirstColorPaletteData[i + 1] = ColorPalette[1][j];
				FirstColorPaletteData[i + 2] = ColorPalette[2][j];
				FirstColorPaletteData[i + 3] = ColorBarPaletteIntegerRange; // Alpha Kanal
				FirstColorPaletteData[i + 4] = ColorPalette[0][j + 1];
				FirstColorPaletteData[i + 5] = ColorPalette[1][j + 1];
				FirstColorPaletteData[i + 6] = ColorPalette[2][j + 1];
				FirstColorPaletteData[i + 7] = ColorBarPaletteIntegerRange; // Alpha Kanal
				FirstColorPaletteData[i + 8] = ColorPalette[0][j + 2];
				FirstColorPaletteData[i + 9] = ColorPalette[1][j + 2];
				FirstColorPaletteData[i + 10] = ColorPalette[2][j + 2];
				FirstColorPaletteData[i + 11] = ColorBarPaletteIntegerRange; // Alpha Kanal
				FirstColorPaletteData[i + 12] = ColorPalette[0][j + 3];
				FirstColorPaletteData[i + 13] = ColorPalette[1][j + 3];
				FirstColorPaletteData[i + 14] = ColorPalette[2][j + 3];
				FirstColorPaletteData[i + 15] = ColorBarPaletteIntegerRange; // Alpha Kanal
				FirstColorPaletteData[i + 16] = ColorPalette[0][j + 4];
				FirstColorPaletteData[i + 17] = ColorPalette[1][j + 4];
				FirstColorPaletteData[i + 18] = ColorPalette[2][j + 4];
				FirstColorPaletteData[i + 19] = ColorBarPaletteIntegerRange; // Alpha Kanal
				FirstColorPaletteData[i + 20] = ColorPalette[0][j + 5];
				FirstColorPaletteData[i + 21] = ColorPalette[1][j + 5];
				FirstColorPaletteData[i + 22] = ColorPalette[2][j + 5];
				FirstColorPaletteData[i + 23] = ColorBarPaletteIntegerRange; // Alpha Kanal
				FirstColorPaletteData[i + 24] = ColorPalette[0][j + 6];
				FirstColorPaletteData[i + 25] = ColorPalette[1][j + 6];
				FirstColorPaletteData[i + 26] = ColorPalette[2][j + 6];
				FirstColorPaletteData[i + 27] = ColorBarPaletteIntegerRange; // Alpha Kanal
				FirstColorPaletteData[i + 28] = ColorPalette[0][j + 7];
				FirstColorPaletteData[i + 29] = ColorPalette[1][j + 7];
				FirstColorPaletteData[i + 30] = ColorPalette[2][j + 7];
				FirstColorPaletteData[i + 31] = ColorBarPaletteIntegerRange; // Alpha Kanal
				
			}

		}
		
		public: GLvoid RMH_OpenGL_LoadSecondColorPalettesData(unsigned short ColorPalette[3][16384]) {

			// Routinen loader givet color palette data til globale color palette array

			// Loop til og med størrelsen af givet color palettes
			for (unsigned int i = 0, j = 0; j < ColorBarPaletteResolution; i += 32, j += 8) {

				// Skriv første color palette data til globalt palette array
				SecondColorPaletteData[i + 0] = ColorPalette[0][j];
				SecondColorPaletteData[i + 1] = ColorPalette[1][j];
				SecondColorPaletteData[i + 2] = ColorPalette[2][j];
				SecondColorPaletteData[i + 3] = ColorBarPaletteIntegerRange; // Alpha Kanal
				SecondColorPaletteData[i + 4] = ColorPalette[0][j + 1];
				SecondColorPaletteData[i + 5] = ColorPalette[1][j + 1];
				SecondColorPaletteData[i + 6] = ColorPalette[2][j + 1];
				SecondColorPaletteData[i + 7] = ColorBarPaletteIntegerRange; // Alpha Kanal
				SecondColorPaletteData[i + 8] = ColorPalette[0][j + 2];
				SecondColorPaletteData[i + 9] = ColorPalette[1][j + 2];
				SecondColorPaletteData[i + 10] = ColorPalette[2][j + 2];
				SecondColorPaletteData[i + 11] = ColorBarPaletteIntegerRange; // Alpha Kanal
				SecondColorPaletteData[i + 12] = ColorPalette[0][j + 3];
				SecondColorPaletteData[i + 13] = ColorPalette[1][j + 3];
				SecondColorPaletteData[i + 14] = ColorPalette[2][j + 3];
				SecondColorPaletteData[i + 15] = ColorBarPaletteIntegerRange; // Alpha Kanal
				SecondColorPaletteData[i + 16] = ColorPalette[0][j + 4];
				SecondColorPaletteData[i + 17] = ColorPalette[1][j + 4];
				SecondColorPaletteData[i + 18] = ColorPalette[2][j + 4];
				SecondColorPaletteData[i + 19] = ColorBarPaletteIntegerRange; // Alpha Kanal
				SecondColorPaletteData[i + 20] = ColorPalette[0][j + 5];
				SecondColorPaletteData[i + 21] = ColorPalette[1][j + 5];
				SecondColorPaletteData[i + 22] = ColorPalette[2][j + 5];
				SecondColorPaletteData[i + 23] = ColorBarPaletteIntegerRange; // Alpha Kanal
				SecondColorPaletteData[i + 24] = ColorPalette[0][j + 6];
				SecondColorPaletteData[i + 25] = ColorPalette[1][j + 6];
				SecondColorPaletteData[i + 26] = ColorPalette[2][j + 6];
				SecondColorPaletteData[i + 27] = ColorBarPaletteIntegerRange; // Alpha Kanal
				SecondColorPaletteData[i + 28] = ColorPalette[0][j + 7];
				SecondColorPaletteData[i + 29] = ColorPalette[1][j + 7];
				SecondColorPaletteData[i + 30] = ColorPalette[2][j + 7];
				SecondColorPaletteData[i + 31] = ColorBarPaletteIntegerRange; // Alpha Kanal

			}

		}
		
		public: ColorBarTagPosition RMH_OpenGL_ReadColorBarTagsPositions() {

			// Routinen læser og retunerer Colorbarens Max/Min Tags Positioner på colorbaren

			// Lokale variabler
			ColorBarTagPosition TagPositions;

			// Læs Maximum og Minimum Tag Positionerne
			TagPositions.MaximumTagPos = (MovableTagY0[MaxTagID] - ColorBarPanelTexturePadding) * ((GLfloat)ColorBarPaletteResolution / ColorBarPixelHeight);
			TagPositions.MinimumTagPos = (MovableTagY0[MinTagID] - ColorBarPanelTexturePadding) * ((GLfloat)ColorBarPaletteResolution / ColorBarPixelHeight);

			// Retuner Positioner
			return TagPositions;

		}

		public: GLvoid RMH_OpenGL_SetColorBarMaxMinRangeTemperature(GLfloat MaxTemperature, GLfloat MinTemperature) {

			// Routinen indstiller colorbarens maximum og minimum temperature range

			// Er manual colorbar temperatur range aktiverede
			if (BarManualRangeFlag == true && BarManualHighRangeFlag == false && BarManualLowRangeFlag == false) {

				// Læs og lager maximum og minimum temperaturer globalt i klasse
				ColorBarMaxTempRange = MaxTemperature + ColorBarMaxRangeOffsetValue;
				ColorBarMinTempRange = MinTemperature + ColorBarMinRangeOffsetValue;

			}
			else if (BarManualRangeFlag == false && BarManualHighRangeFlag == true && BarManualLowRangeFlag == false) {

				// Læs og lager maximum og minimum temperaturer globalt i klasse
				ColorBarMaxTempRange = MaxTemperature + ColorBarMaxRangeOffsetValue;
				ColorBarMinTempRange = MinTemperature;

			}
			else if (BarManualRangeFlag == false && BarManualHighRangeFlag == false && BarManualLowRangeFlag == true) {

				// Læs og lager maximum og minimum temperaturer globalt i klasse
				ColorBarMaxTempRange = MaxTemperature;
				ColorBarMinTempRange = MinTemperature + ColorBarMinRangeOffsetValue;

			}
			else {

				// Læs og lager maximum og minimum temperaturer globalt i klasse
				ColorBarMaxTempRange = MaxTemperature;
				ColorBarMinTempRange = MinTemperature;

			}

			// Er color barens Max temp range indstilling højere end Min temp indstillingen
			if (ColorBarMaxTempRange <= ColorBarMinTempRange) {

				// Indstil Max Range værdien til Min Range værdien
				ColorBarMaxTempRange = ColorBarMinTempRange;

			}

			// Er color barens Min temp range indstilling lavere end Max temp indstillingen
			if (ColorBarMinTempRange >= ColorBarMaxTempRange) {

				// Indstil Min Range værdien til Max Range værdien
				ColorBarMinTempRange = ColorBarMaxTempRange;

			}

		}

		public: GLvoid RMH_OpenGL_ResetColorbarMaxMinRangeOffsetValues() {

			// Routinen nulstiller maximum og minimum temperatur range offset værdierne for manual range mode

			// Nulstil maximum og minimum temperatur range offset værdier
			ColorBarMaxRangeOffsetValue = 0.0;
			ColorBarMinRangeOffsetValue = 0.0;

		}
		
		public: GLvoid RMH_OpenGL_FormatColorBarTickAndTagLabelStrings(System::String^ TempUnitString) {

			// Routinen formaterer colorbarens Major og Minor tick label strings

			// Lokale variabler
			unsigned char i = 0;
			GLfloat TempDifference;
			GLfloat TempTickStepDiff;
			GLfloat MaxTagTemperature;
			GLfloat MinTagTemperature;
			ColorBarTagPosition MaxMinTagsPositions;
			GLfloat TickTemperature = ColorBarMaxTempRange;

			// Læs Colorbarens Tag Positioner
			MaxMinTagsPositions = RMH_OpenGL_ReadColorBarTagsPositions();

			// Udregn Temperatur differensen fra Max til Min
			TempDifference = ColorBarMaxTempRange - ColorBarMinTempRange;
			// Udregn Temperatur tick step differensen 
			TempTickStepDiff = TempDifference / ((GLfloat)(NmbOfColorBarTicks - 1));

			// Udregn Colorbarens Max/Min Tag Temperaturer
			MaxTagTemperature = ColorBarMaxTempRange - ((TempDifference / ColorBarPaletteResolution) * MaxMinTagsPositions.MaximumTagPos);
			MinTagTemperature = ColorBarMaxTempRange - ((TempDifference / ColorBarPaletteResolution) * MaxMinTagsPositions.MinimumTagPos);

			// Formater Colorbarens Maximum temperatur tick label 
			PrivateLocals::ColorBarTickLabels[0] = ColorBarMaxTempRange.ToString("F2") + " " + TempUnitString;

			// Loop for valgte antal Colorbar Minor ticks
			for (i = 0; i < NmbOfColorBarTicks - 2; i++) {

				// Dekrementer Minor Tick Temperatur værdi
				TickTemperature = TickTemperature - TempTickStepDiff;

				// Formater Colorbarens Minor temperatur tick labels 
				PrivateLocals::ColorBarTickLabels[i + 1] = TickTemperature.ToString("F1") + " " + TempUnitString;

			}

			// Formater Colorbarens Minimum temperatur tick label 
			PrivateLocals::ColorBarTickLabels[i + 1] = ColorBarMinTempRange.ToString("F2") + " " + TempUnitString;

			// Formater Tag Max/Min temperaturer til System::Strings
			MaximumTagSystemString = MaxTagTemperature.ToString("F1") + TempUnitString;
			MinimumTagSystemString = MinTagTemperature.ToString("F1") + TempUnitString;

			// Hvis Maximum Tag temperaturen er lig med colorbarens maximum temperatur
			if ((unsigned int)(MaxTagTemperature * 1000.0) == (unsigned int)(ColorBarMaxTempRange * 1000.0)) {

				// Indstil Tag String til Fast string
				MaximumTagStdString = "MAX";

			}
			else {

				// Display Tag indstillings temperaturen i Taget
				MaximumTagStdString = RMH_Conversion_SystemStringToStdString(MaximumTagSystemString);

			}

			// Hvis Minimum Tag temperaturen er lig med colorbarens minimum temperatur
			if ((unsigned int)(MinTagTemperature * 1000.0) == (unsigned int)(ColorBarMinTempRange * 1000.0)) {

				// Indstil Tag String til Fast string
				MinimumTagStdString = "MIN";

			}
			else {

				// Display Tag indstillings temperaturen i Taget
				MinimumTagStdString = RMH_Conversion_SystemStringToStdString(MinimumTagSystemString);

			}

		}

		public: GLvoid RMH_OpenGL_UpdateColorBarMaxMinCenterTempArrowsPos(GLfloat FrameMaxTemp, GLfloat FrameMinTemp, GLfloat FrameCenterTemp) {

			// Routinen opdaterer positionerne for Colorbarens Maximum, Minimum og Center temperatur Pilene 

			// Lokale variabler
			GLfloat LinearScaleFactor;
			GLfloat OffsetScale;

			// Udregn linear skallerings faktoren (a Parameter)
			LinearScaleFactor = ((ColorBarPixelHeight + ColorBarPanelTexturePadding) - ColorBarPanelTexturePadding) / (ColorBarMinTempRange - ColorBarMaxTempRange);
			// Udregn linear Offset skalleringen (b Parameter)
			OffsetScale = -ColorBarMaxTempRange * LinearScaleFactor + ColorBarPanelTexturePadding;

			// Udregn og opdater Colorbarens Maximum, Minimum Og Center temperatur Piles positioner
			ColorBarMaxArrowYPos = LinearScaleFactor * FrameMaxTemp + OffsetScale;
			ColorBarMinArrowYPos = LinearScaleFactor * FrameMinTemp + OffsetScale;
			ColorBarCntArrowYPos = LinearScaleFactor * FrameCenterTemp + OffsetScale;

		}
		
		public: ColorBarManualRangeTemps RMH_OpenGL_ReadColorBarRangeMaxMinValues() {

			// Routinen læser og retunerer maximum og minimum colorbar range værdierne

			// Lokale variabler
			ColorBarManualRangeTemps TempRangeValues;

			// Læs maximum og minimum colorbar range værdierne
			TempRangeValues.ManualMaxRangeTemp = ColorBarMaxTempRange;
			TempRangeValues.ManualMinRangeTemp = ColorBarMinTempRange;

			// Retuner maximum og minimum colorbar range værdierne
			return TempRangeValues;

		}

		public: GLvoid RMH_OpenGL_SetMouseWheelTempOffsetStepSize(GLfloat StepSize) {

			// Routinen indstiller temperatur offset step størrelsen for colorbarens Mus Scroll funktionen

			// Indstil temperatur offset step størrelsen for colorbarens Mus Scroll funktionen
			MouseWheelStepSize = StepSize;

		}

		public: GLvoid RMH_OpenGL_InvertColorBarPalettes(bool InvertFirstPalette, bool InvertSecondPalette) {

			// Routinen konfigurerer inverteringen af de to ColorBar color paletter

			// Opdater lokale klasse variabler - inverterings variabler
			InvertFirstPaletteFlag = InvertFirstPalette;
			InvertSecondPaletteFlag = InvertSecondPalette;

		}

		// --------------------- ColorBar Farve Indstillings Routiner ---------------------- //

		public: GLvoid RMH_OpenGL_SetColorBarTickLineColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens tick linje

			// Indstil colorbarens tick linje farve
			TickLineColorR = ColorR;
			TickLineColorG = ColorG;
			TickLineColorB = ColorB;

		}

		public: GLvoid RMH_OpenGL_SetColorBarMaxTagColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens Maximum Temperatur Tag

			// Indstil colorbarens maximum tag farve
			MaxTagColorR = ColorR;
			MaxTagColorG = ColorG;
			MaxTagColorB = ColorB;

		}

		public: GLvoid RMH_OpenGL_SetColorBarMinTagColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens Minimum Temperatur Tag

			// Indstil colorbarens maximum tag farve
			MinTagColorR = ColorR;
			MinTagColorG = ColorG;
			MinTagColorB = ColorB;

		}

		public: GLvoid RMH_OpenGL_SetColorBarMaxArrowColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens Maximum Temperatur Trackings pil

			// Indstil colorbarens Maximum Temperatur Trackings pils farve
			MaxTrackArrowColorR = ColorR;
			MaxTrackArrowColorG = ColorG;
			MaxTrackArrowColorB = ColorB;

		}

		public: GLvoid RMH_OpenGL_SetColorBarMinArrowColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens Minimum Temperatur Trackings pil

			// Indstil colorbarens Minimum Temperatur Trackings pils farve
			MinTrackArrowColorR = ColorR;
			MinTrackArrowColorG = ColorG;
			MinTrackArrowColorB = ColorB;

		}

		public: GLvoid RMH_OpenGL_SetColorBarCenterArrowColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens Center Temperatur Trackings pil

			// Indstil colorbarens Center Temperatur Trackings pils farve
			CntTrackArrowColorR = ColorR;
			CntTrackArrowColorG = ColorG;
			CntTrackArrowColorB = ColorB;

		}

		public: GLvoid RMH_OpenGL_SetColorBarMaxArrowLabelColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens Maximum Temperatur Trackings pil Label

			// Indstil colorbarens Maximum Temperatur Trackings pils Label farve
			MaxTrackArrowLabelColorR = ColorR;
			MaxTrackArrowLabelColorG = ColorG;
			MaxTrackArrowLabelColorB = ColorB;

		}

		public: GLvoid RMH_OpenGL_SetColorBarMinArrowLabelColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens Minimum Temperatur Trackings pil Label

			// Indstil colorbarens Minimum Temperatur Trackings pils Label farve
			MinTrackArrowLabelColorR = ColorR;
			MinTrackArrowLabelColorG = ColorG;
			MinTrackArrowLabelColorB = ColorB;

		}

		public: GLvoid RMH_OpenGL_SetColorBarCenterLabelArrowColor(GLubyte ColorR, GLubyte ColorG, GLubyte ColorB) {

			// Routinen indstiller farven for colorbarens Center Temperatur Trackings pil Label

			// Indstil colorbarens Center Temperatur Trackings pils Label farve
			CntTrackArrowLabelColorR = ColorR;
			CntTrackArrowLabelColorG = ColorG;
			CntTrackArrowLabelColorB = ColorB;

		}

		// ---------------- Samlede ColorBar Grafiske Rendererings Routine ----------------- //

		public: GLvoid RMH_OpenGL_RenderColorBar(unsigned int TexturePanelWidth, unsigned int TexturePanelHeight, bool DualPaletteEnableFlag, unsigned char NmbOfMinorTicks, bool EnableCenterArrowFlag, bool ManualRangeFlag, bool ManualRangeHighFlag, bool ManualRangeLowFlag) {

			// Routinen rendererer alle colorbarens grafiske objekter
			// Her kan yderligere konfigureres forskellige grafiske offset parameter og værdier

			// Læs Nuværende textur Panels pixel højde og bredde 
			CurrentTexturePanelHeight = (GLdouble)TexturePanelHeight;
			CurrentTexturePanelWidth = (GLdouble)TexturePanelWidth;

			// Udregn Textur til panel skallerings faktor
			TextureToPanelScaleWidthFactor = CurrentTexturePanelWidth / TotalTextureScalableWidth;
			TextureToPanelScaleHeightFactor = CurrentTexturePanelHeight / TotalTextureScalableHeight;

			// Gør Tilhørende Render kontekst det nuværende render kontekst
			RMH_OpenGL_MakeRenderContextCurrent();
			// Ryd Textur farve og bit buffere
			RMH_OpenGL_ClearTextureBuffer();
			// Opdater Textur Field Of View
			RMH_OpenGL_UpdateTextureFieldOfView(TextureWidth, TextureHeight);

			// Bind OpenGL textur og Start OpenGL renderering
			RMH_OpenGL_StartColorBarRender();

			// Render primære ColorBar
			RMH_OpenGL_RenderColorBarPalette(ColorBarX0TexturePos, ColorBarPanelTexturePadding, ColorBarTextureWidth, ColorBarPixelHeight, &FirstColorPaletteData[0], InvertFirstPaletteFlag);

			// Skal Dual color palette vises
			if (DualPaletteEnableFlag == true) {

				// Render sekundære ColorBar
				RMH_OpenGL_RenderColorBarPalette(ColorBarX0TexturePos, ColorBarPanelTexturePadding, ColorBarTextureWidth / 2.0f, ColorBarPixelHeight, &SecondColorPaletteData[0], InvertSecondPaletteFlag);

			}

			// Render Colorbarent Tick Linje
			RMH_OpenGL_RenderColorBarTickLinesAndLabels(ColorBarX0TexturePos + ColorBarTextureWidth + TickLineColorBarOffset, ColorBarPanelTexturePadding,
				ColorBarPixelHeight, NmbOfMinorTicks, TickLineColorR, TickLineColorG, TickLineColorB);

			// Nulstil Colorbarens "Temperatur Trackings Pile Er udenfor Colorbar arealet" indikator flag 
			ShowTopOutsideIndicatorFlag = false;
			ShowButOutsideIndicatorFlag = false;

			// Indstil Colorbarens Range Flag
			BarManualRangeFlag = ManualRangeFlag;
			BarManualHighRangeFlag = ManualRangeHighFlag;
			BarManualLowRangeFlag = ManualRangeLowFlag;

			// Er Manual colorbar temperatur range aktiverede
			if (BarManualRangeFlag == true && BarManualHighRangeFlag == false && BarManualLowRangeFlag == false) {

				// Render kun maximum indikator, hvis den er indenfor colorbarens Y areal
				if (ColorBarMaxArrowYPos < ColorBarPanelTexturePadding) {

					// Maximum temp trackings pilen er over maximum range temperaturen
					ShowTopOutsideIndicatorFlag = true;

				}
				else {

					// Render kun maximum indikator, hvis den er indenfor colorbarens Y areal
					if (ColorBarMaxArrowYPos < ColorBarPixelHeight + ColorBarPanelTexturePadding) {

						// Render Colorbarens Maximum temperatur indikator pil
						RMH_OpenGL_RenderArrowWithLabel(MaxMinTagX0Pos - 1, ColorBarMaxArrowYPos, 5, 5, "MAX",
							MaxTrackArrowColorR, MaxTrackArrowColorG, MaxTrackArrowColorB,
							MaxTrackArrowLabelColorR, MaxTrackArrowLabelColorG, MaxTrackArrowLabelColorB);

					}
					else {

						// Maximum temp trackings pilen er under minimum range temperaturen
						ShowButOutsideIndicatorFlag = true;

					}

				}

				// Render kun minimum indikator, hvis den er indenfor colorbarens Y areal
				if (ColorBarMinArrowYPos > ColorBarPixelHeight + ColorBarPanelTexturePadding) {

					// Minimum temp trackings pilen er under minimum range temperaturen
					ShowButOutsideIndicatorFlag = true;

				}
				else {

					// Render kun minimum indikator, hvis den er indenfor colorbarens Y areal
					if (ColorBarMinArrowYPos > ColorBarPanelTexturePadding) {

						// Render Colorbarens Minimum temperatur indikator pil
						RMH_OpenGL_RenderArrowWithLabel(MaxMinTagX0Pos - 1, ColorBarMinArrowYPos, 5, 5, "MIN",
							MinTrackArrowColorR, MinTrackArrowColorG, MinTrackArrowColorB,
							MinTrackArrowLabelColorR, MinTrackArrowLabelColorG, MinTrackArrowLabelColorB);

					}
					else {

						// Minimum temp trackings pilen er over maximum range temperaturen
						ShowTopOutsideIndicatorFlag = true;

					}

				}

			}
			else if (BarManualRangeFlag == false && BarManualHighRangeFlag == true && BarManualLowRangeFlag == false) {

				// Render kun maximum indikator, hvis den er indenfor colorbarens Y areal
				if (ColorBarMaxArrowYPos < ColorBarPanelTexturePadding) {

					// Maximum temp trackings pilen er over maximum range temperaturen
					ShowTopOutsideIndicatorFlag = true;

				}
				else {

					// Render kun maximum indikator, hvis den er indenfor colorbarens Y areal
					if (ColorBarMaxArrowYPos < ColorBarPixelHeight + ColorBarPanelTexturePadding) {

						// Render Colorbarens Maximum temperatur indikator pil
						RMH_OpenGL_RenderArrowWithLabel(MaxMinTagX0Pos - 1, ColorBarMaxArrowYPos, 5, 5, "MAX",
							MaxTrackArrowColorR, MaxTrackArrowColorG, MaxTrackArrowColorB,
							MaxTrackArrowLabelColorR, MaxTrackArrowLabelColorG, MaxTrackArrowLabelColorB);

					}
					else {

						// Maximum temp trackings pilen er under minimum range temperaturen
						ShowButOutsideIndicatorFlag = true;

					}

				}

			}
			else if (BarManualRangeFlag == false && BarManualHighRangeFlag == false && BarManualLowRangeFlag == true) {

				// Render kun minimum indikator, hvis den er indenfor colorbarens Y areal
				if (ColorBarMinArrowYPos > ColorBarPixelHeight + ColorBarPanelTexturePadding) {

					// Minimum temp trackings pilen er under minimum range temperaturen
					ShowButOutsideIndicatorFlag = true;

				}
				else {

					// Render kun minimum indikator, hvis den er indenfor colorbarens Y areal
					if (ColorBarMinArrowYPos > ColorBarPanelTexturePadding) {

						// Render Colorbarens Minimum temperatur indikator pil
						RMH_OpenGL_RenderArrowWithLabel(MaxMinTagX0Pos - 1, ColorBarMinArrowYPos, 5, 5, "MIN",
							MinTrackArrowColorR, MinTrackArrowColorG, MinTrackArrowColorB,
							MinTrackArrowLabelColorR, MinTrackArrowLabelColorG, MinTrackArrowLabelColorB);

					}
					else {

						// Minimum temp trackings pilen er over maximum range temperaturen
						ShowTopOutsideIndicatorFlag = true;

					}

				}

			}

			// Er Center Colorbar temperatur indikator pilen aktiverede
			if (EnableCenterArrowFlag == true) {

				// Render kun Center indikator, hvis den er indenfor colorbarens Y areal
				if (ColorBarCntArrowYPos > ColorBarPanelTexturePadding) {

					// Render kun Center indikator, hvis den er indenfor colorbarens Y areal
					if (ColorBarCntArrowYPos < ColorBarPixelHeight + ColorBarPanelTexturePadding) {

						// Render Colorbarens Center temperatur indikator pil
						RMH_OpenGL_RenderArrowWithLabel(MaxMinTagX0Pos - 1, ColorBarCntArrowYPos, 7, 7, "Center",
							CntTrackArrowColorR, CntTrackArrowColorG, CntTrackArrowColorB,
							CntTrackArrowLabelColorR, CntTrackArrowLabelColorG, CntTrackArrowLabelColorB);

					}
					else {

						// Center temp trackings pilen er under minimum range temperaturen
						ShowButOutsideIndicatorFlag = true;

					}

				}
				else {

					// Center temp trackings pilen er over maximum range temperaturen
					ShowTopOutsideIndicatorFlag = true;

				}

			}

			// Er en eller flere trakings pile over maximum range temperaturen
			if (ShowTopOutsideIndicatorFlag == true) {

				// Render indikator som indikerer at Max/Min/center track pilene er udenfor colorbar arealet
				RMH_OpenGL_RenderMaxArrowOutsideIndicator(4, 3, 4, 4, MaxTrackArrowColorR, MaxTrackArrowColorG, MaxTrackArrowColorB);

			}

			// Er en eller flere trakings pile under minimum range temperaturen
			if (ShowButOutsideIndicatorFlag == true) {

				// Render indikator som indikerer at Max/Min/center track pilene er udenfor colorbar arealet
				RMH_OpenGL_RenderMinArrowOutsideIndicator(4, ColorBarPixelHeight + ColorBarPanelTexturePadding + 3, 4, 4, MinTrackArrowColorR, MinTrackArrowColorG, MinTrackArrowColorB);
					
			}

			// Render Colorbar Maximum og Minimum Justerbar Tags og tilhørende label strings
			RMH_OpenGL_RenderMovableColorBarTag(MaxMinTagX0Pos, MaxMinTagX0Offset, MaxMinTagLength, MaxMinTagHeight, MaxMinTagArrowLength, MaxTagID, MaxTagColorR, MaxTagColorG, MaxTagColorB);
			RMH_OpenGL_RenderMovableColorBarTag(MaxMinTagX0Pos, MaxMinTagX0Offset, MaxMinTagLength, MaxMinTagHeight, MaxMinTagArrowLength, MinTagID, MinTagColorR, MinTagColorG, MinTagColorB);
			RMH_OpenGL_RenderStringOnTexture(ColorBarAreaX0 - TagLabelXOffset, (MovableTagY0[MaxTagID] * TextureToPanelScaleHeightFactor) + TagLabelYOffset, MaximumTagStdString, TickLineColorR, TickLineColorG, TickLineColorB);
			RMH_OpenGL_RenderStringOnTexture(ColorBarAreaX0 - TagLabelXOffset, (MovableTagY0[MinTagID] * TextureToPanelScaleHeightFactor) + TagLabelYOffset, MinimumTagStdString, TickLineColorR, TickLineColorG, TickLineColorB);

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

		~RMHOpenGLColorBar(GLvoid) {

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
