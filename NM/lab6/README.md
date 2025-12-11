## Практическое задание №4

Выполнил: Веселый Д. А.

Группа: пми-32

Вариант: 7

### **Цель**:

Сформировать практические навыки применения алгоритмов прямого и обратного дискретного преобразования Фурье (DFT и IDFT) и их быстрых реализаций (FFT и IFFT) для анализа одномерных сигналов.

### **Формулировка задания.**

1. На языке программирования С++ реализовать алгоритмы прямого и обратного преобразований Фурье (DFT и IDFT), быстрые алгоритмы прямого и обратного преобразований Фурье для вектора чётной длины (FFT и IFFT). Арифметические операции выполнять при использовании шаблонного класса ```std::complex<double>```.
2. Задать $N = 2^n, n \in \N$ отсчётов зашумлённого сигнала вида:
$$z(j)=A\cos(2\pi\omega_1j/N+\phi)+B\cos(2\pi\omega_2j/N)$$
3. Выполнить для полученного набора данных дискретное преобразование Фурье. Замерить время выполнения кода при использовании DFT и FFT. Заполнить таблицу (отразить только те частоты m, на которых отличны от нуля амплитудный или фазовый спектры)
4. Найти высокочастотные шумовые компоненты сигнала и обнулите их коэффициенты $\^{z}$ в DFT.
5. Вычислить IDFT от модифицированного результата
DFT (с обнулёнными шумовыми компонентами).
Изобразить на одном графике исходный набор значений и результат фильтрации после IDFT. Графики должны быть непрерывными, используйте сплайны
6. Задать $N=2^n, n\in\N$ отсчётов зашумлённого сигнала вида. Получится ли эффективно решить задачу о фильтрации данного сигнала с помощью DFT? Ответ обоснуйте.
$$z(j)=\begin{cases}
0, 0 \leq j < N/4, \\
A+B\cos(2\pi\omega_2j/N), N/4\leq j \leq N/2, \\
0, N/2 < j \leq 3N/4, \\
A+B\cos(2\pi\omega_2j/N), 3N/4<j\leq N.
\end{cases}$$


### Исходные данные

|№ варианта|n|A|B|$\omega_1$|$\omega_2$|$\phi$|
|---|---|---|---|---|---|---|
|7|9|2.87|0.26|2|194|$\pi$/6|

### Задания 1-5:
В соответствии с вариантом исходный сигнал будет иметть вид: $$z(j)=2.87\cos(4\pi j/N + \pi/6)+0.26\cos(388\pi j/N)$$
Выполлняем DFT этого сигнала. Результаты приведены в таблице:

|$m$|Re $z$|Re $\^z$|Im $\^z$|\|$\^z$\||$\phi$|
|---|---|---|---|---|---|
|2| 2.42484| 636.286| 367.36| 734.72 |0.523599|
|194| 1.29554| 66.56| -1.15064e-12| 66.56 |-1.72872e-14|
|318| -1.571| 66.56| 3.86002e-12| 66.56 |5.79931e-14|
|510| 2.56567| 636.286| -367.36| 734.72 -|0.523599|

Как и ожидалось, ненулевые амплитуды в спектре сигнала совпали с $\omega_1$ и $\omega_2$, а также сопряжёнными сигналами $2^n-\omega_1, 2^n-\omega_2$. Высокочастотные компоненты 194 и 318. После обнуления значений этих компонент и обратного дискретного преобразования Фурье (IDFT) на выходе получаем чистый сигнал.
![alt text](image.png)

Сравнение времени работы обычного дискретного преобразования Фурье (DFT): **42мс** и быстрого преобразования Фурье (FFT): **28мс** 
 
### Задание 6:
Для начала рассмотрим сгенерированный сигнал:
![alt text](image-1.png)
Видно, что сигнал состоит из двух значений: 0 и A(2.87), при этом отрезки A зашумлены. Стандартное дискретное преобразование Фурье здесь **не поможет**, так как мы по сути приведем константые значения к периодической функции, шумы таким образом найти не получится. Для решения такой задачи преобразованием Фурье нужно локализовать применение только на зашумленные участки.

### Вывод
В ходе выполнения работы я сформировал практические навыки применения алгоритмов прямого и обратного дискретного преобразования Фурье (DFT и IDFT) и их быстрых реализаций (FFT и IFFT) для анализа одномерных сигналов.

### Приложение
#### Код программы (C++): main.cc
```cpp
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
      non_zero.push_back(i);
    }
  }
  for (auto i : non_zero) dft2[i] = 0;
  auto idft2 = IDFT(dft2);
  SaveSignal(idft2, "idft2.csv");
  return 0;
}
```
Код визуализации заданий 1-5 на python:
```python
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('signal.csv')
df['x'] = range(0, df.size)
a = df.plot(x='x', y='z', grid=True, figsize=(16, 10), style='.-', color='blue', label='Исходный сигнал')
df_idft = pd.read_csv('idft.csv')
df_idft['x'] = df['x']
df_idft.plot(x='x', y='z', style='.-', grid=True, color='red', ax=a, label='Только низкие частоты')
a.spines['bottom'].set_position('zero')
a.spines['left'].set_position('zero')
```

Код визуализации задания 6 на python:
```python
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('signal2.csv')
df['x'] = range(0, df.size)
df.plot(x='x', y='z', grid=True, figsize=(16, 10), style='.-', color='black')
```