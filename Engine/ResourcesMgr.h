#pragma once
#include "Common.h"
#include "Singleton.h"
#include <map>
#include <memory>
#include "Data.h"
#include "HashTable.h"
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
	char* getFile(const char* path, size_t& _size);
	void FreeFile(const char* path);
	void ClearMgr();
private:
	HashTable Files;
};