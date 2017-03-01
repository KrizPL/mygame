#pragma once
#include "Common.h"
#include "Singleton.h"
#include <map>
#include <memory>
#include "HashTable.h"

namespace Engine
{
	class _EXPORT CResourcesMgr
		: public Singleton<CResourcesMgr>
	{
	public:
		typedef unsigned int Handle;
		typedef unsigned char ubyte;

		CResourcesMgr();
		~CResourcesMgr();

		bool LoadArchive(const char* path);
		bool LoadFileFromDisk(const char* path);
		char* getFile(const char* path, size_t& _size) throw (Engine::Error);
		void FreeFile(const char* path);
		void ClearMgr();
	private:
		HashTable Files;
	};
}