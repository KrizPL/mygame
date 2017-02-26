#pragma once
#include "Data.h"
#include "Common.h"
#include <string>
class _EXPORT HashTable
{
public:
	typedef unsigned int Handle;
	typedef unsigned char ubyte;
	void insert(std::string name, Data value);
	Data operator[](std::string);
	void erase(std::string);
	void Clear();
	HashTable();
	~HashTable();
private:
	struct node
	{
		unsigned int key;
		Data value;
		node* left;
		node* right;
	};
	node* root;
	Handle hash(ubyte* _input, int _size);
};

