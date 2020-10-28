Steps to use draw.h properly and don't make mistakes using this buggy code.

* Use only the data structures that exist in this repository, other extern data structures won't work D:

* Send a lambda function as a parameter to determine which nodes you want to paint in color red.

* For weighted graphs, define a structure like the one down below and write a method to print the edge
```cpp:
struct Edge {
  int v;
  int weight;
  
  friend ostream& operator << (ostream& os, const Edge &e) {
    return os << " weight : " << e.weight;
  }
};
```

* Methods issues for data structures than you can draw
  * drawGraph(), drawDigraph()
    * Depending in the graph make sure to 
      * Have at least 100 nodes for array definition
        ```cpp:
        vector<int> graph[101];
        ```
   
      * Don't have an empty graph in the vector definition
        ```cpp:
        vector<vector<int>> graph;
        ```
  
  * drawTrie 
  * drawAho 
  * drawSam 
  * drawEertree 
  
  * drawSeg 
  * drawLazy

