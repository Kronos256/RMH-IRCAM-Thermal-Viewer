#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"
#include "RMH_Application_ColorBarAndPalette.h"
#include "RMH_OpenGL_ColorBar.h"
#include "RMH_Winforms_Library.h"
#include "LiveViewTools.h"
#include <iostream>

namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Summary for Form - LiveViewStream
	public ref class LiveViewStream : public System::Windows::Forms::Form {

		// ------------------------------ Lokale Form Reference Struktur ------------------------------ //

		// Lokale Reference struktur
		ref struct ManagedLocals {

			// Live View Tools Form statiske Objekter og variabler
			static IRCAMThermalViewer::LiveViewTools^ LiveViewToolsForm;

		};

		// ----------------------------- Lokale Form Reference Variabler ------------------------------ //

		// Private Globale klasse objekter og variabler
		bool LiveViewSplitViewToggleflag = true;
		#define _LiveViewStream_DefaultSplitterDistanceRatio          0.50

		// -------------------------------------------------------------------------------------------- //

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		LiveViewStream(void) {

			// Init GUI komponenter og objekter
			InitializeComponent();
			// Formater arrays Og Objekter af winform komponenter til global brug
			InitializeComponentArraysAndGlobalObjects();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Opdaterer Teksten i toppen af GUIen
			RMH_Winforms_ChangeFormTitleBarText(this, "Live View Stream");

			// Initiliser Live View tools Form
			ManagedLocals::LiveViewToolsForm = gcnew IRCAMThermalViewer::LiveViewTools();

			// Dock Live View Tools Form i Live View Formen ved start-op
			DockLiveViewToolsFormInLiveViewToolsPanel();

		}

		// ---------------------------- Diverse Tilhørende Klasse Metoder ----------------------------- //

		void InitializeComponentArraysAndGlobalObjects(void) {

			// Routinen formaterer arrays af winform komponenter til global brug

			// Initiliser globale form objekter
			GlobalVariables::OpenGLRender = gcnew OpenGLWinForms::RMHOpenGLWF(this->LiveViewStreamPanel, 4);
			GlobalVariables::OpenGLColorBar = gcnew OpenGLColorBar::RMHOpenGLColorBar(this->ColorBarMainPanel, 2);
			GlobalVariables::OpenGLHistogram = gcnew OpenGLHistogram::RMHOpenGLHistogram(this->LiveViewHistogramPanel, 2);
			GlobalVariables::GlobaldeleteTempLabelToolStripMenuItem = this->deleteTempLabelToolStripMenuItem;
			GlobalVariables::GlobaldeleteROIToolStripMenuItem = this->deleteROIToolStripMenuItem;
			GlobalVariables::GlobalhistogramSourceToolStripMenuItem = this->histogramSourceToolStripMenuItem;
			GlobalVariables::GlobaldeleteLineToolStripMenuItem = this->deleteLineToolStripMenuItem;
			GlobalVariables::GlobalLiveViewHistogramPanel = this->LiveViewHistogramPanel;
			GlobalVariables::GlobalStreamAndCBarPanel = this->StreamAndCBarPanel;
			GlobalVariables::GlobalLiveViewStreamPanel = this->LiveViewStreamPanel;
			GlobalVariables::GlobaluseDualPaletteToolStripMenuItem = this->useDualPaletteToolStripMenuItem;
			GlobalVariables::GlobalLiveViewMWRotationStripMenuItem = this->LiveViewMWRotationStripMenuItem;
			GlobalVariables::GlobalRotateLiveViewCWStripMenuItem = this->RotateLiveViewCWStripMenuItem;
			GlobalVariables::GlobalRotateLiveViewCCWStripMenuItem = this->RotateLiveViewCCWStripMenuItem;
			GlobalVariables::GlobalSetSharpStdDivToolStripMenuItem = this->SetSharpStdDivToolStripMenuItem;
			GlobalVariables::GlobalimageSharpeningStrengthToolStripMenuItem = this->imageSharpeningStrengthToolStripMenuItem;
			GlobalVariables::GlobalshowUnsharpMaskToolStripMenuItem = this->showUnsharpMaskToolStripMenuItem;
			GlobalVariables::GlobaldeleteAllToolStripMenuItem2 = this->deleteAllToolStripMenuItem2;
			GlobalVariables::GlobalchangeLineColorsToolStripMenuItem = this->changeLineColorsToolStripMenuItem;
			GlobalVariables::GlobalchangeROIColorsToolStripMenuItem = this->changeROIColorsToolStripMenuItem;
			GlobalVariables::GlobaltemperatureRangeToolStripMenuItem = this->temperatureRangeToolStripMenuItem;
			GlobalVariables::GlobalenableFullPaletteRangeAdjustmentToolStripMenuItem = this->enableFullPaletteRangeAdjustmentToolStripMenuItem;
			GlobalVariables::GlobaladjustDualPaletteRangeToolStripMenuItem = this->adjustDualPaletteRangeToolStripMenuItem;
			GlobalVariables::GlobalLiveViewZoomPanel = this->LiveViewZoomPanel;
			GlobalVariables::LiveViewZoomWindowRender = gcnew LiveViewZoomWindow::RMHLiveViewZoomWindow(this->LiveViewZoomPanel);
			GlobalVariables::GlobalLiveViewSplitViewToolStripMenuItem = this->LiveViewSplitViewToolStripMenuItem;
			GlobalVariables::GlobalColorBarMainPanel = this->ColorBarMainPanel;

		}

		void DockLiveViewToolsFormInLiveViewToolsPanel() {

			// Routinen Docker Live View Tools Formen i Live View Tool Panelet

			// Opdater Live View Tools panelets synligheds flag
			LiveViewToolsPanelVisibilityFlag = true;

			// Gør Live View Tools Panelet syneligt
			this->LiveViewToolsPanel->Visible = LiveViewToolsPanelVisibilityFlag;

			// Dock Live View Tools Form i Live View Formen ved start-op
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::LiveViewToolsForm, this->LiveViewToolsPanel, &isLiveViewToolsFormOpen, &isLiveViewToolsFormDocked, &isLiveViewToolsFormUndocked, _FormDockingState_DockForm);

		}

		void HandleLiveViewButtonsHotKeyFunctions(System::Windows::Forms::KeyPressEventArgs^ e) {

			// Routinen håndterer live view funktions knappernes HotKeys 

			// Hvilken knap er blevet trykket
			switch (e->KeyChar) {

				// Eksikver Hot Key funktion
				case '9': ManagedLocals::LiveViewToolsForm->DualColorPaletteButton_Click(nullptr, nullptr);										break; // Live View Dual Color Palette - HotKey: 9
				case '8': ManagedLocals::LiveViewToolsForm->CursorTempTrackButton_Click(nullptr, nullptr);										break; // Mouse Point Temp Tracking - HotKey: 8
				case '7': ManagedLocals::LiveViewToolsForm->AddROIMeasButton_Click(nullptr, nullptr);											break; // Add Live View ROI - HotKey: 7
				case '6': ManagedLocals::LiveViewToolsForm->ShowLineHistButton_Click(nullptr, nullptr);											break; // Show Histogram - HotKey: 6
				case '5': ManagedLocals::LiveViewToolsForm->AddTempSpecLineButton_Click(nullptr, nullptr);										break; // Add Temp Spectrum Line - HotKey: 5
				case '4': ManagedLocals::LiveViewToolsForm->AddTempMeasButton_Click(nullptr, nullptr);											break; // Add Temp Measurement - HotKey: 4
				case '3': ManagedLocals::LiveViewToolsForm->CenterTempTrackButton_Click(nullptr, nullptr);										break; // Center Track - HotKey: 3
				case '2': ManagedLocals::LiveViewToolsForm->MinTempTrackButton_Click(nullptr, nullptr);											break; // Min Track - HotKey: 2
				case '1': ManagedLocals::LiveViewToolsForm->MaxTempTrackButton_Click(nullptr, nullptr);			 								break; // Max Track - HotKey: 1
				case 'h':
				case 'H': ManagedLocals::LiveViewToolsForm->LiveViewRunStopButton_Click(nullptr, nullptr);										break; // Run/Stop - HotKey: H & h
				case 'q':
				case 'Q': ManagedLocals::LiveViewToolsForm->CalibrateCameraButton_Click(nullptr, nullptr);										break; // Calibrate Camera - HotKey: Q & q
				case 't':
				case 'T': ManagedLocals::LiveViewToolsForm->TempRangeButton_Click(nullptr, nullptr);											break; // Temp Range - HotKey: T & t
				case 'x':
				case 'X': ManagedLocals::LiveViewToolsForm->EnhancedResButton_Click(nullptr, nullptr);											break; // Enhanced Resolution - HotKey: X & x
				case 'y':
				case 'Y': ManagedLocals::LiveViewToolsForm->ImageSharpButton_Click(nullptr, nullptr);											break; // Image Sharpening - HotKey: Y & y
				case 'u':
				case 'U':  ManagedLocals::LiveViewToolsForm->UltraResolutionButton_Click(nullptr, nullptr);										break; // Ultra Resolution - HotKey: U & u
				case 'a':
				case 'A': ManagedLocals::LiveViewToolsForm->FixedAspectRatioButton_Click(nullptr, nullptr);										break; // Fixed Aspect Ratio - HotKey: A & a
				case 's':
				case 'S': ManagedLocals::LiveViewToolsForm->SnapshotButton_Click(nullptr, nullptr);												break; // Take Snapshot - HotKey: S & s
				case 'v':
				case 'V': ManagedLocals::LiveViewToolsForm->RecordButton_Click(nullptr, nullptr);												break; // Record Live View - HotKey: V & v
				case 'c':
				case 'C': ManagedLocals::LiveViewToolsForm->TempUnitCButton_Click(ManagedLocals::LiveViewToolsForm->TempUnitCButton, nullptr);	break; // Temp Unit: Celsius - HotKey: C & c
				case 'f':
				case 'F': ManagedLocals::LiveViewToolsForm->TempUnitCButton_Click(ManagedLocals::LiveViewToolsForm->TempUnitFButton, nullptr);	break; // Temp Unit: Fahrenheit - HotKey: F & f
				case 'k':
				case 'K': ManagedLocals::LiveViewToolsForm->TempUnitCButton_Click(ManagedLocals::LiveViewToolsForm->TempUnitKButton, nullptr);	break; // Temp Unit: Kelvin - HotKey: K & k
				case 'm':
				case 'M': RMH_ThermalViewer_StartDataLogging();																					break; // Start Data Logging - HotKey: M & m
				case 'n':
				case 'N': RMH_ThermalViewer_StopDataLogging();																					break; // Stop Data Logging - HotKey: N & n
				case 'o':
				case 'O': RMH_ThermalViewer_TriggerLiveViewSingleFrameCapture();																break; // Live View Singel Trigger - HotKey: O & o
				case 'p':
				case 'P': ManagedLocals::LiveViewToolsForm->PeriodicTimerTriggerButton_Click(nullptr, nullptr);									break; // Live View Periodisk Trigger - HotKey: P & p
				case 'r':
				case 'R': GlobalVariables::OpenGLRender->RMH_OpenGL_RotateLiveViewCW();															break; // Roter Live view billedet med 90 grader CW - HotKey: R & r

			}

		}

		void HandleFormsOpeningDockingAndUndocking(System::Windows::Forms::Form^ FormObject, System::Windows::Forms::Panel^ ParentPanel, bool* FormOpenedFlag, bool* FormDockedFlag, bool* FormUndockedFlag, unsigned short FormState) {

			// Routinen håndterer Docking og Undocking af de forskellige Forms

			// ---------------------------------------------------------------- Docking/Undocking Procedure ---------------------------------------------------------------- //

			// Skal en Form Dockes til parent panelet
			if (FormState == _FormDockingState_DockForm) {

				// Hvis Valgte Form allerede er åben
				if (*FormOpenedFlag == true) {

					// Luk valgte Formen før docking
					RMH_Winforms_CloseForm(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

				}

				// Åben og dock form i main GUIens Main Panel
				RMH_Winforms_OpenAndDockFormInParentPanel(FormObject, ParentPanel, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

			}

			// Skal en Form Undockes fra parent panelet
			if (FormState == _FormDockingState_UndockForm) {

				// Hvis Main View panelet er parent til valgte Form Objekt
				if (FormObject->Parent == ParentPanel) {

					// Nulstil Formens Parent 
					FormObject->Parent = nullptr;
					// Fjern Formen som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

				}

				// Kontroller om formen er åben, med ikke docked
				if (*FormOpenedFlag == true && *FormDockedFlag == false) {

					// Luk Formen
					RMH_Winforms_CloseForm(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

					// Undock Formen og åben i seperat vindue
					RMH_Winforms_OpenFormInSeperateWindow(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

				}

				// Kontroller om formen er åben og docked
				if (*FormOpenedFlag == true && *FormDockedFlag == true) {

					// Luk Formen
					RMH_Winforms_CloseForm(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

					// Undock Formen fra Parent panelet og åben i seperat vindue
					RMH_Winforms_UndockFormFromParentPanel(FormObject, ParentPanel, FormOpenedFlag, FormDockedFlag, FormUndockedFlag, System::Windows::Forms::FormBorderStyle::FixedToolWindow);

				}

				// Kontroller om formen ikke er åben og ikke er docked
				if (*FormOpenedFlag == false && *FormDockedFlag == false) {

					// Undock Formen og åben i seperat vindue
					RMH_Winforms_OpenFormInSeperateWindow(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

				}

			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------- //

		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LiveViewStream() {

			if (components) {

				// Slet alle Form Komponenter
				delete components;

			}

			// Ryd op i managed objekter i RAM
			System::GC::Collect();

		}

	private:

		/// <summary>
		/// Required designer variable.
		/// </summary>
		/// 
		private: System::ComponentModel::IContainer^ components;
		private: System::Windows::Forms::Panel^ CompleteLiveViewPanel;
		private: System::Windows::Forms::Panel^ LiveViewMainPanel;
		private: System::Windows::Forms::Button^ button1;
		private: System::Windows::Forms::Panel^ StreamAndCBarPanel;
		public: System::Windows::Forms::Panel^ LiveViewStreamPanel;
		private: System::Windows::Forms::Panel^ LiveViewStreamSubPanel;
		private: System::Windows::Forms::Button^ button2;
		private: System::Windows::Forms::ContextMenuStrip^ LiveViewContextStrip;
		private: System::Windows::Forms::ToolStripMenuItem^ changeLabelColorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ maxLabelToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ minLabelColorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ centerLabelColorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ liveViewStreamToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
		private: System::Windows::Forms::ToolStripMenuItem^ changeAllLabelsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ deleteROIToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ deleteTempLabelToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI1ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI2ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI3ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI4ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI5ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI6ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI7ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI8ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI9ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI10ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ deleteAllToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas1ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas2ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas3ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas4ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas5ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas6ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas7ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas8ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas9ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeas10ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ deleteAllToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ changeROIColorsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ selectedColorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ passiveColorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ labelSeletedColorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ labelPassiveColorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ changeZOrderToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOIsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOIBringToFrontToolStripMenuItem; 
		private: System::Windows::Forms::ToolStripMenuItem^ tempMeasurementsToolStripMenuItem;	   
		private: System::Windows::Forms::ToolStripMenuItem^ bringToFrontToolStripMenuItem;
		private: System::Windows::Forms::ToolTip^ LiveViewToolTip;
		private: System::Windows::Forms::ToolStripMenuItem^ deleteLineToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line1ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line2ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line3ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line4ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line5ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ spectrumLinesToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ deleteAllToolStripMenuItem3;
		private: System::Windows::Forms::ToolStripMenuItem^ changeLineColorsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ selectedColorToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ passiveColorToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator3;
		private: System::Windows::Forms::ToolStripMenuItem^ bringToFrontToolStripMenuItem1;
		public: System::Windows::Forms::Panel^ ColorBarMainPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
		private: System::Windows::Forms::ContextMenuStrip^ ColorBarContextStrip;
		private: System::Windows::Forms::ToolStripMenuItem^ testToolStripMenuItem;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator4;
		private: System::Windows::Forms::ToolStripMenuItem^ temperatureRangeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ autoToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ manualToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ setColorBarRangesToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ trackCenterTemperatureToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ enableToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ disableToolStripMenuItem;
		private: System::Windows::Forms::ComboBox^ comboBox1;
		private: System::Windows::Forms::ToolStripMenuItem^ mouseWheelStedSizeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ stepSize1ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ stepSize01ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ stepSizeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ stepSize05ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ stepSize02ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ stepSize01ToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ colorBarTemperatureTicksToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem3;
		public: System::Windows::Forms::Panel^ LiveViewHistogramPanel;
		private: System::Windows::Forms::ContextMenuStrip^ HistPanelContextStrip;
		private: System::Windows::Forms::ToolStripMenuItem^ liveViewHistogramToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator7;
		private: System::Windows::Forms::ToolStripMenuItem^ mimicColorBarPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ ShowRangedPaletteToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ showFullPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ useDualColorPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ useLiveViewPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ useDualPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ histogramSourceToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ liveViewToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line1SpectrumToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line2SpectrumToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line3SpectrumToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line4SpectrumToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ line5SpectrumToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator9;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI1AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI2AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI3AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI4AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI5AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI6AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI7AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI8AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI9AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ rOI10AreaToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ imageSharpeningStrengthToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator10;
		private: System::Windows::Forms::ToolStripMenuItem^ SetSharpStdDivToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ showUnsharpMaskToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ ShowUnsharpTrueToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ ShowUnsharpFalseToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator11;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator13;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator12;
		private: System::Windows::Forms::ToolStripMenuItem^ invertColorPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ invertLiveViewPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ invertLiveViewDualPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ invertColorBarBackgroundPaletteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ deleteAllToolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ enableLabelBackgroundToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ enableBackgroundToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ disableBackgroundToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ changeLabelBackgroundColorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator5;
		private: System::Windows::Forms::ToolStripMenuItem^ changeLabelColorsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ enableFullPaletteRangeAdjustmentToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ enableToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ disableToolStripMenuItem1;
		private: System::Windows::Forms::Panel^ LiveViewToolsPanel;
		private: System::Windows::Forms::ToolStripMenuItem^ adjustLivePaletteRangeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ adjustDualPaletteRangeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ enableDefaultToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ disableToolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ enableToolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ disableDefaultToolStripMenuItem;
		private: System::Windows::Forms::Panel^ panel2;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator6;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator8;
		private: System::Windows::Forms::ToolStripMenuItem^ undockToolsPanelToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ toggleToolsPanelVisibilityToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ toggleColorBarVisibilityToolStripMenuItem;
		private: System::Windows::Forms::Panel^ panel3;
		private: System::Windows::Forms::ToolStripMenuItem^ HistNmbOfBinsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem11;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem12;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem13;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem14;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem15;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem16;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem17;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem18;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator14;
		private: System::Windows::Forms::ToolStripMenuItem^ RotateLiveViewCWStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ LiveViewMWRotationStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem3;
		public: System::Windows::Forms::Panel^ LiveViewStreamMainPanel;
		private: System::Windows::Forms::SplitContainer^ LiveViewSplitContainer;
		private: System::Windows::Forms::ToolStripMenuItem^ LiveViewSplitViewToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator15;
		private: System::Windows::Forms::Panel^ LiveViewZoomPanel;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ manualHighRangeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ manualLowRangeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ RotateLiveViewCCWStripMenuItem;

#pragma region Windows Form Designer generated code
		
	    /// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LiveViewStream::typeid));
			this->CompleteLiveViewPanel = (gcnew System::Windows::Forms::Panel());
			this->LiveViewMainPanel = (gcnew System::Windows::Forms::Panel());
			this->StreamAndCBarPanel = (gcnew System::Windows::Forms::Panel());
			this->LiveViewStreamSubPanel = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->LiveViewStreamMainPanel = (gcnew System::Windows::Forms::Panel());
			this->LiveViewSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->LiveViewStreamPanel = (gcnew System::Windows::Forms::Panel());
			this->LiveViewContextStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->liveViewStreamToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator8 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->LiveViewSplitViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator15 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->undockToolsPanelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toggleToolsPanelVisibilityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toggleColorBarVisibilityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator14 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->invertColorPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->invertLiveViewPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->invertLiveViewDualPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->invertColorBarBackgroundPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->LiveViewMWRotationStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RotateLiveViewCWStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RotateLiveViewCCWStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator10 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->SetSharpStdDivToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->imageSharpeningStrengthToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showUnsharpMaskToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ShowUnsharpTrueToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ShowUnsharpFalseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->deleteLineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line4ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line5ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteAllToolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteROIToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI4ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI5ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI6ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI7ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI8ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI9ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI10ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteTempLabelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas4ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas5ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas6ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas7ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas8ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas9ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeas10ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteAllToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteAllToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->enableLabelBackgroundToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enableBackgroundToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->disableBackgroundToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->changeLineColorsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->selectedColorToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->passiveColorToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeROIColorsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->selectedColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->passiveColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeLabelColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeAllLabelsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->maxLabelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->minLabelColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->centerLabelColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->labelSeletedColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->labelPassiveColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeLabelColorsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeLabelBackgroundColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->changeZOrderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOIsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOIBringToFrontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tempMeasurementsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bringToFrontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->spectrumLinesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bringToFrontToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LiveViewZoomPanel = (gcnew System::Windows::Forms::Panel());
			this->LiveViewHistogramPanel = (gcnew System::Windows::Forms::Panel());
			this->HistPanelContextStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->liveViewHistogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator7 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->histogramSourceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line1SpectrumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line2SpectrumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line3SpectrumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line4SpectrumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->line5SpectrumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI1AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI2AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI3AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI4AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI5AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI6AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI7AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI8AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI9AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rOI10AreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->liveViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HistNmbOfBinsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem11 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem12 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem13 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem14 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem15 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem16 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem17 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem18 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator9 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->mimicColorBarPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ShowRangedPaletteToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showFullPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->useDualColorPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->useLiveViewPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->useDualPaletteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LiveViewToolsPanel = (gcnew System::Windows::Forms::Panel());
			this->ColorBarMainPanel = (gcnew System::Windows::Forms::Panel());
			this->ColorBarContextStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->testToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->temperatureRangeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->autoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->manualToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enableFullPaletteRangeAdjustmentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enableToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->disableToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator11 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->colorBarTemperatureTicksToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator13 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->setColorBarRangesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mouseWheelStedSizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stepSize1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stepSize01ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stepSizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stepSize05ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stepSize02ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stepSize01ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator12 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->trackCenterTemperatureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enableToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->disableToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->adjustLivePaletteRangeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enableDefaultToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->disableToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->adjustDualPaletteRangeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enableToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->disableDefaultToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LiveViewToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->manualLowRangeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->manualHighRangeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CompleteLiveViewPanel->SuspendLayout();
			this->LiveViewMainPanel->SuspendLayout();
			this->StreamAndCBarPanel->SuspendLayout();
			this->LiveViewStreamSubPanel->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->LiveViewStreamMainPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LiveViewSplitContainer))->BeginInit();
			this->LiveViewSplitContainer->Panel1->SuspendLayout();
			this->LiveViewSplitContainer->Panel2->SuspendLayout();
			this->LiveViewSplitContainer->SuspendLayout();
			this->LiveViewContextStrip->SuspendLayout();
			this->HistPanelContextStrip->SuspendLayout();
			this->ColorBarContextStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// CompleteLiveViewPanel
			// 
			this->CompleteLiveViewPanel->Controls->Add(this->LiveViewMainPanel);
			this->CompleteLiveViewPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->CompleteLiveViewPanel->Location = System::Drawing::Point(0, 0);
			this->CompleteLiveViewPanel->Margin = System::Windows::Forms::Padding(0);
			this->CompleteLiveViewPanel->Name = L"CompleteLiveViewPanel";
			this->CompleteLiveViewPanel->Size = System::Drawing::Size(1511, 847);
			this->CompleteLiveViewPanel->TabIndex = 4;
			// 
			// LiveViewMainPanel
			// 
			this->LiveViewMainPanel->Controls->Add(this->StreamAndCBarPanel);
			this->LiveViewMainPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->LiveViewMainPanel->Location = System::Drawing::Point(0, 0);
			this->LiveViewMainPanel->Name = L"LiveViewMainPanel";
			this->LiveViewMainPanel->Size = System::Drawing::Size(1511, 847);
			this->LiveViewMainPanel->TabIndex = 2;
			// 
			// StreamAndCBarPanel
			// 
			this->StreamAndCBarPanel->Controls->Add(this->LiveViewStreamSubPanel);
			this->StreamAndCBarPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->StreamAndCBarPanel->Location = System::Drawing::Point(0, 0);
			this->StreamAndCBarPanel->Name = L"StreamAndCBarPanel";
			this->StreamAndCBarPanel->Size = System::Drawing::Size(1511, 847);
			this->StreamAndCBarPanel->TabIndex = 3;
			// 
			// LiveViewStreamSubPanel
			// 
			this->LiveViewStreamSubPanel->Controls->Add(this->panel2);
			this->LiveViewStreamSubPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->LiveViewStreamSubPanel->Location = System::Drawing::Point(0, 0);
			this->LiveViewStreamSubPanel->Margin = System::Windows::Forms::Padding(0);
			this->LiveViewStreamSubPanel->Name = L"LiveViewStreamSubPanel";
			this->LiveViewStreamSubPanel->Padding = System::Windows::Forms::Padding(5);
			this->LiveViewStreamSubPanel->Size = System::Drawing::Size(1511, 847);
			this->LiveViewStreamSubPanel->TabIndex = 2;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->panel3);
			this->panel2->Controls->Add(this->LiveViewHistogramPanel);
			this->panel2->Controls->Add(this->LiveViewToolsPanel);
			this->panel2->Controls->Add(this->ColorBarMainPanel);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(5, 5);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1501, 837);
			this->panel2->TabIndex = 15;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->LiveViewStreamMainPanel);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(172, 0);
			this->panel3->Margin = System::Windows::Forms::Padding(3, 20, 20, 20);
			this->panel3->Name = L"panel3";
			this->panel3->Padding = System::Windows::Forms::Padding(3, 20, 20, 20);
			this->panel3->Size = System::Drawing::Size(1058, 837);
			this->panel3->TabIndex = 13;
			// 
			// LiveViewStreamMainPanel
			// 
			this->LiveViewStreamMainPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->LiveViewStreamMainPanel->Controls->Add(this->LiveViewSplitContainer);
			this->LiveViewStreamMainPanel->Cursor = System::Windows::Forms::Cursors::Default;
			this->LiveViewStreamMainPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->LiveViewStreamMainPanel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->LiveViewStreamMainPanel->Location = System::Drawing::Point(3, 20);
			this->LiveViewStreamMainPanel->Margin = System::Windows::Forms::Padding(0);
			this->LiveViewStreamMainPanel->Name = L"LiveViewStreamMainPanel";
			this->LiveViewStreamMainPanel->Size = System::Drawing::Size(1035, 797);
			this->LiveViewStreamMainPanel->TabIndex = 1;
			// 
			// LiveViewSplitContainer
			// 
			this->LiveViewSplitContainer->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)),
				static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(15)));
			this->LiveViewSplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->LiveViewSplitContainer->Location = System::Drawing::Point(0, 0);
			this->LiveViewSplitContainer->Margin = System::Windows::Forms::Padding(0);
			this->LiveViewSplitContainer->Name = L"LiveViewSplitContainer";
			// 
			// LiveViewSplitContainer.Panel1
			// 
			this->LiveViewSplitContainer->Panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->LiveViewSplitContainer->Panel1->Controls->Add(this->LiveViewStreamPanel);
			this->LiveViewSplitContainer->Panel1MinSize = 385;
			// 
			// LiveViewSplitContainer.Panel2
			// 
			this->LiveViewSplitContainer->Panel2->Controls->Add(this->LiveViewZoomPanel);
			this->LiveViewSplitContainer->Panel2Collapsed = true;
			this->LiveViewSplitContainer->Panel2MinSize = 200;
			this->LiveViewSplitContainer->Size = System::Drawing::Size(1033, 795);
			this->LiveViewSplitContainer->SplitterDistance = 385;
			this->LiveViewSplitContainer->SplitterWidth = 3;
			this->LiveViewSplitContainer->TabIndex = 1;
			// 
			// LiveViewStreamPanel
			// 
			this->LiveViewStreamPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->LiveViewStreamPanel->ContextMenuStrip = this->LiveViewContextStrip;
			this->LiveViewStreamPanel->Cursor = System::Windows::Forms::Cursors::Default;
			this->LiveViewStreamPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->LiveViewStreamPanel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->LiveViewStreamPanel->Location = System::Drawing::Point(0, 0);
			this->LiveViewStreamPanel->Margin = System::Windows::Forms::Padding(0);
			this->LiveViewStreamPanel->Name = L"LiveViewStreamPanel";
			this->LiveViewStreamPanel->Size = System::Drawing::Size(1033, 795);
			this->LiveViewStreamPanel->TabIndex = 0;
			// 
			// LiveViewContextStrip
			// 
			this->LiveViewContextStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->LiveViewContextStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(32) {
				this->liveViewStreamToolStripMenuItem,
					this->toolStripSeparator8, this->LiveViewSplitViewToolStripMenuItem, this->toolStripSeparator15, this->undockToolsPanelToolStripMenuItem,
					this->toggleToolsPanelVisibilityToolStripMenuItem, this->toggleColorBarVisibilityToolStripMenuItem, this->toolStripSeparator14,
					this->invertColorPaletteToolStripMenuItem, this->toolStripSeparator6, this->LiveViewMWRotationStripMenuItem, this->RotateLiveViewCWStripMenuItem,
					this->RotateLiveViewCCWStripMenuItem, this->toolStripSeparator10, this->SetSharpStdDivToolStripMenuItem, this->imageSharpeningStrengthToolStripMenuItem,
					this->showUnsharpMaskToolStripMenuItem, this->toolStripSeparator1, this->deleteLineToolStripMenuItem, this->deleteROIToolStripMenuItem,
					this->deleteTempLabelToolStripMenuItem, this->deleteAllToolStripMenuItem2, this->toolStripSeparator5, this->enableLabelBackgroundToolStripMenuItem,
					this->toolStripSeparator2, this->changeLineColorsToolStripMenuItem, this->changeROIColorsToolStripMenuItem, this->changeLabelColorToolStripMenuItem,
					this->changeLabelColorsToolStripMenuItem, this->changeLabelBackgroundColorToolStripMenuItem, this->toolStripSeparator3, this->changeZOrderToolStripMenuItem
			});
			this->LiveViewContextStrip->Name = L"contextMenuStrip1";
			this->LiveViewContextStrip->ShowImageMargin = false;
			this->LiveViewContextStrip->Size = System::Drawing::Size(242, 564);
			// 
			// liveViewStreamToolStripMenuItem
			// 
			this->liveViewStreamToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->liveViewStreamToolStripMenuItem->Enabled = false;
			this->liveViewStreamToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->liveViewStreamToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->liveViewStreamToolStripMenuItem->Name = L"liveViewStreamToolStripMenuItem";
			this->liveViewStreamToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->liveViewStreamToolStripMenuItem->Text = L"Live View Stream:";
			// 
			// toolStripSeparator8
			// 
			this->toolStripSeparator8->Name = L"toolStripSeparator8";
			this->toolStripSeparator8->Size = System::Drawing::Size(238, 6);
			// 
			// LiveViewSplitViewToolStripMenuItem
			// 
			this->LiveViewSplitViewToolStripMenuItem->Enabled = false;
			this->LiveViewSplitViewToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->LiveViewSplitViewToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->LiveViewSplitViewToolStripMenuItem->Name = L"LiveViewSplitViewToolStripMenuItem";
			this->LiveViewSplitViewToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->LiveViewSplitViewToolStripMenuItem->Text = L"Toggle Live View Split View";
			this->LiveViewSplitViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::LiveViewSplitViewToolStripMenuItem_Click);
			// 
			// toolStripSeparator15
			// 
			this->toolStripSeparator15->Name = L"toolStripSeparator15";
			this->toolStripSeparator15->Size = System::Drawing::Size(238, 6);
			// 
			// undockToolsPanelToolStripMenuItem
			// 
			this->undockToolsPanelToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->undockToolsPanelToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->undockToolsPanelToolStripMenuItem->Name = L"undockToolsPanelToolStripMenuItem";
			this->undockToolsPanelToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->undockToolsPanelToolStripMenuItem->Text = L"Undock Tools Panel";
			this->undockToolsPanelToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::undockToolsPanelToolStripMenuItem_Click);
			// 
			// toggleToolsPanelVisibilityToolStripMenuItem
			// 
			this->toggleToolsPanelVisibilityToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->toggleToolsPanelVisibilityToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->toggleToolsPanelVisibilityToolStripMenuItem->Name = L"toggleToolsPanelVisibilityToolStripMenuItem";
			this->toggleToolsPanelVisibilityToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->toggleToolsPanelVisibilityToolStripMenuItem->Text = L"Toggle Tools Panel Visibility";
			this->toggleToolsPanelVisibilityToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::toggleToolsPanelVisibilityToolStripMenuItem_Click);
			// 
			// toggleColorBarVisibilityToolStripMenuItem
			// 
			this->toggleColorBarVisibilityToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->toggleColorBarVisibilityToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->toggleColorBarVisibilityToolStripMenuItem->Name = L"toggleColorBarVisibilityToolStripMenuItem";
			this->toggleColorBarVisibilityToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->toggleColorBarVisibilityToolStripMenuItem->Text = L"Toggle ColorBar Visibility";
			this->toggleColorBarVisibilityToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::toggleColorBarVisibilityToolStripMenuItem_Click_1);
			// 
			// toolStripSeparator14
			// 
			this->toolStripSeparator14->Name = L"toolStripSeparator14";
			this->toolStripSeparator14->Size = System::Drawing::Size(238, 6);
			// 
			// invertColorPaletteToolStripMenuItem
			// 
			this->invertColorPaletteToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->invertLiveViewPaletteToolStripMenuItem,
					this->invertLiveViewDualPaletteToolStripMenuItem, this->invertColorBarBackgroundPaletteToolStripMenuItem
			});
			this->invertColorPaletteToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->invertColorPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->invertColorPaletteToolStripMenuItem->Name = L"invertColorPaletteToolStripMenuItem";
			this->invertColorPaletteToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->invertColorPaletteToolStripMenuItem->Text = L"Invert Color Palette";
			// 
			// invertLiveViewPaletteToolStripMenuItem
			// 
			this->invertLiveViewPaletteToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->invertLiveViewPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->invertLiveViewPaletteToolStripMenuItem->Name = L"invertLiveViewPaletteToolStripMenuItem";
			this->invertLiveViewPaletteToolStripMenuItem->Size = System::Drawing::Size(265, 22);
			this->invertLiveViewPaletteToolStripMenuItem->Tag = L"0";
			this->invertLiveViewPaletteToolStripMenuItem->Text = L"Invert Live View Palette";
			this->invertLiveViewPaletteToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::invertLiveViewPaletteToolStripMenuItem_Click);
			// 
			// invertLiveViewDualPaletteToolStripMenuItem
			// 
			this->invertLiveViewDualPaletteToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->invertLiveViewDualPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->invertLiveViewDualPaletteToolStripMenuItem->Name = L"invertLiveViewDualPaletteToolStripMenuItem";
			this->invertLiveViewDualPaletteToolStripMenuItem->Size = System::Drawing::Size(265, 22);
			this->invertLiveViewDualPaletteToolStripMenuItem->Tag = L"1";
			this->invertLiveViewDualPaletteToolStripMenuItem->Text = L"Invert Live View Dual Palette";
			this->invertLiveViewDualPaletteToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::invertLiveViewPaletteToolStripMenuItem_Click);
			// 
			// invertColorBarBackgroundPaletteToolStripMenuItem
			// 
			this->invertColorBarBackgroundPaletteToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->invertColorBarBackgroundPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->invertColorBarBackgroundPaletteToolStripMenuItem->Name = L"invertColorBarBackgroundPaletteToolStripMenuItem";
			this->invertColorBarBackgroundPaletteToolStripMenuItem->Size = System::Drawing::Size(265, 22);
			this->invertColorBarBackgroundPaletteToolStripMenuItem->Tag = L"2";
			this->invertColorBarBackgroundPaletteToolStripMenuItem->Text = L"Invert ColorBar Background Palette";
			this->invertColorBarBackgroundPaletteToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::invertLiveViewPaletteToolStripMenuItem_Click);
			// 
			// toolStripSeparator6
			// 
			this->toolStripSeparator6->Name = L"toolStripSeparator6";
			this->toolStripSeparator6->Size = System::Drawing::Size(238, 6);
			// 
			// LiveViewMWRotationStripMenuItem
			// 
			this->LiveViewMWRotationStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->LiveViewMWRotationStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuItem2,
					this->toolStripMenuItem3
			});
			this->LiveViewMWRotationStripMenuItem->Enabled = false;
			this->LiveViewMWRotationStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->LiveViewMWRotationStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->LiveViewMWRotationStripMenuItem->Name = L"LiveViewMWRotationStripMenuItem";
			this->LiveViewMWRotationStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->LiveViewMWRotationStripMenuItem->Text = L"Live View Mouse Wheel Rotation";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem2->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(117, 22);
			this->toolStripMenuItem2->Tag = L"1";
			this->toolStripMenuItem2->Text = L"Enable";
			this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &LiveViewStream::EnableDisableMouseWheelRotation_Click);
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem3->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(117, 22);
			this->toolStripMenuItem3->Tag = L"0";
			this->toolStripMenuItem3->Text = L"Disable";
			this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &LiveViewStream::EnableDisableMouseWheelRotation_Click);
			// 
			// RotateLiveViewCWStripMenuItem
			// 
			this->RotateLiveViewCWStripMenuItem->Enabled = false;
			this->RotateLiveViewCWStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->RotateLiveViewCWStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->RotateLiveViewCWStripMenuItem->Name = L"RotateLiveViewCWStripMenuItem";
			this->RotateLiveViewCWStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->RotateLiveViewCWStripMenuItem->Text = L"Rotate Live View Image CW";
			this->RotateLiveViewCWStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::RotateLiveViewCWStripMenuItem_Click);
			// 
			// RotateLiveViewCCWStripMenuItem
			// 
			this->RotateLiveViewCCWStripMenuItem->Enabled = false;
			this->RotateLiveViewCCWStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->RotateLiveViewCCWStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->RotateLiveViewCCWStripMenuItem->Name = L"RotateLiveViewCCWStripMenuItem";
			this->RotateLiveViewCCWStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->RotateLiveViewCCWStripMenuItem->Text = L"Rotate Live View Image CCW";
			this->RotateLiveViewCCWStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::RotateLiveViewCCWStripMenuItem_Click);
			// 
			// toolStripSeparator10
			// 
			this->toolStripSeparator10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->toolStripSeparator10->Name = L"toolStripSeparator10";
			this->toolStripSeparator10->Size = System::Drawing::Size(238, 6);
			// 
			// SetSharpStdDivToolStripMenuItem
			// 
			this->SetSharpStdDivToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->SetSharpStdDivToolStripMenuItem->Enabled = false;
			this->SetSharpStdDivToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->SetSharpStdDivToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->SetSharpStdDivToolStripMenuItem->Name = L"SetSharpStdDivToolStripMenuItem";
			this->SetSharpStdDivToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->SetSharpStdDivToolStripMenuItem->Text = L"Set Sharpening Standard Deviation";
			this->SetSharpStdDivToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::SetSharpStdDivToolStripMenuItem_Click);
			// 
			// imageSharpeningStrengthToolStripMenuItem
			// 
			this->imageSharpeningStrengthToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->imageSharpeningStrengthToolStripMenuItem->Enabled = false;
			this->imageSharpeningStrengthToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->imageSharpeningStrengthToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->imageSharpeningStrengthToolStripMenuItem->Name = L"imageSharpeningStrengthToolStripMenuItem";
			this->imageSharpeningStrengthToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->imageSharpeningStrengthToolStripMenuItem->Text = L"Set Image Sharpening Strength";
			this->imageSharpeningStrengthToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::imageSharpeningStrengthToolStripMenuItem_Click);
			// 
			// showUnsharpMaskToolStripMenuItem
			// 
			this->showUnsharpMaskToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->showUnsharpMaskToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ShowUnsharpTrueToolStripMenuItem,
					this->ShowUnsharpFalseToolStripMenuItem
			});
			this->showUnsharpMaskToolStripMenuItem->Enabled = false;
			this->showUnsharpMaskToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->showUnsharpMaskToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->showUnsharpMaskToolStripMenuItem->Name = L"showUnsharpMaskToolStripMenuItem";
			this->showUnsharpMaskToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->showUnsharpMaskToolStripMenuItem->Text = L"Edge Focus Assist Mode";
			// 
			// ShowUnsharpTrueToolStripMenuItem
			// 
			this->ShowUnsharpTrueToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ShowUnsharpTrueToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->ShowUnsharpTrueToolStripMenuItem->Name = L"ShowUnsharpTrueToolStripMenuItem";
			this->ShowUnsharpTrueToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->ShowUnsharpTrueToolStripMenuItem->Tag = L"1";
			this->ShowUnsharpTrueToolStripMenuItem->Text = L"Enable";
			this->ShowUnsharpTrueToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::ShowUnsharpTrueToolStripMenuItem_Click);
			// 
			// ShowUnsharpFalseToolStripMenuItem
			// 
			this->ShowUnsharpFalseToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ShowUnsharpFalseToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->ShowUnsharpFalseToolStripMenuItem->Name = L"ShowUnsharpFalseToolStripMenuItem";
			this->ShowUnsharpFalseToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->ShowUnsharpFalseToolStripMenuItem->Tag = L"0";
			this->ShowUnsharpFalseToolStripMenuItem->Text = L"Disable";
			this->ShowUnsharpFalseToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::ShowUnsharpFalseToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(238, 6);
			// 
			// deleteLineToolStripMenuItem
			// 
			this->deleteLineToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->deleteLineToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->line1ToolStripMenuItem,
					this->line2ToolStripMenuItem, this->line3ToolStripMenuItem, this->line4ToolStripMenuItem, this->line5ToolStripMenuItem, this->deleteAllToolStripMenuItem3
			});
			this->deleteLineToolStripMenuItem->Enabled = false;
			this->deleteLineToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->deleteLineToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->deleteLineToolStripMenuItem->Name = L"deleteLineToolStripMenuItem";
			this->deleteLineToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->deleteLineToolStripMenuItem->Text = L"Delete Line";
			// 
			// line1ToolStripMenuItem
			// 
			this->line1ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line1ToolStripMenuItem->Enabled = false;
			this->line1ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line1ToolStripMenuItem->Name = L"line1ToolStripMenuItem";
			this->line1ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->line1ToolStripMenuItem->Tag = L"0";
			this->line1ToolStripMenuItem->Text = L"Line 1";
			this->line1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::line1ToolStripMenuItem_Click);
			// 
			// line2ToolStripMenuItem
			// 
			this->line2ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line2ToolStripMenuItem->Enabled = false;
			this->line2ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line2ToolStripMenuItem->Name = L"line2ToolStripMenuItem";
			this->line2ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->line2ToolStripMenuItem->Tag = L"1";
			this->line2ToolStripMenuItem->Text = L"Line 2";
			this->line2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::line1ToolStripMenuItem_Click);
			// 
			// line3ToolStripMenuItem
			// 
			this->line3ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line3ToolStripMenuItem->Enabled = false;
			this->line3ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line3ToolStripMenuItem->Name = L"line3ToolStripMenuItem";
			this->line3ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->line3ToolStripMenuItem->Tag = L"2";
			this->line3ToolStripMenuItem->Text = L"Line 3";
			this->line3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::line1ToolStripMenuItem_Click);
			// 
			// line4ToolStripMenuItem
			// 
			this->line4ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line4ToolStripMenuItem->Enabled = false;
			this->line4ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line4ToolStripMenuItem->Name = L"line4ToolStripMenuItem";
			this->line4ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->line4ToolStripMenuItem->Tag = L"3";
			this->line4ToolStripMenuItem->Text = L"Line 4";
			this->line4ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::line1ToolStripMenuItem_Click);
			// 
			// line5ToolStripMenuItem
			// 
			this->line5ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line5ToolStripMenuItem->Enabled = false;
			this->line5ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line5ToolStripMenuItem->Name = L"line5ToolStripMenuItem";
			this->line5ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->line5ToolStripMenuItem->Tag = L"4";
			this->line5ToolStripMenuItem->Text = L"Line 5";
			this->line5ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::line1ToolStripMenuItem_Click);
			// 
			// deleteAllToolStripMenuItem3
			// 
			this->deleteAllToolStripMenuItem3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->deleteAllToolStripMenuItem3->ForeColor = System::Drawing::Color::White;
			this->deleteAllToolStripMenuItem3->Name = L"deleteAllToolStripMenuItem3";
			this->deleteAllToolStripMenuItem3->Size = System::Drawing::Size(125, 22);
			this->deleteAllToolStripMenuItem3->Text = L"Delete All";
			this->deleteAllToolStripMenuItem3->Click += gcnew System::EventHandler(this, &LiveViewStream::deleteAllToolStripMenuItem3_Click);
			// 
			// deleteROIToolStripMenuItem
			// 
			this->deleteROIToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->deleteROIToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
				this->rOI1ToolStripMenuItem,
					this->rOI2ToolStripMenuItem, this->rOI3ToolStripMenuItem, this->rOI4ToolStripMenuItem, this->rOI5ToolStripMenuItem, this->rOI6ToolStripMenuItem,
					this->rOI7ToolStripMenuItem, this->rOI8ToolStripMenuItem, this->rOI9ToolStripMenuItem, this->rOI10ToolStripMenuItem, this->deleteAllToolStripMenuItem
			});
			this->deleteROIToolStripMenuItem->Enabled = false;
			this->deleteROIToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->deleteROIToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->deleteROIToolStripMenuItem->Name = L"deleteROIToolStripMenuItem";
			this->deleteROIToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->deleteROIToolStripMenuItem->Text = L"Delete Live ROI";
			// 
			// rOI1ToolStripMenuItem
			// 
			this->rOI1ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI1ToolStripMenuItem->Enabled = false;
			this->rOI1ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI1ToolStripMenuItem->Name = L"rOI1ToolStripMenuItem";
			this->rOI1ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI1ToolStripMenuItem->Tag = L"0";
			this->rOI1ToolStripMenuItem->Text = L"ROI 1";
			this->rOI1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI2ToolStripMenuItem
			// 
			this->rOI2ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI2ToolStripMenuItem->Enabled = false;
			this->rOI2ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI2ToolStripMenuItem->Name = L"rOI2ToolStripMenuItem";
			this->rOI2ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI2ToolStripMenuItem->Tag = L"1";
			this->rOI2ToolStripMenuItem->Text = L"ROI 2";
			this->rOI2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI3ToolStripMenuItem
			// 
			this->rOI3ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI3ToolStripMenuItem->Enabled = false;
			this->rOI3ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI3ToolStripMenuItem->Name = L"rOI3ToolStripMenuItem";
			this->rOI3ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI3ToolStripMenuItem->Tag = L"2";
			this->rOI3ToolStripMenuItem->Text = L"ROI 3";
			this->rOI3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI4ToolStripMenuItem
			// 
			this->rOI4ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI4ToolStripMenuItem->Enabled = false;
			this->rOI4ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI4ToolStripMenuItem->Name = L"rOI4ToolStripMenuItem";
			this->rOI4ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI4ToolStripMenuItem->Tag = L"3";
			this->rOI4ToolStripMenuItem->Text = L"ROI 4";
			this->rOI4ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI5ToolStripMenuItem
			// 
			this->rOI5ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI5ToolStripMenuItem->Enabled = false;
			this->rOI5ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI5ToolStripMenuItem->Name = L"rOI5ToolStripMenuItem";
			this->rOI5ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI5ToolStripMenuItem->Tag = L"4";
			this->rOI5ToolStripMenuItem->Text = L"ROI 5";
			this->rOI5ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI6ToolStripMenuItem
			// 
			this->rOI6ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI6ToolStripMenuItem->Enabled = false;
			this->rOI6ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI6ToolStripMenuItem->Name = L"rOI6ToolStripMenuItem";
			this->rOI6ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI6ToolStripMenuItem->Tag = L"5";
			this->rOI6ToolStripMenuItem->Text = L"ROI 6";
			this->rOI6ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI7ToolStripMenuItem
			// 
			this->rOI7ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI7ToolStripMenuItem->Enabled = false;
			this->rOI7ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI7ToolStripMenuItem->Name = L"rOI7ToolStripMenuItem";
			this->rOI7ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI7ToolStripMenuItem->Tag = L"6";
			this->rOI7ToolStripMenuItem->Text = L"ROI 7";
			this->rOI7ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI8ToolStripMenuItem
			// 
			this->rOI8ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI8ToolStripMenuItem->Enabled = false;
			this->rOI8ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI8ToolStripMenuItem->Name = L"rOI8ToolStripMenuItem";
			this->rOI8ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI8ToolStripMenuItem->Tag = L"7";
			this->rOI8ToolStripMenuItem->Text = L"ROI 8";
			this->rOI8ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI9ToolStripMenuItem
			// 
			this->rOI9ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI9ToolStripMenuItem->Enabled = false;
			this->rOI9ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI9ToolStripMenuItem->Name = L"rOI9ToolStripMenuItem";
			this->rOI9ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI9ToolStripMenuItem->Tag = L"8";
			this->rOI9ToolStripMenuItem->Text = L"ROI 9";
			this->rOI9ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// rOI10ToolStripMenuItem
			// 
			this->rOI10ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI10ToolStripMenuItem->Enabled = false;
			this->rOI10ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI10ToolStripMenuItem->Name = L"rOI10ToolStripMenuItem";
			this->rOI10ToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->rOI10ToolStripMenuItem->Tag = L"9";
			this->rOI10ToolStripMenuItem->Text = L"ROI 10";
			this->rOI10ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOI1ToolStripMenuItem_Click);
			// 
			// deleteAllToolStripMenuItem
			// 
			this->deleteAllToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->deleteAllToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->deleteAllToolStripMenuItem->Name = L"deleteAllToolStripMenuItem";
			this->deleteAllToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->deleteAllToolStripMenuItem->Text = L"Delete All";
			this->deleteAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::deleteAllToolStripMenuItem_Click);
			// 
			// deleteTempLabelToolStripMenuItem
			// 
			this->deleteTempLabelToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->deleteTempLabelToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
				this->tempMeas1ToolStripMenuItem,
					this->tempMeas2ToolStripMenuItem, this->tempMeas3ToolStripMenuItem, this->tempMeas4ToolStripMenuItem, this->tempMeas5ToolStripMenuItem,
					this->tempMeas6ToolStripMenuItem, this->tempMeas7ToolStripMenuItem, this->tempMeas8ToolStripMenuItem, this->tempMeas9ToolStripMenuItem,
					this->tempMeas10ToolStripMenuItem, this->deleteAllToolStripMenuItem1
			});
			this->deleteTempLabelToolStripMenuItem->Enabled = false;
			this->deleteTempLabelToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->deleteTempLabelToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->deleteTempLabelToolStripMenuItem->Name = L"deleteTempLabelToolStripMenuItem";
			this->deleteTempLabelToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->deleteTempLabelToolStripMenuItem->Text = L"Delete Temp Label";
			// 
			// tempMeas1ToolStripMenuItem
			// 
			this->tempMeas1ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas1ToolStripMenuItem->Enabled = false;
			this->tempMeas1ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas1ToolStripMenuItem->Name = L"tempMeas1ToolStripMenuItem";
			this->tempMeas1ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas1ToolStripMenuItem->Tag = L"0";
			this->tempMeas1ToolStripMenuItem->Text = L"Temp Meas 1";
			this->tempMeas1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas2ToolStripMenuItem
			// 
			this->tempMeas2ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas2ToolStripMenuItem->Enabled = false;
			this->tempMeas2ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas2ToolStripMenuItem->Name = L"tempMeas2ToolStripMenuItem";
			this->tempMeas2ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas2ToolStripMenuItem->Tag = L"1";
			this->tempMeas2ToolStripMenuItem->Text = L"Temp Meas 2";
			this->tempMeas2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas3ToolStripMenuItem
			// 
			this->tempMeas3ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas3ToolStripMenuItem->Enabled = false;
			this->tempMeas3ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas3ToolStripMenuItem->Name = L"tempMeas3ToolStripMenuItem";
			this->tempMeas3ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas3ToolStripMenuItem->Tag = L"2";
			this->tempMeas3ToolStripMenuItem->Text = L"Temp Meas 3";
			this->tempMeas3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas4ToolStripMenuItem
			// 
			this->tempMeas4ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas4ToolStripMenuItem->Enabled = false;
			this->tempMeas4ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas4ToolStripMenuItem->Name = L"tempMeas4ToolStripMenuItem";
			this->tempMeas4ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas4ToolStripMenuItem->Tag = L"3";
			this->tempMeas4ToolStripMenuItem->Text = L"Temp Meas 4";
			this->tempMeas4ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas5ToolStripMenuItem
			// 
			this->tempMeas5ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas5ToolStripMenuItem->Enabled = false;
			this->tempMeas5ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas5ToolStripMenuItem->Name = L"tempMeas5ToolStripMenuItem";
			this->tempMeas5ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas5ToolStripMenuItem->Tag = L"4";
			this->tempMeas5ToolStripMenuItem->Text = L"Temp Meas 5";
			this->tempMeas5ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas6ToolStripMenuItem
			// 
			this->tempMeas6ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas6ToolStripMenuItem->Enabled = false;
			this->tempMeas6ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas6ToolStripMenuItem->Name = L"tempMeas6ToolStripMenuItem";
			this->tempMeas6ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas6ToolStripMenuItem->Tag = L"5";
			this->tempMeas6ToolStripMenuItem->Text = L"Temp Meas 6";
			this->tempMeas6ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas7ToolStripMenuItem
			// 
			this->tempMeas7ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas7ToolStripMenuItem->Enabled = false;
			this->tempMeas7ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas7ToolStripMenuItem->Name = L"tempMeas7ToolStripMenuItem";
			this->tempMeas7ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas7ToolStripMenuItem->Tag = L"6";
			this->tempMeas7ToolStripMenuItem->Text = L"Temp Meas 7";
			this->tempMeas7ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas8ToolStripMenuItem
			// 
			this->tempMeas8ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas8ToolStripMenuItem->Enabled = false;
			this->tempMeas8ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas8ToolStripMenuItem->Name = L"tempMeas8ToolStripMenuItem";
			this->tempMeas8ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas8ToolStripMenuItem->Tag = L"7";
			this->tempMeas8ToolStripMenuItem->Text = L"Temp Meas 8";
			this->tempMeas8ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas9ToolStripMenuItem
			// 
			this->tempMeas9ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas9ToolStripMenuItem->Enabled = false;
			this->tempMeas9ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas9ToolStripMenuItem->Name = L"tempMeas9ToolStripMenuItem";
			this->tempMeas9ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas9ToolStripMenuItem->Tag = L"8";
			this->tempMeas9ToolStripMenuItem->Text = L"Temp Meas 9";
			this->tempMeas9ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// tempMeas10ToolStripMenuItem
			// 
			this->tempMeas10ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeas10ToolStripMenuItem->Enabled = false;
			this->tempMeas10ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeas10ToolStripMenuItem->Name = L"tempMeas10ToolStripMenuItem";
			this->tempMeas10ToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->tempMeas10ToolStripMenuItem->Tag = L"9";
			this->tempMeas10ToolStripMenuItem->Text = L"Temp Meas 10";
			this->tempMeas10ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::tempMeas1ToolStripMenuItem_Click);
			// 
			// deleteAllToolStripMenuItem1
			// 
			this->deleteAllToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->deleteAllToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->deleteAllToolStripMenuItem1->Name = L"deleteAllToolStripMenuItem1";
			this->deleteAllToolStripMenuItem1->Size = System::Drawing::Size(155, 22);
			this->deleteAllToolStripMenuItem1->Text = L"Delete All";
			this->deleteAllToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::deleteAllToolStripMenuItem1_Click);
			// 
			// deleteAllToolStripMenuItem2
			// 
			this->deleteAllToolStripMenuItem2->Enabled = false;
			this->deleteAllToolStripMenuItem2->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->deleteAllToolStripMenuItem2->ForeColor = System::Drawing::Color::White;
			this->deleteAllToolStripMenuItem2->Name = L"deleteAllToolStripMenuItem2";
			this->deleteAllToolStripMenuItem2->Size = System::Drawing::Size(241, 22);
			this->deleteAllToolStripMenuItem2->Text = L"Delete All";
			this->deleteAllToolStripMenuItem2->Click += gcnew System::EventHandler(this, &LiveViewStream::deleteAllToolStripMenuItem2_Click);
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(238, 6);
			// 
			// enableLabelBackgroundToolStripMenuItem
			// 
			this->enableLabelBackgroundToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->enableBackgroundToolStripMenuItem,
					this->disableBackgroundToolStripMenuItem
			});
			this->enableLabelBackgroundToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->enableLabelBackgroundToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->enableLabelBackgroundToolStripMenuItem->Name = L"enableLabelBackgroundToolStripMenuItem";
			this->enableLabelBackgroundToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->enableLabelBackgroundToolStripMenuItem->Text = L"Enable Label Background";
			// 
			// enableBackgroundToolStripMenuItem
			// 
			this->enableBackgroundToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->enableBackgroundToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->enableBackgroundToolStripMenuItem->Name = L"enableBackgroundToolStripMenuItem";
			this->enableBackgroundToolStripMenuItem->Size = System::Drawing::Size(186, 22);
			this->enableBackgroundToolStripMenuItem->Tag = L"1";
			this->enableBackgroundToolStripMenuItem->Text = L"Enable Background";
			this->enableBackgroundToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::enableBackgroundToolStripMenuItem_Click);
			// 
			// disableBackgroundToolStripMenuItem
			// 
			this->disableBackgroundToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->disableBackgroundToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->disableBackgroundToolStripMenuItem->Name = L"disableBackgroundToolStripMenuItem";
			this->disableBackgroundToolStripMenuItem->Size = System::Drawing::Size(186, 22);
			this->disableBackgroundToolStripMenuItem->Tag = L"0";
			this->disableBackgroundToolStripMenuItem->Text = L"Disable Background";
			this->disableBackgroundToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::enableBackgroundToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(238, 6);
			// 
			// changeLineColorsToolStripMenuItem
			// 
			this->changeLineColorsToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->changeLineColorsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->selectedColorToolStripMenuItem1,
					this->passiveColorToolStripMenuItem1
			});
			this->changeLineColorsToolStripMenuItem->Enabled = false;
			this->changeLineColorsToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->changeLineColorsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->changeLineColorsToolStripMenuItem->Name = L"changeLineColorsToolStripMenuItem";
			this->changeLineColorsToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->changeLineColorsToolStripMenuItem->Text = L"Change Line Colors";
			// 
			// selectedColorToolStripMenuItem1
			// 
			this->selectedColorToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->selectedColorToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->selectedColorToolStripMenuItem1->Name = L"selectedColorToolStripMenuItem1";
			this->selectedColorToolStripMenuItem1->Size = System::Drawing::Size(155, 22);
			this->selectedColorToolStripMenuItem1->Text = L"Selected Color";
			this->selectedColorToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::selectedColorToolStripMenuItem1_Click);
			// 
			// passiveColorToolStripMenuItem1
			// 
			this->passiveColorToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->passiveColorToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->passiveColorToolStripMenuItem1->Name = L"passiveColorToolStripMenuItem1";
			this->passiveColorToolStripMenuItem1->Size = System::Drawing::Size(155, 22);
			this->passiveColorToolStripMenuItem1->Text = L"Passive Color";
			this->passiveColorToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::passiveColorToolStripMenuItem1_Click);
			// 
			// changeROIColorsToolStripMenuItem
			// 
			this->changeROIColorsToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->changeROIColorsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->selectedColorToolStripMenuItem,
					this->passiveColorToolStripMenuItem
			});
			this->changeROIColorsToolStripMenuItem->Enabled = false;
			this->changeROIColorsToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->changeROIColorsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->changeROIColorsToolStripMenuItem->Name = L"changeROIColorsToolStripMenuItem";
			this->changeROIColorsToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->changeROIColorsToolStripMenuItem->Text = L"Change ROI Colors";
			// 
			// selectedColorToolStripMenuItem
			// 
			this->selectedColorToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->selectedColorToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->selectedColorToolStripMenuItem->Name = L"selectedColorToolStripMenuItem";
			this->selectedColorToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->selectedColorToolStripMenuItem->Text = L"Selected Color";
			this->selectedColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::selectedColorToolStripMenuItem_Click);
			// 
			// passiveColorToolStripMenuItem
			// 
			this->passiveColorToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->passiveColorToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->passiveColorToolStripMenuItem->Name = L"passiveColorToolStripMenuItem";
			this->passiveColorToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->passiveColorToolStripMenuItem->Text = L"Passive Color";
			this->passiveColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::passiveColorToolStripMenuItem_Click);
			// 
			// changeLabelColorToolStripMenuItem
			// 
			this->changeLabelColorToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->changeLabelColorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->changeAllLabelsToolStripMenuItem,
					this->maxLabelToolStripMenuItem, this->minLabelColorToolStripMenuItem, this->centerLabelColorToolStripMenuItem, this->labelSeletedColorToolStripMenuItem,
					this->labelPassiveColorToolStripMenuItem
			});
			this->changeLabelColorToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->changeLabelColorToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->changeLabelColorToolStripMenuItem->Name = L"changeLabelColorToolStripMenuItem";
			this->changeLabelColorToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->changeLabelColorToolStripMenuItem->Text = L"Change Crosshair Colors";
			// 
			// changeAllLabelsToolStripMenuItem
			// 
			this->changeAllLabelsToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->changeAllLabelsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->changeAllLabelsToolStripMenuItem->Name = L"changeAllLabelsToolStripMenuItem";
			this->changeAllLabelsToolStripMenuItem->Size = System::Drawing::Size(243, 22);
			this->changeAllLabelsToolStripMenuItem->Text = L"Change All Crosshair";
			this->changeAllLabelsToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::changeAllLabelsToolStripMenuItem_Click);
			// 
			// maxLabelToolStripMenuItem
			// 
			this->maxLabelToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->maxLabelToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->maxLabelToolStripMenuItem->Name = L"maxLabelToolStripMenuItem";
			this->maxLabelToolStripMenuItem->Size = System::Drawing::Size(243, 22);
			this->maxLabelToolStripMenuItem->Text = L"Max Crosshair Color";
			this->maxLabelToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::maxLabelToolStripMenuItem_Click);
			// 
			// minLabelColorToolStripMenuItem
			// 
			this->minLabelColorToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->minLabelColorToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->minLabelColorToolStripMenuItem->Name = L"minLabelColorToolStripMenuItem";
			this->minLabelColorToolStripMenuItem->Size = System::Drawing::Size(243, 22);
			this->minLabelColorToolStripMenuItem->Text = L"Min Crosshair Color";
			this->minLabelColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::minLabelColorToolStripMenuItem_Click);
			// 
			// centerLabelColorToolStripMenuItem
			// 
			this->centerLabelColorToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->centerLabelColorToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->centerLabelColorToolStripMenuItem->Name = L"centerLabelColorToolStripMenuItem";
			this->centerLabelColorToolStripMenuItem->Size = System::Drawing::Size(243, 22);
			this->centerLabelColorToolStripMenuItem->Text = L"Center Crosshair Color";
			this->centerLabelColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::centerLabelColorToolStripMenuItem_Click);
			// 
			// labelSeletedColorToolStripMenuItem
			// 
			this->labelSeletedColorToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->labelSeletedColorToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->labelSeletedColorToolStripMenuItem->Name = L"labelSeletedColorToolStripMenuItem";
			this->labelSeletedColorToolStripMenuItem->Size = System::Drawing::Size(243, 22);
			this->labelSeletedColorToolStripMenuItem->Text = L"Temp Crosshair Seleted Color";
			this->labelSeletedColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::labelSeletedColorToolStripMenuItem_Click);
			// 
			// labelPassiveColorToolStripMenuItem
			// 
			this->labelPassiveColorToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->labelPassiveColorToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->labelPassiveColorToolStripMenuItem->Name = L"labelPassiveColorToolStripMenuItem";
			this->labelPassiveColorToolStripMenuItem->Size = System::Drawing::Size(243, 22);
			this->labelPassiveColorToolStripMenuItem->Text = L"Temp Crosshair Passive Color";
			this->labelPassiveColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::labelPassiveColorToolStripMenuItem_Click);
			// 
			// changeLabelColorsToolStripMenuItem
			// 
			this->changeLabelColorsToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->changeLabelColorsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->changeLabelColorsToolStripMenuItem->Name = L"changeLabelColorsToolStripMenuItem";
			this->changeLabelColorsToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->changeLabelColorsToolStripMenuItem->Text = L"Change Label Colors";
			this->changeLabelColorsToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::changeLabelColorsToolStripMenuItem_Click);
			// 
			// changeLabelBackgroundColorToolStripMenuItem
			// 
			this->changeLabelBackgroundColorToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->changeLabelBackgroundColorToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->changeLabelBackgroundColorToolStripMenuItem->Name = L"changeLabelBackgroundColorToolStripMenuItem";
			this->changeLabelBackgroundColorToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->changeLabelBackgroundColorToolStripMenuItem->Text = L"Change Label Background Color";
			this->changeLabelBackgroundColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::changeLabelBackgroundColorToolStripMenuItem_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(238, 6);
			// 
			// changeZOrderToolStripMenuItem
			// 
			this->changeZOrderToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->changeZOrderToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->rOIsToolStripMenuItem,
					this->rOIBringToFrontToolStripMenuItem, this->tempMeasurementsToolStripMenuItem, this->bringToFrontToolStripMenuItem, this->spectrumLinesToolStripMenuItem,
					this->bringToFrontToolStripMenuItem1
			});
			this->changeZOrderToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->changeZOrderToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->changeZOrderToolStripMenuItem->Name = L"changeZOrderToolStripMenuItem";
			this->changeZOrderToolStripMenuItem->Size = System::Drawing::Size(241, 22);
			this->changeZOrderToolStripMenuItem->Text = L"Change Drawing Order";
			// 
			// rOIsToolStripMenuItem
			// 
			this->rOIsToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOIsToolStripMenuItem->Enabled = false;
			this->rOIsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOIsToolStripMenuItem->Name = L"rOIsToolStripMenuItem";
			this->rOIsToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->rOIsToolStripMenuItem->Text = L"ROI Boxes:";
			// 
			// rOIBringToFrontToolStripMenuItem
			// 
			this->rOIBringToFrontToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOIBringToFrontToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOIBringToFrontToolStripMenuItem->Name = L"rOIBringToFrontToolStripMenuItem";
			this->rOIBringToFrontToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->rOIBringToFrontToolStripMenuItem->Text = L"Bring To Front";
			this->rOIBringToFrontToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::rOIBringToFrontToolStripMenuItem_Click);
			// 
			// tempMeasurementsToolStripMenuItem
			// 
			this->tempMeasurementsToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->tempMeasurementsToolStripMenuItem->Enabled = false;
			this->tempMeasurementsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->tempMeasurementsToolStripMenuItem->Name = L"tempMeasurementsToolStripMenuItem";
			this->tempMeasurementsToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->tempMeasurementsToolStripMenuItem->Text = L"Temp Measurements:";
			// 
			// bringToFrontToolStripMenuItem
			// 
			this->bringToFrontToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->bringToFrontToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->bringToFrontToolStripMenuItem->Name = L"bringToFrontToolStripMenuItem";
			this->bringToFrontToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->bringToFrontToolStripMenuItem->Text = L"Bring To Front";
			this->bringToFrontToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::bringToFrontToolStripMenuItem_Click);
			// 
			// spectrumLinesToolStripMenuItem
			// 
			this->spectrumLinesToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->spectrumLinesToolStripMenuItem->Enabled = false;
			this->spectrumLinesToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->spectrumLinesToolStripMenuItem->Name = L"spectrumLinesToolStripMenuItem";
			this->spectrumLinesToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->spectrumLinesToolStripMenuItem->Text = L"Spectrum Lines:";
			// 
			// bringToFrontToolStripMenuItem1
			// 
			this->bringToFrontToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->bringToFrontToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->bringToFrontToolStripMenuItem1->Name = L"bringToFrontToolStripMenuItem1";
			this->bringToFrontToolStripMenuItem1->Size = System::Drawing::Size(194, 22);
			this->bringToFrontToolStripMenuItem1->Text = L"Bring To Front";
			this->bringToFrontToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::bringToFrontToolStripMenuItem1_Click);
			// 
			// LiveViewZoomPanel
			// 
			this->LiveViewZoomPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->LiveViewZoomPanel->Location = System::Drawing::Point(0, 0);
			this->LiveViewZoomPanel->Name = L"LiveViewZoomPanel";
			this->LiveViewZoomPanel->Size = System::Drawing::Size(96, 100);
			this->LiveViewZoomPanel->TabIndex = 0;
			// 
			// LiveViewHistogramPanel
			// 
			this->LiveViewHistogramPanel->ContextMenuStrip = this->HistPanelContextStrip;
			this->LiveViewHistogramPanel->Dock = System::Windows::Forms::DockStyle::Right;
			this->LiveViewHistogramPanel->Location = System::Drawing::Point(1230, 0);
			this->LiveViewHistogramPanel->Margin = System::Windows::Forms::Padding(0);
			this->LiveViewHistogramPanel->Name = L"LiveViewHistogramPanel";
			this->LiveViewHistogramPanel->Size = System::Drawing::Size(100, 837);
			this->LiveViewHistogramPanel->TabIndex = 0;
			this->LiveViewHistogramPanel->Visible = false;
			// 
			// HistPanelContextStrip
			// 
			this->HistPanelContextStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->HistPanelContextStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->liveViewHistogramToolStripMenuItem,
					this->toolStripSeparator7, this->histogramSourceToolStripMenuItem, this->HistNmbOfBinsToolStripMenuItem, this->toolStripSeparator9,
					this->mimicColorBarPaletteToolStripMenuItem, this->useDualColorPaletteToolStripMenuItem
			});
			this->HistPanelContextStrip->Name = L"HistPanelContextStrip";
			this->HistPanelContextStrip->ShowImageMargin = false;
			this->HistPanelContextStrip->Size = System::Drawing::Size(207, 126);
			// 
			// liveViewHistogramToolStripMenuItem
			// 
			this->liveViewHistogramToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->liveViewHistogramToolStripMenuItem->Enabled = false;
			this->liveViewHistogramToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->liveViewHistogramToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->liveViewHistogramToolStripMenuItem->Name = L"liveViewHistogramToolStripMenuItem";
			this->liveViewHistogramToolStripMenuItem->Size = System::Drawing::Size(206, 22);
			this->liveViewHistogramToolStripMenuItem->Text = L"Live View Histogram:";
			// 
			// toolStripSeparator7
			// 
			this->toolStripSeparator7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripSeparator7->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator7->Name = L"toolStripSeparator7";
			this->toolStripSeparator7->Size = System::Drawing::Size(203, 6);
			// 
			// histogramSourceToolStripMenuItem
			// 
			this->histogramSourceToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->histogramSourceToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(17) {
				this->line1SpectrumToolStripMenuItem,
					this->line2SpectrumToolStripMenuItem, this->line3SpectrumToolStripMenuItem, this->line4SpectrumToolStripMenuItem, this->line5SpectrumToolStripMenuItem,
					this->rOI1AreaToolStripMenuItem, this->rOI2AreaToolStripMenuItem, this->rOI3AreaToolStripMenuItem, this->rOI4AreaToolStripMenuItem,
					this->rOI5AreaToolStripMenuItem, this->rOI6AreaToolStripMenuItem, this->rOI7AreaToolStripMenuItem, this->rOI8AreaToolStripMenuItem,
					this->rOI9AreaToolStripMenuItem, this->rOI10AreaToolStripMenuItem, this->liveViewToolStripMenuItem, this->toolStripMenuItem1
			});
			this->histogramSourceToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->histogramSourceToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->histogramSourceToolStripMenuItem->Name = L"histogramSourceToolStripMenuItem";
			this->histogramSourceToolStripMenuItem->Size = System::Drawing::Size(206, 22);
			this->histogramSourceToolStripMenuItem->Text = L"Histogram Source";
			// 
			// line1SpectrumToolStripMenuItem
			// 
			this->line1SpectrumToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line1SpectrumToolStripMenuItem->Enabled = false;
			this->line1SpectrumToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line1SpectrumToolStripMenuItem->Name = L"line1SpectrumToolStripMenuItem";
			this->line1SpectrumToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->line1SpectrumToolStripMenuItem->Tag = L"0";
			this->line1SpectrumToolStripMenuItem->Text = L"Line 1 Spectrum";
			this->line1SpectrumToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// line2SpectrumToolStripMenuItem
			// 
			this->line2SpectrumToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line2SpectrumToolStripMenuItem->Enabled = false;
			this->line2SpectrumToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line2SpectrumToolStripMenuItem->Name = L"line2SpectrumToolStripMenuItem";
			this->line2SpectrumToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->line2SpectrumToolStripMenuItem->Tag = L"1";
			this->line2SpectrumToolStripMenuItem->Text = L"Line 2 Spectrum";
			this->line2SpectrumToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// line3SpectrumToolStripMenuItem
			// 
			this->line3SpectrumToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line3SpectrumToolStripMenuItem->Enabled = false;
			this->line3SpectrumToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line3SpectrumToolStripMenuItem->Name = L"line3SpectrumToolStripMenuItem";
			this->line3SpectrumToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->line3SpectrumToolStripMenuItem->Tag = L"2";
			this->line3SpectrumToolStripMenuItem->Text = L"Line 3 Spectrum";
			this->line3SpectrumToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// line4SpectrumToolStripMenuItem
			// 
			this->line4SpectrumToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line4SpectrumToolStripMenuItem->Enabled = false;
			this->line4SpectrumToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line4SpectrumToolStripMenuItem->Name = L"line4SpectrumToolStripMenuItem";
			this->line4SpectrumToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->line4SpectrumToolStripMenuItem->Tag = L"3";
			this->line4SpectrumToolStripMenuItem->Text = L"Line 4 Spectrum";
			this->line4SpectrumToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// line5SpectrumToolStripMenuItem
			// 
			this->line5SpectrumToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->line5SpectrumToolStripMenuItem->Enabled = false;
			this->line5SpectrumToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->line5SpectrumToolStripMenuItem->Name = L"line5SpectrumToolStripMenuItem";
			this->line5SpectrumToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->line5SpectrumToolStripMenuItem->Tag = L"4";
			this->line5SpectrumToolStripMenuItem->Text = L"Line 5 Spectrum";
			this->line5SpectrumToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI1AreaToolStripMenuItem
			// 
			this->rOI1AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI1AreaToolStripMenuItem->Enabled = false;
			this->rOI1AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI1AreaToolStripMenuItem->Name = L"rOI1AreaToolStripMenuItem";
			this->rOI1AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI1AreaToolStripMenuItem->Tag = L"10";
			this->rOI1AreaToolStripMenuItem->Text = L"ROI 1 Area";
			this->rOI1AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI2AreaToolStripMenuItem
			// 
			this->rOI2AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI2AreaToolStripMenuItem->Enabled = false;
			this->rOI2AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI2AreaToolStripMenuItem->Name = L"rOI2AreaToolStripMenuItem";
			this->rOI2AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI2AreaToolStripMenuItem->Tag = L"11";
			this->rOI2AreaToolStripMenuItem->Text = L"ROI 2 Area";
			this->rOI2AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI3AreaToolStripMenuItem
			// 
			this->rOI3AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI3AreaToolStripMenuItem->Enabled = false;
			this->rOI3AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI3AreaToolStripMenuItem->Name = L"rOI3AreaToolStripMenuItem";
			this->rOI3AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI3AreaToolStripMenuItem->Tag = L"12";
			this->rOI3AreaToolStripMenuItem->Text = L"ROI 3 Area";
			this->rOI3AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI4AreaToolStripMenuItem
			// 
			this->rOI4AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI4AreaToolStripMenuItem->Enabled = false;
			this->rOI4AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI4AreaToolStripMenuItem->Name = L"rOI4AreaToolStripMenuItem";
			this->rOI4AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI4AreaToolStripMenuItem->Tag = L"13";
			this->rOI4AreaToolStripMenuItem->Text = L"ROI 4 Area";
			this->rOI4AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI5AreaToolStripMenuItem
			// 
			this->rOI5AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI5AreaToolStripMenuItem->Enabled = false;
			this->rOI5AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI5AreaToolStripMenuItem->Name = L"rOI5AreaToolStripMenuItem";
			this->rOI5AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI5AreaToolStripMenuItem->Tag = L"14";
			this->rOI5AreaToolStripMenuItem->Text = L"ROI 5 Area";
			this->rOI5AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI6AreaToolStripMenuItem
			// 
			this->rOI6AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI6AreaToolStripMenuItem->Enabled = false;
			this->rOI6AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI6AreaToolStripMenuItem->Name = L"rOI6AreaToolStripMenuItem";
			this->rOI6AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI6AreaToolStripMenuItem->Tag = L"15";
			this->rOI6AreaToolStripMenuItem->Text = L"ROI 6 Area";
			this->rOI6AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI7AreaToolStripMenuItem
			// 
			this->rOI7AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI7AreaToolStripMenuItem->Enabled = false;
			this->rOI7AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI7AreaToolStripMenuItem->Name = L"rOI7AreaToolStripMenuItem";
			this->rOI7AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI7AreaToolStripMenuItem->Tag = L"16";
			this->rOI7AreaToolStripMenuItem->Text = L"ROI 7 Area";
			this->rOI7AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI8AreaToolStripMenuItem
			// 
			this->rOI8AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI8AreaToolStripMenuItem->Enabled = false;
			this->rOI8AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI8AreaToolStripMenuItem->Name = L"rOI8AreaToolStripMenuItem";
			this->rOI8AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI8AreaToolStripMenuItem->Tag = L"17";
			this->rOI8AreaToolStripMenuItem->Text = L"ROI 8 Area";
			this->rOI8AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI9AreaToolStripMenuItem
			// 
			this->rOI9AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI9AreaToolStripMenuItem->Enabled = false;
			this->rOI9AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI9AreaToolStripMenuItem->Name = L"rOI9AreaToolStripMenuItem";
			this->rOI9AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI9AreaToolStripMenuItem->Tag = L"18";
			this->rOI9AreaToolStripMenuItem->Text = L"ROI 9 Area";
			this->rOI9AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// rOI10AreaToolStripMenuItem
			// 
			this->rOI10AreaToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->rOI10AreaToolStripMenuItem->Enabled = false;
			this->rOI10AreaToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->rOI10AreaToolStripMenuItem->Name = L"rOI10AreaToolStripMenuItem";
			this->rOI10AreaToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->rOI10AreaToolStripMenuItem->Tag = L"19";
			this->rOI10AreaToolStripMenuItem->Text = L"ROI 10 Area";
			this->rOI10AreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// liveViewToolStripMenuItem
			// 
			this->liveViewToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->liveViewToolStripMenuItem->Enabled = false;
			this->liveViewToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->liveViewToolStripMenuItem->Name = L"liveViewToolStripMenuItem";
			this->liveViewToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->liveViewToolStripMenuItem->Tag = L"6";
			this->liveViewToolStripMenuItem->Text = L"Zoom Window";
			this->liveViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(181, 22);
			this->toolStripMenuItem1->Tag = L"5";
			this->toolStripMenuItem1->Text = L"Live View Spectrum";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::liveViewToolStripMenuItem_Click);
			// 
			// HistNmbOfBinsToolStripMenuItem
			// 
			this->HistNmbOfBinsToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->HistNmbOfBinsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->toolStripMenuItem11,
					this->toolStripMenuItem12, this->toolStripMenuItem13, this->toolStripMenuItem14, this->toolStripMenuItem15, this->toolStripMenuItem16,
					this->toolStripMenuItem17, this->toolStripMenuItem18
			});
			this->HistNmbOfBinsToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->HistNmbOfBinsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->HistNmbOfBinsToolStripMenuItem->Name = L"HistNmbOfBinsToolStripMenuItem";
			this->HistNmbOfBinsToolStripMenuItem->Size = System::Drawing::Size(206, 22);
			this->HistNmbOfBinsToolStripMenuItem->Text = L"Number Of Bins";
			// 
			// toolStripMenuItem11
			// 
			this->toolStripMenuItem11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem11->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem11->Name = L"toolStripMenuItem11";
			this->toolStripMenuItem11->Size = System::Drawing::Size(123, 22);
			this->toolStripMenuItem11->Tag = L"512";
			this->toolStripMenuItem11->Text = L"512 Bins";
			this->toolStripMenuItem11->Click += gcnew System::EventHandler(this, &LiveViewStream::HistogramNumberOfBinsContextMenu_Click);
			// 
			// toolStripMenuItem12
			// 
			this->toolStripMenuItem12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem12->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem12->Name = L"toolStripMenuItem12";
			this->toolStripMenuItem12->Size = System::Drawing::Size(123, 22);
			this->toolStripMenuItem12->Tag = L"256";
			this->toolStripMenuItem12->Text = L"256 Bins";
			this->toolStripMenuItem12->Click += gcnew System::EventHandler(this, &LiveViewStream::HistogramNumberOfBinsContextMenu_Click);
			// 
			// toolStripMenuItem13
			// 
			this->toolStripMenuItem13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem13->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem13->Name = L"toolStripMenuItem13";
			this->toolStripMenuItem13->Size = System::Drawing::Size(123, 22);
			this->toolStripMenuItem13->Tag = L"128";
			this->toolStripMenuItem13->Text = L"128 Bins";
			this->toolStripMenuItem13->Click += gcnew System::EventHandler(this, &LiveViewStream::HistogramNumberOfBinsContextMenu_Click);
			// 
			// toolStripMenuItem14
			// 
			this->toolStripMenuItem14->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem14->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem14->Name = L"toolStripMenuItem14";
			this->toolStripMenuItem14->Size = System::Drawing::Size(123, 22);
			this->toolStripMenuItem14->Tag = L"64";
			this->toolStripMenuItem14->Text = L"64 Bins";
			this->toolStripMenuItem14->Click += gcnew System::EventHandler(this, &LiveViewStream::HistogramNumberOfBinsContextMenu_Click);
			// 
			// toolStripMenuItem15
			// 
			this->toolStripMenuItem15->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem15->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem15->Name = L"toolStripMenuItem15";
			this->toolStripMenuItem15->Size = System::Drawing::Size(123, 22);
			this->toolStripMenuItem15->Tag = L"32";
			this->toolStripMenuItem15->Text = L"32 Bins";
			this->toolStripMenuItem15->Click += gcnew System::EventHandler(this, &LiveViewStream::HistogramNumberOfBinsContextMenu_Click);
			// 
			// toolStripMenuItem16
			// 
			this->toolStripMenuItem16->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem16->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem16->Name = L"toolStripMenuItem16";
			this->toolStripMenuItem16->Size = System::Drawing::Size(123, 22);
			this->toolStripMenuItem16->Tag = L"16";
			this->toolStripMenuItem16->Text = L"16 Bins";
			this->toolStripMenuItem16->Click += gcnew System::EventHandler(this, &LiveViewStream::HistogramNumberOfBinsContextMenu_Click);
			// 
			// toolStripMenuItem17
			// 
			this->toolStripMenuItem17->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem17->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem17->Name = L"toolStripMenuItem17";
			this->toolStripMenuItem17->Size = System::Drawing::Size(123, 22);
			this->toolStripMenuItem17->Tag = L"8";
			this->toolStripMenuItem17->Text = L"8 Bins";
			this->toolStripMenuItem17->Click += gcnew System::EventHandler(this, &LiveViewStream::HistogramNumberOfBinsContextMenu_Click);
			// 
			// toolStripMenuItem18
			// 
			this->toolStripMenuItem18->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem18->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem18->Name = L"toolStripMenuItem18";
			this->toolStripMenuItem18->Size = System::Drawing::Size(123, 22);
			this->toolStripMenuItem18->Tag = L"4";
			this->toolStripMenuItem18->Text = L"4 Bins";
			this->toolStripMenuItem18->Click += gcnew System::EventHandler(this, &LiveViewStream::HistogramNumberOfBinsContextMenu_Click);
			// 
			// toolStripSeparator9
			// 
			this->toolStripSeparator9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripSeparator9->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator9->Name = L"toolStripSeparator9";
			this->toolStripSeparator9->Size = System::Drawing::Size(203, 6);
			// 
			// mimicColorBarPaletteToolStripMenuItem
			// 
			this->mimicColorBarPaletteToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->mimicColorBarPaletteToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ShowRangedPaletteToolStripMenuItem1,
					this->showFullPaletteToolStripMenuItem
			});
			this->mimicColorBarPaletteToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->mimicColorBarPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->mimicColorBarPaletteToolStripMenuItem->Name = L"mimicColorBarPaletteToolStripMenuItem";
			this->mimicColorBarPaletteToolStripMenuItem->Size = System::Drawing::Size(206, 22);
			this->mimicColorBarPaletteToolStripMenuItem->Text = L"Allow Palette Range Change";
			// 
			// ShowRangedPaletteToolStripMenuItem1
			// 
			this->ShowRangedPaletteToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ShowRangedPaletteToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->ShowRangedPaletteToolStripMenuItem1->Name = L"ShowRangedPaletteToolStripMenuItem1";
			this->ShowRangedPaletteToolStripMenuItem1->Size = System::Drawing::Size(193, 22);
			this->ShowRangedPaletteToolStripMenuItem1->Text = L"Show Ranged Palette";
			this->ShowRangedPaletteToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::showRangedPaletteToolStripMenuItem1_Click);
			// 
			// showFullPaletteToolStripMenuItem
			// 
			this->showFullPaletteToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->showFullPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->showFullPaletteToolStripMenuItem->Name = L"showFullPaletteToolStripMenuItem";
			this->showFullPaletteToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->showFullPaletteToolStripMenuItem->Text = L"Show Full Palette";
			this->showFullPaletteToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::showFullPaletteToolStripMenuItem_Click);
			// 
			// useDualColorPaletteToolStripMenuItem
			// 
			this->useDualColorPaletteToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->useDualColorPaletteToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->useLiveViewPaletteToolStripMenuItem,
					this->useDualPaletteToolStripMenuItem
			});
			this->useDualColorPaletteToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->useDualColorPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->useDualColorPaletteToolStripMenuItem->Name = L"useDualColorPaletteToolStripMenuItem";
			this->useDualColorPaletteToolStripMenuItem->Size = System::Drawing::Size(206, 22);
			this->useDualColorPaletteToolStripMenuItem->Text = L"Current Color Palette";
			// 
			// useLiveViewPaletteToolStripMenuItem
			// 
			this->useLiveViewPaletteToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->useLiveViewPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->useLiveViewPaletteToolStripMenuItem->Name = L"useLiveViewPaletteToolStripMenuItem";
			this->useLiveViewPaletteToolStripMenuItem->Size = System::Drawing::Size(192, 22);
			this->useLiveViewPaletteToolStripMenuItem->Text = L"Use Live View Palette";
			this->useLiveViewPaletteToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::useLiveViewPaletteToolStripMenuItem_Click);
			// 
			// useDualPaletteToolStripMenuItem
			// 
			this->useDualPaletteToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->useDualPaletteToolStripMenuItem->Enabled = false;
			this->useDualPaletteToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->useDualPaletteToolStripMenuItem->Name = L"useDualPaletteToolStripMenuItem";
			this->useDualPaletteToolStripMenuItem->Size = System::Drawing::Size(192, 22);
			this->useDualPaletteToolStripMenuItem->Text = L"Use Dual Palette";
			this->useDualPaletteToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::useDualPaletteToolStripMenuItem_Click);
			// 
			// LiveViewToolsPanel
			// 
			this->LiveViewToolsPanel->AutoScroll = true;
			this->LiveViewToolsPanel->AutoScrollMinSize = System::Drawing::Size(150, 835);
			this->LiveViewToolsPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->LiveViewToolsPanel->Location = System::Drawing::Point(0, 0);
			this->LiveViewToolsPanel->Margin = System::Windows::Forms::Padding(0);
			this->LiveViewToolsPanel->Name = L"LiveViewToolsPanel";
			this->LiveViewToolsPanel->Size = System::Drawing::Size(172, 837);
			this->LiveViewToolsPanel->TabIndex = 11;
			// 
			// ColorBarMainPanel
			// 
			this->ColorBarMainPanel->ContextMenuStrip = this->ColorBarContextStrip;
			this->ColorBarMainPanel->Dock = System::Windows::Forms::DockStyle::Right;
			this->ColorBarMainPanel->Location = System::Drawing::Point(1330, 0);
			this->ColorBarMainPanel->Margin = System::Windows::Forms::Padding(0);
			this->ColorBarMainPanel->Name = L"ColorBarMainPanel";
			this->ColorBarMainPanel->Size = System::Drawing::Size(171, 837);
			this->ColorBarMainPanel->TabIndex = 0;
			// 
			// ColorBarContextStrip
			// 
			this->ColorBarContextStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ColorBarContextStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(13) {
				this->testToolStripMenuItem,
					this->toolStripSeparator4, this->temperatureRangeToolStripMenuItem, this->enableFullPaletteRangeAdjustmentToolStripMenuItem,
					this->toolStripSeparator11, this->colorBarTemperatureTicksToolStripMenuItem, this->toolStripSeparator13, this->setColorBarRangesToolStripMenuItem,
					this->mouseWheelStedSizeToolStripMenuItem, this->toolStripSeparator12, this->trackCenterTemperatureToolStripMenuItem, this->adjustLivePaletteRangeToolStripMenuItem,
					this->adjustDualPaletteRangeToolStripMenuItem
			});
			this->ColorBarContextStrip->Name = L"ColorBarContextStrip";
			this->ColorBarContextStrip->ShowImageMargin = false;
			this->ColorBarContextStrip->Size = System::Drawing::Size(215, 248);
			// 
			// testToolStripMenuItem
			// 
			this->testToolStripMenuItem->Enabled = false;
			this->testToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->testToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->testToolStripMenuItem->Name = L"testToolStripMenuItem";
			this->testToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->testToolStripMenuItem->Text = L"Live View ColorBar:";
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(211, 6);
			// 
			// temperatureRangeToolStripMenuItem
			// 
			this->temperatureRangeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->autoToolStripMenuItem,
					this->manualToolStripMenuItem, this->manualHighRangeToolStripMenuItem, this->manualLowRangeToolStripMenuItem
			});
			this->temperatureRangeToolStripMenuItem->Enabled = false;
			this->temperatureRangeToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->temperatureRangeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->temperatureRangeToolStripMenuItem->Name = L"temperatureRangeToolStripMenuItem";
			this->temperatureRangeToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->temperatureRangeToolStripMenuItem->Text = L"ColorBar Range Mode";
			// 
			// autoToolStripMenuItem
			// 
			this->autoToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->autoToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->autoToolStripMenuItem->Name = L"autoToolStripMenuItem";
			this->autoToolStripMenuItem->Size = System::Drawing::Size(183, 22);
			this->autoToolStripMenuItem->Text = L"Auto";
			this->autoToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::autoToolStripMenuItem_Click);
			// 
			// manualToolStripMenuItem
			// 
			this->manualToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->manualToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->manualToolStripMenuItem->Name = L"manualToolStripMenuItem";
			this->manualToolStripMenuItem->Size = System::Drawing::Size(183, 22);
			this->manualToolStripMenuItem->Text = L"Manual";
			this->manualToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::manualToolStripMenuItem_Click);
			// 
			// enableFullPaletteRangeAdjustmentToolStripMenuItem
			// 
			this->enableFullPaletteRangeAdjustmentToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->enableToolStripMenuItem1,
					this->disableToolStripMenuItem1
			});
			this->enableFullPaletteRangeAdjustmentToolStripMenuItem->Enabled = false;
			this->enableFullPaletteRangeAdjustmentToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->enableFullPaletteRangeAdjustmentToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->enableFullPaletteRangeAdjustmentToolStripMenuItem->Name = L"enableFullPaletteRangeAdjustmentToolStripMenuItem";
			this->enableFullPaletteRangeAdjustmentToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->enableFullPaletteRangeAdjustmentToolStripMenuItem->Text = L"Full Palette Range Adjustment";
			// 
			// enableToolStripMenuItem1
			// 
			this->enableToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->enableToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->enableToolStripMenuItem1->Name = L"enableToolStripMenuItem1";
			this->enableToolStripMenuItem1->Size = System::Drawing::Size(117, 22);
			this->enableToolStripMenuItem1->Tag = L"1";
			this->enableToolStripMenuItem1->Text = L"Enable";
			this->enableToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::enableToolStripMenuItem1_Click);
			// 
			// disableToolStripMenuItem1
			// 
			this->disableToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->disableToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->disableToolStripMenuItem1->Name = L"disableToolStripMenuItem1";
			this->disableToolStripMenuItem1->Size = System::Drawing::Size(117, 22);
			this->disableToolStripMenuItem1->Tag = L"0";
			this->disableToolStripMenuItem1->Text = L"Disable";
			this->disableToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::enableToolStripMenuItem1_Click);
			// 
			// toolStripSeparator11
			// 
			this->toolStripSeparator11->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator11->Name = L"toolStripSeparator11";
			this->toolStripSeparator11->Size = System::Drawing::Size(211, 6);
			// 
			// colorBarTemperatureTicksToolStripMenuItem
			// 
			this->colorBarTemperatureTicksToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ticksToolStripMenuItem,
					this->ticksToolStripMenuItem1, this->ticksToolStripMenuItem2, this->ticksToolStripMenuItem3
			});
			this->colorBarTemperatureTicksToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->colorBarTemperatureTicksToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->colorBarTemperatureTicksToolStripMenuItem->Name = L"colorBarTemperatureTicksToolStripMenuItem";
			this->colorBarTemperatureTicksToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->colorBarTemperatureTicksToolStripMenuItem->Text = L"ColorBar Temperature Ticks";
			// 
			// ticksToolStripMenuItem
			// 
			this->ticksToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem->Name = L"ticksToolStripMenuItem";
			this->ticksToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem->Tag = L"1";
			this->ticksToolStripMenuItem->Text = L"5 Ticks";
			this->ticksToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::ticksToolStripMenuItem_Click);
			// 
			// ticksToolStripMenuItem1
			// 
			this->ticksToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem1->Name = L"ticksToolStripMenuItem1";
			this->ticksToolStripMenuItem1->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem1->Tag = L"2";
			this->ticksToolStripMenuItem1->Text = L"10 Ticks";
			this->ticksToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::ticksToolStripMenuItem_Click);
			// 
			// ticksToolStripMenuItem2
			// 
			this->ticksToolStripMenuItem2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem2->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem2->Name = L"ticksToolStripMenuItem2";
			this->ticksToolStripMenuItem2->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem2->Tag = L"3";
			this->ticksToolStripMenuItem2->Text = L"15 Ticks";
			this->ticksToolStripMenuItem2->Click += gcnew System::EventHandler(this, &LiveViewStream::ticksToolStripMenuItem_Click);
			// 
			// ticksToolStripMenuItem3
			// 
			this->ticksToolStripMenuItem3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem3->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem3->Name = L"ticksToolStripMenuItem3";
			this->ticksToolStripMenuItem3->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem3->Tag = L"4";
			this->ticksToolStripMenuItem3->Text = L"20 Ticks";
			this->ticksToolStripMenuItem3->Click += gcnew System::EventHandler(this, &LiveViewStream::ticksToolStripMenuItem_Click);
			// 
			// toolStripSeparator13
			// 
			this->toolStripSeparator13->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator13->Name = L"toolStripSeparator13";
			this->toolStripSeparator13->Size = System::Drawing::Size(211, 6);
			// 
			// setColorBarRangesToolStripMenuItem
			// 
			this->setColorBarRangesToolStripMenuItem->Enabled = false;
			this->setColorBarRangesToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->setColorBarRangesToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->setColorBarRangesToolStripMenuItem->Name = L"setColorBarRangesToolStripMenuItem";
			this->setColorBarRangesToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->setColorBarRangesToolStripMenuItem->Text = L"Set ColorBar Temp Range";
			this->setColorBarRangesToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::setColorBarRangesToolStripMenuItem_Click);
			// 
			// mouseWheelStedSizeToolStripMenuItem
			// 
			this->mouseWheelStedSizeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->stepSize1ToolStripMenuItem,
					this->stepSize01ToolStripMenuItem, this->stepSizeToolStripMenuItem, this->stepSize05ToolStripMenuItem, this->stepSize02ToolStripMenuItem,
					this->stepSize01ToolStripMenuItem1
			});
			this->mouseWheelStedSizeToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->mouseWheelStedSizeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->mouseWheelStedSizeToolStripMenuItem->Name = L"mouseWheelStedSizeToolStripMenuItem";
			this->mouseWheelStedSizeToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->mouseWheelStedSizeToolStripMenuItem->Text = L"Mouse Wheel Temp Step Size";
			// 
			// stepSize1ToolStripMenuItem
			// 
			this->stepSize1ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->stepSize1ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->stepSize1ToolStripMenuItem->Name = L"stepSize1ToolStripMenuItem";
			this->stepSize1ToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->stepSize1ToolStripMenuItem->Tag = L"1";
			this->stepSize1ToolStripMenuItem->Text = L"Step Size: 10";
			this->stepSize1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::stepSize1ToolStripMenuItem_Click);
			// 
			// stepSize01ToolStripMenuItem
			// 
			this->stepSize01ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->stepSize01ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->stepSize01ToolStripMenuItem->Name = L"stepSize01ToolStripMenuItem";
			this->stepSize01ToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->stepSize01ToolStripMenuItem->Tag = L"2";
			this->stepSize01ToolStripMenuItem->Text = L"Step Size: 5";
			this->stepSize01ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::stepSize1ToolStripMenuItem_Click);
			// 
			// stepSizeToolStripMenuItem
			// 
			this->stepSizeToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->stepSizeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->stepSizeToolStripMenuItem->Name = L"stepSizeToolStripMenuItem";
			this->stepSizeToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->stepSizeToolStripMenuItem->Tag = L"3";
			this->stepSizeToolStripMenuItem->Text = L"Step Size: 1";
			this->stepSizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::stepSize1ToolStripMenuItem_Click);
			// 
			// stepSize05ToolStripMenuItem
			// 
			this->stepSize05ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->stepSize05ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->stepSize05ToolStripMenuItem->Name = L"stepSize05ToolStripMenuItem";
			this->stepSize05ToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->stepSize05ToolStripMenuItem->Tag = L"4";
			this->stepSize05ToolStripMenuItem->Text = L"Step Size: 0.5";
			this->stepSize05ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::stepSize1ToolStripMenuItem_Click);
			// 
			// stepSize02ToolStripMenuItem
			// 
			this->stepSize02ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->stepSize02ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->stepSize02ToolStripMenuItem->Name = L"stepSize02ToolStripMenuItem";
			this->stepSize02ToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->stepSize02ToolStripMenuItem->Tag = L"5";
			this->stepSize02ToolStripMenuItem->Text = L"Step Size: 0.2";
			this->stepSize02ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::stepSize1ToolStripMenuItem_Click);
			// 
			// stepSize01ToolStripMenuItem1
			// 
			this->stepSize01ToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->stepSize01ToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->stepSize01ToolStripMenuItem1->Name = L"stepSize01ToolStripMenuItem1";
			this->stepSize01ToolStripMenuItem1->Size = System::Drawing::Size(148, 22);
			this->stepSize01ToolStripMenuItem1->Tag = L"6";
			this->stepSize01ToolStripMenuItem1->Text = L"Step Size: 0.1";
			this->stepSize01ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &LiveViewStream::stepSize1ToolStripMenuItem_Click);
			// 
			// toolStripSeparator12
			// 
			this->toolStripSeparator12->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator12->Name = L"toolStripSeparator12";
			this->toolStripSeparator12->Size = System::Drawing::Size(211, 6);
			// 
			// trackCenterTemperatureToolStripMenuItem
			// 
			this->trackCenterTemperatureToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->enableToolStripMenuItem,
					this->disableToolStripMenuItem
			});
			this->trackCenterTemperatureToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->trackCenterTemperatureToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->trackCenterTemperatureToolStripMenuItem->Name = L"trackCenterTemperatureToolStripMenuItem";
			this->trackCenterTemperatureToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->trackCenterTemperatureToolStripMenuItem->Text = L"Track Center Temperature";
			// 
			// enableToolStripMenuItem
			// 
			this->enableToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->enableToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->enableToolStripMenuItem->Name = L"enableToolStripMenuItem";
			this->enableToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->enableToolStripMenuItem->Text = L"Enable";
			this->enableToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::enableToolStripMenuItem_Click);
			// 
			// disableToolStripMenuItem
			// 
			this->disableToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->disableToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->disableToolStripMenuItem->Name = L"disableToolStripMenuItem";
			this->disableToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->disableToolStripMenuItem->Text = L"Disable";
			this->disableToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::disableToolStripMenuItem_Click);
			// 
			// adjustLivePaletteRangeToolStripMenuItem
			// 
			this->adjustLivePaletteRangeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->enableDefaultToolStripMenuItem,
					this->disableToolStripMenuItem2
			});
			this->adjustLivePaletteRangeToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->adjustLivePaletteRangeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->adjustLivePaletteRangeToolStripMenuItem->Name = L"adjustLivePaletteRangeToolStripMenuItem";
			this->adjustLivePaletteRangeToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->adjustLivePaletteRangeToolStripMenuItem->Text = L"Adjust Live Palette Range";
			// 
			// enableDefaultToolStripMenuItem
			// 
			this->enableDefaultToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->enableDefaultToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->enableDefaultToolStripMenuItem->Name = L"enableDefaultToolStripMenuItem";
			this->enableDefaultToolStripMenuItem->Size = System::Drawing::Size(163, 22);
			this->enableDefaultToolStripMenuItem->Text = L"Enable (Default)";
			this->enableDefaultToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::enableDefaultToolStripMenuItem_Click);
			// 
			// disableToolStripMenuItem2
			// 
			this->disableToolStripMenuItem2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->disableToolStripMenuItem2->ForeColor = System::Drawing::Color::White;
			this->disableToolStripMenuItem2->Name = L"disableToolStripMenuItem2";
			this->disableToolStripMenuItem2->Size = System::Drawing::Size(163, 22);
			this->disableToolStripMenuItem2->Text = L"Disable";
			this->disableToolStripMenuItem2->Click += gcnew System::EventHandler(this, &LiveViewStream::disableToolStripMenuItem2_Click);
			// 
			// adjustDualPaletteRangeToolStripMenuItem
			// 
			this->adjustDualPaletteRangeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->enableToolStripMenuItem2,
					this->disableDefaultToolStripMenuItem
			});
			this->adjustDualPaletteRangeToolStripMenuItem->Enabled = false;
			this->adjustDualPaletteRangeToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->adjustDualPaletteRangeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->adjustDualPaletteRangeToolStripMenuItem->Name = L"adjustDualPaletteRangeToolStripMenuItem";
			this->adjustDualPaletteRangeToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->adjustDualPaletteRangeToolStripMenuItem->Text = L"Adjust Dual Palette Range";
			// 
			// enableToolStripMenuItem2
			// 
			this->enableToolStripMenuItem2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->enableToolStripMenuItem2->ForeColor = System::Drawing::Color::White;
			this->enableToolStripMenuItem2->Name = L"enableToolStripMenuItem2";
			this->enableToolStripMenuItem2->Size = System::Drawing::Size(167, 22);
			this->enableToolStripMenuItem2->Text = L"Enable";
			this->enableToolStripMenuItem2->Click += gcnew System::EventHandler(this, &LiveViewStream::enableToolStripMenuItem2_Click);
			// 
			// disableDefaultToolStripMenuItem
			// 
			this->disableDefaultToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->disableDefaultToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->disableDefaultToolStripMenuItem->Name = L"disableDefaultToolStripMenuItem";
			this->disableDefaultToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->disableDefaultToolStripMenuItem->Text = L"Disable (Default)";
			this->disableDefaultToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::disableDefaultToolStripMenuItem_Click);
			// 
			// manualLowRangeToolStripMenuItem
			// 
			this->manualLowRangeToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->manualLowRangeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->manualLowRangeToolStripMenuItem->Name = L"manualLowRangeToolStripMenuItem";
			this->manualLowRangeToolStripMenuItem->Size = System::Drawing::Size(183, 22);
			this->manualLowRangeToolStripMenuItem->Text = L"Manual Low Range";
			this->manualLowRangeToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::manualLowRangeToolStripMenuItem_Click);
			// 
			// manualHighRangeToolStripMenuItem
			// 
			this->manualHighRangeToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->manualHighRangeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->manualHighRangeToolStripMenuItem->Name = L"manualHighRangeToolStripMenuItem";
			this->manualHighRangeToolStripMenuItem->Size = System::Drawing::Size(183, 22);
			this->manualHighRangeToolStripMenuItem->Text = L"Manual High Range";
			this->manualHighRangeToolStripMenuItem->Click += gcnew System::EventHandler(this, &LiveViewStream::manualHighRangeToolStripMenuItem_Click);
			// 
			// LiveViewStream
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(1511, 847);
			this->Controls->Add(this->CompleteLiveViewPanel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"LiveViewStream";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Tag = L"LiveViewStreamGUI";
			this->Text = L"LiveViewStream";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &LiveViewStream::LiveViewStream_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &LiveViewStream::LiveViewStream_Shown);
			this->Resize += gcnew System::EventHandler(this, &LiveViewStream::LiveViewStream_Resize);
			this->CompleteLiveViewPanel->ResumeLayout(false);
			this->LiveViewMainPanel->ResumeLayout(false);
			this->StreamAndCBarPanel->ResumeLayout(false);
			this->LiveViewStreamSubPanel->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->LiveViewStreamMainPanel->ResumeLayout(false);
			this->LiveViewSplitContainer->Panel1->ResumeLayout(false);
			this->LiveViewSplitContainer->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LiveViewSplitContainer))->EndInit();
			this->LiveViewSplitContainer->ResumeLayout(false);
			this->LiveViewContextStrip->ResumeLayout(false);
			this->HistPanelContextStrip->ResumeLayout(false);
			this->ColorBarContextStrip->ResumeLayout(false);
			this->ResumeLayout(false);

		}

#pragma endregion

		// ---------------------- Opstartnings Og Nedluknings Callback Routiner ----------------------- //

		// Live View Stream Form Opstartnings Callback Routine -> 
		private: System::Void LiveViewStream_Shown(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Aktivering eller deaktivering af label baggrunden - fra læst sessions data
			GlobalVariables::OpenGLRender->RMH_OpenGL_EnableLabelBackground(EnableLabelBackgroundFlag);
			// Opdater Live view labels farve - fra læst sessions data
			GlobalVariables::OpenGLRender->RMH_OpenGL_ChangeRenderedLabelsColor(CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);
			// Opdater Live view labels baggrunds farve - fra læst sessions data
			GlobalVariables::OpenGLRender->RMH_OpenGL_ChangeLabelBackgroundColor(CommonLabelBackgroundColorR, CommonLabelBackgroundColorG, CommonLabelBackgroundColorB);

			// Opdater tilhørende form Flag
			isLiveViewStreamFormOpen = true;

		}

	    // Live View Stream Form Nedluknings Callback Routine -> 
		private: System::Void LiveViewStream_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Opdater tilhørende form Flag
			isLiveViewStreamFormOpen = false;
			isLiveViewStreamFormDocked = false;
			isLiveViewStreamFormUndocked = false;

			// Når Formen lukkes - Gem Formen
			this->Hide();
			// Deaktiver "Disposing" Af Form Objektet
			e->Cancel = true;

		}

	    // -------------------- Color Palette & ColorBar Event & Callback Routiner -------------------- //
		
		// Histogram Antal Bins Context Menu Strip Callback Routine -> 
		private: System::Void HistogramNumberOfBinsContextMenu_Click(System::Object^ sender, System::EventArgs^ e) {

			// Indstil Histogrammets Antal Rendereret Bins
			GlobalVariables::OpenGLHistogram->RMH_OpenGL_SetHistogramNumberOfBins(sender);

		}

		// ------------------- Live View Context Menu Strip Event Callback Routiner ------------------- //

		// Toggle Live View Tools panel synlighed Callback Routine -> 
		private: System::Void toggleToolsPanelVisibilityToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Kontroller om Live View Tools panelet er undocked
			if (isLiveViewToolsFormUndocked != true) {

				// Toggle Live View Tools panelets synligheds flag
				LiveViewToolsPanelVisibilityFlag = !LiveViewToolsPanelVisibilityFlag;

				// Gør Live View Tools Panelet usyneligt/usyneligt
				this->LiveViewToolsPanel->Visible = LiveViewToolsPanelVisibilityFlag;

			}
			else {

				// Skriv GUI Status Meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Live View Tools Panel Is Undocked.", _StatusMessageType_Warning);

			}

		}

		// Toggle ColorBar panelets synlighed Callback Routine -> 
		private: System::Void toggleColorBarVisibilityToolStripMenuItem_Click_1(System::Object^ sender, System::EventArgs^ e) {

			// Toggle ColorBar panelets synligheds flag
			ColorBarPanelVisibilityFlag = !ColorBarPanelVisibilityFlag;

			// Gør Live View Tools Panelet usyneligt/usyneligt
			ColorBarMainPanel->Visible = ColorBarPanelVisibilityFlag;

		}

		// Undock Live View Tools Panel callback Routine ->
		private: System::Void undockToolsPanelToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Undock Live View Tools Form fra Live View Formen
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::LiveViewToolsForm, this->LiveViewToolsPanel, &isLiveViewToolsFormOpen, &isLiveViewToolsFormDocked, &isLiveViewToolsFormUndocked, _FormDockingState_UndockForm);

			// Opdater Live View Tools panelets synligheds flag
			LiveViewToolsPanelVisibilityFlag = false;

			// Gør Live View Tools Panelet usyneligt
			this->LiveViewToolsPanel->Visible = LiveViewToolsPanelVisibilityFlag;

		}

		// Live View Billede CW Roterings Callback Routine ->
		private: System::Void RotateLiveViewCWStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Roter Live view billedet med 90 grader CW
			GlobalVariables::OpenGLRender->RMH_OpenGL_RotateLiveViewCW();

		}

		// Live View Billede CCW Roterings Callback Routine ->
		private: System::Void RotateLiveViewCCWStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Roter Live view billedet med 90 grader CCW
			GlobalVariables::OpenGLRender->RMH_OpenGL_RotateLiveViewCCW();

		}

		// Aktiver/Deaktiver Mus Hjul Live View Roterings Feature Callback Routine ->
		private: System::Void EnableDisableMouseWheelRotation_Click(System::Object^ sender, System::EventArgs^ e) {

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ EnableFlagItemTag = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag og indstil globale enable flag
			bool MouseWheelRotationEnableFlag = Convert::ToBoolean(Convert::ToDouble(EnableFlagItemTag->Tag));

			// Aktiver eller deaktiver live view billede rotering ved brug af Mus Scrol-Hjulet
			GlobalVariables::OpenGLRender->RMH_LiveView_EnableScrollWheelRotation(MouseWheelRotationEnableFlag);

		}

		// Live View Context Menu Alle Crosshair Farve Callback Routine ->
		private: System::Void changeAllLabelsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				MaxCrosshairColorR = SelectedColor->R;
				MaxCrosshairColorG = SelectedColor->G;
				MaxCrosshairColorB = SelectedColor->B;
				MinCrosshairColorR = SelectedColor->R;
				MinCrosshairColorG = SelectedColor->G;
				MinCrosshairColorB = SelectedColor->B;
				CenterCrosshairColorR = SelectedColor->R;
				CenterCrosshairColorG = SelectedColor->G;
				CenterCrosshairColorB = SelectedColor->B;
				TempMeasCrosshairPassiveColorR = SelectedColor->R;
				TempMeasCrosshairPassiveColorG = SelectedColor->G;
				TempMeasCrosshairPassiveColorB = SelectedColor->B;

			}

		}

		// Live View Context Menu Maximum Crosshair Farve Callback Routine ->
		private: System::Void maxLabelToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				MaxCrosshairColorR = SelectedColor->R;
				MaxCrosshairColorG = SelectedColor->G;
				MaxCrosshairColorB = SelectedColor->B;

			}

		}

		// Live View Context Menu Minimum Crosshair Farve Callback Routine ->
		private: System::Void minLabelColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				MinCrosshairColorR = SelectedColor->R;
				MinCrosshairColorG = SelectedColor->G;
				MinCrosshairColorB = SelectedColor->B;

			}

		}

		// Live View Context Menu Center Crosshair Farve Callback Routine ->
		private: System::Void centerLabelColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				CenterCrosshairColorR = SelectedColor->R;
				CenterCrosshairColorG = SelectedColor->G;
				CenterCrosshairColorB = SelectedColor->B;

			}

		}

		// Opdater ROIers Valgte Farve Callback Routine ->
		private: System::Void selectedColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				ROISelectedColorR = SelectedColor->R;
				ROISelectedColorG = SelectedColor->G;
				ROISelectedColorB = SelectedColor->B;

			}

		}

		// Opdater ROIers Passive Farve Callback Routine ->
		private: System::Void passiveColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				ROIPassiveColorR = SelectedColor->R;
				ROIPassiveColorG = SelectedColor->G;
				ROIPassiveColorB = SelectedColor->B;

			}

		}

		// Opdater Temperatur Målingernes valgte Crosshair Farve Callback Routine ->
		private: System::Void labelSeletedColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				TempMeasCrosshairSelectedColorR = SelectedColor->R;
				TempMeasCrosshairSelectedColorG = SelectedColor->G;
				TempMeasCrosshairSelectedColorB = SelectedColor->B;

			}

		}

		// Opdater Temperatur Målingernes passive Crosshair Farve Callback Routine ->
		private: System::Void labelPassiveColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				TempMeasCrosshairPassiveColorR = SelectedColor->R;
				TempMeasCrosshairPassiveColorG = SelectedColor->G;
				TempMeasCrosshairPassiveColorB = SelectedColor->B;

			}

		}

		// Aktiver Label baggrund Context menu Callback Routine ->
		private: System::Void enableBackgroundToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ TagEnableLabelBackGround = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag og indstil globale enable flag
			EnableLabelBackgroundFlag = Convert::ToBoolean(Convert::ToDouble(TagEnableLabelBackGround->Tag));

			// Aktiver eller deaktiver label baggrunden
			GlobalVariables::OpenGLRender->RMH_OpenGL_EnableLabelBackground(EnableLabelBackgroundFlag);

		}

		// Opdater Temperatur Linjernes valgte Label Farve Callback Routine ->
		private: System::Void selectedColorToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				TempLinesSelectedColorR = SelectedColor->R;
				TempLinesSelectedColorG = SelectedColor->G;
				TempLinesSelectedColorB = SelectedColor->B;

			}

		}

		// Opdater Temperatur Linjernes passive Label Farve Callback Routine ->
		private: System::Void passiveColorToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Farve til globale variabel
				TempLinesPassiveColorR = SelectedColor->R;
				TempLinesPassiveColorG = SelectedColor->G;
				TempLinesPassiveColorB = SelectedColor->B;

			}

		}

		// Opdater Live View Temperatur Labels farve Callback Routine ->
		private: System::Void changeLabelColorsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Live View fælles label farve til globale variabel
				CommonLabelColorR = SelectedColor->R;
				CommonLabelColorG = SelectedColor->G;
				CommonLabelColorB = SelectedColor->B;

			}

			// Opdater Live view labels farve
			GlobalVariables::OpenGLRender->RMH_OpenGL_ChangeRenderedLabelsColor(CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

		}

		// Opdater Live View Labels baggrunds farve Callback Routine ->
		private: System::Void changeLabelBackgroundColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokalt fare variabel
			bool DialogAbortFlag = false;
			System::Drawing::Color^ SelectedColor;

			// Åben Farve dialog og læs valgte farve
			SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&DialogAbortFlag);

			// Kontroller farve dialog abort flag
			if (DialogAbortFlag == false) {

				// Indstil Live View fælles label farve til globale variabel
				CommonLabelBackgroundColorR = SelectedColor->R;
				CommonLabelBackgroundColorG = SelectedColor->G;
				CommonLabelBackgroundColorB = SelectedColor->B;

			}

			// Opdater Live view labels baggrunds farve
			GlobalVariables::OpenGLRender->RMH_OpenGL_ChangeLabelBackgroundColor(CommonLabelBackgroundColorR, CommonLabelBackgroundColorG, CommonLabelBackgroundColorB);

		}

		// Slet Valgte ROI Context Menu Callback Routine ->
		private: System::Void rOI1ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Slet valgte ROI Tag fra Live View streamen
			RMH_ThermalViewer_DeleteRegionOfInterestBoxFromLiveView(sender);

		}
		
		// Slet Alle ROI Context Menu Callback Routine ->
		private: System::Void deleteAllToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Slet alle aktive ROIer fra Live View streamen
			RMH_ThermalViewer_DeleteAllRegionOfInterestBoxFromLiveView();

		}

		// Slet Valgte Temperatur Måling Context Menu Callback Routine ->
		private: System::Void tempMeas1ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Slet valgte Temperatur Målings Tag fra Live View streamen
			RMH_ThermalViewer_DeleteTemperatureMeasurementFromLiveView(sender);

		}

		// Slet Alle Temperatur Målinger Context Menu Callback Routine ->
		private: System::Void deleteAllToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {

			// Slet alle aktive Temperatur målinger fra Live View streamen
			RMH_ThermalViewer_DeleteAllTemperatureMeasurementFromLiveView();

		}
		
		// Slet Valgte Temperatur linje Context Menu Callback Routine ->
		private: System::Void line1ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Slet alle aktive Temperatur linjer fra Live View streamen 
			RMH_ThermalViewer_DeleteTemperatureLineFromLiveView(sender);

		}

		// Slet Alle Temperatur linjer Context Menu Callback Routine ->
		private: System::Void deleteAllToolStripMenuItem3_Click(System::Object^ sender, System::EventArgs^ e) {

			// Slet alle aktive Temperatur linjer fra Live View streamen 
			RMH_ThermalViewer_DeleteAllTemperatureLinesFromLiveView();

		}

		// Slet alle ROIer, Linjer og Temperatur labels Context Menu Callback Routine ->
		private: System::Void deleteAllToolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e) {

			// Slet alle aktive ROIer fra Live View streamen
			RMH_ThermalViewer_DeleteAllRegionOfInterestBoxFromLiveView();

			// Slet alle aktive Temperatur linjer fra Live View streamen 
			RMH_ThermalViewer_DeleteAllTemperatureLinesFromLiveView();

			// Slet alle aktive Temperatur målinger fra Live View streamen
			RMH_ThermalViewer_DeleteAllTemperatureMeasurementFromLiveView();

		}

		// ROI "Bring-To-Front" Context Menu Callback Routine ->
		private: System::Void rOIBringToFrontToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater objekt rendererings Z-ordnen for Positions justerbare Rektangler, Crosshairs Og Linjer
			GlobalVariables::OpenGLRender->RMH_OpenGL_UpdateRenderedObjectsZOrder(_ZOrden_RectanglesInFront);

		}

		// Temperatur Målinger "Bring-To-Front" Context Menu Callback Routine ->
		private: System::Void bringToFrontToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater objekt rendererings Z-ordnen for Positions justerbare Rektangler, Crosshairs Og Linjer
			GlobalVariables::OpenGLRender->RMH_OpenGL_UpdateRenderedObjectsZOrder(_ZOrden_CrosshairsInFront);

		}
		
		// Temperatur Målinger "Bring-To-Front" Context Menu Callback Routine ->
		private: System::Void bringToFrontToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater objekt rendererings Z-ordnen for Positions justerbare Rektangler, Crosshairs Og Linjer
			GlobalVariables::OpenGLRender->RMH_OpenGL_UpdateRenderedObjectsZOrder(_ZOrden_LinesInFront);

		}

		// Indstil Billede Sharpening Styrke Context Menu Callback Routine ->
		private: System::Void imageSharpeningStrengthToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Lokale Klasse variabler
			bool DummyFlag = false;

			// Åben Inout værdi Dialog formen - For at indstille billede sharpenings styrke værdien
			ManagedLocals::LiveViewToolsForm->ShowInputValueDialogForm("Set Sharpening Strength", "Value Range: " + _GaussianUnSharpStrength_MinRangeValue.ToString() + " To " + _GaussianUnSharpStrength_MaxRangeValue.ToString(),
				_GaussianUnSharpStrength_MaxRangeValue, _GaussianUnSharpStrength_MinRangeValue, &ImageSharpeningStrength, &DummyFlag);

		}

		// Indstil Billede Sharpening Standard Deviation Context Menu Callback Routine ->
		private: System::Void SetSharpStdDivToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Åben Input værdi Dialog formen - For at indstille billede sharpenings standard deviation værdien
			ManagedLocals::LiveViewToolsForm->ShowInputValueDialogForm("Set UnSharp Standart Deviation", "Value Range: " + _GaussianStandardDeviation_MinRangeValue.ToString() + " To " + _GaussianStandardDeviation_MaxRangeValue.ToString(),
				_GaussianStandardDeviation_MaxRangeValue, _GaussianStandardDeviation_MinRangeValue, &ImageUnSharpeningSigma, &NewGaussianKernelMaskGenerateFlag);

		}
   
		// Aktiver Visning Det filtrerede Unsharpened Billede Context Menu Callback Routine ->
		private: System::Void ShowUnsharpTrueToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Visning af Gaussian Unsharp Maske billedet
			ShowUnsharpenMaskImageFlag = true;

		}

		// Deaktiver Visning Det filtrerede Unsharpened Billede Context Menu Callback Routine ->
		private: System::Void ShowUnsharpFalseToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Visning af Gaussian Unsharp Maske billedet
			ShowUnsharpenMaskImageFlag = false;

		}

		// Inverter Color Palette Context Menu Callback Routine ->
		private: System::Void invertLiveViewPaletteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Inverter valgte Live View eller ColorBar color palette flag
			RMH_ColorPalette_InvertColorPalettes(sender);

		}
		
		// Live View Split View Context Menu Callback Routine ->
		private: System::Void LiveViewSplitViewToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Udregn Split panelets splitter default start position
			unsigned int LiveViewSplitPanelSplitterDistance = this->LiveViewStreamMainPanel->Width * _LiveViewStream_DefaultSplitterDistanceRatio;

			// Toggel Lokalt Live View Split View Feature Flaget
			LiveViewSplitViewToggleflag = LiveViewSplitViewToggleflag ^ 1;
			// Toggel Globalt Live View Split View Feature Flaget
			LiveViewSplitViewEnableFlag = LiveViewSplitViewToggleflag ^ 1;

			// Går Live View Split View panelet synlig
			this->LiveViewSplitContainer->Panel2Collapsed = LiveViewSplitViewToggleflag;

			// Indstil Split panelets splitter default start position
			this->LiveViewSplitContainer->SplitterDistance = LiveViewSplitPanelSplitterDistance;

			// Kontroller om live view split view er aktiverede
			if (LiveViewSplitViewEnableFlag == true) {

				// Aktiver tilhørende label Sub Context Menu Drop Down List Item 
				GlobalVariables::GlobalhistogramSourceToolStripMenuItem->DropDownItems[15]->Enabled = true;

			}
			else {

				// Deaktiver tilhørende label Sub Context Menu Drop Down List Item 
				GlobalVariables::GlobalhistogramSourceToolStripMenuItem->DropDownItems[15]->Enabled = false;

			}

		}

		// ------------------- Colorbar Context Menu Strip Event Callback Routiner -------------------- //
		
		// Colorbar Auto temperatur Range Context Menu Callback Routine ->
		private: System::Void autoToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Colorbar Temperatur Range flag
			ColorBarManualRangeFlag = false;
			ColorBarManualHighRangeFlag = false;
			ColorBarManualLowRangeFlag = false;

			// Deaktiver ColorBar Temperatur Ranges Dialog Context Menu Item
			this->setColorBarRangesToolStripMenuItem->Enabled = false;

			// Opdater Colorbarens tick linje farve
			GlobalVariables::OpenGLColorBar->RMH_OpenGL_SetColorBarTickLineColor(255, 255, 255);

		}

		// Colorbar Manual temperatur Range Context Menu Callback Routine ->
		private: System::Void manualToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Colorbar Temperatur Range flag
			ColorBarManualRangeFlag = true;
			ColorBarManualHighRangeFlag = false;
			ColorBarManualLowRangeFlag = false;

			// Aktiver ColorBar Temperatur Ranges Dialog Context Menu Item
			this->setColorBarRangesToolStripMenuItem->Enabled = true;

			// Nulstil colorbarens maximum og minimum temperatur range offset værdier
			GlobalVariables::OpenGLColorBar->RMH_OpenGL_ResetColorbarMaxMinRangeOffsetValues();

			// Opdater Colorbarens start Manuelle Temperatur range værdier til frame Max/Min Temperaturerne ved Range Skift 
			ColorBarInitialManualRangeMaxTemp = MaximumTemperature;
			ColorBarInitialManualRangeMinTemp = MinimumTemperature;

		}
		
		// Colorbar Manual High temperatur Range Context Menu Callback Routine ->
		private: System::Void manualHighRangeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Colorbar Temperatur Range flag
			ColorBarManualRangeFlag = false;
			ColorBarManualHighRangeFlag = true;
			ColorBarManualLowRangeFlag = false;

			// Aktiver ColorBar Temperatur Ranges Dialog Context Menu Item
			this->setColorBarRangesToolStripMenuItem->Enabled = true;

			// Nulstil colorbarens maximum og minimum temperatur range offset værdier
			GlobalVariables::OpenGLColorBar->RMH_OpenGL_ResetColorbarMaxMinRangeOffsetValues();

			// Opdater Colorbarens start Manuelle Temperatur range værdier til frame Max/Min Temperaturerne ved Range Skift 
			ColorBarInitialManualRangeMaxTemp = MaximumTemperature;
			ColorBarInitialManualRangeMinTemp = MinimumTemperature;

		}

		// Colorbar Manual Low temperatur Range Context Menu Callback Routine ->
		private: System::Void manualLowRangeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Colorbar Temperatur Range flag
			ColorBarManualRangeFlag = false;
			ColorBarManualHighRangeFlag = false;
			ColorBarManualLowRangeFlag = true;

			// Aktiver ColorBar Temperatur Ranges Dialog Context Menu Item
			this->setColorBarRangesToolStripMenuItem->Enabled = true;

			// Nulstil colorbarens maximum og minimum temperatur range offset værdier
			GlobalVariables::OpenGLColorBar->RMH_OpenGL_ResetColorbarMaxMinRangeOffsetValues();

			// Opdater Colorbarens start Manuelle Temperatur range værdier til frame Max/Min Temperaturerne ved Range Skift 
			ColorBarInitialManualRangeMaxTemp = MaximumTemperature;
			ColorBarInitialManualRangeMinTemp = MinimumTemperature;

		}

		// Aktiver Colorbar Center temperatur tracking Context Menu Callback Routine ->
		private: System::Void enableToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Colorbar center Temperatur tracking flag
			ColorBarCenterTrackEnableFlag = true;

		}

		// Deaktiver Colorbar Center temperatur tracking Context Menu Callback Routine ->
		private: System::Void disableToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Colorbar center Temperatur tracking flag
			ColorBarCenterTrackEnableFlag = false;

		}

		// Sæt Colorbar Manual Maximum Og Minimum Temperatur Ranges Context Menu Callback Routine ->
		private: System::Void setColorBarRangesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Nulstil colorbarens maximum og minimum temperatur range offset værdier
			//GlobalVariables::OpenGLColorBar->RMH_OpenGL_ResetColorbarMaxMinRangeOffsetValues();

			// Initiliser og vis Colorbarens temperatur range dialog formen
			ManagedLocals::LiveViewToolsForm->ShowColorbarTemperatureRangeDialogForm();

			// Opdater ColorBar Range Dialogen med relavante værdier og indstiller temperatur enheds stringet
			ManagedLocals::LiveViewToolsForm->ColorBarRangeDialogForm->UpdateColorBarTempRangeDialogValues(MaximumTemperature, MinimumTemperature, GlobalVariables::DefaultTempUnitString);

		}

		// Colorbar Manual Temperatur Ranges Mus Wheel Step Størrelses Context Menu Callback Routine ->
		private: System::Void stepSize1ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater colorbarens Mus Wheel temperatur Step størrelse
			RMH_ColorBar_ChangeManualRangeMouseWheelStepSize(sender);

		}

		// Colorbar Antal Temperatur Ticks Context Menu Callback Routine ->
		private: System::Void ticksToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater antallet af colorbar temperatur ticks
			RMH_ColorBar_ChangeColorBarAmountOfTemperatureTick(sender);

		}

		// Full ColorBar Palette Range Justerings COntext menu Callback Routine ->
		private: System::Void enableToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {

			// Cast Sender objekt som Forms Tool Strip objekt
			System::Windows::Forms::ToolStripMenuItem^ TagAdaptFullColorBarPaletteRangeContext = (System::Windows::Forms::ToolStripMenuItem^)sender;

			// Læs Sub Context Menu identifikations tag og indstil globale enable flag
			AdaptFullColorBarPaletteRangeFlag = Convert::ToBoolean(Convert::ToDouble(TagAdaptFullColorBarPaletteRangeContext->Tag));

		}

		// Aktiver Justering af Live view color palette colorbar range 
		private: System::Void enableDefaultToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver live view color palette skalering
			LiveViewPaletteRangeScalingEnableFlag = true;

		}

		// Deaktiver Justering af Live view color palette colorbar range 
		private: System::Void disableToolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e) {

			// Deaktiver live view color palette skalering
			LiveViewPaletteRangeScalingEnableFlag = false;

		}

		// Aktiver Justering af dual color palette colorbar range 
		private: System::Void enableToolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver Dual live view color palette skalering
			DualPaletteRangeScalingEnableFlag = true;

		}

		// Aktiver Justering af dual color palette colorbar range 
		private: System::Void disableDefaultToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Deaktiver Dual live view color palette skalering
			DualPaletteRangeScalingEnableFlag = false;

		}

		// ------------------- Histogram Context Menu Strip Event Callback Routiner ------------------- //

		// Histogram Source Data Context Menu Callback Routine ->
		private: System::Void liveViewToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater histogrammets data source 
			RMH_ThermalViewer_ChangeHistoramDataSource(sender);

			// Opdater histogrammets color palette inverterings stadie
			RMH_ColorPalette_UpdateHistogramColorPaletteInvertionState();
			
		}

		// Histogram Vis Ranged Palette Context Menu Callback Routine ->
		private: System::Void showRangedPaletteToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Histogram Vis Ranged Palette flag 
			HistogramShowRangedPaletteFlag = true;

			// Opdater histogrammets color palette inverterings stadie
			RMH_ColorPalette_UpdateHistogramColorPaletteInvertionState();

		}

		// Histogram Vis totale color Palette Context Menu Callback Routine ->
		private: System::Void showFullPaletteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Histogram Vis Ranged Palette flag 
			HistogramShowRangedPaletteFlag = false;

			// Opdater histogrammets color palette inverterings stadie
			RMH_ColorPalette_UpdateHistogramColorPaletteInvertionState();

		}

		// Histogram Benyt Live view Palette Context Menu Callback Routine ->
		private: System::Void useLiveViewPaletteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Histogram Live View Eller Dual Palette flag 
			HistogramDualOrLiveViewPaletteFlag = false;

			// Opdater histogrammets color palette inverterings stadie
			RMH_ColorPalette_UpdateHistogramColorPaletteInvertionState();

		}

		// Histogram Benyt Dual Palette Context Menu Callback Routine ->
		private: System::Void useDualPaletteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Histogram Live View Eller Dual Palette flag 
			HistogramDualOrLiveViewPaletteFlag = true;

			// Opdater histogrammets color palette inverterings stadie
			RMH_ColorPalette_UpdateHistogramColorPaletteInvertionState();

		}

		// -------------------------- Form Resizing Event Callback Routiner --------------------------- //
		
		// Form Global Resizing Callback Routine ->
		private: System::Void LiveViewStream_Resize(System::Object^ sender, System::EventArgs^ e) {


		}

	    // -------------------------------------------------------------------------------------------- //

};
}
