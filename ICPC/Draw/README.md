Steps to use draw.h properly and don't make mistakes using this buggy code.

* Use only the data structures that exist in this repository, other extern data structures won't work D:

* Send a lambda function as a parameter to determine which nodes you want to paint in color red.
```cpp
set<int> specialNodes = {1, 2, 3, 4};
drawGraph(graph, [&](int u) {
  return specialNodes.count(u);
});
```

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
    * Depending in the graph definition make sure to 
      * Have at least 100 nodes for the array definition, furthermore, it only prints the first 100 nodes
        ```cpp:
        vector<int> graph[101]; // 101 is fine
        ```
   
      * Don't have an empty graph in the vector definition
        ```cpp:
        vector<vector<int>> graph; // opps graph.size() == 0 D:
        ```
  
  * drawTrie()
  * drawAho() 
  * drawSam() 
  * drawEertree() 
  
  * drawSeg() 
  * drawLazy()

