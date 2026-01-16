#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Структура для параметров модели Лотки-Вольтерра
struct LVdata {
  double alpha, beta, gamma, delta;
  double x0, y0;
  double t_start, t_end, dt;
};

// Сама система дифференциальных уравнений
void phi(double x, double y, const LVdata& data, double& dx, double& dy) {
  dx = (data.alpha - data.beta * y) * x;
  dy = (-data.gamma + data.delta * x) * y;
}

// Явная схема Эйлера (1 порядок)
void euler(const LVdata& data, const string& filename) {
  ofstream file(filename);
  file << "t,x,y\n";
  double t = data.t_start, x = data.x0, y = data.y0;
  file << t << "," << x << "," << y << "\n";
  while (t < data.t_end) {
    double dx, dy;
    phi(x, y, data, dx, dy);
    x += dx * data.dt;
    y += dy * data.dt;
    t += data.dt;
    file << t << "," << x << "," << y << "\n";
  }
  file.close();
}

// Явная схема Рунге-Кутты-2 (2 порядок)
void rk2(const LVdata& data, const string& filename) {
  ofstream file(filename);
  file << "t,x,y\n";
  double t = data.t_start, x = data.x0, y = data.y0;
  file << t << "," << x << "," << y << "\n";
  while (t < data.t_end) {
    double k1_x, k1_y;
    phi(x, y, data, k1_x, k1_y);
    double k2_x, k2_y;
    phi(x + k1_x * data.dt, y + k1_y * data.dt, data, k2_x, k2_y);
    x += (data.dt / 2.0) * (k1_x + k2_x);
    y += (data.dt / 2.0) * (k1_y + k2_y);
    t += data.dt;
    file << t << "," << x << "," << y << "\n";
  }
  file.close();
}

// Явная схема Рунге-Кутты-4 (4 порядок)
void rk4(const LVdata& data, const string& filename) {
  ofstream file(filename);
  file << "t,x,y\n";
  double t = data.t_start, x = data.x0, y = data.y0;
  file << t << "," << x << "," << y << "\n";
  while (t < data.t_end) {
    double k1_x, k1_y;
    phi(x, y, data, k1_x, k1_y);
    double k2_x, k2_y;
    phi(x + 0.5 * data.dt * k1_x, y + 0.5 * data.dt * k1_y, data, k2_x, k2_y);
    double k3_x, k3_y;
    phi(x + 0.5 * data.dt * k2_x, y + 0.5 * data.dt * k2_y, data, k3_x, k3_y);
    double k4_x, k4_y;
    phi(x + data.dt * k3_x, y + data.dt * k3_y, data, k4_x, k4_y);
    x += (data.dt / 6.0) * (k1_x + 2 * k2_x + 2 * k3_x + k4_x);
    y += (data.dt / 6.0) * (k1_y + 2 * k2_y + 2 * k3_y + k4_y);
    t += data.dt;
    file << t << "," << x << "," << y << "\n";
  }
  file.close();
}

// Медленная модель: волки-зайцы
void test1() {
  LVdata data;
  data.alpha = 0.4;
  data.beta = 0.01;
  data.gamma = 0.3;
  data.delta = 0.005;
  double x_eq = data.gamma / data.delta;
  double y_eq = data.alpha / data.beta;
  cout << "Медленная модель" << endl;
  cout << "Точка равновесия: X=" << x_eq << ", Y=" << y_eq << endl;
  data.x0 = x_eq;  // Жертвы
  data.y0 = y_eq;  // Хищники
  data.t_start = 0.0;
  data.t_end = 100.0;
  data.dt = 0.05;
  data.x0 *= 2.;
  // euler(data, "data/test2.csv");
  rk2(data, "data/test1.csv");
  rk4(data, "data/test2.csv");
  data.x0 /= 2.;
  data.y0 *= 2;
  rk2(data, "data/test3.csv");
  rk4(data, "data/test4.csv");
}

// Медленная модель: инфузории-дидинии(кто это воообще???)
void test2() {
  LVdata data;
  data.alpha = 13.0;
  data.beta = 0.2;
  data.gamma = 7.0;
  data.delta = 0.1;
  double x_eq = data.gamma / data.delta;
  double y_eq = data.alpha / data.beta;
  cout << "Быстрая модель" << endl;
  cout << "Точка равновесия: X=" << x_eq << ", Y=" << y_eq << endl;
  data.x0 = x_eq;  // Жертвы
  data.y0 = y_eq;  // Хищники
  data.t_start = 0.0;
  data.t_end = 20.0;
  data.dt = 0.05;
  data.x0 *= 2.;
  // euler(data, "data/test2.csv");
  rk2(data, "data/test5.csv");
  rk4(data, "data/test6.csv");
  data.x0 /= 2.;
  data.y0 *= 2;
  rk2(data, "data/test7.csv");
  rk4(data, "data/test8.csv");
}

int main() {
  test1();
  test2();
  return 0;
}