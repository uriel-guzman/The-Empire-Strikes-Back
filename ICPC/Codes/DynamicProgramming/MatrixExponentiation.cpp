// Hasta no conseguir algo mejor xd

typedef vector<vector<lli>> Mat;

Mat operator * (Mat &A, Mat &B) {
  Mat C(sz(A), vector<lli>(sz(B[0])));
  fore (k, 0, sz(A[0])) 
    fore (i, 0, sz(A))
      fore (j, 0, sz(B[0]))
        C[i][j] += A[i][k] * B[k][j];      
  return C;
}

Mat operator ^ (Mat &A, lli n) {
  Mat C(sz(A), vector<lli>(sz(A)));
  fore (i, 0, sz(A))
    C[i][i] = 1;
  for (; n > 0; n >>= 1) {
    if (n & 1) C = C * A;
    A = A * A;
  }
  return C;
}
