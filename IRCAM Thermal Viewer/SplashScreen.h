#pragma once

namespace IRCAMThermalViewer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class SplashScreen : public System::Windows::Forms::Form
	{
	public:
		SplashScreen(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SplashScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ SplashLayout;
	protected:

	private: System::Windows::Forms::PictureBox^ SplashPictureBox;
	private: System::Windows::Forms::Timer^ SplashScreenTimer;

	private: System::ComponentModel::IContainer^ components;

	protected:


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SplashScreen::typeid));
			this->SplashLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->SplashPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->SplashScreenTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SplashLayout->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplashPictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// SplashLayout
			// 
			this->SplashLayout->ColumnCount = 1;
			this->SplashLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->SplashLayout->Controls->Add(this->SplashPictureBox, 0, 0);
			this->SplashLayout->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SplashLayout->Location = System::Drawing::Point(0, 0);
			this->SplashLayout->Margin = System::Windows::Forms::Padding(2);
			this->SplashLayout->Name = L"SplashLayout";
			this->SplashLayout->RowCount = 1;
			this->SplashLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->SplashLayout->Size = System::Drawing::Size(1400, 800);
			this->SplashLayout->TabIndex = 0;
			// 
			// SplashPictureBox
			// 
			this->SplashPictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SplashPictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SplashPictureBox.Image")));
			this->SplashPictureBox->Location = System::Drawing::Point(0, 0);
			this->SplashPictureBox->Margin = System::Windows::Forms::Padding(0);
			this->SplashPictureBox->Name = L"SplashPictureBox";
			this->SplashPictureBox->Size = System::Drawing::Size(1400, 800);
			this->SplashPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->SplashPictureBox->TabIndex = 0;
			this->SplashPictureBox->TabStop = false;
			// 
			// SplashScreenTimer
			// 
			this->SplashScreenTimer->Enabled = true;
			this->SplashScreenTimer->Interval = 3000;
			this->SplashScreenTimer->Tick += gcnew System::EventHandler(this, &SplashScreen::timer1_Tick);
			// 
			// SplashScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(1400, 800);
			this->Controls->Add(this->SplashLayout);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"SplashScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SplashScreen";
			this->TransparencyKey = System::Drawing::SystemColors::ActiveCaptionText;
			this->SplashLayout->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplashPictureBox))->EndInit();
			this->ResumeLayout(false);

		}

#pragma endregion

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		// Luk Splash Screen
		this->Close();

	}

};
}
