/*
 *  RMH_Application_Information.h
 *
 *  Author: Rune Mark Hansen
 *  Date: November 2022
 *
 */

#pragma once

// RMH_Application_Information.h
#ifndef RMH_Application_Information_H 
#define RMH_Application_Information_H

// Applikationens Discord Server URL Link String
static std::string DiscordServerLinkAddress = "https://discord.gg/3zq3zXFA8B";

// Applikationens Preset Fil Navn ->
static std::string Application_PresetFileName = "IRCAMApplicationPreset.txt";

// Applikationens Information ->
static std::string Application_Name = "IRCAM Thermal Viewer";
static std::string Application_VersionNumber = "3.0.0";
static std::string Application_Revision = "";
static std::string Application_VersionMonth = "September";
static std::string Application_VersionYear = "2026";

// GUI Informations og versions string (Vises i toppen af GUIen)
static std::string ApplicationInformationString = Application_Name + " - [Developed & Written By: Rune Mark Glendorf, " + Application_VersionMonth + " " + Application_VersionYear + " - Version " + Application_VersionNumber + Application_Revision + "]";

#endif /* RMH_Application_Information_H */

