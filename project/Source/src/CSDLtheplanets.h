#ifndef CSDL THEPLANETS_H
#define CSDL    THEPLANETS_H

#include <CSdlApp.h>
#include <CGL_Context.h>


class CSdlTheplanets : public CSdlApp
{
    public:

        CSdlHello();

        void GameLoop();
        virtual void InitGame();

    protected:

        bool ParseKeys(int key, bool down);
        void SetResolution(int w, int h);
        void SetUpDrawing(float StereoOffset);
        void ParseMouseRel(int xrel, int yrel);
        void ParseArgVec(const std::vector<std::string>& ArgStr);
        void MouseWheel(bool up);
        void Zoom(float z);

        //
        //
        //

        CGL_Context* mContext;
};


#endif
