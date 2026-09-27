
/*
 *  RMH_EmissivityTable_Resources.h
 *
 *  Author: Rune Mark Hansen
 *  Date: Match 2023
 *
 */

#pragma once

// RMH_EmissivityTable_Resources.h
#ifndef RMH_EmissivityTable_Resources_H 
#define RMH_EmissivityTable_Resources_H

// Emissivity Tabel Konfigurations Macroer
#define _EmissivityTableNumberOfElements		77

// ---------------------- Emissivity Tabel Matriale String Navne Array ---------------------- //

// Emissivity Tabellens Header overskrift strings ->
static std::vector<std::string> EmissivityTableHeaderStrings = { "Type Of Material:",
																 "Emissivity Value:" };

// Tilgængelige Applikations Color Palettes navne ->
static std::vector<std::string> EmissivityMaterialNames = { "Camera Default",
															"Perfect BlackBody",
															"Aluminum, Polished",
															"Aluminum, Rough Surface",
															"Aluminum, Strongly Oxidized",
															"Asbestos Board",
															"Asbestos Fabric",
															"Asbestos Paper",
															"Asbestos Slate",
															"Brass, Dull, Tarnished",
															"Brass, Polished",
															"Brick, Common",
															"Brick, Glazed, Rough",
															"Brick, Refractory, Rough",
															"Bronze, Porous, Rough",
															"Bronze, Polished",
															"Carbon, Purified",
															"Cast Iron, Rough Casting",
															"Cast Iron, Polished",
															"Charcoal, Powdered",
															"Chromium, Polished",
															"Clay, Fired",
															"Concrete",
															"Copper, Polished",
															"Copper, Commercial Burnished",
															"Copper, Oxidized",
															"Copper, Oxidized To Black",
															"Electrical Tape, Black Plastic",
															"Enamel",
															"Formica",
															"Frozen Soil",
															"Glass",
															"Glass, Frosted",
															"Gold, Polished",
															"Ice",
															"Iron, Hot Rolled",
															"Iron, Oxidized",
															"Iron, Sheet Galvanized, Burnished",
															"Iron, Sheet, Galvanized, Oxidized",
															"Iron, Shiny, Etched",
															"Iron, Wrought, Polished",
															"Lacquer, Bakelite",
															"Lacquer, Black, Dull",
															"Lacquer, Black, Shiny",
															"Lacquer, White",
															"Lampblack",
															"Lead, Gray",
															"Lead, Oxidized",
															"Lead, Red, Powdered",
															"Lead, Shiny",
															"Mercury, Pure",
															"Nickel, On Cast Iron",
															"Nickel, Pure Polished",
															"Paint, Silver Finish",
															"Paint, Oil, Average",
															"Paper, Black, Shiny",
															"Paper, Black, Dull ",
															"Paper, White",
															"Platinum, Pure, Polished",
															"Porcelain, Glazed",
															"Quartz",
															"Rubber",
															"Shellac, Black, Dull",
															"Shellac, Black, Shiny",
															"Snow",
															"Steel, Galvanized",
															"Steel, Oxidized Strongly",
															"Steel, Rolled Freshly ",
															"Steel, Rough Surface",
															"Steel, Rusty Red",
															"Steel, Sheet, Nickelplated",
															"Steel, Sheet, Rolled",
															"Tar Paper",
															"Tin, Burnished",
															"Tungsten",
															"Water",
															"Zinc, Sheet" };

// Tilhørende Emissivity Værdier For Matrialer
static float MaterialEmissivityValues[77] = { 0.98, 1.00, 0.05, 0.07, 0.25, 0.96, 0.78, 0.94, 0.96, 
											  0.22, 0.03, 0.85, 0.85, 0.94, 0.55, 0.10, 0.80, 0.81, 
											  0.21, 0.96, 0.10, 0.91, 0.54, 0.01, 0.07, 0.65, 0.88, 
											  0.95, 0.90, 0.93, 0.93, 0.92, 0.96, 0.02, 0.97, 0.77, 
											  0.74, 0.23, 0.28, 0.16, 0.28, 0.93, 0.97, 0.87, 0.87, 
											  0.96, 0.28, 0.63, 0.93, 0.08, 0.10, 0.05, 0.05, 0.31, 
											  0.94, 0.90, 0.94, 0.90, 0.08, 0.92, 0.93, 0.93, 0.91, 
											  0.82, 0.80, 0.28, 0.88, 0.24, 0.96, 0.69, 0.11, 0.56, 
											  0.92, 0.05, 0.05, 0.98, 0.20 };

// ------------------------------------------------------------------------------------------ //


#endif /* RMH_EmissivityTable_Resources_H */
