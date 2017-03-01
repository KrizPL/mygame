#pragma once
#include "Common.h"
#include "ResourcesMgr.h"
#ifdef WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
namespace Engine
{
	class _EXPORT CTexture
	{
	private:
		GLuint textureID;
		int width, height;
		GLubyte* pData;
	public:
		CTexture();
		bool CreateTexture(const std::string& _path);
		void AddTextureToGPU();
		void ColorKey(GLubyte, GLubyte, GLubyte);
		void SetTexture();

		~CTexture();
	};
}
