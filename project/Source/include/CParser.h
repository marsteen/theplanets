//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CParser.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CParser
{
    public:

        char** SplitLine(char* line, char t, int* AnzahlParams);
        void DeleteSplitLine(char** sline);
};
