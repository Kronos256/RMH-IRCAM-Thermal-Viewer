#pragma once

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"
#include "RMH_Application_ThermalViewer.h"
#include "RMH_Winforms_Library.h"
#include "PopUpDialog.h"

// Inkluderede Resourcer
#include "RMH_2DPlotDataSetSources_Resources.h"
#include "RMH_TemperatureAlarms_Resources.h"
#include "RMH_SupportedIRCameras_Resources.h"
#include "RMH_FullFrameTempData_Resources.h"
#include "RMH_DataLoggingFeature_Resources.h"
#include "RMH_GeneralTriggerEvent_Resources.h"

// Klasse Namespace
namespace IRCAMThermalViewer {

	// Tilhørende namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Summary for Form - ThermalCameraGUI
	public ref class ThermalCameraGUI : public System::Windows::Forms::Form {

		// ------------------------------ Lokale Form Reference Struktur ------------------------------ //

		// Lokale Reference struktur
		ref struct ManagedLocals {

			// Pop-Up GUI Form statiske Objekter og variabler
			static IRCAMThermalViewer::PopUpDialog^ PopUpDialogForm;

		};

		// -------------------------------------------------------------------------------------------- //

	public:

		// ------------------------------------ Klasse Konstruktor ------------------------------------ //

		// Form Konstruktor
		ThermalCameraGUI() {

			// Init GUI komponenter og objekter
			InitializeComponent();
			// Formater arrays og objekter af winform komponenter til global brug
			InitializeComponentArraysAndObjects();

			// Aktiver Applikationens TitelBars Dark Mode
			RMH_Winforms_EnableTitleBarDarkMode(this->Handle);

			// Initiliser Pop-Up GUI Form
			ManagedLocals::PopUpDialogForm = gcnew IRCAMThermalViewer::PopUpDialog("Information", GlobalVariables::TOPDONCameraInformationString);

			// Indstil Gemte Sessions Applikations Parametere
			GlobalVariables::GlobalRecordingFrameRateNumericUpDown->Value = RecordingFrameRateSetValue;

			// Opdater Snapshot default Fil path stringet 
			this->DefaultSnapshotSavePathString->Text = "Default Save File Path:  " + GlobalVariables::SnapShotDefaultPath;
			// Opdater Video Optagning default Fil path stringet 
			this->DefaultRecordingSavePathString->Text = "Default Save File Path:  " + GlobalVariables::RecordingDefaultPath;
			// Opdater Data Logging default Fil path stringet 
			this->DefaultDataLoggingSavePathString->Text = "Default Save File Path:  " + GlobalVariables::LoggingCSVDefaultPath;

			// Load data strings ind i hver 2D Plot Data set ComboBoxer
			LoadDataToDataSetComboBoxsAndSetStartUpConfiguration();

			// Load Data strings til Temperatur Alarm Menu ComboBoxer
			LoadTemperatureAlarmsConfigDataToComboboxes();

			// Opdaterer Teksten i toppen af GUIen
			RMH_Winforms_ChangeFormTitleBarText(this, "Thermal Camera Settings, Setup And Configuration");

			// Indsæt listen over de supporterede termiske kameraer i "Supported Devices" ComboBox.
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(GlobalVariables::GlobalCameraSourceDropList, SupportedCamerasModelNames);
			// Indstil valgte termiske kamera index fra gemte sessions data
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->CameraSourceDropList, SelectedThermalCameraIndex);

			// Indsæt listen over de tilgængelige Full Frame Temp CSV Data Delimitere i tilhørende combibox
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(GlobalVariables::GlobalFullFrameTempDataCSVDelimiterCombiBox, FullFrameTempCSVDataDelimiters);
			// Indstil valgte Full Frame Temp CSV Data Delimitere fra gemte sessions data
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->FullFrameTempDataCSVDelimiterCombiBox, SelectedFullFrameTempCSVDataDelimiterIndex);

			// Indsæt listen over de tilgængelige Data Logging CSV Delimitere i tilhørende combibox
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(GlobalVariables::GlobalDataLoggingCSVDelimiterCombiBox, DataLoggingCSVDataDelimiters);
			// Indstil valgte Data Logging CSV Delimitere fra gemte sessions data
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataLoggingCSVDelimiterCombiBox, SelectedDataLoggingCSVDataDelimiterIndex);

		}

		// ---------------------------- Diverse Tilhørende Klasse Metoder ----------------------------- //

		void InitializeComponentArraysAndObjects(void) {

			// Routinen formaterer arrays og objekter af winform komponenter til global brug

			// Initiliser globale form objekter
			GlobalVariables::CameraConfigNumericUpDowns = gcnew cli::array<System::Windows::Forms::NumericUpDown^>(6) {
				this->TempCorrUpDown,
				this->AmbientTempUpDown,
				this->ReflectedTempUpDown,
				this->HumidityUpDown,
				this->EmissivityUpDown,
				this->DistanceUpDown
			};
			GlobalVariables::Plot2DDataSetComboBoxs = gcnew cli::array<System::Windows::Forms::ComboBox^>(10) {
				this->DataSet1ComboBox,
				this->DataSet2ComboBox,
				this->DataSet3ComboBox,
				this->DataSet4ComboBox,
				this->DataSet5ComboBox,
				this->DataSet6ComboBox,
				this->DataSet7ComboBox,
				this->DataSet8ComboBox,
				this->DataSet9ComboBox,
				this->DataSet10ComboBox
					
			};
			GlobalVariables::Plot2DDataSetColorPanels = gcnew cli::array<System::Windows::Forms::Panel^>(10) {
				this->DataSet1ColorPanel,
				this->DataSet2ColorPanel,
				this->DataSet3ColorPanel,
				this->DataSet4ColorPanel,
				this->DataSet5ColorPanel,
				this->DataSet6ColorPanel,
				this->DataSet7ColorPanel,
				this->DataSet8ColorPanel,
				this->DataSet9ColorPanel,
				this->DataSet10ColorPanel

			};
			GlobalVariables::Plot2DDataSetCheckBoxs = gcnew cli::array<System::Windows::Forms::CheckBox^>(10) {
				this->DataSet1CheckBox,
				this->DataSet2CheckBox,
				this->DataSet3CheckBox,
				this->DataSet4CheckBox,
				this->DataSet5CheckBox,
				this->DataSet6CheckBox,
				this->DataSet7CheckBox,
				this->DataSet8CheckBox,
				this->DataSet9CheckBox,
				this->DataSet10CheckBox

			};
			GlobalVariables::CameraConfigLabels = gcnew cli::array<System::Windows::Forms::Label^>(3) {
				this->TempCorrLabel,
				this->AmbientTempLabel,
				this->ReflectedTempLabel
			};
			GlobalVariables::TempAlarmsStatusLabels = gcnew cli::array<System::Windows::Forms::Label^>(5) {
				this->TempAlarm1StatusLabel,
				this->TempAlarm2StatusLabel,
				this->TempAlarm3StatusLabel,
				this->TempAlarm4StatusLabel,
				this->TempAlarm5StatusLabel
			};
			GlobalVariables::GlobalPeriodicEventnComboBox = gcnew cli::array<System::Windows::Forms::ComboBox^>(5) {
				this->PeriodicEvent1ComboBox,
				this->PeriodicEvent2ComboBox,
				this->PeriodicEvent3ComboBox,
				this->PeriodicEvent4ComboBox,
				this->PeriodicEvent5ComboBox
			};
			GlobalVariables::GlobalPeriodicEventIntervalnUpDown = gcnew cli::array<System::Windows::Forms::NumericUpDown^>(5) {
				this->PeriodicEventInterval1UpDown,
				this->PeriodicEventInterval2UpDown,
				this->PeriodicEventInterval3UpDown,
				this->PeriodicEventInterval4UpDown,
				this->PeriodicEventInterval5UpDown
			};
			GlobalVariables::GlobalPeriodicEventnEnableCheckBox = gcnew cli::array<System::Windows::Forms::CheckBox^>(5) {
				this->PeriodicEvent1EnableCheckBox,
				this->PeriodicEvent2EnableCheckBox,
				this->PeriodicEvent3EnableCheckBox,
				this->PeriodicEvent4EnableCheckBox,
				this->PeriodicEvent5EnableCheckBox
			};
			GlobalVariables::GlobalPeriodicEventnDisableCheckBox = gcnew cli::array<System::Windows::Forms::CheckBox^>(5) {
				this->PeriodicEvent1DisableCheckBox,
				this->PeriodicEvent2DisableCheckBox,
				this->PeriodicEvent3DisableCheckBox,
				this->PeriodicEvent4DisableCheckBox,
				this->PeriodicEvent5DisableCheckBox
			};
			GlobalVariables::GlobalDataLoggingIntervalUpDown = this->LogIntervalUpDown;
			GlobalVariables::GlobalDataLoggingDurationHourUpDown = this->DurationHourUpDown;
			GlobalVariables::GlobalDataLoggingDurationMinuteUpDown = this->DurationMinuteUpDown;
			GlobalVariables::GlobalDataLoggingDurationSecondsUpDown = this->DurationSecondsUpDown;
			GlobalVariables::GlobalAlarmSoundTimer = this->AlarmSoundTimer;
			GlobalVariables::GlobalAlarmTriggerEventTimer = this->AlarmTriggerEventTimer;
			GlobalVariables::GlobalUseWinSnippingToolButton = this->UseWinSnippingToolButton;
			GlobalVariables::GlobalUseWin11ScreenRecordToolButton = this->UseWin11ScreenRecordToolButton;
			GlobalVariables::DefaultCapturingAppPackageFamilyNameString = _MicrosoftStore_SnippingTool;
			GlobalVariables::GlobalCameraShutterTempLabel = this->CameraShutterTempLabel;
			GlobalVariables::GlobalCameraCoreTempLabel = this->CameraCoreTempLabel;
			GlobalVariables::GlobalCameraDetectorTempLabel = this->CameraDetectorTempLabel;
			GlobalVariables::GlobalCameraSourceDropList = this->CameraSourceDropList;
			GlobalVariables::GlobalConnectButton = this->ConnectButton;
			GlobalVariables::GlobalDisconnectButton = this->DisconnectButton;
			GlobalVariables::GlobalReadCameraConfigButton = this->ReadCameraConfigButton;
			GlobalVariables::GlobalSetCameraConfigButton = this->SetCameraConfigButton;
			GlobalVariables::GlobalAutoShutterCalButton = this->AutoShutterCalButton;
			GlobalVariables::GlobalAutoCalPeriodUpDown = this->AutoCalPeriodUpDown;
			GlobalVariables::GlobalAutoCalTimer = this->AutoCalTimer;
			GlobalVariables::GlobalIncludeColorbarSnapButton = this->IncludeColorbarSnapButton;
			GlobalVariables::GlobalSaveRawSensorSnapButton = this->SaveRawSensorSnapButton;
			GlobalVariables::GlobalAlarmTriggerEventsIntervalUpDown = this->AlarmTriggerEventsIntervalUpDown;
			GlobalVariables::GlobalRecoverDefaultCameraSettingsButton = this->RecoverDefaultCameraSettingsButton;
			GlobalVariables::GlobalSaveRawAnalysisRecordingButton = this->SaveRawAnalysisRecordingButton;
			GlobalVariables::GlobalAlarm1TriggerEventResetButton = this->Alarm1TriggerEventResetButton;
			GlobalVariables::GlobalAlarm2TriggerEventResetButton = this->Alarm2TriggerEventResetButton;
			GlobalVariables::GlobalAlarm3TriggerEventResetButton = this->Alarm3TriggerEventResetButton;
			GlobalVariables::GlobalAlarm4TriggerEventResetButton = this->Alarm4TriggerEventResetButton;
			GlobalVariables::GlobalAlarm5TriggerEventResetButton = this->Alarm5TriggerEventResetButton;
			GlobalVariables::GlobalFullFrameTempDataCSVDelimiterCombiBox = this->FullFrameTempDataCSVDelimiterCombiBox;
			GlobalVariables::GlobalDataLoggingCSVDelimiterCombiBox = this->DataLoggingCSVDelimiterCombiBox;
			GlobalVariables::GlobalSensorDriftCalUpDown = this->SensorDriftCalUpDown;
			GlobalVariables::GlobalSensorDriftCalButton = this->SensorDriftCalButton;
			GlobalVariables::GlobalDriftCalTimer = this->DriftCalTimer;
			GlobalVariables::GlobalMaxTempDriftSetPountLabel = this->MaxTempDriftSetPountLabel;
			GlobalVariables::GlobalPeriodicTriggerConfigMenuButton = this->PeriodicTriggerConfigMenuButton;
			GlobalVariables::GlobalPeriodicTriggerSubMenuPanel = this->PeriodicTriggerSubMenuPanel;
			GlobalVariables::GlobalPeriodicTriggerTimer = this->PeriodicTriggerTimer;
			GlobalVariables::GlobalAutoCalMenuButton = this->AutoCalMenuButton;
			GlobalVariables::GlobalSnapshotConfigMenuButton = this->SnapshotConfigMenuButton;
			GlobalVariables::GlobalVideoRecordingMenuButton = this->VideoRecordingMenuButton;
			GlobalVariables::GlobalTempPlotDataSetSettingsMenuButton = this->TempPlotDataSetSettingsMenuButton;
			GlobalVariables::GlobalDataLoggingSettingsMenuButton = this->DataLoggingSettingsMenuButton;
			GlobalVariables::GlobalTempAlarmsConfigMenuButton = this->TempAlarmsConfigMenuButton;
			GlobalVariables::GlobalRecordingFrameRateNumericUpDown = this->RecordingFrameRateNumericUpDown;

		}

		void SaveFormSessionSettings() {

			// Opdater Form Gemte Sessions parametere til globale variabler

			// Lager Valgte Kamera Index til globale variabel til gemt sessions parameter
			SelectedThermalCameraIndex = this->CameraSourceDropList->SelectedIndex;

			// Lager Valgte Full Frame Temp CSV Data Delimiter til globale variabel til gemt sessions parameter
			SelectedFullFrameTempCSVDataDelimiterIndex = this->FullFrameTempDataCSVDelimiterCombiBox->SelectedIndex;

			// Lager Valgte Data Logging CSV Data Delimiter til globale variabel til gemt sessions parameter
			SelectedDataLoggingCSVDataDelimiterIndex = this->DataLoggingCSVDelimiterCombiBox->SelectedIndex;

			// Opdater Temperatur korrektions værdi til globale variabel til gemt sessions parameter
			SavedTempCorrectionSetting = RMH_Conversion_SystemDecimalToFloat(this->TempCorrUpDown->Value);

			// Load 2D Plot Data linjernes farve værdier til globale arrays
			RMH_ThermalViewer_Load2DPlotLineColorDataToGlobalArrays();

		}

		void LoadDataToDataSetComboBoxsAndSetStartUpConfiguration() {

			// Routinen loader data strings ind i hver 2D Plot Data set ComboBoxer
			// Samt indstiller start konfigurationen for 2D plot pointere og ComboBoxer

			// Indsæt listen over de tilgængelige Temperatur Plot Data Sæt Sources til ComboBox
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet1ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet2ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet3ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet4ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet5ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet6ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet7ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet8ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet9ComboBox, PlorDataSetSources);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->DataSet10ComboBox, PlorDataSetSources);

			// Indstil Plot Data Sæt Sources Combibox til start Index
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet1ComboBox, _2DPlotDataSource_MaximumTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet2ComboBox, _2DPlotDataSource_MinimumTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet3ComboBox, _2DPlotDataSource_CenterTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet4ComboBox, _2DPlotDataSource_TempPoint1);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet5ComboBox, _2DPlotDataSource_TempPoint2);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet6ComboBox, _2DPlotDataSource_Line1MaxTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet7ComboBox, _2DPlotDataSource_Line1MinTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet8ComboBox, _2DPlotDataSource_ROI1MaxTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet9ComboBox, _2DPlotDataSource_ROI1MinTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->DataSet10ComboBox, _2DPlotDataSource_MousePositionTemp);

			// Indstil 2D Plottets Data Sæt pointere til start Data Sourcer
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet1SourcePointer, _2DPlotDataSource_MaximumTemp);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet2SourcePointer, _2DPlotDataSource_MinimumTemp);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet3SourcePointer, _2DPlotDataSource_CenterTemp);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet4SourcePointer, _2DPlotDataSource_TempPoint1);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet5SourcePointer, _2DPlotDataSource_TempPoint2);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet6SourcePointer, _2DPlotDataSource_Line1MaxTemp);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet7SourcePointer, _2DPlotDataSource_Line1MinTemp);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet8SourcePointer, _2DPlotDataSource_ROI1MaxTemp);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet9SourcePointer, _2DPlotDataSource_ROI1MinTemp);
			RMH_ThermalViewer_Set2DPlotDataSetSource(&Plot2DDataSet10SourcePointer, _2DPlotDataSource_MousePositionTemp);

		}

		void LoadTemperatureAlarmsConfigDataToComboboxes() {

			// Routinen loader konfigurations strings til temperatur Alarm konfigurations menuens ComboBoxer

			// Indlæs listen over tilgængelige temperatur alarmers data sourcer
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm1DataSourceComboBox, TempAlarmsDataSourcesStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm2DataSourceComboBox, TempAlarmsDataSourcesStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm3DataSourceComboBox, TempAlarmsDataSourcesStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm4DataSourceComboBox, TempAlarmsDataSourcesStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm5DataSourceComboBox, TempAlarmsDataSourcesStrings);

			// Indstil default Temperatur alarmers data sources
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm1DataSourceComboBox, _TempAlarmDataSource_MaximumTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm2DataSourceComboBox, _TempAlarmDataSource_MinimumTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm3DataSourceComboBox, _TempAlarmDataSource_CenterTemp);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm4DataSourceComboBox, _TempAlarmDataSource_TempPoint1);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm5DataSourceComboBox, _TempAlarmDataSource_TempPoint2);

			// Indlæs listen over tilgængelige temperatur alarm konfigurations typer
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm1AlarmTypeComboBox, TempAlarmsConfigTypeStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm2AlarmTypeComboBox, TempAlarmsConfigTypeStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm3AlarmTypeComboBox, TempAlarmsConfigTypeStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm4AlarmTypeComboBox, TempAlarmsConfigTypeStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm5AlarmTypeComboBox, TempAlarmsConfigTypeStrings);

			// Indstil default Temperatur alarmers type konfiguration
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm1AlarmTypeComboBox, _TempAlarmType_Above);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm2AlarmTypeComboBox, _TempAlarmType_Above);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm3AlarmTypeComboBox, _TempAlarmType_Above);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm4AlarmTypeComboBox, _TempAlarmType_Above);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm5AlarmTypeComboBox, _TempAlarmType_Above);

			// Indlæs listen over tilgængelige temperatur alarm trigger aktioner
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm1TriggerActionComboBox, TempAlarmsTriggerActionStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm2TriggerActionComboBox, TempAlarmsTriggerActionStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm3TriggerActionComboBox, TempAlarmsTriggerActionStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm4TriggerActionComboBox, TempAlarmsTriggerActionStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(this->TempAlarm5TriggerActionComboBox, TempAlarmsTriggerActionStrings);

			// Indstil default Temperatur alarmer trigger aktion konfiguration
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm1TriggerActionComboBox, _TempAlarmTriggerAction_None);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm2TriggerActionComboBox, _TempAlarmTriggerAction_None);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm3TriggerActionComboBox, _TempAlarmTriggerAction_None);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm4TriggerActionComboBox, _TempAlarmTriggerAction_None);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(this->TempAlarm5TriggerActionComboBox, _TempAlarmTriggerAction_None);

			// Indlæs listen over tilgængelige periodiske trigger event funktioner
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(GlobalVariables::GlobalPeriodicEventnComboBox[0], PeriodicTriggerEventFuncStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(GlobalVariables::GlobalPeriodicEventnComboBox[1], PeriodicTriggerEventFuncStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(GlobalVariables::GlobalPeriodicEventnComboBox[2], PeriodicTriggerEventFuncStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(GlobalVariables::GlobalPeriodicEventnComboBox[3], PeriodicTriggerEventFuncStrings);
			RMH_Winforms_CombiBox_AddArrayOfItemStrings(GlobalVariables::GlobalPeriodicEventnComboBox[4], PeriodicTriggerEventFuncStrings);

			// Indstil default periodiske trigger event funktionerne
			RMH_Winforms_CombiBox_SetSellectedItemPosition(GlobalVariables::GlobalPeriodicEventnComboBox[0], _TriggerEventFunction_None);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(GlobalVariables::GlobalPeriodicEventnComboBox[1], _TriggerEventFunction_None);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(GlobalVariables::GlobalPeriodicEventnComboBox[2], _TriggerEventFunction_None);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(GlobalVariables::GlobalPeriodicEventnComboBox[3], _TriggerEventFunction_None);
			RMH_Winforms_CombiBox_SetSellectedItemPosition(GlobalVariables::GlobalPeriodicEventnComboBox[4], _TriggerEventFunction_None);

		}

		// -------------------------------------------------------------------------------------------- //

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ThermalCameraGUI() {

			if (components) {

				// Slet alle Form Komponenter
				delete components;

			}

		}
	
	protected:

		private: System::ComponentModel::IContainer^ components;
		private: System::Windows::Forms::Panel^ MainThermalCameraPanel;
		private: System::Windows::Forms::Button^ SetCameraConfigButton;
		private: System::Windows::Forms::NumericUpDown^ DistanceUpDown;
		private: System::Windows::Forms::NumericUpDown^ EmissivityUpDown;
		private: System::Windows::Forms::Label^ label1;
		private: System::Windows::Forms::NumericUpDown^ HumidityUpDown;
		private: System::Windows::Forms::Label^ AmbientTempLabel;
		private: System::Windows::Forms::Button^ ReadCameraConfigButton;
		private: System::Windows::Forms::Button^ ConnectButton;
		private: System::Windows::Forms::NumericUpDown^ ReflectedTempUpDown;
		private: System::Windows::Forms::Label^ DistanceLabel;
		private: System::Windows::Forms::NumericUpDown^ AmbientTempUpDown;
		private: System::Windows::Forms::ComboBox^ CameraSourceDropList;
		private: System::Windows::Forms::Label^ TempCorrLabel;
		private: System::Windows::Forms::Label^ HumidityLabel;
		private: System::Windows::Forms::NumericUpDown^ TempCorrUpDown;
		private: System::Windows::Forms::Label^ EmissivityLabel;
		private: System::Windows::Forms::Label^ ReflectedTempLabel;
		private: System::Windows::Forms::Panel^ ConnectTCAMSubMenuPanel;
		private: System::Windows::Forms::Button^ ConnectTCAMMenuButton;
		private: System::Windows::Forms::Button^ DisconnectButton;
		private: System::Windows::Forms::Panel^ CameraConfigSubMenuPanel;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::Panel^ AutoCalSubMenuPanel;
		private: System::Windows::Forms::Button^ AutoCalMenuButton;
		private: System::Windows::Forms::Panel^ SnapshotConfigSubMenuPanel;
		private: System::Windows::Forms::Button^ SnapshotConfigMenuButton;
		private: System::Windows::Forms::Label^ DefaultSnapshotSavePathString;
		private: System::Windows::Forms::Button^ ChangeSnapDefaultPathButton;
		private: System::Windows::Forms::Button^ IncludeColorbarSnapButton;
		private: System::Windows::Forms::Button^ AutoShutterCalButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
		private: System::Windows::Forms::Label^ label3;
		private: System::Windows::Forms::NumericUpDown^ AutoCalPeriodUpDown;
		private: System::Windows::Forms::Timer^ AutoCalTimer;
		private: System::Windows::Forms::Label^ label4;
		private: System::Windows::Forms::Button^ SaveRawSensorSnapButton;
		private: System::Windows::Forms::Panel^ VideoRecSettingsSubMenuPanel;
		private: System::Windows::Forms::Button^ VideoRecordingMenuButton;
		private: System::Windows::Forms::Panel^ TempPlotDataSetSettingsSubMenuPanel;
		private: System::Windows::Forms::Button^ TempPlotDataSetSettingsMenuButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
		private: System::Windows::Forms::ComboBox^ DataSet1ComboBox;
		private: System::Windows::Forms::Label^ label14;
		private: System::Windows::Forms::Label^ label5;
		private: System::Windows::Forms::Label^ label6;
		private: System::Windows::Forms::Label^ label7;
		private: System::Windows::Forms::Label^ label8;
		private: System::Windows::Forms::Label^ label10;
		private: System::Windows::Forms::Label^ label9;
		private: System::Windows::Forms::Label^ label11;
		private: System::Windows::Forms::Label^ label12;
		private: System::Windows::Forms::Label^ label13;
		private: System::Windows::Forms::CheckBox^ DataSet10CheckBox;
		private: System::Windows::Forms::CheckBox^ DataSet9CheckBox;
		private: System::Windows::Forms::CheckBox^ DataSet8CheckBox;
		private: System::Windows::Forms::CheckBox^ DataSet7CheckBox;
		private: System::Windows::Forms::CheckBox^ DataSet6CheckBox;
		private: System::Windows::Forms::CheckBox^ DataSet5CheckBox;
		private: System::Windows::Forms::CheckBox^ DataSet4CheckBox;
		private: System::Windows::Forms::CheckBox^ DataSet3CheckBox;
		private: System::Windows::Forms::CheckBox^ DataSet2CheckBox;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel24;
		private: System::Windows::Forms::Label^ label34;
		private: System::Windows::Forms::Panel^ DataSet10ColorPanel;
		private: System::Windows::Forms::CheckBox^ DataSet1CheckBox;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel23;
		private: System::Windows::Forms::Label^ label33;
		private: System::Windows::Forms::Panel^ DataSet9ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel22;
		private: System::Windows::Forms::Label^ label32;
		private: System::Windows::Forms::Panel^ DataSet8ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel21;
		private: System::Windows::Forms::Label^ label31;
		private: System::Windows::Forms::Panel^ DataSet7ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel20;
		private: System::Windows::Forms::Label^ label30;
		private: System::Windows::Forms::Panel^ DataSet6ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel19;
		private: System::Windows::Forms::Label^ label29;
		private: System::Windows::Forms::Panel^ DataSet5ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel18;
		private: System::Windows::Forms::Label^ label28;
		private: System::Windows::Forms::Panel^ DataSet4ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel17;
		private: System::Windows::Forms::Label^ label27;
		private: System::Windows::Forms::Panel^ DataSet3ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel16;
		private: System::Windows::Forms::Label^ label26;
		private: System::Windows::Forms::Panel^ DataSet2ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel15;
		private: System::Windows::Forms::Label^ label25;
		private: System::Windows::Forms::Panel^ DataSet1ColorPanel;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel14;
		private: System::Windows::Forms::NumericUpDown^ DataSet10UpDown;
		private: System::Windows::Forms::Label^ label24;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel13;
		private: System::Windows::Forms::NumericUpDown^ DataSet9UpDown;
		private: System::Windows::Forms::Label^ label23;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel12;
		private: System::Windows::Forms::NumericUpDown^ DataSet8UpDown;
		private: System::Windows::Forms::Label^ label22;
		private: System::Windows::Forms::Label^ label37;
		private: System::Windows::Forms::Label^ label36;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel11;
		private: System::Windows::Forms::NumericUpDown^ DataSet7UpDown;
		private: System::Windows::Forms::Label^ label21;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel10;
		private: System::Windows::Forms::NumericUpDown^ DataSet6UpDown;
		private: System::Windows::Forms::Label^ label20;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel9;
		private: System::Windows::Forms::NumericUpDown^ DataSet5UpDown;
		private: System::Windows::Forms::Label^ label19;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel8;
		private: System::Windows::Forms::NumericUpDown^ DataSet4UpDown;
		private: System::Windows::Forms::Label^ label18;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel7;
		private: System::Windows::Forms::NumericUpDown^ DataSet3UpDown;
		private: System::Windows::Forms::Label^ label17;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel6;
		private: System::Windows::Forms::NumericUpDown^ DataSet2UpDown;
		private: System::Windows::Forms::Label^ label16;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
		private: System::Windows::Forms::NumericUpDown^ DataSet1UpDown;
		private: System::Windows::Forms::Label^ label15;
		private: System::Windows::Forms::ComboBox^ DataSet2ComboBox;
		private: System::Windows::Forms::ComboBox^ DataSet10ComboBox;
		private: System::Windows::Forms::ComboBox^ DataSet9ComboBox;
		private: System::Windows::Forms::ComboBox^ DataSet8ComboBox;
		private: System::Windows::Forms::ComboBox^ DataSet7ComboBox;
		private: System::Windows::Forms::ComboBox^ DataSet6ComboBox;
		private: System::Windows::Forms::ComboBox^ DataSet5ComboBox;
		private: System::Windows::Forms::ComboBox^ DataSet4ComboBox;
		private: System::Windows::Forms::ComboBox^ DataSet3ComboBox;
		private: System::Windows::Forms::Panel^ panel11;
		private: System::Windows::Forms::Label^ label82;
		private: System::Windows::Forms::Label^ label80;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel27;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel28;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel29;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel26;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel31;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel30;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel32;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel33;
		private: System::Windows::Forms::Panel^ DataLoggingSettingsSubMenuPanel;
		private: System::Windows::Forms::Button^ DataLoggingSettingsMenuButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel34;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel35;
		private: System::Windows::Forms::Label^ DefaultDataLoggingSavePathString;
		private: System::Windows::Forms::Button^ ChangeCSVDefaultPathButton;
		private: System::Windows::Forms::Label^ label35;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel37;
		private: System::Windows::Forms::Label^ label41;
		private: System::Windows::Forms::NumericUpDown^ LogIntervalUpDown;
		private: System::Windows::Forms::Label^ label40;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel38;
		private: System::Windows::Forms::NumericUpDown^ DurationHourUpDown;
		private: System::Windows::Forms::NumericUpDown^ DurationSecondsUpDown;
		private: System::Windows::Forms::NumericUpDown^ DurationMinuteUpDown;
		private: System::Windows::Forms::Label^ label43;
		private: System::Windows::Forms::Label^ label44;
		private: System::Windows::Forms::Label^ label45;
		private: System::Windows::Forms::Label^ label46;
		private: System::Windows::Forms::Button^ CameraConfigMenuButton;
		private: System::Windows::Forms::Panel^ TempAlarmsConfigSubMenuPanel;
		private: System::Windows::Forms::Button^ TempAlarmsConfigMenuButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel39;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel40;
		private: System::Windows::Forms::Label^ label42;
		private: System::Windows::Forms::Label^ label49;
		private: System::Windows::Forms::Label^ label50;
		private: System::Windows::Forms::Label^ label51;
		private: System::Windows::Forms::Label^ label52;
		private: System::Windows::Forms::Label^ label53;
		private: System::Windows::Forms::Label^ label54;
		private: System::Windows::Forms::Label^ label55;
		private: System::Windows::Forms::Label^ label56;
		private: System::Windows::Forms::Label^ label57;
		private: System::Windows::Forms::Label^ label66;
		private: System::Windows::Forms::Label^ label65;
		private: System::Windows::Forms::Label^ label64;
		private: System::Windows::Forms::Label^ label63;
		private: System::Windows::Forms::CheckBox^ TempAlarm5EnableCheckBox;
		private: System::Windows::Forms::CheckBox^ TempAlarm4EnableCheckBox;
		private: System::Windows::Forms::CheckBox^ TempAlarm3EnableCheckBox;
		private: System::Windows::Forms::Label^ label87;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel55;
		private: System::Windows::Forms::Label^ label76;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm5HighTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel54;
		private: System::Windows::Forms::Label^ label74;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm4HighTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel53;
		private: System::Windows::Forms::Label^ label73;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm3HighTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel52;
		private: System::Windows::Forms::Label^ label72;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm2HighTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel51;
		private: System::Windows::Forms::Label^ label71;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm1HighTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel41;
		private: System::Windows::Forms::Label^ label67;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm1LowTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel45;
		private: System::Windows::Forms::Label^ label75;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm5LowTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel42;
		private: System::Windows::Forms::Label^ label68;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm2LowTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel43;
		private: System::Windows::Forms::Label^ label69;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm3LowTempThresUpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel44;
		private: System::Windows::Forms::Label^ label70;
		private: System::Windows::Forms::NumericUpDown^ TempAlarm4LowTempThresUpDown;
		private: System::Windows::Forms::CheckBox^ TempAlarm1EnableCheckBox;
		private: System::Windows::Forms::CheckBox^ TempAlarm2EnableCheckBox;
		private: System::Windows::Forms::Label^ label88;
		private: System::Windows::Forms::Label^ label89;
		private: System::Windows::Forms::ComboBox^ TempAlarm1AlarmTypeComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm1DataSourceComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm2DataSourceComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm3DataSourceComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm4DataSourceComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm5DataSourceComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm2AlarmTypeComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm3AlarmTypeComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm4AlarmTypeComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm5AlarmTypeComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm1TriggerActionComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm2TriggerActionComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm3TriggerActionComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm4TriggerActionComboBox;
		private: System::Windows::Forms::ComboBox^ TempAlarm5TriggerActionComboBox;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel46;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel47;
		private: System::Windows::Forms::Label^ TempAlarm1StatusLabel;
		private: System::Windows::Forms::Label^ label58;
		private: System::Windows::Forms::CheckBox^ TempAlarmsTriggerSoundCheckBox;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel48;
		private: System::Windows::Forms::Label^ TempAlarm2StatusLabel;
		private: System::Windows::Forms::Label^ label61;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel49;
		private: System::Windows::Forms::Label^ TempAlarm3StatusLabel;
		private: System::Windows::Forms::Label^ label77;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel50;
		private: System::Windows::Forms::Label^ TempAlarm4StatusLabel;
		private: System::Windows::Forms::Label^ label79;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel56;
		private: System::Windows::Forms::Label^ TempAlarm5StatusLabel;
		private: System::Windows::Forms::Label^ label81;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel57;
		private: System::Windows::Forms::Timer^ AlarmSoundTimer;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel58;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel59;
		private: System::Windows::Forms::Label^ label59;
		private: System::Windows::Forms::NumericUpDown^ AlarmTriggerEventsIntervalUpDown;
		private: System::Windows::Forms::Label^ label60;
		private: System::Windows::Forms::CheckBox^ EnableAlarmTriggerEventsCheckBox;
		private: System::Windows::Forms::Timer^ AlarmTriggerEventTimer;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel61;
		private: System::Windows::Forms::Label^ label78;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel62;
		private: System::Windows::Forms::Label^ label62;
		private: System::Windows::Forms::Button^ UseWinSnippingToolButton;
		private: System::Windows::Forms::Button^ UseWin11ScreenRecordToolButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel36;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel63;
		private: System::Windows::Forms::Label^ label39;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel64;
		private: System::Windows::Forms::Label^ label48;
		private: System::Windows::Forms::Label^ label47;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel65;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel66;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel25;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel67;
		private: System::Windows::Forms::Label^ label83;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel68;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel69;
		private: System::Windows::Forms::Label^ CameraShutterTempLabel;
		private: System::Windows::Forms::Label^ CameraCoreTempLabel;
		private: System::Windows::Forms::Button^ ReadIntCameraTempsButton;
		private: System::Windows::Forms::Label^ CameraDetectorTempLabel;
		private: System::Windows::Forms::Button^ RecoverDefaultCameraSettingsButton;
		private: System::Windows::Forms::Label^ label84;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel60;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel70;
		private: System::Windows::Forms::Label^ DefaultRecordingSavePathString;
		private: System::Windows::Forms::Label^ label85;
		private: System::Windows::Forms::Button^ ChangeRecordingDefaultPathButton;
		private: System::Windows::Forms::Label^ label86;
		private: System::Windows::Forms::Button^ SaveRawAnalysisRecordingButton;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel71;
		private: System::Windows::Forms::Button^ Alarm2TriggerEventResetButton;
		private: System::Windows::Forms::Button^ Alarm4TriggerEventResetButton;
		private: System::Windows::Forms::Button^ Alarm5TriggerEventResetButton;
		private: System::Windows::Forms::Button^ Alarm3TriggerEventResetButton;
		private: System::Windows::Forms::Button^ Alarm1TriggerEventResetButton;
		private: System::Windows::Forms::Label^ label90;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel72;
		private: System::Windows::Forms::ComboBox^ FullFrameTempDataCSVDelimiterCombiBox;
		private: System::Windows::Forms::Label^ label91;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel73;
		private: System::Windows::Forms::Label^ label92;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel74;
		private: System::Windows::Forms::NumericUpDown^ SensorDriftCalUpDown;
		private: System::Windows::Forms::Label^ MaxTempDriftSetPountLabel;
		private: System::Windows::Forms::Button^ SensorDriftCalButton;
		private: System::Windows::Forms::Timer^ DriftCalTimer;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel75;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel76;
		private: System::Windows::Forms::Label^ label93;
		private: System::Windows::Forms::ComboBox^ DataLoggingCSVDelimiterCombiBox;
		private: System::Windows::Forms::Button^ PeriodicTriggerConfigMenuButton;
		private: System::Windows::Forms::Panel^ ScrollPaddingPanel;
		private: System::Windows::Forms::Panel^ PeriodicTriggerSubMenuPanel;
		private: System::Windows::Forms::Timer^ PeriodicTriggerTimer;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel78;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel77;
		private: System::Windows::Forms::Label^ label99;
		private: System::Windows::Forms::Label^ label94;
		private: System::Windows::Forms::Label^ label95;
		private: System::Windows::Forms::Label^ label96;
		private: System::Windows::Forms::Label^ label97;
		private: System::Windows::Forms::Label^ label98;
		private: System::Windows::Forms::Label^ label100;
		private: System::Windows::Forms::ComboBox^ PeriodicEvent1ComboBox;
		private: System::Windows::Forms::ComboBox^ PeriodicEvent2ComboBox;
		private: System::Windows::Forms::ComboBox^ PeriodicEvent3ComboBox;
		private: System::Windows::Forms::ComboBox^ PeriodicEvent4ComboBox;
		private: System::Windows::Forms::ComboBox^ PeriodicEvent5ComboBox;
		private: System::Windows::Forms::Label^ label101;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel80;
		private: System::Windows::Forms::Label^ label104;
		private: System::Windows::Forms::Label^ label105;
		private: System::Windows::Forms::NumericUpDown^ PeriodicEventInterval1UpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel79;
		private: System::Windows::Forms::Label^ label102;
		private: System::Windows::Forms::Label^ label103;
		private: System::Windows::Forms::NumericUpDown^ PeriodicEventInterval2UpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel81;
		private: System::Windows::Forms::Label^ label106;
		private: System::Windows::Forms::Label^ label107;
		private: System::Windows::Forms::NumericUpDown^ PeriodicEventInterval3UpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel82;
		private: System::Windows::Forms::Label^ label108;
		private: System::Windows::Forms::Label^ label109;
		private: System::Windows::Forms::NumericUpDown^ PeriodicEventInterval4UpDown;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel83;
		private: System::Windows::Forms::Label^ label110;
		private: System::Windows::Forms::Label^ label111;
		private: System::Windows::Forms::NumericUpDown^ PeriodicEventInterval5UpDown;
		private: System::Windows::Forms::Label^ label112;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent1EnableCheckBox;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent2EnableCheckBox;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent3EnableCheckBox;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent4EnableCheckBox;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent5EnableCheckBox;
		private: System::Windows::Forms::Label^ label113;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent1DisableCheckBox;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent2DisableCheckBox;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent3DisableCheckBox;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent4DisableCheckBox;
		private: System::Windows::Forms::CheckBox^ PeriodicEvent5DisableCheckBox;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel84;
		private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel85;
		private: System::Windows::Forms::NumericUpDown^ RecordingFrameRateNumericUpDown;
		private: System::Windows::Forms::Label^ label115;
		private: System::Windows::Forms::Label^ label114;
		private: System::Windows::Forms::Label^ label38;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ThermalCameraGUI::typeid));
			this->MainThermalCameraPanel = (gcnew System::Windows::Forms::Panel());
			this->ScrollPaddingPanel = (gcnew System::Windows::Forms::Panel());
			this->PeriodicTriggerSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel78 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel77 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label99 = (gcnew System::Windows::Forms::Label());
			this->label94 = (gcnew System::Windows::Forms::Label());
			this->label95 = (gcnew System::Windows::Forms::Label());
			this->label96 = (gcnew System::Windows::Forms::Label());
			this->label97 = (gcnew System::Windows::Forms::Label());
			this->label98 = (gcnew System::Windows::Forms::Label());
			this->label100 = (gcnew System::Windows::Forms::Label());
			this->PeriodicEvent1ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->PeriodicEvent2ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->PeriodicEvent3ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->PeriodicEvent4ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->PeriodicEvent5ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label101 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel80 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label104 = (gcnew System::Windows::Forms::Label());
			this->label105 = (gcnew System::Windows::Forms::Label());
			this->PeriodicEventInterval1UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel79 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label102 = (gcnew System::Windows::Forms::Label());
			this->label103 = (gcnew System::Windows::Forms::Label());
			this->PeriodicEventInterval2UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel81 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label106 = (gcnew System::Windows::Forms::Label());
			this->label107 = (gcnew System::Windows::Forms::Label());
			this->PeriodicEventInterval3UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel82 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label108 = (gcnew System::Windows::Forms::Label());
			this->label109 = (gcnew System::Windows::Forms::Label());
			this->PeriodicEventInterval4UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel83 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label110 = (gcnew System::Windows::Forms::Label());
			this->label111 = (gcnew System::Windows::Forms::Label());
			this->PeriodicEventInterval5UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label112 = (gcnew System::Windows::Forms::Label());
			this->PeriodicEvent1EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicEvent2EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicEvent3EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicEvent4EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicEvent5EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label113 = (gcnew System::Windows::Forms::Label());
			this->PeriodicEvent1DisableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicEvent2DisableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicEvent3DisableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicEvent4DisableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicEvent5DisableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PeriodicTriggerConfigMenuButton = (gcnew System::Windows::Forms::Button());
			this->TempAlarmsConfigSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel39 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel40 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel55 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label76 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm5HighTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel54 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label74 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm4HighTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel53 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label73 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm3HighTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel52 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm2HighTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel51 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm1HighTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel41 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm1LowTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->TempAlarm1AlarmTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->label64 = (gcnew System::Windows::Forms::Label());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm1DataSourceComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm2DataSourceComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm3DataSourceComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm4DataSourceComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm5DataSourceComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm2AlarmTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm3AlarmTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm4AlarmTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm5AlarmTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->tableLayoutPanel45 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label75 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm5LowTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel42 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm2LowTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel43 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm3LowTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel44 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm4LowTempThresUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label87 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm1EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TempAlarm2EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TempAlarm3EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TempAlarm4EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TempAlarm5EnableCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label88 = (gcnew System::Windows::Forms::Label());
			this->TempAlarm1TriggerActionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm2TriggerActionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm3TriggerActionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm4TriggerActionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TempAlarm5TriggerActionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->tableLayoutPanel57 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel46 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel47 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->TempAlarm1StatusLabel = (gcnew System::Windows::Forms::Label());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel48 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->TempAlarm2StatusLabel = (gcnew System::Windows::Forms::Label());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel49 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->TempAlarm3StatusLabel = (gcnew System::Windows::Forms::Label());
			this->label77 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel50 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->TempAlarm4StatusLabel = (gcnew System::Windows::Forms::Label());
			this->label79 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel56 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->TempAlarm5StatusLabel = (gcnew System::Windows::Forms::Label());
			this->label81 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel58 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel59 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->AlarmTriggerEventsIntervalUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->EnableAlarmTriggerEventsCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TempAlarmsTriggerSoundCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayoutPanel71 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->Alarm4TriggerEventResetButton = (gcnew System::Windows::Forms::Button());
			this->Alarm5TriggerEventResetButton = (gcnew System::Windows::Forms::Button());
			this->Alarm3TriggerEventResetButton = (gcnew System::Windows::Forms::Button());
			this->Alarm1TriggerEventResetButton = (gcnew System::Windows::Forms::Button());
			this->Alarm2TriggerEventResetButton = (gcnew System::Windows::Forms::Button());
			this->label90 = (gcnew System::Windows::Forms::Label());
			this->TempAlarmsConfigMenuButton = (gcnew System::Windows::Forms::Button());
			this->DataLoggingSettingsSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel34 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel35 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DefaultDataLoggingSavePathString = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel75 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel76 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label93 = (gcnew System::Windows::Forms::Label());
			this->DataLoggingCSVDelimiterCombiBox = (gcnew System::Windows::Forms::ComboBox());
			this->tableLayoutPanel36 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel63 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->ChangeCSVDefaultPathButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel64 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel65 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel37 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->LogIntervalUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel66 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel38 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->DurationSecondsUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->DurationMinuteUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->DurationHourUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->DataLoggingSettingsMenuButton = (gcnew System::Windows::Forms::Button());
			this->TempPlotDataSetSettingsSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel33 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet1ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->DataSet10ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->tableLayoutPanel14 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet10UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel13 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet9UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel12 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet8UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel11 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet7UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel10 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet6UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet5UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet4UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet3UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet2UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataSet1UpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->DataSet9ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->DataSet8ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->DataSet7ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->DataSet6ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->DataSet5ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->DataSet4ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->DataSet3ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->DataSet2ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel24 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->DataSet10ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel23 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->DataSet9ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel22 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->DataSet8ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel21 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->DataSet7ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel20 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->DataSet6ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel19 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->DataSet5ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel18 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->DataSet4ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel17 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->DataSet3ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel16 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->DataSet2ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel15 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->DataSet1ColorPanel = (gcnew System::Windows::Forms::Panel());
			this->DataSet10CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet9CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet8CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet7CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet6CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet5CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet4CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet3CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet2CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DataSet1CheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->label89 = (gcnew System::Windows::Forms::Label());
			this->TempPlotDataSetSettingsMenuButton = (gcnew System::Windows::Forms::Button());
			this->VideoRecSettingsSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel61 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel60 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel84 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel85 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->RecordingFrameRateNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label115 = (gcnew System::Windows::Forms::Label());
			this->label114 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel70 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label86 = (gcnew System::Windows::Forms::Label());
			this->SaveRawAnalysisRecordingButton = (gcnew System::Windows::Forms::Button());
			this->label85 = (gcnew System::Windows::Forms::Label());
			this->ChangeRecordingDefaultPathButton = (gcnew System::Windows::Forms::Button());
			this->label78 = (gcnew System::Windows::Forms::Label());
			this->UseWinSnippingToolButton = (gcnew System::Windows::Forms::Button());
			this->UseWin11ScreenRecordToolButton = (gcnew System::Windows::Forms::Button());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->DefaultRecordingSavePathString = (gcnew System::Windows::Forms::Label());
			this->VideoRecordingMenuButton = (gcnew System::Windows::Forms::Button());
			this->SnapshotConfigSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel32 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel72 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label91 = (gcnew System::Windows::Forms::Label());
			this->FullFrameTempDataCSVDelimiterCombiBox = (gcnew System::Windows::Forms::ComboBox());
			this->DefaultSnapshotSavePathString = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->ChangeSnapDefaultPathButton = (gcnew System::Windows::Forms::Button());
			this->IncludeColorbarSnapButton = (gcnew System::Windows::Forms::Button());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->SaveRawSensorSnapButton = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SnapshotConfigMenuButton = (gcnew System::Windows::Forms::Button());
			this->AutoCalSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel31 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel68 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel73 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label92 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel74 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->SensorDriftCalUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->MaxTempDriftSetPountLabel = (gcnew System::Windows::Forms::Label());
			this->SensorDriftCalButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel62 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->AutoCalPeriodUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->AutoShutterCalButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel69 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->CameraShutterTempLabel = (gcnew System::Windows::Forms::Label());
			this->CameraCoreTempLabel = (gcnew System::Windows::Forms::Label());
			this->ReadIntCameraTempsButton = (gcnew System::Windows::Forms::Button());
			this->CameraDetectorTempLabel = (gcnew System::Windows::Forms::Label());
			this->AutoCalMenuButton = (gcnew System::Windows::Forms::Button());
			this->CameraConfigSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel30 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel27 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel28 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label84 = (gcnew System::Windows::Forms::Label());
			this->RecoverDefaultCameraSettingsButton = (gcnew System::Windows::Forms::Button());
			this->label82 = (gcnew System::Windows::Forms::Label());
			this->label80 = (gcnew System::Windows::Forms::Label());
			this->ReadCameraConfigButton = (gcnew System::Windows::Forms::Button());
			this->SetCameraConfigButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel29 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel26 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->TempCorrUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->ReflectedTempUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->TempCorrLabel = (gcnew System::Windows::Forms::Label());
			this->DistanceUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->DistanceLabel = (gcnew System::Windows::Forms::Label());
			this->AmbientTempLabel = (gcnew System::Windows::Forms::Label());
			this->EmissivityLabel = (gcnew System::Windows::Forms::Label());
			this->HumidityLabel = (gcnew System::Windows::Forms::Label());
			this->EmissivityUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->AmbientTempUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->ReflectedTempLabel = (gcnew System::Windows::Forms::Label());
			this->HumidityUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->CameraConfigMenuButton = (gcnew System::Windows::Forms::Button());
			this->ConnectTCAMSubMenuPanel = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel25 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel67 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label83 = (gcnew System::Windows::Forms::Label());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->CameraSourceDropList = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ConnectButton = (gcnew System::Windows::Forms::Button());
			this->DisconnectButton = (gcnew System::Windows::Forms::Button());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->ConnectTCAMMenuButton = (gcnew System::Windows::Forms::Button());
			this->AutoCalTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->AlarmSoundTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->AlarmTriggerEventTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->DriftCalTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->PeriodicTriggerTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->MainThermalCameraPanel->SuspendLayout();
			this->PeriodicTriggerSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel78->SuspendLayout();
			this->tableLayoutPanel77->SuspendLayout();
			this->tableLayoutPanel80->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval1UpDown))->BeginInit();
			this->tableLayoutPanel79->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval2UpDown))->BeginInit();
			this->tableLayoutPanel81->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval3UpDown))->BeginInit();
			this->tableLayoutPanel82->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval4UpDown))->BeginInit();
			this->tableLayoutPanel83->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval5UpDown))->BeginInit();
			this->TempAlarmsConfigSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel39->SuspendLayout();
			this->tableLayoutPanel40->SuspendLayout();
			this->tableLayoutPanel55->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm5HighTempThresUpDown))->BeginInit();
			this->tableLayoutPanel54->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm4HighTempThresUpDown))->BeginInit();
			this->tableLayoutPanel53->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm3HighTempThresUpDown))->BeginInit();
			this->tableLayoutPanel52->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm2HighTempThresUpDown))->BeginInit();
			this->tableLayoutPanel51->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm1HighTempThresUpDown))->BeginInit();
			this->tableLayoutPanel41->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm1LowTempThresUpDown))->BeginInit();
			this->tableLayoutPanel45->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm5LowTempThresUpDown))->BeginInit();
			this->tableLayoutPanel42->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm2LowTempThresUpDown))->BeginInit();
			this->tableLayoutPanel43->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm3LowTempThresUpDown))->BeginInit();
			this->tableLayoutPanel44->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm4LowTempThresUpDown))->BeginInit();
			this->tableLayoutPanel57->SuspendLayout();
			this->tableLayoutPanel46->SuspendLayout();
			this->tableLayoutPanel47->SuspendLayout();
			this->tableLayoutPanel48->SuspendLayout();
			this->tableLayoutPanel49->SuspendLayout();
			this->tableLayoutPanel50->SuspendLayout();
			this->tableLayoutPanel56->SuspendLayout();
			this->tableLayoutPanel58->SuspendLayout();
			this->tableLayoutPanel59->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AlarmTriggerEventsIntervalUpDown))->BeginInit();
			this->tableLayoutPanel71->SuspendLayout();
			this->DataLoggingSettingsSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel34->SuspendLayout();
			this->tableLayoutPanel35->SuspendLayout();
			this->tableLayoutPanel75->SuspendLayout();
			this->tableLayoutPanel76->SuspendLayout();
			this->tableLayoutPanel36->SuspendLayout();
			this->tableLayoutPanel63->SuspendLayout();
			this->tableLayoutPanel64->SuspendLayout();
			this->tableLayoutPanel65->SuspendLayout();
			this->tableLayoutPanel37->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LogIntervalUpDown))->BeginInit();
			this->tableLayoutPanel66->SuspendLayout();
			this->tableLayoutPanel38->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DurationSecondsUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DurationMinuteUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DurationHourUpDown))->BeginInit();
			this->TempPlotDataSetSettingsSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel33->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel14->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet10UpDown))->BeginInit();
			this->tableLayoutPanel13->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet9UpDown))->BeginInit();
			this->tableLayoutPanel12->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet8UpDown))->BeginInit();
			this->tableLayoutPanel11->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet7UpDown))->BeginInit();
			this->tableLayoutPanel10->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet6UpDown))->BeginInit();
			this->tableLayoutPanel9->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet5UpDown))->BeginInit();
			this->tableLayoutPanel8->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet4UpDown))->BeginInit();
			this->tableLayoutPanel7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet3UpDown))->BeginInit();
			this->tableLayoutPanel6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet2UpDown))->BeginInit();
			this->tableLayoutPanel5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet1UpDown))->BeginInit();
			this->tableLayoutPanel24->SuspendLayout();
			this->tableLayoutPanel23->SuspendLayout();
			this->tableLayoutPanel22->SuspendLayout();
			this->tableLayoutPanel21->SuspendLayout();
			this->tableLayoutPanel20->SuspendLayout();
			this->tableLayoutPanel19->SuspendLayout();
			this->tableLayoutPanel18->SuspendLayout();
			this->tableLayoutPanel17->SuspendLayout();
			this->tableLayoutPanel16->SuspendLayout();
			this->tableLayoutPanel15->SuspendLayout();
			this->VideoRecSettingsSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel61->SuspendLayout();
			this->tableLayoutPanel60->SuspendLayout();
			this->tableLayoutPanel84->SuspendLayout();
			this->tableLayoutPanel85->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RecordingFrameRateNumericUpDown))->BeginInit();
			this->tableLayoutPanel70->SuspendLayout();
			this->SnapshotConfigSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel32->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel72->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->AutoCalSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel31->SuspendLayout();
			this->tableLayoutPanel68->SuspendLayout();
			this->tableLayoutPanel73->SuspendLayout();
			this->tableLayoutPanel74->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SensorDriftCalUpDown))->BeginInit();
			this->tableLayoutPanel62->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AutoCalPeriodUpDown))->BeginInit();
			this->tableLayoutPanel69->SuspendLayout();
			this->CameraConfigSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel30->SuspendLayout();
			this->tableLayoutPanel27->SuspendLayout();
			this->tableLayoutPanel28->SuspendLayout();
			this->tableLayoutPanel29->SuspendLayout();
			this->tableLayoutPanel26->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempCorrUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReflectedTempUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DistanceUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EmissivityUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AmbientTempUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HumidityUpDown))->BeginInit();
			this->ConnectTCAMSubMenuPanel->SuspendLayout();
			this->tableLayoutPanel25->SuspendLayout();
			this->tableLayoutPanel67->SuspendLayout();
			this->panel11->SuspendLayout();
			this->SuspendLayout();
			// 
			// MainThermalCameraPanel
			// 
			this->MainThermalCameraPanel->AutoScroll = true;
			this->MainThermalCameraPanel->AutoScrollMinSize = System::Drawing::Size(1345, 900);
			this->MainThermalCameraPanel->Controls->Add(this->ScrollPaddingPanel);
			this->MainThermalCameraPanel->Controls->Add(this->PeriodicTriggerSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->PeriodicTriggerConfigMenuButton);
			this->MainThermalCameraPanel->Controls->Add(this->TempAlarmsConfigSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->TempAlarmsConfigMenuButton);
			this->MainThermalCameraPanel->Controls->Add(this->DataLoggingSettingsSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->DataLoggingSettingsMenuButton);
			this->MainThermalCameraPanel->Controls->Add(this->TempPlotDataSetSettingsSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->TempPlotDataSetSettingsMenuButton);
			this->MainThermalCameraPanel->Controls->Add(this->VideoRecSettingsSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->VideoRecordingMenuButton);
			this->MainThermalCameraPanel->Controls->Add(this->SnapshotConfigSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->SnapshotConfigMenuButton);
			this->MainThermalCameraPanel->Controls->Add(this->AutoCalSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->AutoCalMenuButton);
			this->MainThermalCameraPanel->Controls->Add(this->CameraConfigSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->CameraConfigMenuButton);
			this->MainThermalCameraPanel->Controls->Add(this->ConnectTCAMSubMenuPanel);
			this->MainThermalCameraPanel->Controls->Add(this->ConnectTCAMMenuButton);
			this->MainThermalCameraPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->MainThermalCameraPanel->Location = System::Drawing::Point(0, 0);
			this->MainThermalCameraPanel->Name = L"MainThermalCameraPanel";
			this->MainThermalCameraPanel->Padding = System::Windows::Forms::Padding(10);
			this->MainThermalCameraPanel->Size = System::Drawing::Size(1407, 903);
			this->MainThermalCameraPanel->TabIndex = 0;
			// 
			// ScrollPaddingPanel
			// 
			this->ScrollPaddingPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->ScrollPaddingPanel->Location = System::Drawing::Point(10, 3453);
			this->ScrollPaddingPanel->Name = L"ScrollPaddingPanel";
			this->ScrollPaddingPanel->Size = System::Drawing::Size(1370, 650);
			this->ScrollPaddingPanel->TabIndex = 0;
			// 
			// PeriodicTriggerSubMenuPanel
			// 
			this->PeriodicTriggerSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->PeriodicTriggerSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->PeriodicTriggerSubMenuPanel->Controls->Add(this->tableLayoutPanel78);
			this->PeriodicTriggerSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->PeriodicTriggerSubMenuPanel->Location = System::Drawing::Point(10, 3236);
			this->PeriodicTriggerSubMenuPanel->Name = L"PeriodicTriggerSubMenuPanel";
			this->PeriodicTriggerSubMenuPanel->Padding = System::Windows::Forms::Padding(5);
			this->PeriodicTriggerSubMenuPanel->Size = System::Drawing::Size(1370, 217);
			this->PeriodicTriggerSubMenuPanel->TabIndex = 53;
			this->PeriodicTriggerSubMenuPanel->Visible = false;
			// 
			// tableLayoutPanel78
			// 
			this->tableLayoutPanel78->ColumnCount = 1;
			this->tableLayoutPanel78->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel78->Controls->Add(this->tableLayoutPanel77, 0, 0);
			this->tableLayoutPanel78->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel78->Location = System::Drawing::Point(5, 5);
			this->tableLayoutPanel78->Name = L"tableLayoutPanel78";
			this->tableLayoutPanel78->RowCount = 2;
			this->tableLayoutPanel78->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				205)));
			this->tableLayoutPanel78->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel78->Size = System::Drawing::Size(1358, 205);
			this->tableLayoutPanel78->TabIndex = 1;
			// 
			// tableLayoutPanel77
			// 
			this->tableLayoutPanel77->ColumnCount = 6;
			this->tableLayoutPanel77->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				139)));
			this->tableLayoutPanel77->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				229)));
			this->tableLayoutPanel77->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				297)));
			this->tableLayoutPanel77->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				204)));
			this->tableLayoutPanel77->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				114)));
			this->tableLayoutPanel77->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				369)));
			this->tableLayoutPanel77->Controls->Add(this->label99, 0, 5);
			this->tableLayoutPanel77->Controls->Add(this->label94, 0, 0);
			this->tableLayoutPanel77->Controls->Add(this->label95, 0, 1);
			this->tableLayoutPanel77->Controls->Add(this->label96, 0, 2);
			this->tableLayoutPanel77->Controls->Add(this->label97, 0, 3);
			this->tableLayoutPanel77->Controls->Add(this->label98, 0, 4);
			this->tableLayoutPanel77->Controls->Add(this->label100, 1, 0);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent1ComboBox, 1, 1);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent2ComboBox, 1, 2);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent3ComboBox, 1, 3);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent4ComboBox, 1, 4);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent5ComboBox, 1, 5);
			this->tableLayoutPanel77->Controls->Add(this->label101, 2, 0);
			this->tableLayoutPanel77->Controls->Add(this->tableLayoutPanel80, 2, 1);
			this->tableLayoutPanel77->Controls->Add(this->tableLayoutPanel79, 2, 2);
			this->tableLayoutPanel77->Controls->Add(this->tableLayoutPanel81, 2, 3);
			this->tableLayoutPanel77->Controls->Add(this->tableLayoutPanel82, 2, 4);
			this->tableLayoutPanel77->Controls->Add(this->tableLayoutPanel83, 2, 5);
			this->tableLayoutPanel77->Controls->Add(this->label112, 4, 0);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent1EnableCheckBox, 4, 1);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent2EnableCheckBox, 4, 2);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent3EnableCheckBox, 4, 3);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent4EnableCheckBox, 4, 4);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent5EnableCheckBox, 4, 5);
			this->tableLayoutPanel77->Controls->Add(this->label113, 3, 0);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent1DisableCheckBox, 3, 1);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent2DisableCheckBox, 3, 2);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent3DisableCheckBox, 3, 3);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent4DisableCheckBox, 3, 4);
			this->tableLayoutPanel77->Controls->Add(this->PeriodicEvent5DisableCheckBox, 3, 5);
			this->tableLayoutPanel77->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel77->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel77->Name = L"tableLayoutPanel77";
			this->tableLayoutPanel77->RowCount = 6;
			this->tableLayoutPanel77->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				29)));
			this->tableLayoutPanel77->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel77->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel77->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel77->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel77->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel77->Size = System::Drawing::Size(1352, 199);
			this->tableLayoutPanel77->TabIndex = 0;
			// 
			// label99
			// 
			this->label99->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label99->AutoSize = true;
			this->label99->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label99->ForeColor = System::Drawing::Color::White;
			this->label99->Location = System::Drawing::Point(6, 174);
			this->label99->Name = L"label99";
			this->label99->Size = System::Drawing::Size(126, 16);
			this->label99->TabIndex = 57;
			this->label99->Text = L"Periodic Event 5:";
			this->label99->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label94
			// 
			this->label94->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label94->AutoSize = true;
			this->label94->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label94->ForeColor = System::Drawing::Color::White;
			this->label94->Location = System::Drawing::Point(43, 6);
			this->label94->Name = L"label94";
			this->label94->Size = System::Drawing::Size(52, 16);
			this->label94->TabIndex = 52;
			this->label94->Text = L"Event:";
			this->label94->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label95
			// 
			this->label95->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label95->AutoSize = true;
			this->label95->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label95->ForeColor = System::Drawing::Color::White;
			this->label95->Location = System::Drawing::Point(6, 38);
			this->label95->Name = L"label95";
			this->label95->Size = System::Drawing::Size(126, 16);
			this->label95->TabIndex = 53;
			this->label95->Text = L"Periodic Event 1:";
			this->label95->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label96
			// 
			this->label96->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label96->AutoSize = true;
			this->label96->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label96->ForeColor = System::Drawing::Color::White;
			this->label96->Location = System::Drawing::Point(6, 72);
			this->label96->Name = L"label96";
			this->label96->Size = System::Drawing::Size(126, 16);
			this->label96->TabIndex = 54;
			this->label96->Text = L"Periodic Event 2:";
			this->label96->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label97
			// 
			this->label97->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label97->AutoSize = true;
			this->label97->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label97->ForeColor = System::Drawing::Color::White;
			this->label97->Location = System::Drawing::Point(6, 106);
			this->label97->Name = L"label97";
			this->label97->Size = System::Drawing::Size(126, 16);
			this->label97->TabIndex = 55;
			this->label97->Text = L"Periodic Event 3:";
			this->label97->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label98
			// 
			this->label98->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label98->AutoSize = true;
			this->label98->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label98->ForeColor = System::Drawing::Color::White;
			this->label98->Location = System::Drawing::Point(6, 140);
			this->label98->Name = L"label98";
			this->label98->Size = System::Drawing::Size(126, 16);
			this->label98->TabIndex = 56;
			this->label98->Text = L"Periodic Event 4:";
			this->label98->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label100
			// 
			this->label100->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label100->AutoSize = true;
			this->label100->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label100->ForeColor = System::Drawing::Color::White;
			this->label100->Location = System::Drawing::Point(194, 6);
			this->label100->Name = L"label100";
			this->label100->Size = System::Drawing::Size(118, 16);
			this->label100->TabIndex = 58;
			this->label100->Text = L"Event Function:";
			this->label100->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PeriodicEvent1ComboBox
			// 
			this->PeriodicEvent1ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent1ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEvent1ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PeriodicEvent1ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PeriodicEvent1ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent1ComboBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent1ComboBox->IntegralHeight = false;
			this->PeriodicEvent1ComboBox->Location = System::Drawing::Point(144, 34);
			this->PeriodicEvent1ComboBox->Margin = System::Windows::Forms::Padding(5, 3, 5, 3);
			this->PeriodicEvent1ComboBox->MaxDropDownItems = 50;
			this->PeriodicEvent1ComboBox->Name = L"PeriodicEvent1ComboBox";
			this->PeriodicEvent1ComboBox->Size = System::Drawing::Size(219, 24);
			this->PeriodicEvent1ComboBox->TabIndex = 67;
			this->PeriodicEvent1ComboBox->TabStop = false;
			this->PeriodicEvent1ComboBox->Tag = L"0";
			// 
			// PeriodicEvent2ComboBox
			// 
			this->PeriodicEvent2ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent2ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEvent2ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PeriodicEvent2ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PeriodicEvent2ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent2ComboBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent2ComboBox->IntegralHeight = false;
			this->PeriodicEvent2ComboBox->Location = System::Drawing::Point(144, 68);
			this->PeriodicEvent2ComboBox->Margin = System::Windows::Forms::Padding(5, 3, 5, 3);
			this->PeriodicEvent2ComboBox->MaxDropDownItems = 50;
			this->PeriodicEvent2ComboBox->Name = L"PeriodicEvent2ComboBox";
			this->PeriodicEvent2ComboBox->Size = System::Drawing::Size(219, 24);
			this->PeriodicEvent2ComboBox->TabIndex = 68;
			this->PeriodicEvent2ComboBox->TabStop = false;
			this->PeriodicEvent2ComboBox->Tag = L"1";
			// 
			// PeriodicEvent3ComboBox
			// 
			this->PeriodicEvent3ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent3ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEvent3ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PeriodicEvent3ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PeriodicEvent3ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent3ComboBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent3ComboBox->IntegralHeight = false;
			this->PeriodicEvent3ComboBox->Location = System::Drawing::Point(144, 102);
			this->PeriodicEvent3ComboBox->Margin = System::Windows::Forms::Padding(5, 3, 5, 3);
			this->PeriodicEvent3ComboBox->MaxDropDownItems = 50;
			this->PeriodicEvent3ComboBox->Name = L"PeriodicEvent3ComboBox";
			this->PeriodicEvent3ComboBox->Size = System::Drawing::Size(219, 24);
			this->PeriodicEvent3ComboBox->TabIndex = 69;
			this->PeriodicEvent3ComboBox->TabStop = false;
			this->PeriodicEvent3ComboBox->Tag = L"2";
			// 
			// PeriodicEvent4ComboBox
			// 
			this->PeriodicEvent4ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent4ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEvent4ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PeriodicEvent4ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PeriodicEvent4ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent4ComboBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent4ComboBox->IntegralHeight = false;
			this->PeriodicEvent4ComboBox->Location = System::Drawing::Point(144, 136);
			this->PeriodicEvent4ComboBox->Margin = System::Windows::Forms::Padding(5, 3, 5, 3);
			this->PeriodicEvent4ComboBox->MaxDropDownItems = 50;
			this->PeriodicEvent4ComboBox->Name = L"PeriodicEvent4ComboBox";
			this->PeriodicEvent4ComboBox->Size = System::Drawing::Size(219, 24);
			this->PeriodicEvent4ComboBox->TabIndex = 70;
			this->PeriodicEvent4ComboBox->TabStop = false;
			this->PeriodicEvent4ComboBox->Tag = L"3";
			// 
			// PeriodicEvent5ComboBox
			// 
			this->PeriodicEvent5ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent5ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEvent5ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PeriodicEvent5ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PeriodicEvent5ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent5ComboBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent5ComboBox->IntegralHeight = false;
			this->PeriodicEvent5ComboBox->Location = System::Drawing::Point(144, 170);
			this->PeriodicEvent5ComboBox->Margin = System::Windows::Forms::Padding(5, 3, 5, 3);
			this->PeriodicEvent5ComboBox->MaxDropDownItems = 50;
			this->PeriodicEvent5ComboBox->Name = L"PeriodicEvent5ComboBox";
			this->PeriodicEvent5ComboBox->Size = System::Drawing::Size(219, 24);
			this->PeriodicEvent5ComboBox->TabIndex = 71;
			this->PeriodicEvent5ComboBox->TabStop = false;
			this->PeriodicEvent5ComboBox->Tag = L"4";
			// 
			// label101
			// 
			this->label101->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label101->AutoSize = true;
			this->label101->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label101->ForeColor = System::Drawing::Color::White;
			this->label101->Location = System::Drawing::Point(457, 6);
			this->label101->Name = L"label101";
			this->label101->Size = System::Drawing::Size(119, 16);
			this->label101->TabIndex = 72;
			this->label101->Text = L"Trigger Interval:";
			this->label101->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel80
			// 
			this->tableLayoutPanel80->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel80->ColumnCount = 3;
			this->tableLayoutPanel80->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				132)));
			this->tableLayoutPanel80->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				112)));
			this->tableLayoutPanel80->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->tableLayoutPanel80->Controls->Add(this->label104, 0, 0);
			this->tableLayoutPanel80->Controls->Add(this->label105, 2, 0);
			this->tableLayoutPanel80->Controls->Add(this->PeriodicEventInterval1UpDown, 1, 0);
			this->tableLayoutPanel80->Location = System::Drawing::Point(371, 32);
			this->tableLayoutPanel80->Name = L"tableLayoutPanel80";
			this->tableLayoutPanel80->RowCount = 1;
			this->tableLayoutPanel80->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel80->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				28)));
			this->tableLayoutPanel80->Size = System::Drawing::Size(291, 28);
			this->tableLayoutPanel80->TabIndex = 101;
			// 
			// label104
			// 
			this->label104->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label104->AutoSize = true;
			this->label104->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label104->ForeColor = System::Drawing::Color::White;
			this->label104->Location = System::Drawing::Point(5, 6);
			this->label104->Name = L"label104";
			this->label104->Size = System::Drawing::Size(122, 16);
			this->label104->TabIndex = 101;
			this->label104->Text = L"Event 1 Interval:";
			this->label104->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label105
			// 
			this->label105->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label105->AutoSize = true;
			this->label105->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label105->ForeColor = System::Drawing::Color::White;
			this->label105->Location = System::Drawing::Point(252, 6);
			this->label105->Name = L"label105";
			this->label105->Size = System::Drawing::Size(33, 16);
			this->label105->TabIndex = 101;
			this->label105->Text = L"Sec";
			this->label105->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PeriodicEventInterval1UpDown
			// 
			this->PeriodicEventInterval1UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEventInterval1UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEventInterval1UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->PeriodicEventInterval1UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEventInterval1UpDown->ForeColor = System::Drawing::Color::White;
			this->PeriodicEventInterval1UpDown->Location = System::Drawing::Point(136, 4);
			this->PeriodicEventInterval1UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->PeriodicEventInterval1UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PeriodicEventInterval1UpDown->Name = L"PeriodicEventInterval1UpDown";
			this->PeriodicEventInterval1UpDown->Size = System::Drawing::Size(104, 20);
			this->PeriodicEventInterval1UpDown->TabIndex = 20;
			this->PeriodicEventInterval1UpDown->Tag = L"0";
			this->PeriodicEventInterval1UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->PeriodicEventInterval1UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			// 
			// tableLayoutPanel79
			// 
			this->tableLayoutPanel79->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel79->ColumnCount = 3;
			this->tableLayoutPanel79->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				132)));
			this->tableLayoutPanel79->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				112)));
			this->tableLayoutPanel79->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->tableLayoutPanel79->Controls->Add(this->label102, 0, 0);
			this->tableLayoutPanel79->Controls->Add(this->label103, 2, 0);
			this->tableLayoutPanel79->Controls->Add(this->PeriodicEventInterval2UpDown, 1, 0);
			this->tableLayoutPanel79->Location = System::Drawing::Point(371, 66);
			this->tableLayoutPanel79->Name = L"tableLayoutPanel79";
			this->tableLayoutPanel79->RowCount = 1;
			this->tableLayoutPanel79->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel79->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				28)));
			this->tableLayoutPanel79->Size = System::Drawing::Size(291, 28);
			this->tableLayoutPanel79->TabIndex = 102;
			// 
			// label102
			// 
			this->label102->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label102->AutoSize = true;
			this->label102->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label102->ForeColor = System::Drawing::Color::White;
			this->label102->Location = System::Drawing::Point(5, 6);
			this->label102->Name = L"label102";
			this->label102->Size = System::Drawing::Size(122, 16);
			this->label102->TabIndex = 101;
			this->label102->Text = L"Event 2 Interval:";
			this->label102->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label103
			// 
			this->label103->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label103->AutoSize = true;
			this->label103->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label103->ForeColor = System::Drawing::Color::White;
			this->label103->Location = System::Drawing::Point(252, 6);
			this->label103->Name = L"label103";
			this->label103->Size = System::Drawing::Size(33, 16);
			this->label103->TabIndex = 101;
			this->label103->Text = L"Sec";
			this->label103->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PeriodicEventInterval2UpDown
			// 
			this->PeriodicEventInterval2UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEventInterval2UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEventInterval2UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->PeriodicEventInterval2UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEventInterval2UpDown->ForeColor = System::Drawing::Color::White;
			this->PeriodicEventInterval2UpDown->Location = System::Drawing::Point(136, 4);
			this->PeriodicEventInterval2UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->PeriodicEventInterval2UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PeriodicEventInterval2UpDown->Name = L"PeriodicEventInterval2UpDown";
			this->PeriodicEventInterval2UpDown->Size = System::Drawing::Size(104, 20);
			this->PeriodicEventInterval2UpDown->TabIndex = 20;
			this->PeriodicEventInterval2UpDown->Tag = L"1";
			this->PeriodicEventInterval2UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->PeriodicEventInterval2UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			// 
			// tableLayoutPanel81
			// 
			this->tableLayoutPanel81->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel81->ColumnCount = 3;
			this->tableLayoutPanel81->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				132)));
			this->tableLayoutPanel81->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				112)));
			this->tableLayoutPanel81->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->tableLayoutPanel81->Controls->Add(this->label106, 0, 0);
			this->tableLayoutPanel81->Controls->Add(this->label107, 2, 0);
			this->tableLayoutPanel81->Controls->Add(this->PeriodicEventInterval3UpDown, 1, 0);
			this->tableLayoutPanel81->Location = System::Drawing::Point(371, 100);
			this->tableLayoutPanel81->Name = L"tableLayoutPanel81";
			this->tableLayoutPanel81->RowCount = 1;
			this->tableLayoutPanel81->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel81->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				28)));
			this->tableLayoutPanel81->Size = System::Drawing::Size(291, 28);
			this->tableLayoutPanel81->TabIndex = 103;
			// 
			// label106
			// 
			this->label106->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label106->AutoSize = true;
			this->label106->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label106->ForeColor = System::Drawing::Color::White;
			this->label106->Location = System::Drawing::Point(5, 6);
			this->label106->Name = L"label106";
			this->label106->Size = System::Drawing::Size(122, 16);
			this->label106->TabIndex = 101;
			this->label106->Text = L"Event 3 Interval:";
			this->label106->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label107
			// 
			this->label107->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label107->AutoSize = true;
			this->label107->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label107->ForeColor = System::Drawing::Color::White;
			this->label107->Location = System::Drawing::Point(252, 6);
			this->label107->Name = L"label107";
			this->label107->Size = System::Drawing::Size(33, 16);
			this->label107->TabIndex = 101;
			this->label107->Text = L"Sec";
			this->label107->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PeriodicEventInterval3UpDown
			// 
			this->PeriodicEventInterval3UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEventInterval3UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEventInterval3UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->PeriodicEventInterval3UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEventInterval3UpDown->ForeColor = System::Drawing::Color::White;
			this->PeriodicEventInterval3UpDown->Location = System::Drawing::Point(136, 4);
			this->PeriodicEventInterval3UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->PeriodicEventInterval3UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PeriodicEventInterval3UpDown->Name = L"PeriodicEventInterval3UpDown";
			this->PeriodicEventInterval3UpDown->Size = System::Drawing::Size(104, 20);
			this->PeriodicEventInterval3UpDown->TabIndex = 20;
			this->PeriodicEventInterval3UpDown->Tag = L"2";
			this->PeriodicEventInterval3UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->PeriodicEventInterval3UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			// 
			// tableLayoutPanel82
			// 
			this->tableLayoutPanel82->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel82->ColumnCount = 3;
			this->tableLayoutPanel82->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				132)));
			this->tableLayoutPanel82->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				112)));
			this->tableLayoutPanel82->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->tableLayoutPanel82->Controls->Add(this->label108, 0, 0);
			this->tableLayoutPanel82->Controls->Add(this->label109, 2, 0);
			this->tableLayoutPanel82->Controls->Add(this->PeriodicEventInterval4UpDown, 1, 0);
			this->tableLayoutPanel82->Location = System::Drawing::Point(371, 134);
			this->tableLayoutPanel82->Name = L"tableLayoutPanel82";
			this->tableLayoutPanel82->RowCount = 1;
			this->tableLayoutPanel82->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel82->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				28)));
			this->tableLayoutPanel82->Size = System::Drawing::Size(291, 28);
			this->tableLayoutPanel82->TabIndex = 104;
			// 
			// label108
			// 
			this->label108->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label108->AutoSize = true;
			this->label108->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label108->ForeColor = System::Drawing::Color::White;
			this->label108->Location = System::Drawing::Point(5, 6);
			this->label108->Name = L"label108";
			this->label108->Size = System::Drawing::Size(122, 16);
			this->label108->TabIndex = 101;
			this->label108->Text = L"Event 4 Interval:";
			this->label108->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label109
			// 
			this->label109->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label109->AutoSize = true;
			this->label109->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label109->ForeColor = System::Drawing::Color::White;
			this->label109->Location = System::Drawing::Point(252, 6);
			this->label109->Name = L"label109";
			this->label109->Size = System::Drawing::Size(33, 16);
			this->label109->TabIndex = 101;
			this->label109->Text = L"Sec";
			this->label109->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PeriodicEventInterval4UpDown
			// 
			this->PeriodicEventInterval4UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEventInterval4UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEventInterval4UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->PeriodicEventInterval4UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEventInterval4UpDown->ForeColor = System::Drawing::Color::White;
			this->PeriodicEventInterval4UpDown->Location = System::Drawing::Point(136, 4);
			this->PeriodicEventInterval4UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->PeriodicEventInterval4UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PeriodicEventInterval4UpDown->Name = L"PeriodicEventInterval4UpDown";
			this->PeriodicEventInterval4UpDown->Size = System::Drawing::Size(104, 20);
			this->PeriodicEventInterval4UpDown->TabIndex = 20;
			this->PeriodicEventInterval4UpDown->Tag = L"3";
			this->PeriodicEventInterval4UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->PeriodicEventInterval4UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			// 
			// tableLayoutPanel83
			// 
			this->tableLayoutPanel83->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel83->ColumnCount = 3;
			this->tableLayoutPanel83->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				132)));
			this->tableLayoutPanel83->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				112)));
			this->tableLayoutPanel83->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->tableLayoutPanel83->Controls->Add(this->label110, 0, 0);
			this->tableLayoutPanel83->Controls->Add(this->label111, 2, 0);
			this->tableLayoutPanel83->Controls->Add(this->PeriodicEventInterval5UpDown, 1, 0);
			this->tableLayoutPanel83->Location = System::Drawing::Point(371, 168);
			this->tableLayoutPanel83->Name = L"tableLayoutPanel83";
			this->tableLayoutPanel83->RowCount = 1;
			this->tableLayoutPanel83->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel83->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				28)));
			this->tableLayoutPanel83->Size = System::Drawing::Size(291, 28);
			this->tableLayoutPanel83->TabIndex = 105;
			// 
			// label110
			// 
			this->label110->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label110->AutoSize = true;
			this->label110->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label110->ForeColor = System::Drawing::Color::White;
			this->label110->Location = System::Drawing::Point(5, 6);
			this->label110->Name = L"label110";
			this->label110->Size = System::Drawing::Size(122, 16);
			this->label110->TabIndex = 101;
			this->label110->Text = L"Event 5 Interval:";
			this->label110->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label111
			// 
			this->label111->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label111->AutoSize = true;
			this->label111->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label111->ForeColor = System::Drawing::Color::White;
			this->label111->Location = System::Drawing::Point(252, 6);
			this->label111->Name = L"label111";
			this->label111->Size = System::Drawing::Size(33, 16);
			this->label111->TabIndex = 101;
			this->label111->Text = L"Sec";
			this->label111->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PeriodicEventInterval5UpDown
			// 
			this->PeriodicEventInterval5UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEventInterval5UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->PeriodicEventInterval5UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->PeriodicEventInterval5UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->PeriodicEventInterval5UpDown->ForeColor = System::Drawing::Color::White;
			this->PeriodicEventInterval5UpDown->Location = System::Drawing::Point(136, 4);
			this->PeriodicEventInterval5UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->PeriodicEventInterval5UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PeriodicEventInterval5UpDown->Name = L"PeriodicEventInterval5UpDown";
			this->PeriodicEventInterval5UpDown->Size = System::Drawing::Size(104, 20);
			this->PeriodicEventInterval5UpDown->TabIndex = 20;
			this->PeriodicEventInterval5UpDown->Tag = L"4";
			this->PeriodicEventInterval5UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->PeriodicEventInterval5UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			// 
			// label112
			// 
			this->label112->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label112->AutoSize = true;
			this->label112->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label112->ForeColor = System::Drawing::Color::White;
			this->label112->Location = System::Drawing::Point(874, 6);
			this->label112->Name = L"label112";
			this->label112->Size = System::Drawing::Size(104, 16);
			this->label112->TabIndex = 106;
			this->label112->Text = L"Enable Event:";
			this->label112->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PeriodicEvent1EnableCheckBox
			// 
			this->PeriodicEvent1EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent1EnableCheckBox->AutoSize = true;
			this->PeriodicEvent1EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent1EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent1EnableCheckBox->Location = System::Drawing::Point(877, 36);
			this->PeriodicEvent1EnableCheckBox->Name = L"PeriodicEvent1EnableCheckBox";
			this->PeriodicEvent1EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent1EnableCheckBox->Size = System::Drawing::Size(98, 19);
			this->PeriodicEvent1EnableCheckBox->TabIndex = 114;
			this->PeriodicEvent1EnableCheckBox->Tag = L"0";
			this->PeriodicEvent1EnableCheckBox->Text = L"Enable Event";
			this->PeriodicEvent1EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent1EnableCheckBox->UseVisualStyleBackColor = true;
			this->PeriodicEvent1EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::PeriodicEventnEnableCheckBox_CheckedChanged);
			// 
			// PeriodicEvent2EnableCheckBox
			// 
			this->PeriodicEvent2EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent2EnableCheckBox->AutoSize = true;
			this->PeriodicEvent2EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent2EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent2EnableCheckBox->Location = System::Drawing::Point(877, 70);
			this->PeriodicEvent2EnableCheckBox->Name = L"PeriodicEvent2EnableCheckBox";
			this->PeriodicEvent2EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent2EnableCheckBox->Size = System::Drawing::Size(98, 19);
			this->PeriodicEvent2EnableCheckBox->TabIndex = 115;
			this->PeriodicEvent2EnableCheckBox->Tag = L"1";
			this->PeriodicEvent2EnableCheckBox->Text = L"Enable Event";
			this->PeriodicEvent2EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent2EnableCheckBox->UseVisualStyleBackColor = true;
			this->PeriodicEvent2EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::PeriodicEventnEnableCheckBox_CheckedChanged);
			// 
			// PeriodicEvent3EnableCheckBox
			// 
			this->PeriodicEvent3EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent3EnableCheckBox->AutoSize = true;
			this->PeriodicEvent3EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent3EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent3EnableCheckBox->Location = System::Drawing::Point(877, 104);
			this->PeriodicEvent3EnableCheckBox->Name = L"PeriodicEvent3EnableCheckBox";
			this->PeriodicEvent3EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent3EnableCheckBox->Size = System::Drawing::Size(98, 19);
			this->PeriodicEvent3EnableCheckBox->TabIndex = 116;
			this->PeriodicEvent3EnableCheckBox->Tag = L"2";
			this->PeriodicEvent3EnableCheckBox->Text = L"Enable Event";
			this->PeriodicEvent3EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent3EnableCheckBox->UseVisualStyleBackColor = true;
			this->PeriodicEvent3EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::PeriodicEventnEnableCheckBox_CheckedChanged);
			// 
			// PeriodicEvent4EnableCheckBox
			// 
			this->PeriodicEvent4EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent4EnableCheckBox->AutoSize = true;
			this->PeriodicEvent4EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent4EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent4EnableCheckBox->Location = System::Drawing::Point(877, 138);
			this->PeriodicEvent4EnableCheckBox->Name = L"PeriodicEvent4EnableCheckBox";
			this->PeriodicEvent4EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent4EnableCheckBox->Size = System::Drawing::Size(98, 19);
			this->PeriodicEvent4EnableCheckBox->TabIndex = 117;
			this->PeriodicEvent4EnableCheckBox->Tag = L"3";
			this->PeriodicEvent4EnableCheckBox->Text = L"Enable Event";
			this->PeriodicEvent4EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent4EnableCheckBox->UseVisualStyleBackColor = true;
			this->PeriodicEvent4EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::PeriodicEventnEnableCheckBox_CheckedChanged);
			// 
			// PeriodicEvent5EnableCheckBox
			// 
			this->PeriodicEvent5EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent5EnableCheckBox->AutoSize = true;
			this->PeriodicEvent5EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent5EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent5EnableCheckBox->Location = System::Drawing::Point(877, 172);
			this->PeriodicEvent5EnableCheckBox->Name = L"PeriodicEvent5EnableCheckBox";
			this->PeriodicEvent5EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent5EnableCheckBox->Size = System::Drawing::Size(98, 19);
			this->PeriodicEvent5EnableCheckBox->TabIndex = 118;
			this->PeriodicEvent5EnableCheckBox->Tag = L"4";
			this->PeriodicEvent5EnableCheckBox->Text = L"Enable Event";
			this->PeriodicEvent5EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent5EnableCheckBox->UseVisualStyleBackColor = true;
			this->PeriodicEvent5EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::PeriodicEventnEnableCheckBox_CheckedChanged);
			// 
			// label113
			// 
			this->label113->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label113->AutoSize = true;
			this->label113->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label113->ForeColor = System::Drawing::Color::White;
			this->label113->Location = System::Drawing::Point(706, 6);
			this->label113->Name = L"label113";
			this->label113->Size = System::Drawing::Size(121, 16);
			this->label113->TabIndex = 119;
			this->label113->Text = L"Disabling Event:";
			this->label113->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PeriodicEvent1DisableCheckBox
			// 
			this->PeriodicEvent1DisableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent1DisableCheckBox->AutoSize = true;
			this->PeriodicEvent1DisableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent1DisableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent1DisableCheckBox->Location = System::Drawing::Point(671, 36);
			this->PeriodicEvent1DisableCheckBox->Name = L"PeriodicEvent1DisableCheckBox";
			this->PeriodicEvent1DisableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent1DisableCheckBox->Size = System::Drawing::Size(192, 19);
			this->PeriodicEvent1DisableCheckBox->TabIndex = 120;
			this->PeriodicEvent1DisableCheckBox->Tag = L"0";
			this->PeriodicEvent1DisableCheckBox->Text = L"Disable Event On First Trigger";
			this->PeriodicEvent1DisableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent1DisableCheckBox->UseVisualStyleBackColor = true;
			// 
			// PeriodicEvent2DisableCheckBox
			// 
			this->PeriodicEvent2DisableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent2DisableCheckBox->AutoSize = true;
			this->PeriodicEvent2DisableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent2DisableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent2DisableCheckBox->Location = System::Drawing::Point(671, 70);
			this->PeriodicEvent2DisableCheckBox->Name = L"PeriodicEvent2DisableCheckBox";
			this->PeriodicEvent2DisableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent2DisableCheckBox->Size = System::Drawing::Size(192, 19);
			this->PeriodicEvent2DisableCheckBox->TabIndex = 121;
			this->PeriodicEvent2DisableCheckBox->Tag = L"1";
			this->PeriodicEvent2DisableCheckBox->Text = L"Disable Event On First Trigger";
			this->PeriodicEvent2DisableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent2DisableCheckBox->UseVisualStyleBackColor = true;
			// 
			// PeriodicEvent3DisableCheckBox
			// 
			this->PeriodicEvent3DisableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent3DisableCheckBox->AutoSize = true;
			this->PeriodicEvent3DisableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent3DisableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent3DisableCheckBox->Location = System::Drawing::Point(671, 104);
			this->PeriodicEvent3DisableCheckBox->Name = L"PeriodicEvent3DisableCheckBox";
			this->PeriodicEvent3DisableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent3DisableCheckBox->Size = System::Drawing::Size(192, 19);
			this->PeriodicEvent3DisableCheckBox->TabIndex = 122;
			this->PeriodicEvent3DisableCheckBox->Tag = L"2";
			this->PeriodicEvent3DisableCheckBox->Text = L"Disable Event On First Trigger";
			this->PeriodicEvent3DisableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent3DisableCheckBox->UseVisualStyleBackColor = true;
			// 
			// PeriodicEvent4DisableCheckBox
			// 
			this->PeriodicEvent4DisableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent4DisableCheckBox->AutoSize = true;
			this->PeriodicEvent4DisableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent4DisableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent4DisableCheckBox->Location = System::Drawing::Point(671, 138);
			this->PeriodicEvent4DisableCheckBox->Name = L"PeriodicEvent4DisableCheckBox";
			this->PeriodicEvent4DisableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent4DisableCheckBox->Size = System::Drawing::Size(192, 19);
			this->PeriodicEvent4DisableCheckBox->TabIndex = 123;
			this->PeriodicEvent4DisableCheckBox->Tag = L"3";
			this->PeriodicEvent4DisableCheckBox->Text = L"Disable Event On First Trigger";
			this->PeriodicEvent4DisableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent4DisableCheckBox->UseVisualStyleBackColor = true;
			// 
			// PeriodicEvent5DisableCheckBox
			// 
			this->PeriodicEvent5DisableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->PeriodicEvent5DisableCheckBox->AutoSize = true;
			this->PeriodicEvent5DisableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->PeriodicEvent5DisableCheckBox->ForeColor = System::Drawing::Color::White;
			this->PeriodicEvent5DisableCheckBox->Location = System::Drawing::Point(671, 172);
			this->PeriodicEvent5DisableCheckBox->Name = L"PeriodicEvent5DisableCheckBox";
			this->PeriodicEvent5DisableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PeriodicEvent5DisableCheckBox->Size = System::Drawing::Size(192, 19);
			this->PeriodicEvent5DisableCheckBox->TabIndex = 124;
			this->PeriodicEvent5DisableCheckBox->Tag = L"4";
			this->PeriodicEvent5DisableCheckBox->Text = L"Disable Event On First Trigger";
			this->PeriodicEvent5DisableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->PeriodicEvent5DisableCheckBox->UseVisualStyleBackColor = true;
			// 
			// PeriodicTriggerConfigMenuButton
			// 
			this->PeriodicTriggerConfigMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->PeriodicTriggerConfigMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->PeriodicTriggerConfigMenuButton->Enabled = false;
			this->PeriodicTriggerConfigMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->PeriodicTriggerConfigMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->PeriodicTriggerConfigMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->PeriodicTriggerConfigMenuButton->ForeColor = System::Drawing::Color::White;
			this->PeriodicTriggerConfigMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PeriodicTriggerConfigMenuButton.Image")));
			this->PeriodicTriggerConfigMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->PeriodicTriggerConfigMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->PeriodicTriggerConfigMenuButton->Location = System::Drawing::Point(10, 3182);
			this->PeriodicTriggerConfigMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->PeriodicTriggerConfigMenuButton->Name = L"PeriodicTriggerConfigMenuButton";
			this->PeriodicTriggerConfigMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->PeriodicTriggerConfigMenuButton->Size = System::Drawing::Size(1370, 54);
			this->PeriodicTriggerConfigMenuButton->TabIndex = 52;
			this->PeriodicTriggerConfigMenuButton->Text = L"   General And Periodic Trigger Event Configuration:";
			this->PeriodicTriggerConfigMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->PeriodicTriggerConfigMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->PeriodicTriggerConfigMenuButton->UseVisualStyleBackColor = false;
			this->PeriodicTriggerConfigMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::PeriodicTriggerConfigMenuButton_Click);
			// 
			// TempAlarmsConfigSubMenuPanel
			// 
			this->TempAlarmsConfigSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->TempAlarmsConfigSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->TempAlarmsConfigSubMenuPanel->Controls->Add(this->tableLayoutPanel39);
			this->TempAlarmsConfigSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->TempAlarmsConfigSubMenuPanel->Location = System::Drawing::Point(10, 2786);
			this->TempAlarmsConfigSubMenuPanel->Name = L"TempAlarmsConfigSubMenuPanel";
			this->TempAlarmsConfigSubMenuPanel->Size = System::Drawing::Size(1370, 396);
			this->TempAlarmsConfigSubMenuPanel->TabIndex = 49;
			this->TempAlarmsConfigSubMenuPanel->Visible = false;
			// 
			// tableLayoutPanel39
			// 
			this->tableLayoutPanel39->ColumnCount = 2;
			this->tableLayoutPanel39->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				1348)));
			this->tableLayoutPanel39->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel39->Controls->Add(this->tableLayoutPanel40, 0, 1);
			this->tableLayoutPanel39->Controls->Add(this->tableLayoutPanel57, 0, 0);
			this->tableLayoutPanel39->Controls->Add(this->tableLayoutPanel71, 0, 2);
			this->tableLayoutPanel39->Controls->Add(this->label90, 0, 3);
			this->tableLayoutPanel39->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel39->Name = L"tableLayoutPanel39";
			this->tableLayoutPanel39->RowCount = 4;
			this->tableLayoutPanel39->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 26.19048F)));
			this->tableLayoutPanel39->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 73.80952F)));
			this->tableLayoutPanel39->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				51)));
			this->tableLayoutPanel39->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				28)));
			this->tableLayoutPanel39->Size = System::Drawing::Size(1350, 382);
			this->tableLayoutPanel39->TabIndex = 0;
			// 
			// tableLayoutPanel40
			// 
			this->tableLayoutPanel40->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel40->AutoScroll = true;
			this->tableLayoutPanel40->ColumnCount = 7;
			this->tableLayoutPanel40->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				118)));
			this->tableLayoutPanel40->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				233)));
			this->tableLayoutPanel40->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				202)));
			this->tableLayoutPanel40->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				220)));
			this->tableLayoutPanel40->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				220)));
			this->tableLayoutPanel40->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				202)));
			this->tableLayoutPanel40->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				134)));
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel55, 4, 5);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel54, 4, 4);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel53, 4, 3);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel52, 4, 2);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel51, 4, 1);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel41, 3, 1);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm1AlarmTypeComboBox, 2, 1);
			this->tableLayoutPanel40->Controls->Add(this->label66, 4, 0);
			this->tableLayoutPanel40->Controls->Add(this->label65, 3, 0);
			this->tableLayoutPanel40->Controls->Add(this->label64, 2, 0);
			this->tableLayoutPanel40->Controls->Add(this->label52, 0, 0);
			this->tableLayoutPanel40->Controls->Add(this->label53, 0, 1);
			this->tableLayoutPanel40->Controls->Add(this->label54, 0, 2);
			this->tableLayoutPanel40->Controls->Add(this->label55, 0, 3);
			this->tableLayoutPanel40->Controls->Add(this->label56, 0, 4);
			this->tableLayoutPanel40->Controls->Add(this->label57, 0, 5);
			this->tableLayoutPanel40->Controls->Add(this->label63, 1, 0);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm1DataSourceComboBox, 1, 1);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm2DataSourceComboBox, 1, 2);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm3DataSourceComboBox, 1, 3);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm4DataSourceComboBox, 1, 4);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm5DataSourceComboBox, 1, 5);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm2AlarmTypeComboBox, 2, 2);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm3AlarmTypeComboBox, 2, 3);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm4AlarmTypeComboBox, 2, 4);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm5AlarmTypeComboBox, 2, 5);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel45, 3, 5);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel42, 3, 2);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel43, 3, 3);
			this->tableLayoutPanel40->Controls->Add(this->tableLayoutPanel44, 3, 4);
			this->tableLayoutPanel40->Controls->Add(this->label87, 6, 0);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm1EnableCheckBox, 6, 1);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm2EnableCheckBox, 6, 2);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm3EnableCheckBox, 6, 3);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm4EnableCheckBox, 6, 4);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm5EnableCheckBox, 6, 5);
			this->tableLayoutPanel40->Controls->Add(this->label88, 5, 0);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm1TriggerActionComboBox, 5, 1);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm2TriggerActionComboBox, 5, 2);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm3TriggerActionComboBox, 5, 3);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm4TriggerActionComboBox, 5, 4);
			this->tableLayoutPanel40->Controls->Add(this->TempAlarm5TriggerActionComboBox, 5, 5);
			this->tableLayoutPanel40->Location = System::Drawing::Point(9, 85);
			this->tableLayoutPanel40->Name = L"tableLayoutPanel40";
			this->tableLayoutPanel40->RowCount = 6;
			this->tableLayoutPanel40->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12)));
			this->tableLayoutPanel40->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 17.6F)));
			this->tableLayoutPanel40->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 17.6F)));
			this->tableLayoutPanel40->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 17.6F)));
			this->tableLayoutPanel40->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 17.6F)));
			this->tableLayoutPanel40->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 17.6F)));
			this->tableLayoutPanel40->Size = System::Drawing::Size(1329, 211);
			this->tableLayoutPanel40->TabIndex = 0;
			// 
			// tableLayoutPanel55
			// 
			this->tableLayoutPanel55->ColumnCount = 2;
			this->tableLayoutPanel55->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel55->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel55->Controls->Add(this->label76, 0, 0);
			this->tableLayoutPanel55->Controls->Add(this->TempAlarm5HighTempThresUpDown, 1, 0);
			this->tableLayoutPanel55->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel55->Location = System::Drawing::Point(776, 176);
			this->tableLayoutPanel55->Name = L"tableLayoutPanel55";
			this->tableLayoutPanel55->RowCount = 1;
			this->tableLayoutPanel55->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel55->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				32)));
			this->tableLayoutPanel55->Size = System::Drawing::Size(214, 32);
			this->tableLayoutPanel55->TabIndex = 104;
			// 
			// label76
			// 
			this->label76->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label76->AutoSize = true;
			this->label76->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label76->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label76->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label76->Location = System::Drawing::Point(8, 8);
			this->label76->Name = L"label76";
			this->label76->Size = System::Drawing::Size(69, 15);
			this->label76->TabIndex = 28;
			this->label76->Text = L"High Temp:";
			this->label76->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm5HighTempThresUpDown
			// 
			this->TempAlarm5HighTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm5HighTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm5HighTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm5HighTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm5HighTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm5HighTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm5HighTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm5HighTempThresUpDown->Location = System::Drawing::Point(99, 6);
			this->TempAlarm5HighTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm5HighTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm5HighTempThresUpDown->Name = L"TempAlarm5HighTempThresUpDown";
			this->TempAlarm5HighTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm5HighTempThresUpDown->TabIndex = 20;
			this->TempAlarm5HighTempThresUpDown->Tag = L"4";
			this->TempAlarm5HighTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm5HighTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 60, 0, 0, 0 });
			this->TempAlarm5HighTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1HighTempThresUpDown_ValueChanged);
			// 
			// tableLayoutPanel54
			// 
			this->tableLayoutPanel54->ColumnCount = 2;
			this->tableLayoutPanel54->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel54->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel54->Controls->Add(this->label74, 0, 0);
			this->tableLayoutPanel54->Controls->Add(this->TempAlarm4HighTempThresUpDown, 1, 0);
			this->tableLayoutPanel54->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel54->Location = System::Drawing::Point(776, 139);
			this->tableLayoutPanel54->Name = L"tableLayoutPanel54";
			this->tableLayoutPanel54->RowCount = 1;
			this->tableLayoutPanel54->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel54->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel54->Size = System::Drawing::Size(214, 31);
			this->tableLayoutPanel54->TabIndex = 103;
			// 
			// label74
			// 
			this->label74->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label74->AutoSize = true;
			this->label74->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label74->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label74->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label74->Location = System::Drawing::Point(8, 8);
			this->label74->Name = L"label74";
			this->label74->Size = System::Drawing::Size(69, 15);
			this->label74->TabIndex = 28;
			this->label74->Text = L"High Temp:";
			this->label74->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm4HighTempThresUpDown
			// 
			this->TempAlarm4HighTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm4HighTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm4HighTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm4HighTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm4HighTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm4HighTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm4HighTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm4HighTempThresUpDown->Location = System::Drawing::Point(99, 5);
			this->TempAlarm4HighTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm4HighTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm4HighTempThresUpDown->Name = L"TempAlarm4HighTempThresUpDown";
			this->TempAlarm4HighTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm4HighTempThresUpDown->TabIndex = 20;
			this->TempAlarm4HighTempThresUpDown->Tag = L"3";
			this->TempAlarm4HighTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm4HighTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 60, 0, 0, 0 });
			this->TempAlarm4HighTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1HighTempThresUpDown_ValueChanged);
			// 
			// tableLayoutPanel53
			// 
			this->tableLayoutPanel53->ColumnCount = 2;
			this->tableLayoutPanel53->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel53->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel53->Controls->Add(this->label73, 0, 0);
			this->tableLayoutPanel53->Controls->Add(this->TempAlarm3HighTempThresUpDown, 1, 0);
			this->tableLayoutPanel53->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel53->Location = System::Drawing::Point(776, 102);
			this->tableLayoutPanel53->Name = L"tableLayoutPanel53";
			this->tableLayoutPanel53->RowCount = 1;
			this->tableLayoutPanel53->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel53->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel53->Size = System::Drawing::Size(214, 31);
			this->tableLayoutPanel53->TabIndex = 102;
			// 
			// label73
			// 
			this->label73->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label73->AutoSize = true;
			this->label73->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label73->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label73->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label73->Location = System::Drawing::Point(8, 8);
			this->label73->Name = L"label73";
			this->label73->Size = System::Drawing::Size(69, 15);
			this->label73->TabIndex = 28;
			this->label73->Text = L"High Temp:";
			this->label73->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm3HighTempThresUpDown
			// 
			this->TempAlarm3HighTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm3HighTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm3HighTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm3HighTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm3HighTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm3HighTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm3HighTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm3HighTempThresUpDown->Location = System::Drawing::Point(99, 5);
			this->TempAlarm3HighTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm3HighTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm3HighTempThresUpDown->Name = L"TempAlarm3HighTempThresUpDown";
			this->TempAlarm3HighTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm3HighTempThresUpDown->TabIndex = 20;
			this->TempAlarm3HighTempThresUpDown->Tag = L"2";
			this->TempAlarm3HighTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm3HighTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 60, 0, 0, 0 });
			this->TempAlarm3HighTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1HighTempThresUpDown_ValueChanged);
			// 
			// tableLayoutPanel52
			// 
			this->tableLayoutPanel52->ColumnCount = 2;
			this->tableLayoutPanel52->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel52->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel52->Controls->Add(this->label72, 0, 0);
			this->tableLayoutPanel52->Controls->Add(this->TempAlarm2HighTempThresUpDown, 1, 0);
			this->tableLayoutPanel52->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel52->Location = System::Drawing::Point(776, 65);
			this->tableLayoutPanel52->Name = L"tableLayoutPanel52";
			this->tableLayoutPanel52->RowCount = 1;
			this->tableLayoutPanel52->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel52->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel52->Size = System::Drawing::Size(214, 31);
			this->tableLayoutPanel52->TabIndex = 101;
			// 
			// label72
			// 
			this->label72->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label72->AutoSize = true;
			this->label72->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label72->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label72->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label72->Location = System::Drawing::Point(8, 8);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(69, 15);
			this->label72->TabIndex = 28;
			this->label72->Text = L"High Temp:";
			this->label72->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm2HighTempThresUpDown
			// 
			this->TempAlarm2HighTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm2HighTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm2HighTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm2HighTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm2HighTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm2HighTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm2HighTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm2HighTempThresUpDown->Location = System::Drawing::Point(99, 5);
			this->TempAlarm2HighTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm2HighTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm2HighTempThresUpDown->Name = L"TempAlarm2HighTempThresUpDown";
			this->TempAlarm2HighTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm2HighTempThresUpDown->TabIndex = 20;
			this->TempAlarm2HighTempThresUpDown->Tag = L"1";
			this->TempAlarm2HighTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm2HighTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 60, 0, 0, 0 });
			this->TempAlarm2HighTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1HighTempThresUpDown_ValueChanged);
			// 
			// tableLayoutPanel51
			// 
			this->tableLayoutPanel51->ColumnCount = 2;
			this->tableLayoutPanel51->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel51->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel51->Controls->Add(this->label71, 0, 0);
			this->tableLayoutPanel51->Controls->Add(this->TempAlarm1HighTempThresUpDown, 1, 0);
			this->tableLayoutPanel51->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel51->Location = System::Drawing::Point(776, 28);
			this->tableLayoutPanel51->Name = L"tableLayoutPanel51";
			this->tableLayoutPanel51->RowCount = 1;
			this->tableLayoutPanel51->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel51->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel51->Size = System::Drawing::Size(214, 31);
			this->tableLayoutPanel51->TabIndex = 100;
			// 
			// label71
			// 
			this->label71->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label71->AutoSize = true;
			this->label71->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label71->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label71->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label71->Location = System::Drawing::Point(8, 8);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(69, 15);
			this->label71->TabIndex = 28;
			this->label71->Text = L"High Temp:";
			this->label71->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm1HighTempThresUpDown
			// 
			this->TempAlarm1HighTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm1HighTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm1HighTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm1HighTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm1HighTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm1HighTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm1HighTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm1HighTempThresUpDown->Location = System::Drawing::Point(99, 5);
			this->TempAlarm1HighTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm1HighTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm1HighTempThresUpDown->Name = L"TempAlarm1HighTempThresUpDown";
			this->TempAlarm1HighTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm1HighTempThresUpDown->TabIndex = 20;
			this->TempAlarm1HighTempThresUpDown->Tag = L"0";
			this->TempAlarm1HighTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm1HighTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 60, 0, 0, 0 });
			this->TempAlarm1HighTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1HighTempThresUpDown_ValueChanged);
			// 
			// tableLayoutPanel41
			// 
			this->tableLayoutPanel41->ColumnCount = 2;
			this->tableLayoutPanel41->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel41->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel41->Controls->Add(this->label67, 0, 0);
			this->tableLayoutPanel41->Controls->Add(this->TempAlarm1LowTempThresUpDown, 1, 0);
			this->tableLayoutPanel41->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel41->Location = System::Drawing::Point(556, 28);
			this->tableLayoutPanel41->Name = L"tableLayoutPanel41";
			this->tableLayoutPanel41->RowCount = 1;
			this->tableLayoutPanel41->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel41->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel41->Size = System::Drawing::Size(214, 31);
			this->tableLayoutPanel41->TabIndex = 96;
			// 
			// label67
			// 
			this->label67->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label67->AutoSize = true;
			this->label67->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label67->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->label67->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label67->Location = System::Drawing::Point(8, 8);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(68, 15);
			this->label67->TabIndex = 28;
			this->label67->Text = L"Low Temp:";
			this->label67->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm1LowTempThresUpDown
			// 
			this->TempAlarm1LowTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm1LowTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm1LowTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm1LowTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm1LowTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm1LowTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm1LowTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm1LowTempThresUpDown->Location = System::Drawing::Point(99, 5);
			this->TempAlarm1LowTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm1LowTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm1LowTempThresUpDown->Name = L"TempAlarm1LowTempThresUpDown";
			this->TempAlarm1LowTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm1LowTempThresUpDown->TabIndex = 20;
			this->TempAlarm1LowTempThresUpDown->Tag = L"0";
			this->TempAlarm1LowTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm1LowTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->TempAlarm1LowTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1LowTempThresUpDown_ValueChanged);
			// 
			// TempAlarm1AlarmTypeComboBox
			// 
			this->TempAlarm1AlarmTypeComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm1AlarmTypeComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm1AlarmTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm1AlarmTypeComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm1AlarmTypeComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm1AlarmTypeComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm1AlarmTypeComboBox->IntegralHeight = false;
			this->TempAlarm1AlarmTypeComboBox->Location = System::Drawing::Point(362, 31);
			this->TempAlarm1AlarmTypeComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm1AlarmTypeComboBox->MaxDropDownItems = 50;
			this->TempAlarm1AlarmTypeComboBox->Name = L"TempAlarm1AlarmTypeComboBox";
			this->TempAlarm1AlarmTypeComboBox->Size = System::Drawing::Size(180, 24);
			this->TempAlarm1AlarmTypeComboBox->TabIndex = 76;
			this->TempAlarm1AlarmTypeComboBox->TabStop = false;
			this->TempAlarm1AlarmTypeComboBox->Tag = L"0";
			this->TempAlarm1AlarmTypeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1AlarmTypeComboBox_SelectedIndexChanged);
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label66->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label66->ForeColor = System::Drawing::Color::White;
			this->label66->Location = System::Drawing::Point(776, 0);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(214, 25);
			this->label66->TabIndex = 65;
			this->label66->Text = L"High Temperature Threshold:";
			this->label66->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label65->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label65->ForeColor = System::Drawing::Color::White;
			this->label65->Location = System::Drawing::Point(556, 0);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(214, 25);
			this->label65->TabIndex = 64;
			this->label65->Text = L"Low Temperature Threshold:";
			this->label65->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label64
			// 
			this->label64->AutoSize = true;
			this->label64->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label64->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label64->ForeColor = System::Drawing::Color::White;
			this->label64->Location = System::Drawing::Point(354, 0);
			this->label64->Name = L"label64";
			this->label64->Size = System::Drawing::Size(196, 25);
			this->label64->TabIndex = 63;
			this->label64->Text = L"Alarm Type:";
			this->label64->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label52->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label52->ForeColor = System::Drawing::Color::White;
			this->label52->Location = System::Drawing::Point(3, 0);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(112, 25);
			this->label52->TabIndex = 51;
			this->label52->Text = L"Alarm:";
			this->label52->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label53->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label53->ForeColor = System::Drawing::Color::White;
			this->label53->Location = System::Drawing::Point(3, 25);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(112, 37);
			this->label53->TabIndex = 52;
			this->label53->Text = L"Temp Alarm 1:";
			this->label53->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label54->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label54->ForeColor = System::Drawing::Color::White;
			this->label54->Location = System::Drawing::Point(3, 62);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(112, 37);
			this->label54->TabIndex = 53;
			this->label54->Text = L"Temp Alarm 2:";
			this->label54->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label55->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label55->ForeColor = System::Drawing::Color::White;
			this->label55->Location = System::Drawing::Point(3, 99);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(112, 37);
			this->label55->TabIndex = 54;
			this->label55->Text = L"Temp Alarm 3:";
			this->label55->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label56->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label56->ForeColor = System::Drawing::Color::White;
			this->label56->Location = System::Drawing::Point(3, 136);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(112, 37);
			this->label56->TabIndex = 55;
			this->label56->Text = L"Temp Alarm 4:";
			this->label56->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label57->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label57->ForeColor = System::Drawing::Color::White;
			this->label57->Location = System::Drawing::Point(3, 173);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(112, 38);
			this->label57->TabIndex = 56;
			this->label57->Text = L"Temp Alarm 5:";
			this->label57->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label63->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label63->ForeColor = System::Drawing::Color::White;
			this->label63->Location = System::Drawing::Point(121, 0);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(227, 25);
			this->label63->TabIndex = 62;
			this->label63->Text = L"Alarm Data Source:";
			this->label63->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm1DataSourceComboBox
			// 
			this->TempAlarm1DataSourceComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm1DataSourceComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm1DataSourceComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm1DataSourceComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm1DataSourceComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm1DataSourceComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm1DataSourceComboBox->IntegralHeight = false;
			this->TempAlarm1DataSourceComboBox->Location = System::Drawing::Point(129, 31);
			this->TempAlarm1DataSourceComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm1DataSourceComboBox->MaxDropDownItems = 50;
			this->TempAlarm1DataSourceComboBox->Name = L"TempAlarm1DataSourceComboBox";
			this->TempAlarm1DataSourceComboBox->Size = System::Drawing::Size(211, 24);
			this->TempAlarm1DataSourceComboBox->TabIndex = 66;
			this->TempAlarm1DataSourceComboBox->TabStop = false;
			this->TempAlarm1DataSourceComboBox->Tag = L"0";
			this->TempAlarm1DataSourceComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1DataSourceComboBox_SelectedIndexChanged);
			// 
			// TempAlarm2DataSourceComboBox
			// 
			this->TempAlarm2DataSourceComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm2DataSourceComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm2DataSourceComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm2DataSourceComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm2DataSourceComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm2DataSourceComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm2DataSourceComboBox->IntegralHeight = false;
			this->TempAlarm2DataSourceComboBox->Location = System::Drawing::Point(129, 68);
			this->TempAlarm2DataSourceComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm2DataSourceComboBox->MaxDropDownItems = 50;
			this->TempAlarm2DataSourceComboBox->Name = L"TempAlarm2DataSourceComboBox";
			this->TempAlarm2DataSourceComboBox->Size = System::Drawing::Size(211, 24);
			this->TempAlarm2DataSourceComboBox->TabIndex = 67;
			this->TempAlarm2DataSourceComboBox->TabStop = false;
			this->TempAlarm2DataSourceComboBox->Tag = L"1";
			this->TempAlarm2DataSourceComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1DataSourceComboBox_SelectedIndexChanged);
			// 
			// TempAlarm3DataSourceComboBox
			// 
			this->TempAlarm3DataSourceComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm3DataSourceComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm3DataSourceComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm3DataSourceComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm3DataSourceComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm3DataSourceComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm3DataSourceComboBox->IntegralHeight = false;
			this->TempAlarm3DataSourceComboBox->Location = System::Drawing::Point(129, 105);
			this->TempAlarm3DataSourceComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm3DataSourceComboBox->MaxDropDownItems = 50;
			this->TempAlarm3DataSourceComboBox->Name = L"TempAlarm3DataSourceComboBox";
			this->TempAlarm3DataSourceComboBox->Size = System::Drawing::Size(211, 24);
			this->TempAlarm3DataSourceComboBox->TabIndex = 68;
			this->TempAlarm3DataSourceComboBox->TabStop = false;
			this->TempAlarm3DataSourceComboBox->Tag = L"2";
			this->TempAlarm3DataSourceComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1DataSourceComboBox_SelectedIndexChanged);
			// 
			// TempAlarm4DataSourceComboBox
			// 
			this->TempAlarm4DataSourceComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm4DataSourceComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm4DataSourceComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm4DataSourceComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm4DataSourceComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm4DataSourceComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm4DataSourceComboBox->IntegralHeight = false;
			this->TempAlarm4DataSourceComboBox->Location = System::Drawing::Point(129, 142);
			this->TempAlarm4DataSourceComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm4DataSourceComboBox->MaxDropDownItems = 50;
			this->TempAlarm4DataSourceComboBox->Name = L"TempAlarm4DataSourceComboBox";
			this->TempAlarm4DataSourceComboBox->Size = System::Drawing::Size(211, 24);
			this->TempAlarm4DataSourceComboBox->TabIndex = 69;
			this->TempAlarm4DataSourceComboBox->TabStop = false;
			this->TempAlarm4DataSourceComboBox->Tag = L"3";
			this->TempAlarm4DataSourceComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1DataSourceComboBox_SelectedIndexChanged);
			// 
			// TempAlarm5DataSourceComboBox
			// 
			this->TempAlarm5DataSourceComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm5DataSourceComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm5DataSourceComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm5DataSourceComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm5DataSourceComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm5DataSourceComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm5DataSourceComboBox->IntegralHeight = false;
			this->TempAlarm5DataSourceComboBox->Location = System::Drawing::Point(129, 180);
			this->TempAlarm5DataSourceComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm5DataSourceComboBox->MaxDropDownItems = 50;
			this->TempAlarm5DataSourceComboBox->Name = L"TempAlarm5DataSourceComboBox";
			this->TempAlarm5DataSourceComboBox->Size = System::Drawing::Size(211, 24);
			this->TempAlarm5DataSourceComboBox->TabIndex = 70;
			this->TempAlarm5DataSourceComboBox->TabStop = false;
			this->TempAlarm5DataSourceComboBox->Tag = L"4";
			this->TempAlarm5DataSourceComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1DataSourceComboBox_SelectedIndexChanged);
			// 
			// TempAlarm2AlarmTypeComboBox
			// 
			this->TempAlarm2AlarmTypeComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm2AlarmTypeComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm2AlarmTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm2AlarmTypeComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm2AlarmTypeComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm2AlarmTypeComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm2AlarmTypeComboBox->IntegralHeight = false;
			this->TempAlarm2AlarmTypeComboBox->Location = System::Drawing::Point(362, 68);
			this->TempAlarm2AlarmTypeComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm2AlarmTypeComboBox->MaxDropDownItems = 50;
			this->TempAlarm2AlarmTypeComboBox->Name = L"TempAlarm2AlarmTypeComboBox";
			this->TempAlarm2AlarmTypeComboBox->Size = System::Drawing::Size(180, 24);
			this->TempAlarm2AlarmTypeComboBox->TabIndex = 77;
			this->TempAlarm2AlarmTypeComboBox->TabStop = false;
			this->TempAlarm2AlarmTypeComboBox->Tag = L"1";
			this->TempAlarm2AlarmTypeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1AlarmTypeComboBox_SelectedIndexChanged);
			// 
			// TempAlarm3AlarmTypeComboBox
			// 
			this->TempAlarm3AlarmTypeComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm3AlarmTypeComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm3AlarmTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm3AlarmTypeComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm3AlarmTypeComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm3AlarmTypeComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm3AlarmTypeComboBox->IntegralHeight = false;
			this->TempAlarm3AlarmTypeComboBox->Location = System::Drawing::Point(362, 105);
			this->TempAlarm3AlarmTypeComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm3AlarmTypeComboBox->MaxDropDownItems = 50;
			this->TempAlarm3AlarmTypeComboBox->Name = L"TempAlarm3AlarmTypeComboBox";
			this->TempAlarm3AlarmTypeComboBox->Size = System::Drawing::Size(180, 24);
			this->TempAlarm3AlarmTypeComboBox->TabIndex = 78;
			this->TempAlarm3AlarmTypeComboBox->TabStop = false;
			this->TempAlarm3AlarmTypeComboBox->Tag = L"2";
			this->TempAlarm3AlarmTypeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1AlarmTypeComboBox_SelectedIndexChanged);
			// 
			// TempAlarm4AlarmTypeComboBox
			// 
			this->TempAlarm4AlarmTypeComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm4AlarmTypeComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm4AlarmTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm4AlarmTypeComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm4AlarmTypeComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm4AlarmTypeComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm4AlarmTypeComboBox->IntegralHeight = false;
			this->TempAlarm4AlarmTypeComboBox->Location = System::Drawing::Point(362, 142);
			this->TempAlarm4AlarmTypeComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm4AlarmTypeComboBox->MaxDropDownItems = 50;
			this->TempAlarm4AlarmTypeComboBox->Name = L"TempAlarm4AlarmTypeComboBox";
			this->TempAlarm4AlarmTypeComboBox->Size = System::Drawing::Size(180, 24);
			this->TempAlarm4AlarmTypeComboBox->TabIndex = 79;
			this->TempAlarm4AlarmTypeComboBox->TabStop = false;
			this->TempAlarm4AlarmTypeComboBox->Tag = L"3";
			this->TempAlarm4AlarmTypeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1AlarmTypeComboBox_SelectedIndexChanged);
			// 
			// TempAlarm5AlarmTypeComboBox
			// 
			this->TempAlarm5AlarmTypeComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm5AlarmTypeComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm5AlarmTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm5AlarmTypeComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm5AlarmTypeComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm5AlarmTypeComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm5AlarmTypeComboBox->IntegralHeight = false;
			this->TempAlarm5AlarmTypeComboBox->Location = System::Drawing::Point(362, 180);
			this->TempAlarm5AlarmTypeComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm5AlarmTypeComboBox->MaxDropDownItems = 50;
			this->TempAlarm5AlarmTypeComboBox->Name = L"TempAlarm5AlarmTypeComboBox";
			this->TempAlarm5AlarmTypeComboBox->Size = System::Drawing::Size(180, 24);
			this->TempAlarm5AlarmTypeComboBox->TabIndex = 80;
			this->TempAlarm5AlarmTypeComboBox->TabStop = false;
			this->TempAlarm5AlarmTypeComboBox->Tag = L"4";
			this->TempAlarm5AlarmTypeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1AlarmTypeComboBox_SelectedIndexChanged);
			// 
			// tableLayoutPanel45
			// 
			this->tableLayoutPanel45->ColumnCount = 2;
			this->tableLayoutPanel45->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel45->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel45->Controls->Add(this->label75, 0, 0);
			this->tableLayoutPanel45->Controls->Add(this->TempAlarm5LowTempThresUpDown, 1, 0);
			this->tableLayoutPanel45->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel45->Location = System::Drawing::Point(556, 176);
			this->tableLayoutPanel45->Name = L"tableLayoutPanel45";
			this->tableLayoutPanel45->RowCount = 1;
			this->tableLayoutPanel45->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel45->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				32)));
			this->tableLayoutPanel45->Size = System::Drawing::Size(214, 32);
			this->tableLayoutPanel45->TabIndex = 90;
			// 
			// label75
			// 
			this->label75->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label75->AutoSize = true;
			this->label75->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label75->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->label75->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label75->Location = System::Drawing::Point(8, 8);
			this->label75->Name = L"label75";
			this->label75->Size = System::Drawing::Size(68, 15);
			this->label75->TabIndex = 28;
			this->label75->Text = L"Low Temp:";
			this->label75->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm5LowTempThresUpDown
			// 
			this->TempAlarm5LowTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm5LowTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm5LowTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm5LowTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm5LowTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm5LowTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm5LowTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm5LowTempThresUpDown->Location = System::Drawing::Point(99, 6);
			this->TempAlarm5LowTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm5LowTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm5LowTempThresUpDown->Name = L"TempAlarm5LowTempThresUpDown";
			this->TempAlarm5LowTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm5LowTempThresUpDown->TabIndex = 20;
			this->TempAlarm5LowTempThresUpDown->Tag = L"4";
			this->TempAlarm5LowTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm5LowTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->TempAlarm5LowTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1LowTempThresUpDown_ValueChanged);
			// 
			// tableLayoutPanel42
			// 
			this->tableLayoutPanel42->ColumnCount = 2;
			this->tableLayoutPanel42->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel42->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel42->Controls->Add(this->label68, 0, 0);
			this->tableLayoutPanel42->Controls->Add(this->TempAlarm2LowTempThresUpDown, 1, 0);
			this->tableLayoutPanel42->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel42->Location = System::Drawing::Point(556, 65);
			this->tableLayoutPanel42->Name = L"tableLayoutPanel42";
			this->tableLayoutPanel42->RowCount = 1;
			this->tableLayoutPanel42->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel42->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel42->Size = System::Drawing::Size(214, 31);
			this->tableLayoutPanel42->TabIndex = 97;
			// 
			// label68
			// 
			this->label68->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label68->AutoSize = true;
			this->label68->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label68->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->label68->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label68->Location = System::Drawing::Point(8, 8);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(68, 15);
			this->label68->TabIndex = 28;
			this->label68->Text = L"Low Temp:";
			this->label68->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm2LowTempThresUpDown
			// 
			this->TempAlarm2LowTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm2LowTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm2LowTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm2LowTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm2LowTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm2LowTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm2LowTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm2LowTempThresUpDown->Location = System::Drawing::Point(99, 5);
			this->TempAlarm2LowTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm2LowTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm2LowTempThresUpDown->Name = L"TempAlarm2LowTempThresUpDown";
			this->TempAlarm2LowTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm2LowTempThresUpDown->TabIndex = 20;
			this->TempAlarm2LowTempThresUpDown->Tag = L"1";
			this->TempAlarm2LowTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm2LowTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->TempAlarm2LowTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1LowTempThresUpDown_ValueChanged);
			// 
			// tableLayoutPanel43
			// 
			this->tableLayoutPanel43->ColumnCount = 2;
			this->tableLayoutPanel43->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel43->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel43->Controls->Add(this->label69, 0, 0);
			this->tableLayoutPanel43->Controls->Add(this->TempAlarm3LowTempThresUpDown, 1, 0);
			this->tableLayoutPanel43->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel43->Location = System::Drawing::Point(556, 102);
			this->tableLayoutPanel43->Name = L"tableLayoutPanel43";
			this->tableLayoutPanel43->RowCount = 1;
			this->tableLayoutPanel43->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel43->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel43->Size = System::Drawing::Size(214, 31);
			this->tableLayoutPanel43->TabIndex = 98;
			// 
			// label69
			// 
			this->label69->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label69->AutoSize = true;
			this->label69->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label69->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->label69->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label69->Location = System::Drawing::Point(8, 8);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(68, 15);
			this->label69->TabIndex = 28;
			this->label69->Text = L"Low Temp:";
			this->label69->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm3LowTempThresUpDown
			// 
			this->TempAlarm3LowTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm3LowTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm3LowTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm3LowTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm3LowTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm3LowTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm3LowTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm3LowTempThresUpDown->Location = System::Drawing::Point(99, 5);
			this->TempAlarm3LowTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm3LowTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm3LowTempThresUpDown->Name = L"TempAlarm3LowTempThresUpDown";
			this->TempAlarm3LowTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm3LowTempThresUpDown->TabIndex = 20;
			this->TempAlarm3LowTempThresUpDown->Tag = L"2";
			this->TempAlarm3LowTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm3LowTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->TempAlarm3LowTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1LowTempThresUpDown_ValueChanged);
			// 
			// tableLayoutPanel44
			// 
			this->tableLayoutPanel44->ColumnCount = 2;
			this->tableLayoutPanel44->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				85)));
			this->tableLayoutPanel44->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				129)));
			this->tableLayoutPanel44->Controls->Add(this->label70, 0, 0);
			this->tableLayoutPanel44->Controls->Add(this->TempAlarm4LowTempThresUpDown, 1, 0);
			this->tableLayoutPanel44->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel44->Location = System::Drawing::Point(556, 139);
			this->tableLayoutPanel44->Name = L"tableLayoutPanel44";
			this->tableLayoutPanel44->RowCount = 1;
			this->tableLayoutPanel44->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel44->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel44->Size = System::Drawing::Size(214, 31);
			this->tableLayoutPanel44->TabIndex = 99;
			// 
			// label70
			// 
			this->label70->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label70->AutoSize = true;
			this->label70->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label70->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->label70->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label70->Location = System::Drawing::Point(8, 8);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(68, 15);
			this->label70->TabIndex = 28;
			this->label70->Text = L"Low Temp:";
			this->label70->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm4LowTempThresUpDown
			// 
			this->TempAlarm4LowTempThresUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm4LowTempThresUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm4LowTempThresUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempAlarm4LowTempThresUpDown->DecimalPlaces = 2;
			this->TempAlarm4LowTempThresUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm4LowTempThresUpDown->ForeColor = System::Drawing::Color::White;
			this->TempAlarm4LowTempThresUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->TempAlarm4LowTempThresUpDown->Location = System::Drawing::Point(99, 5);
			this->TempAlarm4LowTempThresUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempAlarm4LowTempThresUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->TempAlarm4LowTempThresUpDown->Name = L"TempAlarm4LowTempThresUpDown";
			this->TempAlarm4LowTempThresUpDown->Size = System::Drawing::Size(100, 20);
			this->TempAlarm4LowTempThresUpDown->TabIndex = 20;
			this->TempAlarm4LowTempThresUpDown->Tag = L"3";
			this->TempAlarm4LowTempThresUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TempAlarm4LowTempThresUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->TempAlarm4LowTempThresUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1LowTempThresUpDown_ValueChanged);
			// 
			// label87
			// 
			this->label87->AutoSize = true;
			this->label87->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label87->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label87->ForeColor = System::Drawing::Color::White;
			this->label87->Location = System::Drawing::Point(1198, 0);
			this->label87->Name = L"label87";
			this->label87->Size = System::Drawing::Size(128, 25);
			this->label87->TabIndex = 112;
			this->label87->Text = L"Enable Alarm:";
			this->label87->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm1EnableCheckBox
			// 
			this->TempAlarm1EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm1EnableCheckBox->AutoSize = true;
			this->TempAlarm1EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm1EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm1EnableCheckBox->Location = System::Drawing::Point(1211, 34);
			this->TempAlarm1EnableCheckBox->Name = L"TempAlarm1EnableCheckBox";
			this->TempAlarm1EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TempAlarm1EnableCheckBox->Size = System::Drawing::Size(101, 19);
			this->TempAlarm1EnableCheckBox->TabIndex = 113;
			this->TempAlarm1EnableCheckBox->Tag = L"0";
			this->TempAlarm1EnableCheckBox->Text = L"Enable Alarm";
			this->TempAlarm1EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->TempAlarm1EnableCheckBox->UseVisualStyleBackColor = true;
			this->TempAlarm1EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1EnableCheckBox_CheckedChanged);
			// 
			// TempAlarm2EnableCheckBox
			// 
			this->TempAlarm2EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm2EnableCheckBox->AutoSize = true;
			this->TempAlarm2EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm2EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm2EnableCheckBox->Location = System::Drawing::Point(1211, 71);
			this->TempAlarm2EnableCheckBox->Name = L"TempAlarm2EnableCheckBox";
			this->TempAlarm2EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TempAlarm2EnableCheckBox->Size = System::Drawing::Size(101, 19);
			this->TempAlarm2EnableCheckBox->TabIndex = 117;
			this->TempAlarm2EnableCheckBox->Tag = L"1";
			this->TempAlarm2EnableCheckBox->Text = L"Enable Alarm";
			this->TempAlarm2EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->TempAlarm2EnableCheckBox->UseVisualStyleBackColor = true;
			this->TempAlarm2EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1EnableCheckBox_CheckedChanged);
			// 
			// TempAlarm3EnableCheckBox
			// 
			this->TempAlarm3EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm3EnableCheckBox->AutoSize = true;
			this->TempAlarm3EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm3EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm3EnableCheckBox->Location = System::Drawing::Point(1211, 108);
			this->TempAlarm3EnableCheckBox->Name = L"TempAlarm3EnableCheckBox";
			this->TempAlarm3EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TempAlarm3EnableCheckBox->Size = System::Drawing::Size(101, 19);
			this->TempAlarm3EnableCheckBox->TabIndex = 114;
			this->TempAlarm3EnableCheckBox->Tag = L"2";
			this->TempAlarm3EnableCheckBox->Text = L"Enable Alarm";
			this->TempAlarm3EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->TempAlarm3EnableCheckBox->UseVisualStyleBackColor = true;
			this->TempAlarm3EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1EnableCheckBox_CheckedChanged);
			// 
			// TempAlarm4EnableCheckBox
			// 
			this->TempAlarm4EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm4EnableCheckBox->AutoSize = true;
			this->TempAlarm4EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm4EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm4EnableCheckBox->Location = System::Drawing::Point(1211, 145);
			this->TempAlarm4EnableCheckBox->Name = L"TempAlarm4EnableCheckBox";
			this->TempAlarm4EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TempAlarm4EnableCheckBox->Size = System::Drawing::Size(101, 19);
			this->TempAlarm4EnableCheckBox->TabIndex = 115;
			this->TempAlarm4EnableCheckBox->Tag = L"3";
			this->TempAlarm4EnableCheckBox->Text = L"Enable Alarm";
			this->TempAlarm4EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->TempAlarm4EnableCheckBox->UseVisualStyleBackColor = true;
			this->TempAlarm4EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1EnableCheckBox_CheckedChanged);
			// 
			// TempAlarm5EnableCheckBox
			// 
			this->TempAlarm5EnableCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm5EnableCheckBox->AutoSize = true;
			this->TempAlarm5EnableCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm5EnableCheckBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm5EnableCheckBox->Location = System::Drawing::Point(1211, 182);
			this->TempAlarm5EnableCheckBox->Name = L"TempAlarm5EnableCheckBox";
			this->TempAlarm5EnableCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TempAlarm5EnableCheckBox->Size = System::Drawing::Size(101, 19);
			this->TempAlarm5EnableCheckBox->TabIndex = 116;
			this->TempAlarm5EnableCheckBox->Tag = L"4";
			this->TempAlarm5EnableCheckBox->Text = L"Enable Alarm";
			this->TempAlarm5EnableCheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->TempAlarm5EnableCheckBox->UseVisualStyleBackColor = true;
			this->TempAlarm5EnableCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1EnableCheckBox_CheckedChanged);
			// 
			// label88
			// 
			this->label88->AutoSize = true;
			this->label88->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label88->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label88->ForeColor = System::Drawing::Color::White;
			this->label88->Location = System::Drawing::Point(996, 0);
			this->label88->Name = L"label88";
			this->label88->Size = System::Drawing::Size(196, 25);
			this->label88->TabIndex = 123;
			this->label88->Text = L"Alarm Trigger Events:";
			this->label88->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarm1TriggerActionComboBox
			// 
			this->TempAlarm1TriggerActionComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm1TriggerActionComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm1TriggerActionComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm1TriggerActionComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm1TriggerActionComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm1TriggerActionComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm1TriggerActionComboBox->IntegralHeight = false;
			this->TempAlarm1TriggerActionComboBox->Location = System::Drawing::Point(1004, 31);
			this->TempAlarm1TriggerActionComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm1TriggerActionComboBox->MaxDropDownItems = 50;
			this->TempAlarm1TriggerActionComboBox->Name = L"TempAlarm1TriggerActionComboBox";
			this->TempAlarm1TriggerActionComboBox->Size = System::Drawing::Size(179, 24);
			this->TempAlarm1TriggerActionComboBox->TabIndex = 124;
			this->TempAlarm1TriggerActionComboBox->TabStop = false;
			this->TempAlarm1TriggerActionComboBox->Tag = L"0";
			this->TempAlarm1TriggerActionComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1TriggerActionComboBox_SelectedIndexChanged);
			// 
			// TempAlarm2TriggerActionComboBox
			// 
			this->TempAlarm2TriggerActionComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm2TriggerActionComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm2TriggerActionComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm2TriggerActionComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm2TriggerActionComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm2TriggerActionComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm2TriggerActionComboBox->IntegralHeight = false;
			this->TempAlarm2TriggerActionComboBox->Location = System::Drawing::Point(1004, 68);
			this->TempAlarm2TriggerActionComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm2TriggerActionComboBox->MaxDropDownItems = 50;
			this->TempAlarm2TriggerActionComboBox->Name = L"TempAlarm2TriggerActionComboBox";
			this->TempAlarm2TriggerActionComboBox->Size = System::Drawing::Size(179, 24);
			this->TempAlarm2TriggerActionComboBox->TabIndex = 125;
			this->TempAlarm2TriggerActionComboBox->TabStop = false;
			this->TempAlarm2TriggerActionComboBox->Tag = L"1";
			this->TempAlarm2TriggerActionComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1TriggerActionComboBox_SelectedIndexChanged);
			// 
			// TempAlarm3TriggerActionComboBox
			// 
			this->TempAlarm3TriggerActionComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm3TriggerActionComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm3TriggerActionComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm3TriggerActionComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm3TriggerActionComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm3TriggerActionComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm3TriggerActionComboBox->IntegralHeight = false;
			this->TempAlarm3TriggerActionComboBox->Location = System::Drawing::Point(1004, 105);
			this->TempAlarm3TriggerActionComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm3TriggerActionComboBox->MaxDropDownItems = 50;
			this->TempAlarm3TriggerActionComboBox->Name = L"TempAlarm3TriggerActionComboBox";
			this->TempAlarm3TriggerActionComboBox->Size = System::Drawing::Size(179, 24);
			this->TempAlarm3TriggerActionComboBox->TabIndex = 126;
			this->TempAlarm3TriggerActionComboBox->TabStop = false;
			this->TempAlarm3TriggerActionComboBox->Tag = L"2";
			this->TempAlarm3TriggerActionComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1TriggerActionComboBox_SelectedIndexChanged);
			// 
			// TempAlarm4TriggerActionComboBox
			// 
			this->TempAlarm4TriggerActionComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm4TriggerActionComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm4TriggerActionComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm4TriggerActionComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm4TriggerActionComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm4TriggerActionComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm4TriggerActionComboBox->IntegralHeight = false;
			this->TempAlarm4TriggerActionComboBox->Location = System::Drawing::Point(1004, 142);
			this->TempAlarm4TriggerActionComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm4TriggerActionComboBox->MaxDropDownItems = 50;
			this->TempAlarm4TriggerActionComboBox->Name = L"TempAlarm4TriggerActionComboBox";
			this->TempAlarm4TriggerActionComboBox->Size = System::Drawing::Size(179, 24);
			this->TempAlarm4TriggerActionComboBox->TabIndex = 127;
			this->TempAlarm4TriggerActionComboBox->TabStop = false;
			this->TempAlarm4TriggerActionComboBox->Tag = L"3";
			this->TempAlarm4TriggerActionComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1TriggerActionComboBox_SelectedIndexChanged);
			// 
			// TempAlarm5TriggerActionComboBox
			// 
			this->TempAlarm5TriggerActionComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarm5TriggerActionComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempAlarm5TriggerActionComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TempAlarm5TriggerActionComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarm5TriggerActionComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->TempAlarm5TriggerActionComboBox->ForeColor = System::Drawing::Color::White;
			this->TempAlarm5TriggerActionComboBox->IntegralHeight = false;
			this->TempAlarm5TriggerActionComboBox->Location = System::Drawing::Point(1004, 180);
			this->TempAlarm5TriggerActionComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->TempAlarm5TriggerActionComboBox->MaxDropDownItems = 50;
			this->TempAlarm5TriggerActionComboBox->Name = L"TempAlarm5TriggerActionComboBox";
			this->TempAlarm5TriggerActionComboBox->Size = System::Drawing::Size(179, 24);
			this->TempAlarm5TriggerActionComboBox->TabIndex = 128;
			this->TempAlarm5TriggerActionComboBox->TabStop = false;
			this->TempAlarm5TriggerActionComboBox->Tag = L"4";
			this->TempAlarm5TriggerActionComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarm1TriggerActionComboBox_SelectedIndexChanged);
			// 
			// tableLayoutPanel57
			// 
			this->tableLayoutPanel57->ColumnCount = 3;
			this->tableLayoutPanel57->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				15)));
			this->tableLayoutPanel57->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				70)));
			this->tableLayoutPanel57->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				15)));
			this->tableLayoutPanel57->Controls->Add(this->tableLayoutPanel46, 1, 0);
			this->tableLayoutPanel57->Controls->Add(this->tableLayoutPanel58, 1, 1);
			this->tableLayoutPanel57->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel57->Location = System::Drawing::Point(0, 20);
			this->tableLayoutPanel57->Margin = System::Windows::Forms::Padding(0, 20, 0, 0);
			this->tableLayoutPanel57->Name = L"tableLayoutPanel57";
			this->tableLayoutPanel57->RowCount = 2;
			this->tableLayoutPanel57->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 43.85965F)));
			this->tableLayoutPanel57->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 56.14035F)));
			this->tableLayoutPanel57->Size = System::Drawing::Size(1348, 59);
			this->tableLayoutPanel57->TabIndex = 1;
			// 
			// tableLayoutPanel46
			// 
			this->tableLayoutPanel46->ColumnCount = 5;
			this->tableLayoutPanel46->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28571F)));
			this->tableLayoutPanel46->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28571F)));
			this->tableLayoutPanel46->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28571F)));
			this->tableLayoutPanel46->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28571F)));
			this->tableLayoutPanel46->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28571F)));
			this->tableLayoutPanel46->Controls->Add(this->tableLayoutPanel47, 0, 0);
			this->tableLayoutPanel46->Controls->Add(this->tableLayoutPanel48, 1, 0);
			this->tableLayoutPanel46->Controls->Add(this->tableLayoutPanel49, 2, 0);
			this->tableLayoutPanel46->Controls->Add(this->tableLayoutPanel50, 3, 0);
			this->tableLayoutPanel46->Controls->Add(this->tableLayoutPanel56, 4, 0);
			this->tableLayoutPanel46->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel46->Location = System::Drawing::Point(202, 0);
			this->tableLayoutPanel46->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel46->Name = L"tableLayoutPanel46";
			this->tableLayoutPanel46->RowCount = 1;
			this->tableLayoutPanel46->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel46->Size = System::Drawing::Size(943, 25);
			this->tableLayoutPanel46->TabIndex = 1;
			// 
			// tableLayoutPanel47
			// 
			this->tableLayoutPanel47->ColumnCount = 2;
			this->tableLayoutPanel47->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				110)));
			this->tableLayoutPanel47->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel47->Controls->Add(this->TempAlarm1StatusLabel, 0, 0);
			this->tableLayoutPanel47->Controls->Add(this->label58, 0, 0);
			this->tableLayoutPanel47->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel47->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel47->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel47->Name = L"tableLayoutPanel47";
			this->tableLayoutPanel47->RowCount = 1;
			this->tableLayoutPanel47->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel47->Size = System::Drawing::Size(188, 25);
			this->tableLayoutPanel47->TabIndex = 115;
			// 
			// TempAlarm1StatusLabel
			// 
			this->TempAlarm1StatusLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->TempAlarm1StatusLabel->AutoSize = true;
			this->TempAlarm1StatusLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm1StatusLabel->ForeColor = System::Drawing::Color::White;
			this->TempAlarm1StatusLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->TempAlarm1StatusLabel->Location = System::Drawing::Point(113, 5);
			this->TempAlarm1StatusLabel->Name = L"TempAlarm1StatusLabel";
			this->TempAlarm1StatusLabel->Size = System::Drawing::Size(48, 15);
			this->TempAlarm1StatusLabel->TabIndex = 29;
			this->TempAlarm1StatusLabel->Text = L"Normal";
			this->TempAlarm1StatusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label58
			// 
			this->label58->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label58->AutoSize = true;
			this->label58->Font = (gcnew System::Drawing::Font(L"Arial", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
			this->label58->ForeColor = System::Drawing::Color::White;
			this->label58->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label58->Location = System::Drawing::Point(8, 5);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(94, 15);
			this->label58->TabIndex = 28;
			this->label58->Text = L"Alarm 1 Status:";
			this->label58->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel48
			// 
			this->tableLayoutPanel48->ColumnCount = 2;
			this->tableLayoutPanel48->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				110)));
			this->tableLayoutPanel48->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel48->Controls->Add(this->TempAlarm2StatusLabel, 0, 0);
			this->tableLayoutPanel48->Controls->Add(this->label61, 0, 0);
			this->tableLayoutPanel48->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel48->Location = System::Drawing::Point(188, 0);
			this->tableLayoutPanel48->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel48->Name = L"tableLayoutPanel48";
			this->tableLayoutPanel48->RowCount = 1;
			this->tableLayoutPanel48->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel48->Size = System::Drawing::Size(188, 25);
			this->tableLayoutPanel48->TabIndex = 116;
			// 
			// TempAlarm2StatusLabel
			// 
			this->TempAlarm2StatusLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->TempAlarm2StatusLabel->AutoSize = true;
			this->TempAlarm2StatusLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm2StatusLabel->ForeColor = System::Drawing::Color::White;
			this->TempAlarm2StatusLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->TempAlarm2StatusLabel->Location = System::Drawing::Point(113, 5);
			this->TempAlarm2StatusLabel->Name = L"TempAlarm2StatusLabel";
			this->TempAlarm2StatusLabel->Size = System::Drawing::Size(48, 15);
			this->TempAlarm2StatusLabel->TabIndex = 29;
			this->TempAlarm2StatusLabel->Text = L"Normal";
			this->TempAlarm2StatusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label61
			// 
			this->label61->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label61->AutoSize = true;
			this->label61->Font = (gcnew System::Drawing::Font(L"Arial", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
			this->label61->ForeColor = System::Drawing::Color::White;
			this->label61->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label61->Location = System::Drawing::Point(8, 5);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(94, 15);
			this->label61->TabIndex = 28;
			this->label61->Text = L"Alarm 2 Status:";
			this->label61->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel49
			// 
			this->tableLayoutPanel49->ColumnCount = 2;
			this->tableLayoutPanel49->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				110)));
			this->tableLayoutPanel49->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel49->Controls->Add(this->TempAlarm3StatusLabel, 0, 0);
			this->tableLayoutPanel49->Controls->Add(this->label77, 0, 0);
			this->tableLayoutPanel49->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel49->Location = System::Drawing::Point(376, 0);
			this->tableLayoutPanel49->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel49->Name = L"tableLayoutPanel49";
			this->tableLayoutPanel49->RowCount = 1;
			this->tableLayoutPanel49->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel49->Size = System::Drawing::Size(188, 25);
			this->tableLayoutPanel49->TabIndex = 117;
			// 
			// TempAlarm3StatusLabel
			// 
			this->TempAlarm3StatusLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->TempAlarm3StatusLabel->AutoSize = true;
			this->TempAlarm3StatusLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm3StatusLabel->ForeColor = System::Drawing::Color::White;
			this->TempAlarm3StatusLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->TempAlarm3StatusLabel->Location = System::Drawing::Point(113, 5);
			this->TempAlarm3StatusLabel->Name = L"TempAlarm3StatusLabel";
			this->TempAlarm3StatusLabel->Size = System::Drawing::Size(48, 15);
			this->TempAlarm3StatusLabel->TabIndex = 29;
			this->TempAlarm3StatusLabel->Text = L"Normal";
			this->TempAlarm3StatusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label77
			// 
			this->label77->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label77->AutoSize = true;
			this->label77->Font = (gcnew System::Drawing::Font(L"Arial", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
			this->label77->ForeColor = System::Drawing::Color::White;
			this->label77->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label77->Location = System::Drawing::Point(8, 5);
			this->label77->Name = L"label77";
			this->label77->Size = System::Drawing::Size(94, 15);
			this->label77->TabIndex = 28;
			this->label77->Text = L"Alarm 3 Status:";
			this->label77->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel50
			// 
			this->tableLayoutPanel50->ColumnCount = 2;
			this->tableLayoutPanel50->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				110)));
			this->tableLayoutPanel50->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel50->Controls->Add(this->TempAlarm4StatusLabel, 0, 0);
			this->tableLayoutPanel50->Controls->Add(this->label79, 0, 0);
			this->tableLayoutPanel50->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel50->Location = System::Drawing::Point(564, 0);
			this->tableLayoutPanel50->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel50->Name = L"tableLayoutPanel50";
			this->tableLayoutPanel50->RowCount = 1;
			this->tableLayoutPanel50->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel50->Size = System::Drawing::Size(188, 25);
			this->tableLayoutPanel50->TabIndex = 118;
			// 
			// TempAlarm4StatusLabel
			// 
			this->TempAlarm4StatusLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->TempAlarm4StatusLabel->AutoSize = true;
			this->TempAlarm4StatusLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm4StatusLabel->ForeColor = System::Drawing::Color::White;
			this->TempAlarm4StatusLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->TempAlarm4StatusLabel->Location = System::Drawing::Point(113, 5);
			this->TempAlarm4StatusLabel->Name = L"TempAlarm4StatusLabel";
			this->TempAlarm4StatusLabel->Size = System::Drawing::Size(48, 15);
			this->TempAlarm4StatusLabel->TabIndex = 29;
			this->TempAlarm4StatusLabel->Text = L"Normal";
			this->TempAlarm4StatusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label79
			// 
			this->label79->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label79->AutoSize = true;
			this->label79->Font = (gcnew System::Drawing::Font(L"Arial", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
			this->label79->ForeColor = System::Drawing::Color::White;
			this->label79->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label79->Location = System::Drawing::Point(8, 5);
			this->label79->Name = L"label79";
			this->label79->Size = System::Drawing::Size(94, 15);
			this->label79->TabIndex = 28;
			this->label79->Text = L"Alarm 4 Status:";
			this->label79->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel56
			// 
			this->tableLayoutPanel56->ColumnCount = 2;
			this->tableLayoutPanel56->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				110)));
			this->tableLayoutPanel56->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel56->Controls->Add(this->TempAlarm5StatusLabel, 0, 0);
			this->tableLayoutPanel56->Controls->Add(this->label81, 0, 0);
			this->tableLayoutPanel56->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel56->Location = System::Drawing::Point(752, 0);
			this->tableLayoutPanel56->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel56->Name = L"tableLayoutPanel56";
			this->tableLayoutPanel56->RowCount = 1;
			this->tableLayoutPanel56->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel56->Size = System::Drawing::Size(191, 25);
			this->tableLayoutPanel56->TabIndex = 119;
			// 
			// TempAlarm5StatusLabel
			// 
			this->TempAlarm5StatusLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->TempAlarm5StatusLabel->AutoSize = true;
			this->TempAlarm5StatusLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarm5StatusLabel->ForeColor = System::Drawing::Color::White;
			this->TempAlarm5StatusLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->TempAlarm5StatusLabel->Location = System::Drawing::Point(113, 5);
			this->TempAlarm5StatusLabel->Name = L"TempAlarm5StatusLabel";
			this->TempAlarm5StatusLabel->Size = System::Drawing::Size(48, 15);
			this->TempAlarm5StatusLabel->TabIndex = 29;
			this->TempAlarm5StatusLabel->Text = L"Normal";
			this->TempAlarm5StatusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label81
			// 
			this->label81->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label81->AutoSize = true;
			this->label81->Font = (gcnew System::Drawing::Font(L"Arial", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
			this->label81->ForeColor = System::Drawing::Color::White;
			this->label81->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label81->Location = System::Drawing::Point(8, 5);
			this->label81->Name = L"label81";
			this->label81->Size = System::Drawing::Size(94, 15);
			this->label81->TabIndex = 28;
			this->label81->Text = L"Alarm 5 Status:";
			this->label81->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel58
			// 
			this->tableLayoutPanel58->ColumnCount = 5;
			this->tableLayoutPanel58->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel58->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.45175F)));
			this->tableLayoutPanel58->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				19.5122F)));
			this->tableLayoutPanel58->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				36.9035F)));
			this->tableLayoutPanel58->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel58->Controls->Add(this->tableLayoutPanel59, 3, 0);
			this->tableLayoutPanel58->Controls->Add(this->EnableAlarmTriggerEventsCheckBox, 2, 0);
			this->tableLayoutPanel58->Controls->Add(this->TempAlarmsTriggerSoundCheckBox, 1, 0);
			this->tableLayoutPanel58->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel58->Location = System::Drawing::Point(202, 25);
			this->tableLayoutPanel58->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel58->Name = L"tableLayoutPanel58";
			this->tableLayoutPanel58->RowCount = 1;
			this->tableLayoutPanel58->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel58->Size = System::Drawing::Size(943, 34);
			this->tableLayoutPanel58->TabIndex = 2;
			// 
			// tableLayoutPanel59
			// 
			this->tableLayoutPanel59->ColumnCount = 3;
			this->tableLayoutPanel59->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				155)));
			this->tableLayoutPanel59->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				107)));
			this->tableLayoutPanel59->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				80)));
			this->tableLayoutPanel59->Controls->Add(this->label59, 2, 0);
			this->tableLayoutPanel59->Controls->Add(this->AlarmTriggerEventsIntervalUpDown, 1, 0);
			this->tableLayoutPanel59->Controls->Add(this->label60, 0, 0);
			this->tableLayoutPanel59->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel59->Location = System::Drawing::Point(479, 3);
			this->tableLayoutPanel59->Name = L"tableLayoutPanel59";
			this->tableLayoutPanel59->RowCount = 1;
			this->tableLayoutPanel59->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel59->Size = System::Drawing::Size(342, 28);
			this->tableLayoutPanel59->TabIndex = 30;
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label59->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label59->ForeColor = System::Drawing::Color::White;
			this->label59->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label59->Location = System::Drawing::Point(265, 0);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(74, 28);
			this->label59->TabIndex = 29;
			this->label59->Text = L"Seconds";
			this->label59->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// AlarmTriggerEventsIntervalUpDown
			// 
			this->AlarmTriggerEventsIntervalUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->AlarmTriggerEventsIntervalUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->AlarmTriggerEventsIntervalUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->AlarmTriggerEventsIntervalUpDown->DecimalPlaces = 2;
			this->AlarmTriggerEventsIntervalUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->AlarmTriggerEventsIntervalUpDown->ForeColor = System::Drawing::Color::White;
			this->AlarmTriggerEventsIntervalUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->AlarmTriggerEventsIntervalUpDown->Location = System::Drawing::Point(158, 4);
			this->AlarmTriggerEventsIntervalUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7200, 0, 0, 0 });
			this->AlarmTriggerEventsIntervalUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->AlarmTriggerEventsIntervalUpDown->Name = L"AlarmTriggerEventsIntervalUpDown";
			this->AlarmTriggerEventsIntervalUpDown->Size = System::Drawing::Size(101, 20);
			this->AlarmTriggerEventsIntervalUpDown->TabIndex = 20;
			this->AlarmTriggerEventsIntervalUpDown->Tag = L"7";
			this->AlarmTriggerEventsIntervalUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->AlarmTriggerEventsIntervalUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->AlarmTriggerEventsIntervalUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::AlarmTriggerEventsIntervalUpDown_ValueChanged);
			// 
			// label60
			// 
			this->label60->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label60->AutoSize = true;
			this->label60->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label60->ForeColor = System::Drawing::Color::White;
			this->label60->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label60->Location = System::Drawing::Point(18, 6);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(118, 15);
			this->label60->TabIndex = 28;
			this->label60->Text = L"Trigger Event Delay:";
			this->label60->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// EnableAlarmTriggerEventsCheckBox
			// 
			this->EnableAlarmTriggerEventsCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->EnableAlarmTriggerEventsCheckBox->AutoSize = true;
			this->EnableAlarmTriggerEventsCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->EnableAlarmTriggerEventsCheckBox->ForeColor = System::Drawing::Color::Cyan;
			this->EnableAlarmTriggerEventsCheckBox->Location = System::Drawing::Point(310, 7);
			this->EnableAlarmTriggerEventsCheckBox->Name = L"EnableAlarmTriggerEventsCheckBox";
			this->EnableAlarmTriggerEventsCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->EnableAlarmTriggerEventsCheckBox->Size = System::Drawing::Size(148, 19);
			this->EnableAlarmTriggerEventsCheckBox->TabIndex = 120;
			this->EnableAlarmTriggerEventsCheckBox->Tag = L"0";
			this->EnableAlarmTriggerEventsCheckBox->Text = L"Enable Trigger Events";
			this->EnableAlarmTriggerEventsCheckBox->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->EnableAlarmTriggerEventsCheckBox->UseVisualStyleBackColor = true;
			this->EnableAlarmTriggerEventsCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::EnableAlarmTriggerEventsCheckBox_CheckedChanged);
			// 
			// TempAlarmsTriggerSoundCheckBox
			// 
			this->TempAlarmsTriggerSoundCheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempAlarmsTriggerSoundCheckBox->AutoSize = true;
			this->TempAlarmsTriggerSoundCheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempAlarmsTriggerSoundCheckBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->TempAlarmsTriggerSoundCheckBox->Location = System::Drawing::Point(132, 7);
			this->TempAlarmsTriggerSoundCheckBox->Name = L"TempAlarmsTriggerSoundCheckBox";
			this->TempAlarmsTriggerSoundCheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TempAlarmsTriggerSoundCheckBox->Size = System::Drawing::Size(146, 19);
			this->TempAlarmsTriggerSoundCheckBox->TabIndex = 114;
			this->TempAlarmsTriggerSoundCheckBox->Tag = L"0";
			this->TempAlarmsTriggerSoundCheckBox->Text = L"Enable Trigger Sound";
			this->TempAlarmsTriggerSoundCheckBox->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->TempAlarmsTriggerSoundCheckBox->UseVisualStyleBackColor = true;
			this->TempAlarmsTriggerSoundCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarmsTriggerSoundCheckBox_CheckedChanged);
			// 
			// tableLayoutPanel71
			// 
			this->tableLayoutPanel71->ColumnCount = 5;
			this->tableLayoutPanel71->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel71->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel71->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel71->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel71->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel71->Controls->Add(this->Alarm4TriggerEventResetButton, 0, 0);
			this->tableLayoutPanel71->Controls->Add(this->Alarm5TriggerEventResetButton, 0, 0);
			this->tableLayoutPanel71->Controls->Add(this->Alarm3TriggerEventResetButton, 0, 0);
			this->tableLayoutPanel71->Controls->Add(this->Alarm1TriggerEventResetButton, 0, 0);
			this->tableLayoutPanel71->Controls->Add(this->Alarm2TriggerEventResetButton, 0, 0);
			this->tableLayoutPanel71->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel71->Location = System::Drawing::Point(3, 305);
			this->tableLayoutPanel71->Name = L"tableLayoutPanel71";
			this->tableLayoutPanel71->RowCount = 1;
			this->tableLayoutPanel71->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel71->Size = System::Drawing::Size(1342, 45);
			this->tableLayoutPanel71->TabIndex = 2;
			// 
			// Alarm4TriggerEventResetButton
			// 
			this->Alarm4TriggerEventResetButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->Alarm4TriggerEventResetButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Alarm4TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->Alarm4TriggerEventResetButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Alarm4TriggerEventResetButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->Alarm4TriggerEventResetButton->ForeColor = System::Drawing::Color::White;
			this->Alarm4TriggerEventResetButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->Alarm4TriggerEventResetButton->Location = System::Drawing::Point(819, 3);
			this->Alarm4TriggerEventResetButton->Margin = System::Windows::Forms::Padding(15, 3, 15, 3);
			this->Alarm4TriggerEventResetButton->Name = L"Alarm4TriggerEventResetButton";
			this->Alarm4TriggerEventResetButton->Padding = System::Windows::Forms::Padding(3);
			this->Alarm4TriggerEventResetButton->Size = System::Drawing::Size(238, 39);
			this->Alarm4TriggerEventResetButton->TabIndex = 23;
			this->Alarm4TriggerEventResetButton->Tag = L"3";
			this->Alarm4TriggerEventResetButton->Text = L"Alarm 4 Trigger Event Reset";
			this->Alarm4TriggerEventResetButton->UseVisualStyleBackColor = false;
			this->Alarm4TriggerEventResetButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::Alarm1TriggerEventResetButton_Click);
			// 
			// Alarm5TriggerEventResetButton
			// 
			this->Alarm5TriggerEventResetButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->Alarm5TriggerEventResetButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Alarm5TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->Alarm5TriggerEventResetButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Alarm5TriggerEventResetButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->Alarm5TriggerEventResetButton->ForeColor = System::Drawing::Color::White;
			this->Alarm5TriggerEventResetButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->Alarm5TriggerEventResetButton->Location = System::Drawing::Point(1087, 3);
			this->Alarm5TriggerEventResetButton->Margin = System::Windows::Forms::Padding(15, 3, 15, 3);
			this->Alarm5TriggerEventResetButton->Name = L"Alarm5TriggerEventResetButton";
			this->Alarm5TriggerEventResetButton->Padding = System::Windows::Forms::Padding(3);
			this->Alarm5TriggerEventResetButton->Size = System::Drawing::Size(240, 39);
			this->Alarm5TriggerEventResetButton->TabIndex = 22;
			this->Alarm5TriggerEventResetButton->Tag = L"4";
			this->Alarm5TriggerEventResetButton->Text = L"Alarm 5 Trigger Event Reset";
			this->Alarm5TriggerEventResetButton->UseVisualStyleBackColor = false;
			this->Alarm5TriggerEventResetButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::Alarm1TriggerEventResetButton_Click);
			// 
			// Alarm3TriggerEventResetButton
			// 
			this->Alarm3TriggerEventResetButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->Alarm3TriggerEventResetButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Alarm3TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->Alarm3TriggerEventResetButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Alarm3TriggerEventResetButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->Alarm3TriggerEventResetButton->ForeColor = System::Drawing::Color::White;
			this->Alarm3TriggerEventResetButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->Alarm3TriggerEventResetButton->Location = System::Drawing::Point(551, 3);
			this->Alarm3TriggerEventResetButton->Margin = System::Windows::Forms::Padding(15, 3, 15, 3);
			this->Alarm3TriggerEventResetButton->Name = L"Alarm3TriggerEventResetButton";
			this->Alarm3TriggerEventResetButton->Padding = System::Windows::Forms::Padding(3);
			this->Alarm3TriggerEventResetButton->Size = System::Drawing::Size(238, 39);
			this->Alarm3TriggerEventResetButton->TabIndex = 21;
			this->Alarm3TriggerEventResetButton->Tag = L"2";
			this->Alarm3TriggerEventResetButton->Text = L"Alarm 3 Trigger Event Reset";
			this->Alarm3TriggerEventResetButton->UseVisualStyleBackColor = false;
			this->Alarm3TriggerEventResetButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::Alarm1TriggerEventResetButton_Click);
			// 
			// Alarm1TriggerEventResetButton
			// 
			this->Alarm1TriggerEventResetButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->Alarm1TriggerEventResetButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Alarm1TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->Alarm1TriggerEventResetButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Alarm1TriggerEventResetButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->Alarm1TriggerEventResetButton->ForeColor = System::Drawing::Color::White;
			this->Alarm1TriggerEventResetButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->Alarm1TriggerEventResetButton->Location = System::Drawing::Point(15, 3);
			this->Alarm1TriggerEventResetButton->Margin = System::Windows::Forms::Padding(15, 3, 15, 3);
			this->Alarm1TriggerEventResetButton->Name = L"Alarm1TriggerEventResetButton";
			this->Alarm1TriggerEventResetButton->Padding = System::Windows::Forms::Padding(3);
			this->Alarm1TriggerEventResetButton->Size = System::Drawing::Size(238, 39);
			this->Alarm1TriggerEventResetButton->TabIndex = 20;
			this->Alarm1TriggerEventResetButton->Tag = L"0";
			this->Alarm1TriggerEventResetButton->Text = L"Alarm 1 Trigger Event Reset";
			this->Alarm1TriggerEventResetButton->UseVisualStyleBackColor = false;
			this->Alarm1TriggerEventResetButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::Alarm1TriggerEventResetButton_Click);
			// 
			// Alarm2TriggerEventResetButton
			// 
			this->Alarm2TriggerEventResetButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->Alarm2TriggerEventResetButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Alarm2TriggerEventResetButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->Alarm2TriggerEventResetButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Alarm2TriggerEventResetButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->Alarm2TriggerEventResetButton->ForeColor = System::Drawing::Color::White;
			this->Alarm2TriggerEventResetButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->Alarm2TriggerEventResetButton->Location = System::Drawing::Point(283, 3);
			this->Alarm2TriggerEventResetButton->Margin = System::Windows::Forms::Padding(15, 3, 15, 3);
			this->Alarm2TriggerEventResetButton->Name = L"Alarm2TriggerEventResetButton";
			this->Alarm2TriggerEventResetButton->Padding = System::Windows::Forms::Padding(3);
			this->Alarm2TriggerEventResetButton->Size = System::Drawing::Size(238, 39);
			this->Alarm2TriggerEventResetButton->TabIndex = 19;
			this->Alarm2TriggerEventResetButton->Tag = L"1";
			this->Alarm2TriggerEventResetButton->Text = L"Alarm 2 Trigger Event Reset";
			this->Alarm2TriggerEventResetButton->UseVisualStyleBackColor = false;
			this->Alarm2TriggerEventResetButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::Alarm1TriggerEventResetButton_Click);
			// 
			// label90
			// 
			this->label90->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label90->AutoSize = true;
			this->label90->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label90->ForeColor = System::Drawing::Color::White;
			this->label90->Location = System::Drawing::Point(75, 359);
			this->label90->Name = L"label90";
			this->label90->Size = System::Drawing::Size(1197, 16);
			this->label90->TabIndex = 65;
			this->label90->Text = L"Press The Target Alarm Button, To Reset The Execution Of The Target Alarms Trigge"
				L"r Event. The Alarms Button Border Will Be RED, If Its Trigger Event Has Been Exe"
				L"cuted. ";
			this->label90->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempAlarmsConfigMenuButton
			// 
			this->TempAlarmsConfigMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempAlarmsConfigMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->TempAlarmsConfigMenuButton->Enabled = false;
			this->TempAlarmsConfigMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempAlarmsConfigMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempAlarmsConfigMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->TempAlarmsConfigMenuButton->ForeColor = System::Drawing::Color::White;
			this->TempAlarmsConfigMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TempAlarmsConfigMenuButton.Image")));
			this->TempAlarmsConfigMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->TempAlarmsConfigMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->TempAlarmsConfigMenuButton->Location = System::Drawing::Point(10, 2732);
			this->TempAlarmsConfigMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->TempAlarmsConfigMenuButton->Name = L"TempAlarmsConfigMenuButton";
			this->TempAlarmsConfigMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->TempAlarmsConfigMenuButton->Size = System::Drawing::Size(1370, 54);
			this->TempAlarmsConfigMenuButton->TabIndex = 48;
			this->TempAlarmsConfigMenuButton->Text = L"   Temperature Alarms Configuration:";
			this->TempAlarmsConfigMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->TempAlarmsConfigMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->TempAlarmsConfigMenuButton->UseVisualStyleBackColor = false;
			this->TempAlarmsConfigMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::TempAlarmsConfigMenuButton_Click);
			// 
			// DataLoggingSettingsSubMenuPanel
			// 
			this->DataLoggingSettingsSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->DataLoggingSettingsSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->DataLoggingSettingsSubMenuPanel->Controls->Add(this->tableLayoutPanel34);
			this->DataLoggingSettingsSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->DataLoggingSettingsSubMenuPanel->Location = System::Drawing::Point(10, 2381);
			this->DataLoggingSettingsSubMenuPanel->Name = L"DataLoggingSettingsSubMenuPanel";
			this->DataLoggingSettingsSubMenuPanel->Size = System::Drawing::Size(1370, 351);
			this->DataLoggingSettingsSubMenuPanel->TabIndex = 47;
			this->DataLoggingSettingsSubMenuPanel->Visible = false;
			// 
			// tableLayoutPanel34
			// 
			this->tableLayoutPanel34->ColumnCount = 2;
			this->tableLayoutPanel34->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				715)));
			this->tableLayoutPanel34->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel34->Controls->Add(this->tableLayoutPanel35, 0, 0);
			this->tableLayoutPanel34->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel34->Name = L"tableLayoutPanel34";
			this->tableLayoutPanel34->RowCount = 1;
			this->tableLayoutPanel34->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel34->Size = System::Drawing::Size(1302, 351);
			this->tableLayoutPanel34->TabIndex = 0;
			// 
			// tableLayoutPanel35
			// 
			this->tableLayoutPanel35->ColumnCount = 1;
			this->tableLayoutPanel35->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel35->Controls->Add(this->DefaultDataLoggingSavePathString, 0, 0);
			this->tableLayoutPanel35->Controls->Add(this->tableLayoutPanel75, 0, 1);
			this->tableLayoutPanel35->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel35->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel35->Name = L"tableLayoutPanel35";
			this->tableLayoutPanel35->RowCount = 2;
			this->tableLayoutPanel35->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				34)));
			this->tableLayoutPanel35->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel35->Size = System::Drawing::Size(709, 345);
			this->tableLayoutPanel35->TabIndex = 0;
			// 
			// DefaultDataLoggingSavePathString
			// 
			this->DefaultDataLoggingSavePathString->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->DefaultDataLoggingSavePathString->AutoSize = true;
			this->DefaultDataLoggingSavePathString->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->DefaultDataLoggingSavePathString->ForeColor = System::Drawing::Color::Cyan;
			this->DefaultDataLoggingSavePathString->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->DefaultDataLoggingSavePathString->Location = System::Drawing::Point(15, 18);
			this->DefaultDataLoggingSavePathString->Margin = System::Windows::Forms::Padding(15, 0, 3, 0);
			this->DefaultDataLoggingSavePathString->Name = L"DefaultDataLoggingSavePathString";
			this->DefaultDataLoggingSavePathString->Size = System::Drawing::Size(165, 16);
			this->DefaultDataLoggingSavePathString->TabIndex = 17;
			this->DefaultDataLoggingSavePathString->Text = L"Default Save File Path:";
			this->DefaultDataLoggingSavePathString->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel75
			// 
			this->tableLayoutPanel75->ColumnCount = 1;
			this->tableLayoutPanel75->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel75->Controls->Add(this->tableLayoutPanel76, 0, 1);
			this->tableLayoutPanel75->Controls->Add(this->tableLayoutPanel36, 0, 0);
			this->tableLayoutPanel75->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel75->Location = System::Drawing::Point(3, 37);
			this->tableLayoutPanel75->Name = L"tableLayoutPanel75";
			this->tableLayoutPanel75->RowCount = 2;
			this->tableLayoutPanel75->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				252)));
			this->tableLayoutPanel75->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				49)));
			this->tableLayoutPanel75->Size = System::Drawing::Size(703, 305);
			this->tableLayoutPanel75->TabIndex = 18;
			// 
			// tableLayoutPanel76
			// 
			this->tableLayoutPanel76->ColumnCount = 2;
			this->tableLayoutPanel76->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				36.13087F)));
			this->tableLayoutPanel76->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				63.86913F)));
			this->tableLayoutPanel76->Controls->Add(this->label93, 1, 0);
			this->tableLayoutPanel76->Controls->Add(this->DataLoggingCSVDelimiterCombiBox, 0, 0);
			this->tableLayoutPanel76->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel76->Location = System::Drawing::Point(0, 252);
			this->tableLayoutPanel76->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			this->tableLayoutPanel76->Name = L"tableLayoutPanel76";
			this->tableLayoutPanel76->RowCount = 1;
			this->tableLayoutPanel76->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel76->Size = System::Drawing::Size(703, 38);
			this->tableLayoutPanel76->TabIndex = 24;
			// 
			// label93
			// 
			this->label93->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label93->AutoSize = true;
			this->label93->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label93->ForeColor = System::Drawing::Color::White;
			this->label93->Location = System::Drawing::Point(266, 4);
			this->label93->Name = L"label93";
			this->label93->Size = System::Drawing::Size(424, 30);
			this->label93->TabIndex = 24;
			this->label93->Text = L"Select The Desired Data Logging CSV Delimiter. This Setting Will Be Saved For Eve"
				L"ry Session.";
			this->label93->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataLoggingCSVDelimiterCombiBox
			// 
			this->DataLoggingCSVDelimiterCombiBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataLoggingCSVDelimiterCombiBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataLoggingCSVDelimiterCombiBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataLoggingCSVDelimiterCombiBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataLoggingCSVDelimiterCombiBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataLoggingCSVDelimiterCombiBox->ForeColor = System::Drawing::Color::White;
			this->DataLoggingCSVDelimiterCombiBox->FormattingEnabled = true;
			this->DataLoggingCSVDelimiterCombiBox->Location = System::Drawing::Point(21, 7);
			this->DataLoggingCSVDelimiterCombiBox->Margin = System::Windows::Forms::Padding(20, 5, 0, 5);
			this->DataLoggingCSVDelimiterCombiBox->Name = L"DataLoggingCSVDelimiterCombiBox";
			this->DataLoggingCSVDelimiterCombiBox->Size = System::Drawing::Size(232, 24);
			this->DataLoggingCSVDelimiterCombiBox->TabIndex = 22;
			this->DataLoggingCSVDelimiterCombiBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataLoggingCSVDelimiterCombiBox_SelectedIndexChanged);
			// 
			// tableLayoutPanel36
			// 
			this->tableLayoutPanel36->ColumnCount = 2;
			this->tableLayoutPanel36->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				41.46685F)));
			this->tableLayoutPanel36->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				58.53315F)));
			this->tableLayoutPanel36->Controls->Add(this->tableLayoutPanel63, 0, 0);
			this->tableLayoutPanel36->Controls->Add(this->tableLayoutPanel64, 1, 0);
			this->tableLayoutPanel36->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel36->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel36->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel36->Name = L"tableLayoutPanel36";
			this->tableLayoutPanel36->RowCount = 1;
			this->tableLayoutPanel36->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel36->Size = System::Drawing::Size(703, 252);
			this->tableLayoutPanel36->TabIndex = 18;
			// 
			// tableLayoutPanel63
			// 
			this->tableLayoutPanel63->ColumnCount = 1;
			this->tableLayoutPanel63->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel63->Controls->Add(this->label39, 0, 1);
			this->tableLayoutPanel63->Controls->Add(this->ChangeCSVDefaultPathButton, 0, 0);
			this->tableLayoutPanel63->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel63->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel63->Name = L"tableLayoutPanel63";
			this->tableLayoutPanel63->RowCount = 2;
			this->tableLayoutPanel63->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 83.53413F)));
			this->tableLayoutPanel63->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.46586F)));
			this->tableLayoutPanel63->Size = System::Drawing::Size(285, 246);
			this->tableLayoutPanel63->TabIndex = 0;
			// 
			// label39
			// 
			this->label39->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label39->ForeColor = System::Drawing::Color::White;
			this->label39->Location = System::Drawing::Point(34, 205);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(216, 30);
			this->label39->TabIndex = 24;
			this->label39->Text = L"Press The Button, To Set The Default \r\nCSV Data Logging Save File Path.";
			this->label39->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ChangeCSVDefaultPathButton
			// 
			this->ChangeCSVDefaultPathButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ChangeCSVDefaultPathButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ChangeCSVDefaultPathButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ChangeCSVDefaultPathButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ChangeCSVDefaultPathButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ChangeCSVDefaultPathButton->ForeColor = System::Drawing::Color::White;
			this->ChangeCSVDefaultPathButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ChangeCSVDefaultPathButton.Image")));
			this->ChangeCSVDefaultPathButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ChangeCSVDefaultPathButton->Location = System::Drawing::Point(15, 15);
			this->ChangeCSVDefaultPathButton->Margin = System::Windows::Forms::Padding(15);
			this->ChangeCSVDefaultPathButton->Name = L"ChangeCSVDefaultPathButton";
			this->ChangeCSVDefaultPathButton->Padding = System::Windows::Forms::Padding(3);
			this->ChangeCSVDefaultPathButton->Size = System::Drawing::Size(255, 175);
			this->ChangeCSVDefaultPathButton->TabIndex = 18;
			this->ChangeCSVDefaultPathButton->UseVisualStyleBackColor = false;
			this->ChangeCSVDefaultPathButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::ChangeCSVDefaultPathButton_Click);
			// 
			// tableLayoutPanel64
			// 
			this->tableLayoutPanel64->ColumnCount = 1;
			this->tableLayoutPanel64->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel64->Controls->Add(this->tableLayoutPanel65, 0, 0);
			this->tableLayoutPanel64->Controls->Add(this->tableLayoutPanel66, 0, 1);
			this->tableLayoutPanel64->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel64->Location = System::Drawing::Point(294, 30);
			this->tableLayoutPanel64->Margin = System::Windows::Forms::Padding(3, 30, 3, 30);
			this->tableLayoutPanel64->Name = L"tableLayoutPanel64";
			this->tableLayoutPanel64->RowCount = 2;
			this->tableLayoutPanel64->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 42.05128F)));
			this->tableLayoutPanel64->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 57.94872F)));
			this->tableLayoutPanel64->Size = System::Drawing::Size(406, 192);
			this->tableLayoutPanel64->TabIndex = 1;
			// 
			// tableLayoutPanel65
			// 
			this->tableLayoutPanel65->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel65->ColumnCount = 1;
			this->tableLayoutPanel65->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel65->Controls->Add(this->label47, 0, 0);
			this->tableLayoutPanel65->Controls->Add(this->tableLayoutPanel37, 0, 1);
			this->tableLayoutPanel65->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel65->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel65->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel65->Name = L"tableLayoutPanel65";
			this->tableLayoutPanel65->RowCount = 2;
			this->tableLayoutPanel65->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 54.32099F)));
			this->tableLayoutPanel65->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 45.67901F)));
			this->tableLayoutPanel65->Size = System::Drawing::Size(406, 80);
			this->tableLayoutPanel65->TabIndex = 0;
			// 
			// label47
			// 
			this->label47->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label47->AutoSize = true;
			this->label47->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label47->ForeColor = System::Drawing::Color::White;
			this->label47->Location = System::Drawing::Point(20, 6);
			this->label47->Margin = System::Windows::Forms::Padding(0);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(366, 30);
			this->label47->TabIndex = 31;
			this->label47->Text = L"The Data Logging Interval, Determines The \r\nMeasurement Interval For Each Sample "
				L"Written To The CSV File.";
			this->label47->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel37
			// 
			this->tableLayoutPanel37->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel37->ColumnCount = 3;
			this->tableLayoutPanel37->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				155)));
			this->tableLayoutPanel37->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				107)));
			this->tableLayoutPanel37->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				72)));
			this->tableLayoutPanel37->Controls->Add(this->label41, 2, 0);
			this->tableLayoutPanel37->Controls->Add(this->LogIntervalUpDown, 1, 0);
			this->tableLayoutPanel37->Controls->Add(this->label40, 0, 0);
			this->tableLayoutPanel37->Location = System::Drawing::Point(36, 48);
			this->tableLayoutPanel37->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel37->Name = L"tableLayoutPanel37";
			this->tableLayoutPanel37->RowCount = 1;
			this->tableLayoutPanel37->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel37->Size = System::Drawing::Size(334, 26);
			this->tableLayoutPanel37->TabIndex = 29;
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label41->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label41->ForeColor = System::Drawing::Color::White;
			this->label41->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label41->Location = System::Drawing::Point(265, 0);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(66, 26);
			this->label41->TabIndex = 29;
			this->label41->Text = L"Seconds";
			this->label41->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// LogIntervalUpDown
			// 
			this->LogIntervalUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->LogIntervalUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->LogIntervalUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LogIntervalUpDown->DecimalPlaces = 2;
			this->LogIntervalUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->LogIntervalUpDown->ForeColor = System::Drawing::Color::White;
			this->LogIntervalUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->LogIntervalUpDown->Location = System::Drawing::Point(158, 3);
			this->LogIntervalUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7200, 0, 0, 0 });
			this->LogIntervalUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 196608 });
			this->LogIntervalUpDown->Name = L"LogIntervalUpDown";
			this->LogIntervalUpDown->Size = System::Drawing::Size(101, 20);
			this->LogIntervalUpDown->TabIndex = 20;
			this->LogIntervalUpDown->Tag = L"7";
			this->LogIntervalUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->LogIntervalUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 196608 });
			// 
			// label40
			// 
			this->label40->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label40->AutoSize = true;
			this->label40->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label40->ForeColor = System::Drawing::Color::White;
			this->label40->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label40->Location = System::Drawing::Point(4, 5);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(146, 15);
			this->label40->TabIndex = 28;
			this->label40->Text = L"Logging Sample Interval:";
			this->label40->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel66
			// 
			this->tableLayoutPanel66->ColumnCount = 1;
			this->tableLayoutPanel66->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel66->Controls->Add(this->tableLayoutPanel38, 0, 1);
			this->tableLayoutPanel66->Controls->Add(this->label48, 0, 0);
			this->tableLayoutPanel66->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel66->Location = System::Drawing::Point(0, 80);
			this->tableLayoutPanel66->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel66->Name = L"tableLayoutPanel66";
			this->tableLayoutPanel66->RowCount = 2;
			this->tableLayoutPanel66->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 37.16814F)));
			this->tableLayoutPanel66->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 62.83186F)));
			this->tableLayoutPanel66->Size = System::Drawing::Size(406, 112);
			this->tableLayoutPanel66->TabIndex = 1;
			// 
			// tableLayoutPanel38
			// 
			this->tableLayoutPanel38->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->tableLayoutPanel38->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel38->ColumnCount = 4;
			this->tableLayoutPanel38->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20.004F)));
			this->tableLayoutPanel38->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				26.66533F)));
			this->tableLayoutPanel38->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				26.66533F)));
			this->tableLayoutPanel38->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				26.66533F)));
			this->tableLayoutPanel38->Controls->Add(this->label44, 1, 0);
			this->tableLayoutPanel38->Controls->Add(this->label45, 2, 0);
			this->tableLayoutPanel38->Controls->Add(this->label46, 3, 0);
			this->tableLayoutPanel38->Controls->Add(this->DurationSecondsUpDown, 3, 1);
			this->tableLayoutPanel38->Controls->Add(this->DurationMinuteUpDown, 2, 1);
			this->tableLayoutPanel38->Controls->Add(this->DurationHourUpDown, 1, 1);
			this->tableLayoutPanel38->Controls->Add(this->label43, 0, 1);
			this->tableLayoutPanel38->Location = System::Drawing::Point(36, 55);
			this->tableLayoutPanel38->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel38->Name = L"tableLayoutPanel38";
			this->tableLayoutPanel38->RowCount = 2;
			this->tableLayoutPanel38->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel38->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				35)));
			this->tableLayoutPanel38->Size = System::Drawing::Size(334, 57);
			this->tableLayoutPanel38->TabIndex = 30;
			// 
			// label44
			// 
			this->label44->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label44->AutoSize = true;
			this->label44->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label44->ForeColor = System::Drawing::Color::White;
			this->label44->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label44->Location = System::Drawing::Point(90, 3);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(41, 15);
			this->label44->TabIndex = 32;
			this->label44->Text = L"Hours";
			this->label44->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label45
			// 
			this->label45->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label45->AutoSize = true;
			this->label45->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label45->ForeColor = System::Drawing::Color::White;
			this->label45->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label45->Location = System::Drawing::Point(172, 3);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(52, 15);
			this->label45->TabIndex = 33;
			this->label45->Text = L"Minutes";
			this->label45->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label46
			// 
			this->label46->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label46->AutoSize = true;
			this->label46->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label46->ForeColor = System::Drawing::Color::White;
			this->label46->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label46->Location = System::Drawing::Point(259, 3);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(57, 15);
			this->label46->TabIndex = 34;
			this->label46->Text = L"Seconds";
			this->label46->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DurationSecondsUpDown
			// 
			this->DurationSecondsUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DurationSecondsUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DurationSecondsUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DurationSecondsUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DurationSecondsUpDown->ForeColor = System::Drawing::Color::White;
			this->DurationSecondsUpDown->Location = System::Drawing::Point(253, 28);
			this->DurationSecondsUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 59, 0, 0, 0 });
			this->DurationSecondsUpDown->Name = L"DurationSecondsUpDown";
			this->DurationSecondsUpDown->Size = System::Drawing::Size(70, 20);
			this->DurationSecondsUpDown->TabIndex = 20;
			this->DurationSecondsUpDown->Tag = L"7";
			this->DurationSecondsUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// DurationMinuteUpDown
			// 
			this->DurationMinuteUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DurationMinuteUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DurationMinuteUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DurationMinuteUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DurationMinuteUpDown->ForeColor = System::Drawing::Color::White;
			this->DurationMinuteUpDown->Location = System::Drawing::Point(163, 28);
			this->DurationMinuteUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 59, 0, 0, 0 });
			this->DurationMinuteUpDown->Name = L"DurationMinuteUpDown";
			this->DurationMinuteUpDown->Size = System::Drawing::Size(70, 20);
			this->DurationMinuteUpDown->TabIndex = 31;
			this->DurationMinuteUpDown->Tag = L"7";
			this->DurationMinuteUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DurationMinuteUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// DurationHourUpDown
			// 
			this->DurationHourUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DurationHourUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DurationHourUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DurationHourUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DurationHourUpDown->ForeColor = System::Drawing::Color::White;
			this->DurationHourUpDown->Location = System::Drawing::Point(75, 28);
			this->DurationHourUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 719, 0, 0, 0 });
			this->DurationHourUpDown->Name = L"DurationHourUpDown";
			this->DurationHourUpDown->Size = System::Drawing::Size(70, 20);
			this->DurationHourUpDown->TabIndex = 35;
			this->DurationHourUpDown->Tag = L"7";
			this->DurationHourUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label43
			// 
			this->label43->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label43->AutoSize = true;
			this->label43->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label43->ForeColor = System::Drawing::Color::White;
			this->label43->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label43->Location = System::Drawing::Point(4, 31);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(58, 15);
			this->label43->TabIndex = 28;
			this->label43->Text = L"Duration:";
			this->label43->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label48
			// 
			this->label48->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label48->AutoSize = true;
			this->label48->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label48->ForeColor = System::Drawing::Color::White;
			this->label48->Location = System::Drawing::Point(10, 11);
			this->label48->Margin = System::Windows::Forms::Padding(0);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(386, 30);
			this->label48->TabIndex = 32;
			this->label48->Text = L"Configure The Data Logging Session Duration.\r\nData Logging Will Stop Once The Dur"
				L"ation Time Has Been Reached.";
			this->label48->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataLoggingSettingsMenuButton
			// 
			this->DataLoggingSettingsMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->DataLoggingSettingsMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->DataLoggingSettingsMenuButton->Enabled = false;
			this->DataLoggingSettingsMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->DataLoggingSettingsMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataLoggingSettingsMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->DataLoggingSettingsMenuButton->ForeColor = System::Drawing::Color::White;
			this->DataLoggingSettingsMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DataLoggingSettingsMenuButton.Image")));
			this->DataLoggingSettingsMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->DataLoggingSettingsMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->DataLoggingSettingsMenuButton->Location = System::Drawing::Point(10, 2327);
			this->DataLoggingSettingsMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->DataLoggingSettingsMenuButton->Name = L"DataLoggingSettingsMenuButton";
			this->DataLoggingSettingsMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->DataLoggingSettingsMenuButton->Size = System::Drawing::Size(1370, 54);
			this->DataLoggingSettingsMenuButton->TabIndex = 46;
			this->DataLoggingSettingsMenuButton->Text = L"   Data Logging Session Settings:";
			this->DataLoggingSettingsMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->DataLoggingSettingsMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->DataLoggingSettingsMenuButton->UseVisualStyleBackColor = false;
			this->DataLoggingSettingsMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataLoggingSettingsMenuButton_Click);
			// 
			// TempPlotDataSetSettingsSubMenuPanel
			// 
			this->TempPlotDataSetSettingsSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->TempPlotDataSetSettingsSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->TempPlotDataSetSettingsSubMenuPanel->Controls->Add(this->tableLayoutPanel33);
			this->TempPlotDataSetSettingsSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->TempPlotDataSetSettingsSubMenuPanel->Location = System::Drawing::Point(10, 1899);
			this->TempPlotDataSetSettingsSubMenuPanel->Name = L"TempPlotDataSetSettingsSubMenuPanel";
			this->TempPlotDataSetSettingsSubMenuPanel->Size = System::Drawing::Size(1370, 428);
			this->TempPlotDataSetSettingsSubMenuPanel->TabIndex = 43;
			this->TempPlotDataSetSettingsSubMenuPanel->Visible = false;
			// 
			// tableLayoutPanel33
			// 
			this->tableLayoutPanel33->ColumnCount = 2;
			this->tableLayoutPanel33->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				909)));
			this->tableLayoutPanel33->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				638)));
			this->tableLayoutPanel33->Controls->Add(this->tableLayoutPanel3, 0, 0);
			this->tableLayoutPanel33->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel33->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel33->Name = L"tableLayoutPanel33";
			this->tableLayoutPanel33->RowCount = 1;
			this->tableLayoutPanel33->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel33->Size = System::Drawing::Size(1368, 426);
			this->tableLayoutPanel33->TabIndex = 1;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel3->ColumnCount = 5;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				135)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				240)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				193)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				187)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				130)));
			this->tableLayoutPanel3->Controls->Add(this->DataSet1ComboBox, 1, 1);
			this->tableLayoutPanel3->Controls->Add(this->label14, 0, 10);
			this->tableLayoutPanel3->Controls->Add(this->DataSet10ComboBox, 1, 10);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel14, 2, 10);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel13, 2, 9);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel12, 2, 8);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel11, 2, 7);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel10, 2, 6);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel9, 2, 5);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel8, 2, 4);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel7, 2, 3);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel6, 2, 2);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel5, 2, 1);
			this->tableLayoutPanel3->Controls->Add(this->DataSet9ComboBox, 1, 9);
			this->tableLayoutPanel3->Controls->Add(this->DataSet8ComboBox, 1, 8);
			this->tableLayoutPanel3->Controls->Add(this->DataSet7ComboBox, 1, 7);
			this->tableLayoutPanel3->Controls->Add(this->DataSet6ComboBox, 1, 6);
			this->tableLayoutPanel3->Controls->Add(this->DataSet5ComboBox, 1, 5);
			this->tableLayoutPanel3->Controls->Add(this->DataSet4ComboBox, 1, 4);
			this->tableLayoutPanel3->Controls->Add(this->DataSet3ComboBox, 1, 3);
			this->tableLayoutPanel3->Controls->Add(this->DataSet2ComboBox, 1, 2);
			this->tableLayoutPanel3->Controls->Add(this->label13, 0, 9);
			this->tableLayoutPanel3->Controls->Add(this->label12, 0, 8);
			this->tableLayoutPanel3->Controls->Add(this->label11, 0, 7);
			this->tableLayoutPanel3->Controls->Add(this->label9, 0, 6);
			this->tableLayoutPanel3->Controls->Add(this->label10, 0, 5);
			this->tableLayoutPanel3->Controls->Add(this->label8, 0, 4);
			this->tableLayoutPanel3->Controls->Add(this->label7, 0, 3);
			this->tableLayoutPanel3->Controls->Add(this->label6, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->label5, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel24, 3, 10);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel23, 3, 9);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel22, 3, 8);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel21, 3, 7);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel20, 3, 6);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel19, 3, 5);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel18, 3, 4);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel17, 3, 3);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel16, 3, 2);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel15, 3, 1);
			this->tableLayoutPanel3->Controls->Add(this->DataSet10CheckBox, 4, 10);
			this->tableLayoutPanel3->Controls->Add(this->DataSet9CheckBox, 4, 9);
			this->tableLayoutPanel3->Controls->Add(this->DataSet8CheckBox, 4, 8);
			this->tableLayoutPanel3->Controls->Add(this->DataSet7CheckBox, 4, 7);
			this->tableLayoutPanel3->Controls->Add(this->DataSet6CheckBox, 4, 6);
			this->tableLayoutPanel3->Controls->Add(this->DataSet5CheckBox, 4, 5);
			this->tableLayoutPanel3->Controls->Add(this->DataSet4CheckBox, 4, 4);
			this->tableLayoutPanel3->Controls->Add(this->DataSet3CheckBox, 4, 3);
			this->tableLayoutPanel3->Controls->Add(this->DataSet2CheckBox, 4, 2);
			this->tableLayoutPanel3->Controls->Add(this->DataSet1CheckBox, 4, 1);
			this->tableLayoutPanel3->Controls->Add(this->label42, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->label49, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->label50, 2, 0);
			this->tableLayoutPanel3->Controls->Add(this->label51, 3, 0);
			this->tableLayoutPanel3->Controls->Add(this->label89, 4, 0);
			this->tableLayoutPanel3->Location = System::Drawing::Point(12, 10);
			this->tableLayoutPanel3->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 11;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(885, 406);
			this->tableLayoutPanel3->TabIndex = 0;
			// 
			// DataSet1ComboBox
			// 
			this->DataSet1ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet1ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet1ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet1ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet1ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet1ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet1ComboBox->FormattingEnabled = true;
			this->DataSet1ComboBox->Location = System::Drawing::Point(149, 46);
			this->DataSet1ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet1ComboBox->Name = L"DataSet1ComboBox";
			this->DataSet1ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet1ComboBox->TabIndex = 14;
			this->DataSet1ComboBox->Tag = L"0";
			this->DataSet1ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// label14
			// 
			this->label14->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(3, 364);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(129, 42);
			this->label14->TabIndex = 9;
			this->label14->Text = L"Plot Data Set 10:";
			this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet10ComboBox
			// 
			this->DataSet10ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet10ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet10ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet10ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet10ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet10ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet10ComboBox->FormattingEnabled = true;
			this->DataSet10ComboBox->Location = System::Drawing::Point(149, 373);
			this->DataSet10ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet10ComboBox->Name = L"DataSet10ComboBox";
			this->DataSet10ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet10ComboBox->TabIndex = 15;
			this->DataSet10ComboBox->Tag = L"9";
			this->DataSet10ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// tableLayoutPanel14
			// 
			this->tableLayoutPanel14->ColumnCount = 2;
			this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel14->Controls->Add(this->DataSet10UpDown, 1, 0);
			this->tableLayoutPanel14->Controls->Add(this->label24, 0, 0);
			this->tableLayoutPanel14->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel14->Location = System::Drawing::Point(378, 367);
			this->tableLayoutPanel14->Name = L"tableLayoutPanel14";
			this->tableLayoutPanel14->RowCount = 1;
			this->tableLayoutPanel14->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel14->Size = System::Drawing::Size(187, 36);
			this->tableLayoutPanel14->TabIndex = 30;
			// 
			// DataSet10UpDown
			// 
			this->DataSet10UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet10UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet10UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet10UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet10UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet10UpDown->Location = System::Drawing::Point(99, 8);
			this->DataSet10UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet10UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet10UpDown->Name = L"DataSet10UpDown";
			this->DataSet10UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet10UpDown->TabIndex = 20;
			this->DataSet10UpDown->Tag = L"9";
			this->DataSet10UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet10UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet10UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label24
			// 
			this->label24->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label24->ForeColor = System::Drawing::Color::White;
			this->label24->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label24->Location = System::Drawing::Point(13, 10);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(70, 15);
			this->label24->TabIndex = 28;
			this->label24->Text = L"Line Width:";
			this->label24->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel13
			// 
			this->tableLayoutPanel13->ColumnCount = 2;
			this->tableLayoutPanel13->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel13->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel13->Controls->Add(this->DataSet9UpDown, 1, 0);
			this->tableLayoutPanel13->Controls->Add(this->label23, 0, 0);
			this->tableLayoutPanel13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel13->Location = System::Drawing::Point(378, 331);
			this->tableLayoutPanel13->Name = L"tableLayoutPanel13";
			this->tableLayoutPanel13->RowCount = 1;
			this->tableLayoutPanel13->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel13->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel13->TabIndex = 29;
			// 
			// DataSet9UpDown
			// 
			this->DataSet9UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet9UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet9UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet9UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet9UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet9UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet9UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet9UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet9UpDown->Name = L"DataSet9UpDown";
			this->DataSet9UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet9UpDown->TabIndex = 20;
			this->DataSet9UpDown->Tag = L"8";
			this->DataSet9UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet9UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet9UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label23
			// 
			this->label23->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label23->ForeColor = System::Drawing::Color::White;
			this->label23->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label23->Location = System::Drawing::Point(13, 7);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(70, 15);
			this->label23->TabIndex = 28;
			this->label23->Text = L"Line Width:";
			this->label23->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel12
			// 
			this->tableLayoutPanel12->ColumnCount = 2;
			this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel12->Controls->Add(this->DataSet8UpDown, 1, 0);
			this->tableLayoutPanel12->Controls->Add(this->label22, 0, 0);
			this->tableLayoutPanel12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel12->Location = System::Drawing::Point(378, 295);
			this->tableLayoutPanel12->Name = L"tableLayoutPanel12";
			this->tableLayoutPanel12->RowCount = 1;
			this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel12->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel12->TabIndex = 28;
			// 
			// DataSet8UpDown
			// 
			this->DataSet8UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet8UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet8UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet8UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet8UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet8UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet8UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet8UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet8UpDown->Name = L"DataSet8UpDown";
			this->DataSet8UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet8UpDown->TabIndex = 20;
			this->DataSet8UpDown->Tag = L"7";
			this->DataSet8UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet8UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet8UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label22
			// 
			this->label22->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label22->ForeColor = System::Drawing::Color::White;
			this->label22->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label22->Location = System::Drawing::Point(13, 7);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(70, 15);
			this->label22->TabIndex = 28;
			this->label22->Text = L"Line Width:";
			this->label22->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel11
			// 
			this->tableLayoutPanel11->ColumnCount = 2;
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel11->Controls->Add(this->DataSet7UpDown, 1, 0);
			this->tableLayoutPanel11->Controls->Add(this->label21, 0, 0);
			this->tableLayoutPanel11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel11->Location = System::Drawing::Point(378, 259);
			this->tableLayoutPanel11->Name = L"tableLayoutPanel11";
			this->tableLayoutPanel11->RowCount = 1;
			this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel11->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel11->TabIndex = 27;
			// 
			// DataSet7UpDown
			// 
			this->DataSet7UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet7UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet7UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet7UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet7UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet7UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet7UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet7UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet7UpDown->Name = L"DataSet7UpDown";
			this->DataSet7UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet7UpDown->TabIndex = 20;
			this->DataSet7UpDown->Tag = L"6";
			this->DataSet7UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet7UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet7UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label21
			// 
			this->label21->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label21->ForeColor = System::Drawing::Color::White;
			this->label21->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label21->Location = System::Drawing::Point(13, 7);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(70, 15);
			this->label21->TabIndex = 28;
			this->label21->Text = L"Line Width:";
			this->label21->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel10
			// 
			this->tableLayoutPanel10->ColumnCount = 2;
			this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel10->Controls->Add(this->DataSet6UpDown, 1, 0);
			this->tableLayoutPanel10->Controls->Add(this->label20, 0, 0);
			this->tableLayoutPanel10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel10->Location = System::Drawing::Point(378, 223);
			this->tableLayoutPanel10->Name = L"tableLayoutPanel10";
			this->tableLayoutPanel10->RowCount = 1;
			this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel10->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel10->TabIndex = 26;
			// 
			// DataSet6UpDown
			// 
			this->DataSet6UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet6UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet6UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet6UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet6UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet6UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet6UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet6UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet6UpDown->Name = L"DataSet6UpDown";
			this->DataSet6UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet6UpDown->TabIndex = 20;
			this->DataSet6UpDown->Tag = L"5";
			this->DataSet6UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet6UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet6UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label20
			// 
			this->label20->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label20->ForeColor = System::Drawing::Color::White;
			this->label20->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label20->Location = System::Drawing::Point(13, 7);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(70, 15);
			this->label20->TabIndex = 28;
			this->label20->Text = L"Line Width:";
			this->label20->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel9
			// 
			this->tableLayoutPanel9->ColumnCount = 2;
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel9->Controls->Add(this->DataSet5UpDown, 1, 0);
			this->tableLayoutPanel9->Controls->Add(this->label19, 0, 0);
			this->tableLayoutPanel9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel9->Location = System::Drawing::Point(378, 187);
			this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			this->tableLayoutPanel9->RowCount = 1;
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel9->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel9->TabIndex = 25;
			// 
			// DataSet5UpDown
			// 
			this->DataSet5UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet5UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet5UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet5UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet5UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet5UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet5UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet5UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet5UpDown->Name = L"DataSet5UpDown";
			this->DataSet5UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet5UpDown->TabIndex = 20;
			this->DataSet5UpDown->Tag = L"4";
			this->DataSet5UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet5UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet5UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label19
			// 
			this->label19->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label19->ForeColor = System::Drawing::Color::White;
			this->label19->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label19->Location = System::Drawing::Point(13, 7);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(70, 15);
			this->label19->TabIndex = 28;
			this->label19->Text = L"Line Width:";
			this->label19->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel8
			// 
			this->tableLayoutPanel8->ColumnCount = 2;
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel8->Controls->Add(this->DataSet4UpDown, 1, 0);
			this->tableLayoutPanel8->Controls->Add(this->label18, 0, 0);
			this->tableLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel8->Location = System::Drawing::Point(378, 151);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 1;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel8->TabIndex = 24;
			// 
			// DataSet4UpDown
			// 
			this->DataSet4UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet4UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet4UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet4UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet4UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet4UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet4UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet4UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet4UpDown->Name = L"DataSet4UpDown";
			this->DataSet4UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet4UpDown->TabIndex = 20;
			this->DataSet4UpDown->Tag = L"3";
			this->DataSet4UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet4UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet4UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label18
			// 
			this->label18->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label18->ForeColor = System::Drawing::Color::White;
			this->label18->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label18->Location = System::Drawing::Point(13, 7);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(70, 15);
			this->label18->TabIndex = 28;
			this->label18->Text = L"Line Width:";
			this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel7
			// 
			this->tableLayoutPanel7->ColumnCount = 2;
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel7->Controls->Add(this->DataSet3UpDown, 1, 0);
			this->tableLayoutPanel7->Controls->Add(this->label17, 0, 0);
			this->tableLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel7->Location = System::Drawing::Point(378, 115);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 1;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel7->TabIndex = 23;
			// 
			// DataSet3UpDown
			// 
			this->DataSet3UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet3UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet3UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet3UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet3UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet3UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet3UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet3UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet3UpDown->Name = L"DataSet3UpDown";
			this->DataSet3UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet3UpDown->TabIndex = 20;
			this->DataSet3UpDown->Tag = L"2";
			this->DataSet3UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet3UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet3UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label17
			// 
			this->label17->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label17->ForeColor = System::Drawing::Color::White;
			this->label17->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label17->Location = System::Drawing::Point(13, 7);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(70, 15);
			this->label17->TabIndex = 28;
			this->label17->Text = L"Line Width:";
			this->label17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 2;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel6->Controls->Add(this->DataSet2UpDown, 1, 0);
			this->tableLayoutPanel6->Controls->Add(this->label16, 0, 0);
			this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel6->Location = System::Drawing::Point(378, 79);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 1;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel6->TabIndex = 22;
			// 
			// DataSet2UpDown
			// 
			this->DataSet2UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet2UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet2UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet2UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet2UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet2UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet2UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet2UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet2UpDown->Name = L"DataSet2UpDown";
			this->DataSet2UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet2UpDown->TabIndex = 20;
			this->DataSet2UpDown->Tag = L"1";
			this->DataSet2UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet2UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet2UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label16
			// 
			this->label16->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label16->Location = System::Drawing::Point(13, 7);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(70, 15);
			this->label16->TabIndex = 28;
			this->label16->Text = L"Line Width:";
			this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 2;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				51.75879F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				48.24121F)));
			this->tableLayoutPanel5->Controls->Add(this->DataSet1UpDown, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->label15, 0, 0);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(378, 43);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 1;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(187, 30);
			this->tableLayoutPanel5->TabIndex = 21;
			// 
			// DataSet1UpDown
			// 
			this->DataSet1UpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet1UpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet1UpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DataSet1UpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DataSet1UpDown->ForeColor = System::Drawing::Color::White;
			this->DataSet1UpDown->Location = System::Drawing::Point(99, 5);
			this->DataSet1UpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->DataSet1UpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet1UpDown->Name = L"DataSet1UpDown";
			this->DataSet1UpDown->Size = System::Drawing::Size(85, 20);
			this->DataSet1UpDown->TabIndex = 20;
			this->DataSet1UpDown->Tag = L"0";
			this->DataSet1UpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->DataSet1UpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->DataSet1UpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1UpDown_ValueChanged);
			// 
			// label15
			// 
			this->label15->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label15->Location = System::Drawing::Point(13, 7);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(70, 15);
			this->label15->TabIndex = 28;
			this->label15->Text = L"Line Width:";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet9ComboBox
			// 
			this->DataSet9ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet9ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet9ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet9ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet9ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet9ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet9ComboBox->FormattingEnabled = true;
			this->DataSet9ComboBox->Location = System::Drawing::Point(149, 334);
			this->DataSet9ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet9ComboBox->Name = L"DataSet9ComboBox";
			this->DataSet9ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet9ComboBox->TabIndex = 15;
			this->DataSet9ComboBox->Tag = L"8";
			this->DataSet9ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// DataSet8ComboBox
			// 
			this->DataSet8ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet8ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet8ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet8ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet8ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet8ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet8ComboBox->FormattingEnabled = true;
			this->DataSet8ComboBox->Location = System::Drawing::Point(149, 298);
			this->DataSet8ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet8ComboBox->Name = L"DataSet8ComboBox";
			this->DataSet8ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet8ComboBox->TabIndex = 15;
			this->DataSet8ComboBox->Tag = L"7";
			this->DataSet8ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// DataSet7ComboBox
			// 
			this->DataSet7ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet7ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet7ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet7ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet7ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet7ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet7ComboBox->FormattingEnabled = true;
			this->DataSet7ComboBox->Location = System::Drawing::Point(149, 262);
			this->DataSet7ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet7ComboBox->Name = L"DataSet7ComboBox";
			this->DataSet7ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet7ComboBox->TabIndex = 15;
			this->DataSet7ComboBox->Tag = L"6";
			this->DataSet7ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// DataSet6ComboBox
			// 
			this->DataSet6ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet6ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet6ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet6ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet6ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet6ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet6ComboBox->FormattingEnabled = true;
			this->DataSet6ComboBox->Location = System::Drawing::Point(149, 226);
			this->DataSet6ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet6ComboBox->Name = L"DataSet6ComboBox";
			this->DataSet6ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet6ComboBox->TabIndex = 15;
			this->DataSet6ComboBox->Tag = L"5";
			this->DataSet6ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// DataSet5ComboBox
			// 
			this->DataSet5ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet5ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet5ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet5ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet5ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet5ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet5ComboBox->FormattingEnabled = true;
			this->DataSet5ComboBox->Location = System::Drawing::Point(149, 190);
			this->DataSet5ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet5ComboBox->Name = L"DataSet5ComboBox";
			this->DataSet5ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet5ComboBox->TabIndex = 15;
			this->DataSet5ComboBox->Tag = L"4";
			this->DataSet5ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// DataSet4ComboBox
			// 
			this->DataSet4ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet4ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet4ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet4ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet4ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet4ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet4ComboBox->FormattingEnabled = true;
			this->DataSet4ComboBox->Location = System::Drawing::Point(149, 154);
			this->DataSet4ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet4ComboBox->Name = L"DataSet4ComboBox";
			this->DataSet4ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet4ComboBox->TabIndex = 15;
			this->DataSet4ComboBox->Tag = L"3";
			this->DataSet4ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// DataSet3ComboBox
			// 
			this->DataSet3ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet3ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet3ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet3ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet3ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet3ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet3ComboBox->FormattingEnabled = true;
			this->DataSet3ComboBox->Location = System::Drawing::Point(149, 118);
			this->DataSet3ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet3ComboBox->Name = L"DataSet3ComboBox";
			this->DataSet3ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet3ComboBox->TabIndex = 15;
			this->DataSet3ComboBox->Tag = L"2";
			this->DataSet3ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// DataSet2ComboBox
			// 
			this->DataSet2ComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet2ComboBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DataSet2ComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataSet2ComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DataSet2ComboBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->DataSet2ComboBox->ForeColor = System::Drawing::Color::White;
			this->DataSet2ComboBox->FormattingEnabled = true;
			this->DataSet2ComboBox->Location = System::Drawing::Point(149, 82);
			this->DataSet2ComboBox->Margin = System::Windows::Forms::Padding(10, 3, 10, 3);
			this->DataSet2ComboBox->Name = L"DataSet2ComboBox";
			this->DataSet2ComboBox->Size = System::Drawing::Size(211, 24);
			this->DataSet2ComboBox->TabIndex = 15;
			this->DataSet2ComboBox->Tag = L"1";
			this->DataSet2ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ComboBox_SelectedIndexChanged);
			// 
			// label13
			// 
			this->label13->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(3, 328);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(129, 36);
			this->label13->TabIndex = 8;
			this->label13->Text = L"Plot Data Set 9:";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label12
			// 
			this->label12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(3, 292);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(129, 36);
			this->label12->TabIndex = 7;
			this->label12->Text = L"Plot Data Set 8:";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label11
			// 
			this->label11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(3, 256);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(129, 36);
			this->label11->TabIndex = 6;
			this->label11->Text = L"Plot Data Set 7:";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label9
			// 
			this->label9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(3, 220);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(129, 36);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Plot Data Set 6:";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label10
			// 
			this->label10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(3, 184);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(129, 36);
			this->label10->TabIndex = 5;
			this->label10->Text = L"Plot Data Set 5:";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(3, 148);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(129, 36);
			this->label8->TabIndex = 3;
			this->label8->Text = L"Plot Data Set 4:";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(3, 112);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(129, 36);
			this->label7->TabIndex = 2;
			this->label7->Text = L"Plot Data Set 3:";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(3, 76);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(129, 36);
			this->label6->TabIndex = 1;
			this->label6->Text = L"Plot Data Set 2:";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(3, 40);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(129, 36);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Plot Data Set 1:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel24
			// 
			this->tableLayoutPanel24->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel24->ColumnCount = 2;
			this->tableLayoutPanel24->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel24->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel24->Controls->Add(this->label34, 0, 0);
			this->tableLayoutPanel24->Controls->Add(this->DataSet10ColorPanel, 1, 0);
			this->tableLayoutPanel24->Location = System::Drawing::Point(577, 372);
			this->tableLayoutPanel24->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel24->Name = L"tableLayoutPanel24";
			this->tableLayoutPanel24->RowCount = 1;
			this->tableLayoutPanel24->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel24->Size = System::Drawing::Size(169, 26);
			this->tableLayoutPanel24->TabIndex = 39;
			// 
			// label34
			// 
			this->label34->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label34->ForeColor = System::Drawing::Color::White;
			this->label34->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label34->Location = System::Drawing::Point(8, 5);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(67, 15);
			this->label34->TabIndex = 29;
			this->label34->Text = L"Line Color:";
			this->label34->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet10ColorPanel
			// 
			this->DataSet10ColorPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->DataSet10ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet10ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet10ColorPanel->Name = L"DataSet10ColorPanel";
			this->DataSet10ColorPanel->Size = System::Drawing::Size(79, 20);
			this->DataSet10ColorPanel->TabIndex = 0;
			this->DataSet10ColorPanel->Tag = L"9";
			this->DataSet10ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel23
			// 
			this->tableLayoutPanel23->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel23->ColumnCount = 2;
			this->tableLayoutPanel23->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel23->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel23->Controls->Add(this->label33, 0, 0);
			this->tableLayoutPanel23->Controls->Add(this->DataSet9ColorPanel, 1, 0);
			this->tableLayoutPanel23->Location = System::Drawing::Point(577, 334);
			this->tableLayoutPanel23->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel23->Name = L"tableLayoutPanel23";
			this->tableLayoutPanel23->RowCount = 1;
			this->tableLayoutPanel23->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel23->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel23->TabIndex = 38;
			// 
			// label33
			// 
			this->label33->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label33->ForeColor = System::Drawing::Color::White;
			this->label33->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label33->Location = System::Drawing::Point(8, 4);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(67, 15);
			this->label33->TabIndex = 29;
			this->label33->Text = L"Line Color:";
			this->label33->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet9ColorPanel
			// 
			this->DataSet9ColorPanel->BackColor = System::Drawing::Color::Gray;
			this->DataSet9ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet9ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet9ColorPanel->Name = L"DataSet9ColorPanel";
			this->DataSet9ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet9ColorPanel->TabIndex = 0;
			this->DataSet9ColorPanel->Tag = L"8";
			this->DataSet9ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel22
			// 
			this->tableLayoutPanel22->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel22->ColumnCount = 2;
			this->tableLayoutPanel22->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel22->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel22->Controls->Add(this->label32, 0, 0);
			this->tableLayoutPanel22->Controls->Add(this->DataSet8ColorPanel, 1, 0);
			this->tableLayoutPanel22->Location = System::Drawing::Point(577, 298);
			this->tableLayoutPanel22->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel22->Name = L"tableLayoutPanel22";
			this->tableLayoutPanel22->RowCount = 1;
			this->tableLayoutPanel22->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel22->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel22->TabIndex = 37;
			// 
			// label32
			// 
			this->label32->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label32->ForeColor = System::Drawing::Color::White;
			this->label32->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label32->Location = System::Drawing::Point(8, 4);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(67, 15);
			this->label32->TabIndex = 29;
			this->label32->Text = L"Line Color:";
			this->label32->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet8ColorPanel
			// 
			this->DataSet8ColorPanel->BackColor = System::Drawing::Color::White;
			this->DataSet8ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet8ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet8ColorPanel->Name = L"DataSet8ColorPanel";
			this->DataSet8ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet8ColorPanel->TabIndex = 0;
			this->DataSet8ColorPanel->Tag = L"7";
			this->DataSet8ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel21
			// 
			this->tableLayoutPanel21->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel21->ColumnCount = 2;
			this->tableLayoutPanel21->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel21->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel21->Controls->Add(this->label31, 0, 0);
			this->tableLayoutPanel21->Controls->Add(this->DataSet7ColorPanel, 1, 0);
			this->tableLayoutPanel21->Location = System::Drawing::Point(577, 262);
			this->tableLayoutPanel21->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel21->Name = L"tableLayoutPanel21";
			this->tableLayoutPanel21->RowCount = 1;
			this->tableLayoutPanel21->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel21->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel21->TabIndex = 36;
			// 
			// label31
			// 
			this->label31->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label31->ForeColor = System::Drawing::Color::White;
			this->label31->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label31->Location = System::Drawing::Point(8, 4);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(67, 15);
			this->label31->TabIndex = 29;
			this->label31->Text = L"Line Color:";
			this->label31->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet7ColorPanel
			// 
			this->DataSet7ColorPanel->BackColor = System::Drawing::Color::Cyan;
			this->DataSet7ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet7ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet7ColorPanel->Name = L"DataSet7ColorPanel";
			this->DataSet7ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet7ColorPanel->TabIndex = 0;
			this->DataSet7ColorPanel->Tag = L"6";
			this->DataSet7ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel20
			// 
			this->tableLayoutPanel20->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel20->ColumnCount = 2;
			this->tableLayoutPanel20->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel20->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel20->Controls->Add(this->label30, 0, 0);
			this->tableLayoutPanel20->Controls->Add(this->DataSet6ColorPanel, 1, 0);
			this->tableLayoutPanel20->Location = System::Drawing::Point(577, 226);
			this->tableLayoutPanel20->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel20->Name = L"tableLayoutPanel20";
			this->tableLayoutPanel20->RowCount = 1;
			this->tableLayoutPanel20->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel20->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel20->TabIndex = 35;
			// 
			// label30
			// 
			this->label30->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label30->ForeColor = System::Drawing::Color::White;
			this->label30->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label30->Location = System::Drawing::Point(8, 4);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(67, 15);
			this->label30->TabIndex = 29;
			this->label30->Text = L"Line Color:";
			this->label30->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet6ColorPanel
			// 
			this->DataSet6ColorPanel->BackColor = System::Drawing::Color::Fuchsia;
			this->DataSet6ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet6ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet6ColorPanel->Name = L"DataSet6ColorPanel";
			this->DataSet6ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet6ColorPanel->TabIndex = 0;
			this->DataSet6ColorPanel->Tag = L"5";
			this->DataSet6ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel19
			// 
			this->tableLayoutPanel19->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel19->ColumnCount = 2;
			this->tableLayoutPanel19->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel19->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel19->Controls->Add(this->label29, 0, 0);
			this->tableLayoutPanel19->Controls->Add(this->DataSet5ColorPanel, 1, 0);
			this->tableLayoutPanel19->Location = System::Drawing::Point(577, 190);
			this->tableLayoutPanel19->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel19->Name = L"tableLayoutPanel19";
			this->tableLayoutPanel19->RowCount = 1;
			this->tableLayoutPanel19->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel19->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel19->TabIndex = 34;
			// 
			// label29
			// 
			this->label29->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label29->ForeColor = System::Drawing::Color::White;
			this->label29->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label29->Location = System::Drawing::Point(8, 4);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(67, 15);
			this->label29->TabIndex = 29;
			this->label29->Text = L"Line Color:";
			this->label29->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet5ColorPanel
			// 
			this->DataSet5ColorPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->DataSet5ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet5ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet5ColorPanel->Name = L"DataSet5ColorPanel";
			this->DataSet5ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet5ColorPanel->TabIndex = 0;
			this->DataSet5ColorPanel->Tag = L"4";
			this->DataSet5ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel18
			// 
			this->tableLayoutPanel18->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel18->ColumnCount = 2;
			this->tableLayoutPanel18->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel18->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel18->Controls->Add(this->label28, 0, 0);
			this->tableLayoutPanel18->Controls->Add(this->DataSet4ColorPanel, 1, 0);
			this->tableLayoutPanel18->Location = System::Drawing::Point(577, 154);
			this->tableLayoutPanel18->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel18->Name = L"tableLayoutPanel18";
			this->tableLayoutPanel18->RowCount = 1;
			this->tableLayoutPanel18->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel18->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel18->TabIndex = 33;
			// 
			// label28
			// 
			this->label28->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label28->ForeColor = System::Drawing::Color::White;
			this->label28->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label28->Location = System::Drawing::Point(8, 4);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(67, 15);
			this->label28->TabIndex = 29;
			this->label28->Text = L"Line Color:";
			this->label28->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet4ColorPanel
			// 
			this->DataSet4ColorPanel->BackColor = System::Drawing::Color::Yellow;
			this->DataSet4ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet4ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet4ColorPanel->Name = L"DataSet4ColorPanel";
			this->DataSet4ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet4ColorPanel->TabIndex = 0;
			this->DataSet4ColorPanel->Tag = L"3";
			this->DataSet4ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel17
			// 
			this->tableLayoutPanel17->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel17->ColumnCount = 2;
			this->tableLayoutPanel17->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel17->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel17->Controls->Add(this->label27, 0, 0);
			this->tableLayoutPanel17->Controls->Add(this->DataSet3ColorPanel, 1, 0);
			this->tableLayoutPanel17->Location = System::Drawing::Point(577, 118);
			this->tableLayoutPanel17->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel17->Name = L"tableLayoutPanel17";
			this->tableLayoutPanel17->RowCount = 1;
			this->tableLayoutPanel17->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel17->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel17->TabIndex = 32;
			// 
			// label27
			// 
			this->label27->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label27->ForeColor = System::Drawing::Color::White;
			this->label27->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label27->Location = System::Drawing::Point(8, 4);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(67, 15);
			this->label27->TabIndex = 29;
			this->label27->Text = L"Line Color:";
			this->label27->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet3ColorPanel
			// 
			this->DataSet3ColorPanel->BackColor = System::Drawing::Color::Lime;
			this->DataSet3ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet3ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet3ColorPanel->Name = L"DataSet3ColorPanel";
			this->DataSet3ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet3ColorPanel->TabIndex = 0;
			this->DataSet3ColorPanel->Tag = L"2";
			this->DataSet3ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel16
			// 
			this->tableLayoutPanel16->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel16->ColumnCount = 2;
			this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel16->Controls->Add(this->label26, 0, 0);
			this->tableLayoutPanel16->Controls->Add(this->DataSet2ColorPanel, 1, 0);
			this->tableLayoutPanel16->Location = System::Drawing::Point(577, 82);
			this->tableLayoutPanel16->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel16->Name = L"tableLayoutPanel16";
			this->tableLayoutPanel16->RowCount = 1;
			this->tableLayoutPanel16->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel16->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel16->TabIndex = 31;
			// 
			// label26
			// 
			this->label26->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label26->ForeColor = System::Drawing::Color::White;
			this->label26->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label26->Location = System::Drawing::Point(8, 4);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(67, 15);
			this->label26->TabIndex = 29;
			this->label26->Text = L"Line Color:";
			this->label26->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet2ColorPanel
			// 
			this->DataSet2ColorPanel->BackColor = System::Drawing::Color::Blue;
			this->DataSet2ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet2ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet2ColorPanel->Name = L"DataSet2ColorPanel";
			this->DataSet2ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet2ColorPanel->TabIndex = 0;
			this->DataSet2ColorPanel->Tag = L"1";
			this->DataSet2ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// tableLayoutPanel15
			// 
			this->tableLayoutPanel15->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel15->ColumnCount = 2;
			this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.70414F)));
			this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.29586F)));
			this->tableLayoutPanel15->Controls->Add(this->label25, 0, 0);
			this->tableLayoutPanel15->Controls->Add(this->DataSet1ColorPanel, 1, 0);
			this->tableLayoutPanel15->Location = System::Drawing::Point(577, 46);
			this->tableLayoutPanel15->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel15->Name = L"tableLayoutPanel15";
			this->tableLayoutPanel15->RowCount = 1;
			this->tableLayoutPanel15->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel15->Size = System::Drawing::Size(169, 23);
			this->tableLayoutPanel15->TabIndex = 22;
			// 
			// label25
			// 
			this->label25->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label25->ForeColor = System::Drawing::Color::White;
			this->label25->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label25->Location = System::Drawing::Point(8, 4);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(67, 15);
			this->label25->TabIndex = 29;
			this->label25->Text = L"Line Color:";
			this->label25->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DataSet1ColorPanel
			// 
			this->DataSet1ColorPanel->BackColor = System::Drawing::Color::Red;
			this->DataSet1ColorPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataSet1ColorPanel->Location = System::Drawing::Point(87, 3);
			this->DataSet1ColorPanel->Name = L"DataSet1ColorPanel";
			this->DataSet1ColorPanel->Size = System::Drawing::Size(79, 17);
			this->DataSet1ColorPanel->TabIndex = 0;
			this->DataSet1ColorPanel->Tag = L"0";
			this->DataSet1ColorPanel->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1ColorPanel_Click);
			// 
			// DataSet10CheckBox
			// 
			this->DataSet10CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet10CheckBox->AutoSize = true;
			this->DataSet10CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet10CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet10CheckBox->Location = System::Drawing::Point(770, 375);
			this->DataSet10CheckBox->Name = L"DataSet10CheckBox";
			this->DataSet10CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet10CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet10CheckBox->TabIndex = 49;
			this->DataSet10CheckBox->Tag = L"9";
			this->DataSet10CheckBox->Text = L"Plot Data Set";
			this->DataSet10CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet10CheckBox->UseVisualStyleBackColor = true;
			this->DataSet10CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet9CheckBox
			// 
			this->DataSet9CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet9CheckBox->AutoSize = true;
			this->DataSet9CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet9CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet9CheckBox->Location = System::Drawing::Point(770, 336);
			this->DataSet9CheckBox->Name = L"DataSet9CheckBox";
			this->DataSet9CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet9CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet9CheckBox->TabIndex = 48;
			this->DataSet9CheckBox->Tag = L"8";
			this->DataSet9CheckBox->Text = L"Plot Data Set";
			this->DataSet9CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet9CheckBox->UseVisualStyleBackColor = true;
			this->DataSet9CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet8CheckBox
			// 
			this->DataSet8CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet8CheckBox->AutoSize = true;
			this->DataSet8CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet8CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet8CheckBox->Location = System::Drawing::Point(770, 300);
			this->DataSet8CheckBox->Name = L"DataSet8CheckBox";
			this->DataSet8CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet8CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet8CheckBox->TabIndex = 47;
			this->DataSet8CheckBox->Tag = L"7";
			this->DataSet8CheckBox->Text = L"Plot Data Set";
			this->DataSet8CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet8CheckBox->UseVisualStyleBackColor = true;
			this->DataSet8CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet7CheckBox
			// 
			this->DataSet7CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet7CheckBox->AutoSize = true;
			this->DataSet7CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet7CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet7CheckBox->Location = System::Drawing::Point(770, 264);
			this->DataSet7CheckBox->Name = L"DataSet7CheckBox";
			this->DataSet7CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet7CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet7CheckBox->TabIndex = 46;
			this->DataSet7CheckBox->Tag = L"6";
			this->DataSet7CheckBox->Text = L"Plot Data Set";
			this->DataSet7CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet7CheckBox->UseVisualStyleBackColor = true;
			this->DataSet7CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet6CheckBox
			// 
			this->DataSet6CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet6CheckBox->AutoSize = true;
			this->DataSet6CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet6CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet6CheckBox->Location = System::Drawing::Point(770, 228);
			this->DataSet6CheckBox->Name = L"DataSet6CheckBox";
			this->DataSet6CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet6CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet6CheckBox->TabIndex = 45;
			this->DataSet6CheckBox->Tag = L"5";
			this->DataSet6CheckBox->Text = L"Plot Data Set";
			this->DataSet6CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet6CheckBox->UseVisualStyleBackColor = true;
			this->DataSet6CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet5CheckBox
			// 
			this->DataSet5CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet5CheckBox->AutoSize = true;
			this->DataSet5CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet5CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet5CheckBox->Location = System::Drawing::Point(770, 192);
			this->DataSet5CheckBox->Name = L"DataSet5CheckBox";
			this->DataSet5CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet5CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet5CheckBox->TabIndex = 44;
			this->DataSet5CheckBox->Tag = L"4";
			this->DataSet5CheckBox->Text = L"Plot Data Set";
			this->DataSet5CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet5CheckBox->UseVisualStyleBackColor = true;
			this->DataSet5CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet4CheckBox
			// 
			this->DataSet4CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet4CheckBox->AutoSize = true;
			this->DataSet4CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet4CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet4CheckBox->Location = System::Drawing::Point(770, 156);
			this->DataSet4CheckBox->Name = L"DataSet4CheckBox";
			this->DataSet4CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet4CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet4CheckBox->TabIndex = 43;
			this->DataSet4CheckBox->Tag = L"3";
			this->DataSet4CheckBox->Text = L"Plot Data Set";
			this->DataSet4CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet4CheckBox->UseVisualStyleBackColor = true;
			this->DataSet4CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet3CheckBox
			// 
			this->DataSet3CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet3CheckBox->AutoSize = true;
			this->DataSet3CheckBox->Checked = true;
			this->DataSet3CheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->DataSet3CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet3CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet3CheckBox->Location = System::Drawing::Point(770, 120);
			this->DataSet3CheckBox->Name = L"DataSet3CheckBox";
			this->DataSet3CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet3CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet3CheckBox->TabIndex = 42;
			this->DataSet3CheckBox->Tag = L"2";
			this->DataSet3CheckBox->Text = L"Plot Data Set";
			this->DataSet3CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet3CheckBox->UseVisualStyleBackColor = true;
			this->DataSet3CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet2CheckBox
			// 
			this->DataSet2CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet2CheckBox->AutoSize = true;
			this->DataSet2CheckBox->Checked = true;
			this->DataSet2CheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->DataSet2CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet2CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet2CheckBox->Location = System::Drawing::Point(770, 84);
			this->DataSet2CheckBox->Name = L"DataSet2CheckBox";
			this->DataSet2CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet2CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet2CheckBox->TabIndex = 41;
			this->DataSet2CheckBox->Tag = L"1";
			this->DataSet2CheckBox->Text = L"Plot Data Set";
			this->DataSet2CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet2CheckBox->UseVisualStyleBackColor = true;
			this->DataSet2CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// DataSet1CheckBox
			// 
			this->DataSet1CheckBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DataSet1CheckBox->AutoSize = true;
			this->DataSet1CheckBox->Checked = true;
			this->DataSet1CheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->DataSet1CheckBox->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DataSet1CheckBox->ForeColor = System::Drawing::Color::White;
			this->DataSet1CheckBox->Location = System::Drawing::Point(770, 48);
			this->DataSet1CheckBox->Name = L"DataSet1CheckBox";
			this->DataSet1CheckBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->DataSet1CheckBox->Size = System::Drawing::Size(99, 19);
			this->DataSet1CheckBox->TabIndex = 40;
			this->DataSet1CheckBox->Tag = L"0";
			this->DataSet1CheckBox->Text = L"Plot Data Set";
			this->DataSet1CheckBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->DataSet1CheckBox->UseVisualStyleBackColor = true;
			this->DataSet1CheckBox->CheckStateChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::DataSet1CheckBox_CheckStateChanged);
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label42->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label42->ForeColor = System::Drawing::Color::White;
			this->label42->Location = System::Drawing::Point(3, 0);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(129, 40);
			this->label42->TabIndex = 50;
			this->label42->Text = L"Data Set:";
			this->label42->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label49->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label49->ForeColor = System::Drawing::Color::White;
			this->label49->Location = System::Drawing::Point(138, 0);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(234, 40);
			this->label49->TabIndex = 51;
			this->label49->Text = L"Data Set Source:";
			this->label49->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label50->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label50->ForeColor = System::Drawing::Color::White;
			this->label50->Location = System::Drawing::Point(378, 0);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(187, 40);
			this->label50->TabIndex = 52;
			this->label50->Text = L"Data Set Line Width:";
			this->label50->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label51->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label51->ForeColor = System::Drawing::Color::White;
			this->label51->Location = System::Drawing::Point(571, 0);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(181, 40);
			this->label51->TabIndex = 53;
			this->label51->Text = L"Data Set Color:";
			this->label51->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label89
			// 
			this->label89->AutoSize = true;
			this->label89->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label89->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->label89->ForeColor = System::Drawing::Color::White;
			this->label89->Location = System::Drawing::Point(758, 0);
			this->label89->Name = L"label89";
			this->label89->Size = System::Drawing::Size(124, 40);
			this->label89->TabIndex = 54;
			this->label89->Text = L"Enable Plot:";
			this->label89->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TempPlotDataSetSettingsMenuButton
			// 
			this->TempPlotDataSetSettingsMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempPlotDataSetSettingsMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->TempPlotDataSetSettingsMenuButton->Enabled = false;
			this->TempPlotDataSetSettingsMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->TempPlotDataSetSettingsMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->TempPlotDataSetSettingsMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->TempPlotDataSetSettingsMenuButton->ForeColor = System::Drawing::Color::White;
			this->TempPlotDataSetSettingsMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TempPlotDataSetSettingsMenuButton.Image")));
			this->TempPlotDataSetSettingsMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->TempPlotDataSetSettingsMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->TempPlotDataSetSettingsMenuButton->Location = System::Drawing::Point(10, 1845);
			this->TempPlotDataSetSettingsMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->TempPlotDataSetSettingsMenuButton->Name = L"TempPlotDataSetSettingsMenuButton";
			this->TempPlotDataSetSettingsMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->TempPlotDataSetSettingsMenuButton->Size = System::Drawing::Size(1370, 54);
			this->TempPlotDataSetSettingsMenuButton->TabIndex = 42;
			this->TempPlotDataSetSettingsMenuButton->Text = L"   Temperature Plot Data Set Settings:";
			this->TempPlotDataSetSettingsMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->TempPlotDataSetSettingsMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->TempPlotDataSetSettingsMenuButton->UseVisualStyleBackColor = false;
			this->TempPlotDataSetSettingsMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::TempPlotDataSetSettingsMenuButton_Click);
			// 
			// VideoRecSettingsSubMenuPanel
			// 
			this->VideoRecSettingsSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->VideoRecSettingsSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->VideoRecSettingsSubMenuPanel->Controls->Add(this->tableLayoutPanel61);
			this->VideoRecSettingsSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->VideoRecSettingsSubMenuPanel->Location = System::Drawing::Point(10, 1480);
			this->VideoRecSettingsSubMenuPanel->Name = L"VideoRecSettingsSubMenuPanel";
			this->VideoRecSettingsSubMenuPanel->Size = System::Drawing::Size(1370, 365);
			this->VideoRecSettingsSubMenuPanel->TabIndex = 39;
			this->VideoRecSettingsSubMenuPanel->Visible = false;
			// 
			// tableLayoutPanel61
			// 
			this->tableLayoutPanel61->ColumnCount = 2;
			this->tableLayoutPanel61->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				1187)));
			this->tableLayoutPanel61->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				360)));
			this->tableLayoutPanel61->Controls->Add(this->tableLayoutPanel60, 0, 0);
			this->tableLayoutPanel61->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel61->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel61->Name = L"tableLayoutPanel61";
			this->tableLayoutPanel61->RowCount = 1;
			this->tableLayoutPanel61->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel61->Size = System::Drawing::Size(1368, 363);
			this->tableLayoutPanel61->TabIndex = 0;
			// 
			// tableLayoutPanel60
			// 
			this->tableLayoutPanel60->ColumnCount = 1;
			this->tableLayoutPanel60->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel60->Controls->Add(this->tableLayoutPanel84, 0, 2);
			this->tableLayoutPanel60->Controls->Add(this->tableLayoutPanel70, 0, 1);
			this->tableLayoutPanel60->Controls->Add(this->DefaultRecordingSavePathString, 0, 0);
			this->tableLayoutPanel60->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel60->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel60->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel60->Name = L"tableLayoutPanel60";
			this->tableLayoutPanel60->RowCount = 3;
			this->tableLayoutPanel60->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				37)));
			this->tableLayoutPanel60->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				273)));
			this->tableLayoutPanel60->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				41)));
			this->tableLayoutPanel60->Size = System::Drawing::Size(1187, 363);
			this->tableLayoutPanel60->TabIndex = 0;
			// 
			// tableLayoutPanel84
			// 
			this->tableLayoutPanel84->ColumnCount = 2;
			this->tableLayoutPanel84->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25.61078F)));
			this->tableLayoutPanel84->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				74.38921F)));
			this->tableLayoutPanel84->Controls->Add(this->tableLayoutPanel85, 0, 0);
			this->tableLayoutPanel84->Controls->Add(this->label114, 1, 0);
			this->tableLayoutPanel84->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel84->Location = System::Drawing::Point(0, 310);
			this->tableLayoutPanel84->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			this->tableLayoutPanel84->Name = L"tableLayoutPanel84";
			this->tableLayoutPanel84->RowCount = 1;
			this->tableLayoutPanel84->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel84->Size = System::Drawing::Size(1187, 38);
			this->tableLayoutPanel84->TabIndex = 27;
			// 
			// tableLayoutPanel85
			// 
			this->tableLayoutPanel85->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->tableLayoutPanel85->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel85->ColumnCount = 2;
			this->tableLayoutPanel85->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				65.38461F)));
			this->tableLayoutPanel85->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				34.61538F)));
			this->tableLayoutPanel85->Controls->Add(this->RecordingFrameRateNumericUpDown, 1, 0);
			this->tableLayoutPanel85->Controls->Add(this->label115, 0, 0);
			this->tableLayoutPanel85->Location = System::Drawing::Point(21, 5);
			this->tableLayoutPanel85->Name = L"tableLayoutPanel85";
			this->tableLayoutPanel85->RowCount = 1;
			this->tableLayoutPanel85->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel85->Size = System::Drawing::Size(279, 27);
			this->tableLayoutPanel85->TabIndex = 25;
			// 
			// RecordingFrameRateNumericUpDown
			// 
			this->RecordingFrameRateNumericUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->RecordingFrameRateNumericUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->RecordingFrameRateNumericUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->RecordingFrameRateNumericUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->RecordingFrameRateNumericUpDown->ForeColor = System::Drawing::Color::White;
			this->RecordingFrameRateNumericUpDown->Location = System::Drawing::Point(185, 4);
			this->RecordingFrameRateNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
			this->RecordingFrameRateNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->RecordingFrameRateNumericUpDown->Name = L"RecordingFrameRateNumericUpDown";
			this->RecordingFrameRateNumericUpDown->Size = System::Drawing::Size(90, 20);
			this->RecordingFrameRateNumericUpDown->TabIndex = 20;
			this->RecordingFrameRateNumericUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->RecordingFrameRateNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
			// 
			// label115
			// 
			this->label115->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label115->AutoSize = true;
			this->label115->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label115->ForeColor = System::Drawing::Color::White;
			this->label115->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label115->Location = System::Drawing::Point(10, 6);
			this->label115->Name = L"label115";
			this->label115->Size = System::Drawing::Size(162, 15);
			this->label115->TabIndex = 28;
			this->label115->Text = L"Video Capturing Framerate:";
			this->label115->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label114
			// 
			this->label114->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label114->AutoSize = true;
			this->label114->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label114->ForeColor = System::Drawing::Color::White;
			this->label114->Location = System::Drawing::Point(306, 11);
			this->label114->Name = L"label114";
			this->label114->Size = System::Drawing::Size(392, 15);
			this->label114->TabIndex = 24;
			this->label114->Text = L"Sets The Number Of Captured Video Frames In Hz (Frames Per Sec).";
			this->label114->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel70
			// 
			this->tableLayoutPanel70->ColumnCount = 4;
			this->tableLayoutPanel70->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel70->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel70->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel70->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel70->Controls->Add(this->label86, 3, 1);
			this->tableLayoutPanel70->Controls->Add(this->SaveRawAnalysisRecordingButton, 3, 0);
			this->tableLayoutPanel70->Controls->Add(this->label85, 0, 1);
			this->tableLayoutPanel70->Controls->Add(this->ChangeRecordingDefaultPathButton, 0, 0);
			this->tableLayoutPanel70->Controls->Add(this->label78, 2, 1);
			this->tableLayoutPanel70->Controls->Add(this->UseWinSnippingToolButton, 1, 0);
			this->tableLayoutPanel70->Controls->Add(this->UseWin11ScreenRecordToolButton, 2, 0);
			this->tableLayoutPanel70->Controls->Add(this->label62, 1, 1);
			this->tableLayoutPanel70->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel70->Location = System::Drawing::Point(0, 52);
			this->tableLayoutPanel70->Margin = System::Windows::Forms::Padding(0, 15, 0, 0);
			this->tableLayoutPanel70->Name = L"tableLayoutPanel70";
			this->tableLayoutPanel70->RowCount = 2;
			this->tableLayoutPanel70->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel70->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				46)));
			this->tableLayoutPanel70->Size = System::Drawing::Size(1187, 258);
			this->tableLayoutPanel70->TabIndex = 26;
			// 
			// label86
			// 
			this->label86->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label86->AutoSize = true;
			this->label86->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label86->ForeColor = System::Drawing::Color::White;
			this->label86->Location = System::Drawing::Point(933, 220);
			this->label86->Name = L"label86";
			this->label86->Size = System::Drawing::Size(209, 30);
			this->label86->TabIndex = 27;
			this->label86->Text = L"Save Raw Data File Recording.\r\nFor Post-Analysis Of Recorded Data";
			this->label86->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// SaveRawAnalysisRecordingButton
			// 
			this->SaveRawAnalysisRecordingButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SaveRawAnalysisRecordingButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SaveRawAnalysisRecordingButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->SaveRawAnalysisRecordingButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SaveRawAnalysisRecordingButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->SaveRawAnalysisRecordingButton->ForeColor = System::Drawing::Color::White;
			this->SaveRawAnalysisRecordingButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SaveRawAnalysisRecordingButton.Image")));
			this->SaveRawAnalysisRecordingButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->SaveRawAnalysisRecordingButton->Location = System::Drawing::Point(903, 15);
			this->SaveRawAnalysisRecordingButton->Margin = System::Windows::Forms::Padding(15);
			this->SaveRawAnalysisRecordingButton->Name = L"SaveRawAnalysisRecordingButton";
			this->SaveRawAnalysisRecordingButton->Padding = System::Windows::Forms::Padding(3);
			this->SaveRawAnalysisRecordingButton->Size = System::Drawing::Size(269, 182);
			this->SaveRawAnalysisRecordingButton->TabIndex = 27;
			this->SaveRawAnalysisRecordingButton->Tag = L"1";
			this->SaveRawAnalysisRecordingButton->UseVisualStyleBackColor = false;
			this->SaveRawAnalysisRecordingButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::SaveRawAnalysisRecordingButton_Click);
			// 
			// label85
			// 
			this->label85->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label85->AutoSize = true;
			this->label85->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label85->ForeColor = System::Drawing::Color::White;
			this->label85->Location = System::Drawing::Point(40, 220);
			this->label85->Name = L"label85";
			this->label85->Size = System::Drawing::Size(216, 30);
			this->label85->TabIndex = 28;
			this->label85->Text = L"Press The Button, To Set The Default \r\nRecording Save File Path.";
			this->label85->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ChangeRecordingDefaultPathButton
			// 
			this->ChangeRecordingDefaultPathButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ChangeRecordingDefaultPathButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ChangeRecordingDefaultPathButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ChangeRecordingDefaultPathButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ChangeRecordingDefaultPathButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ChangeRecordingDefaultPathButton->ForeColor = System::Drawing::Color::White;
			this->ChangeRecordingDefaultPathButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ChangeRecordingDefaultPathButton.Image")));
			this->ChangeRecordingDefaultPathButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ChangeRecordingDefaultPathButton->Location = System::Drawing::Point(15, 15);
			this->ChangeRecordingDefaultPathButton->Margin = System::Windows::Forms::Padding(15);
			this->ChangeRecordingDefaultPathButton->Name = L"ChangeRecordingDefaultPathButton";
			this->ChangeRecordingDefaultPathButton->Padding = System::Windows::Forms::Padding(3);
			this->ChangeRecordingDefaultPathButton->Size = System::Drawing::Size(266, 182);
			this->ChangeRecordingDefaultPathButton->TabIndex = 27;
			this->ChangeRecordingDefaultPathButton->UseVisualStyleBackColor = false;
			this->ChangeRecordingDefaultPathButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::ChangeRecordingDefaultPathButton_Click);
			// 
			// label78
			// 
			this->label78->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label78->AutoSize = true;
			this->label78->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label78->ForeColor = System::Drawing::Color::White;
			this->label78->Location = System::Drawing::Point(624, 220);
			this->label78->Name = L"label78";
			this->label78->Size = System::Drawing::Size(231, 30);
			this->label78->TabIndex = 25;
			this->label78->Text = L"Use Native Windows Snipping Tool\r\nFor Screen Capturing And Screen Snips";
			this->label78->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// UseWinSnippingToolButton
			// 
			this->UseWinSnippingToolButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->UseWinSnippingToolButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->UseWinSnippingToolButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->UseWinSnippingToolButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->UseWinSnippingToolButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->UseWinSnippingToolButton->ForeColor = System::Drawing::Color::White;
			this->UseWinSnippingToolButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UseWinSnippingToolButton.Image")));
			this->UseWinSnippingToolButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->UseWinSnippingToolButton->Location = System::Drawing::Point(311, 15);
			this->UseWinSnippingToolButton->Margin = System::Windows::Forms::Padding(15);
			this->UseWinSnippingToolButton->Name = L"UseWinSnippingToolButton";
			this->UseWinSnippingToolButton->Padding = System::Windows::Forms::Padding(3);
			this->UseWinSnippingToolButton->Size = System::Drawing::Size(266, 182);
			this->UseWinSnippingToolButton->TabIndex = 20;
			this->UseWinSnippingToolButton->Tag = L"0";
			this->UseWinSnippingToolButton->UseVisualStyleBackColor = false;
			this->UseWinSnippingToolButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::UseWinSnippingToolButton_Click);
			// 
			// UseWin11ScreenRecordToolButton
			// 
			this->UseWin11ScreenRecordToolButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->UseWin11ScreenRecordToolButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->UseWin11ScreenRecordToolButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->UseWin11ScreenRecordToolButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->UseWin11ScreenRecordToolButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->UseWin11ScreenRecordToolButton->ForeColor = System::Drawing::Color::White;
			this->UseWin11ScreenRecordToolButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UseWin11ScreenRecordToolButton.Image")));
			this->UseWin11ScreenRecordToolButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->UseWin11ScreenRecordToolButton->Location = System::Drawing::Point(607, 15);
			this->UseWin11ScreenRecordToolButton->Margin = System::Windows::Forms::Padding(15);
			this->UseWin11ScreenRecordToolButton->Name = L"UseWin11ScreenRecordToolButton";
			this->UseWin11ScreenRecordToolButton->Padding = System::Windows::Forms::Padding(3);
			this->UseWin11ScreenRecordToolButton->Size = System::Drawing::Size(266, 182);
			this->UseWin11ScreenRecordToolButton->TabIndex = 21;
			this->UseWin11ScreenRecordToolButton->Tag = L"1";
			this->UseWin11ScreenRecordToolButton->UseVisualStyleBackColor = false;
			this->UseWin11ScreenRecordToolButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::UseWinSnippingToolButton_Click);
			// 
			// label62
			// 
			this->label62->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label62->AutoSize = true;
			this->label62->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label62->ForeColor = System::Drawing::Color::White;
			this->label62->Location = System::Drawing::Point(353, 220);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(181, 30);
			this->label62->TabIndex = 24;
			this->label62->Text = L"Use Native Windows Screen\r\nCapturing Tool For WIndows 11";
			this->label62->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DefaultRecordingSavePathString
			// 
			this->DefaultRecordingSavePathString->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->DefaultRecordingSavePathString->AutoSize = true;
			this->DefaultRecordingSavePathString->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->DefaultRecordingSavePathString->ForeColor = System::Drawing::Color::Cyan;
			this->DefaultRecordingSavePathString->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->DefaultRecordingSavePathString->Location = System::Drawing::Point(15, 21);
			this->DefaultRecordingSavePathString->Margin = System::Windows::Forms::Padding(15, 0, 3, 0);
			this->DefaultRecordingSavePathString->Name = L"DefaultRecordingSavePathString";
			this->DefaultRecordingSavePathString->Size = System::Drawing::Size(165, 16);
			this->DefaultRecordingSavePathString->TabIndex = 17;
			this->DefaultRecordingSavePathString->Text = L"Default Save File Path:";
			this->DefaultRecordingSavePathString->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// VideoRecordingMenuButton
			// 
			this->VideoRecordingMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->VideoRecordingMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->VideoRecordingMenuButton->Enabled = false;
			this->VideoRecordingMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->VideoRecordingMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->VideoRecordingMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->VideoRecordingMenuButton->ForeColor = System::Drawing::Color::White;
			this->VideoRecordingMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"VideoRecordingMenuButton.Image")));
			this->VideoRecordingMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->VideoRecordingMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->VideoRecordingMenuButton->Location = System::Drawing::Point(10, 1426);
			this->VideoRecordingMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->VideoRecordingMenuButton->Name = L"VideoRecordingMenuButton";
			this->VideoRecordingMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->VideoRecordingMenuButton->Size = System::Drawing::Size(1370, 54);
			this->VideoRecordingMenuButton->TabIndex = 38;
			this->VideoRecordingMenuButton->Text = L"   Screen Capturing Tool And Video Recording Settings:";
			this->VideoRecordingMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->VideoRecordingMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->VideoRecordingMenuButton->UseVisualStyleBackColor = false;
			this->VideoRecordingMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::VideoRecordingMenuButton_Click);
			// 
			// SnapshotConfigSubMenuPanel
			// 
			this->SnapshotConfigSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->SnapshotConfigSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SnapshotConfigSubMenuPanel->Controls->Add(this->tableLayoutPanel32);
			this->SnapshotConfigSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->SnapshotConfigSubMenuPanel->Location = System::Drawing::Point(10, 1055);
			this->SnapshotConfigSubMenuPanel->Name = L"SnapshotConfigSubMenuPanel";
			this->SnapshotConfigSubMenuPanel->Size = System::Drawing::Size(1370, 371);
			this->SnapshotConfigSubMenuPanel->TabIndex = 37;
			this->SnapshotConfigSubMenuPanel->Visible = false;
			// 
			// tableLayoutPanel32
			// 
			this->tableLayoutPanel32->ColumnCount = 2;
			this->tableLayoutPanel32->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				889)));
			this->tableLayoutPanel32->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				658)));
			this->tableLayoutPanel32->Controls->Add(this->tableLayoutPanel1, 0, 0);
			this->tableLayoutPanel32->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel32->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel32->Name = L"tableLayoutPanel32";
			this->tableLayoutPanel32->RowCount = 1;
			this->tableLayoutPanel32->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				371)));
			this->tableLayoutPanel32->Size = System::Drawing::Size(1368, 369);
			this->tableLayoutPanel32->TabIndex = 21;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel72, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->DefaultSnapshotSavePathString, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 34)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 283)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(889, 371);
			this->tableLayoutPanel1->TabIndex = 20;
			// 
			// tableLayoutPanel72
			// 
			this->tableLayoutPanel72->ColumnCount = 2;
			this->tableLayoutPanel72->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				28.34646F)));
			this->tableLayoutPanel72->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				71.65354F)));
			this->tableLayoutPanel72->Controls->Add(this->label91, 1, 0);
			this->tableLayoutPanel72->Controls->Add(this->FullFrameTempDataCSVDelimiterCombiBox, 0, 0);
			this->tableLayoutPanel72->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel72->Location = System::Drawing::Point(0, 317);
			this->tableLayoutPanel72->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			this->tableLayoutPanel72->Name = L"tableLayoutPanel72";
			this->tableLayoutPanel72->RowCount = 1;
			this->tableLayoutPanel72->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel72->Size = System::Drawing::Size(889, 39);
			this->tableLayoutPanel72->TabIndex = 23;
			// 
			// label91
			// 
			this->label91->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label91->AutoSize = true;
			this->label91->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label91->ForeColor = System::Drawing::Color::White;
			this->label91->Location = System::Drawing::Point(260, 12);
			this->label91->Name = L"label91";
			this->label91->Size = System::Drawing::Size(620, 15);
			this->label91->TabIndex = 24;
			this->label91->Text = L"Select The Desired Full Frame Temperature Data CSV Delimiter. This Setting Will B"
				L"e Saved For Every Session.";
			this->label91->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FullFrameTempDataCSVDelimiterCombiBox
			// 
			this->FullFrameTempDataCSVDelimiterCombiBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->FullFrameTempDataCSVDelimiterCombiBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->FullFrameTempDataCSVDelimiterCombiBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FullFrameTempDataCSVDelimiterCombiBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->FullFrameTempDataCSVDelimiterCombiBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->FullFrameTempDataCSVDelimiterCombiBox->ForeColor = System::Drawing::Color::White;
			this->FullFrameTempDataCSVDelimiterCombiBox->FormattingEnabled = true;
			this->FullFrameTempDataCSVDelimiterCombiBox->Location = System::Drawing::Point(20, 7);
			this->FullFrameTempDataCSVDelimiterCombiBox->Margin = System::Windows::Forms::Padding(20, 5, 0, 5);
			this->FullFrameTempDataCSVDelimiterCombiBox->Name = L"FullFrameTempDataCSVDelimiterCombiBox";
			this->FullFrameTempDataCSVDelimiterCombiBox->Size = System::Drawing::Size(232, 24);
			this->FullFrameTempDataCSVDelimiterCombiBox->TabIndex = 22;
			this->FullFrameTempDataCSVDelimiterCombiBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::FullFrameTempDataCSVDelimiterCombiBox_SelectedIndexChanged);
			// 
			// DefaultSnapshotSavePathString
			// 
			this->DefaultSnapshotSavePathString->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->DefaultSnapshotSavePathString->AutoSize = true;
			this->DefaultSnapshotSavePathString->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->DefaultSnapshotSavePathString->ForeColor = System::Drawing::Color::Cyan;
			this->DefaultSnapshotSavePathString->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->DefaultSnapshotSavePathString->Location = System::Drawing::Point(15, 18);
			this->DefaultSnapshotSavePathString->Margin = System::Windows::Forms::Padding(15, 0, 3, 0);
			this->DefaultSnapshotSavePathString->Name = L"DefaultSnapshotSavePathString";
			this->DefaultSnapshotSavePathString->Size = System::Drawing::Size(165, 16);
			this->DefaultSnapshotSavePathString->TabIndex = 16;
			this->DefaultSnapshotSavePathString->Text = L"Default Save File Path:";
			this->DefaultSnapshotSavePathString->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 3;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel2->Controls->Add(this->label37, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->ChangeSnapDefaultPathButton, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->IncludeColorbarSnapButton, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->label36, 2, 1);
			this->tableLayoutPanel2->Controls->Add(this->SaveRawSensorSnapButton, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->label4, 0, 1);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(0, 49);
			this->tableLayoutPanel2->Margin = System::Windows::Forms::Padding(0, 15, 0, 0);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 49)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(889, 268);
			this->tableLayoutPanel2->TabIndex = 17;
			// 
			// label37
			// 
			this->label37->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label37->ForeColor = System::Drawing::Color::White;
			this->label37->Location = System::Drawing::Point(323, 228);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(242, 30);
			this->label37->TabIndex = 24;
			this->label37->Text = L"Press The Button, To Toggle The Snapthot\r\nOf the Entire Live View Stream Panel\r\n";
			this->label37->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ChangeSnapDefaultPathButton
			// 
			this->ChangeSnapDefaultPathButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ChangeSnapDefaultPathButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ChangeSnapDefaultPathButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ChangeSnapDefaultPathButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ChangeSnapDefaultPathButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ChangeSnapDefaultPathButton->ForeColor = System::Drawing::Color::White;
			this->ChangeSnapDefaultPathButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ChangeSnapDefaultPathButton.Image")));
			this->ChangeSnapDefaultPathButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ChangeSnapDefaultPathButton->Location = System::Drawing::Point(15, 15);
			this->ChangeSnapDefaultPathButton->Margin = System::Windows::Forms::Padding(15);
			this->ChangeSnapDefaultPathButton->Name = L"ChangeSnapDefaultPathButton";
			this->ChangeSnapDefaultPathButton->Padding = System::Windows::Forms::Padding(3);
			this->ChangeSnapDefaultPathButton->Size = System::Drawing::Size(266, 189);
			this->ChangeSnapDefaultPathButton->TabIndex = 17;
			this->ChangeSnapDefaultPathButton->UseVisualStyleBackColor = false;
			this->ChangeSnapDefaultPathButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::ChangeSnapDefaultPathButton_Click);
			// 
			// IncludeColorbarSnapButton
			// 
			this->IncludeColorbarSnapButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->IncludeColorbarSnapButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->IncludeColorbarSnapButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->IncludeColorbarSnapButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->IncludeColorbarSnapButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->IncludeColorbarSnapButton->ForeColor = System::Drawing::Color::White;
			this->IncludeColorbarSnapButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"IncludeColorbarSnapButton.Image")));
			this->IncludeColorbarSnapButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->IncludeColorbarSnapButton->Location = System::Drawing::Point(311, 15);
			this->IncludeColorbarSnapButton->Margin = System::Windows::Forms::Padding(15);
			this->IncludeColorbarSnapButton->Name = L"IncludeColorbarSnapButton";
			this->IncludeColorbarSnapButton->Padding = System::Windows::Forms::Padding(3);
			this->IncludeColorbarSnapButton->Size = System::Drawing::Size(266, 189);
			this->IncludeColorbarSnapButton->TabIndex = 18;
			this->IncludeColorbarSnapButton->UseVisualStyleBackColor = false;
			this->IncludeColorbarSnapButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::IncludeColorbarSnapButton_Click);
			// 
			// label36
			// 
			this->label36->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label36->ForeColor = System::Drawing::Color::White;
			this->label36->Location = System::Drawing::Point(636, 228);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(208, 30);
			this->label36->TabIndex = 24;
			this->label36->Text = L"Press The Button, To Toggle Saving \r\nOf A RAW Image Sensor SnapShot.";
			this->label36->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// SaveRawSensorSnapButton
			// 
			this->SaveRawSensorSnapButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->SaveRawSensorSnapButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SaveRawSensorSnapButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			this->SaveRawSensorSnapButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SaveRawSensorSnapButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->SaveRawSensorSnapButton->ForeColor = System::Drawing::Color::White;
			this->SaveRawSensorSnapButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SaveRawSensorSnapButton.Image")));
			this->SaveRawSensorSnapButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->SaveRawSensorSnapButton->Location = System::Drawing::Point(607, 15);
			this->SaveRawSensorSnapButton->Margin = System::Windows::Forms::Padding(15);
			this->SaveRawSensorSnapButton->Name = L"SaveRawSensorSnapButton";
			this->SaveRawSensorSnapButton->Padding = System::Windows::Forms::Padding(3);
			this->SaveRawSensorSnapButton->Size = System::Drawing::Size(267, 189);
			this->SaveRawSensorSnapButton->TabIndex = 19;
			this->SaveRawSensorSnapButton->UseVisualStyleBackColor = false;
			this->SaveRawSensorSnapButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::SaveRawSensorSnapButton_Click);
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(11, 228);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(274, 30);
			this->label4->TabIndex = 23;
			this->label4->Text = L"Press The Button, To Set The Default SnapShot \r\nAnd Temperature Data CSV Save Fil"
				L"e Path.";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// SnapshotConfigMenuButton
			// 
			this->SnapshotConfigMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SnapshotConfigMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->SnapshotConfigMenuButton->Enabled = false;
			this->SnapshotConfigMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SnapshotConfigMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SnapshotConfigMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->SnapshotConfigMenuButton->ForeColor = System::Drawing::Color::White;
			this->SnapshotConfigMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SnapshotConfigMenuButton.Image")));
			this->SnapshotConfigMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->SnapshotConfigMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->SnapshotConfigMenuButton->Location = System::Drawing::Point(10, 1001);
			this->SnapshotConfigMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->SnapshotConfigMenuButton->Name = L"SnapshotConfigMenuButton";
			this->SnapshotConfigMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->SnapshotConfigMenuButton->Size = System::Drawing::Size(1370, 54);
			this->SnapshotConfigMenuButton->TabIndex = 36;
			this->SnapshotConfigMenuButton->Text = L"   Full Frame Temperature Data CSV And Snapshot Settings:";
			this->SnapshotConfigMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->SnapshotConfigMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->SnapshotConfigMenuButton->UseVisualStyleBackColor = false;
			this->SnapshotConfigMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::SnapshotConfigMenuButton_Click);
			// 
			// AutoCalSubMenuPanel
			// 
			this->AutoCalSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->AutoCalSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->AutoCalSubMenuPanel->Controls->Add(this->tableLayoutPanel31);
			this->AutoCalSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->AutoCalSubMenuPanel->Location = System::Drawing::Point(10, 713);
			this->AutoCalSubMenuPanel->Name = L"AutoCalSubMenuPanel";
			this->AutoCalSubMenuPanel->Size = System::Drawing::Size(1370, 288);
			this->AutoCalSubMenuPanel->TabIndex = 35;
			this->AutoCalSubMenuPanel->Visible = false;
			// 
			// tableLayoutPanel31
			// 
			this->tableLayoutPanel31->ColumnCount = 2;
			this->tableLayoutPanel31->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				1007)));
			this->tableLayoutPanel31->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel31->Controls->Add(this->tableLayoutPanel68, 0, 0);
			this->tableLayoutPanel31->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel31->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel31->Name = L"tableLayoutPanel31";
			this->tableLayoutPanel31->RowCount = 1;
			this->tableLayoutPanel31->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel31->Size = System::Drawing::Size(1368, 286);
			this->tableLayoutPanel31->TabIndex = 21;
			// 
			// tableLayoutPanel68
			// 
			this->tableLayoutPanel68->ColumnCount = 3;
			this->tableLayoutPanel68->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				49.92722F)));
			this->tableLayoutPanel68->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50.07278F)));
			this->tableLayoutPanel68->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				320)));
			this->tableLayoutPanel68->Controls->Add(this->tableLayoutPanel73, 0, 0);
			this->tableLayoutPanel68->Controls->Add(this->tableLayoutPanel62, 0, 0);
			this->tableLayoutPanel68->Controls->Add(this->tableLayoutPanel69, 2, 0);
			this->tableLayoutPanel68->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel68->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel68->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel68->Name = L"tableLayoutPanel68";
			this->tableLayoutPanel68->RowCount = 1;
			this->tableLayoutPanel68->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel68->Size = System::Drawing::Size(1007, 286);
			this->tableLayoutPanel68->TabIndex = 1;
			// 
			// tableLayoutPanel73
			// 
			this->tableLayoutPanel73->ColumnCount = 1;
			this->tableLayoutPanel73->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel73->Controls->Add(this->label92, 0, 1);
			this->tableLayoutPanel73->Controls->Add(this->tableLayoutPanel74, 0, 2);
			this->tableLayoutPanel73->Controls->Add(this->SensorDriftCalButton, 0, 0);
			this->tableLayoutPanel73->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel73->Location = System::Drawing::Point(346, 3);
			this->tableLayoutPanel73->Name = L"tableLayoutPanel73";
			this->tableLayoutPanel73->RowCount = 3;
			this->tableLayoutPanel73->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 74.46809F)));
			this->tableLayoutPanel73->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.6383F)));
			this->tableLayoutPanel73->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.89362F)));
			this->tableLayoutPanel73->Size = System::Drawing::Size(338, 280);
			this->tableLayoutPanel73->TabIndex = 2;
			// 
			// label92
			// 
			this->label92->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label92->AutoSize = true;
			this->label92->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label92->ForeColor = System::Drawing::Color::White;
			this->label92->Location = System::Drawing::Point(17, 208);
			this->label92->Name = L"label92";
			this->label92->Size = System::Drawing::Size(304, 29);
			this->label92->TabIndex = 22;
			this->label92->Text = L"Press The Button To Enable Thermal Camera Sensor\r\nDrift Based Calibration.\r\n";
			this->label92->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel74
			// 
			this->tableLayoutPanel74->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel74->ColumnCount = 2;
			this->tableLayoutPanel74->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				65.38461F)));
			this->tableLayoutPanel74->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				34.61538F)));
			this->tableLayoutPanel74->Controls->Add(this->SensorDriftCalUpDown, 1, 0);
			this->tableLayoutPanel74->Controls->Add(this->MaxTempDriftSetPountLabel, 0, 0);
			this->tableLayoutPanel74->Location = System::Drawing::Point(15, 245);
			this->tableLayoutPanel74->Name = L"tableLayoutPanel74";
			this->tableLayoutPanel74->RowCount = 1;
			this->tableLayoutPanel74->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel74->Size = System::Drawing::Size(308, 27);
			this->tableLayoutPanel74->TabIndex = 20;
			// 
			// SensorDriftCalUpDown
			// 
			this->SensorDriftCalUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SensorDriftCalUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->SensorDriftCalUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->SensorDriftCalUpDown->DecimalPlaces = 3;
			this->SensorDriftCalUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->SensorDriftCalUpDown->ForeColor = System::Drawing::Color::White;
			this->SensorDriftCalUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->SensorDriftCalUpDown->Location = System::Drawing::Point(209, 3);
			this->SensorDriftCalUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->SensorDriftCalUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 131072 });
			this->SensorDriftCalUpDown->Name = L"SensorDriftCalUpDown";
			this->SensorDriftCalUpDown->Size = System::Drawing::Size(91, 20);
			this->SensorDriftCalUpDown->TabIndex = 20;
			this->SensorDriftCalUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->SensorDriftCalUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->SensorDriftCalUpDown->ValueChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::SensorDriftCalUpDown_ValueChanged);
			// 
			// MaxTempDriftSetPountLabel
			// 
			this->MaxTempDriftSetPountLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->MaxTempDriftSetPountLabel->AutoSize = true;
			this->MaxTempDriftSetPountLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->MaxTempDriftSetPountLabel->ForeColor = System::Drawing::Color::White;
			this->MaxTempDriftSetPountLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->MaxTempDriftSetPountLabel->Location = System::Drawing::Point(4, 6);
			this->MaxTempDriftSetPountLabel->Name = L"MaxTempDriftSetPountLabel";
			this->MaxTempDriftSetPountLabel->Size = System::Drawing::Size(193, 15);
			this->MaxTempDriftSetPountLabel->TabIndex = 28;
			this->MaxTempDriftSetPountLabel->Text = L"Maximum Drift Temperature [°C]:";
			this->MaxTempDriftSetPountLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// SensorDriftCalButton
			// 
			this->SensorDriftCalButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->SensorDriftCalButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SensorDriftCalButton->Enabled = false;
			this->SensorDriftCalButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SensorDriftCalButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SensorDriftCalButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->SensorDriftCalButton->ForeColor = System::Drawing::Color::White;
			this->SensorDriftCalButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SensorDriftCalButton.Image")));
			this->SensorDriftCalButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->SensorDriftCalButton->Location = System::Drawing::Point(15, 15);
			this->SensorDriftCalButton->Margin = System::Windows::Forms::Padding(15);
			this->SensorDriftCalButton->Name = L"SensorDriftCalButton";
			this->SensorDriftCalButton->Padding = System::Windows::Forms::Padding(3);
			this->SensorDriftCalButton->Size = System::Drawing::Size(308, 178);
			this->SensorDriftCalButton->TabIndex = 19;
			this->SensorDriftCalButton->UseVisualStyleBackColor = false;
			this->SensorDriftCalButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::SensorDriftCalButton_Click);
			// 
			// tableLayoutPanel62
			// 
			this->tableLayoutPanel62->ColumnCount = 1;
			this->tableLayoutPanel62->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel62->Controls->Add(this->label38, 0, 1);
			this->tableLayoutPanel62->Controls->Add(this->tableLayoutPanel4, 0, 2);
			this->tableLayoutPanel62->Controls->Add(this->AutoShutterCalButton, 0, 0);
			this->tableLayoutPanel62->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel62->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel62->Name = L"tableLayoutPanel62";
			this->tableLayoutPanel62->RowCount = 3;
			this->tableLayoutPanel62->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 74.46809F)));
			this->tableLayoutPanel62->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10.6383F)));
			this->tableLayoutPanel62->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.89362F)));
			this->tableLayoutPanel62->Size = System::Drawing::Size(337, 280);
			this->tableLayoutPanel62->TabIndex = 0;
			// 
			// label38
			// 
			this->label38->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label38->AutoSize = true;
			this->label38->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label38->ForeColor = System::Drawing::Color::White;
			this->label38->Location = System::Drawing::Point(7, 215);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(323, 15);
			this->label38->TabIndex = 22;
			this->label38->Text = L"Press The Button To Enable periodic Shutter Calibration.\r\n";
			this->label38->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				65.38461F)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				34.61538F)));
			this->tableLayoutPanel4->Controls->Add(this->AutoCalPeriodUpDown, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->label3, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(29, 245);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(279, 27);
			this->tableLayoutPanel4->TabIndex = 20;
			// 
			// AutoCalPeriodUpDown
			// 
			this->AutoCalPeriodUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->AutoCalPeriodUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->AutoCalPeriodUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->AutoCalPeriodUpDown->DecimalPlaces = 1;
			this->AutoCalPeriodUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->AutoCalPeriodUpDown->ForeColor = System::Drawing::Color::White;
			this->AutoCalPeriodUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->AutoCalPeriodUpDown->Location = System::Drawing::Point(185, 3);
			this->AutoCalPeriodUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 600, 0, 0, 0 });
			this->AutoCalPeriodUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->AutoCalPeriodUpDown->Name = L"AutoCalPeriodUpDown";
			this->AutoCalPeriodUpDown->Size = System::Drawing::Size(91, 20);
			this->AutoCalPeriodUpDown->TabIndex = 20;
			this->AutoCalPeriodUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->AutoCalPeriodUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label3->Location = System::Drawing::Point(4, 6);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(173, 15);
			this->label3->TabIndex = 28;
			this->label3->Text = L"Auto Calibration Period [Sec]:";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// AutoShutterCalButton
			// 
			this->AutoShutterCalButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->AutoShutterCalButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->AutoShutterCalButton->Enabled = false;
			this->AutoShutterCalButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AutoShutterCalButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AutoShutterCalButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->AutoShutterCalButton->ForeColor = System::Drawing::Color::White;
			this->AutoShutterCalButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AutoShutterCalButton.Image")));
			this->AutoShutterCalButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->AutoShutterCalButton->Location = System::Drawing::Point(15, 15);
			this->AutoShutterCalButton->Margin = System::Windows::Forms::Padding(15);
			this->AutoShutterCalButton->Name = L"AutoShutterCalButton";
			this->AutoShutterCalButton->Padding = System::Windows::Forms::Padding(3);
			this->AutoShutterCalButton->Size = System::Drawing::Size(307, 178);
			this->AutoShutterCalButton->TabIndex = 19;
			this->AutoShutterCalButton->UseVisualStyleBackColor = false;
			this->AutoShutterCalButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::AutoShutterCalButton_Click);
			// 
			// tableLayoutPanel69
			// 
			this->tableLayoutPanel69->ColumnCount = 1;
			this->tableLayoutPanel69->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel69->Controls->Add(this->CameraShutterTempLabel, 0, 3);
			this->tableLayoutPanel69->Controls->Add(this->CameraCoreTempLabel, 0, 2);
			this->tableLayoutPanel69->Controls->Add(this->ReadIntCameraTempsButton, 0, 0);
			this->tableLayoutPanel69->Controls->Add(this->CameraDetectorTempLabel, 0, 1);
			this->tableLayoutPanel69->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel69->Location = System::Drawing::Point(690, 3);
			this->tableLayoutPanel69->Name = L"tableLayoutPanel69";
			this->tableLayoutPanel69->RowCount = 4;
			this->tableLayoutPanel69->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				192)));
			this->tableLayoutPanel69->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel69->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel69->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel69->Size = System::Drawing::Size(314, 280);
			this->tableLayoutPanel69->TabIndex = 1;
			// 
			// CameraShutterTempLabel
			// 
			this->CameraShutterTempLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->CameraShutterTempLabel->AutoSize = true;
			this->CameraShutterTempLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->CameraShutterTempLabel->ForeColor = System::Drawing::Color::White;
			this->CameraShutterTempLabel->Location = System::Drawing::Point(74, 250);
			this->CameraShutterTempLabel->Name = L"CameraShutterTempLabel";
			this->CameraShutterTempLabel->Size = System::Drawing::Size(165, 19);
			this->CameraShutterTempLabel->TabIndex = 23;
			this->CameraShutterTempLabel->Text = L"Camera Shutter: N/A\r\n";
			this->CameraShutterTempLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CameraCoreTempLabel
			// 
			this->CameraCoreTempLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->CameraCoreTempLabel->AutoSize = true;
			this->CameraCoreTempLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->CameraCoreTempLabel->ForeColor = System::Drawing::Color::White;
			this->CameraCoreTempLabel->Location = System::Drawing::Point(84, 221);
			this->CameraCoreTempLabel->Name = L"CameraCoreTempLabel";
			this->CameraCoreTempLabel->Size = System::Drawing::Size(146, 19);
			this->CameraCoreTempLabel->TabIndex = 23;
			this->CameraCoreTempLabel->Text = L"Camera Core: N/A";
			this->CameraCoreTempLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ReadIntCameraTempsButton
			// 
			this->ReadIntCameraTempsButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ReadIntCameraTempsButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ReadIntCameraTempsButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ReadIntCameraTempsButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ReadIntCameraTempsButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ReadIntCameraTempsButton->ForeColor = System::Drawing::Color::White;
			this->ReadIntCameraTempsButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ReadIntCameraTempsButton.Image")));
			this->ReadIntCameraTempsButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ReadIntCameraTempsButton->Location = System::Drawing::Point(15, 15);
			this->ReadIntCameraTempsButton->Margin = System::Windows::Forms::Padding(15);
			this->ReadIntCameraTempsButton->Name = L"ReadIntCameraTempsButton";
			this->ReadIntCameraTempsButton->Padding = System::Windows::Forms::Padding(3);
			this->ReadIntCameraTempsButton->Size = System::Drawing::Size(284, 162);
			this->ReadIntCameraTempsButton->TabIndex = 20;
			this->ReadIntCameraTempsButton->Text = L"Read Internal Camera\r\nTemperatures";
			this->ReadIntCameraTempsButton->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->ReadIntCameraTempsButton->UseVisualStyleBackColor = false;
			this->ReadIntCameraTempsButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::ReadIntCameraTempsButton_Click);
			// 
			// CameraDetectorTempLabel
			// 
			this->CameraDetectorTempLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->CameraDetectorTempLabel->AutoSize = true;
			this->CameraDetectorTempLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->CameraDetectorTempLabel->ForeColor = System::Drawing::Color::White;
			this->CameraDetectorTempLabel->Location = System::Drawing::Point(70, 192);
			this->CameraDetectorTempLabel->Name = L"CameraDetectorTempLabel";
			this->CameraDetectorTempLabel->Size = System::Drawing::Size(174, 19);
			this->CameraDetectorTempLabel->TabIndex = 23;
			this->CameraDetectorTempLabel->Text = L"Camera Detector: N/A\r\n";
			this->CameraDetectorTempLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// AutoCalMenuButton
			// 
			this->AutoCalMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AutoCalMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->AutoCalMenuButton->Enabled = false;
			this->AutoCalMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->AutoCalMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->AutoCalMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->AutoCalMenuButton->ForeColor = System::Drawing::Color::White;
			this->AutoCalMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AutoCalMenuButton.Image")));
			this->AutoCalMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->AutoCalMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->AutoCalMenuButton->Location = System::Drawing::Point(10, 659);
			this->AutoCalMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->AutoCalMenuButton->Name = L"AutoCalMenuButton";
			this->AutoCalMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->AutoCalMenuButton->Size = System::Drawing::Size(1370, 54);
			this->AutoCalMenuButton->TabIndex = 34;
			this->AutoCalMenuButton->Text = L"   Thermal Camera Calibration Settings:";
			this->AutoCalMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->AutoCalMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->AutoCalMenuButton->UseVisualStyleBackColor = false;
			this->AutoCalMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::AutoCalMenuButton_Click);
			// 
			// CameraConfigSubMenuPanel
			// 
			this->CameraConfigSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->CameraConfigSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->CameraConfigSubMenuPanel->Controls->Add(this->tableLayoutPanel30);
			this->CameraConfigSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->CameraConfigSubMenuPanel->Location = System::Drawing::Point(10, 404);
			this->CameraConfigSubMenuPanel->Name = L"CameraConfigSubMenuPanel";
			this->CameraConfigSubMenuPanel->Size = System::Drawing::Size(1370, 255);
			this->CameraConfigSubMenuPanel->TabIndex = 33;
			this->CameraConfigSubMenuPanel->Visible = false;
			// 
			// tableLayoutPanel30
			// 
			this->tableLayoutPanel30->ColumnCount = 2;
			this->tableLayoutPanel30->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				1170)));
			this->tableLayoutPanel30->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				377)));
			this->tableLayoutPanel30->Controls->Add(this->tableLayoutPanel27, 0, 0);
			this->tableLayoutPanel30->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel30->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel30->Name = L"tableLayoutPanel30";
			this->tableLayoutPanel30->RowCount = 1;
			this->tableLayoutPanel30->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel30->Size = System::Drawing::Size(1368, 253);
			this->tableLayoutPanel30->TabIndex = 31;
			// 
			// tableLayoutPanel27
			// 
			this->tableLayoutPanel27->ColumnCount = 2;
			this->tableLayoutPanel27->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				419)));
			this->tableLayoutPanel27->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				751)));
			this->tableLayoutPanel27->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel27->Controls->Add(this->tableLayoutPanel28, 1, 0);
			this->tableLayoutPanel27->Controls->Add(this->tableLayoutPanel29, 0, 0);
			this->tableLayoutPanel27->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel27->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel27->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel27->Name = L"tableLayoutPanel27";
			this->tableLayoutPanel27->RowCount = 1;
			this->tableLayoutPanel27->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel27->Size = System::Drawing::Size(1170, 253);
			this->tableLayoutPanel27->TabIndex = 30;
			// 
			// tableLayoutPanel28
			// 
			this->tableLayoutPanel28->ColumnCount = 3;
			this->tableLayoutPanel28->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				32.08054F)));
			this->tableLayoutPanel28->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				32.75168F)));
			this->tableLayoutPanel28->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				35.16779F)));
			this->tableLayoutPanel28->Controls->Add(this->label84, 2, 1);
			this->tableLayoutPanel28->Controls->Add(this->RecoverDefaultCameraSettingsButton, 2, 0);
			this->tableLayoutPanel28->Controls->Add(this->label82, 1, 1);
			this->tableLayoutPanel28->Controls->Add(this->label80, 0, 1);
			this->tableLayoutPanel28->Controls->Add(this->ReadCameraConfigButton, 1, 0);
			this->tableLayoutPanel28->Controls->Add(this->SetCameraConfigButton, 0, 0);
			this->tableLayoutPanel28->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel28->Location = System::Drawing::Point(422, 3);
			this->tableLayoutPanel28->Name = L"tableLayoutPanel28";
			this->tableLayoutPanel28->RowCount = 2;
			this->tableLayoutPanel28->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 84.32204F)));
			this->tableLayoutPanel28->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 15.67797F)));
			this->tableLayoutPanel28->Size = System::Drawing::Size(745, 247);
			this->tableLayoutPanel28->TabIndex = 30;
			// 
			// label84
			// 
			this->label84->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label84->AutoSize = true;
			this->label84->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label84->ForeColor = System::Drawing::Color::White;
			this->label84->Location = System::Drawing::Point(493, 208);
			this->label84->Name = L"label84";
			this->label84->Size = System::Drawing::Size(241, 30);
			this->label84->TabIndex = 32;
			this->label84->Text = L"Press The Button, To Recover The Default\r\nCamera Temperature Setttings";
			this->label84->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// RecoverDefaultCameraSettingsButton
			// 
			this->RecoverDefaultCameraSettingsButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->RecoverDefaultCameraSettingsButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->RecoverDefaultCameraSettingsButton->Enabled = false;
			this->RecoverDefaultCameraSettingsButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->RecoverDefaultCameraSettingsButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RecoverDefaultCameraSettingsButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->RecoverDefaultCameraSettingsButton->ForeColor = System::Drawing::Color::White;
			this->RecoverDefaultCameraSettingsButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"RecoverDefaultCameraSettingsButton.Image")));
			this->RecoverDefaultCameraSettingsButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->RecoverDefaultCameraSettingsButton->Location = System::Drawing::Point(498, 15);
			this->RecoverDefaultCameraSettingsButton->Margin = System::Windows::Forms::Padding(15);
			this->RecoverDefaultCameraSettingsButton->Name = L"RecoverDefaultCameraSettingsButton";
			this->RecoverDefaultCameraSettingsButton->Padding = System::Windows::Forms::Padding(3);
			this->RecoverDefaultCameraSettingsButton->Size = System::Drawing::Size(232, 178);
			this->RecoverDefaultCameraSettingsButton->TabIndex = 31;
			this->RecoverDefaultCameraSettingsButton->UseVisualStyleBackColor = false;
			this->RecoverDefaultCameraSettingsButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::RecoverDefaultCameraSettingsButton_Click);
			// 
			// label82
			// 
			this->label82->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label82->AutoSize = true;
			this->label82->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label82->ForeColor = System::Drawing::Color::White;
			this->label82->Location = System::Drawing::Point(248, 208);
			this->label82->Name = L"label82";
			this->label82->Size = System::Drawing::Size(226, 30);
			this->label82->TabIndex = 27;
			this->label82->Text = L"Press The Button, To Read The Current\r\nCamera Configuration.";
			this->label82->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label80
			// 
			this->label80->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label80->AutoSize = true;
			this->label80->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label80->ForeColor = System::Drawing::Color::White;
			this->label80->Location = System::Drawing::Point(33, 208);
			this->label80->Name = L"label80";
			this->label80->Size = System::Drawing::Size(173, 30);
			this->label80->TabIndex = 26;
			this->label80->Text = L"Press The Button, To Set The \r\nCamera Configuration.";
			this->label80->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ReadCameraConfigButton
			// 
			this->ReadCameraConfigButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ReadCameraConfigButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ReadCameraConfigButton->Enabled = false;
			this->ReadCameraConfigButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ReadCameraConfigButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ReadCameraConfigButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->ReadCameraConfigButton->ForeColor = System::Drawing::Color::White;
			this->ReadCameraConfigButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ReadCameraConfigButton.Image")));
			this->ReadCameraConfigButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ReadCameraConfigButton->Location = System::Drawing::Point(254, 15);
			this->ReadCameraConfigButton->Margin = System::Windows::Forms::Padding(15);
			this->ReadCameraConfigButton->Name = L"ReadCameraConfigButton";
			this->ReadCameraConfigButton->Padding = System::Windows::Forms::Padding(3);
			this->ReadCameraConfigButton->Size = System::Drawing::Size(214, 178);
			this->ReadCameraConfigButton->TabIndex = 16;
			this->ReadCameraConfigButton->UseVisualStyleBackColor = false;
			this->ReadCameraConfigButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::ReadCameraConfigButton_Click);
			// 
			// SetCameraConfigButton
			// 
			this->SetCameraConfigButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->SetCameraConfigButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SetCameraConfigButton->Enabled = false;
			this->SetCameraConfigButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->SetCameraConfigButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->SetCameraConfigButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->SetCameraConfigButton->ForeColor = System::Drawing::Color::White;
			this->SetCameraConfigButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SetCameraConfigButton.Image")));
			this->SetCameraConfigButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->SetCameraConfigButton->Location = System::Drawing::Point(15, 15);
			this->SetCameraConfigButton->Margin = System::Windows::Forms::Padding(15);
			this->SetCameraConfigButton->Name = L"SetCameraConfigButton";
			this->SetCameraConfigButton->Padding = System::Windows::Forms::Padding(3);
			this->SetCameraConfigButton->Size = System::Drawing::Size(209, 178);
			this->SetCameraConfigButton->TabIndex = 25;
			this->SetCameraConfigButton->UseVisualStyleBackColor = false;
			this->SetCameraConfigButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::SetCameraConfigButton_Click);
			// 
			// tableLayoutPanel29
			// 
			this->tableLayoutPanel29->ColumnCount = 1;
			this->tableLayoutPanel29->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel29->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel29->Controls->Add(this->tableLayoutPanel26, 0, 1);
			this->tableLayoutPanel29->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel29->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel29->Name = L"tableLayoutPanel29";
			this->tableLayoutPanel29->RowCount = 2;
			this->tableLayoutPanel29->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel29->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				210)));
			this->tableLayoutPanel29->Size = System::Drawing::Size(413, 247);
			this->tableLayoutPanel29->TabIndex = 31;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(92, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(229, 18);
			this->label2->TabIndex = 27;
			this->label2->Text = L"Thermal Camera Configuration.";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel26
			// 
			this->tableLayoutPanel26->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel26->ColumnCount = 2;
			this->tableLayoutPanel26->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel26->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel26->Controls->Add(this->TempCorrUpDown, 1, 0);
			this->tableLayoutPanel26->Controls->Add(this->ReflectedTempUpDown, 1, 2);
			this->tableLayoutPanel26->Controls->Add(this->TempCorrLabel, 0, 0);
			this->tableLayoutPanel26->Controls->Add(this->DistanceUpDown, 1, 5);
			this->tableLayoutPanel26->Controls->Add(this->DistanceLabel, 0, 5);
			this->tableLayoutPanel26->Controls->Add(this->AmbientTempLabel, 0, 1);
			this->tableLayoutPanel26->Controls->Add(this->EmissivityLabel, 0, 4);
			this->tableLayoutPanel26->Controls->Add(this->HumidityLabel, 0, 3);
			this->tableLayoutPanel26->Controls->Add(this->EmissivityUpDown, 1, 4);
			this->tableLayoutPanel26->Controls->Add(this->AmbientTempUpDown, 1, 1);
			this->tableLayoutPanel26->Controls->Add(this->ReflectedTempLabel, 0, 2);
			this->tableLayoutPanel26->Controls->Add(this->HumidityUpDown, 1, 3);
			this->tableLayoutPanel26->Location = System::Drawing::Point(23, 54);
			this->tableLayoutPanel26->Margin = System::Windows::Forms::Padding(15);
			this->tableLayoutPanel26->Name = L"tableLayoutPanel26";
			this->tableLayoutPanel26->RowCount = 6;
			this->tableLayoutPanel26->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel26->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel26->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel26->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel26->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel26->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
			this->tableLayoutPanel26->Size = System::Drawing::Size(366, 176);
			this->tableLayoutPanel26->TabIndex = 29;
			// 
			// TempCorrUpDown
			// 
			this->TempCorrUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempCorrUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->TempCorrUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TempCorrUpDown->DecimalPlaces = 1;
			this->TempCorrUpDown->Enabled = false;
			this->TempCorrUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->TempCorrUpDown->ForeColor = System::Drawing::Color::White;
			this->TempCorrUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->TempCorrUpDown->Location = System::Drawing::Point(186, 4);
			this->TempCorrUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->TempCorrUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, System::Int32::MinValue });
			this->TempCorrUpDown->Name = L"TempCorrUpDown";
			this->TempCorrUpDown->Size = System::Drawing::Size(177, 20);
			this->TempCorrUpDown->TabIndex = 11;
			this->TempCorrUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// ReflectedTempUpDown
			// 
			this->ReflectedTempUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ReflectedTempUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ReflectedTempUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->ReflectedTempUpDown->DecimalPlaces = 1;
			this->ReflectedTempUpDown->Enabled = false;
			this->ReflectedTempUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->ReflectedTempUpDown->ForeColor = System::Drawing::Color::White;
			this->ReflectedTempUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->ReflectedTempUpDown->Location = System::Drawing::Point(186, 62);
			this->ReflectedTempUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->ReflectedTempUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, System::Int32::MinValue });
			this->ReflectedTempUpDown->Name = L"ReflectedTempUpDown";
			this->ReflectedTempUpDown->Size = System::Drawing::Size(177, 20);
			this->ReflectedTempUpDown->TabIndex = 19;
			this->ReflectedTempUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// TempCorrLabel
			// 
			this->TempCorrLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->TempCorrLabel->AutoSize = true;
			this->TempCorrLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->TempCorrLabel->ForeColor = System::Drawing::Color::White;
			this->TempCorrLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->TempCorrLabel->Location = System::Drawing::Point(6, 7);
			this->TempCorrLabel->Name = L"TempCorrLabel";
			this->TempCorrLabel->Size = System::Drawing::Size(170, 15);
			this->TempCorrLabel->TabIndex = 15;
			this->TempCorrLabel->Text = L"Temperature Correction [°C]:";
			this->TempCorrLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// DistanceUpDown
			// 
			this->DistanceUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DistanceUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DistanceUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DistanceUpDown->Enabled = false;
			this->DistanceUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->DistanceUpDown->ForeColor = System::Drawing::Color::White;
			this->DistanceUpDown->Location = System::Drawing::Point(186, 150);
			this->DistanceUpDown->Name = L"DistanceUpDown";
			this->DistanceUpDown->Size = System::Drawing::Size(177, 20);
			this->DistanceUpDown->TabIndex = 18;
			this->DistanceUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// DistanceLabel
			// 
			this->DistanceLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->DistanceLabel->AutoSize = true;
			this->DistanceLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->DistanceLabel->ForeColor = System::Drawing::Color::White;
			this->DistanceLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->DistanceLabel->Location = System::Drawing::Point(12, 153);
			this->DistanceLabel->Name = L"DistanceLabel";
			this->DistanceLabel->Size = System::Drawing::Size(159, 15);
			this->DistanceLabel->TabIndex = 27;
			this->DistanceLabel->Text = L"Surface Distance [Meters]:";
			this->DistanceLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// AmbientTempLabel
			// 
			this->AmbientTempLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->AmbientTempLabel->AutoSize = true;
			this->AmbientTempLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->AmbientTempLabel->ForeColor = System::Drawing::Color::White;
			this->AmbientTempLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->AmbientTempLabel->Location = System::Drawing::Point(13, 36);
			this->AmbientTempLabel->Name = L"AmbientTempLabel";
			this->AmbientTempLabel->Size = System::Drawing::Size(157, 15);
			this->AmbientTempLabel->TabIndex = 17;
			this->AmbientTempLabel->Text = L"Ambient Temperature [°C]:";
			this->AmbientTempLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// EmissivityLabel
			// 
			this->EmissivityLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->EmissivityLabel->AutoSize = true;
			this->EmissivityLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->EmissivityLabel->ForeColor = System::Drawing::Color::White;
			this->EmissivityLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->EmissivityLabel->Location = System::Drawing::Point(14, 123);
			this->EmissivityLabel->Name = L"EmissivityLabel";
			this->EmissivityLabel->Size = System::Drawing::Size(155, 15);
			this->EmissivityLabel->TabIndex = 26;
			this->EmissivityLabel->Text = L"Object Surface Emissivity:";
			this->EmissivityLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// HumidityLabel
			// 
			this->HumidityLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->HumidityLabel->AutoSize = true;
			this->HumidityLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->HumidityLabel->ForeColor = System::Drawing::Color::White;
			this->HumidityLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->HumidityLabel->Location = System::Drawing::Point(15, 94);
			this->HumidityLabel->Name = L"HumidityLabel";
			this->HumidityLabel->Size = System::Drawing::Size(152, 15);
			this->HumidityLabel->TabIndex = 24;
			this->HumidityLabel->Text = L"Surrounding Humidity [%];";
			this->HumidityLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// EmissivityUpDown
			// 
			this->EmissivityUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->EmissivityUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->EmissivityUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->EmissivityUpDown->DecimalPlaces = 2;
			this->EmissivityUpDown->Enabled = false;
			this->EmissivityUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->EmissivityUpDown->ForeColor = System::Drawing::Color::White;
			this->EmissivityUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->EmissivityUpDown->Location = System::Drawing::Point(186, 120);
			this->EmissivityUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->EmissivityUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 196608 });
			this->EmissivityUpDown->Name = L"EmissivityUpDown";
			this->EmissivityUpDown->Size = System::Drawing::Size(177, 20);
			this->EmissivityUpDown->TabIndex = 22;
			this->EmissivityUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->EmissivityUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 196608 });
			// 
			// AmbientTempUpDown
			// 
			this->AmbientTempUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->AmbientTempUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->AmbientTempUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->AmbientTempUpDown->DecimalPlaces = 1;
			this->AmbientTempUpDown->Enabled = false;
			this->AmbientTempUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->AmbientTempUpDown->ForeColor = System::Drawing::Color::White;
			this->AmbientTempUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->AmbientTempUpDown->Location = System::Drawing::Point(186, 33);
			this->AmbientTempUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->AmbientTempUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, System::Int32::MinValue });
			this->AmbientTempUpDown->Name = L"AmbientTempUpDown";
			this->AmbientTempUpDown->Size = System::Drawing::Size(177, 20);
			this->AmbientTempUpDown->TabIndex = 20;
			this->AmbientTempUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// ReflectedTempLabel
			// 
			this->ReflectedTempLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ReflectedTempLabel->AutoSize = true;
			this->ReflectedTempLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->ReflectedTempLabel->ForeColor = System::Drawing::Color::White;
			this->ReflectedTempLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ReflectedTempLabel->Location = System::Drawing::Point(9, 65);
			this->ReflectedTempLabel->Name = L"ReflectedTempLabel";
			this->ReflectedTempLabel->Size = System::Drawing::Size(164, 15);
			this->ReflectedTempLabel->TabIndex = 21;
			this->ReflectedTempLabel->Text = L"Reflected Temperature [°C]:";
			this->ReflectedTempLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// HumidityUpDown
			// 
			this->HumidityUpDown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->HumidityUpDown->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->HumidityUpDown->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->HumidityUpDown->DecimalPlaces = 2;
			this->HumidityUpDown->Enabled = false;
			this->HumidityUpDown->Font = (gcnew System::Drawing::Font(L"Arial", 10.5F, System::Drawing::FontStyle::Bold));
			this->HumidityUpDown->ForeColor = System::Drawing::Color::White;
			this->HumidityUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->HumidityUpDown->Location = System::Drawing::Point(186, 91);
			this->HumidityUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->HumidityUpDown->Name = L"HumidityUpDown";
			this->HumidityUpDown->Size = System::Drawing::Size(177, 20);
			this->HumidityUpDown->TabIndex = 23;
			this->HumidityUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// CameraConfigMenuButton
			// 
			this->CameraConfigMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->CameraConfigMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->CameraConfigMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->CameraConfigMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CameraConfigMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->CameraConfigMenuButton->ForeColor = System::Drawing::Color::White;
			this->CameraConfigMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CameraConfigMenuButton.Image")));
			this->CameraConfigMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->CameraConfigMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->CameraConfigMenuButton->Location = System::Drawing::Point(10, 350);
			this->CameraConfigMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->CameraConfigMenuButton->Name = L"CameraConfigMenuButton";
			this->CameraConfigMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->CameraConfigMenuButton->Size = System::Drawing::Size(1370, 54);
			this->CameraConfigMenuButton->TabIndex = 32;
			this->CameraConfigMenuButton->Text = L"   Thermal Camera Configuration:";
			this->CameraConfigMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->CameraConfigMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->CameraConfigMenuButton->UseVisualStyleBackColor = false;
			this->CameraConfigMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::CameraConfigMenuButton_Click);
			// 
			// ConnectTCAMSubMenuPanel
			// 
			this->ConnectTCAMSubMenuPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ConnectTCAMSubMenuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ConnectTCAMSubMenuPanel->Controls->Add(this->tableLayoutPanel25);
			this->ConnectTCAMSubMenuPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->ConnectTCAMSubMenuPanel->Location = System::Drawing::Point(10, 64);
			this->ConnectTCAMSubMenuPanel->Name = L"ConnectTCAMSubMenuPanel";
			this->ConnectTCAMSubMenuPanel->Size = System::Drawing::Size(1370, 286);
			this->ConnectTCAMSubMenuPanel->TabIndex = 31;
			// 
			// tableLayoutPanel25
			// 
			this->tableLayoutPanel25->ColumnCount = 2;
			this->tableLayoutPanel25->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				744)));
			this->tableLayoutPanel25->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel25->Controls->Add(this->tableLayoutPanel67, 0, 0);
			this->tableLayoutPanel25->Controls->Add(this->label35, 1, 0);
			this->tableLayoutPanel25->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel25->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel25->Name = L"tableLayoutPanel25";
			this->tableLayoutPanel25->RowCount = 1;
			this->tableLayoutPanel25->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel25->Size = System::Drawing::Size(1368, 284);
			this->tableLayoutPanel25->TabIndex = 0;
			// 
			// tableLayoutPanel67
			// 
			this->tableLayoutPanel67->ColumnCount = 2;
			this->tableLayoutPanel67->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel67->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel67->Controls->Add(this->label83, 1, 1);
			this->tableLayoutPanel67->Controls->Add(this->panel11, 0, 1);
			this->tableLayoutPanel67->Controls->Add(this->ConnectButton, 0, 0);
			this->tableLayoutPanel67->Controls->Add(this->DisconnectButton, 1, 0);
			this->tableLayoutPanel67->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel67->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel67->Name = L"tableLayoutPanel67";
			this->tableLayoutPanel67->RowCount = 2;
			this->tableLayoutPanel67->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 80)));
			this->tableLayoutPanel67->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel67->Size = System::Drawing::Size(738, 278);
			this->tableLayoutPanel67->TabIndex = 0;
			// 
			// label83
			// 
			this->label83->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label83->AutoSize = true;
			this->label83->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label83->ForeColor = System::Drawing::Color::White;
			this->label83->Location = System::Drawing::Point(441, 222);
			this->label83->Name = L"label83";
			this->label83->Size = System::Drawing::Size(225, 30);
			this->label83->TabIndex = 27;
			this->label83->Text = L"Press The Button, To Disconnect\r\nFrom The Connected Thermal Camera.";
			this->label83->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// panel11
			// 
			this->panel11->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->panel11->Controls->Add(this->CameraSourceDropList);
			this->panel11->Controls->Add(this->label1);
			this->panel11->Location = System::Drawing::Point(46, 222);
			this->panel11->Margin = System::Windows::Forms::Padding(0);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(277, 43);
			this->panel11->TabIndex = 0;
			// 
			// CameraSourceDropList
			// 
			this->CameraSourceDropList->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->CameraSourceDropList->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->CameraSourceDropList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->CameraSourceDropList->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CameraSourceDropList->Font = (gcnew System::Drawing::Font(L"Arial", 9.5F, System::Drawing::FontStyle::Bold));
			this->CameraSourceDropList->ForeColor = System::Drawing::Color::White;
			this->CameraSourceDropList->FormattingEnabled = true;
			this->CameraSourceDropList->Location = System::Drawing::Point(0, 19);
			this->CameraSourceDropList->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->CameraSourceDropList->Name = L"CameraSourceDropList";
			this->CameraSourceDropList->Size = System::Drawing::Size(277, 24);
			this->CameraSourceDropList->TabIndex = 13;
			this->CameraSourceDropList->SelectedIndexChanged += gcnew System::EventHandler(this, &ThermalCameraGUI::CameraSourceDropList_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label1->Location = System::Drawing::Point(-3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(267, 15);
			this->label1->TabIndex = 14;
			this->label1->Text = L"Sellect A Thermal Camera And Press Connect";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// ConnectButton
			// 
			this->ConnectButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ConnectButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ConnectButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ConnectButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->ConnectButton->ForeColor = System::Drawing::Color::White;
			this->ConnectButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ConnectButton.Image")));
			this->ConnectButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ConnectButton->Location = System::Drawing::Point(15, 15);
			this->ConnectButton->Margin = System::Windows::Forms::Padding(15);
			this->ConnectButton->Name = L"ConnectButton";
			this->ConnectButton->Padding = System::Windows::Forms::Padding(3);
			this->ConnectButton->Size = System::Drawing::Size(339, 192);
			this->ConnectButton->TabIndex = 12;
			this->ConnectButton->Text = L"Connect";
			this->ConnectButton->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->ConnectButton->UseVisualStyleBackColor = false;
			this->ConnectButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::ConnectButton_Click);
			// 
			// DisconnectButton
			// 
			this->DisconnectButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->DisconnectButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DisconnectButton->Enabled = false;
			this->DisconnectButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->DisconnectButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->DisconnectButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->DisconnectButton->ForeColor = System::Drawing::Color::White;
			this->DisconnectButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DisconnectButton.Image")));
			this->DisconnectButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->DisconnectButton->Location = System::Drawing::Point(384, 15);
			this->DisconnectButton->Margin = System::Windows::Forms::Padding(15);
			this->DisconnectButton->Name = L"DisconnectButton";
			this->DisconnectButton->Padding = System::Windows::Forms::Padding(3);
			this->DisconnectButton->Size = System::Drawing::Size(339, 192);
			this->DisconnectButton->TabIndex = 15;
			this->DisconnectButton->Text = L"Disconnect";
			this->DisconnectButton->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->DisconnectButton->UseVisualStyleBackColor = false;
			this->DisconnectButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::DisconnectButton_Click);
			// 
			// label35
			// 
			this->label35->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->label35->ForeColor = System::Drawing::Color::White;
			this->label35->Location = System::Drawing::Point(747, 67);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(468, 150);
			this->label35->TabIndex = 19;
			this->label35->Text = resources->GetString(L"label35.Text");
			this->label35->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// ConnectTCAMMenuButton
			// 
			this->ConnectTCAMMenuButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ConnectTCAMMenuButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->ConnectTCAMMenuButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ConnectTCAMMenuButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ConnectTCAMMenuButton->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->ConnectTCAMMenuButton->ForeColor = System::Drawing::Color::White;
			this->ConnectTCAMMenuButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ConnectTCAMMenuButton.Image")));
			this->ConnectTCAMMenuButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->ConnectTCAMMenuButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ConnectTCAMMenuButton->Location = System::Drawing::Point(10, 10);
			this->ConnectTCAMMenuButton->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);
			this->ConnectTCAMMenuButton->Name = L"ConnectTCAMMenuButton";
			this->ConnectTCAMMenuButton->Padding = System::Windows::Forms::Padding(3);
			this->ConnectTCAMMenuButton->Size = System::Drawing::Size(1370, 54);
			this->ConnectTCAMMenuButton->TabIndex = 30;
			this->ConnectTCAMMenuButton->Text = L"   Connect To A Thermal Camera:";
			this->ConnectTCAMMenuButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->ConnectTCAMMenuButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->ConnectTCAMMenuButton->UseVisualStyleBackColor = false;
			this->ConnectTCAMMenuButton->Click += gcnew System::EventHandler(this, &ThermalCameraGUI::ConnectTCAMMenuButton_Click);
			// 
			// AutoCalTimer
			// 
			this->AutoCalTimer->Interval = 5000;
			this->AutoCalTimer->Tick += gcnew System::EventHandler(this, &ThermalCameraGUI::AutoCalTimer_Tick);
			// 
			// AlarmSoundTimer
			// 
			this->AlarmSoundTimer->Interval = 2000;
			this->AlarmSoundTimer->Tick += gcnew System::EventHandler(this, &ThermalCameraGUI::AlarmSoundTimer_Tick);
			// 
			// AlarmTriggerEventTimer
			// 
			this->AlarmTriggerEventTimer->Interval = 1000;
			this->AlarmTriggerEventTimer->Tick += gcnew System::EventHandler(this, &ThermalCameraGUI::AlarmTriggerEventTimer_Tick);
			// 
			// DriftCalTimer
			// 
			this->DriftCalTimer->Interval = 5000;
			this->DriftCalTimer->Tick += gcnew System::EventHandler(this, &ThermalCameraGUI::DriftCalTimer_Tick);
			// 
			// PeriodicTriggerTimer
			// 
			this->PeriodicTriggerTimer->Interval = 1000;
			this->PeriodicTriggerTimer->Tick += gcnew System::EventHandler(this, &ThermalCameraGUI::PeriodicTriggerTimer_Tick);
			// 
			// ThermalCameraGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(1407, 903);
			this->Controls->Add(this->MainThermalCameraPanel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ThermalCameraGUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ThermalCameraGUI";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ThermalCameraGUI::ThermalCameraGUI_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &ThermalCameraGUI::ThermalCameraGUI_Shown);
			this->MainThermalCameraPanel->ResumeLayout(false);
			this->PeriodicTriggerSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel78->ResumeLayout(false);
			this->tableLayoutPanel77->ResumeLayout(false);
			this->tableLayoutPanel77->PerformLayout();
			this->tableLayoutPanel80->ResumeLayout(false);
			this->tableLayoutPanel80->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval1UpDown))->EndInit();
			this->tableLayoutPanel79->ResumeLayout(false);
			this->tableLayoutPanel79->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval2UpDown))->EndInit();
			this->tableLayoutPanel81->ResumeLayout(false);
			this->tableLayoutPanel81->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval3UpDown))->EndInit();
			this->tableLayoutPanel82->ResumeLayout(false);
			this->tableLayoutPanel82->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval4UpDown))->EndInit();
			this->tableLayoutPanel83->ResumeLayout(false);
			this->tableLayoutPanel83->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PeriodicEventInterval5UpDown))->EndInit();
			this->TempAlarmsConfigSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel39->ResumeLayout(false);
			this->tableLayoutPanel39->PerformLayout();
			this->tableLayoutPanel40->ResumeLayout(false);
			this->tableLayoutPanel40->PerformLayout();
			this->tableLayoutPanel55->ResumeLayout(false);
			this->tableLayoutPanel55->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm5HighTempThresUpDown))->EndInit();
			this->tableLayoutPanel54->ResumeLayout(false);
			this->tableLayoutPanel54->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm4HighTempThresUpDown))->EndInit();
			this->tableLayoutPanel53->ResumeLayout(false);
			this->tableLayoutPanel53->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm3HighTempThresUpDown))->EndInit();
			this->tableLayoutPanel52->ResumeLayout(false);
			this->tableLayoutPanel52->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm2HighTempThresUpDown))->EndInit();
			this->tableLayoutPanel51->ResumeLayout(false);
			this->tableLayoutPanel51->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm1HighTempThresUpDown))->EndInit();
			this->tableLayoutPanel41->ResumeLayout(false);
			this->tableLayoutPanel41->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm1LowTempThresUpDown))->EndInit();
			this->tableLayoutPanel45->ResumeLayout(false);
			this->tableLayoutPanel45->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm5LowTempThresUpDown))->EndInit();
			this->tableLayoutPanel42->ResumeLayout(false);
			this->tableLayoutPanel42->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm2LowTempThresUpDown))->EndInit();
			this->tableLayoutPanel43->ResumeLayout(false);
			this->tableLayoutPanel43->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm3LowTempThresUpDown))->EndInit();
			this->tableLayoutPanel44->ResumeLayout(false);
			this->tableLayoutPanel44->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempAlarm4LowTempThresUpDown))->EndInit();
			this->tableLayoutPanel57->ResumeLayout(false);
			this->tableLayoutPanel46->ResumeLayout(false);
			this->tableLayoutPanel47->ResumeLayout(false);
			this->tableLayoutPanel47->PerformLayout();
			this->tableLayoutPanel48->ResumeLayout(false);
			this->tableLayoutPanel48->PerformLayout();
			this->tableLayoutPanel49->ResumeLayout(false);
			this->tableLayoutPanel49->PerformLayout();
			this->tableLayoutPanel50->ResumeLayout(false);
			this->tableLayoutPanel50->PerformLayout();
			this->tableLayoutPanel56->ResumeLayout(false);
			this->tableLayoutPanel56->PerformLayout();
			this->tableLayoutPanel58->ResumeLayout(false);
			this->tableLayoutPanel58->PerformLayout();
			this->tableLayoutPanel59->ResumeLayout(false);
			this->tableLayoutPanel59->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AlarmTriggerEventsIntervalUpDown))->EndInit();
			this->tableLayoutPanel71->ResumeLayout(false);
			this->DataLoggingSettingsSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel34->ResumeLayout(false);
			this->tableLayoutPanel35->ResumeLayout(false);
			this->tableLayoutPanel35->PerformLayout();
			this->tableLayoutPanel75->ResumeLayout(false);
			this->tableLayoutPanel76->ResumeLayout(false);
			this->tableLayoutPanel76->PerformLayout();
			this->tableLayoutPanel36->ResumeLayout(false);
			this->tableLayoutPanel63->ResumeLayout(false);
			this->tableLayoutPanel63->PerformLayout();
			this->tableLayoutPanel64->ResumeLayout(false);
			this->tableLayoutPanel65->ResumeLayout(false);
			this->tableLayoutPanel65->PerformLayout();
			this->tableLayoutPanel37->ResumeLayout(false);
			this->tableLayoutPanel37->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LogIntervalUpDown))->EndInit();
			this->tableLayoutPanel66->ResumeLayout(false);
			this->tableLayoutPanel66->PerformLayout();
			this->tableLayoutPanel38->ResumeLayout(false);
			this->tableLayoutPanel38->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DurationSecondsUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DurationMinuteUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DurationHourUpDown))->EndInit();
			this->TempPlotDataSetSettingsSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel33->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel14->ResumeLayout(false);
			this->tableLayoutPanel14->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet10UpDown))->EndInit();
			this->tableLayoutPanel13->ResumeLayout(false);
			this->tableLayoutPanel13->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet9UpDown))->EndInit();
			this->tableLayoutPanel12->ResumeLayout(false);
			this->tableLayoutPanel12->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet8UpDown))->EndInit();
			this->tableLayoutPanel11->ResumeLayout(false);
			this->tableLayoutPanel11->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet7UpDown))->EndInit();
			this->tableLayoutPanel10->ResumeLayout(false);
			this->tableLayoutPanel10->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet6UpDown))->EndInit();
			this->tableLayoutPanel9->ResumeLayout(false);
			this->tableLayoutPanel9->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet5UpDown))->EndInit();
			this->tableLayoutPanel8->ResumeLayout(false);
			this->tableLayoutPanel8->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet4UpDown))->EndInit();
			this->tableLayoutPanel7->ResumeLayout(false);
			this->tableLayoutPanel7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet3UpDown))->EndInit();
			this->tableLayoutPanel6->ResumeLayout(false);
			this->tableLayoutPanel6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet2UpDown))->EndInit();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataSet1UpDown))->EndInit();
			this->tableLayoutPanel24->ResumeLayout(false);
			this->tableLayoutPanel24->PerformLayout();
			this->tableLayoutPanel23->ResumeLayout(false);
			this->tableLayoutPanel23->PerformLayout();
			this->tableLayoutPanel22->ResumeLayout(false);
			this->tableLayoutPanel22->PerformLayout();
			this->tableLayoutPanel21->ResumeLayout(false);
			this->tableLayoutPanel21->PerformLayout();
			this->tableLayoutPanel20->ResumeLayout(false);
			this->tableLayoutPanel20->PerformLayout();
			this->tableLayoutPanel19->ResumeLayout(false);
			this->tableLayoutPanel19->PerformLayout();
			this->tableLayoutPanel18->ResumeLayout(false);
			this->tableLayoutPanel18->PerformLayout();
			this->tableLayoutPanel17->ResumeLayout(false);
			this->tableLayoutPanel17->PerformLayout();
			this->tableLayoutPanel16->ResumeLayout(false);
			this->tableLayoutPanel16->PerformLayout();
			this->tableLayoutPanel15->ResumeLayout(false);
			this->tableLayoutPanel15->PerformLayout();
			this->VideoRecSettingsSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel61->ResumeLayout(false);
			this->tableLayoutPanel60->ResumeLayout(false);
			this->tableLayoutPanel60->PerformLayout();
			this->tableLayoutPanel84->ResumeLayout(false);
			this->tableLayoutPanel84->PerformLayout();
			this->tableLayoutPanel85->ResumeLayout(false);
			this->tableLayoutPanel85->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RecordingFrameRateNumericUpDown))->EndInit();
			this->tableLayoutPanel70->ResumeLayout(false);
			this->tableLayoutPanel70->PerformLayout();
			this->SnapshotConfigSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel32->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel72->ResumeLayout(false);
			this->tableLayoutPanel72->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->AutoCalSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel31->ResumeLayout(false);
			this->tableLayoutPanel68->ResumeLayout(false);
			this->tableLayoutPanel73->ResumeLayout(false);
			this->tableLayoutPanel73->PerformLayout();
			this->tableLayoutPanel74->ResumeLayout(false);
			this->tableLayoutPanel74->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SensorDriftCalUpDown))->EndInit();
			this->tableLayoutPanel62->ResumeLayout(false);
			this->tableLayoutPanel62->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AutoCalPeriodUpDown))->EndInit();
			this->tableLayoutPanel69->ResumeLayout(false);
			this->tableLayoutPanel69->PerformLayout();
			this->CameraConfigSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel30->ResumeLayout(false);
			this->tableLayoutPanel27->ResumeLayout(false);
			this->tableLayoutPanel28->ResumeLayout(false);
			this->tableLayoutPanel28->PerformLayout();
			this->tableLayoutPanel29->ResumeLayout(false);
			this->tableLayoutPanel29->PerformLayout();
			this->tableLayoutPanel26->ResumeLayout(false);
			this->tableLayoutPanel26->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TempCorrUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ReflectedTempUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DistanceUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EmissivityUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AmbientTempUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HumidityUpDown))->EndInit();
			this->ConnectTCAMSubMenuPanel->ResumeLayout(false);
			this->tableLayoutPanel25->ResumeLayout(false);
			this->tableLayoutPanel25->PerformLayout();
			this->tableLayoutPanel67->ResumeLayout(false);
			this->tableLayoutPanel67->PerformLayout();
			this->panel11->ResumeLayout(false);
			this->panel11->PerformLayout();
			this->ResumeLayout(false);

		}

#pragma endregion

		// ------------------ Main GUI Opstartnings Og Nedluknings Callback Routiner ------------------ //

		// Thermal Camera Form Opstartnings Callback Routine -> 
		private: System::Void ThermalCameraGUI_Shown(System::Object^ sender, System::EventArgs^ e) {

			// Opdater tilhørende form Flag
			isThermalCameraFormOpen = true;

			// Aktiver Plot af en valgt DataSæt index
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_EnablePlotOfDataSetx(_2DPlotDataSet_1, true);
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_EnablePlotOfDataSetx(_2DPlotDataSet_2, true);
			GlobalVariables::OpenGL2DPlot->RMH_OpenGL_EnablePlotOfDataSetx(_2DPlotDataSet_3, true);

		}

	    // Thermal Camera Form Nedluknings Callback Routine ->
		private: System::Void ThermalCameraGUI_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

			// Opdater tilhørende form Flag
			isThermalCameraFormOpen = false;
			isThermalCameraFormDocked = false;
			isThermalCameraFormUndocked = false;

			// Når Formen lukkes - Gem Formen
			this->Hide();
			// Deaktiver "Disposing" Af Form Objektet
			e->Cancel = true;

		}
		
		// ------------------------- Form Fælles Reference CallBack Routiner -------------------------- //

		// Reference Routine Til Deaktivering Af CombiBox Mus Hjul Scroll Deaktiverings Callback Routine ->
		private: System::Void ComboBox_MouseWheelDisable(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

			// Lokale objekter - Event argument konvertering
			System::Windows::Forms::HandledMouseEventArgs^ MouseEventArgs = dynamic_cast<System::Windows::Forms::HandledMouseEventArgs^>(e);

			// Kontroller om event argumenter ikke er null
			if (MouseEventArgs != nullptr) {

				// Deaktiver yderligere event for handle
				MouseEventArgs->Handled = true;

			}

		}

		// --------------------------- GUI Menu/Sub-Menu Callback Routiner ---------------------------- //

		// Connect To Thermal Camera Menu Knap Callback ->
		private: System::Void ConnectTCAMMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Termisk Kamera Connect Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->ConnectTCAMSubMenuPanel, this->ConnectTCAMMenuButton);

		}

		// Thermal Camera Konfiguration Menu Knap Callback ->
		private: System::Void CameraConfigMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Termisk Kamera Konfigurations Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->CameraConfigSubMenuPanel, this->CameraConfigMenuButton);

		}

		// Automatisk Kamera Kalibrering Menu Knap Callback ->
		private: System::Void AutoCalMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Termisk Kamera Auto Kalibrerings Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->AutoCalSubMenuPanel, this->AutoCalMenuButton);

		}

		// Snapshot Indstillinger Menu Knap Callback ->
		private: System::Void SnapshotConfigMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Snapshot Indstillingers Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->SnapshotConfigSubMenuPanel, this->SnapshotConfigMenuButton);

		}

		// Video Optagnings Indstillinger Menu Knap Callback ->
		private: System::Void VideoRecordingMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Video Optagning Indstillingers Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->VideoRecSettingsSubMenuPanel, this->VideoRecordingMenuButton);

		}

		// Plot Data Sæt Konfiguration Indstillingers Menu Knap Callback ->
		private: System::Void TempPlotDataSetSettingsMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Plot Data Sæt Konfiguration Indstillingers Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->TempPlotDataSetSettingsSubMenuPanel, this->TempPlotDataSetSettingsMenuButton);

		}

		// Data Logging Indstillingers Menu Knap Callback ->
		private: System::Void DataLoggingSettingsMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {
			
			// Toggle Data Loggings Indstillingers Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->DataLoggingSettingsSubMenuPanel, this->DataLoggingSettingsMenuButton);

		}
		
		// Data Logging Delimiter CombiBox Ny Delimiter Valgt CallBack ROutine ->
		private: System::Void DataLoggingCSVDelimiterCombiBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater hvilken Data delimiter som benyttes når der gemmes en data Logging CSV fil
			RMH_ThermalViewer_UpdateDataLoggingCSVDataDelimiter();

		}

		// Temperatur Alarmers Konfigurations Menu Knap Callback ->
		private: System::Void TempAlarmsConfigMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater tilhørende "Menu er åben" flag
			TempAlarmsConfigMenuIsOpen = !TempAlarmsConfigMenuIsOpen;

			// Toggle Temp Alarmernes Konfiguration Indstillingers Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->TempAlarmsConfigSubMenuPanel, this->TempAlarmsConfigMenuButton);

		}
		
		// General Og Periodisk Trigger Konfigurations Menu Knap Callback ->
		private: System::Void PeriodicTriggerConfigMenuButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle General Og Periodisk Trigger Konfiguration Indstillingers Sub Menu
			RMH_Winforms_ToggleSubMenuPanel(this->PeriodicTriggerSubMenuPanel, this->PeriodicTriggerConfigMenuButton);

		}

		// -------------------- Thermal Camera Connect Og Konfigurations Callbacks -------------------- //

		// Connect Knap click event Callback Routine ->
		private: System::Void ConnectButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Kontroller om TOPDON informations dialogen skal vises
			if (PopUpDialogDontShowFlag == false) {

				// Åben informations dialogen - Med Info Om TOPDON Cameraer
				ManagedLocals::PopUpDialogForm->ShowDialog();

			}

			// Forbind til valgte termiske kamera eller analysis mode
			RMH_IRThermalCamera_ConnectToThermalCameraOrAnalysisMode();

		}

		// Connect Knap click event Callback Routine ->
		private: System::Void DisconnectButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Håndter handlingerne ved ændring af Kamera source ComboBox Item - Samme Som Disconnect
			RMH_ThermalViewer_HandleSellectedDeviceOrModeChange();

			// Opdater GUI controls (Executes any pending requests for painting.)
			this->Update();

		}

		// Supported Kamera Device ComboBox Værdi Ændrings Callback ->
		private: System::Void CameraSourceDropList_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Håndter handlingerne ved ændring af Kamera source ComboBox Item
			RMH_ThermalViewer_HandleSellectedDeviceOrModeChange();

			// Opdater GUI controls (Executes any pending requests for painting.)
			this->Update();

		}

	    // Læs Kamera Konfigurations Knap Click Callback Routine ->
		private: System::Void ReadCameraConfigButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Læs og vis de læste interne kamera konfigurations parametere
			RMH_ThermalViewer_ReadAndDisplayCameraConfigParameters();

			// Opdater GUI controls (Executes any pending requests for painting.)
			this->Update();

		}

		// Indstil Kamera Konfigurations Knap Click Callback Routine ->
		private: System::Void SetCameraConfigButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Temperatur korrektions værdi til globale variabel til gemt sessions parameter
			SavedTempCorrectionSetting = RMH_Conversion_SystemDecimalToFloat(this->TempCorrUpDown->Value);

			// Skriv/Sæt de indstillede Kamera konfigurations parametere til kamera hukommelse
			RMH_ThermalViewer_SetCameraConfigParameters();

			// Opdater GUI controls (Executes any pending requests for painting.)
			this->Update();

		}

		// Genindstil/Recover default kamera temperature konfigurations Knap Click Callback Routine -> 
		private: System::Void RecoverDefaultCameraSettingsButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Indstil default temperatur konfigurationen for termisk kamera
			RMH_ThermalViewer_RecoverDefaultCameraTempConfiguration();

		}

		// ------------- Automatisk Shutter Kalibration Menu Og Konfigurations Callbacks -------------- //

		// Aktiver Auto Kalibrerings timer Knap Click Callback Routine ->
		private: System::Void AutoShutterCalButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle Automatisk shutter kalibrerings feature timeren
			RMH_ThermalViewer_ToggleCameraAutoShutterCalibrationTimer();

		}

		// Aktiver Temperatur Drift Baserede Kalibrerings timer Knap Click Callback Routine ->
		private: System::Void SensorDriftCalButton_Click(System::Object^ sender, System::EventArgs^ e) {
			
			// Toggle Temperatur Drift Baseret kalibrerings feature timeren
			RMH_ThermalViewer_ToggleCameraDriftBasedCalibrationTimer();

		}

		// Auto Kalibrerings timer Callback Routine ->
		private: System::Void AutoCalTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

			// Eksikver events ved auto kalibrerings timer callback
			RMH_IRThermalCamera_AutoShutterCalTimerCallbackHandler();

		}

		// Temperatur Drift Baserede Kalibrerings timer Callback Routine ->
		private: System::Void DriftCalTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

			// Eksikver events ved Temperatur Drift Baserede kalibrerings timer callback
			RMH_IRThermalCamera_TempDriftBasedCalTimerCallbackHandler();

		}

		// Temperatur Drift Baserede Kalibrerings Set-punkts værdi Callback Routine ->
		private: System::Void SensorDriftCalUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Temperatur Drift Baserede Kalibrerings Set-punkts værdien
			TempDriftCalibrationSetValue = (double)this->SensorDriftCalUpDown->Value;

		}

		// Læs Kameraets interne temperaturer Knap Callback Routine ->
		private: System::Void ReadIntCameraTempsButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Læs Kameraets interne kalibrerings temperaturer
			RMH_ThermalViewer_ReadThermalCameraInternalTemps();

		}

		// ------ Full Frame CSV Data Og Snapshot Indstillingers Menu Og Konfigurations Callbacks ------ //

		// Indstil Snapshot default fil path Callback Routine ->
		private: System::Void ChangeSnapDefaultPathButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater fil lokationen hvor et Live View Snapshot skal gemmes
			RMH_ThermalViewer_UpdateSnapshotDefaultSaveFilePath(this->DefaultSnapshotSavePathString);

		}

		// Inkluder ColorBar i Snapshot Knap Callback Routine ->
		private: System::Void IncludeColorbarSnapButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle om det valgte snapshot skal indeholde colorbaren eller ikke
			RMH_ThermalViewer_IncludeColorBarInSnapshot();

		}

		// Gem Rå Sensor Data Snapshot Knap Callback Routine ->
		private: System::Void SaveRawSensorSnapButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle om et Rå sensor data snapshot skal gemmes med tilhørende live view snapshot
			RMH_ThermalViewer_ToggleSavinfOfRawSensorDataSnapshot();

		}

		// Full Frame CSV Data Delimiter CombiBox Index ændret CallBack Routine ->
		private: System::Void FullFrameTempDataCSVDelimiterCombiBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater hvilken Data delimiter som benyttes når der gemmes en Full frame temperatur data CSV fil
			RMH_ThermalViewer_UpdateFullFrameTemperatureCSVDataDelimiter();

		}

		// ------------- Video Optagnings Indstillingers Menu Og Konfigurations Callbacks ------------- //

		// Default Live view video capturing applikation Knap Callback Routine ->
		private: System::Void UseWinSnippingToolButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Det default Video Capturing program for optagning af live view video
			RMH_ThermalViewer_ConfigDefaultCapturingProgram(sender);

		}
	
		// Indstil Video Recording default fil path Callback Routine ->
		private: System::Void ChangeRecordingDefaultPathButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater fil lokationen hvor video optagningen skal gemmes
			RMH_ThermalViewer_UpdateVideoRecordingDefaultSaveFilePath(this->DefaultRecordingSavePathString);

		}

		// Toggle gemning af RAW Data optagning Callback Routine ->
		private: System::Void SaveRawAnalysisRecordingButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Toggle optagning af en RAW data fil
			RMH_ThermalViewer_ToggleRecordingOfRAWDataForPostAnalysis();

		}

		// ------------ Temp Plot Data Sæt Indstillingers Menu Og Konfigurations Callbacks ------------ //

		// Plot Data Sæt Aktiverings CheckBox Callback Routine ->
		private: System::Void DataSet1CheckBox_CheckStateChanged(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver 2D Plot Data Set til plotning
			RMH_ThermalViewer_Enable2DPlotDataSet(sender);

			// Opdater 2D Plot Legend
			RMH_ThermalViewer_Update2DPlotLegendLabels();

		}

		// Plot Data Sæt Linje Farve Click Callback Routine ->
		private: System::Void DataSet1ColorPanel_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater 2D Plot Data sæt farve - Samt Menu panel
			RMH_ThermalViewer_Change2DPlotDataSetAndSettingsPanelColor(sender);

			// Opdater 2D Plot Legend
			RMH_ThermalViewer_Update2DPlotLegendLabels();

		}

		// Plot Data Sæt Linje Tykkelse UpDown Callback Routine ->
		private: System::Void DataSet1UpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater 2D Plot Data Sæt linje tykkelse
			RMH_ThermalViewer_Change2DPlotDataSetLineWidth(sender);

		}

		// Plot Data Sæt Source ComboBox Callback Routine ->
		private: System::Void DataSet1ComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Indstil 2D Plot data sæt source til valgte ComboBox Index
			RMH_ThermalViewer_Change2DPlotDataSetSource(sender);

			// Opdater Kun 2D Plot Legende når TempMeasGUI er loaded
			if (TempMeasGUIReadyFlag == true) {

				// Opdater 2D Plot Legend
				RMH_ThermalViewer_Update2DPlotLegendLabels();

			}

		}

		// --------------- Data Logging Indstillingers Menu Og Konfigurations Callbacks --------------- //

		// Indstil Data Logging default fil path Callback Routine ->
		private: System::Void ChangeCSVDefaultPathButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Opdater fil lokationen hvor Data Logging CSV filen skal gemmes
			RMH_ThermalViewer_UpdateDataLoggingDefaultSaveFilePath(this->DefaultDataLoggingSavePathString);

		}

		// ------------- Temperatur Alarm Indstillingers Menu Og Konfigurations Callbacks ------------- //

		// Temperatur Alarm Data Sources ComboBox Callback Routine ->
		private: System::Void TempAlarm1DataSourceComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Temperatur Alarms Data Source Reference
			RMH_ThermalViewer_ChangeTemperatureAlarmDataSource(sender);

		}

		// Temperatur Alarm Type ComboBox Callback Routine ->
		private: System::Void TempAlarm1AlarmTypeComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Temperatur Alarms Type konfiguration
			RMH_ThermalViewer_ChangeTempAlarmConfigType(sender);

		}

		// Temperatur Alarm Low Temp Set Punkt Ændret Callback Routine ->
		private: System::Void TempAlarm1LowTempThresUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Temperatur Alarmens Low Temp Tærskel værdi
			RMH_ThermalViewer_ChangeTempAlarmLowTempSetPoint(sender);

		}

		// Temperatur Alarm High Temp Set Punkt Ændret Callback Routine ->
		private: System::Void TempAlarm1HighTempThresUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Temperatur Alarmens High Temp Tærskel værdi
			RMH_ThermalViewer_ChangeTempAlarmHighTempSetPoint(sender);

		}

		// Temperatur Alarm Trigger Aktion Combobox Ændret Callback Routine ->
		private: System::Void TempAlarm1TriggerActionComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Temperatur Alarmens Trigger aktions parameter
			RMH_ThermalViewer_ChangeTempAlarmTriggerAction(sender);

		}

		// Temperatur Alarm aktiverings status ændret Callback Routine ->
		private: System::Void TempAlarm1EnableCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver eller deaktiver Temperatur Alarm
			RMH_ThermalViewer_EnableTemperatureAlarm(sender);

		}
		
		// Aktiver Temperatur Alarm Trigger Lyd CheckBox Callback ->
		private: System::Void TempAlarmsTriggerSoundCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver eller deaktiver temperatur alarmernes advarsels lyd timer
			RMH_ThermalViewer_OpdateTempAlarmTriggerSoundTimer(sender);

		}

		// Temperatur alarmernes Trigger Lyd timer Tick Callback Routine ->
		private: System::Void AlarmSoundTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

			// Håndter trigger events for temperatur alarmernes advarsels lyds timer 
			RMH_ThermalViewer_AlarmSoundTimerTickEventHandler();

		}

		// Aktiver Temperatur Alarm Trigger events CheckBox Callback ->
		private: System::Void EnableAlarmTriggerEventsCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver Temperatur alarmernes trigger events
			RMH_ThermalViewer_EnableAlarmTriggerEvents(sender);

		}

		// Temperatur alarmernes Trigger Event timer Tick Callback Routine ->
		private: System::Void AlarmTriggerEventTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

			// Håndter trigger events for temperatur alarmernes trigger event timer 
			RMH_ThermalViewer_AlarmTriggerEventTimerTickEventHandler();

		}

		// Reset Alarm trigger event eksikvering knappers Callback Routine ->
		private: System::Void Alarm1TriggerEventResetButton_Click(System::Object^ sender, System::EventArgs^ e) {

			// Nulstil "Trigger event er blevet eksikverede" flaget for tilhørende temp alarm
			RMH_ThermalViewer_ResetAlarmTriggerEventExecutedFlag(sender);

		}

		// Alarm trigger event Delay timer UpDown Værdi Ændret Callback Routine ->
		private: System::Void AlarmTriggerEventsIntervalUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

			// Opdater Alarm trigger event Delay timer interval 
			GlobalVariables::GlobalAlarmTriggerEventTimer->Interval = (unsigned int)(GlobalVariables::GlobalAlarmTriggerEventsIntervalUpDown->Value * 1000);

		}
		
		// ------- General Og Periodisk Trigger Indstillingers Menu Og Konfigurations Callbacks ------- //

		// General Og Periodisk Trigger Timer Tick Callback Routine ->
		private: System::Void PeriodicTriggerTimer_Tick(System::Object^ sender, System::EventArgs^ e) {

			// Håndter events for den periodiske trigger event timer
			RMH_ThermalViewer_PeriodicTriggerEventTimerTickEventHandler();

		}
		
		// Periodisk Trigger Event Aktiverings CheckBoxCallback Routine ->
		private: System::Void PeriodicEventnEnableCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			// Aktiver eller deaktiver valgte Periodiske Trigger event
			RMH_ThermalViewer_EnableDisableSelectedPeriodicTriggerEvent(sender);

		}

		// -------------------------------------------------------------------------------------------- //

};
}
