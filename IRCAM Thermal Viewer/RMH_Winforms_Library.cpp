/*
 *  RMH_Winforms_Library.c
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

// Inkluderede Blblioteker
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <wincodec.h>
#include <msclr/marshal_cppstd.h>
#include "RMH_Winforms_Library.h"
#include "RMH_MathConversions_Library.h"
#include "SplashScreen.h"
#include "MainGUI.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

// Globale Variabler og objekter
double MaxExecutionTime = 0.0;
double MinExecutionTime = 1000.0;
unsigned int RichTextBoxNumberOfLines = 0;

// Globale namespaces
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace IRCAMThermalViewer;
using namespace std;
using namespace Microsoft::Win32;

// ------------------------- Winform Titlebar Håndterings Routiner -------------------------- //

void RMH_Winforms_EnableTitleBarDarkMode(System::IntPtr FormHandle) {

	// Routinen Aktiverer Winforms Applikationens TitelBars Dark Mode

	// Lokale Varaibler
	BOOL UseDark = TRUE;
	const int DWMWA_USE_IMMERSIVE_DARK_MODE = 20;

	// Aktiverer Winforms Applikationens TitelBars Dark Mode
	DwmSetWindowAttribute(static_cast<HWND>(FormHandle.ToPointer()), DWMWA_USE_IMMERSIVE_DARK_MODE, &UseDark, sizeof(UseDark));

}

// ----------------------------- Winform Benchmarkings Routiner ----------------------------- //

System::Diagnostics::Stopwatch^ RMH_Winforms_StartBenchMarkTimer() {

	// Routinen Starter en intern timer til code benchmarking

	/*
	 *  Eksempel ->
	 *  
	 *   // Start Benchmark Timer
	 *   System::Diagnostics::Stopwatch^ BenchMarkTimer = RMH_Winforms_StartBenchMarkTimer();
	 * 
	 *   // ----- Benchmark Kode Her ----- //
	 * 
	 *   // Stop Timer og display Benchmark Tid
	 *   RMH_Winforms_StopBenchmarkTimerAndDisplay(BenchMarkTimer);
	 * 
	 */

	// Lokale objekter og variabler
	System::Diagnostics::Stopwatch^ BenchmarkTimer;

	// Start intern timer til code benchmarking
	BenchmarkTimer = Stopwatch::StartNew();

	// Retuner Timer Objekt
	return BenchmarkTimer;

}

void RMH_Winforms_StopBenchmarkTimerAndDisplay(System::Diagnostics::Stopwatch^ BenchmarkTimer) {

	// Routinen stopper interne Benchmark Timer, udregner og viser 
	// Kode eksikverings tiden [i sekundter], i Output Vindue, siden timeren blev startet

	// Stil Benchmark Timer
	BenchmarkTimer->Stop();

	// Udregn eksikverings Benchmark tiderne
	double TimerFrequency = double(BenchmarkTimer->Frequency);
	double ElapsedTicks = double(BenchmarkTimer->ElapsedTicks);
	double ExecutionTime = ElapsedTicks * (1.0 / TimerFrequency);

	// Kontroller maksimale eksikverings tid
	if (ExecutionTime > MaxExecutionTime) {
		// Lager maksimale eksikverings tid
		MaxExecutionTime = ExecutionTime;
	}

	// Kontroller minimale eksikverings tid
	if (ExecutionTime < MinExecutionTime) {
		// Lager minimale eksikverings tid
		MinExecutionTime = ExecutionTime;
	}

	// Display Benchmark tid i Output Vindue
	cout << "Elapsed Time [Sec]:" << ExecutionTime << endl;
	cout << "Max Execution Time [Sec]:" << MaxExecutionTime << endl;
	cout << "Min Execution Time [Sec]:" << MinExecutionTime << endl;

	// Reset Benchmark Timer 
	BenchmarkTimer->Reset();

}

// ---------------------------- Winform GUI Håndterings Routiner ---------------------------- //

void RMH_Winforms_StartMainApplicationGUI() {

	// Routinen Konfigurerer Applikations parameter og starter winform GUI

	// Aktiver Applikationens Visual stil render
	Application::EnableVisualStyles();
	// Applicationen Benytter den globale deafult Text render 
	Application::SetCompatibleTextRenderingDefault(false);

	// Vis Start Splash Screen
	Application::Run(gcnew SplashScreen());
	// Start Main GUI applikation
	Application::Run(gcnew MainGUI());

}

void RMH_Winforms_ChangeFormTitleBarText(System::Windows::Forms::Form^ Winform, std::string Text) {

	// Routinen opdaterer texten i toppen af Winform GUIen

	// Opdater texten i toppen af Winform GUIen
	Winform->Text = RMH_Conversion_StdStringToSystemString(Text);

}

// --------------------- Winform Eksterne Processer Håndterings Routiner -------------------- //

void RMH_Winforms_OpenLinkURL(System::String^ LinkURL) {

	// Routinen starter en process som åbner et givet link URL

	// Håndtering for ikke supporterede windows versionen (Fx Windows 10 S)
	try {

		// Navigate Til givet URL addresse
		System::Diagnostics::Process::Start(LinkURL);

	}
	catch (System::Exception^ Ex) {}

}

bool RMH_Winforms_OpenWindowsMicrosoftStoreApp(System::String^ PackageFamilyName) {

	// Routinen åbner en valgt ekstern Microsoft Store Applikation i en ny process
	// Relavant Information -> https://www.auslogics.com/en/articles/how-to-open-microsoft-store-apps-from-command-prompt/

	// Lokale variabler og objekter
	bool AppProcessErrorFlag = false;
	System::Diagnostics::Process^ AppProcess = gcnew System::Diagnostics::Process();

	// Håndtering af fejl ved åbning af App process
	try {

		// Skriv eksikverings kommando til Shell terminal
		AppProcess->StartInfo->FileName = "CMD.exe";
		// Eksikver "Åben MS Store App" Shell Terminal string kommando
		AppProcess->StartInfo->Arguments = "/c explorer.exe shell:AppsFolder\\" + PackageFamilyName + "!App";
		// Åben ikke for Shell terminal vinduet
		AppProcess->StartInfo->WindowStyle = System::Diagnostics::ProcessWindowStyle::Hidden;

		// Eksikver Kommando
		AppProcess->Start();

		// Bring Applikations process vinduet til fronten af skærmen
		BringWindowToTop(static_cast<HWND>(AppProcess->MainWindowHandle.ToPointer()));

	}
	catch (System::Exception^ Ex) { AppProcessErrorFlag = true; }

	// Retuner Process status
	return AppProcessErrorFlag;

}

void RMH_Winforms_OpenExternalApplicationEXE(System::String^ ExternalEXENameString) {

	// Routinen starter en ekstern process til åbning af en ekstern .exe executabel

	// Hent primære applikationens aktuelle mappe og .exe sti
	String^ ExePath = Process::GetCurrentProcess()->MainModule->FileName;
	String^ Directory = System::IO::Path::GetDirectoryName(ExePath);

	// Formater Stien til applikationens .exe fil
	String^ targetExePath = System::IO::Path::Combine(Directory, ExternalEXENameString);

	// Error Håndtering
	try {

		// Start Applikations Processen
		Process::Start(targetExePath);

	}
	catch (Exception^ ex) {

		// Display Statuss Meddelses Box
		MessageBox::Show("External Executable Not Found!");

	}

}

// ------------ Winform Windows Skærm Width/Height/Scaling/DPI Læsnings Routiner ------------ //

WINMonitorSettings RMH_Winforms_ReadWindowsScreenSettings() {

	// Routinen læser Skærm bredden og højden i pixels, samt Skalaen og DPI indstillings værdierne
	// De retunerede værdier for er skærmen hvor applikationen er placeret.

	// Lokale objekter og Variabler
	DEVMODE DevMode;
	MONITORINFOEX MonitorInfoEx;
	WINMonitorSettings CurrentMonitorSettings;
	HWND activeWindow = GetActiveWindow();
	HMONITOR Monitor = MonitorFromWindow(activeWindow, MONITOR_DEFAULTTONEAREST);

	// Nulstil antallet af aktive Monitorer
	CurrentMonitorSettings.NumberOfConnectedMonitors = 0;

	// Loop igennem antallet af aktive skærme
	for (unsigned int i = 0; i < System::Windows::Forms::Screen::AllScreens->Length; i++) {

		// Inkrementer antal aktive monitorer i windows
		CurrentMonitorSettings.NumberOfConnectedMonitors = CurrentMonitorSettings.NumberOfConnectedMonitors + 1;

	}

	// Læs den Visuelle bredde og højde af nuværende Monitor
	MonitorInfoEx.cbSize = sizeof(MonitorInfoEx);
	GetMonitorInfo(Monitor, &MonitorInfoEx);
	CurrentMonitorSettings.MonitorVirtualWidth = (unsigned short)(MonitorInfoEx.rcMonitor.right - MonitorInfoEx.rcMonitor.left);
	CurrentMonitorSettings.MonitorVirtualHeight = (unsigned short)(MonitorInfoEx.rcMonitor.bottom - MonitorInfoEx.rcMonitor.top);

	// Læs den Fysiske bredde og højde af nuværende Monitor
	DevMode.dmSize = sizeof(DevMode);
	DevMode.dmDriverExtra = 0;
	EnumDisplaySettings(MonitorInfoEx.szDevice, ENUM_CURRENT_SETTINGS, &DevMode);
	CurrentMonitorSettings.MonitorPhysicalWidth = (unsigned short)DevMode.dmPelsWidth;
	CurrentMonitorSettings.MonitorPhysicalHeight = (unsigned short)DevMode.dmPelsHeight;

	// Udregn monitorens skallerings faktor
	CurrentMonitorSettings.MonitorHorizontalScaleSetting = (unsigned short)(((float)CurrentMonitorSettings.MonitorPhysicalWidth / (float)CurrentMonitorSettings.MonitorVirtualWidth) * 100.0);
	CurrentMonitorSettings.MonitorVerticalScaleSetting = (unsigned short)(((float)CurrentMonitorSettings.MonitorPhysicalHeight / (float)CurrentMonitorSettings.MonitorVirtualHeight) * 100.0);

	// Læs tilsvarende Monitor DPI indstilling Fra Skallerings indstilling
	switch (CurrentMonitorSettings.MonitorHorizontalScaleSetting) {

		// Læs Monitorens DPI indstilling
		case 100: CurrentMonitorSettings.MonitorDPISetting = 96;  break; // DPI 96  -> 100 % Skala
		case 125: CurrentMonitorSettings.MonitorDPISetting = 120; break; // DPI 120 -> 125 % Skala
		case 150: CurrentMonitorSettings.MonitorDPISetting = 144; break; // DPI 144 -> 150 % Skala
		case 175: CurrentMonitorSettings.MonitorDPISetting = 168; break; // DPI 168 -> 175 % Skala

	}

	// Retuner Windows Skærm indstillings Parameter struktur
	return CurrentMonitorSettings;

}

// -------------------------- Winform ComboBox Håndterings Routiner ------------------------- //

void RMH_Winforms_CombiBox_AddArrayOfItemStrings(System::Windows::Forms::ComboBox^ CombiBox, std::vector<std::string> StringArray) {

	// Routinen tilføjer et array af std::string til Items i valgte ComboBox

	// Lokale objekter
	cli::array<System::Object^>^ ItemObjects = gcnew cli::array<System::Object^ >(StringArray.size());

    // Loop til og med størrelsen af Input arrayet
	for (int i = 0; i < StringArray.size(); i++) {

		// Tilføj Objekters string navne til item objekt array
		ItemObjects[i] = RMH_Conversion_StdStringToSystemString(StringArray[i]);

	}

	// Tilføj objekt array til ComboBox Liste
	CombiBox->Items->AddRange(ItemObjects);

}

void RMH_Winforms_CombiBox_SetSellectedItemPosition(System::Windows::Forms::ComboBox^ CombiBox, unsigned char ItemIndex) {

	// Routinen sætter CombiBoxen til valgte item position

	// Sæt ComboBox position til Item Index
	CombiBox->SelectedIndex = ItemIndex;

}

// ----------------------- Winform NumericUpDown Håndterings Routiner ----------------------- //

bool RMH_Winforms_NumericUpDown_ChangeNumber(System::Windows::Forms::NumericUpDown^ NumericUpDown, float InputNumber, float ScaleFactor, float Offset, float DefaultValue) {

	// Routinen Sætter det givet "InputNumber" til numericUpDown control
	// Input argumenterne "ScaleFactor" og "Offset" er givet til valgfri Konvertering af "Number" 
	// "DefaultValue" er givet som den default værdi ved overflow. (Skal være indenfor maximum/Minimum værdien af NumericUpDown Komponent)
	// Routinen retunerer "True" hvis værdien var indenfor rækkevidden og ->
	// "False" hvis den var uden for rækkevidden og at default værdien er blevet brugt i stedet for.

	// Lokale Variabler
	bool ReturnStatus = false;
	float CalculatedValue = InputNumber * ScaleFactor + Offset;
	float CalculatedDefault = DefaultValue * ScaleFactor + Offset;

	// Kontroller om den udregnede værdi er indenform rækkevidden af et "System::Decimal"
	// og at værdien er indenfor værdien af den numeriske UpDowns maximum og minimum værdi.
	if (CalculatedValue >= (float)Decimal::MinValue && CalculatedValue <= (float)Decimal::MaxValue && 
		CalculatedValue >= (float)NumericUpDown->Minimum && CalculatedValue <= (float)NumericUpDown->Maximum) {

		// Konverter og display givet nummer i NumericUpDown Komponent
		NumericUpDown->Value = System::Convert::ToDecimal(CalculatedValue);

		// Opdater status
		ReturnStatus = true;

	}
	else {

		// Værdien er uden for rækkevidden - skriv Default værdi til NumericUpDown
		NumericUpDown->Value = System::Convert::ToDecimal(CalculatedDefault);

	}

	// Retuner Status
	return ReturnStatus;

}

// ------------------------ Winform RichTextBox Håndterings Routiner ------------------------ //

void RMH_Winforms_RichTextBox_WriteLine(System::Windows::Forms::RichTextBox^ RichTextBox, std::string Text, unsigned int MessageType) {

	// Routinen skriver en givet string til tekst box (RichTextBox) 

	/*
	 *  Tilhørende Macroer ->
	 *
	 *  // Status Meddelses typer macroer
	 *  #define _StatusMessageType_Normal      1
	 *  #define _StatusMessageType_Success     2
	 *  #define _StatusMessageType_Warning     3
	 *  #define _StatusMessageType_Error       4
	 * 
	 */


	// Ændre text farven afhængigt af meddelses typen
	switch (MessageType) {

		// Meddelsen er en Normal status meddelse
		case _StatusMessageType_Normal:

			// Indstil meddelses farven
			RichTextBox->SelectionColor = System::Drawing::Color::White;

		break;

		// Meddelsen er en Success status meddelse
		case _StatusMessageType_Success:

			// Indstil meddelses farven
			RichTextBox->SelectionColor = System::Drawing::Color::Lime;

		break;

		// Meddelsen er en Warning status meddelse
		case _StatusMessageType_Warning:

			// Indstil meddelses farven
			RichTextBox->SelectionColor = System::Drawing::Color::Yellow;

		break;

		// Meddelsen er en Error status meddelse
		case _StatusMessageType_Error:

			// Indstil meddelses farven
			RichTextBox->SelectionColor = System::Drawing::Color::Red;

		break;

	}

	// Kontroller om text boxen er tox for text
	if (String::IsNullOrEmpty(RichTextBox->Text)) {
		
		// Nulstil antal Text Box Linjer variablet
		RichTextBoxNumberOfLines = 0; 

	}

	// Inkrementer antallet af viste linjer varaiblet
	RichTextBoxNumberOfLines = RichTextBoxNumberOfLines + 1;

	// Hvis antallet af viste linjer har nået et maksimum
	if (RichTextBoxNumberOfLines >= 35) {

		// Nulstil antal Text Box Linjer variablet
		RichTextBoxNumberOfLines = 0;

		// Ryd Text Boksen
		RichTextBox->Clear();

	}

	// Skriv givet string i tekst box
	RichTextBox->AppendText(RMH_Conversion_StdStringToSystemString(Text));
	// Line Feed - Ny linje
	RichTextBox->AppendText("\n");

	// Scroll ned i bunden af tekst boxen
	RichTextBox->ScrollToCaret();

	// Opdater Text Box 
	RichTextBox->Update();

}

// ----------------------- Winform DataGridView Håndterings Routiner ------------------------ //

void RMH_Winforms_DataGridView_Display2ColumnDataGridView(System::Windows::Forms::DataGridView^ DataGridView, std::vector<std::string> ColumnsHeaderText, System::String^ RowHeaderText, float ColumnHeaderTextSize, float RowHeaderTextSize, float CellTextSize, System::Drawing::Color ColumnRowHeaderTextColor, System::Drawing::Color ColumnRowHeaderBackColor, unsigned int ColumnHeaderHeight, unsigned int RowHeaderWidth, std::vector<std::string> Column1Strings, float *Column2Data) {

	// Routinen tilføjer en kolonne til et givet DataGridView 

	// Indstil kolonne headerens text farve
	DataGridView->ColumnHeadersDefaultCellStyle->ForeColor = ColumnRowHeaderTextColor;
	// Indstil kolonne headerens baggrunds farve
	DataGridView->ColumnHeadersDefaultCellStyle->BackColor = ColumnRowHeaderBackColor;
	// Deaktiver Visual styles for column
	DataGridView->EnableHeadersVisualStyles = false;

	// Indstil kolonne Header border Style - Ingen Border
	DataGridView->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;

	// Indstil kolonne Header Font Størrelse
	DataGridView->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", ColumnHeaderTextSize, FontStyle::Bold);

	// Indstil kolonne Header højden
	DataGridView->ColumnHeadersHeight = ColumnHeaderHeight;

	// Deaktiver Resizing af Headeren
	DataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;

	// Tilføj antal kolonner
	for (unsigned char i = 0; i < ColumnsHeaderText.size(); i++) {

		// Tilføj kolonne til Data Grid View
		DataGridView->Columns->Add(i.ToString(), RMH_Conversion_StdStringToSystemString(ColumnsHeaderText[i]));

		// Indstil kolonnens text farve
		DataGridView->Columns[i.ToString()]->DefaultCellStyle->ForeColor = ColumnRowHeaderTextColor;
		// Indstil kolonne baggrunds farve
		DataGridView->Columns[i.ToString()]->DefaultCellStyle->BackColor = ColumnRowHeaderBackColor;

		// Kolonnen skal fylde hele Data Grid Viewet
		DataGridView->Columns[i.ToString()]->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

		// Deaktiver Column soterings feature
		DataGridView->Columns[i.ToString()]->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;

	}

	// ---------------------------------- Tilføj Row Data Til Oprettede Kolonne ---------------------------------- // 
	
	// Indstil rækkens headerens text farve
	DataGridView->RowHeadersDefaultCellStyle->ForeColor = ColumnRowHeaderTextColor;
	// Indstil rækkens headerens baggrunds farve
	DataGridView->RowHeadersDefaultCellStyle->BackColor = ColumnRowHeaderBackColor;
	// Deaktiver Visual styles for column
	DataGridView->EnableHeadersVisualStyles = false;

	// Indstil rækkens Header border Style - Ingen Border
	DataGridView->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
	// Indstil rækkens cellernes border Style - Ingen Border
	DataGridView->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;

	// Indstil rækkens Header Font Størrelse
	DataGridView->RowHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", RowHeaderTextSize, FontStyle::Bold);
	// Indstil rækkens Celle Font Størrelse
	DataGridView->DefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", CellTextSize, FontStyle::Bold);

	// Indstil rækkens Header bredde
	DataGridView->RowHeadersWidth = RowHeaderWidth;

	// Loop igennem hele det givet string array
	for (unsigned int i = 0; i < Column1Strings.size(); i++) {

		// Tilføj række til Data grid view
		DataGridView->Rows->Add(RMH_Conversion_StdStringToSystemString(Column1Strings[i]), RMH_Conversion_FloatToSystemString(Column2Data[i]));

		// Tilfæj Række header text
		DataGridView->Rows[i]->HeaderCell->Value = String::Format(RowHeaderText + " {0}", i + 1);

		// Indstil Rækkens Tag
		DataGridView->Rows[i]->Tag = i;

	}

	// ----------------------------------------------------------------------------------------------------------- // 

}

// --------------------------- Winforms Billede Visnings Routiner --------------------------- //

void RMH_Winforms_PictureBox_UpdateImageBitmap(System::Windows::Forms::PictureBox^ PictureBox, System::Drawing::Bitmap^ Bitmap, System::Drawing::Imaging::ColorPalette^ ColorPalette) {

	// Routinen viser et givet Bitmap objekt, i en valgt "PictureBox" control handler

	// Sæt Bitmap Color Palette
	Bitmap->Palette = ColorPalette;

	// Slet Picture Box unmanaged Memory
	//delete PictureBox->Image;
	// Opdater Picture Box Image frame data 
	PictureBox->Image = Bitmap;

}

// --------------------- Winforms Menu Og Sub-Menu Håndterings Routiner --------------------- //

void RMH_Winforms_HideSubMenuPanel(System::Windows::Forms::Panel^ SubMenuPanel) {

	// Routinen lukker valgte Sub-Menu Panel

	// Kontroller om Sub-Menuen er synlig
	if (SubMenuPanel->Visible == true) {
		// Gør Sub-Menu usynlige
		SubMenuPanel->Visible = false;
	}

}

void RMH_Winforms_ToggleSubMenuPanel(System::Windows::Forms::Panel^ SubMenuPanel, System::Windows::Forms::Button^ MenuButton) {

	// Routinen Toggler valgte Sub-Menu Panel og opdaterer Menu Knappens "Expanded" karakter (+/-)

	// Kontroller om Sub-Menuen er usynlig
	if (SubMenuPanel->Visible == false) {

		// Luk valgte Sub-Menu Panel
		RMH_Winforms_HideSubMenuPanel(SubMenuPanel);

		// Gør Sub-Menu synlige
		SubMenuPanel->Visible = true;

		// Opdater Menu knappens "Expanded" Karakter
		MenuButton->Text = MenuButton->Text->Replace('+', '-');

		// Refresh Sub-Menu Panel
		SubMenuPanel->Refresh();

	}
	else {

		// Gør Sub-Menu usynlige
		SubMenuPanel->Visible = false;

		// Opdater Menu knappens "Expanded" Karakter
		MenuButton->Text = MenuButton->Text->Replace('-', '+');

	}

}

// ---------------- Winforms Form Dockings & Undockings Håndterings Routiner ---------------- //

void RMH_Winforms_CloseForm(System::Windows::Forms::Form^ FormObject, bool *FormOpenedFlag, bool *FormDockedFlag, bool *FormUndockedFlag) {

	// Routinen lukker en givet form

	// Luk form Objektet
	FormObject->Close();

	// Opdater formens status flag
	*FormOpenedFlag = false;
	*FormDockedFlag = false;
	*FormUndockedFlag = false;

}

void RMH_Winforms_OpenFormInSeperateWindow(System::Windows::Forms::Form^ FormObject, bool *FormOpenedFlag, bool *FormDockedFlag, bool *FormUndockedFlag) {

	// Routinen åbner en givet Form i et seperat vindue

	// Konfigurer Formens Border Style 
	FormObject->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
	// Konfigurer Formens Start position ved Åbning/Undocking
	FormObject->StartPosition = FormStartPosition::CenterScreen;

	// Konfigurer Formen som en "Top Level" Form
	FormObject->TopLevel = true;

	// Vis Formen
	FormObject->Show();

	// Opdater formens status flag
	*FormOpenedFlag = true;
	*FormDockedFlag = false;
	*FormUndockedFlag = true;

}

void RMH_Winforms_OpenAndDockFormInParentPanel(System::Windows::Forms::Form^ FormObject, System::Windows::Forms::Panel^ ParentPanel, bool *FormOpenedFlag, bool *FormDockedFlag, bool *FormUndockedFlag) {

	// Routinen åbner og "Docker" en givet Form i et givet "Parent" Panel

	/*
	*  Tilhørende Form "FormClosing" Overwrite Funktion ->
	* 
	*	private: System::Void ThermalCameraGUI_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	*
	*		// Ved lukning skal formen gemmes
	*		this->Hide();
	*		// Deaktiver "Dispose" Af Formen
	*		e->Cancel = true;
	*
	*		// Opdater Formens "Er Åben" Flag
	*       FormOpenedFlag = false;
	*		FormDockedFlag = false;
	*		isFormUndocked = false;
	*
	*	}
	*  
	*/

	// Sikre at form objektet ikke er maximerede før at den dockes
	if (FormObject->WindowState == FormWindowState::Maximized) {
		FormObject->WindowState = FormWindowState::Normal;
	}

	// Indstil Formen som en Top-Level Form
	FormObject->TopLevel = false;
	FormObject->Parent = ParentPanel;

	// Indstil Formens "Parent" som givet "Parent" Panel
	FormObject->Parent = ParentPanel;

	// Konfigurer Formens Border Style 
	FormObject->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
	// Formen skal fylde hele "Parent" Panelet
	FormObject->Size = ParentPanel->ClientSize;
	FormObject->Dock = DockStyle::Fill;

	// Vis Formen i "Parent" Panelet
	FormObject->Show();
	ParentPanel->PerformLayout();
	FormObject->PerformLayout();

	// Opdater formens status flag
	*FormOpenedFlag = true;
	*FormDockedFlag = true;
	*FormUndockedFlag = false;

}

void RMH_Winforms_UndockFormFromParentPanel(System::Windows::Forms::Form^ FormObject, System::Windows::Forms::Panel^ ParentPanel, bool *FormOpenedFlag, bool *FormDockedFlag, bool *FormUndockedFlag, System::Windows::Forms::FormBorderStyle FormBorderStyle) {

	// Routinen åbner en givet Form. Hvis formen er "Docked" i et "Parent" Panel, så bliver Formen "Undocked" fra panelet og åbnet i et separat vindue.

	// Nulstil Formens Dockings Style
	FormObject->Dock = DockStyle::None;
	// Nulstil Formens Parent 
	FormObject->Parent = nullptr;

	// Fjern Formen som en "Control" fra givet "Parent" Panel
	ParentPanel->Controls->Clear();

	// Konfigurer Formens Border Style
	FormObject->FormBorderStyle = FormBorderStyle;
	// Konfigurer Formens Start position ved Åbning/Undocking
	FormObject->StartPosition = FormStartPosition::CenterScreen;

	// Konfigurere Formen som en "Top Most" Form
	FormObject->TopMost = true;
	// Konfigurer Formen som en "Top Level" Form
	FormObject->TopLevel = true;

	// Vis Formen
	FormObject->Show();

	// Opdater formens status flag
	*FormOpenedFlag = true;
	*FormDockedFlag = false;
	*FormUndockedFlag = true;

}

// ------------ Winforms Display Child Form I Parent Panel Håndterings Routiner ------------- //

bool RMH_Winforms_ToggleChildFormInParentPanel(System::Windows::Forms::Form^ ChildForm, cli::interior_ptr<System::Windows::Forms::Form^> CurrentActiveForm, System::Windows::Forms::Panel^ ParentPanel) {

	// Routinen åbner den valgte Child Form i et givet parent Form panel
	// Retunerede status indikerer som givet Form er åbem eller lukket

	// Hvis en Aktive View Form er aktiv i Parent panelet
	if ((*CurrentActiveForm) != nullptr) {

		// Luk den Nuværende aktive Form
		(*CurrentActiveForm)->Close();
		// Nulstil Nuværende aktive Form til NULL
		(*CurrentActiveForm) = nullptr;

		// Retuner Form status
		return false;

	}
	else {

		// Opdater aktive form til Child Form
		(*CurrentActiveForm) = ChildForm;

		// Ny Child Form er ikke en Top-Level Form
		ChildForm->TopLevel = false;
		// Indstil Child Form uden "Border"
		ChildForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		// Den viste Child Form skal udfylde hele Parent Panelet
		ChildForm->Dock = System::Windows::Forms::DockStyle::Fill;
		// Indstil Child formens størrelse til parent panel størrelsen - Undgå flikker
		ChildForm->Size.Width = ParentPanel->Size.Width;
		ChildForm->Size.Height = ParentPanel->Size.Height;

		// Tilføj Valgte Child Form Til parent Panelet, som en control komponent
		ParentPanel->Controls->Add(ChildForm);
		// Indstil parent Panelets Tag til Child Form
		ParentPanel->Tag = ChildForm;

		// Bring Child formen til fronten af parent panelet
		ChildForm->BringToFront();
		// Display og vis Child formen i parent panelet
		ChildForm->Show();

		// Retuner Form status
		return true;

	}

}

bool RMH_Winforms_AddChildAsControlToParentPanel(System::Windows::Forms::Form^ ChildForm, System::Windows::Forms::Panel^ ParentPanel) {

	// Routinen tilføjer den valgte Form som en "control" i givet parent form panel

	// Child Form er ikke en Top-Level Form
	ChildForm->TopLevel = false;
	// Indstil Child Form uden "Border"
	ChildForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
	// Den viste Child Form skal udfylde hele parent Panelet
	ChildForm->Dock = System::Windows::Forms::DockStyle::Fill;
	// Indstil Child Formens størrelse til panel størrelsen - Undgå flikker
	ChildForm->Size.Width = ParentPanel->Size.Width;
	ChildForm->Size.Height = ParentPanel->Size.Height;

	// Tilføj Valgte Child Form Til Panelet, som en control komponent
	ParentPanel->Controls->Add(ChildForm);

	// Indstil Parent Panelets Tag til Child Form
	ParentPanel->Tag = ChildForm;

	// Bring Child Form bagerest i Parent panelet
	ChildForm->SendToBack();

	// Display og vis den tilføjet Child form
	ChildForm->Show();

	// Retuner status
	return true;

}

bool RMH_Winforms_BringChildFormTOFront(System::Windows::Forms::Form^ ChildForm) {

	// Routinen sender en Child Form (vist i en parent form panel) 
	// til front positionen i et parent panel.

	// Send child form til fronten af parent panelet
	ChildForm->BringToFront();

	// Retuner status
	return true;

}

bool RMH_Winforms_SendChildFormToBack(System::Windows::Forms::Form^ ChildForm) {

	// Routinen sender en Child Form (vist i en parent form panel) 
	// til bagereste position i parent panelet.

	// Send child form til bagereste position i parent panelet
	ChildForm->SendToBack();

	// Retuner status
	return true;

}

// ------------------------ Winform Color Dialog Vælg Farve Routiner ------------------------ //

System::Drawing::Color^ RMH_Winforms_ShowAndReadColorDialog(bool *DialogAbortedFlag) {

	// Routinen åbner en Color dialog, og retunerer den valgte farve
	// Hvis dialogen er blevet lukket, uden at en farve er blevet valgt, da bliver "DialogAbortedFlag" sat til true.

	// Lokale variabler
	System::Drawing::Color^ SelectedColor;
	ColorDialog^ MyDialog = gcnew ColorDialog;

	// Tillad valg af custom farve.
	MyDialog->AllowFullOpen = true;
	// Tillad hjælpe funktionalitet
	MyDialog->ShowHelp = true;

	// Opdater Dialog Abort Flag
	*DialogAbortedFlag = false;

	// Update the text box color if the user clicks OK 
	if (MyDialog->ShowDialog() == ::System::Windows::Forms::DialogResult::OK) {

		// Læs valgte farve fra dialog
		SelectedColor = MyDialog->Color;

		// Opdater Dialog Abort Flag
		*DialogAbortedFlag = false;

	}
	else {

		// Retuner hvid ved dialog abort
		SelectedColor = System::Drawing::Color::FromArgb(255, 255, 255, 255);

		// Opdater Dialog Abort Flag
		*DialogAbortedFlag = true;

	}

	// Retuner valgte farve fra dialog
	return SelectedColor;

}

// ------------------------ Winform CSV Skrivnings/Læsnings Routiner ------------------------ //

void RMH_Winforms_WriteHeaderStringsToCSVFile(std::string FilePath, std::string FileName, std::vector<std::string> HeaderStrings, unsigned int NmbOfHeaderStrings, System::String^ DataDelimiter) {

	// Routinen skriver header beskrivelses strings til CSV fil path

	// Lokale objekter og variabler
	std::ofstream File;
	std::string CSVFilePath = FilePath + "/" + FileName;
	std::string CombinedHeaderString;

	// Åben csv fil - append til fil (Generer Fil hvis ingen fil er på stien)
	File.open(CSVFilePath, std::ios_base::app);

	// Loop til og med antallet af header strings
	for (unsigned int i = 0; i < NmbOfHeaderStrings; i++) {

		// Skriv ikke et komma efter sidste string
		if (i < NmbOfHeaderStrings - 1) {

			// Formater samlede write string - Med komma
			CombinedHeaderString = CombinedHeaderString + HeaderStrings[i] + RMH_Conversion_SystemStringToStdString(DataDelimiter);

		}
		else {

			// Formater samlede write string - Uden komma
			CombinedHeaderString = CombinedHeaderString + HeaderStrings[i];

		}

	}

	// Append string til CSV fil 
	File << CombinedHeaderString << std::endl;

	// Luk Åbnede CSV file
	File.close();

}

void RMH_Winforms_WriteDataArrayToCSVFile(std::string FilePath, std::string FileName, std::string RowIDString, std::string RowHeaderString, double *CSVData, unsigned int NmbOfValues, System::String^ DataDelimiter) {

	// Routinen Skriver et array af data til en CSV Fil

	// Lokale objekter og variabler
	std::ofstream File;
	std::string CSVFilePath = FilePath + "/" + FileName;
	std::string DataStrings[10];
	std::string CombinedCSVWriteString;

	// Åben csv fil - append til fil (Generer Fil hvis ingen fil er på stien)
	File.open(CSVFilePath, std::ios_base::app);

	// Kontroller om filen allerede er åben
	if (File.is_open() == true) {

		// Luk filen før den kan åbnes
		File.close();

	}

	// Åben csv fil - append til fil (Generer Fil hvis ingen fil er på stien)
	File.open(CSVFilePath, std::ios_base::app);

	// Loop til og med antallet af array data punkter
	for (unsigned int i = 0; i < NmbOfValues; i++) {

		// Formater data til string til CSV skrivning
		DataStrings[i] = RMH_Conversion_SystemStringToStdString(CSVData[i].ToString("F5"));

		// Skriv ikke et komma efter sidste string
		if (i < NmbOfValues - 1) {

			// Formater samlede write string - Med komma
			CombinedCSVWriteString = CombinedCSVWriteString + DataStrings[i] + RMH_Conversion_SystemStringToStdString(DataDelimiter);

		}
		else {

			// Formater samlede write string - Uden komma 
			CombinedCSVWriteString = CombinedCSVWriteString + DataStrings[i];

		}

	}

	// Append string til CSV fil 
	File << RowIDString + RMH_Conversion_SystemStringToStdString(DataDelimiter) + RowHeaderString + RMH_Conversion_SystemStringToStdString(DataDelimiter) + CombinedCSVWriteString << std::endl;

	// Luk Åbnede CSV file
	File.close();

}

void RMH_Winforms_WriteDataArrayMatrixToCSVFile(std::string FilePath, std::string FileName, double* CSVData, unsigned int ArrayMatrixWidth, unsigned int ArrayMatrixHeight, System::String^ DataDelimiter) {

	// Routinen Skriver et array af data til en CSV Fil

	// Lokale objekter og variabler
	std::ofstream File;
	std::string CSVFilePath = FilePath + "/" + FileName;
	std::string DataStrings[10];
	std::string CombinedCSVWriteString;
	unsigned int MatrixArrayIndex = 0;
	System::String^ DateHeaderString = System::DateTime::Now.ToString("HH:mm:ss.fff dd-MM-yyyy");

	// Åben csv fil - append til fil (Generer Fil hvis ingen fil er på stien)
	File.open(CSVFilePath, std::ios_base::app);

	// Kontroller om filen allerede er åben
	if (File.is_open() == true) {

		// Luk filen før den kan åbnes
		File.close();

	}

	// Åben csv fil - append til fil (Generer Fil hvis ingen fil er på stien)
	File.open(CSVFilePath, std::ios_base::app);

	// Skriv Fil Dato header string 
	File << "Time And Data For Captured Data: " + RMH_Conversion_SystemStringToStdString(DateHeaderString);

	// Ny Linje
	File << std::endl;
	File << std::endl;

	// Loop igennem array matricens rækker
	for (unsigned int Y = 0; Y < ArrayMatrixHeight; Y++) {

		// Loop igennem array matricens kolonner
		for (unsigned int X = 0; X < ArrayMatrixWidth; X++) {

			// Konverter matrice index til array index
			MatrixArrayIndex = (Y * ArrayMatrixWidth) + X;

			// Skriv ikke et komma efter sidste string
			if (X < ArrayMatrixWidth - 1) {

				// Formater samlede write string - Med komma
				File << RMH_Conversion_SystemStringToStdString(CSVData[MatrixArrayIndex].ToString("F5")) + RMH_Conversion_SystemStringToStdString(DataDelimiter);

			}
			else {

				// Formater samlede write string - Uden komma 
				File << RMH_Conversion_SystemStringToStdString(CSVData[MatrixArrayIndex].ToString("F5"));

			}

		}

		// Ny Linje
		File << std::endl;

	}

	// Luk Åbnede CSV file
	File.close();

}

void RMH_Winforms_GenerateAndWriteCSVFile(std::string FilePath, std::string FileName, std::vector<std::string> AppendString) {

	// Routinen skriver et string array til en CSV fil med giver fil path

	// Lokale objekter og variabler
	std::ofstream File;
	std::string RemovefilePath = FilePath + "/" + FileName;

	// Slet eksisterende CSV fil i Path
	std::remove(RemovefilePath.c_str());

	// Kontroller om filen allerede er åben
	if (File.is_open() == true) {

		// Luk filen før den kan åbnes
		File.close();

	}

	// Åben csv fil - append til fil (Generer Fil hvis ingen fil er på stien)
	File.open(RemovefilePath, std::ios_base::app);

	// Skriv String vector Data Til CSV fil
	for (unsigned int i = 0; i < AppendString.size(); i++) {

		// Append string til CSV fil 
		File << AppendString[i] << std::endl;

	}

	// Luk Åbnede CSV file
	File.close();

}

RMHWinformsLib::FileReadFormat RMH_Winforms_ReadLinesFromCSVFile(std::string FilePath, std::string FileName) {

	// Routinen læser og retunerer et Std::String array Fra givet input Fil Path
	// som indholder alle læste linjer fra valgte Fil

	// Lokale Variabler og Objekter
	std::ifstream File;
	unsigned long i = 0;
	std::string ReadStringLine;
	unsigned long FileNumbOfLines = 0;
	std::string FullPath = FilePath + "/" + FileName;
	RMHWinformsLib::FileReadFormat ReadFile;

	// Åben Valgte input Fil Path
	File.open(FullPath);

	// Kontroller Om filen blev åbnet
	// Hvis Filens Path lokation er forkert - Fejl
	if (!File) {
		
		// Nulstil "Fil Blev Læst Korrekt" Flaget
		// Grundet fil læsnings fejl
		ReadFile.FileReadSuccess = false;
		// Opdater "Zero Length" Status Flag
		ReadFile.FileZeroLengthFlag = true;
		// Nulstil antallet af læste linjer fra filen
		ReadFile.FileLineLength = 0;

	}
	else {

		// Nulstil Antal læste linjer 
		FileNumbOfLines = 0;

		// Loop igennem alle filens linjer
		while (File.good()) {

			// Læs filens String linjer
			std::getline(File, ReadStringLine, '\n');

			// Inkrementer Antal læste linjer 
			FileNumbOfLines++;

		}

		// Nulstil Fil pointere
		File.clear();
		File.seekg(0);

		// Kontroller at filen ikke er Tom
		if (FileNumbOfLines == 0) {

			// Opdater "Zero Length" Status Flag
			ReadFile.FileZeroLengthFlag = true;

		}
		else {

			// Indlæs fil strings til lokalt vector string
			for (i = 0; i < FileNumbOfLines - 1; i++) {

				// Læs filens String linjer
				std::getline(File, ReadStringLine, '\n');

				// Skriv læste string til format vector array 
				ReadFile.FileStrings[i] = ReadStringLine;

			}

			// Nulstil "Zero Length" Status Flag
			ReadFile.FileZeroLengthFlag = false;
			// Opdater "Fil Blev Læst Korrekt" Flaget
			ReadFile.FileReadSuccess = true;
			// Lager antallet af læste linjer fra filen
			ReadFile.FileLineLength = FileNumbOfLines - 1;

		}

	}

	// Luk Åbnede CSV file
	File.close();

	// Retuner Fil Data og status Flag
	return ReadFile;

}

// -------------------- Winform Fil åben/Gem Dialog Håndterings Routiner -------------------- //

System::String^ RMH_Winforms_GetSaveFileDialogDirectory() {

	// Routinen åbner en fil explorer, som benyttes til at indstille et path til hvor en fil skal gemmes til.
	// Routinen retunerer path lokations stringet

	// Lokale objekter og variabler
	System::String^ FilePathNameString;
	System::String^ FilePathString = "None";
	System::Windows::Forms::SaveFileDialog^ SaveFilePathDialog = gcnew System::Windows::Forms::SaveFileDialog;

	// Konfigurer fil type filtre
	SaveFilePathDialog->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
	// Kik efter alle tilgængelige fil typer
	SaveFilePathDialog->FilterIndex = 2;
	// Restorer tidligere valgt Directory
	SaveFilePathDialog->RestoreDirectory = true;
	// Indstil default dummy filnavn
	SaveFilePathDialog->FileName = "DefaultSavePath";

	// Åben "Save File Dialog" og vent på et korrekt valgt path
	if (SaveFilePathDialog->ShowDialog() == ::DialogResult::OK) {

		// Læs valgte filnavn path 
		FilePathNameString = SaveFilePathDialog->FileName;

		// Håndtering hvis en fil lokering ikke blev valgt
		try {

			// Læs valgte fil Directory path string uden filnavn
			FilePathString = System::IO::Path::GetDirectoryName(FilePathNameString);

		}
		catch (System::Exception^ Ex) {

			// Dialog exploreren blev lukket og intet path blev valgt
			FilePathString = "None";

		}

	}

	// Fortag Garbage collection
	GC::Collect();

	// Retuner Valgte fil path string
	return FilePathString;

}

System::String^ RMH_Winforms_GetOpenFileDialogDirectory() {

	// Routinen åbner en fil explorer, som benyttes til at læse et path fra hvor en fil skal åbnes.
	// Routinen retunerer path lokations stringet

	// Lokale objekter og variabler
	System::String^ FilePathNameString;
	System::String^ FilePathString = "None";
	System::Windows::Forms::OpenFileDialog^ OpenFilePathDialog = gcnew System::Windows::Forms::OpenFileDialog;

	// Konfigurer fil type filtre
	OpenFilePathDialog->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
	// Kik efter alle tilgængelige fil typer
	OpenFilePathDialog->FilterIndex = 2;
	// Restorer tidligere valgt Directory
	OpenFilePathDialog->RestoreDirectory = true;
	// Indstil default dummy filnavn
	OpenFilePathDialog->FileName = "DefaultOpenPath";

	// Åben dialogen
	DialogResult DResult = OpenFilePathDialog->ShowDialog();

	// Vent på et korrekt valgt path
	if (DResult == DialogResult::OK) {

		// Læs valgte filnavn path 
		FilePathNameString = OpenFilePathDialog->FileName;

	}
	else if (DResult == DialogResult::Cancel) {

		// Dialog exploreren blev lukket og intet path blev valgt
		FilePathNameString = "None";

	}

	// Fortag Garbage collection
	GC::Collect();

	// Retuner Valgte fil path string
	return FilePathNameString;

}

// --------------------------- Winform Chart Håndterings Routiner --------------------------- //

void RMH_Winforms_Charts_ChangeXAxesLimits(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartArea1Index, double ChartXAxesMinimum, double ChartXAxesMaximum) {

	// Routinen indstiller winforms chartets X-Akse begr nsninger

	// Indstil chats maximum og minimum X-Akse gr nser
	Chart->ChartAreas[ChartArea1Index]->Axes[0]->Maximum = ChartXAxesMaximum;
	Chart->ChartAreas[ChartArea1Index]->Axes[0]->Minimum = ChartXAxesMinimum;

}

void RMH_Winforms_Charts_ChangeXAxesTickInterval(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartArea1Index, double AxesInterval) {

	// Routinen indstiller winforms chartets X-Akse tick interval

	// Indstil intervallet for chartets X-Akse
	Chart->ChartAreas[ChartArea1Index]->Axes[0]->Interval = AxesInterval;

}

void RMH_Winforms_Charts_ChangeYAxesLimits(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartArea1Index, double ChartYAxesMinimum, double ChartYAxesMaximum) {

	// Routinen indstiller winforms chartets Y-Akse begr nsninger

	// Indstil chats maximum og minimum Y-Akse gr nser
	Chart->ChartAreas[ChartArea1Index]->Axes[1]->Maximum = ChartYAxesMaximum;
	Chart->ChartAreas[ChartArea1Index]->Axes[1]->Minimum = ChartYAxesMinimum;

}

void RMH_Winforms_Charts_ChangeYAxesTickInterval(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartArea1Index, double AxesInterval) {

	// Routinen indstiller winforms chartets Y-Akse tick interval

	// Indstil intervallet for chartets X-Akse
	Chart->ChartAreas[ChartArea1Index]->Axes[1]->Interval = AxesInterval;

}

void RMH_Winforms_Charts_AddDataArrayToChartSeries(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartSeriesIndex, double* SeriesXDataArray, double* SeriesYDataArray, unsigned int SeriesDataArrayLength) {

	// Routinen skriver et array af data til valgte chart data serie

	// Ryd Chartets data punkter
	Chart->Series[ChartSeriesIndex]->Points->Clear();

	// Loop til og med l ngden af givet data array
	for (unsigned int i = 0; i < SeriesDataArrayLength; i++) {

		// Tilf j givet data array til chart serie data
		Chart->Series[ChartSeriesIndex]->Points->AddXY(SeriesXDataArray[i], SeriesYDataArray[i]);

	}

}

void RMH_Winforms_Charts_AddDataPointToChartSeries(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartSeriesIndex, double PointXData, double PointYData) {

	// Routinen skriver et givet data punkt til valgte chart data serie

	// Tilføj givet data point til chart serie data
	Chart->Series[ChartSeriesIndex]->Points->AddXY(PointXData, PointYData);

}

void RMH_Winforms_Charts_ClearChartDataPoints(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartSeriesIndex) {

	// Routinen nulstiller og rydder valgte Chart indexets data punkter

	// Ryd Chartets data punkter
	Chart->Series[ChartSeriesIndex]->Points->Clear();

}

// -------------------------- Winform Billede Og SnapShot Routiner -------------------------- //

bool RMH_Winforms_SavePanelSnapShotPNG(System::Windows::Forms::Panel^ SrcPanel, System::String^ SnapShotPath) {

	// Routinen gemmer et PNG snapshot fra et givet input grafisk panel.
	// input Fil Path Eksempel: C:\Users\User\Desktop
	// Routinen retunerer "true" hvis snapshot er blevet korrekt gemt - ellers "false"
	// Det gemte fil navn er formaterede på formen: Snapshot_HHmmssddMMyyyy

	// Lokale variabler
	bool ReturnStatus = false;
	float PanelUpperLeftSourceX = 0;
	float PanelUpperLeftSourceY = 0;
	float WinScaleSettingNormalized = 0;
	WINMonitorSettings WindowsScreenSettings;
	System::Drawing::Size CompensatedScreenSize = SrcPanel->Size;

	// Formater Filens data identifikations string (Snapshot_HHmmssddMMyyyy)
	System::String^ FileName = System::DateTime::Now.ToString("HHmmssfffddMMyyyy");

	// Læs Windows skærm parametere
	WindowsScreenSettings = RMH_Winforms_ReadWindowsScreenSettings();

	// Normaliser Windows skallerings indstillingen 
	WinScaleSettingNormalized = (float)WindowsScreenSettings.MonitorHorizontalScaleSetting / 100.0;

	// Udregn Panelets Top venstre X & Y pixel kordinater - Kompenser for windows Skallerings indstilling
	PanelUpperLeftSourceX = (float)SrcPanel->PointToScreen(System::Drawing::Point(0, 0)).X * (WinScaleSettingNormalized - 1.0);
	PanelUpperLeftSourceY = (float)SrcPanel->PointToScreen(System::Drawing::Point(0, 0)).Y * (WinScaleSettingNormalized - 1.0);

	// Udregn snapshot kompenserede højde og bredde fra læste skærm skallerings faktor
	CompensatedScreenSize.Width = (float)SrcPanel->Size.Width * WinScaleSettingNormalized;
	CompensatedScreenSize.Height = (float)SrcPanel->Size.Height * WinScaleSettingNormalized;

	// Generer Reference Bitmap til Snapshot grafisk data
	System::Drawing::Bitmap^ SnapShotBitMap = gcnew System::Drawing::Bitmap(CompensatedScreenSize.Width, CompensatedScreenSize.Height);

	// Generer Grafisk reference objekt til lagering af Reference Bitmap data
	System::Drawing::Graphics^ PanelGraphics = System::Drawing::Graphics::FromImage(SnapShotBitMap);

	// Kopier panelets grafiske data til Grafisk reference objekt (Indenfor panalets grænser)
	PanelGraphics->CopyFromScreen(SrcPanel->PointToScreen(System::Drawing::Point(RMH_Math_Round(PanelUpperLeftSourceX), RMH_Math_Round(PanelUpperLeftSourceY))), System::Drawing::Point(0, 0), CompensatedScreenSize);

	// Håndtering ved Path string fejl
	try {

		// Gem Snashot billede på valge fil lokation
		SnapShotBitMap->Save(SnapShotPath + "/SnapShot_" + FileName + ".png", System::Drawing::Imaging::ImageFormat::Png);

		// Opdater Retunerede status
		ReturnStatus = true;

	}
	catch (System::Exception^ Ex) {

		// Opdater Retunerede status
		ReturnStatus = false;

	}

	// Fortag Garbage collection
	GC::Collect();

	// Retuner Status
	return ReturnStatus;

}

bool RMH_Winforms_SaveRawImageDataAsSnapShotPNG(System::String^ SnapShotPath, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char *ImageData) {

	// Routinen gemmer Rå input Billede data som et PNG snapshot.
	// input Fil Path Eksempel: C:\Users\User\Desktop
	// Routinen retunerer "true" hvis snapshot er blevet korrekt gemt - ellers "false"
	// Det gemte fil navn er formaterede på formen: Snapshot_HHmmssddMMyyyy

	// Lokale variabler
	bool ReturnStatus = false;
	unsigned char* BGRImageData = new unsigned char[ImageDataWidth * ImageDataHeight * 3];

	// Formater Filens data identifikations string (SnapshotRAW_HHmmssddMMyyyy)
	System::String^ FileName = System::DateTime::Now.ToString("HHmmssfffddMMyyyy");

	// Konverter array data fra RGB Til BGR format
	for (unsigned int Y = 0; Y < ImageDataHeight; Y++) {

		// Loop i gennem alle array matricens rækker
		for (unsigned int X = 0; X < ImageDataWidth; X++) {

			// Læs source og destinations indexerne
			unsigned int SrcIndex = (Y * ImageDataWidth + X) * 3;
			unsigned int DstIndex = (Y * ImageDataWidth + X) * 3;

			// Om arranger RGB Data Til BGR format
			BGRImageData[DstIndex + 2] = ImageData[SrcIndex + 0];
			BGRImageData[DstIndex + 1] = ImageData[SrcIndex + 1];
			BGRImageData[DstIndex + 0] = ImageData[SrcIndex + 2];

		}
	}

	// Generer Bitmap fra givet billede data til Snapshot grafisk data
	System::Drawing::Bitmap^ SnapShotBitMap = gcnew System::Drawing::Bitmap(
		ImageDataWidth, ImageDataHeight, 3 * ImageDataWidth, 
		System::Drawing::Imaging::PixelFormat::Format24bppRgb,
		System::IntPtr(&BGRImageData[0]));

	// Håndtering ved Path string fejl
	try {

		// Gem Snashot billede på valge fil lokation
		SnapShotBitMap->Save(SnapShotPath + "/SnapShotRAW_" + FileName + ".png", System::Drawing::Imaging::ImageFormat::Png);

		// Opdater Retunerede status
		ReturnStatus = true;

	}
	catch (System::Exception^ Ex) {

		// Opdater Retunerede status
		ReturnStatus = false;

	}

	// Fortag Garbage collection
	GC::Collect();

	// Frigør allokerede hukommelse for buffer array  
	delete[] BGRImageData;

	// Retuner Status
	return ReturnStatus;

}

// ------------------------ Winform Web Browser Håndterings Routiner ------------------------ //

bool RMH_Winforms_IsAdobeReaderInstalled() {

	// Routinen Kontroller om "Adobe Reader" er installerede på brugerens computer

	// String array af mulige Registry nøgle Stier
	cli::array<String^>^ PossibleRegistryKeys = {
		"SOFTWARE\\Adobe\\Acrobat Reader",
		"SOFTWARE\\WOW6432Node\\Adobe\\Acrobat Reader",
		"SOFTWARE\\Adobe\\Adobe Acrobat",
		"SOFTWARE\\WOW6432Node\\Adobe\\Adobe Acrobat"
	};

	// Kontroller hver Key i Registry
	for each (String ^ KeyPath in PossibleRegistryKeys) {

		// Håndter Exception
		try {

			// Open the registry key
			RegistryKey^ Key = Registry::LocalMachine->OpenSubKey(KeyPath);

			// Hvis registry nøglen ikke er en nul pointer
			if (Key != nullptr) {

				// Læs registry nøglen navn
				cli::array<String^>^ SubKeyNames = Key->GetSubKeyNames();

				// Hvis Nøglens Sub navn string længde er over 0
				if (SubKeyNames->Length > 0) {

					// Prøv på at finde Adode Reader Executablen (.exe)
					for each (String ^ Version in SubKeyNames) {

						// Læs Registry Nøglens Version
						RegistryKey^ VersionKey = Key->OpenSubKey(Version + "\\InstallPath");

						// Hvis registry nøglen versionen ikke er en nul pointer
						if (VersionKey != nullptr) {

							// Læs executable stien
							String^ InstallPath = static_cast<String^>(VersionKey->GetValue(""));

							// Kontroller at executable stien faktisk er et string
							if (!String::IsNullOrEmpty(InstallPath)) {

								// Construct the full path to the executable
								String^ ReaderExePath = Path::Combine(InstallPath, "Acrobat.exe");

								// Kontroller/Check om Adobe Reader executable eksisterer
								if (File::Exists(ReaderExePath)) {

									// Luk for registry Versions nøglen
									VersionKey->Close();
									// Luk for registry nøglen
									Key->Close();

									// Adobe Reader executable Blev Fundet (Adobe Reader Er Installerede På Computeren)
									return true; 

								}

							}

							// Luk for registry Versions nøglen
							VersionKey->Close();

						}

					}

				}

				// Luk for registry nøglen
				Key->Close();

			}

		}
		catch (Exception^ ex) { }

	}

	// Adobe Reader executable Blev IKKE Fundet (Adobe Reader Er IKKE Installerede På Computeren)
	return false; 

}

void RMH_Winforms_OpenPDFInWebbrowser(System::Windows::Forms::WebBrowser^ WebBrowserControl, System::String^ PDFFileName) {

	// Routinen åbner en PDF fil i givet Webbrowser Komponent.
	// PDF filen skal likke på samme sti som applikationens .exe

	// Kontroller om Adobe Reader er installerede på computeren
	if (RMH_Winforms_IsAdobeReaderInstalled() == true) {

		// Hent stien til for applikations .exe fil
		String^ exePath = Application::StartupPath;

		// Konstruer den fulde sti til PDF-filen
		String^ pdfPath = Path::Combine(exePath, PDFFileName);

		// Tjek om PDF-filen eksisterer, før den indlæses
		if (File::Exists(pdfPath)) {

			// Konverter filstien til URI-format
			String^ pdfUri = "file:///" + pdfPath->Replace("\\", "/");

			// Indlæs PDF-filen i WebBrowser komponentet
			WebBrowserControl->Navigate(pdfUri);

		}
		else {

			// Konstruer custom HTML til en error meddelse
			String^ errorHtml = R"(
                <html>
                <head>
                    <style>
                        body { background-color: #232323; color: #ffffff; font-family: Arial, sans-serif; text-align: center; padding: 50px; }
                        h1 { color: #ff0000; }
                        p { font-size: 16px; }
                    </style>
                </head>
                <body>
                    <h1> PDF Manual File Error: The Software Manual PDF File Was Not Found!</h1>
                    <p>The PDF File Was Not Found On Path: <strong>)" + pdfPath + R"(</strong></p>
                    <p>Please Check If The File Is In The Displayed Path Or Contact Software Admin.</p>
                </body>
                </html>
            )";

			// Display den custom error HTML meddelse i WebBrowser komponentet
			WebBrowserControl->DocumentText = errorHtml;

		}

	}
	else {

		// Konstruer custom HTML til en error meddelse
		String^ errorHtml = R"(
                <html>
                <head>
                    <style>
                        body { background-color: #232323; color: #ffffff; font-family: Arial, sans-serif; text-align: center; padding: 50px; }
                        h1 { color: #ff0000; }
                        p { font-size: 16px; }
                    </style>
                </head>
                <body>
                    <h1> Adobe Reader Is Not Installed!</h1>
                    <p>- Please Install Adobe Reader To Read The Software User Manual -</p>
					<p>Link: https://get.adobe.com/dk/reader/</p>
                </body>
                </html>
            )";

		// Display den custom error HTML meddelse i WebBrowser komponentet
		WebBrowserControl->DocumentText = errorHtml;

	}

}

// ------------------------------------------------------------------------------------------ //


