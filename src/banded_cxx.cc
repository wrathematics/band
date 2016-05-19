// Storage reference: http://www.netlib.org/lapack/lug/node124.html
template <typename T>
static int banded_diag(const int m, const int n, const T *in, T *out)
{
  int ind_in;
  int ind_out = 0;
  
  for (ind_in=0; ind_in<m*n; ind_in+=m+1)
  {
    out[ind_out] = in[ind_in];
    ind_out++;
  }
  
  return 0;
}

template <typename T>
static int banded_gen(const int m, const int n, const int kl, const int ku, const T *in, T *out)
{
  int i, j;
  int mj;
  int ind = 0;
  

  
  return 0;
}

template <typename T>
int banded(const int m, const int n, const int kl, const int ku, const T *in, T *out)
{
  if (kl == 0 && ku == 0)
    return banded_diag(m, n, in, out);
  else
    return banded_gen(m, n, kl, ku, in, out);
}

extern "C" int banded_int(const int m, const int n, const int kl, const int ku, const int *__restrict in, int *__restrict out)
{
  return banded(m, n, kl, ku, in, out);
}

extern "C" int banded_double(const int m, const int n, const int kl, const int ku, const double *__restrict in, double *__restrict out)
{
  return banded(m, n, kl, ku, in, out);
}

// ncols is always the same as the input
extern "C" int banded_nr(const int kl, const int ku, const bool symmetric)
{
  int nrows;
  
  if (symmetric)
    nrows = kl + 1;
  else
    nrows = kl + ku + 1;
  
  return nrows;
}
