#include <fstream>
#include "ResourcesMgr.h"
#include "libs\ziplib\include\ZipArchive.h"
#include "libs\ziplib\include\ZipArchiveEntry.h"
#include "libs\ziplib\include\ZipFile.h"

#pragma comment(lib,"libs/ziplib/lib/bzip2.lib")
#pragma comment(lib,"libs/ziplib/lib/lzma.lib")
#pragma comment(lib,"libs/ziplib/lib/ZipLib.lib")
#pragma comment(lib,"libs/ziplib/lib/zlib.lib")

bool Engine::CResourcesMgr::LoadArchive(const char * path)
{
	ZipArchive::Ptr file = ZipFile::Open(path);
	if (!file) return false;
	int entries = file->GetEntriesCount();
	for (int i = 0; i < entries; i++)
	{
		ZipArchiveEntry::Ptr entry = file->GetEntry(i);
		char* _d = new char[entry->GetSize()];
		entry->GetDecompressionStream()->read(_d, entry->GetSize());
		
		Files.insert(entry->GetFullName(), _d, entry->GetSize());
	}
	return true;
}

bool Engine::CResourcesMgr::LoadFileFromDisk(const char * path)
{
	std::ifstream file(path,std::ios::binary);
	if (!(file.good()))
		return false;
	int start = 0, end = 0;
	file.seekg(file.end);
	end = (int)file.tellg();
	file.seekg(file.beg);
	start = (int)file.tellg();
	char* _d = new char[(end - start)];
	file.read(_d, (end - start));
	file.close();
	if (!_d)
		return false;
	Files.insert(path, _d, end-start);
	return true;
}

char* Engine::CResourcesMgr::getFile(const char * path, size_t& _size) throw (Engine::Error)
{
	char* result = Files.find(path, _size);
	if (!result)
		throw Engine::FILE_NOT_FOUND;
	return 
}

void Engine::CResourcesMgr::FreeFile(const char * path)
{
	Files.erase(path);
}

void Engine::CResourcesMgr::ClearMgr()
{
	Files.Clear();
}

Engine::CResourcesMgr::CResourcesMgr()
{
	Files.Clear();
}


Engine::CResourcesMgr::~CResourcesMgr()
{
}


