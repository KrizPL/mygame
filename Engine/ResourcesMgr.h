#pragma once
#include "Common.h"
#include "Singleton.h"
#include <map>
#include <memory>
#include "Data.h"
EXPIMP_TEMPLATE template class _EXPORT std::map<unsigned int, Data>;
class _EXPORT CResourcesMgr
	: public Singleton<CResourcesMgr>
{
public:
	typedef unsigned int Handle;
	typedef unsigned char ubyte;
	typedef std::map<Handle, Data> FilesList;
	typedef std::pair<Handle, Data> File;

	CResourcesMgr();
	~CResourcesMgr();

	bool LoadArchive(const char* path);
	bool LoadFileFromDisk(const char* path);
	Data getFile(const char* path);
	void FreeFile(const char* path);
	void ClearMgr();
private:
	
	Handle hash(ubyte* _input, int _size);
	FilesList Files;
};