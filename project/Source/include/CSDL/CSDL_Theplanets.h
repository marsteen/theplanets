#ifndef CSDL_THEPLANETS_H
#define CSDL_THEPLANETS_H

#include <CSDL/CSDL_App.h>
#include <CSDL/CSDL_Context.h>


class CSDL_Theplanets : public CSDL_App
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

		CSDL_Context* mContext;

};


#endif
