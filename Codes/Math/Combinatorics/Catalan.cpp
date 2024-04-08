catalan[0] = 1LL;
fore (i, 0, N) {
  catalan[i + 1] = catalan[i] * lli(4 * i + 2) % MOD
                   * fpow(i + 2, MOD - 2) % MOD;
}
