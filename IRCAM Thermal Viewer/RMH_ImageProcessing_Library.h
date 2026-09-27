
/*
 *  RMH_ImageProcessing_Library.h
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

#pragma once

// RMH_ImageProcessing_Library.h
#ifndef RMH_ImageProcessing_Library_H 
#define RMH_ImageProcessing_Library_H

// Tilhørende Biblioteker
#include "RMH_ThermalCameraSupport_Library.h"

// ----------------------- Billede Opløsnings Format Reference Matricer ---------------------- //

// Billede Opløsnings Format Reference Macroer
#define _ImageProcessing_ImageResolution_8Bit           255
#define _ImageProcessing_ImageResolution_14Bit          16383
#define _ImageProcessing_ImageResolution_16Bit          65535

// ---------------- Billede Processerings Kernal Koordinat Reference Matricer ---------------- //

// Billede Kernel Makse Størrelses Macroer
#define _ImageKernelMaskFilter_Size3x3            3 * 3
#define _ImageKernelMaskFilter_Size5x5            5 * 5

// 3x3 Billede Processerings Kernel X Koordinater Reference Matrice
static float Kernel3x3MatrixXCoordinates[_ImageKernelMaskFilter_Size3x3] = {

	-1, 0, 1,
	-1 ,0, 1,
	-1, 0, 1

};

// 3x3 Billede Processerings Kernel Y Koordinater Reference Matrice
static float Kernel3x3MatrixYCoordinates[_ImageKernelMaskFilter_Size3x3] = {

	-1, -1, -1,
	 0,  0,  0,
	 1,  1,  1

};


// 5x5 Billede Processerings Kernel X Koordinater Reference Matrice
static float Kernel5x5MatrixXCoordinates[_ImageKernelMaskFilter_Size5x5] = {

	-2, -1, 0, 1, 2,
	-2, -1, 0, 1, 2,
	-2, -1, 0, 1, 2,
	-2, -1, 0, 1, 2,
	-2, -1, 0, 1, 2
	
};

// 5x5 Billede Processerings Kernel Y Koordinater Reference Matrice
static float Kernel5x5MatrixYCoordinates[_ImageKernelMaskFilter_Size5x5] = {

	-2, -2, -2, -2, -2,
	-1, -1, -1, -1, -1,
	 0,  0,  0,  0,  0,
	 1,  1,  1,  1,  1,
	 2,  2,  2,  2,  2
 
};

// ------------------------------- Laplacian Kernal Matricer -------------------------------- //

// Laplacian Kernel maske macroer
#define _LaplacianImageSharpening_MinNmbOfKernelMasks     1
#define _LaplacianImageSharpening_MaxNmbOfKernelMasks     3

// Tilgængelige Laplacian Kernal Masker Macroer
#define _LaplacianImageKernel_3x3KernalMask1              1
#define _LaplacianImageKernel_3x3KernalMask2              2
#define _LaplacianImageKernel_5x5KernalMask1              3

// Billede Filtrerings 3x3 Laplacian Kernel Maske 1
static float Laplacian3x3KernelMask1[_ImageKernelMaskFilter_Size3x3] = {

	 0, -1, 0,
	-1, 4, -1,
	 0, -1, 0

};

// Billede Filtrerings 3x3 Laplacian Kernel Maske 2
static float Laplacian3x3KernelMask2[_ImageKernelMaskFilter_Size3x3] = {

	-1, -1, -1,
	-1,  8, -1,
	-1, -1, -1

};

// Billede Filtrerings 5x5 Laplacian Kernel Maske 2
static float Laplacian5x5KernelMask2[_ImageKernelMaskFilter_Size5x5] = {

	 0,  0, -1,  0,  0,
	 0, -1, -2, -1,  0,
	-1, -2, 16, -2, -1,
	 0, -1, -2, -1,  0,
	 0,  0, -1,  0,  0

};

// -------------------------------- Gaussian Kernal Matricer -------------------------------- //

// Gaussiam Blur Max/Min Standard Deviation (Sigma) Macroer
#define _GaussianStandardDeviation_MaxRangeValue      2
#define _GaussianStandardDeviation_MinRangeValue      0.2

// Gaussian Unsharp Billede Sharpening Max/Min Styrke Macroer
#define _GaussianUnSharpStrength_MaxRangeValue        10
#define _GaussianUnSharpStrength_MinRangeValue        0

// Billede Filtrerings 3x3 Gaussian Kernel Maske - Default Sigma = 1
static float Gaussian3x3KernelMask[_ImageKernelMaskFilter_Size3x3] = {

	1, 2, 1,  
	2, 4, 2,  
	1, 2, 1   
	 
};

// Billede Filtrerings 5x5 Gaussian Kernel Maske - Default Sigma = 1
static float Gaussian5x5KernelMask[_ImageKernelMaskFilter_Size5x5] = {

	1,  4,  6,  4, 1,
	4, 16, 24, 16, 4,
	6, 24, 36, 24, 6,
	4, 16, 24, 16, 4,
	1,  4,  6,  4, 1

};

// ------------------------------ Billede Udregnings Routiner ------------------------------- //

double RMH_ImageCalculations_CalMeanOfImage16Bit(unsigned short* ImageData, unsigned int FrameWidth, unsigned int FrameHeight);

// ---------------------- Billede Non-Uniformity Korrektions Routiner ----------------------- //

void RMH_ImageNonUniformityCorrection_ConvertBaselineImageTo16Bit(unsigned char* BaselineImageData, unsigned short* OutputBaseline16Bit, unsigned int FrameWidth, unsigned int FrameHeight);
double RMH_ImageNonUniformityCorrection_CalNonUniformityMap(unsigned short* BaselineImageData, unsigned int FrameWidth, unsigned int FrameHeight, unsigned int FrameMetaDataSize, double* OutputNonUniformityMap);
void RMH_ImageNonUniformityCorrection_ZeroNonUniformityMapArrayData(double* OutputNonUniformityMap, unsigned int FrameWidth, unsigned int FrameHeight);

// ----------------------------- Billede Konverterings Routiner ----------------------------- //

void RMH_ImageConversion_ArrangeYUY2ToRGB24(unsigned char* YUY2in,unsigned char* RGBout, unsigned int FrameWidth, unsigned int FrameHeight);
void RMH_ImageConversion_ConvertYUY2ToGrayscaleRGB24(unsigned char* YUY2in, unsigned char* GrayscaleOut, unsigned int FrameWidth, unsigned int FrameHeight);
void RMH_ImageConversion_ConvertYUY2ToGrayscaleRGB8(unsigned char* YUY2in, unsigned char* GrayscaleOut, unsigned int FrameWidth, unsigned int FrameHeight);
void RMH_ImageConversion_ConvertRGB24ToGrayscaleRGB24(unsigned char* RGBin, unsigned char* GrayscaleOut, unsigned int FrameWidth,unsigned int FrameHeight);

// -------------- Color Palette Billede Processerings & Konverterings Routiner -------------- //

void RMH_ImageProcessing_ApplyColorPaletteToGrayscaleImageData(unsigned short* Data, unsigned int FrameWidth, unsigned int FrameHeight, unsigned short ColorPalette[3][16384], bool InvertColorPalette, unsigned short* MappedData);
void RMH_ImageProcessing_ApplyOverlayedPaletteToGrayScaleImageData(unsigned short* Data, unsigned short* MappedData, unsigned int FrameWidth, unsigned int FrameHeight, unsigned short BackGroundColorPalette[3][16384], unsigned short OverlayedColorPalette[3][16384], bool InvertBackGroundColorPalette, bool InvertOverlayedColorPalette, unsigned int X0Pos, unsigned int Y0Pos, unsigned int OCPWidth, unsigned int OCPHeight);
void RMH_ImageProcessing_DisplayColorPaletteInPictureBox(unsigned char ColorPalette[3][256], System::Windows::Forms::PictureBox^ PictureBox);
void RMH_ImageProcessing_FormatColorPaletteRangeInsideBackgroundPalette(unsigned short MainPalette[3][16384], bool MainPaletteInvertFlag, bool AdaptFullPaletteWithinRange, unsigned short BackPalette[3][16384], bool BackPaletteInvertFlag, unsigned short MainPaletteMaxRange, unsigned short MainPaletteMinRange, unsigned short(*OutputPalette)[16384]);

// ----------------------------- Billede Processerings Routiner ----------------------------- //

void RMH_ImageProcessing_LinearAutomaticGainControlRaw(unsigned short* ThermalData, unsigned short* GainGrayscale, unsigned int FrameWidth, unsigned int FrameHeight, double MaxOutPixelVal, double MinOutPixelVal, double MaxInPixelVal, double MinInPixelVal);
unsigned char RMH_ImageProcessing_GetKernelPixelOverlayPixelValue(unsigned char* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, float XPos, float YPos);

// --- Gaussian Billede Filtrerings Processering --->

void RMH_ImageProcessing_2DGaussian3x3KernelBlur(unsigned char* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char* BluredImage);

// --- Unsharp Mask Billede Sharpenning Processering --->

bool RMH_ImageProcessing_GenerateUnsharpKernelMask(unsigned char KernelMaskSize, float Sigma, float* KernelMaskPointer);
void RMH_ImageProcessing_2DUnsharpMaskKernelImageSharpening(unsigned short* ImageData, unsigned int ImageResolution, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char KernelMaskSize, float* KernelMaskPointer, float SharpeningStrength, bool OutputUnsharpMaskFlag, unsigned short* SharpenedImage);

// --- Laplacian Billede Sharpening Processering --->

void RMH_ImageProcessing_LaplacianImageSharpening(unsigned char* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char KernelMask, float SharpeningStreangth, bool ShowFilteredMaks, unsigned char* SharpenedImage);

// --- Billede Median Filtrerings Processering --->

void RMH_ImageProcessing_ImageMedianFiltering(unsigned char* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned char* MedianFilteredImage);

// --- Billede 2D Interpolation Processering --->

void RMH_ImageProcessing_2DBilinearInterpolation(unsigned short* ImageData, unsigned int ImageDataWidth, unsigned int ImageDataHeight, unsigned int InterpolatedImageWidth, unsigned int InterpolatedImageHeight, unsigned short* InterpolatedImage);

// ------------------------------------------------------------------------------------------ //

#endif /* RMH_ImageProcessing_Library_H */
