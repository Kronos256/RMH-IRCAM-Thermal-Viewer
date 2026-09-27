#pragma once

// Inkluderede Blblioteker

// Klasse Namespace
namespace IRCAMThermalViewer {
	
	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Reflection;
	using namespace System::IO;

	// Summary for Form - UserGuideViewerGUI
	public ref class UserGuideViewerGUI : public System::Windows::Forms::Form {

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		UserGuideViewerGUI(void) {

			// Init GUI komponenter og objekter
			InitializeComponent();
			// Indstil globale objekter fra denne Form til global brug
			InitializeGlobalFormsObjects();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Åben Software Manual PDF filen I Webbrowser Vinduet
			RMH_Winforms_OpenPDFInWebbrowser(this->webBrowser1, "IRCAMSoftwareManual.pdf");

		}

		// ---------------------------- Diverse Specifikke Klasse Metoder ----------------------------- //

		void InitializeGlobalFormsObjects() {

			// Routinen indstiller globale objekter fra denne form
			// Så disse kan blive tilgået fra andre Forms


			
		}

		// -------------------------------------------------------------------------------------------- //

	protected:
		
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UserGuideViewerGUI() {

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
		private: System::Windows::Forms::WebBrowser^ webBrowser1;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UserGuideViewerGUI::typeid));
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->SuspendLayout();
			// 
			// webBrowser1
			// 
			this->webBrowser1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->webBrowser1->Location = System::Drawing::Point(5, 5);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(1339, 871);
			this->webBrowser1->TabIndex = 0;
			// 
			// UserGuideViewerGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(1349, 881);
			this->Controls->Add(this->webBrowser1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"UserGuideViewerGUI";
			this->Padding = System::Windows::Forms::Padding(5);
			this->Text = L"UserGuideViewerGUI";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &UserGuideViewerGUI::UserGuideViewerGUI_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &UserGuideViewerGUI::UserGuideViewerGUI_Shown);
			this->ResumeLayout(false);

		}

#pragma endregion

		// ---------------------- Opstartnings Og Nedluknings Callback Routiner ----------------------- //

		// User Guide Form Opstartnings Callback Routine ->
		private: System::Void UserGuideViewerGUI_Shown(System::Object^ sender, System::EventArgs^ e) {

			// Opdater tilhørende form Flag
			isUserGuideFormOpen = true;
			
		}
 
		// User Guide Form Nedluknings Callback Routine -> 
		private: System::Void UserGuideViewerGUI_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Opdater tilhørende form Flag
			isUserGuideFormOpen = false;
			isUserGuideFormDocked = false;
			isUserGuideFormUndocked = false;

			// Når Formen lukkes - Gem Formen
			this->Hide();
			// Deaktiver "Disposing" Af Form Objektet
			e->Cancel = true;

		}

		// -------------------------------------------------------------------------------------------- //

	};
}
