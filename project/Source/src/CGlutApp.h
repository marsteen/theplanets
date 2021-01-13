#ifndef CGlutApp_H
#define CGlutApp_H

#include <GL/glew.h>
#include <GL/glut.h>

class CGlutApp
{
	public:

		CGlutApp(void);

		void MouseMotionLeft(int dx, int dy);
		void Transform(void);

	protected:

		float mXrot;
		float mYrot;
		float mScale;
};

#endif
