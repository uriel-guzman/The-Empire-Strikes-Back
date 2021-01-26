bitset<N> isPrime;

void phiSieve() {
  isPrime.set(); // bitset<N> is faster
  iota(phi, phi + N, 0);
  fore (i, 2, N) if (isPrime[i]) 
    for (int j = i; j < N; j += i) {
      isPrime[j] = (i == j);
      phi[j] /= i;
      phi[j] *= i - 1;
    }
 }
