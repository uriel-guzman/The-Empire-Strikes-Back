template <class T>
bool umax(T& a, T b) {
  return (a = max(a, b)) == b;
}
