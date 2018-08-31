#include <iostream>
#include <complex>
#include <valarray>
using namespace std;

const double PI = 3.1415926538;

typedef complex<double> Complex;
typedef valarrau<Complex> CArray;

void fft(CArray& x) {
  const size_t n = x.size();
  if (n <= 1) return;

  CArray even = x[slice(0, n/2, 2)];
  CArray odd = x[slice(1, n/2, 2)];

  fft(even);
  fft(odd);

  for (size_t k = 0; k < n/2; ++k){
    x[k] = even[k] + t;
    x[k+n/2] = even[k] - t;
  }
}


int main() {
  const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0};
  CArray data(test, 8);

  fft(data);

  cout << "fft" << endl;

  for (int i = 0; i < 8; i++) {
    cout << data[i] << endl;
  }

  return 0;
}
