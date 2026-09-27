
/*
 *  RMH_Application_SaveSession.h
 *
 *  Author: Rune Mark Hansen
 *  Date: December 2022
 *
 */

// Inkluderede Blbiloteker
#include "RMH_Application_SaveSession.h"
#include "RMH_MathConversions_Library.h"
#include "RMH_Winforms_Library.h"
#include <algorithm>
#include <iostream>
#include <vector>

// Inkluderede Resourcer
#include "GlobalObjectsAndVariables.h"
#include "RMH_Application_Information.h"
#include "RMH_2DPlotDataSetSources_Resources.h"

// Gemt Applikations sessions data fil linje længde
#define _SavedSessionCSVFileLineLength          79 + 1 + 1 // Index nummer + Top Header + Bund Header 

// ------------ Routiner Til Håndtering Af Gemt Applikations Sessions Parametere ------------- //

void RMH_Application_SaveLastSessionConfigToFile() {

	// Routinen genererer og gemmer seneste applikations sessions konfiguration i "Documents" Mappen i windows
	// værdier og opsætning i en CSV Fil i executable fil lokationen. 
	// Denne kan derefter læses ved start-op for at sætte sidste aktive applikations konfiguration

	// Læs MyDocuments windows path 
	System::String^ Path = System::Environment::GetFolderPath(System::Environment::SpecialFolder::MyDocuments);
	// Konverter Path System::String Til Std::String
	std::string StdPathString = RMH_Conversion_SystemStringToStdString(Path);
	// Restat karakter "\" med karekter "\" i Path String
	std::replace(StdPathString.begin(), StdPathString.end(), '\\', '/');

	// ------------- Data Som Skal Gemmes I Applikations Preset CSV Fil -------------- //

	// String med Applikations Opsætnings Data 
	std::vector<std::string> SavedSessionDescription = {

		// Fil Start Header
		"- IRCAM Thermal Viewer: Application Configuration Data -",

		// ----------------------- Valgte Termiske Kamera ------------------------ //

		// Valgte Termiske Kamera Index - Row Index 1
		RMH_Conversion_IntToStdString(SelectedThermalCameraIndex),

		// ---------------------------- Color Palette ---------------------------- //

		// Valgte Color Palette Index - Row Index 2
		RMH_Conversion_IntToStdString(SelectedColorPaletteIndex),

		// -------------------- Temperatur Korrektions Værdi --------------------- //

		// Gem sat temperatur korrektions værdi - Row Index 3
		RMH_Conversion_FloatToStdString(SavedTempCorrectionSetting, 5),

		// ---------------------- Aspect Ratio Indstilling ----------------------- //

		// Gem Sessionens Aspect ratio indstilling  - Row Index 4
		RMH_Conversion_SystemStringToStdString(FixedLiveViewAspectRatio.ToString()),

		// ------------------------- Dual Color Palette -------------------------- //

		// Valgte Color Palette Index - Row Index 5
		RMH_Conversion_IntToStdString(SelectedDualColorPaletteIndex),

		// ---------------------- Enhanced Resolution Flag ----------------------- //

		// Gem Sessionens Enhanced Resolution indstilling  - Row Index 6
		RMH_Conversion_SystemStringToStdString(EnhancedResEnableFlag.ToString()),

		// ------------------------- SnapShot Save Path -------------------------- //

		// Gem Sessionens Snapshot Fil Path String  - Row Index 7
		RMH_Conversion_SystemStringToStdString(GlobalVariables::SnapShotDefaultPath),

		// ------------------------ Data Logging Save Path ----------------------- //

		// Gem Sessionens Data Loggings Fil Path String  - Row Index 8
		RMH_Conversion_SystemStringToStdString(GlobalVariables::LoggingCSVDefaultPath),

		// ------------------ Temperatur 2D Plot Indstillinger ------------------- //

		// Gem 2D Plot Sættenes Linje farver
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_1].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_1].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_1].ToString()),    // Index 9 - 11
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_2].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_2].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_2].ToString()),    // Index 12 - 14
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_3].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_3].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_3].ToString()),    // Index 15 - 17
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_4].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_4].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_4].ToString()),    // Index 18 - 20
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_5].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_5].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_5].ToString()),    // Index 21 - 23
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_6].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_6].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_6].ToString()),    // Index 24 - 26
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_7].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_7].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_7].ToString()),    // Index 27 - 29
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_8].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_8].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_8].ToString()),    // Index 30 - 32
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_9].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_9].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_9].ToString()),    // Index 33 - 35
		RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsR[_2DPlotDataSet_10].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsG[_2DPlotDataSet_10].ToString()), RMH_Conversion_SystemStringToStdString(Plot2DDataSetLineColorsB[_2DPlotDataSet_10].ToString()), // Index 36 - 38

		// ------------------- Live View Farver Indstillinger -------------------- //

		// Gem live view label baggrunds indstillingen
		RMH_Conversion_SystemStringToStdString(EnableLabelBackgroundFlag.ToString()),		// Index 39

		// Gem Live View Label, Baggrund, Crosshair mm. Farve data
		RMH_Conversion_SystemStringToStdString(CommonLabelColorR.ToString()),				// Index 40
		RMH_Conversion_SystemStringToStdString(CommonLabelColorG.ToString()),				// Index 41
		RMH_Conversion_SystemStringToStdString(CommonLabelColorB.ToString()),				// Index 42
		RMH_Conversion_SystemStringToStdString(CommonLabelBackgroundColorR.ToString()),		// Index 43
		RMH_Conversion_SystemStringToStdString(CommonLabelBackgroundColorG.ToString()),		// Index 44
		RMH_Conversion_SystemStringToStdString(CommonLabelBackgroundColorB.ToString()),		// Index 45
		RMH_Conversion_SystemStringToStdString(MaxCrosshairColorR.ToString()),				// Index 46
		RMH_Conversion_SystemStringToStdString(MaxCrosshairColorG.ToString()),				// Index 47
		RMH_Conversion_SystemStringToStdString(MaxCrosshairColorB.ToString()),				// Index 48
		RMH_Conversion_SystemStringToStdString(MinCrosshairColorR.ToString()),				// Index 49
		RMH_Conversion_SystemStringToStdString(MinCrosshairColorG.ToString()),				// Index 50
		RMH_Conversion_SystemStringToStdString(MinCrosshairColorB.ToString()),				// Index 51
		RMH_Conversion_SystemStringToStdString(CenterCrosshairColorR.ToString()),			// Index 52
		RMH_Conversion_SystemStringToStdString(CenterCrosshairColorG.ToString()),			// Index 53
		RMH_Conversion_SystemStringToStdString(CenterCrosshairColorB.ToString()),			// Index 54
		RMH_Conversion_SystemStringToStdString(ROISelectedColorR.ToString()),				// Index 55
		RMH_Conversion_SystemStringToStdString(ROISelectedColorG.ToString()),				// Index 56
		RMH_Conversion_SystemStringToStdString(ROISelectedColorB.ToString()),				// Index 57
		RMH_Conversion_SystemStringToStdString(ROIPassiveColorR.ToString()),				// Index 58
		RMH_Conversion_SystemStringToStdString(ROIPassiveColorG.ToString()),				// Index 59
		RMH_Conversion_SystemStringToStdString(ROIPassiveColorB.ToString()),				// Index 60
		RMH_Conversion_SystemStringToStdString(TempMeasCrosshairSelectedColorR.ToString()), // Index 61
		RMH_Conversion_SystemStringToStdString(TempMeasCrosshairSelectedColorG.ToString()), // Index 62
		RMH_Conversion_SystemStringToStdString(TempMeasCrosshairSelectedColorB.ToString()), // Index 63
		RMH_Conversion_SystemStringToStdString(TempMeasCrosshairPassiveColorR.ToString()),  // Index 64
		RMH_Conversion_SystemStringToStdString(TempMeasCrosshairPassiveColorG.ToString()),  // Index 65
		RMH_Conversion_SystemStringToStdString(TempMeasCrosshairPassiveColorB.ToString()),  // Index 66
		RMH_Conversion_SystemStringToStdString(TempLinesSelectedColorR.ToString()),			// Index 67
		RMH_Conversion_SystemStringToStdString(TempLinesSelectedColorG.ToString()),			// Index 68
		RMH_Conversion_SystemStringToStdString(TempLinesSelectedColorB.ToString()),			// Index 69
		RMH_Conversion_SystemStringToStdString(TempLinesPassiveColorR.ToString()),			// Index 70
		RMH_Conversion_SystemStringToStdString(TempLinesPassiveColorG.ToString()),			// Index 71
		RMH_Conversion_SystemStringToStdString(TempLinesPassiveColorB.ToString()),			// Index 72

		// ----------------------- ColorBar Indstillinger ------------------------ //

		// Gem ColorBarens "Full Palette" Range justerings indstilling
		RMH_Conversion_SystemStringToStdString(AdaptFullColorBarPaletteRangeFlag.ToString()), // Index 73

		// --------------------- Video Optagnings Save Path ---------------------- //

		// Gem Sessionens Snapshot Fil Path String  - Row Index 74
		RMH_Conversion_SystemStringToStdString(GlobalVariables::RecordingDefaultPath), // Index 74

		// ------------------ Full Frame Data CSV Indstillinger ------------------ //

		// Gem Sessionens Full Frame CSV Data Delimiter Index værdi  - Row Index 75
		RMH_Conversion_SystemStringToStdString(SelectedFullFrameTempCSVDataDelimiterIndex.ToString()), // Index 75

		// ------------------- Kamera Info Pop-Up Vis-Ikke Flag ------------------- //

		// Gem Sessionens Kamera Info Pop-Up "Vis Ikke" Flag  - Row Index 76
		RMH_Conversion_SystemStringToStdString(PopUpDialogDontShowFlag.ToString()),

		// --------------------- Data Loggings Indstillinger --------------------- //

		// Gem Sessionens Data Logging CSV Data Delimiter Index værdi  - Row Index 77
		RMH_Conversion_SystemStringToStdString(SelectedDataLoggingCSVDataDelimiterIndex.ToString()), // Index 77

		// ------------------- Diverse Indstillings Parametere ------------------- //

		// Diverse Applikations Indstillings Parametere
		RMH_Conversion_SystemStringToStdString(UltraResolutionEnableFlag.ToString()),									// Index 78
		RMH_Conversion_IntToStdString((unsigned int)GlobalVariables::GlobalRecordingFrameRateNumericUpDown->Value),		// Index 79

		// ----------------------------------------------------------------------- //

		// Fil Slut Header
		"- End Of Session Configuration - "
	};

	// ------------------------------------------------------------------------------- //

	// Generer Og Gem Applikations Data i Preset CSV Fil
	RMH_Winforms_GenerateAndWriteCSVFile(StdPathString, Application_PresetFileName, SavedSessionDescription);

}

void RMH_Application_SetSavedSessionConfigToApplication(System::Windows::Forms::RichTextBox^ GUIInfoTextArea) {

	// Routinen læser den gemte applikation session konfigurations fil
	// Og indstiller de relavante applikations værdier og objekter ved start 

	// Lokale Fil data objekt
	RMHWinformsLib::FileReadFormat PresetFile;

	// Læs MyDocuments windows path 
	System::String^ Path = System::Environment::GetFolderPath(System::Environment::SpecialFolder::MyDocuments);
	// Konverter Path System::String Til Std::String
	std::string StdPathString = RMH_Conversion_SystemStringToStdString(Path);
	// Restat karakter "\" med karekter "\" i Path String
	std::replace(StdPathString.begin(), StdPathString.end(), '\\', '/');

	// Læs Data fra applikationens Preset fil
	PresetFile = RMH_Winforms_ReadLinesFromCSVFile(StdPathString, Application_PresetFileName);

	// Håndtering af fil fejl
	try {

		// Blev en gyldig konfigurations fil læst 
		if (PresetFile.FileReadSuccess == true) {

			// Skriv GUI Status Meddelse
			RMH_Winforms_RichTextBox_WriteLine(GUIInfoTextArea, "Session Configuration File Found.", _StatusMessageType_Normal);

			// Kontroller at filen ikke er Tom og har korrekt længde
			if ((PresetFile.FileLineLength != 0 || PresetFile.FileZeroLengthFlag == true) && PresetFile.FileLineLength == _SavedSessionCSVFileLineLength) {

				// Skriv GUI Status Meddelse
				RMH_Winforms_RichTextBox_WriteLine(GUIInfoTextArea, "Loading Last Session Configuration...", _StatusMessageType_Normal);

				/*
				 *  Indstilling Af Fil Konfigurations Data ->
				 */

				 // ----------------------- Valgte Termiske Kamera ------------------------ //

				 // Læs Gemte Camera Source Item index
				SelectedThermalCameraIndex = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[1]);

				// ---------------------------- Color Palette ---------------------------- //

				// Læs Gemte Color Palette Item index
				SelectedColorPaletteIndex = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[2]);

				// -------------------- Temperatur Korrektions Værdi --------------------- //

				// Indstil Gemt Temp korrektions værdi til Kamera config UpDown
				SavedTempCorrectionSetting = RMH_Conversion_StdStringToFloat(PresetFile.FileStrings[3]);

				// ---------------------- Aspect Ratio Indstilling ----------------------- //

				// Indstil Gemt Aspect Ratio Indstilling
				FixedLiveViewAspectRatio = RMH_Conversion_StdStringToBoolean(PresetFile.FileStrings[4]);

				// ------------------------- Dual Color Palette -------------------------- //

				// Læs Gemte Dual Color Palette Item index
				SelectedDualColorPaletteIndex = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[5]);

				// ---------------------- Enhanced Resolution Flag ----------------------- //

				// Læs Gemte Enhanced Resolution Mode Indstilling
				EnhancedResEnableFlag = RMH_Conversion_StdStringToBoolean(PresetFile.FileStrings[6]);

				// ------------------------- SnapShot Save Path -------------------------- //

				// Læs Gemte Snapshot Fil path string
				GlobalVariables::SnapShotDefaultPath = RMH_Conversion_StdStringToSystemString(PresetFile.FileStrings[7]);

				// ------------------------ Data Logging Save Path ----------------------- //

				// Læs Gemte Data Logging Fil path string
				GlobalVariables::LoggingCSVDefaultPath = RMH_Conversion_StdStringToSystemString(PresetFile.FileStrings[8]);

				// ------------------ Temperatur 2D Plot Indstillinger ------------------- //

				// Læs Gemte 2D Plot Linje Farve Data
				for (unsigned int i = 0, j = 0; i < _2DPlotMaxNumberOfDataSets; i++, j += 3) {

					// Skriv Gemte 2D Plot Linje Farve Data til globale arrays
					Plot2DDataSetLineColorsR[i] = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[9 + j]);
					Plot2DDataSetLineColorsG[i] = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[10 + j]);
					Plot2DDataSetLineColorsB[i] = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[11 + j]);

				}

				// ------------------- Live View Farver Indstillinger -------------------- //

				// Læs live view label baggrunds indstillingen
				EnableLabelBackgroundFlag = RMH_Conversion_StdStringToBoolean(PresetFile.FileStrings[39]);

				// Læs Live View Label, Baggrund, Crosshair mm. Farve data
				CommonLabelColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[40]);
				CommonLabelColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[41]);
				CommonLabelColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[42]);
				CommonLabelBackgroundColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[43]);
				CommonLabelBackgroundColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[44]);
				CommonLabelBackgroundColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[45]);
				MaxCrosshairColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[46]);
				MaxCrosshairColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[47]);
				MaxCrosshairColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[48]);
				MinCrosshairColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[49]);
				MinCrosshairColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[50]);
				MinCrosshairColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[51]);
				CenterCrosshairColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[52]);
				CenterCrosshairColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[53]);
				CenterCrosshairColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[54]);
				ROISelectedColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[55]);
				ROISelectedColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[56]);
				ROISelectedColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[57]);
				ROIPassiveColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[58]);
				ROIPassiveColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[59]);
				ROIPassiveColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[60]);
				TempMeasCrosshairSelectedColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[61]);
				TempMeasCrosshairSelectedColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[62]);
				TempMeasCrosshairSelectedColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[63]);
				TempMeasCrosshairPassiveColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[64]);
				TempMeasCrosshairPassiveColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[65]);
				TempMeasCrosshairPassiveColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[66]);
			    TempLinesSelectedColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[67]);
				TempLinesSelectedColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[68]);
				TempLinesSelectedColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[69]);
				TempLinesPassiveColorR = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[70]);
				TempLinesPassiveColorG = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[71]);
				TempLinesPassiveColorB = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[72]);

				// ----------------------- ColorBar Indstillinger ------------------------ //

				// Læs ColorBarens "Full Palette" Range justerings indstilling
				AdaptFullColorBarPaletteRangeFlag = RMH_Conversion_StdStringToBoolean(PresetFile.FileStrings[73]);

				// --------------------- Video Optagnings Save Path ---------------------- //

				// Læs Gemte Snapshot Fil path string
				GlobalVariables::RecordingDefaultPath = RMH_Conversion_StdStringToSystemString(PresetFile.FileStrings[74]);

				// ------------------ Full Frame Data CSV Indstillinger ------------------ //

				// Læs Gemte Full Frame CSV Data Delimiter Index værdi
				SelectedFullFrameTempCSVDataDelimiterIndex = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[75]);

				// ------------------- Kamera Info Pop-Up Vis-Ikke Flag ------------------- //

				// Læs Gemte Kamera Info Pop-Up "Vis Ikke" Flag
				PopUpDialogDontShowFlag = RMH_Conversion_StdStringToBoolean(PresetFile.FileStrings[76]);

				// --------------------- Data Loggings Indstillinger --------------------- //

				// Læs Gemte Data Logging CSV Data Delimiter Index værdi
				SelectedDataLoggingCSVDataDelimiterIndex = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[77]);

				// ------------------- Diverse Indstillings Parametere ------------------- //

				// Diverse Applikations Indstillings Parametere
				UltraResolutionEnableFlag = RMH_Conversion_StdStringToBoolean(PresetFile.FileStrings[78]);
				RecordingFrameRateSetValue = RMH_Conversion_StdStringToInt(PresetFile.FileStrings[79]);

				// ----------------------------------------------------------------------- //

				// Skriv GUI Status Meddelse
				RMH_Winforms_RichTextBox_WriteLine(GUIInfoTextArea, "Session Configuration Set.", _StatusMessageType_Normal);

			}
			else {
				// Skriv GUI Status Meddelse
				RMH_Winforms_RichTextBox_WriteLine(GUIInfoTextArea, "Session Configuration File Is Empty Or Length Error!", _StatusMessageType_Normal);
			}

		}
		else {
			// Skriv GUI Status Meddelse
			RMH_Winforms_RichTextBox_WriteLine(GUIInfoTextArea, "No Session Configuration File Found!", _StatusMessageType_Normal);
		}

	}
	catch (System::Exception^ Ex) {

		// Skriv GUI Status Meddelse
		RMH_Winforms_RichTextBox_WriteLine(GUIInfoTextArea, "Session Configuration File Format Error! ", _StatusMessageType_Error);

	}

}

// ------------------------------------------------------------------------------------------ //
