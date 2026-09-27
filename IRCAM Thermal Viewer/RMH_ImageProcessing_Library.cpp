
/*
 *  RMH_ImageProcessing_Library.c
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

// Inkluderede Blblioteker
#include "GlobalObjectsAndVariables.h"
#include "RMH_ImageProcessing_Library.h"
#include "RMH_MathConversions_Library.h"
#include "RMH_ThermalCameraSupport_Library.h"
#include "RMH_SupportedIRCameras_Resources.h"

// Tilhørende namespaces for bibliotek
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace std;

// ------------------------------ Billede Udregnings Routiner ------------------------------- //

double RMH_ImageCalculations_CalMeanOfImage16Bit(unsigned short* ImageData, unsigned int FrameWidth, unsigned int FrameHeight) {

	// Routinen udregner middel værdien for et givet billede data array.
	// Givet input billede array data skal være 16Bit eller lavere.

	// Lokale variabler
	double PixelValMean = 0.0;
	unsigned long long int PixelValSum = 0;

	// Udregn pixel summen for alle Y positioner
	for (unsigned int Y = 0; Y < FrameHeight; Y++) {

		// Udregn pixel summen for alle X positioner
		for (unsigned int X = 0; X < FrameWidth; X++) {

			// Udregn samlede pixel data Sum
			PixelValSum += ImageData[Y * FrameWidth + X]; 

		}
	}

	// Udregn Pixel datens middel værdi fra pixel sum
	PixelValMean = (double)PixelValSum / ((double)FrameWidth * (double)FrameHeight);

	// Retuner udregnede Pixel data Middel værdi
	return PixelValMean;

}

// ---------------------- Billede Non-Uniformity Korrektions Routiner ----------------------- //

void RMH_ImageNonUniformityCorrection_ConvertBaselineImageTo16Bit(unsigned char* BaselineImageData, unsigned short* OutputBaseline16Bit, unsigned int FrameWidth, unsigned int FrameHeight) {

	// Routinen konverterer et givet Baseline billede data array til et 16Bit Baseline array

	// Lokale variabler
	register unsigned short Pixel16BitValue[3];

	// Loop igennem alle baseline bånd pixels
	for (unsigned int i = 0, j = 0; i < (FrameWidth * FrameHeight); i += 3, j += 6) {

		// Læs og konverter Baseline billede bånds data til 16Bit Pixel data 
		Pixel16BitValue[0] = ((unsigned short)(*(BaselineImageData + (j + 1))) << 8) | ((unsigned short)*(BaselineImageData + (j + 0)));
		Pixel16BitValue[1] = ((unsigned short)(*(BaselineImageData + (j + 3))) << 8) | ((unsigned short)*(BaselineImageData + (j + 2)));
		Pixel16BitValue[2] = ((unsigned short)(*(BaselineImageData + (j + 5))) << 8) | ((unsigned short)*(BaselineImageData + (j + 4)));

		// Skriv konverterede pixel værdier til pointer array
		*(OutputBaseline16Bit + (i + 0)) = Pixel16BitValue[0];
		*(OutputBaseline16Bit + (i + 1)) = Pixel16BitValue[1];
		*(OutputBaseline16Bit + (i + 2)) = Pixel16BitValue[2];

	}

}

double RMH_ImageNonUniformityCorrection_CalNonUniformityMap(unsigned short* BaselineImageData, unsigned int FrameWidth, unsigned int FrameHeight, unsigned int FrameMetaDataSize, double* OutputNonUniformityMap) {

	// Routinen udregner Non-Uniformity Mapen af et givet CMOS baseline billede data array.
	// Routinen retunerer CMOS baseline billedet Middel værdi, samt Non-Uniformity mappingen som et double array.

	// Lokale variabler
	double BaselineImageMeanValue = 0.0;

	// Udregn Middel værdien af CMOS Baseline målingen - Uden meta data
	BaselineImageMeanValue = RMH_ImageCalculations_CalMeanOfImage16Bit(BaselineImageData, FrameWidth, FrameHeight - FrameMetaDataSize);

	// Træk Middel værdien af CMOS Baseline målingen fra selve Baseline pixel værdierne - Udregn Non-Uniformity mappingen
	for (unsigned int i = 0; i < (FrameWidth * (FrameHeight - FrameMetaDataSize)); i += 3) {

		// Udregn Non-Uniformity mappingen for Baseline billede dataen
		OutputNonUniformityMap[i + 0] = (double)(*(BaselineImageData + (i + 0))) - BaselineImageMeanValue;
		OutputNonUniformityMap[i + 1] = (double)(*(BaselineImageData + (i + 1))) - BaselineImageMeanValue;
		OutputNonUniformityMap[i + 2] = (double)(*(BaselineImageData + (i + 2))) - BaselineImageMeanValue;

	}

	// Retuner Middel værdien af CMOS Baseline målingen
	return BaselineImageMeanValue;

}

void RMH_ImageNonUniformityCorrection_ZeroNonUniformityMapArrayData(double* OutputNonUniformityMap, unsigned int FrameWidth, unsigned int FrameHeight) {

	// Routinen nulstiller alle Non-Uniformity Map Arrayets data positioner til '0'

	// Loop igennem all Non-Uniformity Map Arrayets data positioner
	for (unsigned int i = 0; i < FrameWidth * FrameHeight; i += 8) {

		// Nulstil array index data til '0'
		*(OutputNonUniformityMap + (i + 0)) = 0.0;
		*(OutputNonUniformityMap + (i + 1)) = 0.0;
		*(OutputNonUniformityMap + (i + 2)) = 0.0;
		*(OutputNonUniformityMap + (i + 3)) = 0.0;
		*(OutputNonUniformityMap + (i + 4)) = 0.0;
		*(OutputNonUniformityMap + (i + 5)) = 0.0;
		*(OutputNonUniformityMap + (i + 6)) = 0.0;
		*(OutputNonUniformityMap + (i + 7)) = 0.0;

	}

}

// ----------------------------- Billede Konverterings Routiner ----------------------------- //

void RMH_ImageConversion_ArrangeYUY2ToRGB24(unsigned char* YUY2in, unsigned char* RGBout, unsigned int FrameWidth, unsigned int FrameHeight) {

	// Routinen Omarrangere et input billede frame array på formatet YUY2
	// Til et billede frame array på formatet RGB24.

	// Omarrangere YUY2 Pixels til RGB24 Format
	for (int i = 0, j = 0; i < (FrameWidth * FrameHeight * 3); i += 6, j += 4) {

		// Skriv Omarrangerede Data til pointer
		*(RGBout + (i + 0)) = *(YUY2in + (j + 1)); // Rød  - U0
		*(RGBout + (i + 1)) = *(YUY2in + (j + 1)); // Grøn - U0
		*(RGBout + (i + 2)) = *(YUY2in + (j + 0)); // Blå  - Y0
		*(RGBout + (i + 3)) = *(YUY2in + (j + 3)); // Rød  - U1
		*(RGBout + (i + 4)) = *(YUY2in + (j + 3)); // Grøn - U2
		*(RGBout + (i + 5)) = *(YUY2in + (j + 2)); // Rød  - Y1

	}

}

void RMH_ImageConversion_ConvertYUY2ToGrayscaleRGB24(unsigned char* YUY2in, unsigned char* GrayscaleOut, unsigned int FrameWidth, unsigned int FrameHeight) {

	// Routinen konverterer 24Bit YUY2 til 24Bit Grayscale
	// Og retunerer konverterede grayscale array til argument pointer

	// Lokale variabler
	unsigned char PixelValue = 0;

	// Loop igennem alle YUY2 bånd pixels
	for (int i = 0, j = 0; i < (FrameWidth * FrameHeight * 3); i += 3, j += 2) {

		// Udregn fælles RGB24 Grayscale Pixel værdi
		PixelValue = (unsigned char)RMH_Math_Round((0.2989 * (double)(*(YUY2in + (j + 0))))) +
				  	 (unsigned char)RMH_Math_Round((0.5870 * (double)(*(YUY2in + (j + 1))))) +
					 (unsigned char)RMH_Math_Round((0.1140 * (double)(*(YUY2in + (j + 1)))));

		// Skriv Grayscale pixel værdi til pointer array
		*(GrayscaleOut + (i + 0)) = PixelValue;
		*(GrayscaleOut + (i + 1)) = PixelValue;
		*(GrayscaleOut + (i + 2)) = PixelValue;

	}

}

void RMH_ImageConversion_ConvertYUY2ToGrayscaleRGB8(unsigned char* YUY2in, unsigned char* GrayscaleOut, unsigned int FrameWidth, unsigned int FrameHeight) {

	// Routinen konverterer 24Bit YUY2 til 8Bit Grayscale
	// Og retunerer konverterede grayscale array til argument pointer

	// Lokale variabler
	unsigned char PixelValue = 0;

	// Loop igennem alle YUY2 bånd pixels
	for (int i = 0, j = 0; i < (FrameWidth * FrameHeight); i += 1, j += 2) {

		// Udregn fælles RGB24 Grayscale Pixel værdi
		PixelValue = (unsigned char)RMH_Math_Round((0.2989 * (double)(*(YUY2in + (j + 0))))) +
				 	 (unsigned char)RMH_Math_Round((0.5870 * (double)(*(YUY2in + (j + 1))))) +
					 (unsigned char)RMH_Math_Round((0.1140 * (double)(*(YUY2in + (j + 1)))));

		// Skriv Grayscale pixel værdi til pointer array
		*(GrayscaleOut + (i + 0)) = PixelValue;

	}

}

void RMH_ImageConversion_ConvertRGB24ToGrayscaleRGB24(unsigned char *RGBin, unsigned char *GrayscaleOut, unsigned int FrameWidth, unsigned int FrameHeight) {

	// Routinen konverterer 24Bit RGB til 24Bit Grayscale
	// Og retunerer konverterede grayscale array til argument pointer

	// Lokale variabler
	unsigned char PixelValue = 0;

	// Loop igennem alle RGB bånd pixels
	for (int i = 0, j = 0; i < (FrameWidth * FrameHeight * 3); i += 3, j += 3) {

		// Udregn fælles RGB24 Grayscale Pixel værdi
		PixelValue = (unsigned char)RMH_Math_Round((0.2989 * (double)(*(RGBin + (j + 2))))) +
					 (unsigned char)RMH_Math_Round((0.5870 * (double)(*(RGBin + (j + 1))))) +
					 (unsigned char)RMH_Math_Round((0.1140 * (double)(*(RGBin + (j + 0)))));

		// Skriv Grayscale pixel værdi til pointer array
		*(GrayscaleOut + (i + 0)) = PixelValue;
		*(GrayscaleOut + (i + 1)) = PixelValue;
		*(GrayscaleOut + (i + 2)) = PixelValue;

	}

}

// -------------- Color Palette Billede Processerings & Konverterings Routiner -------------- //

void RMH_ImageProcessing_ApplyColorPaletteToGrayscaleImageData(unsigned short* Data, unsigned int FrameWidth, unsigned int FrameHeight, unsigned short ColorPalette[3][16384], bool InvertColorPalette, unsigned short* MappedData) {

	// Routinen tilføjer en given Color Palette til input billede dataen.
	// Dette gøres ved at benytte Color Palette arrayet som look-up tabel for billede dataen
	// Routinen retunerer Color mapped RGB24 billede data

	// Loop igennem grayscale billede data
	for (unsigned int i = 0, j = 0; i < (FrameWidth * FrameHeight * 3); i += 9, j += 3) {

		// Skal color paletten inverteres
		if (InvertColorPalette == true) {

			// Formater billede data til color palette format - inverterede color palette - 3 Del-Bånd af gangen (Hurtigst -> "Loop Unrolling")
			*(MappedData + (i + 0)) = ColorPalette[0][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + j)];
			*(MappedData + (i + 1)) = ColorPalette[1][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + j)];
			*(MappedData + (i + 2)) = ColorPalette[2][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + j)];
			*(MappedData + (i + 3)) = ColorPalette[0][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + (j + 1))];
			*(MappedData + (i + 4)) = ColorPalette[1][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + (j + 1))];
			*(MappedData + (i + 5)) = ColorPalette[2][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + (j + 1))];
			*(MappedData + (i + 6)) = ColorPalette[0][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + (j + 2))];
			*(MappedData + (i + 7)) = ColorPalette[1][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + (j + 2))];
			*(MappedData + (i + 8)) = ColorPalette[2][_ImageProcessing_ImageResolution_14Bit - (unsigned short)*(Data + (j + 2))];

		}
		else {

			// Formater billede data til color palette format - Normal color palette - 3 Del-Bånd af gangen (Hurtigst -> "Loop Unrolling")
			*(MappedData + (i + 0)) = ColorPalette[0][(unsigned short)*(Data + j)];
			*(MappedData + (i + 1)) = ColorPalette[1][(unsigned short)*(Data + j)];
			*(MappedData + (i + 2)) = ColorPalette[2][(unsigned short)*(Data + j)];
			*(MappedData + (i + 3)) = ColorPalette[0][(unsigned short)*(Data + (j + 1))];
			*(MappedData + (i + 4)) = ColorPalette[1][(unsigned short)*(Data + (j + 1))];
			*(MappedData + (i + 5)) = ColorPalette[2][(unsigned short)*(Data + (j + 1))];
			*(MappedData + (i + 6)) = ColorPalette[0][(unsigned short)*(Data + (j + 2))];
			*(MappedData + (i + 7)) = ColorPalette[1][(unsigned short)*(Data + (j + 2))];
			*(MappedData + (i + 8)) = ColorPalette[2][(unsigned short)*(Data + (j + 2))];

		}

	}

}

void RMH_ImageProcessing_ApplyOverlayedPaletteToGrayScaleImageData(unsigned short* Data, unsigned short* MappedData, unsigned int FrameWidth, unsigned int FrameHeight, unsigned short BackGroundColorPalette[3][16384], unsigned short OverlayedColorPalette[3][16384], bool InvertBackGroundColorPalette, bool InvertOverlayedColorPalette, unsigned int X0Pos, unsigned int Y0Pos, unsigned int OCPWidth, unsigned int OCPHeight) {

	// Routinen tilføjer en given Baggrunds Color Palette til det givet input billede data.
	// Samt tilfæjer en ekstra overlejret Color Palette Oven På denne.
	// Dette giver Mulighed for at vise billede dataen med flere forskellige Color Palettes på samme tid.

	// Lokale variabler
	unsigned int DataFrameRowCount = 0;
	unsigned int OverlayedPaletteStartIndex = 0;
	unsigned int OverlayedPaletteStopIndex = 0;

	// Udregn Start og Stop index værdierne for den overlejret Palette
	OverlayedPaletteStartIndex = (Y0Pos * FrameWidth) + X0Pos;
	OverlayedPaletteStopIndex = (OverlayedPaletteStartIndex + OCPWidth) - 1;

	// Loop igennem grayscale billede data
	for (unsigned int i = 0, j = 0; i < (FrameWidth * FrameHeight * 3); i += 3, j += 1) {

		// Kontroller om nuværende index er indenfor "Overlayed" Color Palette Index Række Området
		if ((j >= OverlayedPaletteStartIndex && j <= OverlayedPaletteStopIndex) && DataFrameRowCount < OCPHeight) {

			// Skal den overlejede color palette inverteres
			if (InvertOverlayedColorPalette == true) {

				// Formater billede data med Overlayed color palette data - inverterede
				*(MappedData + (i + 0)) = OverlayedColorPalette[0][_ImageProcessing_ImageResolution_14Bit - *(Data + (j + 0))];
				*(MappedData + (i + 1)) = OverlayedColorPalette[1][_ImageProcessing_ImageResolution_14Bit - *(Data + (j + 0))];
				*(MappedData + (i + 2)) = OverlayedColorPalette[2][_ImageProcessing_ImageResolution_14Bit - *(Data + (j + 0))];

			}
			else {

				// Formater billede data med Overlayed color palette data 
				*(MappedData + (i + 0)) = OverlayedColorPalette[0][*(Data + (j + 0))];
				*(MappedData + (i + 1)) = OverlayedColorPalette[1][*(Data + (j + 0))];
				*(MappedData + (i + 2)) = OverlayedColorPalette[2][*(Data + (j + 0))];

			}

			// Er Stop index værdien for den overlejret Palette nåede - Per Row
			if (j >= OverlayedPaletteStopIndex) {

				// Inkrementer Frame Data Row Tæller variabel
				DataFrameRowCount = DataFrameRowCount + 1;

				// Inkrementer til næste overlejret Palette data række
				OverlayedPaletteStartIndex = OverlayedPaletteStartIndex + FrameWidth;
				OverlayedPaletteStopIndex = OverlayedPaletteStopIndex + FrameWidth;

			}

		}
		else {

			// Skal baggrunds paletten inverteres
			if (InvertBackGroundColorPalette == true) {

				// Formater billede data med Baggrund color palette data - inverterede
				*(MappedData + (i + 0)) = BackGroundColorPalette[0][_ImageProcessing_ImageResolution_14Bit - *(Data + (j + 0))];
				*(MappedData + (i + 1)) = BackGroundColorPalette[1][_ImageProcessing_ImageResolution_14Bit - *(Data + (j + 0))];
				*(MappedData + (i + 2)) = BackGroundColorPalette[2][_ImageProcessing_ImageResolution_14Bit - *(Data + (j + 0))];

			}
			else {

				// Formater billede data med Baggrund color palette data 
				*(MappedData + (i + 0)) = BackGroundColorPalette[0][*(Data + (j + 0))];
				*(MappedData + (i + 1)) = BackGroundColorPalette[1][*(Data + (j + 0))];
				*(MappedData + (i + 2)) = BackGroundColorPalette[2][*(Data + (j + 0))];

			}

		}

	}

}

void RMH_ImageProcessing_DisplayColorPaletteInPictureBox(unsigned char ColorPalette[3][256], System::Windows::Forms::PictureBox^ PictureBox) {

	// Routinen Om-Formaterer et givet Color Palette array til et RGB array og konverterrer dette til Bitmap
	// Og viser Bitmappet i en givet PictureBox Uden de normale anti-aliserings problemer

	// Lokale definerede konstanter
	#define _ColorBar_Width      4      // Skal være et multiplum af 2!
	#define _ColorBar_Height     256    // Skal være et multiplum af 2!
	#define _ColorBar_RGBBands   3

	// Lokale variabler og objekter
	System::Drawing::Bitmap^ TempBitmap = gcnew Bitmap(PictureBox->Width, PictureBox->Height, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	System::Drawing::Graphics^ BitmapGraphics = Graphics::FromImage(TempBitmap);

	// Lokale array til givet Color Palette Om-formatering
	unsigned char ColorPaletteRGB[_ColorBar_Width * _ColorBar_Height * _ColorBar_RGBBands] = { 0 };
	// Udregn Givet Color Palette array til RGB Color Palette array offset  
	unsigned char ColorPaletteArrayOffset = (_ColorBar_Width * _ColorBar_Height * _ColorBar_RGBBands) / _ColorBar_Height;

	// Konverter og formater Color Palette til RGB array
	for (int i = 0; i < (_ColorBar_Width * _ColorBar_Height * _ColorBar_RGBBands); i += 3) {

		// Skriv RGB værdier fra givet Color Palette array til Formaterede RGB array
		ColorPaletteRGB[i + 0] = ColorPalette[2][i / ColorPaletteArrayOffset];  // Blå
		ColorPaletteRGB[i + 1] = ColorPalette[1][i / ColorPaletteArrayOffset];  // Grøn
		ColorPaletteRGB[i + 2] = ColorPalette[0][i / ColorPaletteArrayOffset];  // Rød

	}

	// Konverter Formaterede RGB array til Bitmap
	System::Drawing::Bitmap^ ColorBarBitmap = gcnew System::Drawing::Bitmap(
		_ColorBar_Width,
		_ColorBar_Height,
		_ColorBar_RGBBands * _ColorBar_Width,
		System::Drawing::Imaging::PixelFormat::Format24bppRgb,
		IntPtr(ColorPaletteRGB));

	// Roter Bitmap Med 180 Grader - KAN OPTIMERES!!
	ColorBarBitmap->RotateFlip(System::Drawing::RotateFlipType::Rotate180FlipNone);

	// Ryd Grafik objektet til default "BackColor"
	BitmapGraphics->Clear(PictureBox->BackColor);

	// Konfigurer Bitmap Interpolations metode
	BitmapGraphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::Bilinear;

	// Tilpas Color Palette Bitmap ind i området af Pictureboxen
	BitmapGraphics->DrawImage(
		ColorBarBitmap,                                          // Source Bitmap Billede
		System::Drawing::Rectangle(0, 0, PictureBox->Width, PictureBox->Height),  // Distanations Rectangle
		0,                                                       // Source X kordinat
		0,                                                       // Source Y kordinat
		_ColorBar_Width - 1,                                     // Width af Source Rectangle
		_ColorBar_Height,                                        // Height af Source Rectangle
		GraphicsUnit::Pixel);                                    // Grafisk Unit Format 

    // Slet Midlertidigt grafisk objekt
	delete BitmapGraphics;

	// Display Formaterede Color Palette Bitmap i PictureBox
	PictureBox->Image = TempBitmap;

}

void RMH_ImageProcessing_FormatColorPaletteRangeInsideBackgroundPalette(unsigned short MainPalette[3][16384], bool MainPaletteInvertFlag, bool AdaptFullPaletteWithinRange, unsigned short BackPalette[3][16384], bool BackPaletteInvertFlag, unsigned short MainPaletteMaxRange, unsigned short MainPaletteMinRange, unsigned short (*OutputPalette)[16384]) {

	// Routinen formaterer en givet color palette oveni en baggrund color palette, med givet range parameter

	// Lokale variabler
	unsigned int RangedIndex = 0;
	unsigned int RangeDifference = MainPaletteMaxRange - MainPaletteMinRange;
	double RangeScale = (double)_ImageProcessing_ImageResolution_14Bit / RangeDifference;

	// Loop til og med længden af color paletten
	for (unsigned int i = 0; i < (_ImageProcessing_ImageResolution_14Bit + 1); i++) {

		// Hvis index er indenfor den primære palette Max/Min range
		if (i >= MainPaletteMinRange && i <= MainPaletteMaxRange) {

			// Skal hele den primære color palette justeres til af fitte indstillede range
			if (AdaptFullPaletteWithinRange == true) {

				// Udregn Range Index for full color palette range justering
				RangedIndex = (unsigned int)(RangeScale * (i - MainPaletteMinRange));

			}
			else {

				// Range Index er lig med 'i'
				RangedIndex = i;

			}

			// Skriv primære palette RGB værdier til output array pointer
			*(*(OutputPalette + 0) + i) = MainPalette[0][RangedIndex];
			*(*(OutputPalette + 1) + i) = MainPalette[1][RangedIndex];
			*(*(OutputPalette + 2) + i) = MainPalette[2][RangedIndex];

		}
		else {

			// Kompenser for inverterede main color palette
			if (MainPaletteInvertFlag == true) {

				// Skal baggrunds paletten inverteres
				if (BackPaletteInvertFlag == true) {

					// Skriv Baggrund palette RGB værdier til output array pointer
					*(*(OutputPalette + 0) + i) = BackPalette[0][i];
					*(*(OutputPalette + 1) + i) = BackPalette[1][i];
					*(*(OutputPalette + 2) + i) = BackPalette[2][i];


				}
				else {

					// Skriv Baggrund palette RGB værdier til output array pointer
					*(*(OutputPalette + 0) + i) = BackPalette[0][_ImageProcessing_ImageResolution_14Bit - i];
					*(*(OutputPalette + 1) + i) = BackPalette[1][_ImageProcessing_ImageResolution_14Bit - i];
					*(*(OutputPalette + 2) + i) = BackPalette[2][_ImageProcessing_ImageResolution_14Bit - i];

				}

			}
			else {

				// Skal baggrunds paletten inverteres
				if (BackPaletteInvertFlag == true) {

					// Skriv Baggrund palette RGB værdier til output array pointer
					*(*(OutputPalette + 0) + i) = BackPalette[0][_ImageProcessing_ImageResolution_14Bit - i];
					*(*(OutputPalette + 1) + i) = BackPalette[1][_ImageProcessing_ImageResolution_14Bit - i];
					*(*(OutputPalette + 2) + i) = BackPalette[2][_ImageProcessing_ImageResolution_14Bit - i];


				}
				else {

					// Skriv Baggrund palette RGB værdier til output array pointer
					*(*(OutputPalette + 0) + i) = BackPalette[0][i];
					*(*(OutputPalette + 1) + i) = BackPalette[1][i];
					*(*(OutputPalette + 2) + i) = BackPalette[2][i];

				}

			}

		}

	}

}

// ----------------------------- Billede Processerings Routiner ----------------------------- //

void RMH_ImageProcessing_LinearAutomaticGainControlRaw(unsigned short *ThermalData, unsigned short *GainGrayscale, unsigned int FrameWidth, unsigned int FrameHeight, double MaxOutPixelVal, double MinOutPixelVal, double MaxInPixelVal, double MinInPixelVal) {

	// Routinen implementerer Linear Automatisk Gain Kontrol til et input billede data array
	// AGC billede dataer er derfra passerede videre til pointer arrayet.
	// Algoritme er liniariceret som: y = a * x + b

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

		// Læs pixel værdierne
		PixelValue1 = (double)*(ThermalData + i);
		PixelValue2 = (double)*(ThermalData + (i + 1));
		PixelValue3 = (double)*(ThermalData + (i + 2));
		PixelValue4 = (double)*(ThermalData + (i + 3));

		// Skaller Pixel værdier til givet skallerings og offset faktor
		*(GainGrayscale + i) = (unsigned short)(LinearScaleFactor * PixelValue1 + OffsetScale);
		*(GainGrayscale + (i + 1)) = (unsigned short)(LinearScaleFactor * PixelValue2 + OffsetScale);
		*(GainGrayscale + (i + 2)) = (unsigned short)(LinearScaleFactor * PixelValue3 + OffsetScale);
		*(GainGrayscale + (i + 3)) = (unsigned short)(LinearScaleFactor * PixelValue4 + OffsetScale);

	}

}

unsigned char RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(unsigned char* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, float XPos, float YPos) {

	// Routinen håndterer pixel værdien for en filter Kernel med kordinat udenfor billede data matricen

	// Lokale variabler
	unsigned int ArrayIndex = 0;

	// For pixel værdier udenfor Billede data matrice området
	if (XPos < 0.0) { XPos = 0.0; }
	if (XPos > ImageDataWidth - 1) { XPos = ImageDataWidth - 1; }
	if (YPos < 0.0) { YPos = 0.0; }
	if (YPos > ImageDataHeight - 1) { YPos = ImageDataHeight - 1; }

	// Konverter matrice index til array index
	ArrayIndex = (YPos * ImageDataWidth) + XPos;

	// Retuner Pixel data værdien
	return *(ImageData + ArrayIndex);

}

// --- Gaussian Billede Filtrerings Processering --->

void RMH_ImageProcessing_2DGaussian3x3KernelBlur(unsigned char* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char *BluredImage) {

	// Routinen implementerer et 2D Gaussian Kernel Blur filter

	// Lokale variabler
	unsigned int ArrayIndex = 0;
	float GaussianKernelSum = 0.0;
	float GaussianImageKernelSum = 0.0;
	unsigned int KernalMaskSize = 3 * 3;

	// Loop igennem alle billed matricens rækker
	for (unsigned int Y = 0; Y < ImageDataHeight; Y++) {

		// Loop igennem alle billed matricens Kolonner
		for (unsigned int X = 0; X < ImageDataWidth; X++) {

			// Nulstil Gaussian kernel sum variabelet
			GaussianImageKernelSum = 0;
			// Nulstil Gaussian Kernal sum variablet
			GaussianKernelSum = 0;

			// Loop for hver position i Kernel masken
			for (unsigned int i = 0; i < KernalMaskSize; i++) {

				// Udregn Gaussian Kernelens Sum
				GaussianKernelSum = GaussianKernelSum + Gaussian3x3KernelMask[i];

				// Udregn den filtreret 2. Ordens Laplacian Billede data koefficient
				GaussianImageKernelSum = GaussianImageKernelSum + (Gaussian3x3KernelMask[i] * (float)RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)X + Kernel3x3MatrixXCoordinates[i], (float)Y + Kernel3x3MatrixYCoordinates[i]));

			}
			
			// Divider Udregnede Gaussian Blur pixel værdi med Kernel Sum (Kernel Normalisering)
			GaussianImageKernelSum = GaussianImageKernelSum / GaussianKernelSum;

			// Konverter matrice index til array index
			ArrayIndex = (Y * ImageDataWidth) + X;

			// Clamp processerede billede pixel data til 8Bit Range
			if (GaussianImageKernelSum > 255.0) { GaussianImageKernelSum = 255.0; }
			if (GaussianImageKernelSum < 0.0) { GaussianImageKernelSum = 0.0; }

			// Skriv Gaussian Blur Billede data til pointer array
			*(BluredImage + ArrayIndex) = (unsigned char)GaussianImageKernelSum;

		}

	}

}

// --- Unsharp Mask Billede Sharpenning Processering --->

bool RMH_ImageProcessing_GenerateUnsharpKernelMask(unsigned char KernelMaskSize, float Sigma, float *KernelMaskPointer) {

	// Routinen genererer en Normaliseret Unsharp Kernel masken til Unsharp billede filtrerings routinen
	// Givet sigma indput er Unsharp Kernel maskens Standard diviation
	// Rotutinen retunerer et status flag som indikerer at Kernel masken var korrekt genereret

	// Lokale variabler
	float PI = 3.141592654;
	float EQDivisionPart = 0.0;
	float* KernelXCoordPointer;
	float* KernelYCoordPointer;
	float EQExponentialPart = 0.0;
	float KernalScaleFactor = 0.0;
	bool KernelMaskOKFlag = false;
	float GaussianKernalValue = 0.0;
	float MinimumKernalValue = 0xFFFF;
	bool KernelMaskGeneratedOkFlag = false;

	// Kontroller valgte Kernel Maske størrelse og indstil relavante parametere
	switch (KernelMaskSize) {

		// Indstil pointer til valgte filter Kernel, Filter Kernel X/Y koordinat matricer
		case _ImageKernelMaskFilter_Size3x3: KernelMaskOKFlag = true; KernelXCoordPointer = Kernel3x3MatrixXCoordinates; KernelYCoordPointer = Kernel3x3MatrixYCoordinates; break;
		case _ImageKernelMaskFilter_Size5x5: KernelMaskOKFlag = true; KernelXCoordPointer = Kernel5x5MatrixXCoordinates; KernelYCoordPointer = Kernel5x5MatrixYCoordinates; break;

	}

	// Kontroller om korrekte kernel maske parametere er blevet givet
	if (KernelMaskOKFlag == true) {

		// Loop til og med størrelsen af Gaussian kernel masken som skal genereres
		for (unsigned int i = 0; i < KernelMaskSize; i++) {

			// Udregn del stykker af samlede Gaussian Kernel formular
			EQDivisionPart = 1 / (2 * PI * pow(Sigma, 2));
			EQExponentialPart = exp(-(pow(KernelXCoordPointer[i], 2) + pow(KernelYCoordPointer[i], 2)) / (2 * pow(Sigma, 2)));

			// Udregn den samlede aktuelle Gaussian Kernel Værdi
			GaussianKernalValue = EQDivisionPart * EQExponentialPart;

			// Find den laveste Gaussian Kernal værdi 
			if (GaussianKernalValue < MinimumKernalValue) {

				// Opdater Laveste Gaussian Kernal værdi
				MinimumKernalValue = GaussianKernalValue;

			}

			// Udregn Gaussian kernelens Normalicerings Faktor
			KernalScaleFactor = 1.0 / MinimumKernalValue;

			// Udregn den Normaliseret Gaussian Kernel Værdi
			*(KernelMaskPointer + i) = KernalScaleFactor * GaussianKernalValue;

		}

		// Opdater kernel maske status flag
		KernelMaskGeneratedOkFlag = true;

	}
	else {

		// Opdater kernel maske status flag
		KernelMaskGeneratedOkFlag = false;

	}

	// Retuner kernel maske genererings stauts
	return KernelMaskGeneratedOkFlag;

}

void RMH_ImageProcessing_2DUnsharpMaskKernelImageSharpening(unsigned short* ImageData, unsigned int ImageResolution, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char KernelMaskSize, float *KernelMaskPointer, float SharpeningStrength, bool OutputUnsharpMaskFlag, unsigned short* SharpenedImage) {

	// Routinen implementerer et 2-Dimensionelt Gaussian Blur Unsharp Kernel Maske Billede processerings teknik
	// Som benyttes til at gøre et billede mere skarpt, men konfigurerbar styrke.
	// 19-05-2023 -> Routinen er blevet super optimerede med "Loop Unrolling" med en faktor af 8 = 450% hurtigere
	// 23-07-2023 -> Opdaterede.

	/*
		
		Tilhørende Macroer ->

		// Billede Opløsnings Format Reference Macroer
		#define _ImageProcessing_ImageResolution_8Bit           255
		#define _ImageProcessing_ImageResolution_14Bit          16383
		#define _ImageProcessing_ImageResolution_16Bit          65535
	
	
	*/

	// Lokale variabler - Lager i CPU register
	register float* KernelXCoordPointer;
	register float* KernelYCoordPointer;
	register float GaussianKernelSum = 0.0;
	register float KernelToImageXPos1 = 0;
	register float KernelToImageXPos2 = 0;
	register float KernelToImageXPos3 = 0;
	register float KernelToImageXPos4 = 0;
	register float KernelToImageXPos5 = 0;
	register float KernelToImageXPos6 = 0;
	register float KernelToImageXPos7 = 0;
	register float KernelToImageXPos8 = 0;
	register float KernelToImageYPos = 0;
	register unsigned int ArrayIndex1 = 0;
	register unsigned int ArrayIndex2 = 0;
	register unsigned int ArrayIndex3 = 0;
	register unsigned int ArrayIndex4 = 0;
	register unsigned int ArrayIndex5 = 0;
	register unsigned int ArrayIndex6 = 0;
	register unsigned int ArrayIndex7 = 0;
	register unsigned int ArrayIndex8 = 0;
	register float BlurMaskPixelValue1 = 0;
	register float BlurMaskPixelValue2 = 0;
	register float BlurMaskPixelValue3 = 0;
	register float BlurMaskPixelValue4 = 0;
	register float BlurMaskPixelValue5 = 0;
	register float BlurMaskPixelValue6 = 0;
	register float BlurMaskPixelValue7 = 0;
	register float BlurMaskPixelValue8 = 0;
	register float SharpenedPixelValue1 = 0;
	register float SharpenedPixelValue2 = 0;
	register float SharpenedPixelValue3 = 0;
	register float SharpenedPixelValue4 = 0;
	register float SharpenedPixelValue5 = 0;
	register float SharpenedPixelValue6 = 0;
	register float SharpenedPixelValue7 = 0;
	register float SharpenedPixelValue8 = 0;
	register float GaussianImageKernelSum1 = 0.0;
	register float GaussianImageKernelSum2 = 0.0;
	register float GaussianImageKernelSum3 = 0.0;
	register float GaussianImageKernelSum4 = 0.0;
	register float GaussianImageKernelSum5 = 0.0;
	register float GaussianImageKernelSum6 = 0.0;
	register float GaussianImageKernelSum7 = 0.0;
	register float GaussianImageKernelSum8 = 0.0;
	register unsigned int KernelToImageIndex1 = 0;
	register unsigned int KernelToImageIndex2 = 0;
	register unsigned int KernelToImageIndex3 = 0;
	register unsigned int KernelToImageIndex4 = 0;
	register unsigned int KernelToImageIndex5 = 0;
	register unsigned int KernelToImageIndex6 = 0;
	register unsigned int KernelToImageIndex7 = 0;
	register unsigned int KernelToImageIndex8 = 0;

	// Kontroller valgte Kernel Maske størrelse og indstil relavante parametere
	switch (KernelMaskSize) {

		// Indstil pointer til valgte filter Kernel, Filter Kernel X/Y koordinat matricer
		case _ImageKernelMaskFilter_Size3x3: KernelXCoordPointer = Kernel3x3MatrixXCoordinates; KernelYCoordPointer = Kernel3x3MatrixYCoordinates; break;
		case _ImageKernelMaskFilter_Size5x5: KernelXCoordPointer = Kernel5x5MatrixXCoordinates; KernelYCoordPointer = Kernel5x5MatrixYCoordinates; break;

	}

	// Loop for hver position i Kernel masken
	for (unsigned int i = 0; i < KernelMaskSize; i++) {

		// Udregn Gaussian Kernel maskens Sum
		GaussianKernelSum = GaussianKernelSum + *(KernelMaskPointer + i);  

	}

	// Division til Multiplikations konverter gaussian sum (CPU Cycle Optimering)
	GaussianKernelSum = 1.0 / GaussianKernelSum;

	// Loop igennem alle billed matricens rækker
	for (unsigned int Y = 0; Y < ImageDataHeight; Y++) {

		// Loop igennem alle billed matricens Kolonner
		for (unsigned int X = 0; X < ImageDataWidth; X += 8) {

			// Nulstil Gaussian kernel sum variabelet
			GaussianImageKernelSum1 = 0.0;
			GaussianImageKernelSum2 = 0.0;
			GaussianImageKernelSum3 = 0.0;
			GaussianImageKernelSum4 = 0.0;
			GaussianImageKernelSum5 = 0.0;
			GaussianImageKernelSum6 = 0.0;
			GaussianImageKernelSum7 = 0.0;
			GaussianImageKernelSum8 = 0.0;

			// Loop for each position in the kernel mask
			for (unsigned int i = 0; i < KernelMaskSize; i++) {

				// Udregn Kernel-Til-Billede X & Y kordinaterne
				KernelToImageXPos1 = X + *(KernelXCoordPointer + i);
				KernelToImageXPos2 = (X + 1) + *(KernelXCoordPointer + i);
				KernelToImageXPos3 = (X + 2) + *(KernelXCoordPointer + i);
				KernelToImageXPos4 = (X + 3) + *(KernelXCoordPointer + i);
				KernelToImageXPos5 = (X + 4) + *(KernelXCoordPointer + i);
				KernelToImageXPos6 = (X + 5) + *(KernelXCoordPointer + i);
				KernelToImageXPos7 = (X + 6) + *(KernelXCoordPointer + i);
				KernelToImageXPos8 = (X + 7) + *(KernelXCoordPointer + i);
				KernelToImageYPos = Y + *(KernelYCoordPointer + i);

				// Kompenser for pixel værdier udenfor Billede data matrice området
				if (KernelToImageXPos1 < 0) { KernelToImageXPos1 = 0; } if (KernelToImageXPos1 > ImageDataWidth - 1) { KernelToImageXPos1 = ImageDataWidth - 1; }
				if (KernelToImageXPos2 < 0) { KernelToImageXPos2 = 0; } if (KernelToImageXPos2 > ImageDataWidth - 1) { KernelToImageXPos2 = ImageDataWidth - 1; }
				if (KernelToImageXPos3 < 0) { KernelToImageXPos3 = 0; } if (KernelToImageXPos3 > ImageDataWidth - 1) { KernelToImageXPos3 = ImageDataWidth - 1; }
				if (KernelToImageXPos4 < 0) { KernelToImageXPos4 = 0; } if (KernelToImageXPos4 > ImageDataWidth - 1) { KernelToImageXPos4 = ImageDataWidth - 1; }
				if (KernelToImageXPos5 < 0) { KernelToImageXPos5 = 0; } if (KernelToImageXPos5 > ImageDataWidth - 1) { KernelToImageXPos5 = ImageDataWidth - 1; }
				if (KernelToImageXPos6 < 0) { KernelToImageXPos6 = 0; } if (KernelToImageXPos6 > ImageDataWidth - 1) { KernelToImageXPos6 = ImageDataWidth - 1; }
				if (KernelToImageXPos7 < 0) { KernelToImageXPos7 = 0; } if (KernelToImageXPos7 > ImageDataWidth - 1) { KernelToImageXPos7 = ImageDataWidth - 1; }
				if (KernelToImageXPos8 < 0) { KernelToImageXPos8 = 0; } if (KernelToImageXPos8 > ImageDataWidth - 1) { KernelToImageXPos8 = ImageDataWidth - 1; }
				if (KernelToImageYPos < 0)  { KernelToImageYPos = 0;  } if (KernelToImageYPos > ImageDataHeight - 1) { KernelToImageYPos = ImageDataHeight - 1; }

				// Udregn Kernel Til Billede Index
				KernelToImageIndex1 = KernelToImageYPos * ImageDataWidth + KernelToImageXPos1;
				KernelToImageIndex2 = KernelToImageYPos * ImageDataWidth + KernelToImageXPos2;
				KernelToImageIndex3 = KernelToImageYPos * ImageDataWidth + KernelToImageXPos3;
				KernelToImageIndex4 = KernelToImageYPos * ImageDataWidth + KernelToImageXPos4;
				KernelToImageIndex5 = KernelToImageYPos * ImageDataWidth + KernelToImageXPos5;
				KernelToImageIndex6 = KernelToImageYPos * ImageDataWidth + KernelToImageXPos6;
				KernelToImageIndex7 = KernelToImageYPos * ImageDataWidth + KernelToImageXPos7;
				KernelToImageIndex8 = KernelToImageYPos * ImageDataWidth + KernelToImageXPos8;

				// Udregn Gaussian Unsharp Kernel-Til-Billede data summen
				GaussianImageKernelSum1 = GaussianImageKernelSum1 + *(KernelMaskPointer + i) * *(ImageData + KernelToImageIndex1);
				GaussianImageKernelSum2 = GaussianImageKernelSum2 + *(KernelMaskPointer + i) * *(ImageData + KernelToImageIndex2);
				GaussianImageKernelSum3 = GaussianImageKernelSum3 + *(KernelMaskPointer + i) * *(ImageData + KernelToImageIndex3);
				GaussianImageKernelSum4 = GaussianImageKernelSum4 + *(KernelMaskPointer + i) * *(ImageData + KernelToImageIndex4);
				GaussianImageKernelSum5 = GaussianImageKernelSum5 + *(KernelMaskPointer + i) * *(ImageData + KernelToImageIndex5);
				GaussianImageKernelSum6 = GaussianImageKernelSum6 + *(KernelMaskPointer + i) * *(ImageData + KernelToImageIndex6);
				GaussianImageKernelSum7 = GaussianImageKernelSum7 + *(KernelMaskPointer + i) * *(ImageData + KernelToImageIndex7);
				GaussianImageKernelSum8 = GaussianImageKernelSum8 + *(KernelMaskPointer + i) * *(ImageData + KernelToImageIndex8);

			}

			// Konverter matrice index til array index
			ArrayIndex1 = (Y * ImageDataWidth) + X;
			ArrayIndex2 = ArrayIndex1 + 1;
			ArrayIndex3 = ArrayIndex1 + 2;
			ArrayIndex4 = ArrayIndex1 + 3;
			ArrayIndex5 = ArrayIndex1 + 4;
			ArrayIndex6 = ArrayIndex1 + 5;
			ArrayIndex7 = ArrayIndex1 + 6;
			ArrayIndex8 = ArrayIndex1 + 7;

			// Divider (kompenserede division) Udregnede Gaussian Blur pixel værdi med Kernel Sum (Kernel Normalisering)
			GaussianImageKernelSum1 = GaussianImageKernelSum1 * GaussianKernelSum;
			GaussianImageKernelSum2 = GaussianImageKernelSum2 * GaussianKernelSum;
			GaussianImageKernelSum3 = GaussianImageKernelSum3 * GaussianKernelSum;
			GaussianImageKernelSum4 = GaussianImageKernelSum4 * GaussianKernelSum;
			GaussianImageKernelSum5 = GaussianImageKernelSum5 * GaussianKernelSum;
			GaussianImageKernelSum6 = GaussianImageKernelSum6 * GaussianKernelSum;
			GaussianImageKernelSum7 = GaussianImageKernelSum7 * GaussianKernelSum;
			GaussianImageKernelSum8 = GaussianImageKernelSum8 * GaussianKernelSum;

			// Udregn Unsharp Maske pixel værdien
			BlurMaskPixelValue1 = (float)(*(ImageData + ArrayIndex1) - GaussianImageKernelSum1) * SharpeningStrength;
			BlurMaskPixelValue2 = (float)(*(ImageData + ArrayIndex2) - GaussianImageKernelSum2) * SharpeningStrength;
			BlurMaskPixelValue3 = (float)(*(ImageData + ArrayIndex3) - GaussianImageKernelSum3) * SharpeningStrength;
			BlurMaskPixelValue4 = (float)(*(ImageData + ArrayIndex4) - GaussianImageKernelSum4) * SharpeningStrength;
			BlurMaskPixelValue5 = (float)(*(ImageData + ArrayIndex5) - GaussianImageKernelSum5) * SharpeningStrength;
			BlurMaskPixelValue6 = (float)(*(ImageData + ArrayIndex6) - GaussianImageKernelSum6) * SharpeningStrength;
			BlurMaskPixelValue7 = (float)(*(ImageData + ArrayIndex7) - GaussianImageKernelSum7) * SharpeningStrength;
			BlurMaskPixelValue8 = (float)(*(ImageData + ArrayIndex8) - GaussianImageKernelSum8) * SharpeningStrength;

			// Skal Unsharp makse pixel værdierne skrives til output array
			if (OutputUnsharpMaskFlag == true) {

				// Skiv Unsharp makse pixel værdierne skrives til output array
				SharpenedPixelValue1 = BlurMaskPixelValue1;
				SharpenedPixelValue2 = BlurMaskPixelValue2;
				SharpenedPixelValue3 = BlurMaskPixelValue3;
				SharpenedPixelValue4 = BlurMaskPixelValue4;
				SharpenedPixelValue5 = BlurMaskPixelValue5;
				SharpenedPixelValue6 = BlurMaskPixelValue6;
				SharpenedPixelValue7 = BlurMaskPixelValue7;
				SharpenedPixelValue8 = BlurMaskPixelValue8;

			}
			else {

				// Skriv sharpened billede processerede pixel til output array
				SharpenedPixelValue1 = *(ImageData + ArrayIndex1) + BlurMaskPixelValue1;
				SharpenedPixelValue2 = *(ImageData + ArrayIndex2) + BlurMaskPixelValue2;
				SharpenedPixelValue3 = *(ImageData + ArrayIndex3) + BlurMaskPixelValue3;
				SharpenedPixelValue4 = *(ImageData + ArrayIndex4) + BlurMaskPixelValue4;
				SharpenedPixelValue5 = *(ImageData + ArrayIndex5) + BlurMaskPixelValue5;
				SharpenedPixelValue6 = *(ImageData + ArrayIndex6) + BlurMaskPixelValue6;
				SharpenedPixelValue7 = *(ImageData + ArrayIndex7) + BlurMaskPixelValue7;
				SharpenedPixelValue8 = *(ImageData + ArrayIndex8) + BlurMaskPixelValue8;

			}

			// Clamp processerede billede pixel data til billede opløsningens fulde Range
			if (SharpenedPixelValue1 > ImageResolution) { SharpenedPixelValue1 = ImageResolution; } if (SharpenedPixelValue1 < 0.0) { SharpenedPixelValue1 = 0.0; }
			if (SharpenedPixelValue2 > ImageResolution) { SharpenedPixelValue2 = ImageResolution; } if (SharpenedPixelValue2 < 0.0) { SharpenedPixelValue2 = 0.0; }
			if (SharpenedPixelValue3 > ImageResolution) { SharpenedPixelValue3 = ImageResolution; } if (SharpenedPixelValue3 < 0.0) { SharpenedPixelValue3 = 0.0; }
			if (SharpenedPixelValue4 > ImageResolution) { SharpenedPixelValue4 = ImageResolution; } if (SharpenedPixelValue4 < 0.0) { SharpenedPixelValue4 = 0.0; }
			if (SharpenedPixelValue5 > ImageResolution) { SharpenedPixelValue5 = ImageResolution; } if (SharpenedPixelValue5 < 0.0) { SharpenedPixelValue5 = 0.0; }
			if (SharpenedPixelValue6 > ImageResolution) { SharpenedPixelValue6 = ImageResolution; } if (SharpenedPixelValue6 < 0.0) { SharpenedPixelValue6 = 0.0; }
			if (SharpenedPixelValue7 > ImageResolution) { SharpenedPixelValue7 = ImageResolution; } if (SharpenedPixelValue7 < 0.0) { SharpenedPixelValue7 = 0.0; }
			if (SharpenedPixelValue8 > ImageResolution) { SharpenedPixelValue8 = ImageResolution; } if (SharpenedPixelValue8 < 0.0) { SharpenedPixelValue8 = 0.0; }

			// Skriv Gaussian Blur skærpede Billede data til pointer array
			*(SharpenedImage + ArrayIndex1) = (unsigned short)SharpenedPixelValue1;
			*(SharpenedImage + ArrayIndex2) = (unsigned short)SharpenedPixelValue2;
			*(SharpenedImage + ArrayIndex3) = (unsigned short)SharpenedPixelValue3;
			*(SharpenedImage + ArrayIndex4) = (unsigned short)SharpenedPixelValue4;
			*(SharpenedImage + ArrayIndex5) = (unsigned short)SharpenedPixelValue5;
			*(SharpenedImage + ArrayIndex6) = (unsigned short)SharpenedPixelValue6;
			*(SharpenedImage + ArrayIndex7) = (unsigned short)SharpenedPixelValue7;
			*(SharpenedImage + ArrayIndex8) = (unsigned short)SharpenedPixelValue8;

		}

	}

}

// --- Laplacian Billede Sharpening Processering --->

void RMH_ImageProcessing_LaplacianImageSharpening(unsigned char* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char KernelMask, float SharpeningStreangth, bool ShowFilteredMaks, unsigned char* SharpenedImage) {

	// Routinen implementerer Laplacian Kernel filtrering til givet input billede data
	// Hvilket benyttes til at gøre et billede mere skarpt

	// Lokale variabler
	float* KernelMaskPointer;
	float* KernelXCoordPointer;
	float* KernelYCoordPointer;
	float IILaplacianVal = 0.0;
	unsigned int ArrayIndex = 0;
	float SharpenedPixelValue = 0.0;
	unsigned int KernalMaskSize = 0;
	unsigned int KernelCenterIndex = 0;

	// Begræns valget af Kernel maske input værdien
	if (KernelMask < _LaplacianImageSharpening_MinNmbOfKernelMasks) { KernelMask = _LaplacianImageSharpening_MinNmbOfKernelMasks; }
	if (KernelMask > _LaplacianImageSharpening_MaxNmbOfKernelMasks) { KernelMask = _LaplacianImageSharpening_MaxNmbOfKernelMasks; }

	// Valg af filter maske
	switch (KernelMask) {

		// Indstil pointer til valgte filter Kernel, Filter Kernel X/Y koordinat matricer og indstil fast kernel størrelse
		case _LaplacianImageKernel_3x3KernalMask1: KernalMaskSize = 3 * 3; KernelMaskPointer = Laplacian3x3KernelMask1; KernelXCoordPointer = Kernel3x3MatrixXCoordinates; KernelYCoordPointer = Kernel3x3MatrixYCoordinates;  break;
		case _LaplacianImageKernel_3x3KernalMask2: KernalMaskSize = 3 * 3; KernelMaskPointer = Laplacian3x3KernelMask2; KernelXCoordPointer = Kernel3x3MatrixXCoordinates; KernelYCoordPointer = Kernel3x3MatrixYCoordinates;  break;
		case _LaplacianImageKernel_5x5KernalMask1: KernalMaskSize = 5 * 5; KernelMaskPointer = Laplacian5x5KernelMask2; KernelXCoordPointer = Kernel5x5MatrixXCoordinates; KernelYCoordPointer = Kernel5x5MatrixYCoordinates;  break;

	}

	// Udregn Kernel mertricens center koefficients array index
	KernelCenterIndex = (KernalMaskSize - 1) / 2;

	// Loop igennem alle billed matricens rækker
	for (unsigned int Y = 0; Y < ImageDataHeight; Y++) {

		// Loop igennem alle billed matricens Kolonner
		for (unsigned int X = 0; X < ImageDataWidth; X++) {

			// Nulstil Laplacian Sharpenings sum værien
			IILaplacianVal = 0;

			// Loop for hver position i Kernel masken
			for (unsigned int i = 0; i < KernalMaskSize; i++) {

				// Udregn den filtreret 2. Ordens Laplacian Billede data koefficient
				IILaplacianVal = IILaplacianVal + ((KernelMaskPointer[i] * SharpeningStreangth) * (float)RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)X + KernelXCoordPointer[i], (float)Y + KernelYCoordPointer[i]));

			}

			// Konverter matrice index til array index
			ArrayIndex = (Y * ImageDataWidth) + X;

			// Kontroller polaritet af filter maskens center koefficient (undgå clipping)
			if (KernelMaskPointer[KernelCenterIndex] < 0.0) {

				// Træk altid laveste værdi fra højeste værdi
				if (IILaplacianVal > (float)ImageData[ArrayIndex]) {

					// Skal kun det filtreret Laplacian billede vises
					if (ShowFilteredMaks == true) {

						// Udregn den Skærpet billede pixel værdi
						SharpenedPixelValue = IILaplacianVal;

					}
					else {

						// Udregn den Skærpet billede pixel værdi
						SharpenedPixelValue = IILaplacianVal - (float)ImageData[ArrayIndex];

					}

					// Clamp Skærpet billede pixel data til 8Bit Range
					if (SharpenedPixelValue > 255.0) { SharpenedPixelValue = 255.0; }
					if (SharpenedPixelValue < 0.0) { SharpenedPixelValue = 0.0; }

					// Skriv Skærpet Billede data til pointer array
					*(SharpenedImage + ArrayIndex) = (unsigned char)SharpenedPixelValue;

				}
				else {

					// Skal kun det filtreret Laplacian billede vises
					if (ShowFilteredMaks == true) {

						// Udregn den Skærpet billede pixel værdi
						SharpenedPixelValue = IILaplacianVal;

					}
					else {

						// Udregn den Skærpet billede pixel værdi
						SharpenedPixelValue = (float)ImageData[ArrayIndex] - IILaplacianVal;

					}

					// Clamp Skærpet billede pixel data til 8Bit Range
					if (SharpenedPixelValue > 255.0) { SharpenedPixelValue = 255.0; }
					if (SharpenedPixelValue < 0.0) { SharpenedPixelValue = 0.0; }

					// Skriv Skærpet Billede data til pointer array
					*(SharpenedImage + ArrayIndex) = (unsigned char)SharpenedPixelValue;

				}

			}
			else {

				// Skal kun det filtreret Laplacian billede vises
				if (ShowFilteredMaks == true) {

					// Udregn den Skærpet billede pixel værdi
					SharpenedPixelValue = IILaplacianVal;

				}
				else {

					// Udregn den Skærpet billede pixel værdi
					SharpenedPixelValue = IILaplacianVal + (float)ImageData[ArrayIndex];

				}

				// Clamp Skærpet billede pixel data til 8Bit Range
				if (SharpenedPixelValue > 255.0) { SharpenedPixelValue = 255.0; }
				if (SharpenedPixelValue < 0.0) { SharpenedPixelValue = 0.0; }

				// Skriv Skærpet Billede data til pointer array
				*(SharpenedImage + ArrayIndex) = (unsigned char)SharpenedPixelValue;

			}

		}

	}

}

// --- Billede Median Filtrerings Processering --->

void RMH_ImageProcessing_ImageMedianFiltering(unsigned char* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char *MedianFilteredImage) {

	// Routinen implementerer et 3x3 median maske billede filter

	// Lokale variabler
	unsigned int Temp = 0;
	unsigned int ArrayIndex = 0;
	unsigned char MedianKernelArray[3 * 3];
	unsigned int MedianMaskSize = 3 * 3;

	// Loop igennem alle billed matricens rækker
	for (unsigned int FrameRow = 0; FrameRow < ImageDataHeight; FrameRow++) {

		// Loop igennem alle billed matricens Kolonner
		for (unsigned int FrameColumn = 0; FrameColumn < ImageDataWidth; FrameColumn++) {

			// Læs Median Filterets Kernel Matrice pixel værdier
			MedianKernelArray[0] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn - 1, (float)FrameRow - 1);
			MedianKernelArray[1] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn, (float)FrameRow - 1);
			MedianKernelArray[2] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn + 1, (float)FrameRow - 1);
			MedianKernelArray[3] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn - 1, (float)FrameRow);
			MedianKernelArray[4] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn, (float)FrameRow);
			MedianKernelArray[5] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn + 1, (float)FrameRow);
			MedianKernelArray[6] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn - 1, (float)FrameRow + 1);
			MedianKernelArray[7] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn, (float)FrameRow + 1);
			MedianKernelArray[8] = RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(&ImageData[0], ImageDataWidth, ImageDataHeight, (float)FrameColumn + 1, (float)FrameRow + 1);

			// Konverter matrice index til array index
			ArrayIndex = (FrameRow * ImageDataWidth) + FrameColumn;

			// Sorter Median kernel matricens rækker
			for (unsigned int i = 0; i < MedianMaskSize - 1; i++) {

				// Sorter Median kernel matricens kolonner
				for (unsigned int j = 0; j < MedianMaskSize - i; j++) {

					// Sorter laveste kernel værdier fra start til slut index
					if (MedianKernelArray[j] <= MedianKernelArray[j + 1]) {

						// Læs midlatidig array data og sorter kernel arrayet
						Temp = MedianKernelArray[j];
						MedianKernelArray[j] = MedianKernelArray[j + 1];
						MedianKernelArray[j + 1] = Temp;

					}
					else {

						// Fortsæt ydre iteration 
						continue;

					}

				}
			}

			// Skriv billedets median værdi til filtreret billede array pointer
			*(MedianFilteredImage + ArrayIndex) = MedianKernelArray[4];

		}

	}

}

// --- Billede 2D Interpolation Processering --->

void RMH_ImageProcessing_2DBilinearInterpolation(unsigned short* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned int InterpolatedImageWidth, unsigned int InterpolatedImageHeight, unsigned short* InterpolatedImage) {

	// Routinen implementerer 2D Bilinear Interpolation 
	// Hvilket benyttes til at op/ned-skallerer et billedes opløsning
	// Routinen er specielt optimerede til at være ekstrem hurtig til at håndterer positiv integer billed data.

	// Lokale variabler
	double WidthRatio = 0.0;
	double HeightRatio = 0.0;
	double YHeightHeight = 0.0;
	double YHeightWeight = 0.0;
	double XWidthWeight = 0.0;
	double XHeightRatioStepSize = 0.0;
	double YWidthRatioStepSize = 0.0;
	unsigned int YHeightLength = 0.0;
	unsigned int XWidthLength = 0.0;
	unsigned int XWidthHeight = 0.0;
	unsigned int YHeightLengthIndex = 0;
	unsigned int YHeightHeightIndex = 0;
	unsigned int ImagePixelValue = 0.0;

	// Kontroller givet billede data opløsnings parametere - Udregn Det interpolerede billedes Højde/Bredde forhold
	if (InterpolatedImageWidth > 1) { WidthRatio = ((double)ImageDataWidth - 1.0) / ((double)InterpolatedImageWidth - 1.0); } else { WidthRatio = 0; }
	if (InterpolatedImageHeight > 1) { HeightRatio = ((double)ImageDataHeight - 1.0) / ((double)InterpolatedImageHeight - 1.0); } else { HeightRatio = 0; }

	// Loop igennem alle billed matricens Kolonner
	for (unsigned int X = 0; X < InterpolatedImageHeight; X++) {

		// Udregn Højde forholdets X fraktions parameter
		XHeightRatioStepSize = HeightRatio * X;

		// Udregn Y pixel længden, højden og vægten fra tilhørende højde/længde forhold
		YHeightLength = XHeightRatioStepSize;
		YHeightHeight = (unsigned int)(XHeightRatioStepSize + 0.999);  // RMH Implementering af Hurtig -> ceil(XHeightRatioStepSize);
		YHeightWeight = XHeightRatioStepSize - YHeightLength;

		// Udregn billed data arrayets Y højde og Vægt indekser
		YHeightLengthIndex = YHeightLength * ImageDataWidth;
		YHeightHeightIndex = YHeightHeight * ImageDataWidth;

		// Loop igennem alle billed arrayets Rækker
		for (unsigned int Y = 0; Y < InterpolatedImageWidth; Y++) {

			// Udregn længde forholdets Y fraktions parameter
			YWidthRatioStepSize = WidthRatio * Y;

			// Udregn X pixel længden, højden og vægten fra tilhørende højde/længde forhold
			XWidthLength = YWidthRatioStepSize;
			XWidthHeight = (unsigned int)(YWidthRatioStepSize + 0.999); // RMH Implementering af Hurtig -> ceil(YWidthRatioStepSize);
			XWidthWeight = YWidthRatioStepSize - XWidthLength;

			// Udregn den interpolerede pixels værdi
			ImagePixelValue = ImageData[YHeightLengthIndex + XWidthLength] * (1.0 - XWidthWeight) * (1.0 - YHeightWeight) +
							  ImageData[YHeightLengthIndex + XWidthHeight] * XWidthWeight * (1.0 - YHeightWeight) +
							  ImageData[YHeightHeightIndex + XWidthLength] * YHeightWeight * (1.0 - XWidthWeight) +
							  ImageData[YHeightHeightIndex + XWidthHeight] * XWidthWeight * YHeightWeight;

			// Skriv Interpolerede pixels værdi til givet pointer array
			*(InterpolatedImage + (X * InterpolatedImageWidth + Y)) = ImagePixelValue;

		}
	}

}

// ------------------------------------------------------------------------------------------ //