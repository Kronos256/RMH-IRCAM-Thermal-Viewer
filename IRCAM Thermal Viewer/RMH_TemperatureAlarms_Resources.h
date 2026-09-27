
/*
 *  RMH_TemperatureAlarms_Resources.h
 *
 *  Author: Rune Mark Hansen
 *  Date: Match 2023
 *
 */

#pragma once

// RMH_TemperatureAlarms_Resources.h
#ifndef RMH_TemperatureAlarms_Resources_H 
#define RMH_TemperatureAlarms_Resources_H

// --------------------- Tilgængelige Temperatur Alarmers Resource Data --------------------- //

// Maksimale antal konfigurerbare Temperatur Alarmer
#define _MaxNumberOfConfigurableTempAlarms         5

// Temperatur Alarm Nummer Macroer
#define _TemperatureAlarm_1                        0
#define _TemperatureAlarm_2                        1
#define _TemperatureAlarm_3                        2
#define _TemperatureAlarm_4                        3
#define _TemperatureAlarm_5                        4

// Temperatur Alarm Source Index Macroer
#define _TempAlarmDataSource_MaximumTemp			0
#define _TempAlarmDataSource_MinimumTemp			1
#define _TempAlarmDataSource_AverageTemp			2
#define _TempAlarmDataSource_CenterTemp			    3
#define _TempAlarmDataSource_TempPoint1			    4
#define _TempAlarmDataSource_TempPoint2			    5
#define _TempAlarmDataSource_TempPoint3			    6
#define _TempAlarmDataSource_TempPoint4			    7
#define _TempAlarmDataSource_TempPoint5			    8 
#define _TempAlarmDataSource_TempPoint6			    9
#define _TempAlarmDataSource_TempPoint7			    10
#define _TempAlarmDataSource_TempPoint8			    11
#define _TempAlarmDataSource_TempPoint9			    12
#define _TempAlarmDataSource_TempPoint10			13
#define _TempAlarmDataSource_Line1MaxTemp			14 
#define _TempAlarmDataSource_Line1MinTemp			15
#define _TempAlarmDataSource_Line2MaxTemp			16
#define _TempAlarmDataSource_Line2MinTemp			17
#define _TempAlarmDataSource_Line3MaxTemp			18
#define _TempAlarmDataSource_Line3MinTemp			19
#define _TempAlarmDataSource_Line4MaxTemp			20
#define _TempAlarmDataSource_Line4MinTemp			21
#define _TempAlarmDataSource_Line5MaxTemp			22
#define _TempAlarmDataSource_Line5MinTemp			23
#define _TempAlarmDataSource_ROI1MaxTemp			24
#define _TempAlarmDataSource_ROI1MinTemp			25
#define _TempAlarmDataSource_ROI2MaxTemp			26
#define _TempAlarmDataSource_ROI2MinTemp			27
#define _TempAlarmDataSource_ROI3MaxTemp			28
#define _TempAlarmDataSource_ROI3MinTemp			29
#define _TempAlarmDataSource_ROI4MaxTemp			30
#define _TempAlarmDataSource_ROI4MinTemp			31 
#define _TempAlarmDataSource_ROI5MaxTemp			32
#define _TempAlarmDataSource_ROI5MinTemp			33
#define _TempAlarmDataSource_ROI6MaxTemp			34 
#define _TempAlarmDataSource_ROI6MinTemp			35
#define _TempAlarmDataSource_ROI7MaxTemp			36
#define _TempAlarmDataSource_ROI7MinTemp			37
#define _TempAlarmDataSource_ROI8MaxTemp			38
#define _TempAlarmDataSource_ROI8MinTemp			39
#define _TempAlarmDataSource_ROI9MaxTemp			40
#define _TempAlarmDataSource_ROI9MinTemp			41
#define _TempAlarmDataSource_ROI10MaxTemp			42
#define _TempAlarmDataSource_ROI10MinTemp			43
#define _TempAlarmDataSource_MousePositionTemp		44

// Temperatur Alarm konfigurations type Macroer
#define _TempAlarmType_Above                        0
#define _TempAlarmType_Below                        1
#define _TempAlarmType_Window                       2

// Temperatur alarmers trigger aktion konfigurations Macroer
#define _TempAlarmTriggerAction_None                    0    
#define _TempAlarmTriggerAction_StartDataLogging        1                
#define _TempAlarmTriggerAction_StopDataLogging         2      
#define _TempAlarmTriggerAction_StartVideoRecording     3 
#define _TempAlarmTriggerAction_StopVideoRecording      4 
#define _TempAlarmTriggerAction_SaveSnapshot            5 
#define _TempAlarmTriggerAction_SaveFullFrameTempData   6
             
// Temperatur Alarm Type Navne Strings ->
static std::vector<std::string> TempAlarmsConfigTypeStrings = { "Above",
															    "Below",
															    "Window" };

// Temperatur Alarm Trigger aktion Navne Strings ->
static std::vector<std::string> TempAlarmsTriggerActionStrings = { "None",
																   "Start Data Logging",
														           "Stop Data Logging", 
																   "Start Video Recording", 
																   "Stop Video Recording", 
	                                                               "Save Snapshot", 
															       "Save Frame Temp Data"};

// Tilgængelige Temperatur Alarm Data Sources Navne Strings ->
static std::vector<std::string> TempAlarmsDataSourcesStrings = { "Maximum Temp",
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
																 "Line 2 Max Temp",
																 "Line 2 Min Temp",
																 "Line 3 Max Temp",
																 "Line 3 Min Temp",
																 "Line 4 Max Temp",
																 "Line 4 Min Temp",
																 "Line 5 Max Temp",
																 "Line 5 Min Temp",
																 "ROI 1 Max Temp",
																 "ROI 1 Min Temp",
																 "ROI 2 Max Temp",
																 "ROI 2 Min Temp",
																 "ROI 3 Max Temp",
																 "ROI 3 Min Temp",
																 "ROI 4 Max Temp",
																 "ROI 4 Min Temp",
																 "ROI 5 Max Temp",
																 "ROI 5 Min Temp",
																 "ROI 6 Max Temp",
																 "ROI 6 Min Temp",
																 "ROI 7 Max Temp",
																 "ROI 7 Min Temp",
																 "ROI 8 Max Temp",
																 "ROI 8 Min Temp",
																 "ROI 9 Max Temp",
																 "ROI 9 Min Temp",
																 "ROI 10 Max Temp",
																 "ROI 10 Min Temp",
																 "Mouse Position Temp" };

// ------------------------------------------------------------------------------------------ //

#endif /* RMH_TemperatureAlarms_Resources_H */
