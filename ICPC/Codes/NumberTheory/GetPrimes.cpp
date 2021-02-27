bitset<P> prime;
vi primes;

void getPrimes() {
  prime.set();
  prime[0] = prime[1] = 0;

  for (int i = 2; i * i < P; ++i)
    if (prime[i])
      for (int j = i * i; j < P; j += i)
        prime[j] = 0;

  fore (i, 2, P)
    if (prime[i])
      primes.pb(i);
}
