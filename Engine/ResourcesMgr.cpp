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
		temp.second = new char[entry->GetSize()];
		entry->GetDecompressionStream()->read(temp.second, entry->GetSize());
		temp.second.setSize(entry->GetSize());
		Files.insert(temp);
	}
	return true;
}

bool CResourcesMgr::LoadFileFromDisk(const char * path)
{
	std::ifstream file(path,std::ios::binary);
	if (!(file.good()))
		return false;
	File temp;
	temp.first = hash((ubyte*)path, strlen(path));
	int start = 0, end = 0;
	file.seekg(file.end);
	end = (int)file.tellg();
	file.seekg(file.beg);
	start = (int)file.tellg();
	temp.second = new char[(end - start)];
	file.read(temp.second, (end - start));
	file.close();
	temp.second.setSize(end - start);
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

void CResourcesMgr::FreeFile(const char * path)
{
	size_t stringSize = strlen(path);
	Handle file = hash((ubyte*)path, stringSize);
	Files.erase(file);
}

void CResourcesMgr::ClearMgr()
{
	Files.clear();
}

CResourcesMgr::CResourcesMgr()
{
	Files.clear();
}


CResourcesMgr::~CResourcesMgr()
{
}


