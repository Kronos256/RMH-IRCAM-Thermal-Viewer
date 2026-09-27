#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"
#include "RMH_Application_ColorBarAndPalette.h"
#include "RMH_OpenGL_ColorBar.h"
#include "RMH_Winforms_Library.h"
#include "RMH_Application_ThermalViewer.h"
#include "ColorBarRangeDialog.h"
#include "InputValueDialog.h"
#include "StatisticsWindow.h"
#include <iostream>

// Klasse Namespace
namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Summary for Form - LiveViewTools
	public ref class LiveViewTools : public System::Windows::Forms::Form {

		// ------------------------------ Lokale Form Reference Struktur ------------------------------ //
	
		// Lokale og Globale klasse form objekter og strukturer
		public: IRCAMThermalViewer::ColorBarRangeDialog^ ColorBarRangeDialogForm;
		public: IRCAMThermalViewer::InputValueDialog^ InputValueDialogForm;
		public: IRCAMThermalViewer::StatisticsWindow^ StatisticsWindowForm;

		// -------------------------------------------------------------------------------------------- //

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		LiveViewTools(void) {

			// Init GUI komponenter og objekter
			InitializeComponent();
			// Formater arrays Og Objekter af winform komponenter til global brug
			InitializeComponentArraysAndGlobalObjects();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Opdaterer Teksten i toppen af GUIen
			RMH_Winforms_ChangeFormTitleBarText(this, "Live View Tools");
			
		}

		// ---------------------------- Diverse Specifikke Klasse Metoder ----------------------------- //

		void InitializeComponentArraysAndGlobalObjects(void) {

			// Routinen formaterer arrays af winform komponenter til global brug

			// Initiliser globale form objekter
			GlobalVariables::GlobalLiveViewRunStopButton = this->LiveViewRunStopButton;
			GlobalVariables::TempUnitButtons = gcnew cli::array<System::Windows::Forms::Button^>(12) {
				this->TempUnitCButton,
				this->TempUnitFButton,
				this->TempUnitKButton
			};
			GlobalVariables::GlobalMaxTempTrackButton = this->MaxTempTrackButton;
			GlobalVariables::GlobalMinTempTrackButton = this->MinTempTrackButton;
			GlobalVariables::GlobalCenterTempTrackButton = this->CenterTempTrackButton;
			GlobalVariables::GlobalCursorTempTrackButton = this->CursorTempTrackButton;
			GlobalVariables::GlobalAddTempMeasButton = this->AddTempMeasButton;
			GlobalVariables::GlobalAddROIMeasButton = this->AddROIMeasButton;
			GlobalVariables::GlobalAddTempSpecLineButton = this->AddTempSpecLineButton;
			GlobalVariables::GlobalShowLineHistButton = this->ShowLineHistButton;
			GlobalVariables::GlobalImageSharpButton = this->ImageSharpButton;
			GlobalVariables::GlobalCalibrateCameraButton = this->CalibrateCameraButton;
			GlobalVariables::GlobalTempRangeButton = this->TempRangeButton;
			GlobalVariables::GlobalFixedAspectRatioButton = this->FixedAspectRatioButton;
			GlobalVariables::GlobalColorPaletteComboBox = this->ColorPaletteComboBox;
			GlobalVariables::GlobalDualColorPaletteComboBox = this->DualColorPaletteComboBox;
			GlobalVariables::GlobalColorBarBackPaletteComboBox = this->ColorBarBackPaletteComboBox;
			GlobalVariables::GlobalRecordingButton = this->RecordingButton;
			GlobalVariables::GlobalUltraResolutionButton = this->UltraResolutionButton;
			GlobalVariables::GlobalPeriodicTimerTriggerButton = this->PeriodicTimerTriggerButton;
			GlobalVariables::GlobalEnhancedResButton = this->EnhancedResButton;
			GlobalVariables::GlobalSaveTempFrameDataButton = this->SaveTempFrameDataButton;
			GlobalVariables::GlobalSnapshotButton = this->SnapshotButton;
			GlobalVariables::GlobalDualColorPaletteButton = this->DualColorPaletteButton;

		}

		void ShowInputValueDialogForm(System::String^ InfoLabel1String, System::String^ InfoLabel2String, float UpDownMaxRangeVal, float UpDownMinRangeVal, float* DialogOutputVal, bool* NewValueReadyFlag) {

			// Routinen indstiller og viser input værdi dialogen

			// Kontroller at dialogen ikke allerede er åben
			if (InputValueDialogIsShownFlag == false) {

				// Initiliser input værdi dialog formen
				InputValueDialogForm = gcnew IRCAMThermalViewer::InputValueDialog(InfoLabel1String, InfoLabel2String, UpDownMaxRangeVal, UpDownMinRangeVal, DialogOutputVal, NewValueReadyFlag);

				// Åben input værdi dialog formen
				InputValueDialogForm->Show();

			}
			else {

				// Luk input værdi dialog formen
				InputValueDialogForm->Close();

				// Initiliser input værdi dialog formen
				InputValueDialogForm = gcnew IRCAMThermalViewer::InputValueDialog(InfoLabel1String, InfoLabel2String, UpDownMaxRangeVal, UpDownMinRangeVal, DialogOutputVal, NewValueReadyFlag);

				// Åben input værdi dialog formen
				InputValueDialogForm->Show();

			}

		}

		void ShowColorbarTemperatureRangeDialogForm() {

			// Routinen Initiliser og viser Colorbarens temperatur range dialog formen

			// Kontroller at Colorbar range dialogen ikke allerede er åben
			if (ColorBarDialogIsShownFlag == false) {

				// Initiliser ColorBar Temperatur Range Dialog Form
				ColorBarRangeDialogForm = gcnew IRCAMThermalViewer::ColorBarRangeDialog();

				// Åben Colorbarens temperatur range dialog formen
				ColorBarRangeDialogForm->Show();

			}
			else {

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Colorbar Range Dialog Is Already Open!", _StatusMessageType_Normal);

			}

		}

		void ShowLiveViewStatisticsWindowForm() {

			// Routinen Initiliser og viser Live View Statistik Vindue formen

			// Kontroller at Live View Statistik Vinduet ikke allerede er åben
			if (LiveViewStatisticsWindowIsShownFlag == false) {

				// Initiliser Live View Statistik Vindue Formen
				StatisticsWindowForm = gcnew IRCAMThermalViewer::StatisticsWindow();

				// Åben Live View Statistik Vindue formen
				StatisticsWindowForm->Show();

			}
			else {

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Live View Statistics Window Is Already Open!", _StatusMessageType_Normal);

			}

		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		~LiveViewTools() {

			if (components) {

				// Slet alle Form Komponenter
				delete components;

			}
		}

	protected:
	
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private: System::ComponentModel::IContainer^ components;
		public: System::Windows::Forms::Button^ TempUnitKButton;
		private: System::Windows::Forms::Button^ SnapshotButton;
		public: System::Windows::Forms::Button^ TempUnitFButton;
		private: System::Windows::Forms::Button^ RecordButton;
		public: System::Windows::Forms::Button^ TempUnitCButton;
		private: System::Windows::Forms::Button^ FixedAspectRatioButton;
		private: System::Windows::Forms::Button^ ImageSharpButton;
		private: System::Windows::Forms::Button^ EnhancedResButton;
		public: System::Windows::Forms::Button^ LiveViewRunStopButton;
		public: System::Windows::Forms::Button^ CalibrateCameraButton;
		private: System::Windows::Forms::Button^ TempRangeButton;
		private: System::Windows::Forms::Button^ ShowLineHistButton;
		private: System::Windows::Forms::Button^ AddTempSpecLineButton;
		private: System::Windows::Forms::Button^ MinTempTrackButton;
		private: System::Windows::Forms::Button^ MaxTempTrackButton;
		private: System::Windows::Forms::Button^ AddTempMeasButton;
		private: System::Windows::Forms::Button^ CenterTempTrackButton;
		private: System::Windows::Forms::Button^ DualColorPaletteButton;
		private: System::Windows::Forms::Button^ CursorTempTrackButton;
		private: System::Windows::Forms::Button^ AddROIMeasButton;
		private: System::Windows::Forms::Label^ label1;
		public: System::Windows::Forms::ComboBox^ ColorPaletteComboBox;
		private: System::Windows::Forms::Label^ label3;
		public: System::Windows::Forms::ComboBox^ DualColorPaletteComboBox;
		private: System::Windows::Forms::Label^ label4;
		public: System::Windows::Forms::ComboBox^ ColorBarBackPaletteComboBox;
		private: System::Windows::Forms::ToolTip^ LiveViewTooTips;
		private: System::Windows::Forms::Button^ RecordingButton;
		private: System::Windows::Forms::Button^ SaveTempFrameDataButton;
		private: System::Windows::Forms::Button^ ShowLiveViewStatisticsButton;
		private: System::Windows::Forms::Button^ UltraResolutionButton;
		private: System::Windows::Forms::Button^ PeriodicTimerTriggerButton;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LiveViewTools::typeid));
			this->TempUnitKButton = (gcnew System::Windows::Forms::Button());
			this->SnapshotButton = (gcnew System::Windows::Forms::Button());
			this->TempUnitFButton = (gcnew System::Windows::Forms::Button());
			this->RecordButton = (gcnew System::Windows::Forms::Button());
			this->TempUnitCButton = (gcnew System::Windows::Forms::Button());
			this->FixedAspectRatioButton = (gcnew System::Windows::Forms::Button());
			this->ImageSharpButton = (gcnew System::Windows::Forms::Button());
			this->EnhancedResButton = (gcnew System::Windows::Forms::Button());
			this->LiveViewRunStopButton = (gcnew System::Windows::Forms::Button());
			this->CalibrateCameraButton = (gcnew System::Windows::Forms::Button());
			this->TempRangeButton = (gcnew System::Windows::Forms::Button());
			this->ShowLineHistButton = (gcnew System::Windows::Forms::Button());
			this->AddTempSpecLineButton = (gcnew System::Windows::Forms::Button());
			this->MinTempTrackButton = (gcnew System::Windows::Forms::Button());
			this->MaxTempTrackButton = (gcnew System::Windows::Forms::Button());
			this->AddTempMeasButton = (gcnew System::Windows::Forms::Button());
			this->CenterTempTrackButton = (gcnew System::Windows::Forms::Button());
			this->DualColorPaletteButton = (gcnew System::Windows::Forms::Button());
			this->CursorTempTrackButton = (gcnew System::Windows::Forms::Button());
			this->AddROIMeasButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ColorPaletteComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->DualColorPaletteComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ColorBarBackPaletteComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->LiveViewTooTips = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->RecordingButton = (gcnew System::Windows::Forms::Button());
			this->SaveTempFrameDataButton = (gcnew System::Windows::Forms::Button());
			this->ShowLiveViewStatisticsButton = (gcnew System::Windows::Forms::Button());
			this->UltraResolutionButton = (gcnew System::Windows::Forms::Button());
			this->PeriodicTimerTriggerButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// TempUnitKButton
			// 
			this->TempUnitKButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempUnitKButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->TempUnitKButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempUnitKButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempUnitKButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempUnitKButton->ForeColor = System::Drawing::Color::White;
			this->TempUnitKButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TempUnitKButton.Image")));
			this->TempUnitKButton->Location = System::Drawing::Point(9, 735);
			this->TempUnitKButton->Name = L"TempUnitKButton";
			this->TempUnitKButton->Size = System::Drawing::Size(64, 48);
			this->TempUnitKButton->TabIndex = 18;
			this->TempUnitKButton->Tag = L"3";
			this->TempUnitKButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->TempUnitKButton, L"Change Temperature Unit: Kelvin\r\nHotKey: K\r\n");
			this->TempUnitKButton->UseVisualStyleBackColor = false;
			this->TempUnitKButton->Click += gcnew System::EventHandler(this, &LiveViewTools::TempUnitCButton_Click);
			// 
			// SnapshotButton
			// 
			this->SnapshotButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SnapshotButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->SnapshotButton->Enabled = false;
			this->SnapshotButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SnapshotButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SnapshotButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->SnapshotButton->ForeColor = System::Drawing::Color::White;
			this->SnapshotButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SnapshotButton.Image")));
			this->SnapshotButton->Location = System::Drawing::Point(79, 573);
			this->SnapshotButton->Name = L"SnapshotButton";
			this->SnapshotButton->Size = System::Drawing::Size(64, 48);
			this->SnapshotButton->TabIndex = 14;
			this->SnapshotButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->SnapshotButton, L"Take Live View\r\nSnapshot\r\nHotKey: S");
			this->SnapshotButton->UseVisualStyleBackColor = false;
			this->SnapshotButton->Click += gcnew System::EventHandler(this, &LiveViewTools::SnapshotButton_Click);
			// 
			// TempUnitFButton
			// 
			this->TempUnitFButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempUnitFButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->TempUnitFButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempUnitFButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempUnitFButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempUnitFButton->ForeColor = System::Drawing::Color::White;
			this->TempUnitFButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TempUnitFButton.Image")));
			this->TempUnitFButton->Location = System::Drawing::Point(9, 789);
			this->TempUnitFButton->Name = L"TempUnitFButton";
			this->TempUnitFButton->Size = System::Drawing::Size(64, 48);
			this->TempUnitFButton->TabIndex = 15;
			this->TempUnitFButton->Tag = L"2";
			this->TempUnitFButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->TempUnitFButton, L"Change Temperature Unit: Fahrenheit\r\nHotKey: F");
			this->TempUnitFButton->UseVisualStyleBackColor = false;
			this->TempUnitFButton->Click += gcnew System::EventHandler(this, &LiveViewTools::TempUnitCButton_Click);
			// 
			// RecordButton
			// 
			this->RecordButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->RecordButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->RecordButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->RecordButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RecordButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->RecordButton->ForeColor = System::Drawing::Color::White;
			this->RecordButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"RecordButton.Image")));
			this->RecordButton->Location = System::Drawing::Point(9, 627);
			this->RecordButton->Name = L"RecordButton";
			this->RecordButton->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->RecordButton->Size = System::Drawing::Size(64, 48);
			this->RecordButton->TabIndex = 19;
			this->RecordButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->RecordButton, L"Open Screen Capture Tool\r\nHotKey: V");
			this->RecordButton->UseVisualStyleBackColor = false;
			this->RecordButton->Click += gcnew System::EventHandler(this, &LiveViewTools::RecordButton_Click);
			// 
			// TempUnitCButton
			// 
			this->TempUnitCButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempUnitCButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->TempUnitCButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->TempUnitCButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempUnitCButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempUnitCButton->ForeColor = System::Drawing::Color::White;
			this->TempUnitCButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TempUnitCButton.Image")));
			this->TempUnitCButton->Location = System::Drawing::Point(9, 681);
			this->TempUnitCButton->Name = L"TempUnitCButton";
			this->TempUnitCButton->Size = System::Drawing::Size(64, 48);
			this->TempUnitCButton->TabIndex = 10;
			this->TempUnitCButton->Tag = L"1";
			this->TempUnitCButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->TempUnitCButton, L"Change Temperature Unit: Celsius\r\nHotKey: C");
			this->TempUnitCButton->UseVisualStyleBackColor = false;
			this->TempUnitCButton->Click += gcnew System::EventHandler(this, &LiveViewTools::TempUnitCButton_Click);
			// 
			// FixedAspectRatioButton
			// 
			this->FixedAspectRatioButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->FixedAspectRatioButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->FixedAspectRatioButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->FixedAspectRatioButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->FixedAspectRatioButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->FixedAspectRatioButton->ForeColor = System::Drawing::Color::White;
			this->FixedAspectRatioButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FixedAspectRatioButton.Image")));
			this->FixedAspectRatioButton->Location = System::Drawing::Point(9, 573);
			this->FixedAspectRatioButton->Name = L"FixedAspectRatioButton";
			this->FixedAspectRatioButton->Size = System::Drawing::Size(64, 48);
			this->FixedAspectRatioButton->TabIndex = 9;
			this->FixedAspectRatioButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->FixedAspectRatioButton, L"Toggle Live View \r\nFixed Aspect Ratio\r\nHotKey: A\r\n");
			this->FixedAspectRatioButton->UseVisualStyleBackColor = false;
			this->FixedAspectRatioButton->Click += gcnew System::EventHandler(this, &LiveViewTools::FixedAspectRatioButton_Click);
			// 
			// ImageSharpButton
			// 
			this->ImageSharpButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ImageSharpButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ImageSharpButton->Enabled = false;
			this->ImageSharpButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->ImageSharpButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ImageSharpButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->ImageSharpButton->ForeColor = System::Drawing::Color::White;
			this->ImageSharpButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ImageSharpButton.Image")));
			this->ImageSharpButton->Location = System::Drawing::Point(9, 519);
			this->ImageSharpButton->Name = L"ImageSharpButton";
			this->ImageSharpButton->Size = System::Drawing::Size(64, 48);
			this->ImageSharpButton->TabIndex = 12;
			this->ImageSharpButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->ImageSharpButton, L"Toggle Live View \r\nImage Sharpening\r\nHotKey: Y");
			this->ImageSharpButton->UseVisualStyleBackColor = false;
			this->ImageSharpButton->Click += gcnew System::EventHandler(this, &LiveViewTools::ImageSharpButton_Click);
			// 
			// EnhancedResButton
			// 
			this->EnhancedResButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->EnhancedResButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->EnhancedResButton->Enabled = false;
			this->EnhancedResButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->EnhancedResButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->EnhancedResButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->EnhancedResButton->ForeColor = System::Drawing::Color::White;
			this->EnhancedResButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"EnhancedResButton.Image")));
			this->EnhancedResButton->Location = System::Drawing::Point(79, 519);
			this->EnhancedResButton->Name = L"EnhancedResButton";
			this->EnhancedResButton->Size = System::Drawing::Size(64, 48);
			this->EnhancedResButton->TabIndex = 11;
			this->EnhancedResButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->EnhancedResButton, L"Toggle Enhanced \r\nResolution Mode\r\nHotKey: X");
			this->EnhancedResButton->UseVisualStyleBackColor = false;
			this->EnhancedResButton->Click += gcnew System::EventHandler(this, &LiveViewTools::EnhancedResButton_Click);
			// 
			// LiveViewRunStopButton
			// 
			this->LiveViewRunStopButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->LiveViewRunStopButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->LiveViewRunStopButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->LiveViewRunStopButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->LiveViewRunStopButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->LiveViewRunStopButton->ForeColor = System::Drawing::Color::White;
			this->LiveViewRunStopButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"LiveViewRunStopButton.Image")));
			this->LiveViewRunStopButton->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->LiveViewRunStopButton->Location = System::Drawing::Point(9, 12);
			this->LiveViewRunStopButton->Name = L"LiveViewRunStopButton";
			this->LiveViewRunStopButton->Size = System::Drawing::Size(134, 48);
			this->LiveViewRunStopButton->TabIndex = 16;
			this->LiveViewRunStopButton->Text = L"  Live View\r\n  Run/Stop";
			this->LiveViewRunStopButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->LiveViewRunStopButton, L"Live Vew Run/Stop\r\nRun/Stop HotKey: H\r\nSingle Trigger HotKey: O");
			this->LiveViewRunStopButton->UseVisualStyleBackColor = false;
			this->LiveViewRunStopButton->Click += gcnew System::EventHandler(this, &LiveViewTools::LiveViewRunStopButton_Click);
			// 
			// CalibrateCameraButton
			// 
			this->CalibrateCameraButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->CalibrateCameraButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->CalibrateCameraButton->Enabled = false;
			this->CalibrateCameraButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->CalibrateCameraButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CalibrateCameraButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CalibrateCameraButton->ForeColor = System::Drawing::Color::White;
			this->CalibrateCameraButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CalibrateCameraButton.Image")));
			this->CalibrateCameraButton->Location = System::Drawing::Point(9, 195);
			this->CalibrateCameraButton->Name = L"CalibrateCameraButton";
			this->CalibrateCameraButton->Size = System::Drawing::Size(64, 48);
			this->CalibrateCameraButton->TabIndex = 13;
			this->LiveViewTooTips->SetToolTip(this->CalibrateCameraButton, L"Calibrate Camera\r\nHotKey: Q");
			this->CalibrateCameraButton->UseVisualStyleBackColor = false;
			this->CalibrateCameraButton->Click += gcnew System::EventHandler(this, &LiveViewTools::CalibrateCameraButton_Click);
			// 
			// TempRangeButton
			// 
			this->TempRangeButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempRangeButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->TempRangeButton->Enabled = false;
			this->TempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempRangeButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempRangeButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempRangeButton->ForeColor = System::Drawing::Color::White;
			this->TempRangeButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TempRangeButton.Image")));
			this->TempRangeButton->Location = System::Drawing::Point(78, 195);
			this->TempRangeButton->Name = L"TempRangeButton";
			this->TempRangeButton->Size = System::Drawing::Size(65, 48);
			this->TempRangeButton->TabIndex = 17;
			this->TempRangeButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->TempRangeButton, L"Change Temperature Range\r\nHotKey: T");
			this->TempRangeButton->UseVisualStyleBackColor = false;
			this->TempRangeButton->Click += gcnew System::EventHandler(this, &LiveViewTools::TempRangeButton_Click);
			// 
			// ShowLineHistButton
			// 
			this->ShowLineHistButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ShowLineHistButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ShowLineHistButton->Enabled = false;
			this->ShowLineHistButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ShowLineHistButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ShowLineHistButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->ShowLineHistButton->ForeColor = System::Drawing::Color::White;
			this->ShowLineHistButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ShowLineHistButton.Image")));
			this->ShowLineHistButton->Location = System::Drawing::Point(79, 357);
			this->ShowLineHistButton->Name = L"ShowLineHistButton";
			this->ShowLineHistButton->Size = System::Drawing::Size(64, 48);
			this->ShowLineHistButton->TabIndex = 27;
			this->ShowLineHistButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->ShowLineHistButton, L"Show Live View Histogram\r\nHotKey: 6");
			this->ShowLineHistButton->UseVisualStyleBackColor = false;
			this->ShowLineHistButton->Click += gcnew System::EventHandler(this, &LiveViewTools::ShowLineHistButton_Click);
			// 
			// AddTempSpecLineButton
			// 
			this->AddTempSpecLineButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AddTempSpecLineButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->AddTempSpecLineButton->Enabled = false;
			this->AddTempSpecLineButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AddTempSpecLineButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AddTempSpecLineButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->AddTempSpecLineButton->ForeColor = System::Drawing::Color::White;
			this->AddTempSpecLineButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AddTempSpecLineButton.Image")));
			this->AddTempSpecLineButton->Location = System::Drawing::Point(9, 357);
			this->AddTempSpecLineButton->Name = L"AddTempSpecLineButton";
			this->AddTempSpecLineButton->Size = System::Drawing::Size(64, 48);
			this->AddTempSpecLineButton->TabIndex = 28;
			this->AddTempSpecLineButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->AddTempSpecLineButton, L"Add Temperature Spectrum Line\r\nHotKey: 5");
			this->AddTempSpecLineButton->UseVisualStyleBackColor = false;
			this->AddTempSpecLineButton->Click += gcnew System::EventHandler(this, &LiveViewTools::AddTempSpecLineButton_Click);
			// 
			// MinTempTrackButton
			// 
			this->MinTempTrackButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->MinTempTrackButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->MinTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->MinTempTrackButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->MinTempTrackButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->MinTempTrackButton->ForeColor = System::Drawing::Color::White;
			this->MinTempTrackButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MinTempTrackButton.Image")));
			this->MinTempTrackButton->Location = System::Drawing::Point(79, 249);
			this->MinTempTrackButton->Name = L"MinTempTrackButton";
			this->MinTempTrackButton->Size = System::Drawing::Size(64, 48);
			this->MinTempTrackButton->TabIndex = 21;
			this->MinTempTrackButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->MinTempTrackButton, L"Track Minimum Temperature\r\nHotKey: 2\r\n");
			this->MinTempTrackButton->UseVisualStyleBackColor = false;
			this->MinTempTrackButton->Click += gcnew System::EventHandler(this, &LiveViewTools::MinTempTrackButton_Click);
			// 
			// MaxTempTrackButton
			// 
			this->MaxTempTrackButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->MaxTempTrackButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->MaxTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->MaxTempTrackButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->MaxTempTrackButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->MaxTempTrackButton->ForeColor = System::Drawing::Color::White;
			this->MaxTempTrackButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MaxTempTrackButton.Image")));
			this->MaxTempTrackButton->Location = System::Drawing::Point(9, 249);
			this->MaxTempTrackButton->Name = L"MaxTempTrackButton";
			this->MaxTempTrackButton->Size = System::Drawing::Size(64, 48);
			this->MaxTempTrackButton->TabIndex = 20;
			this->MaxTempTrackButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->MaxTempTrackButton, L"Track Maximum Temperature\r\nHotKey: 1");
			this->MaxTempTrackButton->UseVisualStyleBackColor = false;
			this->MaxTempTrackButton->Click += gcnew System::EventHandler(this, &LiveViewTools::MaxTempTrackButton_Click);
			// 
			// AddTempMeasButton
			// 
			this->AddTempMeasButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AddTempMeasButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->AddTempMeasButton->Enabled = false;
			this->AddTempMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AddTempMeasButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AddTempMeasButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->AddTempMeasButton->ForeColor = System::Drawing::Color::White;
			this->AddTempMeasButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AddTempMeasButton.Image")));
			this->AddTempMeasButton->Location = System::Drawing::Point(79, 303);
			this->AddTempMeasButton->Name = L"AddTempMeasButton";
			this->AddTempMeasButton->Size = System::Drawing::Size(64, 48);
			this->AddTempMeasButton->TabIndex = 23;
			this->AddTempMeasButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->AddTempMeasButton, L"Add Temperature Measurement\r\nHotKey: 4");
			this->AddTempMeasButton->UseVisualStyleBackColor = false;
			this->AddTempMeasButton->Click += gcnew System::EventHandler(this, &LiveViewTools::AddTempMeasButton_Click);
			// 
			// CenterTempTrackButton
			// 
			this->CenterTempTrackButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->CenterTempTrackButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->CenterTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->CenterTempTrackButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CenterTempTrackButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CenterTempTrackButton->ForeColor = System::Drawing::Color::White;
			this->CenterTempTrackButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CenterTempTrackButton.Image")));
			this->CenterTempTrackButton->Location = System::Drawing::Point(9, 303);
			this->CenterTempTrackButton->Name = L"CenterTempTrackButton";
			this->CenterTempTrackButton->Size = System::Drawing::Size(64, 48);
			this->CenterTempTrackButton->TabIndex = 22;
			this->CenterTempTrackButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->CenterTempTrackButton, L"Track Center Temperature\r\nHotKey: 3");
			this->CenterTempTrackButton->UseVisualStyleBackColor = false;
			this->CenterTempTrackButton->Click += gcnew System::EventHandler(this, &LiveViewTools::CenterTempTrackButton_Click);
			// 
			// DualColorPaletteButton
			// 
			this->DualColorPaletteButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->DualColorPaletteButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->DualColorPaletteButton->Enabled = false;
			this->DualColorPaletteButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->DualColorPaletteButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DualColorPaletteButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DualColorPaletteButton->ForeColor = System::Drawing::Color::White;
			this->DualColorPaletteButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DualColorPaletteButton.Image")));
			this->DualColorPaletteButton->Location = System::Drawing::Point(9, 465);
			this->DualColorPaletteButton->Name = L"DualColorPaletteButton";
			this->DualColorPaletteButton->Size = System::Drawing::Size(64, 48);
			this->DualColorPaletteButton->TabIndex = 25;
			this->DualColorPaletteButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->DualColorPaletteButton, L"Toggle Live View\r\nDual Color Palette Box\r\nHotKey: 9");
			this->DualColorPaletteButton->UseVisualStyleBackColor = false;
			this->DualColorPaletteButton->Click += gcnew System::EventHandler(this, &LiveViewTools::DualColorPaletteButton_Click);
			// 
			// CursorTempTrackButton
			// 
			this->CursorTempTrackButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->CursorTempTrackButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->CursorTempTrackButton->Enabled = false;
			this->CursorTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->CursorTempTrackButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CursorTempTrackButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CursorTempTrackButton->ForeColor = System::Drawing::Color::White;
			this->CursorTempTrackButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CursorTempTrackButton.Image")));
			this->CursorTempTrackButton->Location = System::Drawing::Point(79, 411);
			this->CursorTempTrackButton->Name = L"CursorTempTrackButton";
			this->CursorTempTrackButton->Size = System::Drawing::Size(64, 48);
			this->CursorTempTrackButton->TabIndex = 26;
			this->CursorTempTrackButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->CursorTempTrackButton, L"Track Mouse Cursor \r\nTemperature\r\nHotKey: 8");
			this->CursorTempTrackButton->UseVisualStyleBackColor = false;
			this->CursorTempTrackButton->Click += gcnew System::EventHandler(this, &LiveViewTools::CursorTempTrackButton_Click);
			// 
			// AddROIMeasButton
			// 
			this->AddROIMeasButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AddROIMeasButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->AddROIMeasButton->Enabled = false;
			this->AddROIMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AddROIMeasButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AddROIMeasButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->AddROIMeasButton->ForeColor = System::Drawing::Color::White;
			this->AddROIMeasButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AddROIMeasButton.Image")));
			this->AddROIMeasButton->Location = System::Drawing::Point(9, 411);
			this->AddROIMeasButton->Name = L"AddROIMeasButton";
			this->AddROIMeasButton->Size = System::Drawing::Size(64, 48);
			this->AddROIMeasButton->TabIndex = 24;
			this->AddROIMeasButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->AddROIMeasButton, L"Add Region Of Interest\r\nAdjustable Box\r\nHotKey: 7");
			this->AddROIMeasButton->UseVisualStyleBackColor = false;
			this->AddROIMeasButton->Click += gcnew System::EventHandler(this, &LiveViewTools::AddROIMeasButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(9, 66);
			this->label1->Margin = System::Windows::Forms::Padding(0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(109, 15);
			this->label1->TabIndex = 32;
			this->label1->Text = L"Live Color Palette:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ColorPaletteComboBox
			// 
			this->ColorPaletteComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ColorPaletteComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ColorPaletteComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ColorPaletteComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ColorPaletteComboBox->ForeColor = System::Drawing::Color::White;
			this->ColorPaletteComboBox->FormattingEnabled = true;
			this->ColorPaletteComboBox->Location = System::Drawing::Point(9, 81);
			this->ColorPaletteComboBox->Margin = System::Windows::Forms::Padding(0);
			this->ColorPaletteComboBox->Name = L"ColorPaletteComboBox";
			this->ColorPaletteComboBox->Size = System::Drawing::Size(134, 24);
			this->ColorPaletteComboBox->TabIndex = 29;
			this->ColorPaletteComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &LiveViewTools::ColorPaletteComboBox_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(9, 105);
			this->label3->Margin = System::Windows::Forms::Padding(0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(111, 15);
			this->label3->TabIndex = 33;
			this->label3->Text = L"Dual Color Palette:";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DualColorPaletteComboBox
			// 
			this->DualColorPaletteComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->DualColorPaletteComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DualColorPaletteComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DualColorPaletteComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->DualColorPaletteComboBox->ForeColor = System::Drawing::Color::White;
			this->DualColorPaletteComboBox->FormattingEnabled = true;
			this->DualColorPaletteComboBox->Location = System::Drawing::Point(9, 120);
			this->DualColorPaletteComboBox->Margin = System::Windows::Forms::Padding(0);
			this->DualColorPaletteComboBox->Name = L"DualColorPaletteComboBox";
			this->DualColorPaletteComboBox->Size = System::Drawing::Size(134, 24);
			this->DualColorPaletteComboBox->TabIndex = 30;
			this->DualColorPaletteComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &LiveViewTools::DualColorPaletteComboBox_SelectedIndexChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(9, 144);
			this->label4->Margin = System::Windows::Forms::Padding(0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(135, 15);
			this->label4->TabIndex = 34;
			this->label4->Text = L"ColorBar Back Palette:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ColorBarBackPaletteComboBox
			// 
			this->ColorBarBackPaletteComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ColorBarBackPaletteComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ColorBarBackPaletteComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ColorBarBackPaletteComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ColorBarBackPaletteComboBox->ForeColor = System::Drawing::Color::White;
			this->ColorBarBackPaletteComboBox->FormattingEnabled = true;
			this->ColorBarBackPaletteComboBox->Location = System::Drawing::Point(9, 159);
			this->ColorBarBackPaletteComboBox->Margin = System::Windows::Forms::Padding(0);
			this->ColorBarBackPaletteComboBox->Name = L"ColorBarBackPaletteComboBox";
			this->ColorBarBackPaletteComboBox->Size = System::Drawing::Size(134, 24);
			this->ColorBarBackPaletteComboBox->TabIndex = 31;
			this->ColorBarBackPaletteComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &LiveViewTools::ColorBarBackPaletteComboBox_SelectedIndexChanged);
			// 
			// LiveViewTooTips
			// 
			this->LiveViewTooTips->AutomaticDelay = 100;
			this->LiveViewTooTips->AutoPopDelay = 5000;
			this->LiveViewTooTips->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->LiveViewTooTips->ForeColor = System::Drawing::Color::White;
			this->LiveViewTooTips->InitialDelay = 100;
			this->LiveViewTooTips->ReshowDelay = 20;
			// 
			// RecordingButton
			// 
			this->RecordingButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->RecordingButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->RecordingButton->Enabled = false;
			this->RecordingButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->RecordingButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RecordingButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->RecordingButton->ForeColor = System::Drawing::Color::White;
			this->RecordingButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"RecordingButton.Image")));
			this->RecordingButton->Location = System::Drawing::Point(79, 627);
			this->RecordingButton->Name = L"RecordingButton";
			this->RecordingButton->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->RecordingButton->Size = System::Drawing::Size(64, 48);
			this->RecordingButton->TabIndex = 35;
			this->RecordingButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->RecordingButton, L"Record Live View Data\r\nFor Post-Analysis.\r\nClick To Toggle Start/Stop");
			this->RecordingButton->UseVisualStyleBackColor = false;
			this->RecordingButton->Click += gcnew System::EventHandler(this, &LiveViewTools::RecordingButton_Click);
			// 
			// SaveTempFrameDataButton
			// 
			this->SaveTempFrameDataButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SaveTempFrameDataButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->SaveTempFrameDataButton->Enabled = false;
			this->SaveTempFrameDataButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SaveTempFrameDataButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SaveTempFrameDataButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->SaveTempFrameDataButton->ForeColor = System::Drawing::Color::White;
			this->SaveTempFrameDataButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SaveTempFrameDataButton.Image")));
			this->SaveTempFrameDataButton->Location = System::Drawing::Point(79, 735);
			this->SaveTempFrameDataButton->Name = L"SaveTempFrameDataButton";
			this->SaveTempFrameDataButton->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->SaveTempFrameDataButton->Size = System::Drawing::Size(64, 48);
			this->SaveTempFrameDataButton->TabIndex = 36;
			this->SaveTempFrameDataButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->SaveTempFrameDataButton, L"Save Full Frame \r\nTemperature Data\r\nTo CSV FIle.");
			this->SaveTempFrameDataButton->UseVisualStyleBackColor = false;
			this->SaveTempFrameDataButton->Click += gcnew System::EventHandler(this, &LiveViewTools::SaveTempFrameDataButton_Click);
			// 
			// ShowLiveViewStatisticsButton
			// 
			this->ShowLiveViewStatisticsButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ShowLiveViewStatisticsButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ShowLiveViewStatisticsButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ShowLiveViewStatisticsButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ShowLiveViewStatisticsButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->ShowLiveViewStatisticsButton->ForeColor = System::Drawing::Color::White;
			this->ShowLiveViewStatisticsButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ShowLiveViewStatisticsButton.Image")));
			this->ShowLiveViewStatisticsButton->Location = System::Drawing::Point(79, 789);
			this->ShowLiveViewStatisticsButton->Name = L"ShowLiveViewStatisticsButton";
			this->ShowLiveViewStatisticsButton->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->ShowLiveViewStatisticsButton->Size = System::Drawing::Size(64, 48);
			this->ShowLiveViewStatisticsButton->TabIndex = 37;
			this->ShowLiveViewStatisticsButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->ShowLiveViewStatisticsButton, L"Show Live View Statistics");
			this->ShowLiveViewStatisticsButton->UseVisualStyleBackColor = false;
			this->ShowLiveViewStatisticsButton->Click += gcnew System::EventHandler(this, &LiveViewTools::ShowLiveViewStatisticsButton_Click);
			// 
			// UltraResolutionButton
			// 
			this->UltraResolutionButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->UltraResolutionButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->UltraResolutionButton->Enabled = false;
			this->UltraResolutionButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->UltraResolutionButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->UltraResolutionButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->UltraResolutionButton->ForeColor = System::Drawing::Color::White;
			this->UltraResolutionButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UltraResolutionButton.Image")));
			this->UltraResolutionButton->Location = System::Drawing::Point(79, 465);
			this->UltraResolutionButton->Name = L"UltraResolutionButton";
			this->UltraResolutionButton->Size = System::Drawing::Size(64, 48);
			this->UltraResolutionButton->TabIndex = 38;
			this->UltraResolutionButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->UltraResolutionButton, L"Toggle Ultra \r\nResolution Mode\r\nHotKey: U");
			this->UltraResolutionButton->UseVisualStyleBackColor = false;
			this->UltraResolutionButton->Click += gcnew System::EventHandler(this, &LiveViewTools::UltraResolutionButton_Click);
			// 
			// PeriodicTimerTriggerButton
			// 
			this->PeriodicTimerTriggerButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->PeriodicTimerTriggerButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->PeriodicTimerTriggerButton->Enabled = false;
			this->PeriodicTimerTriggerButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->PeriodicTimerTriggerButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PeriodicTimerTriggerButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicTimerTriggerButton->ForeColor = System::Drawing::Color::White;
			this->PeriodicTimerTriggerButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PeriodicTimerTriggerButton.Image")));
			this->PeriodicTimerTriggerButton->Location = System::Drawing::Point(79, 681);
			this->PeriodicTimerTriggerButton->Name = L"PeriodicTimerTriggerButton";
			this->PeriodicTimerTriggerButton->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->PeriodicTimerTriggerButton->Size = System::Drawing::Size(64, 48);
			this->PeriodicTimerTriggerButton->TabIndex = 39;
			this->PeriodicTimerTriggerButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->LiveViewTooTips->SetToolTip(this->PeriodicTimerTriggerButton, L"Start Periodic Trigger Timer\r\nHotKey: P");
			this->PeriodicTimerTriggerButton->UseVisualStyleBackColor = false;
			this->PeriodicTimerTriggerButton->Click += gcnew System::EventHandler(this, &LiveViewTools::PeriodicTimerTriggerButton_Click);
			// 
			// LiveViewTools
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(151, 888);
			this->Controls->Add(this->PeriodicTimerTriggerButton);
			this->Controls->Add(this->UltraResolutionButton);
			this->Controls->Add(this->ShowLiveViewStatisticsButton);
			this->Controls->Add(this->SaveTempFrameDataButton);
			this->Controls->Add(this->RecordingButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ColorPaletteComboBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->DualColorPaletteComboBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->ColorBarBackPaletteComboBox);
			this->Controls->Add(this->ShowLineHistButton);
			this->Controls->Add(this->AddTempSpecLineButton);
			this->Controls->Add(this->MinTempTrackButton);
			this->Controls->Add(this->MaxTempTrackButton);
			this->Controls->Add(this->AddTempMeasButton);
			this->Controls->Add(this->CenterTempTrackButton);
			this->Controls->Add(this->DualColorPaletteButton);
			this->Controls->Add(this->CursorTempTrackButton);
			this->Controls->Add(this->AddROIMeasButton);
			this->Controls->Add(this->TempUnitKButton);
			this->Controls->Add(this->SnapshotButton);
			this->Controls->Add(this->TempUnitFButton);
			this->Controls->Add(this->RecordButton);
			this->Controls->Add(this->TempUnitCButton);
			this->Controls->Add(this->FixedAspectRatioButton);
			this->Controls->Add(this->ImageSharpButton);
			this->Controls->Add(this->EnhancedResButton);
			this->Controls->Add(this->LiveViewRunStopButton);
			this->Controls->Add(this->CalibrateCameraButton);
			this->Controls->Add(this->TempRangeButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(170, 888);
			this->MinimumSize = System::Drawing::Size(151, 0);
			this->Name = L"LiveViewTools";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LiveViewTools";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &LiveViewTools::LiveViewTools_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &LiveViewTools::LiveViewTools_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

		// ---------------------- Opstartnings Og Nedluknings Callback Routiner ----------------------- //

		// Live View Tools Form Opstartnings Callback Routine -> 
		private: System::Void LiveViewTools_Shown(System::Object^ sender, System::EventArgs^ e) {

			// Indsæt listen over de tilgængelige Color Palettes i "Color Palette" ComboBox
			RMH_ColorPalette_LoadColorPalettesToCombiBox(this->ColorPaletteComboBox);
			// Indstil "Default" valgte Color Palette 
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->ColorPaletteComboBox, SelectedColorPaletteIndex);

			// Indsæt listen over de tilgængelige Color Palettes i "Dual Color Palette" ComboBox
			RMH_ColorPalette_LoadColorPalettesToCombiBox(this->DualColorPaletteComboBox);
			// Indstil "Default" valgte Dual Color Palette 
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DualColorPaletteComboBox, SelectedDualColorPaletteIndex);

			// Indsæt listen over de tilgængelige Color Palettes i "ColorBar Background Palette" ComboBox
			RMH_ColorPalette_LoadColorPalettesToCombiBox(this->ColorBarBackPaletteComboBox);
			// Indstil "Default" valgte ColorBar Background Palette
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->ColorBarBackPaletteComboBox, 10);

			// Opdater Aspect Ratio Knap border farve, fra Gemt Sessions indstilling
			RMH_ThermalViewer_UpdateAspectRatioButtonBorderColor();

			// Opdater Aktivering eller deaktivering af label baggrunden - fra læst sessions data
			GlobalVariables::OpenGLRender->RMH_OpenGL_EnableLabelBackground(EnableLabelBackgroundFlag);
			// Opdater Live view labels farve - fra læst sessions data
			GlobalVariables::OpenGLRender->RMH_OpenGL_ChangeRenderedLabelsColor(CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);
			// Opdater Live view labels baggrunds farve - fra læst sessions data
			GlobalVariables::OpenGLRender->RMH_OpenGL_ChangeLabelBackgroundColor(CommonLabelBackgroundColorR, CommonLabelBackgroundColorG, CommonLabelBackgroundColorB);

			// Opdater tilhørende form Flag
			isLiveViewToolsFormOpen = true;

		}

		// Live View Tools Form Nedluknings Callback Routine -> 
		private: System::Void LiveViewTools_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Opdater tilhørende form Flag
			isLiveViewToolsFormOpen = false;
			isLiveViewToolsFormDocked = false;
			isLiveViewToolsFormUndocked = false;

			// Når Formen lukkes - Gem Formen
			this->Hide();
			// Deaktiver "Disposing" Af Form Objektet
			e->Cancel = true;

		}

		// --------------------- Live View Run/Stop Knap Event & Callback Routine -------------------- //
		
		// Live View Stream Run/Stop Knap Callback Routine ->
		public: System::Void LiveViewRunStopButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Live View Streamen Run/Stop Stadie
			RMH_ThermalViewer_ToggleLiveViewStreamRunStop();

		}

		// ------------------------- Color Palette ComboBox Callback Routine -------------------------- //
		
		// Color Palette DropDown List Ændret Callback Routine ->
		public: System::Void ColorPaletteComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Live View Color Palette
			RMH_ColorPalette_ChangeColorPalette(this->ColorPaletteComboBox);

			// Lager Valgte Color Palette til globale variabel til gemt sessions parameter
			SelectedColorPaletteIndex = GlobalVariables::GlobalColorPaletteComboBox->SelectedIndex;

		}

		// Dual Color Palette DropDown List Ændret Callback Routine ->
		public: System::Void DualColorPaletteComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Live View Dual Color Palette
			RMH_ColorPalette_ChangeDualColorPalette(this->DualColorPaletteComboBox);

			// Lager Valgte Dual Color Palette til globale variabel til gemt sessions parameter
			SelectedDualColorPaletteIndex = GlobalVariables::GlobalDualColorPaletteComboBox->SelectedIndex;

		}

		// Baggrund Color Palette DropDown List Ændret Callback Routine ->
		public: System::Void ColorBarBackPaletteComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Colorbarens Baggrunds Color Palette
			RMH_ColorPalette_ChangeColorBarBackgroundColorPalette(this->ColorBarBackPaletteComboBox);

		}

		// --------------------- Kamera Kalibrerings Knap Event & Callback Routine -------------------- //

		// Kamera kalibrerings knap Callback Routine ->
		public: System::Void CalibrateCameraButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Kalibrer forbundet Termiske Kamera
			RMH_IRThermalCamera_CalibrateThermalCamera();

		}

		// -------------------- Kamera Temperatur Range Knap Event Callback Routine ------------------- //

		// Kamera Temperatur Range Knap Callback Routine ->
		public: System::Void TempRangeButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Skift Kamera Temperatur Range
			RMH_IRThermalCamera_ChangeThermalCameraTemperatureRange();

		}

		// -------------------- Max/Min Og Center Temp Track Knap Callback Routiner ------------------- //

		// Maximum Temperatur Tracking Knap Callback Routine ->
		public: System::Void MaxTempTrackButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggel live view maximum temperatur tracking
			RMH_ThermalViewer_ToggleMaximumTempTracking();

		}

		// Minimum Temperatur Tracking Knap Callback Routine ->
		public: System::Void MinTempTrackButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggel live view minimum temperatur tracking
			RMH_ThermalViewer_ToggleMinimumTempTracking();

		}

		// Center Temperatur Tracking Knap Callback Routine ->
		public: System::Void CenterTempTrackButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggel live view center temperatur tracking
			RMH_ThermalViewer_ToggleCenterTempTracking();

		}
		
		// ------------------------ Add Temp Measurement Knap Callback Routine ------------------------ //

		// Tilføj Temperatur Measurement Label Knap Callback Routine ->
		public: System::Void AddTempMeasButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver temperatur måling til renderering på Live View streamen
			RMH_ThermalViewer_AddTemperatureMeasurementToLiveView();

		}

		// ----------------------- Add Temp Spectrum Line Knap Callback Routine ----------------------- //
		
		// Tilføj Temperatur Linje Knap Callback Routine ->
		public: System::Void AddTempSpecLineButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver temperatur linje til renderering på Live View streamen
			RMH_ThermalViewer_AddTemperatureLineToLiveView();

		}

		// --------------------- Live View Histogram Knap Event & Callback Routine -------------------- //

		// Vis live view histogram Knap Callback Routine ->
		public: System::Void ShowLineHistButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver live view streamens Histogram feature for linjer og frame data
			RMH_ThermalViewer_EnableLiveViewHistogram();

		}

		// -------------------------- Add Live ROI Box Knap Callback Routine -------------------------- //
		
		// Tilføj ROI Box Knap Callback Routine ->
		public: System::Void AddROIMeasButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver ROI til renderering på Live View streamen
			RMH_ThermalViewer_AddRegionOfInterestBoxToLiveView();

		}
		
		// -------------------- Mus Punkt Temperatur Tracking Knap Callback Routine ------------------- //
		
		// Mus Temperatur Tracking Knap Callback Routine ->
		public: System::Void CursorTempTrackButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggel live view Mus Cursor temperatur tracking
			RMH_ThermalViewer_ToggleMouseCursorTempTracking();

		}
		
		// ------------------------- Dual Color Palette Knap Callback Routine ------------------------- //
		
		// Dual Color Palette Knap Callback Routine ->
		public: System::Void DualColorPaletteButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Dual Color palette aktiverings flag
			DualColorPaletteEnableFlag = !DualColorPaletteEnableFlag;

			// Håndter event ved aktivering af Dual live View Color Palettes
			RMH_ColorPalette_EnableDualColorPalettes(this->DualColorPaletteButton);

			// Resize Dual Color Palette panel
			this->DualColorPaletteComboBox_SelectedIndexChanged(nullptr, nullptr);

			// Aktiver eller deaktiver Histogram Context sub menu hvis dual palette er aktiv
			if (DualColorPaletteEnableFlag == true) {

				// Aktiver relavant Histogram Context sub menu
				GlobalVariables::GlobaluseDualPaletteToolStripMenuItem->Enabled = true;

			}
			else {

				// Deaktiver relavant Histogram Context sub menu
				GlobalVariables::GlobaluseDualPaletteToolStripMenuItem->Enabled = false;

			}

		}

		// -------------------- Live View Enhanced Opløsnings Knap Callback Routine ------------------- //

		// Enhanced Opløsnings Knap Callback Routine ->
		public: System::Void EnhancedResButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Enable Flag
			EnhancedResEnableFlag = !EnhancedResEnableFlag;

			// Toggel Live view enhanced billed opløsnings mode
			RMH_ThermalViewer_ToggleEnhancedLiveViewResolution();

		}
		
		// Ultra Opløsnings Feature Knap Callback Routine ->
		public: System::Void UltraResolutionButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle live view Ultra Opløsnings aktiverings flaget
			UltraResolutionEnableFlag = !UltraResolutionEnableFlag;

			// Toggel Live view Ultra opløsnings mode
			RMH_ThermalViewer_ToggleLiveViewUltraResolution();

		}
		
		// --------------------- Live View Image Sharpening Knap Callback Routine --------------------- //

		// Image Sharpening Knap Callback Routine ->
		public: System::Void ImageSharpButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggel Live view Image Sharpening feature
			RMH_ThermalViewer_ToggleLiveViewImageSharpening();

		}

		// ------------------- Live View Aspect Ratio Knap Event & Callback Routine ------------------- //
		
		// Fast Aspect Ratio Knap Callback Routine ->
		public: System::Void FixedAspectRatioButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Aspect Ratio parameter
			FixedLiveViewAspectRatio = !FixedLiveViewAspectRatio;

			// Opdater Aspect Ratio Knap border farve
			RMH_ThermalViewer_UpdateAspectRatioButtonBorderColor();

		}

		// ----------------------- Take SnapShot Knap Event & Callback Routine ------------------------ //

		// Tag et Snapshot Knap Callback Routine ->
		public: System::Void SnapshotButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Gem et live view snapshot
			RMH_ThermalViewer_SaveLiveViewSnapshot();

		}

		// ----------------------- Video Capture Knap Event & Callback Routine ------------------------ //
		
		// Optag Applikations video knap Callback Routine ->
		public: System::Void RecordButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Åben valgte Default Video Capturing Program
			RMH_ThermalViewer_OpenDefaultVideoCapturingApp();

		}

		// ------------------------ Optag Video Knap Event & Callback Routine ------------------------- //

		// Start Eller Stop Data Optagning knap Callback Routine ->
		private: System::Void RecordingButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Video optagnings flag
			VideoRecordingStartedFlag = !VideoRecordingStartedFlag;

			// Start eller Stop Video Optagning
			RMH_ThermalViewer_StartStopVideoRecording();

		}

		// ------------------- Temperatur Enheds Knappers Event & Callback Routiner ------------------- //

		// Nested Temperatur Enheds Kanppernes Event Callback routine ->
		public: System::Void TempUnitCButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Ændre Temperatur Målingernes Enhed
			RMH_ThermalViewer_ChangeTemperatureUnit(sender);

			// Læs Maximum, Minimum Og Center Temperaturer
			RMH_ThermalViewer_ReadMaxMinCentTemperatures();

			// Opdater Colorbarens start Manuelle Temperatur range værdier til frame Max/Min Temperaturerne ved Range Skift 
			ColorBarInitialManualRangeMaxTemp = MaximumTemperature;
			ColorBarInitialManualRangeMinTemp = MinimumTemperature;

			// Kontroller om ColorBar Temp Ranges Dialog Vinduet er åbent
			if (ColorBarDialogIsShownFlag == true) {

				// Opdater ColorBar Range Dialogen med relavante værdier og indstiller temperatur enheds stringet
				ColorBarRangeDialogForm->UpdateColorBarTempRangeDialogValues(MaximumTemperature, MinimumTemperature, GlobalVariables::DefaultTempUnitString);

			}

		}

		// ----------- Gem Fuld Frame Temperatur Data Til CSV Knap Event & Callback Routiner ----------- //

		// Gem Fuld Frame Temperatur Data Til CSV Knap Callback routine ->
		private: System::Void SaveTempFrameDataButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Generer og Gem en Fuld Frame Temperatur Data CSV fil
			RMH_ThermalViewer_SaveFullFrameTemperatureDataToCSVFile();

		}

		// -------------- Vis Live View Statistik Vindue Knap Event & Callback Routiner --------------- //

		// Vis Live View Statistik Vindue Knap Callback routine ->
		private: System::Void ShowLiveViewStatisticsButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Åben Live View Statistik Vinduet
			ShowLiveViewStatisticsWindowForm();

		}
		
		// --------------- Start Periodisk Trigger Timer Knap Event & Callback Routiner --------------- //

		// Start Periodisk Trigger Timer Knap Callback routine ->
		public: System::Void PeriodicTimerTriggerButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Hvis Live View streamen er i STOP Mode
			if (LiveViewRunStopFlag == false) {

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "The Periodic Trigger Timer Is Disabled. (Can Only Be Enabled In Live View Start/RUN Mode)", _StatusMessageType_Warning);

			}

			// Toggle Aktiveringen af den periodiske trigger timer
			RMH_ThermalViewer_TogglePeriodicTriggerTimer();

		}

		// -------------------------------------------------------------------------------------------- //

};
}
