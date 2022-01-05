bitset<N> isPrime;
int phi[N];

void phiSieve() {
  isPrime.set();
  iota(phi, phi + N, 0);
  fore (i, 2, N)
    if (isPrime[i])
      for (int j = i; j < N; j += i) {
        isPrime[j] = (i == j);
        phi[j] = phi[j] / i * (i - 1);
      }
}