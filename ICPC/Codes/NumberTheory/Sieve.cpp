bitset<N> isPrime;
vi primes;

void getPrimes() {
  isPrime.set();
  isPrime[0] = isPrime[1] = 0;
  for (int i = 2; i * i < N; ++i) if (isPrime[i])
    for (int j = i * i; j < N; j += i)
      isPrime[j] = 0;
  fore (i, 2, N) 
    if (isPrime[i])
      primes.pb(i);
}