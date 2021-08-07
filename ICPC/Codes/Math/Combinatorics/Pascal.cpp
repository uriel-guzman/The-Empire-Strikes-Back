fore (i, 0, N) {
  choose[i][0] = choose[i][i] = 1;
  for (int j = 1; j <= i; j++)
    choose[i][j] = choose[i - 1][j - 1] + choose[i - 1][j];
}
