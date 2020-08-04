lli gcd(lli a, lli b) {
  return b ? gcd(b, a % b) : a;
}