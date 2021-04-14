Mint fac[N], ifac[N];

Mint choose(int n, int k) {
  if (n < 0 || k < 0 || n < k)
    return 0;
  return fac[n] * ifac[k] * ifac[n - k];
}

void factorial(int n) {
  fac[0] = 1;
  fore (i, 1, n)
    fac[i] = fac[i - 1] * i;
  ifac[n - 1] = fac[n - 1].inv();
  fore (i, n - 1, 0)
    ifac[i] = ifac[i + 1] * (i + 1);
}