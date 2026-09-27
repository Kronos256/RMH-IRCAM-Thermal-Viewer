
/*
 *  RMH_Application_ColorBarAndPalette.h
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

#pragma once

// RMH_Application_ColorBarAndPalette.h
#ifndef RMH_Application_ColorBarAndPalette_H 
#define RMH_Application_ColorBarAndPalette_H

// --------------------------- Color Palette Håndterings Routiner --------------------------- //

void RMH_ColorPalette_LoadColorPalettesToCombiBox(System::Windows::Forms::ComboBox^ ColorPaletteComboBox);
void RMH_ColorPalette_ChangeColorPalette(System::Windows::Forms::ComboBox^ ColorPaletteComboBox);
void RMH_ColorPalette_ChangeDualColorPalette(System::Windows::Forms::ComboBox^ DualColorPaletteComboBox);
void RMH_ColorPalette_ChangeColorBarBackgroundColorPalette(System::Windows::Forms::ComboBox^ ColorBarBackPaletteComboBox);
void RMH_ColorPalette_EnableDualColorPalettes(System::Windows::Forms::Button^ DualColorPaletteButton);
void RMH_ColorPalette_UpdateHistogramColorPaletteInvertionState();
void RMH_ColorPalette_InvertColorPalettes(System::Object^ sender);

// -------------------------- Color Bar Panel Håndterings Routiner -------------------------- //

void RMH_ColorBar_ChangeManualRangeMouseWheelStepSize(System::Object^ sender);
void RMH_ColorBar_ChangeColorBarAmountOfTemperatureTick(System::Object^ sender);

// ------------------------------------------------------------------------------------------ //

#endif /* RMH_Application_ColorBarAndPalette_H */