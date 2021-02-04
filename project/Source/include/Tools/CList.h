//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CList.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

template<class TListElem>
class CListElem
{
    public:

        TListElem* next;    // Zeiger auf nächstes Element
        TListElem* prev;    // Zeiger auf vorheriges Element
};

template<class TListElem>
class CList
{
    public:

        TListElem* NewListElem();
        TListElem* GetFirst();
        TListElem* GetNext();
        TListElem* GetLast();
        TListElem* GetPrev();
        TListElem* GetElemNr(int nr);
        int GetListNr(TListElem* le);
        TListElem* InsertListElem(TListElem* ie);
        TListElem* InsertListElem(TListElem* ie, TListElem* te);
        TListElem* InsertListElemPrev(TListElem* ie, TListElem* ne);



        void NewListElem(TListElem*);

        void DeleteListElem(TListElem* le);
        void RemoveListElem(TListElem* le);
        bool SwapElem(TListElem* le1, TListElem* le2);
        TListElem* SwapNext(TListElem* le1);
        TListElem* SwapPrev(TListElem* le2);
        void SortPtrList(TListElem** PtrList, int Anzahl, int Offset);
        int GetOffset(TListElem* le, void* mptr);


        TListElem** CreatePtrList(void);
        int CreatePtrList(TListElem** PtrList);
        void SortList(int (* CmpListElem)(const void* v1, const void* v2));

        int Count(void);

        void SetEmpty()
        {
            root = NULL;
            last = NULL;
        }


        CList()
        {
            SetEmpty();
        }


        void ClearList(void);

        ~CList()
        {
            ClearList();
        }


    protected:

        TListElem* root;
        TListElem* last;
        TListElem* akt;
        TListElem* rnext;
};


// Die Baumstruktur ist Liste und Element zugleich

template<class TTreeElem>
class CTreeElem : public CList<TTreeElem>, public CListElem<TTreeElem>
{
    public:
};
