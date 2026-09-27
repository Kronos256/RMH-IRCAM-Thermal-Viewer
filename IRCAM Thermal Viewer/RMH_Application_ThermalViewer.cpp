/*
 *  RMH_Application_ThermalViewer.c
 *
 *  Author: Rune Mark Hansen
 *  Date: april 2023
 *
 */

// Inkluderede biblioteker
#include "RMH_Application_ThermalViewer.h"
#include "RMH_MathConversions_Library.h"
#include "RMH_ImageProcessing_Library.h"
#include "RMH_ThermalCameraSupport_Library.h"
#include "RMH_AnalysisMode_Routines.h"
#include "RMH_OpenGL_Winforms.h"
#include "VideoPlayBackTools.h"

// Inkluderede Resourcer
#include "GlobalObjectsAndVariables.h"
#include "RMH_SupportedIRCameras_Resources.h"
#include "RMH_2DPlotDataSetSources_Resources.h"
#include "RMH_EmissivityTable_Resources.h"
#include "RMH_TemperatureAlarms_Resources.h"
#include "RMH_FullFrameTempData_Resources.h"
#include "RMH_DataLoggingFeature_Resources.h"
#include "RMH_GeneralTriggerEvent_Resources.h"

// Globale Namespaces
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
using namespace std;

// Statiske Formaterede Color palette Arrays
static unsigned short FormattedLiveViewPalette[3][16384];
static unsigned short FormattedDualLiveViewPalette[3][16384];

// ROI Enable Flag Og Render Ordens Arrays
static unsigned short ActiveROIRenderingOrder[_MaxNumberOfMovableRectangles] = { 0,0,0,0,0,0,0,0,0,0 };
static bool ActiveROIEnableFlags[_MaxNumberOfMovableRectangles] = { false,false,false,false,false,false,false,false,false,false };

// Temp Meas Enable Flag Og Render Ordens Arrays
static unsigned short ActiveTempMeasRenderingOrder[_MaxNumberOfMovableCrosshairs] = { 0,0,0,0,0,0,0,0,0,0 };
static bool ActiveTempMeasEnableFlags[_MaxNumberOfMovableCrosshairs] = { false,false,false,false,false,false,false,false,false,false };

// Temp Meas Enable Flag Og Render Ordens Arrays
static unsigned short ActiveTempLineRenderingOrder[_MaxNumberOfMovableLines] = { 0,0,0,0,0 };
static bool ActiveTempLineEnableFlags[_MaxNumberOfMovableLines] = { false,false,false,false,false };

// ----------------- Applikation Features Aktiverings Håndterings Routiner ------------------ //

void RMH_Application_DisableMainGUIMenuButtons() {

	// Routinen aktiverer eller deaktiverer et givet applikations feature sæt.

	// Loop igennem hele arrayet af Menu knapper
	for (unsigned int i = 0; i < GlobalVariables::MainGUILeftMenuButtons->Length; i++) {

		// Deaktiver Main Menu Feature knapperne
		GlobalVariables::MainGUILeftMenuButtons[i]->Enabled = false;

	}

}

void RMH_Application_EnableApplicationFeatures() {

	// Routinen aktiverer applikations features afhængigt af om applikationen er i Trial eller Full feature mode

	// Aktiver Tilhørende Applikations Feature Sæt
	// Blev et kamera korrekt forbundet, eller er Recording/Snapshot Analysis mode valgt
	if (IRCamera.ConnectedFlag == true || GlobalVariables::GlobalCameraSourceDropList->SelectedIndex == _SnapShotAnalysisMode || GlobalVariables::GlobalCameraSourceDropList->SelectedIndex == _RecordingAnalysisMode) {

		// Skriv GUI Status Meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Genuine License Check Successful!", _StatusMessageType_Success);

		// Tilhørende Feature Mode Aktiverede Feature Sæt
		GlobalVariables::GlobalCursorTempTrackButton->Enabled = true;
		GlobalVariables::GlobalAddTempMeasButton->Enabled = true;
		GlobalVariables::GlobalAddROIMeasButton->Enabled = true;
		GlobalVariables::GlobalAddTempSpecLineButton->Enabled = true;
		GlobalVariables::GlobalShowLineHistButton->Enabled = true;
		GlobalVariables::GlobalImageSharpButton->Enabled = true;
		GlobalVariables::GlobalCalibrateCameraButton->Enabled = true;
		GlobalVariables::GlobalTempRangeButton->Enabled = true;
		GlobalVariables::GlobalFixedAspectRatioButton->Enabled = true;
		GlobalVariables::GlobalRecordingButton->Enabled = true;
		GlobalVariables::GlobalUltraResolutionButton->Enabled = true;
		GlobalVariables::GlobalPeriodicTimerTriggerButton->Enabled = true;
		GlobalVariables::GlobalEnhancedResButton->Enabled = true;

		// Aktiver Dual Color Palette Combobox
		GlobalVariables::GlobalDualColorPaletteComboBox->Enabled = true;

		// Aktiver Gem Full-Frame Temperatur Data Featuren
		GlobalVariables::GlobalSaveTempFrameDataButton->Enabled = true;

		// Aktiver SnapShot Featuren
		GlobalVariables::GlobalSnapshotButton->Enabled = true;

		// Aktiver Live View Dual Color Palette Featuren
		GlobalVariables::GlobalDualColorPaletteButton->Enabled = true;

		// Aktiver Diverse Kamera Konfigurations Menu Features
		GlobalVariables::GlobalAutoCalMenuButton->Enabled = true;
		GlobalVariables::GlobalSnapshotConfigMenuButton->Enabled = true;
		GlobalVariables::GlobalVideoRecordingMenuButton->Enabled = true;
		GlobalVariables::GlobalTempPlotDataSetSettingsMenuButton->Enabled = true;
		GlobalVariables::GlobalDataLoggingSettingsMenuButton->Enabled = true;
		GlobalVariables::GlobalTempAlarmsConfigMenuButton->Enabled = true;
		GlobalVariables::GlobalPeriodicTriggerConfigMenuButton->Enabled = true;

		// Aktiver Live View Stream Context Menu Features
		GlobalVariables::GlobalLiveViewMWRotationStripMenuItem->Enabled = true;
		GlobalVariables::GlobalRotateLiveViewCWStripMenuItem->Enabled = true;
		GlobalVariables::GlobalRotateLiveViewCCWStripMenuItem->Enabled = true;
		GlobalVariables::GlobalSetSharpStdDivToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobalimageSharpeningStrengthToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobalshowUnsharpMaskToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobaldeleteLineToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobaldeleteROIToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobaldeleteTempLabelToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobaldeleteAllToolStripMenuItem2->Enabled = true;
		GlobalVariables::GlobalchangeLineColorsToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobalchangeROIColorsToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobalLiveViewSplitViewToolStripMenuItem->Enabled = true;

		// Aktiver Live View ColorBar Context Menu Features
		GlobalVariables::GlobaltemperatureRangeToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobalenableFullPaletteRangeAdjustmentToolStripMenuItem->Enabled = true;
		GlobalVariables::GlobaladjustDualPaletteRangeToolStripMenuItem->Enabled = true;

		// Loop igennem hele arrayet af Menu knapper
		for (unsigned int i = 0; i < GlobalVariables::MainGUILeftMenuButtons->Length; i++) {

			// Aktiver Main Menu Feature knapperne
			GlobalVariables::MainGUILeftMenuButtons[i]->Enabled = true;

		}

	}

}

// ----------------------- Kamera Konfigurations Håndterings Routiner ----------------------- //

void RMH_ThermalViewer_EnableCameraConfigurationControls(bool EnableState) {

	// Routinen aktiverer eller deaktiverer Kamera konfigurations GUI komponenter

	// Aktiver Kamera konfigurations NumericUpDowns
	for (unsigned int i = 0; i < (unsigned int)GlobalVariables::CameraConfigNumericUpDowns->Length; i++) {

		// Aktiver Kamera konfigurations NumericUpDowns
		GlobalVariables::CameraConfigNumericUpDowns[i]->Enabled = EnableState;

	}

	// Aktiver Read/Set/Recover Kamera konfigurations knapper
	GlobalVariables::GlobalReadCameraConfigButton->Enabled = EnableState;
	GlobalVariables::GlobalSetCameraConfigButton->Enabled = EnableState;
	GlobalVariables::GlobalRecoverDefaultCameraSettingsButton->Enabled = EnableState;

}

void RMH_ThermalViewer_ReadAndDisplayCameraConfigParameters() {

	// Routinen læser og viser de læste interne camera konfigurations parametere

	// Lokale Variabler
	bool ConfigurationValuesOKFlag[6] = { false, false, false, false, false, false };

	// Kontroller om et kamera er forbundet
	if (IRCamera.ConnectedFlag == true) {

		// Læs En enkelt data frame fra det termisk kamera
		RMH_IRThermalCamera_ReadFrameRaw(&IRCameraFrameData[0], &VideoFrameSize);
		// Formater Rå YUY2 Data til 16Bit termisk data array
		RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(&IRCamera, &IRCameraFrameData[0], &FrameThermalDataRaw[0]);
		// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
		RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

		// Læs kameraets interne konfigurations parametere
		RMH_IRThermalCamera_ReadCameraConfigParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

		// Skriv læste interne kamera konfigurations parametere til Kamera konfigurations panel
		//RMH_Winforms_NumericUpDown_ChangeNumber(NumericUpDowns[0], IRCamera.TemperatureCorrectionSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor); - Ikke Benyttet
		ConfigurationValuesOKFlag[1] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[1], IRCamera.AmbientTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_AmbientTemperatureValue);
		ConfigurationValuesOKFlag[2] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[2], IRCamera.ReflectedTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_ReflectedTemperatureValue);
		ConfigurationValuesOKFlag[3] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[3], IRCamera.HumiditySetting, 1, 0, _IRThermalCameraDefault_SurroundingHumidityValue);
		ConfigurationValuesOKFlag[4] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[4], IRCamera.EmissivitySetting, 1, 0, _IRThermalCameraDefault_ObjectEmissivityValue);
		ConfigurationValuesOKFlag[5] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[5], IRCamera.DistanceSetting, 1, 0, _IRThermalCameraDefault_ObjectDistanceValue);

		// Kontroller om konfigurations værdierne var uden for rækkevidde
		if (ConfigurationValuesOKFlag[1] == false) {

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
			// Opdater tilhørende konfigurations værdi til default værdi
			IRCamera.ReflectedTemperatureSetting = _IRThermalCameraDefault_ReflectedTemperatureValue;

		}
		if (ConfigurationValuesOKFlag[2] == false) {

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
			// Opdater tilhørende konfigurations værdi til default værdi
			IRCamera.AmbientTemperatureSetting = _IRThermalCameraDefault_AmbientTemperatureValue;

		}
		if (ConfigurationValuesOKFlag[3] == false) {

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Humidity Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
			// Opdater tilhørende konfigurations værdi til default værdi
			IRCamera.HumiditySetting = _IRThermalCameraDefault_SurroundingHumidityValue;

		}
		if (ConfigurationValuesOKFlag[4] == false) {

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Emissivity Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
			// Opdater tilhørende konfigurations værdi til default værdi
			IRCamera.EmissivitySetting = _IRThermalCameraDefault_ObjectEmissivityValue;

		}
		if (ConfigurationValuesOKFlag[5] == false) {

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Distance Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
			// Opdater tilhørende konfigurations værdi til default værdi
			IRCamera.DistanceSetting = _IRThermalCameraDefault_ObjectDistanceValue;

		}

		// Skriv GUI Start Meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "The Thermal Camera Configuration Has Been Read And Displayed.", _StatusMessageType_Success);

	}
	else {

		// Skriv GUI Start Meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Please Connect To A Thermal Camera Before Reading The Configuration!", _StatusMessageType_Normal);

	}

}

void RMH_ThermalViewer_ReadAndDisplayRAWVideoFileCameraConfigParameters() {

	// Routinen læser og viser de læste interne camera konfigurations parametere
	// Disse er for den læste video RAW fil i "Recording Analysis" Mode

	// Skriv læste interne kamera konfigurations parametere til Kamera konfigurations panel
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[0], IRCamera.TemperatureCorrectionSetting, 1, 0, _IRThermalCameraDefault_TemperatureCorrectionValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[1], IRCamera.AmbientTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_AmbientTemperatureValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[2], IRCamera.ReflectedTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_ReflectedTemperatureValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[3], IRCamera.HumiditySetting, 1, 0, _IRThermalCameraDefault_SurroundingHumidityValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[4], IRCamera.EmissivitySetting, 1, 0, _IRThermalCameraDefault_ObjectEmissivityValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[5], IRCamera.DistanceSetting, 1, 0, _IRThermalCameraDefault_ObjectDistanceValue);

	// Skriv GUI Start Meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "The Thermal Camera Configuration Has Been Read From The Video File And Displayed In The Settings Menu", _StatusMessageType_Success);

}

void RMH_ThermalViewer_ReadAndDisplayRAWSnapShotFileCameraConfigParameters() {

	// Routinen læser og viser de læste interne camera konfigurations parametere
	// Disse er for den læste SnapShot RAW fil i "SnapShot Analysis" Mode

	// Skriv læste interne kamera konfigurations parametere til Kamera konfigurations panel
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[0], IRCamera.TemperatureCorrectionSetting, 1, 0, _IRThermalCameraDefault_TemperatureCorrectionValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[1], IRCamera.AmbientTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_AmbientTemperatureValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[2], IRCamera.ReflectedTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_ReflectedTemperatureValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[3], IRCamera.HumiditySetting, 1, 0, _IRThermalCameraDefault_SurroundingHumidityValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[4], IRCamera.EmissivitySetting, 1, 0, _IRThermalCameraDefault_ObjectEmissivityValue);
	RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[5], IRCamera.DistanceSetting, 1, 0, _IRThermalCameraDefault_ObjectDistanceValue);

	// Skriv GUI Start Meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "The Thermal Camera Configuration Has Been Read From The SnapShot File And Displayed In The Settings Menu", _StatusMessageType_Success);

}

void RMH_ThermalViewer_SetCameraConfigParameters() {

	// Routinen skiver de indstillede konfigurations parameter til kameraet

	// Kontroller og kompenser for Temperatur Enheds indstilling
	switch (TempUnitState) {

		// Temperatur Enhed: Celsius
		case 1:

			// Tilbage konverter til Celsius og opdater kamera konfigurations parameter
			IRCamera.AmbientTemperatureSetting = RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[1]->Value);
			IRCamera.ReflectedTemperatureSetting = RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[2]->Value);

		break;

		// Temperatur Enhed: Fahrenheit
		case 2:

			// Tilbage konverter til Celsius og opdater kamera konfigurations parameter
			IRCamera.AmbientTemperatureSetting = 0.55556f * (RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[1]->Value) - 32.0f);
			IRCamera.ReflectedTemperatureSetting = 0.55556f * (RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[2]->Value) - 32.0f);

		break;

		// Temperatur Enhed: Kelvin
		case 3:

			// Tilbage konverter til Celsius og opdater kamera konfigurations parameter
			IRCamera.AmbientTemperatureSetting = RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[1]->Value) - 273.15f;
			IRCamera.ReflectedTemperatureSetting = RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[2]->Value) - 273.15f;

		break;

	}

	// Opdater kamera konfigurations parameter i "IRCamera" Objektet fra tilhørende GUI NumericUpDowns
	IRCamera.TemperatureCorrectionSetting = RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[0]->Value);
	IRCamera.HumiditySetting = RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[3]->Value);
	IRCamera.EmissivitySetting = RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[4]->Value);
	IRCamera.DistanceSetting = RMH_Conversion_SystemDecimalToFloat(GlobalVariables::CameraConfigNumericUpDowns[5]->Value);

	// Skriv de indstillede kamera konfigurations parameter fra objekt "IRcamera" Til kameraets interne hukommelse.
	RMH_IRThermalCamera_SaveConfigParametersToCamera(&IRCamera, IRCamera.ThermalCameraSupportPool);

	// Skriv GUI Start Meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "New Thermal Camera Configuration Has Been Set.", _StatusMessageType_Success);

	// Generer/Opdater Temperatur Loop-Up Tabel
	RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);

}

void RMH_ThermalViewer_SetCameraConfigUpDownRanges(float TemperatureUnitScaleFactor, float TemperatureUnitOffsetFactor) {

	// Routinen indstiller Kamera konfigurations panelets NumericUpDowns Maksimale og Minimale
	// rækkevidder som et resultat af temperatur endheds konfigurations skift.

	// Konfigurer Temperatur Korrektion Max/Min NumericUpDown begrænsninger
	GlobalVariables::CameraConfigNumericUpDowns[0]->Maximum = RMH_Conversion_FloatToSystemDecimal(_TempCorrectionUpDown_DefaultMaxValue);
	GlobalVariables::CameraConfigNumericUpDowns[0]->Minimum = RMH_Conversion_FloatToSystemDecimal(_TempCorrectionUpDown_DefaultMinValue);

	// Konfigurer Ambiente Temperatur Max/Min NumericUpDown begrænsninger
	GlobalVariables::CameraConfigNumericUpDowns[1]->Maximum = RMH_Conversion_FloatToSystemDecimal((_AmbientTempUpDown_DefaultMaxValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor);
	GlobalVariables::CameraConfigNumericUpDowns[1]->Minimum = RMH_Conversion_FloatToSystemDecimal((_AmbientTempUpDown_DefaultMinValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor);

	// Konfigurer Reflecterede Temperatur Max/Min NumericUpDown begrænsninger
	GlobalVariables::CameraConfigNumericUpDowns[2]->Maximum = RMH_Conversion_FloatToSystemDecimal((_ReflectedTempUpDown_DefaultMaxValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor);
	GlobalVariables::CameraConfigNumericUpDowns[2]->Minimum = RMH_Conversion_FloatToSystemDecimal((_ReflectedTempUpDown_DefaultMinValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor);

}

void RMH_ThermalViewer_RecoverDefaultCameraTempConfiguration() {

	// Routinen indstiller default temperatur konfigurationen for forbundet termisk kamera

	// Indstil/skirv default temperagur konfigurations værdier til tilhørende UpDowns 
	GlobalVariables::CameraConfigNumericUpDowns[0]->Value = (System::Decimal)_IRThermalCameraDefault_TemperatureCorrectionValue;                                                                // Temperator Korrektion
	GlobalVariables::CameraConfigNumericUpDowns[1]->Value = (System::Decimal)((_IRThermalCameraDefault_AmbientTemperatureValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor);    // Ambiente Temperatur
	GlobalVariables::CameraConfigNumericUpDowns[2]->Value = (System::Decimal)((_IRThermalCameraDefault_ReflectedTemperatureValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor);  // Reflekterede Temperatur
	GlobalVariables::CameraConfigNumericUpDowns[3]->Value = (System::Decimal)_IRThermalCameraDefault_SurroundingHumidityValue;                                                                  // Humidity 
	GlobalVariables::CameraConfigNumericUpDowns[4]->Value = (System::Decimal)_IRThermalCameraDefault_ObjectEmissivityValue;                                                                     // Emissivity
	GlobalVariables::CameraConfigNumericUpDowns[5]->Value = (System::Decimal)_IRThermalCameraDefault_ObjectDistanceValue;                                                                       // Afstand

}

// ---------------- 2D Temperatur Plot Håndterings & Konfigurations Routiner ---------------- //

void RMH_ThermalViewer_Set2DPlotDataSetSource(double **Plot2DDataSetSourcePointer, unsigned char DataSource) {

	// Routinen indstiller 2D Plottets Data Sæt pointere til valgte Data Source

	// Hvilket data source er valgt
	switch (DataSource) {

		// Indstil Data Source pointer
		case _2DPlotDataSource_MaximumTemp:			*Plot2DDataSetSourcePointer = &MaximumTemperature;				break;
		case _2DPlotDataSource_MinimumTemp:			*Plot2DDataSetSourcePointer = &MinimumTemperature;				break;
		case _2DPlotDataSource_AverageTemp:			*Plot2DDataSetSourcePointer = &AverageTemperature;				break;
		case _2DPlotDataSource_CenterTemp:			*Plot2DDataSetSourcePointer = &CenterTemperature;				break;
		case _2DPlotDataSource_TempPoint1:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[0];		break;
		case _2DPlotDataSource_TempPoint2:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[1];		break;
		case _2DPlotDataSource_TempPoint3:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[2];		break;
		case _2DPlotDataSource_TempPoint4:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[3];		break;
		case _2DPlotDataSource_TempPoint5:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[4];		break;
		case _2DPlotDataSource_TempPoint6:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[5];		break;
		case _2DPlotDataSource_TempPoint7:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[6];		break;
		case _2DPlotDataSource_TempPoint8:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[7];		break;
		case _2DPlotDataSource_TempPoint9:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[8];		break;
		case _2DPlotDataSource_TempPoint10:			*Plot2DDataSetSourcePointer = &TempMeasurementValues[9];		break;
		case _2DPlotDataSource_Line1MaxTemp:		*Plot2DDataSetSourcePointer = &TempLinesMaxTempValues[0];		break;
		case _2DPlotDataSource_Line1MinTemp:		*Plot2DDataSetSourcePointer = &TempLinesMinTempValues[0];		break;
		case _2DPlotDataSource_Line1AvgTemp:		*Plot2DDataSetSourcePointer = &TempLinesAvgTempValues[0];		break;
		case _2DPlotDataSource_Line2MaxTemp:		*Plot2DDataSetSourcePointer = &TempLinesMaxTempValues[1];		break;
		case _2DPlotDataSource_Line2MinTemp:		*Plot2DDataSetSourcePointer = &TempLinesMinTempValues[1];		break;
		case _2DPlotDataSource_Line2AvgTemp:		*Plot2DDataSetSourcePointer = &TempLinesAvgTempValues[1];		break;
		case _2DPlotDataSource_Line3MaxTemp:		*Plot2DDataSetSourcePointer = &TempLinesMaxTempValues[2];		break;
		case _2DPlotDataSource_Line3MinTemp:		*Plot2DDataSetSourcePointer = &TempLinesMinTempValues[2];		break;
		case _2DPlotDataSource_Line3AvgTemp:		*Plot2DDataSetSourcePointer = &TempLinesAvgTempValues[2];		break;
		case _2DPlotDataSource_Line4MaxTemp:		*Plot2DDataSetSourcePointer = &TempLinesMaxTempValues[3];		break;
		case _2DPlotDataSource_Line4MinTemp:		*Plot2DDataSetSourcePointer = &TempLinesMinTempValues[3];		break;
		case _2DPlotDataSource_Line4AvgTemp:		*Plot2DDataSetSourcePointer = &TempLinesAvgTempValues[3];		break;
		case _2DPlotDataSource_Line5MaxTemp:		*Plot2DDataSetSourcePointer = &TempLinesMaxTempValues[4];		break;
		case _2DPlotDataSource_Line5MinTemp:		*Plot2DDataSetSourcePointer = &TempLinesMinTempValues[4];		break;
		case _2DPlotDataSource_Line5AvgTemp:		*Plot2DDataSetSourcePointer = &TempLinesAvgTempValues[4];		break;
		case _2DPlotDataSource_ROI1MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[0].MaxValue;	break;
		case _2DPlotDataSource_ROI1MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[0].MinValue;	break;
		case _2DPlotDataSource_ROI1AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[0].AvgValue;	break;
		case _2DPlotDataSource_ROI2MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[1].MaxValue;	break;
		case _2DPlotDataSource_ROI2MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[1].MinValue;	break;
		case _2DPlotDataSource_ROI2AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[1].AvgValue;	break;
		case _2DPlotDataSource_ROI3MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[2].MaxValue;	break;
		case _2DPlotDataSource_ROI3MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[2].MinValue;	break;
		case _2DPlotDataSource_ROI3AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[2].AvgValue;	break;
		case _2DPlotDataSource_ROI4MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[3].MaxValue;	break;
		case _2DPlotDataSource_ROI4MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[3].MinValue;	break;
		case _2DPlotDataSource_ROI4AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[3].AvgValue;	break;
		case _2DPlotDataSource_ROI5MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[4].MaxValue;	break;
		case _2DPlotDataSource_ROI5MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[4].MinValue;	break;
		case _2DPlotDataSource_ROI5AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[4].AvgValue;	break;
		case _2DPlotDataSource_ROI6MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[5].MaxValue;	break;
		case _2DPlotDataSource_ROI6MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[5].MinValue;	break;
		case _2DPlotDataSource_ROI6AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[5].AvgValue;	break;
		case _2DPlotDataSource_ROI7MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[6].MaxValue;	break;
		case _2DPlotDataSource_ROI7MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[6].MinValue;	break;
		case _2DPlotDataSource_ROI7AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[6].AvgValue;	break;
		case _2DPlotDataSource_ROI8MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[7].MaxValue;	break;
		case _2DPlotDataSource_ROI8MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[7].MinValue;	break;
		case _2DPlotDataSource_ROI8AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[7].AvgValue;	break;
		case _2DPlotDataSource_ROI9MaxTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[8].MaxValue;	break;
		case _2DPlotDataSource_ROI9MinTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[8].MinValue;	break;
		case _2DPlotDataSource_ROI9AvgTemp:			*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[8].AvgValue;	break;
		case _2DPlotDataSource_ROI10MaxTemp:		*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[9].MaxValue;	break;
		case _2DPlotDataSource_ROI10MinTemp:		*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[9].MinValue;	break;
		case _2DPlotDataSource_ROI10AvgTemp:		*Plot2DDataSetSourcePointer = &ROIAreaPixelValues[9].AvgValue;	break;
		case _2DPlotDataSource_MousePositionTemp:   *Plot2DDataSetSourcePointer = &CursorTemperature;				break;
		case _2DPlotDataSource_ThermalSensorDrift:  *Plot2DDataSetSourcePointer = &SensorTemperatureCalDrift;		break;

	}

}

void RMH_ThermalViewer_Enable2DPlotDataSet(System::Object^ sender) {

	// Routinen aktiverer et 2D Plot Data Set til plotning

	// Cast Sender objekt som Forms CheckBox objekt
	System::Windows::Forms::CheckBox^ CheckBox = (System::Windows::Forms::CheckBox^)sender;

	// Læs Forms CheckBox objekt identifikations tag
	unsigned char CheckBoxTag = Convert::ToInt16(CheckBox->Tag);

	// Kontroller CheckBox Stadie
	if ((bool)CheckBox->Checked == false) {

		// Nulstil data sæt linje data rendererings index offset værdi
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_ResetDataSetLineDataIndexRenderOffset(CheckBoxTag);

	}

	// Aktiver Plot af en valgt DataSæt index
	GlobalVariables::OpenGL2DPlot->RMH_OpenGL_EnablePlotOfDataSetx(CheckBoxTag, (bool)CheckBox->Checked);

}

void RMH_ThermalViewer_Load2DPlotLineColorDataToGlobalArrays() {

	// Routinen loader 2D Plot linje farve data til globale Arrays

	// Loop til og med det maksimale antal 2D Plot Data Sæts
	for (unsigned int i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

		// Load 2D Plot Data linjernes farve værdier til globale arrays
		Plot2DDataSetLineColorsR[i] = GlobalVariables::Plot2DDataSetColorPanels[i]->BackColor.R;
		Plot2DDataSetLineColorsG[i] = GlobalVariables::Plot2DDataSetColorPanels[i]->BackColor.G;
		Plot2DDataSetLineColorsB[i] = GlobalVariables::Plot2DDataSetColorPanels[i]->BackColor.B;

	}

}

void RMH_ThermalViewer_Load2DPlotSavedSessionLineColorData() {

	// Routinen indstiller de gemte sessions 2D Plot linje farve data

	// Loop til og med det maksimale antal 2D Plot Data Sæts
	for (unsigned int i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

		// Indstil 2D Plot linje farve data til visuelle paneler
		GlobalVariables::Plot2DDataSetColorPanels[i]->BackColor = System::Drawing::Color::FromArgb(255, Plot2DDataSetLineColorsR[i], Plot2DDataSetLineColorsG[i], Plot2DDataSetLineColorsB[i]);

		// Indstil Plot data sættets linje farve
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_SetDataSetLineColor(i, Plot2DDataSetLineColorsR[i], Plot2DDataSetLineColorsG[i], Plot2DDataSetLineColorsB[i]);

	}

}

void RMH_ThermalViewer_Change2DPlotDataSetAndSettingsPanelColor(System::Object^ sender) {

	// Routinen opdaterer og indstiller 2D Plot Data sæt farve, samt indstillings panelets farve

	// Lokalt fare variabel
	bool ColorDialogAbortFlag = false;
	System::Drawing::Color^ SelectedColor;

	// Cast Sender objekt som Forms Panel objekt
	System::Windows::Forms::Panel^ PanelObject = (System::Windows::Forms::Panel^)sender;

	// Læs Forms Panel objekt identifikations tag
	unsigned char ColorPanelTag = Convert::ToInt16(PanelObject->Tag);

	// Åben Farve dialog og læs valgte farve
	SelectedColor = RMH_Winforms_ShowAndReadColorDialog(&ColorDialogAbortFlag);

	// Kontroller farve dialog abort flag
	if (ColorDialogAbortFlag == false) {

		// Indstil Farve paneles nye valgte farve
		PanelObject->BackColor = System::Drawing::Color::FromArgb(255, SelectedColor->R, SelectedColor->G, SelectedColor->B);

		// Indstil Plot data sættets linje farve
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_SetDataSetLineColor(ColorPanelTag, SelectedColor->R, SelectedColor->G, SelectedColor->B);

	}

}

void RMH_ThermalViewer_Change2DPlotDataSetLineWidth(System::Object^ sender) {

	// Routinen indstiller et 2D Plots Data Sæts linje tykkelse

	// Cast Sender objekt som Forms NumericUpDown objekt
	System::Windows::Forms::NumericUpDown^ NumericUpDownObject = (System::Windows::Forms::NumericUpDown^)sender;

	// Læs Forms NumericUpDown objekt identifikations tag
	unsigned char NumericUpDownTag = Convert::ToInt16(NumericUpDownObject->Tag);

	// Indstil Plot Data sættets linje tykkelse
	GlobalVariables::OpenGL2DPlot->RMH_OpenGL_SetDataSetLineWidth(NumericUpDownTag, (float)NumericUpDownObject->Value);

}

void RMH_ThermalViewer_Change2DPlotDataSetSource(System::Object^ sender) {

	// Routinen indstiller et nyt valgt 2D Plot data sæt source til valgte ComboBox Index

	// Cast Sender objekt som Forms ComboBox objekt
	System::Windows::Forms::ComboBox^ ComboBox = (System::Windows::Forms::ComboBox^)sender;

	// Læs Forms ComboBox objekt identifikations tag
	unsigned char ComboBoxTag = Convert::ToInt16(ComboBox->Tag);

	// Valg Af 2D Plot Data Sæt Fra ComboBox Tag ID
	switch (ComboBoxTag) {

		// Indstil valgte Data Sæt
		case _2DPlotDataSet_1:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet1SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_2:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet2SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_3:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet3SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_4:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet4SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_5:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet5SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_6:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet6SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_7:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet7SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_8:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet8SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_9:  RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet9SourcePointer, ComboBox->SelectedIndex); break;
		case _2DPlotDataSet_10: RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet10SourcePointer, ComboBox->SelectedIndex); break;

	}

}

void RMH_ThermalViewer_Update2DPlotLegendLabels() {

	// Rotinen opdaterer og indstiller 2D Plottets Legend labels med Data Sættets navn og farve

	// Lokale variabler
	unsigned int DataSetCheckedIndex = 0;

	// Loop til og med det maksimale antal 2D Plot Data Sæts
	for (unsigned int i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

		// Gør 2D Plot Legend label synlig
		GlobalVariables::Plot2DLegendLabels[DataSetCheckedIndex]->Visible = false;

		// Inkrementer Data set index 
		DataSetCheckedIndex = DataSetCheckedIndex + 1;

	}

	// Nulstil Data set index 
	DataSetCheckedIndex = 0;

	// Loop til og med det maksimale antal 2D Plot Data Sæts
	for (unsigned int i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

		// Kontroller hvilke 2D Plot data sæt er aktive
		if (GlobalVariables::Plot2DDataSetCheckBoxs[i]->Checked == true) {

			// Gør 2D Plot Legend label synlig
			GlobalVariables::Plot2DLegendLabels[DataSetCheckedIndex]->Visible = true;

			// Indstil 2D Plot Legend Text til ComboBox Data Set Text
			GlobalVariables::Plot2DLegendLabels[DataSetCheckedIndex]->Text = GlobalVariables::Plot2DDataSetComboBoxs[i]->Text;

			// Opdater 2D Plot Legend Text farven
			GlobalVariables::Plot2DLegendLabels[DataSetCheckedIndex]->ForeColor = GlobalVariables::Plot2DDataSetColorPanels[i]->BackColor;

			// Inkrementer Data set index 
			DataSetCheckedIndex = DataSetCheckedIndex + 1;

		}
		else {

			// Gør 2D Plot Legend label usynlig
			GlobalVariables::Plot2DLegendLabels[DataSetCheckedIndex]->Visible = false;

			// Nulstil 2D Plot Legend Text farven
			GlobalVariables::Plot2DLegendLabels[DataSetCheckedIndex]->ForeColor = System::Drawing::Color::FromArgb(255, 60, 60, 60);

		}

	}

}

// --------------------------- Data Logging Håndterings Routiner ---------------------------- //

void RMH_ThermalViewer_SetDataLoggingSourcePointer(double** DataLoggingSourcePointer, unsigned char DataSource) {

	// Routinen indstiller den givet Data loggings data source pointer

	// Hvilket data source er valgt
	switch (DataSource) {

		// Indstil Data Source pointer
		case _2DPlotDataSource_MaximumTemp:			*DataLoggingSourcePointer = &MaximumTemperature;				break;
		case _2DPlotDataSource_MinimumTemp:			*DataLoggingSourcePointer = &MinimumTemperature;				break;
		case _2DPlotDataSource_CenterTemp:			*DataLoggingSourcePointer = &CenterTemperature;					break;
		case _2DPlotDataSource_TempPoint1:			*DataLoggingSourcePointer = &TempMeasurementValues[0];			break;
		case _2DPlotDataSource_TempPoint2:			*DataLoggingSourcePointer = &TempMeasurementValues[1];			break;
		case _2DPlotDataSource_TempPoint3:			*DataLoggingSourcePointer = &TempMeasurementValues[2];			break;
		case _2DPlotDataSource_TempPoint4:			*DataLoggingSourcePointer = &TempMeasurementValues[3];			break;
		case _2DPlotDataSource_TempPoint5:			*DataLoggingSourcePointer = &TempMeasurementValues[4];			break;
		case _2DPlotDataSource_TempPoint6:			*DataLoggingSourcePointer = &TempMeasurementValues[5];			break;
		case _2DPlotDataSource_TempPoint7:			*DataLoggingSourcePointer = &TempMeasurementValues[6];			break;
		case _2DPlotDataSource_TempPoint8:			*DataLoggingSourcePointer = &TempMeasurementValues[7];			break;
		case _2DPlotDataSource_TempPoint9:			*DataLoggingSourcePointer = &TempMeasurementValues[8];			break;
		case _2DPlotDataSource_TempPoint10:			*DataLoggingSourcePointer = &TempMeasurementValues[9];			break;
		case _2DPlotDataSource_Line1MaxTemp:		*DataLoggingSourcePointer = &TempLinesMaxTempValues[0];			break;
		case _2DPlotDataSource_Line1MinTemp:		*DataLoggingSourcePointer = &TempLinesMinTempValues[0];			break;
		case _2DPlotDataSource_Line1AvgTemp:		*DataLoggingSourcePointer = &TempLinesAvgTempValues[0];			break;
		case _2DPlotDataSource_Line2MaxTemp:		*DataLoggingSourcePointer = &TempLinesMaxTempValues[1];			break;
		case _2DPlotDataSource_Line2MinTemp:		*DataLoggingSourcePointer = &TempLinesMinTempValues[1];			break;
		case _2DPlotDataSource_Line2AvgTemp:		*DataLoggingSourcePointer = &TempLinesAvgTempValues[1];			break;
		case _2DPlotDataSource_Line3MaxTemp:		*DataLoggingSourcePointer = &TempLinesMaxTempValues[2];			break;
		case _2DPlotDataSource_Line3MinTemp:		*DataLoggingSourcePointer = &TempLinesMinTempValues[2];			break;
		case _2DPlotDataSource_Line3AvgTemp:		*DataLoggingSourcePointer = &TempLinesAvgTempValues[2];			break;
		case _2DPlotDataSource_Line4MaxTemp:		*DataLoggingSourcePointer = &TempLinesMaxTempValues[3];			break;
		case _2DPlotDataSource_Line4MinTemp:		*DataLoggingSourcePointer = &TempLinesMinTempValues[3];			break;
		case _2DPlotDataSource_Line4AvgTemp:		*DataLoggingSourcePointer = &TempLinesAvgTempValues[3];			break;
		case _2DPlotDataSource_Line5MaxTemp:		*DataLoggingSourcePointer = &TempLinesMaxTempValues[4];			break;
		case _2DPlotDataSource_Line5MinTemp:		*DataLoggingSourcePointer = &TempLinesMinTempValues[4];			break;
		case _2DPlotDataSource_Line5AvgTemp:		*DataLoggingSourcePointer = &TempLinesAvgTempValues[4];			break;
		case _2DPlotDataSource_ROI1MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[0].MaxValue;	break;
		case _2DPlotDataSource_ROI1MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[0].MinValue;	break;
		case _2DPlotDataSource_ROI1AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[0].AvgValue;	break;
		case _2DPlotDataSource_ROI2MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[1].MaxValue;	break;
		case _2DPlotDataSource_ROI2MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[1].MinValue;	break;
		case _2DPlotDataSource_ROI2AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[1].AvgValue;	break;
		case _2DPlotDataSource_ROI3MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[2].MaxValue;	break;
		case _2DPlotDataSource_ROI3MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[2].MinValue;	break;
		case _2DPlotDataSource_ROI3AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[2].AvgValue;	break;
		case _2DPlotDataSource_ROI4MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[3].MaxValue;	break;
		case _2DPlotDataSource_ROI4MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[3].MinValue;	break;
		case _2DPlotDataSource_ROI4AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[3].AvgValue;	break;
		case _2DPlotDataSource_ROI5MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[4].MaxValue;	break;
		case _2DPlotDataSource_ROI5MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[4].MinValue;	break;
		case _2DPlotDataSource_ROI5AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[4].AvgValue;	break;
		case _2DPlotDataSource_ROI6MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[5].MaxValue;	break;
		case _2DPlotDataSource_ROI6MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[5].MinValue;	break;
		case _2DPlotDataSource_ROI6AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[5].AvgValue;	break;
		case _2DPlotDataSource_ROI7MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[6].MaxValue;	break;
		case _2DPlotDataSource_ROI7MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[6].MinValue;	break;
		case _2DPlotDataSource_ROI7AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[6].AvgValue;	break;
		case _2DPlotDataSource_ROI8MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[7].MaxValue;	break;
		case _2DPlotDataSource_ROI8MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[7].MinValue;	break;
		case _2DPlotDataSource_ROI8AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[7].AvgValue;	break;
		case _2DPlotDataSource_ROI9MaxTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[8].MaxValue;	break;
		case _2DPlotDataSource_ROI9MinTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[8].MinValue;	break;
		case _2DPlotDataSource_ROI9AvgTemp:			*DataLoggingSourcePointer = &ROIAreaPixelValues[8].AvgValue;	break;
		case _2DPlotDataSource_ROI10MaxTemp:		*DataLoggingSourcePointer = &ROIAreaPixelValues[9].MaxValue;	break;
		case _2DPlotDataSource_ROI10MinTemp:		*DataLoggingSourcePointer = &ROIAreaPixelValues[9].MinValue;	break;
		case _2DPlotDataSource_ROI10AvgTemp:		*DataLoggingSourcePointer = &ROIAreaPixelValues[9].AvgValue;	break;
		case _2DPlotDataSource_MousePositionTemp:   *DataLoggingSourcePointer = &CursorTemperature;					break;
		case _2DPlotDataSource_ThermalSensorDrift:  *DataLoggingSourcePointer = &SensorTemperatureCalDrift;			break;

	}

}

void RMH_ThermalViewer_ChangeDataLoggingDataSetSource(unsigned char DataSetIndex, unsigned char DataSourceIndex) {

	// Routinen indstiller et data loggings pointer til et valgt data set source

	// Valg af Data loggings data set
	switch (DataSetIndex) {

		// Indstil data loggings data set til givet data source
		case _2DPlotDataSet_1:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet1SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_2:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet2SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_3:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet3SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_4:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet4SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_5:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet5SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_6:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet6SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_7:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet7SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_8:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet8SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_9:  RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet9SourcePointer, DataSourceIndex);  break;
		case _2DPlotDataSet_10: RMH_ThermalViewer_SetDataLoggingSourcePointer(&DataLoggingDataSet10SourcePointer, DataSourceIndex); break;

	}

}

double* RMH_ThermalViewer_GetDataLoggingSourcePointerFromIndex(unsigned char DataSourceIndex) {

	// Routinen retunerer en valgt data logging data source pointer

	// Lokale variabler
	double* ReturnPointer;

	// Valg af data source pointer index
	switch (DataSourceIndex) {

		// Indstil retunerings pointer til aktuel data loggings source pointer
		case _2DPlotDataSet_1:   ReturnPointer = DataLoggingDataSet1SourcePointer;   break;
		case _2DPlotDataSet_2:   ReturnPointer = DataLoggingDataSet2SourcePointer;   break;
		case _2DPlotDataSet_3:   ReturnPointer = DataLoggingDataSet3SourcePointer;   break;
		case _2DPlotDataSet_4:   ReturnPointer = DataLoggingDataSet4SourcePointer;   break;
		case _2DPlotDataSet_5:   ReturnPointer = DataLoggingDataSet5SourcePointer;   break;
		case _2DPlotDataSet_6:   ReturnPointer = DataLoggingDataSet6SourcePointer;   break;
		case _2DPlotDataSet_7:   ReturnPointer = DataLoggingDataSet7SourcePointer;   break;
		case _2DPlotDataSet_8:   ReturnPointer = DataLoggingDataSet8SourcePointer;   break;
		case _2DPlotDataSet_9:   ReturnPointer = DataLoggingDataSet9SourcePointer;   break;
		case _2DPlotDataSet_10:  ReturnPointer = DataLoggingDataSet10SourcePointer;  break;
	
	}

	// Retuner Data Logging Data source pointer
	return ReturnPointer;

}

void RMH_ThermalViewer_UpdateDataLoggingDefaultSaveFilePath(System::Windows::Forms::Label^ DefaultPathString) {

	// Routinen opdaterer fil lokationen hvor Data Logging CSV filen skal gemmes

	// Lokale variabler
	System::String^ SaveFilePathString;

	// Læs valgte Data logging default save fil path 
	SaveFilePathString = RMH_Winforms_GetSaveFileDialogDirectory();

	// Kontroller om et path blev valgt, eller om dialogen blev lukket
	if (SaveFilePathString == "None") {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "No New Default Data Logging File Path Was Choosen!", _StatusMessageType_Warning);

	}
	else {

		// Opdater Data logging default path
		GlobalVariables::LoggingCSVDefaultPath = SaveFilePathString;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "New Default Data Logging File Path Was Choosen.", _StatusMessageType_Success);

	}

	// Opdater Data logging default Fil path stringet 
	DefaultPathString->Text = "Default Save File Path:  " + GlobalVariables::LoggingCSVDefaultPath;

}

void RMH_ThermalViewer_StartDataLogging() {

	// Routinen konfigurerer Data logging sessionen og starter data logging

	// Lokalr variabler
	unsigned int SelectedSourceIndex = 0;
	unsigned char DataLoggingDataSetIndex = 0;
	unsigned short DataLoggingDurationHoursValue = 0;
	unsigned short DataLoggingDurationMinutesValue = 0;
	unsigned short DataLoggingDurationSedundsValue = 0;
	std::vector<std::string> CSVFileHeaderStrings = { "Sample", "Time(ms)", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A" };

	// Kontroller data logging is Running flag
	if (DataLoggingIsRunningFlag == false) {

		// Nulstil Data Logging duration timer variabel
		DataLoggingDurationTimerMilliSec = 0;

		// Nulstil antallet af aktive data logging sæt
		DataLoggingNumberOfActiveSets = 0;

		// Læs Data Loggings sessionens varigheds parametere
		DataLoggingDurationHoursValue = System::Decimal::ToInt16(GlobalVariables::GlobalDataLoggingDurationHourUpDown->Value);
		DataLoggingDurationMinutesValue = System::Decimal::ToInt16(GlobalVariables::GlobalDataLoggingDurationMinuteUpDown->Value);
		DataLoggingDurationSedundsValue = System::Decimal::ToInt16(GlobalVariables::GlobalDataLoggingDurationSecondsUpDown->Value);

		// Udregn data logging sessionens længde i Millisekundter
		DataLoggingSessionDurationMilliSec = (DataLoggingDurationHoursValue * 3600000) + (DataLoggingDurationMinutesValue * 60000) + (DataLoggingDurationSedundsValue * 1000);

		// Indstil Data Logging thread eksikverings intervals variabel
		DataLoggingIntervalMilliSec = (unsigned long)(System::Decimal::ToDouble(GlobalVariables::GlobalDataLoggingIntervalUpDown->Value) * 1000.0);

		// ----------------------------------- Formater Data Logging Plot Data Set Pointers ----------------------------------- //

		// Loop til og med det maksimale antal 2D Plot data sæts
		for (unsigned int i = 0; i < _2DPlotMaxNumberOfDataSets; i++) {

			// Kontroller om data set er aktivt for data logging
			if (GlobalVariables::Plot2DDataSetCheckBoxs[i]->Checked == true) {

				// Læs det aktive data sets combobox data source index
				SelectedSourceIndex = GlobalVariables::Plot2DDataSetComboBoxs[i]->SelectedIndex;

				// Indstil Data logging data set til valgte combobox data source
				RMH_ThermalViewer_ChangeDataLoggingDataSetSource(DataLoggingDataSetIndex, SelectedSourceIndex);

				// Lager Data set source beskrivelse i CSV header string array
				CSVFileHeaderStrings[DataLoggingDataSetIndex + 2] = RMH_Conversion_SystemStringToStdString(GlobalVariables::Plot2DDataSetComboBoxs[i]->Text);

				// Inkrementer data loggings data set index variabel
				DataLoggingDataSetIndex = DataLoggingDataSetIndex + 1;

				// Inkrementer antallet af aktive data logging sæt tæller variabel
				DataLoggingNumberOfActiveSets = DataLoggingNumberOfActiveSets + 1;

			}

		}

		// -------------------------------- Generer Og Formater Data Logging Sessionens CSV Fil -------------------------------- //

		// Formater Filens data identifikations string (DataLogSession_HHmmssddMMyyyy)
		System::String^ FileName = System::DateTime::Now.ToString("HHmmssfffddMMyyyy");

		// Formater Data logging sessionens Fil navn
		GlobalVariables::DataLoggingSessionFileNameString = "DataLogSession_" + FileName + ".txt";

		// Generer Data logging CSV fil med tilhørende Fil header
		RMH_Winforms_WriteHeaderStringsToCSVFile(RMH_Conversion_SystemStringToStdString(GlobalVariables::LoggingCSVDefaultPath), 
			RMH_Conversion_SystemStringToStdString(GlobalVariables::DataLoggingSessionFileNameString), CSVFileHeaderStrings, DataLoggingNumberOfActiveSets + 2, GlobalVariables::DataLoggingCSVDelimiterString);

		// -------------------------------------------------------------------------------------------------------------------- //

		// Opdater Data logging is running flag
		DataLoggingIsRunningFlag = true;

		// Start Data Logging Thread Process
		GlobalVariables::GlobalDataLoggingThread->RunWorkerAsync();

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Data Logging Has Started.", _StatusMessageType_Success);

	}
	else {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Data Logging Is Already Running!", _StatusMessageType_Warning);

	}

}

void RMH_ThermalViewer_StopDataLogging() {

	// Kontroller data logging status
	if (DataLoggingIsRunningFlag == true) {

		// Opdater Data logging is running flag
		DataLoggingIsRunningFlag = false;

		// Opdater 2D Plot Data Logging indikator string med timer - Inaktiv stadie
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_SetDataLoggingLabelStateAndTimer(DataLoggingIsRunningFlag, DataLoggingDurationTimerMilliSec);

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Data Logging Session Has Stopped.", _StatusMessageType_Warning);

	}
	else {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "No Data Logging Session Is Running...", _StatusMessageType_Normal);

	}
	
}

void RMH_ThermalViewer_UpdateDataLoggingCSVDataDelimiter() {

	// Routinen opdaterer hvilken Data delimiter som benyttes når der gemmes en data logging CSV fil

	// Lokale variabler
	unsigned char DataDelimiterIndex = 0;

	// Læs den valgte Data delimiter fra tilhørende CombiBox
	DataDelimiterIndex = GlobalVariables::GlobalDataLoggingCSVDelimiterCombiBox->SelectedIndex;

	// Lager og opdater læste CSV Data delimiter i globalt variabel
	SelectedDataLoggingCSVDataDelimiterIndex = DataDelimiterIndex;

	// Hvilken Delimiter index er blevet valgt
	switch (SelectedDataLoggingCSVDataDelimiterIndex) {

		// Opdater tilhørende globale delimiter string
		case _DataLoggingDelimiterIndex_Comma:		GlobalVariables::DataLoggingCSVDelimiterString = ",";  break;
		case _DataLoggingDelimiterIndex_Semicolon:	GlobalVariables::DataLoggingCSVDelimiterString = ";";  break;
		case _DataLoggingDelimiterIndex_Colon:		GlobalVariables::DataLoggingCSVDelimiterString = ":";  break;
		case _DataLoggingDelimiterIndex_Space:		GlobalVariables::DataLoggingCSVDelimiterString = " ";  break;
		case _DataLoggingDelimiterIndex_Tab:		GlobalVariables::DataLoggingCSVDelimiterString = "\t"; break;

	}

}

void RMH_ThermalViewer_DataLoggingThreadProcess() {

	// Routinen er den tilhørende Data Logging processor thread

	// Lokale variabler
	unsigned long NumberOfSampels = 0;

	// Eksikver thread process Loop hvis data logging er aktivt 
	while (DataLoggingIsRunningFlag == true) {

		// Eksikverings intervallet for thread er data logging intervallet
		System::Threading::Thread::Sleep(DataLoggingIntervalMilliSec);

		// Opdater Data loggings varigheds tæller variabel
		DataLoggingDurationTimerMilliSec = DataLoggingDurationTimerMilliSec + DataLoggingIntervalMilliSec;

		// Opdater 2D Plot Data Logging indikator string med timer
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_SetDataLoggingLabelStateAndTimer(DataLoggingIsRunningFlag, DataLoggingDurationTimerMilliSec);

		// Indlæs data loggings source data til data array
		for (unsigned int i = 0; i < DataLoggingNumberOfActiveSets; i++) {

			// Indlæs data til Source data array
			DataLoggingSourceDataArray[i] = *RMH_ThermalViewer_GetDataLoggingSourcePointerFromIndex(i);

		}

		// Inkrementer antallet af sampels tæller varaibel
		NumberOfSampels = NumberOfSampels + 1;

		// Hvis Data logging sessionen har nåede sin indstillede ende
		if (DataLoggingDurationTimerMilliSec >= DataLoggingSessionDurationMilliSec + DataLoggingIntervalMilliSec) {

			// Opdater Data logging is running flag
			DataLoggingIsRunningFlag = false;

			// Opdater 2D Plot Data Logging indikator string med timer - Inaktiv stadie
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_SetDataLoggingLabelStateAndTimer(DataLoggingIsRunningFlag, DataLoggingDurationTimerMilliSec);

			// Bryd While loop
			break;

		}

		// Skriv data til genereret CSV Fil
		RMH_Winforms_WriteDataArrayToCSVFile(RMH_Conversion_SystemStringToStdString(GlobalVariables::LoggingCSVDefaultPath),
			RMH_Conversion_SystemStringToStdString(GlobalVariables::DataLoggingSessionFileNameString),
			RMH_Conversion_SystemStringToStdString(NumberOfSampels.ToString()),
			RMH_Conversion_SystemStringToStdString(DataLoggingDurationTimerMilliSec.ToString()),
			&DataLoggingSourceDataArray[0], DataLoggingNumberOfActiveSets, GlobalVariables::DataLoggingCSVDelimiterString);

	}

}

// ------------------------ Temperatur Alarmers Håndterings Routiner ------------------------ //

void RMH_ThermalViewer_SetTempAlarmDataSourcePointer(double** TempAlarmSourcePointer, unsigned char AlarmDataSource) {

	// Routinen indstiller en valgt temperatur alarm data source pointer

	// Hvilket alarm data source er valgt
	switch (AlarmDataSource) {

		// Indstil alarm Data Source pointer
		case _TempAlarmDataSource_MaximumTemp:			*TempAlarmSourcePointer = &MaximumTemperature;				break;
		case _TempAlarmDataSource_MinimumTemp:			*TempAlarmSourcePointer = &MinimumTemperature;				break;
		case _TempAlarmDataSource_AverageTemp:			*TempAlarmSourcePointer = &AverageTemperature;				break;
		case _TempAlarmDataSource_CenterTemp:			*TempAlarmSourcePointer = &CenterTemperature;				break;
		case _TempAlarmDataSource_TempPoint1:			*TempAlarmSourcePointer = &TempMeasurementValues[0];		break;
		case _TempAlarmDataSource_TempPoint2:			*TempAlarmSourcePointer = &TempMeasurementValues[1];		break;
		case _TempAlarmDataSource_TempPoint3:			*TempAlarmSourcePointer = &TempMeasurementValues[2];		break;
		case _TempAlarmDataSource_TempPoint4:			*TempAlarmSourcePointer = &TempMeasurementValues[3];		break;
		case _TempAlarmDataSource_TempPoint5:			*TempAlarmSourcePointer = &TempMeasurementValues[4];		break;
		case _TempAlarmDataSource_TempPoint6:			*TempAlarmSourcePointer = &TempMeasurementValues[5];		break;
		case _TempAlarmDataSource_TempPoint7:			*TempAlarmSourcePointer = &TempMeasurementValues[6];		break;
		case _TempAlarmDataSource_TempPoint8:			*TempAlarmSourcePointer = &TempMeasurementValues[7];		break;
		case _TempAlarmDataSource_TempPoint9:			*TempAlarmSourcePointer = &TempMeasurementValues[8];		break;
		case _TempAlarmDataSource_TempPoint10:			*TempAlarmSourcePointer = &TempMeasurementValues[9];		break;
		case _TempAlarmDataSource_Line1MaxTemp:			*TempAlarmSourcePointer = &TempLinesMaxTempValues[0];		break;
		case _TempAlarmDataSource_Line1MinTemp:			*TempAlarmSourcePointer = &TempLinesMinTempValues[0];		break;
		case _TempAlarmDataSource_Line2MaxTemp:			*TempAlarmSourcePointer = &TempLinesMaxTempValues[1];		break;
		case _TempAlarmDataSource_Line2MinTemp:			*TempAlarmSourcePointer = &TempLinesMinTempValues[1];		break;
		case _TempAlarmDataSource_Line3MaxTemp:			*TempAlarmSourcePointer = &TempLinesMaxTempValues[2];		break;
		case _TempAlarmDataSource_Line3MinTemp:			*TempAlarmSourcePointer = &TempLinesMinTempValues[2];		break;
		case _TempAlarmDataSource_Line4MaxTemp:			*TempAlarmSourcePointer = &TempLinesMaxTempValues[3];		break;
		case _TempAlarmDataSource_Line4MinTemp:			*TempAlarmSourcePointer = &TempLinesMinTempValues[3];		break;
		case _TempAlarmDataSource_Line5MaxTemp:			*TempAlarmSourcePointer = &TempLinesMaxTempValues[4];		break;
		case _TempAlarmDataSource_Line5MinTemp:			*TempAlarmSourcePointer = &TempLinesMinTempValues[4];		break;
		case _TempAlarmDataSource_ROI1MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[0].MaxValue;	break;
		case _TempAlarmDataSource_ROI1MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[0].MinValue;	break;
		case _TempAlarmDataSource_ROI2MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[1].MaxValue;	break;
		case _TempAlarmDataSource_ROI2MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[1].MinValue;	break;
		case _TempAlarmDataSource_ROI3MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[2].MaxValue;	break;
		case _TempAlarmDataSource_ROI3MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[2].MinValue;	break;
		case _TempAlarmDataSource_ROI4MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[3].MaxValue;	break;
		case _TempAlarmDataSource_ROI4MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[3].MinValue;	break;
		case _TempAlarmDataSource_ROI5MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[4].MaxValue;	break;
		case _TempAlarmDataSource_ROI5MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[4].MinValue;	break;
		case _TempAlarmDataSource_ROI6MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[5].MaxValue;	break;
		case _TempAlarmDataSource_ROI6MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[5].MinValue;	break;
		case _TempAlarmDataSource_ROI7MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[6].MaxValue;	break;
		case _TempAlarmDataSource_ROI7MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[6].MinValue;	break;
		case _TempAlarmDataSource_ROI8MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[7].MaxValue;	break;
		case _TempAlarmDataSource_ROI8MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[7].MinValue;	break;
		case _TempAlarmDataSource_ROI9MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[8].MaxValue;	break;
		case _TempAlarmDataSource_ROI9MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[8].MinValue;	break;
		case _TempAlarmDataSource_ROI10MaxTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[9].MaxValue;	break;
		case _TempAlarmDataSource_ROI10MinTemp:			*TempAlarmSourcePointer = &ROIAreaPixelValues[9].MinValue;	break;
		case _TempAlarmDataSource_MousePositionTemp:    *TempAlarmSourcePointer = &CursorTemperature;				break;

	}

}

void RMH_ThermalViewer_ChangeTemperatureAlarmDataSource(System::Object^ sender) {

	// Routinen indstiller en temperatur alarm pointer til et valgt data source

	// Cast Sender objekt som Forms ComboBox objekt
	System::Windows::Forms::ComboBox^ ComboBox = (System::Windows::Forms::ComboBox^)sender;

	// Læs Forms ComboBox objekt identifikations tag
	unsigned char ComboBoxTag = Convert::ToInt16(ComboBox->Tag);

	// Valg af temp alarm data source
	switch (ComboBoxTag) {

		// Indstil temperatur alarm data til givet data source
		case _TemperatureAlarm_1:  RMH_ThermalViewer_SetTempAlarmDataSourcePointer(&TempAlarm1DataSourcePointer, ComboBox->SelectedIndex);  break;
		case _TemperatureAlarm_2:  RMH_ThermalViewer_SetTempAlarmDataSourcePointer(&TempAlarm2DataSourcePointer, ComboBox->SelectedIndex);  break;
		case _TemperatureAlarm_3:  RMH_ThermalViewer_SetTempAlarmDataSourcePointer(&TempAlarm3DataSourcePointer, ComboBox->SelectedIndex);  break;
		case _TemperatureAlarm_4:  RMH_ThermalViewer_SetTempAlarmDataSourcePointer(&TempAlarm4DataSourcePointer, ComboBox->SelectedIndex);  break;
		case _TemperatureAlarm_5:  RMH_ThermalViewer_SetTempAlarmDataSourcePointer(&TempAlarm5DataSourcePointer, ComboBox->SelectedIndex);  break;

	}

	// Nulstil temperatur alarmens status Label string og farve
	GlobalVariables::TempAlarmsStatusLabels[ComboBoxTag]->Text = "Normal";
	GlobalVariables::TempAlarmsStatusLabels[ComboBoxTag]->ForeColor = System::Drawing::Color::White;

	// Nulstil temperatur Alarmens Trigger status
	AlarmsTriggerStatusArray[ComboBoxTag] = false;

}

void RMH_ThermalViewer_ChangeTempAlarmConfigType(System::Object^ sender) {

	// Routinen indstiller temperatur alarmens type

	// Cast Sender objekt som Forms ComboBox objekt
	System::Windows::Forms::ComboBox^ ComboBox = (System::Windows::Forms::ComboBox^)sender;

	// Læs Forms ComboBox objekt identifikations tag
	unsigned char ComboBoxTag = Convert::ToInt16(ComboBox->Tag);

	// Indstil temperatur alarm trigger type
	TempAlarmsConfigType[ComboBoxTag] = ComboBox->SelectedIndex;

	// Nulstil temperatur alarmens status Label string og farve
	GlobalVariables::TempAlarmsStatusLabels[ComboBoxTag]->Text = "Normal";
	GlobalVariables::TempAlarmsStatusLabels[ComboBoxTag]->ForeColor = System::Drawing::Color::White;

	// Nulstil temperatur Alarmens Trigger status
	AlarmsTriggerStatusArray[ComboBoxTag] = false;

}

void RMH_ThermalViewer_ChangeTempAlarmLowTempSetPoint(System::Object^ sender) {

	// Routinen indstiller en valgt temperatur alarms low temperaturs værdi

	// Cast Sender objekt som Forms UpDown objekt
	System::Windows::Forms::NumericUpDown^ SenderUpDown = (System::Windows::Forms::NumericUpDown^)sender;

	// Læs Forms UpDown objekt identifikations tag
	unsigned char SenderUpDownTag = Convert::ToInt16(SenderUpDown->Tag);

	// Skriv indstillede Temp alarm low værdi til globalt array
	TempAlarmsLowTempValues[SenderUpDownTag] = (float)SenderUpDown->Value;

	// Nulstil temperatur alarmens status Label string og farve
	GlobalVariables::TempAlarmsStatusLabels[SenderUpDownTag]->Text = "Normal";
	GlobalVariables::TempAlarmsStatusLabels[SenderUpDownTag]->ForeColor = System::Drawing::Color::White;

	// Nulstil temperatur Alarmens Trigger status
	AlarmsTriggerStatusArray[SenderUpDownTag] = false;

}

void RMH_ThermalViewer_ChangeTempAlarmHighTempSetPoint(System::Object^ sender) {

	// Routinen indstiller en valgt temperatur alarms High temperaturs værdi

	// Cast Sender objekt som Forms UpDown objekt
	System::Windows::Forms::NumericUpDown^ SenderUpDown = (System::Windows::Forms::NumericUpDown^)sender;

	// Læs Forms UpDown objekt identifikations tag
	unsigned char SenderUpDownTag = Convert::ToInt16(SenderUpDown->Tag);

	// Skriv indstillede Temp alarm High værdi til globalt array
	TempAlarmsHighTempValues[SenderUpDownTag] = (float)SenderUpDown->Value;

	// Nulstil temperatur alarmens status Label string og farve
	GlobalVariables::TempAlarmsStatusLabels[SenderUpDownTag]->Text = "Normal";
	GlobalVariables::TempAlarmsStatusLabels[SenderUpDownTag]->ForeColor = System::Drawing::Color::White;

	// Nulstil temperatur Alarmens Trigger status
	AlarmsTriggerStatusArray[SenderUpDownTag] = false;

}

void RMH_ThermalViewer_ChangeTempAlarmTriggerAction(System::Object^ sender) {

	// Routinen indstiller den valgte temperatur alarms trigger aktion

	// Cast Sender objekt som Forms ComboBox objekt
	System::Windows::Forms::ComboBox^ ComboBox = (System::Windows::Forms::ComboBox^)sender;

	// Læs Forms ComboBox objekt identifikations tag
	unsigned char ComboBoxTag = Convert::ToInt16(ComboBox->Tag);

	// Skriv indstillede Temp alarm High værdi til globalt array
	TempAlarmsTriggerAction[ComboBoxTag] = ComboBox->SelectedIndex;

	// Nulstil temperatur alarmens status Label string og farve
	GlobalVariables::TempAlarmsStatusLabels[ComboBoxTag]->Text = "Normal";
	GlobalVariables::TempAlarmsStatusLabels[ComboBoxTag]->ForeColor = System::Drawing::Color::White;

	// Nulstil temperatur Alarmens Trigger status
	AlarmsTriggerStatusArray[ComboBoxTag] = false;

}

void RMH_ThermalViewer_EnableTemperatureAlarm(System::Object^ sender) {

	// Routinen aktiverer eller deaktiverer en valgt temperatur alarm

	// Cast Sender objekt som Forms CheckBox objekt
	System::Windows::Forms::CheckBox^ CheckBox = (System::Windows::Forms::CheckBox^)sender;

	// Læs Forms CheckBox objekt identifikations tag
	unsigned char CheckBoxTag = Convert::ToInt16(CheckBox->Tag);

	// Opdater temperatur alarmens aktiverings stadie
	EnabledTempAlarmsArray[CheckBoxTag] = (bool)CheckBox->Checked;

	// Nulstil temperatur alarmens status Label string og farve
	GlobalVariables::TempAlarmsStatusLabels[CheckBoxTag]->Text = "Normal";
	GlobalVariables::TempAlarmsStatusLabels[CheckBoxTag]->ForeColor = System::Drawing::Color::White;

	// Nulstil temperatur Alarmens Trigger status
	AlarmsTriggerStatusArray[CheckBoxTag] = false;

}

void RMH_ThermalViewer_UpdateTempAlarmsStatusLabels() {

	// Routinen opdaterer temperatur alarmens status label afhængigt af det triggerede stadie

	// Loop til og med det maksimale antal aktive temperatur alarmer
	for (unsigned int i = 0; i < _MaxNumberOfConfigurableTempAlarms; i++) {

		// Er valgte temperatur Alarmen aktiverede
		if (EnabledTempAlarmsArray[i] == true) {

			// Kontroller om den valgte temperatur alarm er blevet triggerede
			if (AlarmsTriggerStatusArray[i] == true) {

				// Opdater temperatur alarmens status Label string og farve
				GlobalVariables::TempAlarmsStatusLabels[i]->Text = "Triggered!";
				GlobalVariables::TempAlarmsStatusLabels[i]->ForeColor = System::Drawing::Color::Red;

			}
			else {

				// Opdater temperatur alarmens status Label string og farve
				GlobalVariables::TempAlarmsStatusLabels[i]->Text = "Normal";
				GlobalVariables::TempAlarmsStatusLabels[i]->ForeColor = System::Drawing::Color::White;

			}

		}

	}

}

void RMH_ThermalViewer_ReadTemperatureAlarmStatus(unsigned char TemperatureAlarmIndex, double TemperatureAlarmSourcePointer) {

	// Routinen kontroller om en aktiv temperatur alarm er blevet triggerede

	// Er valgte temperatur Alarmen aktiverede
	if (EnabledTempAlarmsArray[TemperatureAlarmIndex] == true) {

		// Kontroller temperatur alarmens type
		switch (TempAlarmsConfigType[TemperatureAlarmIndex]) {

			// Temperatur alarmen er en "Trigger Above Temp" Type Alarm
			case _TempAlarmType_Above: 

				// Kontroller om temperatur alarmens source data er højere end alarmens High Set Punkt
				if (TemperatureAlarmSourcePointer >= TempAlarmsHighTempValues[TemperatureAlarmIndex]) {

					// Opdater temperatur alarmens trigger status
					AlarmsTriggerStatusArray[TemperatureAlarmIndex] = true;

				}
				else {

					// Opdater temperatur alarmens trigger status
					AlarmsTriggerStatusArray[TemperatureAlarmIndex] = false;

				}
				
			break;

			// Temperatur alarmen er en "Trigger Below Temp" Type Alarm
			case _TempAlarmType_Below: 

				// Kontroller om temperatur alarmens source data er lavere end alarmens Low Set Punkt
				if (TemperatureAlarmSourcePointer <= TempAlarmsLowTempValues[TemperatureAlarmIndex]) {

					// Opdater temperatur alarmens trigger status
					AlarmsTriggerStatusArray[TemperatureAlarmIndex] = true;

				}
				else {

					// Opdater temperatur alarmens trigger status
					AlarmsTriggerStatusArray[TemperatureAlarmIndex] = false;

				}
				
			break;

			// Temperatur alarmen er en "Temp Window Trigger" Type Alarm
			case _TempAlarmType_Window:

				// Kontroller om temperatur alarmens source data er inden for det indstillede temperatur vindue
				if (TemperatureAlarmSourcePointer > TempAlarmsLowTempValues[TemperatureAlarmIndex] && TemperatureAlarmSourcePointer < TempAlarmsHighTempValues[TemperatureAlarmIndex]) {

					// Opdater temperatur alarmens trigger status
					AlarmsTriggerStatusArray[TemperatureAlarmIndex] = false;

				}
				else {

					// Opdater temperatur alarmens trigger status
					AlarmsTriggerStatusArray[TemperatureAlarmIndex] = true;

				}
	
			break;

		}

	}

}

void RMH_ThermalViewer_MonitorEnabledTempAlarmsStatus() {

	// Routinen kontroller det triggerede stadie for de aktive temperatur alarmer

	// Læs og opdater temperatur alarmernes staus
	RMH_ThermalViewer_ReadTemperatureAlarmStatus(_TemperatureAlarm_1, *TempAlarm1DataSourcePointer);
	RMH_ThermalViewer_ReadTemperatureAlarmStatus(_TemperatureAlarm_2, *TempAlarm2DataSourcePointer);
	RMH_ThermalViewer_ReadTemperatureAlarmStatus(_TemperatureAlarm_3, *TempAlarm3DataSourcePointer);
	RMH_ThermalViewer_ReadTemperatureAlarmStatus(_TemperatureAlarm_4, *TempAlarm4DataSourcePointer);
	RMH_ThermalViewer_ReadTemperatureAlarmStatus(_TemperatureAlarm_5, *TempAlarm5DataSourcePointer);

}

void RMH_ThermalViewer_OpdateTempAlarmTriggerSoundTimer(System::Object^ sender) {

	// Routinen aktiverer eller deaktiverer temperatur alarmernes advarsels lyds timer

	// Cast Sender objekt som Forms CheckBox objekt
	System::Windows::Forms::CheckBox^ CheckBox = (System::Windows::Forms::CheckBox^)sender;

	// Kontroller om alarmernes advarsels lyd skal aktiveres
	if (CheckBox->Checked == true) {

		// Opdater temperatur alarmernes advarsels lyds timer aktive stadie
		TempAlarmTriggerSoundFlag = true;

		// Aktiver temperatur alarmernes advarsels lyds timer
		GlobalVariables::GlobalAlarmSoundTimer->Enabled = true;

	}
	else {

		// Opdater temperatur alarmernes advarsels lyds timer aktive stadie
		TempAlarmTriggerSoundFlag = false;

		// Deaktiver temperatur alarmernes advarsels lyds timer
		GlobalVariables::GlobalAlarmSoundTimer->Enabled = false;

	}
	
}

void RMH_ThermalViewer_AlarmSoundTimerTickEventHandler() {

	// Routinen håndterer trigger events for temperatur alarmernes advarsels lyds timer 

	// Er temperatur alarmernes advarsels lyd aktiverede
	if (TempAlarmTriggerSoundFlag == true) {

		// Kontroller om der er alarmer som er blevet triggerede
		if (AlarmsTriggerStatusArray[_TemperatureAlarm_1] == true ||
			AlarmsTriggerStatusArray[_TemperatureAlarm_2] == true ||
			AlarmsTriggerStatusArray[_TemperatureAlarm_3] == true ||
			AlarmsTriggerStatusArray[_TemperatureAlarm_4] == true ||
			AlarmsTriggerStatusArray[_TemperatureAlarm_5] == true) {

			// Afspil Alarm advarsels lyd
			System::Media::SystemSounds::Hand->Play();

		}

	}

}

void RMH_ThermalViewer_EnableAlarmTriggerEvents(System::Object^ sender) {

	// Routinen aktiverer Temperatur alarmernes trigger events

	// Cast Sender objekt som Forms CheckBox objekt
	System::Windows::Forms::CheckBox^ CheckBox = (System::Windows::Forms::CheckBox^)sender;

	// Opdater temperatur alarmernes trigger event aktiverings flag
	TempAlarmsTriggerEventsEnableFlag = (bool)CheckBox->Checked;

	// Kontroller stadiet for checkbox
	if (TempAlarmsTriggerEventsEnableFlag == true) {

		// Konfigurer trigger timer interval 
		GlobalVariables::GlobalAlarmTriggerEventTimer->Interval = (unsigned int)(GlobalVariables::GlobalAlarmTriggerEventsIntervalUpDown->Value * 1000);

		// Aktiver temperatur alarmernes trigger event timer
		GlobalVariables::GlobalAlarmTriggerEventTimer->Enabled = true;

	}
	else {

		// Deaktiver temperatur alarmernes trigger event timer
		GlobalVariables::GlobalAlarmTriggerEventTimer->Enabled = false;

	}

}

void RMH_ThermalViewer_UpdateAlarmsTriggerEventResetButtonsBorderColor(unsigned char TemperatureAlarmIndex, bool TriggerEventExecutedFlag) {

	// Routinen opdaterer Border Farven for "Trigger event er blevet eksikverede" status knapperne

	// Valg af temperatur alarm Index
	switch (TemperatureAlarmIndex) {

		// Opdater Temperatur alarm 1 knappen Border Farve
		case _TemperatureAlarm_1:  

			// Er temp alarmens trigger event blevet eksikveret
			if (TriggerEventExecutedFlag == true) {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm1TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

			}
			else {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm1TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

			}
				
		break;

		// Opdater Temperatur alarm 2 knappen Border Farve
		case _TemperatureAlarm_2:

			// Er temp alarmens trigger event blevet eksikveret
			if (TriggerEventExecutedFlag == true) {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm2TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

			}
			else {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm2TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

			}

		break;

		// Opdater Temperatur alarm 3 knappen Border Farve
		case _TemperatureAlarm_3:

			// Er temp alarmens trigger event blevet eksikveret
			if (TriggerEventExecutedFlag == true) {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm3TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

			}
			else {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm3TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

			}

		break;

		// Opdater Temperatur alarm 4 knappen Border Farve
		case _TemperatureAlarm_4:

			// Er temp alarmens trigger event blevet eksikveret
			if (TriggerEventExecutedFlag == true) {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm4TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

			}
			else {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm4TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

			}

		break;

		// Opdater Temperatur alarm 5 knappen Border Farve
		case _TemperatureAlarm_5:

			// Er temp alarmens trigger event blevet eksikveret
			if (TriggerEventExecutedFlag == true) {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm5TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

			}
			else {

				// Opdater Knap Border Farve
				GlobalVariables::GlobalAlarm5TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

			}

		break;

	}

}

void RMH_ThermalViewer_ResetAlarmTriggerEventExecutedFlag(System::Object^ sender) {

	// Routinen nulstiller "Trigger event er blevet eksikverede" flaget for læste alarm tag

	// Cast Sender objekt som Forms Button objekt
	System::Windows::Forms::Button^ TriggerResetButton = (System::Windows::Forms::Button^)sender;

	// Læs trykkede Knaps identifikations tag
	unsigned int TriggerEventResetButtonTag = Convert::ToInt32(TriggerResetButton->Tag);

	// Nulstil "Trigger event er blevet eksikverede" flaget for tilhørende temp alarm
	TriggerEventExecutedFlag[TriggerEventResetButtonTag] = false;

	// Opdater Tilhørene trigger event reset knap border farvve
	RMH_ThermalViewer_UpdateAlarmsTriggerEventResetButtonsBorderColor(TriggerEventResetButtonTag, TriggerEventExecutedFlag[TriggerEventResetButtonTag]);

}

void RMH_ThermalViewer_HandleTempAlarmTriggerActionEvent(unsigned char TemperatureAlarmIndex) {

	// Routinen håndterer trigger aktions eventet for en triggerede alarm

	// Kontroller om den valgte temperatur alarm er aktiverede
	if (EnabledTempAlarmsArray[TemperatureAlarmIndex] == true) {

		// Kontroller Om Termperatur Alarmen er blevet triggeret
		if (AlarmsTriggerStatusArray[TemperatureAlarmIndex] == true) {

			// Eksikver Kun trigger Event Hvis den ikke allerede har været triggerede
			// Eller hvis trigger Event "Er Blevet Eksikverede" flaget er 'false'
			if (TriggerEventExecutedFlag[TemperatureAlarmIndex] == false) {

				// Kontroller Alarment Trigger aktion konfiguration
				switch (TempAlarmsTriggerAction[TemperatureAlarmIndex]) {

					// -------------------------------------------------------------------------- //

					// Eksikver alarm trigger aktion
					case _TempAlarmTriggerAction_None: break;

					// -------------------------------------------------------------------------- //

					case _TempAlarmTriggerAction_StartDataLogging:

						// Start Temperatur Data Logging Session
						RMH_ThermalViewer_StartDataLogging();

					break;

					// -------------------------------------------------------------------------- //

					case _TempAlarmTriggerAction_StopDataLogging:

						// Stop Temperatur Data Logging Session
						RMH_ThermalViewer_StopDataLogging();

					break;

					// -------------------------------------------------------------------------- //

					case _TempAlarmTriggerAction_StartVideoRecording:

						// Opdater Video optagnings flag - Start Optagning
						VideoRecordingStartedFlag = true;
						// Start Video Optagning
						RMH_ThermalViewer_StartStopVideoRecording();

					break;

					// -------------------------------------------------------------------------- //

					case _TempAlarmTriggerAction_StopVideoRecording:

						// Opdater Video optagnings flag - Stop Optagning
						VideoRecordingStartedFlag = false;
						// Stop Video Optagning
						RMH_ThermalViewer_StartStopVideoRecording();

					break;

					// -------------------------------------------------------------------------- //

					case _TempAlarmTriggerAction_SaveSnapshot:

						// Gem et live view snapshot
						RMH_ThermalViewer_SaveLiveViewSnapshot();

					break;

					// -------------------------------------------------------------------------- //

					case _TempAlarmTriggerAction_SaveFullFrameTempData:

						// Generer og Gem en Fuld Frame Temperatur Data CSV fil
						RMH_ThermalViewer_SaveFullFrameTemperatureDataToCSVFile();

					break;

					// -------------------------------------------------------------------------- //

				}

				// Opdater Alarm Trigger Event "Er Blevet Eksikverede" Flag
				TriggerEventExecutedFlag[TemperatureAlarmIndex] = true;

				// Opdater Tilhørene trigger event reset knap border farvve
				RMH_ThermalViewer_UpdateAlarmsTriggerEventResetButtonsBorderColor(TemperatureAlarmIndex, TriggerEventExecutedFlag[TemperatureAlarmIndex]);

			}

		}

	}

}

void RMH_ThermalViewer_AlarmTriggerEventTimerTickEventHandler() {

	// Routinen håndterer trigger events for temperatur alarmernes trigger event timer 

	// Eksikver trigger events for aktive temperatur alarmer
	RMH_ThermalViewer_HandleTempAlarmTriggerActionEvent(_TemperatureAlarm_1);
	RMH_ThermalViewer_HandleTempAlarmTriggerActionEvent(_TemperatureAlarm_2);
	RMH_ThermalViewer_HandleTempAlarmTriggerActionEvent(_TemperatureAlarm_3);
	RMH_ThermalViewer_HandleTempAlarmTriggerActionEvent(_TemperatureAlarm_4);
	RMH_ThermalViewer_HandleTempAlarmTriggerActionEvent(_TemperatureAlarm_5);

}

// ------------------- General Og Periodisk Trigger Håndterings Routiner -------------------- //

void RMH_ThermalViewer_TogglePeriodicTriggerTimer() {

	// Routinen aktiverer eller deaktiverer den periodiske trigger timer

	// Toggle den periodiske trigger timers aktiverings flag
	PeriodicTriggerTimerEnableFlag = !PeriodicTriggerTimerEnableFlag;

	// Hvis Live View streamen er i STOP Mode
	if (LiveViewRunStopFlag == false) {

		// Nulstil den periodiske trigger timers aktiverings flag
		PeriodicTriggerTimerEnableFlag = false;

	}

	// Håndter nyt stadie for aktiverings flag
	if (PeriodicTriggerTimerEnableFlag == true) {

		// Aktiver den periodiske trigger timer
		GlobalVariables::GlobalPeriodicTriggerTimer->Enabled = true;

		// Indstil Trigger timerens eksikverings interval
		GlobalVariables::GlobalPeriodicTriggerTimer->Interval = 1000;

		// Opdater Knap Border Farve
		GlobalVariables::GlobalPeriodicTimerTriggerButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Deaktiver den periodiske trigger timer
		GlobalVariables::GlobalPeriodicTriggerTimer->Enabled = false;

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalPeriodicTimerTriggerButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

}

void RMH_ThermalViewer_EnableDisableSelectedPeriodicTriggerEvent(System::Object^ sender) {

	// Routinen aktiverer eller deaktiverer valgte Periodiske Trigger Event 

	// Cast Sender objekt som Forms CheckBox objekt
	System::Windows::Forms::CheckBox^ CheckBoxTag = (System::Windows::Forms::CheckBox^)sender;

	// Læs valgte CheckBox identifikations tag
	unsigned int TriggerEventResetButtonTag = Convert::ToInt32(CheckBoxTag->Tag);

	// Aktiver eller deaktiver valgte Periodiske trigger event
	PeriodicTriggerEventEnableFlags[TriggerEventResetButtonTag] = GlobalVariables::GlobalPeriodicEventnEnableCheckBox[TriggerEventResetButtonTag]->Checked;

	// Hvis den periodiske trigger timer er blevet aktiverede
	if (GlobalVariables::GlobalPeriodicEventnEnableCheckBox[TriggerEventResetButtonTag]->Checked == true) {

		// Deaktiver tilhørende konfigurations GUI elementer
		GlobalVariables::GlobalPeriodicEventnComboBox[TriggerEventResetButtonTag]->Enabled = false;
		GlobalVariables::GlobalPeriodicEventIntervalnUpDown[TriggerEventResetButtonTag]->Enabled = false;
		GlobalVariables::GlobalPeriodicEventnDisableCheckBox[TriggerEventResetButtonTag]->Enabled = false;

	}
	else {

		// Aktiver tilhørende konfigurations GUI elementer
		GlobalVariables::GlobalPeriodicEventnComboBox[TriggerEventResetButtonTag]->Enabled = true;
		GlobalVariables::GlobalPeriodicEventIntervalnUpDown[TriggerEventResetButtonTag]->Enabled = true;
		GlobalVariables::GlobalPeriodicEventnDisableCheckBox[TriggerEventResetButtonTag]->Enabled = true;

	}

}

void RMH_ThermalViewer_DisablePeriodicTriggerEventIndex(unsigned int PeriodicTriggerEvent) {

	// Routinen deaktiverer valgte Periodiske Trigger Event 

	/*
	
		Tilhørende Macroer ->

		// Periodiske Trigger Event Nummer Macroer
		#define _PeriodicTriggerEvent_1                               0
		#define _PeriodicTriggerEvent_2                               1
		#define _PeriodicTriggerEvent_3                               2
		#define _PeriodicTriggerEvent_4                               3
		#define _PeriodicTriggerEvent_5                               4
	
	*/

	// Deaktiver valgte Periodiske trigger event
	PeriodicTriggerEventEnableFlags[PeriodicTriggerEvent] = false;
	GlobalVariables::GlobalPeriodicEventnEnableCheckBox[PeriodicTriggerEvent]->Checked = false;

}

void RMH_ThermalViewer_ExecuteTriggerEventIndex(unsigned short TriggerEventFunction) {

	// Routinen eksikverer valgte trigger event funktion fra givet event funktions index

	// Kontroller Hvilken periodisk trigger event funktion er blevet indstillet
	switch (GlobalVariables::GlobalPeriodicEventnComboBox[TriggerEventFunction]->SelectedIndex) {

		// -------------------------------------------------------------------------- //

		// Eksikver tilhørende periodisk trigger event funktion
		case _TriggerEventFunction_None: 
			
			// Deaktiver valgte Periodiske Trigger Event 
			RMH_ThermalViewer_DisablePeriodicTriggerEventIndex(TriggerEventFunction);

		break;

		// Eksikver tilhørende periodisk trigger event funktion
		case _TriggerEventFunction_StartDataLogging:

			// Start Temperatur Data Logging Session
			RMH_ThermalViewer_StartDataLogging();

		break;

		// Eksikver tilhørende periodisk trigger event funktion
		case _TriggerEventFunction_StopDataLogging:

			// Stop Temperatur Data Logging Session
			RMH_ThermalViewer_StopDataLogging();

		break;

		// Eksikver tilhørende periodisk trigger event funktion
		case _TriggerEventFunction_StartVideoRecording:

			// Opdater Video optagnings flag - Start Optagning
			VideoRecordingStartedFlag = true;
			// Start Video Optagning
			RMH_ThermalViewer_StartStopVideoRecording();

		break;

		// Eksikver tilhørende periodisk trigger event funktion
		case _TriggerEventFunction_StopVideoRecording:

			// Opdater Video optagnings flag - Stop Optagning
			VideoRecordingStartedFlag = false;
			// Stop Video Optagning
			RMH_ThermalViewer_StartStopVideoRecording();

		break;

		// Eksikver tilhørende periodisk trigger event funktion
		case _TriggerEventFunction_SaveSnapshot:

			// Gem et live view snapshot
			RMH_ThermalViewer_SaveLiveViewSnapshot();

		break;

		// Eksikver tilhørende periodisk trigger event funktion
		case _TriggerEventFunction_SaveFullFrameTempData:

			// Generer og Gem en Fuld Frame Temperatur Data CSV fil
			RMH_ThermalViewer_SaveFullFrameTemperatureDataToCSVFile();

		break;

		// -------------------------------------------------------------------------- //

	}

}

void RMH_ThermalViewer_ExecuteSelectedPeriodicTriggerEvent(unsigned int PeriodicTriggerEvent) {

	// Routinen eksikverer konfigureret periodiske trigger event, hvis aktiverede.

	/*

		Tilhørende Macroer ->

		// Periodiske Trigger Event Nummer Macroer
		#define _PeriodicTriggerEvent_1                               0
		#define _PeriodicTriggerEvent_2                               1
		#define _PeriodicTriggerEvent_3                               2
		#define _PeriodicTriggerEvent_4                               3
		#define _PeriodicTriggerEvent_5                               4

	*/

	// Kontroller om valgte periodiske trigger event er aktiverede
	if (PeriodicTriggerEventEnableFlags[PeriodicTriggerEvent] == true) {

		// Inkrementer valgte periodiske trigger events Time-Out tæller varaibel
		PeriodicEventTriggerCounter[PeriodicTriggerEvent] = PeriodicEventTriggerCounter[PeriodicTriggerEvent] + 1;

		// Kontroller om valgte periodiske trigger event har nået sin indstillede interval værdi
		if (PeriodicEventTriggerCounter[PeriodicTriggerEvent] >= GlobalVariables::GlobalPeriodicEventIntervalnUpDown[PeriodicTriggerEvent]->Value) {

			// Nulstil valgte periodiske trigger events Time-Out tæller varaibel
			PeriodicEventTriggerCounter[PeriodicTriggerEvent] = 0;

			// Eksikver indstillede periodiske trigger event funktion
			RMH_ThermalViewer_ExecuteTriggerEventIndex(PeriodicTriggerEvent);

			// Kontroller om trigger event eksikveringen skal nulstilles efter første eksikvering
			if (GlobalVariables::GlobalPeriodicEventnDisableCheckBox[PeriodicTriggerEvent]->Checked == true) {

				// Deaktiver valgte Periodiske Trigger Event 
				RMH_ThermalViewer_DisablePeriodicTriggerEventIndex(PeriodicTriggerEvent);

			}

		}

	}
	else {

		// Nulstil valgte periodiske trigger events Time-Out tæller varaibel
		PeriodicEventTriggerCounter[PeriodicTriggerEvent] = 0;

	}

}

void RMH_ThermalViewer_PeriodicTriggerEventTimerTickEventHandler() {

	// Routinen håndterer events for den periodiske trigger event timer 

	// Eksikver alle aktiverede periodiske trigger event funktioner
	RMH_ThermalViewer_ExecuteSelectedPeriodicTriggerEvent(_PeriodicTriggerEvent_1);
	RMH_ThermalViewer_ExecuteSelectedPeriodicTriggerEvent(_PeriodicTriggerEvent_2);
	RMH_ThermalViewer_ExecuteSelectedPeriodicTriggerEvent(_PeriodicTriggerEvent_3);
	RMH_ThermalViewer_ExecuteSelectedPeriodicTriggerEvent(_PeriodicTriggerEvent_4);
	RMH_ThermalViewer_ExecuteSelectedPeriodicTriggerEvent(_PeriodicTriggerEvent_5);
	
	// Kontroller om alle trigger events er deaktiverede
	if (PeriodicTriggerEventEnableFlags[_PeriodicTriggerEvent_1] == false &&
		PeriodicTriggerEventEnableFlags[_PeriodicTriggerEvent_2] == false &&
		PeriodicTriggerEventEnableFlags[_PeriodicTriggerEvent_3] == false &&
		PeriodicTriggerEventEnableFlags[_PeriodicTriggerEvent_4] == false &&
		PeriodicTriggerEventEnableFlags[_PeriodicTriggerEvent_5] == false) {

		// Deaktiver Periodiske Trigger Events
		PeriodicTriggerTimerEnableFlag = true;
		RMH_ThermalViewer_TogglePeriodicTriggerTimer();

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "No Periodic Trigger Events Are Enabled...", _StatusMessageType_Warning);

	}

}

// ---------------------- Emissivity Tabel Skærm Håndterings Routiner ----------------------- //

void RMH_ThermalViewer_LoadEmissivisyTableValueToThermalCamera(System::Windows::Forms::DataGridViewCellEventArgs^ e) {

	// Routinen indlæser den valgte emissivity tabel værdi til det termiske kamera og opdaterer tilhørende GUI elementer

	// Lokale variabler
	float DataGridViewRowIndex;
	bool SetNewEmissivityConfigFlag = true;

	// Læs hvilken Row celle er blevet trykket 
	DataGridViewRowIndex = e->RowIndex;

	// Kontroller for minimalt emissivity tabel index 
	if (DataGridViewRowIndex < 0.0) {

		// Indstil til mindst tilladte emissivity tabel index 
		DataGridViewRowIndex = 0;

		// Opdater Ny Emissivity Config Flag
		SetNewEmissivityConfigFlag = false;

	}

	// Kontroller for maksimal emissivity tabel index 
	if (DataGridViewRowIndex >= _EmissivityTableNumberOfElements) {

		// Indstil til maksimale tilladte emissivity tabel index 
		DataGridViewRowIndex = _EmissivityTableNumberOfElements - 1;

		// Opdater Ny Emissivity Config Flag
		SetNewEmissivityConfigFlag = false;

	}

	// Skal En ny Emissivity konfiguration skrives til kameraet
	if (SetNewEmissivityConfigFlag == true) {

		// Skriv valgte Emissivity værdi til "Thermal Camera Configuration" Menu UpDown
		GlobalVariables::CameraConfigNumericUpDowns[4]->Value = (System::Decimal)MaterialEmissivityValues[(unsigned int)DataGridViewRowIndex];

		// Skriv/Sæt de indstillede Kamera konfigurations parametere til kamera hukommelse
		RMH_ThermalViewer_SetCameraConfigParameters();

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Material Sellected: " + EmissivityMaterialNames[(unsigned int)DataGridViewRowIndex], _StatusMessageType_Normal);
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Material Emissivity: " + RMH_Conversion_FloatToStdString(MaterialEmissivityValues[(unsigned int)DataGridViewRowIndex], 2), _StatusMessageType_Normal);
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "New Emissivity Value Has Been Set!", _StatusMessageType_Success);

	}

}

// --------------------- Kamera Auto Kalibrerings Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_ToggleCameraAutoShutterCalibrationTimer() {

	// Routinen aktiverer eller deaktiverer auto kalibrerings feature timeren

	// Toggle Auto kalibrerings aktiverings flag
	AutoShutterCalEnableFlag = !AutoShutterCalEnableFlag;

	// Skal Automatisk shutter kalibrering aktiveres eller deaktiveres
	if (AutoShutterCalEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalAutoShutterCalButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

		// Konfigurer timer perioden
		GlobalVariables::GlobalAutoCalTimer->Interval = ((unsigned int)GlobalVariables::GlobalAutoCalPeriodUpDown->Value) * 1000;

		// Aktiver auto kalibrerings timer
		GlobalVariables::GlobalAutoCalTimer->Enabled = true;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Automatic Shutter Calibration Is Enabled", _StatusMessageType_Success);

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalAutoShutterCalButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

		// Deaktiver auto kalibrerings timer
		GlobalVariables::GlobalAutoCalTimer->Enabled = false;

	}

	// Opdater knap grafik
	GlobalVariables::GlobalAutoShutterCalButton->Refresh();

}

void RMH_ThermalViewer_ToggleCameraDriftBasedCalibrationTimer() {

	// Routinen aktiverer eller deaktiverer Temperatur Drift Baserede kalibrerings featuren 

	// Toggle Temperatur Drift Baserede kalibrerings aktiverings flag
	DriftBasedCalEnableFlag = !DriftBasedCalEnableFlag;

	// Skal Temperatur Drift Baserede kalibrering aktiveres eller deaktiveres
	if (DriftBasedCalEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalSensorDriftCalButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

		// Konfigurer timer perioden
		GlobalVariables::GlobalDriftCalTimer->Interval = 2000;

		// Aktiver auto kalibrerings timer
		GlobalVariables::GlobalDriftCalTimer->Enabled = true;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Drift Base Calibration Is Enabled", _StatusMessageType_Success);

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalSensorDriftCalButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

		// Deaktiver auto kalibrerings timer
		GlobalVariables::GlobalDriftCalTimer->Enabled = false;

	}

	// Opdater knap grafik
	GlobalVariables::GlobalAutoShutterCalButton->Refresh();

}

void RMH_ThermalViewer_ReadThermalCameraInternalTemps() {

	// Routinen læser og viser kameraets interne Detektor, Core og Shutter temperaturer

	// Lokale variabler
	float CameraDetectorTemp = (IRCamera.temp_fpa * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
	float CameraCoreTemp = (IRCamera.temp_core * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
	float CameraShutterTemp = (IRCamera.temp_shutter * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
	
	// Opdater Kameraets interne temperatur labels
	GlobalVariables::GlobalCameraDetectorTempLabel->Text = "Camera Detector: " + CameraDetectorTemp.ToString("F3") + GlobalVariables::DefaultTempUnitString;
	GlobalVariables::GlobalCameraCoreTempLabel->Text = "Camera Core: " + CameraCoreTemp.ToString("F3") + GlobalVariables::DefaultTempUnitString;
	GlobalVariables::GlobalCameraShutterTempLabel->Text = "Camera Shutter: " + CameraShutterTemp.ToString("F3") + GlobalVariables::DefaultTempUnitString;

}

// ---------------- Kamera Afbrydelses Eller Mode Skift Håndterings Routiner ---------------- //

void RMH_ThermalViewer_HandleSellectedDeviceOrModeChange() {

	// Routinen håndterer handlingerne ved ændring af Kamera source ComboBox Item

	// ----------------------------------- Nulstil Temperatur Range stadier ----------------------------------- //

	// Nulstil Termiske kamera High-Range Flag
	ThermalCameraHighRangeFlag = false;

	// Opdater Temperatur Range Knap border farve
	GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	// Opdater IR Kamera Device Temperatur Range variabel
	IRCamera.CurrentIRTempRangeFlag = 1;

	// -------------------------------------------------------------------------------------------------------- //

	// Deaktiver Kamera konfigurations GUI komponenter
	RMH_ThermalViewer_EnableCameraConfigurationControls(false);

	// Nulstil Auto kalibrerings aktiverings flag - Falsk efter tilhørende routine eksikvering
	AutoShutterCalEnableFlag = true;
	// Deaktiver Automatisk shutter kalibrerings feature timeren
	RMH_ThermalViewer_ToggleCameraAutoShutterCalibrationTimer();
	// Deaktiver Auto Shutter kalibration knap i indstillings menuen
	GlobalVariables::GlobalAutoShutterCalButton->Enabled = false;

	// Deaktiver Kamera Disconnect Knap
	GlobalVariables::GlobalDisconnectButton->Enabled = false;
	// Deaktiver Kalibrerings knap i Live View Tools Panel
	GlobalVariables::GlobalCalibrateCameraButton->Enabled = false;
	// Deaktiver Temperatur Drift Baseret kalibration knap i indstillings menuen
	GlobalVariables::GlobalSensorDriftCalButton->Enabled = false;
	// Deaktiver Temperatur Range knap i Live View Tools Panel
	GlobalVariables::GlobalTempRangeButton->Enabled = false;
	// Deaktiver Recording Knap i Live View Tools Panel
	GlobalVariables::GlobalRecordingButton->Enabled = false;

	// Kontroller om Video Playback Formen er åben
	if (VideoPlaybackControlsFormIsOpenFlag == true) {

		// Deaktiver Play, Frem og tilbage knapperne
		GlobalVariables::VideoPlaybackForwardStepButton->Enabled = false;
		GlobalVariables::VideoPlaybackBackwardStepButton->Enabled = false;
		GlobalVariables::VideoPlaybackPlayStopButton->Enabled = false;

	}

	// Loop igennem hele arrayet af Main Form GUIens Menu knapper
	for (unsigned int i = 0; i < GlobalVariables::MainGUILeftMenuButtons->Length; i++) {

		// Deaktiver Main GUI Formens Venstra menu knapper - Untagen "Settings" Menu Knappen
		GlobalVariables::MainGUILeftMenuButtons[i]->Enabled = false;

	}

	// Deaktiver GUI update timer
	GlobalVariables::GlobalMainGUIUpdateTimer->Enabled = false;
	GlobalVariables::GlobalMainGUIUpdateTimer->Stop();

	// Kontroller om et kamera var forbundet
	if (IRCamera.ConnectedFlag == true) {
		// Skriv GUI Status Meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Has Been Disconnected And The Video Stream Has Stopped!", _StatusMessageType_Normal);
	}

	// Nulstil Kamera "isStreaming" status flag
	IRCamera.isStreaming = false;
	// Opdater Kamera Connect status flag
	IRCamera.ConnectedFlag = false;

	// Kun hvis "Recording Analysis" Mode ikke er aktiv
	if (InRecordingAnalysisModeFlag == false && InSnapShotAnalysisModeFlag == false) {

		// Stop Kamera video capturing
		RMH_IRThermalCamera_StopCapturing();
		// Stop Video Capture og luk for kameraet - hvis et kamera er aktivt
		RMH_IRThermalCamera_CloseIRCameraDevice();

	}

	// Er "SnapShot Analysis" Mode valgt
	if (GlobalVariables::GlobalCameraSourceDropList->SelectedIndex == _SnapShotAnalysisMode) { 

		// Opdater Connect Knap Label Text
		GlobalVariables::GlobalConnectButton->Text = L"Click To\r\nBrowse And Open\r\nSnapShot File";
		// Opdater Connect Knap border farve 
		GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}
	else if (GlobalVariables::GlobalCameraSourceDropList->SelectedIndex == _RecordingAnalysisMode) { // Er "Recording Analysis" Mode valgt

		// Opdater Connect Knap Label Text
		GlobalVariables::GlobalConnectButton->Text = L"Click To\r\nBrowse And Open\r\nVideo File";
		// Opdater Connect Knap border farve 
		GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}
	else {

		// Nulstil Connect Knap Label Text
		GlobalVariables::GlobalConnectButton->Text = L"Connect";
		// Opdater Connect Knap border farve 
		GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Luk "Recording Analysis" Mode video fil, hvis den er åben
	RMH_VideoFileReading_CloseRecordingAnalysisModeFile();

	// Hvis "Recording Analysis" Mode er aktic
	if (InRecordingAnalysisModeFlag == true) {

		// Luk for video playback controls panel formen
		CloseVideoPlayBackControlsFormFlag = true;

	}

	// Nulstil "Er i Recording Analysis Mode" flaget
	InRecordingAnalysisModeFlag = false;
	// Nulstil "Er i SnapShot Analysis Mode" flaget
	InSnapShotAnalysisModeFlag = false;

}

void RMH_ThermalViewer_HandleCameraDisconnectedEvents(bool ShowStatusMEssageFlag) {

	// Routinen håndterer events når kamera forbindelsen bliver afbrudt under video streaming

	// Skal ikke fortages i "Recording Analysis" Mode og "SnapShot Analysis" Mode
	if (InRecordingAnalysisModeFlag == false && InSnapShotAnalysisModeFlag == false) {

		// Kontroller om kamera forbindelsen blev afbrudt
		if (RMH_IRThermalCamera_CheckForCameraDisconnection()) {

			// Skriv GUI Status Meddelse
			if (ShowStatusMEssageFlag == true) { RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Connection To The Thermal Camera Was Lost!", _StatusMessageType_Error); }

			// Håndter GUI stadie ved tabt kamera forbindelse eller "Mode" skift
			RMH_ThermalViewer_HandleSellectedDeviceOrModeChange();

		}

	}

}

// --------------------- Kamera Temperatur Enheds Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_ChangeTemperatureUnit(System::Object^ sender) {

	// Routinen håndterer temperatur enheds knapperne, som et nested callbak for alle tre knapper.
	// Routinen håndterer ligeledes events og handlinger ved skift af temperatur enheden, for alle temperature målinger.

	// Cast Sender objekt som Forms Button objekt
	System::Windows::Forms::Button^ PressedTempUnitButton = (System::Windows::Forms::Button^)sender;

	// Læs trykket knaps identifikations tag
	unsigned int ButtonTag = Convert::ToInt32(PressedTempUnitButton->Tag);

	// Kontroller at ny valgte Temp enhed ikke er den nuværende
	if (TempUnitState != ButtonTag) {

		// Hvilken knap er blevet trykket - læs knap Tag
		switch (ButtonTag) {

			// Celsius Knap
			case 1:

				// Opdater knapperned Border farve
				GlobalVariables::TempUnitButtons[0]->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
				GlobalVariables::TempUnitButtons[1]->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);
				GlobalVariables::TempUnitButtons[2]->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

				// Opdater temperatur enhedens skallerings faktor fra celsius
				TemperatureUnitScaleFactor = 1.0;
				// Opdater temperatur enhedens Offset værdi fra celsius
				TemperatureUnitOffsetFactor = 0.0;

				// Opdater Temp Unit Status Oldstate
				TempUnitOldstate = TempUnitState;
				// Opdater Temp Unit Status værdi
				TempUnitState = 1;

				// Opdater Default Temperatur Enheds String
				GlobalVariables::DefaultTempUnitString = "°C";

				// Skriv GUI Start Meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Measurement Unit Changed To: Celsius.", _StatusMessageType_Normal);

			break;

			// Fahrenheit Knap
			case 2:

				// Opdater knapperned Border farve
				GlobalVariables::TempUnitButtons[0]->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);
				GlobalVariables::TempUnitButtons[1]->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
				GlobalVariables::TempUnitButtons[2]->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

				// Opdater temperatur enhedens skallerings faktor fra celsius
				TemperatureUnitScaleFactor = 1.8;
				// Opdater temperatur enhedens Offset værdi fra celsius
				TemperatureUnitOffsetFactor = 32.0;

				// Opdater Temp Unit Status Oldstate
				TempUnitOldstate = TempUnitState;
				// Opdater Temp Unit Status værdi
				TempUnitState = 2;

				// Opdater Default Temperatur Enheds String
				GlobalVariables::DefaultTempUnitString = "°F";

				// Skriv GUI Start Meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Measurement Unit Changed To: Fahrenheit.", _StatusMessageType_Normal);

			break;

			// Kelvin Knap
			case 3:

				// Opdater knapperned Border farve
				GlobalVariables::TempUnitButtons[0]->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);
				GlobalVariables::TempUnitButtons[1]->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);
				GlobalVariables::TempUnitButtons[2]->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

				// Opdater temperatur enhedens skallerings faktor fra celsius
				TemperatureUnitScaleFactor = 1.0;
				// Opdater temperatur enhedens Offset værdi fra celsius
				TemperatureUnitOffsetFactor = 273.15;

				// Opdater Temp Unit Status Oldstate
				TempUnitOldstate = TempUnitState;
				// Opdater Temp Unit Status værdi
				TempUnitState = 3;

				// Opdater Default Temperatur Enheds String
				GlobalVariables::DefaultTempUnitString = "K";

				// Skriv GUI Start Meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Measurement Unit Changed To: Kelvin.", _StatusMessageType_Normal);

			break;

		}

		// --------------- Opdater GUI elementer til valgte Temperatur enhed --------------- //

		// ----- Kamera Konfigurations Panel ----->

		// Updater Kamera konfigurations panelets NumericUpDowns Maksimale og Minimale begrænsninger
		RMH_ThermalViewer_SetCameraConfigUpDownRanges(TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

		// Opdater kamera konfigurations Numeric UpDowns parametere værdier
		RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[1], IRCamera.ReflectedTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_ReflectedTemperatureValue);
		RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[2], IRCamera.AmbientTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_AmbientTemperatureValue);

		// Opdater Kamera konfigurations panelets labels temperatur enheds string
		GlobalVariables::CameraConfigLabels[0]->Text = "Temperature Correction [" + GlobalVariables::DefaultTempUnitString + "]:";
		GlobalVariables::CameraConfigLabels[1]->Text = "Ambient Temperature [" + GlobalVariables::DefaultTempUnitString + "]:";
		GlobalVariables::CameraConfigLabels[2]->Text = "Reflected Temperature [" + GlobalVariables::DefaultTempUnitString + "]:";

		// ----- Video PlayBack Controls Panel ----->

		// Opdater Kun hvis Video Playback Formen Er Åben
		if (VideoPlaybackControlsFormIsOpenFlag == true) {

			// Opdater Video PlayBack Controls labels temperatur enheds string
			GlobalVariables::VideoPlaybackTempCorrectionLabel->Text = RMH_Conversion_FloatToSystemString(IRCamera.TemperatureCorrectionSetting) + " " + GlobalVariables::DefaultTempUnitString;
			GlobalVariables::VideoPlaybackAmbientTempLabel->Text = RMH_Conversion_FloatToSystemString(IRCamera.AmbientTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor) + " " + GlobalVariables::DefaultTempUnitString;
			GlobalVariables::VideoPlaybackReflectedTempLabel->Text = RMH_Conversion_FloatToSystemString(IRCamera.ReflectedTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor) + " " + GlobalVariables::DefaultTempUnitString;

		}

		// ------ Live View Statistik Vindue ------->
		
		// Nulstil Maksimum Peak Værdien
		MaxPeakTemperature = 0;
		// Nulstil Minimum Peak Værdien
		MinPeakTemperature = 2000.0;

		// Opdater Maksimale drift temperatur label i kalibrerings settings menu
		GlobalVariables::GlobalMaxTempDriftSetPountLabel->Text = "Maximum Drift Temperature [" + GlobalVariables::DefaultTempUnitString + "]:";

		// --------------------------------------------------------------------------------- //

	}

}

// ----------------------- Temperatur Trackings Håndterings Routiner ------------------------ //

void RMH_ThermalViewer_ReadMaxMinCentTemperatures() {

	// Routinen læser Maximum, Minimum og Center temperaturer 

	// Læs Maximum, Minimum og Center temperatur og kompenser for valg af temperatur enhed
	MaximumTemperature = (RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, IRCamera.Tmax_Tmp_Raw, IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
	MinimumTemperature = (RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, IRCamera.Tmin_Tmp_Raw, IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
	CenterTemperature = (RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, IRCamera.Center_Tmp_Raw, IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

	// Udregn/Konverter den rå Gennemsnitlige Termiske Frame Data værdi til en aktuel temperatur
	AverageTemperature = (RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, IRCamera.Tavg_Tmp_Raw, IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

}

void RMH_ThermalViewer_FormatMaximumTemperatureLabel() {

	// Routinen formaterer et tilhørende label til renderering på live view

	// Formater Maximum temperatur label til live view renderering
	GlobalVariables::MaximumTempLabel = "Max: " + MaximumTemperature.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

}

void RMH_ThermalViewer_FormatMinimumTemperatureLabel() {

	// Routinen formaterer et tilhørende label til renderering på live view

	// Formater Minimum temperatur label til live view renderering
	GlobalVariables::MinimumTempLabel = "Min: " + MinimumTemperature.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

}

void RMH_ThermalViewer_FormatCenterTemperatureLabel() {

	// Routinen formaterer et tilhørende label til renderering på live view

	// Formater Center temperatur label til live view renderering
	GlobalVariables::CenterTempLabel = "Center: " + CenterTemperature.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

}

void RMH_ThermalViewer_ReadAndFormatMouseCursorTempAndLabel() {

	// Routinen læser og formaterer et tilhørende label til Mus cursor label renderering på live view

	// Læs Mus Cursor temperaturen og kompenser for valg af temperatur enhed
	CursorTemperature = (RMH_IRThermalCamera_ReadFramePixelTemperature(&IRCamera, &FrameThermalDataRaw[0], LiveViewCursorTrackPos.CursorXPos, LiveViewCursorTrackPos.CursorYPos, IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

	// Formater Mus Cursor temperatur label til live view renderering
	GlobalVariables::MouseCursorTempLabel = "Temp: " + CursorTemperature.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

}

void RMH_ThermalViewer_ReadAndFormatROITempAndLabels() {

	// Routinen læser aktive ROI Maximum og Minimum Temperaturerne og Formaterer Tilhørende Label Strings Til Renderering

	// Lokale variabler
	unsigned short Renderindex = 0;

	// Læs temperatur og formater labels for alle aktive ROIer
	for (unsigned int i = 0; i < NumOfActiveLiveViewROIs; i++) {

		// Læs Render orden indexet
		Renderindex = ActiveROIRenderingOrder[i];

		// Læs Aktive ROI Maximum og Minimum Temperature - Samt ROI arealets Rå Pixel værdier
		ROIAreaPixelValues[Renderindex] = RMH_IRThermalCamera_ReadROIAreaPixelInfoInsideFrameArea(&IRCamera,
			&FrameThermalDataRaw[0], IRCamera.FrameWidth,
			ROIRectanglePositions[Renderindex].RectangleX0Pos,
			ROIRectanglePositions[Renderindex].RectangleY0Pos,
			ROIRectanglePositions[Renderindex].RectangleWidth,
			ROIRectanglePositions[Renderindex].RectangleHeight,
			ROIxReturnAreaRawPixelValsFlags[Renderindex], &ROIxAreaRawPixelValues[0], 
			IRCamera.ThermalCameraSupportPool);

		// Konpenser for valgte temperatur enhed
		ROIAreaPixelValues[Renderindex].MaxValue = (ROIAreaPixelValues[Renderindex].MaxValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		ROIAreaPixelValues[Renderindex].MinValue = (ROIAreaPixelValues[Renderindex].MinValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		ROIAreaPixelValues[Renderindex].AvgValue = (ROIAreaPixelValues[Renderindex].AvgValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

		// Formater ROI Maximum og Minimum temperatur label til live view renderering
		GlobalVariables::ROIMaxTempLabels[Renderindex] = "Max: " + ROIAreaPixelValues[Renderindex].MaxValue.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;
		GlobalVariables::ROIMinTempLabels[Renderindex] = "Min: " + ROIAreaPixelValues[Renderindex].MinValue.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

	}

	// Er Live View Split View aktiverede
	if (LiveViewSplitViewEnableFlag == true) {

		// Læs Zoom ROI Maximum og Minimum Temperature - Samt ROI arealets Rå Pixel værdier
		ZoomROIAreaPixelValues = RMH_IRThermalCamera_ReadROIAreaPixelInfoInsideFrameArea(&IRCamera,
			&FrameThermalDataRaw[0], IRCamera.FrameWidth,
			ZoomROIRectanglePositions.RectangleX0Pos,
			ZoomROIRectanglePositions.RectangleY0Pos,
			ZoomROIRectanglePositions.RectangleWidth,
			ZoomROIRectanglePositions.RectangleHeight,
			true, &ZoomROIxAreaRawPixelValues[0],
			IRCamera.ThermalCameraSupportPool);

		// Konpenser for valgte temperatur enhed
		ZoomROIAreaPixelValues.MaxValue = (ZoomROIAreaPixelValues.MaxValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		ZoomROIAreaPixelValues.MinValue = (ZoomROIAreaPixelValues.MinValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		ZoomROIAreaPixelValues.AvgValue = (ZoomROIAreaPixelValues.AvgValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

		// Formater Zoom ROI Maximum og Minimum temperatur label til live view renderering
		GlobalVariables::ZoomROIMaxTempLabels = "Max: " + ZoomROIAreaPixelValues.MaxValue.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;
		GlobalVariables::ZoomROIMinTempLabels = "Min: " + ZoomROIAreaPixelValues.MinValue.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

	}

}

void RMH_ThermalViewer_ReadAndFormatTempMeasurementsAndLabels() {

	// Routinen læser aktive ROI Maximum og Minimum Temperaturerne og Formaterer Tilhørende Label Strings Til Renderering

	// Lokale variabler
	unsigned short Renderindex = 0;

	// Læs temperaturer og formater labels for alle aktive temperatur målinger
	for (unsigned int i = 0; i < NumOfActiveLiveViewTempMeas; i++) {

		// Læs Render orden indexet
		Renderindex = ActiveTempMeasRenderingOrder[i];

		// Læs Aktive Temp Målings temperatur
		TempMeasurementValues[Renderindex] = RMH_IRThermalCamera_ReadFramePixelTemperature(&IRCamera, &FrameThermalDataRaw[0],
			TempMeasPositions[Renderindex].CrosshairX0Pos, TempMeasPositions[Renderindex].CrosshairY0Pos, IRCamera.ThermalCameraSupportPool);

		// Konpenser for valgte temperatur enhed
		TempMeasurementValues[Renderindex] = (TempMeasurementValues[Renderindex] * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

		// Formater temperatur målings Label string til live view renderering
		GlobalVariables::TempMeasurementsLabels[Renderindex] = TempMeasurementValues[Renderindex].ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

	}

}

void RMH_ThermalViewer_ReadAndFormatLinesMaxMinAvgTempsAndLabels() {

	// Routinen læser aktive linjers Maximum, Minimum Og Gennemsnitlig Temperaturerne og Formaterer Tilhørende Label Strings Til Renderering

	// Lokale variabler
	double LineTempValue = 0.0;
	unsigned short Renderindex = 0;
	double LineMaximumTemperature = 0.0;
	double LineMinimumTemperature = 0.0;
	double LineAverageTemperature = 0.0;
	unsigned short TempLinesPositionsXCordinates = 0;
	unsigned short TempLinesPositionsYCordinates = 0;

	// Læs Live View billeders Native Højde, Bredde Og Aspect Ratio parametere
	LiveViewNativeImageWidth = GlobalVariables::OpenGLRender->RMH_LiveView_GetNativeImageWidth();
	LiveViewNativeImageHeight = GlobalVariables::OpenGLRender->RMH_LiveView_GetNativeImageHeight();
	LiveViewNativeImageAspectRatio = GlobalVariables::OpenGLRender->RMH_LiveView_GetNativeImageAspectRatio();

	// Læs temperaturer og formater labels for alle aktive temperatur linjer
	for (unsigned int i = 0; i < NumOfActiveLiveViewLines; i++) {

		// Læs Render orden indexet
		Renderindex = ActiveTempLineRenderingOrder[i];

		// Indstil Maximum og Minimums værdier til Absolut Max/Min
		LineMaximumTemperature = -10000;
		LineMinimumTemperature = 10000;

		// Linjens gennemsnitlige temperatur værdi
		LineAverageTemperature = 0.0;

		// Læs temperatur linjens Maximum og minimum temperaturer
		for (unsigned int j = 0; j < TempLinesPositions[Renderindex].LinePixelLength; j++) {

			// Kontroller Live View Roterings Indstillingen
			if (GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation() == 0) {

				// Læs Temperatur Linjernes X/Y Positions Koordinater
				TempLinesPositionsXCordinates = TempLinesPositions[Renderindex].LineXCordinates[j];
				TempLinesPositionsYCordinates = TempLinesPositions[Renderindex].LineYCordinates[j];

			}
			if (GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation() == 90) {

				// Læs Temperatur Linjernes X/Y Positions Koordinater
				TempLinesPositionsXCordinates = LiveViewNativeImageWidth - TempLinesPositions[Renderindex].LineYCordinates[j] * LiveViewNativeImageAspectRatio;
				TempLinesPositionsYCordinates = TempLinesPositions[Renderindex].LineXCordinates[j] / LiveViewNativeImageAspectRatio;
	
			}
			if (GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation() == 180) {

				// Læs Temperatur Linjernes X/Y Positions Koordinater
				TempLinesPositionsXCordinates = LiveViewNativeImageWidth - TempLinesPositions[Renderindex].LineXCordinates[j];
				TempLinesPositionsYCordinates = LiveViewNativeImageHeight - TempLinesPositions[Renderindex].LineYCordinates[j];
	
			}
			if (GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation() == 270) {

				// Læs Temperatur Linjernes X/Y Positions Koordinater
				TempLinesPositionsXCordinates = TempLinesPositions[Renderindex].LineYCordinates[j] * LiveViewNativeImageAspectRatio;
				TempLinesPositionsYCordinates = LiveViewNativeImageHeight - TempLinesPositions[Renderindex].LineXCordinates[j] / LiveViewNativeImageAspectRatio;
	
			}

			// Læs Temperatur værdien fra linjens X/Y kordinater
			LineTempValue = RMH_IRThermalCamera_ReadFramePixelTemperature(&IRCamera, &FrameThermalDataRaw[0], TempLinesPositionsXCordinates, TempLinesPositionsYCordinates, IRCamera.ThermalCameraSupportPool);

			// Lager Linjens Temperatur værdier
			TempLinesTemperatureValues[Renderindex][j] = (LineTempValue * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

			// Kontroller for Maximum Temperatur
			if (LineTempValue > LineMaximumTemperature) {

				// Opdater Maximum Temperatur værdi
				LineMaximumTemperature = LineTempValue;

				// Lager Maximum temperaturens Frame X/Y Kordinater
				TempLinesMaxTempValueXCoordinate[Renderindex] = TempLinesPositions[Renderindex].LineXCordinates[j];
				TempLinesMaxTempValueYCoordinate[Renderindex] = TempLinesPositions[Renderindex].LineYCordinates[j];

			}

			// Kontroller for Maximum Temperatur
			if (LineTempValue < LineMinimumTemperature) {

				// Opdater Minimum Temperatur værdi
				LineMinimumTemperature = LineTempValue;

				// Lager Minimum temperaturens Frame X/Y Kordinater
				TempLinesMinTempValueXCoordinate[Renderindex] = TempLinesPositions[Renderindex].LineXCordinates[j];
				TempLinesMinTempValueYCoordinate[Renderindex] = TempLinesPositions[Renderindex].LineYCordinates[j];

			}

			// Akkumulere summen af alle Linje pixel værdiers temperatur sum
			LineAverageTemperature = LineAverageTemperature + LineTempValue;

		}

		// Udregn den gennemsnitlige Linje temperatur
		LineAverageTemperature = LineAverageTemperature / (double)(TempLinesPositions[Renderindex].LinePixelLength);

		// Konpenser for valgte temperatur enhed
		LineMaximumTemperature = (LineMaximumTemperature * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		LineMinimumTemperature = (LineMinimumTemperature * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		LineAverageTemperature = (LineAverageTemperature * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

		// Lager læste Maximum, minimums og gennemsnitlig temperaturer i globalt array
		TempLinesMaxTempValues[Renderindex] = LineMaximumTemperature;
		TempLinesMinTempValues[Renderindex] = LineMinimumTemperature;
		TempLinesAvgTempValues[Renderindex] = LineAverageTemperature;

		// Formater temperatur målings Label string til live view renderering
		GlobalVariables::TempLinesMaxLabels[Renderindex] = "Max: " + TempLinesMaxTempValues[Renderindex].ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;
		GlobalVariables::TempLinesMinLabels[Renderindex] = "Min: " + TempLinesMinTempValues[Renderindex].ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

	}

}

void RMH_ThermalViewer_ToggleMaximumTempTracking() {

	// Routinen aktiverer eller deaktiverer live view maximum temperatur tracking

	// Toggle Max Temp trackings aktiverings flag
	MaxTempTrackingEnableFlag = !MaxTempTrackingEnableFlag;

	// Skal Dual Color Palette aktiveres eller deaktiveres
	if (MaxTempTrackingEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalMaxTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalMaxTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Opdater knap grafik
	GlobalVariables::GlobalMaxTempTrackButton->Refresh();

}

void RMH_ThermalViewer_ToggleMinimumTempTracking() {

	// Routinen aktiverer eller deaktiverer live view minimum temperatur tracking

	// Toggle Min Temp trackings aktiverings flag
	MinTempTrackingEnableFlag = !MinTempTrackingEnableFlag;

	// Skal Dual Color Palette aktiveres eller deaktiveres
	if (MinTempTrackingEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalMinTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalMinTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Opdater knap grafik
	GlobalVariables::GlobalMinTempTrackButton->Refresh();

}

void RMH_ThermalViewer_ToggleCenterTempTracking() {

	// Routinen aktiverer eller deaktiverer live view center temperatur tracking

	// Toggle Center Temp trackings aktiverings flag
	CenterTempTrackingEnableFlag = !CenterTempTrackingEnableFlag;

	// Skal Dual Color Palette aktiveres eller deaktiveres
	if (CenterTempTrackingEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalCenterTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalCenterTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Opdater knap grafik
	GlobalVariables::GlobalCenterTempTrackButton->Refresh();

}

void RMH_ThermalViewer_ToggleMouseCursorTempTracking() {
	
	// Routinen aktiverer eller deaktiverer Mus Cursor temperatur tracking

	// Toggle Center Temp trackings aktiverings flag
	CursorTempTrackEnableFlag = !CursorTempTrackEnableFlag;

	// Skal Dual Color Palette aktiveres eller deaktiveres
	if (CursorTempTrackEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalCursorTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalCursorTempTrackButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Aktiver eller deaktiver Mus Cursor Temperatur tracking
	GlobalVariables::OpenGLRender->RMH_OpenGL_EnableMouseCursorTrackingWLabel(CursorTempTrackEnableFlag);

	// Opdater knap grafik
	GlobalVariables::GlobalCursorTempTrackButton->Refresh();

}

// --------------------- Live View Statistik Data Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_CalLiveViewStatisticsData() {

	// Routinen udregner Live view statistik vinduets tilhørende data.

	// Udregn det termiske kameras temperatur drift fra sidste kalibrering
	SensorTemperatureCalDrift = CurrentCalDetectorTemperature - IRCamera.temp_fpa;

	// Kontroller om Live View Statistik Vinduet er åbent
	if (LiveViewStatisticsWindowIsShownFlag == true) {

		// Udregn Live View "Span" (Max - Min) Temperaturen
		TemperatureSpan = MaximumTemperature - MinimumTemperature;
		// Udregn hvor meget af det termiske kameras nuværende temperatur range er brugt (0 - 14Bit = 0% - 100%)
		ThermalCameraRangeUsage = ((double)IRCamera.Tmax_Tmp_Raw / 16383.0) * 100.0;

		// Udren det termiske kameras sensor drift error (Tdrift / (Min - Max))
		SensorDriftError = (SensorTemperatureCalDrift / (MinimumTemperature - MaximumTemperature)) * 100.0;

		// Er den maksimale temperatur blevet højere
		if (MaximumTemperature > MaxPeakTemperature) {

			// Lager den nyeste højeste temperatur måling
			MaxPeakTemperature = MaximumTemperature;

		}

		// Er den minimale temperatur blevet mindre
		if (MinimumTemperature < MinPeakTemperature) {

			// Lager den nyeste mindste temperatur måling
			MinPeakTemperature = MinimumTemperature;

		}

	}

}

void RMH_ThermalViewer_UpdateAndFormatLiveViewStatisticsLabels() {

	// Routinen udregner Live view statistik data, samt opdaterer og formaterer Statistik Labels

	// Kontroller om Live View Statistik Vinduet er åbent
	if (LiveViewStatisticsWindowIsShownFlag == true) {

		// Akkumuler læste kameras frame rate Sum
		IRCamera.CameraFrameRateSum = IRCamera.CameraFrameRateSum + RMH_IRThermalCamera_ReadCameraFPS();

		// Inkrementer kameraets frame rate tæller varaibel
		IRCamera.CameraFrameRateSumCounter = IRCamera.CameraFrameRateSumCounter + 1;

		// Hvis læste kameras frame rate Sum har Akkumulerede nok målinger
		if (IRCamera.CameraFrameRateSumCounter >= (unsigned int)IRCamera.FrameRate) {

			// Udregn kamerats gennemsnitlige frame rate
			IRCamera.CameraAverageFrameRate = IRCamera.CameraFrameRateSum / 20;

			// Nulstil læste kameras frame rate Sum
			IRCamera.CameraFrameRateSum = 0;
			// Nulstil kameraets frame rate tæller varaibel
			IRCamera.CameraFrameRateSumCounter = 0;

			// Opdater Live View Statistik Vinduets FPS Label
			GlobalVariables::GlobalFrameRateLabel->Text = IRCamera.CameraAverageFrameRate.ToString("F2") + " FPS";

		}

		// Opdater Live View Statistik Vinduets "Antal fanget frames" Label
		GlobalVariables::GlobalNumberOfFramesLabel->Text = IRCamera.NumbOfCapturedFrames.ToString();
		// Opdater Live View Statistik Vinduets "Temperatur Span" Label
		GlobalVariables::GlobalSpanLabel->Text = TemperatureSpan.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;;
		// Opdater Live View Statistik Vinduets "Gennemsnitlige Temperatur" Label
		GlobalVariables::GlobalAverageLabel->Text = AverageTemperature.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;
		// Opdater Live View Statistik Vinduets "Range Usage" Label
		GlobalVariables::GlobalRangeUsageLabel->Text = ThermalCameraRangeUsage.ToString("F2") + "%";
		// Opdater Live View Statistik Vinduets "Drift" Label
		GlobalVariables::GlobalDriftLabel->Text = (SensorTemperatureCalDrift * TemperatureUnitScaleFactor).ToString("F5") + " " + GlobalVariables::DefaultTempUnitString;
		// Opdater Live View Statistik Vinduets "Drift Error" Label
		GlobalVariables::GlobalDriftErrorLabel->Text = SensorDriftError.ToString("F5") + "%";
		// Opdater Live View Statistik Vinduets "Max Peak" Label
		GlobalVariables::GlobalMaxPeakLabel->Text = MaxPeakTemperature.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;
		// Opdater Live View Statistik Vinduets "Min Peak" Label
		GlobalVariables::GlobalMinPeakLabel->Text = MinPeakTemperature.ToString(GlobalVariables::TemperaturePrecision) + " " + GlobalVariables::DefaultTempUnitString;

	}

}

// ------------------ Fast Temperatur Label Trackings Håndterings Routiner ------------------ //

void RMH_ThermalViewer_UpdateTempMeasurementsRenderingOrder() {

	// Routinen lager aktiverede Temp Målings labels positioner i et array
	// Som definerer senere rendererings orden

	// Lokale variabler
	unsigned int ActiveTempMeasOrderIndex = 0;

	// Loop til og med det maksimale tilladte antal Temp Meas Labels
	for (unsigned int i = 0; i < _MaxNumberOfMovableCrosshairs; i++) {

		// Hvis læste aktive Temp Meas Label er aktiverede
		if (ActiveTempMeasEnableFlags[i] == true) {

			// Lager de aktiverede Temp Meas Labels indexer i rendererings ordens array
			ActiveTempMeasRenderingOrder[ActiveTempMeasOrderIndex] = i;

			// Inkrementer lokalt ordens index tæller variabel
			ActiveTempMeasOrderIndex = ActiveTempMeasOrderIndex + 1;

		}

	}

}

void RMH_ThermalViewer_AddTemperatureMeasurementToLiveView() {

	// Routinen aktiverer et temperatur målings label til live view streamen

	// Lokale variabler
	unsigned int ActiveTempMeasEnableIndex = 0;

	// Hvis det maksimale antal aktive temperature målinger er nåede
	if (NumOfActiveLiveViewTempMeas < _MaxNumberOfMovableCrosshairs) {

		// Loop til og med det maksimale tilladte antal Crosshair labels
		for (unsigned int i = 0; i < _MaxNumberOfMovableCrosshairs; i++) {

			// Hvilke Temperatur målinger er ikke aktive
			if (ActiveTempMeasEnableFlags[i] == false) {

				// Læs index positionen for senest slettede temp måling
				ActiveTempMeasEnableIndex = i;

				// Opdater ROI enable flag array position
				ActiveTempMeasEnableFlags[ActiveTempMeasEnableIndex] = true;

				// Bryd for loop
				break;

			}

		}

		// Opdater Temp målingernes rendererings orden
		RMH_ThermalViewer_UpdateTempMeasurementsRenderingOrder();

		// Aktiver tilhørende ROI Sub Context Menu Drop Down List Item 
		GlobalVariables::GlobaldeleteTempLabelToolStripMenuItem->DropDownItems[ActiveTempMeasEnableIndex]->Enabled = true;

		// Inkrementer antallet af aktive Temperatur målinger
		NumOfActiveLiveViewTempMeas = NumOfActiveLiveViewTempMeas + 1;

		// Opdater Knap Border Farve
		GlobalVariables::GlobalAddTempMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalAddTempMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::Magenta;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Maximum Number Of Temperature Measurements Reached!", _StatusMessageType_Warning);

	}

}

void RMH_ThermalViewer_DeleteTemperatureMeasurementFromLiveView(System::Object^ sender) {

	// Routinen fjerner en Temperatur måling fra rendererings listen på Live View streamen

	// Cast Sender objekt som Forms Tool Strip objekt
	System::Windows::Forms::ToolStripMenuItem^ TempMeasIndex = (System::Windows::Forms::ToolStripMenuItem^)sender;

	// Læs Sub Context Menu identifikations tag
	unsigned int TempMeasIndexTag = Convert::ToInt32(TempMeasIndex->Tag);

	// Kontroller om der er Temperatur målinger at slette
	if (NumOfActiveLiveViewTempMeas > 0) {

		// Deaktiver tilhørende Temperatur målinger Sub Context Menu Drop Down List Item 
		GlobalVariables::GlobaldeleteTempLabelToolStripMenuItem->DropDownItems[TempMeasIndexTag]->Enabled = false;

		// Dekrementer antallet af aktive  Temperatur målinger
		NumOfActiveLiveViewTempMeas = NumOfActiveLiveViewTempMeas - 1;

		// Hvis sidste Temperatur målinger er blever slettet
		if (NumOfActiveLiveViewTempMeas <= 0) {
			// Nulstil Knap Border Farve
			GlobalVariables::GlobalAddTempMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);
		}
		else {
			// Opdater Knap Border Farve
			GlobalVariables::GlobalAddTempMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
		}

		// Nulstil tilhørende Temperatur målings Tag enable flag
		ActiveTempMeasEnableFlags[TempMeasIndexTag] = false;

		// Opdater Temp målingernes rendererings orden
		RMH_ThermalViewer_UpdateTempMeasurementsRenderingOrder();

	}

}

void RMH_ThermalViewer_DeleteAllTemperatureMeasurementFromLiveView() {

	// Routinen sletter alle aktive Temperatur målinger fra Live View Streamen

	// Loop til og med det maksimale tilladte antal Temperatur målinger
	for (unsigned int i = 0; i < _MaxNumberOfMovableCrosshairs; i++) {

		// Kontroller aktive Temperatur Målinger
		if (ActiveTempMeasEnableFlags[i] == true) {

			// Deaktiver tilhørende Temp målings Sub Context Menu Drop Down List Item 
			GlobalVariables::GlobaldeleteTempLabelToolStripMenuItem->DropDownItems[i]->Enabled = false;

			// Dekrementer antallet af aktive Temp Målinger
			NumOfActiveLiveViewTempMeas = NumOfActiveLiveViewTempMeas - 1;

			// Nulstil tilhørende Temp Målings Tag enable flag
			ActiveTempMeasEnableFlags[i] = false;

		}

	}

	// Nulstil Knap Border Farve
	GlobalVariables::GlobalAddTempMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	// Opdater Temp målingernes rendererings orden
	RMH_ThermalViewer_UpdateTempMeasurementsRenderingOrder();

}

// --------------------- ROI Temperatur Trackings Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_UpdateROIRenderingOrder() {

	// Routinen lager aktiverede ROI positioner i et array
    // Som definerer senere rendererings orden
	
	// Lokale variabler
	unsigned int ActiveROIOrderIndex = 0;

	// Loop til og med det maksimale tilladte antal ROIRektangler
	for (unsigned int i = 0; i < _MaxNumberOfMovableRectangles; i++) {

		// Hvis læste aktive ROI flag er aktiverede
		if (ActiveROIEnableFlags[i] == true) {

			// Lager de aktiverede ROIers indexer i ROI rendererings ordens array
			ActiveROIRenderingOrder[ActiveROIOrderIndex] = i;

			// Inkrementer lokalt ordens index tæller variabel
			ActiveROIOrderIndex = ActiveROIOrderIndex + 1;

		}

	}

}

void RMH_ThermalViewer_AddRegionOfInterestBoxToLiveView() {

	// Routinen Aktiverer et ROI til renderering på Live View streamen

	// Lokale variabler
	unsigned int ActiveROIEnableIndex = 0;

	// Hvis det maksimale antal aktive ROIer (Minus Color Palette ROI) Er nåede - 2 = (Color Palette ROI + Zoom ROI)
	if (NumOfActiveLiveViewROIs < _MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs) {

		// Loop til og med det maksimale tilladte antal ROIRektangler
		for (unsigned int i = 0; i < _MaxNumberOfMovableRectangles; i++) {

			// Hvilke ROIer er ikke aktive
			if (ActiveROIEnableFlags[i] == false) {

				// Læs index positionen for senest slettede ROI
				ActiveROIEnableIndex = i;

				// Opdater ROI enable flag array position
				ActiveROIEnableFlags[ActiveROIEnableIndex] = true;

				// Bryd for loop
				break;

			}

		}

		// Opdater ROIernes rendererings orden
		RMH_ThermalViewer_UpdateROIRenderingOrder();

		// Aktiver tilhørende ROI Sub Context Menu Drop Down List Item 
		GlobalVariables::GlobaldeleteROIToolStripMenuItem->DropDownItems[ActiveROIEnableIndex]->Enabled = true;
		GlobalVariables::GlobalhistogramSourceToolStripMenuItem->DropDownItems[ActiveROIEnableIndex + 5]->Enabled = true;

		// Inkrementer antallet af aktive ROIer
		NumOfActiveLiveViewROIs = NumOfActiveLiveViewROIs + 1;

		// Opdater Knap Border Farve
		GlobalVariables::GlobalAddROIMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalAddROIMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::Magenta;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Maximum Number Of ROI Reached!", _StatusMessageType_Warning);

	}

}

void RMH_ThermalViewer_DeleteRegionOfInterestBoxFromLiveView(System::Object^ sender) {

	// Routinen fjerner et ROI fra rendererings listen på Live View streamen

	// Cast Sender objekt som Forms Tool Strip objekt
	System::Windows::Forms::ToolStripMenuItem^ ROIIndex = (System::Windows::Forms::ToolStripMenuItem^)sender;

	// Læs Sub Context Menu identifikations tag
	unsigned int ROIIndexTag = Convert::ToInt32(ROIIndex->Tag);

	// Kontroller om der er ROIer at slette
	if (NumOfActiveLiveViewROIs > 0) {

		// Deaktiver tilhørende ROI Sub Context Menu Drop Down List Item 
		GlobalVariables::GlobaldeleteROIToolStripMenuItem->DropDownItems[ROIIndexTag]->Enabled = false;
		GlobalVariables::GlobalhistogramSourceToolStripMenuItem->DropDownItems[ROIIndexTag + 5]->Enabled = false;

		// Dekrementer antallet af aktive ROIer
		NumOfActiveLiveViewROIs = NumOfActiveLiveViewROIs - 1;

		// Hvis sidste ROI er blever slettet
		if (NumOfActiveLiveViewROIs <= 0) {
			// Nulstil Knap Border Farve
			GlobalVariables::GlobalAddROIMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);
		}
		else {
			// Opdater Knap Border Farve
			GlobalVariables::GlobalAddROIMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
		}

		// Nulstil tilhørende tag ROI enable flag
		ActiveROIEnableFlags[ROIIndexTag] = false;

		// Opdater ROIernes rendererings orden
		RMH_ThermalViewer_UpdateROIRenderingOrder();

	}

}

void RMH_ThermalViewer_DeleteAllRegionOfInterestBoxFromLiveView() {

	// Routinen sletter alle aktive ROIer fra Live View Streamen

	// Loop til og med det maksimale tilladte antal ROIRektangler
	for (unsigned int i = 0; i < _MaxNumberOfMovableRectangles; i++) {

		// Kontroller aktive ROIer
		if (ActiveROIEnableFlags[i] == true) {

			// Deaktiver tilhørende ROI Sub Context Menu Drop Down List Item 
			GlobalVariables::GlobaldeleteROIToolStripMenuItem->DropDownItems[i]->Enabled = false;
			GlobalVariables::GlobalhistogramSourceToolStripMenuItem->DropDownItems[i + 5]->Enabled = false;

			// Dekrementer antallet af aktive ROIer
			NumOfActiveLiveViewROIs = NumOfActiveLiveViewROIs - 1;

			// Nulstil tilhørende tag ROI enable flag
			ActiveROIEnableFlags[i] = false;

		}

	}

	// Nulstil Knap Border Farve
	GlobalVariables::GlobalAddROIMeasButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	// Opdater ROIernes rendererings orden
	RMH_ThermalViewer_UpdateROIRenderingOrder();

}

// --------------------- Temperatur Linje Tracking Håndterings Routiner --------------------- //

void RMH_ThermalViewer_UpdateTempLinesRenderingOrder() {

	// Routinen lager aktiverede Temp Linjers positioner i et array
	// Som definerer senere rendererings orden

	// Lokale variabler
	unsigned int ActiveLinesOrderIndex = 0;

	// Loop til og med det maksimale tilladte antal linjer
	for (unsigned int i = 0; i < _MaxNumberOfMovableLines; i++) {

		// Hvis læste aktive linje er aktiverede
		if (ActiveTempLineEnableFlags[i] == true) {

			// Lager de aktiverede linjers indexer i rendererings ordens array
			ActiveTempLineRenderingOrder[ActiveLinesOrderIndex] = i;

			// Inkrementer lokalt ordens index tæller variabel
			ActiveLinesOrderIndex = ActiveLinesOrderIndex + 1;

		}

	}

}

void RMH_ThermalViewer_AddTemperatureLineToLiveView() {

	// Routinen Aktiverer en Temperatur Linje til renderering på Live View streamen

	// Lokale variabler
	unsigned int ActiveLineEnableIndex = 0;

	// Hvis det maksimale antal aktive temperatur linjer er nåede
	if (NumOfActiveLiveViewLines < _MaxNumberOfMovableLines) {

		// Loop til og med det maksimale tilladte antal linjer
		for (unsigned int i = 0; i < _MaxNumberOfMovableLines; i++) {

			// Hvilke linjer er ikke aktive
			if (ActiveTempLineEnableFlags[i] == false) {

				// Læs index positionen for senest slettede linje
				ActiveLineEnableIndex = i;

				// Opdater ROI enable flag array position
				ActiveTempLineEnableFlags[ActiveLineEnableIndex] = true;

				// Bryd for loop
				break;

			}

		}

		// Opdater Linjernes rendererings orden
		RMH_ThermalViewer_UpdateTempLinesRenderingOrder();

		// Aktiver tilhørende label Sub Context Menu Drop Down List Item 
		GlobalVariables::GlobaldeleteLineToolStripMenuItem->DropDownItems[ActiveLineEnableIndex]->Enabled = true;
		GlobalVariables::GlobalhistogramSourceToolStripMenuItem->DropDownItems[ActiveLineEnableIndex]->Enabled = true;

		// Inkrementer antallet af aktive linjer
		NumOfActiveLiveViewLines = NumOfActiveLiveViewLines + 1;

		// Opdater Knap Border Farve
		GlobalVariables::GlobalAddTempSpecLineButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalAddTempSpecLineButton->FlatAppearance->BorderColor = System::Drawing::Color::Magenta;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Maximum Number Of Lines Reached!", _StatusMessageType_Warning);

	}

}

void RMH_ThermalViewer_DeleteTemperatureLineFromLiveView(System::Object^ sender) {

	// Routinen fjerner en temperatur linje fra rendererings listen på Live View streamen

	// Cast Sender objekt som Forms Tool Strip objekt
	System::Windows::Forms::ToolStripMenuItem^ LineIndex = (System::Windows::Forms::ToolStripMenuItem^)sender;

	// Læs Sub Context Menu identifikations tag
	unsigned int LineIndexTag = Convert::ToInt32(LineIndex->Tag);

	// Kontroller om der er linjer som kan slette
	if (NumOfActiveLiveViewLines > 0) {

		// Deaktiver tilhørende linje Sub Context Menu Drop Down List Item 
		GlobalVariables::GlobaldeleteLineToolStripMenuItem->DropDownItems[LineIndexTag]->Enabled = false;
		GlobalVariables::GlobalhistogramSourceToolStripMenuItem->DropDownItems[LineIndexTag]->Enabled = false;

		// Dekrementer antallet af aktive linjer
		NumOfActiveLiveViewLines = NumOfActiveLiveViewLines - 1;

		// Hvis sidste linje er blever slettet
		if (NumOfActiveLiveViewLines <= 0) {
			// Nulstil Knap Border Farve
			GlobalVariables::GlobalAddTempSpecLineButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);
		}
		else {
			// Opdater Knap Border Farve
			GlobalVariables::GlobalAddTempSpecLineButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
		}

		// Nulstil tilhørende Tag linje enable flag
		ActiveTempLineEnableFlags[LineIndexTag] = false;

		// Opdater Linjernes rendererings orden
		RMH_ThermalViewer_UpdateTempLinesRenderingOrder();

	}

}

void RMH_ThermalViewer_DeleteAllTemperatureLinesFromLiveView() {

	// Routinen sletter alle aktive temperatur linjer fra Live View Streamen

	// Loop til og med det maksimale tilladte antal temperatur linjer
	for (unsigned int i = 0; i < _MaxNumberOfMovableLines; i++) {

		// Kontroller aktive temperatur linjer
		if (ActiveTempLineEnableFlags[i] == true) {

			// Deaktiver tilhørende temperatur linjes Sub Context Menu Drop Down List Item 
			GlobalVariables::GlobaldeleteLineToolStripMenuItem->DropDownItems[i]->Enabled = false;
			GlobalVariables::GlobalhistogramSourceToolStripMenuItem->DropDownItems[i]->Enabled = false;

			// Dekrementer antallet af aktive temperatur linjes
			NumOfActiveLiveViewLines = NumOfActiveLiveViewLines - 1;

			// Nulstil tilhørende Linjes Tag enable flag
			ActiveTempLineEnableFlags[i] = false;

		}

	}

	// Nulstil Knap Border Farve
	GlobalVariables::GlobalAddTempSpecLineButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	// Opdater Linjernes rendererings orden
	RMH_ThermalViewer_UpdateTempLinesRenderingOrder();

}

// ------------------------ Live View Histogram Håndterings Routiner ------------------------ //

void RMH_ThermalViewer_EnableLiveViewHistogram() {

	// Routinen aktiverer live view streamens Histogram feature for linjer og frame data

	// Toggle live view histogram enable flag
	LiveViewHistogramEnableFlag = !LiveViewHistogramEnableFlag;

	// Skallive view histogram aktiveres eller deaktiveres
	if (LiveViewHistogramEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalShowLineHistButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

		// Gør Histogram panel synlig
		GlobalVariables::GlobalLiveViewHistogramPanel->Visible = true;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalShowLineHistButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

		// Gør Histogram panel usynlig
		GlobalVariables::GlobalLiveViewHistogramPanel->Visible = false;

	}

	// Opdater knap grafik
	GlobalVariables::GlobalShowLineHistButton->Refresh();

}

void RMH_ThermalViewer_ChangeHistoramDataSource(System::Object^ sender) {

	// Routinen indstiller histogrammets data source 
	// Som enten kan være temperature linjer, ROIer eller hele Live view billedet

	// Cast Sender objekt som Forms Tool Strip objekt
	System::Windows::Forms::ToolStripMenuItem^ MenuIndex = (System::Windows::Forms::ToolStripMenuItem^)sender;

	// Læs Sub Context Menu identifikations tag
	unsigned int MenuIndexTag = Convert::ToInt32(MenuIndex->Tag);

	// Opdater Histogrammets data source tag værdi
	HistogramDataSourceTag = (unsigned char)MenuIndexTag;

	// Loop til og med det maksimale antal ROIer
	for (unsigned int i = 0; i < _MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs; i++) {

		// Deaktiver læsning af Rå pixel data fra alle Aktive ROIer
		ROIxReturnAreaRawPixelValsFlags[i] = false;

	}

	// Hvis valgte Histogram Data source er en af de aktive ROIer
	if (HistogramDataSourceTag >= _MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs) {

		// Aktiver læsning af Rå pixel data for det valgte ROI
		ROIxReturnAreaRawPixelValsFlags[HistogramDataSourceTag - (_MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs)] = true;

	}

}

// -------------- Gem Fuld Frame Temperatur Data Til CSV Håndterings Routiner --------------- //

void RMH_ThermalViewer_UpdateFullFrameTemperatureCSVDataDelimiter() {

	// Routinen opdaterer hvilken Data delimiter som benyttes når der gemmes en Full frame temperatur data CSV fil

	// Lokale variabler
	unsigned char DataDelimiterIndex = 0;

	// Læs den valgte Data delimiter fra tilhørende CombiBox
	DataDelimiterIndex = GlobalVariables::GlobalFullFrameTempDataCSVDelimiterCombiBox->SelectedIndex;

	// Lager og opdater læste CSV Data delimiter i globalt variabel
	SelectedFullFrameTempCSVDataDelimiterIndex = DataDelimiterIndex;

	// Hvilken Delimiter index er blevet valgt
	switch (SelectedFullFrameTempCSVDataDelimiterIndex) {

		// Opdater tilhørende globale delimiter string
		case _FullFrameTempCSVDataDelimiterIndex_Comma:		GlobalVariables::FullFrameDataCSVDelimiterString = ",";  break;
		case _FullFrameTempCSVDataDelimiterIndex_Semicolon: GlobalVariables::FullFrameDataCSVDelimiterString = ";";  break;
		case _FullFrameTempCSVDataDelimiterIndex_Colon:		GlobalVariables::FullFrameDataCSVDelimiterString = ":";  break;
		case _FullFrameTempCSVDataDelimiterIndex_Space:		GlobalVariables::FullFrameDataCSVDelimiterString = " ";  break;
		case _FullFrameTempCSVDataDelimiterIndex_Tab:		GlobalVariables::FullFrameDataCSVDelimiterString = "\t"; break;

	}

}

void RMH_ThermalViewer_SaveFullFrameTemperatureDataToCSVFile() {

	// Routinen opretter/gemmer en CSV fil og formaterer den seneste data frame til en fuld frame af temperatur data, Som derefter skrives til CSV filen.
	// Den gemte fils sti er den samme som den valgte snapshots fil sti

	// Lokale variabler - Frame Bredde og Højde konstanter
	unsigned int FrameWidth = IRCamera.FrameWidth;
	unsigned int FrameHeight = IRCamera.FrameHeight - IRCamera.FrameMetadataSize;

	// Formater Filens data identifikations string (FrameTempData_HHmmssddMMyyyy)
	System::String^ FileName = System::DateTime::Now.ToString("HHmmssfffddMMyyyy");
	// Formater Temperatur frame Data Filens navn
	System::String^ FrameTempDataFileNameString = "FrameTempData_" + FileName + ".txt";

	// Fortag Live View Single frame trigger
	RMH_ThermalViewer_TriggerLiveViewSingleFrameCapture();

	// Loop igennem alle rå termiske data værdier i tilhørende frame data array
	for (unsigned long i = 0; i < (FrameWidth * FrameHeight); i += 4) {

		// Konverter Rå termisk data til temperature data og lager i array
		FrameTemperatureData[i + 0] = (RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, FrameThermalDataRaw[i + 0], IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		FrameTemperatureData[i + 1] = (RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, FrameThermalDataRaw[i + 1], IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		FrameTemperatureData[i + 2] = (RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, FrameThermalDataRaw[i + 2], IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;
		FrameTemperatureData[i + 3] = (RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, FrameThermalDataRaw[i + 3], IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor;

	}

	// Generer Temperatur Frame Data CSV fil og skriv data til fil
	RMH_Winforms_WriteDataArrayMatrixToCSVFile(RMH_Conversion_SystemStringToStdString(GlobalVariables::SnapShotDefaultPath), RMH_Conversion_SystemStringToStdString(FrameTempDataFileNameString), &FrameTemperatureData[0], FrameWidth, FrameHeight, GlobalVariables::FullFrameDataCSVDelimiterString);

	// Skriv GUI Status Meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Full Frame Temperature Data CSV, Has Been Saved To Path.", _StatusMessageType_Success);

	// Genstart Live View Streamen
	LiveViewRunStopFlag = false;
	RMH_ThermalViewer_ToggleLiveViewStreamRunStop();

}

// ----------- Live View Stream Video Optagning Og Snapshot Håndterings Routiner ------------ //

void RMH_ThermalViewer_UpdateSnapshotDefaultSaveFilePath(System::Windows::Forms::Label^ DefaultPathString) {

	// Routinen opdaterer fil lokationen hvor et Live View Snapshot skal gemmes

	// Lokale variabler
	System::String^ SaveFilePathString;

	// Læs valgte snapshot default save fil path 
	SaveFilePathString = RMH_Winforms_GetSaveFileDialogDirectory();

	// Kontroller om et path blev valgt, eller om dialogen blev lukket
	if (SaveFilePathString == "None") {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "No New Default Snapshot File Path Was Choosen!", _StatusMessageType_Warning);

	}
	else {

		// Opdater Snapshot default path
		GlobalVariables::SnapShotDefaultPath = SaveFilePathString;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "New Default Snapshot File Path Was Choosen.", _StatusMessageType_Success);

	}

	// Opdater Snapshot default Fil path stringet 
	DefaultPathString->Text = "Default Save File Path:  " + GlobalVariables::SnapShotDefaultPath;

}

void RMH_ThermalViewer_UpdateVideoRecordingDefaultSaveFilePath(System::Windows::Forms::Label^ DefaultPathString) {

	// Routinen opdaterer fil lokationen hvor Video optagningen skal gemmes

	// Lokale variabler
	System::String^ SaveFilePathString;

	// Læs valgte Video optagnings default save fil path 
	SaveFilePathString = RMH_Winforms_GetSaveFileDialogDirectory();

	// Kontroller om et path blev valgt, eller om dialogen blev lukket
	if (SaveFilePathString == "None") {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "No New Default Video Recording File Path Was Choosen!", _StatusMessageType_Warning);

	}
	else {

		// Opdater Snapshot default path
		GlobalVariables::RecordingDefaultPath = SaveFilePathString;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "New Default Video Recording File Path Was Choosen.", _StatusMessageType_Success);

	}

	// Opdater Snapshot default Fil path stringet 
	DefaultPathString->Text = "Default Save File Path:  " + GlobalVariables::RecordingDefaultPath;

}

void RMH_ThermalViewer_IncludeColorBarInSnapshot() {

	// Routinen håndterer om det valgte snapshot skal indeholde colorbaren eller ikke

	// Toggle inkluder Colorbar i snapshot aktiverings flag
	IncludeColorBarSnapshotFlag = !IncludeColorBarSnapshotFlag;

	// Skal colorbaren inkluderes i snapshot aktiveres eller deaktiveres
	if (IncludeColorBarSnapshotFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalIncludeColorbarSnapButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalIncludeColorbarSnapButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Opdater knap grafik
	GlobalVariables::GlobalIncludeColorbarSnapButton->Refresh();

}

void RMH_ThermalViewer_ToggleSavinfOfRawSensorDataSnapshot() {

	// Routinen opdater GUI elementer og kontrol flag, når et RÅ sensor data snapshot 
	// er blevet valgt til at skulle gemmes med det tilhørende live view snapshot.

	// Toggle Gem Rå sensor data snapshot aktiverings flag
	CaptureRawSensorSnapshotFlag = !CaptureRawSensorSnapshotFlag;

	// Skal Gem Rå sensor data gemmes
	if (CaptureRawSensorSnapshotFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalSaveRawSensorSnapButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalSaveRawSensorSnapButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Opdater knap grafik
	GlobalVariables::GlobalSaveRawSensorSnapButton->Refresh();

}

void RMH_ThermalViewer_SaveLiveViewSnapshot() {

	// Routinen gemmer et snapshot af live View streamen, med eller uden colorbaren og tools panelet

	// lokale variabler
	bool SnapshotStatus = false;
	bool RawSnapshotStatus = false;

	// Kontroller om live view panalet er i visning i guien - Eller er undocked
	if (isLiveViewStreamFormOpen == true) {

		// Skal snapshotet indeholde colorbaren og tools panelet
		if (IncludeColorBarSnapshotFlag == true) {
			// Gem et snapshot af live view streamen - med colorbar og tools panelet
			SnapshotStatus = RMH_Winforms_SavePanelSnapShotPNG(GlobalVariables::GlobalStreamAndCBarPanel, GlobalVariables::SnapShotDefaultPath);
		}
		else {
			// Gem et snapshot af live view streamen - uden colorbar
			SnapshotStatus = RMH_Winforms_SavePanelSnapShotPNG(GlobalVariables::GlobalLiveViewStreamPanel, GlobalVariables::SnapShotDefaultPath);
		}
	}

	// Skal et tilhørende Rå sensor data snapshot gemmes
	if (CaptureRawSensorSnapshotFlag == true) {

		// Gem et Rå sensor data snapshot fra forbundet termiske kamera
		RawSnapshotStatus = RMH_IRThermalCamera_ConvertCapturedRawImageDataToSnapshotPNG(IRCamera.ThermalCameraSupportPool);

	}

	// Kontroller om snapshot blev korrekt gemt
	if (SnapshotStatus == true) {
		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Snapshot Has Been Saved To Path Location.", _StatusMessageType_Success);
	}
	else {
		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Could Not Save The Snapshot To Path Location!", _StatusMessageType_Error);
	}

	// Skal et tilhørende Rå sensor data snapshot gemmes
	if (CaptureRawSensorSnapshotFlag == true) {

		// Kontroller om Rå snapshot blev korrekt gemt
		if (RawSnapshotStatus == true) {
			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "RAW Snapshot Has Been Saved To Path Location.", _StatusMessageType_Success);
		}
		else {
			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Could Not Save The RAW Snapshot To Path Location!", _StatusMessageType_Error);
		}

	}

}

void RMH_ThermalViewer_SaveSurfacePlotSnapshot() {

	// Routinen gemmer et snapshot af 3D surface plottet

	// lokale variabler
	bool SnapshotStatus = false;

	// Gem et snapshot af 3D Surface Plottet
	SnapshotStatus = RMH_Winforms_SavePanelSnapShotPNG(GlobalVariables::GlobalSurfacePlotPanel, GlobalVariables::SnapShotDefaultPath);
	
	// Kontroller om snapshot blev korrekt gemt
	if (SnapshotStatus == true) {
		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Snapshot Has Been Saved To Path Location.", _StatusMessageType_Success);
	}
	else {
		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Could Not Save The Snapshot To Path Location!", _StatusMessageType_Error);
	}

}

void RMH_ThermalViewer_ConfigDefaultCapturingProgram(System::Object^ sender) {

	// Routinen konfigurerer det default Video Capturing program for optagning af live view video

	// Cast Sender objekt som Forms Button objekt
	System::Windows::Forms::Button^ SettingsButton = (System::Windows::Forms::Button^)sender;

	// Læs indstillings knappens identifikations tag
	unsigned int ButtonTag = Convert::ToInt32(SettingsButton->Tag);

	// Hvilken knap er blevet trykket
	switch (ButtonTag) {

		// Snipping Tool
		case 0: 

			// Opdater Knappernes Border Farver
			GlobalVariables::GlobalUseWinSnippingToolButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			GlobalVariables::GlobalUseWin11ScreenRecordToolButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

			// Opdater Det default Video Capturing program for optagning af live view video
			GlobalVariables::DefaultCapturingAppPackageFamilyNameString = _MicrosoftStore_SnippingTool;


		break;

		// Screen Recorder FOr Windows 11
		case 1: 

			// Opdater Knappernes Border Farver
			GlobalVariables::GlobalUseWinSnippingToolButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);
			GlobalVariables::GlobalUseWin11ScreenRecordToolButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

			// Opdater Det default Video Capturing program for optagning af live view video
			GlobalVariables::DefaultCapturingAppPackageFamilyNameString = _MicrosoftStore_ScreenRecorderForWindows11;

		break;

	}

	// Opdater knappernes grafik
	GlobalVariables::GlobalUseWinSnippingToolButton->Refresh();
	GlobalVariables::GlobalUseWin11ScreenRecordToolButton->Refresh();

}

void RMH_ThermalViewer_OpenDefaultVideoCapturingApp() {

	// Routinen åbner den valgte default video capturing applikation

	// Lokale Variabler
	bool AppProcessErrorStatus = false;

	// Åben den valgte default Video Capturing applikation
	AppProcessErrorStatus = RMH_Winforms_OpenWindowsMicrosoftStoreApp(GlobalVariables::DefaultCapturingAppPackageFamilyNameString);

	// Kontroller om der var nogle fejl ved åbningen af appen
	if (AppProcessErrorStatus == true) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Could Not Open The Selected Capturing Program!", _StatusMessageType_Error);

	}
	else {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Opening Video Capturing Program...", _StatusMessageType_Normal);

	}

}

void RMH_ThermalViewer_ToggleRecordingOfRAWDataForPostAnalysis() {

	// Routinen Toggler om der skal gemmes en RAW data optagnings fil

	// Toggle RAW data optagnings flag
	SaveRAWDataRecordingFlag = !SaveRAWDataRecordingFlag;

	// Skal RAW data optagning aktiveres eller deaktiveres
	if (SaveRAWDataRecordingFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalSaveRawAnalysisRecordingButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalSaveRawAnalysisRecordingButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Opdater knap grafik
	GlobalVariables::GlobalSaveRawAnalysisRecordingButton->Refresh();

}

void RMH_ThermalViewer_StartStopVideoRecording() {

	// Routinen starten optagningen af video data

	// Generer og skriv ekstra RAW Meta data til frame data array 
	RMH_AnalysisMode_AddIDAndMetaDataToFrameArray(IRCamera.FrameWidth, IRCamera.FrameHeight, &IRCameraFrameData[0],
		IRCamera.ThermalCameraSupportPool, IRCamera.FrameMetadataSize, IRCamera.FrameWidthPixelOffset, IRCamera.FrameHeightPixelOffset,
		IRCamera.TemperatureCorrectionSetting, IRCamera.AmbientTemperatureSetting, IRCamera.ReflectedTemperatureSetting, IRCamera.HumiditySetting, IRCamera.EmissivitySetting, IRCamera.DistanceSetting);

	// Generer og skriv ekstra RAW Meta data til frame data array - For Pool 3 Kameraer med NUC Korrektion
	RMH_AnalysisMode_AddIDAndMetaDataToFrameArray(IRCamera.FrameWidth, IRCamera.FrameHeight, &FrameThermalData3Band[0],
		IRCamera.ThermalCameraSupportPool, IRCamera.FrameMetadataSize, IRCamera.FrameWidthPixelOffset, IRCamera.FrameHeightPixelOffset,
		IRCamera.TemperatureCorrectionSetting, IRCamera.AmbientTemperatureSetting, IRCamera.ReflectedTemperatureSetting, IRCamera.HumiditySetting, IRCamera.EmissivitySetting, IRCamera.DistanceSetting);

	// Kontroller om video optagning skal startes
	if (VideoRecordingStartedFlag == true && VideoFilesReadyFlag == false) {

		// Indstil Optagningens Globale Framerate Varaibel
		RecordingFrameRateSetValue = (unsigned int)GlobalVariables::GlobalRecordingFrameRateNumericUpDown->Value;

		// Nulstil Video Optagnings Time-Out Tæller Variablet
		RecordingFrameRateTimeOutCounter = 0;

		// Deaktiver brugen af "SaveRawAnalysisRecordingButton" ved start af video optagning
		GlobalVariables::GlobalSaveRawAnalysisRecordingButton->Enabled = false;

		// Kontroller om der skal gemmes en RAW Optagning
		if (SaveRAWDataRecordingFlag == true) {

			// Konfigurerer og klargøre en AVI video fil til optagning af RAW camera data
			RMH_VideoFileRecording_SetupRecordingAnalysisModeVideoFile(GlobalVariables::RecordingDefaultPath, "RAWRecording_", IRCamera.FrameWidth, IRCamera.FrameHeight, RecordingFrameRateSetValue);

		}

		// Hvis Live View Ultra Opløsnings Mode er aktiverede
		if (UltraResolutionEnableFlag == true) {

			// Konfigurerer og klargøre en AVI video fil til optagning af processerede camera data
			RMH_VideoFileRecording_SetupLiveViewCaptureVideoFile(GlobalVariables::RecordingDefaultPath, "Recording_", IRCamera.FrameWidth * UltraResolutionScaleFactor, (IRCamera.FrameHeight - IRCamera.FrameMetadataSize) * UltraResolutionScaleFactor, RecordingFrameRateSetValue);

			// Deaktiver Ultra Opløsnings Knappen I Live-View Tools Panelet
			GlobalVariables::GlobalUltraResolutionButton->Enabled = false;

		}
		else {

			// Konfigurerer og klargøre en AVI video fil til optagning af processerede camera data
			RMH_VideoFileRecording_SetupLiveViewCaptureVideoFile(GlobalVariables::RecordingDefaultPath, "Recording_", IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, RecordingFrameRateSetValue);

		}

		// Opdater optagnings tools knap Border Farve
		GlobalVariables::GlobalRecordingButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

		// Skriv Status Meddelse til GUI Status Text Box
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Video Recording Has Started.", _StatusMessageType_Success);

		// Opdater Video filernes "Ready" flag
		VideoFilesReadyFlag = true;

	}

	// Kontroller om video optagning skal stoppes
	if (VideoRecordingStartedFlag == false && VideoFilesReadyFlag == true) {

		// Nulstil Video filernes "Ready" flag
		VideoFilesReadyFlag = false;

		// Kontroller om der skal gemmes en RAW Optagning
		if (SaveRAWDataRecordingFlag == true) {

			// Luk og gem optagningen af RAW camera data
			RMH_VideoFileRecording_CloseVideoFileWriting(_VideoFileWriteObject_RecordingAnalysisModeFile);

		}

		// Aktiver Ultra Opløsnings Knappen I Live-View Tools Panelet
		GlobalVariables::GlobalUltraResolutionButton->Enabled = true;

		// Luk og gem optagningen processerede camera data
		RMH_VideoFileRecording_CloseVideoFileWriting(_VideoFileWriteObject_LiveViewStreamFile);

		// Nulstil optagnings tools knap Border Farve
		GlobalVariables::GlobalRecordingButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

		// Skriv Status Meddelse til GUI Status Text Box
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Video Recording Has Stopped.", _StatusMessageType_Warning);

		// Aktiver brugen af "SaveRawAnalysisRecordingButton" ved start af video optagning
		GlobalVariables::GlobalSaveRawAnalysisRecordingButton->Enabled = true;

	}

	// Nulstil "Ny optagnings frame" klar flag
	NewRecordFrameAvailableFlag = false;

}

// --------------------- Live View Stream Run/Stop Håndterings Routiner --------------------- //

void RMH_ThermalViewer_ToggleLiveViewStreamRunStop() {

	// Routinen toggler Live View Streamen Run/Stop Stadie

	// Toggle Live View Streamens Run/Stop Flag
	LiveViewRunStopFlag = !LiveViewRunStopFlag;

	// Skal colorbaren inkluderes i snapshot aktiveres eller deaktiveres
	if (LiveViewRunStopFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalLiveViewRunStopButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalLiveViewRunStopButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 255, 0, 0);

	}

	// Opdater knap grafik
	GlobalVariables::GlobalLiveViewRunStopButton->Refresh();

}

void RMH_ThermalViewer_TriggerLiveViewSingleFrameCapture() {

	// Routinen trigger en enkelt Live View data frame capture

	// Opdater Live View Streamens Run/Stop Flag
	LiveViewRunStopFlag = false;

	// Nulstil Knap Border Farve
	GlobalVariables::GlobalLiveViewRunStopButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 255, 255, 0);

	// Opdater knap grafik
	GlobalVariables::GlobalLiveViewRunStopButton->Refresh();

	// Opdater Live View Single frame trigger flag
	LiveViewSingleFrameTriggerFlag = true;

}

// -------------- Termisk Kamera Billede Processerings Og Håndterings Routiner -------------- //

void RMH_ThermalViewer_FrameCrabberCallback() {

	// Routinen eksikverer hver gang at en data frame fra forbundet kamera er blevet modtaget

	// Inkrementer antal læste kamera video frames
	IRCamera.NumbOfCapturedFrames = IRCamera.NumbOfCapturedFrames + 1;
	
	// Aktiver Thread Data Event - Bliver Ikke Brugt 
	//GlobalVariables::ThreadDataReadyEvent->Set();

}

void RMH_ThermalViewer_ImageProcessingSequence() {

	// Routinen detaljerer kamera billede processeringen af den termiske ratiometriske data
	// Og implementeringerne af forskellige billede processerings teknikker.
	// Routinen er skrevet til at være optimeret til at blive eksikverede i en seperat CPU process Thread
	// Håndteringen af Colorbaren data er ligeledes håndterede i denne routine

	// Kontroller Live View Run/Stop og single trigger flags Stadier
	if (LiveViewRunStopFlag == true || LiveViewSingleFrameTriggerFlag == true) {

		// Er Applikationen i "Recording Analysis" Mode
		if (InRecordingAnalysisModeFlag == true) {

			// Læs valgte rå video frame fra åben RAW Fil
			RMH_VideoFileReading_ReadVideoFileFrame(CurrentPlayBackFrameValue, RecordingAnalysisModeFileInfo.NumberOfFrames, &IRCameraFrameData[0]);

			// Hver Læste frame er en ny frame
			IsCapturedFrameNewFlag = true;

		}
		else {

			// Læs rå frame data fra termisk kamera
			IsCapturedFrameNewFlag = RMH_IRThermalCamera_ReadFrameRaw(&IRCameraFrameData[0], &VideoFrameSize);

		}

		// Formater Rå YUY2 Data til 16Bit termisk data array - Læs Dataens Gennemsnitlige værdi
		IRCamera.Tavg_Tmp_Raw = RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(&IRCamera, &IRCameraFrameData[0], &FrameThermalDataRaw[0]);

		// Kontroller om den seneste læste frame er en ny data frame
		if (IsCapturedFrameNewFlag == true && NewRecordFrameAvailableFlag == false) {

			// Opdater "Ny optagnings frame" klar flag
			NewRecordFrameAvailableFlag = true;

		}

		// Opdater Live View Single frame trigger flag
		LiveViewSingleFrameTriggerFlag = false;

	}

	// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
	RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// Læs Maximum, Minimum Og Center Temperaturer
	RMH_ThermalViewer_ReadMaxMinCentTemperatures();

	// ---------------------------------- Generering Af Gaussian Kernel Maske ----------------------------------- //

	// Kontroller om en ny Gaussian Kernel maske skal genereres
	if (NewGaussianKernelMaskGenerateFlag == true) {

		// Nulstil "Der skal genereres en ny Gaussian Kernal Maske" flag
		NewGaussianKernelMaskGenerateFlag = false;

		// Generer Ny Gaussian Kernel Unsharp Maske
		RMH_ImageProcessing_GenerateUnsharpKernelMask(_ImageKernelMaskFilter_Size3x3, ImageUnSharpeningSigma, &GlobalGaussian3x3KernelMask[0]);

	}

	// --------------------------------- ColorBar & Billede Processering Part 1 --------------------------------- //

	// Kontroller om Colorbaren er i automatisk eller manual range mode
	if (ColorBarManualRangeFlag == true && ColorBarManualHighRangeFlag == false && ColorBarManualLowRangeFlag == false) {

		// Set colorbarens maximum og minimum temperatur range værdier
		GlobalVariables::OpenGLColorBar->RMH_OpenGL_SetColorBarMaxMinRangeTemperature(ColorBarInitialManualRangeMaxTemp, ColorBarInitialManualRangeMinTemp);

		// Læs Colorbarens maximum og minimum range værdier i Manual range mode
		ManualTempRangeSetValues = GlobalVariables::OpenGLColorBar->RMH_OpenGL_ReadColorBarRangeMaxMinValues();

		// Er Billede Sharpening aktiverede
		if (LiveViewImageSharpeningEnableFlag == true) {

			// Implementerer Linear Automatisk Gain Kontrol Til billede data - konverter til grayscale - Manual Range
			RMH_IRThermalCamera_LinearAutomaticGainControlTemp(&FrameThermalDataRaw[0], &AGCSharpFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageProcessing_ImageResolution_14Bit, 0,
				ManualTempRangeSetValues.ManualMaxRangeTemp, ManualTempRangeSetValues.ManualMinRangeTemp, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

			// Fortag Billede Skærpning med Gaussian Unsharp Maskering
			RMH_ImageProcessing_2DUnsharpMaskKernelImageSharpening(&AGCSharpFrameDataArray[0], _ImageProcessing_ImageResolution_14Bit, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageKernelMaskFilter_Size3x3, &GlobalGaussian3x3KernelMask[0], ImageSharpeningStrength, ShowUnsharpenMaskImageFlag, &AGCFrameDataArray[0]);

		}
		else {

			// Implementerer Linear Automatisk Gain Kontrol Til billede data - konverter til grayscale - Manual Range
			RMH_IRThermalCamera_LinearAutomaticGainControlTemp(&FrameThermalDataRaw[0], &AGCFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageProcessing_ImageResolution_14Bit, 0,
				ManualTempRangeSetValues.ManualMaxRangeTemp, ManualTempRangeSetValues.ManualMinRangeTemp, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

		}

	}
	else if (ColorBarManualRangeFlag == false && ColorBarManualHighRangeFlag == true && ColorBarManualLowRangeFlag == false) {

		// Set colorbarens maximum og minimum temperatur range værdier
		GlobalVariables::OpenGLColorBar->RMH_OpenGL_SetColorBarMaxMinRangeTemperature(ColorBarInitialManualRangeMaxTemp, MinimumTemperature);

		// Læs Colorbarens maximum og minimum range værdier i Manual range mode
		ManualTempRangeSetValues = GlobalVariables::OpenGLColorBar->RMH_OpenGL_ReadColorBarRangeMaxMinValues();

		// Er Billede Sharpening aktiverede
		if (LiveViewImageSharpeningEnableFlag == true) {

			// Implementerer Linear Automatisk Gain Kontrol Til billede data - konverter til grayscale - Manual Range
			RMH_IRThermalCamera_LinearAutomaticGainControlTemp(&FrameThermalDataRaw[0], &AGCSharpFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageProcessing_ImageResolution_14Bit, 0,
				ManualTempRangeSetValues.ManualMaxRangeTemp, MinimumTemperature, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

			// Fortag Billede Skærpning med Gaussian Unsharp Maskering
			RMH_ImageProcessing_2DUnsharpMaskKernelImageSharpening(&AGCSharpFrameDataArray[0], _ImageProcessing_ImageResolution_14Bit, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageKernelMaskFilter_Size3x3, &GlobalGaussian3x3KernelMask[0], ImageSharpeningStrength, ShowUnsharpenMaskImageFlag, &AGCFrameDataArray[0]);

		}
		else {

			// Implementerer Linear Automatisk Gain Kontrol Til billede data - konverter til grayscale - Manual Range
			RMH_IRThermalCamera_LinearAutomaticGainControlTemp(&FrameThermalDataRaw[0], &AGCFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageProcessing_ImageResolution_14Bit, 0,
				ManualTempRangeSetValues.ManualMaxRangeTemp, MinimumTemperature, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

		}

	}
	else if (ColorBarManualRangeFlag == false && ColorBarManualHighRangeFlag == false && ColorBarManualLowRangeFlag == true) {

		// Set colorbarens maximum og minimum temperatur range værdier
		GlobalVariables::OpenGLColorBar->RMH_OpenGL_SetColorBarMaxMinRangeTemperature(MaximumTemperature, ColorBarInitialManualRangeMinTemp);

		// Læs Colorbarens maximum og minimum range værdier i Manual range mode
		ManualTempRangeSetValues = GlobalVariables::OpenGLColorBar->RMH_OpenGL_ReadColorBarRangeMaxMinValues();

		// Er Billede Sharpening aktiverede
		if (LiveViewImageSharpeningEnableFlag == true) {

			// Implementerer Linear Automatisk Gain Kontrol Til billede data - konverter til grayscale - Manual Range
			RMH_IRThermalCamera_LinearAutomaticGainControlTemp(&FrameThermalDataRaw[0], &AGCSharpFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageProcessing_ImageResolution_14Bit, 0,
				MaximumTemperature, ManualTempRangeSetValues.ManualMinRangeTemp, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

			// Fortag Billede Skærpning med Gaussian Unsharp Maskering
			RMH_ImageProcessing_2DUnsharpMaskKernelImageSharpening(&AGCSharpFrameDataArray[0], _ImageProcessing_ImageResolution_14Bit, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageKernelMaskFilter_Size3x3, &GlobalGaussian3x3KernelMask[0], ImageSharpeningStrength, ShowUnsharpenMaskImageFlag, &AGCFrameDataArray[0]);

		}
		else {

			// Implementerer Linear Automatisk Gain Kontrol Til billede data - konverter til grayscale - Manual Range
			RMH_IRThermalCamera_LinearAutomaticGainControlTemp(&FrameThermalDataRaw[0], &AGCFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageProcessing_ImageResolution_14Bit, 0,
				MaximumTemperature, ManualTempRangeSetValues.ManualMinRangeTemp, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

		}

	}
	else {

		// Set colorbarens maximum og minimum temperatur range værdier
		GlobalVariables::OpenGLColorBar->RMH_OpenGL_SetColorBarMaxMinRangeTemperature(MaximumTemperature, MinimumTemperature);

		// Er Billede Sharpening aktiverede
		if (LiveViewImageSharpeningEnableFlag == true) {

			// Implementerer Linear Automatisk Gain Kontrol Til billede data - konverter til grayscale - Adaptiv Range
			RMH_ImageProcessing_LinearAutomaticGainControlRaw(&FrameThermalDataRaw[0], &AGCSharpFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageProcessing_ImageResolution_14Bit, 0, IRCamera.Tmax_Tmp_Raw, IRCamera.Tmin_Tmp_Raw);

			// Fortag Billede Skærpning med Gaussian Unsharp Maskering
			RMH_ImageProcessing_2DUnsharpMaskKernelImageSharpening(&AGCSharpFrameDataArray[0], _ImageProcessing_ImageResolution_14Bit, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageKernelMaskFilter_Size3x3, &GlobalGaussian3x3KernelMask[0], ImageSharpeningStrength, ShowUnsharpenMaskImageFlag, &AGCFrameDataArray[0]);

		}
		else {

			// Implementerer Linear Automatisk Gain Kontrol Til billede data - konverter til grayscale - Adaptiv Range
			RMH_ImageProcessing_LinearAutomaticGainControlRaw(&FrameThermalDataRaw[0], &AGCFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, _ImageProcessing_ImageResolution_14Bit, 0, IRCamera.Tmax_Tmp_Raw, IRCamera.Tmin_Tmp_Raw);

		}

	}

	// Formater colorbarens Major og Minor tick label strings
	GlobalVariables::OpenGLColorBar->RMH_OpenGL_FormatColorBarTickAndTagLabelStrings(GlobalVariables::DefaultTempUnitString);

	// Opdater Colorbarens Maximum, Minimum og center temperatur indikator piles position
	GlobalVariables::OpenGLColorBar->RMH_OpenGL_UpdateColorBarMaxMinCenterTempArrowsPos(MaximumTemperature, MinimumTemperature, CenterTemperature);

	// ------------------------------ Color Palette & Billede Processering Part 2 ------------------------------- //

	// Læs ColorBar Maximum Og Minimum Tagenes Positioner
	ColorBarMaxMinTagPositions = GlobalVariables::OpenGLColorBar->RMH_OpenGL_ReadColorBarTagsPositions();

	// Skal Live View color palette range skaleres i colorbaren
	if (LiveViewPaletteRangeScalingEnableFlag == true) {

		// Opdater Live View color palette Maximum Og Minimum Range Positioner
		LiveViewPaletteTagPositions = ColorBarMaxMinTagPositions;

	}

	// Kompenser for inverterede live view color palette
	if (InvertLiveViewPaletteFlag == true) {

		// Formater Live view color palette indenfor konfigureret colorbar maximum og minimum Tag temperatur range
		RMH_ImageProcessing_FormatColorPaletteRangeInsideBackgroundPalette(ColorPalettePtr, InvertLiveViewPaletteFlag, AdaptFullColorBarPaletteRangeFlag, ColorBarBackPalettePtr, InvertColorBarBackgroundPaletteFlag,
			LiveViewPaletteTagPositions.MinimumTagPos - 1, LiveViewPaletteTagPositions.MaximumTagPos, FormattedLiveViewPalette);

	}
	else {

		// Formater Live view color palette indenfor konfigureret colorbar maximum og minimum Tag temperatur range
		RMH_ImageProcessing_FormatColorPaletteRangeInsideBackgroundPalette(ColorPalettePtr, InvertLiveViewPaletteFlag, AdaptFullColorBarPaletteRangeFlag, ColorBarBackPalettePtr, InvertColorBarBackgroundPaletteFlag,
			_ImageProcessing_ImageResolution_14Bit - LiveViewPaletteTagPositions.MaximumTagPos, _ImageProcessing_ImageResolution_14Bit - (LiveViewPaletteTagPositions.MinimumTagPos - 1), FormattedLiveViewPalette);

	}

	// Skriv Formaterede Live view color palette til colorbar data struktur 
	GlobalVariables::OpenGLColorBar->RMH_OpenGL_LoadFirstColorPalettesData(FormattedLiveViewPalette);
	
	// Er Dual Color Palette Aktiverede
	if (DualColorPaletteEnableFlag == true) {

		// Skal Dual Live View color palette range skaleres i colorbaren
		if (DualPaletteRangeScalingEnableFlag == true) {

			// Opdater Dual color palette Maximum Og Minimum Range Positioner
			DualLiveViewPaletteTagPositions = ColorBarMaxMinTagPositions;

		}

		// Kompenser for inverterede Dual Live View Color Palette
		if (InvertLiveViewDualPaletteFlag == true) {

			// Formater Live view color palette indenfor konfigureret colorbar maximum og minimum Tag temperatur range
			RMH_ImageProcessing_FormatColorPaletteRangeInsideBackgroundPalette(DualColorPalettePtr, InvertLiveViewDualPaletteFlag, AdaptFullColorBarPaletteRangeFlag, ColorBarBackPalettePtr, InvertColorBarBackgroundPaletteFlag,
				DualLiveViewPaletteTagPositions.MinimumTagPos - 1, DualLiveViewPaletteTagPositions.MaximumTagPos, FormattedDualLiveViewPalette);

		}
		else {

			// Formater Live view color palette indenfor konfigureret colorbar maximum og minimum Tag temperatur range
			RMH_ImageProcessing_FormatColorPaletteRangeInsideBackgroundPalette(DualColorPalettePtr, InvertLiveViewDualPaletteFlag, AdaptFullColorBarPaletteRangeFlag, ColorBarBackPalettePtr, InvertColorBarBackgroundPaletteFlag,
				_ImageProcessing_ImageResolution_14Bit - DualLiveViewPaletteTagPositions.MaximumTagPos, _ImageProcessing_ImageResolution_14Bit - (DualLiveViewPaletteTagPositions.MinimumTagPos - 1), FormattedDualLiveViewPalette);

		}

		// Skriv Formaterede Dual Live view color palette til colorbar data struktur 
		GlobalVariables::OpenGLColorBar->RMH_OpenGL_LoadSecondColorPalettesData(FormattedDualLiveViewPalette);

		// Map frame data til valgte Color Palette format - Med Dual Color Palette
		RMH_ImageProcessing_ApplyOverlayedPaletteToGrayScaleImageData(
			&AGCFrameDataArray[0], &ProcessedThermalImage[0],
			IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize,
			FormattedLiveViewPalette, FormattedDualLiveViewPalette,
			InvertLiveViewPaletteFlag, InvertLiveViewDualPaletteFlag,
			DualPaletteRectPosition.RectangleX0Pos, DualPaletteRectPosition.RectangleY0Pos,
			DualPaletteRectPosition.RectangleWidth, DualPaletteRectPosition.RectangleHeight);

	}
	else {

		// Map frame data til valgte Color Palette format
		RMH_ImageProcessing_ApplyColorPaletteToGrayscaleImageData(&AGCFrameDataArray[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, FormattedLiveViewPalette, InvertLiveViewPaletteFlag, &ProcessedThermalImage[0]);

	}

	// ----------------------------------------------- Histogram ------------------------------------------------ //

	// Er Live view histogram panelet aktiverede
	if (LiveViewHistogramEnableFlag == true && LiveViewHistogramDataReadyFlag == false) {

		// Hvilken Palette skal histogrammet rendereres med
		if (HistogramDualOrLiveViewPaletteFlag == false) {

			// Skal den formaterede eller fulde color palette vises 
			if (HistogramShowRangedPaletteFlag == true) {

				// Load histogram color palette
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_LoadHistogramColorPalette(FormattedLiveViewPalette);

			}
			else {

				// Load histogram color palette
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_LoadHistogramColorPalette(ColorPalettePtr);

			}

		}
		else {

			// Skal den formaterede eller fulde color palette vises 
			if (HistogramShowRangedPaletteFlag == true) {

				// Load histogram color palette
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_LoadHistogramColorPalette(FormattedDualLiveViewPalette);

			}
			else {

				// Load histogram color palette
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_LoadHistogramColorPalette(DualColorPalettePtr);

			}

		}

		// Kontroller om Colorbaren er i automatisk eller manual range mode
		if (ColorBarManualRangeFlag == true && ColorBarManualHighRangeFlag == false && ColorBarManualLowRangeFlag == false) {

			// Er histogrammets Data source Live view dataen
			if (HistogramDataSourceTag == 5) {

				// Formater og fordel Frame data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &FrameThermalDataRaw[0],
					IRCamera.FrameWidth * (IRCamera.FrameHeight - IRCamera.FrameMetadataSize), 
					ManualTempRangeSetValues.ManualMaxRangeTemp, ManualTempRangeSetValues.ManualMinRangeTemp,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			// Er histogrammets Data source Live view Zoom dataen
			else if (HistogramDataSourceTag == 6) {

				// Formater og fordel valgte Zoom ROI data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &ZoomROIxAreaRawPixelValues[0],
					ZoomROIAreaPixelValues.ROIAreaNmbOfPixels, ManualTempRangeSetValues.ManualMaxRangeTemp, ManualTempRangeSetValues.ManualMinRangeTemp,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			else if (HistogramDataSourceTag >= _MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs) {

				// Formater og fordel valgte ROI data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &ROIxAreaRawPixelValues[0],
					ROIAreaPixelValues[HistogramDataSourceTag - (_MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs)].ROIAreaNmbOfPixels,
					ManualTempRangeSetValues.ManualMaxRangeTemp, ManualTempRangeSetValues.ManualMinRangeTemp,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			else {

				// Formater og fordel valgte Linje Data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataLine(&IRCamera, &FrameThermalDataRaw[0],
					&TempLinesPositions[HistogramDataSourceTag].LineXCordinates[0],
					&TempLinesPositions[HistogramDataSourceTag].LineYCordinates[0],
					TempLinesPositions[HistogramDataSourceTag].LinePixelLength,
					ManualTempRangeSetValues.ManualMaxRangeTemp,
					ManualTempRangeSetValues.ManualMinRangeTemp, 
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

			}

		}
		else if (ColorBarManualRangeFlag == false && ColorBarManualHighRangeFlag == true && ColorBarManualLowRangeFlag == false) {

			// Er histogrammets Data source Live view dataen
			if (HistogramDataSourceTag == 5) {

				// Formater og fordel Frame data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &FrameThermalDataRaw[0],
					IRCamera.FrameWidth * (IRCamera.FrameHeight - IRCamera.FrameMetadataSize),
					ManualTempRangeSetValues.ManualMaxRangeTemp, MinimumTemperature,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			// Er histogrammets Data source Live view Zoom dataen
			else if (HistogramDataSourceTag == 6) {

				// Formater og fordel valgte Zoom ROI data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &ZoomROIxAreaRawPixelValues[0],
					ZoomROIAreaPixelValues.ROIAreaNmbOfPixels, ManualTempRangeSetValues.ManualMaxRangeTemp, MinimumTemperature,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			else if (HistogramDataSourceTag >= _MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs) {

				// Formater og fordel valgte ROI data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &ROIxAreaRawPixelValues[0],
					ROIAreaPixelValues[HistogramDataSourceTag - (_MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs)].ROIAreaNmbOfPixels,
					ManualTempRangeSetValues.ManualMaxRangeTemp, MinimumTemperature,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			else {

				// Formater og fordel valgte Linje Data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataLine(&IRCamera, &FrameThermalDataRaw[0],
					&TempLinesPositions[HistogramDataSourceTag].LineXCordinates[0],
					&TempLinesPositions[HistogramDataSourceTag].LineYCordinates[0],
					TempLinesPositions[HistogramDataSourceTag].LinePixelLength,
					ManualTempRangeSetValues.ManualMaxRangeTemp,
					MinimumTemperature,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

			}

		}
		else if (ColorBarManualRangeFlag == false && ColorBarManualHighRangeFlag == false && ColorBarManualLowRangeFlag == true) {

			// Er histogrammets Data source Live view dataen
			if (HistogramDataSourceTag == 5) {

				// Formater og fordel Frame data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &FrameThermalDataRaw[0],
					IRCamera.FrameWidth * (IRCamera.FrameHeight - IRCamera.FrameMetadataSize),
					MaximumTemperature, ManualTempRangeSetValues.ManualMinRangeTemp,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			// Er histogrammets Data source Live view Zoom dataen
			else if (HistogramDataSourceTag == 6) {

				// Formater og fordel valgte Zoom ROI data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &ZoomROIxAreaRawPixelValues[0],
					ZoomROIAreaPixelValues.ROIAreaNmbOfPixels, MaximumTemperature, ManualTempRangeSetValues.ManualMinRangeTemp,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			else if (HistogramDataSourceTag >= _MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs) {

				// Formater og fordel valgte ROI data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataTemp(&IRCamera, &ROIxAreaRawPixelValues[0],
					ROIAreaPixelValues[HistogramDataSourceTag - (_MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs)].ROIAreaNmbOfPixels,
					MaximumTemperature, ManualTempRangeSetValues.ManualMinRangeTemp,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, IRCamera.ThermalCameraSupportPool);

			}
			else {

				// Formater og fordel valgte Linje Data til Histogram Bins - Manuel Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataLine(&IRCamera, &FrameThermalDataRaw[0],
					&TempLinesPositions[HistogramDataSourceTag].LineXCordinates[0],
					&TempLinesPositions[HistogramDataSourceTag].LineYCordinates[0],
					TempLinesPositions[HistogramDataSourceTag].LinePixelLength,
					MaximumTemperature,
					ManualTempRangeSetValues.ManualMinRangeTemp,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

			}

		}
		else {

			// Er histogrammets Data source Live view dataen
			if (HistogramDataSourceTag == 5) {

				// Formater og fordel Frame data til Histogram Bins - Auto Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataRaw(&FrameThermalDataRaw[0],
					IRCamera.FrameWidth * (IRCamera.FrameHeight - IRCamera.FrameMetadataSize), IRCamera.Tmax_Tmp_Raw, IRCamera.Tmin_Tmp_Raw);

			}
			// Er histogrammets Data source Live view Zoom dataen
			else if (HistogramDataSourceTag == 6) {

				// Formater og fordel valgte Zoom ROI data til Histogram Bins - Auto Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataRaw(&ZoomROIxAreaRawPixelValues[0],
					ZoomROIAreaPixelValues.ROIAreaNmbOfPixels, IRCamera.Tmax_Tmp_Raw, IRCamera.Tmin_Tmp_Raw);

			}
			else if (HistogramDataSourceTag >= _MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs) {

				// Formater og fordel valgte ROI data til Histogram Bins - Auto Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataRaw(&ROIxAreaRawPixelValues[0],
					ROIAreaPixelValues[HistogramDataSourceTag - (_MaxNumberOfMovableRectangles - _NumberOfNonMainLiveViewROIs)].ROIAreaNmbOfPixels,
					IRCamera.Tmax_Tmp_Raw, IRCamera.Tmin_Tmp_Raw);

			}
			else {

				// Formater og fordel valgte Linje Data til Histogram Bins - Auto Range
				GlobalVariables::OpenGLHistogram->RMH_OpenGL_FormatHistogramBinDataLine(&IRCamera, &FrameThermalDataRaw[0],
					&TempLinesPositions[HistogramDataSourceTag].LineXCordinates[0],
					&TempLinesPositions[HistogramDataSourceTag].LineYCordinates[0],
					TempLinesPositions[HistogramDataSourceTag].LinePixelLength,
					(RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, IRCamera.Tmax_Tmp_Raw, IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor,
					(RMH_IRThermalCamera_ReadPixelTemperature(&IRCamera, IRCamera.Tmin_Tmp_Raw, IRCamera.ThermalCameraSupportPool) * TemperatureUnitScaleFactor) + TemperatureUnitOffsetFactor,
					TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor);

			}

		}

		// Opdater "Histogram Data Er Klar Til Rengerering" Flaget
		LiveViewHistogramDataReadyFlag = true;

	}

	// ------------------------------------------ Temperatur Tracking ------------------------------------------- //

	// Læs Aktive ROI Max/Min Temperaturerne og Formaterer Tilhørende Label Strings Til Renderering
	RMH_ThermalViewer_ReadAndFormatROITempAndLabels();

	// Læs aktive Temperatur målingers temperaturer og Formaterer Tilhørende Label Strings Til Renderering 
	RMH_ThermalViewer_ReadAndFormatTempMeasurementsAndLabels();

	// Læs aktive Temperatur linjers temperaturer og Formaterer Tilhørende Label Strings Til Renderering 
	RMH_ThermalViewer_ReadAndFormatLinesMaxMinAvgTempsAndLabels();

	// Er maximum temperatur tracking aktiverede
	if (MaxTempTrackingEnableFlag == true) {

		// Formater Max Temperatur label til renderering på live view
		RMH_ThermalViewer_FormatMaximumTemperatureLabel();

	}

	// Er Minimum temperatur tracking aktiverede
	if (MinTempTrackingEnableFlag == true) {

		// Formater Min Temperatur label til renderering på live view
		RMH_ThermalViewer_FormatMinimumTemperatureLabel();

	}

	// Er Center temperatur tracking aktiverede
	if (CenterTempTrackingEnableFlag == true) {

		// Formater Center Temperatur label til renderering på live view
		RMH_ThermalViewer_FormatCenterTemperatureLabel();

	}

	// Hvis Mus Cursor Temperatur tracking er aktiverede
	if (CursorTempTrackEnableFlag == true) {

		// Læs og formater temperatur og label til Mus cursor label renderering på live view
		RMH_ThermalViewer_ReadAndFormatMouseCursorTempAndLabel();

	}

	// ---------------------------------------------- 2D Plot Data ---------------------------------------------- //

	// Er Temperatur Plot Formen i Visning
	if (isTempMeasurementsFormDocked == true || isTempMeasurementsFormUndocked == true) {

		// Tilføj målinger til aktive 2D Plot data Sæt 
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet1SourcePointer, _2DPlotDataSet_1);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet2SourcePointer, _2DPlotDataSet_2);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet3SourcePointer, _2DPlotDataSet_3);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet4SourcePointer, _2DPlotDataSet_4);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet5SourcePointer, _2DPlotDataSet_5);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet6SourcePointer, _2DPlotDataSet_6);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet7SourcePointer, _2DPlotDataSet_7);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet8SourcePointer, _2DPlotDataSet_8);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet9SourcePointer, _2DPlotDataSet_9);
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_AddDataPointToPlotDataSet(*Plot2DDataSet10SourcePointer, _2DPlotDataSet_10);

		// Læs Maximum og Minimums værdien for alle aktive data sæt og indstiller plottets Y-Akse Range varaibler
		GlobalVariables::OpenGL2DPlot->RMH_OpenGL_ReadDataSetsMaxMinDataRangeValues();

	}

	// ------------------------------------------- Temperatur Alarmer ------------------------------------------- //

	// Monitorer aktive temperatur alarmer og opdater deres statuser
	RMH_ThermalViewer_MonitorEnabledTempAlarmsStatus();

	// ---------------------------------------- Live View Statistik Data ---------------------------------------- //

	// Udregn Live View Statistik Vinduets Data
	RMH_ThermalViewer_CalLiveViewStatisticsData();

	// ---------------------------------------------------------------------------------------------------------- //

}

void RMH_ThermalViewer_SecondaryProcessingSequence() {

	// Routinen benyttes som en sekundær processerings thread

	// Lokale varaibler
	unsigned int FrameWidth = IRCamera.FrameWidth; 
	unsigned int FrameHeight = IRCamera.FrameHeight - IRCamera.FrameMetadataSize;

	// Hvis Live View Ultra Opløsnings Mode er aktiverede
	if (UltraResolutionEnableFlag == true && UltraResolutionImageDataReadyFlag == false && UltraResolutionImageDataReadyZoomFlag == false) {

		// Fortag Bilinear 2D Interpolering Af AGC Billede Data
		RMH_ImageProcessing_2DBilinearInterpolation(&AGCFrameDataArray[0], FrameWidth, FrameHeight, FrameWidth * UltraResolutionScaleFactor, FrameHeight * UltraResolutionScaleFactor, &UltraResolutionImage[0]);

		// Er Dual Color Palette Aktiverede
		if (DualColorPaletteEnableFlag == true) {

			// Map frame data til valgte Color Palette format - Med Dual Color Palette
			RMH_ImageProcessing_ApplyOverlayedPaletteToGrayScaleImageData(
				&UltraResolutionImage[0], &PrecessedUltraResolutionImage[0],
				FrameWidth * UltraResolutionScaleFactor, FrameHeight * UltraResolutionScaleFactor,
				FormattedLiveViewPalette, FormattedDualLiveViewPalette,
				InvertLiveViewPaletteFlag, InvertLiveViewDualPaletteFlag,
				DualPaletteRectPosition.RectangleX0Pos * UltraResolutionScaleFactor, DualPaletteRectPosition.RectangleY0Pos * UltraResolutionScaleFactor,
				DualPaletteRectPosition.RectangleWidth * UltraResolutionScaleFactor, DualPaletteRectPosition.RectangleHeight * UltraResolutionScaleFactor);

		}
		else {

			// Map frame data til valgte Color Palette format
			RMH_ImageProcessing_ApplyColorPaletteToGrayscaleImageData(&UltraResolutionImage[0], FrameWidth * UltraResolutionScaleFactor, FrameHeight * UltraResolutionScaleFactor, FormattedLiveViewPalette, InvertLiveViewPaletteFlag, &PrecessedUltraResolutionImage[0]);

		}

		// Opdater "Ultra Opløsnings Billede" Færdig processerede og klar flaget
		UltraResolutionImageDataReadyFlag = true;
		UltraResolutionImageDataReadyZoomFlag = true;

	}

}

void RMH_ThermalViewer_ToggleEnhancedLiveViewResolution() {

	// Routinen aktiverer eller deaktiverer Live view enhanced billed opløsnings mode

	// Håndter nyt stadie for aktiverings flag
	if (EnhancedResEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalEnhancedResButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalEnhancedResButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Aktiver eller deaktiver enhanced billed opløsnings mod
	GlobalVariables::OpenGLRender->RMH_OpenGL_EnableTextureLinearInterpolation(EnhancedResEnableFlag);

}

void RMH_ThermalViewer_ToggleLiveViewImageSharpening() {

	// Routinen aktiverer eller deaktiverer Live view billed Sharpenings featuren

	// Toggle live view billed Sharpenings aktiverings flag
	LiveViewImageSharpeningEnableFlag = !LiveViewImageSharpeningEnableFlag;

	// Håndter nyt stadie for aktiverings flag
	if (LiveViewImageSharpeningEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalImageSharpButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalImageSharpButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

}

void RMH_ThermalViewer_ToggleLiveViewUltraResolution() {

	// Routinen aktiverer eller deaktiverer Live view Ultra billed opløsnings mode

	// Håndtering ag stadiet for aktiverings flag
	if (UltraResolutionEnableFlag == true) {

		// Opdater Knap Border Farve
		GlobalVariables::GlobalUltraResolutionButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Knap Border Farve
		GlobalVariables::GlobalUltraResolutionButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Aktiver eller deaktiver Ultra opløsnings modet
	GlobalVariables::OpenGLRender->RMH_LiveViewStream_UltraResolutionMode(UltraResolutionEnableFlag);

}

// --------------- Live View Aspect Ratio Knap Og Event Håndterings Routiner ---------------- //

void RMH_ThermalViewer_UpdateAspectRatioButtonBorderColor() {

	// Routinen Indstiller start tilstanden for Live View Aspecr ratio knappen

	// Kontroller nuværende aspect ratio indstilling
	if (FixedLiveViewAspectRatio == true) {

		// Opdater aspect ratio knap border farve
		GlobalVariables::GlobalFixedAspectRatioButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Opdater aspect ratio knap border farve
		GlobalVariables::GlobalFixedAspectRatioButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

}

// -------------------- Surface Plot Opdaterings Og Håndterings Routiner -------------------- //

void RMH_ThermalViewer_UpdateSurfacePlotMenuScreen(unsigned int SurfacePlotPanelWidth, unsigned int SurfacePlotPanelHeight) {

	// Routinen opdaterer Surface Plottet med seneste processerede data

	// Render 3. dimensional Surface Plot
	GlobalVariables::OpenGLSurfacePlot->RMH_OpenGL_RenderSurfacePlot(SurfacePlotPanelWidth, SurfacePlotPanelHeight, &ProcessedThermalImage[0], IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, &FrameThermalDataRaw[0], IRCamera.Tmax_Tmp_Raw, IRCamera.Tmin_Tmp_Raw);

}

// ----------------------- 2D Plot Opdaterings Og Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_Update2DPlotMenuScreen(unsigned int PlotPanelWidth, unsigned int PlotPanelHeight) {

	// Routinen opdaterer 2D Plottet med seneste processerede data

	// Render 2. dimensional X/Y Plot
	GlobalVariables::OpenGL2DPlot->RMH_OpenGL_Render2DPlot(PlotPanelWidth, PlotPanelHeight, GlobalVariables::DefaultTempUnitString);

}

// ----------------- Temperatur Alarmer Opdaterings Og Håndterings Routiner ----------------- //

void RMH_ThermalViewer_UpdateTemperatureAlarmsSubMenuStatusLabels() {

	// Routinen opdaterer ralavante temperatur alarmers stauts labels 

	// Opdater aktive temperatur alarmens status labels
	RMH_ThermalViewer_UpdateTempAlarmsStatusLabels();

}

// --------------- Live View Opdaterings, Optagnings Og Håndterings Routiner ---------------- //

void RMH_ThermalViewer_WriteDataToVideoRecordingFilesSequence() {

	// Routinen håndterer skrivningen af relatanv data til video filer, hvis video optagning er startede

	// Kontroller Om En Ny Video Data Frame Er Klar
	if (NewRecordFrameAvailableFlag == true) {

		// Inkrementer Video Optagnings Time-Out Tæller Variablet
		RecordingFrameRateTimeOutCounter = RecordingFrameRateTimeOutCounter + 1;

		// Kontroller Om Video Optagnings Time-Out Tæller Variablet Har Nået Set Punkts Værdien
		if (RecordingFrameRateTimeOutCounter >= (IRCamera.FrameRate / RecordingFrameRateSetValue)) {

			// Håndter skrivningen af valgte Kamera Pool data til video filer, hvis video optagning er startede og klar
			RMH_IRThermalCamera_WriteDataToVideoRecordingFilesSequence(IRCamera.ThermalCameraSupportPool);

			// Nulstil Video Optagnings Time-Out Tæller Variablet
			RecordingFrameRateTimeOutCounter = 0;

		}

		// Nulstil "Ny optagnings frame" klar flag
		NewRecordFrameAvailableFlag = false;

	}

}

// ZOOM TEMPERATUR LABELS - IKKE FÆRDIG !!!
void RMH_ThermalViewer_UpdateLiveView(unsigned int LiveViewPanelWidth, unsigned int LiveViewPanelHeight, bool FixedAspectRatio, unsigned int ColorBarPanelWidth, unsigned int ColorBarPanelHeight, unsigned int HistogramPanelWidth, unsigned int HistogramPanelHeight) {

	// Routinen opdaterer Live View Video Streamen, Colorbaren og live view histogrammet med seneste processerede billed data

	// Lokale variabler
	unsigned int i = 0;

	// Render ColorBar med tilhørende tick linje, labels og yderligere grafiske objekter
	GlobalVariables::OpenGLColorBar->RMH_OpenGL_RenderColorBar(ColorBarPanelWidth, ColorBarPanelHeight, DualColorPaletteEnableFlag, NmbOfColorBarTempTicks, ColorBarCenterTrackEnableFlag, ColorBarManualRangeFlag, ColorBarManualHighRangeFlag, ColorBarManualLowRangeFlag);

	// Hvis Live View Ultra Opløsnings Mode er aktiverede
	if (UltraResolutionEnableFlag == true) {

		// Er Ultra Opløsnings Billede Data Færdig processerede og klar
		if (UltraResolutionImageDataReadyFlag == true) {

			// Render Nyeste processerede Ultra Opløsnings billed data i Live View Texture panel 
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderGrayscaleUltraResolutionImageData(LiveViewPanelWidth, LiveViewPanelHeight,
				PrecessedUltraResolutionImage, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize,
				IRCamera.FrameWidth * UltraResolutionScaleFactor, (IRCamera.FrameHeight - IRCamera.FrameMetadataSize) * UltraResolutionScaleFactor, FixedAspectRatio);

			// Nulstil "Ultra Opløsnings Billede" Færdig processerede og klar flaget
			UltraResolutionImageDataReadyFlag = false;

		}

	}
	else {

		// Render Nyeste processerede billed data i Live View Texture panel 
		GlobalVariables::OpenGLRender->RMH_OpenGL_RenderGrayscale16BitImageData(LiveViewPanelWidth, LiveViewPanelHeight,
			ProcessedThermalImage, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, FixedAspectRatio);

	}

	// Er Dual Color Palette Aktiverede
	if (DualColorPaletteEnableFlag == true) {

		// Renderer Størrelses justerbar rektangel og læs dens position på texturen
		DualPaletteRectPosition = GlobalVariables::OpenGLRender->RMH_OpenGL_RenderMovableRectangle(1, "Palette", 
			ROISelectedColorR, ROISelectedColorG, ROISelectedColorB, ROIPassiveColorR, ROIPassiveColorG, ROIPassiveColorB, false);

	}

	// Render antallet af aktive ROI Rektangler
	for (i = 0; i < NumOfActiveLiveViewROIs; i++) {

		// Renderer Størrelses justerbar ROI rektangel - Med aktive orden og læs ROI position
		ROIRectanglePositions[ActiveROIRenderingOrder[i]] = GlobalVariables::OpenGLRender->RMH_OpenGL_RenderMovableRectangle(
			ActiveROIRenderingOrder[i] + 3, "ROI " + std::to_string(ActiveROIRenderingOrder[i] + 1),
			ROISelectedColorR, ROISelectedColorG, ROISelectedColorB, ROIPassiveColorR, ROIPassiveColorG, ROIPassiveColorB, false);

		// Render ROI Maximum Temperatur Crosshair og label
		GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
			ROIAreaPixelValues[ActiveROIRenderingOrder[i]].ROIMaxPixelWidth,
			ROIAreaPixelValues[ActiveROIRenderingOrder[i]].ROIMaxPixelHeight, true,
			GlobalVariables::ROIMaxTempLabels[ActiveROIRenderingOrder[i]],
			MaxCrosshairColorR, MaxCrosshairColorG, MaxCrosshairColorB);

		// Render ROI Minimum Temperatur Crosshair og label
		GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
			ROIAreaPixelValues[ActiveROIRenderingOrder[i]].ROIMinPixelWidth,
			ROIAreaPixelValues[ActiveROIRenderingOrder[i]].ROIMinPixelHeight, true,
			GlobalVariables::ROIMinTempLabels[ActiveROIRenderingOrder[i]],
			MinCrosshairColorR, MinCrosshairColorG, MinCrosshairColorB);

	}

	// Render antallet af aktive Temperatur Målinger
	for (i = 0; i < NumOfActiveLiveViewTempMeas; i++) {

		// Renderer Positions justerbar Temperatur Målings Crosshair med label
		TempMeasPositions[ActiveTempMeasRenderingOrder[i]] = GlobalVariables::OpenGLRender->RMH_OpenGL_RenderMovableCrossHairWithLabel(
			ActiveTempMeasRenderingOrder[i] + 1, 
			"TM" + (ActiveTempMeasRenderingOrder[i] + 1).ToString() + ": " + GlobalVariables::TempMeasurementsLabels[ActiveTempMeasRenderingOrder[i]],
			TempMeasCrosshairSelectedColorR, TempMeasCrosshairSelectedColorG, TempMeasCrosshairSelectedColorB,
			TempMeasCrosshairPassiveColorR, TempMeasCrosshairPassiveColorG, TempMeasCrosshairPassiveColorB);

	}

	// Render antallet af aktive Temperatur linjer
	for (i = 0; i < NumOfActiveLiveViewLines; i++) {

		// Renderer Positions justerbar Temperatur linjer på live view streamen
		TempLinesPositions[ActiveTempLineRenderingOrder[i]] = GlobalVariables::OpenGLRender->RMH_OpenGL_RenderMovableLine(
			ActiveTempLineRenderingOrder[i] + 1, 2,
			TempLinesSelectedColorR, TempLinesSelectedColorG, TempLinesSelectedColorB, 
			TempLinesPassiveColorR, TempLinesPassiveColorG, TempLinesPassiveColorB);

		// Kontroller Live View Roterings Indstillingen
		if (GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation() == 0) {

			// Render Linje Maximum Temperatur Crosshair og label
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
				TempLinesMaxTempValueXCoordinate[ActiveTempLineRenderingOrder[i]],
				TempLinesMaxTempValueYCoordinate[ActiveTempLineRenderingOrder[i]],
				true, GlobalVariables::TempLinesMaxLabels[ActiveTempLineRenderingOrder[i]],
				MaxCrosshairColorR, MaxCrosshairColorG, MaxCrosshairColorB);

			// Render Linje Minimum Temperatur Crosshair og label
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
				TempLinesMinTempValueXCoordinate[ActiveTempLineRenderingOrder[i]],
				TempLinesMinTempValueYCoordinate[ActiveTempLineRenderingOrder[i]],
				true, GlobalVariables::TempLinesMinLabels[ActiveTempLineRenderingOrder[i]],
				MinCrosshairColorR, MinCrosshairColorG, MinCrosshairColorB);

		}
		if (GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation() == 90) {

			// Render Linje Maximum Temperatur Crosshair og label
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
				LiveViewNativeImageWidth - ((double)TempLinesMaxTempValueYCoordinate[ActiveTempLineRenderingOrder[i]]) * LiveViewNativeImageAspectRatio,
				(double)TempLinesMaxTempValueXCoordinate[ActiveTempLineRenderingOrder[i]] / LiveViewNativeImageAspectRatio,
				true, GlobalVariables::TempLinesMaxLabels[ActiveTempLineRenderingOrder[i]],
				MaxCrosshairColorR, MaxCrosshairColorG, MaxCrosshairColorB);

			// Render Linje Minimum Temperatur Crosshair og label
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
				LiveViewNativeImageWidth - ((double)TempLinesMinTempValueYCoordinate[ActiveTempLineRenderingOrder[i]]) * LiveViewNativeImageAspectRatio,
				(double)TempLinesMinTempValueXCoordinate[ActiveTempLineRenderingOrder[i]] / LiveViewNativeImageAspectRatio,
				true, GlobalVariables::TempLinesMinLabels[ActiveTempLineRenderingOrder[i]],
				MinCrosshairColorR, MinCrosshairColorG, MinCrosshairColorB);

		}
		if (GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation() == 180) {

			// Render Linje Maximum Temperatur Crosshair og label
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
				LiveViewNativeImageWidth - (double)TempLinesMaxTempValueXCoordinate[ActiveTempLineRenderingOrder[i]],
				LiveViewNativeImageHeight - (double)TempLinesMaxTempValueYCoordinate[ActiveTempLineRenderingOrder[i]],
				true, GlobalVariables::TempLinesMaxLabels[ActiveTempLineRenderingOrder[i]],
				MaxCrosshairColorR, MaxCrosshairColorG, MaxCrosshairColorB);

			// Render Linje Minimum Temperatur Crosshair og label
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
				LiveViewNativeImageWidth - (double)TempLinesMinTempValueXCoordinate[ActiveTempLineRenderingOrder[i]],
				LiveViewNativeImageHeight - (double)TempLinesMinTempValueYCoordinate[ActiveTempLineRenderingOrder[i]],
				true, GlobalVariables::TempLinesMinLabels[ActiveTempLineRenderingOrder[i]],
				MinCrosshairColorR, MinCrosshairColorG, MinCrosshairColorB);

		}
		if (GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation() == 270) {

			// Render Linje Maximum Temperatur Crosshair og label
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
				(double)TempLinesMaxTempValueYCoordinate[ActiveTempLineRenderingOrder[i]] * LiveViewNativeImageAspectRatio,
				LiveViewNativeImageHeight - (double)TempLinesMaxTempValueXCoordinate[ActiveTempLineRenderingOrder[i]] / LiveViewNativeImageAspectRatio,
				true, GlobalVariables::TempLinesMaxLabels[ActiveTempLineRenderingOrder[i]],
				MaxCrosshairColorR, MaxCrosshairColorG, MaxCrosshairColorB);

			// Render Linje Minimum Temperatur Crosshair og label
			GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
				(double)TempLinesMinTempValueYCoordinate[ActiveTempLineRenderingOrder[i]] * LiveViewNativeImageAspectRatio,
				LiveViewNativeImageHeight - (double)TempLinesMinTempValueXCoordinate[ActiveTempLineRenderingOrder[i]] / LiveViewNativeImageAspectRatio,
				true, GlobalVariables::TempLinesMinLabels[ActiveTempLineRenderingOrder[i]],
				MinCrosshairColorR, MinCrosshairColorG, MinCrosshairColorB);

		}

	}

	// Er maximum temperatur tracking aktiverede
	if (MaxTempTrackingEnableFlag == true) {

		// Render Maximum temperatur Crosshair med label på live view texturen
		GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
			IRCamera.Tmax_X, IRCamera.Tmax_Y, true, 
			GlobalVariables::MaximumTempLabel, 
			MaxCrosshairColorR, MaxCrosshairColorG, MaxCrosshairColorB);

	}

	// Er Minimum temperatur tracking aktiverede
	if (MinTempTrackingEnableFlag == true) {

		// Render Minimum temperatur Crosshair med label på live view texturen
		GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairWithLabel(
			IRCamera.Tmin_X, IRCamera.Tmin_Y, true,
			GlobalVariables::MinimumTempLabel, 
			MinCrosshairColorR, MinCrosshairColorG, MinCrosshairColorB);

	}

	// Er Center temperatur tracking aktiverede
	if (CenterTempTrackingEnableFlag == true) {

		// Render Minimum temperatur Crosshair med label på live view texturen
		GlobalVariables::OpenGLRender->RMH_OpenGL_RenderCrossHairCenterLabel(
			IRCamera.FrameWidth * 0.5, ((IRCamera.FrameHeight - IRCamera.FrameMetadataSize) * 0.5),
			GlobalVariables::CenterTempLabel, 
			CenterCrosshairColorR, CenterCrosshairColorG, CenterCrosshairColorB);

	}

	// Hvis Mus Cursor Temperatur tracking er aktiverede
	if (CursorTempTrackEnableFlag == true) {

		// Render Mus Cursor Temperatur trackings label
		LiveViewCursorTrackPos = GlobalVariables::OpenGLRender->RMH_OpenGL_RenderMouseCursorLabel(GlobalVariables::MouseCursorTempLabel, CommonLabelColorR, CommonLabelColorG, CommonLabelColorB);

	}

	// Er Live View Split View aktiverede
	if (LiveViewSplitViewEnableFlag == true) {

		// Renderer Størrelses justerbar rektangel til indstilling af Live View Zoom
		ZoomROIRectanglePositions = GlobalVariables::OpenGLRender->RMH_OpenGL_RenderMovableRectangle(2, "Zoom",
			ROISelectedColorR, ROISelectedColorG, ROISelectedColorB, ROIPassiveColorR, ROIPassiveColorG, ROIPassiveColorB, true);

	}
	
	// Marker enden på en Live View OpenGL rendererins sekvens
	GlobalVariables::OpenGLRender->RMH_OpenGL_RenderingFinishedMark();

	// Er Live view histogram panelet aktiverede
	if (LiveViewHistogramEnableFlag == true && LiveViewHistogramDataReadyFlag == true) {

		// Render Live View Histogram i Histogram Panelet
		GlobalVariables::OpenGLHistogram->RMH_OpenGL_RenderHistogram(HistogramPanelWidth, HistogramPanelHeight);

		// Nulstil "Histogram Data Er Klar Til Rengerering" Flaget
		LiveViewHistogramDataReadyFlag = false;

	}

	// Er Live View Split View aktiverede
	if (LiveViewSplitViewEnableFlag == true) {

		// Hvis Live View Ultra Opløsnings Mode er aktiverede
		if (UltraResolutionEnableFlag == true) {

			// Er Ultra Opløsnings Billede Data Færdig processerede og klar
			if (UltraResolutionImageDataReadyZoomFlag == true) {

				// Render Nyeste processerede Ultra Opløsnings billed data i Live View Zoom Texture panel 
				GlobalVariables::LiveViewZoomWindowRender->RMH_LiveView_RenderZoomWindowUltraResolution(GlobalVariables::GlobalLiveViewZoomPanel->Width, GlobalVariables::GlobalLiveViewZoomPanel->Height,
					PrecessedUltraResolutionImage, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize,
					IRCamera.FrameWidth * UltraResolutionScaleFactor, (IRCamera.FrameHeight - IRCamera.FrameMetadataSize) * UltraResolutionScaleFactor, FixedAspectRatio,
					ZoomROIRectanglePositions.RectangleX0Pos, ZoomROIRectanglePositions.RectangleY0Pos, ZoomROIRectanglePositions.RectangleWidth, ZoomROIRectanglePositions.RectangleHeight,
					GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation());

				// Nulstil "Ultra Opløsnings Zoom Billede" Færdig processerede og klar flaget
				UltraResolutionImageDataReadyZoomFlag = false;

			}

		}
		else {

			// Renderer Live View Zoom Vinduet
			GlobalVariables::LiveViewZoomWindowRender->RMH_LiveView_RenderZoomWindow(GlobalVariables::GlobalLiveViewZoomPanel->Width, GlobalVariables::GlobalLiveViewZoomPanel->Height, 
				ProcessedThermalImage, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, FixedAspectRatio,
				ZoomROIRectanglePositions.RectangleX0Pos, ZoomROIRectanglePositions.RectangleY0Pos, ZoomROIRectanglePositions.RectangleWidth, ZoomROIRectanglePositions.RectangleHeight,
				GlobalVariables::OpenGLRender->RMH_LiveView_GetRotation());

		}

		//cout << ZoomROIRectanglePositions.RectangleX0Pos << endl;
		//cout << ZoomROIRectanglePositions.RectangleY0Pos << endl;
		//cout << ZoomROIRectanglePositions.RectangleWidth << endl;
		//cout << ZoomROIRectanglePositions.RectangleHeight << endl;
		//cout << endl;

		// Render ROI Maximum Temperatur Crosshair og label
		//GlobalVariables::LiveViewZoomWindowRender->RMH_LiveView_RenderCrossHairWithLabel(
			//ZoomROIAreaPixelValues.ROIMaxPixelWidth + ZoomROIRectanglePositions.RectangleX0Pos,
			//ZoomROIAreaPixelValues.ROIMaxPixelHeight + ZoomROIRectanglePositions.RectangleX0Pos, true,
			//GlobalVariables::ZoomROIMaxTempLabels,
			//MaxCrosshairColorR, MaxCrosshairColorG, MaxCrosshairColorB);
	
		// Render ROI Minimum Temperatur Crosshair og label
		//GlobalVariables::LiveViewZoomWindowRender->RMH_LiveView_RenderCrossHairWithLabel(
			//ZoomROIAreaPixelValues.ROIMinPixelWidth,
			//ZoomROIAreaPixelValues.ROIMinPixelHeight, true,
			//GlobalVariables::ZoomROIMinTempLabels,
			//MinCrosshairColorR, MinCrosshairColorG, MinCrosshairColorB);



		// Marker enden på en Zoom Winduets OpenGL rendererins sekvens
		GlobalVariables::LiveViewZoomWindowRender->RMH_OpenGL_RenderingFinishedMark();

	}
	else {

		// Nulstil "Ultra Opløsnings Zoom Billede" Færdig processerede og klar flaget
		UltraResolutionImageDataReadyZoomFlag = false;

	}

}

// ------------------------------------------------------------------------------------------ //