template <class T>
bool umin(T& a, T b) {
  a = min(a, b);
  return a == b;
}
