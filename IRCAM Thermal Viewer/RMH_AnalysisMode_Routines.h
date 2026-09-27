
/*
 *  RMH_RecordingAnalysisMode_Routines.h
 *
 *  Author: Rune Mark Hansen
 *  Date: Juli 2023
 *
 */

#pragma once

 // RMH_RecordingAnalysisMode_Routines.h
#ifndef RMH_RecordingAnalysisMode_Routines_H 
#define RMH_RecordingAnalysisMode_Routines_H

// Inkluderede Biblioteker
#include <opencv2/opencv.hpp>

// RAW Optagning/Snapshot Identifikations Data Reference Macroer
#define _RAWFileIDData_FileIDString                                      "IRCAM.RAM"

// RAW Optagning Meta Data Index Reference Macroer
#define _RAWRecordingFileMetaDataIndex_IDStringStop                      8
#define _RAWRecordingFileMetaDataIndex_CameraPool                        9
#define _RAWRecordingFileMetaDataIndex_MetaDataSizeMSB                   10
#define _RAWRecordingFileMetaDataIndex_MetaDataSizeLSB                   11
#define _RAWRecordingFileMetaDataIndex_FrameWidthPixelOffsetMSB          12
#define _RAWRecordingFileMetaDataIndex_FrameWidthPixelOffsetLSB          13
#define _RAWRecordingFileMetaDataIndex_FrameHeightPixelOffsetMSB         14
#define _RAWRecordingFileMetaDataIndex_FrameHeightPixelOffsetLSB         15 
#define _RAWRecordingFileMetaDataIndex_CameraTempCorrectionMSB           16         
#define _RAWRecordingFileMetaDataIndex_CameraTempCorrectionLSB1          17         
#define _RAWRecordingFileMetaDataIndex_CameraTempCorrectionLSB2          18          
#define _RAWRecordingFileMetaDataIndex_CameraTempCorrectionLSB3          19 
#define _RAWRecordingFileMetaDataIndex_CameraAmbientTempMSB              20             
#define _RAWRecordingFileMetaDataIndex_CameraAmbientTempLSB1             21              
#define _RAWRecordingFileMetaDataIndex_CameraAmbientTempLSB2             22        
#define _RAWRecordingFileMetaDataIndex_CameraAmbientTempLSB3             23
#define _RAWRecordingFileMetaDataIndex_CameraReflectedTempMSB            24           
#define _RAWRecordingFileMetaDataIndex_CameraReflectedTempLSB1           25            
#define _RAWRecordingFileMetaDataIndex_CameraReflectedTempLSB2           26           
#define _RAWRecordingFileMetaDataIndex_CameraReflectedTempLSB3           27 
#define _RAWRecordingFileMetaDataIndex_CameraHumidityMSB                 28           
#define _RAWRecordingFileMetaDataIndex_CameraHumidityLSB1                29         
#define _RAWRecordingFileMetaDataIndex_CameraHumidityLSB2                30          
#define _RAWRecordingFileMetaDataIndex_CameraHumidityLSB3                31
#define _RAWRecordingFileMetaDataIndex_CameraEmissivityMSB               32              
#define _RAWRecordingFileMetaDataIndex_CameraEmissivityLSB1              33              
#define _RAWRecordingFileMetaDataIndex_CameraEmissivityLSB2              34             
#define _RAWRecordingFileMetaDataIndex_CameraEmissivityLSB3              35
#define _RAWRecordingFileMetaDataIndex_CameraDistanceMSB                 36           
#define _RAWRecordingFileMetaDataIndex_CameraDistanceLSB                 37      
#define _RAWRecordingFileMetaDataIndex_DataEndChar                       38

// Video fil skrivnings index reference macroer
#define _VideoFileWriteObject_RecordingAnalysisModeFile                  1
#define _VideoFileWriteObject_LiveViewStreamFile                         2

// Læsning af video fil Error koder Reference Macroer
#define _ReadAVIFile_StatusCode_FrameReadOK                              1
#define _ReadAVIFile_StatusCode_FileIsNotOpen                            2
#define _ReadAVIFile_StatusCode_FrameNumberOutOfRange                    3
#define _ReadAVIFile_StatusCode_FrameReadError                           4

// --------------------------------------------------- Blbliotek Reference Klasser --------------------------------------------------- //

// Læst RAW Video Fil Information Klasse struktur
struct RAWVideoFileInfo {

    // RAW Video Fil Variabler og objekter
    bool IsFileOpenFlag = false;
    bool IsAVIFileFlag = false;
    unsigned int FrameWidth = 0;
    unsigned int FrameHeight = 0;
    double FrameRate = 0.0;
    unsigned long NumberOfFrames = 0;
    double DurationTime = 0.0;

};

// Læst RAW SnapShot Fil Information Klasse struktur
struct RAWSnapShotFileInfo {

    // RAW Snapshot Fil Variabler og objekter
    bool FileErrorFlag = false;
    bool IsFileReady = false;
    bool IsPNGFileFlag = false;
    unsigned int FrameWidth = 0;
    unsigned int FrameHeight = 0;

};

// RAW Video Fil Identifikations Klasse struktur
struct RAWFileIDFormat {

    // RAW Video Fil ID Variabler og objekter
    unsigned char RAWIDCharData[200] = { 0 };
    unsigned short CameraPoolID = 0;
    unsigned int FileMetaDataSizeID = 0;
    unsigned int FileFrameWidthPixelOffsetID = 0;
    unsigned int FileFrameHeightPixelOffsetID = 0;
    float RecordingTempCorrectionSetting = 0;
    float RecordingAmbientTempSetting = 0;
    float RecordingReflectedTempSetting = 0;
    float RecordingHumiditySetting = 0;
    float RecordingEmissivitySetting = 0;
    unsigned int RecordingDistanceSetting = 0;

};

// -------------------------------- Fælles Video Fil Optagnings Og Analysis Mode Håndterings Routiner -------------------------------- //

void RMH_AnalysisMode_AddIDAndMetaDataToFrameArray(unsigned int FrameWidth, unsigned int FrameHeight, unsigned char* RAWFrameDataArray,
    unsigned short CameraPoolID, unsigned int MetaDataSizeID, unsigned int FrameWidthPixelOffsetID, unsigned int FrameHeightPixelOffsetID,
    float CameraTempCorrectionSetting, float CameraAmbientTempSetting, float CameraReflectedTempSetting, float CameraHumiditySetting, float CameraEmissivitySetting, unsigned int CameraDistanceSetting);

RAWFileIDFormat RMH_AnalysisMode_ReadRAWMetaData(unsigned int FrameWidth, unsigned int FrameHeight, unsigned char* RAWFrameDataArray);

// ---------------------------- Video Fil Optagnings, Konfigurations, Indstillings Og Skrivnings Routiner ---------------------------- //

bool RMH_VideoFileRecording_SetupRecordingAnalysisModeVideoFile(System::String^ FileSavePath, System::String^ FileName, unsigned int FrameWidth, unsigned int FrameHeight, double FrameRate);
bool RMH_VideoFileRecording_SetupLiveViewCaptureVideoFile(System::String^ FileSavePath, System::String^ FileName, unsigned int FrameWidth, unsigned int FrameHeight, double FrameRate);
void RMH_VideoFileRecording_WriteDataToFile(unsigned short FileIndex, unsigned int FrameWidth, unsigned int FrameHeight, unsigned char* CapturedFrameData);
void RMH_VideoFileRecording_WriteDataToFile16Bit(unsigned short FileIndex, unsigned int FrameWidth, unsigned int FrameHeight, unsigned short* CapturedFrameData);
bool RMH_VideoFileRecording_CloseVideoFileWriting(unsigned short FileIndex);

// ----------------------------- Video Fil Læsnings, Konfigurations, Indstillings Og Skrivnings Routiner ----------------------------- //

bool RMH_VideoFileReading_IsRECAnalysisModeFileOpen();
RAWVideoFileInfo RMH_VideoFileReading_SetupRecordingAnalysisModeVideoFileReader(System::String^ AVIFilePath);
unsigned int RMH_VideoFileReading_ReadVideoFileFrame(unsigned long TargetFrameNumber, unsigned long FileTotalNumOfFrames, unsigned char* ReadFrameData);
bool RMH_VideoFileReading_CloseRecordingAnalysisModeFile();

// --------------------------- SnapShot Fil Læsnings, Konfigurations, Indstillings Og Skrivnings Routiner ---------------------------- //

RAWSnapShotFileInfo RMH_AnalysisMode_ReadAndLoadPNGImage(System::String^ ImageFilePath, unsigned char* ImageData);

// ----------------------------------------------------------------------------------------------------------------------------------- //

#endif /* RMH_RecordingAnalysisMode_Routines_H */
