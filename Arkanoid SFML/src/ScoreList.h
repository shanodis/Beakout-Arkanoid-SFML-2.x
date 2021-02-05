#pragma once
#include "Engine.h"
using namespace std;

class ScoreList
{
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
	}*root;

public:
	ScoreList();
	~ScoreList();
	void add_node(int score, string playerName);
	void delete_tree(struct BTree* ptr);
	int find_max_node();
	int find_min_node();

private:
	void create_tree(int score, string playerName);
};