#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

double phi_raide(double x, double u) {
  return -50.0 * (u - cos(x));
}

double exact_raide(double x) {
  return -2500.0/2501.0 * exp(-50.0*x) + 2500.0/2501.0 * cos(x) + 50.0/2501.0 * sin(x);
}

void euler_explicite(int N, double u0, double h, double *solution) {
  solution[0] = u0;
  for (int n = 1; n <= N; n++) {
    double x_n = (n - 1) * h;
    solution[n] = solution[n - 1] + h * phi_raide(x_n, solution[n - 1]);
  }
}

void euler_implicite(int N, double u0, double h, double *solution) {
  solution[0] = u0;
  for (int n = 1; n <= N; n++) {
    double x_n = n * h;
    solution[n] = (solution[n - 1] + 50.0 * h * cos(x_n)) / (1.0 + 50.0 * h);
  }
}

void dump_trajectory(const char* filename, int N, double h, double u0) {
  ofstream f(filename);
  f << "x,u_ex,u_im,u_exact\n";
  double *sol_ex = static_cast<double*>(calloc(N + 1, sizeof(double)));
  double *sol_im = static_cast<double*>(calloc(N + 1, sizeof(double)));
  euler_explicite(N, u0, h, sol_ex);
  euler_implicite(N, u0, h, sol_im);
  for (int n = 0; n <= N; n++) {
    double x_n = n * h;
    f << x_n << "," << sol_ex[n] << "," << sol_im[n] << "," << exact_raide(x_n) << "\n";
  }
  free(sol_ex);
  free(sol_im);
}

int main() {
  double u0 = 0.0;
  double b = 2.0; 

  ofstream file("errors_raide.csv");
  file << "h,err_ex,err_im\n";

  for (int i = 0; i < 6; i++) {
    double h = pow(10, -i);
    int N = static_cast<int>(b / h);
    if (N < 1) continue;

    double *sol_ex = static_cast<double*>(calloc(N + 1, sizeof(double)));
    double *sol_im = static_cast<double*>(calloc(N + 1, sizeof(double)));

    euler_explicite(N, u0, h, sol_ex);
    euler_implicite(N, u0, h, sol_im);

    double exact_final = exact_raide(N * h);
    double err_ex = fabs(sol_ex[N] - exact_final);
    double err_im = fabs(sol_im[N] - exact_final);

    file << h << "," << err_ex << "," << err_im << "\n";

    free(sol_ex);
    free(sol_im);
  }
  file.close();

  dump_trajectory("traj_h01.csv", 20, 0.1, 0.0);
  dump_trajectory("traj_h001.csv", 200, 0.01, 0.0);
  return 0;
}

