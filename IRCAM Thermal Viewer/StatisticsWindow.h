#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"

namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Summary for Form - StatisticsWindow
	public ref class StatisticsWindow : public System::Windows::Forms::Form {

	public:
		
		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		StatisticsWindow(void) {

			// Init GUI komponenter og objekter
			InitializeComponent();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Opdaterer Teksten i toppen af Dialogen
			RMH_Winforms_ChangeFormTitleBarText(this, "Live View Statistics:");
			
			// Indstil globale objekter fra denne Form til global brug
			InitializeGlobalFormsObjects();

			// Opdater Konstante statistik værdier og tilhørende labels
			UpdateConstantStatisticsValueLabels();

			// Opdater tilhørende form er aktiv flag
			LiveViewStatisticsWindowIsShownFlag = true;

		}

		// ---------------------------- Diverse Specifikke Klasse Metoder ----------------------------- //

		void UpdateConstantStatisticsValueLabels() {

			// Routinen Opdaterer Labels for de konstante værdier i statistik vinduet

			// Opdater konstante værdi labels i statistik vinduet
			this->CameraNameLabel->Text = RMH_Conversion_StdStringToSystemString(IRCamera.CameraDeviceName);
			this->CalValue0Label->Text = IRCamera.CalValue0.ToString("F1");
			this->CalValue1Label->Text = IRCamera.CalValue1.ToString("F6");
			this->CalValue2Label->Text = IRCamera.CalValue2.ToString("F6");
			this->CalValue3Label->Text = IRCamera.CalValue3.ToString("F8");
			this->CalValue4Label->Text = IRCamera.CalValue4.ToString("F6");
			this->CalValue5Label->Text = IRCamera.CalValue5.ToString("F6");

			// Hvis Live View Ultra Opløsnings Mode er aktiverede
			if (UltraResolutionEnableFlag == true) {

				// Opdater konstante værdi labels i statistik vinduet
				this->WidthLabel->Text = (IRCamera.FrameWidth * UltraResolutionScaleFactor).ToString() + " Pixels";
				this->HeightLabel->Text = ((IRCamera.FrameHeight - IRCamera.FrameMetadataSize) * UltraResolutionScaleFactor).ToString() + " Pixels";

			}
			else {

				// Opdater konstante værdi labels i statistik vinduet
				this->WidthLabel->Text = IRCamera.FrameWidth.ToString() + " Pixels";
				this->HeightLabel->Text = (IRCamera.FrameHeight - IRCamera.FrameMetadataSize).ToString() + " Pixels";

			}

		}

		void InitializeGlobalFormsObjects() {

			// Routinen indstiller globale objekter fra denne form
			// Så disse kan blve tilgået fra andre Forms

			// Initiliser Globale objeker til tilhørende Form Objekter
			GlobalVariables::GlobalFrameRateLabel = this->FrameRateLabel;
			GlobalVariables::GlobalNumberOfFramesLabel = this->NumberOfFramesLabel;
			GlobalVariables::GlobalSpanLabel = this->SpanLabel;
			GlobalVariables::GlobalAverageLabel = this->AverageLabel;
			GlobalVariables::GlobalRangeUsageLabel = this->RangeUsageLabel;
			GlobalVariables::GlobalDriftLabel = this->DriftLabel;
			GlobalVariables::GlobalDriftErrorLabel = this->DriftErrorLabel;
			GlobalVariables::GlobalMaxPeakLabel = this->MaxPeakLabel;
			GlobalVariables::GlobalMinPeakLabel = this->MinPeakLabel;

		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~StatisticsWindow() {

			// Opdater tilhørende form er aktiv flag
			LiveViewStatisticsWindowIsShownFlag = false;

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
		private: System::ComponentModel::Container ^components;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel6;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel8;	
		private: System::Windows::Forms::Label^ label1;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::Label^ label3;
		private: System::Windows::Forms::Label^ label5;
		private: System::Windows::Forms::Label^ label4;
		private: System::Windows::Forms::Label^ label6;
		private: System::Windows::Forms::Label^ label7;
		private: System::Windows::Forms::Label^ label8;
		private: System::Windows::Forms::Label^ label9;
		private: System::Windows::Forms::Label^ label10;
		private: System::Windows::Forms::Label^ label11;
		private: System::Windows::Forms::Label^ label12;
		private: System::Windows::Forms::Label^ label14;
		private: System::Windows::Forms::Label^ label13;
		private: System::Windows::Forms::Label^ label15;
		private: System::Windows::Forms::Label^ label16;
		private: System::Windows::Forms::Label^ label17;
		private: System::Windows::Forms::Label^ label19;
		private: System::Windows::Forms::Label^ label18;
		private: System::Windows::Forms::Label^ FrameRateLabel;
		private: System::Windows::Forms::Label^ CameraNameLabel;
		private: System::Windows::Forms::Label^ WidthLabel;
		private: System::Windows::Forms::Label^ HeightLabel;
		private: System::Windows::Forms::Label^ CalValue0Label;
		private: System::Windows::Forms::Label^ CalValue1Label;
		private: System::Windows::Forms::Label^ CalValue2Label;
		private: System::Windows::Forms::Label^ CalValue3Label;
		private: System::Windows::Forms::Label^ CalValue4Label;
		private: System::Windows::Forms::Label^ CalValue5Label;
		private: System::Windows::Forms::Label^ MinPeakLabel;
		private: System::Windows::Forms::Label^ MaxPeakLabel;
		private: System::Windows::Forms::Label^ DriftErrorLabel;
		private: System::Windows::Forms::Label^ DriftLabel;
		private: System::Windows::Forms::Label^ RangeUsageLabel;
		private: System::Windows::Forms::Label^ AverageLabel;
		private: System::Windows::Forms::Label^ SpanLabel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		private: System::Windows::Forms::CheckBox^ TopMostCheckBox;
		private: System::Windows::Forms::Label^ NumberOfFramesLabel;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(StatisticsWindow::typeid));
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->TopMostCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->MinPeakLabel = (gcnew System::Windows::Forms::Label());
			this->MaxPeakLabel = (gcnew System::Windows::Forms::Label());
			this->DriftErrorLabel = (gcnew System::Windows::Forms::Label());
			this->DriftLabel = (gcnew System::Windows::Forms::Label());
			this->RangeUsageLabel = (gcnew System::Windows::Forms::Label());
			this->AverageLabel = (gcnew System::Windows::Forms::Label());
			this->SpanLabel = (gcnew System::Windows::Forms::Label());
			this->NumberOfFramesLabel = (gcnew System::Windows::Forms::Label());
			this->FrameRateLabel = (gcnew System::Windows::Forms::Label());
			this->CameraNameLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->WidthLabel = (gcnew System::Windows::Forms::Label());
			this->HeightLabel = (gcnew System::Windows::Forms::Label());
			this->CalValue0Label = (gcnew System::Windows::Forms::Label());
			this->CalValue1Label = (gcnew System::Windows::Forms::Label());
			this->CalValue2Label = (gcnew System::Windows::Forms::Label());
			this->CalValue3Label = (gcnew System::Windows::Forms::Label());
			this->CalValue4Label = (gcnew System::Windows::Forms::Label());
			this->CalValue5Label = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel6->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel8->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel6->ColumnCount = 1;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel1, 0, 0);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel8, 0, 1);
			this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel6->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel6->Margin = System::Windows::Forms::Padding(5);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 2;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.3F)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 85.7F)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(661, 254);
			this->tableLayoutPanel6->TabIndex = 3;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->TopMostCheckBox, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label4, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(4, 4);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(653, 29);
			this->tableLayoutPanel1->TabIndex = 29;
			// 
			// TopMostCheckBox
			// 
			this->TopMostCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TopMostCheckBox->AutoSize = true;
			this->TopMostCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Bold));
			this->TopMostCheckBox->ForeColor = System::Drawing::Color::White;
			this->TopMostCheckBox->Location = System::Drawing::Point(433, 5);
			this->TopMostCheckBox->Name = L"TopMostCheckBox";
			this->TopMostCheckBox->Size = System::Drawing::Size(112, 19);
			this->TopMostCheckBox->TabIndex = 31;
			this->TopMostCheckBox->Text = L"Always In Front";
			this->TopMostCheckBox->UseVisualStyleBackColor = true;
			this->TopMostCheckBox->CheckedChanged += gcnew System::EventHandler(this, &StatisticsWindow::TopMostCheckBox_CheckedChanged);
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(31, 5);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(263, 18);
			this->label4->TabIndex = 28;
			this->label4->Text = L"Live View Statistics And Information:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel8
			// 
			this->tableLayoutPanel8->ColumnCount = 4;
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				26.5625F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.75F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				35.9375F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.75F)));
			this->tableLayoutPanel8->Controls->Add(this->MinPeakLabel, 3, 8);
			this->tableLayoutPanel8->Controls->Add(this->MaxPeakLabel, 3, 7);
			this->tableLayoutPanel8->Controls->Add(this->DriftErrorLabel, 3, 6);
			this->tableLayoutPanel8->Controls->Add(this->DriftLabel, 3, 5);
			this->tableLayoutPanel8->Controls->Add(this->RangeUsageLabel, 3, 4);
			this->tableLayoutPanel8->Controls->Add(this->AverageLabel, 3, 3);
			this->tableLayoutPanel8->Controls->Add(this->SpanLabel, 3, 2);
			this->tableLayoutPanel8->Controls->Add(this->NumberOfFramesLabel, 3, 1);
			this->tableLayoutPanel8->Controls->Add(this->FrameRateLabel, 3, 0);
			this->tableLayoutPanel8->Controls->Add(this->CameraNameLabel, 1, 0);
			this->tableLayoutPanel8->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel8->Controls->Add(this->label13, 0, 1);
			this->tableLayoutPanel8->Controls->Add(this->label14, 0, 2);
			this->tableLayoutPanel8->Controls->Add(this->label6, 0, 3);
			this->tableLayoutPanel8->Controls->Add(this->label7, 0, 4);
			this->tableLayoutPanel8->Controls->Add(this->label8, 0, 5);
			this->tableLayoutPanel8->Controls->Add(this->label9, 0, 6);
			this->tableLayoutPanel8->Controls->Add(this->label10, 0, 7);
			this->tableLayoutPanel8->Controls->Add(this->label11, 0, 8);
			this->tableLayoutPanel8->Controls->Add(this->label12, 2, 0);
			this->tableLayoutPanel8->Controls->Add(this->label15, 2, 1);
			this->tableLayoutPanel8->Controls->Add(this->label2, 2, 2);
			this->tableLayoutPanel8->Controls->Add(this->label16, 2, 3);
			this->tableLayoutPanel8->Controls->Add(this->label3, 2, 4);
			this->tableLayoutPanel8->Controls->Add(this->label5, 2, 5);
			this->tableLayoutPanel8->Controls->Add(this->label19, 2, 8);
			this->tableLayoutPanel8->Controls->Add(this->label18, 2, 6);
			this->tableLayoutPanel8->Controls->Add(this->label17, 2, 7);
			this->tableLayoutPanel8->Controls->Add(this->WidthLabel, 1, 1);
			this->tableLayoutPanel8->Controls->Add(this->HeightLabel, 1, 2);
			this->tableLayoutPanel8->Controls->Add(this->CalValue0Label, 1, 3);
			this->tableLayoutPanel8->Controls->Add(this->CalValue1Label, 1, 4);
			this->tableLayoutPanel8->Controls->Add(this->CalValue2Label, 1, 5);
			this->tableLayoutPanel8->Controls->Add(this->CalValue3Label, 1, 6);
			this->tableLayoutPanel8->Controls->Add(this->CalValue4Label, 1, 7);
			this->tableLayoutPanel8->Controls->Add(this->CalValue5Label, 1, 8);
			this->tableLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel8->Location = System::Drawing::Point(4, 40);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 9;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 11.11111F)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(653, 210);
			this->tableLayoutPanel8->TabIndex = 30;
			// 
			// MinPeakLabel
			// 
			this->MinPeakLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->MinPeakLabel->AutoSize = true;
			this->MinPeakLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->MinPeakLabel->ForeColor = System::Drawing::Color::White;
			this->MinPeakLabel->Location = System::Drawing::Point(532, 189);
			this->MinPeakLabel->Name = L"MinPeakLabel";
			this->MinPeakLabel->Size = System::Drawing::Size(59, 15);
			this->MinPeakLabel->TabIndex = 64;
			this->MinPeakLabel->Text = L"Min Peak";
			this->MinPeakLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->MinPeakLabel->Click += gcnew System::EventHandler(this, &StatisticsWindow::MinPeakLabel_Click);
			// 
			// MaxPeakLabel
			// 
			this->MaxPeakLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->MaxPeakLabel->AutoSize = true;
			this->MaxPeakLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->MaxPeakLabel->ForeColor = System::Drawing::Color::White;
			this->MaxPeakLabel->Location = System::Drawing::Point(532, 165);
			this->MaxPeakLabel->Name = L"MaxPeakLabel";
			this->MaxPeakLabel->Size = System::Drawing::Size(63, 15);
			this->MaxPeakLabel->TabIndex = 63;
			this->MaxPeakLabel->Text = L"Max Peak";
			this->MaxPeakLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->MaxPeakLabel->Click += gcnew System::EventHandler(this, &StatisticsWindow::MaxPeakLabel_Click);
			// 
			// DriftErrorLabel
			// 
			this->DriftErrorLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->DriftErrorLabel->AutoSize = true;
			this->DriftErrorLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DriftErrorLabel->ForeColor = System::Drawing::Color::White;
			this->DriftErrorLabel->Location = System::Drawing::Point(532, 142);
			this->DriftErrorLabel->Name = L"DriftErrorLabel";
			this->DriftErrorLabel->Size = System::Drawing::Size(63, 15);
			this->DriftErrorLabel->TabIndex = 62;
			this->DriftErrorLabel->Text = L"Drift Error";
			this->DriftErrorLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DriftLabel
			// 
			this->DriftLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->DriftLabel->AutoSize = true;
			this->DriftLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DriftLabel->ForeColor = System::Drawing::Color::White;
			this->DriftLabel->Location = System::Drawing::Point(532, 119);
			this->DriftLabel->Name = L"DriftLabel";
			this->DriftLabel->Size = System::Drawing::Size(31, 15);
			this->DriftLabel->TabIndex = 61;
			this->DriftLabel->Text = L"Drift";
			this->DriftLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// RangeUsageLabel
			// 
			this->RangeUsageLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->RangeUsageLabel->AutoSize = true;
			this->RangeUsageLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->RangeUsageLabel->ForeColor = System::Drawing::Color::White;
			this->RangeUsageLabel->Location = System::Drawing::Point(532, 96);
			this->RangeUsageLabel->Name = L"RangeUsageLabel";
			this->RangeUsageLabel->Size = System::Drawing::Size(82, 15);
			this->RangeUsageLabel->TabIndex = 60;
			this->RangeUsageLabel->Text = L"Range Usage";
			this->RangeUsageLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// AverageLabel
			// 
			this->AverageLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->AverageLabel->AutoSize = true;
			this->AverageLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->AverageLabel->ForeColor = System::Drawing::Color::White;
			this->AverageLabel->Location = System::Drawing::Point(532, 73);
			this->AverageLabel->Name = L"AverageLabel";
			this->AverageLabel->Size = System::Drawing::Size(54, 15);
			this->AverageLabel->TabIndex = 59;
			this->AverageLabel->Text = L"Average";
			this->AverageLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// SpanLabel
			// 
			this->SpanLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->SpanLabel->AutoSize = true;
			this->SpanLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->SpanLabel->ForeColor = System::Drawing::Color::White;
			this->SpanLabel->Location = System::Drawing::Point(532, 50);
			this->SpanLabel->Name = L"SpanLabel";
			this->SpanLabel->Size = System::Drawing::Size(36, 15);
			this->SpanLabel->TabIndex = 58;
			this->SpanLabel->Text = L"Span";
			this->SpanLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// NumberOfFramesLabel
			// 
			this->NumberOfFramesLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->NumberOfFramesLabel->AutoSize = true;
			this->NumberOfFramesLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->NumberOfFramesLabel->ForeColor = System::Drawing::Color::White;
			this->NumberOfFramesLabel->Location = System::Drawing::Point(532, 27);
			this->NumberOfFramesLabel->Name = L"NumberOfFramesLabel";
			this->NumberOfFramesLabel->Size = System::Drawing::Size(114, 15);
			this->NumberOfFramesLabel->TabIndex = 57;
			this->NumberOfFramesLabel->Text = L"Number Of Frames";
			this->NumberOfFramesLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FrameRateLabel
			// 
			this->FrameRateLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->FrameRateLabel->AutoSize = true;
			this->FrameRateLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->FrameRateLabel->ForeColor = System::Drawing::Color::White;
			this->FrameRateLabel->Location = System::Drawing::Point(532, 4);
			this->FrameRateLabel->Name = L"FrameRateLabel";
			this->FrameRateLabel->Size = System::Drawing::Size(72, 15);
			this->FrameRateLabel->TabIndex = 56;
			this->FrameRateLabel->Text = L"Frame Rate";
			this->FrameRateLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CameraNameLabel
			// 
			this->CameraNameLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->CameraNameLabel->AutoSize = true;
			this->CameraNameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CameraNameLabel->ForeColor = System::Drawing::Color::White;
			this->CameraNameLabel->Location = System::Drawing::Point(176, 4);
			this->CameraNameLabel->Name = L"CameraNameLabel";
			this->CameraNameLabel->Size = System::Drawing::Size(88, 15);
			this->CameraNameLabel->TabIndex = 47;
			this->CameraNameLabel->Text = L"Camera Name";
			this->CameraNameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(3, 4);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(141, 15);
			this->label1->TabIndex = 30;
			this->label1->Text = L"Thermal Camera Name:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label13
			// 
			this->label13->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(3, 27);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(157, 15);
			this->label13->TabIndex = 40;
			this->label13->Text = L"Camera Resolution, Width:";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label14
			// 
			this->label14->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(3, 50);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(160, 15);
			this->label14->TabIndex = 41;
			this->label14->Text = L"Camera Resolution, Height:";
			this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(3, 73);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(159, 15);
			this->label6->TabIndex = 34;
			this->label6->Text = L"Sensor Calibration Value 0:";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(3, 96);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(159, 15);
			this->label7->TabIndex = 35;
			this->label7->Text = L"Sensor Calibration Value 1:";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(3, 119);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(159, 15);
			this->label8->TabIndex = 36;
			this->label8->Text = L"Sensor Calibration Value 2:";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label9
			// 
			this->label9->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(3, 142);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(159, 15);
			this->label9->TabIndex = 37;
			this->label9->Text = L"Sensor Calibration Value 3:";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label10
			// 
			this->label10->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(3, 165);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(159, 15);
			this->label10->TabIndex = 38;
			this->label10->Text = L"Sensor Calibration Value 4:";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label11
			// 
			this->label11->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(3, 189);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(159, 15);
			this->label11->TabIndex = 39;
			this->label11->Text = L"Sensor Calibration Value 5:";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label12
			// 
			this->label12->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(298, 4);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(132, 15);
			this->label12->TabIndex = 29;
			this->label12->Text = L"Live View Frame Rate:";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label15
			// 
			this->label15->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(298, 27);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(172, 15);
			this->label15->TabIndex = 42;
			this->label15->Text = L"Number Of Captured Frames:";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(298, 50);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(175, 15);
			this->label2->TabIndex = 31;
			this->label2->Text = L"Live View Temperature, Span:";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label16
			// 
			this->label16->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->Location = System::Drawing::Point(298, 73);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(193, 15);
			this->label16->TabIndex = 43;
			this->label16->Text = L"Live View Temperature, Average:";
			this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(298, 96);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(221, 15);
			this->label3->TabIndex = 32;
			this->label3->Text = L"Live View Temperature, Range Usage:";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(298, 119);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(170, 15);
			this->label5->TabIndex = 33;
			this->label5->Text = L"Live View Temperature, Drift:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label19
			// 
			this->label19->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label19->ForeColor = System::Drawing::Color::White;
			this->label19->Location = System::Drawing::Point(298, 189);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(198, 15);
			this->label19->TabIndex = 46;
			this->label19->Text = L"Live View Temperature, Min Peak:";
			this->label19->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label18
			// 
			this->label18->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label18->ForeColor = System::Drawing::Color::White;
			this->label18->Location = System::Drawing::Point(298, 142);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(199, 15);
			this->label18->TabIndex = 45;
			this->label18->Text = L"Live View Temperature, Drift Error";
			this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label17
			// 
			this->label17->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label17->ForeColor = System::Drawing::Color::White;
			this->label17->Location = System::Drawing::Point(298, 165);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(202, 15);
			this->label17->TabIndex = 44;
			this->label17->Text = L"Live View Temperature, Max Peak:";
			this->label17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// WidthLabel
			// 
			this->WidthLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->WidthLabel->AutoSize = true;
			this->WidthLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->WidthLabel->ForeColor = System::Drawing::Color::White;
			this->WidthLabel->Location = System::Drawing::Point(176, 27);
			this->WidthLabel->Name = L"WidthLabel";
			this->WidthLabel->Size = System::Drawing::Size(40, 15);
			this->WidthLabel->TabIndex = 48;
			this->WidthLabel->Text = L"Width";
			this->WidthLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// HeightLabel
			// 
			this->HeightLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->HeightLabel->AutoSize = true;
			this->HeightLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->HeightLabel->ForeColor = System::Drawing::Color::White;
			this->HeightLabel->Location = System::Drawing::Point(176, 50);
			this->HeightLabel->Name = L"HeightLabel";
			this->HeightLabel->Size = System::Drawing::Size(43, 15);
			this->HeightLabel->TabIndex = 49;
			this->HeightLabel->Text = L"Height";
			this->HeightLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CalValue0Label
			// 
			this->CalValue0Label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->CalValue0Label->AutoSize = true;
			this->CalValue0Label->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CalValue0Label->ForeColor = System::Drawing::Color::White;
			this->CalValue0Label->Location = System::Drawing::Point(176, 73);
			this->CalValue0Label->Name = L"CalValue0Label";
			this->CalValue0Label->Size = System::Drawing::Size(63, 15);
			this->CalValue0Label->TabIndex = 50;
			this->CalValue0Label->Text = L"CalValue0";
			this->CalValue0Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CalValue1Label
			// 
			this->CalValue1Label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->CalValue1Label->AutoSize = true;
			this->CalValue1Label->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CalValue1Label->ForeColor = System::Drawing::Color::White;
			this->CalValue1Label->Location = System::Drawing::Point(176, 96);
			this->CalValue1Label->Name = L"CalValue1Label";
			this->CalValue1Label->Size = System::Drawing::Size(63, 15);
			this->CalValue1Label->TabIndex = 51;
			this->CalValue1Label->Text = L"CalValue1";
			this->CalValue1Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CalValue2Label
			// 
			this->CalValue2Label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->CalValue2Label->AutoSize = true;
			this->CalValue2Label->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CalValue2Label->ForeColor = System::Drawing::Color::White;
			this->CalValue2Label->Location = System::Drawing::Point(176, 119);
			this->CalValue2Label->Name = L"CalValue2Label";
			this->CalValue2Label->Size = System::Drawing::Size(63, 15);
			this->CalValue2Label->TabIndex = 52;
			this->CalValue2Label->Text = L"CalValue2";
			this->CalValue2Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CalValue3Label
			// 
			this->CalValue3Label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->CalValue3Label->AutoSize = true;
			this->CalValue3Label->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CalValue3Label->ForeColor = System::Drawing::Color::White;
			this->CalValue3Label->Location = System::Drawing::Point(176, 142);
			this->CalValue3Label->Name = L"CalValue3Label";
			this->CalValue3Label->Size = System::Drawing::Size(63, 15);
			this->CalValue3Label->TabIndex = 53;
			this->CalValue3Label->Text = L"CalValue3";
			this->CalValue3Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CalValue4Label
			// 
			this->CalValue4Label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->CalValue4Label->AutoSize = true;
			this->CalValue4Label->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CalValue4Label->ForeColor = System::Drawing::Color::White;
			this->CalValue4Label->Location = System::Drawing::Point(176, 165);
			this->CalValue4Label->Name = L"CalValue4Label";
			this->CalValue4Label->Size = System::Drawing::Size(63, 15);
			this->CalValue4Label->TabIndex = 54;
			this->CalValue4Label->Text = L"CalValue4";
			this->CalValue4Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CalValue5Label
			// 
			this->CalValue5Label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->CalValue5Label->AutoSize = true;
			this->CalValue5Label->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->CalValue5Label->ForeColor = System::Drawing::Color::White;
			this->CalValue5Label->Location = System::Drawing::Point(176, 189);
			this->CalValue5Label->Name = L"CalValue5Label";
			this->CalValue5Label->Size = System::Drawing::Size(63, 15);
			this->CalValue5Label->TabIndex = 55;
			this->CalValue5Label->Text = L"CalValue5";
			this->CalValue5Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// StatisticsWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(661, 254);
			this->Controls->Add(this->tableLayoutPanel6);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"StatisticsWindow";
			this->Opacity = 0.9;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"StatisticsWindow";
			this->tableLayoutPanel6->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel8->ResumeLayout(false);
			this->tableLayoutPanel8->PerformLayout();
			this->ResumeLayout(false);

		}

#pragma endregion

		// -------------------------- Statistik Vindue GUI Callback Routiner -------------------------- //
		
		// Live View Statistik Vindue Max Peak værdi Click Callback Routine ->
		private: System::Void MaxPeakLabel_Click(System::Object^ sender, System::EventArgs^ e) {

			// Nulstil Maksimum Peak Værdien
			MaxPeakTemperature = 0;

		}

		// Live View Statistik Vindue Min Peak værdi Click Callback Routine ->
		private: System::Void MinPeakLabel_Click(System::Object^ sender, System::EventArgs^ e) {

			// Nulstil Minimum Peak Værdien
			MinPeakTemperature = 2000.0;

		}

		// Live View Statistik Vindue "Always In Front" Checkbox Callback Routine ->
		private: System::Void TopMostCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Live View Statistik Vindue formens "Top Most" konfiguration
			this->TopMost = this->TopMostCheckBox->Checked;

		}

		// -------------------------------------------------------------------------------------------- //

};
}
