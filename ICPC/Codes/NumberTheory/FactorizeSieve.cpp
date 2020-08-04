void factorizeSieve() {
  iota(factor, factor + N, 0);
  for (int i = 2; i * i < N; i++) if (factor[i] == i)
    for (int j = i * i; j < N; j += i)
      factor[j] = i;
}