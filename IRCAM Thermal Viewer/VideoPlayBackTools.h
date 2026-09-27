#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"
#include "RMH_Winforms_Library.h"
#include <iostream>

// Globale Statiske klasse objekter og variabler
static unsigned char ElapsedTimeStringChar[] = { '0','0','0',':','0','0',':','0','0',':','0','0','0' };
static unsigned char RemainingTimeStringChar[] = { '0','0','0',':','0','0',':','0','0',':','0','0','0' };

// Klasse Namespace
namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	// Summary for Form - VideoPlayBackTools
	public ref class VideoPlayBackTools : public System::Windows::Forms::Form {

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		VideoPlayBackTools() {

			// Init GUI komponenter og objekter
			InitializeComponent();
			// Indstil globale objekter fra denne Form til global brug
			InitializeGlobalFormsObjects();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Læs Valgte Video fils informations parametere 
			RecordingAnalysisModeFileInfo = RMH_VideoFileReading_SetupRecordingAnalysisModeVideoFileReader(GlobalVariables::RecordingAnalysisModeRAWFilePath);

			// Opdater "Video Playback Formen Er Åben" flaget
			VideoPlaybackControlsFormIsOpenFlag = true;

			// Opdaterer Teksten i toppen af GUIens TitelBar
			RMH_Winforms_ChangeFormTitleBarText(this, "Video Playback Controls");

			// Opdater Termisk Kamera konfigurations labels
			this->TempCorrectionLabel->Text = RMH_Conversion_FloatToSystemString(IRCamera.TemperatureCorrectionSetting) + " " + GlobalVariables::DefaultTempUnitString;
			this->AmbientTempLabel->Text = RMH_Conversion_FloatToSystemString(IRCamera.AmbientTemperatureSetting) + " " + GlobalVariables::DefaultTempUnitString;
			this->ReflectedTempLabel->Text = RMH_Conversion_FloatToSystemString(IRCamera.ReflectedTemperatureSetting) + " " + GlobalVariables::DefaultTempUnitString;
			this->HumidityLabel->Text = RMH_Conversion_FloatToSystemString(IRCamera.HumiditySetting) + " " + "%RH";
			this->EmissivityLabel->Text = RMH_Conversion_FloatToSystemString(IRCamera.EmissivitySetting);
			this->DistanceLabel->Text = RMH_Conversion_IntToSystemString(IRCamera.DistanceSetting) + " " + "Meter";

			// Nulstil Nuværende Frame Indeks værdi
			CurrentPlayBackFrameValue = 0;
			// Nulstil TrackBar position
			this->FrameTrackBar->Value = CurrentPlayBackFrameValue;
			// Indstil TrackBarens Maksimale grænse værdi til det maksimale antal læste frames
			this->FrameTrackBar->Maximum = RecordingAnalysisModeFileInfo.NumberOfFrames;
			
			// Opdater Video Informations labels
			this->VideoDurationLabel->Text = RMH_Conversion_FloatToSystemString(RecordingAnalysisModeFileInfo.DurationTime) + " Sec";
			this->NumOfFramesLabel->Text = RMH_Conversion_IntToSystemString(RecordingAnalysisModeFileInfo.NumberOfFrames) + " Frames";
			this->CurrentFrameLabel->Text = RMH_Conversion_IntToSystemString(CurrentPlayBackFrameValue) + " Frames";
			this->FrameRateLabel->Text = RMH_Conversion_IntToSystemString(RecordingAnalysisModeFileInfo.FrameRate) + " FPS";
			this->FrameWidthLabel->Text = RMH_Conversion_IntToSystemString(RecordingAnalysisModeFileInfo.FrameWidth) + " Pixels";
			this->FrameHeightLabel->Text = RMH_Conversion_IntToSystemString(RecordingAnalysisModeFileInfo.FrameHeight - IRCamera.FrameMetadataSize) + " Pixels";

			// Opdater tilbageværende og Forløbet tids labels
			FormatUpdataAndDisplayElapsedAndRemainingTimeLabels();

		}

		// ---------------------------- Diverse Specifikke Klasse Metoder ----------------------------- //

		void InitializeGlobalFormsObjects() {

			// Routinen indstiller globale objekter fra denne form
			// Så disse kan blve tilgået fra andre Forms

			// Initiliser Globale objeker til tilhørende Form Objekter
			GlobalVariables::VideoPlaybackTempCorrectionLabel = this->TempCorrectionLabel;
			GlobalVariables::VideoPlaybackAmbientTempLabel = this->AmbientTempLabel;
			GlobalVariables::VideoPlaybackReflectedTempLabel = this->ReflectedTempLabel;
			GlobalVariables::VideoPlaybackForwardStepButton = this->ForwardStepButton;
			GlobalVariables::VideoPlaybackBackwardStepButton = this->BackwardStepButton;
			GlobalVariables::VideoPlaybackPlayStopButton = this->PlayStopButton;

		}

		void FormatUpdataAndDisplayElapsedAndRemainingTimeLabels() {

			// Routinen konverterer og håndtererr opdateringen af de to Elapsed time og Remaining Time Labels

			// Udregn hver video frames tids periode i sekunter
			double FramePeriod = RecordingAnalysisModeFileInfo.DurationTime / (double)RecordingAnalysisModeFileInfo.NumberOfFrames;
			// Udregn video filens varighed i MilliSekunter
			double TotalVideoDurationMilliSec = RecordingAnalysisModeFileInfo.DurationTime * 1000.0;

			// Udregn den forløbet tid fra nuværende playback frame nummer 
			unsigned long ElapsedTimeValueMilliSec = (unsigned long)((FramePeriod * 1000.0) * (double)CurrentPlayBackFrameValue);
			// Udregn den tilbageværende tid fra nuværende playback frame nummer 
			unsigned long RemainingTimeTimeValueMilliSec = (unsigned long)(TotalVideoDurationMilliSec - (double)ElapsedTimeValueMilliSec);

			// Formater "Elapsed" tids label
			unsigned int HoursValue = (ElapsedTimeValueMilliSec / 3600000) % 720;
			unsigned int MinutesValue = (ElapsedTimeValueMilliSec / 60000) % 60;
			unsigned int SecondsValue = (ElapsedTimeValueMilliSec / 1000) % 60;
			unsigned int MilliSecValue = ElapsedTimeValueMilliSec % 1000;

			// Konverterog formater  Timer, Minutter, Sekundter og millisekundter for "Elapsed Time" label string
			ElapsedTimeStringChar[0] = (HoursValue / 100) % 10 + 48;
			ElapsedTimeStringChar[1] = (HoursValue / 10) % 10 + 48;
			ElapsedTimeStringChar[2] = HoursValue % 10 + 48;
			ElapsedTimeStringChar[4] = (MinutesValue / 10) % 10 + 48;
			ElapsedTimeStringChar[5] = MinutesValue % 10 + 48;
			ElapsedTimeStringChar[7] = (SecondsValue / 10) % 10 + 48;
			ElapsedTimeStringChar[8] = SecondsValue % 10 + 48;
			ElapsedTimeStringChar[10] = (MilliSecValue / 100) % 10 + 48;
			ElapsedTimeStringChar[11] = (MilliSecValue / 10) % 10 + 48;
			ElapsedTimeStringChar[12] = MilliSecValue % 10 + 48;

			// Formater "Remaining" tids label
			HoursValue = (RemainingTimeTimeValueMilliSec / 3600000) % 720;
			MinutesValue = (RemainingTimeTimeValueMilliSec / 60000) % 60;
			SecondsValue = (RemainingTimeTimeValueMilliSec / 1000) % 60;
			MilliSecValue = RemainingTimeTimeValueMilliSec % 1000;

			// Konverterog formater  Timer, Minutter, Sekundter og millisekundter for "Remaining Time" label string
			RemainingTimeStringChar[0] = (HoursValue / 100) % 10 + 48;
			RemainingTimeStringChar[1] = (HoursValue / 10) % 10 + 48;
			RemainingTimeStringChar[2] = HoursValue % 10 + 48;
			RemainingTimeStringChar[4] = (MinutesValue / 10) % 10 + 48;
			RemainingTimeStringChar[5] = MinutesValue % 10 + 48;
			RemainingTimeStringChar[7] = (SecondsValue / 10) % 10 + 48;
			RemainingTimeStringChar[8] = SecondsValue % 10 + 48;
			RemainingTimeStringChar[10] = (MilliSecValue / 100) % 10 + 48;
			RemainingTimeStringChar[11] = (MilliSecValue / 10) % 10 + 48;
			RemainingTimeStringChar[12] = MilliSecValue % 10 + 48;

			// Opdater "Elapsed" og "Remaining" tids labels
			this->ElapsedTimeLabel->Text = RMH_Conversion_UnsignedCharArrayToSystemString(ElapsedTimeStringChar, 13);
			this->RemainingTimeLabel->Text = RMH_Conversion_UnsignedCharArrayToSystemString(RemainingTimeStringChar, 13);

		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~VideoPlayBackTools() {

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
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		private: System::Windows::Forms::TrackBar^ FrameTrackBar;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
		private: System::Windows::Forms::Label^ RemainingTimeLabel;
		private: System::Windows::Forms::Label^ ElapsedTimeLabel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
		private: System::Windows::Forms::Button^ PlayStopButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel6;
		private: System::Windows::Forms::Label^ label4;
		private: System::Windows::Forms::Button^ ForwardStepButton;
		private: System::Windows::Forms::Button^ BackwardStepButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel7;
		private: System::Windows::Forms::Label^ label10;
		private: System::Windows::Forms::Label^ label5;
		private: System::Windows::Forms::Label^ label6;
		private: System::Windows::Forms::Label^ label8;
		private: System::Windows::Forms::Label^ label9;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel8;
		private: System::Windows::Forms::Label^ label11;
		private: System::Windows::Forms::Label^ label12;
		private: System::Windows::Forms::Label^ label13;
		private: System::Windows::Forms::Label^ label14;
		private: System::Windows::Forms::Label^ label15;
		private: System::Windows::Forms::Label^ label16;
		private: System::Windows::Forms::Label^ DistanceLabel;
		private: System::Windows::Forms::Label^ EmissivityLabel;
		private: System::Windows::Forms::Label^ HumidityLabel;
		private: System::Windows::Forms::Label^ ReflectedTempLabel;
		private: System::Windows::Forms::Label^ AmbientTempLabel;
		private: System::Windows::Forms::Label^ TempCorrectionLabel;
		private: System::Windows::Forms::Label^ VideoDurationLabel;
		private: System::Windows::Forms::Label^ NumOfFramesLabel;
		private: System::Windows::Forms::Label^ FrameRateLabel;
		private: System::Windows::Forms::Label^ FrameWidthLabel;
		private: System::Windows::Forms::Label^ FrameHeightLabel;
		private: System::Windows::Forms::Label^ CurrentFrameLabel;
		private: System::Windows::Forms::ToolTip^ PlayBackToolTips;
		private: System::Windows::Forms::Timer^ PlayTimer;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel9;
		private: System::Windows::Forms::CheckBox^ TopMostCheckBox;
		private: System::Windows::Forms::Label^ label1;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(VideoPlayBackTools::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DistanceLabel = (gcnew System::Windows::Forms::Label());
			this->EmissivityLabel = (gcnew System::Windows::Forms::Label());
			this->HumidityLabel = (gcnew System::Windows::Forms::Label());
			this->ReflectedTempLabel = (gcnew System::Windows::Forms::Label());
			this->AmbientTempLabel = (gcnew System::Windows::Forms::Label());
			this->TempCorrectionLabel = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->CurrentFrameLabel = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->VideoDurationLabel = (gcnew System::Windows::Forms::Label());
			this->NumOfFramesLabel = (gcnew System::Windows::Forms::Label());
			this->FrameRateLabel = (gcnew System::Windows::Forms::Label());
			this->FrameWidthLabel = (gcnew System::Windows::Forms::Label());
			this->FrameHeightLabel = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->FrameTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->RemainingTimeLabel = (gcnew System::Windows::Forms::Label());
			this->ForwardStepButton = (gcnew System::Windows::Forms::Button());
			this->BackwardStepButton = (gcnew System::Windows::Forms::Button());
			this->PlayStopButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->ElapsedTimeLabel = (gcnew System::Windows::Forms::Label());
			this->TopMostCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PlayBackToolTips = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->PlayTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel6->SuspendLayout();
			this->tableLayoutPanel8->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FrameTrackBar))->BeginInit();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->tableLayoutPanel9->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel6, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 1, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(609, 140);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel6->ColumnCount = 1;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel8, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->label4, 0, 0);
			this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel6->Location = System::Drawing::Point(5, 5);
			this->tableLayoutPanel6->Margin = System::Windows::Forms::Padding(5);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 2;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.3F)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 85.7F)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(294, 130);
			this->tableLayoutPanel6->TabIndex = 2;
			// 
			// tableLayoutPanel8
			// 
			this->tableLayoutPanel8->ColumnCount = 2;
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				60)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40)));
			this->tableLayoutPanel8->Controls->Add(this->DistanceLabel, 1, 5);
			this->tableLayoutPanel8->Controls->Add(this->EmissivityLabel, 1, 4);
			this->tableLayoutPanel8->Controls->Add(this->HumidityLabel, 1, 3);
			this->tableLayoutPanel8->Controls->Add(this->ReflectedTempLabel, 1, 2);
			this->tableLayoutPanel8->Controls->Add(this->AmbientTempLabel, 1, 1);
			this->tableLayoutPanel8->Controls->Add(this->TempCorrectionLabel, 1, 0);
			this->tableLayoutPanel8->Controls->Add(this->label11, 0, 5);
			this->tableLayoutPanel8->Controls->Add(this->label12, 0, 0);
			this->tableLayoutPanel8->Controls->Add(this->label13, 0, 1);
			this->tableLayoutPanel8->Controls->Add(this->label14, 0, 2);
			this->tableLayoutPanel8->Controls->Add(this->label15, 0, 3);
			this->tableLayoutPanel8->Controls->Add(this->label16, 0, 4);
			this->tableLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel8->Location = System::Drawing::Point(4, 23);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 6;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(286, 103);
			this->tableLayoutPanel8->TabIndex = 30;
			// 
			// DistanceLabel
			// 
			this->DistanceLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DistanceLabel->AutoSize = true;
			this->DistanceLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DistanceLabel->ForeColor = System::Drawing::Color::White;
			this->DistanceLabel->Location = System::Drawing::Point(213, 86);
			this->DistanceLabel->Name = L"DistanceLabel";
			this->DistanceLabel->Size = System::Drawing::Size(31, 15);
			this->DistanceLabel->TabIndex = 40;
			this->DistanceLabel->Text = L"NAN";
			this->DistanceLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// EmissivityLabel
			// 
			this->EmissivityLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->EmissivityLabel->AutoSize = true;
			this->EmissivityLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->EmissivityLabel->ForeColor = System::Drawing::Color::White;
			this->EmissivityLabel->Location = System::Drawing::Point(213, 69);
			this->EmissivityLabel->Name = L"EmissivityLabel";
			this->EmissivityLabel->Size = System::Drawing::Size(31, 15);
			this->EmissivityLabel->TabIndex = 39;
			this->EmissivityLabel->Text = L"NAN";
			this->EmissivityLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// HumidityLabel
			// 
			this->HumidityLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->HumidityLabel->AutoSize = true;
			this->HumidityLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->HumidityLabel->ForeColor = System::Drawing::Color::White;
			this->HumidityLabel->Location = System::Drawing::Point(213, 52);
			this->HumidityLabel->Name = L"HumidityLabel";
			this->HumidityLabel->Size = System::Drawing::Size(31, 15);
			this->HumidityLabel->TabIndex = 38;
			this->HumidityLabel->Text = L"NAN";
			this->HumidityLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ReflectedTempLabel
			// 
			this->ReflectedTempLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ReflectedTempLabel->AutoSize = true;
			this->ReflectedTempLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->ReflectedTempLabel->ForeColor = System::Drawing::Color::White;
			this->ReflectedTempLabel->Location = System::Drawing::Point(213, 35);
			this->ReflectedTempLabel->Name = L"ReflectedTempLabel";
			this->ReflectedTempLabel->Size = System::Drawing::Size(31, 15);
			this->ReflectedTempLabel->TabIndex = 37;
			this->ReflectedTempLabel->Text = L"NAN";
			this->ReflectedTempLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// AmbientTempLabel
			// 
			this->AmbientTempLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->AmbientTempLabel->AutoSize = true;
			this->AmbientTempLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->AmbientTempLabel->ForeColor = System::Drawing::Color::White;
			this->AmbientTempLabel->Location = System::Drawing::Point(213, 18);
			this->AmbientTempLabel->Name = L"AmbientTempLabel";
			this->AmbientTempLabel->Size = System::Drawing::Size(31, 15);
			this->AmbientTempLabel->TabIndex = 36;
			this->AmbientTempLabel->Text = L"NAN";
			this->AmbientTempLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempCorrectionLabel
			// 
			this->TempCorrectionLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempCorrectionLabel->AutoSize = true;
			this->TempCorrectionLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempCorrectionLabel->ForeColor = System::Drawing::Color::White;
			this->TempCorrectionLabel->Location = System::Drawing::Point(213, 1);
			this->TempCorrectionLabel->Name = L"TempCorrectionLabel";
			this->TempCorrectionLabel->Size = System::Drawing::Size(31, 15);
			this->TempCorrectionLabel->TabIndex = 35;
			this->TempCorrectionLabel->Text = L"NAN";
			this->TempCorrectionLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label11
			// 
			this->label11->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(3, 86);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(100, 15);
			this->label11->TabIndex = 34;
			this->label11->Text = L"Object Distance:";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label12
			// 
			this->label12->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(3, 1);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(146, 15);
			this->label12->TabIndex = 29;
			this->label12->Text = L"Temperature Correction:";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label13
			// 
			this->label13->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(3, 18);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(133, 15);
			this->label13->TabIndex = 30;
			this->label13->Text = L"Ambient Temperature:";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label14
			// 
			this->label14->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(3, 35);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(140, 15);
			this->label14->TabIndex = 31;
			this->label14->Text = L"Reflected Temperature:";
			this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label15
			// 
			this->label15->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(3, 52);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(132, 15);
			this->label15->TabIndex = 32;
			this->label15->Text = L"Surrounding Humidity:";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label16
			// 
			this->label16->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->Location = System::Drawing::Point(3, 69);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(107, 15);
			this->label16->TabIndex = 33;
			this->label16->Text = L"Object Emissivity:";
			this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(55, 2);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(184, 15);
			this->label4->TabIndex = 28;
			this->label4->Text = L"Thermal Camera Configuration:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel7, 0, 1);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(309, 5);
			this->tableLayoutPanel2->Margin = System::Windows::Forms::Padding(5);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.3F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 85.7F)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(295, 130);
			this->tableLayoutPanel2->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(92, 2);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(110, 15);
			this->label2->TabIndex = 28;
			this->label2->Text = L"Video Information:";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel7
			// 
			this->tableLayoutPanel7->ColumnCount = 2;
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				60)));
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40)));
			this->tableLayoutPanel7->Controls->Add(this->CurrentFrameLabel, 1, 2);
			this->tableLayoutPanel7->Controls->Add(this->label5, 0, 0);
			this->tableLayoutPanel7->Controls->Add(this->label1, 0, 2);
			this->tableLayoutPanel7->Controls->Add(this->label6, 0, 1);
			this->tableLayoutPanel7->Controls->Add(this->label8, 0, 3);
			this->tableLayoutPanel7->Controls->Add(this->label9, 0, 4);
			this->tableLayoutPanel7->Controls->Add(this->VideoDurationLabel, 1, 0);
			this->tableLayoutPanel7->Controls->Add(this->NumOfFramesLabel, 1, 1);
			this->tableLayoutPanel7->Controls->Add(this->FrameRateLabel, 1, 3);
			this->tableLayoutPanel7->Controls->Add(this->FrameWidthLabel, 1, 4);
			this->tableLayoutPanel7->Controls->Add(this->FrameHeightLabel, 1, 5);
			this->tableLayoutPanel7->Controls->Add(this->label10, 0, 5);
			this->tableLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel7->Location = System::Drawing::Point(4, 23);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 6;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(287, 103);
			this->tableLayoutPanel7->TabIndex = 29;
			// 
			// CurrentFrameLabel
			// 
			this->CurrentFrameLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->CurrentFrameLabel->AutoSize = true;
			this->CurrentFrameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CurrentFrameLabel->ForeColor = System::Drawing::Color::White;
			this->CurrentFrameLabel->Location = System::Drawing::Point(214, 35);
			this->CurrentFrameLabel->Name = L"CurrentFrameLabel";
			this->CurrentFrameLabel->Size = System::Drawing::Size(31, 15);
			this->CurrentFrameLabel->TabIndex = 41;
			this->CurrentFrameLabel->Text = L"NAN";
			this->CurrentFrameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(3, 1);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(126, 15);
			this->label5->TabIndex = 29;
			this->label5->Text = L"Video Duration [Sec]:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(3, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 15);
			this->label1->TabIndex = 30;
			this->label1->Text = L"Current Frame:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(3, 18);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(114, 15);
			this->label6->TabIndex = 30;
			this->label6->Text = L"Number Of Frames";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(3, 52);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(110, 15);
			this->label8->TabIndex = 32;
			this->label8->Text = L"Video Frame Rate:";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label9
			// 
			this->label9->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(3, 69);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(117, 15);
			this->label9->TabIndex = 33;
			this->label9->Text = L"Video Frame Width:";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// VideoDurationLabel
			// 
			this->VideoDurationLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->VideoDurationLabel->AutoSize = true;
			this->VideoDurationLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->VideoDurationLabel->ForeColor = System::Drawing::Color::White;
			this->VideoDurationLabel->Location = System::Drawing::Point(214, 1);
			this->VideoDurationLabel->Name = L"VideoDurationLabel";
			this->VideoDurationLabel->Size = System::Drawing::Size(31, 15);
			this->VideoDurationLabel->TabIndex = 36;
			this->VideoDurationLabel->Text = L"NAN";
			this->VideoDurationLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// NumOfFramesLabel
			// 
			this->NumOfFramesLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->NumOfFramesLabel->AutoSize = true;
			this->NumOfFramesLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->NumOfFramesLabel->ForeColor = System::Drawing::Color::White;
			this->NumOfFramesLabel->Location = System::Drawing::Point(214, 18);
			this->NumOfFramesLabel->Name = L"NumOfFramesLabel";
			this->NumOfFramesLabel->Size = System::Drawing::Size(31, 15);
			this->NumOfFramesLabel->TabIndex = 37;
			this->NumOfFramesLabel->Text = L"NAN";
			this->NumOfFramesLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FrameRateLabel
			// 
			this->FrameRateLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->FrameRateLabel->AutoSize = true;
			this->FrameRateLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->FrameRateLabel->ForeColor = System::Drawing::Color::White;
			this->FrameRateLabel->Location = System::Drawing::Point(214, 52);
			this->FrameRateLabel->Name = L"FrameRateLabel";
			this->FrameRateLabel->Size = System::Drawing::Size(31, 15);
			this->FrameRateLabel->TabIndex = 39;
			this->FrameRateLabel->Text = L"NAN";
			this->FrameRateLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FrameWidthLabel
			// 
			this->FrameWidthLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->FrameWidthLabel->AutoSize = true;
			this->FrameWidthLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->FrameWidthLabel->ForeColor = System::Drawing::Color::White;
			this->FrameWidthLabel->Location = System::Drawing::Point(214, 69);
			this->FrameWidthLabel->Name = L"FrameWidthLabel";
			this->FrameWidthLabel->Size = System::Drawing::Size(31, 15);
			this->FrameWidthLabel->TabIndex = 40;
			this->FrameWidthLabel->Text = L"NAN";
			this->FrameWidthLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FrameHeightLabel
			// 
			this->FrameHeightLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->FrameHeightLabel->AutoSize = true;
			this->FrameHeightLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->FrameHeightLabel->ForeColor = System::Drawing::Color::White;
			this->FrameHeightLabel->Location = System::Drawing::Point(214, 86);
			this->FrameHeightLabel->Name = L"FrameHeightLabel";
			this->FrameHeightLabel->Size = System::Drawing::Size(31, 15);
			this->FrameHeightLabel->TabIndex = 41;
			this->FrameHeightLabel->Text = L"NAN";
			this->FrameHeightLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label10
			// 
			this->label10->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(3, 86);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(120, 15);
			this->label10->TabIndex = 34;
			this->label10->Text = L"Video Frame Height:";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FrameTrackBar
			// 
			this->FrameTrackBar->Dock = System::Windows::Forms::DockStyle::Fill;
			this->FrameTrackBar->Location = System::Drawing::Point(3, 3);
			this->FrameTrackBar->Name = L"FrameTrackBar";
			this->FrameTrackBar->Size = System::Drawing::Size(603, 25);
			this->FrameTrackBar->TabIndex = 0;
			this->FrameTrackBar->TickFrequency = 0;
			this->FrameTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
			this->FrameTrackBar->ValueChanged += gcnew System::EventHandler(this, &VideoPlayBackTools::FrameTrackBar_ValueChanged);
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 1;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel4, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel1, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel5, 0, 2);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 3;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 31)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 52)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(615, 229);
			this->tableLayoutPanel3->TabIndex = 1;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel4->Controls->Add(this->FrameTrackBar, 0, 0);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 146);
			this->tableLayoutPanel4->Margin = System::Windows::Forms::Padding(3, 0, 3, 0);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(609, 31);
			this->tableLayoutPanel4->TabIndex = 2;
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 5;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				29.64912F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				10.26316F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				11.40351F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				28.94737F)));
			this->tableLayoutPanel5->Controls->Add(this->RemainingTimeLabel, 4, 0);
			this->tableLayoutPanel5->Controls->Add(this->ForwardStepButton, 3, 0);
			this->tableLayoutPanel5->Controls->Add(this->BackwardStepButton, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->PlayStopButton, 2, 0);
			this->tableLayoutPanel5->Controls->Add(this->tableLayoutPanel9, 0, 0);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(3, 177);
			this->tableLayoutPanel5->Margin = System::Windows::Forms::Padding(3, 0, 3, 3);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 1;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(609, 49);
			this->tableLayoutPanel5->TabIndex = 3;
			// 
			// RemainingTimeLabel
			// 
			this->RemainingTimeLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->RemainingTimeLabel->AutoSize = true;
			this->RemainingTimeLabel->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Bold));
			this->RemainingTimeLabel->ForeColor = System::Drawing::Color::White;
			this->RemainingTimeLabel->Location = System::Drawing::Point(518, 0);
			this->RemainingTimeLabel->Margin = System::Windows::Forms::Padding(5, 0, 5, 5);
			this->RemainingTimeLabel->Name = L"RemainingTimeLabel";
			this->RemainingTimeLabel->Size = System::Drawing::Size(86, 15);
			this->RemainingTimeLabel->TabIndex = 30;
			this->RemainingTimeLabel->Text = L"000:00:00:000";
			this->RemainingTimeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ForwardStepButton
			// 
			this->ForwardStepButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ForwardStepButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ForwardStepButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ForwardStepButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ForwardStepButton->FlatAppearance->BorderSize = 0;
			this->ForwardStepButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ForwardStepButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->ForwardStepButton->ForeColor = System::Drawing::Color::White;
			this->ForwardStepButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ForwardStepButton.Image")));
			this->ForwardStepButton->Location = System::Drawing::Point(365, 2);
			this->ForwardStepButton->Margin = System::Windows::Forms::Padding(2);
			this->ForwardStepButton->Name = L"ForwardStepButton";
			this->ForwardStepButton->Size = System::Drawing::Size(65, 45);
			this->ForwardStepButton->TabIndex = 28;
			this->ForwardStepButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->PlayBackToolTips->SetToolTip(this->ForwardStepButton, L"Step Forwards A Single Frame\r\n");
			this->ForwardStepButton->UseVisualStyleBackColor = false;
			this->ForwardStepButton->Click += gcnew System::EventHandler(this, &VideoPlayBackTools::ForwardStepButton_Click);
			// 
			// BackwardStepButton
			// 
			this->BackwardStepButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->BackwardStepButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->BackwardStepButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BackwardStepButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->BackwardStepButton->FlatAppearance->BorderSize = 0;
			this->BackwardStepButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BackwardStepButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->BackwardStepButton->ForeColor = System::Drawing::Color::White;
			this->BackwardStepButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BackwardStepButton.Image")));
			this->BackwardStepButton->Location = System::Drawing::Point(182, 2);
			this->BackwardStepButton->Margin = System::Windows::Forms::Padding(2);
			this->BackwardStepButton->Name = L"BackwardStepButton";
			this->BackwardStepButton->Size = System::Drawing::Size(58, 45);
			this->BackwardStepButton->TabIndex = 29;
			this->BackwardStepButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->PlayBackToolTips->SetToolTip(this->BackwardStepButton, L"Step Backwards A Single Frame\r\n");
			this->BackwardStepButton->UseVisualStyleBackColor = false;
			this->BackwardStepButton->Click += gcnew System::EventHandler(this, &VideoPlayBackTools::BackwardStepButton_Click);
			// 
			// PlayStopButton
			// 
			this->PlayStopButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->PlayStopButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->PlayStopButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PlayStopButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->PlayStopButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PlayStopButton->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
			this->PlayStopButton->ForeColor = System::Drawing::Color::White;
			this->PlayStopButton->Location = System::Drawing::Point(246, 4);
			this->PlayStopButton->Margin = System::Windows::Forms::Padding(4);
			this->PlayStopButton->Name = L"PlayStopButton";
			this->PlayStopButton->Size = System::Drawing::Size(113, 41);
			this->PlayStopButton->TabIndex = 27;
			this->PlayStopButton->Text = L"Play";
			this->PlayStopButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->PlayStopButton->UseVisualStyleBackColor = false;
			this->PlayStopButton->Click += gcnew System::EventHandler(this, &VideoPlayBackTools::PlayStopButton_Click);
			// 
			// tableLayoutPanel9
			// 
			this->tableLayoutPanel9->ColumnCount = 1;
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel9->Controls->Add(this->ElapsedTimeLabel, 0, 0);
			this->tableLayoutPanel9->Controls->Add(this->TopMostCheckBox, 0, 1);
			this->tableLayoutPanel9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel9->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel9->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			this->tableLayoutPanel9->RowCount = 2;
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 40.81633F)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 59.18367F)));
			this->tableLayoutPanel9->Size = System::Drawing::Size(180, 49);
			this->tableLayoutPanel9->TabIndex = 31;
			// 
			// ElapsedTimeLabel
			// 
			this->ElapsedTimeLabel->AutoSize = true;
			this->ElapsedTimeLabel->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Bold));
			this->ElapsedTimeLabel->ForeColor = System::Drawing::Color::White;
			this->ElapsedTimeLabel->Location = System::Drawing::Point(5, 0);
			this->ElapsedTimeLabel->Margin = System::Windows::Forms::Padding(5, 0, 5, 5);
			this->ElapsedTimeLabel->Name = L"ElapsedTimeLabel";
			this->ElapsedTimeLabel->Size = System::Drawing::Size(86, 15);
			this->ElapsedTimeLabel->TabIndex = 29;
			this->ElapsedTimeLabel->Text = L"000:00:00:000";
			this->ElapsedTimeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TopMostCheckBox
			// 
			this->TopMostCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TopMostCheckBox->AutoSize = true;
			this->TopMostCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Bold));
			this->TopMostCheckBox->ForeColor = System::Drawing::Color::White;
			this->TopMostCheckBox->Location = System::Drawing::Point(34, 25);
			this->TopMostCheckBox->Name = L"TopMostCheckBox";
			this->TopMostCheckBox->Size = System::Drawing::Size(112, 19);
			this->TopMostCheckBox->TabIndex = 30;
			this->TopMostCheckBox->Text = L"Always In Front";
			this->TopMostCheckBox->UseVisualStyleBackColor = true;
			this->TopMostCheckBox->CheckedChanged += gcnew System::EventHandler(this, &VideoPlayBackTools::TopMostCheckBox_CheckedChanged);
			// 
			// PlayBackToolTips
			// 
			this->PlayBackToolTips->AutomaticDelay = 100;
			this->PlayBackToolTips->AutoPopDelay = 5000;
			this->PlayBackToolTips->InitialDelay = 100;
			this->PlayBackToolTips->ReshowDelay = 20;
			// 
			// PlayTimer
			// 
			this->PlayTimer->Interval = 1000;
			this->PlayTimer->Tick += gcnew System::EventHandler(this, &VideoPlayBackTools::PlayTimer_Tick);
			// 
			// VideoPlayBackTools
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(615, 229);
			this->ControlBox = false;
			this->Controls->Add(this->tableLayoutPanel3);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"VideoPlayBackTools";
			this->Opacity = 0.95;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"VideoPlayBackTools";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &VideoPlayBackTools::VideoPlayBackTools_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &VideoPlayBackTools::VideoPlayBackTools_Shown);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel6->ResumeLayout(false);
			this->tableLayoutPanel6->PerformLayout();
			this->tableLayoutPanel8->ResumeLayout(false);
			this->tableLayoutPanel8->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel7->ResumeLayout(false);
			this->tableLayoutPanel7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FrameTrackBar))->EndInit();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->tableLayoutPanel9->ResumeLayout(false);
			this->tableLayoutPanel9->PerformLayout();
			this->ResumeLayout(false);

		}

#pragma endregion

		// ---------------------- Opstartnings Og Nedluknings Callback Routiner ----------------------- //
		
		// Video Playback Controls Form Opstartnings Callback Routine -> 
		private: System::Void VideoPlayBackTools_Shown(System::Object^ sender, System::EventArgs^ e) {


		}

		// Video Playback Controls Form Nedluknings Callback Routine -> 
		private: System::Void VideoPlayBackTools_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Nulstil "Video Playback Formen Er Åben" flaget
			VideoPlaybackControlsFormIsOpenFlag = false;

			// Hvis "Recording Analysis" Mode er aktiv
			if (InRecordingAnalysisModeFlag == true) {

				// Gen-Åben video playback controls panel formen
				OpenVideoPlayBackControlsFormFlag = true;

			}

		}

		// ---------------------------- Form GUI Event & Callback Routiner ---------------------------- //

		// Video Frame TrackBar Værdi ændret Callback Routine ->
		private: System::Void FrameTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Nuværende Frame Indeks værdi fra trackbar værdi
			CurrentPlayBackFrameValue = this->FrameTrackBar->Value;
			// Opdater nuværende frame informations label
			this->CurrentFrameLabel->Text = RMH_Conversion_IntToSystemString(CurrentPlayBackFrameValue) + " Frames";

			// Opdater tilbageværende og Forløbet tids labels
			FormatUpdataAndDisplayElapsedAndRemainingTimeLabels();

		}

		// Video Playback step Backward knap Callback Routine ->
		private: System::Void BackwardStepButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Kontroller om nuværende playback frame værdi er '0'
			if (CurrentPlayBackFrameValue == 0) {
				
				// Indstil nuværende playback frame til maks frame værdi
				CurrentPlayBackFrameValue = RecordingAnalysisModeFileInfo.NumberOfFrames;

			}
			else {

				// Dekrementer nuværende playback frame variabel
				CurrentPlayBackFrameValue = CurrentPlayBackFrameValue - 1;

			}

			// Kontroller om nuværende playback frame er over det maksimale antal frames
			if (CurrentPlayBackFrameValue > RecordingAnalysisModeFileInfo.NumberOfFrames) {

				// Nulstil nuværende playback frame variabel
				CurrentPlayBackFrameValue = 0;

			}

			// Opdater Trackbar værdi fra Frame Indeks værdi
			this->FrameTrackBar->Value = CurrentPlayBackFrameValue;
			// Opdater nuværende frame informations label
			this->CurrentFrameLabel->Text = RMH_Conversion_IntToSystemString(CurrentPlayBackFrameValue) + " Frames";

			// Opdater tilbageværende og Forløbet tids labels
			FormatUpdataAndDisplayElapsedAndRemainingTimeLabels();

		}

		// Video Playback Play knap Callback Routine ->
		private: System::Void PlayStopButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle video playback controls Play/Stop Flag
			VideoPlayBackControlsPlayStopFlag = !VideoPlayBackControlsPlayStopFlag;

			// Kontroller stadiet af video playback controls Play/Stop Flag - True: Play
			if (VideoPlayBackControlsPlayStopFlag == true) {

				// Opdater Play/Stop Knap Text og border farve
				this->PlayStopButton->Text = "Stop";
				this->PlayStopButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

				// Konfigurer Timer interval fra læst video frame rate
				this->PlayTimer->Interval = (unsigned int)(1000.0 / RecordingAnalysisModeFileInfo.FrameRate);

				// Aktiver Play timer tick 
				this->PlayTimer->Enabled = true;

			}
			else {

				// Opdater Play/Stop Knap Text og border farve
				this->PlayStopButton->Text = "Play";
				this->PlayStopButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

				// Deaktiver Play timer tick 
				this->PlayTimer->Enabled = false;

			}

		}

		// Video Playback step Forward knap Callback Routine ->
		private: System::Void ForwardStepButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Inkrementer nuværende playback frame variabel
			CurrentPlayBackFrameValue = CurrentPlayBackFrameValue + 1;

			// Kontroller om nuværende playback frame er over det maksimale antal frames
			if (CurrentPlayBackFrameValue > RecordingAnalysisModeFileInfo.NumberOfFrames) {

				// Nulstil nuværende playback frame variabel
				CurrentPlayBackFrameValue = 0;

			}

			// Opdater Trackbar værdi fra Frame Indeks værdi
			this->FrameTrackBar->Value = CurrentPlayBackFrameValue;
			// Opdater nuværende frame informations label
			this->CurrentFrameLabel->Text = RMH_Conversion_IntToSystemString(CurrentPlayBackFrameValue) + " Frames";

			// Opdater tilbageværende og Forløbet tids labels
			FormatUpdataAndDisplayElapsedAndRemainingTimeLabels();

		}

		// Video Playback "Always In Front" Checkbox Callback Routine ->
		private: System::Void TopMostCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Video PLayback formens "Top Most" konfiguration
			this->TopMost = this->TopMostCheckBox->Checked;

		}

		// ----------------------------- Play Timer Tick Callback Routine ----------------------------- //

		// Play Timer TickCallback Routine ->
		private: System::Void PlayTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

			// Inkrementer nuværende playback frame variabel
			CurrentPlayBackFrameValue = CurrentPlayBackFrameValue + 1;

			// Kontroller om nuværende playback frame er over det maksimale antal frames
			if (CurrentPlayBackFrameValue > RecordingAnalysisModeFileInfo.NumberOfFrames) {
				
				// Nulstil nuværende playback frame variabel
				CurrentPlayBackFrameValue = 0;

			}

			// Opdater Trackbar værdi fra Frame Indeks værdi
			this->FrameTrackBar->Value = CurrentPlayBackFrameValue;
			// Opdater nuværende frame informations label
			this->CurrentFrameLabel->Text = RMH_Conversion_IntToSystemString(CurrentPlayBackFrameValue) + " Frames";

			// Opdater tilbageværende og Forløbet tids labels
			FormatUpdataAndDisplayElapsedAndRemainingTimeLabels();

		}

		// -------------------------------------------------------------------------------------------- //
	
};
}
