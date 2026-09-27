/*
 *  RMH_Winforms_Library.h
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

#pragma once

 // RMH_Winforms_Library.h
#ifndef RMH_Winforms_Library_H 
#define RMH_Winforms_Library_H

// Inkluderede Blbiloteker
#include <string>
#include <vector>
#include <array>

// Status Meddelses typer macroer
#define _StatusMessageType_Normal      1
#define _StatusMessageType_Success     2
#define _StatusMessageType_Warning     3
#define _StatusMessageType_Error       4

// Microsoft Store applikationers "PackageFamilyName" strings
#define _MicrosoftStore_ScreenRecorderForWindows11          "45907smallapp.ScreenRecorderforWindows11_z9hw59krvrfng"
#define _MicrosoftStore_SnippingTool                        "Microsoft.ScreenSketch_8wekyb3d8bbwe"

// Form Docking & Undockings indstillings Macroer
#define _FormDockingState_DockForm         1
#define _FormDockingState_UndockForm       2

// ---------------------------- Tilhørende Klasser Og Strukturer ---------------------------- //

// Tilhørende Namespace Til Klasse
namespace RMHWinformsLib {

    // Specifik Klasse Ved læsning af Fil 
    class FileReadFormat {
    public:

        // Klasse variabler og objekter
        bool FileReadSuccess = false;
        bool FileZeroLengthFlag = false;
        std::vector<std::string> FileStrings{120};
        unsigned long FileLineLength = 0;

    };

}

// Specifik Struktur Til Læsning Af Skærm indstillings parameter
struct WINMonitorSettings {

    // Struktur variabler og objekter (Maks Antal Monitorer = 10)
    unsigned short NumberOfConnectedMonitors = 0;
    unsigned short MonitorVirtualWidth = 0;
    unsigned short MonitorPhysicalWidth = 0;
    unsigned short MonitorVirtualHeight = 0;
    unsigned short MonitorPhysicalHeight = 0;
    unsigned short MonitorDPISetting = 0;
    unsigned short MonitorHorizontalScaleSetting = 0;
    unsigned short MonitorVerticalScaleSetting = 0;

};

// ------------------------- Winform Titlebar Håndterings Routiner -------------------------- //

void RMH_Winforms_EnableTitleBarDarkMode(System::IntPtr FormHandle);

// ----------------------------- Winform Benchmarkings Routiner ----------------------------- //

System::Diagnostics::Stopwatch^ RMH_Winforms_StartBenchMarkTimer();
void RMH_Winforms_StopBenchmarkTimerAndDisplay(System::Diagnostics::Stopwatch^ BenchmarkTimer);

// ---------------------------- Winform GUI Håndterings Routiner ---------------------------- //

void RMH_Winforms_StartMainApplicationGUI();
void RMH_Winforms_ChangeFormTitleBarText(System::Windows::Forms::Form^ Winform, std::string Text);

// --------------------- Winform Eksterne Processer Håndterings Routiner -------------------- //

void RMH_Winforms_OpenLinkURL(System::String^ LinkURL);
bool RMH_Winforms_OpenWindowsMicrosoftStoreApp(System::String^ PackageFamilyName);
void RMH_Winforms_OpenExternalApplicationEXE(System::String^ ExternalEXENameString);

// ------------ Winform Windows Skærm Width/Height/Scaling/DPI Læsnings Routiner ------------ //

WINMonitorSettings RMH_Winforms_ReadWindowsScreenSettings();

// -------------------------- Winform ComboBox Håndterings Routiner ------------------------- //

void RMH_Winforms_CombiBox_AddArrayOfItemStrings(System::Windows::Forms::ComboBox^ CombiBox, std::vector<std::string> StringArray);
void RMH_Winforms_CombiBox_SetSellectedItemPosition(System::Windows::Forms::ComboBox^ CombiBox, unsigned char ItemIndex);

// ----------------------- Winform NumericUpDown Håndterings Routiner ----------------------- //

bool RMH_Winforms_NumericUpDown_ChangeNumber(System::Windows::Forms::NumericUpDown^ NumericUpDown, float InputNumber, float ScaleFactor, float Offset, float DefaultValue);

// ------------------------ Winform RichTextBox Håndterings Routiner ------------------------ //

void RMH_Winforms_RichTextBox_WriteLine(System::Windows::Forms::RichTextBox^ RichTextBox, std::string Text, unsigned int MessageType);

// ----------------------- Winform DataGridView Håndterings Routiner ------------------------ //

void RMH_Winforms_DataGridView_Display2ColumnDataGridView(System::Windows::Forms::DataGridView^ DataGridView, std::vector<std::string> ColumnsHeaderText, System::String^ RowHeaderText, float ColumnHeaderTextSize, float RowHeaderTextSize, float CellTextSize, System::Drawing::Color ColumnRowHeaderTextColor, System::Drawing::Color ColumnRowHeaderBackColor, unsigned int ColumnHeaderHeight, unsigned int RowHeaderWidth, std::vector<std::string> Column1Strings, float* Column2Data);

// --------------------------- Winforms Billede Visnings Routiner --------------------------- //

void RMH_Winforms_PictureBox_UpdateImageBitmap(System::Windows::Forms::PictureBox^ PictureBox, System::Drawing::Bitmap^ Bitmap, System::Drawing::Imaging::ColorPalette^ ColorPalette);

// --------------------- Winforms Menu Og Sub-Menu Håndterings Routiner --------------------- //

void RMH_Winforms_HideSubMenuPanel(System::Windows::Forms::Panel^ SubMenuPanel);
void RMH_Winforms_ToggleSubMenuPanel(System::Windows::Forms::Panel^ SubMenuPanel, System::Windows::Forms::Button^ MenuButton);

// ---------------- Winforms Form Dockings & Undockings Håndterings Routiner ---------------- //

void RMH_Winforms_CloseForm(System::Windows::Forms::Form^ FormObject, bool* FormOpenedFlag, bool* FormDockedFlag, bool* FormUndockedFlag);
void RMH_Winforms_OpenFormInSeperateWindow(System::Windows::Forms::Form^ FormObject, bool* FormOpenedFlag, bool* FormDockedFlag, bool* FormUndockedFlag);
void RMH_Winforms_OpenAndDockFormInParentPanel(System::Windows::Forms::Form^ FormObject, System::Windows::Forms::Panel^ ParentPanel, bool* FormOpenedFlag, bool* FormDockedFlag, bool* FormUndockedFlag);
void RMH_Winforms_UndockFormFromParentPanel(System::Windows::Forms::Form^ FormObject, System::Windows::Forms::Panel^ ParentPanel, bool* FormOpenedFlag, bool* FormDockedFlag, bool* FormUndockedFlag, System::Windows::Forms::FormBorderStyle FormBorderStyle);

// ------------ Winforms Display Child Form I Parent Panel Håndterings Routiner ------------- //

bool RMH_Winforms_ToggleChildFormInParentPanel(System::Windows::Forms::Form^ ChildForm, cli::interior_ptr<System::Windows::Forms::Form^> CurrentActiveForm, System::Windows::Forms::Panel^ ParentPanel);
bool RMH_Winforms_AddChildAsControlToParentPanel(System::Windows::Forms::Form^ ChildForm, System::Windows::Forms::Panel^ ParentPanel);
bool RMH_Winforms_BringChildFormTOFront(System::Windows::Forms::Form^ ChildForm);
bool RMH_Winforms_SendChildFormToBack(System::Windows::Forms::Form^ ChildForm);

// ------------------------ Winform Color Dialog Vælg Farve Routiner ------------------------ //

System::Drawing::Color^ RMH_Winforms_ShowAndReadColorDialog(bool* DialogAbortedFlag);

// ------------------------ Winform CSV Skrivnings/Læsnings Routiner ------------------------ //

void RMH_Winforms_WriteHeaderStringsToCSVFile(std::string FilePath, std::string FileName, std::vector<std::string> HeaderStrings, unsigned int NmbOfHeaderStrings, System::String^ DataDelimiter);
void RMH_Winforms_WriteDataArrayToCSVFile(std::string FilePath, std::string FileName, std::string RowIDString, std::string RowHeaderString, double* CSVData, unsigned int NmbOfValues, System::String^ DataDelimiter);
void RMH_Winforms_WriteDataArrayMatrixToCSVFile(std::string FilePath, std::string FileName, double* CSVData, unsigned int ArrayMatrixWidth, unsigned int ArrayMatrixHeight, System::String^ DataDelimiter);
void RMH_Winforms_GenerateAndWriteCSVFile(std::string FilePath, std::string FileName, std::vector<std::string> AppendString); 
RMHWinformsLib::FileReadFormat RMH_Winforms_ReadLinesFromCSVFile(std::string FilePath, std::string FileName);

// -------------------- Winform Fil åben/Gem Dialog Håndterings Routiner -------------------- //

System::String^ RMH_Winforms_GetSaveFileDialogDirectory();
System::String^ RMH_Winforms_GetOpenFileDialogDirectory();

// --------------------------- Winform Chart Håndterings Routiner --------------------------- //

void RMH_Winforms_Charts_ChangeXAxesLimits(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartArea1Index, double ChartXAxesMinimum, double ChartXAxesMaximum);
void RMH_Winforms_Charts_ChangeXAxesTickInterval(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartArea1Index, double AxesInterval);
void RMH_Winforms_Charts_ChangeYAxesLimits(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartArea1Index, double ChartYAxesMinimum, double ChartYAxesMaximum);
void RMH_Winforms_Charts_ChangeYAxesTickInterval(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartArea1Index, double AxesInterval);
void RMH_Winforms_Charts_AddDataArrayToChartSeries(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartSeriesIndex, double* SeriesXDataArray, double* SeriesYDataArray, unsigned int SeriesDataArrayLength);
void RMH_Winforms_Charts_AddDataPointToChartSeries(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartSeriesIndex, double PointXData, double PointYData);
void RMH_Winforms_Charts_ClearChartDataPoints(System::Windows::Forms::DataVisualization::Charting::Chart^ Chart, unsigned int ChartSeriesIndex);

// ------------------------ Winform Panel Billede SnapShot Routiner ------------------------- //

bool RMH_Winforms_SavePanelSnapShotPNG(System::Windows::Forms::Panel^ SrcPanel, System::String^ SnapShotPath);
bool RMH_Winforms_SaveRawImageDataAsSnapShotPNG(System::String^ SnapShotPath, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char* ImageData);

// ------------------------ Winform Web Browser Håndterings Routiner ------------------------ //

bool RMH_Winforms_IsAdobeReaderInstalled();
void RMH_Winforms_OpenPDFInWebbrowser(System::Windows::Forms::WebBrowser^ WebBrowserControl, System::String^ PDFFileName);

// ------------------------------------------------------------------------------------------ //

#endif /* RMH_Winforms_Library_H */
