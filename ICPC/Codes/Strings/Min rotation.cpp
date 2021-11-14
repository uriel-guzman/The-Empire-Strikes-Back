template <class T>
int minRotation(T& s) {
  int n = sz(s), i = 0, j = 1;
  while (i < n && j < n) {
    int k = 0;
    while (k < n && s[(i + k) % n] == s[(j + k) % n])
      k++;
    (s[(i + k) % n] <= s[(j + k) % n] ? j : i) += k + 1;
    j += i == j;
  }
  return i < n ? i : j;
}