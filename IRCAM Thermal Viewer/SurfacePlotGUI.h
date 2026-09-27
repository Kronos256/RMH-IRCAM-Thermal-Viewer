#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"
#include "RMH_Application_ThermalViewer.h"

namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Summary for Form - LiveViewStream
	public ref class SurfacePlotGUI : public System::Windows::Forms::Form {

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		SurfacePlotGUI() {

			// Init GUI komponenter og objekter
			InitializeComponent();
			// Formater arrays Og Objekter af winform komponenter til global brug
			InitializeComponentArraysAndGlobalObjects();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);
			
			// Opdaterer Teksten i toppen af GUIen
			RMH_Winforms_ChangeFormTitleBarText(this, "3D Surface Plot");

		}

		// ---------------------------- Diverse Tilhørende Klasse Metoder ----------------------------- //

		void InitializeComponentArraysAndGlobalObjects(void) {

			// Routinen formaterer arrays af winform komponenter til global brug

			// Initiliser Globale form objekter
			GlobalVariables::OpenGLSurfacePlot = gcnew OpenGLSurfacePlot::RMHOpenGLSurfacePlot(this->SurfacePlotPanel, 4, 4);
			GlobalVariables::GlobalSurfacePlotPanel = this->SurfacePlotPanel;

		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SurfacePlotGUI() {

			if (components) {

				// Slet alle Form Komponenter
				delete components;

			}

			// Ryd op i managed objekter i RAM
			System::GC::Collect();

		}
	
	protected:

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private: System::ComponentModel::IContainer^ components;
		public: System::Windows::Forms::Panel^ SurfacePlotPanel;
		private: System::Windows::Forms::ContextMenuStrip^ SurfacePlotContextMenu;
		private: System::Windows::Forms::ToolStripMenuItem^ dSurfacePlotToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
		private: System::Windows::Forms::ToolStripMenuItem^ resetToDefaultViewToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;
		private: System::Windows::Forms::ToolStripMenuItem^ saveSnapshotToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator3;
		private: System::Windows::Forms::ToolStripMenuItem^ surfaceZDataScaleToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ ZDataScaleMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ ZDataScaleMenuItem3;
		private: System::Windows::Forms::ToolStripMenuItem^ ZDataScaleMenuItem4;
		private: System::Windows::Forms::ToolStripMenuItem^ ZDataScaleMenuItem5;
		private: System::Windows::Forms::ToolStripMenuItem^ ZDataScaleMenuItem6;
		private: System::Windows::Forms::ToolStripMenuItem^ ZDataScaleMenuItem7;
		private: System::Windows::Forms::ToolStripMenuItem^ ZDataScaleMenuItem8;
		private: System::Windows::Forms::ToolStripMenuItem^ xToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ xToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ xToolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ xToolStripMenuItem3;
		private: System::Windows::Forms::ToolStripMenuItem^ polygonModeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ pointModeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ lineModeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ fillModeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ pointModeSizeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem3;
		private: System::Windows::Forms::ToolStripMenuItem^ size3ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ size4ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ size5ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ lineModeSizeToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ size1ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ size2ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ size3ToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ size4ToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^ size5ToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator4;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem8;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem7;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem6;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem4;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem5;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem9;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem10;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem11;
		private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem12;
		private: System::Windows::Forms::ToolStripMenuItem^ ZDataScaleMenuItem9;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SurfacePlotGUI::typeid));
			this->SurfacePlotPanel = (gcnew System::Windows::Forms::Panel());
			this->SurfacePlotContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->dSurfacePlotToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->polygonModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pointModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fillModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pointModeSizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->size3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->size4ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->size5ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineModeSizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->size1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->size2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->size3ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->size4ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->size5ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->resetToDefaultViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveSnapshotToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->surfaceZDataScaleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem8 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ZDataScaleMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ZDataScaleMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ZDataScaleMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ZDataScaleMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ZDataScaleMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ZDataScaleMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xToolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ZDataScaleMenuItem8 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ZDataScaleMenuItem9 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem9 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem10 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem11 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem12 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SurfacePlotContextMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// SurfacePlotPanel
			// 
			this->SurfacePlotPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SurfacePlotPanel->ContextMenuStrip = this->SurfacePlotContextMenu;
			this->SurfacePlotPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SurfacePlotPanel->Location = System::Drawing::Point(5, 5);
			this->SurfacePlotPanel->Name = L"SurfacePlotPanel";
			this->SurfacePlotPanel->Size = System::Drawing::Size(1435, 803);
			this->SurfacePlotPanel->TabIndex = 0;
			// 
			// SurfacePlotContextMenu
			// 
			this->SurfacePlotContextMenu->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->SurfacePlotContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
				this->dSurfacePlotToolStripMenuItem,
					this->toolStripSeparator4, this->polygonModeToolStripMenuItem, this->pointModeSizeToolStripMenuItem, this->lineModeSizeToolStripMenuItem,
					this->toolStripSeparator1, this->resetToDefaultViewToolStripMenuItem, this->toolStripSeparator2, this->saveSnapshotToolStripMenuItem,
					this->toolStripSeparator3, this->surfaceZDataScaleToolStripMenuItem
			});
			this->SurfacePlotContextMenu->Name = L"SurfacePlotContextMenu";
			this->SurfacePlotContextMenu->ShowImageMargin = false;
			this->SurfacePlotContextMenu->Size = System::Drawing::Size(175, 182);
			// 
			// dSurfacePlotToolStripMenuItem
			// 
			this->dSurfacePlotToolStripMenuItem->Enabled = false;
			this->dSurfacePlotToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->dSurfacePlotToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->dSurfacePlotToolStripMenuItem->Name = L"dSurfacePlotToolStripMenuItem";
			this->dSurfacePlotToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->dSurfacePlotToolStripMenuItem->Text = L"3D Surface Plot:";
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(171, 6);
			// 
			// polygonModeToolStripMenuItem
			// 
			this->polygonModeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->pointModeToolStripMenuItem,
					this->lineModeToolStripMenuItem, this->fillModeToolStripMenuItem
			});
			this->polygonModeToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->polygonModeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->polygonModeToolStripMenuItem->Name = L"polygonModeToolStripMenuItem";
			this->polygonModeToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->polygonModeToolStripMenuItem->Text = L"Polygon Mode";
			// 
			// pointModeToolStripMenuItem
			// 
			this->pointModeToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->pointModeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->pointModeToolStripMenuItem->Name = L"pointModeToolStripMenuItem";
			this->pointModeToolStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->pointModeToolStripMenuItem->Tag = L"0";
			this->pointModeToolStripMenuItem->Text = L"Point Mode";
			this->pointModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::pointModeToolStripMenuItem_Click);
			// 
			// lineModeToolStripMenuItem
			// 
			this->lineModeToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->lineModeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->lineModeToolStripMenuItem->Name = L"lineModeToolStripMenuItem";
			this->lineModeToolStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->lineModeToolStripMenuItem->Tag = L"1";
			this->lineModeToolStripMenuItem->Text = L"Line Mode";
			this->lineModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::pointModeToolStripMenuItem_Click);
			// 
			// fillModeToolStripMenuItem
			// 
			this->fillModeToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->fillModeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->fillModeToolStripMenuItem->Name = L"fillModeToolStripMenuItem";
			this->fillModeToolStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->fillModeToolStripMenuItem->Tag = L"2";
			this->fillModeToolStripMenuItem->Text = L"Fill Mode";
			this->fillModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::pointModeToolStripMenuItem_Click);
			// 
			// pointModeSizeToolStripMenuItem
			// 
			this->pointModeSizeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->toolStripMenuItem2,
					this->toolStripMenuItem3, this->size3ToolStripMenuItem, this->size4ToolStripMenuItem, this->size5ToolStripMenuItem
			});
			this->pointModeSizeToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->pointModeSizeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->pointModeSizeToolStripMenuItem->Name = L"pointModeSizeToolStripMenuItem";
			this->pointModeSizeToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->pointModeSizeToolStripMenuItem->Text = L"Point Mode Size";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem2->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(110, 22);
			this->toolStripMenuItem2->Tag = L"1";
			this->toolStripMenuItem2->Text = L"Size: 1";
			this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::toolStripMenuItem2_Click);
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem3->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(110, 22);
			this->toolStripMenuItem3->Tag = L"2";
			this->toolStripMenuItem3->Text = L"Size: 2";
			this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::toolStripMenuItem2_Click);
			// 
			// size3ToolStripMenuItem
			// 
			this->size3ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->size3ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->size3ToolStripMenuItem->Name = L"size3ToolStripMenuItem";
			this->size3ToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->size3ToolStripMenuItem->Tag = L"3";
			this->size3ToolStripMenuItem->Text = L"Size: 3";
			this->size3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::toolStripMenuItem2_Click);
			// 
			// size4ToolStripMenuItem
			// 
			this->size4ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->size4ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->size4ToolStripMenuItem->Name = L"size4ToolStripMenuItem";
			this->size4ToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->size4ToolStripMenuItem->Tag = L"4";
			this->size4ToolStripMenuItem->Text = L"Size: 4";
			this->size4ToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::toolStripMenuItem2_Click);
			// 
			// size5ToolStripMenuItem
			// 
			this->size5ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->size5ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->size5ToolStripMenuItem->Name = L"size5ToolStripMenuItem";
			this->size5ToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->size5ToolStripMenuItem->Tag = L"5";
			this->size5ToolStripMenuItem->Text = L"Size: 5";
			this->size5ToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::toolStripMenuItem2_Click);
			// 
			// lineModeSizeToolStripMenuItem
			// 
			this->lineModeSizeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->size1ToolStripMenuItem,
					this->size2ToolStripMenuItem, this->size3ToolStripMenuItem1, this->size4ToolStripMenuItem1, this->size5ToolStripMenuItem1
			});
			this->lineModeSizeToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->lineModeSizeToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->lineModeSizeToolStripMenuItem->Name = L"lineModeSizeToolStripMenuItem";
			this->lineModeSizeToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->lineModeSizeToolStripMenuItem->Text = L"Line Mode Size";
			// 
			// size1ToolStripMenuItem
			// 
			this->size1ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->size1ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->size1ToolStripMenuItem->Name = L"size1ToolStripMenuItem";
			this->size1ToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->size1ToolStripMenuItem->Tag = L"1";
			this->size1ToolStripMenuItem->Text = L"Size: 1";
			this->size1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::size1ToolStripMenuItem_Click);
			// 
			// size2ToolStripMenuItem
			// 
			this->size2ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->size2ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->size2ToolStripMenuItem->Name = L"size2ToolStripMenuItem";
			this->size2ToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->size2ToolStripMenuItem->Tag = L"2";
			this->size2ToolStripMenuItem->Text = L"Size: 2";
			this->size2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::size1ToolStripMenuItem_Click);
			// 
			// size3ToolStripMenuItem1
			// 
			this->size3ToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->size3ToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->size3ToolStripMenuItem1->Name = L"size3ToolStripMenuItem1";
			this->size3ToolStripMenuItem1->Size = System::Drawing::Size(110, 22);
			this->size3ToolStripMenuItem1->Tag = L"3";
			this->size3ToolStripMenuItem1->Text = L"Size: 3";
			this->size3ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::size1ToolStripMenuItem_Click);
			// 
			// size4ToolStripMenuItem1
			// 
			this->size4ToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->size4ToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->size4ToolStripMenuItem1->Name = L"size4ToolStripMenuItem1";
			this->size4ToolStripMenuItem1->Size = System::Drawing::Size(110, 22);
			this->size4ToolStripMenuItem1->Tag = L"4";
			this->size4ToolStripMenuItem1->Text = L"Size: 4";
			this->size4ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::size1ToolStripMenuItem_Click);
			// 
			// size5ToolStripMenuItem1
			// 
			this->size5ToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->size5ToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->size5ToolStripMenuItem1->Name = L"size5ToolStripMenuItem1";
			this->size5ToolStripMenuItem1->Size = System::Drawing::Size(110, 22);
			this->size5ToolStripMenuItem1->Tag = L"5";
			this->size5ToolStripMenuItem1->Text = L"Size: 5";
			this->size5ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::size1ToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(171, 6);
			// 
			// resetToDefaultViewToolStripMenuItem
			// 
			this->resetToDefaultViewToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->resetToDefaultViewToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->resetToDefaultViewToolStripMenuItem->Name = L"resetToDefaultViewToolStripMenuItem";
			this->resetToDefaultViewToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->resetToDefaultViewToolStripMenuItem->Text = L"Reset To Default View";
			this->resetToDefaultViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::resetToDefaultViewToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(171, 6);
			// 
			// saveSnapshotToolStripMenuItem
			// 
			this->saveSnapshotToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->saveSnapshotToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->saveSnapshotToolStripMenuItem->Name = L"saveSnapshotToolStripMenuItem";
			this->saveSnapshotToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->saveSnapshotToolStripMenuItem->Text = L"Save Snapshot";
			this->saveSnapshotToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::saveSnapshotToolStripMenuItem_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->ForeColor = System::Drawing::Color::White;
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(171, 6);
			// 
			// surfaceZDataScaleToolStripMenuItem
			// 
			this->surfaceZDataScaleToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(21) {
				this->toolStripMenuItem8,
					this->toolStripMenuItem7, this->toolStripMenuItem6, this->toolStripMenuItem4, this->toolStripMenuItem5, this->ZDataScaleMenuItem2,
					this->ZDataScaleMenuItem3, this->ZDataScaleMenuItem4, this->ZDataScaleMenuItem5, this->ZDataScaleMenuItem6, this->ZDataScaleMenuItem7,
					this->xToolStripMenuItem, this->xToolStripMenuItem1, this->xToolStripMenuItem2, this->xToolStripMenuItem3, this->ZDataScaleMenuItem8,
					this->ZDataScaleMenuItem9, this->toolStripMenuItem9, this->toolStripMenuItem10, this->toolStripMenuItem11, this->toolStripMenuItem12
			});
			this->surfaceZDataScaleToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->surfaceZDataScaleToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->surfaceZDataScaleToolStripMenuItem->Name = L"surfaceZDataScaleToolStripMenuItem";
			this->surfaceZDataScaleToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->surfaceZDataScaleToolStripMenuItem->Text = L"Surface Z Height Scale";
			// 
			// toolStripMenuItem8
			// 
			this->toolStripMenuItem8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem8->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem8->Name = L"toolStripMenuItem8";
			this->toolStripMenuItem8->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem8->Tag = L"0.1";
			this->toolStripMenuItem8->Text = L"-90%";
			this->toolStripMenuItem8->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// toolStripMenuItem7
			// 
			this->toolStripMenuItem7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem7->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem7->Name = L"toolStripMenuItem7";
			this->toolStripMenuItem7->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem7->Tag = L"0.2";
			this->toolStripMenuItem7->Text = L"-80%";
			this->toolStripMenuItem7->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// toolStripMenuItem6
			// 
			this->toolStripMenuItem6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem6->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
			this->toolStripMenuItem6->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem6->Tag = L"0.3";
			this->toolStripMenuItem6->Text = L"-70%";
			this->toolStripMenuItem6->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// toolStripMenuItem4
			// 
			this->toolStripMenuItem4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem4->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
			this->toolStripMenuItem4->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem4->Tag = L"0.4";
			this->toolStripMenuItem4->Text = L"-60%";
			this->toolStripMenuItem4->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// toolStripMenuItem5
			// 
			this->toolStripMenuItem5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem5->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
			this->toolStripMenuItem5->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem5->Tag = L"0.5";
			this->toolStripMenuItem5->Text = L"-50% - Default";
			this->toolStripMenuItem5->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// ZDataScaleMenuItem2
			// 
			this->ZDataScaleMenuItem2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ZDataScaleMenuItem2->ForeColor = System::Drawing::Color::White;
			this->ZDataScaleMenuItem2->Name = L"ZDataScaleMenuItem2";
			this->ZDataScaleMenuItem2->Size = System::Drawing::Size(152, 22);
			this->ZDataScaleMenuItem2->Tag = L"0.6";
			this->ZDataScaleMenuItem2->Text = L"-40%";
			this->ZDataScaleMenuItem2->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// ZDataScaleMenuItem3
			// 
			this->ZDataScaleMenuItem3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ZDataScaleMenuItem3->ForeColor = System::Drawing::Color::White;
			this->ZDataScaleMenuItem3->Name = L"ZDataScaleMenuItem3";
			this->ZDataScaleMenuItem3->Size = System::Drawing::Size(152, 22);
			this->ZDataScaleMenuItem3->Tag = L"0.7";
			this->ZDataScaleMenuItem3->Text = L"-30%";
			this->ZDataScaleMenuItem3->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// ZDataScaleMenuItem4
			// 
			this->ZDataScaleMenuItem4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ZDataScaleMenuItem4->ForeColor = System::Drawing::Color::White;
			this->ZDataScaleMenuItem4->Name = L"ZDataScaleMenuItem4";
			this->ZDataScaleMenuItem4->Size = System::Drawing::Size(152, 22);
			this->ZDataScaleMenuItem4->Tag = L"0.8";
			this->ZDataScaleMenuItem4->Text = L"-20%";
			this->ZDataScaleMenuItem4->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// ZDataScaleMenuItem5
			// 
			this->ZDataScaleMenuItem5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ZDataScaleMenuItem5->ForeColor = System::Drawing::Color::White;
			this->ZDataScaleMenuItem5->Name = L"ZDataScaleMenuItem5";
			this->ZDataScaleMenuItem5->Size = System::Drawing::Size(152, 22);
			this->ZDataScaleMenuItem5->Tag = L"0.9";
			this->ZDataScaleMenuItem5->Text = L"-10%";
			this->ZDataScaleMenuItem5->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// ZDataScaleMenuItem6
			// 
			this->ZDataScaleMenuItem6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ZDataScaleMenuItem6->ForeColor = System::Drawing::Color::White;
			this->ZDataScaleMenuItem6->Name = L"ZDataScaleMenuItem6";
			this->ZDataScaleMenuItem6->Size = System::Drawing::Size(152, 22);
			this->ZDataScaleMenuItem6->Tag = L"0.95";
			this->ZDataScaleMenuItem6->Text = L"-5%";
			this->ZDataScaleMenuItem6->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// ZDataScaleMenuItem7
			// 
			this->ZDataScaleMenuItem7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ZDataScaleMenuItem7->ForeColor = System::Drawing::Color::White;
			this->ZDataScaleMenuItem7->Name = L"ZDataScaleMenuItem7";
			this->ZDataScaleMenuItem7->Size = System::Drawing::Size(152, 22);
			this->ZDataScaleMenuItem7->Tag = L"0";
			this->ZDataScaleMenuItem7->Text = L"0%";
			this->ZDataScaleMenuItem7->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// xToolStripMenuItem
			// 
			this->xToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->xToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->xToolStripMenuItem->Name = L"xToolStripMenuItem";
			this->xToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->xToolStripMenuItem->Tag = L"1.05";
			this->xToolStripMenuItem->Text = L"+5%";
			this->xToolStripMenuItem->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// xToolStripMenuItem1
			// 
			this->xToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->xToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
			this->xToolStripMenuItem1->Name = L"xToolStripMenuItem1";
			this->xToolStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->xToolStripMenuItem1->Tag = L"1.1";
			this->xToolStripMenuItem1->Text = L"+10%";
			this->xToolStripMenuItem1->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// xToolStripMenuItem2
			// 
			this->xToolStripMenuItem2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->xToolStripMenuItem2->ForeColor = System::Drawing::Color::White;
			this->xToolStripMenuItem2->Name = L"xToolStripMenuItem2";
			this->xToolStripMenuItem2->Size = System::Drawing::Size(152, 22);
			this->xToolStripMenuItem2->Tag = L"1.2";
			this->xToolStripMenuItem2->Text = L"+20%";
			this->xToolStripMenuItem2->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// xToolStripMenuItem3
			// 
			this->xToolStripMenuItem3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->xToolStripMenuItem3->ForeColor = System::Drawing::Color::White;
			this->xToolStripMenuItem3->Name = L"xToolStripMenuItem3";
			this->xToolStripMenuItem3->Size = System::Drawing::Size(152, 22);
			this->xToolStripMenuItem3->Tag = L"1.3";
			this->xToolStripMenuItem3->Text = L"+30%";
			this->xToolStripMenuItem3->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// ZDataScaleMenuItem8
			// 
			this->ZDataScaleMenuItem8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ZDataScaleMenuItem8->ForeColor = System::Drawing::Color::White;
			this->ZDataScaleMenuItem8->Name = L"ZDataScaleMenuItem8";
			this->ZDataScaleMenuItem8->Size = System::Drawing::Size(152, 22);
			this->ZDataScaleMenuItem8->Tag = L"1.4";
			this->ZDataScaleMenuItem8->Text = L"+40%";
			this->ZDataScaleMenuItem8->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// ZDataScaleMenuItem9
			// 
			this->ZDataScaleMenuItem9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ZDataScaleMenuItem9->ForeColor = System::Drawing::Color::White;
			this->ZDataScaleMenuItem9->Name = L"ZDataScaleMenuItem9";
			this->ZDataScaleMenuItem9->Size = System::Drawing::Size(152, 22);
			this->ZDataScaleMenuItem9->Tag = L"1.5";
			this->ZDataScaleMenuItem9->Text = L"+50%";
			this->ZDataScaleMenuItem9->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// toolStripMenuItem9
			// 
			this->toolStripMenuItem9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem9->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem9->Name = L"toolStripMenuItem9";
			this->toolStripMenuItem9->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem9->Tag = L"1.5";
			this->toolStripMenuItem9->Text = L"+60%";
			this->toolStripMenuItem9->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// toolStripMenuItem10
			// 
			this->toolStripMenuItem10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem10->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem10->Name = L"toolStripMenuItem10";
			this->toolStripMenuItem10->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem10->Tag = L"1.7";
			this->toolStripMenuItem10->Text = L"+70%";
			this->toolStripMenuItem10->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// toolStripMenuItem11
			// 
			this->toolStripMenuItem11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem11->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem11->Name = L"toolStripMenuItem11";
			this->toolStripMenuItem11->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem11->Tag = L"1.8";
			this->toolStripMenuItem11->Text = L"+80%";
			this->toolStripMenuItem11->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// toolStripMenuItem12
			// 
			this->toolStripMenuItem12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->toolStripMenuItem12->ForeColor = System::Drawing::Color::White;
			this->toolStripMenuItem12->Name = L"toolStripMenuItem12";
			this->toolStripMenuItem12->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem12->Tag = L"1.9";
			this->toolStripMenuItem12->Text = L"+90%";
			this->toolStripMenuItem12->Click += gcnew System::EventHandler(this, &SurfacePlotGUI::ZDataScaleMenuItem2_Click);
			// 
			// SurfacePlotGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(1445, 813);
			this->Controls->Add(this->SurfacePlotPanel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"SurfacePlotGUI";
			this->Padding = System::Windows::Forms::Padding(5);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SurfacePlotGUI";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SurfacePlotGUI::SurfacePlotGUI_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &SurfacePlotGUI::SurfacePlotGUI_Shown);
			this->SurfacePlotContextMenu->ResumeLayout(false);
			this->ResumeLayout(false);

		}

#pragma endregion
		
		// -------------------- GUI Opstartnings Og Nedluknings Callback Routiner --------------------- //
		
		// Surface Plot Form Opstartnings Callback Routine -> 
		private: System::Void SurfacePlotGUI_Shown(System::Object^ sender, System::EventArgs^ e) {

			// Opdater tilhørende form Flag
			isSurfacePlotFormOpen = true;

		}

		// Surface Plot Form Nedluknings Callback Routine ->
		private: System::Void SurfacePlotGUI_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Opdater tilhørende form Flag
			isSurfacePlotFormOpen = false;
			isSurfacePlotFormDocked = false;
			isSurfacePlotFormUndocked = false;

			// Når Formen lukkes - Gem Formen
			this->Hide();
			// Deaktiver "Disposing" Af Form Objektet
			e->Cancel = true;

		}

		// ----------------------- Surface Plot Context Menu Callback Routiner ------------------------ //

		// Surface Plot polygon renderings mode callback routine ->
		private: System::Void pointModeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Indstil Surface Plot polygon renderings mode
			GlobalVariables::OpenGLSurfacePlot->RMH_OpenGL_SetSurfacePlotPolygonMode(sender);

		}

		// Surface Plot polygon mode Punkt størrelses callback routine ->
		private: System::Void toolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e) {

			// Indstil punkt størrelsen i tilhørende polygon mode
			GlobalVariables::OpenGLSurfacePlot->RMH_OpenGL_SetSurfacePlotPolygonModePointSize(sender);

		}

		// Surface Plot polygon mode Linje størrelses callback routine ->
		private: System::Void size1ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Indstil linje størrelsen i tilhørende polygon mode
			GlobalVariables::OpenGLSurfacePlot->RMH_OpenGL_SetSurfacePlotPolygonModeLineSize(sender);

		}

		// Reset surface plot view context menu callback routine ->
		private: System::Void resetToDefaultViewToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Nulstil surface plot view
			GlobalVariables::OpenGLSurfacePlot->RMH_OpenGL_ResetSurfacePlotView();

		}

		// Surface plot Snapshot context menu callback routine ->
		private: System::Void saveSnapshotToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

			// Gem et 3D surface Plot snapshot
			RMH_ThermalViewer_SaveSurfacePlotSnapshot();

		}

		// Surface Plot Z-Data Skala context menu callback routine ->
		private: System::Void ZDataScaleMenuItem2_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Surface plottets maksimale Z højde
			GlobalVariables::OpenGLSurfacePlot->RMH_OpenGL_UpdateSurfacePlotMaxZHeight(sender);

		}

		// -------------------------------------------------------------------------------------------- //

};
}
