//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	SPlanetDesc.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef SPLANETDESC_H
#define SPLANETDESC_H

struct SPlanetDesc
{
    const char* mTextur;        // Textur-Dateiname
    const char* mNameGer;       // Deutscher Name
    const char* mNameEng;       // Englischer Name
    float		mDistanceMin;   // Min. Abstand zu Planeten
    float		mDistanceMax;   // Max. Abstand zu Planeten
    float		mSize;          // Groesse relativ zum Planeten
    float		mRotSpeed;      // Umdrehungsgeschwindigkeit
    float		mOrbitSpeed;    // Umlaufgeschwindigkeit
};

#endif
