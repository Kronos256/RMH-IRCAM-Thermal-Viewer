
/*
 *  RMH_AnalysisMode_Routines.c
 *
 *  Author: Rune Mark Hansen
 *  Date: July 2023
 *
 */

// Inkluderede Blblioteker
#include <Windows.h>
#include <wincodec.h>
#include <opencv2/opencv.hpp>
#include <msclr/marshal_cppstd.h>
#include "RMH_MathConversions_Library.h"
#include "RMH_AnalysisMode_Routines.h"

// Globale namespaces
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace std;

// Globale varibler og objekter
cv::Mat FrameFormatRGB;
cv::VideoWriter RECAnalysisModeFileWriterRAW;
cv::VideoWriter LiveViewDataFileWriter;
cv::VideoCapture RECAnalysisModeFileReader;

// -------------------------------- Fælles Video Fil Optagnings Og Analysis Mode Håndterings Routiner -------------------------------- //

void RMH_AnalysisMode_AddIDAndMetaDataToFrameArray(unsigned int FrameWidth, unsigned int FrameHeight, unsigned char *RAWFrameDataArray,
    unsigned short CameraPoolID, unsigned int MetaDataSizeID, unsigned int FrameWidthPixelOffsetID, unsigned int FrameHeightPixelOffsetID, 
    float CameraTempCorrectionSetting, float CameraAmbientTempSetting, float CameraReflectedTempSetting, float CameraHumiditySetting, float CameraEmissivitySetting, unsigned int CameraDistanceSetting) {

    // Routinen tilføjer en ekstra række af data til givet Frame Meta data areal.
    // Dataen benyttes til at idenfificerer dataen i en gemt video eller Snapshot fil, samt filen selv
    // Dette benyttes ligeledes også til at tilføje meta data til den optagede fil.

    // Lokale variabler
    const char* IdentificationDataPointer;
    unsigned int lineSize = FrameWidth * 3;
    unsigned int lineIndex = FrameHeight - 1;
    unsigned int startIndex = lineIndex * lineSize;
    unsigned char SettingsValueArray[4];

    // Skriv Filens identifikations data string til Frame Meta data areal
    for (unsigned int i = 0; i < _RAWRecordingFileMetaDataIndex_IDStringStop; i++) {

        // Skriv karakterer til Frame Meta data areal
        RAWFrameDataArray[startIndex + i] = _RAWFileIDData_FileIDString[i];

    }

    // Skriv Filens Kamera Pool identifikations data til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraPool] = CameraPoolID;

    // Skriv Filens Meta Data Størrelses identifikations data til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_MetaDataSizeMSB] = (MetaDataSizeID & 0xFF00) >> 8;
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_MetaDataSizeLSB] = MetaDataSizeID & 0x00FF;

    // Skriv Filens Frame Width Pixel Offsets identifikations data til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_FrameWidthPixelOffsetMSB] = (FrameWidthPixelOffsetID & 0xFF00) >> 8;
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_FrameWidthPixelOffsetLSB] = FrameWidthPixelOffsetID & 0x00FF;

    // Skriv Filens Frame Height Pixel Offsets identifikations data til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_FrameHeightPixelOffsetMSB] = (FrameHeightPixelOffsetID & 0xFF00) >> 8;
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_FrameHeightPixelOffsetLSB] = FrameHeightPixelOffsetID & 0x00FF;

    // Konveter temperatur Korrections værdi til 4x8Bit
    RMH_Conversion_SinglePrecisionFloatTo4xUnsignedChar(CameraTempCorrectionSetting, &SettingsValueArray[0]);
    // Skriv Det termiske kameras Temperatur Korrektions værdi til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraTempCorrectionMSB] = SettingsValueArray[0];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraTempCorrectionLSB1] = SettingsValueArray[1];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraTempCorrectionLSB2] = SettingsValueArray[2];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraTempCorrectionLSB3] = SettingsValueArray[3];

    // Konveter ambient temperatur værdi til 4x8Bit
    RMH_Conversion_SinglePrecisionFloatTo4xUnsignedChar(CameraAmbientTempSetting, &SettingsValueArray[0]);
    // Skriv Det termiske kameras ambient Temperatur værdi til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraAmbientTempMSB] = SettingsValueArray[0];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraAmbientTempLSB1] = SettingsValueArray[1];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraAmbientTempLSB2] = SettingsValueArray[2];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraAmbientTempLSB3] = SettingsValueArray[3];

    // Konveter reflekterede temperatur værdi til 4x8Bit
    RMH_Conversion_SinglePrecisionFloatTo4xUnsignedChar(CameraReflectedTempSetting, &SettingsValueArray[0]);
    // Skriv Det termiske kameras reflekterede Temperatur værdi til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraReflectedTempMSB] = SettingsValueArray[0];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraReflectedTempLSB1] = SettingsValueArray[1];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraReflectedTempLSB2] = SettingsValueArray[2];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraReflectedTempLSB3] = SettingsValueArray[3];

    // Konveter humidity indstilling værdi til 4x8Bit
    RMH_Conversion_SinglePrecisionFloatTo4xUnsignedChar(CameraHumiditySetting, &SettingsValueArray[0]);
    // Skriv Det termiske kameras humidity indstillings værdi til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraHumidityMSB] = SettingsValueArray[0];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraHumidityLSB1] = SettingsValueArray[1];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraHumidityLSB2] = SettingsValueArray[2];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraHumidityLSB3] = SettingsValueArray[3];

    // Konveter Emissivity indstilling værdi til 4x8Bit
    RMH_Conversion_SinglePrecisionFloatTo4xUnsignedChar(CameraEmissivitySetting, &SettingsValueArray[0]);
    // Skriv Det termiske kameras Emissivity indstillings værdi til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraEmissivityMSB] = SettingsValueArray[0];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraEmissivityLSB1] = SettingsValueArray[1];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraEmissivityLSB2] = SettingsValueArray[2];
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraEmissivityLSB3] = SettingsValueArray[3];

    // Skriv Det termiske kameras Distance indstillings værdi til Frame Meta data areal
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraDistanceMSB] = (CameraDistanceSetting & 0xFF00) >> 8;
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_CameraDistanceLSB] = CameraDistanceSetting & 0x00FF;

    // Skriv Filens End-Karakter - indiker slut på ID data
    RAWFrameDataArray[startIndex + _RAWRecordingFileMetaDataIndex_DataEndChar] = '!';

}

RAWFileIDFormat RMH_AnalysisMode_ReadRAWMetaData(unsigned int FrameWidth, unsigned int FrameHeight, unsigned char* RAWFrameDataArray) {

    // Routinen læser RAW filens identifikations/Meta data.
    // Dataen benyttes til at idenfificerer dataen i filen og om filen er en RAW fil til analyse i SnapShot Eller Recording "Analysis Mode"

    // Lokale variabler
    RAWFileIDFormat FileIDData;
    unsigned int LineSize = FrameWidth * 3;
    unsigned int LineIndex = FrameHeight - 1;
    unsigned int StartIndex = LineIndex * LineSize;
    unsigned char SettingsValueArray[4];

    // Loop fra start index af tilføjet Meta linje
    for (unsigned int i = StartIndex, j = 0; i < StartIndex + LineSize; i++, j++) {

        // Læs Filens Identifikations karakterer
        if (j <= _RAWRecordingFileMetaDataIndex_IDStringStop) {  FileIDData.RAWIDCharData[j] = RAWFrameDataArray[i]; }
        // Læs Filens Kamera Pool Meta data
        if (j == _RAWRecordingFileMetaDataIndex_CameraPool) { FileIDData.CameraPoolID = RAWFrameDataArray[i]; }
        // Læs Filens Meta data størrelses Meta data
        if (j == _RAWRecordingFileMetaDataIndex_MetaDataSizeMSB) { FileIDData.FileMetaDataSizeID = ((unsigned int)RAWFrameDataArray[i] << 8) | (unsigned int)RAWFrameDataArray[i + 1]; }
        // Læs Frame Width Pixel Offsets Meta data
        if (j == _RAWRecordingFileMetaDataIndex_FrameWidthPixelOffsetMSB) { FileIDData.FileFrameWidthPixelOffsetID = ((unsigned int)RAWFrameDataArray[i] << 8) | (unsigned int)RAWFrameDataArray[i + 1]; }
        // Læs Frame Height Pixel Offsets Meta data
        if (j == _RAWRecordingFileMetaDataIndex_FrameHeightPixelOffsetMSB) { FileIDData.FileFrameHeightPixelOffsetID = ((unsigned int)RAWFrameDataArray[i] << 8) | (unsigned int)RAWFrameDataArray[i + 1]; }

        // Læs det termiske kameras Temperatur Korrektions parameter
        if (j == _RAWRecordingFileMetaDataIndex_CameraTempCorrectionMSB) { FileIDData.RecordingTempCorrectionSetting = RMH_Conversion_UnsignedCharToSinglePrecisionFloat2(RAWFrameDataArray[i + 0], RAWFrameDataArray[i + 1], RAWFrameDataArray[i + 2], RAWFrameDataArray[i + 3]); }
        // Læs det termiske kameras Ambiente Temperatur parameter
        if (j == _RAWRecordingFileMetaDataIndex_CameraAmbientTempMSB) { FileIDData.RecordingAmbientTempSetting = RMH_Conversion_UnsignedCharToSinglePrecisionFloat2(RAWFrameDataArray[i + 0], RAWFrameDataArray[i + 1], RAWFrameDataArray[i + 2], RAWFrameDataArray[i + 3]); }
        // Læs det termiske kameras reflekterede Temperatur parameter
        if (j == _RAWRecordingFileMetaDataIndex_CameraReflectedTempMSB) { FileIDData.RecordingReflectedTempSetting = RMH_Conversion_UnsignedCharToSinglePrecisionFloat2(RAWFrameDataArray[i + 0], RAWFrameDataArray[i + 1], RAWFrameDataArray[i + 2], RAWFrameDataArray[i + 3]); }
        // Læs det termiske kameras Humidity indstillings parameter
        if (j == _RAWRecordingFileMetaDataIndex_CameraHumidityMSB) { FileIDData.RecordingHumiditySetting = RMH_Conversion_UnsignedCharToSinglePrecisionFloat2(RAWFrameDataArray[i + 0], RAWFrameDataArray[i + 1], RAWFrameDataArray[i + 2], RAWFrameDataArray[i + 3]); }
        // Læs det termiske kameras Emissivity indstillings parameter
        if (j == _RAWRecordingFileMetaDataIndex_CameraEmissivityMSB) { FileIDData.RecordingEmissivitySetting = RMH_Conversion_UnsignedCharToSinglePrecisionFloat2(RAWFrameDataArray[i + 0], RAWFrameDataArray[i + 1], RAWFrameDataArray[i + 2], RAWFrameDataArray[i + 3]); }
        // Læs det termiske kameras Distance indstillings parameter
        if (j == _RAWRecordingFileMetaDataIndex_CameraDistanceMSB) { FileIDData.RecordingDistanceSetting = ((unsigned int)RAWFrameDataArray[i] << 8) | (unsigned int)RAWFrameDataArray[i + 1]; }

        // Kontroller om slut karakteren er nåede
        if (RAWFrameDataArray[i] == '!') {

            // Bryd For Loop
            break;

        }
        
    }
    
    // Retuner identifications data struktur
    return FileIDData;

}

// ---------------------------- Video Fil Optagnings, Konfigurations, Indstillings Og Skrivnings Routiner ---------------------------- //

bool RMH_VideoFileRecording_SetupRecordingAnalysisModeVideoFile(System::String^ FileSavePath, System::String^ FileName, unsigned int FrameWidth, unsigned int FrameHeight, double FrameRate) {

    // Routinen konfigurerer og klargøre en .avi video fil optagning af RAW kamera data.
    // Denne fil benyttes i "REcording Analysis Mode".
    // Det gemte AVI video fils navn, er formaterede på formen: "'FileName'_HHmmssddMMyyyy"
    // Input Fil Path (FileSavePath) Eksempel: C:\Users\User\Desktop
    
    // Formater Filens navne string (Recording_HHmmssddMMyyyy)
    System::String^ FileNameDate = System::DateTime::Now.ToString("HHmmssddMMyyyy");

    // Konverter givet fil navn string til et cv::string - med tilhørende .avi fil type string 
    cv::String FileNameString = RMH_VideoRecording_ConvertSystemStringToCVString(FileSavePath + "/" + FileName + FileNameDate + ".avi");

    // Konfigurer og Åben AVI video filen til skrivning - Fourcc: RGBA - RAW Format
    RECAnalysisModeFileWriterRAW.open(FileNameString, cv::VideoWriter::fourcc('R', 'G', 'B', 'A'), FrameRate, cv::Size(FrameWidth, FrameHeight + 1));

    // Kontroller om "VideoWriter" objektet er blevet korrekt initialiseret og er klar til skrivning.
    if (RECAnalysisModeFileWriterRAW.isOpened() == true) {

        // Retuner: "VideoWriter" objekt initialisering OK
        return true;

    }
    else {

        // Retuner: "VideoWriter" objekt initialisering fejl!
        return false;

    }

}

bool RMH_VideoFileRecording_SetupLiveViewCaptureVideoFile(System::String^ FileSavePath, System::String^ FileName, unsigned int FrameWidth, unsigned int FrameHeight, double FrameRate) {

    // Routinen konfigurerer og klargøre en .avi video fil optagning af Live View Stream dataen.
    // Det gemte AVI video fils navn, er formaterede på formen: "'FileName'_HHmmssddMMyyyy"
    // Input Fil Path (FileSavePath) Eksempel: C:\Users\User\Desktop

    // Formater Filens navne string (Recording_HHmmssddMMyyyy)
    System::String^ FileNameDate = System::DateTime::Now.ToString("HHmmssddMMyyyy");

    // Konverter givet fil navn string til et cv::string - med tilhørende .avi fil type string 
    cv::String FileNameString = RMH_VideoRecording_ConvertSystemStringToCVString(FileSavePath + "/" + FileName + FileNameDate + ".avi");

    // Konfigurer og Åben AVI video filen til skrivning - Fourcc: YUYV 
    LiveViewDataFileWriter.open(FileNameString, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), FrameRate, cv::Size(FrameWidth, FrameHeight));

    // Kontroller om "VideoWriter" objektet er blevet korrekt initialiseret og er klar til skrivning.
    if (LiveViewDataFileWriter.isOpened() == true) {

        // Retuner: "VideoWriter" objekt initialisering OK
        return true;

    }
    else {

        // Retuner: "VideoWriter" objekt initialisering fejl!
        return false;

    }

}

void RMH_VideoFileRecording_WriteDataToFile(unsigned short FileIndex, unsigned int FrameWidth, unsigned int FrameHeight, unsigned char *CapturedFrameData) {

    // Routinen skriver givet frame data array til valgte video fil

    // Hvilket VideoWriter objekt er blevet valgt
    switch (FileIndex) {

        // VideoWriter Objekt nummer 1
        case _VideoFileWriteObject_RecordingAnalysisModeFile:

            // Tilføj ekstra pixel række til Analysis Mode Fil - Til ID Data
            FrameHeight = FrameHeight + 1;

        break;

    }

    // Konvereter Billede data til cv::Mat format
    cv::Mat MatFrame(FrameHeight, FrameWidth, CV_8UC3, CapturedFrameData);

    // Konverter BGR Format Til RGB Format
    cv::cvtColor(MatFrame, FrameFormatRGB, cv::COLOR_BGR2RGB);

    // Hvilket VideoWriter objekt er blevet valgt
    switch (FileIndex) {

        // VideoWriter Objekt nummer 1 - Recording Analysis Mode Fil
        case _VideoFileWriteObject_RecordingAnalysisModeFile:

            // Skriv Frame dataen til AVI video filen
            RECAnalysisModeFileWriterRAW.write(FrameFormatRGB);
            
        break;

        // VideoWriter Objekt nummer 2 - Live View Stream Fil
        case _VideoFileWriteObject_LiveViewStreamFile:

            // Skriv Frame dataen til AVI video filen
            LiveViewDataFileWriter.write(FrameFormatRGB);

        break;

    }

}

void RMH_VideoFileRecording_WriteDataToFile16Bit(unsigned short FileIndex, unsigned int FrameWidth, unsigned int FrameHeight, unsigned short* CapturedFrameData) {

    // Routinen skriver givet frame data array til valgte video fil

    // Lokale Objekter
    cv::Mat MatFrame8U;

    // Hvilket VideoWriter objekt er blevet valgt
    switch (FileIndex) {

        // VideoWriter Objekt nummer 1
        case _VideoFileWriteObject_RecordingAnalysisModeFile:

            // Tilføj ekstra pixel række til Analysis Mode Fil - Til ID Data
            FrameHeight = FrameHeight + 1;

        break;

    }

    // Konvereter Billede data til cv::Mat format
    cv::Mat MatFrame(FrameHeight, FrameWidth, CV_16UC3, CapturedFrameData);

    // Konverter 16Bit Video Frame Til 8Bit (1 / 256 = 0.00390625)
    MatFrame.convertTo(MatFrame8U, CV_8UC3, 0.00390625);

    // Konverter BGR Format Til RGB Format
    cv::cvtColor(MatFrame8U, FrameFormatRGB, cv::COLOR_BGR2RGB);

    // Hvilket VideoWriter objekt er blevet valgt
    switch (FileIndex) {

        // VideoWriter Objekt nummer 1 - Recording Analysis Mode Fil
        case _VideoFileWriteObject_RecordingAnalysisModeFile:

            // Skriv Frame dataen til AVI video filen
            RECAnalysisModeFileWriterRAW.write(FrameFormatRGB);

        break;

        // VideoWriter Objekt nummer 2 - Live View Stream Fil
        case _VideoFileWriteObject_LiveViewStreamFile:

            // Skriv Frame dataen til AVI video filen
            LiveViewDataFileWriter.write(FrameFormatRGB);

        break;

    }

}

bool RMH_VideoFileRecording_CloseVideoFileWriting(unsigned short FileIndex) {

    // Routinen lukker og gemmer AVI video filen
    // Retunerer "true" hvis "VideoWriter" objektet er blevet korrekt lukket

    // Hvilket VideoWriter objekt er blevet valgt
    switch (FileIndex) {

        // VideoWriter Objekt nummer 1 - Recording Analysis Mode Fil
        case _VideoFileWriteObject_RecordingAnalysisModeFile:

            // Kontroller om "VideoWriter" objektet er åbent.
            if (RECAnalysisModeFileWriterRAW.isOpened() == true) {

                // Luk AVI video filen for skrivning
                RECAnalysisModeFileWriterRAW.release();

                // Retuner status
                return true;

            }
            else {

                // Retuner status
                return false;

            }

        break;

        // VideoWriter Objekt nummer 2 - Live View Stream Fil
        case _VideoFileWriteObject_LiveViewStreamFile:

            // Kontroller om "VideoWriter" objektet er åbent.
            if (LiveViewDataFileWriter.isOpened() == true) {

                // Luk AVI video filen for skrivning
                LiveViewDataFileWriter.release();

                // Retuner status
                return true;

            }
            else {

                // Retuner status
                return false;

            }

        break;

    }

}

// ----------------------------- Video Fil Læsnings, Konfigurations, Indstillings Og Skrivnings Routiner ----------------------------- //

bool RMH_VideoFileReading_IsRECAnalysisModeFileOpen() {

    // Routinen kontroller om AVI Filen, brugt i "Recording Analysis" Mode, er åben

    // Kontroller om AVI filen er åben
    if (RECAnalysisModeFileReader.isOpened() == true) {

        // Retuner status
        return true;

    }
    else {

        // Retuner Status
        return false;

    }

}

RAWVideoFileInfo RMH_VideoFileReading_SetupRecordingAnalysisModeVideoFileReader(System::String^ AVIFilePath) {

    // Routinen konfigurerer og opsætter et VideoReader objekt til læsning af en AVI video fil i "Recording Analysis" Mode
    // Routinen retunerer "true", hvis filen er blevet korrekt åbnet - ellers "false" ved fejl

    // Lokale Variabler
    System::String^ FileTypeExtension;
    RAWVideoFileInfo RECAnalysisModeFileInfo;

    // Hvis givet Fil Path er "None" - Ingen fil valgt
    if (AVIFilePath == "None") {

        // Nulstil fil information strukturens parametere
        RECAnalysisModeFileInfo.IsFileOpenFlag = false;
        RECAnalysisModeFileInfo.IsAVIFileFlag = false;
        RECAnalysisModeFileInfo.FrameWidth = 0;
        RECAnalysisModeFileInfo.FrameHeight = 0;
        RECAnalysisModeFileInfo.FrameRate = 0.0;
        RECAnalysisModeFileInfo.NumberOfFrames = 0;
        RECAnalysisModeFileInfo.DurationTime = 0.0;
        
    }
    else {

        // Kontroller om filen allerede er åben
        if (RMH_VideoFileReading_IsRECAnalysisModeFileOpen() == true) {

            // Luk for video filen
            RECAnalysisModeFileReader.release();

        }

        // Læs hvilken fil typer som er blevet valgt fra givet input fil path
        FileTypeExtension = AVIFilePath->Substring(AVIFilePath->LastIndexOf(".") + 1);

        // Kontroller om den givet path er til en ".avi" fil
        if (FileTypeExtension != "avi") {

            // Nulstil "Filen er en .avi fil" flaget
            RECAnalysisModeFileInfo.IsAVIFileFlag = false;

        }
        else {

            // Konverter givet input fil path til cv::string
            cv::String FilePath = RMH_VideoRecording_ConvertSystemStringToCVString(AVIFilePath);

            // Open valgte AVI fil 
            RECAnalysisModeFileReader.open(FilePath);

            // Kontroller om filen er blevet åbnet
            if (RMH_VideoFileReading_IsRECAnalysisModeFileOpen() == true) {

                // Opdater "Filen er en .avi fil" flaget
                RECAnalysisModeFileInfo.IsAVIFileFlag = true;

                // Opdater "Filen er åben" flaget
                RECAnalysisModeFileInfo.IsFileOpenFlag = true;

                // Læs filens pixel bredde og højde
                RECAnalysisModeFileInfo.FrameWidth = RECAnalysisModeFileReader.get(cv::CAP_PROP_FRAME_WIDTH);
                RECAnalysisModeFileInfo.FrameHeight = RECAnalysisModeFileReader.get(cv::CAP_PROP_FRAME_HEIGHT);

                // Læs filens Frame Rate
                RECAnalysisModeFileInfo.FrameRate = RECAnalysisModeFileReader.get(cv::CAP_PROP_FPS);

                // Læs antallet af data frames, som filen indeholder
                RECAnalysisModeFileInfo.NumberOfFrames = RECAnalysisModeFileReader.get(cv::CAP_PROP_FRAME_COUNT);

                // Udregn længden af filen i sekundter
                RECAnalysisModeFileInfo.DurationTime = (double)RECAnalysisModeFileInfo.NumberOfFrames / (double)RECAnalysisModeFileInfo.FrameRate;

            }
            else {

                // Nulstil filens parametere
                RECAnalysisModeFileInfo.IsFileOpenFlag = false;
                RECAnalysisModeFileInfo.IsAVIFileFlag = false;
                RECAnalysisModeFileInfo.FrameWidth = 0;
                RECAnalysisModeFileInfo.FrameHeight = 0;
                RECAnalysisModeFileInfo.FrameRate = 0.0;
                RECAnalysisModeFileInfo.NumberOfFrames = 0;
                RECAnalysisModeFileInfo.DurationTime = 0.0;

            }

        }

    }

    // Retuner filens information
    return RECAnalysisModeFileInfo;

}

unsigned int RMH_VideoFileReading_ReadVideoFileFrame(unsigned long TargetFrameNumber, unsigned long FileTotalNumOfFrames, unsigned char *ReadFrameData) {

    // Routinen læser en video frame fra åbnet "Recording Analysis" Mode RAW video fil
    
    /*
     *   Retunerer filgende status/error koder:
     * 
     *   // Læsning af video fil Error koder Reference Macroer
     *   #define _ReadAVIFile_StatusCode_FrameReadOK              1
     *   #define _ReadAVIFile_StatusCode_FileIsNotOpen            2
     *   #define _ReadAVIFile_StatusCode_FrameNumberOutOfRange    3
     *   #define _ReadAVIFile_StatusCode_FrameReadError           4
     * 
     */

    // Lokale variabler
    cv::Mat ReadFrame;
    cv::Mat ReadFrameRGB;

    // Kontroller om video filen er åben
    if (RMH_VideoFileReading_IsRECAnalysisModeFileOpen() == true) {

        // Er givet frame nummer inden for 0 - FileTotalNumOfFrames
        if (TargetFrameNumber >= 0 && TargetFrameNumber < FileTotalNumOfFrames) {

            // Indstil positionen af valgte frame nummer til læsning
            RECAnalysisModeFileReader.set(cv::CAP_PROP_POS_FRAMES, TargetFrameNumber);

            // Læs Frame nummerets data - kontroller om dataen blev korrekt læst
            if (RECAnalysisModeFileReader.read(ReadFrame)) {

                // Konverter læste frame fra BGR til RGB
                cv::cvtColor(ReadFrame, ReadFrameRGB, cv::COLOR_BGR2RGB);

                // Skriv frame data til pointer 
                memcpy(ReadFrameData, ReadFrameRGB.data, ReadFrameRGB.total() * ReadFrameRGB.elemSize());

            }
            else {

                // Retuner Status - Fejl ved læsning af frame
                return _ReadAVIFile_StatusCode_FrameReadError;

            }

        }
        else {

            // Retuner Status - Givet "FrameNumber" er uden for rækkevidden
            return _ReadAVIFile_StatusCode_FrameNumberOutOfRange;

        }

        // Retuner Status - Frame er blevet læst
        return _ReadAVIFile_StatusCode_FrameReadOK;

    }
    else {

        // Retuner Status - Fil ikke åben
        return _ReadAVIFile_StatusCode_FileIsNotOpen;

    }

}

bool RMH_VideoFileReading_CloseRecordingAnalysisModeFile() {

    // Routinen lukker for læsningen af AVI video filen
    // Retunerer "true" hvis "VideoCapture" objektet er blevet korrekt lukket

    // Kontroller om "VideoCapture" objektet er åbent.
    if (RMH_VideoFileReading_IsRECAnalysisModeFileOpen() == true) {

        // Luk AVI video filen for læsning
        RECAnalysisModeFileReader.release();

        // Retuner status
        return true;

    }
    else {

        // Retuner status
        return false;

    }

}

// --------------------------- SnapShot Fil Læsnings, Konfigurations, Indstillings Og Skrivnings Routiner ---------------------------- //

RAWSnapShotFileInfo RMH_AnalysisMode_ReadAndLoadPNGImage(System::String^ ImageFilePath, unsigned char* ImageData) {

    // Routinen åbner læser en PNG billede fil på valgte sti, hvoe billedets pixel data kan læses som: 
    // unsigned char RED = ImageData[3 * (Y * Width + X)];
    // unsigned char GREEN = ImageData[3 * (Y * Width + X) + 1];
    // unsigned char BLUE = ImageData[3 * (Y * Width + X) + 2];

    // Lokale varaibler
    unsigned int ImgWidth = 0;
    unsigned int ImgHeight = 0;
    unsigned int BufferSize = 0;
    System::String^ FileTypeExtension;
    RAWSnapShotFileInfo SnapShotAnalysisModeFileInfo;

    // Læs hvilken fil typer som er blevet valgt fra givet input fil path
    FileTypeExtension = ImageFilePath->Substring(ImageFilePath->LastIndexOf(".") + 1);

    // Kontroller om den givet path er til en ".png" fil
    if (FileTypeExtension != "png") {

        // Nulstil "Filen er en .png fil" flaget
        SnapShotAnalysisModeFileInfo.IsPNGFileFlag = false;
        // Nulstil "Fil er ikke Klar" flaget
        SnapShotAnalysisModeFileInfo.IsFileReady = false;
        // Nulstil Fil Fejl Flaget
        SnapShotAnalysisModeFileInfo.FileErrorFlag = true;

        // Retuner Info Struktur
        return SnapShotAnalysisModeFileInfo;

    }
    else if (FileTypeExtension == "png") {

        // Opdater "Filen er en .png fil" flaget
        SnapShotAnalysisModeFileInfo.IsPNGFileFlag = true;

    }

    // Konverter System::String til et standart C++ string
    std::wstring wfilename = msclr::interop::marshal_as<std::wstring>(ImageFilePath);

    // Initiliser COM Bibliotek
    CoInitialize(nullptr);

    // Generer og konfigurer "WIC factory"
    IWICImagingFactory* pFactory = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory));

    // Kontroler handler fejl
    if (FAILED(hr)) {

        // Un-initiliser COM Bibliotek
        CoUninitialize();

        // Nulstil "Fil er ikke Klar" flaget
        SnapShotAnalysisModeFileInfo.IsFileReady = false;
        // Nulstil Fil Fejl Flaget
        SnapShotAnalysisModeFileInfo.FileErrorFlag = true;

        // Retuner Info Struktur
        return SnapShotAnalysisModeFileInfo;

    }

    // Generer og konfigurer Dekoder for PNG billede
    IWICBitmapDecoder* pDecoder = nullptr;
    hr = pFactory->CreateDecoderFromFilename(wfilename.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

    // Kontroler handler fejl
    if (FAILED(hr)) {

        // Frigiv "WIC factory"
        pFactory->Release();
        // Un-initiliser COM Bibliotek
        CoUninitialize();

        // Nulstil "Fil er ikke Klar" flaget
        SnapShotAnalysisModeFileInfo.IsFileReady = false;
        // Nulstil Fil Fejl Flaget
        SnapShotAnalysisModeFileInfo.FileErrorFlag = true;

        // Retuner Info Struktur
        return SnapShotAnalysisModeFileInfo;

    }

    // Læs den første billede frame fra fil dekoderen (PNG billeder har kun en frame)
    IWICBitmapFrameDecode* pFrame = nullptr;
    hr = pDecoder->GetFrame(0, &pFrame);

    // Kontroler handler fejl
    if (FAILED(hr)) {

        // Frigiv billede dekoder
        pDecoder->Release();
        // Frigiv "WIC factory"
        pFactory->Release();
        // Un-initiliser COM Bibliotek
        CoUninitialize();

        // Nulstil "Fil er ikke Klar" flaget
        SnapShotAnalysisModeFileInfo.IsFileReady = false;
        // Nulstil Fil Fejl Flaget
        SnapShotAnalysisModeFileInfo.FileErrorFlag = true;

        // Retuner Info Struktur
        return SnapShotAnalysisModeFileInfo;

    }

    // Læs PGN billedets Størrelse
    hr = pFrame->GetSize(&ImgWidth, &ImgHeight);

    // Kontroler handler fejl
    if (FAILED(hr)) {

        // Frigiv billede størrelses struktur
        pFrame->Release();
        // Frigiv billede dekoder
        pDecoder->Release();
        // Frigiv "WIC factory"
        pFactory->Release();
        // Un-initiliser COM Bibliotek
        CoUninitialize();

        // Nulstil "Fil er ikke Klar" flaget
        SnapShotAnalysisModeFileInfo.IsFileReady = false;
        // Nulstil Fil Fejl Flaget
        SnapShotAnalysisModeFileInfo.FileErrorFlag = true;

        // Retuner Info Struktur
        return SnapShotAnalysisModeFileInfo;

    }

    // Læs og retuner, til pointer, læste PGN billedes højde og brede
    SnapShotAnalysisModeFileInfo.FrameWidth = static_cast<unsigned int>(ImgWidth);
    SnapShotAnalysisModeFileInfo.FrameHeight = static_cast<unsigned int>(ImgHeight);

    // Udregn buffer stærrelsen for PNG billedets pixel data (3 Bånd RGB)
    BufferSize = ImgWidth * ImgHeight * 3;

    // Alloker hukommelse til billedets pixel data
    unsigned char* Buffer = new unsigned char[BufferSize];

    // Læs PNG Billedets Pixel data RGB
    WICRect Rect = { 0, 0, static_cast<unsigned int>(ImgWidth), static_cast<unsigned int>(ImgHeight) };
    hr = pFrame->CopyPixels(&Rect, ImgWidth * 3, BufferSize, Buffer);

    // Kontroler handler fejl
    if (FAILED(hr)) {

        // Slet Allokerede hukommelse til pixel buffer 
        delete[] Buffer;
        // Frigiv billede størrelses struktur
        pFrame->Release();
        // Frigiv billede dekoder
        pDecoder->Release();
        // Frigiv "WIC factory"
        pFactory->Release();
        // Un-initiliser COM Bibliotek
        CoUninitialize();

        // Nulstil "Fil er ikke Klar" flaget
        SnapShotAnalysisModeFileInfo.IsFileReady = false;
        // Nulstil Fil Fejl Flaget
        SnapShotAnalysisModeFileInfo.FileErrorFlag = true;

        // Retuner Info Struktur
        return SnapShotAnalysisModeFileInfo;

    }

    // Konverter Læste billede BGR data til RGB
    for (unsigned int Y = 0; Y < ImgHeight; Y++) {

        // Loop i gennem alle array matricens rækker
        for (unsigned int X = 0; X < ImgWidth; X++) {

            // Udregn start indexet for nuværende pixel inde
            unsigned int pixelIndex = 3 * (Y * ImgWidth + X);

            // Byt om på R og B komponenterne
            unsigned char temp = Buffer[pixelIndex];
            Buffer[pixelIndex] = Buffer[pixelIndex + 2]; // R -> B
            Buffer[pixelIndex + 2] = temp; // B -> R
        }
    }

    // Frigiv billede handler resourcer
    pFrame->Release();
    pDecoder->Release();
    pFactory->Release();
    // Un-initiliser COM Bibliotek
    CoUninitialize();

    // Kopir pixel data til "ImageData" array
    memcpy(ImageData, Buffer, BufferSize);

    // Slet Allokerede hukommelse til pixel buffer 
    delete[] Buffer;

    // Opdater "Filen Er Klar" Flaget
    SnapShotAnalysisModeFileInfo.IsFileReady = true;
    // Opdater Fil Fejl Flaget
    SnapShotAnalysisModeFileInfo.FileErrorFlag = false;

    // Retuner Info Struktur
    return SnapShotAnalysisModeFileInfo;

}

// ----------------------------------------------------------------------------------------------------------------------------------- //