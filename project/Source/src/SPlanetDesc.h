
#ifndef SPLANETDESC_H
#define SPLANETDESC_H

struct SPlanetDesc
{
	const char* mTextur;       // Textur-Dateiname
	const char* mNameGer;      // Deetuscher Name
	const char* mNameEng;      // Englischer Name
	float       mDistance;     // Abstand zu Planeten
	float       mSize;         // Groesse relativ zum Planeten
	float       mRotSpeed;     // Umdrehungsgeschwindigkeit
	float       mOrbitSpeed;   // Umlaufgeschwindigkeit
};

#endif
