int mem[N];

int mex(set<int> &st) {
  int x = 0;
  while (st.count(x))
    x++;
  return x;
}

int grundy(int n) {
  if (n < 0)  
    return INF;
  if (n == 0)
    return 0;
  int &g = mem[n];
  if (g == -1) {
    set<int> st;
    for (int x : {a, b})
      st.insert(grundy(n - x));
    g = mex(st);
  } 
  return g;
}
