char gc() {
  return getchar_unlocked();
}

void readInt() {}
template <class H, class... T>
void readInt(H& h, T&&... t) {
  char c, s = 1;
  while (isspace(c = gc()))
    ;
  if (c == '-')
    s = -1, c = gc();
  for (h = c - '0'; isdigit(c = gc()); h = h * 10 + c - '0')
    ;
  h *= s;
  readInt(t...);
}

void readFloat() {}
template <class H, class... T>
void readFloat(H& h, T&&... t) {
  int c, s = 1, fp = 0, fpl = 1;
  while (isspace(c = gc()))
    ;
  if (c == '-')
    s = -1, c = gc();
  for (h = c - '0'; isdigit(c = gc()); h = h * 10 + c - '0')
    ;
  h *= s;
  if (h == '.')
    for (; isdigit(c = gc()); fp = fp * 10 + c - '0', fpl *= 10)
      ;
  h += (double)fp / fpl;
  readFloat(t...);
}