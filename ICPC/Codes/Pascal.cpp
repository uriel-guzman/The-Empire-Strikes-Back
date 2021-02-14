fore (i, 0, N)
  c[i][0] = c[i][i] = 1;

fore (i, 1, N)
  fore (j, 1, i)
    c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
