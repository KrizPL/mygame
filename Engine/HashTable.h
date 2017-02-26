#pragma once
#include "Data.h"
#include "Common.h"
#include <string>
class _EXPORT HashTable
{
public:
	typedef unsigned int Handle;
	typedef unsigned char ubyte;
private:
	struct _EXPORT node
	{
		Handle key;
		Data value;
		node* left;
		node* right;
	};
	node* root;
	Handle hash(ubyte* _input, int _size);
public:

	void insert(std::string name, Data value);
	Data operator[](std::string);
	void erase(std::string);
	void Clear();
	HashTable();
	~HashTable();
	friend void DeleteAll(node**);
	friend node* find(Handle, node*);
	friend node** findPtr(Handle, node**);
	friend void Insert(node*, node*);
};

