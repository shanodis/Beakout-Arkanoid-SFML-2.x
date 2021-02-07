#pragma once
#include "Engine.h"
using namespace std;

struct BTree
{
	int score;
	string playerName;
	BTree* left, * right;
	BTree()
	{
		playerName = score = 0;
		left = right = NULL;
	}
};

class ScoreList
{
	BTree* root;
	int textIterator;
public:
	ScoreList();
	~ScoreList();
	void add_node(int score, string playerName);
	void delete_tree(struct BTree* ptr);
	void saveStrings(Text* strings);

private:
	void inorder_save(BTree* ptr, Text* strings);
	void create_tree(int score, string playerName);
};