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

#endif