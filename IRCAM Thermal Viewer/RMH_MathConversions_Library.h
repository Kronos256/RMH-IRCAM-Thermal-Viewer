
/*
 *  RMH_MathConversions_Library.h
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

#pragma once

// RMH_MathConversions_Library.h
#ifndef RMH_MathConversions_Library_H 
#define RMH_MathConversions_Library_H

// Inkluderede Blbiloteker
#include <string>
#include <opencv2/opencv.hpp>
#include <msclr\marshal_cppstd.h>

// Tilhørende Namespaces
using namespace std;

// --------------------------------- Konverterings Routiner --------------------------------- //

void RMH_Conversion_IntToUnsignedCharArray(unsigned int InputInteger, unsigned short TargetStringLength, unsigned char* OutputCharArray);
System::String^ RMH_Conversion_StdStringToSystemString(std::string InputString);
std::string RMH_Conversion_SystemStringToStdString(System::String^ InputString);
System::String^ RMH_Conversion_IntToSystemString(unsigned int InputValue);
std::string RMH_Conversion_IntToStdString(unsigned int InputValue);
unsigned int RMH_Conversion_StdStringToInt(std::string InputString);
unsigned int RMH_Conversion_SystemStringToInt(System::String^ InputString);
std::string RMH_Conversion_FloatToStdString(float Inputvalue, unsigned char Precision);
float RMH_Conversion_StdStringToFloat(std::string inputString);
double RMH_Conversion_StdStringToDouble(std::string inputString);
bool RMH_Conversion_ReplaceCharOrStringInString(std::string& InputString, std::string& From, std::string& To);
float RMH_Conversion_uint32ToSinglePrecisionFloat(unsigned int InputValue);
void RMH_Conversion_SinglePrecisionFloatTo4xUnsignedChar(float Value, unsigned char* OutputValues);
float RMH_Conversion_UnsignedCharToSinglePrecisionFloat(unsigned char* InputValues);
float RMH_Conversion_UnsignedCharToSinglePrecisionFloat2(unsigned char Input1, unsigned char Input2, unsigned char Input3, unsigned char Input4);
float RMH_Conversion_uint16x2ToSinglePrecisionFloat(unsigned short HighValue, unsigned short LowValue);
float RMH_Conversion_SystemDecimalToFloat(System::Decimal Decimal);
double RMH_Conversion_SystemDecimalToDouble(System::Decimal Decimal);
System::Decimal RMH_Conversion_FloatToSystemDecimal(float InputValue);
System::Decimal RMH_Conversion_DoubleToSystemDecimal(double InputValue);
bool RMH_Conversion_StdStringToBoolean(std::string InputString);
System::String^ RMH_Conversion_FloatToSystemString(float Value);
const char* RMH_Conversion_SystemStringToCharPtr(System::String^ str);
System::String^ RMH_Conversion_UnsignedCharArrayToSystemString(unsigned char* InputArray, unsigned int ArrayLength);
cv::String RMH_VideoRecording_ConvertSystemStringToCVString(System::String^ sysString);

// -------------------- Matematiske Udregnings & Konverterings Routiner --------------------- //

unsigned int RMH_Math_Round(double InputValue);
double RMH_Math_absDouble(double InputValue);

// ------------------------------------------------------------------------------------------ //

#endif /* RMH_MathConversions_Library_H */