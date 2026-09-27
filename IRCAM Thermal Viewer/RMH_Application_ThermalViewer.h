/*
 *  RMH_Application_ThermalViewer.h
 *
 *  Author: Rune Mark Hansen
 *  Date: May 2023
 *
 */

#pragma once

// RMH_Application_ThermalViewer.h
#ifndef RMH_Application_ThermalViewer_H 
#define RMH_Application_ThermalViewer_H

// Kamera konfigurations panelets NumericUpDowns "Start-Op" Max/Min Begrænsninger
#define _TempCorrectionUpDown_DefaultMaxValue     1000.0
#define _TempCorrectionUpDown_DefaultMinValue    -1000.0
#define _AmbientTempUpDown_DefaultMaxValue        85.0
#define _AmbientTempUpDown_DefaultMinValue       -20.0
#define _ReflectedTempUpDown_DefaultMaxValue      85.0
#define _ReflectedTempUpDown_DefaultMinValue     -20.0
#define _DistanceUpDown_DefaultMaxValue           100
#define _DistanceUpDown_DefaultMinValue           1

// ----------------- Applikation Features Aktiverings Håndterings Routiner ------------------ //

void RMH_Application_DisableMainGUIMenuButtons();
void RMH_Application_EnableApplicationFeatures();

// ----------------------- Kamera Konfigurations Håndterings Routiner ----------------------- //

void RMH_ThermalViewer_EnableCameraConfigurationControls(bool EnableState);
void RMH_ThermalViewer_ReadAndDisplayCameraConfigParameters();
void RMH_ThermalViewer_ReadAndDisplayRAWVideoFileCameraConfigParameters();
void RMH_ThermalViewer_ReadAndDisplayRAWSnapShotFileCameraConfigParameters();
void RMH_ThermalViewer_SetCameraConfigParameters();
void RMH_ThermalViewer_SetCameraConfigUpDownRanges(float TemperatureUnitScaleFactor, float TemperatureUnitOffsetFactor);
void RMH_ThermalViewer_RecoverDefaultCameraTempConfiguration();

// ---------------- 2D Temperatur Plot Håndterings & Konfigurations Routiner ---------------- //

void RMH_ThermalViewer_Set2DPlotDataSetSource(double** Plot2DDataSetSourcePointer, unsigned char DataSource);
void RMH_ThermalViewer_Enable2DPlotDataSet(System::Object^ sender);
void RMH_ThermalViewer_Load2DPlotLineColorDataToGlobalArrays();
void RMH_ThermalViewer_Load2DPlotSavedSessionLineColorData();
void RMH_ThermalViewer_Change2DPlotDataSetAndSettingsPanelColor(System::Object^ sender);
void RMH_ThermalViewer_Change2DPlotDataSetLineWidth(System::Object^ sender);
void RMH_ThermalViewer_Change2DPlotDataSetSource(System::Object^ sender);
void RMH_ThermalViewer_Update2DPlotLegendLabels();

// --------------------------- Data Logging Håndterings Routiner ---------------------------- //

void RMH_ThermalViewer_SetDataLoggingSourcePointer(double** DataLoggingSourcePointer, unsigned char DataSource);
void RMH_ThermalViewer_ChangeDataLoggingDataSetSource(unsigned char DataSetIndex, unsigned char DataSourceIndex);
double* RMH_ThermalViewer_GetDataLoggingSourcePointerFromIndex(unsigned char DataSourceIndex);
void RMH_ThermalViewer_UpdateDataLoggingDefaultSaveFilePath(System::Windows::Forms::Label^ DefaultPathString);
void RMH_ThermalViewer_StartDataLogging();
void RMH_ThermalViewer_StopDataLogging();
void RMH_ThermalViewer_UpdateDataLoggingCSVDataDelimiter();
void RMH_ThermalViewer_DataLoggingThreadProcess();

// ------------------------ Temperatur Alarmers Håndterings Routiner ------------------------ //

void RMH_ThermalViewer_SetTempAlarmDataSourcePointer(double** TempAlarmSourcePointer, unsigned char AlarmDataSource);
void RMH_ThermalViewer_ChangeTemperatureAlarmDataSource(System::Object^ sender);
void RMH_ThermalViewer_ChangeTempAlarmConfigType(System::Object^ sender);
void RMH_ThermalViewer_ChangeTempAlarmLowTempSetPoint(System::Object^ sender);
void RMH_ThermalViewer_ChangeTempAlarmHighTempSetPoint(System::Object^ sender);
void RMH_ThermalViewer_ChangeTempAlarmTriggerAction(System::Object^ sender);
void RMH_ThermalViewer_EnableTemperatureAlarm(System::Object^ sender);
void RMH_ThermalViewer_UpdateTempAlarmsStatusLabels();
void RMH_ThermalViewer_ReadTemperatureAlarmStatus(unsigned char TemperatureAlarmIndex, double TemperatureAlarmSourcePointer);
void RMH_ThermalViewer_MonitorEnabledTempAlarmsStatus();
void RMH_ThermalViewer_OpdateTempAlarmTriggerSoundTimer(System::Object^ sender);
void RMH_ThermalViewer_AlarmSoundTimerTickEventHandler();
void RMH_ThermalViewer_EnableAlarmTriggerEvents(System::Object^ sender);
void RMH_ThermalViewer_UpdateAlarmsTriggerEventResetButtonsBorderColor(unsigned char TemperatureAlarmIndex, bool TriggerEventExecutedFlag);
void RMH_ThermalViewer_ResetAlarmTriggerEventExecutedFlag(System::Object^ sender);
void RMH_ThermalViewer_HandleTempAlarmTriggerActionEvent(unsigned char TemperatureAlarmIndex);
void RMH_ThermalViewer_AlarmTriggerEventTimerTickEventHandler();

// ------------------- General Og Periodisk Trigger Håndterings Routiner -------------------- //

void RMH_ThermalViewer_TogglePeriodicTriggerTimer();
void RMH_ThermalViewer_EnableDisableSelectedPeriodicTriggerEvent(System::Object^ sender);
void RMH_ThermalViewer_DisablePeriodicTriggerEventIndex(unsigned int PeriodicTriggerEvent);
void RMH_ThermalViewer_ExecuteTriggerEventIndex(unsigned short TriggerEventFunction);
void RMH_ThermalViewer_ExecuteSelectedPeriodicTriggerEvent(unsigned int PeriodicTriggerEvent);
void RMH_ThermalViewer_PeriodicTriggerEventTimerTickEventHandler();

// ---------------------- Emissivity Tabel Skærm Håndterings Routiner ----------------------- //

void RMH_ThermalViewer_LoadEmissivisyTableValueToThermalCamera(System::Windows::Forms::DataGridViewCellEventArgs^ e);

// --------------------- Kamera Auto Kalibrerings Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_ToggleCameraAutoShutterCalibrationTimer();
void RMH_ThermalViewer_ToggleCameraDriftBasedCalibrationTimer();
void RMH_ThermalViewer_ReadThermalCameraInternalTemps();

// ------------------------ Kamera Afbrydelses Håndterings Routiner ------------------------- //

void RMH_ThermalViewer_HandleSellectedDeviceOrModeChange();
void RMH_ThermalViewer_HandleCameraDisconnectedEvents(bool ShowStatusMEssageFlag);

// --------------------- Kamera Temperatur Enheds Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_ChangeTemperatureUnit(System::Object^ sender);

// ----------------------- Temperatur Trackings Håndterings Routiner ------------------------ //

void RMH_ThermalViewer_ReadMaxMinCentTemperatures();
void RMH_ThermalViewer_FormatMaximumTemperatureLabel();
void RMH_ThermalViewer_FormatMinimumTemperatureLabel();
void RMH_ThermalViewer_FormatCenterTemperatureLabel();
void RMH_ThermalViewer_ReadAndFormatMouseCursorTempAndLabel();
void RMH_ThermalViewer_ReadAndFormatROITempAndLabels();
void RMH_ThermalViewer_ReadAndFormatTempMeasurementsAndLabels();
void RMH_ThermalViewer_ReadAndFormatLinesMaxMinAvgTempsAndLabels();
void RMH_ThermalViewer_ToggleMaximumTempTracking();
void RMH_ThermalViewer_ToggleMinimumTempTracking();
void RMH_ThermalViewer_ToggleCenterTempTracking();
void RMH_ThermalViewer_ToggleMouseCursorTempTracking();

// --------------------- Live View Statistik Data Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_CalLiveViewStatisticsData();
void RMH_ThermalViewer_UpdateAndFormatLiveViewStatisticsLabels();

// ------------------ Fast Temperatur Label Trackings Håndterings Routiner ------------------ //

void RMH_ThermalViewer_UpdateTempMeasurementsRenderingOrder();
void RMH_ThermalViewer_AddTemperatureMeasurementToLiveView();
void RMH_ThermalViewer_DeleteTemperatureMeasurementFromLiveView(System::Object^ sender);
void RMH_ThermalViewer_DeleteAllTemperatureMeasurementFromLiveView();

// --------------------- ROI Temperatur Trackings Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_UpdateROIRenderingOrder();
void RMH_ThermalViewer_AddRegionOfInterestBoxToLiveView();
void RMH_ThermalViewer_DeleteRegionOfInterestBoxFromLiveView(System::Object^ sender);
void RMH_ThermalViewer_DeleteAllRegionOfInterestBoxFromLiveView();

// --------------------- Temperatur Linje Tracking Håndterings Routiner --------------------- //

void RMH_ThermalViewer_UpdateTempLinesRenderingOrder();
void RMH_ThermalViewer_AddTemperatureLineToLiveView();
void RMH_ThermalViewer_DeleteTemperatureLineFromLiveView(System::Object^ sender);
void RMH_ThermalViewer_DeleteAllTemperatureLinesFromLiveView();

// ------------------------ Live View Histogram Håndterings Routiner ------------------------ //

void RMH_ThermalViewer_EnableLiveViewHistogram();
void RMH_ThermalViewer_ChangeHistoramDataSource(System::Object^ sender);

// -------------- Gem Fuld Frame Temperatur Data Til CSV Håndterings Routiner --------------- //

void RMH_ThermalViewer_UpdateFullFrameTemperatureCSVDataDelimiter();
void RMH_ThermalViewer_SaveFullFrameTemperatureDataToCSVFile();

// ----------- Live View Stream Video Optagning Og Snapshot Håndterings Routiner ------------ //

void RMH_ThermalViewer_UpdateSnapshotDefaultSaveFilePath(System::Windows::Forms::Label^ DefaultPathString);
void RMH_ThermalViewer_UpdateVideoRecordingDefaultSaveFilePath(System::Windows::Forms::Label^ DefaultPathString);
void RMH_ThermalViewer_IncludeColorBarInSnapshot();
void RMH_ThermalViewer_ToggleSavinfOfRawSensorDataSnapshot();
void RMH_ThermalViewer_SaveLiveViewSnapshot();
void RMH_ThermalViewer_SaveSurfacePlotSnapshot();
void RMH_ThermalViewer_ConfigDefaultCapturingProgram(System::Object^ sender);
void RMH_ThermalViewer_OpenDefaultVideoCapturingApp();
void RMH_ThermalViewer_ToggleRecordingOfRAWDataForPostAnalysis();
void RMH_ThermalViewer_StartStopVideoRecording();

// --------------------- Live View Stream Run/Stop Håndterings Routiner --------------------- //

void RMH_ThermalViewer_ToggleLiveViewStreamRunStop();
void RMH_ThermalViewer_TriggerLiveViewSingleFrameCapture();

// ------------------ Termisk Kamera Billede Processerings Loops Routiner ------------------- //

void RMH_ThermalViewer_FrameCrabberCallback();
void RMH_ThermalViewer_ImageProcessingSequence();
void RMH_ThermalViewer_SecondaryProcessingSequence();
void RMH_ThermalViewer_ToggleEnhancedLiveViewResolution();
void RMH_ThermalViewer_ToggleLiveViewImageSharpening();
void RMH_ThermalViewer_ToggleLiveViewUltraResolution();

// --------------- Live View Aspect Ratio Knap Og Event Håndterings Routiner ---------------- //

void RMH_ThermalViewer_UpdateAspectRatioButtonBorderColor();

// ------------------ Surface Plot Menu Opdaterings Og Håndterings Routiner ----------------- //

void RMH_ThermalViewer_UpdateSurfacePlotMenuScreen(unsigned int SurfacePlotPanelWidth, unsigned int SurfacePlotPanelHeight);

// ----------------------- 2D Plot Opdaterings Og Håndterings Routiner ---------------------- //

void RMH_ThermalViewer_Update2DPlotMenuScreen(unsigned int PlotPanelWidth, unsigned int PlotPanelHeight);

// ----------------- Temperatur Alarmer Opdaterings Og Håndterings Routiner ----------------- //

void RMH_ThermalViewer_UpdateTemperatureAlarmsSubMenuStatusLabels();

// ------------------- Live View Menu Opdaterings Og Håndterings Routiner ------------------- //

void RMH_ThermalViewer_WriteDataToVideoRecordingFilesSequence();
void RMH_ThermalViewer_UpdateLiveView(unsigned int LiveViewPanelWidth, unsigned int LiveViewPanelHeight, bool FixedAspectRatio, unsigned int ColorBarPanelWidth, unsigned int ColorBarPanelHeight, unsigned int HistogramPanelWidth, unsigned int HistogramPanelHeight);

// ------------------------------------------------------------------------------------------ //

#endif /* RMH_Application_ThermalViewer_H */
