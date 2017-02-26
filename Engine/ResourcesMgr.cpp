#include "ResourcesMgr.h"



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
