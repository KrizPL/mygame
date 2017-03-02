#pragma once
#include "Common.h"

#ifdef WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>

namespace Engine
{
	class _EXPORT CRender
	{
	private:
		HWND hWnd;
		HDC hDC;
		HGLRC hRC;
	public:
		CRender();
		void startFrame();
		void endFrame();
		bool OpenGLInit(HWND&, int width, int height, int colorDepth) throw (Engine::Error);

		~CRender();
	};
}