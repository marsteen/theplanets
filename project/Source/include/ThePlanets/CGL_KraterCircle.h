//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_KraterCircle.h
// @DATE     :	30.1.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_KraterCircle_H
#define CGL_KraterCircle_H

#include <list>
#include <SLabel.h>

class CGL_KraterCircle
{
    public:
        static void draw(const SLabel& label);
        static void drawAllCircles(const std::list<SLabel>& labelList);       

};

#endif
