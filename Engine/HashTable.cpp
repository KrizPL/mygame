#include "HashTable.h"



void HashTable::insert(std::string name, Data value)
{
	node* temp = new node();
	temp->left = 0;
	temp->right = 0;
	temp->key = hash((ubyte*)name.c_str(), name.size());
	temp->value = value;
	if (!root)
	{
		root = temp;
		return;
	}
	node* iterator = root;
	while (true)
	{
		if (iterator->key < temp->key)
		{
			if (!(iterator->left))
			{
				iterator->left = temp;
				return;
			}
			else
			{
				iterator = iterator->left;
				break;
			}
		}
		else if (iterator->key > temp->key)
		{
			if (!(iterator->right))
			{
				iterator->right = temp;
				return;
			}
			else
			{
				iterator = iterator->right;
				break;
			}
		}
		else return;
	}

}

Data HashTable::operator[](std::string name)
{
	Handle _hash = hash((ubyte*)name.c_str(), name.size());
	if (!root)
	{
		if(root->key == _hash)
		return root->value;
	}
	node* iterator = root;
	while (true)
	{
		if (iterator->key < _hash)
		{
			if (!(iterator->left))
				return 0;
			else
			{
				iterator = iterator->left;
				break;
			}
		}
		else if (iterator->key > _hash)
		{
			if (!(iterator->right))
			{
				return 0;
			}
			else
			{
				iterator = iterator->right;
				break;
			}
		}
		else return iterator->value;
	}
}

void HashTable::erase(std::string _name)
{
	Handle _hash = hash((ubyte*)_name.c_str(), _name.size());
	if (!root)
	{
		if (root->key == _hash)
		{

		}
	}
	node* iterator = root;
	while (true)
	{
		if (iterator->key < _hash)
		{
			if (!(iterator->left))
				return;
			else
			{
				iterator = iterator->left;
				break;
			}
		}
		else if (iterator->key > _hash)
		{
			if (!(iterator->right))
			{
				return;
			}
			else
			{
				iterator = iterator->right;
				break;
			}
		}
		else
		{
			node *_left = iterator->left, *_right = iterator->right;
			delete iterator;
			if (_right)
			{
				if (!root)
				{
					root = _right;
					
				}
				else
				{
					iterator = root;
					while (true)
					{
						if (iterator->key < _right->key)
						{
							if (!(iterator->left))
							{
								iterator->left = _right;
								break;
							}
							else
							{
								iterator = iterator->left;
								continue;
							}
						}
						else if (iterator->key > _right->key)
						{
							if (!(iterator->right))
							{
								iterator->right = _right;
								break;
							}
							else
							{
								iterator = iterator->right;
								continue;
							}
						}
						else return;
					}
				}
				if (_left)
				{
					if (!root)
					{
						root = _left;
					}
					else
					{
						iterator = root;
						while (true)
						{
							if (iterator->key < _left->key)
							{
								if (!(iterator->left))
								{
									iterator->left = _left;
									break;
								}
								else
								{
									iterator = iterator->left;
									continue;
								}
							}
							else if (iterator->key > _left->key)
							{
								if (!(iterator->right))
								{
									iterator->right = _left;
									break;
								}
								else
								{
									iterator = iterator->right;
									continue;
								}
							}
							else break;
						}
					}
			}
		}
	}
}

void HashTable::Clear()
{
	return;
}

HashTable::HashTable()
	: root(0)
{
}


HashTable::~HashTable()
{
}
HashTable::Handle HashTable::hash(ubyte * _input, int _size)
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