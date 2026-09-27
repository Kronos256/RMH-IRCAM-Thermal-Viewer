
/*
 *  RMH_ThermalCameraSupport_Library.c
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

// Inkluderede Blbiloteker
#include <string>
#include <math.h>
#include <iostream>
#include <cstdlib> 
#include "uvc_camera.h"
#include "GlobalObjectsAndVariables.h"
#include "RMH_MathConversions_Library.h"
#include "RMH_ThermalCameraSupport_Library.h"
#include "RMH_SupportedIRCameras_Resources.h"
#include "RMH_Application_ThermalViewer.h"

// Tilhørende Namespaces
using namespace DirectShowCamera;
using namespace ThermalCameraDevice;
using namespace System::Diagnostics;

// Globale Objekter og variabler
UVCCamera IRThermalCamera = UVCCamera();
std::vector<CameraDevice> IRThermalCameraDeivceList;

// ----------------------- USB Kommunikations, Læsnings/Skrivnings, Konfigurations & Håndterings Routiner ------------------------ //

// ------------------------------------------------------------------------------------------------------------------------------- //
//																																   //
//									Routiner & Funktioner Til Support For Følgende Kameraer (Pool 1) ->							   //
//																																   //
//									- InfiRay T2L																				   //
//									- InfiRay T2-Search																			   //
//									- InfiRay T2S+																				   //
//									- InfiRay T2Pro																				   //
//									- InfiRay T3-Search																			   //
//									- InfiRay T3S																				   //
//									- InfiRay T3Pro																				   //
//									- InfiRay DV-DL13	                                                                           //
//									- InfiRay S0 Series																			   //
//									- HTI HT-301																				   //
//																																   //
//									Routiner & Funktioner Til Support For Følgende Kameraer (Pool 2) ->							   //
//																																   //
//									- InfiRay Tiny1-C																			   //
//									- InfiRay P2																				   //
//									- InfiRay P2Pro + Thermal Master P2Pro                                                         //
//									- UNI-T UTi260M                                                                                //  
//									- TOPDON TC001                                                                                 //
//                                  - TOPDON TC002																				   //
//                                  - Victor 328B																				   //
//                                  - LODESTAR L2																				   //
//																																   //
//									Routiner & Funktioner Til Support For Følgende Kameraer (Pool 3) ->							   //
//																																   //
//									- InfiRay T2L V2	    																	   //
//									- InfiRay T2-Search V2																		   //
//									- InfiRay T2S+ V2																			   //
//									- InfiRay T2Pro V2																			   //
//																																   //
//									Routiner & Funktioner Til Support For Følgende Kameraer (Pool 3) ->							   //
//																																   //
//									- Thermal Master P2																			   //
//																																   //
// ------------------------------------------------------------------------------------------------------------------------------- //

// -------------------------------- Kamera Initialiserings, Konfigurations & Håndterings Routiner -------------------------------- //

double RMH_IRThermalCamera_ReadCameraFPS() {

	// Routinen læser og retunerer det forbundet termiske kameras frame rate 

	// Læs og retuner kameraets Frame Rate
	return IRThermalCamera.getFPS();

}

void RMH_IRThermalCamera_StartCapturing() {

	// Routinen starter kameraets video capture

	// Kontroller at kameraet er åbent
	if (IRThermalCamera.isOpened() == true) {

		// Start video capture
		IRThermalCamera.startCapture();

	}

}

void RMH_IRThermalCamera_StopCapturing() {

	// Routinen stopper kameraets video capture

	// Kontroller at kameraet er åbent
	if (IRThermalCamera.isOpened() == true) {

		// Stop video capture
		IRThermalCamera.stopCapture();

	}

}

void RMH_IRThermalCamera_CloseIRCameraDevice() {

	// Routinen stopper og lukker for DirectShow Webcam Devicet
	// Hvilket også deaktiverer video streaming

	// Luk for Video Capture device
	IRThermalCamera.stopCapture();
	IRThermalCamera.close();

}

bool RMH_IRThermalCamera_CheckForCameraDisconnection() {

	// Routinen kontrollerer om kamera forbindelsen blev afbrudt 

	// Retuner forbindelses status
	return IRThermalCamera.checkDisconnection();

}

void RMH_IRThermalCamera_OpenIRCameraDevice(unsigned char IRCameraDeviceIndex, unsigned short SupportedCameraPool) {

	// Routinen Åbner for DirectShow Webcam Devicet, med givet index - Hvilket også aktiverer video streaming

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Åben for valgte Video Capture device - Supporterede Kamera pool 1
			IRThermalCamera.open(IRThermalCameraDeivceList[IRCameraDeviceIndex]);

			// Konfigurer kamera til at give RAW Data
			IRThermalCamera.setZoom(0x8004);

		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2:

			// Åben for valgte Video Capture device - Supporterede Kamera pool 2
			IRThermalCamera.open(IRThermalCameraDeivceList[IRCameraDeviceIndex], _SupporteredeThermalCameraPool2_SensorWidthWithThermalData, _SupporteredeThermalCameraPool2_SensorHeightWithThermalData);

		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Åben for valgte Video Capture device - Supporterede Kamera pool 3
			IRThermalCamera.open(IRThermalCameraDeivceList[IRCameraDeviceIndex]);

			// Konfigurer kamera til at give RAW Data
			//IRThermalCamera.setZoom(0x8081); // Behøves ikke
			IRThermalCamera.setZoom(0x8005);
			//IRThermalCamera.setZoom(0x8004); // Behøves ikke

		break;

		// Supporterede Kamera pool 4
		case _SupportedThermalCameras_Pool_4:

			// Åben for valgte Video Capture device - Supporterede Kamera pool 2
			IRThermalCamera.open(IRThermalCameraDeivceList[IRCameraDeviceIndex], _SupporteredeThermalCameraPool4_SensorWidthWithThermalData, _SupporteredeThermalCameraPool4_SensorHeightWithThermalData);

		break;

	}

	// Konfigurer Kamera til Default temperatur Range
	RMH_IRThermalCamera_SetIRCameraTemperatureRange(_ThermalCamera_TemperatureRange_LowRange, SupportedCameraPool);

	// Kalibrer Termisk Kamera
	RMH_IRThermalCamera_CalibrateIRCamera(SupportedCameraPool);

}

void RMH_IRThermalCamera_CalibrateIRCamera(unsigned short SupportedCameraPool) {

	// Routinen fortager en IR kamera shutter kalibrering

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Fortag en IR Kamera kalibrering
			IRThermalCamera.setZoom(_IRCameraPool1_NUCCalibrationCommand);

		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2:


		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Fortag en IR Kamera kalibrering
			IRThermalCamera.setZoom(_IRCameraPool3_NUCCalibrationCommand);

		break;

		// Supporterede Kamera pool 4
		case _SupportedThermalCameras_Pool_4:


		break;

	}

}

void RMH_IRThermalCamera_SetIRCameraTemperatureRange(unsigned int TemperatureRange, unsigned short SupportedCameraPool) {

	// Routinen konfigurerer IR kameraets Temperatur Range

	/*
	 *  Tilhørende Macroer ->
	 *
	 *  // Termisk Kamera Temperatur Range Reference Macroer 
	 *  #define _ThermalCamera_TemperatureRange_HighRange           1
	 *  #define _ThermalCamera_TemperatureRange_LowRange            0
	 *
	 */

	 // Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Hvilken Temperatur Range skal indstilles
			switch (TemperatureRange) {

				// Konfigurerer IR kameraets Temperatur Range
				case _ThermalCamera_TemperatureRange_HighRange: IRThermalCamera.setZoom(_IRCameraPool1_TemperatureRange_HighRangeREG); break;
				case _ThermalCamera_TemperatureRange_LowRange:  IRThermalCamera.setZoom(_IRCameraPool1_TemperatureRange_LowRangeREG);  break;

			}

		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2:

			// Hvilken Temperatur Range skal indstilles
			switch (TemperatureRange) {

				// Konfigurerer IR kameraets Temperatur Range
				case _ThermalCamera_TemperatureRange_HighRange: break;
				case _ThermalCamera_TemperatureRange_LowRange:  break;

			}

		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Hvilken Temperatur Range skal indstilles
			switch (TemperatureRange) {

				// Konfigurerer IR kameraets Temperatur Range
				case _ThermalCamera_TemperatureRange_HighRange: IRThermalCamera.setZoom(_IRCameraPool3_TemperatureRange_HighRangeREG); break;
				case _ThermalCamera_TemperatureRange_LowRange:  IRThermalCamera.setZoom(_IRCameraPool3_TemperatureRange_LowRangeREG);  break;

			}

		break;

		// Supporterede Kamera pool 4
		case _SupportedThermalCameras_Pool_4:

			// Hvilken Temperatur Range skal indstilles
			switch (TemperatureRange) {

				// Konfigurerer IR kameraets Temperatur Range
				case _ThermalCamera_TemperatureRange_HighRange: break;
				case _ThermalCamera_TemperatureRange_LowRange:  break;

			}

		break;

	}

}

// ÆNDRET 18-11-2025 !!!!!!!
void RMH_IRThermalCamera_InitIRCameraConstants(ThermalCameraDevice::IRCameraDeviceFormat* CameraStatus, unsigned short SupportedCameraPool) {

	// Routinen indstiller tilsluttede IR kameraets kalibrerings, Meta Data og Frame Data konstanter.
	// Hvilket afhænger af IR sensorens fysiske opløsning og supporterede pool

	// Lokale Variabler - Frame Height Munis Meta Data
	unsigned int FrameHeightMinusMeta = CameraStatus->FrameHeight - CameraStatus->FrameMetadataSize;

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// ------------------------------------ Supporterede Kamera Pool 1 ------------------------------------ //

		case _SupportedThermalCameras_Pool_1:

			// Sæt default nul kalibrerings parametere
			CameraStatus->CalValue0Offset = 390.0;
			CameraStatus->CalValue0Fpamul = 7.05;

			// Udregn længden til starten af meta data 1
			CameraStatus->MetaData1Index = CameraStatus->FrameWidth * FrameHeightMinusMeta;

			// Kontroller IR sensorens Pixel bredde
			switch (CameraStatus->FrameWidth) {

				// For 640x IR Sensorer
				case 640:

					// Sæt Detektor temperaturen kalibrerings konstanter
					CameraStatus->fpa_off = 6867;
					CameraStatus->fpa_div = 33.8;
					// Udregn længden til starten af meta data 2
					CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth * 3;

				break;

				// For 384x IR Sensorer
				case 384:

					// Sæt Detektor temperaturen kalibrerings konstanter
					CameraStatus->fpa_off = 7800;
					CameraStatus->fpa_div = 36.0;
					// Udregn længden til starten af meta data 2
					CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth * 3;

				break;

				// For 256x IR Sensorer
				case 256:

					// Sæt Detektor temperaturen kalibrerings konstanter
					CameraStatus->fpa_off = 8617;
					CameraStatus->fpa_div = 37.682;
					// Udregn længden til starten af meta data 2
					CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth;
					// Opdater nul kalibrerings parametere
					CameraStatus->CalValue0Offset = 170.0;
					CameraStatus->CalValue0Fpamul = 0.0;

				break;

				// For 240x IR Sensorer
				case 240:

					// Sæt Detektor temperaturen kalibrerings konstanter
					CameraStatus->fpa_off = 7800;
					CameraStatus->fpa_div = 36.0;
					// Udregn længden til starten af meta data 2
					CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth;

				break;

			}

			// Udregn matrice index for meta data 1 og meta data 2
			CameraStatus->MetaData1Index = CameraStatus->MetaData1Index - 1;
			CameraStatus->MetaData2Index = CameraStatus->MetaData2Index - 1;

		break;

		// ------------------------------------ Supporterede Kamera pool 2 ------------------------------------ //

		case _SupportedThermalCameras_Pool_2:

			// Indstil Meta Data Index 1 for Max/Min/Center frame data
			CameraStatus->MetaData1Index = CameraStatus->FrameWidth * (CameraStatus->FrameHeight - CameraStatus->FrameMetadataSize);

		break;

		// ------------------------------------ Supporterede Kamera Pool 3 ------------------------------------ //

		case _SupportedThermalCameras_Pool_3:

			// Sæt default nul kalibrerings parametere
			CameraStatus->CalValue0Offset = 390.0;
			CameraStatus->CalValue0Fpamul = 7.05;

			// Udregn længden til starten af meta data 1
			CameraStatus->MetaData1Index = CameraStatus->FrameWidth * FrameHeightMinusMeta;

			// Kontroller IR sensorens Pixel bredde
			switch (CameraStatus->FrameWidth) {

				// For 640x IR Sensorer
				case 640:

					// Sæt Detektor temperaturen kalibrerings konstanter
					CameraStatus->fpa_off = 6867;
					CameraStatus->fpa_div = 33.8;
					// Udregn længden til starten af meta data 2
					CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth * 3;

				break;

				// For 384x IR Sensorer
				case 384:

					// Sæt Detektor temperaturen kalibrerings konstanter
					CameraStatus->fpa_off = 7800;
					CameraStatus->fpa_div = 36.0;
					// Udregn længden til starten af meta data 2
					CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth * 3;

				break;

				// For 256x IR Sensorer
				case 256:

					// Sæt Detektor temperaturen kalibrerings konstanter
					CameraStatus->fpa_off = 8617; 
					CameraStatus->fpa_div = 13.9; // 37.682
					// Udregn længden til starten af meta data 2
					CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth;
					// Opdater nul kalibrerings parametere
					//CameraStatus->CalValue0Offset = 170.0;
					//CameraStatus->CalValue0Fpamul = 0.0;

				break;

				// For 240x IR Sensorer
				case 240:

					// Sæt Detektor temperaturen kalibrerings konstanter
					CameraStatus->fpa_off = 7800;
					CameraStatus->fpa_div = 36.0;
					// Udregn længden til starten af meta data 2
					CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth;

				break;

			}

			// Udregn matrice index for meta data 1 og meta data 2
			CameraStatus->MetaData1Index = CameraStatus->MetaData1Index - 1;
			CameraStatus->MetaData2Index = CameraStatus->MetaData2Index - 1;

			// Indstil Meta Data Index 3 for Max/Min/Center frame data
			CameraStatus->MetaData3Index = CameraStatus->FrameWidth * (CameraStatus->FrameHeight - CameraStatus->FrameMetadataSize);

		break;

		// ------------------------------------ Supporterede Kamera pool 4 ------------------------------------ //

		case _SupportedThermalCameras_Pool_4:

			// Indstil Meta Data Index 1
			CameraStatus->MetaData1Index = CameraStatus->FrameWidth * (CameraStatus->FrameHeight - CameraStatus->FrameMetadataSize);
			// Indstil Meta Data Index 2
			CameraStatus->MetaData2Index = CameraStatus->MetaData1Index + CameraStatus->FrameWidth;

		break;

		// ---------------------------------------------------------------------------------------------------- //

	}

}

ThermalCameraDevice::IRCameraDeviceFormat RMH_IRThermalCamera_ConnectToThermalCamera(System::Windows::Forms::ComboBox^ CameraSourceComboBox) {

	// Routinen læser tilgængelige tilsluttede kamera enheder 
	// og forbinder til camera devicet med det givet input navn valgt i kamera device combobox.
	// Routinen retunerer en "ThermalCameraDevice::IRCameraDeviceFormat" klasse
	// 
	// Lokale objekter og variabler
	unsigned int NumberOfCameraDeviceNames = 0;
	std::vector<std::string> CameraDeviceNamesPointer;
	ThermalCameraDevice::IRCameraDeviceFormat CameraStatus;
	
	// Læs tilhørende ComboBox item index værdi
	CameraStatus.SellectedCameraIndex = CameraSourceComboBox->SelectedIndex;

	// Kontroller og opdater tilhørende supporterede kamera pool og tilhørende kamera frame rate parameter
	switch (CameraStatus.SellectedCameraIndex) {

		// Opdater kameraets pool variabel
		case _SupportedThermalCamera_InfiRayT2L:        CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayT2LDeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT2L_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT2LV2:      CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_3; CameraDeviceNamesPointer = InfiRayT2LV2DeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT2LV2_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT2Search:   CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayT2SearchDeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT2Search_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT2SearchV2: CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_3; CameraDeviceNamesPointer = InfiRayT2SearchV2DeviceNames;	CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT2SearchV2_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT2Sp:       CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayT2SpDeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT2Sp_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT2SpV2:     CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_3; CameraDeviceNamesPointer = InfiRayT2SpV2DeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT2SpV2_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT2Pro:      CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayT2ProDeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT2Pro_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT2ProV2:    CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_3; CameraDeviceNamesPointer = InfiRayT2ProV2DeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT2ProV2_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT3Search:   CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayT3SearchDeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT3Search_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT3S:	    CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayT3SDeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT3S_FrameRate; break;
		case _SupportedThermalCamera_InfiRayT3Pro:      CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayT3ProDeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayT3Pro_FrameRate; break;
		case _SupportedThermalCamera_InfiRayP2:         CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_2; CameraDeviceNamesPointer = InfiRayP2DeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayP2_FrameRate; break;
		case _SupportedThermalCamera_ThermalMasterP2:   CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_4; CameraDeviceNamesPointer = ThermalMasterP2DeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_ThermalMasterP2_FrameRate; break;
		case _SupportedThermalCamera_InfiRayP2Pro:      CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_2; CameraDeviceNamesPointer = InfiRayP2ProDeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayP2Pro_FrameRate; break;
		case _SupportedThermalCamera_InfiRayDVDL13:     CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayDVDL13DeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayDVDL13_FrameRate; break;
		case _SupportedThermalCamera_InfiRayS0Series:   CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = InfiRayS0SeriesDeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayS0Series_FrameRate; break;
		case _SupportedThermalCamera_InfiRayTiny1C:     CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_2; CameraDeviceNamesPointer = InfiRayTiny1CDeviceNames;		CameraStatus.FrameRate = _SupportedThermalCamera_InfiRayTiny1C_FrameRate; break;
		case _SupportedThermalCamera_HTIHT301:          CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_1; CameraDeviceNamesPointer = HTIHT301DeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_HTIHT301_FrameRate; break;
		case _SupportedThermalCamera_UNITUTi260M:       CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_2; CameraDeviceNamesPointer = UNITUTi260MDeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_UNITUTi260M_FrameRate; break;
		case _SupportedThermalCamera_TOPDONTC001:       CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_2; CameraDeviceNamesPointer = TOPDONTC001DeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_TOPDONTC001_FrameRate; break;
		case _SupportedThermalCamera_TOPDONTC002:       CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_2; CameraDeviceNamesPointer = TOPDONTC002DeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_TOPDONTC002_FrameRate; break;
		case _SupportedThermalCamera_Victor328B:        CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_2; CameraDeviceNamesPointer = Victor328BDeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_Victor328B_FrameRate; break;	
		case _SupportedThermalCamera_LODESTARL2:        CameraStatus.ThermalCameraSupportPool = _SupportedThermalCameras_Pool_2; CameraDeviceNamesPointer = LODESTARL2DeviceNames;			CameraStatus.FrameRate = _SupportedThermalCamera_LODESTARL2_FrameRate; break;

	}

	// Læs antallet af kamera device navne i tilhørende string array
	NumberOfCameraDeviceNames = CameraDeviceNamesPointer.size();

	// Opdater Kamera connect falg
	CameraStatus.ConnectedFlag = false;

	// Læs tilgændelige forbundet kameraer
	IRThermalCameraDeivceList = IRThermalCamera.getCameras();

	// Er ingen kameraer fundet eller aktive
	if (IRThermalCameraDeivceList.size() == 0) {

		// Opdater Kamera status meddelse
		CameraStatus.StatusMessage = "Error: No Available Thermal Camera Devices Detected!";
		// Opdater Kamera connected status flag
		CameraStatus.ConnectedFlag = false;

	}
	else {

		// Loop igennem alle tilgængelige kameraer
		for (unsigned int i = 0; i < IRThermalCameraDeivceList.size(); i++) {

			// Læs aktive kameras device navne fra array
			CameraStatus.CameraDeviceName = IRThermalCameraDeivceList[i].getFriendlyName();

			// Loop igennem antallet af kamera device navne i tilhørende string array
			for (unsigned int j = 0; j < NumberOfCameraDeviceNames; j++) {

				// Matcher læste device navn med input device navn?
				if (CameraStatus.CameraDeviceName.c_str() == CameraDeviceNamesPointer[j]) {

					// Opdater Kamera connect falg
					CameraStatus.ConnectedFlag = true;
					// Gem kamera index værdien 
					CameraStatus.IRCameraDeviceIndex = i;
					// Bryd indereste for loop
					break;

				}
				else {

					// Opdater Kamera connect falg
					CameraStatus.ConnectedFlag = false;

				}

			}

			// Blev indereste for loop brudt?
			if (CameraStatus.ConnectedFlag == true) {

				// Bryd ydereste for loop
				break;

			}

		}

		// Hvis valgte kamera blev fundet i device liste arrayet -> Forbind til kamaraet 
		if (CameraStatus.ConnectedFlag == true) {

			// Stop Video Capture og luk for kameraet
			RMH_IRThermalCamera_CloseIRCameraDevice();
			// Nulstil Kamera "isStreaming" status flag
			CameraStatus.isStreaming = false;

			// Åben valgte kamera til video stream
			RMH_IRThermalCamera_OpenIRCameraDevice(CameraStatus.IRCameraDeviceIndex, CameraStatus.ThermalCameraSupportPool);

			// Opdater Kamera device info - Frame Width
			CameraStatus.FrameWidth = IRThermalCamera.getWidth();
			// Opdater Kamera device info - Frame Height
			CameraStatus.FrameHeight = IRThermalCamera.getHeight();

			// Læs det termiske kameras tilhørende supporterede kamera pool 
			switch (CameraStatus.ThermalCameraSupportPool) {

				// Opdater Kamera device info - MetaData Størrelse
				case _SupportedThermalCameras_Pool_1: CameraStatus.FrameMetadataSize = round((float)CameraStatus.FrameHeight - (float)CameraStatus.FrameWidth / (float)_FixedThermalCameraFrame_AspectRatio_Pool_1); break;
				case _SupportedThermalCameras_Pool_2: CameraStatus.FrameMetadataSize = round((float)CameraStatus.FrameHeight - (float)CameraStatus.FrameWidth / (float)_FixedThermalCameraFrame_AspectRatio_Pool_2); break;
				case _SupportedThermalCameras_Pool_3: CameraStatus.FrameMetadataSize = round((float)CameraStatus.FrameHeight - (float)CameraStatus.FrameWidth / (float)_FixedThermalCameraFrame_AspectRatio_Pool_3); break;
				case _SupportedThermalCameras_Pool_4: CameraStatus.FrameMetadataSize = round((float)CameraStatus.FrameHeight - (float)CameraStatus.FrameWidth / (float)_FixedThermalCameraFrame_AspectRatio_Pool_4); break;

			}

			// Læs kameraets system device path
			CameraStatus.CameraSystemDevicePath = IRThermalCameraDeivceList[CameraStatus.IRCameraDeviceIndex].getDevicePath();

			// Læs IR Kameraets Operative Konstanter - Relativt til supporterede pool
			RMH_IRThermalCamera_InitIRCameraConstants(&CameraStatus, CameraStatus.ThermalCameraSupportPool);

			// Opdater Kamera status meddelse
			CameraStatus.StatusMessage = "Thermal Camera Is Connected And Ready.";

		}
		else {

			// Stop Video Capture og luk for kameraet
			RMH_IRThermalCamera_CloseIRCameraDevice();
			// Nulstil Kamera "isStreaming" status flag
			CameraStatus.isStreaming = false;

			// Opdater Kamera status meddelse
			CameraStatus.StatusMessage = "Error: Could Not Connect To The Selected Thermal Camera!";

			// Nulstil kameras device navn fra klasse objekt
			CameraStatus.CameraDeviceName = "NAN";
			// Nulstil kameraets system device path
			CameraStatus.CameraSystemDevicePath = "NAN";
			// Nulstil kamera index værdien 
			CameraStatus.IRCameraDeviceIndex = 0;
			// Nulstil Kamera device info - Frame Width
			CameraStatus.FrameWidth = 0;
			// Nulstil Kamera device info - Frame Height
			CameraStatus.FrameHeight = 0;
			// Nulstil Kamera device info - MetaData Størrelse
			CameraStatus.FrameMetadataSize = 0;

			// Nulstil IR Kameraets Operative Konstanter
			CameraStatus.fpa_off = 0.0;
			CameraStatus.fpa_div = 0.0;
			CameraStatus.CalValue0Offset = 0.0;
			CameraStatus.CalValue0Fpamul = 0.0;
			CameraStatus.MetaData1Index = 0;
			CameraStatus.MetaData2Index = 0;

		}

	}

	// Retuner kamera status
	return CameraStatus;

}

// ---------------------------------- Rå Billede Data Til Rå Termisk Data Konverterings Routine ---------------------------------- //

double RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned char* YUY2in, unsigned short* ThermalDataRaw) {

	// Routinen konverterer de Rå 24Bit YUY2 kamera data til et 14Bit Rå Termografisk data array, som indeholder de Rå termiske kamera sensor intensitets værdier
	// Maximum, Minimum og Center dataen bliver tilføjet i slutningen af det termiske data array, hvis valgte termiske kamera pool har behov for dette.
	// Formatet at det tilføjet Maximum, Minimum og Center data (i slutningen af det termiske data array) er: [Max_X Max_Y Max_Raw Min_X Min_Y Min_Raw Center_Raw].
	// Disse har følgende index værdier: (FrameHeightOffset * FrameWidth) + n -> n = 0 - 6
	// Routinen retunerer konverterede ThermalDataens Gennemsnitlige værdi som et 32Bit Double.

	// Lokale variabler
	unsigned short PixelXCoordinate = 0;
	unsigned short PixelYCoordinate = 0;
	unsigned short CenterPixelValue = 0;
	unsigned short CenterPixelIndex = 0;
	unsigned short MaximumPixelValue = 0;
	unsigned short MaximumPixelXCoord = 0;
	unsigned short MaximumPixelYCoord = 0;
	unsigned short MinimumPixelValue = 65535;
	unsigned short MinimumPixelXCoord = 0;
	unsigned short MinimumPixelYCoord = 0;
	unsigned short Pixel16BitValue[4];
	bool AddMaxMinCenterDataToThermalDataArray = false;
	unsigned int AddMaxMinCenterStopIndex = 0;
	unsigned int FrameDataArrayOffset = (IRCamera->FrameHeightPixelOffset * IRCamera->FrameWidth) + IRCamera->FrameWidthPixelOffset;
	bool PerformNonUniformityCorrection = false;
	unsigned long long int ThermalDataAverageValue = 0;
	unsigned long FrameSizeMinusMeta = IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize);

	// Kontroller hvilken Termisk kamera pool er blevet valgt
	switch (IRCamera->ThermalCameraSupportPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Konverter alle data bytes
			IRCamera->FrameHeight = IRCamera->FrameHeight;

			// Max/Min/Center data skal IKKE tilføjes til slutningen af det termiske frame data array
			// Da de allerede indgår som en del af frame meta dataen
			AddMaxMinCenterDataToThermalDataArray = false;

			// Indstil Stop index for Max/Min/Center data
			AddMaxMinCenterStopIndex = IRCamera->FrameWidth * IRCamera->FrameHeight;

			// Fortag Ikke Non-Uniformity Korrektion af billede data
			PerformNonUniformityCorrection = false;

		break;

		// Supporterede Kamera pool 2 Og 4
		case _SupportedThermalCameras_Pool_2: case _SupportedThermalCameras_Pool_4:

			// Konverter Kun Meta Data området
			IRCamera->FrameHeight = IRCamera->FrameHeight;
					
			// Udregn Center pixels array index værdien
			CenterPixelIndex = ((IRCamera->FrameHeight - IRCamera->FrameMetadataSize) * 0.5) * IRCamera->FrameWidth + (IRCamera->FrameWidth * 0.5);

			// Max/Min/Center data skal tilføjes til slutningen af det termiske frame data array
			AddMaxMinCenterDataToThermalDataArray = true;

			// Indstil Stop index for Max/Min/Center data
			AddMaxMinCenterStopIndex = IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize);

		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3: 

			// Konverter alle data bytes
			IRCamera->FrameHeight = IRCamera->FrameHeight;

			// Udregn Center pixels array index værdien
			CenterPixelIndex = ((IRCamera->FrameHeight - IRCamera->FrameMetadataSize) * 0.5) * IRCamera->FrameWidth + (IRCamera->FrameWidth * 0.5);

			// Max/Min/Center data skal tilføjes til slutningen af det termiske frame data array
			AddMaxMinCenterDataToThermalDataArray = true;

			// Indstil Stop index for Max/Min/Center data
			AddMaxMinCenterStopIndex = IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize);

			// Fortag Non-Uniformity Korrektion af billede data
			PerformNonUniformityCorrection = true;

		break;

	}

	// Loop igennem alle YUY2 bånd pixels - FrameDataArrayOffset * 2 -> (2 x 8Bit)
	for (unsigned int i = 0, j = FrameDataArrayOffset * 2; i < (IRCamera->FrameWidth * IRCamera->FrameHeight); i += 4, j += 8) {
		
		// Læs og konverter kameraets bånds data til 16Bit Pixel data (14Bit Full-Scale) - YUY2 High og Low Byte til samlede 16Bit integer
		Pixel16BitValue[0] = ((unsigned short)(*(YUY2in + (j + 1))) << 8) | ((unsigned short)*(YUY2in + (j + 0)));
		Pixel16BitValue[1] = ((unsigned short)(*(YUY2in + (j + 3))) << 8) | ((unsigned short)*(YUY2in + (j + 2)));
		Pixel16BitValue[2] = ((unsigned short)(*(YUY2in + (j + 5))) << 8) | ((unsigned short)*(YUY2in + (j + 4)));
		Pixel16BitValue[3] = ((unsigned short)(*(YUY2in + (j + 7))) << 8) | ((unsigned short)*(YUY2in + (j + 6)));
	
		// Begræns ikke 16bit pixel værdier i Meta data området
		if (i < FrameSizeMinusMeta) {

			// Skal billede data Non-Uniformity Korrigeres
			if (PerformNonUniformityCorrection == true) {

				// Fortage Non-Uniformity Korrektion af billede data ved at trække Non-Uniformity map dataen fra.
				Pixel16BitValue[0] = (unsigned short)((double)(Pixel16BitValue[0]) - ImageCMOSNonUniformityMapData[i + 0]);
				Pixel16BitValue[1] = (unsigned short)((double)(Pixel16BitValue[1]) - ImageCMOSNonUniformityMapData[i + 1]);
				Pixel16BitValue[2] = (unsigned short)((double)(Pixel16BitValue[2]) - ImageCMOSNonUniformityMapData[i + 2]);
				Pixel16BitValue[3] = (unsigned short)((double)(Pixel16BitValue[3]) - ImageCMOSNonUniformityMapData[i + 3]);

				// Begræns maksimal pixel værdierne til 14Bit Full-Scale 
				if (Pixel16BitValue[0] > _ImageProcessing_ImageResolution_14Bit) { Pixel16BitValue[0] = _ImageProcessing_ImageResolution_14Bit; }
				if (Pixel16BitValue[1] > _ImageProcessing_ImageResolution_14Bit) { Pixel16BitValue[1] = _ImageProcessing_ImageResolution_14Bit; }
				if (Pixel16BitValue[2] > _ImageProcessing_ImageResolution_14Bit) { Pixel16BitValue[2] = _ImageProcessing_ImageResolution_14Bit; }
				if (Pixel16BitValue[3] > _ImageProcessing_ImageResolution_14Bit) { Pixel16BitValue[3] = _ImageProcessing_ImageResolution_14Bit; }

			}

			// Akkumiler konverterede værdier til samlede sum
			ThermalDataAverageValue = ThermalDataAverageValue + (Pixel16BitValue[0] + Pixel16BitValue[1] + Pixel16BitValue[2] + Pixel16BitValue[3]);

		}

		// Skal Max/Min/Center data tilføjes til slutningen af det termiske frame data array
		if (AddMaxMinCenterDataToThermalDataArray == true) {

			// Loop for hver læst bånd pixel værdi
			for (unsigned int n = 0; n < 4; n++) {

				// Kontroler stop index for Max/Min/Center værdier
				if (i < AddMaxMinCenterStopIndex) {

					// Kontroller for Maximum pixel værdi
					if (Pixel16BitValue[n] > MaximumPixelValue) {

						// Opdater Maximum Pixel værdi
						MaximumPixelValue = Pixel16BitValue[n];

						// Læs Maximum værdiens X/Y Koordinater
						MaximumPixelXCoord = PixelXCoordinate;
						MaximumPixelYCoord = PixelYCoordinate;

					}

					// Kontroller for Minimum pixel værdi
					if (Pixel16BitValue[n] < MinimumPixelValue) {

						// Opdater Minimum Pixel værdi
						MinimumPixelValue = Pixel16BitValue[n];

						// Læs Minimum værdiens X/Y Koordinater
						MinimumPixelXCoord = PixelXCoordinate;
						MinimumPixelYCoord = PixelYCoordinate;

					}

					// Inkrementer Pixel X koordinat variablet 
					PixelXCoordinate = PixelXCoordinate + 1;

					// Hvis X koordinat variablet er over eller lig med Frame bredden
					if (PixelXCoordinate >= IRCamera->FrameWidth) {

						// Nulstil Pixel X koordinatet
						PixelXCoordinate = 0;

						// Inkrementer Pixel Y koordinat variablet 
						PixelYCoordinate = PixelYCoordinate + 1;

						// Hvis Y koordinat variablet er over eller lig med Frame højden
						if (PixelYCoordinate >= IRCamera->FrameHeight) {

							// Nulstil Pixel Y koordinatet
							PixelYCoordinate = 0;

						}

					}

				}

			}

		}

		// Skriv konverterede pixel værdier til pointer array
		*(ThermalDataRaw + (i + 0)) = Pixel16BitValue[0];
		*(ThermalDataRaw + (i + 1)) = Pixel16BitValue[1];
		*(ThermalDataRaw + (i + 2)) = Pixel16BitValue[2];
		*(ThermalDataRaw + (i + 3)) = Pixel16BitValue[3];

	}

	// Skal Max/Min/Center data tilføjes til slutningen af det termiske frame data array
	if (AddMaxMinCenterDataToThermalDataArray == true) {

		// Tilføj Max/Min/Center data til slutningen af det termiske frame data array
		*(ThermalDataRaw + (IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize)) + 0) = MaximumPixelXCoord;
		*(ThermalDataRaw + (IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize)) + 1) = MaximumPixelYCoord;
		*(ThermalDataRaw + (IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize)) + 2) = MaximumPixelValue;
		*(ThermalDataRaw + (IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize)) + 3) = MinimumPixelXCoord;
		*(ThermalDataRaw + (IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize)) + 4) = MinimumPixelYCoord;
		*(ThermalDataRaw + (IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize)) + 5) = MinimumPixelValue;
		*(ThermalDataRaw + (IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize)) + 6) = *(ThermalDataRaw + CenterPixelIndex);

	}

	// Retuner Den termiske Frame datas gennemsnitlige værdi
	return (double)ThermalDataAverageValue / (double)FrameSizeMinusMeta;

}

void RMH_IRThermalCamera_Convert14BitThermalDataArrayToYUY2(unsigned short* ThermalData, unsigned char* YUY2Out, unsigned int FrameWidth, unsigned int FrameHeight) {

	// Routinen konverterer et givet 16Bit (14Bit Full-Scale) Termografisk data array til et YUY2 array.
	// Routinen benyttes som en del af "Recording analysis mode" NUC data kompenseringen, når der skal gemmes video data som er NUC korrigerede.

	// Loop igennem alle Termografisk data array pixels
	for (unsigned int i = 0, j = 0; i < (FrameWidth * FrameHeight); i += 4, j += 8) {

		// Konverter Termografisk data array til et YUY2 array
		*(YUY2Out + (j + 0)) = (unsigned char)(ThermalData[i + 0] & 0x00FF);
		*(YUY2Out + (j + 1)) = (unsigned char)((ThermalData[i + 0] & 0xFF00) >> 8);
		*(YUY2Out + (j + 2)) = (unsigned char)(ThermalData[i + 1] & 0x00FF);
		*(YUY2Out + (j + 3)) = (unsigned char)((ThermalData[i + 1] & 0xFF00) >> 8);
		*(YUY2Out + (j + 4)) = (unsigned char)(ThermalData[i + 2] & 0x00FF);
		*(YUY2Out + (j + 5)) = (unsigned char)((ThermalData[i + 2] & 0xFF00) >> 8);
		*(YUY2Out + (j + 6)) = (unsigned char)(ThermalData[i + 3] & 0x00FF);
		*(YUY2Out + (j + 7)) = (unsigned char)((ThermalData[i + 3] & 0xFF00) >> 8);

	}

}

// --------------------------------- Termisk Kamera Pool Specifikke Billede Processerings Routine -------------------------------- //

void RMH_IRThermalCamera_LinearAutomaticGainControlTemp(unsigned short* ThermalData, unsigned short* GainGrayscale, unsigned int FrameWidth, unsigned int FrameHeight, double MaxOutPixelVal, double MinOutPixelVal, double MaxInPixelVal, double MinInPixelVal, float TempUnitScaleFactor, float TempUnitOffsetFactor) {

	// Routinen implementerer Linear Automatisk Gain Kontrol til et input billede data array
	// AGC billede dataer er derfra passerede videre til pointer arrayet.
	// Min Algoritme er liniariceret som: y = a * x + b

	// Lokale variabler - Lager i CPU register
	register double PixelValue1 = 0.0;
	register double PixelValue2 = 0.0;
	register double PixelValue3 = 0.0;
	register double PixelValue4 = 0.0;
	
	// Udregn linear skallerings faktoren (a Parameter)
	double LinearScaleFactor = ((double)MinOutPixelVal - (double)MaxOutPixelVal) / ((double)MinInPixelVal - (double)MaxInPixelVal);
	// Udregn linear Offset skalleringen (b Parameter)
	double OffsetScale = -LinearScaleFactor * (double)MaxInPixelVal + (double)MaxOutPixelVal;

	// Loop til og med frame opløsningen W * H
	for (unsigned int i = 0; i < (FrameWidth * FrameHeight); i += 4) {

		// Hvilken supporterede kamera pool er valgt (Gælder for både Pool 1 og 3)
		if (IRCamera.ThermalCameraSupportPool == _SupportedThermalCameras_Pool_1 || IRCamera.ThermalCameraSupportPool == _SupportedThermalCameras_Pool_3) {

			// Udregn Pixel temperaturen fra rå pixel data
			PixelValue1 = *(ThermalData + i);
			PixelValue2 = *(ThermalData + i + 1);
			PixelValue3 = *(ThermalData + i + 2);
			PixelValue4 = *(ThermalData + i + 3);

			// Læs Pixel Temperatur fra Look-up Tabel
			PixelValue1 = IRCamera.TemperatureLookUpTabel[*(ThermalData + i) & 0x3FFF];
			PixelValue2 = IRCamera.TemperatureLookUpTabel[*(ThermalData + i + 1) & 0x3FFF];
			PixelValue3 = IRCamera.TemperatureLookUpTabel[*(ThermalData + i + 2) & 0x3FFF];
			PixelValue4 = IRCamera.TemperatureLookUpTabel[*(ThermalData + i + 3) & 0x3FFF];

		}
		else if (IRCamera.ThermalCameraSupportPool == _SupportedThermalCameras_Pool_2 || IRCamera.ThermalCameraSupportPool == _SupportedThermalCameras_Pool_4) {

			// Udregn Pixel temperaturen fra rå pixel data
			PixelValue1 = (*(ThermalData + i) * 0.015625) - 273.15;
			PixelValue2 = (*(ThermalData + i + 1) * 0.015625) - 273.15;
			PixelValue3 = (*(ThermalData + i + 2) * 0.015625) - 273.15;
			PixelValue4 = (*(ThermalData + i + 3) * 0.015625) - 273.15;

			// Kompenser for miljø bidraget til temperatur udregningerne
			PixelValue1 = PixelValue1 * IRCamera.ObjectEnvirTempCorrectionFactor + IRCamera.ObjectEnvirTempCorrectionOffset;
			PixelValue2 = PixelValue2 * IRCamera.ObjectEnvirTempCorrectionFactor + IRCamera.ObjectEnvirTempCorrectionOffset;
			PixelValue3 = PixelValue3 * IRCamera.ObjectEnvirTempCorrectionFactor + IRCamera.ObjectEnvirTempCorrectionOffset;
			PixelValue4 = PixelValue4 * IRCamera.ObjectEnvirTempCorrectionFactor + IRCamera.ObjectEnvirTempCorrectionOffset;

			// Kompender for temperatur korrektion 
			PixelValue1 = PixelValue1 + IRCamera.TemperatureCorrectionSetting;
			PixelValue2 = PixelValue2 + IRCamera.TemperatureCorrectionSetting;
			PixelValue3 = PixelValue3 + IRCamera.TemperatureCorrectionSetting;
			PixelValue4 = PixelValue4 + IRCamera.TemperatureCorrectionSetting;

		}

		// Kompenser for temperatur enhed
		PixelValue1 = (PixelValue1 * TempUnitScaleFactor) + TempUnitOffsetFactor;
		PixelValue2 = (PixelValue2 * TempUnitScaleFactor) + TempUnitOffsetFactor;
		PixelValue3 = (PixelValue3 * TempUnitScaleFactor) + TempUnitOffsetFactor;
		PixelValue4 = (PixelValue4 * TempUnitScaleFactor) + TempUnitOffsetFactor;

		// Begræns pixel værdierne - Fortages for at undgå pixel overflow
		if (PixelValue1 >= MaxInPixelVal) { PixelValue1 = MaxInPixelVal; }
		if (PixelValue1 <= MinInPixelVal) { PixelValue1 = MinInPixelVal; }
		if (PixelValue2 >= MaxInPixelVal) { PixelValue2 = MaxInPixelVal; }
		if (PixelValue2 <= MinInPixelVal) { PixelValue2 = MinInPixelVal; }
		if (PixelValue3 >= MaxInPixelVal) { PixelValue3 = MaxInPixelVal; }
		if (PixelValue3 <= MinInPixelVal) { PixelValue3 = MinInPixelVal; }
		if (PixelValue4 >= MaxInPixelVal) { PixelValue4 = MaxInPixelVal; }
		if (PixelValue4 <= MinInPixelVal) { PixelValue4 = MinInPixelVal; }

		// Skaller Pixel værdier til givet skallerings og offset faktor
		*(GainGrayscale + i) = (unsigned short)(LinearScaleFactor * PixelValue1 + OffsetScale);
		*(GainGrayscale + i + 1) = (unsigned short)(LinearScaleFactor * PixelValue2 + OffsetScale);
		*(GainGrayscale + i + 2) = (unsigned short)(LinearScaleFactor * PixelValue3 + OffsetScale);
		*(GainGrayscale + i + 3) = (unsigned short)(LinearScaleFactor * PixelValue4 + OffsetScale);

	}

}

// --------------------------------- Termisk Kamera Region Of Interest (ROI) Håndterings Routine --------------------------------- //

ROIAreaPixelInfoFormat RMH_IRThermalCamera_ReadROIAreaPixelInfoInsideFrameArea(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short* ThermalData, unsigned int FrameWidth, unsigned int AreaX0Pos, unsigned int AreaY0Pos, unsigned int AreaWidth, unsigned int AreaHeight, bool ReturnROIPixels, unsigned short* ROIAreaRawPixelValues, unsigned short SupportedCameraPool) {

	// Routinen læser ROI Arealets pixel informations værdier indenfor et givet frame data areal.
	// Og ligeledes læser frame højde og bredde kordinatet for Max/Min temperaturerne.
	// Alle andre Rå pixel værdier, inden for arealet, bliver ligeledes læst og retunerede til pointer array.

	// Lokale variabler
	register double PixelTempValue = 0.0;
	register double PixelAvgTempValue = 0.0;
	register unsigned short PixelValue = 0;
	register unsigned int AreaStartIndex = 0;
	register unsigned int AreaStopIndex = 0;
	register unsigned int RawPixlDataIndex = 0;
	register unsigned int ROINumberOfPixels = 0;
	register ROIAreaPixelInfoFormat ROIPixelData;

	// Initiliser start værdier for Max/Min
	ROIPixelData.MaxValue = -10000;
	ROIPixelData.MinValue = 10000;

	// Læs ROI arealets antal pixels
	ROIPixelData.ROIAreaNmbOfPixels = AreaWidth * AreaHeight;

	// Udregn Start og Stop index værdierne for den aktive areal
	AreaStartIndex = (AreaY0Pos * FrameWidth) + AreaX0Pos;
	AreaStopIndex = AreaStartIndex + AreaWidth;

	// Nulstil ROI Gennemsnitlig temperatur værdi
	PixelAvgTempValue = 0.0;
	// Nulstil Antal ROI pixels variabel
	ROINumberOfPixels = 0;

	// Loop igennem alle arealets pixel rækker
	for (unsigned int i = 0; i < AreaHeight; i++) {

		// Find Maximum og Minimum Pixel værdien for hver frame pixel række
		for (unsigned int j = AreaStartIndex, k = 0; j < AreaStopIndex; j++, k++) {

			// Inkrementer antallet af ROI Pixels
			ROINumberOfPixels = ROINumberOfPixels + 1;

			// Læs frame pixel temperatur dataen
			PixelValue = *(ThermalData + j);

			// Skal ROI arealets Rå pixel værdier retuneres til pointer array
			if (ReturnROIPixels == true) {

				// Lager ROIets Rå Pixel værdier i array på output format. 
				*(ROIAreaRawPixelValues + RawPixlDataIndex) = PixelValue;

				// Inkrementer Rå pixel data indeks
				RawPixlDataIndex = RawPixlDataIndex + 1;

			}

			// Hvilken supporterede kamera pool er valgt (Gælder for både Pool 1 og 3)
			if (SupportedCameraPool == _SupportedThermalCameras_Pool_1 || SupportedCameraPool == _SupportedThermalCameras_Pool_3) {

				// Læs Pixel Temperatur fra Look-up Tabel
				PixelTempValue = IRCamera->TemperatureLookUpTabel[PixelValue & 0x3FFF];

			}
			// Gældende for både Pool 2 og 4
			else if (SupportedCameraPool == _SupportedThermalCameras_Pool_2 || SupportedCameraPool == _SupportedThermalCameras_Pool_4) {

				// Udregn Pixel temperaturen fra rå pixel data
				PixelTempValue = (PixelValue * 0.015625) - 273.15;
				// Kompenser for miljø bidraget til temperatur udregningerne
				PixelTempValue = PixelTempValue * IRCamera->ObjectEnvirTempCorrectionFactor + IRCamera->ObjectEnvirTempCorrectionOffset;
				// Kompender for temperatur korrektion 
				PixelTempValue = PixelTempValue + IRCamera->TemperatureCorrectionSetting;

			}

			// Akkumulere summen af alle ROI pixel værdiers temperatur sum
			PixelAvgTempValue = PixelAvgTempValue + PixelTempValue;

			// Kontroller for Maximum pixel værdi
			if (PixelTempValue > ROIPixelData.MaxValue) {

				// Opdater Maximum Pixel værdi
				ROIPixelData.MaxValue = PixelTempValue;

				// Lager Maximum temperaturens Frame W/H Kordinater
				ROIPixelData.ROIMaxPixelWidth = (AreaX0Pos + k);
				ROIPixelData.ROIMaxPixelHeight = (AreaY0Pos + i);

			}

			// Kontroller for Minimum pixel værdi
			if (PixelTempValue < ROIPixelData.MinValue) {

				// Opdater Minimum Pixel værdi
				ROIPixelData.MinValue = PixelTempValue;

				// Lager Minimum temperaturens Frame W/H Kordinater
				ROIPixelData.ROIMinPixelWidth = (AreaX0Pos + k);
				ROIPixelData.ROIMinPixelHeight = (AreaY0Pos + i);

			}

		}

		// Inkrementer til næste aktive areal data række
		AreaStartIndex = AreaStartIndex + FrameWidth;
		AreaStopIndex = AreaStopIndex + FrameWidth;

	}

	// Udregn ROI Arealets gennemsnitlige temperatur
	ROIPixelData.AvgValue = PixelAvgTempValue / (double)ROINumberOfPixels;

	// Retuner Maximum og Minimum Pixel format
	return ROIPixelData;

}

// -------------------------------------------- Kamera Frame Data Håndterings Routiner ------------------------------------------- //

bool RMH_IRThermalCamera_ReadFrameRaw(unsigned char* ImageData, unsigned int* ImageSize) {

	// Routinen læser og retunerer en Rå data frame fra kameraet

	// Retuner Kamera data frame
	return IRThermalCamera.getFrame(ImageData, (int*)ImageSize, true);

}

void RMH_IRThermalCamera_ReadCalFrameMetaData(unsigned short* ThermalData, ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool) {

	// Routinen Læser IR kameraets frame Meta Data og Udregner Interne IR Sensor Temperaturer

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Læs og Udregn IR Kameraets Detektor temperaturen
			IRCamera->temp_fpa_Raw = (double)(*(ThermalData + (IRCamera->MetaData1Index + 2)));
			IRCamera->temp_fpa = 20.0 - ((double)(IRCamera->temp_fpa_Raw - IRCamera->fpa_off)) / IRCamera->fpa_div;

			// Læs og Udregn IR Kameraets Shutter temperaturen
			IRCamera->temp_shutter_Raw = *(ThermalData + (IRCamera->MetaData2Index + 2));
			IRCamera->temp_shutter = (double)(IRCamera->temp_shutter_Raw) / 10.0 - 273.15;

			// Læs og Udregn IR Kameraets Core temperaturen
			IRCamera->temp_core_Raw = *(ThermalData + (IRCamera->MetaData2Index + 3));
			IRCamera->temp_core = (double)(IRCamera->temp_core_Raw) / 10.0 - 273.15;

			// Læs Max, Min og Center punkternes Rå temperatur og kordinat Data
			IRCamera->Tmax_X =         *(ThermalData + (IRCamera->MetaData1Index + 3));
			IRCamera->Tmax_Y =         *(ThermalData + (IRCamera->MetaData1Index + 4));
			IRCamera->Tmax_Tmp_Raw =   *(ThermalData + (IRCamera->MetaData1Index + 5));
			IRCamera->Tmin_X =         *(ThermalData + (IRCamera->MetaData1Index + 6));
			IRCamera->Tmin_Y =         *(ThermalData + (IRCamera->MetaData1Index + 7));
			IRCamera->Tmin_Tmp_Raw =   *(ThermalData + (IRCamera->MetaData1Index + 8));
			IRCamera->Center_Tmp_Raw = *(ThermalData + (IRCamera->MetaData1Index + 13));

		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2:

			// Læs og Udregn IR Kameraets Detektor temperaturen - Ikke Supporterede Endnu! (Skal Være 1!!)
			IRCamera->temp_fpa_Raw = 1;
			IRCamera->temp_fpa = 1;

			// Læs og Udregn IR Kameraets Shutter temperaturen - Ikke Supporterede Endnu! (Skal Være 1!!)
			IRCamera->temp_shutter_Raw = 1;
			IRCamera->temp_shutter = 1;

			// Læs og Udregn IR Kameraets Core temperaturen - Ikke Supporterede Endnu! (Skal Være 1!!)
			IRCamera->temp_core_Raw = 1;
			IRCamera->temp_core = 1;

			// Læs Max, Min og Center punkternes Rå temperatur og kordinat Data
			IRCamera->Tmax_X =         *(ThermalData + (IRCamera->MetaData1Index + 0));
			IRCamera->Tmax_Y =         *(ThermalData + (IRCamera->MetaData1Index + 1));
			IRCamera->Tmax_Tmp_Raw =   *(ThermalData + (IRCamera->MetaData1Index + 2));
			IRCamera->Tmin_X =         *(ThermalData + (IRCamera->MetaData1Index + 3));
			IRCamera->Tmin_Y =         *(ThermalData + (IRCamera->MetaData1Index + 4));
			IRCamera->Tmin_Tmp_Raw =   *(ThermalData + (IRCamera->MetaData1Index + 5));
			IRCamera->Center_Tmp_Raw = *(ThermalData + (IRCamera->MetaData1Index + 6));

		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Læs og Udregn IR Kameraets Detektor temperaturen
			IRCamera->temp_fpa_Raw = (double)(*(ThermalData + (IRCamera->MetaData1Index + 2)));
			IRCamera->temp_fpa = 20.0 - ((double)(IRCamera->temp_fpa_Raw - IRCamera->fpa_off)) / IRCamera->fpa_div;

			// Læs og Udregn IR Kameraets Shutter temperaturen
			IRCamera->temp_shutter_Raw = *(ThermalData + (IRCamera->MetaData2Index + 2));
			IRCamera->temp_shutter = ((((double)(IRCamera->temp_shutter_Raw) * 0.625) + 2731.5) / 10.0) - 273.15;

			// Læs og Udregn IR Kameraets Core temperaturen - V2 Raporterer Ikke Core Temp!
			IRCamera->temp_core_Raw = *(ThermalData + (IRCamera->MetaData2Index + 3));
			IRCamera->temp_core = ((((double)(IRCamera->temp_core_Raw) * 0.625) + 2731.5) / 10.0) - 273.15;

			// Læs Max, Min og Center punkternes Rå temperatur og kordinat Data
			IRCamera->Tmax_X =         *(ThermalData + (IRCamera->MetaData3Index + 0));
			IRCamera->Tmax_Y =         *(ThermalData + (IRCamera->MetaData3Index + 1));
			IRCamera->Tmax_Tmp_Raw =   *(ThermalData + (IRCamera->MetaData3Index + 2));
			IRCamera->Tmin_X =         *(ThermalData + (IRCamera->MetaData3Index + 3));
			IRCamera->Tmin_Y =         *(ThermalData + (IRCamera->MetaData3Index + 4));
			IRCamera->Tmin_Tmp_Raw =   *(ThermalData + (IRCamera->MetaData3Index + 5));
			IRCamera->Center_Tmp_Raw = *(ThermalData + (IRCamera->MetaData3Index + 6));

		break;

		// Supporterede Kamera pool 4
		case _SupportedThermalCameras_Pool_4:

			// Læs og Udregn IR Kameraets Detektor temperaturen - Ikke Supporterede Endnu! (Skal Være 1!!)
			IRCamera->temp_fpa_Raw = 1;
			IRCamera->temp_fpa = 1;

			// Læs og Udregn IR Kameraets Shutter temperaturen - Ikke Supporterede Endnu! (Skal Være 1!!)
			IRCamera->temp_shutter_Raw = 1;
			IRCamera->temp_shutter = 1;

			// Læs og Udregn IR Kameraets Core temperaturen - Ikke Supporterede Endnu! (Skal Være 1!!)
			IRCamera->temp_core_Raw = 1;
			IRCamera->temp_core = 1;

			// Læs Max, Min og Center punkternes Rå temperatur og kordinat Data
			IRCamera->Tmax_X = *(ThermalData + (IRCamera->MetaData1Index + 0));
			IRCamera->Tmax_Y = *(ThermalData + (IRCamera->MetaData1Index + 1));
			IRCamera->Tmax_Tmp_Raw = *(ThermalData + (IRCamera->MetaData1Index + 2));
			IRCamera->Tmin_X = *(ThermalData + (IRCamera->MetaData1Index + 3));
			IRCamera->Tmin_Y = *(ThermalData + (IRCamera->MetaData1Index + 4));
			IRCamera->Tmin_Tmp_Raw = *(ThermalData + (IRCamera->MetaData1Index + 5));
			IRCamera->Center_Tmp_Raw = *(ThermalData + (IRCamera->MetaData1Index + 6));

		break;

	}

}

void RMH_IRThermalCamera_ReadCalibrationParameters(unsigned short* ThermalData, ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool) {

	// Routinen læser IR Kameraets interne kalibrerings parameter
	// Som skal benyttes til at udregne temperatur Look-Op Tabellen

	// Lokale variabler
	unsigned int MetaCal16BitSizeOffset = 2;

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Aflæs IR Kameras interne kalibrerings parameter
			IRCamera->CalValue0 = *(ThermalData + (IRCamera->MetaData2Index + 1));
			IRCamera->CalValue1 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 3 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 4 + MetaCal16BitSizeOffset)));
			IRCamera->CalValue2 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 5 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 6 + MetaCal16BitSizeOffset)));
			IRCamera->CalValue3 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 7 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 8 + MetaCal16BitSizeOffset)));
			IRCamera->CalValue4 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 9 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 10 + MetaCal16BitSizeOffset)));
			IRCamera->CalValue5 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 11 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 12 + MetaCal16BitSizeOffset)));

		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2:

			// Aflæs IR Kameras interne kalibrerings parameter
			IRCamera->CalValue0 = 0.0;
			IRCamera->CalValue1 = 0.0;
			IRCamera->CalValue2 = 0.0;
			IRCamera->CalValue3 = 0.0;
			IRCamera->CalValue4 = 0.0;
			IRCamera->CalValue5 = 0.0;

		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Aflæs IR Kameras interne kalibrerings parameter
			IRCamera->CalValue0 = *(ThermalData + (IRCamera->MetaData2Index + 1));
			IRCamera->CalValue1 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 3 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 4 + MetaCal16BitSizeOffset)));
			IRCamera->CalValue2 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 5 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 6 + MetaCal16BitSizeOffset)));
			IRCamera->CalValue3 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 7 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 8 + MetaCal16BitSizeOffset)));
			IRCamera->CalValue4 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 9 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 10 + MetaCal16BitSizeOffset)));
			IRCamera->CalValue5 = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 11 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 12 + MetaCal16BitSizeOffset)));

		break;

		// Supporterede Kamera pool 4
		case _SupportedThermalCameras_Pool_4:

			// Aflæs IR Kameras interne kalibrerings parameter
			IRCamera->CalValue0 = 0.0;
			IRCamera->CalValue1 = 0.0;
			IRCamera->CalValue2 = 0.0;
			IRCamera->CalValue3 = 0.0;
			IRCamera->CalValue4 = 0.0;
			IRCamera->CalValue5 = 0.0;

		break;

	}

}

// --------------------------------------- Kamera Konfigurations Data Håndterings Routiner --------------------------------------- //

void RMH_IRThermalCamera_ReadCameraConfigParameters(unsigned short* ThermalData, ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool) {

	// Routinen læser kameraets interne konfigurations parametere

	// Lokale variabler
	unsigned int MetaCal16BitSizeOffset = 2;

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Læs kameraets interne konfigurations parameter
			//IRCamera->TemperatureCorrectionSetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 127 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 128 + MetaCal16BitSizeOffset)));
			IRCamera->ReflectedTemperatureSetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 129 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 130 + MetaCal16BitSizeOffset)));
			IRCamera->AmbientTemperatureSetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 131 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 132 + MetaCal16BitSizeOffset)));
			IRCamera->HumiditySetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 133 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 134 + MetaCal16BitSizeOffset)));
			IRCamera->EmissivitySetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 135 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 136 + MetaCal16BitSizeOffset)));
			IRCamera->DistanceSetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 137 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 138 + MetaCal16BitSizeOffset)));

		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2:

			// Læs kameraets interne konfigurations parameter - fra tilhørende GUI UpDowns
			IRCamera->TemperatureCorrectionSetting = _IRThermalCameraDefault_TemperatureCorrectionValue;
			IRCamera->AmbientTemperatureSetting = _IRThermalCameraDefault_AmbientTemperatureValue;
			IRCamera->ReflectedTemperatureSetting = _IRThermalCameraDefault_ReflectedTemperatureValue;
			IRCamera->HumiditySetting = _IRThermalCameraDefault_SurroundingHumidityValue;
			IRCamera->EmissivitySetting = _IRThermalCameraDefault_ObjectEmissivityValue;
			IRCamera->DistanceSetting = _IRThermalCameraDefault_ObjectDistanceValue;

		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Læs kameraets interne konfigurations parameter
			//IRCamera->TemperatureCorrectionSetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 127 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 128 + MetaCal16BitSizeOffset)));
			IRCamera->ReflectedTemperatureSetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 129 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 130 + MetaCal16BitSizeOffset)));
			IRCamera->AmbientTemperatureSetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 131 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 132 + MetaCal16BitSizeOffset)));
			IRCamera->HumiditySetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 133 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 134 + MetaCal16BitSizeOffset)));
			IRCamera->EmissivitySetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 135 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 136 + MetaCal16BitSizeOffset)));
			IRCamera->DistanceSetting = RMH_Conversion_uint16x2ToSinglePrecisionFloat(*(ThermalData + (IRCamera->MetaData2Index + 137 + MetaCal16BitSizeOffset)), *(ThermalData + (IRCamera->MetaData2Index + 138 + MetaCal16BitSizeOffset))) + 1.0;

		break;

		// Supporterede Kamera pool 4
		case _SupportedThermalCameras_Pool_4:

			// Læs kameraets interne konfigurations parameter - fra tilhørende GUI UpDowns
			IRCamera->TemperatureCorrectionSetting = _IRThermalCameraDefault_TemperatureCorrectionValue;
			IRCamera->AmbientTemperatureSetting = _IRThermalCameraDefault_AmbientTemperatureValue;
			IRCamera->ReflectedTemperatureSetting = _IRThermalCameraDefault_ReflectedTemperatureValue;
			IRCamera->HumiditySetting = _IRThermalCameraDefault_SurroundingHumidityValue;
			IRCamera->EmissivitySetting = _IRThermalCameraDefault_ObjectEmissivityValue;
			IRCamera->DistanceSetting = _IRThermalCameraDefault_ObjectDistanceValue;

		break;

	}

}

void RMH_IRThermalCamera_WriteCameraConfigParameter(unsigned int ParameterAddress, float ParameterValue, unsigned short SupportedCameraPool) {

	// Routinen skriver givet kamera konfigurations parameter til Kameraet.

	/*
	 *  Tilhørende Macroer ->  
	 * 
	 *   // Interne IR Kamera Konfigurations Parameter Addresser - For Supporterede Kamera Pool x
	 *   #define _IRCameraPoolx_ConfigParameterAddress_TempCorr      0x0000
	 *   #define _IRCameraPoolx_ConfigParameterAddress_ReflTemp      0x0004
	 *   #define _IRCameraPoolx_ConfigParameterAddress_AmbTemp       0x0008
	 *   #define _IRCameraPoolx_ConfigParameterAddress_Humidity      0x000C
	 *   #define _IRCameraPoolx_ConfigParameterAddress_Emissivity    0x0010
	 *   #define _IRCameraPoolx_ConfigParameterAddress_Distance      0x0014
	 * 
	 */

	// Lokale variabler
	unsigned char* DataPointer = (unsigned char*)&ParameterValue;

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Skriv Float parameter til parameter interne kamera addresse
			IRThermalCamera.setZoom((((ParameterAddress + 0) & 0x7F) << 8) | DataPointer[0]);
			IRThermalCamera.setZoom((((ParameterAddress + 1) & 0x7F) << 8) | DataPointer[1]);
			IRThermalCamera.setZoom((((ParameterAddress + 2) & 0x7F) << 8) | DataPointer[2]);
			IRThermalCamera.setZoom((((ParameterAddress + 3) & 0x7F) << 8) | DataPointer[3]);
			
		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2:


			
		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Skriv Float parameter til parameter interne kamera addresse
			IRThermalCamera.setZoom((((ParameterAddress + 0) & 0x7F) << 8) | DataPointer[0]);
			IRThermalCamera.setZoom((((ParameterAddress + 1) & 0x7F) << 8) | DataPointer[1]);
			IRThermalCamera.setZoom((((ParameterAddress + 2) & 0x7F) << 8) | DataPointer[2]);
			IRThermalCamera.setZoom((((ParameterAddress + 3) & 0x7F) << 8) | DataPointer[3]);

		break;

		// Supporterede Kamera pool 4
		case _SupportedThermalCameras_Pool_4:



		break;

	}

}

void RMH_IRThermalCamera_SaveConfigParametersToCamera(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool) {

	// Routinen skriver de indstillede kamera konfigurations parameter fra objekt "IRcamera"
	// Til kameraets interne hukommelse.

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1 og 3
		case _SupportedThermalCameras_Pool_1: case _SupportedThermalCameras_Pool_3:

			// Skriv Konfigurations Parameter til kameraets interne hukommelse
			//RMH_IRThermalCamera_WrtreCameraConfigParameter(_IRCamera_ConfigParameterAddress_TempCorrREG, IRCamera->TemperatureCorrectionSetting);
			RMH_IRThermalCamera_WriteCameraConfigParameter(_IRCameraPool1_ConfigParameterAddress_ReflTempREG, IRCamera->ReflectedTemperatureSetting, SupportedCameraPool);
			RMH_IRThermalCamera_WriteCameraConfigParameter(_IRCameraPool1_ConfigParameterAddress_AmbTempREG, IRCamera->AmbientTemperatureSetting, SupportedCameraPool);
			RMH_IRThermalCamera_WriteCameraConfigParameter(_IRCameraPool1_ConfigParameterAddress_HumidityREG, IRCamera->HumiditySetting, SupportedCameraPool);
			RMH_IRThermalCamera_WriteCameraConfigParameter(_IRCameraPool1_ConfigParameterAddress_EmissivityREG, IRCamera->EmissivitySetting, SupportedCameraPool);
			RMH_IRThermalCamera_WriteCameraConfigParameter(_IRCameraPool1_ConfigParameterAddress_DistanceREG, IRCamera->DistanceSetting, SupportedCameraPool);
		
		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2:



		break;

		// Supporterede Kamera pool 4
		case _SupportedThermalCameras_Pool_4:



		break;

	}

}

// --------------------------------------------- Thermodynamiske Udregnings Routiner --------------------------------------------- //

double RMH_IRThermalCamera_CalAtmosphericWaterVaporContribution(double Humidity, double AmbientTemp) {

	// Routinen udregner det reflekterede bidrag fra Atmosfærisk vanddamp
	// Routinen retunerer Omega som double

	// Lokale variabler og objekter
	double Omega = 0.0;

	// Koefficienter for mængden af vand damp i atmosfæren
	double h1 = 1.5587;
	double h2 = 0.069390;
	double h3 = -0.000278160;
	double h4 = 0.68455e-6;

	// Udregn det reflekterede bidrag fra atmosfærisk vand damp
	Omega = Humidity * exp(pow(AmbientTemp, 3) * h4 + pow(AmbientTemp, 2) * h3 + AmbientTemp * h2 + h1);

	// Retuner udregne omega
	return Omega;

}

double RMH_IRThermalCamera_CalAtmosphericWaterVaporAttenuation(double Omega, unsigned short DistanceMeters) {

	// Routinen udregner attenueringen forsaget af atmosfærisk vand damp
	// Routinen retunerer atmosfæriske wavelength transmission "Tau" som double

	// Lokale variabler
	double Tau = 0.0;

	// Atmosfærisk dæmpnings konstant
	double Katm = 1.9;

	// Atmosfærisk vand damp attenuerings konstanter
	double a1 = 0.0066;
	double a2 = 0.0126;

	// Vand damp attenuerings konstanter (ved jordens overflade)
	double b1 = -0.0023;
	double b2 = -0.0067;

	// Udregn bidraget fra den atmosfæriske wavelength transmission
	Tau = Katm * exp(-sqrt((double)DistanceMeters) * (a1 + b1 * sqrt(Omega))) + (1 - Katm) * exp(-sqrt((double)DistanceMeters) * (a2 + b2 * sqrt(Omega)));

	// Retuner udregnede Tau
	return Tau;

}

// --------------------------------------------- Thermografiske Udregnings Routiner ---------------------------------------------- //

// ÆNDRET 18-11-2025 !!!!!!!
void RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short SupportedCameraPool) {

	// Routinen udregner og generer en temperatur LookUp tabel
	// Som benyttes til at konverterer pixel data til aktuel temperatur

	// Lokale variabler
	double n = 0.0;
	double Tau = 0.0;
	double wtot, ttot;
	double Omega = 0.0;
	double ObjectTemp = 0;
	double NumeratorPart = 0.0;
	double Sigma = 0.0000000567;
	double DenominatorPart = 0.0;
	double LookUpTableOffset = 0.0;
	double CalValue0Correction = 0.0;
	double SqrtComplexNegative = 0.0;
	double EmissivityTauSigma = 0.0;
	double EmissivitySigma = 0.0;
	double TSensorContribution = 0.0;
	double TReflectContribution = 0.0;
	double TAmbientContribution = 0.0;
	double TSensCoreContribution = 0.0;
	double CalValue_A, CalValue_B, CalValue_C, CalValue_D;
	
	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1 og 3
		case _SupportedThermalCameras_Pool_1: case _SupportedThermalCameras_Pool_3:

			// ------------------------------------------------- Termografisk Loop-Up Tabels Udregninger Pool 1 ------------------------------------------------- // 

			// Udregn det reflekterede bedrag fra atmosfærisk vand damp
			Omega = RMH_IRThermalCamera_CalAtmosphericWaterVaporContribution(IRCamera->HumiditySetting, IRCamera->AmbientTemperatureSetting);
			// Funktionen udregner dæmpning faktoren fra atmosfærisk vand damp
			Tau = RMH_IRThermalCamera_CalAtmosphericWaterVaporAttenuation(Omega, IRCamera->DistanceSetting);

			// Split objekt temperatur ligningens tæller og nævner
			NumeratorPart = (1.0 - IRCamera->EmissivitySetting) * Tau * pow((IRCamera->ReflectedTemperatureSetting + 273.15), 4) + (1.0 - Tau) * pow((IRCamera->AmbientTemperatureSetting + 273.15), 4);
			DenominatorPart = IRCamera->EmissivitySetting * Tau;

			// Udregn konpenserede Kamera kalibrerings værdier
			CalValue_A = IRCamera->CalValue2 / (IRCamera->CalValue1 + IRCamera->CalValue1);
			CalValue_B = IRCamera->CalValue2 * IRCamera->CalValue2 / (IRCamera->CalValue1 * IRCamera->CalValue1 * 4.0);
			CalValue_C = IRCamera->CalValue1 * pow(IRCamera->temp_shutter, 2) + IRCamera->temp_shutter * IRCamera->CalValue2;
			CalValue_D = IRCamera->CalValue3 * pow(IRCamera->temp_fpa, 2) + IRCamera->CalValue4 * IRCamera->temp_fpa + IRCamera->CalValue5;

			// Hvis IR Kameraets Temperatur Range er low range
			if (IRCamera->CurrentIRTempRangeFlag == 1) {

				// Udregn korrection til Kalibrerings værdi
				CalValue0Correction = IRCamera->CalValue0Offset - IRCamera->temp_fpa * IRCamera->CalValue0Fpamul;

				// Hvis korrectionen er lavere end '0'
				if (CalValue0Correction < 0.0) {
					// Nulstil korrections værdien
					CalValue0Correction = 0.0;
				}

			}
			else {

				// Nulstil korrections værdien
				CalValue0Correction = 0.0;

			}

			// Udregn LookUp Tabellens Offset værdi
			LookUpTableOffset = IRCamera->CalValue0 - CalValue0Correction;

			// Generer Look-Up Tabel med længden af IR sensorens Bit bredde - 14Bit 
			for (unsigned int i = 0; i < 16384; i++) {

				// Udreng Kvardratrods parameter  
				SqrtComplexNegative = (((double)i - LookUpTableOffset) * CalValue_D + CalValue_C) / IRCamera->CalValue1 + CalValue_B;
					
				// Kontroller om værdien er negativ
				if (SqrtComplexNegative < 0) {
					// Konverter Kvardratrods værdi til positiv
					n = sqrt(-SqrtComplexNegative);
				}
				else {
					// Udregn Kvardratrod af positiv værdi
					n = sqrt(SqrtComplexNegative);
				}
				
				// Formuler 2. ordens polynomie til objekt temperatur udregning
				wtot = pow((n - CalValue_A + 273.15), 4);
				ttot = pow(((wtot - NumeratorPart) / DenominatorPart), 0.25) - 273.15;

				// Udregn Objekt temperaturen
				ObjectTemp = ttot + (IRCamera->DistanceSetting * 0.85 - 1.125) * (ttot - IRCamera->AmbientTemperatureSetting) / 100.0 + IRCamera->TemperatureCorrectionSetting;

				// Skriv Data til Temperatur Look-Up Tabel
				IRCamera->TemperatureLookUpTabel[i] = ObjectTemp;

			}

			// -------------------------------------------------------------------------------------------------------------------------------------------------- // 

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "New Temperature Look-Up Tabel Has Been Generated.", _StatusMessageType_Normal);
			
		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2: case _SupportedThermalCameras_Pool_4:

			// Udregn det reflekterede bedrag fra atmosfærisk vand damp
			Omega = RMH_IRThermalCamera_CalAtmosphericWaterVaporContribution(IRCamera->HumiditySetting, IRCamera->AmbientTemperatureSetting);
			// Funktionen udregner dæmpning faktoren fra atmosfærisk vand damp
			Tau = RMH_IRThermalCamera_CalAtmosphericWaterVaporAttenuation(Omega, IRCamera->DistanceSetting);

			// Udregn miljø bidraget til temperatur udregningerne - kompenser for eksterne temperaturer
			TReflectContribution = (1.0 - IRCamera->EmissivitySetting) * Tau * Sigma * IRCamera->ReflectedTemperatureSetting;
			TAmbientContribution = (1.0 - Tau) * Sigma * IRCamera->AmbientTemperatureSetting;
			TSensCoreContribution = (1.0 - IRCamera->temp_shutter / IRCamera->temp_core) * Sigma * IRCamera->temp_shutter;
			EmissivityTauSigma = 1.0 / (IRCamera->EmissivitySetting * Tau * Sigma);
			EmissivitySigma = Sigma * IRCamera->EmissivitySetting;

			// Udregn miljø bidragets skallerings faktor og offset 
			IRCamera->ObjectEnvirTempCorrectionOffset = -(TReflectContribution * EmissivityTauSigma) - (TAmbientContribution * EmissivityTauSigma) - (TSensCoreContribution * EmissivityTauSigma);
			IRCamera->ObjectEnvirTempCorrectionFactor = EmissivityTauSigma * EmissivitySigma;

		break;

	}

}

double RMH_IRThermalCamera_ReadPixelTemperature(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short PixelValue, unsigned short SupportedCameraPool) {

	// Routinen retunerer Pixel temperaturen fra genereret temperatur Look-op tabel eller fra Pool spesifik udregning

	// Lokale variabler
	double PixelTemperature = 0.0;

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1 og 3
		case _SupportedThermalCameras_Pool_1: case _SupportedThermalCameras_Pool_3:

			// Læs Pixel Temperatur fra Look-up Tabel
			PixelTemperature = IRCamera->TemperatureLookUpTabel[PixelValue & 0x3FFF];

		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2: case _SupportedThermalCameras_Pool_4:

			// Udregn Pixel temperaturen fra rå pixel data
			PixelTemperature = ((double)PixelValue * 0.015625) - 273.15;
			// Kompenser for miljø bidraget til temperatur udregningerne
			PixelTemperature = PixelTemperature * IRCamera->ObjectEnvirTempCorrectionFactor + IRCamera->ObjectEnvirTempCorrectionOffset;
			// Kompender for temperatur korrektion 
			PixelTemperature = PixelTemperature + IRCamera->TemperatureCorrectionSetting;
			
		break;

	}

	// Retuner Pixel temperaturen
	return PixelTemperature;

}

double RMH_IRThermalCamera_ReadFramePixelTemperature(ThermalCameraDevice::IRCameraDeviceFormat* IRCamera, unsigned short* ThermalData, unsigned short PixelWidth, unsigned short PixelHeight, unsigned short SupportedCameraPool) {

	// Routinen læser og retunerer en pixels data værdi fra det termiske frame data array
	// Input Pixel positionerne er på matrice form som positionen i matricen: Width x Height

	// Lokale variabler
	double PixelTemperature = 0.0;
	unsigned int PixelData = 0;
	unsigned int ArrayIndex = 0;

	// Konverter matrice index til array index
	ArrayIndex = (PixelHeight * IRCamera->FrameWidth) + PixelWidth;

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1 og 3
		case _SupportedThermalCameras_Pool_1: case _SupportedThermalCameras_Pool_3:

			// Forhindre Array index Overflow
			if (ArrayIndex > (IRCamera->FrameWidth * IRCamera->FrameHeight) - 1) { ArrayIndex = 0; }

			// Læs pixel data fra termisk frame data
			PixelData = *(ThermalData + ArrayIndex);

			// Læs pixel temperaturen
			PixelTemperature = IRCamera->TemperatureLookUpTabel[PixelData & 0x3FFF];

		break;

		// Supporterede Kamera pool 2
		case _SupportedThermalCameras_Pool_2: case _SupportedThermalCameras_Pool_4:

			// Forhindre Array index Overflow
			if (ArrayIndex > (IRCamera->FrameWidth * (IRCamera->FrameHeight - IRCamera->FrameMetadataSize)) - 1) { ArrayIndex = 0; }

			// Læs pixel data fra termisk frame data
			PixelData = *(ThermalData + ArrayIndex);

			// Udregn Pixel temperaturen fra rå pixel data
			PixelTemperature = ((double)PixelData * 0.015625) - 273.15;
			// Kompenser for miljø bidraget til temperatur udregningerne
			PixelTemperature = PixelTemperature * IRCamera->ObjectEnvirTempCorrectionFactor + IRCamera->ObjectEnvirTempCorrectionOffset;
			// Kompender for temperatur korrektion 
			PixelTemperature = PixelTemperature + IRCamera->TemperatureCorrectionSetting;

		break;

	}

	// Retuner Pixel Temperatur 
	return PixelTemperature;

}

// ------------------------------- Recording/Snapshot Analysis Mode Kamera Pool Spesifikke Routine ------------------------------- //

void RMH_IRThermalCamera_WriteDataToVideoRecordingFilesSequence(unsigned short SupportedCameraPool) {

	// Routinen håndterer skrivningen af valgte Kamera Pool data til video filer, hvis video optagning er startede og klar

	// Er video optagning startede, er Video filerne klar til skrivning
	if (VideoRecordingStartedFlag == true && VideoFilesReadyFlag == true) {

		// Skal RAW ikke-processerede kamera Data gemmes 
		if (SaveRAWDataRecordingFlag == true) {

			// Hvilken supporterede kamera pool er valgt
			switch (SupportedCameraPool) {

				// Supporterede Kamera pool 1, 2 og 4
				case _SupportedThermalCameras_Pool_1: case _SupportedThermalCameras_Pool_2: case _SupportedThermalCameras_Pool_4:

					// Skriv RAW Kamera data frames til Video fil
					RMH_VideoFileRecording_WriteDataToFile(_VideoFileWriteObject_RecordingAnalysisModeFile, IRCamera.FrameWidth, IRCamera.FrameHeight, IRCameraFrameData);

				break;

				// Supporterede Kamera pool 3
				case _SupportedThermalCameras_Pool_3:

					// Konverter Termografisk data array til et YUY2 array - Med NUC korrigerede data
					RMH_IRThermalCamera_Convert14BitThermalDataArrayToYUY2(&FrameThermalDataRaw[0], &FrameThermalData3Band[0], IRCamera.FrameWidth, IRCamera.FrameHeight);

					// Skriv NUC korrigerede RAW Kamera data frames til Video fil
					RMH_VideoFileRecording_WriteDataToFile(_VideoFileWriteObject_RecordingAnalysisModeFile, IRCamera.FrameWidth, IRCamera.FrameHeight, FrameThermalData3Band);
				
				break;

			}

		}

		// Hvis Live View Ultra Opløsnings Mode er aktiverede
		if (UltraResolutionEnableFlag == true) {

			// Skriv Processerede Kamera data frames til Video fil
			RMH_VideoFileRecording_WriteDataToFile16Bit(_VideoFileWriteObject_LiveViewStreamFile, IRCamera.FrameWidth * UltraResolutionScaleFactor, (IRCamera.FrameHeight - IRCamera.FrameMetadataSize) * UltraResolutionScaleFactor, PrecessedUltraResolutionImage);

		}
		else {

			// Skriv Processerede Kamera data frames til Video fil
			RMH_VideoFileRecording_WriteDataToFile16Bit(_VideoFileWriteObject_LiveViewStreamFile, IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize, ProcessedThermalImage);

		}

	}

}

bool RMH_IRThermalCamera_ConvertCapturedRawImageDataToSnapshotPNG(unsigned short SupportedCameraPool) {

	// Routinen håndterer konverteringen af valgte Kamera Pool RAW data til Snapshot PNG Data.
	// Routinen retunerer Snapshot file statusen

	// Lokale variabler
	bool SnapshotStatus = false;

	// Hvilken supporterede kamera pool er valgt
	switch (SupportedCameraPool) {

		// Supporterede Kamera pool 1, 2 og 4
		case _SupportedThermalCameras_Pool_1: case _SupportedThermalCameras_Pool_2: case _SupportedThermalCameras_Pool_4:

			// Generer og skriv ekstra RAW Meta data til frame data array 
			RMH_AnalysisMode_AddIDAndMetaDataToFrameArray(IRCamera.FrameWidth, IRCamera.FrameHeight, &IRCameraFrameData[0],
				IRCamera.ThermalCameraSupportPool, IRCamera.FrameMetadataSize, IRCamera.FrameWidthPixelOffset, IRCamera.FrameHeightPixelOffset,
				IRCamera.TemperatureCorrectionSetting, IRCamera.AmbientTemperatureSetting, IRCamera.ReflectedTemperatureSetting, IRCamera.HumiditySetting, IRCamera.EmissivitySetting, IRCamera.DistanceSetting);

			// Gem et Rå sensor data snapshot fra forbundet termiske kamera
			SnapshotStatus = RMH_Winforms_SaveRawImageDataAsSnapShotPNG(GlobalVariables::SnapShotDefaultPath, IRCamera.FrameWidth, IRCamera.FrameHeight, &IRCameraFrameData[0]);

		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Generer og skriv ekstra RAW Meta data til frame data array - For Pool 3 Kameraer med NUC Korrektion
			RMH_AnalysisMode_AddIDAndMetaDataToFrameArray(IRCamera.FrameWidth, IRCamera.FrameHeight, &FrameThermalData3Band[0],
				IRCamera.ThermalCameraSupportPool, IRCamera.FrameMetadataSize, IRCamera.FrameWidthPixelOffset, IRCamera.FrameHeightPixelOffset,
				IRCamera.TemperatureCorrectionSetting, IRCamera.AmbientTemperatureSetting, IRCamera.ReflectedTemperatureSetting, IRCamera.HumiditySetting, IRCamera.EmissivitySetting, IRCamera.DistanceSetting);

			// Konverter Termografisk data array til et YUY2 array - Med NUC korrigerede data
			RMH_IRThermalCamera_Convert14BitThermalDataArrayToYUY2(&FrameThermalDataRaw[0], &FrameThermalData3Band[0], IRCamera.FrameWidth, IRCamera.FrameHeight);

			// Gem et Rå sensor data snapshot fra forbundet termiske kamera - Med NUC korrigerede data
			SnapshotStatus = RMH_Winforms_SaveRawImageDataAsSnapShotPNG(GlobalVariables::SnapShotDefaultPath, IRCamera.FrameWidth, IRCamera.FrameHeight, &FrameThermalData3Band[0]);

		break;

	}

	// Retuner Snapshot Status
	return SnapshotStatus;

}

// --------------------------------- Termisk Kamera Pool Specifikke Håndterings/Kontrol Routiner --------------------------------- //

void RMH_IRThermalCamera_AutoShutterCalTimerCallbackHandler() {

	// Routinen håndterer events ved eksikveringen af auto kalibrerings timerens callback  

	// Hvis Automatisk Shutter kalibrering er aktiverede
	if (AutoShutterCalEnableFlag == true) {

		// Kalibrer Termisk kamera
		RMH_IRThermalCamera_CalibrateThermalCamera();

	}

}

void RMH_IRThermalCamera_TempDriftBasedCalTimerCallbackHandler() {

	// Routinen håndterer events ved eksikveringen af Temperatur Drift Baseret kalibrerings timerens callback  

	// Kontroller om det termiske kameras nuværende drift er over/lig med set-punkts værdien
	if (RMH_Math_absDouble(SensorTemperatureCalDrift * TemperatureUnitScaleFactor) >= TempDriftCalibrationSetValue) {

		// Kalibrer Termisk kamera
		RMH_IRThermalCamera_CalibrateThermalCamera();

	}

}

void RMH_IRThermalCamera_CalibrateThermalCamera() {

	// Routinen kalibrerer det forbundet termiske kamera
	// Og håndterer events ved kamera kalibrering

	// Hvilken termisk kamera pool er forbundet
	switch (IRCamera.ThermalCameraSupportPool) {

		// Supporterede Kamera pool 1
		case _SupportedThermalCameras_Pool_1:

			// Opdater Kalibrerings Knap Border Farve
			GlobalVariables::GlobalCalibrateCameraButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			GlobalVariables::GlobalCalibrateCameraButton->Refresh();

			// Kalibrer Termisk kamera
			RMH_IRThermalCamera_CalibrateIRCamera(IRCamera.ThermalCameraSupportPool);

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Is Calibrating...", _StatusMessageType_Normal);

			// Vent på At Kalibrering er færdig
			System::Threading::Thread::Sleep(_ThermalCameraShutter_CloseTimeMs);

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Calibrating Finished.", _StatusMessageType_Success);

			// Opdater Kalibrerings Knap Border Farve
			GlobalVariables::GlobalCalibrateCameraButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

			// Læs En enkelt frame data fra det termisk kamera
			RMH_IRThermalCamera_ReadFrameRaw(&IRCameraFrameData[0], &VideoFrameSize);
			// Formater Rå YUY2 Data til 16Bit termisk data array
			RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(&IRCamera, &IRCameraFrameData[0], &FrameThermalDataRaw[0]);
			// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
			RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);
			// Læs IR kameraets Interne kalibrerings Parameter
			RMH_IRThermalCamera_ReadCalibrationParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

			// Generer/Opdater Temperatur Loop-Up Tabel
			RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);
			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Generated New Temperature Look-Up Tabel.", _StatusMessageType_Normal);

		break;

		// Supporterede Kamera pool 2 og 4
		case _SupportedThermalCameras_Pool_2: case _SupportedThermalCameras_Pool_4:

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "This Function Is Not Supported For The Camera In This Version Of IRCAM Thermal Viewer", _StatusMessageType_Warning);

		break;

		// Supporterede Kamera pool 3
		case _SupportedThermalCameras_Pool_3:

			// Opdater Kalibrerings Knap Border Farve
			GlobalVariables::GlobalCalibrateCameraButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;
			GlobalVariables::GlobalCalibrateCameraButton->Refresh();

			// Kalibrer Termisk kamera
			RMH_IRThermalCamera_CalibrateIRCamera(IRCamera.ThermalCameraSupportPool);

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Shutter Is Closed...", _StatusMessageType_Normal);

			// Vent på At Kalibrerings shutteren er lukket
			System::Threading::Thread::Sleep(_ThermalCameraShutter_CloseTimeMs);

			// Læs En enkelt frame med kamera shutteren lukkede - CMOS Baseline måling
			RMH_IRThermalCamera_ReadFrameRaw(&IRCameraFrameData[0], &VideoFrameSize);

			// --------------------------------------- Non-Uniformity Korrektion --------------------------------------- //

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Performing Non-Uniformity Correction & Calibration...", _StatusMessageType_Normal);

			// Konverter CMOS Baseline måling til 16Bit data array
			RMH_ImageNonUniformityCorrection_ConvertBaselineImageTo16Bit(&IRCameraFrameData[0], &ClosedShutterCMOSBaselineData[0], IRCamera.FrameWidth, IRCamera.FrameHeight);

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Calculating Non-Uniformity Mapping...", _StatusMessageType_Normal);

			// Udregn Middel værdien af CMOS Baseline målingen, samt Baseline dataens Non-Uniformity Mapping
			ImageCMOSBaselineMeanValue = RMH_ImageNonUniformityCorrection_CalNonUniformityMap(&ClosedShutterCMOSBaselineData[0], IRCamera.FrameWidth, IRCamera.FrameHeight, IRCamera.FrameMetadataSize, &ImageCMOSNonUniformityMapData[0]);

			// --------------------------------------------------------------------------------------------------------- //

			// Vent på At Kalibrerings shutteren er Åben Igen
			System::Threading::Thread::Sleep(_ThermalCameraShutter_OpenTimeMs);

			// Læs En enkelt frame data fra det termisk kamera
			RMH_IRThermalCamera_ReadFrameRaw(&IRCameraFrameData[0], &VideoFrameSize);
			// Formater Rå YUY2 Data til 16Bit termisk data array
			RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(&IRCamera, &IRCameraFrameData[0], &FrameThermalDataRaw[0]);
			// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
			RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);
			// Læs IR kameraets Interne kalibrerings Parameter
			RMH_IRThermalCamera_ReadCalibrationParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

			// Generer/Opdater Temperatur Loop-Up Tabel
			RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Non-Uniformity Correction & Calibrating Finished.", _StatusMessageType_Normal);

			// Opdater Kalibrerings Knap Border Farve
			GlobalVariables::GlobalCalibrateCameraButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

		break;

	}

	// Lager sidste kalibrerings Sensor Detektor temperatur
	CurrentCalDetectorTemperature = IRCamera.temp_fpa;

}

void RMH_IRThermalCamera_ChangeThermalCameraTemperatureRange() {

	// Routinen skifter det termiske kameras temperatur range

	// Lokale variabler
	bool SupportsHighTemperatureRangeFlag = false;

	// Kontroller om tilsluttede kamera supporterer en højere temperatur range
	switch (IRCamera.SellectedCameraIndex) {

		// Opdater kameraets pool variabel
		case _SupportedThermalCamera_InfiRayT2L:        SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT2L_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT2LV2:      SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT2LV2_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT2Search:   SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT2Search_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT2SearchV2: SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT2SearchV2_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT2Sp:       SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT2Sp_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT2SpV2:     SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT2SpV2_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT2Pro:      SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT2Pro_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT2ProV2:    SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT2ProV2_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT3Search:   SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT3Search_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT3S:	    SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT3S_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayT3Pro:      SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayT3Pro_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayP2:         SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayP2_SupportsHighRange; break;
		case _SupportedThermalCamera_ThermalMasterP2:   SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_ThermalMasterP2_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayP2Pro:      SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayP2Pro_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayDVDL13:     SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayDVDL13_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayS0Series:   SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayS0Series_SupportsHighRange; break;
		case _SupportedThermalCamera_InfiRayTiny1C:     SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_InfiRayTiny1C_SupportsHighRange; break;
		case _SupportedThermalCamera_HTIHT301:          SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_HTIHT301_SupportsHighRange; break;
		case _SupportedThermalCamera_UNITUTi260M:       SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_UNITUTi260M_SupportsHighRange; break;
		case _SupportedThermalCamera_TOPDONTC001:       SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_TOPDONTC001_SupportsHighRange; break;
		case _SupportedThermalCamera_TOPDONTC002:       SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_TOPDONTC002_SupportsHighRange; break;
		case _SupportedThermalCamera_Victor328B:        SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_Victor328B_SupportsHighRange; break;
		case _SupportedThermalCamera_LODESTARL2:        SupportsHighTemperatureRangeFlag = _SupportedThermalCamera_LODESTARL2_SupportsHighRange; break;

	}

	// Hvis det forbundet termiske kamera supporterer en højere temperatur range
	if (SupportsHighTemperatureRangeFlag == true) {

		// Hvilken termisk kamera pool er forbundet
		switch (IRCamera.ThermalCameraSupportPool) {

			// Supporterede Kamera pool 1
			case _SupportedThermalCameras_Pool_1:

				// Toggle Temperatur range flag
				ThermalCameraHighRangeFlag = !ThermalCameraHighRangeFlag;

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Changing Thermal Camera Temperature Range... Please Wait...", _StatusMessageType_Normal);

				// Håndter temperatur range flag stadie
				if (ThermalCameraHighRangeFlag == true) {

					// Konfigurer det Termisk kamera til dens højeste Temperatur Range
					RMH_IRThermalCamera_SetIRCameraTemperatureRange(_ThermalCamera_TemperatureRange_HighRange, IRCamera.ThermalCameraSupportPool);

					// Opdater Temperatur Range Knap border farve
					GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::Yellow;

					// Opdater temperatur range knap grafik
					GlobalVariables::GlobalTempRangeButton->Update();
					// Vent på korrekt skift af temperatur range
					System::Threading::Thread::Sleep(_ThermalCameraPool1_RangeSwitchReadyTimeMs);

					// Opdater IR Kamera Device Temperatur Range variabel
					IRCamera.CurrentIRTempRangeFlag = 2;

					// Opdater Temperatur Range Knap border farve
					GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

				}
				else {

					// Konfigurer det Termisk kamera til dens laveste Temperatur Range
					RMH_IRThermalCamera_SetIRCameraTemperatureRange(_ThermalCamera_TemperatureRange_LowRange, IRCamera.ThermalCameraSupportPool);

					// Opdater Temperatur Range Knap border farve
					GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::Yellow;

					// Opdater temperatur range knap grafik
					GlobalVariables::GlobalTempRangeButton->Update();
					// Vent på korrekt skift af temperatur range
					System::Threading::Thread::Sleep(_ThermalCameraPool1_RangeSwitchReadyTimeMs);

					// Opdater IR Kamera Device Temperatur Range variabel
					IRCamera.CurrentIRTempRangeFlag = 1;

					// Opdater Temperatur Range Knap border farve
					GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

				}

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Temperature Range Was Changed", _StatusMessageType_Normal);

				// Fortag en Termisk kamera kalibrering
				RMH_IRThermalCamera_CalibrateThermalCamera();

			break;

			// Supporterede Kamera pool 2 og 4
			case _SupportedThermalCameras_Pool_2: case _SupportedThermalCameras_Pool_4:

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "This Function Is Not Supported For The Camera In This Version Of IRCAM Thermal Viewer", _StatusMessageType_Warning);

			break;

			// Supporterede Kamera pool 3
			case _SupportedThermalCameras_Pool_3:

				// Toggle Temperatur range flag
				ThermalCameraHighRangeFlag = !ThermalCameraHighRangeFlag;

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Changing Thermal Camera Temperature Range... Please Wait...", _StatusMessageType_Normal);

				// Håndter temperatur range flag stadie
				if (ThermalCameraHighRangeFlag == true) {

					// Konfigurer det Termisk kamera til dens højeste Temperatur Range
					RMH_IRThermalCamera_SetIRCameraTemperatureRange(_ThermalCamera_TemperatureRange_HighRange, IRCamera.ThermalCameraSupportPool);

					// Opdater Temperatur Range Knap border farve
					GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::Yellow;

					// Opdater temperatur range knap grafik
					GlobalVariables::GlobalTempRangeButton->Update();
					// Vent på korrekt skift af temperatur range
					System::Threading::Thread::Sleep(_ThermalCameraPool3_RangeSwitchReadyTimeMs);

					// Opdater IR Kamera Device Temperatur Range variabel
					IRCamera.CurrentIRTempRangeFlag = 2;

					// Opdater Temperatur Range Knap border farve
					GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

				}
				else {

					// Konfigurer det Termisk kamera til dens laveste Temperatur Range
					RMH_IRThermalCamera_SetIRCameraTemperatureRange(_ThermalCamera_TemperatureRange_LowRange, IRCamera.ThermalCameraSupportPool);

					// Opdater Temperatur Range Knap border farve
					GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::Yellow;

					// Opdater temperatur range knap grafik
					GlobalVariables::GlobalTempRangeButton->Update();
					// Vent på korrekt skift af temperatur range
					System::Threading::Thread::Sleep(_ThermalCameraPool3_RangeSwitchReadyTimeMs);

					// Opdater IR Kamera Device Temperatur Range variabel
					IRCamera.CurrentIRTempRangeFlag = 1;

					// Opdater Temperatur Range Knap border farve
					GlobalVariables::GlobalTempRangeButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

				}

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Temperature Range Was Changed", _StatusMessageType_Normal);

				// Fortag en Termisk kamera kalibrering
				RMH_IRThermalCamera_CalibrateThermalCamera();

			break;

		}

	}
	else { // Hvis det forbundet termiske kamera IKKE supporterer en højere temperatur range

		// Opdater IR Kamera Device Temperatur Range variabel
		IRCamera.CurrentIRTempRangeFlag = 1;

		// Nulstil Temperatur range flag
		ThermalCameraHighRangeFlag = false;

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "The Connected Thermal Camera Does Not Support A Higher Temperature Range.", _StatusMessageType_Warning);

	}

}

void RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool1() {

	// Routinen håndterer events, sekvenser og handlinger som skal fortages efter forbindelsen med et Pool 1 Termisk kamera 

	// Lokale Variabler
	bool ConfigurationValuesOKFlag[6] = { false, false, false, false, false, false };

	// Indstil Det termiske kameraets Frames Pixel Offset værdier
	IRCamera.FrameWidthPixelOffset = _SupporteredeThermalCameraPool1_FrameWidthPixelOffset;
	IRCamera.FrameHeightPixelOffset = _SupporteredeThermalCameraPool1_FrameHeightPixelOffset;

	// Start Kamera video capturing
	RMH_IRThermalCamera_StartCapturing();

	// Nulstil antal læste kamera video frames
	IRCamera.NumbOfCapturedFrames = 0;

	// Læs Kamera frame data indtil at video feed er klar 
	// Loopet afsluttes når kameraet raporterer korrekte interne temperatur data
	while (1) {

		// Vent for at læse hver data frame
		System::Threading::Thread::Sleep(125);

		// Inkrementer antal læste kamera video frames
		IRCamera.NumbOfCapturedFrames = IRCamera.NumbOfCapturedFrames + 1;

		// Læs En enkelt frame data fra det termisk kamera
		RMH_IRThermalCamera_ReadFrameRaw(&IRCameraFrameData[0], &VideoFrameSize);
		// Formater Rå YUY2 Data til 16Bit termisk data array
		RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(&IRCamera, &IRCameraFrameData[0], &FrameThermalDataRaw[0]);
		// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
		RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

		// Hvis interne temperatur data er andet end 0
		if (IRCamera.temp_fpa_Raw != 0 && IRCamera.temp_shutter_Raw != 0) {

			// Kontroller om Core Temperaturen er tilgængelig
			if (IRCamera.temp_core_Raw == 0) {

				// Skriv GUI status meddelse
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Does Not Support Core Temperature Measurements.", _StatusMessageType_Normal);

			}

			// Bryd While Loop
			break;

		}

		// Time håndtering - Hvis de interne temperatur data ikke er blevet læst ordenligt
		if (IRCamera.NumbOfCapturedFrames >= 25) {

			// Skriv GUI status meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Initial Frame Meta Data Read Sequence Failed!", _StatusMessageType_Error);

			// Nulstil antal læste kamera video frames
			IRCamera.NumbOfCapturedFrames = 0;

			// Sæt Kamera connect Error Flag
			CameraConnectErrorFlag = true;

			// Bryd While Loop
			break;

		}

	}

	// Stop Kamera video capturing
	RMH_IRThermalCamera_StopCapturing();

	// Lager sidste kalibrerings Sensor Detektor temperatur
	CurrentCalDetectorTemperature = IRCamera.temp_fpa;

	// Skriv GUI status meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reading The Thermal Camera Internal Calibration...", _StatusMessageType_Normal);
	// Læs IR kameraets Interne kalibrerings Parameter
	RMH_IRThermalCamera_ReadCalibrationParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// Skriv GUI status meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reading The Thermal Camera Temperature Configuration...", _StatusMessageType_Normal);
	// Læs kameraets interne konfigurations parametere
	RMH_IRThermalCamera_ReadCameraConfigParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// ---------------------------------------------- Skriv Kamera Temperatur Konfiguration ---------------------------------------------- //

	// Skriv GUI status meddelse - Konfigurations parametere
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Device Pool: Pool " + RMH_Conversion_IntToStdString(IRCamera.ThermalCameraSupportPool), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Correction: " + RMH_Conversion_FloatToStdString(IRCamera.TemperatureCorrectionSetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature: " + RMH_Conversion_FloatToStdString(IRCamera.ReflectedTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature " + RMH_Conversion_FloatToStdString(IRCamera.AmbientTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Humidity: " + RMH_Conversion_FloatToStdString(IRCamera.HumiditySetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Emissivity: " + RMH_Conversion_FloatToStdString(IRCamera.EmissivitySetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Distance: " + RMH_Conversion_FloatToStdString(IRCamera.DistanceSetting, 5), _StatusMessageType_Normal);

	// ----------------------------------------------------------------------------------------------------------------------------------- //

	// Opdater Gemt Temp Korrektions værdi fra ekstern fil
	IRCamera.TemperatureCorrectionSetting = SavedTempCorrectionSetting;

	// Skriv læste interne kamera konfigurations parametere til Kamera konfigurations panel
	ConfigurationValuesOKFlag[0] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[0], IRCamera.TemperatureCorrectionSetting, 1, 0, _IRThermalCameraDefault_TemperatureCorrectionValue);
	ConfigurationValuesOKFlag[1] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[1], IRCamera.AmbientTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_AmbientTemperatureValue);
	ConfigurationValuesOKFlag[2] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[2], IRCamera.ReflectedTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_ReflectedTemperatureValue);
	ConfigurationValuesOKFlag[3] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[3], IRCamera.HumiditySetting, 1, 0, _IRThermalCameraDefault_SurroundingHumidityValue);
	ConfigurationValuesOKFlag[4] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[4], IRCamera.EmissivitySetting, 1, 0, _IRThermalCameraDefault_ObjectEmissivityValue);
	ConfigurationValuesOKFlag[5] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[5], IRCamera.DistanceSetting, 1, 0, _IRThermalCameraDefault_ObjectDistanceValue);

	// Kontroller om konfigurations værdierne var uden for rækkevidde
	if (ConfigurationValuesOKFlag[0] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Correction Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.TemperatureCorrectionSetting = _IRThermalCameraDefault_TemperatureCorrectionValue;

	}
	if (ConfigurationValuesOKFlag[1] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.AmbientTemperatureSetting = _IRThermalCameraDefault_AmbientTemperatureValue;

	}
	if (ConfigurationValuesOKFlag[2] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.ReflectedTemperatureSetting = _IRThermalCameraDefault_ReflectedTemperatureValue;

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

	// Skriv GUI status meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Generating Temperature Look-Up Tabel...", _StatusMessageType_Normal);

	// Generer Temperatur Loop-Up Tabel
	RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);

}

void RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool2() {

	// Routinen håndterer events, sekvenser og handlinger som skal fortages efter forbindelsen med et Pool 2 Termisk kamera 

	// Lokale Variabler
	bool ConfigurationValuesOKFlag[6] = { false, false, false, false, false, false };

	// Indstil Det termiske kameraets Frames Pixel Offset værdier
	IRCamera.FrameWidthPixelOffset = _SupporteredeThermalCameraPool2_FrameWidthPixelOffset;
	IRCamera.FrameHeightPixelOffset = _SupporteredeThermalCameraPool2_FrameHeightPixelOffset;

	// Skriv GUI status meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reading The Thermal Camera Temperature Configuration...", _StatusMessageType_Normal);
	// Læs kameraets interne konfigurations parametere
	RMH_IRThermalCamera_ReadCameraConfigParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// ---------------------------------------------- Skriv Kamera Temperatur Konfiguration ---------------------------------------------- //

	// Skriv GUI status meddelse - Konfigurations parametere
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Device Pool: Pool " + RMH_Conversion_IntToStdString(IRCamera.ThermalCameraSupportPool), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Correction: " + RMH_Conversion_FloatToStdString(IRCamera.TemperatureCorrectionSetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature: " + RMH_Conversion_FloatToStdString(IRCamera.ReflectedTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature " + RMH_Conversion_FloatToStdString(IRCamera.AmbientTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Humidity: " + RMH_Conversion_FloatToStdString(IRCamera.HumiditySetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Emissivity: " + RMH_Conversion_FloatToStdString(IRCamera.EmissivitySetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Distance: " + RMH_Conversion_FloatToStdString(IRCamera.DistanceSetting, 5), _StatusMessageType_Normal);

	// ----------------------------------------------------------------------------------------------------------------------------------- //

	// Skriv læste interne kamera konfigurations parametere til Kamera konfigurations panel
	ConfigurationValuesOKFlag[0] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[0], IRCamera.TemperatureCorrectionSetting, 1, 0, _IRThermalCameraDefault_TemperatureCorrectionValue);
	ConfigurationValuesOKFlag[1] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[1], IRCamera.AmbientTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_AmbientTemperatureValue);
	ConfigurationValuesOKFlag[2] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[2], IRCamera.ReflectedTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_ReflectedTemperatureValue);
	ConfigurationValuesOKFlag[3] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[3], IRCamera.HumiditySetting, 1, 0, _IRThermalCameraDefault_SurroundingHumidityValue);
	ConfigurationValuesOKFlag[4] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[4], IRCamera.EmissivitySetting, 1, 0, _IRThermalCameraDefault_ObjectEmissivityValue);
	ConfigurationValuesOKFlag[5] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[5], IRCamera.DistanceSetting, 1, 0, _IRThermalCameraDefault_ObjectDistanceValue);

	// Kontroller om konfigurations værdierne var uden for rækkevidde
	if (ConfigurationValuesOKFlag[0] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Correction Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.TemperatureCorrectionSetting = _IRThermalCameraDefault_TemperatureCorrectionValue;

	}
	if (ConfigurationValuesOKFlag[1] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.AmbientTemperatureSetting = _IRThermalCameraDefault_AmbientTemperatureValue;

	}
	if (ConfigurationValuesOKFlag[2] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.ReflectedTemperatureSetting = _IRThermalCameraDefault_ReflectedTemperatureValue;

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

	// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
	RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// Generer Temperatur Loop-Up Tabel
	RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);

}

void RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool3() {

	// Routinen håndterer events, sekvenser og handlinger som skal fortages efter forbindelsen med et Pool 3 Termisk kamera 

	// Lokale Variabler
	bool ConfigurationValuesOKFlag[6] = { false, false, false, false, false, false };
	unsigned int CenterPixelIndex = ((IRCamera.FrameHeight - IRCamera.FrameMetadataSize) * 0.5) * IRCamera.FrameWidth + (IRCamera.FrameWidth * 0.5);

	// Indstil Det termiske kameraets Frames Pixel Offset værdier
	IRCamera.FrameWidthPixelOffset = _SupporteredeThermalCameraPool3_FrameWidthPixelOffset;
	IRCamera.FrameHeightPixelOffset = _SupporteredeThermalCameraPool3_FrameHeightPixelOffset;

	// Start Kamera video capturing
	RMH_IRThermalCamera_StartCapturing();

	// Vent på at det termiske kamera er klar
	System::Threading::Thread::Sleep(_ThermalCameraPool3_ReadyTimeMs);

	// Fortage en Termisk Kamera Kalibrering
	RMH_IRThermalCamera_CalibrateThermalCamera();

	// Stop Kamera video capturing
	RMH_IRThermalCamera_StopCapturing();

	// Nulstil Antal læste video frames variabel
	IRCamera.NumbOfCapturedFrames = 0;

	// Skriv GUI status meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reading The Thermal Camera Internal Calibration...", _StatusMessageType_Normal);
	// Læs IR kameraets Interne kalibrerings Parameter
	RMH_IRThermalCamera_ReadCalibrationParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// Skriv GUI status meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reading The Thermal Camera Temperature Configuration...", _StatusMessageType_Normal);
	// Læs kameraets interne konfigurations parametere
	RMH_IRThermalCamera_ReadCameraConfigParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// ---------------------------------------------- Skriv Kamera Temperatur Konfiguration ---------------------------------------------- //

	// Skriv GUI status meddelse - Konfigurations parametere
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Device Pool: Pool " + RMH_Conversion_IntToStdString(IRCamera.ThermalCameraSupportPool), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Correction: " + RMH_Conversion_FloatToStdString(IRCamera.TemperatureCorrectionSetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature: " + RMH_Conversion_FloatToStdString(IRCamera.ReflectedTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature " + RMH_Conversion_FloatToStdString(IRCamera.AmbientTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Humidity: " + RMH_Conversion_FloatToStdString(IRCamera.HumiditySetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Emissivity: " + RMH_Conversion_FloatToStdString(IRCamera.EmissivitySetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Distance: " + RMH_Conversion_FloatToStdString(IRCamera.DistanceSetting, 5), _StatusMessageType_Normal);

	// ----------------------------------------------------------------------------------------------------------------------------------- //

	// Opdater Gemt Temp Korrektions værdi fra ekstern fil
	IRCamera.TemperatureCorrectionSetting = SavedTempCorrectionSetting;

	// Skriv læste interne kamera konfigurations parametere til Kamera konfigurations panel
	ConfigurationValuesOKFlag[0] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[0], IRCamera.TemperatureCorrectionSetting, 1, 0, _IRThermalCameraDefault_TemperatureCorrectionValue);
	ConfigurationValuesOKFlag[1] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[1], IRCamera.AmbientTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_AmbientTemperatureValue);
	ConfigurationValuesOKFlag[2] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[2], IRCamera.ReflectedTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_ReflectedTemperatureValue);
	ConfigurationValuesOKFlag[3] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[3], IRCamera.HumiditySetting, 1, 0, _IRThermalCameraDefault_SurroundingHumidityValue);
	ConfigurationValuesOKFlag[4] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[4], IRCamera.EmissivitySetting, 1, 0, _IRThermalCameraDefault_ObjectEmissivityValue);
	ConfigurationValuesOKFlag[5] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[5], IRCamera.DistanceSetting, 1, 0, _IRThermalCameraDefault_ObjectDistanceValue);

	// Kontroller om konfigurations værdierne var uden for rækkevidde
	if (ConfigurationValuesOKFlag[0] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Correction Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.TemperatureCorrectionSetting = _IRThermalCameraDefault_TemperatureCorrectionValue;

	}
	if (ConfigurationValuesOKFlag[1] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.AmbientTemperatureSetting = _IRThermalCameraDefault_AmbientTemperatureValue;

	}
	if (ConfigurationValuesOKFlag[2] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.ReflectedTemperatureSetting = _IRThermalCameraDefault_ReflectedTemperatureValue;

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

	// Skriv GUI status meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Generating Temperature Look-Up Tabel...", _StatusMessageType_Normal);

	// Generer Temperatur Loop-Up Tabel
	RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);

}

void RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool4() {

	// Routinen håndterer events, sekvenser og handlinger som skal fortages efter forbindelsen med et Pool 4 Termisk kamera 

	// Lokale Variabler
	bool ConfigurationValuesOKFlag[6] = { false, false, false, false, false, false };

	// Indstil Det termiske kameraets Frames Pixel Offset værdier
	IRCamera.FrameWidthPixelOffset = _SupporteredeThermalCameraPool4_FrameWidthPixelOffset;
	IRCamera.FrameHeightPixelOffset = _SupporteredeThermalCameraPool4_FrameHeightPixelOffset;

	// Skriv GUI status meddelse
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reading The Thermal Camera Temperature Configuration...", _StatusMessageType_Normal);
	// Læs kameraets interne konfigurations parametere
	RMH_IRThermalCamera_ReadCameraConfigParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// ---------------------------------------------- Skriv Kamera Temperatur Konfiguration ---------------------------------------------- //

	// Skriv GUI status meddelse - Konfigurations parametere
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Device Pool: Pool " + RMH_Conversion_IntToStdString(IRCamera.ThermalCameraSupportPool), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Correction: " + RMH_Conversion_FloatToStdString(IRCamera.TemperatureCorrectionSetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature: " + RMH_Conversion_FloatToStdString(IRCamera.ReflectedTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature " + RMH_Conversion_FloatToStdString(IRCamera.AmbientTemperatureSetting * TemperatureUnitScaleFactor + TemperatureUnitOffsetFactor, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Humidity: " + RMH_Conversion_FloatToStdString(IRCamera.HumiditySetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Emissivity: " + RMH_Conversion_FloatToStdString(IRCamera.EmissivitySetting, 5), _StatusMessageType_Normal);
	RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Distance: " + RMH_Conversion_FloatToStdString(IRCamera.DistanceSetting, 5), _StatusMessageType_Normal);

	// ----------------------------------------------------------------------------------------------------------------------------------- //

	// Skriv læste interne kamera konfigurations parametere til Kamera konfigurations panel
	ConfigurationValuesOKFlag[0] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[0], IRCamera.TemperatureCorrectionSetting, 1, 0, _IRThermalCameraDefault_TemperatureCorrectionValue);
	ConfigurationValuesOKFlag[1] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[1], IRCamera.AmbientTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_AmbientTemperatureValue);
	ConfigurationValuesOKFlag[2] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[2], IRCamera.ReflectedTemperatureSetting, TemperatureUnitScaleFactor, TemperatureUnitOffsetFactor, _IRThermalCameraDefault_ReflectedTemperatureValue);
	ConfigurationValuesOKFlag[3] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[3], IRCamera.HumiditySetting, 1, 0, _IRThermalCameraDefault_SurroundingHumidityValue);
	ConfigurationValuesOKFlag[4] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[4], IRCamera.EmissivitySetting, 1, 0, _IRThermalCameraDefault_ObjectEmissivityValue);
	ConfigurationValuesOKFlag[5] = RMH_Winforms_NumericUpDown_ChangeNumber(GlobalVariables::CameraConfigNumericUpDowns[5], IRCamera.DistanceSetting, 1, 0, _IRThermalCameraDefault_ObjectDistanceValue);

	// Kontroller om konfigurations værdierne var uden for rækkevidde
	if (ConfigurationValuesOKFlag[0] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Temperature Correction Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.TemperatureCorrectionSetting = _IRThermalCameraDefault_TemperatureCorrectionValue;

	}
	if (ConfigurationValuesOKFlag[1] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Ambient Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.AmbientTemperatureSetting = _IRThermalCameraDefault_AmbientTemperatureValue;

	}
	if (ConfigurationValuesOKFlag[2] == false) {

		// Skriv GUI status meddelse
		RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Reflected Temperature Setting Was Out Of Range - Using Default Value.", _StatusMessageType_Error);
		// Opdater tilhørende konfigurations værdi til default værdi
		IRCamera.ReflectedTemperatureSetting = _IRThermalCameraDefault_ReflectedTemperatureValue;

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

	// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
	RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

	// Generer Temperatur Loop-Up Tabel
	RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);

}

void RMH_IRThermalCamera_ConnectToThermalCameraOrAnalysisMode() {

	// Routinen håndterer events ved forbindelsen til et valgt termiske kamera pool
	// Eller events hvis "Recording Analysis" Mode er valgt

	// Ryd Status Meddelses Arealet
	GlobalVariables::GlobalGUIInfoTextArea->Clear();

	// Nulstil CMOS Non-Uniformity Mappings data arrayet ved forbindelse ellen mode skift
	RMH_ImageNonUniformityCorrection_ZeroNonUniformityMapArrayData(&ImageCMOSNonUniformityMapData[0], IRCamera.FrameWidth, IRCamera.FrameHeight);

	/*
	// Kontroller Om Applikationen Har En Ægte License Installerede
	RMH_Application_HandleOnlinePeriodicLicenseCheck();

	// Kontroller Applikationens feature status
	if (CheckApplicationWindowsStatus == 3567482) {

		// Kontroller om applikationens trial periode er udløbet
		if (TrialPeriodExpiredFlag == true) {

			// Skriv GUI Status Meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Your Trial Period Has Expired!, Please Extend The Period Or Buy A License.", _StatusMessageType_Warning);

			// Eksikver ikke resten af routinen
			return;

		}

	}
	*/

	// Er "Snapshot Analysis" Mode valgt
	if (GlobalVariables::GlobalCameraSourceDropList->SelectedIndex == _SnapShotAnalysisMode) {

		// Kontroller om en SnapShot fil, eller om "SnapShot Analysis" Mode allerede er aktiv og åben
		if (InSnapShotAnalysisModeFlag == true || SnapShotAnalysisModeFileInfo.IsFileReady == true) {

			// Håndter events og handlinger for nustilling af "SnapShot Analysis" Mode
			RMH_ThermalViewer_HandleSellectedDeviceOrModeChange();

		}

		// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
		//													   Læs RAW SnapShot Fil Til Analyse													           // 
		// ----------------------------------------------------------------------------------------------------------------------------------------------- // 

		// Åben "Open File" Dialog til valg af RAW Fil
		GlobalVariables::SnapShotAnalysisModeRAWFilePath = RMH_Winforms_GetOpenFileDialogDirectory();

		// Læs Valgte SnapShot fils informations parametere 
		SnapShotAnalysisModeFileInfo = RMH_AnalysisMode_ReadAndLoadPNGImage(GlobalVariables::SnapShotAnalysisModeRAWFilePath, &IRCameraFrameData[0]);

		// Blev der Registreret nogle fejl vev læsning af Snapshot filen 
		if (SnapShotAnalysisModeFileInfo.FileErrorFlag == false) {

			// Er den læste SnapShot Fil en .png fil
			if (SnapShotAnalysisModeFileInfo.IsPNGFileFlag == true) {

				// Skriv GUI Status Meddelse - Filen er en .png fil
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Extension Is: .png.", _StatusMessageType_Normal);

				// Kontroller den læste SnapShots fils frame bredde
				if (SnapShotAnalysisModeFileInfo.FrameWidth > 0) {

					// Skriv GUI Status Meddelse - Filens Frame Bredde
					RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Frame Width: " + RMH_Conversion_IntToStdString(SnapShotAnalysisModeFileInfo.FrameWidth) + " Pixels", _StatusMessageType_Normal);

					// Kontroller den læste SnapShots fils frame højde
					if (SnapShotAnalysisModeFileInfo.FrameHeight > 0) {

						// Skriv GUI Status Meddelse - Filens Frame højde
						RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Frame Height: " + RMH_Conversion_IntToStdString(SnapShotAnalysisModeFileInfo.FrameHeight) + " Pixels", _StatusMessageType_Normal);

						// Kontroller om filen er klar 
						if (SnapShotAnalysisModeFileInfo.IsFileReady == true) {

							// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
							//                                            Læs SnapShot Filens Meta Data Og Kontroller RAW ID String                                            // 
							// ----------------------------------------------------------------------------------------------------------------------------------------------- //

							// Konfigurer og Indstil Kamera Parametere fra læst video data information
							IRCamera.FrameWidth = SnapShotAnalysisModeFileInfo.FrameWidth;
							IRCamera.FrameHeight = SnapShotAnalysisModeFileInfo.FrameHeight;
							IRCamera.FrameRate = 1; // Frame Rate Er 1 i SnapShot Analysis Mode

							// Læs SnapShot filens identifikations og meta data
							SnapShotAnalysisModeFileMetaData = RMH_AnalysisMode_ReadRAWMetaData(IRCamera.FrameWidth, IRCamera.FrameHeight, &IRCameraFrameData[0]);

							// Nulstil RAW fil ID String Match flag
							RAWFileIDStringMatchFlag = false;

							// Kontroller om filen er en RAW Optagelse fra IRCAM Thermal Viewer Softwaret - Kontroller meta data stringet
							for (unsigned int i = 0; i < _RAWRecordingFileMetaDataIndex_IDStringStop; i++) {

								// Kontroller om filens RAW identifikations string matcher det forventede
								if (SnapShotAnalysisModeFileMetaData.RAWIDCharData[i] == _RAWFileIDData_FileIDString[i]) {

									// Opdater RAW fil ID String Match flag - skal matche på alle karakterer
									RAWFileIDStringMatchFlag = true;

								}
								else {

									// Nulstil RAW fil ID String Match flag - ID String Er Ikke Et Match
									RAWFileIDStringMatchFlag = false;
									// Bryd For Loop
									break;

								}

							}

							// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
							//                                    Kontroller Om Den Åbnede Fils Meta Data Indeholder Korrekte ID String                                        // 
							// ----------------------------------------------------------------------------------------------------------------------------------------------- //

							// Var SnapShot filens ID String et match
							if (RAWFileIDStringMatchFlag == true) {

								// Konfigurer og Indstil Kamera Parametere fra læst SnapShot data meta data
								IRCamera.FrameMetadataSize = SnapShotAnalysisModeFileMetaData.FileMetaDataSizeID;
								IRCamera.FrameWidthPixelOffset = SnapShotAnalysisModeFileMetaData.FileFrameWidthPixelOffsetID;
								IRCamera.FrameHeightPixelOffset = SnapShotAnalysisModeFileMetaData.FileFrameHeightPixelOffsetID;
								IRCamera.ThermalCameraSupportPool = SnapShotAnalysisModeFileMetaData.CameraPoolID;
								IRCamera.TemperatureCorrectionSetting = SnapShotAnalysisModeFileMetaData.RecordingTempCorrectionSetting;
								IRCamera.AmbientTemperatureSetting = SnapShotAnalysisModeFileMetaData.RecordingAmbientTempSetting;
								IRCamera.ReflectedTemperatureSetting = SnapShotAnalysisModeFileMetaData.RecordingReflectedTempSetting;
								IRCamera.HumiditySetting = SnapShotAnalysisModeFileMetaData.RecordingHumiditySetting;
								IRCamera.EmissivitySetting = SnapShotAnalysisModeFileMetaData.RecordingEmissivitySetting;
								IRCamera.DistanceSetting = SnapShotAnalysisModeFileMetaData.RecordingDistanceSetting;

								// Læs IR Kameraets Operative Konstanter - Relativt til supporterede pool
								RMH_IRThermalCamera_InitIRCameraConstants(&IRCamera, IRCamera.ThermalCameraSupportPool);

								// Formater Rå YUY2 Data, fra video fil, til 16Bit termisk data array
								RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(&IRCamera, &IRCameraFrameData[0], &FrameThermalDataRaw[0]);
								// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
								RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

								// Nulstil Antal læste video frames variabel
								IRCamera.NumbOfCapturedFrames = 0;

								// Læs Video Fil kamera dataens kalibrerings Parameter
								RMH_IRThermalCamera_ReadCalibrationParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);
								// Generer kamera Temperatur Loop-Up Tabel
								RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);

								// Læs og vis de læste interne camera konfigurations parametere - Fra SnapShot fil Meta data
								RMH_ThermalViewer_ReadAndDisplayRAWSnapShotFileCameraConfigParameters();

								// ------------------------------------------------- Opdater GUI Elementer & Komponenter ------------------------------------------------- //

								// Opdater Connect Knap Label Text
								GlobalVariables::GlobalConnectButton->Text = "File is Open\r\nAnd Ready";
								// Opdater Connect Knap border farve 
								GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

								// ----------------------------------- Initialisering OpenGL Rendererings Textur For Live Video Stream ----------------------------------- //

								// Konfigurer Live View Stream OpenGL Textur rendererings opløsning 
								GlobalVariables::OpenGLRender->RMH_OpenGL_InitImageTexture(IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize);
								// Konfigurer Live View OpenGL Zoom Textur rendererings opløsning 
								GlobalVariables::LiveViewZoomWindowRender->RMH_OpenGL_InitLiveViewZoomWindow(IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize);

								// Toggle/Opdater Live view enhanced billed opløsnings mode
								RMH_ThermalViewer_ToggleEnhancedLiveViewResolution();
								// Toggle/Opdater Live view Ultra billed opløsnings mode
								RMH_ThermalViewer_ToggleLiveViewUltraResolution();

								// --------------------------------- Start Læsning Af Video Fil, Processerings Thread & Main Update Timer -------------------------------- //

								// Opdater kamera "Fil er forbundet" flag
								IRCamera.ConnectedFlag = true;

								// Start Asynkron Thread operation
								GlobalVariables::GlobalVideoStreamThread->RunWorkerAsync();
								GlobalVariables::GlobalSecondaryProcessingThread->RunWorkerAsync();

								// Aktiver GUI update timer
								GlobalVariables::GlobalMainGUIUpdateTimer->Enabled = true;
								GlobalVariables::GlobalMainGUIUpdateTimer->Start();

								// Opdater Kamera "isStreaming" status flag
								IRCamera.isStreaming = true;

								// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
								//                                    Filen Er Kontrollerede Og Klar Til Læsning. "SnapShot Analysis" Er Aktiv                                     // 
								// ----------------------------------------------------------------------------------------------------------------------------------------------- //

								// Opdater "Er i SnapShot Analysis Mode" flaget
								InSnapShotAnalysisModeFlag = true;

								// Skriv GUI Status Meddelse - Filen Er Klar
								RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "SnapShot Analysis Is Now Ready - Open The Live View Stream To Analyse Your Snapshot.", _StatusMessageType_Success);

								// Aktiver Applikations Features
								RMH_Application_EnableApplicationFeatures();

							}
							else {

								// Skriv GUI Status Meddelse - Video Files er ikke en RAW.avi Fil
								RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "The Selected File Is Not A RAW.png File. Please Select A Correct RAW.png File!", _StatusMessageType_Error);

							}

						}
						else {

							// Skriv GUI Status Meddelse - SnapShot Fil Læsnings Fejl
							RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "An Error Occured While Reading The File, Please Try Another File", _StatusMessageType_Error);

							// Nulstil "Er i SnapShot Analysis Mode" flaget
							InSnapShotAnalysisModeFlag = false;

						}

					}
					else {

						// Skriv GUI Status Meddelse - Filen Frame højde fejl
						RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Error: File Has '0' Pixel Height!", _StatusMessageType_Error);

						// Nulstil "Er i SnapShot Analysis Mode" flaget
						InSnapShotAnalysisModeFlag = false;

					}

				}
				else {

					// Skriv GUI Status Meddelse - Filen Frame bredde fejl
					RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Error: File Has '0' Pixel Width!", _StatusMessageType_Error);

					// Nulstil "Er i SnapShot Analysis Mode" flaget
					InSnapShotAnalysisModeFlag = false;

				}

			}
			else {

				// Skriv GUI Status Meddelse - Filen er ikke en .png fil
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Is Not An .png File!", _StatusMessageType_Error);

				// Nulstil "Er i SnapShot Analysis Mode" flaget
				InSnapShotAnalysisModeFlag = false;

			}

		}
		else {

			// Skriv GUI Status Meddelse - SnapShot Fil Læsnings Fejl
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Could Not Read The Selected SnapShot File, Please Check If The Correct File Was Selected!", _StatusMessageType_Error);

			// Nulstil "Er i SnapShot Analysis Mode" flaget
			InSnapShotAnalysisModeFlag = false;

		}

		// Hvis "SnapShot Analysis" mode ikke er blevet aktiv
		if (InSnapShotAnalysisModeFlag == false) {

			// Håndter events og handlinger for nustilling af "SnapShot Analysis" Mode
			RMH_ThermalViewer_HandleSellectedDeviceOrModeChange();

			// Skriv GUI Status Meddelse - Filen er ikke blevet åbnet
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected SnapShot File Could Not Be Opened, Please Check The Selected File Or Choose Another File.", _StatusMessageType_Error);

		}

	}
	else if (GlobalVariables::GlobalCameraSourceDropList->SelectedIndex == _RecordingAnalysisMode) { // Er "Recording Analysis" Mode valgt

		// Kontroller om en video fil, eller om "Recording Analysis" Mode allerede er aktiv og åben
		if (InRecordingAnalysisModeFlag == true || RecordingAnalysisModeFileInfo.IsFileOpenFlag == true) {

			// Håndter events og handlinger for nustilling af "Recording Analysis" Mode
			RMH_ThermalViewer_HandleSellectedDeviceOrModeChange();

		}

		// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
		//													   Læs RAW Video Fil Til Analyse													           // 
		// ----------------------------------------------------------------------------------------------------------------------------------------------- // 

		// Åben "Open File" Dialog til valg af RAW Fil
		GlobalVariables::RecordingAnalysisModeRAWFilePath = RMH_Winforms_GetOpenFileDialogDirectory();

		// Læs Valgte Video fils informations parametere 
		RecordingAnalysisModeFileInfo = RMH_VideoFileReading_SetupRecordingAnalysisModeVideoFileReader(GlobalVariables::RecordingAnalysisModeRAWFilePath);

		// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
		//                         Kontroller Om Video Filen Er den korrekte RAW Fil og At Filen Er Blevet Korrekt Læst Og Er Klar                         // 
		// ----------------------------------------------------------------------------------------------------------------------------------------------- //

		//  Kontroller om video filen er blevet korrekt åbnet
		if (RecordingAnalysisModeFileInfo.IsFileOpenFlag == true) {

			// Skriv GUI Status Meddelse - Filen er blevet åbnet
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected Video File Is Open.", _StatusMessageType_Normal);

			// Kontroller om den læste fil er en ".avi" fil
			if (RecordingAnalysisModeFileInfo.IsAVIFileFlag == true) {

				// Skriv GUI Status Meddelse - Filen er en .avi fil
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Extension Is: .avi.", _StatusMessageType_Normal);

				// Kontroller den læste fils frame bredde
				if (RecordingAnalysisModeFileInfo.FrameWidth > 0) {

					// Skriv GUI Status Meddelse - Filens Frame Bredde
					RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Frame Width: " + RMH_Conversion_IntToStdString(RecordingAnalysisModeFileInfo.FrameWidth) + " Pixels", _StatusMessageType_Normal);

					// Kontroller den læste fils frame højde
					if (RecordingAnalysisModeFileInfo.FrameHeight > 0) {

						// Skriv GUI Status Meddelse - Filens Frame højde
						RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Frame Height: " + RMH_Conversion_IntToStdString(RecordingAnalysisModeFileInfo.FrameHeight) + " Pixels", _StatusMessageType_Normal);

						// Kontroller den læste fils antal frames nummer
						if (RecordingAnalysisModeFileInfo.NumberOfFrames > 0) {

							// Skriv GUI Status Meddelse - Filens antal frames
							RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Number Of Frames: " + RMH_Conversion_IntToStdString(RecordingAnalysisModeFileInfo.NumberOfFrames) + " Frames", _StatusMessageType_Normal);

							// Kontroller den læste fils frame rate
							if (RecordingAnalysisModeFileInfo.FrameRate > 0) {

								// Skriv GUI Status Meddelse - Filens Frame Rate
								RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Frame Rate: " + RMH_Conversion_IntToStdString(RecordingAnalysisModeFileInfo.FrameRate) + " FPS", _StatusMessageType_Normal);

								// Kontroller den læste fils varighed i sekundter
								if (RecordingAnalysisModeFileInfo.DurationTime > 0.0) {

									// Skriv GUI Status Meddelse - Filens varighed i sekundter
									RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "File Duration: " + RMH_Conversion_FloatToStdString(RecordingAnalysisModeFileInfo.DurationTime, 5) + " Sec", _StatusMessageType_Normal);

									// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
									//                                             Læs Video Filens Meta Data Og Kontroller RAW ID String                                              // 
									// ----------------------------------------------------------------------------------------------------------------------------------------------- //

									// Konfigurer og Indstil Kamera Parametere fra læst video data information
									IRCamera.FrameWidth = RecordingAnalysisModeFileInfo.FrameWidth;
									IRCamera.FrameHeight = RecordingAnalysisModeFileInfo.FrameHeight;
									IRCamera.FrameRate = RecordingAnalysisModeFileInfo.FrameRate;

									// Læs den første frame af data fra åbnede video fil
									RMH_VideoFileReading_ReadVideoFileFrame(1, RecordingAnalysisModeFileInfo.NumberOfFrames, &IRCameraFrameData[0]);

									// Læs Video filens identifikations og meta data
									RecordingAnalysisModeFileMetaData = RMH_AnalysisMode_ReadRAWMetaData(IRCamera.FrameWidth, IRCamera.FrameHeight, &IRCameraFrameData[0]);

									// Nulstil RAW fil ID String Match flag
									RAWFileIDStringMatchFlag = false;

									// Kontroller om filen er en RAW Optagelse fra IRCAM Thermal Viewer Softwaret - Kontroller meta data stringet
									for (unsigned int i = 0; i < _RAWRecordingFileMetaDataIndex_IDStringStop; i++) {

										// Kontroller om filens RAW identifikations string matcher det forventede
										if (RecordingAnalysisModeFileMetaData.RAWIDCharData[i] == _RAWFileIDData_FileIDString[i]) {

											// Opdater RAW fil ID String Match flag - skal matche på alle karakterer
											RAWFileIDStringMatchFlag = true;

										}
										else {

											// Nulstil RAW fil ID String Match flag - ID String Er Ikke Et Match
											RAWFileIDStringMatchFlag = false;
											// Bryd For Loop
											break;

										}

									}

									// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
									//                                    Kontroller Om Den Åbnede Fils Meta Data Indeholder Korrekte ID String                                        // 
									// ----------------------------------------------------------------------------------------------------------------------------------------------- //

									// Var video filens ID String et match
									if (RAWFileIDStringMatchFlag == true) {

										// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
										//                                                 Konfigurer Og Opstart "Recording Analysis Mode"                                                 // 
										// ----------------------------------------------------------------------------------------------------------------------------------------------- //

										// Konfigurer og Indstil Kamera Parametere fra læst video data meta data
										IRCamera.FrameMetadataSize = RecordingAnalysisModeFileMetaData.FileMetaDataSizeID;
										IRCamera.FrameWidthPixelOffset = RecordingAnalysisModeFileMetaData.FileFrameWidthPixelOffsetID;
										IRCamera.FrameHeightPixelOffset = RecordingAnalysisModeFileMetaData.FileFrameHeightPixelOffsetID;
										IRCamera.ThermalCameraSupportPool = RecordingAnalysisModeFileMetaData.CameraPoolID;
										IRCamera.TemperatureCorrectionSetting = RecordingAnalysisModeFileMetaData.RecordingTempCorrectionSetting;
										IRCamera.AmbientTemperatureSetting = RecordingAnalysisModeFileMetaData.RecordingAmbientTempSetting;
										IRCamera.ReflectedTemperatureSetting = RecordingAnalysisModeFileMetaData.RecordingReflectedTempSetting;
										IRCamera.HumiditySetting = RecordingAnalysisModeFileMetaData.RecordingHumiditySetting;
										IRCamera.EmissivitySetting = RecordingAnalysisModeFileMetaData.RecordingEmissivitySetting;
										IRCamera.DistanceSetting = RecordingAnalysisModeFileMetaData.RecordingDistanceSetting;

										// Læs IR Kameraets Operative Konstanter - Relativt til supporterede pool
										RMH_IRThermalCamera_InitIRCameraConstants(&IRCamera, IRCamera.ThermalCameraSupportPool);

										// Formater Rå YUY2 Data, fra video fil, til 16Bit termisk data array
										RMH_IRThermalCamera_ConvertYUY2To14BitThermalDataArray(&IRCamera, &IRCameraFrameData[0], &FrameThermalDataRaw[0]);
										// Læs IR kameraets frame Meta Data og Udregn Interne IR Sensor Temperaturer
										RMH_IRThermalCamera_ReadCalFrameMetaData(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);

										// Nulstil Antal læste video frames variabel
										IRCamera.NumbOfCapturedFrames = 0;

										// Læs Video Fil kamera dataens kalibrerings Parameter
										RMH_IRThermalCamera_ReadCalibrationParameters(&FrameThermalDataRaw[0], &IRCamera, IRCamera.ThermalCameraSupportPool);
										// Generer kamera Temperatur Loop-Up Tabel
										RMH_IRThermalCamera_GenerateThermoGrapicLookUpTable(&IRCamera, IRCamera.ThermalCameraSupportPool);

										// Læs og vis de læste interne camera konfigurations parametere - Fra video fil Meta data
										RMH_ThermalViewer_ReadAndDisplayRAWVideoFileCameraConfigParameters();

										// ------------------------------------------------- Opdater GUI Elementer & Komponenter ------------------------------------------------- //

										// Opdater Connect Knap Label Text
										GlobalVariables::GlobalConnectButton->Text = "File is Open\r\nAnd Ready";
										// Opdater Connect Knap border farve 
										GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

										// ----------------------------------- Initialisering OpenGL Rendererings Textur For Live Video Stream ----------------------------------- //

										// Konfigurer Live View Stream OpenGL Textur rendererings opløsning 
										GlobalVariables::OpenGLRender->RMH_OpenGL_InitImageTexture(IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize);
										// Konfigurer Live View OpenGL Zoom Textur rendererings opløsning 
										GlobalVariables::LiveViewZoomWindowRender->RMH_OpenGL_InitLiveViewZoomWindow(IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize);

										// Toggle/Opdater Live view enhanced billed opløsnings mode
										RMH_ThermalViewer_ToggleEnhancedLiveViewResolution();
										// Toggle/Opdater Live view Ultra billed opløsnings mode
										RMH_ThermalViewer_ToggleLiveViewUltraResolution();

										// --------------------------------- Start Læsning Af Video Fil, Processerings Thread & Main Update Timer -------------------------------- //

										// Opdater kamera "Fil er forbundet" flag
										IRCamera.ConnectedFlag = true;

										// Start Asynkron Thread operation
										GlobalVariables::GlobalVideoStreamThread->RunWorkerAsync();
										GlobalVariables::GlobalSecondaryProcessingThread->RunWorkerAsync();

										// Aktiver GUI update timer
										GlobalVariables::GlobalMainGUIUpdateTimer->Enabled = true;
										GlobalVariables::GlobalMainGUIUpdateTimer->Start();

										// Opdater Kamera "isStreaming" status flag
										IRCamera.isStreaming = true;

										// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
										//                                    Filen Er Kontrollerede Og Klar Til Læsning. "Recording Analysis" Er Aktiv                                    // 
										// ----------------------------------------------------------------------------------------------------------------------------------------------- //

										// Åben video playback controls panel formen
										OpenVideoPlayBackControlsFormFlag = true;

										// Opdater "Er i Recording Analysis Mode" flaget
										InRecordingAnalysisModeFlag = true;

										// Aktiver Recording Knap i Live View Tools Panel
										GlobalVariables::GlobalRecordingButton->Enabled = true;

										// Skriv GUI Status Meddelse - Filen Er Klar
										RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Recording Analysis Is Now Ready.", _StatusMessageType_Success);

										// Aktiver Applikations Features
										RMH_Application_EnableApplicationFeatures();

									}
									else {

										// Skriv GUI Status Meddelse - Video Files er ikke en RAW.avi Fil
										RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "The Selected File Is Not A RAW.avi File. Please Select A Correct RAW.avi File!", _StatusMessageType_Error);

									}

								}
								else {

									// Skriv GUI Status Meddelse - Filens varighed Fejl
									RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Error: Duration Is 0 Sec!", _StatusMessageType_Error);

									// Nulstil "Er i Recording Analysis Mode" flaget
									InRecordingAnalysisModeFlag = false;

								}

							}
							else {

								// Skriv GUI Status Meddelse - Frame Rate Fejl
								RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Error: Frame Rate Is '0' FPS!", _StatusMessageType_Error);

								// Nulstil "Er i Recording Analysis Mode" flaget
								InRecordingAnalysisModeFlag = false;

							}

						}
						else {

							// Skriv GUI Status Meddelse - Filen Har ingen frames
							RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Error: File Has '0' Total Frames!", _StatusMessageType_Error);

							// Nulstil "Er i Recording Analysis Mode" flaget
							InRecordingAnalysisModeFlag = false;

						}

					}
					else {

						// Skriv GUI Status Meddelse - Filen Frame højde fejl
						RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Error: File Has '0' Pixel Height!", _StatusMessageType_Error);

						// Nulstil "Er i Recording Analysis Mode" flaget
						InRecordingAnalysisModeFlag = false;

					}

				}
				else {

					// Skriv GUI Status Meddelse - Filen Frame Bredde fejl
					RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Error: File Has '0' Pixel Width!", _StatusMessageType_Error);

					// Nulstil "Er i Recording Analysis Mode" flaget
					InRecordingAnalysisModeFlag = false;

				}

			}
			else {

				// Skriv GUI Status Meddelse - Filen er ikke en .avi fil
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected File Is Not An .avi File!", _StatusMessageType_Error);

				// Nulstil "Er i Recording Analysis Mode" flaget
				InRecordingAnalysisModeFlag = false;

			}

		}
		else {

			// Skriv GUI Status Meddelse - Filen er ikke blevet åbnet
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected Video File Could Not Be Opened!", _StatusMessageType_Error);

			// Nulstil "Er i Recording Analysis Mode" flaget
			InRecordingAnalysisModeFlag = false;

		}

		// Hvis "Recording Analysis" mode ikke er blevet aktiv
		if (InRecordingAnalysisModeFlag == false) {

			// Håndter events og handlinger for nustilling af "Recording Analysis" Mode
			RMH_ThermalViewer_HandleSellectedDeviceOrModeChange();

			// Skriv GUI Status Meddelse - Filen er ikke blevet åbnet
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Selected Video File Could Not Be Opened, Please Check The Selected File.", _StatusMessageType_Error);

		}

	}
	else {

		// Nulstil "Er i Recording Analysis Mode" flaget
		InRecordingAnalysisModeFlag = false;

		// Nulstil Kamera connect Error Flag
		CameraConnectErrorFlag = false;

		// Komtroller om termisk kameraet allerede er forbundet og aktivt
		if (IRCamera.ConnectedFlag == true) {

			// Skriv GUI Status Meddelse - hvis et termisk kameraet allerede er forbundet og er aktivt
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "A Thermal Camera Is Already Connected & Streaming Video.", _StatusMessageType_Normal);
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Sellect Another Camera Or Press The Disconnect Button To Disconnect The Connected Thermal Camera.", _StatusMessageType_Normal);

		}
		else {

			// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
			//													   Forbind Til Valgte Termiske Kamera Pool													   // 
			// ----------------------------------------------------------------------------------------------------------------------------------------------- // 

			// Nulstil Antal læste video frames variabel
			IRCamera.NumbOfCapturedFrames = 0;

			// Skriv GUI Status Meddelse
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Connecting To The Sellected Thermal Camera...", _StatusMessageType_Normal);

			// Forbind til valgte termiske kamera og retuner status
			IRCamera = RMH_IRThermalCamera_ConnectToThermalCamera(GlobalVariables::GlobalCameraSourceDropList);

			// Skriv Kamera Status Meddelse til GUI Status Text Box
			RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, IRCamera.StatusMessage, _StatusMessageType_Normal);

			// ----------------------------------------------------------------------------------------------------------------------------------------------- // 
			//								  Hvis en aktiv forbindelse til det valgte termisk kameraet blev etableret										   // 
			// ----------------------------------------------------------------------------------------------------------------------------------------------- //  

			// Hvis en aktiv forbindelse til det valgte termisk kameraet blev etableret
			if (IRCamera.ConnectedFlag == true) {

				// ------------------------------------------------------------------------------------------------------------------------------------------- //
				//                                                     Skriv Forbindelses Status Meddelser                                                     //
				// ------------------------------------------------------------------------------------------------------------------------------------------- //

				// Skriv Kamera Device navn til GUI Status Text Box
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Device Name: " + IRCamera.CameraDeviceName, _StatusMessageType_Normal);

				// Skriv Kamera Device IR Sensor Frame Info til GUI Status Text Box
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Image Frame Width: " + RMH_Conversion_IntToStdString(IRCamera.FrameWidth) + " Pixels", _StatusMessageType_Normal);
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Image Frame Height: " + RMH_Conversion_IntToStdString(IRCamera.FrameHeight - IRCamera.FrameMetadataSize) + " Pixels", _StatusMessageType_Normal);

				// ------------------------------------------------------------------------------------------------------------------------------------------- //
				//             Håndter Events, Sekvenser & Handlinger Som Skal Fortages Efter Forbindelsen Med Et Valgt Pool Af Termiske kameraer              //
				// ------------------------------------------------------------------------------------------------------------------------------------------- //

				// Opdater Connect Knap Label Text
				GlobalVariables::GlobalConnectButton->Text = "Please Wait...";
				// Opdater Connect Knap border farve 
				GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::Yellow;
				GlobalVariables::GlobalConnectButton->Update();

				// Hvilken kamera pool tilhører det forbundet termiske kamera
				switch (IRCamera.ThermalCameraSupportPool) {

					// Supporterede Termiaks kamera Pool 1
					case _SupportedThermalCameras_Pool_1:

						// Håndter events, sekvenser og handlinger som skal fortages efter forbindelsen med et Pool 1 Termisk kamera 
						RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool1();

					break;

					// Supporterede Termiaks kamera Pool 2
					case _SupportedThermalCameras_Pool_2:

						// Håndter events, sekvenser og handlinger som skal fortages efter forbindelsen med et Pool 2 Termisk kamera 
						RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool2();

					break;

					// Supporterede Termiaks kamera Pool 3
					case _SupportedThermalCameras_Pool_3:

						// Håndter events, sekvenser og handlinger som skal fortages efter forbindelsen med et Pool 3 Termisk kamera 
						RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool3();

					break;

					// Supporterede Termiaks kamera Pool 4
					case _SupportedThermalCameras_Pool_4:

						// Håndter events, sekvenser og handlinger som skal fortages efter forbindelsen med et Pool 3 Termisk kamera 
						RMH_IRThermalCamera_ThermalCameraInitialConnectionEvents_Pool4();

					break;

				}

				// ------------------------------------------------------------------------------------------------------------------------------------------- //
				//                        Håndter Events, Sekvenser & Handlinger Efter Start-Op Initiliseringen Af Det Termiske Kamera                         //
				// ------------------------------------------------------------------------------------------------------------------------------------------- //

				// Hvis der ikke var nogle Kamera forbindelses fejl
				if (CameraConnectErrorFlag == false) {

					// ------------------------------------------------- Opdater GUI Elementer & Komponenter ------------------------------------------------- //

					// Opdater Connect Knap Label Text
					GlobalVariables::GlobalConnectButton->Text = "Connected";
					// Opdater Connect Knap border farve 
					GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

					// Aktiver Kamera konfigurations GUI komponenter
					RMH_ThermalViewer_EnableCameraConfigurationControls(true);

					// Aktiver Kamera Disconnect Knap
					GlobalVariables::GlobalDisconnectButton->Enabled = true;
					// Aktiver Auto Shutter kalibration knap i indstillings menuen
					GlobalVariables::GlobalAutoShutterCalButton->Enabled = true;
					// Aktiver Temperatur Drift Baseret kalibration knap i indstillings menuen
					GlobalVariables::GlobalSensorDriftCalButton->Enabled = true;
					// Aktiver Kalibrerings knap i Live View Tools Panel
					GlobalVariables::GlobalCalibrateCameraButton->Enabled = true;
					// Aktiver Temperatur Range knap i Live View Tools Panel
					GlobalVariables::GlobalTempRangeButton->Enabled = true;
					// Aktiver Recording Knap i Live View Tools Panel
					GlobalVariables::GlobalRecordingButton->Enabled = true;

					// ----------------------------------- Initialisering OpenGL Rendererings Textur For Live Video Stream ----------------------------------- //

					// Konfigurer Live View Stream OpenGL Textur rendererings opløsning 
					GlobalVariables::OpenGLRender->RMH_OpenGL_InitImageTexture(IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize);
					// Konfigurer Live View OpenGL Zoom Textur rendererings opløsning 
					GlobalVariables::LiveViewZoomWindowRender->RMH_OpenGL_InitLiveViewZoomWindow(IRCamera.FrameWidth, IRCamera.FrameHeight - IRCamera.FrameMetadataSize);

					// Toggle/Opdater Live view enhanced billed opløsnings mode
					RMH_ThermalViewer_ToggleEnhancedLiveViewResolution();
					// Toggle/Opdater Live view Ultra billed opløsnings mode
					RMH_ThermalViewer_ToggleLiveViewUltraResolution();

					// ------------------------------- Start Kamera Video Capturing, Processerings Thread & Main Update Timer -------------------------------- //

					// Skriv GUI Status Meddelse
					RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Starting The Live View Video Stream...", _StatusMessageType_Normal);

					// Start Kamera video capturing
					RMH_IRThermalCamera_StartCapturing();

					// Start Asynkron Thread operation
					GlobalVariables::GlobalVideoStreamThread->RunWorkerAsync();
					GlobalVariables::GlobalSecondaryProcessingThread->RunWorkerAsync();

					// Aktiver GUI update timer
					GlobalVariables::GlobalMainGUIUpdateTimer->Enabled = true;
					GlobalVariables::GlobalMainGUIUpdateTimer->Start();

					// Opdater Kamera "isStreaming" status flag
					IRCamera.isStreaming = true;

					// ----------------------------------------------------- Skriv Slut Status Meddelse ------------------------------------------------------ //

					// Skriv GUI Status Meddelse
					RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "The Camera Is Now Streaming Live Video.", _StatusMessageType_Success);

					// Aktiver Applikations Features
					RMH_Application_EnableApplicationFeatures();

					// --------------------------------------------------------------------------------------------------------------------------------------- //

				}
				else { // Hvis der blev registreret Kamera forbindelses fejl

					// ------------------------------------------------ Nulstilling Af Relavante Kontrol Flag ------------------------------------------------ //

					// Nulstil Kamera connect Error Flag
					CameraConnectErrorFlag = false;

					// Nulstil Kamera connect flag
					IRCamera.ConnectedFlag = false;

					// ------------------------------------------- Stop Kamera Video Capturing & Main Update Timer ------------------------------------------- //

					// Deaktiver GUI update timer
					GlobalVariables::GlobalMainGUIUpdateTimer->Enabled = false;
					GlobalVariables::GlobalMainGUIUpdateTimer->Stop();

					// Opdater Connect Knap borer farve - indiker forbindelses fejl
					GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

					// Skriv GUI status meddelse
					RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "ERROR: Camera Video Feed Could Not Be Started!", _StatusMessageType_Error);

					// --------------------------------------------------------------------------------------------------------------------------------------- //

				}

				// ------------------------------------------------------------------------------------------------------------------------------------------- //
			}
			else { // Hvis en aktiv forbindelse til det valgte termisk kameraet IKKE blev etableret

				// Nulstil Connect Knap Label Text
				GlobalVariables::GlobalConnectButton->Text = "Camera Not Found!";
				// Opdater Connect Knap border farve 
				GlobalVariables::GlobalConnectButton->FlatAppearance->BorderColor = System::Drawing::Color::Red;

				// Skriv Kamera Device navn til GUI Status Text Box
				RMH_Winforms_RichTextBox_WriteLine(GlobalVariables::GlobalGUIInfoTextArea, "Thermal Camera Device Could Not Be Found, Or A Connection Error Occured", _StatusMessageType_Error);

			}
		}

	}

}

// ------------------------------------------------------------------------------------------------------------------------------- //




