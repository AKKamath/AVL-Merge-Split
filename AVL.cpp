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
	node* extractMin(node **);     // Get minimum value in O(LogN)
	node* mergeWithNode(node *, node *, node *); // Merge trees in O(LogN + LogM)
	void breakTree(int, node **, node **);       // Break trees along key in O(LogM + LogN)
public:
	AVL()
	{
		root = NULL;
	}
	AVL split(int key);  // Changes calling tree to larger tree, returns smaller tree
	AVL add(AVL tree2);  // O(LogM + LogN) calls extractMin() and mergeWithNode()
	AVL ins(int val);    // O(LogN) calls insert()
	AVL del(int val);    // O(LogN) calls delet()
	int find(int val);   // O(LogN)
	void disp();         // O(N) traversal, for debugging
};
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
// Assumption: All nodes of tree2 have values
// that are <= the smallest value in tree1
AVL::node* AVL::mergeWithNode(node *tree1, node *tree2, node *mergeNode)
{
    if(tree1 == NULL || tree2 == NULL || mergeNode == NULL)
    	return tree1;
	if(tree1->height - tree2->height >= 2)
	{
		tree1->left = mergeWithNode(tree1->left, tree2, mergeNode);
		tree1 = checkHeights(tree1);
		return tree1;
	}
	else if(tree2->height - tree1->height >= 2)
	{
		tree2->right = mergeWithNode(tree1->right, tree2, mergeNode);
		tree2 = checkHeights(tree2);
		return tree2;
	}
	mergeNode->left = tree2;
	mergeNode->right = tree1;
	mergeNode = checkHeights(mergeNode);
	return mergeNode;
}
// Get the minimum value in O(LogN)
AVL::node* AVL::extractMin(node **tree)
{
	if(tree == NULL)
		return NULL;
	// Found minimum node
	if((*tree)->left == NULL)
	{
		// Copy details
		node *temp = new node;
		*temp = **tree;
		// Remove node from tree
		*tree = delet(*tree, (*tree)->data);
		// Rebalance
		*tree = checkHeights(*tree);
		return temp;
	}
	// Keep moving
	node *t = extractMin(&((*tree)->left));
	// Rebalance
	*tree = checkHeights(*tree);
	return t;
}
// Tree1 is initial tree, as well as final larger tree
void AVL::breakTree(int key, node **tree1, node **tree2)
{
    if(tree1 == NULL)
    	return;
	// Move to appropriate node
	// then store subtree in appropriate tree
    if(key > (*tree1)->data)
	{
        breakTree(key, &(*tree1)->right, tree2);
        (*tree2) = mergeWithNode((*tree2), (*tree1)->left, (*tree1));
        (*tree1) = (*tree1)->right;
	}
	else if(key < (*tree1)->data)
	{
        breakTree(key, &(*tree1)->left, tree2);
        (*tree1) = mergeWithNode((*tree1)->right, (*tree1)->left, (*tree1));
	}
	else
	{
		node *n = (*tree1);
        (*tree2) = (*tree1)->left;
        (*tree1) = (*tree1)->right;
        delete n;
	}
}
// PUBLIC FUNCTIONS
// Returns smaller tree
AVL AVL::split(int key)
{
    AVL tree2;
    breakTree(key, &root, &tree2.root);
    return tree2;
}
// Assumption: Tree2 is tree with smaller keys
AVL AVL::add(AVL tree2)
{
    node *m = extractMin(&root);
	root = mergeWithNode(root, tree2.root, m);
    return *this;
}
AVL AVL::ins(int val)
{
	root = insert(root, val);
	return *this;
}

AVL AVL::del(int val)
{
	root = delet(root, val);
	return *this;
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
        cout<<"1. Insert \n2. Delete \n3. Display \n4. Merge \n5. Split \n0. Exit\n";
        cin>>opt;
        int val;
        switch(opt)
        {
		case 1:
            cin>>val;
            tree1.ins(val);
            break;
		case 2:
			cin>>val;
			tree1.del(val);
			break;
		case 3:
			tree1.disp();
			break;
		case 4:
			{
                int N;
                cout<<"Enter number of nodes in smaller tree\n";
                cin>>N;
                cout<<"Enter node values\n";
                while(N)
				{
                    int x;
                    cin>>x;
                    tree2.ins(x);
                    --N;
				}
                tree1.add(tree2);
			}
			break;
		case 5:
			{
				int ind;
                cout<<"Enter key to split using\n";
				cin>>ind;
				tree1.split(ind).disp();
				tree1.disp();
			}
			break;
        }
	}while(opt != 0);
	return 0;
}
