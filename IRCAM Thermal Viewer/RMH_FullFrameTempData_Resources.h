
/*
 *  RMH_FullFrameTempData_Resources.h
 *
 *  Author: Rune Mark Hansen
 *  Date: Juli 2023
 *
 */

#pragma once

// RMH_FullFrameTempData_Resources.h
#ifndef RMH_FullFrameTempData_Resources_H 
#define RMH_FullFrameTempData_Resources_H

// Temperatur CSV Data Delimiter Index macroer
#define _FullFrameTempCSVDataDelimiterIndex_Comma           0       
#define _FullFrameTempCSVDataDelimiterIndex_Semicolon       1          
#define _FullFrameTempCSVDataDelimiterIndex_Colon           2            
#define _FullFrameTempCSVDataDelimiterIndex_Space           3       
#define _FullFrameTempCSVDataDelimiterIndex_Tab             4 

// Tilgængelige Temperatur CSV Data Delimiter ->
static std::vector<std::string> FullFrameTempCSVDataDelimiters = { "Comma", "Semicolon", "Colon", "Space", "Tab"};

#endif /* RMH_FullFrameTempData_Resources_H */
