
/*
 *  RMH_CustomColorPalette_Resources.h
 *
 *  Author: Rune Mark Hansen
 *  Date: Match 2023
 *
 */

#pragma once

// RMH_CustomColorPalette_Resources.h
#ifndef RMH_CustomColorPalette_Resources_H 
#define RMH_CustomColorPalette_Resources_H

// --------------------- Tilgængelige Temperatur Plot Data Sæt Sources ---------------------- //

// 2D Plot Maximale Antal Data Sæt Macro
#define _2DPlotMaxNumberOfDataSets              10

// 2D Plot Data Sæt Macroer
#define _2DPlotDataSet_1                        0
#define _2DPlotDataSet_2                        1
#define _2DPlotDataSet_3                        2
#define _2DPlotDataSet_4                        3
#define _2DPlotDataSet_5                        4
#define _2DPlotDataSet_6                        5
#define _2DPlotDataSet_7                        6
#define _2DPlotDataSet_8                        7
#define _2DPlotDataSet_9                        8
#define _2DPlotDataSet_10                       9

// 2D Plot Data Set Source Index Macroer
#define _2DPlotDataSource_MaximumTemp			0
#define _2DPlotDataSource_MinimumTemp			1
#define _2DPlotDataSource_AverageTemp			2
#define _2DPlotDataSource_CenterTemp			3
#define _2DPlotDataSource_TempPoint1			4
#define _2DPlotDataSource_TempPoint2			5
#define _2DPlotDataSource_TempPoint3			6
#define _2DPlotDataSource_TempPoint4			7
#define _2DPlotDataSource_TempPoint5			8 
#define _2DPlotDataSource_TempPoint6			9
#define _2DPlotDataSource_TempPoint7			10
#define _2DPlotDataSource_TempPoint8			11
#define _2DPlotDataSource_TempPoint9			12
#define _2DPlotDataSource_TempPoint10			13
#define _2DPlotDataSource_Line1MaxTemp			14 
#define _2DPlotDataSource_Line1MinTemp			15
#define _2DPlotDataSource_Line1AvgTemp			16
#define _2DPlotDataSource_Line2MaxTemp			17
#define _2DPlotDataSource_Line2MinTemp			18
#define _2DPlotDataSource_Line2AvgTemp			19
#define _2DPlotDataSource_Line3MaxTemp			20
#define _2DPlotDataSource_Line3MinTemp			21
#define _2DPlotDataSource_Line3AvgTemp			22
#define _2DPlotDataSource_Line4MaxTemp			23
#define _2DPlotDataSource_Line4MinTemp			24
#define _2DPlotDataSource_Line4AvgTemp			25
#define _2DPlotDataSource_Line5MaxTemp			26
#define _2DPlotDataSource_Line5MinTemp			27
#define _2DPlotDataSource_Line5AvgTemp			28
#define _2DPlotDataSource_ROI1MaxTemp			29
#define _2DPlotDataSource_ROI1MinTemp			30
#define _2DPlotDataSource_ROI1AvgTemp			31
#define _2DPlotDataSource_ROI2MaxTemp			32
#define _2DPlotDataSource_ROI2MinTemp			33
#define _2DPlotDataSource_ROI2AvgTemp			34
#define _2DPlotDataSource_ROI3MaxTemp			35
#define _2DPlotDataSource_ROI3MinTemp			36
#define _2DPlotDataSource_ROI3AvgTemp			37
#define _2DPlotDataSource_ROI4MaxTemp			38
#define _2DPlotDataSource_ROI4MinTemp			39
#define _2DPlotDataSource_ROI4AvgTemp			40
#define _2DPlotDataSource_ROI5MaxTemp			41
#define _2DPlotDataSource_ROI5MinTemp			42
#define _2DPlotDataSource_ROI5AvgTemp			43
#define _2DPlotDataSource_ROI6MaxTemp			44 
#define _2DPlotDataSource_ROI6MinTemp			45
#define _2DPlotDataSource_ROI6AvgTemp			46
#define _2DPlotDataSource_ROI7MaxTemp			47
#define _2DPlotDataSource_ROI7MinTemp			48
#define _2DPlotDataSource_ROI7AvgTemp			49
#define _2DPlotDataSource_ROI8MaxTemp			50
#define _2DPlotDataSource_ROI8MinTemp			51
#define _2DPlotDataSource_ROI8AvgTemp			52
#define _2DPlotDataSource_ROI9MaxTemp			53
#define _2DPlotDataSource_ROI9MinTemp			54
#define _2DPlotDataSource_ROI9AvgTemp			55
#define _2DPlotDataSource_ROI10MaxTemp			56
#define _2DPlotDataSource_ROI10MinTemp			57
#define _2DPlotDataSource_ROI10AvgTemp			58
#define _2DPlotDataSource_MousePositionTemp		59
#define _2DPlotDataSource_ThermalSensorDrift    60

// Tilgængelige 2D PLot Data Set Sources Navne Strings ->
static std::vector<std::string> PlorDataSetSources = { "Maximum Temp",
													   "Minimum Temp", 
													   "Average Temp",
													   "Center Temp",
													   "Temp Point 1",
													   "Temp Point 2",
													   "Temp Point 3",
													   "Temp Point 4",
													   "Temp Point 5",
													   "Temp Point 6",
													   "Temp Point 7",
													   "Temp Point 8",
													   "Temp Point 9",
													   "Temp Point 10",
													   "Line 1 Max Temp",
													   "Line 1 Min Temp",
													   "Line 1 Avg Temp",
													   "Line 2 Max Temp",
													   "Line 2 Min Temp",
													   "Line 2 Avg Temp",
													   "Line 3 Max Temp",
													   "Line 3 Min Temp",
													   "Line 3 Avg Temp",
													   "Line 4 Max Temp",
													   "Line 4 Min Temp",
													   "Line 4 Avg Temp",
													   "Line 5 Max Temp",
													   "Line 5 Min Temp",
													   "Line 5 Avg Temp",
													   "ROI 1 Max Temp",
													   "ROI 1 Min Temp",
													   "ROI 1 Avg Temp",
													   "ROI 2 Max Temp",
													   "ROI 2 Min Temp",
													   "ROI 2 Avg Temp",
													   "ROI 3 Max Temp",
													   "ROI 3 Min Temp",
													   "ROI 3 Avg Temp",
													   "ROI 4 Max Temp",
													   "ROI 4 Min Temp",
													   "ROI 4 Avg Temp",
													   "ROI 5 Max Temp",
													   "ROI 5 Min Temp",
													   "ROI 5 Avg Temp",
													   "ROI 6 Max Temp",
													   "ROI 6 Min Temp",
													   "ROI 6 Avg Temp",
													   "ROI 7 Max Temp",
													   "ROI 7 Min Temp",
													   "ROI 7 Avg Temp",
													   "ROI 8 Max Temp",
													   "ROI 8 Min Temp",
													   "ROI 8 Avg Temp",
													   "ROI 9 Max Temp",
													   "ROI 9 Min Temp",
													   "ROI 9 Avg Temp",
													   "ROI 10 Max Temp",
													   "ROI 10 Min Temp",
													   "ROI 10 Avg Temp",
													   "Mouse Position Temp", 
												       "Thermal Sensor Drift"};

// ------------------------------------------------------------------------------------------ //

#endif /* RMH_CustomColorPalette_Resources_H */
