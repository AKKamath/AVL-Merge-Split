# AVL-Merge-Split
Standard implementation of AVL trees, along with special merge and split functionality.

## Base AVL Functionality
* Guaranteed logarithmic insertion time complexity.  
* Guaranteed logarithmic search time complexity for a particular node.  
* Guaranteed logarithmic time complexity for deletion.  

### Format
Let N denote number of nodes present in tree.
Let VAL denote some integer value.
- Declaration, O(1)  
``
AVL treeName;
``
- Insertion, O(LogN)  
Returns AVL  
``
treeName.ins(VAL);
``
- Deletion O(LogN)  
Returns AVL  
``
treeName.del(VAL);
``
- Node search, O(LogN)
Returns -1 in case node not found, else returns value  
``
treeName.find(VAL);
``
- Display (For debug purposes), O(N)  
Outputs all nodes, all nodes at same level are on same line.  
In case value of a node is NULL, the same is outputted.  
``
treeName.disp();
``

## Additional Functionality
In addition to the above, this AVL tree also supports merging and splitting. 

### Merging, O(LogM + LogN)
Allows for two AVL trees to be combined into a single tree.  
Requires one tree to contain only values less than all the values in the other tree.  
Destroys both trees in the process.  
O(LogM + LogN) where M and N are the sizes of each tree.  
Returns the newly merged tree.  
``
treeName1.add(treeName2);
``
