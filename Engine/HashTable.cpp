#include "HashTable.h"
void DeleteAll(HashTable::node** node)
{
	if (*node)
	{
		if ((*node)->left) { DeleteAll(&((*node)->left)); }
		if ((*node)->right) { (&((*node)->right)); }
		delete (*node)->value;
		(*node)->value;
		delete *node;
		*node = 0;
	}
}

HashTable::node * _find(HashTable::Handle tar, HashTable::node *start)
{
	if ((start != 0) && (start->key == tar)) return start;
	else if ((start != 0) && (start->key < tar)) return _find(tar, start->left);
	else if ((start != 0) && (start->key > tar)) return _find(tar, start->right);
	else return 0;
}

HashTable::node ** findPtr(HashTable::Handle tar, HashTable::node **start)
{
	if ((start != 0) && ((*start)->key == tar)) return start;
	else if ((start != 0) && ((*start)->key < tar)) return findPtr(tar, &((*start)->left));
	else if ((start != 0) && ((*start)->key > tar)) return findPtr(tar, &((*start)->right));
	else return 0;
}
void Insert(HashTable::node *tar, HashTable::node *start)
{
	if (start->key == tar->key) return;
	if (start->key < tar->key) {
		if (start->left)
			Insert(tar, start->left);
		else
		{
			start->left = tar;
			return;
		}
	}
	else
	{
		if (start->right)
			Insert(tar, start->right);
		else
		{
			start->right = tar;
			return;
		}
	}

}
void HashTable::insert(std::string name, char* value, size_t _size)
{
	node* temp = new node();
	temp->left = 0;
	temp->right = 0;
	temp->size = _size;
	temp->key = hash((ubyte*)name.c_str(), name.size());
	temp->value = value;
	if (!root)
	{
		root = temp;
		return;
	}
	node* iterator = root;
	Insert(temp, iterator);

}

char* HashTable::find(std::string name, size_t& _size)
{
	Handle _hash = hash((ubyte*)name.c_str(), name.size());

	node* iterator = root;
	node* _findNode = _find(_hash, root);
	if (!_findNode) return 0;
	_size = _findNode->size;
	return _find(_hash, root)->value;
}

void HashTable::erase(std::string _name)
{
	Handle _hash = hash((ubyte*)_name.c_str(), _name.size());
	node** iterator = &root;
	node** toDelete = findPtr(_hash, iterator);
	if (!toDelete) return;
	node *left = (*toDelete)->left, *right = (*toDelete)->right;
	if (*toDelete == root)
	{
		delete [] (*toDelete)->value;
		(*toDelete)->value = 0;
		delete *toDelete;
		if (!left) {
			root = right;
			return;
		}
		root = left;
		if (right)
		{
			*iterator = root;
			Insert(right, *iterator);
			return;
		}
	}
	delete[] (*toDelete)->value;
	(*toDelete)->value = 0;
	delete *toDelete;
	*toDelete = 0;
	*iterator = root;
	if (left) Insert(left, *iterator);
	*iterator = root;
	if (right) Insert(right, *iterator);
}
void HashTable::Clear()
{
	DeleteAll(&root);
}

HashTable::HashTable()
	: root(0)
{
}


HashTable::~HashTable()
{
	DeleteAll(&root);
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