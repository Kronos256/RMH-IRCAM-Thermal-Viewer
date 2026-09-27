
/*
 *  GlobalObjectsAndVariables.cpp
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

// Maximum Frame Data Array Størrelse
#define MaximumFrameDataArraySize       (1600 * 1200 * 3) // Bredde * Højde * Bånd

// Inkluderede Resourcer
#include "GlobalObjectsAndVariables.h"
#include "RMH_ThermalCameraSupport_Library.h"

// Inkluderede Resourcer
#include "RMH_CustomColorPalette_Resources.h"
#include "RMH_TemperatureAlarms_Resources.h"
#include "RMH_GeneralTriggerEvent_Resources.h"

// Definition af globale Extern Objekter
IRCameraDeviceFormat IRCamera;

// Live view elementers Farve globale variable
bool EnableLabelBackgroundFlag = true;
unsigned char CommonLabelColorR = 255;
unsigned char CommonLabelColorG = 255;
unsigned char CommonLabelColorB = 255;
unsigned char CommonLabelBackgroundColorR = 35;
unsigned char CommonLabelBackgroundColorG = 35;
unsigned char CommonLabelBackgroundColorB = 35;
unsigned char MaxCrosshairColorR = 255;
unsigned char MaxCrosshairColorG = 0;
unsigned char MaxCrosshairColorB = 0;
unsigned char MinCrosshairColorR = 0;
unsigned char MinCrosshairColorG = 127;
unsigned char MinCrosshairColorB = 255;
unsigned char CenterCrosshairColorR = 255;
unsigned char CenterCrosshairColorG = 255;
unsigned char CenterCrosshairColorB = 255;
unsigned char ROISelectedColorR = 0;
unsigned char ROISelectedColorG = 255;
unsigned char ROISelectedColorB = 0;
unsigned char ROIPassiveColorR = 255;
unsigned char ROIPassiveColorG = 255;
unsigned char ROIPassiveColorB = 255;
unsigned char TempMeasCrosshairSelectedColorR = 0;
unsigned char TempMeasCrosshairSelectedColorG = 255;
unsigned char TempMeasCrosshairSelectedColorB = 0;
unsigned char TempMeasCrosshairPassiveColorR = 255;
unsigned char TempMeasCrosshairPassiveColorG = 255;
unsigned char TempMeasCrosshairPassiveColorB = 255;
unsigned char TempLinesSelectedColorR = 0;
unsigned char TempLinesSelectedColorG = 255;
unsigned char TempLinesSelectedColorB = 0;
unsigned char TempLinesPassiveColorR = 255;
unsigned char TempLinesPassiveColorG = 255;
unsigned char TempLinesPassiveColorB = 255;

// GUI form positions flag
bool isWelcomeScreenFormOpen = false;
bool isWelcomeScreenFormDocked = false;
bool isWelcomeScreenFormUndocked = false;
bool isUserGuideFormOpen = false;
bool isUserGuideFormDocked = false;
bool isUserGuideFormUndocked = false;
bool isThermalCameraFormOpen = false;
bool isThermalCameraFormDocked = false;
bool isThermalCameraFormUndocked = false;
bool isLiveViewStreamFormOpen = false;
bool isLiveViewStreamFormDocked = false;
bool isLiveViewStreamFormUndocked = false;
bool isSurfacePlotFormOpen = false;
bool isSurfacePlotFormDocked = false;
bool isSurfacePlotFormUndocked = false;
bool isTempMeasurementsFormOpen = false;
bool isTempMeasurementsFormDocked = false;
bool isTempMeasurementsFormUndocked = false;
bool isEmissivityTableFormOpen = false;
bool isEmissivityTableFormDocked = false;
bool isEmissivityTableFormUndocked = false;
bool isLiveViewToolsFormOpen = false;
bool isLiveViewToolsFormDocked = false;
bool isLiveViewToolsFormUndocked = false;

// Definition af globale Extern Variabler
bool ThreadStoppedFlag = false;
bool ThreadDataReadyFlag = false;
bool CameraConnectErrorFlag = false;
bool InvertLiveViewPaletteFlag = false;
bool InvertLiveViewDualPaletteFlag = false;
bool InvertColorBarBackgroundPaletteFlag = false;
unsigned short (*ColorPalettePtr)[_ImageProcessing_ImageResolution_14Bit + 1] = RMH_CustomPalette_IsoRainBow2;
unsigned short (*DualColorPalettePtr)[_ImageProcessing_ImageResolution_14Bit + 1] = RMH_CustomPalette_Gray;
unsigned short (*ColorBarBackPalettePtr)[_ImageProcessing_ImageResolution_14Bit + 1] = RMH_CustomPalette_Gray;
unsigned int SelectedColorPaletteIndex = _ColorPaletteIndex_IsoRainBow2;
unsigned int SelectedDualColorPaletteIndex = _ColorPaletteIndex_Gray;
float SavedTempCorrectionSetting = 0.0;
float TemperatureUnitScaleFactor = 1.0;
float TemperatureUnitOffsetFactor = 0.0;
unsigned int VideoFrameSize = 0;
unsigned char TempUnitState = 1;
unsigned char TempUnitOldstate = 1;
unsigned short AGCFrameDataArray[MaximumFrameDataArraySize] = { 0 };
unsigned short AGCSharpFrameDataArray[MaximumFrameDataArraySize] = { 0 };
unsigned short ProcessedThermalImage[MaximumFrameDataArraySize] = { 0 };
unsigned short UltraResolutionImage[MaximumFrameDataArraySize] = { 0 };
unsigned short PrecessedUltraResolutionImage[MaximumFrameDataArraySize] = { 0 };
unsigned char IRCameraFrameData[MaximumFrameDataArraySize] = { 0 };
unsigned char FrameThermalData3Band[MaximumFrameDataArraySize] = { 0 };
unsigned short FrameThermalDataRaw[MaximumFrameDataArraySize] = { 0 };
float FrameThermalDataTemp[MaximumFrameDataArraySize] = { 0 };
unsigned short ClosedShutterCMOSBaselineData[MaximumFrameDataArraySize] = { 0 };
double ImageCMOSNonUniformityMapData[MaximumFrameDataArraySize] = { 0 };
double FrameTemperatureData[MaximumFrameDataArraySize] = { 0 };
unsigned short ROIxAreaRawPixelValues[MaximumFrameDataArraySize] = { 0 };
unsigned short ZoomROIxAreaRawPixelValues[MaximumFrameDataArraySize] = { 0 };
bool ROIxReturnAreaRawPixelValsFlags[_MaxNumberOfMovableRectangles - 1] = { false, false, false, false, false, false, false, false, false, false };
unsigned char SelectedThermalCameraIndex = 5;
bool FixedLiveViewAspectRatio = true;
bool ThermalCameraHighRangeFlag = false;
bool DualColorPaletteEnableFlag = false;
bool MaxTempTrackingEnableFlag = false;
bool MinTempTrackingEnableFlag = false;
bool CenterTempTrackingEnableFlag = false;
double MaximumTemperature = 0.0;
double MinimumTemperature = 0.0;
double AverageTemperature = 0.0;
double CenterTemperature = 0.0;
double TemperatureSpan = 0.0;
double ThermalCameraRangeUsage = 0.0;
double MaxPeakTemperature = 0.0;
double MinPeakTemperature = 2000.0;
double CurrentCalDetectorTemperature = 0.0;
double SensorTemperatureCalDrift = 0.0;
double SensorDriftError = 0.0;
bool EnhancedResEnableFlag = true;
bool UltraResolutionEnableFlag = true;
bool CursorTempTrackEnableFlag = false;
double CursorTemperature = 0.0;
unsigned char NumOfActiveLiveViewROIs = 0;
unsigned char NumOfActiveLiveViewTempMeas = 0;
unsigned char NumOfActiveLiveViewLines = 0;
bool ColorBarManualRangeFlag = false;
bool ColorBarManualHighRangeFlag = false;
bool ColorBarManualLowRangeFlag = false;
bool ColorBarCenterTrackEnableFlag = false;
double ColorBarInitialManualRangeMaxTemp = 0.0f;
double ColorBarInitialManualRangeMinTemp = 0.0f;
double ColorBarManualMaxTempRange = 0.0f;
double ColorBarManualMinTempRange = 0.0f;
bool ColorBarDialogIsShownFlag = false;
bool InputValueDialogIsShownFlag = false;
bool LiveViewPaletteRangeScalingEnableFlag = true;
bool DualPaletteRangeScalingEnableFlag = false;
unsigned char NmbOfColorBarTempTicks = 15;
bool IncludeColorBarSnapshotFlag = true;
bool CaptureRawSensorSnapshotFlag = true;
bool LiveViewHistogramEnableFlag = false;
bool LiveViewHistogramDataReadyFlag = false;
bool HistogramDualOrLiveViewPaletteFlag = false; // Default: Benyt Live View Palette
bool HistogramShowRangedPaletteFlag = true;
unsigned char HistogramDataSourceTag = 5;
bool LiveViewImageSharpeningEnableFlag = true;
float ImageSharpeningStrength = 1.5;  // Default Styrke 1.5 
float ImageUnSharpeningSigma = 2; // Default Standard Deviation
bool NewGaussianKernelMaskGenerateFlag = false;
float GlobalGaussian3x3KernelMask[_ImageKernelMaskFilter_Size3x3] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 }; // Sigma = 1
float GlobalGaussian5x5KernelMask[_ImageKernelMaskFilter_Size5x5] = { 1, 4, 6, 4, 1, 4, 16, 24, 16, 4, 6, 24, 36, 24, 6, 4, 16, 24, 16, 4, 1, 4, 6, 4, 1 }; // Sigma = 1
bool ShowUnsharpenMaskImageFlag = false;
bool AutoShutterCalEnableFlag = false;
bool DriftBasedCalEnableFlag = false;
bool TempMeasGUIReadyFlag = false;
bool LiveViewRunStopFlag = true; // True = Run, False = Stop
bool LiveViewSingleFrameTriggerFlag = false;
bool AdaptFullColorBarPaletteRangeFlag = true;
bool LiveViewToolsPanelVisibilityFlag = true;
bool ColorBarPanelVisibilityFlag = true;
bool SaveRAWDataRecordingFlag = true;
bool VideoRecordingStartedFlag = false;
bool VideoFilesReadyFlag = false;
bool IsCapturedFrameNewFlag = false;
bool NewRecordFrameAvailableFlag = false;
bool InRecordingAnalysisModeFlag = false;
bool InSnapShotAnalysisModeFlag = false;
bool RAWFileIDStringMatchFlag = false;
bool OpenVideoPlayBackControlsFormFlag = false;
bool CloseVideoPlayBackControlsFormFlag = false;
bool VideoPlaybackControlsFormIsOpenFlag = false;
unsigned long CurrentPlayBackFrameValue = 0;
bool VideoPlayBackControlsPlayStopFlag = false; // Stop = false, Play = true
unsigned char SelectedFullFrameTempCSVDataDelimiterIndex = 0;
unsigned char SelectedDataLoggingCSVDataDelimiterIndex = 0;
unsigned char* SnapShotAnalysisModeImageData = nullptr;
double ImageCMOSBaselineMeanValue = 0.0;
bool PopUpDialogDontShowFlag = false;
bool LiveViewStatisticsWindowIsShownFlag = false;
double TempDriftCalibrationSetValue = 1.0;
unsigned int UltraResolutionScaleFactor = 2;
bool PeriodicTriggerTimerEnableFlag = false;
double LiveViewNativeImageWidth = 100.0;
double LiveViewNativeImageHeight = 100.0;
double LiveViewNativeImageAspectRatio = 1.0;
bool UltraResolutionImageDataReadyFlag = false;
bool UltraResolutionImageDataReadyZoomFlag = false;
unsigned int RemainingTrialDays = 0;
bool LiveViewSplitViewEnableFlag = false;
double TempLinesTemperatureValues[_MaxNumberOfMovableLines][_MovableLinesMaxPixelLength];
unsigned int RecordingFrameRateSetValue = 25;
unsigned int RecordingFrameRateTimeOutCounter = 0;

// Data Logging Objekter og variabler
bool DataLoggingIsRunningFlag = false;
unsigned char DataLoggingNumberOfActiveSets = 0;
unsigned long DataLoggingIntervalMilliSec = 1000;
unsigned long DataLoggingDurationTimerMilliSec = 0;
unsigned long DataLoggingSessionDurationMilliSec = 0;
double DataLoggingSourceDataArray[_2DPlotMaxNumberOfDataSets];
double* DataLoggingDataSet1SourcePointer = &MaximumTemperature;
double* DataLoggingDataSet2SourcePointer = &MinimumTemperature;
double* DataLoggingDataSet3SourcePointer = &CenterTemperature;
double* DataLoggingDataSet4SourcePointer = &TempMeasurementValues[0];
double* DataLoggingDataSet5SourcePointer = &TempMeasurementValues[1];
double* DataLoggingDataSet6SourcePointer = &TempLinesMaxTempValues[0];
double* DataLoggingDataSet7SourcePointer = &TempLinesMinTempValues[0];
double* DataLoggingDataSet8SourcePointer = &ROIAreaPixelValues[0].MaxValue;
double* DataLoggingDataSet9SourcePointer = &ROIAreaPixelValues[0].MinValue;
double* DataLoggingDataSet10SourcePointer = &CursorTemperature;

// Temperatur Alarm Variabler og Objekter
bool TempAlarmsConfigMenuIsOpen = false;
bool TempAlarmTriggerSoundFlag = false;
bool TempAlarmsTriggerEventsEnableFlag = false;
float TempAlarmsLowTempValues[_MaxNumberOfConfigurableTempAlarms] = { 10.0, 10.0, 10.0, 10.0, 10.0 };
float TempAlarmsHighTempValues[_MaxNumberOfConfigurableTempAlarms] = { 60.0, 60.0, 60.0, 60.0, 60.0 };
unsigned char TempAlarmsConfigType[_MaxNumberOfConfigurableTempAlarms] = { 0, 0, 0, 0, 0 };
unsigned char TempAlarmsTriggerAction[_MaxNumberOfConfigurableTempAlarms] = { 0, 0, 0, 0, 0 };
bool EnabledTempAlarmsArray[_MaxNumberOfConfigurableTempAlarms] = { false, false, false, false, false};
bool AlarmsTriggerStatusArray[_MaxNumberOfConfigurableTempAlarms] = { false, false, false, false, false };
bool TriggerEventExecutedFlag[_MaxNumberOfConfigurableTempAlarms] = { false, false, false, false, false };
double* TempAlarm1DataSourcePointer = &MaximumTemperature;
double* TempAlarm2DataSourcePointer = &MinimumTemperature;
double* TempAlarm3DataSourcePointer = &CenterTemperature;
double* TempAlarm4DataSourcePointer = &TempMeasurementValues[0];
double* TempAlarm5DataSourcePointer = &TempMeasurementValues[1];

// 2D Plot Data Sæt Source Pointers
unsigned char Plot2DDataSetLineColorsR[_2DPlotMaxNumberOfDataSets] = {255,  0, 50,255,255,255,  0,255,128,128};
unsigned char Plot2DDataSetLineColorsG[_2DPlotMaxNumberOfDataSets] = {  0,  0,205,255,128,  0,255,255,128,255};
unsigned char Plot2DDataSetLineColorsB[_2DPlotMaxNumberOfDataSets] = {  0,255, 50,  0,  0,255,255,255,128,128};
double *Plot2DDataSet1SourcePointer = &MaximumTemperature;
double *Plot2DDataSet2SourcePointer = &MinimumTemperature;
double *Plot2DDataSet3SourcePointer = &CenterTemperature;
double *Plot2DDataSet4SourcePointer = &TempMeasurementValues[0];
double *Plot2DDataSet5SourcePointer = &TempMeasurementValues[1];
double *Plot2DDataSet6SourcePointer = &TempLinesMaxTempValues[0];
double *Plot2DDataSet7SourcePointer = &TempLinesMinTempValues[0];
double *Plot2DDataSet8SourcePointer = &ROIAreaPixelValues[0].MaxValue;
double *Plot2DDataSet9SourcePointer = &ROIAreaPixelValues[0].MinValue;
double *Plot2DDataSet10SourcePointer = &CursorTemperature;

// Generalle Og Periodiske Trigger Event Timer Objekter og variabler
bool PeriodicTriggerEventEnableFlags[_MaxNumberOfConfigurablePeriodicTriggerEvents] = { false, false, false, false, false };
unsigned int PeriodicEventTriggerCounter[_MaxNumberOfConfigurablePeriodicTriggerEvents] = { 0, 0, 0, 0, 0 };


