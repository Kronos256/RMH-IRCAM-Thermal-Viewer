
/*
 *  Main.cpp
 *
 *  Author: Rune Mark Hansen
 *  Start Date: April 2023
 *  Opdaterede: 25-09-2026
 * 
 *  TODO:
 * 
 *    Ideer ->
 *   
 *    Store Opgaver ->
 * 	
 *		- Opdater Histogram Til PBO OpenGL
 *		- Opdater LiveView Snapshot Funktionalitet (BITMAP)
 *		- Opdater Temperatur Alarm Funktionalitet
 *      - Opdater Periodisk Trigger Funktionalitet
 *		- Test Ny 2D Plot Hastighed!
 *		- Hvis Surface Plot Formen er Undocked Med 2D Plot Formen Undocked, så kan Surface Plot Line Mode Ikke Ændres?
 *		- Opdater Applikation Med Hurtigere Surface Plot Med Vertex Arrays mm
 *      - Opdater Applikation Til At benytte Nye, Moderne Og Hurtigere OpenGL Rengerering.
 * 
 *    Medium Opgaver ->
 *   
 *    Små Opgaver ->
 *		
 *		- Tilføj alarm "Nulstil Event Trigger" som en periodisk trigger mulighed
 *		- Gem Sessionens Live View Roterings Indstilling 
 *		- Tilføj TNV256i Kamera
 *		- Tilføj HT203U Kamera (Tiny1-C Sensor)
 *		- Tilføj HIKMICRO Mini2Plus
 *      - Tilføj TOOLTOP T7 Kamera (Test Om P2/Pro Variant...)
 * 
 *    Fundet Fejl, Eller Kontroller Feature ->
 * 
 *		- Recording Analysis Mode - High Range Problem!!
 *		- High Range Look-up tabel for T2S+_V2 matcher ikke (Kontroller Udregninger) (Muligvis Grundet & 0x3FFF i linjen: TemperatureLookUpTabel[PixelValue & 0x3FFF])
 *		- Find Ud af hvordan man trigger en shutter kalibrering for InfiRay P2/P2Pro (Pool 2 kameraer)
 *		- Find Ud af hvordan man skifter temperatur Range for InfiRay P2/P2Pro (Pool 2 kameraer)
 * 
 *    Er Fixet Eller Tilføjet -> 
 * 
 *	  SKAL KONTROLLERES FØRST!
 *		- Kontroller Snapshot Temperatur Data For P2 Kameraer
 *		- HIGH Range For T2 V2 Kamera Serier 
 * 
 *      
 *		 
 */

// Deaktiver applikations Console
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

// Inkluderede Blblioteker
#include "MainGUI.h"
#include "SplashScreen.h"

// Globale namespaces
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace IRCAMThermalViewer;
using namespace std;
[STAThreadAttribute]

void main() {

	// Aktiver Applikationens Visual stil render
	System::Windows::Forms::Application::EnableVisualStyles();
	// Applicationen Benytter den globale default Text render 
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

	// Vis Start Splash Screen
	System::Windows::Forms::Application::Run(gcnew SplashScreen());
	// Start Main GUI applikation
	System::Windows::Forms::Application::Run(gcnew MainGUI());

}
