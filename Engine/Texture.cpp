#include "Texture.h"
#include "libs\soil\include\SOIL.h"
#include <gl\GLU.h>
#include <iostream>

#pragma comment(lib, "OPENGL32.lib")
#pragma comment(lib, "libs/soil/lib/SOIL.lib")
#pragma comment(lib, "GLU32.lib")
Engine::CTexture::CTexture()
	: pData(0), width(0), height(0), textureID(0)
{
}

bool Engine::CTexture::CreateTexture(const std::string & _path)
{

	int channels = 0;
	size_t FileSize = 0;
	char * data = CResourcesMgr::getInstance()->getFile(_path.c_str(), FileSize);
	if (!data)
		return false;
	char* rawFile = new char[FileSize];
	memcpy(rawFile, data, FileSize);
	data = 0;
	GLubyte* rawImage = SOIL_load_image_from_memory((GLubyte*)rawFile, FileSize, &width, &height,
		&channels, SOIL_LOAD_AUTO);
	if (rawFile)
	{
		delete[] rawFile;
		rawFile = 0;
	}
	if (!rawImage)
	{
		width = 0;
		height = 0;
		return false;
	}
	int i, j;
	for (j = 0; j * 2 < height; ++j)
	{
		int index1 = j * width * channels;
		int index2 = (height - 1 - j) * width * channels;
		for (i = width * channels; i > 0; --i)
		{
			unsigned char temp = rawImage[index1];
			rawImage[index1] = rawImage[index2];
			rawImage[index2] = temp;
			++index1;
			++index2;
		}
	}
	pData = new GLubyte[width*height * 4];
	if (channels == 4)
	{
		memcpy(pData, rawImage, (width*height * 4));

	}
	else if (channels == 3)
	{
		int k = 0;
		for (int l = 0; l < (width*height * 4); l += 4)
		{
			pData[l] = rawImage[k];
			pData[l + 1] = rawImage[k + 1];
			pData[l + 2] = rawImage[k + 2];
			pData[l + 3] = 255;
			k += 3;
		}
	}
	if (rawImage)
	{
		delete[] rawImage;
		rawImage = 0;
	}
	return true;
}

void Engine::CTexture::AddTextureToGPU()
{
	if ((!pData) || (width == 0) || (height == 0))
		return;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
	std::cout << gluErrorString(glGetError()) << '\n';
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	std::cout << gluErrorString(glGetError()) << '\n';
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::CTexture::ColorKey(GLubyte r, GLubyte g, GLubyte b)
{
	for (int i = 0; i < (width*height * 4); i += 4)
	{
		if ((pData[i] == r) && (pData[i + 1] == g) && (pData[i + 2] == b))
			pData[i + 3] = 0;
		else
			pData[i + 3] = 255;
	}
}

void Engine::CTexture::SetTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}


Engine::CTexture::~CTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	if (textureID != 0)
		glDeleteTextures(1, &textureID);
	if (pData)
	{
		delete[] pData;
		pData = 0;
	}
}
