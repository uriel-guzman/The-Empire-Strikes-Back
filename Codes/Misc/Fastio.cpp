namespace fastio {
int ptr, ye;
char temp[25], str[32333667], out[15333667];

void init() { // init() first
  ptr = 0, ye = 0;
  fread(str, 1, 32333667, stdin);
}

inline int number() { // x = number()
  int i, j, val = 0;
  while (str[ptr] < 45 || str[ptr] > 57) ptr++;
  while (str[ptr] > 47 && str[ptr] < 58) val = (val * 10) + (str[ptr++] - 48);
  return val;
}

inline void convert(int x) { // convert(x) then print()
  int i, d = 0;
  if (x < 0) x = -x, out[ye++] = 45;
  do { temp[++d] = (x % 10) + 48, x /= 10; } while (x > 0);
  for (i = d; i; i--) out[ye++] = temp[i];
  out[ye++] = 10;
}

inline void print() { fwrite(out, 1, ye, stdout); }
} // namespace fastio

using namespace fastio;
