#include "Engine.h"

ScoreList::ScoreList() { root = NULL; }

ScoreList::~ScoreList() { delete_tree(root); }

void ScoreList::create_tree(int score, string playerName)
{
    root = new struct BTree;
    root->score = score;
    root->playerName = playerName;
    root->left = root->right = NULL;
}

void ScoreList::delete_tree(BTree* ptr)
{
	if (ptr)
	{
		delete_tree(ptr->left);
		delete_tree(ptr->right);
		delete ptr;
	}
}

void ScoreList::add_node(int score, string playerName)
{
    if (root == NULL)
    {
        create_tree(score, playerName);
        return;
    }

    struct BTree* new_node = root, * parent = root;
    while (new_node)
    {
        parent = new_node;

        if (new_node->score < score)
            new_node = new_node->right;
        else
            new_node = new_node->left;
    }
    new_node = new struct BTree;
    new_node->score = score;
    new_node->playerName = playerName;
    new_node->right = new_node->left = NULL;

    if (parent->score > new_node->score)
        parent->left = new_node;
    else
        parent->right = new_node;
}