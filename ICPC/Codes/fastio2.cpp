char gc() { return getchar_unlocked(); }

void readInt() {}
template <class T, class... Args>
void readInt(T &a, Args&&... b) {
  char c, s = 1;
  while (isspace(c = gc()));
  if (c == '-') s = -1, c = gc();
  for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0');
  a *= s;
  readInt(b...);
}

void readFloat() {}
template <class T, class... Args>
void readFloat(T &a, Args&&... b) {
  int c, s = 1, fp = 0, fpl = 1;
  while (isspace(c = gc()));
  if (c == '-') s = -1, c = gc();
  for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0');
  a *= s;
  if (c == '.')
    for (; isdigit(c = gc()); fp = fp * 10 + c - '0', fpl *= 10);
  a += (double)fp / fpl;
  readFloat(b...);
}