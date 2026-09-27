
/*
 *  GlobalObjectsAndVariables.h
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

#pragma once

// GlobalObjectsAndVariables.h
#ifndef GlobalObjectsAndVariables_H 
#define GlobalObjectsAndVariables_H

// Inkluderede biblioteker
#include "RMH_OpenGL_Winforms.h"
#include "RMH_OpenGL_ColorBar.h"
#include "RMH_OpenGL_Histogram.h"
#include "RMH_OpenGL_SurfacePlot.h"
#include "RMH_OpenGL_2DPlot.h"
#include "RMH_LiveView_ZoomWindow.h"
#include "RMH_ThermalCameraSupport_Library.h"
#include "RMH_AnalysisMode_Routines.h"
#include "RMH_ImageProcessing_Library.h"
#include "RMH_GeneralTriggerEvent_Resources.h"

// tilhørende name spaces
using namespace ThermalCameraDevice;
using namespace OpenGLWinForms;
using namespace OpenGLColorBar;
using namespace OpenGL2DPlot;

// ------------------------------- Globale "Normale" Variabler ------------------------------- //

// Gemte Applikations Parametere
extern float SavedTempCorrectionSetting;
extern unsigned char SelectedThermalCameraIndex;
extern unsigned int SelectedColorPaletteIndex;
extern unsigned int SelectedDualColorPaletteIndex;

// Diverse Globale statiske/extern Objekter og variabler
extern IRCameraDeviceFormat IRCamera;
static ColorBarManualRangeTemps ManualTempRangeSetValues;
static ColorBarTagPosition ColorBarMaxMinTagPositions;
static ColorBarTagPosition LiveViewPaletteTagPositions;
static ColorBarTagPosition DualLiveViewPaletteTagPositions;
static RectangelPosition DualPaletteRectPosition;
static MouseCursorPosition LiveViewCursorTrackPos;
static RectangelPosition ROIRectanglePositions[_MaxNumberOfMovableRectangles - 1];
static ROIAreaPixelInfoFormat ROIAreaPixelValues[_MaxNumberOfMovableRectangles - 1];
static RectangelPosition ZoomROIRectanglePositions;
static ROIAreaPixelInfoFormat ZoomROIAreaPixelValues;
static CrosshairWLabelPosition TempMeasPositions[_MaxNumberOfMovableCrosshairs];
static double TempMeasurementValues[_MaxNumberOfMovableCrosshairs];
static LineSpecsPosition TempLinesPositions[_MaxNumberOfMovableLines];
static double TempLinesMaxTempValues[_MaxNumberOfMovableLines];
static double TempLinesMinTempValues[_MaxNumberOfMovableLines];
static double TempLinesAvgTempValues[_MaxNumberOfMovableLines];
extern double TempLinesTemperatureValues[_MaxNumberOfMovableLines][_MovableLinesMaxPixelLength];
static unsigned short TempLinesMaxTempValueXCoordinate[_MaxNumberOfMovableLines];
static unsigned short TempLinesMaxTempValueYCoordinate[_MaxNumberOfMovableLines];
static unsigned short TempLinesMinTempValueXCoordinate[_MaxNumberOfMovableLines];
static unsigned short TempLinesMinTempValueYCoordinate[_MaxNumberOfMovableLines];
static RAWVideoFileInfo RecordingAnalysisModeFileInfo;
static RAWSnapShotFileInfo SnapShotAnalysisModeFileInfo;
static RAWFileIDFormat RecordingAnalysisModeFileMetaData;
static RAWFileIDFormat SnapShotAnalysisModeFileMetaData;

// Diverse Globale Variabler
extern unsigned int VideoFrameSize;
extern bool CameraConnectErrorFlag; 
extern unsigned char TempUnitState;
extern unsigned char TempUnitOldstate;
extern float TemperatureUnitScaleFactor;
extern float TemperatureUnitOffsetFactor;
extern bool InvertLiveViewPaletteFlag;
extern bool InvertLiveViewDualPaletteFlag;
extern bool InvertColorBarBackgroundPaletteFlag;
extern unsigned short (*ColorPalettePtr)[_ImageProcessing_ImageResolution_14Bit + 1];
extern unsigned short (*DualColorPalettePtr)[_ImageProcessing_ImageResolution_14Bit + 1];
extern unsigned short (*ColorBarBackPalettePtr)[_ImageProcessing_ImageResolution_14Bit + 1];
extern unsigned short AGCFrameDataArray[];
extern unsigned short AGCSharpFrameDataArray[];
extern unsigned short ProcessedThermalImage[];
extern unsigned short UltraResolutionImage[];
extern unsigned short PrecessedUltraResolutionImage[];
extern unsigned char IRCameraFrameData[];
extern unsigned char FrameThermalData3Band[];
extern unsigned short FrameThermalDataRaw[];
extern float FrameThermalDataTemp[];
extern unsigned short ClosedShutterCMOSBaselineData[];
extern double ImageCMOSNonUniformityMapData[];
extern double FrameTemperatureData[];
extern unsigned short ROIxAreaRawPixelValues[];
extern unsigned short ZoomROIxAreaRawPixelValues[];
extern bool ROIxReturnAreaRawPixelValsFlags[_MaxNumberOfMovableRectangles - 1];
extern bool ThreadDataReadyFlag;
extern bool ThreadStoppedFlag;
extern bool FixedLiveViewAspectRatio;
extern bool ThermalCameraHighRangeFlag;
extern bool DualColorPaletteEnableFlag;
extern bool MaxTempTrackingEnableFlag;
extern bool MinTempTrackingEnableFlag;
extern bool CenterTempTrackingEnableFlag;
extern double MaximumTemperature;
extern double MinimumTemperature;
extern double AverageTemperature;
extern double CenterTemperature;
extern double TemperatureSpan;
extern double ThermalCameraRangeUsage;
extern double MaxPeakTemperature;
extern double MinPeakTemperature;
extern double CurrentCalDetectorTemperature;
extern double SensorTemperatureCalDrift;
extern double SensorDriftError;
extern bool EnhancedResEnableFlag;
extern bool UltraResolutionEnableFlag;
extern bool CursorTempTrackEnableFlag;
extern double CursorTemperature;
extern unsigned char NumOfActiveLiveViewROIs;
extern unsigned char NumOfActiveLiveViewTempMeas;
extern unsigned char NumOfActiveLiveViewLines;
extern bool ColorBarManualRangeFlag;
extern bool ColorBarManualHighRangeFlag;
extern bool ColorBarManualLowRangeFlag;
extern bool ColorBarCenterTrackEnableFlag;
extern double ColorBarInitialManualRangeMaxTemp;
extern double ColorBarInitialManualRangeMinTemp;
extern double ColorBarManualMaxTempRange;
extern double ColorBarManualMinTempRange;
extern bool ColorBarDialogIsShownFlag;
extern bool InputValueDialogIsShownFlag;
extern bool LiveViewPaletteRangeScalingEnableFlag;
extern bool DualPaletteRangeScalingEnableFlag;
extern unsigned char NmbOfColorBarTempTicks;
extern bool IncludeColorBarSnapshotFlag;
extern bool CaptureRawSensorSnapshotFlag;
extern bool LiveViewHistogramEnableFlag;
extern bool LiveViewHistogramDataReadyFlag;
extern bool HistogramDualOrLiveViewPaletteFlag;
extern bool HistogramShowRangedPaletteFlag;
extern unsigned char HistogramDataSourceTag;
extern bool LiveViewImageSharpeningEnableFlag;
extern float ImageSharpeningStrength;
extern float ImageUnSharpeningSigma;
extern bool NewGaussianKernelMaskGenerateFlag;
extern float GlobalGaussian3x3KernelMask[];
extern float GlobalGaussian5x5KernelMask[];
extern bool ShowUnsharpenMaskImageFlag;
extern bool AutoShutterCalEnableFlag;
extern bool DriftBasedCalEnableFlag;
extern bool TempMeasGUIReadyFlag;
extern bool LiveViewRunStopFlag;
extern bool LiveViewSingleFrameTriggerFlag;
extern bool AdaptFullColorBarPaletteRangeFlag;
extern bool LiveViewToolsPanelVisibilityFlag;
extern bool ColorBarPanelVisibilityFlag;
extern bool SaveRAWDataRecordingFlag;
extern bool VideoRecordingStartedFlag;
extern bool VideoFilesReadyFlag;
extern bool IsCapturedFrameNewFlag;
extern bool NewRecordFrameAvailableFlag;
extern bool InRecordingAnalysisModeFlag;
extern bool InSnapShotAnalysisModeFlag;
extern bool RAWFileIDStringMatchFlag;
extern bool OpenVideoPlayBackControlsFormFlag;
extern bool CloseVideoPlayBackControlsFormFlag;
extern bool VideoPlaybackControlsFormIsOpenFlag;
extern unsigned long CurrentPlayBackFrameValue;
extern bool VideoPlayBackControlsPlayStopFlag; 
extern unsigned char SelectedFullFrameTempCSVDataDelimiterIndex;
extern unsigned char SelectedDataLoggingCSVDataDelimiterIndex;
extern unsigned char* SnapShotAnalysisModeImageData;
extern double ImageCMOSBaselineMeanValue;
extern bool PopUpDialogDontShowFlag;
extern bool LiveViewStatisticsWindowIsShownFlag;
extern double TempDriftCalibrationSetValue;
extern unsigned int UltraResolutionScaleFactor;
extern bool PeriodicTriggerTimerEnableFlag;
extern double LiveViewNativeImageWidth;
extern double LiveViewNativeImageHeight;
extern double LiveViewNativeImageAspectRatio;
extern bool UltraResolutionImageDataReadyFlag;
extern bool UltraResolutionImageDataReadyZoomFlag;
extern unsigned int RemainingTrialDays;
extern bool LiveViewSplitViewEnableFlag;
extern unsigned int RecordingFrameRateSetValue;
extern unsigned int RecordingFrameRateTimeOutCounter;

// Data Logging Objekter og variabler
extern bool DataLoggingIsRunningFlag;
extern unsigned char DataLoggingNumberOfActiveSets;
extern unsigned long DataLoggingIntervalMilliSec;
extern unsigned long DataLoggingDurationTimerMilliSec;
extern unsigned long DataLoggingSessionDurationMilliSec;
extern double DataLoggingSourceDataArray[_2DPlotMaxNumberOfDataSets];
extern double* DataLoggingDataSet1SourcePointer;
extern double* DataLoggingDataSet2SourcePointer;
extern double* DataLoggingDataSet3SourcePointer;
extern double* DataLoggingDataSet4SourcePointer;
extern double* DataLoggingDataSet5SourcePointer;
extern double* DataLoggingDataSet6SourcePointer;
extern double* DataLoggingDataSet7SourcePointer;
extern double* DataLoggingDataSet8SourcePointer;
extern double* DataLoggingDataSet9SourcePointer;
extern double* DataLoggingDataSet10SourcePointer;

// Temperatur Alarm Variabler og Objekter
extern bool TempAlarmsConfigMenuIsOpen;
extern bool TempAlarmTriggerSoundFlag;
extern bool TempAlarmsTriggerEventsEnableFlag;
extern float TempAlarmsLowTempValues[];
extern float TempAlarmsHighTempValues[];
extern unsigned char TempAlarmsConfigType[];
extern unsigned char TempAlarmsTriggerAction[];
extern bool TriggerEventExecutedFlag[];
extern bool EnabledTempAlarmsArray[];
extern bool AlarmsTriggerStatusArray[];
extern double* TempAlarm1DataSourcePointer;
extern double* TempAlarm2DataSourcePointer;
extern double* TempAlarm3DataSourcePointer;
extern double* TempAlarm4DataSourcePointer;
extern double* TempAlarm5DataSourcePointer;

// Live view elementers Farve globale variable
extern bool EnableLabelBackgroundFlag;
extern unsigned char CommonLabelColorR;
extern unsigned char CommonLabelColorG;
extern unsigned char CommonLabelColorB;
extern unsigned char CommonLabelBackgroundColorR;
extern unsigned char CommonLabelBackgroundColorG;
extern unsigned char CommonLabelBackgroundColorB;
extern unsigned char MaxCrosshairColorR;
extern unsigned char MaxCrosshairColorG;
extern unsigned char MaxCrosshairColorB;
extern unsigned char MinCrosshairColorR;
extern unsigned char MinCrosshairColorG;
extern unsigned char MinCrosshairColorB;
extern unsigned char CenterCrosshairColorR;
extern unsigned char CenterCrosshairColorG;
extern unsigned char CenterCrosshairColorB;
extern unsigned char ROISelectedColorR;
extern unsigned char ROISelectedColorG;
extern unsigned char ROISelectedColorB;
extern unsigned char ROIPassiveColorR;
extern unsigned char ROIPassiveColorG;
extern unsigned char ROIPassiveColorB;
extern unsigned char TempMeasCrosshairSelectedColorR;
extern unsigned char TempMeasCrosshairSelectedColorG;
extern unsigned char TempMeasCrosshairSelectedColorB;
extern unsigned char TempMeasCrosshairPassiveColorR;
extern unsigned char TempMeasCrosshairPassiveColorG;
extern unsigned char TempMeasCrosshairPassiveColorB;
extern unsigned char TempLinesSelectedColorR;
extern unsigned char TempLinesSelectedColorG;
extern unsigned char TempLinesSelectedColorB;
extern unsigned char TempLinesPassiveColorR;
extern unsigned char TempLinesPassiveColorG;
extern unsigned char TempLinesPassiveColorB;

// GUI form positions flag
extern bool isWelcomeScreenFormOpen;
extern bool isWelcomeScreenFormDocked;
extern bool isWelcomeScreenFormUndocked;
extern bool isUserGuideFormOpen;
extern bool isUserGuideFormDocked;
extern bool isUserGuideFormUndocked;
extern bool isThermalCameraFormOpen;
extern bool isThermalCameraFormDocked;
extern bool isThermalCameraFormUndocked;
extern bool isLiveViewStreamFormOpen;
extern bool isLiveViewStreamFormDocked;
extern bool isLiveViewStreamFormUndocked;
extern bool isSurfacePlotFormOpen;
extern bool isSurfacePlotFormDocked;
extern bool isSurfacePlotFormUndocked;
extern bool isTempMeasurementsFormOpen;
extern bool isTempMeasurementsFormDocked;
extern bool isTempMeasurementsFormUndocked;
extern bool isEmissivityTableFormOpen;
extern bool isEmissivityTableFormDocked;
extern bool isEmissivityTableFormUndocked;
extern bool isLiveViewToolsFormOpen;
extern bool isLiveViewToolsFormDocked;
extern bool isLiveViewToolsFormUndocked;

// 2D Plot Data Sæt Source Pointers
extern unsigned char Plot2DDataSetLineColorsR[_2DPlotMaxNumberOfDataSets];
extern unsigned char Plot2DDataSetLineColorsG[_2DPlotMaxNumberOfDataSets];
extern unsigned char Plot2DDataSetLineColorsB[_2DPlotMaxNumberOfDataSets];
extern double *Plot2DDataSet1SourcePointer;
extern double *Plot2DDataSet2SourcePointer;
extern double *Plot2DDataSet3SourcePointer;
extern double *Plot2DDataSet4SourcePointer;
extern double *Plot2DDataSet5SourcePointer;
extern double *Plot2DDataSet6SourcePointer;
extern double *Plot2DDataSet7SourcePointer;
extern double *Plot2DDataSet8SourcePointer;
extern double *Plot2DDataSet9SourcePointer;
extern double *Plot2DDataSet10SourcePointer;

// Generalle Og Periodiske Trigger Event Timer Objekter og variabler
extern bool PeriodicTriggerEventEnableFlags[_MaxNumberOfConfigurablePeriodicTriggerEvents];
extern unsigned int PeriodicEventTriggerCounter[_MaxNumberOfConfigurablePeriodicTriggerEvents];

// --------------------- Globale Managed Variabler & Objekter Variabler ---------------------- //

// Globale Managed objekters reference struktur
ref struct GlobalVariables {

	// --------------------------- Tværform Objekter Og Variabler ---------------------------- //

	// Fælles Globale Reference Strings
	static System::String^ TOPDONCameraInformationString = "PLEASE NOTE!\r\nIf You Are Connecting To A TOPDON Or P2/Pro Camera And Have The TCView\r\nSoftware Drivers Installed, You Will Need To Uninstall The TOPDON Drivers\r\nTo Use Your TOPDON Or P2/Pro Camera With This Software!\r\n The Driver Can Be Uninstalled From Windows Device Manager.";

	// Fælles Globale statiske objekter & variabler
	static System::Windows::Forms::Form^ ActiveForm = nullptr;
	static System::String^ DefaultTempUnitString = "°C";
	static System::String^ TemperaturePrecision = "F3";
	static System::String^ RecordingAnalysisModeRAWFilePath = "";
	static System::String^ FullFrameDataCSVDelimiterString = ",";
	static System::String^ DataLoggingCSVDelimiterString = ",";
	static System::String^ SnapShotAnalysisModeRAWFilePath = "";
	static System::Threading::AutoResetEvent^ ThreadDataReadyEvent = gcnew System::Threading::AutoResetEvent(false);

	// Fil Path Lokerings strings, Navn Strings Og diverse Applikations strings
	static System::String^ SnapShotDefaultPath = System::Environment::GetFolderPath(System::Environment::SpecialFolder::Desktop);
	static System::String^ RecordingDefaultPath = System::Environment::GetFolderPath(System::Environment::SpecialFolder::Desktop);
	static System::String^ LoggingCSVDefaultPath = System::Environment::GetFolderPath(System::Environment::SpecialFolder::Desktop);
	static System::String^ DataLoggingSessionFileNameString = nullptr;
	static System::String^ DefaultCapturingAppPackageFamilyNameString = nullptr;

	// Globale objekter fra MainGUI Formen
	static System::Windows::Forms::RichTextBox^ GlobalGUIInfoTextArea = nullptr;
	static System::ComponentModel::BackgroundWorker^ GlobalVideoStreamThread = nullptr;
	static System::ComponentModel::BackgroundWorker^ GlobalSecondaryProcessingThread = nullptr;
	static System::Windows::Forms::Timer^ GlobalMainGUIUpdateTimer = nullptr;
	static System::Windows::Forms::Button^ GlobalTempMeasMenuButton = nullptr;
	static System::Windows::Forms::Button^ GlobalSurfacePlotMenuButton = nullptr;
	static cli::array<System::Windows::Forms::Button^>^ MainGUILeftMenuButtons = nullptr;

	// Globale objekter fra ThermalCameraGUI Formen
	static System::Windows::Forms::ComboBox^ GlobalCameraSourceDropList = nullptr;
	static System::Windows::Forms::Button^ GlobalConnectButton = nullptr;
	static System::Windows::Forms::Button^ GlobalDisconnectButton = nullptr;
	static System::Windows::Forms::Button^ GlobalReadCameraConfigButton = nullptr;
	static System::Windows::Forms::Button^ GlobalSetCameraConfigButton = nullptr;
	static cli::array<System::Windows::Forms::NumericUpDown^>^ CameraConfigNumericUpDowns = nullptr;
	static cli::array<System::Windows::Forms::ComboBox^>^ Plot2DDataSetComboBoxs = nullptr;
	static cli::array<System::Windows::Forms::Panel^>^ Plot2DDataSetColorPanels = nullptr;
	static cli::array<System::Windows::Forms::CheckBox^>^ Plot2DDataSetCheckBoxs = nullptr;
	static cli::array<System::Windows::Forms::Label^>^ CameraConfigLabels = nullptr;
	static cli::array<System::Windows::Forms::Label^>^ TempAlarmsStatusLabels = nullptr;
	static cli::array<System::Windows::Forms::ComboBox^>^ GlobalPeriodicEventnComboBox = nullptr;
	static cli::array<System::Windows::Forms::NumericUpDown^>^ GlobalPeriodicEventIntervalnUpDown = nullptr;
	static cli::array<System::Windows::Forms::CheckBox^>^ GlobalPeriodicEventnEnableCheckBox = nullptr;
	static cli::array<System::Windows::Forms::CheckBox^>^ GlobalPeriodicEventnDisableCheckBox = nullptr;
	static System::Windows::Forms::NumericUpDown^ GlobalDataLoggingIntervalUpDown = nullptr;
	static System::Windows::Forms::NumericUpDown^ GlobalDataLoggingDurationHourUpDown = nullptr;
	static System::Windows::Forms::NumericUpDown^ GlobalDataLoggingDurationMinuteUpDown = nullptr;
	static System::Windows::Forms::NumericUpDown^ GlobalDataLoggingDurationSecondsUpDown = nullptr;
	static System::Windows::Forms::Timer^ GlobalAlarmSoundTimer = nullptr;
	static System::Windows::Forms::Timer^ GlobalAlarmTriggerEventTimer = nullptr;
	static System::Windows::Forms::Button^ GlobalUseWinSnippingToolButton = nullptr;
	static System::Windows::Forms::Button^ GlobalUseWin11ScreenRecordToolButton = nullptr;
	static System::Windows::Forms::Label^ GlobalCameraShutterTempLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalCameraCoreTempLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalCameraDetectorTempLabel = nullptr;
	static System::Windows::Forms::Button^ GlobalAutoShutterCalButton = nullptr;
	static System::Windows::Forms::NumericUpDown^ GlobalAutoCalPeriodUpDown = nullptr;
	static System::Windows::Forms::Timer^ GlobalAutoCalTimer = nullptr;
	static System::Windows::Forms::Timer^ GlobalDriftCalTimer = nullptr;
	static System::Windows::Forms::Button^ GlobalIncludeColorbarSnapButton = nullptr;
	static System::Windows::Forms::Button^ GlobalSaveRawSensorSnapButton = nullptr;
	static System::Windows::Forms::NumericUpDown^ GlobalAlarmTriggerEventsIntervalUpDown = nullptr;
	static System::Windows::Forms::Button^ GlobalRecoverDefaultCameraSettingsButton = nullptr;
	static System::Windows::Forms::Button^ GlobalSaveRawAnalysisRecordingButton = nullptr;
	static System::Windows::Forms::Button^ GlobalAlarm1TriggerEventResetButton = nullptr;
	static System::Windows::Forms::Button^ GlobalAlarm2TriggerEventResetButton = nullptr;
	static System::Windows::Forms::Button^ GlobalAlarm3TriggerEventResetButton = nullptr;
	static System::Windows::Forms::Button^ GlobalAlarm4TriggerEventResetButton = nullptr;
	static System::Windows::Forms::Button^ GlobalAlarm5TriggerEventResetButton = nullptr;
	static System::Windows::Forms::ComboBox^ GlobalFullFrameTempDataCSVDelimiterCombiBox = nullptr;
	static System::Windows::Forms::ComboBox^ GlobalDataLoggingCSVDelimiterCombiBox = nullptr;
	static System::Windows::Forms::NumericUpDown^ GlobalSensorDriftCalUpDown = nullptr;
	static System::Windows::Forms::Button^ GlobalSensorDriftCalButton = nullptr;
	static System::Windows::Forms::Label^ GlobalMaxTempDriftSetPountLabel = nullptr;
	static System::Windows::Forms::Button^ GlobalPeriodicTriggerConfigMenuButton = nullptr;
	static System::Windows::Forms::Panel^ GlobalPeriodicTriggerSubMenuPanel = nullptr;
	static System::Windows::Forms::Timer^ GlobalPeriodicTriggerTimer = nullptr;
	static System::Windows::Forms::Button^ GlobalAutoCalMenuButton = nullptr;
	static System::Windows::Forms::Button^ GlobalSnapshotConfigMenuButton = nullptr;
	static System::Windows::Forms::Button^ GlobalVideoRecordingMenuButton = nullptr;
	static System::Windows::Forms::Button^ GlobalTempPlotDataSetSettingsMenuButton = nullptr;
	static System::Windows::Forms::Button^ GlobalDataLoggingSettingsMenuButton = nullptr;
	static System::Windows::Forms::Button^ GlobalTempAlarmsConfigMenuButton = nullptr;
	static System::Windows::Forms::NumericUpDown^ GlobalRecordingFrameRateNumericUpDown = nullptr;


	// Globale objekter fra LiveViewStream & LiveViewTools Formen
	static LiveViewZoomWindow::RMHLiveViewZoomWindow^ LiveViewZoomWindowRender;
	static OpenGLWinForms::RMHOpenGLWF^ OpenGLRender;
	static OpenGLColorBar::RMHOpenGLColorBar^ OpenGLColorBar;
	static OpenGLHistogram::RMHOpenGLHistogram^ OpenGLHistogram;
	static System::String^ MaximumTempLabel = "N/A";
	static System::String^ MinimumTempLabel = "N/A";
	static System::String^ CenterTempLabel = "N/A";
	static System::String^ MouseCursorTempLabel = "N/A";
	static System::String^ ZoomROIMaxTempLabels = "N/A";
	static System::String^ ZoomROIMinTempLabels = "N/A";
	static cli::array<System::String^>^ ROIMaxTempLabels = { "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A" };
	static cli::array<System::String^>^ ROIMinTempLabels = { "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A" };
	static cli::array<System::String^>^ TempMeasurementsLabels = { "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A" };
	static cli::array<System::String^>^ TempLinesMaxLabels = { "N/A", "N/A", "N/A", "N/A", "N/A" };
	static cli::array<System::String^>^ TempLinesMinLabels = { "N/A", "N/A", "N/A", "N/A", "N/A" };
	static System::Windows::Forms::Button^ GlobalEnhancedResButton = nullptr;
	static System::Windows::Forms::Button^ GlobalLiveViewRunStopButton = nullptr;
	static cli::array<System::Windows::Forms::Button^>^ TempUnitButtons = nullptr;
	static System::Windows::Forms::Button^ GlobalMaxTempTrackButton = nullptr;
	static System::Windows::Forms::Button^ GlobalMinTempTrackButton = nullptr;
	static System::Windows::Forms::Button^ GlobalCenterTempTrackButton = nullptr;
	static System::Windows::Forms::Button^ GlobalCursorTempTrackButton = nullptr;
	static System::Windows::Forms::Button^ GlobalAddTempMeasButton = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobaldeleteTempLabelToolStripMenuItem = nullptr;
	static System::Windows::Forms::Button^ GlobalAddROIMeasButton = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobaldeleteROIToolStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalhistogramSourceToolStripMenuItem = nullptr;
	static System::Windows::Forms::Button^ GlobalAddTempSpecLineButton = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobaldeleteLineToolStripMenuItem = nullptr;
	static System::Windows::Forms::Button^ GlobalShowLineHistButton = nullptr;
	static System::Windows::Forms::Panel^ GlobalLiveViewHistogramPanel = nullptr;
	static System::Windows::Forms::Panel^ GlobalStreamAndCBarPanel = nullptr;
	static System::Windows::Forms::Panel^ GlobalLiveViewStreamPanel = nullptr;
	static System::Windows::Forms::Button^ GlobalImageSharpButton = nullptr;
	static System::Windows::Forms::Button^ GlobalCalibrateCameraButton = nullptr;
	static System::Windows::Forms::Button^ GlobalTempRangeButton = nullptr;
	static System::Windows::Forms::Button^ GlobalFixedAspectRatioButton = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobaluseDualPaletteToolStripMenuItem = nullptr;
	static System::Windows::Forms::ComboBox^ GlobalColorPaletteComboBox = nullptr;
	static System::Windows::Forms::ComboBox^ GlobalDualColorPaletteComboBox = nullptr;
	static System::Windows::Forms::ComboBox^ GlobalColorBarBackPaletteComboBox = nullptr;
	static System::Windows::Forms::Button^ GlobalRecordingButton = nullptr;
	static System::Windows::Forms::Button^ GlobalUltraResolutionButton = nullptr;
	static System::Windows::Forms::Button^ GlobalPeriodicTimerTriggerButton = nullptr;
	static System::Windows::Forms::Button^ GlobalSaveTempFrameDataButton = nullptr;
	static System::Windows::Forms::Button^ GlobalSnapshotButton = nullptr;
	static System::Windows::Forms::Button^ GlobalDualColorPaletteButton = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalLiveViewMWRotationStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalRotateLiveViewCWStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalRotateLiveViewCCWStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalSetSharpStdDivToolStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalimageSharpeningStrengthToolStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalshowUnsharpMaskToolStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobaldeleteAllToolStripMenuItem2 = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalchangeLineColorsToolStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalchangeROIColorsToolStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobaltemperatureRangeToolStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalenableFullPaletteRangeAdjustmentToolStripMenuItem = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobaladjustDualPaletteRangeToolStripMenuItem = nullptr;
	static System::Windows::Forms::Panel^ GlobalLiveViewZoomPanel = nullptr;
	static System::Windows::Forms::ToolStripMenuItem^ GlobalLiveViewSplitViewToolStripMenuItem = nullptr;
	static System::Windows::Forms::Panel^ GlobalColorBarMainPanel = nullptr;

	// Globale objekter fra SurfacePlotGUI Formen
	static OpenGLSurfacePlot::RMHOpenGLSurfacePlot^ OpenGLSurfacePlot;
	static System::Windows::Forms::Panel^ GlobalSurfacePlotPanel = nullptr;

	// Globale objekter fra TempMeasGUI Formen
	static OpenGL2DPlot::RMHOpenGL2DPlot^ OpenGL2DPlot;
	static cli::array<System::Windows::Forms::Label^>^ Plot2DLegendLabels = nullptr;
	static System::ComponentModel::BackgroundWorker^ GlobalDataLoggingThread = nullptr;

	// Globale objekter fra VideoPlayBackTools Formen
	static System::Windows::Forms::Label^ VideoPlaybackTempCorrectionLabel = nullptr;
	static System::Windows::Forms::Label^ VideoPlaybackAmbientTempLabel = nullptr;
	static System::Windows::Forms::Label^ VideoPlaybackReflectedTempLabel = nullptr;
	static System::Windows::Forms::Button^ VideoPlaybackForwardStepButton = nullptr;
	static System::Windows::Forms::Button^ VideoPlaybackBackwardStepButton = nullptr;
	static System::Windows::Forms::Button^ VideoPlaybackPlayStopButton = nullptr; 

	// Globale objekter fra Live View Statistik Formen
	static System::Windows::Forms::Label^ GlobalFrameRateLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalNumberOfFramesLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalSpanLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalAverageLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalRangeUsageLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalDriftLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalDriftErrorLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalMaxPeakLabel = nullptr;
	static System::Windows::Forms::Label^ GlobalMinPeakLabel = nullptr;

	// --------------------------------------------------------------------------------------- // 

};

// ------------------------------------------------------------------------------------------- //

#endif /* GlobalObjectsAndVariables_H */

