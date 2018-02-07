#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

class AVL
{
	struct node
	{
		int data;           // Search value
		node *left, *right; // Pointers to children
		int height;         // Height of subtree
		node()
		{
			left = NULL;
			right = NULL;
			height = 0;
		}
	};
	node *root;
	node* rotateRight(node *);     // O(1) right rotate function
	node* rotateLeft(node *);      // O(1) left rotate function
	node* insert(node *, int);     // O(LogN) recursive insertion
	node* delet(node *, int);      // O(LogN) recursive deletion
	node* checkHeights(node *);    // Maintain balance in the force
public:
	AVL()
	{
		root = NULL;
	}
	void ins(int val);   // O(LogN) calls insert()
	void del(int val);   // O(LogN) calls delet()
	int find(int val);   // O(LogN)
	void disp();         // O(N) traversal, for debugging
};
AVL::node* AVL::rotateLeft(node *n)
{
	if(n == NULL || n->right == NULL)
		return n;
	node *t = n->right;
	n->right = t->left;
	t->left = n;

	// Set heights
	if(n->left != NULL && n->right != NULL)
		n->height = max(n->left->height, n->right->height) + 1;
	else if(n->left != NULL)
		n->height = n->left->height + 1;
	else if(n->right != NULL)
		n->height = n->right->height + 1;
	else
		n->height = 1;

	if(t->right != NULL)
		t->height = max(n->height, t->right->height) + 1;
	else
		t->height = n->height + 1;
	return t;
}
AVL::node* AVL::rotateRight(node *n)
{
	if(n == NULL || n->left == NULL)
		return n;
	node *t = n->left;
	n->left = t->right;
	t->right = n;

	// Set heights
	if(n->left != NULL && n->right != NULL)
		n->height = max(n->left->height, n->right->height) + 1;
	else if(n->left != NULL)
		n->height = n->left->height + 1;
	else if(n->right != NULL)
		n->height = n->right->height + 1;
	else
		n->height = 1;

	if(t->left != NULL)
		t->height = max(n->height, t->left->height) + 1;
	else
		t->height = n->height + 1;
	return t;
}
AVL::node* AVL::checkHeights(node *n)
{
	if(n == NULL)
		return n;
	if(n->left == NULL && n->right == NULL)
	{
        n->height = 1;
		return n;
	}
	else if(n->left == NULL)
	{
		n->height = n->right->height + 1;
		if(n->right->height >= 2)
		{
			if(n->right->left != NULL && (n->right->right == NULL || n->right->left->height > n->right->right->height))
				n->right = rotateRight(n->right);
			return rotateLeft(n);
		}
	}
	else if(n->right == NULL)
	{
		n->height = n->left->height + 1;
		if(n->left->height >= 2)
		{
			if(n->left->right != NULL && (n->left->left == NULL || n->left->right->height > n->left->left->height))
				n->left = rotateLeft(n->left);
			return rotateRight(n);
		}
	}
	else
	{
		n->height = max(n->left->height, n->right->height) + 1;
		if(abs(n->left->height - n->right->height) >= 2)
		{
			if(n->left->height > n->right->height)
			{
				if(n->left->right != NULL && (n->left->left == NULL || n->left->right->height > n->left->left->height))
					n->left = rotateLeft(n->left);
				return rotateRight(n);
			}
			else
			{
				if(n->right->left != NULL && (n->right->right == NULL || n->right->left->height > n->right->right->height))
					n->right = rotateRight(n->right);
				return rotateLeft(n);
			}
		}
	}
	return n;
}
void AVL::ins(int val)
{
	root = insert(root, val);
}
AVL::node* AVL::insert(node *n, int val)
{
	// Create and insert node
	if(n == NULL)
	{
		n = new node;
		n->data = val;
		n->height = 1;
		return n;
	}

	// Insert into appropriate subtree
	if(n->data <= val)
		n->right = insert(n->right, val);
	else
		n->left = insert(n->left, val);

	// Recalculate heights and rotate
	return checkHeights(n);
}
void AVL::del(int val)
{
	root = delet(root, val);
}
AVL::node* AVL::delet(node *n, int val)
{
	if(n == NULL)
	{
		cerr<<"Node not found\n";
		return NULL;
	}
	// Find and delete node
	if(val == n->data)
	{
		if(n->left == NULL && n->right == NULL)
		{
			delete n;
			return NULL;
		}
		else if(n->left == NULL)
		{
			node *t = n->right;
			*n = *t;
			delete t;
		}
		else if(n->right == NULL)
		{
			node *t = n->left;
			*n = *t;
			delete t;
		}
		else
		{
			node *t = n->left;
			while(t->right != NULL)
				t = t->right;
			int temp = n->data;
			n->data = t->data;
			t->data = temp;
			n->left = delet(n->left, val);
		}
	}
	else if(val < n->data)
		n->left = delet(n->left, val);
	else
		n->right = delet(n->right, val);
	// Rebalance tree
	return checkHeights(n);
}
int AVL::find(int val)
{
	// Search tree until required value encountered
	node *t = root;
	while(t != NULL && t->data != val)
	{
		if(val > t->data)
			t = t->right;
		else
			t = t->left;
	}
	// Value not found
	if(t == NULL)
		return -1;
	// Value found
	return t->data;
}
void AVL::disp()
{
	if(root == NULL)
	{
		cout<<"NULL\n";
		return;
	}
	int sp = 1;
    for(int i = 1; i < root->height; ++i)
    	sp *= 2;
	queue<node *> p, q;
	int i = 0;
	q.push(root);
	while(i != root->height)
	{
		while(!q.empty())
		{
			for(int j = 0; j < sp; ++j)
				cout<<"    ";
			if(q.front() != NULL)
			{
				cout<<q.front()->data<<"("<<q.front()->height<<")";
				p.push(q.front()->left);
				p.push(q.front()->right);
			}
			else
			{
				cout<<"NULL";
				p.push(NULL);
				p.push(NULL);
			}
			q.pop();
		}
		cout<<"\n";
		++i;
		sp /= 2;
		q.swap(p);
	}
}

int main()
{
	AVL tree1, tree2;
	int opt = 0;
    do
	{
        cout<<"1. Insert \n2. Delete \n3. Display \n0. Exit\n";
        cin>>opt;
        int val;
        switch(opt)
        {
		case 1:
            cin>>val;
            tree.ins(val);
            break;
		case 2:
			cin>>val;
			tree.del(val);
			break;
		case 3:
			tree.disp();
			break;
        }
	}while(opt != 0);
	return 0;
}
