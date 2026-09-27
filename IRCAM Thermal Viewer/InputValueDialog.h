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

	// Summary for Form - InputValueDialog
	public ref class InputValueDialog : public System::Windows::Forms::Form {

		// Lokale klasse variabler og objekter
		float *DialogOutputValuePointer;
		bool* DialogNewValueReadyFlag = false;

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		InputValueDialog(System::String^ InfoLabel1String, System::String^ InfoLabel2String, float UpDownMaxRangeVal, float UpDownMinRangeVal, float *DialogOutputVal, bool *NewValueReadyFlag) {

			// Init GUI komponenter og objekter
			InitializeComponent();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Initiliser lokalt ouput dialog værdi og "værdi klar" flag pointere
			DialogOutputValuePointer = DialogOutputVal;
			DialogNewValueReadyFlag = NewValueReadyFlag;

			// Opdaterer Teksten i toppen af Dialogen
			RMH_Winforms_ChangeFormTitleBarText(this, "Please Enter A Value");
			
			// Opdater Informations labels
			this->InfoLabel1->Text = InfoLabel1String;
			this->InfoLabel2->Text = InfoLabel2String;

			// Opdater Input dialog UpDown Max/Min Range
			this->InputValueUpDown->Maximum = (System::Decimal)UpDownMaxRangeVal;
			this->InputValueUpDown->Minimum = (System::Decimal)UpDownMinRangeVal;

			// Sæt Input dialog UpDown værdi til givet output værdi pointer
			this->InputValueUpDown->Value = (System::Decimal) * DialogOutputVal;

			// Opdater tilhørende form er aktiv flag
			InputValueDialogIsShownFlag = true;
			
		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~InputValueDialog() {

			// Opdater tilhørende form er aktiv flag
			InputValueDialogIsShownFlag = false;

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
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
		private: System::Windows::Forms::PictureBox^ pictureBox1;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
		public: System::Windows::Forms::Button^ SetInputValueButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		private: System::Windows::Forms::Label^ InfoLabel2;
		private: System::Windows::Forms::Label^ InfoLabel1;
		private: System::Windows::Forms::NumericUpDown^ InputValueUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
		public: System::Windows::Forms::Button^ ApplyValueButton;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(InputValueDialog::typeid));
			this->InputValueUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->InfoLabel2 = (gcnew System::Windows::Forms::Label());
			this->InfoLabel1 = (gcnew System::Windows::Forms::Label());
			this->SetInputValueButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->ApplyValueButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InputValueUpDown))->BeginInit();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// InputValueUpDown
			// 
			this->InputValueUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->InputValueUpDown->DecimalPlaces = 2;
			this->InputValueUpDown->Dock = System::Windows::Forms::DockStyle::Fill;
			this->InputValueUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			this->InputValueUpDown->ForeColor = System::Drawing::Color::White;
			this->InputValueUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->InputValueUpDown->Location = System::Drawing::Point(3, 77);
			this->InputValueUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->InputValueUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, System::Int32::MinValue });
			this->InputValueUpDown->Name = L"InputValueUpDown";
			this->InputValueUpDown->Size = System::Drawing::Size(210, 24);
			this->InputValueUpDown->TabIndex = 0;
			this->InputValueUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40.45534F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				59.54466F)));
			this->tableLayoutPanel2->Controls->Add(this->pictureBox1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel3, 1, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel2->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(379, 119);
			this->tableLayoutPanel2->TabIndex = 5;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(153, 119);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				10)));
			this->tableLayoutPanel3->Controls->Add(this->InputValueUpDown, 0, 3);
			this->tableLayoutPanel3->Controls->Add(this->InfoLabel2, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->InfoLabel1, 0, 1);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(153, 0);
			this->tableLayoutPanel3->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 5;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.25044F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 26.50113F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 26.50113F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 26.49686F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.25044F)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(226, 119);
			this->tableLayoutPanel3->TabIndex = 1;
			// 
			// InfoLabel2
			// 
			this->InfoLabel2->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->InfoLabel2->AutoSize = true;
			this->InfoLabel2->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->InfoLabel2->ForeColor = System::Drawing::Color::White;
			this->InfoLabel2->Location = System::Drawing::Point(3, 50);
			this->InfoLabel2->Name = L"InfoLabel2";
			this->InfoLabel2->Size = System::Drawing::Size(82, 16);
			this->InfoLabel2->TabIndex = 6;
			this->InfoLabel2->Text = L"Info Label 2";
			this->InfoLabel2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// InfoLabel1
			// 
			this->InfoLabel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->InfoLabel1->AutoSize = true;
			this->InfoLabel1->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->InfoLabel1->ForeColor = System::Drawing::Color::White;
			this->InfoLabel1->Location = System::Drawing::Point(3, 27);
			this->InfoLabel1->Name = L"InfoLabel1";
			this->InfoLabel1->Size = System::Drawing::Size(82, 16);
			this->InfoLabel1->TabIndex = 7;
			this->InfoLabel1->Text = L"Info Label 1";
			// 
			// SetInputValueButton
			// 
			this->SetInputValueButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SetInputValueButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->SetInputValueButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SetInputValueButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SetInputValueButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SetInputValueButton->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			this->SetInputValueButton->ForeColor = System::Drawing::Color::White;
			this->SetInputValueButton->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SetInputValueButton->Location = System::Drawing::Point(10, 10);
			this->SetInputValueButton->Margin = System::Windows::Forms::Padding(10);
			this->SetInputValueButton->Name = L"SetInputValueButton";
			this->SetInputValueButton->Size = System::Drawing::Size(166, 39);
			this->SetInputValueButton->TabIndex = 2;
			this->SetInputValueButton->Text = L"OK";
			this->SetInputValueButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->SetInputValueButton->UseVisualStyleBackColor = false;
			this->SetInputValueButton->Click += gcnew System::EventHandler(this, &InputValueDialog::SetInputValueButton_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(15);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 65)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(379, 184);
			this->tableLayoutPanel1->TabIndex = 6;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel4->Controls->Add(this->ApplyValueButton, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->SetInputValueButton, 0, 0);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 122);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(373, 59);
			this->tableLayoutPanel4->TabIndex = 6;
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
			this->ApplyValueButton->Location = System::Drawing::Point(196, 10);
			this->ApplyValueButton->Margin = System::Windows::Forms::Padding(10);
			this->ApplyValueButton->Name = L"ApplyValueButton";
			this->ApplyValueButton->Size = System::Drawing::Size(167, 39);
			this->ApplyValueButton->TabIndex = 3;
			this->ApplyValueButton->Text = L"Apply";
			this->ApplyValueButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->ApplyValueButton->UseVisualStyleBackColor = false;
			this->ApplyValueButton->Click += gcnew System::EventHandler(this, &InputValueDialog::ApplyValueButton_Click);
			// 
			// InputValueDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(379, 184);
			this->Controls->Add(this->tableLayoutPanel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"InputValueDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"InputValueDialog";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InputValueUpDown))->EndInit();
			this->tableLayoutPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->ResumeLayout(false);

		}

#pragma endregion

		// ------------------------------ Input Dialog Callback Routiner ------------------------------ //

		// Input Værdi Dialog OK Knap Callback Routine ->
		private: System::Void SetInputValueButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Skriv indstillede dialog værdi til output pointer addresse
			*DialogOutputValuePointer = (float)this->InputValueUpDown->Value;

			// Opdater "Dialog værdi er klar" flag
			*DialogNewValueReadyFlag = true;

			// Luk Dialog
			this->Close();

		}

		// Apply værdi dialog knap Callback Routine ->
		private: System::Void ApplyValueButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Skriv indstillede dialog værdi til output pointer addresse
			*DialogOutputValuePointer = (float)this->InputValueUpDown->Value;

			// Opdater "Dialog værdi er klar" flag
			*DialogNewValueReadyFlag = true;

		}

		// -------------------------------------------------------------------------------------------- //

};
}
