/*
 *  RMH_MathConversions_Library.c
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

 // Inkluderede Blblioteker
#include <sstream>
#include <math.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <msclr\marshal_cppstd.h>
#include <string>
#include "RMH_MathConversions_Library.h"

// Tilhørende namespaces for bibliotek
using namespace System;
using namespace std;

// --------------------------------- Konverterings Routiner --------------------------------- //

void RMH_Conversion_IntToUnsignedCharArray(unsigned int InputInteger, unsigned short TargetStringLength, unsigned char *OutputCharArray) {

	// Routinen konverterer et input integer til Unsigned Char (C Implementering)

	// Lokale variabler
	unsigned long CharacterDigitMultiplier = 0;

	// Loop til og med den maksimale string længde
	for (unsigned int i = 0; i < TargetStringLength; i++) {

		// Udregn digit skallerings faktoren
		CharacterDigitMultiplier = pow(10, i);

		// Konverter integer til unsigned char og skriv til pointer array
		*(OutputCharArray + i) = (InputInteger / CharacterDigitMultiplier) % 10 + 48;

	}

}

System::String^ RMH_Conversion_StdStringToSystemString(std::string InputString) {

	// Routinen konverterer et std::string til et System::String

	// Lokale objekter
	System::String^ SystemString;

	// Konverter std::string til System::String
	SystemString = gcnew System::String(InputString.c_str());

	// Retuner konverterede System::String
	return SystemString;

}

std::string RMH_Conversion_SystemStringToStdString(System::String^ InputString) {

	// Routinen konverterer et System::String til et std::string 

	// Lokale objekter
	std::string StdString;

	// Konverter System::String til std::string
	StdString = msclr::interop::marshal_as<std::string>(InputString);

	// Retuner konverterede std::string
	return StdString;

}

System::String^ RMH_Conversion_IntToSystemString(unsigned int InputValue) {

	// Routinen Konverterer et input integer til et System::String

	// Retuner konverterede System::String
	return System::Convert::ToString(InputValue);

}

std::string RMH_Conversion_IntToStdString(unsigned int InputValue) {

	// Routinen Konverterer et input integer til et Std::String

	// Retuner konverterede Std::String
	return std::to_string(InputValue);

}

unsigned int RMH_Conversion_StdStringToInt(std::string InputString) {

	// Routinen konverterer et std::string til en integer

	// Retuner konverterede string som int
	return std::stoi(InputString);

}

unsigned int RMH_Conversion_SystemStringToInt(System::String^ InputString) {

	// Routinen konverterer et System::String til en integer

	// Retuner konverterede string som int
	return std::stoi(RMH_Conversion_SystemStringToStdString(InputString));

}

std::string RMH_Conversion_FloatToStdString(float Inputvalue, unsigned char Precision) {

	// Routinen konverterer et input float til et std::string og retunerer std::stringet

	// Lokale variabler objekter
	std::ostringstream out;
	// Sæt string decimal præcision
	out.precision(Precision);
	// Skriv string til stringstream
	out << std::fixed << Inputvalue;

	// Retuner konverterede Float -> std::string
	return out.str();

}

float RMH_Conversion_StdStringToFloat(std::string inputString) {

	// Routinen konverterer et std::string til float

	// Retuner konverterede std::string -> float
	return std::stof(inputString);

}

double RMH_Conversion_StdStringToDouble(std::string inputString) {

	// Routinen konverterer et std::string til double

	// Retuner konverterede std::string -> double
	return std::stod(inputString);

}

bool RMH_Conversion_ReplaceCharOrStringInString(std::string& InputString, std::string& From, std::string& To) {

	// Routinen Erstater en givet karakter eller string ""

	// Find Start Opsitionen Af "From" string
	size_t start_pos = InputString.find(From);

	// Hvis string Start positionen har OverFlow
	if (start_pos == std::string::npos) return false;

	// Erstat String "From" i "InputString" med "To" String 
	InputString.replace(start_pos, From.length(), To);

	// Retuner Status
	return true;
}

float RMH_Conversion_uint32ToSinglePrecisionFloat(unsigned int InputValue) {

	// Rotinen konverterer et 32Bit unsigned integer til et Single-Precision
	// Det konverterede Single-Precision nummer bliver retunerede som et float

	// Retuner 32Bit integer som Type konverterede Single-Precision float
	return *reinterpret_cast<float*>(&InputValue);

}

void RMH_Conversion_SinglePrecisionFloatTo4xUnsignedChar(float Value, unsigned char* OutputValues) {

	// Routinen konverterer en givet float værdi til 4 x unsigned char værdier

	// Typecast ponter som unsigned int
	unsigned int* IntValue = reinterpret_cast<unsigned int*>(&Value);

	// Skriv Typecastet værdier til pointer array
	OutputValues[0] = (*IntValue >> 24) & 0xFF;
	OutputValues[1] = (*IntValue >> 16) & 0xFF;
	OutputValues[2] = (*IntValue >> 8) & 0xFF;
	OutputValues[3] = *IntValue & 0xFF;
	
}

float RMH_Conversion_UnsignedCharToSinglePrecisionFloat(unsigned char* InputValues) {

	// Routinen konverterer 4 x unsigned char værdier til et Singl ePrecision Float

	// Nulstil baseline integer værdi
	unsigned int IntValue = 0;

	// Formater samlede 32Bit integer
	IntValue |= (static_cast<unsigned int>(InputValues[0]) << 24);
	IntValue |= (static_cast<unsigned int>(InputValues[1]) << 16);
	IntValue |= (static_cast<unsigned int>(InputValues[2]) << 8);
	IntValue |= static_cast<unsigned int>(InputValues[3]);

	// Typecast integer værdien til float
	float floatValue = *reinterpret_cast<float*>(&IntValue);

	// Retuner float værdi
	return floatValue;
}

float RMH_Conversion_UnsignedCharToSinglePrecisionFloat2(unsigned char Input1, unsigned char Input2, unsigned char Input3, unsigned char Input4) {

	// Routinen konverterer 4 x unsigned char værdier til et Singl ePrecision Float

	// Nulstil baseline integer værdi
	unsigned int IntValue = 0;

	// Formater samlede 32Bit integer
	IntValue |= (static_cast<unsigned int>(Input1) << 24);
	IntValue |= (static_cast<unsigned int>(Input2) << 16);
	IntValue |= (static_cast<unsigned int>(Input3) << 8);
	IntValue |= static_cast<unsigned int>(Input4);

	// Typecast integer værdien til float
	float floatValue = *reinterpret_cast<float*>(&IntValue);

	// Retuner float værdi
	return floatValue;
}

float RMH_Conversion_uint16x2ToSinglePrecisionFloat(unsigned short HighValue, unsigned short LowValue) {

	// Rotinen konverterer to 16Bit unsigned integer til et Single-Precision
	// Det konverterede Single-Precision nummer bliver retunerede som et float

	// Kombiner de to 16bit integer til 32Bit
	unsigned int Combined32Bit = ((unsigned int)HighValue << 16) | LowValue;

	// Retuner 2x16Bit integer som Type konverterede Single-Precision float
	return *reinterpret_cast<float*>(&Combined32Bit);

}

float RMH_Conversion_SystemDecimalToFloat(System::Decimal Decimal) {

	// Routinen Konverterer et System::Decimal Til float

	// Retuner det konverterede System::Decimal -> Float
	return (float)System::Decimal::ToDouble(Decimal);

}

double RMH_Conversion_SystemDecimalToDouble(System::Decimal Decimal) {

	// Routinen Konverterer et System::Decimal Til double

	// Retuner det konverterede System::Decimal -> doulbe
	return (float)System::Decimal::ToDouble(Decimal);

}

System::Decimal RMH_Conversion_FloatToSystemDecimal(float InputValue) {

	// Routinen konverterer et givet float til System::Decimal

	// Retuner konverterede Float -> System:Decimal
	return System::Convert::ToDecimal(InputValue);

}

System::Decimal RMH_Conversion_DoubleToSystemDecimal(double InputValue) {

	// Routinen konverterer et givet double til System::Decimal

	// Retuner konverterede double -> System:Decimal
	return System::Convert::ToDecimal(InputValue);

}

bool RMH_Conversion_StdStringToBoolean(std::string InputString) {

	// Routinen konverterer et Std::String til Boolean

	// Kontroller string
	if (InputString == "True") {
		// Retuner Boolean true
		return true;
	}
	else {
		// Retuner Boolean false
		return false;
	}

}

System::String^ RMH_Conversion_FloatToSystemString(float Value) {

	// Routinen konverterer et givet float til et System::String

	// Retuner System::String
	return Value.ToString();

}

const char* RMH_Conversion_SystemStringToCharPtr(System::String^ str) {

	// Routinen konverterer et System::String til en const char pointer

	// Konverter string til Std::String
	std::string stdStr = msclr::interop::marshal_as<std::string>(str);
	// Konverter Std::String til const char pointer
	const char* charPtr = stdStr.c_str();

	// Retuner const char pointer
	return charPtr;

}

System::String^ RMH_Conversion_UnsignedCharArrayToSystemString(unsigned char* InputArray, unsigned int ArrayLength) {

	// Routinen konverterer et unsigned char *array til System::String

	// Konverter unsigned char array til std::string
	std::string stdString(reinterpret_cast<char*>(InputArray), ArrayLength);

	// Konverter Std::String til System::String
	System::String^ ConvertedSystemString = msclr::interop::marshal_as<System::String^>(stdString);

	// Retuner konverterede System::String
	return ConvertedSystemString;

}

cv::String RMH_VideoRecording_ConvertSystemStringToCVString(System::String^ sysString) {

	// Routinen konverterer et System::String til et cv::string
	// og retunerer det konverterede cv::String

	// Konverter System::String til et std::string
	std::string StdString = msclr::interop::marshal_as<std::string>(sysString);

	// Konverter std::string til et cv::String
	cv::String CvString(StdString.c_str());

	// Retuner konverterede cv::String
	return CvString;

}

// -------------------- Matematiske Udregnings & Konverterings Routiner --------------------- //

unsigned int RMH_Math_Round(double InputValue) {

	// Routinen retunerer nærmeste input værdi interger 

	// Kontroller Input Værdien
	if (InputValue < 0.0) {
		// Rund ned til nærmeste interger
		return (unsigned int)(InputValue - 0.5);
	}
	else {
		// Rund op til nærmeste interger
		return (unsigned int)(InputValue + 0.5);
	}

}

double RMH_Math_absDouble(double InputValue) {

	// Routinen udregner og retunerer absolut værdien at et givet input

	// Hvis givet input værdi er lavere end 0
	if (InputValue < 0.0) return -InputValue;
	else return InputValue;

}

// ------------------------------------------------------------------------------------------ //