#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"
#include "RMH_ImageProcessing_Library.h"
#include "RMH_Application_ThermalViewer.h"
#include "RMH_Application_SaveSession.h"
#include "RMH_MathConversions_Library.h"
#include "RMH_Winforms_Library.h"
#include <iostream>

// Inkluderede applikations Resourcer
#include "RMH_Application_Information.h"

// Inkluderede Form Headere
#include "LiveViewStream.h"
#include "WelcomeScreen.h"
#include "ThermalCameraGUI.h"
#include "SurfacePlotGUI.h"
#include "TempMeasGUI.h"
#include "EmissivityTableGUI.h"
#include "VideoPlayBackTools.h"
#include "PopUpDialog.h"
#include "UserGuideViewerGUI.h"

// Klasse Namespace
namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace std;

	// Summary for Form - MainGUI
	public ref class MainGUI : public System::Windows::Forms::Form {

	public:

		// ------------------------------ Lokale Form Reference Struktur ------------------------------ //

		// Lokale Reference struktur
		ref struct ManagedLocals {

			// Live View Stream Form statiske Objekter og variabler
			static IRCAMThermalViewer::LiveViewStream^ LiveViewStreamForm;

			// Welcome Screen Form statiske Objekter og variabler
			static IRCAMThermalViewer::WelcomeScreen^ WelcomeScreenForm;

			// User Guide Form statiske Objekter og variabler
			static IRCAMThermalViewer::UserGuideViewerGUI^ UserGuideViewerGUIForm;

			// Thermal Kamera Form statiske Objekter og variabler
			static IRCAMThermalViewer::ThermalCameraGUI^ ThermalCameraGUIForm;

			// Surface Plot Form statiske Objekter og variabler
			static IRCAMThermalViewer::SurfacePlotGUI^ SurfacePlotGUIForm;

			// Temperatur Målings Plot Form statiske Objekter og variabler
			static IRCAMThermalViewer::TempMeasGUI^ TempMeasurementsGUIForm;

			// Emissivity Tabel GUI Form statiske Objekter og variabler
			static IRCAMThermalViewer::EmissivityTableGUI^ EmissivityTableGUIForm;

			// Video Playback Tools GUI Form statiske Objekter og variabler
			static IRCAMThermalViewer::VideoPlayBackTools^ PlayBackControlsPanelForm;

		};

		// -------------------------------------------------------------------------------------------- //

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		MainGUI(void) {

			// Init GUI komponenter og objekter
			InitializeComponent();
			// Formater arrays af winform komponenter til global brug
			InitializeComponentArrays();
			// Indstil globale objekter fra denne Form til global brug
			InitializeGlobalFormsObjects();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Indstil gemt applikation configuration ved applikation start op
			RMH_Application_SetSavedSessionConfigToApplication(this->GUIInfoTextArea);

			// Initiliser Live View Screen Form
			ManagedLocals::LiveViewStreamForm = gcnew IRCAMThermalViewer::LiveViewStream();
			// Initiliser Welcome Screen Form
			ManagedLocals::WelcomeScreenForm = gcnew IRCAMThermalViewer::WelcomeScreen();
			// Initiliser User Guide GUI Form
			ManagedLocals::UserGuideViewerGUIForm = gcnew IRCAMThermalViewer::UserGuideViewerGUI();
			// Initiliser Thermal Camera GUI Form
			ManagedLocals::ThermalCameraGUIForm = gcnew IRCAMThermalViewer::ThermalCameraGUI();
			// Initiliser Surface Plot GUI Form
			ManagedLocals::SurfacePlotGUIForm = gcnew IRCAMThermalViewer::SurfacePlotGUI();
			// Initiliser Temperatur Målings Plot GUI Form
			ManagedLocals::TempMeasurementsGUIForm = gcnew IRCAMThermalViewer::TempMeasGUI();
			// Initiliser Emissivity Tabel GUI Form
			ManagedLocals::EmissivityTableGUIForm = gcnew IRCAMThermalViewer::EmissivityTableGUI();

			// Indstil de gemte sessions 2D Plot linje farve data
			RMH_ThermalViewer_Load2DPlotSavedSessionLineColorData();

			// Håndter Docking af Velkommens Formen ved start-op
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::WelcomeScreenForm, this->MainViewTopPanel, &isWelcomeScreenFormOpen, &isWelcomeScreenFormDocked, &isWelcomeScreenFormUndocked, _FormDockingState_DockForm);

			// Opdater formens Titelbar string
			RMH_Winforms_ChangeFormTitleBarText(this, ApplicationInformationString);

		}

		// ---------------------------- Diverse Specifikke Klasse Metoder ----------------------------- //

		void InitializeComponentArrays(void) {

			// Routinen formaterer arrays af winform komponenter til global brug

			// Array Af Main GUIens Menu Knapper
			GlobalVariables::MainGUILeftMenuButtons = gcnew cli::array<System::Windows::Forms::Button^>(8) {
				this->LiveViewMenuButton,
				this->SurfacePlotMenuButton,
				this->TempMeasMenuButton,
				this->EmissivityMenuButton,
				this->LiveViewUndockButton,
				this->SurfacePlotUndockButton,
				this->TempMeasUndockButton,
				this->EmissivityUndockButton
			};

		}

		void InitializeGlobalFormsObjects() {

			// Routinen indstiller globale objekter fra denne form
			// Så disse kan blve tilgået fra andre Forms

			// Initiliser Globale objeker til tilhørende Form Objekter
			GlobalVariables::GlobalGUIInfoTextArea = this->GUIInfoTextArea;
			GlobalVariables::GlobalVideoStreamThread = this->VideoStreamThread;
			GlobalVariables::GlobalMainGUIUpdateTimer = this->MainGUIUpdateTimer;
			GlobalVariables::GlobalTempMeasMenuButton = this->TempMeasMenuButton;
			GlobalVariables::GlobalSurfacePlotMenuButton = this->SurfacePlotMenuButton;
			GlobalVariables::GlobalSecondaryProcessingThread = this->SecondaryProcessingThread;

		}

		void HandleFormsOpeningDockingAndUndocking(System::Windows::Forms::Form^ FormObject, System::Windows::Forms::Panel^ ParentPanel, bool* FormOpenedFlag, bool* FormDockedFlag, bool* FormUndockedFlag, unsigned short FormState) {

			// Routinen håndterer Docking og Undocking af de forskellige Forms

			// Skal en Form Dockes til parent panelet
			if (FormState == _FormDockingState_DockForm) {

				// Kontroller stadiet for tidligere tilhørende Form objekt
				if (isThermalCameraFormOpen == true && isThermalCameraFormDocked == true && FormObject != ManagedLocals::ThermalCameraGUIForm) {

					// Fjern tilhørende Form som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

					// Luk tilhørende Form objekt
					RMH_Winforms_CloseForm(ManagedLocals::ThermalCameraGUIForm, &isThermalCameraFormOpen, &isThermalCameraFormDocked, &isThermalCameraFormUndocked);

				}
				if (isLiveViewStreamFormOpen == true && isLiveViewStreamFormDocked == true && FormObject != ManagedLocals::LiveViewStreamForm) {

					// Fjern tilhørende Form som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

					// Luk tilhørende Form objekt
					RMH_Winforms_CloseForm(ManagedLocals::LiveViewStreamForm, &isLiveViewStreamFormOpen, &isLiveViewStreamFormDocked, &isLiveViewStreamFormUndocked);

				}
				if (isSurfacePlotFormOpen == true && isSurfacePlotFormDocked == true && FormObject != ManagedLocals::SurfacePlotGUIForm) {

					// Fjern tilhørende Form som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

					// Luk tilhørende Form objekt
					RMH_Winforms_CloseForm(ManagedLocals::SurfacePlotGUIForm, &isSurfacePlotFormOpen, &isSurfacePlotFormDocked, &isSurfacePlotFormUndocked);

				}
				if (isTempMeasurementsFormOpen == true && isTempMeasurementsFormDocked == true && FormObject != ManagedLocals::TempMeasurementsGUIForm) {

					// Fjern tilhørende Form som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

					// Luk tilhørende Form objekt
					RMH_Winforms_CloseForm(ManagedLocals::TempMeasurementsGUIForm, &isTempMeasurementsFormOpen, &isTempMeasurementsFormDocked, &isTempMeasurementsFormUndocked);

				}
				if (isEmissivityTableFormOpen == true && isEmissivityTableFormDocked == true && FormObject != ManagedLocals::EmissivityTableGUIForm) {

					// Fjern tilhørende Form som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

					// Luk tilhørende Form objekt
					RMH_Winforms_CloseForm(ManagedLocals::EmissivityTableGUIForm, &isEmissivityTableFormOpen, &isEmissivityTableFormDocked, &isEmissivityTableFormUndocked);

				}
				if (isWelcomeScreenFormOpen == true && isWelcomeScreenFormDocked == true && FormObject != ManagedLocals::WelcomeScreenForm) {

					// Fjern tilhørende Form som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

					// Luk tilhørende Form objekt
					RMH_Winforms_CloseForm(ManagedLocals::WelcomeScreenForm, &isWelcomeScreenFormOpen, &isWelcomeScreenFormDocked, &isWelcomeScreenFormUndocked);

				}
				if (isUserGuideFormOpen == true && isUserGuideFormDocked == true && FormObject != ManagedLocals::UserGuideViewerGUIForm) {

					// Fjern tilhørende Form som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

					// Luk tilhørende Form objekt
					RMH_Winforms_CloseForm(ManagedLocals::UserGuideViewerGUIForm, &isUserGuideFormOpen, &isUserGuideFormDocked, &isUserGuideFormUndocked);

				}

			}

			// ---------------------------------------------------------------- Docking/Undocking Procedure ---------------------------------------------------------------- //

			// Skal en Form Dockes til parent panelet
			if (FormState == _FormDockingState_DockForm) {

				// Hvis Valgte Form allerede er åben
				if (*FormOpenedFlag == true) {

					// Luk valgte Formen før docking
					RMH_Winforms_CloseForm(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

				}

				// Åben og dock form i main GUIens Main Panel
				RMH_Winforms_OpenAndDockFormInParentPanel(FormObject, ParentPanel, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

			}

			// Skal en Form Undockes fra parent panelet
			if (FormState == _FormDockingState_UndockForm) {

				// Hvis Main View panelet er parent til valgte Form Objekt
				if (FormObject->Parent == ParentPanel) {

					// Nulstil Formens Parent 
					FormObject->Parent = nullptr;
					// Fjern Formen som en "Control" fra givet "Parent" Panel
					ParentPanel->Controls->Clear();

				}

				// Kontroller om formen er åben, med ikke docked
				if (*FormOpenedFlag == true && *FormDockedFlag == false) {

					// Luk Formen
					RMH_Winforms_CloseForm(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

					// Undock Formen og åben i seperat vindue
					RMH_Winforms_OpenFormInSeperateWindow(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

				}

				// Kontroller om formen er åben og docked
				if (*FormOpenedFlag == true && *FormDockedFlag == true) {

					// Luk Formen
					RMH_Winforms_CloseForm(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

					// Undock Formen fra Parent panelet og åben i seperat vindue
					RMH_Winforms_UndockFormFromParentPanel(FormObject, ParentPanel, FormOpenedFlag, FormDockedFlag, FormUndockedFlag, System::Windows::Forms::FormBorderStyle::Sizable);

				}

				// Kontroller om formen ikke er åben og ikke er docked
				if (*FormOpenedFlag == false && *FormDockedFlag == false) {

					// Undock Formen og åben i seperat vindue
					RMH_Winforms_OpenFormInSeperateWindow(FormObject, FormOpenedFlag, FormDockedFlag, FormUndockedFlag);

				}

			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------- //

			// Hvis ingen Forms er docket i Main GUIens View panel
			if (isThermalCameraFormDocked == false &&
				isLiveViewStreamFormDocked == false &&
				isSurfacePlotFormDocked == false &&
				isTempMeasurementsFormDocked == false &&
				isEmissivityTableFormDocked == false) {

				// Åben og dock Velkommen Skærm formen i main GUIens Main Panel
				RMH_Winforms_OpenAndDockFormInParentPanel(ManagedLocals::WelcomeScreenForm, ParentPanel, &isWelcomeScreenFormOpen, &isWelcomeScreenFormDocked, &isWelcomeScreenFormUndocked);

			}

		}

		// -------------------------------------------------------------------------------------------- //

		protected:

			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~MainGUI() {

				if (components) {

					// Slet alle Form Komponenter
					delete components;

				}

			}

		public:

			/// <summary>
			/// Required designer variable.
			/// </summary>
			private: System::ComponentModel::IContainer^ components;
			private: System::Windows::Forms::ColorDialog^ GlobalColorDialog;
			private: System::Windows::Forms::ToolTip^ GlobalInfoToolTip;
			private: System::Windows::Forms::Panel^ LeftGUIPanel;
			private: System::Windows::Forms::Button^ ThermalCAMMenuButton;
			private: System::Windows::Forms::Panel^ TopLeftGUIPanel;
			private: System::Windows::Forms::Button^ AboutMenuButton;
			private: System::Windows::Forms::Button^ EmissivityMenuButton;
			private: System::Windows::Forms::Button^ TempMeasMenuButton;
			private: System::Windows::Forms::Button^ SurfacePlotMenuButton;
			private: System::Windows::Forms::Button^ LiveViewMenuButton;
			private: System::Windows::Forms::Panel^ MainViewTopPanel;
			private: System::Windows::Forms::Timer^ MainGUIUpdateTimer;
			private: System::Windows::Forms::RichTextBox^ GUIInfoTextArea;
			private: System::Windows::Forms::Panel^ MainMenuButtonsPanel;
			private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
			private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
			private: System::Windows::Forms::Button^ ThermalCAMUndockButton;
			private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel6;
			private: System::Windows::Forms::Button^ EmissivityUndockButton;
			private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
			private: System::Windows::Forms::Button^ TempMeasUndockButton;
			private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
			private: System::Windows::Forms::Button^ SurfacePlotUndockButton;
			private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
			private: System::Windows::Forms::SplitContainer^ splitContainer1;
			private: System::Windows::Forms::Button^ UserGuideButton;
			private: System::ComponentModel::BackgroundWorker^ SecondaryProcessingThread;
			private: System::ComponentModel::BackgroundWorker^ VideoStreamThread;
			private: System::Windows::Forms::Button^ LiveViewUndockButton;

	#pragma region Windows Form Designer generated code

			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void) {
				this->components = (gcnew System::ComponentModel::Container());
				System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainGUI::typeid));
				this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
				this->MainViewTopPanel = (gcnew System::Windows::Forms::Panel());
				this->GUIInfoTextArea = (gcnew System::Windows::Forms::RichTextBox());
				this->VideoStreamThread = (gcnew System::ComponentModel::BackgroundWorker());
				this->GlobalColorDialog = (gcnew System::Windows::Forms::ColorDialog());
				this->GlobalInfoToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
				this->MainGUIUpdateTimer = (gcnew System::Windows::Forms::Timer(this->components));
				this->LeftGUIPanel = (gcnew System::Windows::Forms::Panel());
				this->UserGuideButton = (gcnew System::Windows::Forms::Button());
				this->AboutMenuButton = (gcnew System::Windows::Forms::Button());
				this->MainMenuButtonsPanel = (gcnew System::Windows::Forms::Panel());
				this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
				this->EmissivityUndockButton = (gcnew System::Windows::Forms::Button());
				this->EmissivityMenuButton = (gcnew System::Windows::Forms::Button());
				this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
				this->ThermalCAMUndockButton = (gcnew System::Windows::Forms::Button());
				this->ThermalCAMMenuButton = (gcnew System::Windows::Forms::Button());
				this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
				this->TempMeasUndockButton = (gcnew System::Windows::Forms::Button());
				this->TempMeasMenuButton = (gcnew System::Windows::Forms::Button());
				this->TopLeftGUIPanel = (gcnew System::Windows::Forms::Panel());
				this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
				this->SurfacePlotUndockButton = (gcnew System::Windows::Forms::Button());
				this->SurfacePlotMenuButton = (gcnew System::Windows::Forms::Button());
				this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
				this->LiveViewMenuButton = (gcnew System::Windows::Forms::Button());
				this->LiveViewUndockButton = (gcnew System::Windows::Forms::Button());
				this->SecondaryProcessingThread = (gcnew System::ComponentModel::BackgroundWorker());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
				this->splitContainer1->Panel1->SuspendLayout();
				this->splitContainer1->Panel2->SuspendLayout();
				this->splitContainer1->SuspendLayout();
				this->LeftGUIPanel->SuspendLayout();
				this->MainMenuButtonsPanel->SuspendLayout();
				this->tableLayoutPanel1->SuspendLayout();
				this->tableLayoutPanel6->SuspendLayout();
				this->tableLayoutPanel2->SuspendLayout();
				this->tableLayoutPanel5->SuspendLayout();
				this->tableLayoutPanel4->SuspendLayout();
				this->tableLayoutPanel3->SuspendLayout();
				this->SuspendLayout();
				// 
				// splitContainer1
				// 
				resources->ApplyResources(this->splitContainer1, L"splitContainer1");
				this->splitContainer1->Name = L"splitContainer1";
				// 
				// splitContainer1.Panel1
				// 
				this->splitContainer1->Panel1->Controls->Add(this->MainViewTopPanel);
				// 
				// splitContainer1.Panel2
				// 
				this->splitContainer1->Panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->splitContainer1->Panel2->Controls->Add(this->GUIInfoTextArea);
				resources->ApplyResources(this->splitContainer1->Panel2, L"splitContainer1.Panel2");
				// 
				// MainViewTopPanel
				// 
				this->MainViewTopPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				resources->ApplyResources(this->MainViewTopPanel, L"MainViewTopPanel");
				this->MainViewTopPanel->Name = L"MainViewTopPanel";
				// 
				// GUIInfoTextArea
				// 
				this->GUIInfoTextArea->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->GUIInfoTextArea->BorderStyle = System::Windows::Forms::BorderStyle::None;
				this->GUIInfoTextArea->DetectUrls = false;
				resources->ApplyResources(this->GUIInfoTextArea, L"GUIInfoTextArea");
				this->GUIInfoTextArea->ForeColor = System::Drawing::Color::White;
				this->GUIInfoTextArea->HideSelection = false;
				this->GUIInfoTextArea->Name = L"GUIInfoTextArea";
				// 
				// VideoStreamThread
				// 
				this->VideoStreamThread->WorkerReportsProgress = true;
				this->VideoStreamThread->WorkerSupportsCancellation = true;
				this->VideoStreamThread->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainGUI::VideoStreamThread_DoWork);
				// 
				// GlobalColorDialog
				// 
				this->GlobalColorDialog->FullOpen = true;
				// 
				// GlobalInfoToolTip
				// 
				this->GlobalInfoToolTip->AutomaticDelay = 1000;
				this->GlobalInfoToolTip->AutoPopDelay = 5000;
				this->GlobalInfoToolTip->InitialDelay = 500;
				this->GlobalInfoToolTip->ReshowDelay = 200;
				this->GlobalInfoToolTip->ToolTipTitle = L"Information:";
				this->GlobalInfoToolTip->UseAnimation = false;
				this->GlobalInfoToolTip->UseFading = false;
				// 
				// MainGUIUpdateTimer
				// 
				this->MainGUIUpdateTimer->Interval = 5;
				this->MainGUIUpdateTimer->Tick += gcnew System::EventHandler(this, &MainGUI::MainGUIUpdateTimer_Tick);
				// 
				// LeftGUIPanel
				// 
				this->LeftGUIPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
					static_cast<System::Int32>(static_cast<System::Byte>(32)));
				this->LeftGUIPanel->Controls->Add(this->UserGuideButton);
				this->LeftGUIPanel->Controls->Add(this->AboutMenuButton);
				this->LeftGUIPanel->Controls->Add(this->MainMenuButtonsPanel);
				resources->ApplyResources(this->LeftGUIPanel, L"LeftGUIPanel");
				this->LeftGUIPanel->Name = L"LeftGUIPanel";
				// 
				// UserGuideButton
				// 
				resources->ApplyResources(this->UserGuideButton, L"UserGuideButton");
				this->UserGuideButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->UserGuideButton->ForeColor = System::Drawing::Color::White;
				this->UserGuideButton->Name = L"UserGuideButton";
				this->UserGuideButton->UseVisualStyleBackColor = true;
				this->UserGuideButton->Click += gcnew System::EventHandler(this, &MainGUI::UserGuideButton_Click);
				// 
				// AboutMenuButton
				// 
				resources->ApplyResources(this->AboutMenuButton, L"AboutMenuButton");
				this->AboutMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->AboutMenuButton->ForeColor = System::Drawing::Color::White;
				this->AboutMenuButton->Name = L"AboutMenuButton";
				this->AboutMenuButton->UseVisualStyleBackColor = true;
				this->AboutMenuButton->Click += gcnew System::EventHandler(this, &MainGUI::AboutMenuButton_Click);
				// 
				// MainMenuButtonsPanel
				// 
				this->MainMenuButtonsPanel->Controls->Add(this->tableLayoutPanel1);
				resources->ApplyResources(this->MainMenuButtonsPanel, L"MainMenuButtonsPanel");
				this->MainMenuButtonsPanel->Name = L"MainMenuButtonsPanel";
				// 
				// tableLayoutPanel1
				// 
				resources->ApplyResources(this->tableLayoutPanel1, L"tableLayoutPanel1");
				this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel6, 0, 5);
				this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
				this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel5, 0, 4);
				this->tableLayoutPanel1->Controls->Add(this->TopLeftGUIPanel, 0, 0);
				this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 0, 3);
				this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 0, 2);
				this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
				// 
				// tableLayoutPanel6
				// 
				resources->ApplyResources(this->tableLayoutPanel6, L"tableLayoutPanel6");
				this->tableLayoutPanel6->Controls->Add(this->EmissivityUndockButton, 1, 0);
				this->tableLayoutPanel6->Controls->Add(this->EmissivityMenuButton, 0, 0);
				this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
				// 
				// EmissivityUndockButton
				// 
				resources->ApplyResources(this->EmissivityUndockButton, L"EmissivityUndockButton");
				this->EmissivityUndockButton->BackColor = System::Drawing::Color::Transparent;
				this->EmissivityUndockButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->EmissivityUndockButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->EmissivityUndockButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->EmissivityUndockButton->ForeColor = System::Drawing::Color::White;
				this->EmissivityUndockButton->Name = L"EmissivityUndockButton";
				this->EmissivityUndockButton->UseVisualStyleBackColor = false;
				this->EmissivityUndockButton->Click += gcnew System::EventHandler(this, &MainGUI::EmissivityUndockButton_Click);
				// 
				// EmissivityMenuButton
				// 
				resources->ApplyResources(this->EmissivityMenuButton, L"EmissivityMenuButton");
				this->EmissivityMenuButton->BackColor = System::Drawing::Color::Transparent;
				this->EmissivityMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->EmissivityMenuButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->EmissivityMenuButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->EmissivityMenuButton->ForeColor = System::Drawing::Color::White;
				this->EmissivityMenuButton->Name = L"EmissivityMenuButton";
				this->EmissivityMenuButton->UseVisualStyleBackColor = false;
				this->EmissivityMenuButton->Click += gcnew System::EventHandler(this, &MainGUI::EmissivityMenuButton_Click);
				// 
				// tableLayoutPanel2
				// 
				resources->ApplyResources(this->tableLayoutPanel2, L"tableLayoutPanel2");
				this->tableLayoutPanel2->Controls->Add(this->ThermalCAMUndockButton, 1, 0);
				this->tableLayoutPanel2->Controls->Add(this->ThermalCAMMenuButton, 0, 0);
				this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
				// 
				// ThermalCAMUndockButton
				// 
				resources->ApplyResources(this->ThermalCAMUndockButton, L"ThermalCAMUndockButton");
				this->ThermalCAMUndockButton->BackColor = System::Drawing::Color::Transparent;
				this->ThermalCAMUndockButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->ThermalCAMUndockButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->ThermalCAMUndockButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->ThermalCAMUndockButton->ForeColor = System::Drawing::Color::White;
				this->ThermalCAMUndockButton->Name = L"ThermalCAMUndockButton";
				this->ThermalCAMUndockButton->UseVisualStyleBackColor = false;
				this->ThermalCAMUndockButton->Click += gcnew System::EventHandler(this, &MainGUI::ThermalCAMUndockButton_Click);
				// 
				// ThermalCAMMenuButton
				// 
				resources->ApplyResources(this->ThermalCAMMenuButton, L"ThermalCAMMenuButton");
				this->ThermalCAMMenuButton->BackColor = System::Drawing::Color::Transparent;
				this->ThermalCAMMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->ThermalCAMMenuButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->ThermalCAMMenuButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->ThermalCAMMenuButton->ForeColor = System::Drawing::Color::White;
				this->ThermalCAMMenuButton->Name = L"ThermalCAMMenuButton";
				this->ThermalCAMMenuButton->UseVisualStyleBackColor = false;
				this->ThermalCAMMenuButton->Click += gcnew System::EventHandler(this, &MainGUI::ThermalCAMMenuButton_Click);
				// 
				// tableLayoutPanel5
				// 
				resources->ApplyResources(this->tableLayoutPanel5, L"tableLayoutPanel5");
				this->tableLayoutPanel5->Controls->Add(this->TempMeasUndockButton, 1, 0);
				this->tableLayoutPanel5->Controls->Add(this->TempMeasMenuButton, 0, 0);
				this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
				// 
				// TempMeasUndockButton
				// 
				resources->ApplyResources(this->TempMeasUndockButton, L"TempMeasUndockButton");
				this->TempMeasUndockButton->BackColor = System::Drawing::Color::Transparent;
				this->TempMeasUndockButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->TempMeasUndockButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->TempMeasUndockButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->TempMeasUndockButton->ForeColor = System::Drawing::Color::White;
				this->TempMeasUndockButton->Name = L"TempMeasUndockButton";
				this->TempMeasUndockButton->UseVisualStyleBackColor = false;
				this->TempMeasUndockButton->Click += gcnew System::EventHandler(this, &MainGUI::TempMeasUndockButton_Click);
				// 
				// TempMeasMenuButton
				// 
				resources->ApplyResources(this->TempMeasMenuButton, L"TempMeasMenuButton");
				this->TempMeasMenuButton->BackColor = System::Drawing::Color::Transparent;
				this->TempMeasMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->TempMeasMenuButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->TempMeasMenuButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->TempMeasMenuButton->ForeColor = System::Drawing::Color::White;
				this->TempMeasMenuButton->Name = L"TempMeasMenuButton";
				this->TempMeasMenuButton->UseVisualStyleBackColor = false;
				this->TempMeasMenuButton->Click += gcnew System::EventHandler(this, &MainGUI::TempMeasMenuButton_Click);
				// 
				// TopLeftGUIPanel
				// 
				this->TopLeftGUIPanel->BackColor = System::Drawing::Color::Transparent;
				resources->ApplyResources(this->TopLeftGUIPanel, L"TopLeftGUIPanel");
				this->TopLeftGUIPanel->Name = L"TopLeftGUIPanel";
				// 
				// tableLayoutPanel4
				// 
				resources->ApplyResources(this->tableLayoutPanel4, L"tableLayoutPanel4");
				this->tableLayoutPanel4->Controls->Add(this->SurfacePlotUndockButton, 1, 0);
				this->tableLayoutPanel4->Controls->Add(this->SurfacePlotMenuButton, 0, 0);
				this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
				// 
				// SurfacePlotUndockButton
				// 
				resources->ApplyResources(this->SurfacePlotUndockButton, L"SurfacePlotUndockButton");
				this->SurfacePlotUndockButton->BackColor = System::Drawing::Color::Transparent;
				this->SurfacePlotUndockButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->SurfacePlotUndockButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->SurfacePlotUndockButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->SurfacePlotUndockButton->ForeColor = System::Drawing::Color::White;
				this->SurfacePlotUndockButton->Name = L"SurfacePlotUndockButton";
				this->SurfacePlotUndockButton->UseVisualStyleBackColor = false;
				this->SurfacePlotUndockButton->Click += gcnew System::EventHandler(this, &MainGUI::SurfacePlotUndockButton_Click);
				// 
				// SurfacePlotMenuButton
				// 
				resources->ApplyResources(this->SurfacePlotMenuButton, L"SurfacePlotMenuButton");
				this->SurfacePlotMenuButton->BackColor = System::Drawing::Color::Transparent;
				this->SurfacePlotMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->SurfacePlotMenuButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->SurfacePlotMenuButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->SurfacePlotMenuButton->ForeColor = System::Drawing::Color::White;
				this->SurfacePlotMenuButton->Name = L"SurfacePlotMenuButton";
				this->SurfacePlotMenuButton->UseVisualStyleBackColor = false;
				this->SurfacePlotMenuButton->Click += gcnew System::EventHandler(this, &MainGUI::SurfacePlotMenuButton_Click);
				// 
				// tableLayoutPanel3
				// 
				resources->ApplyResources(this->tableLayoutPanel3, L"tableLayoutPanel3");
				this->tableLayoutPanel3->Controls->Add(this->LiveViewMenuButton, 0, 0);
				this->tableLayoutPanel3->Controls->Add(this->LiveViewUndockButton, 1, 0);
				this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
				// 
				// LiveViewMenuButton
				// 
				resources->ApplyResources(this->LiveViewMenuButton, L"LiveViewMenuButton");
				this->LiveViewMenuButton->BackColor = System::Drawing::Color::Transparent;
				this->LiveViewMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->LiveViewMenuButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->LiveViewMenuButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->LiveViewMenuButton->ForeColor = System::Drawing::Color::White;
				this->LiveViewMenuButton->Name = L"LiveViewMenuButton";
				this->LiveViewMenuButton->UseVisualStyleBackColor = false;
				this->LiveViewMenuButton->Click += gcnew System::EventHandler(this, &MainGUI::LiveViewMenuButton_Click);
				// 
				// LiveViewUndockButton
				// 
				resources->ApplyResources(this->LiveViewUndockButton, L"LiveViewUndockButton");
				this->LiveViewUndockButton->BackColor = System::Drawing::Color::Transparent;
				this->LiveViewUndockButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->LiveViewUndockButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)),
					static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
				this->LiveViewUndockButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
					static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)));
				this->LiveViewUndockButton->ForeColor = System::Drawing::Color::White;
				this->LiveViewUndockButton->Name = L"LiveViewUndockButton";
				this->LiveViewUndockButton->UseVisualStyleBackColor = false;
				this->LiveViewUndockButton->Click += gcnew System::EventHandler(this, &MainGUI::LiveViewUndockButton_Click);
				// 
				// SecondaryProcessingThread
				// 
				this->SecondaryProcessingThread->WorkerReportsProgress = true;
				this->SecondaryProcessingThread->WorkerSupportsCancellation = true;
				this->SecondaryProcessingThread->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainGUI::SecondaryProcessingThread_DoWork);
				// 
				// MainGUI
				// 
				resources->ApplyResources(this, L"$this");
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
				this->BackColor = System::Drawing::Color::Black;
				this->Controls->Add(this->splitContainer1);
				this->Controls->Add(this->LeftGUIPanel);
				this->KeyPreview = true;
				this->Name = L"MainGUI";
				this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
				this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainGUI::MainGUI_FormClosing);
				this->Shown += gcnew System::EventHandler(this, &MainGUI::MainGUI_Shown);
				this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainGUI::MainGUI_KeyPress);
				this->splitContainer1->Panel1->ResumeLayout(false);
				this->splitContainer1->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
				this->splitContainer1->ResumeLayout(false);
				this->LeftGUIPanel->ResumeLayout(false);
				this->MainMenuButtonsPanel->ResumeLayout(false);
				this->tableLayoutPanel1->ResumeLayout(false);
				this->tableLayoutPanel6->ResumeLayout(false);
				this->tableLayoutPanel2->ResumeLayout(false);
				this->tableLayoutPanel5->ResumeLayout(false);
				this->tableLayoutPanel4->ResumeLayout(false);
				this->tableLayoutPanel3->ResumeLayout(false);
				this->ResumeLayout(false);

			}

	#pragma endregion

		// ------------------ Main GUI Opstartnings Og Nedluknings Callback Routiner ------------------ //

		// Main GUI Opstartnings Callback Routine -> 
		private: System::Void MainGUI_Shown(System::Object^ sender, System::EventArgs^ e) {

			// Routinen er Applikation GUIens Start op funktion
			// Som tager relavante GUI komponenter som input argument

			// Skriv GUI Start Meddelse
			RMH_Winforms_RichTextBox_WriteLine(this->GUIInfoTextArea, "Sellect A Thermal Camera Or Mode, In The Settings Menu, & Press The 'Connect' or 'Open File' Button.", _StatusMessageType_Normal);

		}

		// Main GUI Nedluknings Callback Routine ->
		private: System::Void MainGUI_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Routinen er Applikation GUIens Nedluknings routine

			// Opdater Thermal Camera Form Sessions parametere til globale variabler
			ManagedLocals::ThermalCameraGUIForm->SaveFormSessionSettings();

			// Gem de nuværende applikations sessions parameter til næste session
			RMH_Application_SaveLastSessionConfigToFile();

		}

		// -------------------- Main GUI Tastatur Key-Press Event Callback Routine -------------------- //
		
		// Main GUI Key-Press Event Callback Routine ->
		private: System::Void MainGUI_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {

			// Kontroller om live view streamen, 3D surface Plottet eller Temp Plottet er i visning
			if (isLiveViewStreamFormOpen == true || isTempMeasurementsFormOpen == true  || isSurfacePlotFormOpen == true ) {

				// Håndter live view funktions knappernes HotKeys 
				ManagedLocals::LiveViewStreamForm->HandleLiveViewButtonsHotKeyFunctions(e);

			}

		}

		// --------------------------- GUI Menu/Sub-Menu Callback Routiner ---------------------------- //

		// Thermal Camera Menu Knap Callback ->
		private: System::Void ThermalCAMMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Docking af Form GUIen i Main GUIens Main View Panel
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::ThermalCameraGUIForm, this->MainViewTopPanel, &isThermalCameraFormOpen, &isThermalCameraFormDocked, &isThermalCameraFormUndocked, _FormDockingState_DockForm);

		}

		// Thermal Camera Undock Knap Callback ->
		private: System::Void ThermalCAMUndockButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Undocking af Form GUIen
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::ThermalCameraGUIForm, this->MainViewTopPanel, &isThermalCameraFormOpen, &isThermalCameraFormDocked, &isThermalCameraFormUndocked, _FormDockingState_UndockForm);

		}

	    // Live View Menu Knap Callback ->
		private: System::Void LiveViewMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Docking af Form GUIen i Main GUIens Main View Panel
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::LiveViewStreamForm, this->MainViewTopPanel, &isLiveViewStreamFormOpen, &isLiveViewStreamFormDocked, &isLiveViewStreamFormUndocked, _FormDockingState_DockForm);

			// Garbage Collect Applikationen
			GC::Collect();

		}

		// Live View Undock Knap Callback ->
		private: System::Void LiveViewUndockButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Undocking af Form GUIen
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::LiveViewStreamForm, this->MainViewTopPanel, &isLiveViewStreamFormOpen, &isLiveViewStreamFormDocked, &isLiveViewStreamFormUndocked, _FormDockingState_UndockForm);
			
			// Garbage Collect Applikationen
			GC::Collect();

		}

	    // Surface Plot Menu Knap Callback ->
		private: System::Void SurfacePlotMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Docking af Form GUIen i Main GUIens Main View Panel
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::SurfacePlotGUIForm, this->MainViewTopPanel, &isSurfacePlotFormOpen, &isSurfacePlotFormDocked, &isSurfacePlotFormUndocked, _FormDockingState_DockForm);

			// Garbage Collect Applikationen
			GC::Collect();

		}

		// Surface Plot Undock Knap Callback ->
		private: System::Void SurfacePlotUndockButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Undocking af Form GUIen
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::SurfacePlotGUIForm, this->MainViewTopPanel, &isSurfacePlotFormOpen, &isSurfacePlotFormDocked, &isSurfacePlotFormUndocked, _FormDockingState_UndockForm);

			// Garbage Collect Applikationen
			GC::Collect();

		}

	    // Temperature Measurements Menu Knap Callback ->
		private: System::Void TempMeasMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Docking af Form GUIen i Main GUIens Main View Panel
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::TempMeasurementsGUIForm, this->MainViewTopPanel, &isTempMeasurementsFormOpen, &isTempMeasurementsFormDocked, &isTempMeasurementsFormUndocked, _FormDockingState_DockForm);
			
		}

		// Temperature Measurements Undock Knap Callback ->
		private: System::Void TempMeasUndockButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Undocking af Form GUIen
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::TempMeasurementsGUIForm, this->MainViewTopPanel, &isTempMeasurementsFormOpen, &isTempMeasurementsFormDocked, &isTempMeasurementsFormUndocked, _FormDockingState_UndockForm);

		}

		// Emissivity Tabel Menu Knap Callback ->
		private: System::Void EmissivityMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Docking af Form GUIen i Main GUIens Main View Panel
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::EmissivityTableGUIForm, this->MainViewTopPanel, &isEmissivityTableFormOpen, &isEmissivityTableFormDocked, &isEmissivityTableFormUndocked, _FormDockingState_DockForm);

		}

		// Emissivity Tabel Undock Knap Callback ->
		private: System::Void EmissivityUndockButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Undocking af Form GUIen
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::EmissivityTableGUIForm, this->MainViewTopPanel, &isEmissivityTableFormOpen, &isEmissivityTableFormDocked, &isEmissivityTableFormUndocked, _FormDockingState_UndockForm);

		}

		// About Informations Menu knap Callback ->
		private: System::Void AboutMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Docking af Form GUIen i Main GUIens Main View Panel
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::WelcomeScreenForm, this->MainViewTopPanel, &isWelcomeScreenFormOpen, &isWelcomeScreenFormDocked, &isWelcomeScreenFormUndocked, _FormDockingState_DockForm);

		}

		// User Guide Menu knap Callback ->
		private: System::Void UserGuideButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter Docking af Form GUIen i Main GUIens Main View Panel
			HandleFormsOpeningDockingAndUndocking(ManagedLocals::UserGuideViewerGUIForm, this->MainViewTopPanel, &isUserGuideFormOpen, &isUserGuideFormDocked, &isUserGuideFormUndocked, _FormDockingState_DockForm);

		}

		// --------------------------- Video Stream Thread Callback Routiner -------------------------- //
			   
		// Video Stream Process Thread Callback Routine ->
		private: System::Void VideoStreamThread_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
					
			// Primære Thread Process
			while (IRCamera.ConnectedFlag) {

				// Kontroller Thread Data ready flag
				if (ThreadDataReadyFlag == false) {

					// Eksikver Termisk kamera Billede Processerings Sekvens 
					RMH_ThermalViewer_ImageProcessingSequence();

					// Opdater Thread Data klar flag
					ThreadDataReadyFlag = true;

				}

				// Kontroller om kameraet er blevet frakoblet
				if (IRCamera.ConnectedFlag == false) {

					// Skriv GUI Start Meddelse i terminal
					cout << "Video Processing Thread Stopped\n" << endl;

					// Bryd Thread Loop
					break;

				}

				// Begræns CPU brug og lad thread vente
				System::Threading::Thread::Sleep(1);

			}
			
		}

		// Sekundær Processerings Thread Callback Routine ->
		private: System::Void SecondaryProcessingThread_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

			// Primære Thread Process
			while (IRCamera.ConnectedFlag) {

				// Håndtering Af sekundær processerings thread
				RMH_ThermalViewer_SecondaryProcessingSequence();

				// Kontroller om kameraet er blevet frakoblet
				if (IRCamera.ConnectedFlag == false) {

					// Skriv GUI Start Meddelse i terminal
					cout << "Secondary Processing Thread Stopped\n" << endl;

					// Bryd Thread Loop
					break;

				}

				// Begræns CPU brug og lad thread vente
				System::Threading::Thread::Sleep(1);

			}

		}

		// Main GUI Update Timer Callback ->
		private: System::Void MainGUIUpdateTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

			// Routinen er en timer callback som benyttes til at opdaterer GUI elementer

			// Er processerede data fra thread klar
			if (ThreadDataReadyFlag == true) {

				// Er Live View Form GUIen åben
				if (isLiveViewStreamFormOpen == true) {

					// Opdater Live View Stream Menuen
					RMH_ThermalViewer_UpdateLiveView(GlobalVariables::GlobalLiveViewStreamPanel->Width,
						GlobalVariables::GlobalLiveViewStreamPanel->Height, FixedLiveViewAspectRatio,
						GlobalVariables::GlobalColorBarMainPanel->Width,
						GlobalVariables::GlobalColorBarMainPanel->Height,
						GlobalVariables::GlobalLiveViewHistogramPanel->Width,
						GlobalVariables::GlobalLiveViewHistogramPanel->Height);

				}

				// Er video optagning blevet startede
				if (VideoRecordingStartedFlag == true) {

					// Håndter skrivning af relatanv data til video filer, hvis video optagning er startede
					RMH_ThermalViewer_WriteDataToVideoRecordingFilesSequence();

				}

				// Skal Surface Plot Form GUIen vises i tilhørende panel
				if (isSurfacePlotFormOpen == true) {

					// Opdater Surface Plot Formen
					RMH_ThermalViewer_UpdateSurfacePlotMenuScreen(ManagedLocals::SurfacePlotGUIForm->SurfacePlotPanel->Width,
						ManagedLocals::SurfacePlotGUIForm->SurfacePlotPanel->Height);

				}

				// Skal 2D Plot Form GUIen vises i tilhørende panel
				if (isTempMeasurementsFormOpen == true) {

					// Opdater 2D Plot Formen
					RMH_ThermalViewer_Update2DPlotMenuScreen(ManagedLocals::TempMeasurementsGUIForm->Temp2DPlotPanel->Width, 
						ManagedLocals::TempMeasurementsGUIForm->Temp2DPlotPanel->Height);

				}

				// Opdater kun temperature alarmernes status labels, hvis menuen er i visning og hvis kamera config formen er i visning
				if (TempAlarmsConfigMenuIsOpen == true && isThermalCameraFormOpen == true) {

					// Opdater aktive temperatur Alarmers status labels i Sub Menu
					RMH_ThermalViewer_UpdateTemperatureAlarmsSubMenuStatusLabels();

				}

				// Opdater Live View Statistik Vinduets Data Label - Hvis vinduet er åbent
				RMH_ThermalViewer_UpdateAndFormatLiveViewStatisticsLabels();

				// Nulstil Thread Data klar flag
				ThreadDataReadyFlag = false;

			}

			// --------------------- Åben, Dock og Luk Form GUIer Håndtering ---------------------- //

			// Hvis Live View Tools Panelet er blevet lukket
			if (isLiveViewToolsFormOpen == false) {

				// Dock tools formen tilbage i live view formen
				ManagedLocals::LiveViewStreamForm->DockLiveViewToolsFormInLiveViewToolsPanel();

			}

			// Skal video playback controls formen åbnes og er formen allerede lukket
			if (OpenVideoPlayBackControlsFormFlag == true && VideoPlaybackControlsFormIsOpenFlag == false) {

				// Alloker Video Playback Controls Kontrol Formen til hukommelsen
				ManagedLocals::PlayBackControlsPanelForm = gcnew IRCAMThermalViewer::VideoPlayBackTools();

				// Åben/Vis Video Playback Controls Kontrol Formen 
				ManagedLocals::PlayBackControlsPanelForm->Show();

				// Nulstil "Åben video playback" form flaget
				OpenVideoPlayBackControlsFormFlag = false;

			}

			// Skal video playback controls formen lukkes og er formen allerede åben
			if (CloseVideoPlayBackControlsFormFlag == true && VideoPlaybackControlsFormIsOpenFlag == true) {

				// Åben/Vis Video Playback Controls Kontrol Formen 
				ManagedLocals::PlayBackControlsPanelForm->Close();

				// Nulstil "Luk video playback" form flaget
				CloseVideoPlayBackControlsFormFlag = false;

			}

			// ----------------- Håndtering Af USB Forbindelses Tab Til Kameraet ------------------ //

			// Håndter Events ved tab af forbindelsen til kameraet
			RMH_ThermalViewer_HandleCameraDisconnectedEvents(true);

			// Var Kameraets USB forbindelsen tabt
			if (IRCamera.ConnectedFlag == false) {

				// Deaktiver Main GUIens Menu Knapper
				RMH_Application_DisableMainGUIMenuButtons();

				// Håndter Docking af Form GUIen i Main GUIens Main View Panel
				HandleFormsOpeningDockingAndUndocking(ManagedLocals::ThermalCameraGUIForm, this->MainViewTopPanel, &isThermalCameraFormOpen, &isThermalCameraFormDocked, &isThermalCameraFormUndocked, _FormDockingState_DockForm);

			}

			// ------------------------------------------------------------------------------------ //

		}

	    // -------------------------------------------------------------------------------------------- //

};
}
