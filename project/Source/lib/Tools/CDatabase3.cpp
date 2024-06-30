//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CDatabase3.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <CDatabase3.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CRecord
// Methode:		IsValid
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

inline bool CDatabase3::IsValid(int c)
{
    if ((c == 0x0A) ||
        (c == 0x0D) ||
        (c == 0))
    {
        return false;
    }
    return true;
}


//---------------------------------------------------------------------------
//
// Klasse:    CRecord
// Methode:		Show
//
//
//---------------------------------------------------------------------------

void CRecord::Show()
{
#if 0
    cout << (int)size() << " ";
    for (vector<string>::iterator dr = begin();
        dr != end();
        dr++)
    {
        cout << *dr << ' ';
    }
    cout << "-" << endl;
#endif
}


//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:		LineEnd
//
//
//---------------------------------------------------------------------------

static inline bool LineEnd(char c)
{
    return (c == 0x0A) || (c == 0x0D);
}


//---------------------------------------------------------------------------
//
// Klasse:    CDatabase3
// Methode:		Read
//
// Parameter: Filename  = Dateiname der Datenbank
//            SplitChar = Trenn-Charakter, z.B. '\t' oder ' '
//
// Return:
//
//---------------------------------------------------------------------------

int CDatabase3::Read(list<CRecord>* db, const string& BasePath, const string& Filename, char SplitChar)
{
    if (db == NULL)
    {
        db = this;
    }

    ifstream infile((BasePath + Filename).c_str(), ios::in | ios::binary);

    if (infile.good())
    {
        string Linebuffer;
        CRecord rc;
        int LineNumber = 1;
        bool CommentMode = false;
        char cLast = 0;

        while (!infile.eof())
        {
            char c;
            infile.get(c);

            if (infile.eof())
            {
                c = 0x0D;
            }

            if ((c == '#') || ((c == '/') && (cLast == '/')))
            {
                do
                {
                    infile.get(c);
                } while (!LineEnd(c) && !infile.eof());
                LineNumber++;
                Linebuffer.clear();
            }
            else
            if (IsValid(c))
            {
                if (c != '\t')
                {
                    cLast = c;
                    Linebuffer.push_back(c);
                }
                else
                {
                    rc.push_back(Linebuffer);
                    Linebuffer.clear();
                }
            }
            else
            {
                if ((c != 0x0A) || (c != 0x0D))
                {
                    if (!Linebuffer.empty())
                    {
                        rc.push_back(Linebuffer);
                        Linebuffer.clear();
                    }
                    if (!rc.empty())
                    {
                        if (CommentMode)
                        {
                            if (rc.front() == "*/")
                            {
                                CommentMode = false;
                            }
                        }
                        else
                        {
                            if (rc.front() == "/*")
                            {
                                CommentMode = true;
                            }
                            else
                            {
                                if (rc[0] == "$INCLUDE")
                                {
                                    if (rc.size() == 2)
                                    {
                                        CDatabase3 DbInclude;
                                        DbInclude.Read(this, BasePath, rc[1], SplitChar);
                                    }
                                    else
                                    {
                                        //cout << "****** wrong include parameter count " << LineNumber << endl;
                                        exit(0);
                                    }
                                }
                                else
                                {
                                    rc.mLineNumber = LineNumber;
                                    rc.mFilename = Filename;
                                    db->push_back(rc);
                                    //rc.Show();
                                }
                            }
                        }
                        rc.clear();
                    }
                    LineNumber++;
                }
            }
        }
    }
    else
    {
        cout << "***** cannot open " << BasePath <<  Filename << endl;
    }
    infile.close();

    //cout << "Size=" << size() << endl;

    return db->size();
}
