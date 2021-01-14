//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	EG3DInterfaceCommand.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef  EG3DInterfaceCommand_H
#define  EG3DInterfaceCommand_H

enum EG3DInterfaceCommand
{
    EG3DcomSetGlobals,          // Set global structure
    EG3DcomInit,                // Init and load resource list
    EG3DcomDraw,                // Draw resource list
    EG3DcomAdjust,              // Adjust after changes
    EG3DcomReload,              // Reload entire resource list
    EG3DcomSendChar,            // Send single char
    EG3DcomRollover,            // Check for mouse-rollover
    EG3DcomLeftMouseClick,      // Send left mousebutton click
    EG3DcomSearchChild,         // Search Child Object
    EG3DcomSetChildPos,         // Set Child Position
    EG3DcomGetChildPos,         // Get Child Position
    EG3DcomSetButton,           // Set Button "active"
    EG3DcomClrButton,           // Set Button "normal"
    EG3DcomActivateKnot,        // Activate Knot
    EG3DcomDeactivateKnot,      // Deactivate Knot
    EG3DcomChangeString,        // Change String content
    EG3DcomSetScale,            // Change scaling
    EG3DcomDrawString           // Draw String
};
#endif
