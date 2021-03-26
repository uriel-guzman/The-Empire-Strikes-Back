template <class T> 
void print(T l, T r) {
  fore (i, l, r)
    cout << *i << " \n"[i == prev(r)];
}

