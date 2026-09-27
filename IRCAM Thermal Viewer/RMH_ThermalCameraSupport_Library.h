
/*
 *  RMH_ThermalCameraSupport_Library.h
 *
 *  Author: Rune Mark Hansen
 *  Date: april 2023
 *
 */

#pragma once

// RMH_ThermalCameraSupport_Library.h
#ifndef RMH_ThermalCameraSupport_Library_H 
#define RMH_ThermalCameraSupport_Library_H

// Inkluderede Blbiloteker
#include <string>
#include <vector>

// ------------------------------ Blbliotek Reference Klasser ------------------------------- //

// ROI Areal Pixel Information Klasse struktur
struct ROIAreaPixelInfoFormat {

    // Maximum/Minimum Pixel parametere
    double MaxValue = 0.0;
    double MinValue = 0.0;
    double AvgValue = 0.0;
    unsigned int ROIMaxPixelWidth = 0;
    unsigned int ROIMaxPixelHeight = 0;
    unsigned int ROIMinPixelWidth = 0;
    unsigned int ROIMinPixelHeight = 0;
    unsigned int ROIAreaNmbOfPixels = 0;

};

// ----------------------------------- Tilhørende Klasser ----------------------------------- //

// Tilhørende Namespace Til Klasse
namespace ThermalCameraDevice {

    // IR Kamera Device informations Klasse 
    class IRCameraDeviceFormat {
    public:

        // Termisk kamera identifikations index og pool variabler
        unsigned int SellectedCameraIndex = 0;
        unsigned short ThermalCameraSupportPool = 0;

        // Frame Pixel Data Width/Height Offset parametere
        unsigned int FrameWidthPixelOffset = 0;
        unsigned int FrameHeightPixelOffset = 0;

        // Kamera Frame Rate variabler
        double FrameRate = 0.0;
        double CameraFrameRateSum = 0.0;
        unsigned int CameraFrameRateSumCounter = 0;
        double CameraAverageFrameRate = 0.0;

        // Diverse Variabler & Objekter
        std::string StatusMessage = "NAN";
        bool ConnectedFlag = false;  
        bool isStreaming = false;
        unsigned long NumbOfCapturedFrames = 0;
        unsigned char CurrentIRTempRangeFlag = 1; // '1' - LowRange, '2' - High Range 

        // Suporterede Termisk Kamera Pool 2 specifikke variabler
        double ObjectEnvirTempCorrectionFactor = 0.0;
        double ObjectEnvirTempCorrectionOffset = 0.0;

        // Konstante Variabler & Objekter
        std::string CameraDeviceName = "NAN";
        std::string CameraSystemDevicePath = "NAN";
        unsigned char IRCameraDeviceIndex = 0;
        double fpa_off = 0.0;
        double fpa_div = 0.0;
        double CalValue0Offset = 0.0;
        double CalValue0Fpamul = 0.0;
        unsigned int MetaData1Index = 0;
        unsigned int MetaData2Index = 0;
        unsigned int MetaData3Index = 0;
        unsigned int FrameWidth = 0;
        unsigned int FrameHeight = 0;
        unsigned int FrameMetadataSize = 0;

        // Statiske Meta Data Variabler & Objekter
        unsigned short Tmax_X = 0;            // Frame Max Temp X-Kordinat
        unsigned short Tmax_Y = 0;            // Frame Max Temp Y-Kordinat
        unsigned short Tmax_Tmp_Raw = 0;      // Frame Max Temp Rå Data
        unsigned short Tmin_X = 0;            // Frame Min Temp X-Kordinat
        unsigned short Tmin_Y = 0;            // Frame Min Temp Y-Kordinat
        unsigned short Tmin_Tmp_Raw = 0;      // Frame Min Temp Rå Data
        double Tavg_Tmp_Raw = 0;              // Frame Sensor Gennemsnitlig Værdi
        unsigned short Center_Tmp_Raw = 0;    // Frame Center Temp Rå Data
        unsigned short temp_fpa_Raw = 0;      // IR Kamera Detector Temp Rå Data
        unsigned short temp_shutter_Raw = 0;  // IR Kamera Shutter Temp Rå Data
        unsigned short temp_core_Raw = 0;     // IR Kamera Core Temp Rå Data
        double temp_fpa = 0.0;                // IR Kamera Detector Temp (Udregnede)
        double temp_shutter = 0.0;            // IR Kamera Shutter Temp (Udregnede)
        double temp_core = 0.0;               // IR Kamera Core Temp (Udregnede)

        // Statiske Kalibrerings Variabler
        float CalValue0 = 0.0;
        float CalValue1 = 0.0;
        float CalValue2 = 0.0;
        float CalValue3 = 0.0;
        float CalValue4 = 0.0;
        float CalValue5 = 0.0;

        // Interne Kamera Konfigurations parameter Variabler
        float TemperatureCorrectionSetting = 0.0;
        float ReflectedTemperatureSetting = 0.0;
        float AmbientTemperatureSetting = 0.0;
        float HumiditySetting = 0.0;
        float EmissivitySetting = 0.0;
        float DistanceSetting = 0.0;

        // Kamera Temperatur Loop-Up Tabel array
        double TemperatureLookUpTabel[16384];
        
    };

}

// -------------------------------- Kamera Initialiserings, Konfigurations & Håndterings Routiner -------------------------------- //

double RMH_IRThermalCamera_ReadCameraFPS();
void RMH_IRThermalCamera_StartCapturing();
void RMH_IRThermalCamera_StopCapturing();
void RMH_IRThermalCamera_CloseIRCameraDevice();
bool RMH_IRThermalCamera_CheckForCameraDisconnection();
void RMH_IRThermalCamera_OpenIRCameraDevice(unsigned char IRCameraDeviceIndex, unsigned short SupportedCameraPool);
void RMH_IRThermalCamera_CalibrateIRCamera(unsigned short SupportedCameraPool);
void RMH_IRThermalCamera_SetIRCameraTemperatureRange(unsigned int TemperatureRange, unsigned short SupportedCameraPool);
void RMH_IRThermalCamera_InitIRCameraConstants(ThermalCameraDevice::IRCameraDeviceFormat* CameraStatus, unsigned short SupportedCameraPool);
ThermalCameraDevice::IRCameraDeviceFormat RMH_IRThermalCamera_ConnectToThermalCamera(System::Windows::Forms::ComboBox^ CameraSourceComboBox);

// ---------------------------------- Rå Billede Data Til Rå Termisk Data Konverterings Routine ---------------------------------- //

double RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned char* YUY2in, unsigned short* ThermalDataRaw);
void RMH_IRThermalCamera_Convert14BitThermalDataArrayToYUY2(unsigned short* ThermalData, unsigned char* YUY2Out, unsigned int FrameWidth, unsigned int FrameHeight);

// --------------------------------- Termisk Kamera Region Of Interest (ROI) Håndterings Routine --------------------------------- //

ROIAreaPixelInfoFormat RMH_IRThermalCamera_ReadROIAreaPixelInfoInsideFrameArea(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short* ThermalData, unsigned int FrameWidth, unsigned int AreaX0Pos, unsigned int AreaY0Pos, unsigned int AreaWidth, unsigned int AreaHeight, bool ReturnROIPixels, unsigned short* ROIAreaRawPixelValues, unsigned short SupportedCameraPool);

// --------------------------------- Termisk Kamera Pool Specifikke Billede Processerings Routine -------------------------------- //

void RMH_IRThermalCamera_LinearAutomaticGainControlTemp(unsigned short* ThermalData, unsigned short* GainGrayscale, unsigned int FrameWidth, unsigned int FrameHeight, double MaxOutPixelVal, double MinOutPixelVal, double MaxInPixelVal, double MinInPixelVal, float TempUnitScaleFactor, float TempUnitOffsetFactor);

// -------------------------------------------- Kamera Frame Data Håndterings Routiner ------------------------------------------- //

bool RMH_IRThermalCamera_ReadFrameRaw(unsigned char* ImageData, unsigned int* ImageSize);
void RMH_IRThermalCamera_ReadCalFrameMetaData(unsigned short* ThermalData, ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool);
void RMH_IRThermalCamera_ReadCalibrationParameters(unsigned short* ThermalData, ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool);

// --------------------------------------- Kamera Konfigurations Data Håndterings Routiner --------------------------------------- //

void RMH_IRThermalCamera_ReadCameraConfigParameters(unsigned short* ThermalData, ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool);
void RMH_IRThermalCamera_WriteCameraConfigParameter(unsigned int ParameterAddress, float ParameterValue, unsigned short SupportedCameraPool);
void RMH_IRThermalCamera_SaveConfigParametersToCamera(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool);

// --------------------------------------------- Thermodynamiske Udregnings Routiner --------------------------------------------- //

double RMH_IRThermalCamera_CalAtmosphericWaterVaporContribution(double Humidity, double AmbientTemp);
double RMH_IRThermalCamera_CalAtmosphericWaterVaporAttenuation(double Omega, unsigned short DistanceMeters);

// --------------------------------------------- Thermografiske Udregnings Routiner ---------------------------------------------- //

void RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool);
double RMH_IRThermalCamera_ReadPixelTemperature(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short PixelValue, unsigned short SupportedCameraPool);
double RMH_IRThermalCamera_ReadFramePixelTemperature(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short* ThermalData, unsigned short PixelWidth, unsigned short PixelHeight, unsigned short SupportedCameraPool);

// ------------------------------- Recording/Snapshot Analysis Mode Kamera Pool Spesifikke Routine ------------------------------- //

void RMH_IRThermalCamera_WriteDataToVideoRecordingFilesSequence(unsigned short SupportedCameraPool);
bool RMH_IRThermalCamera_ConvertCapturedRawImageDataToSnapshotPNG(unsigned short SupportedCameraPool);

// --------------------------------- Termisk Kamera Pool Specifikke Håndterings/Kontrol Routiner --------------------------------- //

void RMH_IRThermalCamera_AutoShutterCalTimerCallbackHandler();
void RMH_IRThermalCamera_TempDriftBasedCalTimerCallbackHandler();
void RMH_IRThermalCamera_CalibrateThermalCamera();
void RMH_IRThermalCamera_ChangeThermalCameraTemperatureRange();
void RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool1();
void RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool2();
void RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool3();
void RMH_IRThermalCamera_ConnectToThermalCameraOrAnalysisMode();

// ------------------------------------------------------------------------------------------------------------------------------- //

#endif /* RMH_ThermalCameraSupport_Library_H */