template <class T>
bool umin(T& a, T b) {
  return (a = min(a, b)) == b;
}
