//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CStringTool.hpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSTRINGTOOL_HPP
#define CSTRINGTOOL_HPP

#include <string>
#include <sstream>

#include <CStringTool.h>

template<typename T>
T CStringTool::StringTo(const std::string& str)
{
    T Value;
    std::stringstream istr(str);

    istr >> Value;
    return Value;
}


#endif
