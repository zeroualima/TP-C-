#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

double phi(double x, double u) {
  return 2 * x * u;
}

void resolution(int N, double u0, double h, double *solution) {
  solution[0] = u0;
  for (int n = 1; n <= N; n++) {
    double x_n = (n - 1) * h;
    solution[n] = solution[n - 1] + h * phi(x_n, solution[n - 1]);
  }
}

int main() {
  double u0;
  cout << "Entrez la condition initiale: " << flush;
  cin >> u0;

  ofstream file("errors.csv");
  file << "h,error\n";

  for (int i = 0; i < 10; i++) {
    double h = pow(10, -i);
    int N = 1 / h;
    double *solution = static_cast<double*>(calloc(N + 1, sizeof(double)));
    resolution(N, u0, h, solution);
    double err = fabs(solution[N] - exp(1.0));
    file << h << "," << err << "\n";
    free(solution);
  }
  file.close();
  return 0;
}