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

	// Summary for Form - PopUpDialog
	public ref class PopUpDialog : public System::Windows::Forms::Form {

	public:

		PopUpDialog(std::string DialogTitleText, System::String^ DialogInfoText) {

			// Init GUI komponenter og objekter
			InitializeComponent();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Opdaterer Teksten i toppen af Dialogen
			RMH_Winforms_ChangeFormTitleBarText(this, DialogTitleText);

			// Opdater Pop-Up Dialogens informations Text
			PopUpDialogText->Text = DialogInfoText;
			
		}

		// ----------------------- Diverse Tilhørende Klasse Metoder ----------------------- //

		// --------------------------------------------------------------------------------- //

	protected:
		
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PopUpDialog() {

			if (components) {

				delete components;

			}

		}
	
	private:

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private: System::ComponentModel::Container ^components;
		private: System::Windows::Forms::Label^ PopUpDialogText;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		private: System::Windows::Forms::CheckBox^ PopUpDontShowChechBox;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
		private: System::Windows::Forms::Button^ PopUpDialogOKButton;

#pragma region Windows Form Designer generated code
		
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(PopUpDialog::typeid));
			this->PopUpDialogText = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->PopUpDontShowChechBox = (gcnew System::Windows::Forms::CheckBox());
			this->PopUpDialogOKButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// PopUpDialogText
			// 
			this->PopUpDialogText->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PopUpDialogText->AutoSize = true;
			this->PopUpDialogText->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->PopUpDialogText->ForeColor = System::Drawing::Color::White;
			this->PopUpDialogText->Location = System::Drawing::Point(277, 47);
			this->PopUpDialogText->Name = L"PopUpDialogText";
			this->PopUpDialogText->Size = System::Drawing::Size(48, 16);
			this->PopUpDialogText->TabIndex = 6;
			this->PopUpDialogText->Text = L"Text 1";
			this->PopUpDialogText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->PopUpDialogText, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 57.78894F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 42.21106F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(603, 192);
			this->tableLayoutPanel1->TabIndex = 7;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->Controls->Add(this->PopUpDontShowChechBox, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->PopUpDialogOKButton, 0, 1);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 113);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 32.05128F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 67.94872F)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(597, 76);
			this->tableLayoutPanel2->TabIndex = 32;
			// 
			// PopUpDontShowChechBox
			// 
			this->PopUpDontShowChechBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PopUpDontShowChechBox->AutoSize = true;
			this->PopUpDontShowChechBox->Font = (gcnew System::Drawing::Font(L"Arial", 8.5F, System::Drawing::FontStyle::Bold));
			this->PopUpDontShowChechBox->ForeColor = System::Drawing::Color::White;
			this->PopUpDontShowChechBox->Location = System::Drawing::Point(196, 3);
			this->PopUpDontShowChechBox->Name = L"PopUpDontShowChechBox";
			this->PopUpDontShowChechBox->Size = System::Drawing::Size(204, 18);
			this->PopUpDontShowChechBox->TabIndex = 31;
			this->PopUpDontShowChechBox->Text = L"Dont Show This Message Again";
			this->PopUpDontShowChechBox->UseVisualStyleBackColor = true;
			this->PopUpDontShowChechBox->CheckedChanged += gcnew System::EventHandler(this, &PopUpDialog::PopUpDontShowChechBox_CheckedChanged);
			// 
			// PopUpDialogOKButton
			// 
			this->PopUpDialogOKButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->PopUpDialogOKButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->PopUpDialogOKButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PopUpDialogOKButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->PopUpDialogOKButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PopUpDialogOKButton->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			this->PopUpDialogOKButton->ForeColor = System::Drawing::Color::White;
			this->PopUpDialogOKButton->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->PopUpDialogOKButton->Location = System::Drawing::Point(8, 32);
			this->PopUpDialogOKButton->Margin = System::Windows::Forms::Padding(8);
			this->PopUpDialogOKButton->Name = L"PopUpDialogOKButton";
			this->PopUpDialogOKButton->Size = System::Drawing::Size(581, 36);
			this->PopUpDialogOKButton->TabIndex = 9;
			this->PopUpDialogOKButton->Text = L"OK";
			this->PopUpDialogOKButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->PopUpDialogOKButton->UseVisualStyleBackColor = false;
			this->PopUpDialogOKButton->Click += gcnew System::EventHandler(this, &PopUpDialog::PopUpDialogOKButton_Click);
			// 
			// PopUpDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(603, 192);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"PopUpDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PopUpDialog";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);

		}

#pragma endregion

		// Pop-Up Dialog OK knap Callback Routine ->
		private: System::Void PopUpDialogOKButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Luk Pop-Up Dialogen
			this->Close();
			// Garbage collect
			GC::Collect();

		}
		
		// Pop-Up Dialog "Dont Show" Check Box Callback Routine ->
		private: System::Void PopUpDontShowChechBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater flaget for om Pop-Up Dialogen skal vises
			PopUpDialogDontShowFlag = (bool)this->PopUpDontShowChechBox->Checked;

		}

	};
}
