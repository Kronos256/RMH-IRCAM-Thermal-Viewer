
/*
 *  RMH_Application_ColorBarAndPalette.cpp
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

// Inkluderede Biblioteker
#include "RMH_Application_ColorBarAndPalette.h"
#include "RMH_ThermalCameraSupport_Library.h"
#include "RMH_ImageProcessing_Library.h"
#include "RMH_Winforms_Library.h"
#include <iostream>

// Inkluderede Resourcer
#include "GlobalObjectsAndVariables.h"
#include "RMH_CustomColorPalette_Resources.h"

// Globale Namespaces
using namespace System;
using namespace std;

// --------------------------- Color Palette Håndterings Routiner --------------------------- //

void RMH_ColorPalette_LoadColorPalettesToCombiBox(System::Windows::Forms::ComboBox^ ColorPaletteComboBox) {

	// Routinen loader tilgængelige Color Palette navne, fra resourcer, til tilhørende CombiBox

	// Indsæt listen over de tilgængelige Color Palettes i "Color Palette" ComboBox
	RMH_Winforms_CombiBox_AddArrayOfItemStrings(ColorPaletteComboBox, ColorPaletteNames);

}

void RMH_ColorPalette_ChangeColorPalette(System::Windows::Forms::ComboBox^ ColorPaletteComboBox) {

	// Routinen indstiller valgte Color Palette til Live View Picture Boxen

	// Læs valgte Color Palette
	unsigned int ColorPaletteIndex = ColorPaletteComboBox->SelectedIndex;

	// Indstilling af valgte Color Palette
	switch (ColorPaletteIndex) {

		// Color Palette: Parula
		case _ColorPaletteIndex_Parula:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Parula;

		break;

		// Color Palette: Turbo
		case _ColorPaletteIndex_Turbo:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Turbo;

		break;

		// Color Palette: Jet
		case _ColorPaletteIndex_Jet:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Jet;

		break;

		// Color Palette: HSV
		case _ColorPaletteIndex_HSV:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_HSV;

		break;

		// Color Palette: Hot
		case _ColorPaletteIndex_Hot:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Hot;

		break;

		// Color Palette: Cool
		case _ColorPaletteIndex_Cool:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Cool;

		break;

		// Color Palette: Spring
		case _ColorPaletteIndex_Spring:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Spring;

		break;

		// Color Palette: Summer
		case _ColorPaletteIndex_Summer:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Summer;

		break;

		// Color Palette: Autumn
		case _ColorPaletteIndex_Autumn:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Autumn;

		break;

		// Color Palette: Winter
		case _ColorPaletteIndex_Winter:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Winter;

		break;

		// Color Palette: Gray
		case _ColorPaletteIndex_Gray:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Gray;

		break;

		// Color Palette: Bone
		case _ColorPaletteIndex_Bone:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Bone;

		break;

		// Color Palette: Copper
		case _ColorPaletteIndex_Copper:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Copper;

		break;

		// Color Palette: Pink
		case _ColorPaletteIndex_Pink:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Pink;

		break;

		// Color Palette: Custom DarkHot
		case _ColorPaletteIndex_DarkHot:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_DarkHot;

		break;

		// Color Palette: Custom ColdSpot
		case _ColorPaletteIndex_ColdSpot:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_ColdSpot;

		break;

		// Color Palette: Custom ColdHotSpot
		case _ColorPaletteIndex_ColdHotSpot:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_ColdHotSpot;

		break;

		// Color Palette: Custom BlackRed
		case _ColorPaletteIndex_BlackRed:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_BlackRed;

		break;

		// Color Palette: Custom Inferno
		case _ColorPaletteIndex_Inferno:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Inferno;

		break;

		// Color Palette: Custom Magma
		case _ColorPaletteIndex_Magma:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Magma;

		break;

		// Color Palette: Custom Plasma
		case _ColorPaletteIndex_Plasma:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Plasma;

		break;

		// Color Palette: Custom Lava
		case _ColorPaletteIndex_Lava:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Lava;

		break;

		// Color Palette: Custom LavaHT
		case _ColorPaletteIndex_LavaHT:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_LavaHT;

		break;

		// Color Palette: Custom InfiRay
		case _ColorPaletteIndex_InfiRay:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_InfiRay;

		break;

		// Color Palette: Custom BowHC
		case _ColorPaletteIndex_BowHC:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_BowHC;

		break;

		// Color Palette: Custom RainHC
		case _ColorPaletteIndex_RainHC:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_RainHC;

		break;

		// Color Palette: Custom RainHT
		case _ColorPaletteIndex_RainHT:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_RainHT;

		break;

		// Color Palette: Custom Iron
		case _ColorPaletteIndex_Iron:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Iron;

		break;

		// Color Palette: Custom Viridis
		case _ColorPaletteIndex_Viridis:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Viridis;

		break;

		// Color Palette: Custom Tesla
		case _ColorPaletteIndex_Tesla:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Tesla;

		break;

		// Color Palette: Custom Helix
		case _ColorPaletteIndex_Helix:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Helix;

		break;

		// Color Palette: Custom Grey10
		case _ColorPaletteIndex_Grey10:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Grey10;

		break;

		// Color Palette: Custom GreyRed
		case _ColorPaletteIndex_GreyRed:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_GreyRed;

		break;

		// Color Palette: Custom Iron10
		case _ColorPaletteIndex_Iron10:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Iron10;

		break;

		// Color Palette: Custom Medical
		case _ColorPaletteIndex_Medical1:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Medical1;

		break;

		// Color Palette: Custom Medical
		case _ColorPaletteIndex_Medical2:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Medical2;

		break;

		// Color Palette: Custom MIdGrey
		case _ColorPaletteIndex_MidGrey:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_MidGrey;

		break;

		// Color Palette: Custom Prism
		case _ColorPaletteIndex_Prism:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Prism;

		break;

		// Color Palette: Custom Rain
		case _ColorPaletteIndex_Rain:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Rain;

		break;

		// Color Palette: Custom Rain10
		case _ColorPaletteIndex_Rain10:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Rain10;

		break;

		// Color Palette: Custom DarkRed
		case _ColorPaletteIndex_DarkRed:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_DarkRed;

		break;

		// Color Palette: Custom Lambda
		case _ColorPaletteIndex_Lambda:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Lambda;

		break;

		// Color Palette: Custom AllWhite
		case _ColorPaletteIndex_AllWhite:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_AllWhite;

		break;

		// Color Palette: Custom AllBlack
		case _ColorPaletteIndex_AllBlack:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_AllBlack;

		break;

		// Color Palette: Custom InfernoEX
		case _ColorPaletteIndex_InfernoEX:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_InfernoEX;

		break;

		// Color Palette: Custom IsoRainBow1
		case _ColorPaletteIndex_IsoRainBow1:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_IsoRainBow1;

		break;

		// Color Palette: Custom IsoRainBow2
		case _ColorPaletteIndex_IsoRainBow2:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_IsoRainBow2;

		break;

		// Color Palette: Custom IsoTropic
		case _ColorPaletteIndex_IsoTropic:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_IsoTropic;

		break;

		// Color Palette: Custom UAVFlying
		case _ColorPaletteIndex_UAVFlying:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_UAVFlying;

		break;

		// Color Palette: Custom SpectrumHot
		case _ColorPaletteIndex_SpectrumHot:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_SpectrumHot;

		break;

		// Color Palette: Custom Epsilon
		case _ColorPaletteIndex_Epsilon:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_Epsilon;

		break;

		// Color Palette: Custom EmissivityMap
		case _ColorPaletteIndex_EmissivityMap:

			// Opdater Color Palette Pointer
			ColorPalettePtr = RMH_CustomPalette_EmissivityMap;

		break;

	}

}

void RMH_ColorPalette_ChangeDualColorPalette(System::Windows::Forms::ComboBox^ DualColorPaletteComboBox) {

	// Routinen indstiller valgte Dual Color Palette til Live View Picture Boxen

	// Læs valgte Dual Color Palette
	unsigned int ColorPaletteIndex = DualColorPaletteComboBox->SelectedIndex;

	// Indstilling af valgte Color Palette
	switch (ColorPaletteIndex) {

		// Color Palette: Parula
		case _ColorPaletteIndex_Parula:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Parula;

		break;

		// Color Palette: Turbo
		case _ColorPaletteIndex_Turbo:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Turbo;

		break;

		// Color Palette: Jet
		case _ColorPaletteIndex_Jet:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Jet;

		break;

		// Color Palette: HSV
		case _ColorPaletteIndex_HSV:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_HSV;

		break;

		// Color Palette: Hot
		case _ColorPaletteIndex_Hot:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Hot;

		break;

		// Color Palette: Cool
		case _ColorPaletteIndex_Cool:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Cool;

		break;

		// Color Palette: Spring
		case _ColorPaletteIndex_Spring:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Spring;

		break;

		// Color Palette: Summer
		case _ColorPaletteIndex_Summer:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Summer;

		break;

		// Color Palette: Autumn
		case _ColorPaletteIndex_Autumn:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Autumn;

		break;

		// Color Palette: Winter
		case _ColorPaletteIndex_Winter:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Winter;

		break;

		// Color Palette: Gray
		case _ColorPaletteIndex_Gray:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Gray;

		break;

		// Color Palette: Bone
		case _ColorPaletteIndex_Bone:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Bone;

		break;

		// Color Palette: Copper
		case _ColorPaletteIndex_Copper:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Copper;

		break;

		// Color Palette: Pink
		case _ColorPaletteIndex_Pink:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Pink;

		break;

		// Color Palette: Custom DarkHot
		case _ColorPaletteIndex_DarkHot:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_DarkHot;

		break;

		// Color Palette: Custom ColdSpot
		case _ColorPaletteIndex_ColdSpot:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_ColdSpot;

		break;

		// Color Palette: Custom ColdHotSpot
		case _ColorPaletteIndex_ColdHotSpot:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_ColdHotSpot;

		break;

		// Color Palette: Custom BlackRed
		case _ColorPaletteIndex_BlackRed:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_BlackRed;

		break;

		// Color Palette: Custom Inferno
		case _ColorPaletteIndex_Inferno:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Inferno;

		break;

		// Color Palette: Custom Magma
		case _ColorPaletteIndex_Magma:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Magma;

		break;

		// Color Palette: Custom Plasma
		case _ColorPaletteIndex_Plasma:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Plasma;

		break;

		// Color Palette: Custom Lava
		case _ColorPaletteIndex_Lava:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Lava;

		break;

		// Color Palette: Custom LavaHT
		case _ColorPaletteIndex_LavaHT:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_LavaHT;

		break;

		// Color Palette: Custom InfiRay
		case _ColorPaletteIndex_InfiRay:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_InfiRay;

		break;

		// Color Palette: Custom BowHC
		case _ColorPaletteIndex_BowHC:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_BowHC;

		break;

		// Color Palette: Custom RainHC
		case _ColorPaletteIndex_RainHC:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_RainHC;

		break;

		// Color Palette: Custom RainHT
		case _ColorPaletteIndex_RainHT:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_RainHT;

		break;

		// Color Palette: Custom Iron
		case _ColorPaletteIndex_Iron:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Iron;

		break;

		// Color Palette: Custom Viridis
		case _ColorPaletteIndex_Viridis:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Viridis;

		break;

		// Color Palette: Custom Tesla
		case _ColorPaletteIndex_Tesla:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Tesla;
			 
		break;

		// Color Palette: Custom Helix
		case _ColorPaletteIndex_Helix:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Helix;

		break;

		// Color Palette: Custom Grey10
		case _ColorPaletteIndex_Grey10:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Grey10;

		break;

		// Color Palette: Custom GreyRed
		case _ColorPaletteIndex_GreyRed:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_GreyRed;

		break;

		// Color Palette: Custom Iron10
		case _ColorPaletteIndex_Iron10:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Iron10;

		break;

		// Color Palette: Custom Medical 1
		case _ColorPaletteIndex_Medical1:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Medical1;

		break;

		// Color Palette: Custom Medical 2
		case _ColorPaletteIndex_Medical2:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Medical2;

		break;

		// Color Palette: Custom MIdGrey
		case _ColorPaletteIndex_MidGrey:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_MidGrey;

		break;

		// Color Palette: Custom Prism
		case _ColorPaletteIndex_Prism:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Prism;

		break;

		// Color Palette: Custom Rain
		case _ColorPaletteIndex_Rain:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Rain;

		break;

		// Color Palette: Custom Rain10
		case _ColorPaletteIndex_Rain10:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Rain10;

		break;

		// Color Palette: Custom DarkRed
		case _ColorPaletteIndex_DarkRed:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_DarkRed;

		break;

		// Color Palette: Custom Lambda
		case _ColorPaletteIndex_Lambda:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Lambda;

		break;

		// Color Palette: Custom AllWhite
		case _ColorPaletteIndex_AllWhite:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_AllWhite;

		break;

		// Color Palette: Custom AllBlack
		case _ColorPaletteIndex_AllBlack:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_AllBlack;

		break;

		// Color Palette: Custom InfernoEX
		case _ColorPaletteIndex_InfernoEX:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_InfernoEX;

		break;

		// Color Palette: Custom IsoRainBow1
		case _ColorPaletteIndex_IsoRainBow1:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_IsoRainBow1;

		break;

		// Color Palette: Custom IsoRainBow2
		case _ColorPaletteIndex_IsoRainBow2:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_IsoRainBow2;

		break;

		// Color Palette: Custom IsoTropic
		case _ColorPaletteIndex_IsoTropic:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_IsoTropic;

		break;

		// Color Palette: Custom UAVFlying
		case _ColorPaletteIndex_UAVFlying:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_UAVFlying;

		break;

		// Color Palette: Custom SpectrumHot
		case _ColorPaletteIndex_SpectrumHot:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_SpectrumHot;

		break;

		// Color Palette: Custom Epsilon
		case _ColorPaletteIndex_Epsilon:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_Epsilon;

		break;

		// Color Palette: Custom EmissivityMap
		case _ColorPaletteIndex_EmissivityMap:

			// Opdater Color Palette Pointer
			DualColorPalettePtr = RMH_CustomPalette_EmissivityMap;

		break;

	}

}

void RMH_ColorPalette_ChangeColorBarBackgroundColorPalette(System::Windows::Forms::ComboBox^ ColorBarBackPaletteComboBox) {

	// Routinen indstiller valgte Color Palette som baggrunds palette til colorbaren

	// Læs valgte colorbar baggrunds Color Palette
	unsigned int ColorPaletteIndex = ColorBarBackPaletteComboBox->SelectedIndex;

	// Indstilling af valgte Color Palette
	switch (ColorPaletteIndex) {

		// Color Palette: Parula
		case _ColorPaletteIndex_Parula:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Parula;

		break;

		// Color Palette: Turbo
		case _ColorPaletteIndex_Turbo:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Turbo;

		break;

		// Color Palette: Jet
		case _ColorPaletteIndex_Jet:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Jet;

		break;

		// Color Palette: HSV
		case _ColorPaletteIndex_HSV:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_HSV;

		break;

		// Color Palette: Hot
		case _ColorPaletteIndex_Hot:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Hot;

		break;

		// Color Palette: Cool
		case _ColorPaletteIndex_Cool:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Cool;

		break;

		// Color Palette: Spring
		case _ColorPaletteIndex_Spring:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Spring;

		break;

		// Color Palette: Summer
		case _ColorPaletteIndex_Summer:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Summer;

		break;

		// Color Palette: Autumn
		case _ColorPaletteIndex_Autumn:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Autumn;

		break;

		// Color Palette: Winter
		case _ColorPaletteIndex_Winter:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Winter;

		break;

		// Color Palette: Gray
		case _ColorPaletteIndex_Gray:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Gray;

		break;

		// Color Palette: Bone
		case _ColorPaletteIndex_Bone:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Bone;

		break;

		// Color Palette: Copper
		case _ColorPaletteIndex_Copper:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Copper;

		break;

		// Color Palette: Pink
		case _ColorPaletteIndex_Pink:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Pink;

		break;

		// Color Palette: Custom DarkHot
		case _ColorPaletteIndex_DarkHot:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_DarkHot;

		break;

		// Color Palette: Custom ColdSpot
		case _ColorPaletteIndex_ColdSpot:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_ColdSpot;

		break;

		// Color Palette: Custom ColdHotSpot
		case _ColorPaletteIndex_ColdHotSpot:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_ColdHotSpot;

		break;

		// Color Palette: Custom BlackRed
		case _ColorPaletteIndex_BlackRed:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_BlackRed;

		break;

		// Color Palette: Custom Inferno
		case _ColorPaletteIndex_Inferno:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Inferno;

		break;

		// Color Palette: Custom Magma
		case _ColorPaletteIndex_Magma:
	
			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Magma;

		break;

		// Color Palette: Custom Plasma
		case _ColorPaletteIndex_Plasma:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Plasma;

		break;

		// Color Palette: Custom Lava
		case _ColorPaletteIndex_Lava:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Lava;

		break;

		// Color Palette: Custom LavaHT
		case _ColorPaletteIndex_LavaHT:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_LavaHT;

		break;

		// Color Palette: Custom InfiRay
		case _ColorPaletteIndex_InfiRay:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_InfiRay;

		break;

		// Color Palette: Custom BowHC
		case _ColorPaletteIndex_BowHC:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_BowHC;

		break;

		// Color Palette: Custom RainHC
		case _ColorPaletteIndex_RainHC:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_RainHC;

		break;

		// Color Palette: Custom RainHT
		case _ColorPaletteIndex_RainHT:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_RainHT;

		break;

		// Color Palette: Custom Iron
		case _ColorPaletteIndex_Iron:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Iron;

		break;

		// Color Palette: Custom Viridis
		case _ColorPaletteIndex_Viridis:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Viridis;

		break;

		// Color Palette: Custom Tesla
		case _ColorPaletteIndex_Tesla:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Tesla;

		break;

		// Color Palette: Custom Helix
		case _ColorPaletteIndex_Helix:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Helix;

		break;

		// Color Palette: Custom Grey10
		case _ColorPaletteIndex_Grey10:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Grey10;

		break;

		// Color Palette: Custom GreyRed
		case _ColorPaletteIndex_GreyRed:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_GreyRed;

		break;

		// Color Palette: Custom Iron10
		case _ColorPaletteIndex_Iron10:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Iron10;

		break;

		// Color Palette: Custom Medical 1
		case _ColorPaletteIndex_Medical1:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Medical1;

		break;

		// Color Palette: Custom Medical 2
		case _ColorPaletteIndex_Medical2:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Medical2;

			break;

		// Color Palette: Custom MIdGrey
		case _ColorPaletteIndex_MidGrey:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_MidGrey;

		break;

		// Color Palette: Custom Prism
		case _ColorPaletteIndex_Prism:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Prism;

		break;

		// Color Palette: Custom Rain
		case _ColorPaletteIndex_Rain:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Rain;

		break;

		// Color Palette: Custom Rain10
		case _ColorPaletteIndex_Rain10:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Rain10;

		break;

		// Color Palette: Custom DarkRed
		case _ColorPaletteIndex_DarkRed:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_DarkRed;

		break;

			// Color Palette: Custom Lambda
		case _ColorPaletteIndex_Lambda:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Lambda;

		break;

		// Color Palette: Custom AllWhite
		case _ColorPaletteIndex_AllWhite:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_AllWhite;

		break;

			// Color Palette: Custom AllBlack
		case _ColorPaletteIndex_AllBlack:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_AllBlack;

		break;

		// Color Palette: Custom InfernoEX
		case _ColorPaletteIndex_InfernoEX:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_InfernoEX;

		break;

		// Color Palette: Custom IsoRainBow1
		case _ColorPaletteIndex_IsoRainBow1:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_IsoRainBow1;

		break;

		// Color Palette: Custom IsoRainBow2
		case _ColorPaletteIndex_IsoRainBow2:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_IsoRainBow2;

		break;

		// Color Palette: Custom IsoTropic
		case _ColorPaletteIndex_IsoTropic:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_IsoTropic;

		break;

		// Color Palette: Custom UAVFlying
		case _ColorPaletteIndex_UAVFlying:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_UAVFlying;

		break;

		// Color Palette: Custom SpectrumHot
		case _ColorPaletteIndex_SpectrumHot:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_SpectrumHot;

		break;

		// Color Palette: Custom Epsilon
		case _ColorPaletteIndex_Epsilon:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_Epsilon;

		break;

		// Color Palette: Custom EmissivityMap
		case _ColorPaletteIndex_EmissivityMap:

			// Opdater Color Palette Pointer
			ColorBarBackPalettePtr = RMH_CustomPalette_EmissivityMap;

		break;

	}

}

void RMH_ColorPalette_EnableDualColorPalettes(System::Windows::Forms::Button^ DualColorPaletteButton) {

	// Routinen Håndterer event ved aktivering af Dual live View Color Palettes

	// Skal Dual Color Palette aktiveres eller deaktiveres
	if (DualColorPaletteEnableFlag == true) {

		// Opdater Dual Color Palette Knap Border Farve
		DualColorPaletteButton->FlatAppearance->BorderColor = System::Drawing::Color::Lime;

	}
	else {

		// Nulstil Dual Color Palette Knap Border Farve
		DualColorPaletteButton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(255, 40, 40, 40);

	}

	// Opdater Dual Color Palette Knap grafik
	DualColorPaletteButton->Refresh();

}

void RMH_ColorPalette_UpdateHistogramColorPaletteInvertionState() {

	// Routinen opdaterer histogrammets color palettes inverterings stadie

	// Kontroller hvilken color palette som histogrammet benytter
	// Hvis histogrammet color palette er indstillet som Dual Color paletten
	if (HistogramDualOrLiveViewPaletteFlag == true) {

		// Skal Dual color paletten inverteres for Histogrammet
		if (InvertLiveViewDualPaletteFlag == true) {

			// Opdater histogrammets color palette inverterings flag 
			GlobalVariables::OpenGLHistogram->RMH_OpenGL_InvertHistogramColorPalette(true);

		}
		else {

			// Opdater histogrammets color palette inverterings flag 
			GlobalVariables::OpenGLHistogram->RMH_OpenGL_InvertHistogramColorPalette(false);

		}

	}
	else {

		// Skal Live view color paletten inverteres for Histogrammet
		if (InvertLiveViewPaletteFlag == true) {

			// Opdater histogrammets color palette inverterings flag 
			GlobalVariables::OpenGLHistogram->RMH_OpenGL_InvertHistogramColorPalette(true);

		}
		else {

			// Opdater histogrammets color palette inverterings flag 
			GlobalVariables::OpenGLHistogram->RMH_OpenGL_InvertHistogramColorPalette(false);

		}

	}

}

void RMH_ColorPalette_InvertColorPalettes(System::Object^ sender) {

	// Routinen opdaterer det inverterede stadie for en valgt color palette

	// Cast Sender objekt som Forms ToolStripMenuItem objekt
	System::Windows::Forms::ToolStripMenuItem^ InvertMenuItem = (System::Windows::Forms::ToolStripMenuItem^)sender;

	// Læs Tool Strip Menuens identifikations tag
	unsigned int InvertMenuItemTag = Convert::ToInt32(InvertMenuItem->Tag);

	// Hvilken color palette skal inverteres
	switch (InvertMenuItemTag) {

		// Inveter valgte color palette
		case 0: InvertLiveViewPaletteFlag = !InvertLiveViewPaletteFlag;						break;
		case 1: InvertLiveViewDualPaletteFlag = !InvertLiveViewDualPaletteFlag;				break;
		case 2: InvertColorBarBackgroundPaletteFlag = !InvertColorBarBackgroundPaletteFlag; break;

	}

	// Opdater histogrammets color palette inverterings stadie
	RMH_ColorPalette_UpdateHistogramColorPaletteInvertionState();

	// Opdater Colorbarens paletters inverterings stadier 
	GlobalVariables::OpenGLColorBar->RMH_OpenGL_InvertColorBarPalettes(InvertLiveViewPaletteFlag, InvertLiveViewDualPaletteFlag);

}

// -------------------------- Color Bar Panel Håndterings Routiner -------------------------- //

void RMH_ColorBar_ChangeManualRangeMouseWheelStepSize(System::Object^ sender) {

	// Routinen indstiller colorbarens Mus Wheel temperatur Step størrelse

	// Lokale variabler
	float MouseWheelStepSize = 0.0;

	// Cast Sender objekt som Forms Tool Strip objekt
	System::Windows::Forms::ToolStripMenuItem^ MenuStripIndex = (System::Windows::Forms::ToolStripMenuItem^)sender;

	// Læs Sub Context Menu identifikations tag
	unsigned int IndexTag = Convert::ToInt32(MenuStripIndex->Tag);

	// Opdater til valgte Step Størrelse
	switch (IndexTag) {

		// Konfigurer Step Størrelse
		case 1: MouseWheelStepSize = 10.0; break;
		case 2: MouseWheelStepSize = 5.0;  break;
		case 3: MouseWheelStepSize = 1.0;  break;
		case 4: MouseWheelStepSize = 0.5;  break;
		case 5: MouseWheelStepSize = 0.2;  break;
		case 6: MouseWheelStepSize = 0.1;  break;

	}

	// Opdater colorbarens Mus Wheel temperatur Step størrelse
	GlobalVariables::OpenGLColorBar->RMH_OpenGL_SetMouseWheelTempOffsetStepSize(MouseWheelStepSize);

}

void RMH_ColorBar_ChangeColorBarAmountOfTemperatureTick(System::Object^ sender) {

	// Routinen indstiller antallet af colorbar temperatur ticks til nogle faste værdier

	// Lokale variabler
	unsigned char ColorBarTempTicks = 0;

	// Cast Sender objekt som Forms Tool Strip objekt
	System::Windows::Forms::ToolStripMenuItem^ MenuStripIndex = (System::Windows::Forms::ToolStripMenuItem^)sender;

	// Læs Sub Context Menu identifikations tag
	unsigned int IndexTag = Convert::ToInt32(MenuStripIndex->Tag);

	// Opdater til valgte antal ticks
	switch (IndexTag) {

		// Konfigurer Step Størrelse
		case 1: ColorBarTempTicks = 5;  break;
		case 2: ColorBarTempTicks = 10; break;
		case 3: ColorBarTempTicks = 15; break;
		case 4: ColorBarTempTicks = 20; break;

	}

	// Opdater colorbarens antal af temperatur ticks
	NmbOfColorBarTempTicks = ColorBarTempTicks;

}

// ------------------------------------------------------------------------------------------ //
