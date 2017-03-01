#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#ifndef ENGINE_EXPORTS
#define _EXPORT __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#else
#define _EXPORT __declspec(dllexport)
#define EXPIMP_TEMPLATE
#endif
#include <string>
namespace Engine
{
	struct Error
	{
		unsigned short code;
		std::string description;
	};
	const Error FILE_NOT_FOUND = { 0,"File not found" };
	const Error NOT_FOUND_PF = { 1,"Didn't find pixel format" };
	const Error PF_SET_ERROR = { 2,"Pixel format set error" };
	const Error CONTEXT_C_ERROR = { 3,"Render Context create error" };
	const Error CONTEXT_S_ERROR = { 4,"Render Context set error" };
	const Error DC_ERROR = { 4,"Device Context get error" };
}

#endif