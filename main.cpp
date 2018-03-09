#include <algorithm>
#include <iostream>
#include <queue>
#include "AVL.h"
using namespace std;
#define TYPE int

int main()
{
	AVL<int> tree1, tree2;
	int opt = 0;
	do
	{
		cout<<"1. Insert \n2. Delete \n3. Display \n4. Merge \n5. Split \n0. Exit\n";
		cin>>opt;
		TYPE val;
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
					TYPE x;
					cin>>x;
					tree2.ins(x);
					--N;
				}
				tree1.add(tree2);
			}
			break;
		case 5:
			{
				TYPE ind;
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
