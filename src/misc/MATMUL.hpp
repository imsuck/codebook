template <typename T, unsigned int S, int mod>
struct Matrix {
  T m[S][S];

  Matrix(bool identity = 0) {
    for (int i = 0; i < S; ++i)
      for (int j = 0; j < S; ++j)
        m[i][j] = (i == j) ? identity : 0;
  }

  T *operator[](int i) { return m[i]; }

  const T *const operator[](int i) const { return m[i]; }

  Matrix operator*(const Matrix &rhs) {
    Matrix res(0);
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j)
        for (int k = 0; k < S; ++k)
          (res[i][j] += m[i][k] * rhs[k][j] % mod) %= mod;
    }
    return res;
  }
};

template <typename T, unsigned int S, int mod>
Matrix<T, S, mod> binpow(Matrix<T, S, mod> base,
                         long long p) {
  Matrix<T, S, mod> res(1);
  while (p) {
    if (p & 1) res = res * base;
    base = base * base;
    p >>= 1;
  }
  return res;
}