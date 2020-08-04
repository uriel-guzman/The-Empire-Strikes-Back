void phiSieve() {
  isp.set(); // bitset<N> is faster
  iota(phi, phi + N, 0);
  fore (i, 2, N) if (isp[i]) 
    for (int j = i; j < N; j += i) {
      isp[j] = (i == j);
      phi[j] /= i;
      phi[j] *= i - 1;
    }
 }
