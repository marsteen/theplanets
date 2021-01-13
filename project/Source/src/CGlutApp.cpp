

#include "CGlutApp.h"

CGlutApp::CGlutApp()
{
	mXrot  = 0;
	mYrot  = 0;
	mZrot  = 0;
	mScale = 0;
}


void CGlutApp::MouseMotionLeft(int dx, int dy)
{
	if (mScale >= 1.0)
	{
		mXrot += (float) dy / (mScale * mScale * 3);
		mYrot += (float) dx / (mScale * mScale * -3);
	}
	else
	{
		mXrot += (float) dy / 3;
		mYrot += (float) dx / -3;
	}

	if (mXrot > 85)
	{
		mXrot = 85;
	}
	if (mXrot < -85)
	{
		mXrot = -85;
	}

}

void CGlutApp::Transform()
{
	glRotatef(mXrot, 1.0, 0.0, 0.0);
	glRotatef(mZrot, 0.0, 0.0, 1.0);
	glRotatef(mYrot, 0.0, 1.0, 0.0);
}

