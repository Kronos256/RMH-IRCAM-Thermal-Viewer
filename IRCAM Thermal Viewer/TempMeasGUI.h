#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"

// Klasse Namespace
namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Summary for Form - TempMeasGUI
	public ref class TempMeasGUI : public System::Windows::Forms::Form {

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		TempMeasGUI(void) {

			// Init GUI komponenter og objekter
			InitializeComponent();
			// Formater arrays Og Objekter af winform komponenter til global brug
			InitializeComponentArraysAndGlobalObjects();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Opdaterer Teksten i toppen af GUIen
			RMH_Winforms_ChangeFormTitleBarText(this, "Temperature Measurements Plot");

		}

		// ---------------------------- Diverse Tilhørende Klasse Metoder ----------------------------- //

		void InitializeComponentArraysAndGlobalObjects(void) {

			// Routinen formaterer arrays af winform komponenter til global brug

			// Array Af 2D Plot Legend LAbels
			GlobalVariables::Plot2DLegendLabels = gcnew cli::array<System::Windows::Forms::Label^>(10) {
				this->LegendLabel1,
				this->LegendLabel2,
				this->LegendLabel3,
				this->LegendLabel4,
				this->LegendLabel5,
				this->LegendLabel6,
				this->LegendLabel7,
				this->LegendLabel8,
				this->LegendLabel9,
				this->LegendLabel10
			};

			// Generer textur til 2D plot OpenGL renderering
			GlobalVariables::OpenGL2DPlot = gcnew OpenGL2DPlot::RMHOpenGL2DPlot(this->Temp2DPlotPanel, 4, 4);

			// Sæt global data logging thread objekt
			GlobalVariables::GlobalDataLoggingThread = this->DataLoggingThread;

			// Opdater 2D Plot Legend
			RMH_ThermalViewer_Update2DPlotLegendLabels();

			// Opdater Temp Meas GUI ready flag
			TempMeasGUIReadyFlag = true;

		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TempMeasGUI() {

			// Opdater Temp Meas GUI ready flag
			TempMeasGUIReadyFlag = false;

			if (components) {

				// Slet alle Form Komponenter
				delete components;

			}
		}

	protected:

		private: System::ComponentModel::IContainer^ components;
		private: System::Windows::Forms::ContextMenuStrip^ TempMeasContextMenu;
		private: System::Windows::Forms::ToolStripMenuItem^ dMeasurementPlotToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
		private: System::Windows::Forms::ToolStripMenuItem^ xAxiesToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem3;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem4;
		private: System::Windows::Forms::ToolStripMenuItem^ yAxisNumberOfTicksToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem5;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem6;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem7;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem8;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem9;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem10;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;
		private: System::Windows::Forms::ToolStripMenuItem^ ticksToolStripMenuItem12;
		private: System::Windows::Forms::ToolStripMenuItem^ showPlotBorderBoxToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ showBoxToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ hIdeBoxToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ showPlotGridToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ showGridToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ hideGridToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator3;
		private: System::Windows::Forms::ToolStripMenuItem^ clearPlotToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator4;
		private: System::Windows::Forms::Label^ LegendLabel1;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
		private: System::Windows::Forms::Label^ LegendLabel10;
		private: System::Windows::Forms::Label^ LegendLabel9;
		private: System::Windows::Forms::Label^ LegendLabel8;
		private: System::Windows::Forms::Label^ LegendLabel7;
		private: System::Windows::Forms::Label^ LegendLabel6;
		private: System::Windows::Forms::Label^ LegendLabel5;
		private: System::Windows::Forms::Label^ LegendLabel4;
		private: System::Windows::Forms::Label^ LegendLabel3;
		private: System::Windows::Forms::Label^ LegendLabel2;
		private: System::Windows::Forms::Panel^ panel1;
		private: System::Windows::Forms::ToolStripMenuItem^ startDataLoggingToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ stopDataLoggingToolStripMenuItem;
		private: System::ComponentModel::BackgroundWorker^ DataLoggingThread;

	private:

		/// <summary>
		/// Required designer variable.
		/// </summary>

		public: System::Windows::Forms::Panel^ Temp2DPlotPanel;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(TempMeasGUI::typeid));
			this->Temp2DPlotPanel = (gcnew System::Windows::Forms::Panel());
			this->TempMeasContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->dMeasurementPlotToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->xAxiesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem12 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->yAxisNumberOfTicksToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem8 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem9 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ticksToolStripMenuItem10 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->showPlotBorderBoxToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showBoxToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hIdeBoxToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showPlotGridToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showGridToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hideGridToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->clearPlotToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->startDataLoggingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stopDataLoggingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->LegendLabel10 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel9 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel8 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel7 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel6 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel5 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel4 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel3 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel2 = (gcnew System::Windows::Forms::Label());
			this->LegendLabel1 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->DataLoggingThread = (gcnew System::ComponentModel::BackgroundWorker());
			this->TempMeasContextMenu->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// Temp2DPlotPanel
			// 
			this->Temp2DPlotPanel->ContextMenuStrip = this->TempMeasContextMenu;
			this->Temp2DPlotPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Temp2DPlotPanel->Location = System::Drawing::Point(0, 0);
			this->Temp2DPlotPanel->Margin = System::Windows::Forms::Padding(0);
			this->Temp2DPlotPanel->Name = L"Temp2DPlotPanel";
			this->Temp2DPlotPanel->Size = System::Drawing::Size(1580, 780);
			this->Temp2DPlotPanel->TabIndex = 0;
			// 
			// TempMeasContextMenu
			// 
			this->TempMeasContextMenu->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->TempMeasContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {
				this->dMeasurementPlotToolStripMenuItem,
					this->toolStripSeparator1, this->xAxiesToolStripMenuItem, this->yAxisNumberOfTicksToolStripMenuItem, this->toolStripSeparator2,
					this->showPlotBorderBoxToolStripMenuItem, this->showPlotGridToolStripMenuItem, this->toolStripSeparator3, this->clearPlotToolStripMenuItem,
					this->toolStripSeparator4, this->startDataLoggingToolStripMenuItem, this->stopDataLoggingToolStripMenuItem
			});
			this->TempMeasContextMenu->Name = L"TempMeasContextMenu";
			this->TempMeasContextMenu->ShowImageMargin = false;
			this->TempMeasContextMenu->Size = System::Drawing::Size(201, 204);
			// 
			// dMeasurementPlotToolStripMenuItem
			// 
			this->dMeasurementPlotToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->dMeasurementPlotToolStripMenuItem->Enabled = false;
			this->dMeasurementPlotToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->dMeasurementPlotToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->dMeasurementPlotToolStripMenuItem->Name = L"dMeasurementPlotToolStripMenuItem";
			this->dMeasurementPlotToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->dMeasurementPlotToolStripMenuItem->Text = L"2D Measurement Plot:";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripSeparator1->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(197, 6);
			// 
			// xAxiesToolStripMenuItem
			// 
			this->xAxiesToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->xAxiesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->toolStripMenuItem2,
					this->toolStripMenuItem3, this->ticksToolStripMenuItem, this->ticksToolStripMenuItem4, this->ticksToolStripMenuItem12
			});
			this->xAxiesToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->xAxiesToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->xAxiesToolStripMenuItem->Name = L"xAxiesToolStripMenuItem";
			this->xAxiesToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->xAxiesToolStripMenuItem->Text = L"X-Axis Number Of Ticks";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem2->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(120, 22);
			this->toolStripMenuItem2->Tag = L"5";
			this->toolStripMenuItem2->Text = L"5 Ticks";
			this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &TempMeasGUI::toolStripMenuItem2_Click);
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem3->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(120, 22);
			this->toolStripMenuItem3->Tag = L"10";
			this->toolStripMenuItem3->Text = L"10 Ticks";
			this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &TempMeasGUI::toolStripMenuItem2_Click);
			// 
			// ticksToolStripMenuItem
			// 
			this->ticksToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem->Name = L"ticksToolStripMenuItem";
			this->ticksToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem->Tag = L"20";
			this->ticksToolStripMenuItem->Text = L"20 Ticks";
			this->ticksToolStripMenuItem->Click += gcnew System::EventHandler(this, &TempMeasGUI::toolStripMenuItem2_Click);
			// 
			// ticksToolStripMenuItem4
			// 
			this->ticksToolStripMenuItem4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem4->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem4->Name = L"ticksToolStripMenuItem4";
			this->ticksToolStripMenuItem4->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem4->Tag = L"25";
			this->ticksToolStripMenuItem4->Text = L"25 Ticks";
			this->ticksToolStripMenuItem4->Click += gcnew System::EventHandler(this, &TempMeasGUI::toolStripMenuItem2_Click);
			// 
			// ticksToolStripMenuItem12
			// 
			this->ticksToolStripMenuItem12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem12->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem12->Name = L"ticksToolStripMenuItem12";
			this->ticksToolStripMenuItem12->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem12->Tag = L"50";
			this->ticksToolStripMenuItem12->Text = L"50 Ticks";
			this->ticksToolStripMenuItem12->Click += gcnew System::EventHandler(this, &TempMeasGUI::toolStripMenuItem2_Click);
			// 
			// yAxisNumberOfTicksToolStripMenuItem
			// 
			this->yAxisNumberOfTicksToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->yAxisNumberOfTicksToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->ticksToolStripMenuItem5,
					this->ticksToolStripMenuItem6, this->ticksToolStripMenuItem7, this->ticksToolStripMenuItem8, this->ticksToolStripMenuItem9, this->ticksToolStripMenuItem10
			});
			this->yAxisNumberOfTicksToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->yAxisNumberOfTicksToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->yAxisNumberOfTicksToolStripMenuItem->Name = L"yAxisNumberOfTicksToolStripMenuItem";
			this->yAxisNumberOfTicksToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->yAxisNumberOfTicksToolStripMenuItem->Text = L"Y-Axis Number Of Ticks";
			// 
			// ticksToolStripMenuItem5
			// 
			this->ticksToolStripMenuItem5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem5->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem5->Name = L"ticksToolStripMenuItem5";
			this->ticksToolStripMenuItem5->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem5->Tag = L"5";
			this->ticksToolStripMenuItem5->Text = L"5 Ticks";
			this->ticksToolStripMenuItem5->Click += gcnew System::EventHandler(this, &TempMeasGUI::ticksToolStripMenuItem5_Click);
			// 
			// ticksToolStripMenuItem6
			// 
			this->ticksToolStripMenuItem6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem6->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem6->Name = L"ticksToolStripMenuItem6";
			this->ticksToolStripMenuItem6->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem6->Tag = L"10";
			this->ticksToolStripMenuItem6->Text = L"10 Ticks";
			this->ticksToolStripMenuItem6->Click += gcnew System::EventHandler(this, &TempMeasGUI::ticksToolStripMenuItem5_Click);
			// 
			// ticksToolStripMenuItem7
			// 
			this->ticksToolStripMenuItem7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem7->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem7->Name = L"ticksToolStripMenuItem7";
			this->ticksToolStripMenuItem7->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem7->Tag = L"15";
			this->ticksToolStripMenuItem7->Text = L"15 Ticks";
			this->ticksToolStripMenuItem7->Click += gcnew System::EventHandler(this, &TempMeasGUI::ticksToolStripMenuItem5_Click);
			// 
			// ticksToolStripMenuItem8
			// 
			this->ticksToolStripMenuItem8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem8->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem8->Name = L"ticksToolStripMenuItem8";
			this->ticksToolStripMenuItem8->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem8->Tag = L"20";
			this->ticksToolStripMenuItem8->Text = L"20 Ticks";
			this->ticksToolStripMenuItem8->Click += gcnew System::EventHandler(this, &TempMeasGUI::ticksToolStripMenuItem5_Click);
			// 
			// ticksToolStripMenuItem9
			// 
			this->ticksToolStripMenuItem9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem9->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem9->Name = L"ticksToolStripMenuItem9";
			this->ticksToolStripMenuItem9->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem9->Tag = L"25";
			this->ticksToolStripMenuItem9->Text = L"25 Ticks";
			this->ticksToolStripMenuItem9->Click += gcnew System::EventHandler(this, &TempMeasGUI::ticksToolStripMenuItem5_Click);
			// 
			// ticksToolStripMenuItem10
			// 
			this->ticksToolStripMenuItem10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ticksToolStripMenuItem10->ForeColor = System::Drawing::Color::White;
			this->ticksToolStripMenuItem10->Name = L"ticksToolStripMenuItem10";
			this->ticksToolStripMenuItem10->Size = System::Drawing::Size(120, 22);
			this->ticksToolStripMenuItem10->Tag = L"30";
			this->ticksToolStripMenuItem10->Text = L"30 Ticks";
			this->ticksToolStripMenuItem10->Click += gcnew System::EventHandler(this, &TempMeasGUI::ticksToolStripMenuItem5_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripSeparator2->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(197, 6);
			// 
			// showPlotBorderBoxToolStripMenuItem
			// 
			this->showPlotBorderBoxToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->showPlotBorderBoxToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->showBoxToolStripMenuItem,
					this->hIdeBoxToolStripMenuItem
			});
			this->showPlotBorderBoxToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->showPlotBorderBoxToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->showPlotBorderBoxToolStripMenuItem->Name = L"showPlotBorderBoxToolStripMenuItem";
			this->showPlotBorderBoxToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->showPlotBorderBoxToolStripMenuItem->Text = L"Show Plot Border Box ";
			// 
			// showBoxToolStripMenuItem
			// 
			this->showBoxToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->showBoxToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->showBoxToolStripMenuItem->Name = L"showBoxToolStripMenuItem";
			this->showBoxToolStripMenuItem->Size = System::Drawing::Size(128, 22);
			this->showBoxToolStripMenuItem->Text = L"Show Box";
			this->showBoxToolStripMenuItem->Click += gcnew System::EventHandler(this, &TempMeasGUI::showBoxToolStripMenuItem_Click);
			// 
			// hIdeBoxToolStripMenuItem
			// 
			this->hIdeBoxToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->hIdeBoxToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->hIdeBoxToolStripMenuItem->Name = L"hIdeBoxToolStripMenuItem";
			this->hIdeBoxToolStripMenuItem->Size = System::Drawing::Size(128, 22);
			this->hIdeBoxToolStripMenuItem->Text = L"HIde Box";
			this->hIdeBoxToolStripMenuItem->Click += gcnew System::EventHandler(this, &TempMeasGUI::hIdeBoxToolStripMenuItem_Click);
			// 
			// showPlotGridToolStripMenuItem
			// 
			this->showPlotGridToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->showPlotGridToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->showGridToolStripMenuItem,
					this->hideGridToolStripMenuItem
			});
			this->showPlotGridToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->showPlotGridToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->showPlotGridToolStripMenuItem->Name = L"showPlotGridToolStripMenuItem";
			this->showPlotGridToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->showPlotGridToolStripMenuItem->Text = L"Show Plot Grid";
			// 
			// showGridToolStripMenuItem
			// 
			this->showGridToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->showGridToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->showGridToolStripMenuItem->Name = L"showGridToolStripMenuItem";
			this->showGridToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->showGridToolStripMenuItem->Text = L"Show Grid";
			this->showGridToolStripMenuItem->Click += gcnew System::EventHandler(this, &TempMeasGUI::showGridToolStripMenuItem_Click);
			// 
			// hideGridToolStripMenuItem
			// 
			this->hideGridToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->hideGridToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->hideGridToolStripMenuItem->Name = L"hideGridToolStripMenuItem";
			this->hideGridToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->hideGridToolStripMenuItem->Text = L"Hide Grid";
			this->hideGridToolStripMenuItem->Click += gcnew System::EventHandler(this, &TempMeasGUI::hideGridToolStripMenuItem_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripSeparator3->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(197, 6);
			// 
			// clearPlotToolStripMenuItem
			// 
			this->clearPlotToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->clearPlotToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->clearPlotToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->clearPlotToolStripMenuItem->Name = L"clearPlotToolStripMenuItem";
			this->clearPlotToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->clearPlotToolStripMenuItem->Text = L"Clear Plot Data";
			this->clearPlotToolStripMenuItem->Click += gcnew System::EventHandler(this, &TempMeasGUI::clearPlotToolStripMenuItem_Click);
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripSeparator4->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(197, 6);
			// 
			// startDataLoggingToolStripMenuItem
			// 
			this->startDataLoggingToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->startDataLoggingToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->startDataLoggingToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->startDataLoggingToolStripMenuItem->Name = L"startDataLoggingToolStripMenuItem";
			this->startDataLoggingToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->startDataLoggingToolStripMenuItem->Text = L"Start Data Logging Session";
			this->startDataLoggingToolStripMenuItem->Click += gcnew System::EventHandler(this, &TempMeasGUI::startDataLoggingToolStripMenuItem_Click);
			// 
			// stopDataLoggingToolStripMenuItem
			// 
			this->stopDataLoggingToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->stopDataLoggingToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->stopDataLoggingToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->stopDataLoggingToolStripMenuItem->Name = L"stopDataLoggingToolStripMenuItem";
			this->stopDataLoggingToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->stopDataLoggingToolStripMenuItem->Text = L"Stop Data Logging Session";
			this->stopDataLoggingToolStripMenuItem->Click += gcnew System::EventHandler(this, &TempMeasGUI::stopDataLoggingToolStripMenuItem_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->Temp2DPlotPanel, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 22)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1580, 802);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 12;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				3)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				9.399999F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				3)));
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel10, 10, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel9, 9, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel8, 8, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel7, 7, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel6, 6, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel5, 5, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel4, 4, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel3, 3, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel2, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->LegendLabel1, 1, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(0, 780);
			this->tableLayoutPanel2->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(1580, 22);
			this->tableLayoutPanel2->TabIndex = 2;
			// 
			// LegendLabel10
			// 
			this->LegendLabel10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel10->AutoSize = true;
			this->LegendLabel10->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel10->Location = System::Drawing::Point(1379, 0);
			this->LegendLabel10->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel10->Name = L"LegendLabel10";
			this->LegendLabel10->Size = System::Drawing::Size(148, 22);
			this->LegendLabel10->TabIndex = 9;
			this->LegendLabel10->Text = L"Legend 10";
			this->LegendLabel10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel10->Visible = false;
			// 
			// LegendLabel9
			// 
			this->LegendLabel9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel9->AutoSize = true;
			this->LegendLabel9->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel9->Location = System::Drawing::Point(1231, 0);
			this->LegendLabel9->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel9->Name = L"LegendLabel9";
			this->LegendLabel9->Size = System::Drawing::Size(148, 22);
			this->LegendLabel9->TabIndex = 8;
			this->LegendLabel9->Text = L"Legend 9";
			this->LegendLabel9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel9->Visible = false;
			// 
			// LegendLabel8
			// 
			this->LegendLabel8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel8->AutoSize = true;
			this->LegendLabel8->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel8->Location = System::Drawing::Point(1083, 0);
			this->LegendLabel8->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel8->Name = L"LegendLabel8";
			this->LegendLabel8->Size = System::Drawing::Size(148, 22);
			this->LegendLabel8->TabIndex = 7;
			this->LegendLabel8->Text = L"Legend 8";
			this->LegendLabel8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel8->Visible = false;
			// 
			// LegendLabel7
			// 
			this->LegendLabel7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel7->AutoSize = true;
			this->LegendLabel7->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel7->Location = System::Drawing::Point(935, 0);
			this->LegendLabel7->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel7->Name = L"LegendLabel7";
			this->LegendLabel7->Size = System::Drawing::Size(148, 22);
			this->LegendLabel7->TabIndex = 6;
			this->LegendLabel7->Text = L"Legend 7";
			this->LegendLabel7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel7->Visible = false;
			// 
			// LegendLabel6
			// 
			this->LegendLabel6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel6->AutoSize = true;
			this->LegendLabel6->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel6->Location = System::Drawing::Point(787, 0);
			this->LegendLabel6->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel6->Name = L"LegendLabel6";
			this->LegendLabel6->Size = System::Drawing::Size(148, 22);
			this->LegendLabel6->TabIndex = 5;
			this->LegendLabel6->Text = L"Legend 6";
			this->LegendLabel6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel6->Visible = false;
			// 
			// LegendLabel5
			// 
			this->LegendLabel5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel5->AutoSize = true;
			this->LegendLabel5->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel5->Location = System::Drawing::Point(639, 0);
			this->LegendLabel5->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel5->Name = L"LegendLabel5";
			this->LegendLabel5->Size = System::Drawing::Size(148, 22);
			this->LegendLabel5->TabIndex = 4;
			this->LegendLabel5->Text = L"Legend 5";
			this->LegendLabel5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel5->Visible = false;
			// 
			// LegendLabel4
			// 
			this->LegendLabel4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel4->AutoSize = true;
			this->LegendLabel4->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel4->Location = System::Drawing::Point(491, 0);
			this->LegendLabel4->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel4->Name = L"LegendLabel4";
			this->LegendLabel4->Size = System::Drawing::Size(148, 22);
			this->LegendLabel4->TabIndex = 3;
			this->LegendLabel4->Text = L"Legend 4";
			this->LegendLabel4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel4->Visible = false;
			// 
			// LegendLabel3
			// 
			this->LegendLabel3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel3->AutoSize = true;
			this->LegendLabel3->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel3->Location = System::Drawing::Point(343, 0);
			this->LegendLabel3->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel3->Name = L"LegendLabel3";
			this->LegendLabel3->Size = System::Drawing::Size(148, 22);
			this->LegendLabel3->TabIndex = 2;
			this->LegendLabel3->Text = L"Legend 3";
			this->LegendLabel3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel3->Visible = false;
			// 
			// LegendLabel2
			// 
			this->LegendLabel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel2->AutoSize = true;
			this->LegendLabel2->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel2->Location = System::Drawing::Point(195, 0);
			this->LegendLabel2->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel2->Name = L"LegendLabel2";
			this->LegendLabel2->Size = System::Drawing::Size(148, 22);
			this->LegendLabel2->TabIndex = 1;
			this->LegendLabel2->Text = L"Legend 2";
			this->LegendLabel2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel2->Visible = false;
			// 
			// LegendLabel1
			// 
			this->LegendLabel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LegendLabel1->AutoSize = true;
			this->LegendLabel1->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Bold));
			this->LegendLabel1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->LegendLabel1->Location = System::Drawing::Point(47, 0);
			this->LegendLabel1->Margin = System::Windows::Forms::Padding(0);
			this->LegendLabel1->Name = L"LegendLabel1";
			this->LegendLabel1->Size = System::Drawing::Size(148, 22);
			this->LegendLabel1->TabIndex = 0;
			this->LegendLabel1->Text = L"Legend 1";
			this->LegendLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->LegendLabel1->Visible = false;
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->tableLayoutPanel1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(10, 10);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1582, 804);
			this->panel1->TabIndex = 2;
			// 
			// DataLoggingThread
			// 
			this->DataLoggingThread->WorkerReportsProgress = true;
			this->DataLoggingThread->WorkerSupportsCancellation = true;
			this->DataLoggingThread->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &TempMeasGUI::DataLoggingThread_DoWork);
			// 
			// TempMeasGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(1602, 824);
			this->Controls->Add(this->panel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"TempMeasGUI";
			this->Padding = System::Windows::Forms::Padding(10);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"TempMeasGUI";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &TempMeasGUI::TempMeasGUI_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &TempMeasGUI::TempMeasGUI_Shown);
			this->TempMeasContextMenu->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}

#pragma endregion

		// ------------------ Temp GUI Opstartnings Og Nedluknings Callback Routiner ------------------ //

		// Temp Meas GUI Form Opstartnings Callback Routine -> 
		private: System::Void TempMeasGUI_Shown(System::Object^ sender, System::EventArgs^ e) {

			// Opdater tilhørende form Flag
			isTempMeasurementsFormOpen = true;

		}

		// Temp Meas GUI Form Nedluknings Callback Routine ->
		private: System::Void TempMeasGUI_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Opdater tilhørende form Flag
			isTempMeasurementsFormOpen = false;
			isTempMeasurementsFormDocked = false;
			isTempMeasurementsFormUndocked = false;

			// Når Formen lukkes - Gem Formen
			this->Hide();
			// Deaktiver "Disposing" Af Form Objektet
			e->Cancel = true;

		}

		// ----------------------- Temp Meas GUI Context Menu Callback Routiner ----------------------- //

		// X-Axis Number Of Ticks Context Menu Callback Routine ->
		private: System::Void toolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater antallet af X Ticks
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_Set2DPlotNumberOfXTicks(sender);

		}

		// Y-Axis Number Of Ticks Context Menu Callback Routine ->
		private: System::Void ticksToolStripMenuItem5_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater antallet af X Ticks
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_Set2DPlotNumberOfYTicks(sender);

		}

		// Vis Plot Box Context Menu Callback Routine ->
		private: System::Void showBoxToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Vis 2D Plottets grænse Box
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_Enable2DPlotBox(true);

		}

		// Skjul Plot Box Context Menu Callback Routine ->
		private: System::Void hIdeBoxToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Skjul 2D Plottets grænse Box
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_Enable2DPlotBox(false);

		}

		// Vis Plot Grid Context Menu Callback Routine ->
		private: System::Void showGridToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Vis 2D Plottets Grid linjer
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_Enable2DPlotGridLines(true);

		}

		// Skjul Plot Grid Context Menu Callback Routine ->
		private: System::Void hideGridToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Skjul 2D Plottets Grid linjer
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_Enable2DPlotGridLines(false);

		}

		// Ryd Plot Context Menu Callback Routine ->
		private: System::Void clearPlotToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Nulstil 2D plottets data og ryd 2D plottet
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_Clear2DPlot();

		}

		// Start Data Logging Context Menu Callback Routine ->
		private: System::Void startDataLoggingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Start Data logging
			RMH_ThermalViewer_StartDataLogging();

		}
		
		// Sttop Data Logging Context Menu Callback Routine ->
		private: System::Void stopDataLoggingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Stop Data logging
			RMH_ThermalViewer_StopDataLogging();

		}

		// ------------------------- Data Logging Thread Do-Work Callback ----------------------------- //

		// Data Logging Thread Do Work Event Callback Routine ->
		private: System::Void DataLoggingThread_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

			// Eksikver Data logging Thread process
			RMH_ThermalViewer_DataLoggingThreadProcess();

		}

		// -------------------------------------------------------------------------------------------- //

};
}
