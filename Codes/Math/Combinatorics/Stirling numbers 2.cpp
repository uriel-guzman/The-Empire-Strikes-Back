Mint stirling2(int n, int k) {
  Mint sum = 0;
  fore (i, 0, k + 1)
    sum += fpow<Mint>(-1, i) * choose(k, i)
           * fpow<Mint>(k - i, n);
  return sum * ifac(k);
};