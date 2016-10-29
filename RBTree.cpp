/*************************************************************************
	> File Name: RBTree.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月29日 星期六 21时03分52秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include <cassert>

using namespace std;

typedef enum{RAD, BLACK}Color;
typedef struct {} Record;


template<class KeyType>
class RBTree
{
public:
	typedef struct RBTNode
	{
		struct RBTNode *leftchild;
		struct RBTNode *rightchild;
		struct RBTNode *parent;
		KeyType         key;
		Color           color;
	}RBTNode;
	
	RBTree(RBTNode* ptree = NULL):head(ptree){}
	static RBTNode* BuyNode()
	{
		RBTNode *p = (RBTNode*)malloc(sizeof(RBTNode));
		if(p == NULL) exit(1);
		
		memset(p, 0, sizeof(RBTNode));
	}
	static void FreeNode(RBTNode* ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	static void RotateLeft(RBTNode *& ptr)
	{
		RBTNode* newRoot = ptr->rightchild;
		newRoot->parent = ptr->parent;
		ptr->rightchild = newRoot->leftchild;
		if (newRoot->leftchild != nullptr)
		{
			newRoot->leftchild->parent = ptr;
		}
		newRoot->leftchild = ptr;
		ptr->parent = newRoot;
		ptr = newRoot;
	}

	static void RotateRight(RBTNode *& ptr)
	{
		RBTNode* newRoot = ptr->leftchild;
		newRoot->parent = ptr->parent;
		ptr->leftchild = newRoot->rightchild;
		if (newRoot->rightchild != nullptr)
		{
			newRoot->rightchild->parent = ptr;
		}
		newRoot->rightchild = ptr;
		ptr->parent = newRoot;
		ptr = newRoot;
	}
	

	

	static bool Insert(RBTNode *& ptree, const KeyType &x)
	{
		RBTNode *pa = NULL;
		if(ptree == NULL)
		{
			ptree = BuyNode();
			ptree->parent = pa;
			ptree->key = x;
			ptree->color = BLACK;
			
			return true;
		}
		
		RBTNode *cur = ptree;
		
		while(cur)
		{
			if(cur->key < x)
			{
				pa = cur;
				cur = cur->rightchild;
			}
			else if(cur->key > x)
			{
				pa = cur;
				cur = cur->leftchild;
			}
			else 
			{
				return false;
			}
		}
		
		cur = BuyNode();
		cur->key = x;
		
		if(x > pa->key)
		{
			pa->rightchild = cur;
		}
		else
		{
			pa->leftchild = cur;
		}
		cur->parent = pa;
		
		while(cur != ptree && pa->color == RAD)
		{
			RBTNode *grandfather = pa->parent;
			if(grandfather->leftchild == pa)
			{
				RBTNode *uncle = grandfather->rightchild;
				if(uncle && uncle->color == RAD)
				{
					pa->color = uncle->color = BLACK;
					grandfather->color = RAD;
					
					cur = grandfather;	
					pa = cur->parent;
				}
				else
				{
					if(cur == pa->leftchild)
					{
						grandfather->color = RAD;
						pa->color = BLACK;
						if(grandfather->parent != NULL)
						{
							grandfather->parent->leftchild = pa;
						}
						else
						{
							ptree = pa;
						}
						RotateRight(grandfather);
					}
					else 
					{
						cur->color = BLACK;
						grandfather->color = RAD;
						RotateLeft(pa);
						grandfather->leftchild = pa;

						if(grandfather->parent != NULL)
						{
							grandfather->parent->leftchild = pa;
						}
						else
						{
							ptree = pa;
						}
						RotateRight(grandfather);
					}
				}
			}
			else
			{
				RBTNode *uncle = grandfather->leftchild;
				if(uncle && uncle->color == RAD)
				{
					uncle->color = pa->color = BLACK;
					grandfather->color = RAD;
					
					cur = grandfather;
					pa = cur->parent;	
				}
				else
				{
					if(pa->rightchild == cur)
					{
						grandfather->color = RAD;
						pa->color = BLACK;
						if(grandfather->parent != NULL)
						{
							grandfather->parent->rightchild = pa;
						}
						else
						{
							ptree = pa;
						}
						RotateLeft(grandfather);
						
					}
					else 
					{
						cur->color = BLACK;
						grandfather->color = RAD;
						
						RotateRight(pa);
						grandfather->rightchild = pa;
						if(grandfather->parent != NULL)
						{
							grandfather->parent->rightchild = pa;
						}
						else
						{
							ptree = pa;
						};
						RotateLeft(grandfather);
					}
				}
			}
		}
		
		ptree->color = BLACK;
		
		return true;	
	}
	static void InOrder(RBTNode *ptr)
	{
		if(ptr != NULL)
		{
			InOrder(ptr->leftchild);
			cout << ptr->key << " ";
			InOrder(ptr->rightchild);
		}
	}
	bool Insert(const KeyType &x)
	{
		return Insert(head, x);
	}
	void InOrder()
	{
		InOrder(head);
	}
private:
	RBTNode *head;
};


int main()
{
	RBTree<int> rbt;
	int ar[] = {8,6,9,5,4,11};
	int len = sizeof(ar)/sizeof(ar[0]);

	for(int i = 0; i < len; ++i)
	{
		rbt.Insert(ar[i]);
	}

	rbt.InOrder();

	cout << endl;
	return 0;
}
