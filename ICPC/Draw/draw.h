#ifndef DRAW_H
#define DRAW_H

#include <bits/stdc++.h>
using namespace std;

#ifdef __APPLE__
#define open "open"
#else 
#define open "xdg-open"
#endif

#define df(b, e) ((b) > (e))
#define fore(i, b, e) for (auto i = (b) - df(b, e); i != e - df(b, e); i += 1 - 2 * df(b, e))
#define sz(x) int(x.size())
#define all(x) begin(x), end(x)
#define f first
#define s second
#define pb push_back

const bool printLinks = 0; // for aho-corasick, suffix-automaton, eertree
const bool printString = 0; // for trie-based, string instead of chars

const string colorRed = "red";
const string colorBlue = "blue";
const string colorPurple = "\"#c9a9ff\"";
const string normalNodeColor = colorPurple;
const string linkColor = colorRed;
const string specialNodeColor = colorRed;

#define dirLeftRight "LR"
#define dirTopBottom "TB"
#define dir dirTopBottom // Change here the direction

/*-----------------------------------------------------------------------------------------------------------*/

static int numWeightedGraph[2] = {0, 0};
static int numGraph[2] = {0, 0};
static int numTrie = 0;
static int numAho = 0;
static int numSam = 0;
static int numEertree = 0;
static int numSegtree = 0;
static int numLazy = 0;

/*-----------------------------------------------------------------------------------------------------------*/

void runFile(const string file) {
  const string image = file.substr(0, sz(file) - 4) + ".png"; // remove ".dot" and add ".png", 4 characters
  const string create = string("dot -Tpng " + file + " -o " + image);
  // const string createAndOpen = string("dot -Tpng " + file + " -o " + image + " && " + open + " " + image);
  system(create.c_str());
}

string getFile(const string &name, int id) {
  return string("drawings/" + name + to_string(id) + ".dot");
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class Edge>
void drawGraph(const vector<Edge> arr[]) {
  drawGraph(arr, [&]([[maybe_unused]]int u) {
    return false;
  });
}

template <class Edge, class Fun>
void drawGraph(const vector<Edge> arr[], const Fun paintNode) {
  // common sense, you will not print more than 100 nodes, you simply can't understand that amount of nodes :p
  const int n = 100; 
  vector<vector<Edge>> graph;
  for (int u = 0; u < n; u++) {
    graph.push_back({});
    for (const auto v : arr[u])
      graph.back().push_back(v);
  }
  drawGraph(graph, paintNode, 0);
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class Edge>
void drawDigraph(const vector<Edge> arr[]) {
  drawDigraph(arr, [&]([[maybe_unused]]int u) {
    return false;
  });
}

template <class Edge, class Fun>
void drawDigraph(const vector<Edge> arr[], const Fun paintNode) {
  // common sense, you will not print more than 100 nodes, you simply can't understand that amount of nodes :p
  const int n = 100; 
  vector<vector<Edge>> graph;
  for (int u = 0; u < n; u++) {
    graph.push_back({});
    for (const auto v : arr[u])
      graph.back().push_back(v);
  }
  drawGraph(graph, paintNode, 1);
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class Edge, class Fun>
void drawGraph(const vector<vector<Edge>> &graph, const Fun paintNode, const bool directed) {
  const string name = "weighted" + string(directed ? "Digraph" : "Graph");
  const string file = getFile(name, ++numWeightedGraph[directed]);

  ofstream os{file.c_str()};
  os << (directed ? "digraph" : "graph");
  os << " G {" << endl;
  os << "rankdir=" << dir << endl;

  // Graph printing
  int n = graph.size();
  for (int u = 0; u < n; u++) if (graph[u].size()) {
    string how = "[style=filled, color=" + normalNodeColor + "]";
    if (paintNode(u)) {
      how.pop_back();
      how += ", shape=doublecircle, color=" + specialNodeColor + "]";
    }
    os << u << how << endl;
    for (const Edge e : graph[u]) 
      if (directed || u <= e.v) {
        os << u << (directed ? " -> " : " -- ") << e.v;
        os << " [label=\" " << e << "\"]";
        os << endl;
      }
  }
  os << "}" << endl;

  runFile(file);
}

template <class Fun>
void drawGraph(const vector<vector<int>> &graph, const Fun paintNode, const bool directed) {
  const string name = (directed ? "digraph" : "graph");
  const string file = getFile(name, ++numGraph[directed]);

  ofstream os{file.c_str()};
  os << (directed ? "digraph" : "graph");
  os << " G {" << endl;
  os << "rankdir=" << dir << endl;

  // Graph printing
  int n = graph.size();
  for (int u = 0; u < n; u++) if (graph[u].size()) {
    string how = "[style=filled, color=" + normalNodeColor + "]";
    if (paintNode(u)) {
      how.pop_back();
      how += ", shape=doublecircle, color=" + specialNodeColor + "]";
    }
    os << u << how << endl;
    for (const auto v : graph[u]) 
      if (directed || u <= v) {
        os << u << (directed ? " -> " : " -- ") << v << endl;
      }
  }
  os << "}" << endl;

  runFile(file);
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class Trie>
void drawTrie(const Trie &trie) {
  drawTrie(trie, [&]([[maybe_unused]]int u) {
    return false;
  });
}

template <class Trie, class Fun>
void drawTrie(const Trie &trie, const Fun paintNode) {
  const string name = "trie";
  const string file = getFile(name, ++numTrie);

  ofstream os{file.c_str()};
  os << "digraph";
  os << " G {" << endl;
  os << "rankdir=" << dir << endl;
  
  // Trie printing
  int n = sz(trie.trie);
  vector<bool> vis(n, 0);
  function<void(int, string)> dfs = [&](int u, string txt) {
    vis[u] = 1;
    os << u << "[label = \"" << txt << "\"]" << endl;
    string how = "[style=filled, color=" + normalNodeColor + "]";
    if (paintNode(u)) {
      how.pop_back();
      how += ", shape=doublecircle, color=" + specialNodeColor + "]";
    }
    os << u << how << endl;
    for (auto [c, v] : trie.trie[u]) if (v != u) {
      os << u << " -> " << v << endl;
      if (!vis[v])
        dfs(v, string(printString ? txt : "") + string(1, c));
    }
  };

  dfs(0, "");
  os << "}" << endl;

  runFile(file);
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class Aho>
void drawAho(const Aho &aho) {
  drawAho(aho, [&]([[maybe_unused]]int u) {
    return false;
  });
}

template <class Aho, class Fun>
void drawAho(const Aho &aho, const Fun paintNode) {
  const string name = "aho";
  const string file = getFile(name, ++numAho);

  ofstream os{file.c_str()};
  os << "digraph";
  os << " G {" << endl;
  os << "rankdir=" << dir << endl;

  // Links printing
  int n = sz(aho.trie);
  for (int u = 0; u < n && printLinks; u++) 
    os << u << " -> " << aho.link[u] << "[style=dotted, color=" << linkColor << "]" << endl;

  // Trie printing
  vector<bool> vis(n, 0);
  function<void(int, string)> dfs = [&](int u, string txt) {
    vis[u] = 1;
    os << u << "[label = \"" << txt << "\"]" << endl;
    string how = "[style=filled, color=" + normalNodeColor + "]";
    if (paintNode(u)) {
      how.pop_back();
      how += ", shape=doublecircle, color=" + specialNodeColor + "]";
    }
    os << u << how << endl;
    for (auto [c, v] : aho.trie[u]) if (v != u) {
      os << u << " -> " << v << endl;
      if (!vis[v])
        dfs(v, string(printString ? txt : "") + string(1, c));
    }
  };

  dfs(0, "");
  os << "}" << endl;

  runFile(file);
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class SuffixAutomaton>
void drawSam(const SuffixAutomaton &sam) {
  drawSam(sam, [&]([[maybe_unused]]int u) {
    return false;
  });
}

template <class SuffixAutomaton, class Fun>
void drawSam(const SuffixAutomaton &sam, const Fun paintNode) {
  const string name = "sam";
  const string file = getFile(name, ++numSam);

  ofstream os{file.c_str()};
  os << "digraph";
  os << " G {" << endl;
  os << "rankdir=" << dir << endl;

  // Links printing
  int n = sz(sam.trie);
  for (int u = 0; u < n && printLinks; u++) 
    os << u << " -> " << sam.link[u] << "[style=dotted, color=" << linkColor << "]" << endl;

  // Trie printing
  vector<bool> vis(n, 0);
  function<void(int, string)> dfs = [&](int u, string txt) {
    vis[u] = 1;
    os << u << "[label = \"" << txt << "\"]" << endl;
    string how = "[style=filled, color=" + normalNodeColor + "]";
    if (paintNode(u)) {
      how.pop_back();
      how += ", shape=doublecircle, color=" + specialNodeColor + "]";
    }
    os << u << how << endl;
    for (auto [c, v] : sam.trie[u]) if (v != u) {
      os << u << " -> " << v << endl;
      if (!vis[v])
        dfs(v, string(printString ? txt : "") + string(1, c));
    }
  };

  dfs(0, "");
  os << "}" << endl;

  runFile(file);
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class Eertree>
void drawEertree(const Eertree &eert) {
  drawEertree(eert, [&]([[maybe_unused]]int u) {
    return false;
  });
}

template <class Eertree, class Fun>
void drawEertree(const Eertree &eert, const Fun paintNode) {
  const string name = "eertree";
  const string file = getFile(name, ++numEertree);

  ofstream os{file.c_str()};
  os << "digraph";
  os << " G {" << endl;
  os << "rankdir=" << dir << endl;
  os << "{rank=same; 0, 1 }" << endl; // roots of the Eertree
  os << "0 [label=\"0\"]\n 1[label=\"-1\"]" << endl; // text instead of the nodes

  // Links printing
  int n = sz(eert.trie);
  for (int u = 0; u < n && printLinks; u++) 
    os << u << " -> " << eert.link[u] << "[style=dotted, color=" << linkColor << "]" << endl;
  
  // Trie printing
  vector<bool> vis(n, 0);
  function<void(int, string)> dfs = [&](int u, string txt) {
    vis[u] = 1;
    os << u << "[label = \"" << txt << "\"]" << endl;
    string how = "[style=filled, color=" + normalNodeColor + "]";
    if (paintNode(u)) {
      how.pop_back();
      how += ", shape=doublecircle, color=" + specialNodeColor + "]";
    }
    os << u << how << endl;
    for (auto [c, v] : eert.trie[u]) if (v != u) {
      os << u << " -> " << v << endl;
      if (vis[v]) 
        continue;
      if (printString) {
        dfs(v, string(1, c) + txt + string(1, c));
      } else { 
        dfs(v, string(1, c));
      }
    }
  };
  // Two roots, check each one independently
  fore (u, 0, 2) {
    string how = "[style=filled, color=" + normalNodeColor + "]";
    if (paintNode(u)) {
      how.pop_back();
      how += ", shape=doublecircle, color=" + specialNodeColor + "]";
    }
    os << u << how << endl;
    for (auto [c, v] : eert.trie[u]) {
      os << u << " -> " << v << endl;
      dfs(v, string(2 - u % 2, c));
    }
  }
  os << "}" << endl;

  runFile(file);
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class Segtree>
void drawSeg(Segtree* t) {
  drawSeg(t, [&]([[maybe_unused]]Segtree* u) -> string {
    return "";
  });
}

template <class Segtree, class Fun>
void drawSeg(Segtree *t, const Fun paintNode) {
  const string name = "segtree";
  const string file = getFile(name, ++numSegtree);

  ofstream os{file.c_str()};
  os << "digraph";
  os << " G {" << endl;
  os << "rankdir=" << dir << endl;
  os << "node [style=filled, shape = box, color=" << normalNodeColor << "]" << endl; // Shape of the node

  function<void(Segtree *t, int)> dfs = [&](Segtree *t, int x) {
    os << "node" << x << "[label = \"";
    os << "[" << t->l << "," << t->r << "] \\n " << paintNode(t);
    os << "\"]" << endl;
    if (t->L) {
      os << "node" << x << " -> node" << (x * 2) << endl;
      dfs(t->L, x * 2);
    }
    if (t->R) {
      os << "node" << x << " -> node" << (x * 2 + 1) << endl;
      dfs(t->R, x * 2 + 1);
    }
  };

  dfs(t, 1);
  os << "}" << endl;

  runFile(file);
}

/*-----------------------------------------------------------------------------------------------------------*/

template <class Lazy>
void drawLazy(Lazy *t) {
  drawLazy(t, [&]([[maybe_unused]]Lazy *u) -> string {
    return "";
  });
}

template <class Lazy, class Fun>
void drawLazy(Lazy *t, const Fun paintNode) {
  const string name = "lazy";
  const string file = getFile(name, ++numLazy);

  ofstream os{file.c_str()};
  os << "digraph";
  os << " G {" << endl;
  os << "rankdir=" << dir << endl;
  os << "node [style=filled, shape = box, color=" << normalNodeColor << "]" << endl; // Shape of the node

  function<void(Lazy*, int)> dfs = [&](Lazy *t, int x) {
    t->push(); 
    os << "node" << x << "[label = \"";
    os << "[" << t->l << "," << t->r << "] \\n " << paintNode(t);
    os << "\"]" << endl;
    if (t->L) {
      os << "node" << x << " -> node" << (x * 2) << endl;
      dfs(t->L, x * 2);
    }
    if (t->R) {
      os << "node" << x << " -> node" << (x * 2 + 1) << endl;
      dfs(t->R, x * 2 + 1);
    }
  };

  dfs(t, 1);
  os << "}" << endl;

  runFile(file);
}

#endif
