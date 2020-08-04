lli lcm(lli a, lli b) {
  return a / gcd(a, b) * b;
}