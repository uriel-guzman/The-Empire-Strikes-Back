template <class T>
bool umax(T &a, T b) {
  a = max(a, b);
  return a == b;
}
