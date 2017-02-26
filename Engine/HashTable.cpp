#include "HashTable.h"
void DeleteAll(HashTable::node** node)
{
	if (*node)
	{
		if ((*node)->left) { DeleteAll(&((*node)->left)); }
		if ((*node)->right) { (&((*node)->right)); }
		delete *node;
		*node = 0;
	}
}

HashTable::node * find(HashTable::Handle tar, HashTable::node *start)
{
	if ((start != 0) && (start->key == tar)) return start;
	else if ((start != 0) && (start->key < tar)) return find(tar, start->left);
	else if ((start != 0) && (start->key > tar)) return find(tar, start->right);
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
	Insert(temp, iterator);

}

Data HashTable::operator[](std::string name)
{
	Handle _hash = hash((ubyte*)name.c_str(), name.size());

	node* iterator = root;
	return find(_hash, root) ? find(_hash, root)->value : 0;
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
		(*toDelete)->value.ResetCount();
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
	(*toDelete)->value.ResetCount();
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