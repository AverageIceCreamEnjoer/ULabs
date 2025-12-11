#include <chrono>
#include <cmath>
#include <complex>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const double eps = 1e-6;

vector<complex<double>> GenerateSignal(int n, double a, double b, double omega1,
                                       double omega2, double phi) {
  size_t s = 1 << n;
  vector<complex<double>> signal(s);
  for (size_t i = 0; i < s; ++i)
    signal[i] = a * cos(2 * M_PI * omega1 * i / s + phi) +
                b * cos(2 * M_PI * omega2 * i / s);
  return signal;
}

void SaveSignal(const vector<complex<double>>& signal, const string& filename) {
  ofstream out(filename);
  out << "z" << endl;
  for (complex<double> x : signal) out << x.real() << endl;
}

vector<complex<double>> DFT(const vector<complex<double>>& signal) {
  int n = signal.size();
  vector<complex<double>> result(n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      result[i] += complex<double>(cos(2 * M_PI * i * j / n),
                                   sin(-2 * M_PI * i * j / n)) *
                   signal[j];
  return result;
}

vector<complex<double>> IDFT(const vector<complex<double>>& signal) {
  int n = signal.size();
  vector<complex<double>> result(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      result[i] += complex<double>(cos(2 * M_PI * i * j / n),
                                   sin(2 * M_PI * i * j / n)) *
                   signal[j];
    result[i] /= n;
  }
  return result;
}

bool IsPowerOf2(int n) { return (n & (n - 1)) == 0; }

class W_m {
 public:
  W_m(int m) : m_(m) {
    matrix_.resize(m_);
    for (int i = 0; i < m_; ++i) {
      matrix_[i].resize(m_);
      for (int j = 0; j < m_; ++j) {
        matrix_[i][j] = complex<double>(cos(-2 * M_PI * i * j / m_),
                                        sin(-2 * M_PI * i * j / m_));
      }
    }
  }

  vector<complex<double>> operator*(const vector<complex<double>>& v) {
    if (v.size() != m_)
      throw invalid_argument("Vector size must be equal to m");
    vector<complex<double>> result(m_);
    for (int i = 0; i < m_; ++i)
      for (int j = 0; j < m_; ++j) result[i] += matrix_[i][j] * v[j];
    return result;
  }

 private:
  int m_;
  vector<vector<complex<double>>> matrix_;
};

vector<complex<double>> FFT(const vector<complex<double>>& signal) {
  int N = signal.size();
  if (!IsPowerOf2(N))
    throw invalid_argument("Size of input signal must be a power of 2");
  int M = N / 2;
  vector<complex<double>> u(M);
  vector<complex<double>> v(M);
  for (int k = 0; k < M; ++k) {
    u[k] = signal[2 * k];
    v[k] = signal[2 * k + 1];
  }
  vector<complex<double>> u_ = W_m(M) * u;
  vector<complex<double>> v_ = W_m(M) * v;
  vector<complex<double>> result(N);
  for (int m = 0; m < M; ++m) {
    result[m] =
        u_[m] +
        complex<double>(cos(-2 * M_PI * m / N), sin(-2 * M_PI * m / N)) * v_[m];
    result[m + M] =
        u_[m] -
        complex<double>(cos(-2 * M_PI * m / N), sin(-2 * M_PI * m / N)) * v_[m];
  }
  return result;
}

vector<complex<double>> IFFT(const vector<complex<double>>& signal) {
  int N = signal.size();
  if (!IsPowerOf2(N))
    throw invalid_argument("Size of input signal must be a power of 2");
  vector<complex<double>> z = FFT(signal);
  vector<complex<double>> result(N);
  for (int i = 0; i < N; ++i) result[i] = z[N - i] / static_cast<double>(N);
  return result;
}

vector<complex<double>> GenerateSignal2(int n, double a, double b,
                                        double omega2) {
  int N = 1 << n;
  vector<complex<double>> signal(N);
  for (int i = 0; i < N; ++i) {
    if (i < N / 4) {
      signal[i] = 0;
    } else if (i < N / 2) {
      signal[i] = a + b * cos(2 * M_PI * omega2 * i / N);
    } else if (i < 3 * N / 4) {
      signal[i] = 0;
    } else {
      signal[i] = a + b * cos(2 * M_PI * omega2 * i / N);
    }
  }
  return signal;
}

int main() {
  int n = 9;
  double a = 2.87;
  double b = 0.26;
  double omega1 = 2;
  double omega2 = 194;
  double phi = M_PI / 6;
  /* Пример
  int n = 9;
  double a = 2.5;
  double b = 0.2;
  double omega1 = 3;
  double omega2 = 125;
  double phi = M_PI / 2;
  */
  vector<complex<double>> signal = GenerateSignal(n, a, b, omega1, omega2, phi);
  SaveSignal(signal, "signal.csv");
  auto dft_start = std::chrono::high_resolution_clock::now();
  vector<complex<double>> dft = DFT(signal);
  for (int i = 0; i < dft.size(); ++i) {
    double mag = sqrt(pow(dft[i].real(), 2) + pow(dft[i].imag(), 2));
    if (mag > eps)
      cout << i << " " << signal[i] << " " << dft[i].real() << " "
           << dft[i].imag() << " " << mag << " "
           << atan2(dft[i].imag(), dft[i].real()) << endl;
  }
  for (auto i : {194, 318}) dft[i] = 0;
  vector<complex<double>> idft = IDFT(dft);
  auto dft_time = std::chrono::high_resolution_clock::now() - dft_start;
  SaveSignal(idft, "idft.csv");
  cout << "-------------\n";
  auto fft_start = std::chrono::high_resolution_clock::now();
  vector<complex<double>> fft = FFT(signal);
  auto ifft = IFFT(fft);
  auto fft_time = std::chrono::high_resolution_clock::now() - fft_start;
  for (int i = 0; i < fft.size(); ++i) {
    double mag = sqrt(pow(fft[i].real(), 2) + pow(fft[i].imag(), 2));
    if (mag > eps)
      cout << i << " " << signal[i] << " " << fft[i].real() << " "
           << fft[i].imag() << " " << mag << " "
           << atan2(fft[i].imag(), fft[i].real()) << endl;
  }
  cout << "-------------\n";
  cout << "DFT time: "
       << chrono::duration_cast<std::chrono::milliseconds>(dft_time).count()
       << " ms\n";
  cout << "FFT time: "
       << chrono::duration_cast<std::chrono::milliseconds>(fft_time).count()
       << " ms\n";
  auto signal2 = GenerateSignal2(n, a, b, omega2);
  SaveSignal(signal2, "signal2.csv");
  auto dft2 = DFT(signal2);
  vector<int> non_zero;
  for (int i = 0; i < dft2.size(); ++i) {
    double mag = sqrt(pow(dft2[i].real(), 2) + pow(dft2[i].imag(), 2));
    if (mag > eps) {
      // cout << i << " " << signal2[i] << " " << dft2[i].real() << " "
      //      << dft2[i].imag() << " " << mag << " "
      //      << atan2(dft2[i].imag(), dft2[i].real()) << endl;
      non_zero.push_back(i);
    }
  }
  for (auto i : non_zero) dft2[i] = 0;
  auto idft2 = IDFT(dft2);
  SaveSignal(idft2, "idft2.csv");
  return 0;
}