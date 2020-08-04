int erat[N >> 6];
#define bit(i) ((i >> 1) & 31)
#define prime(i) !(erat[i >> 6] >> bit(i) & 1)
 
void bitSieve() {
  for (int i = 3; i * i < N; i += 2) if (prime(i))
    for (int j = i * i; j < N; j += (i << 1))
      erat[j >> 6] |= 1 << bit(j);
}