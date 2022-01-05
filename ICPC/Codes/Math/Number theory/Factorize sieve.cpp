int factor[N];

void factorizeSieve() {
  iota(factor, factor + N, 0);
  for (int i = 2; i * i < N; i++)
    if (factor[i] == i)
      for (int j = i * i; j < N; j += i)
        factor[j] = i;
}

map<int, int> factorize(int n) {
  map<int, int> cnt;
  while (n > 1) {
    cnt[factor[n]]++;
    n /= factor[n];
  }
  return cnt;
}
