#include <fstream>
#include "ResourcesMgr.h"
#include "libs\ziplib\include\ZipArchive.h"
#include "libs\ziplib\include\ZipArchiveEntry.h"
#include "libs\ziplib\include\ZipFile.h"

#pragma comment(lib,"libs/ziplib/lib/bzip2.lib")
#pragma comment(lib,"libs/ziplib/lib/lzma.lib")
#pragma comment(lib,"libs/ziplib/lib/ZipLib.lib")
#pragma comment(lib,"libs/ziplib/lib/zlib.lib")

bool CResourcesMgr::LoadArchive(const char * path)
{
	ZipArchive::Ptr file = ZipFile::Open(path);
	if (!file) return false;
	int entries = file->GetEntriesCount();
	for (int i = 0; i < entries; i++)
	{
		ZipArchiveEntry::Ptr entry = file->GetEntry(i);
		File temp;
		std::string name = entry->GetFullName();
		temp.first = hash((ubyte*)(name.c_str()), name.size());
		entry->GetDecompressionStream()->read(temp.second, entry->GetSize());
		Files.insert(temp);
	}
	return true;
}

bool CResourcesMgr::LoadFileFromDisk(const char * path)
{
	std::ifstream file(path);
	if (!(file.good()))
		return false;
	File temp;
	temp.first = hash((ubyte*)path, strlen(path));
	int start = 0, end = 0;
	file.seekg(file.end);
	end = (int)file.tellg();
	file.seekg(file.beg);
	start = (int)file.tellg();
	file.read(temp.second, (end - start));
	file.close();
	if (!temp.second)
		return false;
	Files.insert(temp);
	return true;
}

Data CResourcesMgr::getFile(const char * path)
{
	size_t stringSize = strlen(path);
	Handle handle = hash((ubyte*)path, stringSize);
	return Files[handle];
}

CResourcesMgr::CResourcesMgr()
{
}


CResourcesMgr::~CResourcesMgr()
{
}

CResourcesMgr::Handle CResourcesMgr::hash(ubyte * _input, int _size)
{
	Handle hashO = 0;
	for (int i = 0; i < _size; i++)
	{
		hashO += _input[i];
		hashO += hashO << 10;
		hashO ^= hashO >> 6;
	}
	hashO += hashO << 3;
	hashO += hashO >> 11;
	hashO ^= hashO << 15;
	return hashO;
}
