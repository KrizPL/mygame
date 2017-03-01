#pragma once
#include "Common.h"
#include <string>

class _EXPORT HashTable
{
public:
	typedef unsigned int Handle;
	typedef unsigned char ubyte;
private:
	struct node
	{
		Handle key;
		char* value;
		size_t size;
		node* left;
		node* right;
	};
	node* root;
	Handle hash(ubyte* _input, int _size);
public:
	void insert(std::string name, char* value, size_t _size);
	char* find(std::string, size_t&);
	void erase(std::string);
	void Clear();
	HashTable();
	~HashTable();
	friend void DeleteAll(node**);
	friend node* _find(Handle, node*);
	friend node** findPtr(Handle, node**);
	friend void Insert(node*, node*);
};

