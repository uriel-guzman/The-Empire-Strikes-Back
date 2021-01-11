template <class T>
using Mat = vector<vector<T>>;

template <class T>
Mat<T> operator * (Mat<T> &A, Mat<T> &B) {
  Mat<T> C(sz(A), vector<T>(sz(B[0])));
  fore (k, 0, sz(A[0])) 
    fore (i, 0, sz(A))
      fore (j, 0, sz(B[0]))
        C[i][j] += A[i][k] * B[k][j];      
  return C;
}

template <class T>
Mat<T> fpow(Mat<T> &A, lli n) {
  Mat<T> C(sz(A), vector<T>(sz(A)));
  fore (i, 0, sz(A))
    C[i][i] = 1;
  for (; n > 0; n >>= 1) {
    if (n & 1) C = C * A;
    A = A * A;
  }
  return C;
}
