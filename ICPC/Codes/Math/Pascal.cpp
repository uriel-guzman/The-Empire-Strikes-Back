fore (i, 0, N) {
  c[i][0] = c[i][i] = 1;
  for (int j = 1; j <= i; j++)
    c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
}
