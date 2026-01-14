#include <cmath>
#include <complex>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

using cd = complex<double>;
using vec = vector<cd>;

constexpr inline bool IsPowerOf2(int n) { return (n & (n - 1)) == 0; }

vec DFT(const vec& signal) {
  int n = signal.size();
  vec result(n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      result[i] +=
          cd(cos(2 * M_PI * i * j / n), sin(-2 * M_PI * i * j / n)) * signal[j];
  return result;
}

vec IDFT(const vec& signal) {
  int n = signal.size();
  vec result(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      result[i] +=
          cd(cos(2 * M_PI * i * j / n), sin(2 * M_PI * i * j / n)) * signal[j];
    result[i] /= n;
  }
  return result;
}

class W_m {
 public:
  W_m(int m) : m_(m) {
    matrix_.resize(m_);
    for (int i = 0; i < m_; ++i) {
      matrix_[i].resize(m_);
      for (int j = 0; j < m_; ++j) {
        matrix_[i][j] =
            cd(cos(-2 * M_PI * i * j / m_), sin(-2 * M_PI * i * j / m_));
      }
    }
  }

  vec operator*(const vec& v) {
    if (v.size() != m_)
      throw invalid_argument("Vector size must be equal to m");
    vec result(m_);
    for (int i = 0; i < m_; ++i)
      for (int j = 0; j < m_; ++j) result[i] += matrix_[i][j] * v[j];
    return result;
  }

 private:
  int m_;
  vector<vec> matrix_;
};

vec FFT(const vec& signal) {
  /*int N = signal.size();
  if (!IsPowerOf2(N))
    throw invalid_argument("Size of input signal must be a power of 2");
  int M = N / 2;
  vec u(M);
  vec v(M);
  for (int k = 0; k < M; ++k) {
    u[k] = signal[2 * k];
    v[k] = signal[2 * k + 1];
  }
  vec u_ = W_m(M) * u;
  vec v_ = W_m(M) * v;
  vec result(N);
  for (int m = 0; m < M; ++m) {
    result[m] =
        u_[m] + cd(cos(-2 * M_PI * m / N), sin(-2 * M_PI * m / N)) * v_[m];
    result[m + M] =
        u_[m] - cd(cos(-2 * M_PI * m / N), sin(-2 * M_PI * m / N)) * v_[m];
  }
  return result;*/
  size_t n = signal.size(), m = n / 2;
  vec res(n);
  cd exp, u, v;
  for (size_t i = 0; i < m; ++i) {
    u = {0, 0};
    v = {0, 0};
    for (size_t j = 0; j < m; ++j) {
      exp = {cos(-2 * M_PI * i * j / m), sin(-2 * M_PI * i * j / m)};
      u += signal[2 * j] * exp;
      v += signal[2 * j + 1] * exp;
    }
    exp = {cos(-2 * M_PI * i / n), sin(-2 * M_PI * i / n)};
    res[i] = u + exp * v;
    res[i + m] = u - exp * v;
  }
  return res;
}

vec IFFT(const vec& signal) {
  int N = signal.size(); /*
   if (!IsPowerOf2(N))
     throw invalid_argument("Size of input signal must be a power of 2");
   vec z = FFT(signal);
   vec result(N);
   for (int i = 0; i < N; ++i) result[i] = z[N - i] / static_cast<double>(N);
   return result;*/
  vec res = FFT(signal);
  cd tmp;
  for (int i = 1; i <= N / 2; ++i) {
    tmp = res[i];
    res[i] = res[N - i] / static_cast<double>(N);
    res[N - i] = tmp / static_cast<double>(N);
  }
  res[0] /= static_cast<double>(N);
  return res;
}

// Свёртка комплексных векторов
vec Convolution(const vec& vec1, const vec& vec2) {
  size_t N = vec1.size();
  vec result = FFT(vec1);
  vec help = FFT(vec2);
  for (size_t i = 0; i < N; ++i) help[i] *= result[i];
  return IFFT(help);
}

// Циклический сдвиг
vec Shift(int k, const vec& signal) {
  size_t N = signal.size();
  vec res(N, 0.0);
  for (int i = 0; i < N; ++i) res[i] = signal[i - k + ((i - k < 0) ? N : 0)];
  return res;
}

// Сгущающая выборка в 2^l раз
vec DSample(int l, const vec& signal) {
  int step = 1 << l;  // 2^l
  size_t N = signal.size() / step;
  vec res(N, 0.0);
  for (size_t i = 0; i < N; ++i) res[i] = signal[i * step];
  return res;
}

// Разрежающая выборка в 2^l раз
vec USample(int l, const vec& signal) {
  int step = 1 << l;
  size_t N = signal.size() * step;
  vec result(N, 0.0);
  for (size_t i = 0; i < N; ++i)
    result[i] = (i % step == 0) ? signal[i / step] : 0;
  return result;
}

constexpr inline double amplitude(const cd& z) {
  return sqrt(z.real() * z.real() + z.imag() * z.imag());
}

// Сохранение сигнала в .csv
void SaveSignal(const vec& signal, const string& filename, int type = -1) {
  ofstream out(filename);
  if (type == -1) {
    out << "z" << endl;
    for (cd x : signal) out << x.real() << endl;
  } else {
    out << "x,z" << endl;
    for (int i = 0; i < signal.size(); ++i) {
      out << (1 << type) * i << "," << signal[i].real() << endl;
    }
  }
}

// Скалярное произведение комплексных векторов
cd Scalar(const vec& vec1, const vec& vec2) {
  size_t N = vec1.size();
  cd res(0, 0);
  for (size_t i = 0; i < N; ++i)
    res += vec1[i] * cd(vec2[i].real(), -vec2[i].imag());
  return res;
}

class Wavelet {
 private:
  vec u, v;
  vector<vec> f, g;

 public:
  enum class BasisType { Haar = 1, DaubechiesD6, Complex_Shennon };

  // Конструтор создает отцовский и материнский вейвлеты
  Wavelet(size_t signal_size, BasisType type)
      : u(signal_size, 0.), v(signal_size, 0.), f(), g() {
    switch (type) {
      case BasisType::Haar: {
        if (signal_size < 2)
          throw runtime_error("error: haar basis size must be 2 at least");
        u[0] = 1. / sqrt(2);
        u[1] = u[0];
        v[0] = u[0];
        v[1] = -v[0];
        break;
      }
      case BasisType::DaubechiesD6: {
        // Коэффициенты u (Low-pass)
        double k = sqrt(2) / 32, a = 1 - sqrt(10), b = 1 + sqrt(10),
               c = sqrt(5 + 2 * sqrt(10));
        vec tmp = {k * (b + c),
                   k * (2 * a + 3 * b + 3 * c),
                   k * (6 * a + 4 * b + 2 * c),
                   k * (6 * a + 4 * b - 2 * c),
                   k * (2 * a + 3 * b - 3 * c),
                   k * (b - c)};
        for (int i = 0; i < tmp.size(); ++i) u[i] = tmp[i];
        v[0] = -u[1];
        v[1] = u[0];
        v[signal_size - 1] = u[2];
        v[signal_size - 2] = -u[3];
        v[signal_size - 3] = u[4];
        v[signal_size - 4] = -u[5];
        break;
      }
      case BasisType::Complex_Shennon: {
        cd val;
        u[0] = v[0] = 1. / sqrt(2);
        for (size_t i = 1; i < signal_size; ++i) {
          u[i] = {sqrt(2) / signal_size * cos(M_PI * i / signal_size) *
                      sin(M_PI * i / 2) / sin(M_PI * i / signal_size),
                  -sqrt(2) / signal_size * sin(M_PI * i / signal_size) *
                      sin(M_PI * i / 2) / sin(M_PI * i / signal_size)};
          v[i] = pow(-1, i) * u[i];
        }
        break;
      }
      default: {
        throw runtime_error("error: unknown basis type");
      }
    }
  }

 private:
  // Построение системы вэйвлет фильтров
  void WaveletFilters(size_t stages) {
    size_t n = u.size();
    vector<vec> u_filters(stages), v_filters(stages);
    u_filters[0] = u;
    v_filters[0] = v;
    for (size_t i = 1; i < stages; ++i) {
      size_t mx_idx = 1 << i;
      size_t sz = n / mx_idx;
      u_filters[i].resize(sz);
      v_filters[i].resize(sz);
      for (size_t j = 0; j < sz; ++j)
        for (size_t k = 0; k < mx_idx; ++k) {
          u_filters[i][j] += u_filters[0][j + k * n / mx_idx];
          v_filters[i][j] += v_filters[0][j + k * n / mx_idx];
        }
    }
    f.resize(stages);
    g.resize(stages);
    f[0] = v_filters[0];
    g[0] = u_filters[0];
    for (size_t i = 1; i < stages; ++i) {
      f[i] = Convolution(g[i - 1], USample(i, v_filters[i]));
      g[i] = Convolution(g[i - 1], USample(i, u_filters[i]));
    }
  }

  /**
   *  Построение вэйвлет базисов
   * @param stage - номер этапа
   * @param psi - вектор отцовский (высокочастотный) вейвлет базиса
   * @param phi - вектор материнский (низкочастотный) вейвлет базиса
   */
  void WaveletBasis(size_t stage, vector<vec>& psi, vector<vec>& phi) {
    size_t n = u.size();
    size_t sz = n / (1 << stage);
    if (g.size() < stage) WaveletFilters(stage + 1);
    psi.resize(sz);
    phi.resize(sz);
    for (size_t i = 0; i < sz; ++i) {
      int idx = (1 << stage) * i;
      psi[i] = Shift(idx, f[stage - 1]);
      phi[i] = Shift(idx, g[stage - 1]);
    }
  }

 public:
  /**
   * Фаза анализа
   * @param stage - номер этапа
   * @param signal - вектор сигнала
   * @param k_psi - коэффициенты разложения по отцовский (высокочастотный)
   * вейвлет базиса
   * @param k_phi - коэффициенты разложения по материнский (низкочастотный)
   * вейвлет базиса
   */
  void AnalysisPhase(size_t stage, const vec& signal, vec& k_psi, vec& k_phi) {
    vector<vec> psi, phi;
    WaveletBasis(stage, psi, phi);
    size_t sz = psi.size();
    for (size_t i = 0; i < sz; ++i) {
      k_psi.push_back(Scalar(signal, psi[i]));
      k_phi.push_back(Scalar(signal, phi[i]));
    }
  }

  /**
   * Фаза синтеза
   * @param stage - номер этапа
   * @param signal - вектор сигнала
   * @param k_psi - коэффициенты разложения по отцовский (высокочастотный)
   * вейвлет базиса
   * @param k_phi - коэффициенты разложения по материнский (низкочастотный)
   * вейвлет базиса
   * @param P, Q - ортоганальные проекции сигнала на множества psi, phi на stage
   * этапе
   * @param Recovery - восстановленный сигнал
   */
  void SynthesisPhase(size_t stage, const vec& signal, const vec& k_psi,
                      const vec& k_phi, vec& P, vec& Q, vec& Recovery) {
    vector<vec> psi, phi;
    WaveletBasis(stage, psi, phi);
    size_t sz = psi.size(), n = u.size();
    for (size_t data_idx = 0; data_idx < n; ++data_idx) {
      cd p_stage(0.), q_stage(0.);
      for (size_t basis_idx = 0; basis_idx < sz; ++basis_idx) {
        p_stage += k_phi[basis_idx] * phi[basis_idx][data_idx];
        q_stage += k_psi[basis_idx] * psi[basis_idx][data_idx];
      }
      P.push_back(p_stage);
      Q.push_back(q_stage);
      Recovery.push_back(P[data_idx] + Q[data_idx]);
    }
  }
};

vec GenerateSignal1(int n, double a, double b, double omega2) {
  int N = 1 << n;
  vec signal(N);
  for (int i = 0; i < N; ++i) {
    if (i < N / 4) {
      signal[i] = 0;
    } else if (i <= N / 2) {
      signal[i] = a + b * cos(2 * M_PI * omega2 * i / N);
    } else if (i <= 3 * N / 4) {
      signal[i] = 0;
    } else {
      signal[i] = a + b * cos(2 * M_PI * omega2 * i / N);
    }
  }
  return signal;
}

vec GenerateSignal2(int n, double a, double b, double omega1, double omega2,
                    double phi) {
  size_t s = 1 << n;
  vec signal(s);
  for (size_t i = 0; i < s; ++i)
    signal[i] = a * cos(2 * M_PI * omega1 * i / s + phi) +
                b * cos(2 * M_PI * omega2 * i / s);
  return signal;
}

void test1() {
  /* Пример */
  int n = 9;
  double a = 2.5;
  double b = 0.2;
  double omega1 = 3;
  double omega2 = 125;
  double phi = M_PI / 2;
  string dir = "data1/";
  vec signal = GenerateSignal1(n, a, b, omega2);
  SaveSignal(signal, dir + "signal1.csv");
  cout << "-------------\n";
  Wavelet w(signal.size(), Wavelet::BasisType::DaubechiesD6);
  for (int stage = 1; stage <= 4; ++stage) {
    vec k_psi, k_phi, P, Q, Recovery;
    w.AnalysisPhase(stage, signal, k_psi, k_phi);
    SaveSignal(k_phi, dir + "kPhi_" + to_string(stage) + ".csv", stage);
    SaveSignal(k_psi, dir + "kPsi_" + to_string(stage) + ".csv", stage);
    w.SynthesisPhase(stage, signal, k_psi, k_phi, P, Q, Recovery);
    SaveSignal(P, dir + "P_" + to_string(stage) + ".csv");
    SaveSignal(Q, dir + "Q_" + to_string(stage) + ".csv");
    SaveSignal(Recovery, dir + "R_" + to_string(stage) + ".csv");
  }
}

void test2() {
  /* Пример */
  int n = 10;
  double a = 2.5;
  double b = 0.13;
  double omega1 = 3;
  double omega2 = 185;
  double phi = M_PI / 2;
  string dir = "data2/";
  vec signal = GenerateSignal1(n, a, b, omega2);
  SaveSignal(signal, dir + "signal1.csv");
  cout << "-------------\n";
  Wavelet w(signal.size(), Wavelet::BasisType::Haar);
  for (int stage = 1; stage <= 4; ++stage) {
    vec k_psi, k_phi, P, Q, Recovery;
    w.AnalysisPhase(stage, signal, k_psi, k_phi);
    SaveSignal(k_phi, dir + "kPhi_" + to_string(stage) + ".csv");
    SaveSignal(k_psi, dir + "kPsi_" + to_string(stage) + ".csv");
    w.SynthesisPhase(stage, signal, k_psi, k_phi, P, Q, Recovery);
    SaveSignal(P, dir + "P_" + to_string(stage) + ".csv");
    SaveSignal(Q, dir + "Q_" + to_string(stage) + ".csv");
    SaveSignal(Recovery, dir + "R_" + to_string(stage) + ".csv");
  }
}

void test3() {
  /* Пример */
  int n = 9;
  double a = 2.87;
  double b = 0.26;
  double omega1 = 2;
  double omega2 = 194;
  double phi = M_PI / 6;
  string dir = "data3/";
  vec signal = GenerateSignal1(n, a, b, omega2);
  SaveSignal(signal, dir + "signal1.csv");
  cout << "-------------\n";
  Wavelet w = Wavelet(signal.size(), Wavelet::BasisType::Haar);
  for (int stage = 1; stage <= 4; ++stage) {
    vec k_psi, k_phi, P, Q, Recovery;
    w.AnalysisPhase(stage, signal, k_psi, k_phi);
    SaveSignal(k_phi, dir + "kPhi_" + to_string(stage) + ".csv", stage);
    SaveSignal(k_psi, dir + "kPsi_" + to_string(stage) + ".csv", stage);
    w.SynthesisPhase(stage, signal, k_psi, k_phi, P, Q, Recovery);
    SaveSignal(P, dir + "P_" + to_string(stage) + ".csv");
    SaveSignal(Q, dir + "Q_" + to_string(stage) + ".csv");
    SaveSignal(Recovery, dir + "R_" + to_string(stage) + ".csv");
  }
  cout << "-------------\n";
  dir = "data4/";
  w = Wavelet(signal.size(), Wavelet::BasisType::DaubechiesD6);
  for (int stage = 1; stage <= 4; ++stage) {
    vec k_psi, k_phi, P, Q, Recovery;
    w.AnalysisPhase(stage, signal, k_psi, k_phi);
    SaveSignal(k_phi, dir + "kPhi_" + to_string(stage) + ".csv", stage);
    SaveSignal(k_psi, dir + "kPsi_" + to_string(stage) + ".csv", stage);
    w.SynthesisPhase(stage, signal, k_psi, k_phi, P, Q, Recovery);
    SaveSignal(P, dir + "P_" + to_string(stage) + ".csv");
    SaveSignal(Q, dir + "Q_" + to_string(stage) + ".csv");
    SaveSignal(Recovery, dir + "R_" + to_string(stage) + ".csv");
  }
  cout << "-------------\n";
  dir = "data5/";
  w = Wavelet(signal.size(), Wavelet::BasisType::Complex_Shennon);
  for (int stage = 1; stage <= 4; ++stage) {
    vec k_psi, k_phi, P, Q, Recovery;
    w.AnalysisPhase(stage, signal, k_psi, k_phi);
    SaveSignal(k_phi, dir + "kPhi_" + to_string(stage) + ".csv", stage);
    SaveSignal(k_psi, dir + "kPsi_" + to_string(stage) + ".csv", stage);
    w.SynthesisPhase(stage, signal, k_psi, k_phi, P, Q, Recovery);
    SaveSignal(P, dir + "P_" + to_string(stage) + ".csv");
    SaveSignal(Q, dir + "Q_" + to_string(stage) + ".csv");
    SaveSignal(Recovery, dir + "R_" + to_string(stage) + ".csv");
  }
}

int main() {
  test3();
  return 0;
}