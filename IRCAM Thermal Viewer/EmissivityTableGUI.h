#pragma once

// Inkluderede Blblioteker
#include "RMH_Winforms_Library.h"

// Inkluderede applikations Resourcer
#include "RMH_EmissivityTable_Resources.h"

// Klasse Namespace
namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Summary for Form - MainGUI EmissivityTableGUI
	public ref class EmissivityTableGUI : public System::Windows::Forms::Form {

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		EmissivityTableGUI(void) {

			// Init GUI komponenter og objekter
			InitializeComponent();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Indlæs Data til Emissivity Tabellen
			RMH_Winforms_DataGridView_Display2ColumnDataGridView(
				this->EmissivityDataGridView, EmissivityTableHeaderStrings, 
				"Type:", 14, 12, 10, System::Drawing::Color::White, 
				System::Drawing::Color::FromArgb(255, 32, 32, 32), 50, 150, 
				EmissivityMaterialNames, &MaterialEmissivityValues[0]);

			// Opdaterer Teksten i toppen af GUIen
			RMH_Winforms_ChangeFormTitleBarText(this, "Emissivity Material Loop-Up Table");

		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EmissivityTableGUI() {

			if (components) {

				// Slet alle Form Komponenter
				delete components;

			}
		}
	
	protected:

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private: System::ComponentModel::Container ^components;
		private: System::Windows::Forms::Label^ label1;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		private: System::Windows::Forms::DataGridView^ EmissivityDataGridView;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(EmissivityTableGUI::typeid));
			this->EmissivityDataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EmissivityDataGridView))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// EmissivityDataGridView
			// 
			this->EmissivityDataGridView->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->EmissivityDataGridView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->EmissivityDataGridView->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::Color::White;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::Color::White;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->EmissivityDataGridView->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->EmissivityDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->EmissivityDataGridView->DefaultCellStyle = dataGridViewCellStyle2;
			this->EmissivityDataGridView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->EmissivityDataGridView->Location = System::Drawing::Point(3, 39);
			this->EmissivityDataGridView->Name = L"EmissivityDataGridView";
			this->EmissivityDataGridView->ReadOnly = true;
			this->EmissivityDataGridView->RowHeadersWidth = 500;
			this->EmissivityDataGridView->Size = System::Drawing::Size(1249, 832);
			this->EmissivityDataGridView->TabIndex = 0;
			this->EmissivityDataGridView->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &EmissivityTableGUI::EmissivityDataGridView_CellDoubleClick);
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(3, 10);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(633, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Double Click On A Emissivity Value, Material Or Type, To Load The Selected Value "
				L"To The Camera.";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->EmissivityDataGridView, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(20, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 36)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1255, 874);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// EmissivityTableGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(1295, 894);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"EmissivityTableGUI";
			this->Padding = System::Windows::Forms::Padding(20, 0, 20, 20);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"EmissivityTableGUI";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &EmissivityTableGUI::EmissivityTableGUI_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &EmissivityTableGUI::EmissivityTableGUI_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EmissivityDataGridView))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}

#pragma endregion

		// --------------- Emissivity GUI Opstartnings Og Nedluknings Callback Routiner --------------- //

		// Emissivity Tabel GUI Opstartnings Callback Routine -> 
		private: System::Void EmissivityTableGUI_Shown(System::Object^ sender, System::EventArgs^ e) {

			// Opdater tilhørende form Flag
			isEmissivityTableFormOpen = true;

		}

		// Emissivity Tabel GUI Nedluknings Callback Routine ->
		private: System::Void EmissivityTableGUI_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Opdater tilhørende form Flag
			isEmissivityTableFormOpen = false;
			isEmissivityTableFormDocked = false;
			isEmissivityTableFormUndocked = false;

			// Når Formen lukkes - Gem Formen
			this->Hide();
			// Deaktiver "Disposing" Af Form Objektet
			e->Cancel = true;

		}

		// ----------------------- Emissivity Tabel GUI Event Callback Routiner ----------------------- //

		// Emissivity Tabel Celle Double Click Event Callback Routine ->
		private: System::Void EmissivityDataGridView_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {

			// Indstil Valgte Emissivity Værdi Til Termiske Kamera
			RMH_ThermalViewer_LoadEmissivisyTableValueToThermalCamera(e);

		}

		// -------------------------------------------------------------------------------------------- //

};
}
