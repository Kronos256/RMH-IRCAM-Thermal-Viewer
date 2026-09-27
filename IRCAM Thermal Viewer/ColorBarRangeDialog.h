#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"
#include "RMH_Winforms_Library.h"

namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Summary for Form - ColorBarRangeDialog
	public ref class ColorBarRangeDialog : public System::Windows::Forms::Form {

	public:

		ColorBarRangeDialog(void) {

			// Init GUI komponenter og objekter
			InitializeComponent();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Opdaterer Teksten i toppen af Dialogen
			RMH_Winforms_ChangeFormTitleBarText(this, "Set ColorBar Temperature Ranges:");

			// Opdater tilhørende form er aktiv flag
			ColorBarDialogIsShownFlag = true;
			
		}

		// ----------------------- Diverse Tilhørende Klasse Metoder ----------------------- //

		System::Void UpdateColorBarTempRangeDialogValues(double MaximumTemperature, double MinimumTemperature, System::String^ DefaultTempUnitString) {

			// Routinen opdaterer formens numeriske UpDowns med start værdier og indstiller temperatur enheds stringet

			// Error håndtering (Double til System::Decimal)
			try {

				// Indstil Maximum og Minimum Temperatur range værdierne i UpDowns
				this->ColorBarMaxRangeUpDown->Value = (System::Decimal)MaximumTemperature;
				this->ColorBarMinRangeUpDown->Value = (System::Decimal)MinimumTemperature;

				// Opdater numeriske UpDown Enheds string
				this->MaxRangeUnitString->Text = DefaultTempUnitString;
				this->MinRangeUnitString->Text = DefaultTempUnitString;

			}
			catch (System::Exception^ Ex) {
				
				// Skriv GUI Status Meddelse - Filen er en .png fil
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Values Entered Were to Large Or To Low!", _StatusMessageType_Error);

				// Indstil Range UpDown værdier til General Range værdier
				this->ColorBarMaxRangeUpDown->Value = (System::Decimal)50.0;
				this->ColorBarMinRangeUpDown->Value = (System::Decimal)20.0;

			}

		}

		// --------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ColorBarRangeDialog() {

			// Opdater tilhørende form er aktiv flag
			ColorBarDialogIsShownFlag = false;

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
		System::ComponentModel::Container ^components;
		private: System::Windows::Forms::NumericUpDown^ ColorBarMaxRangeUpDown;
		private: System::Windows::Forms::Label^ label1;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		private: System::Windows::Forms::Label^ MaxRangeUnitString;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
		private: System::Windows::Forms::PictureBox^ pictureBox1;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
		private: System::Windows::Forms::Label^ MinRangeUnitString;
		private: System::Windows::Forms::Label^ label4;
		private: System::Windows::Forms::NumericUpDown^ ColorBarMinRangeUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel6;
		private: System::Windows::Forms::Button^ ApplyValueButton;
		private: System::Windows::Forms::Button^ SetColorBarTempRangesButton;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) 
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ColorBarRangeDialog::typeid));
			this->ColorBarMaxRangeUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->MaxRangeUnitString = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->MinRangeUnitString = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ColorBarMinRangeUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->ApplyValueButton = (gcnew System::Windows::Forms::Button());
			this->SetColorBarTempRangesButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ColorBarMaxRangeUpDown))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tableLayoutPanel5->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ColorBarMinRangeUpDown))->BeginInit();
			this->tableLayoutPanel6->SuspendLayout();
			this->SuspendLayout();
			// 
			// ColorBarMaxRangeUpDown
			// 
			this->ColorBarMaxRangeUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ColorBarMaxRangeUpDown->DecimalPlaces = 2;
			this->ColorBarMaxRangeUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ColorBarMaxRangeUpDown->ForeColor = System::Drawing::Color::White;
			this->ColorBarMaxRangeUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->ColorBarMaxRangeUpDown->Location = System::Drawing::Point(257, 3);
			this->ColorBarMaxRangeUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->ColorBarMaxRangeUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, System::Int32::MinValue });
			this->ColorBarMaxRangeUpDown->Name = L"ColorBarMaxRangeUpDown";
			this->ColorBarMaxRangeUpDown->Size = System::Drawing::Size(106, 23);
			this->ColorBarMaxRangeUpDown->TabIndex = 0;
			this->ColorBarMaxRangeUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(3, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(248, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"ColorBar Max Temperature Range:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				254)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				112)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				53)));
			this->tableLayoutPanel1->Controls->Add(this->MaxRangeUnitString, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->ColorBarMaxRangeUpDown, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(10, 53);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(419, 30);
			this->tableLayoutPanel1->TabIndex = 3;
			// 
			// MaxRangeUnitString
			// 
			this->MaxRangeUnitString->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->MaxRangeUnitString->AutoSize = true;
			this->MaxRangeUnitString->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->MaxRangeUnitString->ForeColor = System::Drawing::Color::White;
			this->MaxRangeUnitString->Location = System::Drawing::Point(369, 7);
			this->MaxRangeUnitString->Name = L"MaxRangeUnitString";
			this->MaxRangeUnitString->Size = System::Drawing::Size(47, 16);
			this->MaxRangeUnitString->TabIndex = 3;
			this->MaxRangeUnitString->Text = L"Unit";
			this->MaxRangeUnitString->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 1;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel4, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel6, 0, 1);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 2;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 70.43478F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 29.56522F)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(585, 187);
			this->tableLayoutPanel3->TabIndex = 9;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25.07837F)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				74.92163F)));
			this->tableLayoutPanel4->Controls->Add(this->pictureBox1, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->tableLayoutPanel5, 1, 0);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel4->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(585, 131);
			this->tableLayoutPanel4->TabIndex = 10;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(3, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(140, 125);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 1;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel5->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel5->Controls->Add(this->tableLayoutPanel1, 0, 1);
			this->tableLayoutPanel5->Controls->Add(this->tableLayoutPanel2, 0, 2);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(146, 0);
			this->tableLayoutPanel5->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 3;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(439, 131);
			this->tableLayoutPanel5->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(76, 11);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(286, 32);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Set The Desired Maximum And Minimum\r\nTemperature Ranges For The ColorBar";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel2->ColumnCount = 3;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				254)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				112)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				53)));
			this->tableLayoutPanel2->Controls->Add(this->MinRangeUnitString, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->label4, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->ColorBarMinRangeUpDown, 1, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(10, 93);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(419, 30);
			this->tableLayoutPanel2->TabIndex = 4;
			// 
			// MinRangeUnitString
			// 
			this->MinRangeUnitString->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->MinRangeUnitString->AutoSize = true;
			this->MinRangeUnitString->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->MinRangeUnitString->ForeColor = System::Drawing::Color::White;
			this->MinRangeUnitString->Location = System::Drawing::Point(369, 7);
			this->MinRangeUnitString->Name = L"MinRangeUnitString";
			this->MinRangeUnitString->Size = System::Drawing::Size(47, 16);
			this->MinRangeUnitString->TabIndex = 3;
			this->MinRangeUnitString->Text = L"Unit";
			this->MinRangeUnitString->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(3, 7);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(248, 16);
			this->label4->TabIndex = 2;
			this->label4->Text = L"ColorBar Min Temperature Range:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ColorBarMinRangeUpDown
			// 
			this->ColorBarMinRangeUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ColorBarMinRangeUpDown->DecimalPlaces = 2;
			this->ColorBarMinRangeUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ColorBarMinRangeUpDown->ForeColor = System::Drawing::Color::White;
			this->ColorBarMinRangeUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->ColorBarMinRangeUpDown->Location = System::Drawing::Point(257, 3);
			this->ColorBarMinRangeUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->ColorBarMinRangeUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, System::Int32::MinValue });
			this->ColorBarMinRangeUpDown->Name = L"ColorBarMinRangeUpDown";
			this->ColorBarMinRangeUpDown->Size = System::Drawing::Size(106, 23);
			this->ColorBarMinRangeUpDown->TabIndex = 0;
			this->ColorBarMinRangeUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 2;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel6->Controls->Add(this->ApplyValueButton, 1, 0);
			this->tableLayoutPanel6->Controls->Add(this->SetColorBarTempRangesButton, 0, 0);
			this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel6->Location = System::Drawing::Point(3, 134);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 1;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(579, 50);
			this->tableLayoutPanel6->TabIndex = 11;
			// 
			// ApplyValueButton
			// 
			this->ApplyValueButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ApplyValueButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ApplyValueButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ApplyValueButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ApplyValueButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ApplyValueButton->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			this->ApplyValueButton->ForeColor = System::Drawing::Color::White;
			this->ApplyValueButton->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->ApplyValueButton->Location = System::Drawing::Point(297, 8);
			this->ApplyValueButton->Margin = System::Windows::Forms::Padding(8);
			this->ApplyValueButton->Name = L"ApplyValueButton";
			this->ApplyValueButton->Size = System::Drawing::Size(274, 34);
			this->ApplyValueButton->TabIndex = 9;
			this->ApplyValueButton->Text = L"Apply";
			this->ApplyValueButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->ApplyValueButton->UseVisualStyleBackColor = false;
			this->ApplyValueButton->Click += gcnew System::EventHandler(this, &ColorBarRangeDialog::ApplyValueButton_Click);
			// 
			// SetColorBarTempRangesButton
			// 
			this->SetColorBarTempRangesButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SetColorBarTempRangesButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->SetColorBarTempRangesButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SetColorBarTempRangesButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SetColorBarTempRangesButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SetColorBarTempRangesButton->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			this->SetColorBarTempRangesButton->ForeColor = System::Drawing::Color::White;
			this->SetColorBarTempRangesButton->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SetColorBarTempRangesButton->Location = System::Drawing::Point(8, 8);
			this->SetColorBarTempRangesButton->Margin = System::Windows::Forms::Padding(8);
			this->SetColorBarTempRangesButton->Name = L"SetColorBarTempRangesButton";
			this->SetColorBarTempRangesButton->Size = System::Drawing::Size(273, 34);
			this->SetColorBarTempRangesButton->TabIndex = 8;
			this->SetColorBarTempRangesButton->Text = L"OK";
			this->SetColorBarTempRangesButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->SetColorBarTempRangesButton->UseVisualStyleBackColor = false;
			this->SetColorBarTempRangesButton->Click += gcnew System::EventHandler(this, &ColorBarRangeDialog::SetColorBarTempRangesButton_Click);
			// 
			// ColorBarRangeDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(585, 187);
			this->Controls->Add(this->tableLayoutPanel3);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ColorBarRangeDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ColorBarRangeDialog";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ColorBarMaxRangeUpDown))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ColorBarMinRangeUpDown))->EndInit();
			this->tableLayoutPanel6->ResumeLayout(false);
			this->ResumeLayout(false);

		}

#pragma endregion

		// Sæt ColorBar Maximum og Minimum Temperatur Range Callback Routine ->
		private: System::Void SetColorBarTempRangesButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Nulstil colorbarens maximum og minimum temperatur range offset værdier
			GlobalVariables::OpenGLColorBar->RMH_OpenGL_ResetColorbarMaxMinRangeOffsetValues();

			// Indstil Colorbarens start Manuelle Temperatur range værdier til frame Max/Min Temperaturerne ved Range Skift 
			ColorBarInitialManualRangeMaxTemp = (double)this->ColorBarMaxRangeUpDown->Value;
			ColorBarInitialManualRangeMinTemp = (double)this->ColorBarMinRangeUpDown->Value;

			// Luk Dialog
			this->Close();

		}

		// Apply ColorBar Maximum og Minimum Temperatur Range Callback Routine ->
		private: System::Void ApplyValueButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Nulstil colorbarens maximum og minimum temperatur range offset værdier
			GlobalVariables::OpenGLColorBar->RMH_OpenGL_ResetColorbarMaxMinRangeOffsetValues();

			// Indstil Colorbarens start Manuelle Temperatur range værdier til frame Max/Min Temperaturerne ved Range Skift 
			ColorBarInitialManualRangeMaxTemp = (double)this->ColorBarMaxRangeUpDown->Value;
			ColorBarInitialManualRangeMinTemp = (double)this->ColorBarMinRangeUpDown->Value;

		}

};
}
