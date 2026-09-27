
/*
 *  RMH_Application_SaveSession.h
 *
 *  Author: Rune Mark Hansen
 *  Date: December 2022
 *
 */

#pragma once

// RMH_Application_SaveSession.h
#ifndef RMH_Application_SaveSession_H 
#define RMH_Application_SaveSession_H

// ------------ Routiner Til Håndtering Af Gemt Applikations Sessions Parametere ------------- //

void RMH_Application_SaveLastSessionConfigToFile();
void RMH_Application_SetSavedSessionConfigToApplication(System::Windows::Forms::RichTextBox^ GUIInfoTextArea);

// ------------------------------------------------------------------------------------------ //

#endif /* RMH_Application_SaveSession_H */
