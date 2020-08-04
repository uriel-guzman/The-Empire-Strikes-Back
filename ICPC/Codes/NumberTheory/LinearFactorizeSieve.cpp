void linearFactorizeSieve() {
  fore (i, 2, N) {
    if (factor[i] == 0) 
      factor[i] = i, primes.pb(i);
    for (int p : primes) {
      if (p > factor[i] || lli(i) * p >= N)
        break;
      factor[i * p] = p;
    }
  }
}