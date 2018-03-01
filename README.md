# AVL-Merge-Split
Standard implementation of AVL trees, along with special join and split functionality.

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
In addition to the above, this AVL tree also supports joining and splitting. 

### Joining, O(LogM + LogN)
Allows for two AVL trees to be combined into a single tree.  
Requires one tree to contain only values less than all the values in the other tree.  
Destroys both trees in the process.  
O(LogM + LogN) where M and N are the sizes of each tree.  
Returns the newly joined tree.  
``
treeName1.add(treeName2);
``

### Splitting, O(LogM + LogN)   
Given a key matching a node in the tree, breaks the AVL tree into two AVL trees.   
One tree contains only nodes with smaller values than the provided key, the other with larger values.   
The node with the key itself is deleted.   
Modifies the calling tree to be the larger-valued tree.   
Returns the smaller valued tree.   
O(LogN) where N is the size of the tree.   
```C
treeName1.split(VAL).disp() // Outputs smaller tree
treeName1.disp() // Outputs larger tree
```
