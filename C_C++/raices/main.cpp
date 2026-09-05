#include <iostream>
#include <iomanip>
#include <cmath> //libreria matematica
#include <gsl/gsl_roots.h> //libreria raices
#include <gsl/gsl_errno.h> //libreria para indicar diferentes estados

double f(double x, void *params) { //creacion funcion llamada f
  return x*x*x - 5*x +1; //funcion a hallar las raices
}

double df(double x, void *params) { //creacion de la derivada
  return 3*x*x - 5; //derivada de la funcion
}

void fdf(double x, void *params, double *y, double *dy) {
  *y = f(x, params);
  *dy = df(x, params);
}

int main() {
  const gsl_root_fdfsolver_type *T; //creacion variable llamada T
  gsl_root_fdfsolver *s; //creacion variable llamada s, solucionador de raices
  gsl_function_fdf FDF; //creacion estructura llamada FDF

  FDF.f = &f;
  FDF.df = &df;
  FDF.fdf = &fdf;
  FDF.params = nullptr;

  double x = 0.0;
  double x_prev = 1.0;

  T = gsl_root_fdfsolver_newton; //se indica que se va a usar Steffensen
  s = gsl_root_fdfsolver_alloc(T); //creacion del solucionador

  gsl_root_fdfsolver_set(s, &FDF, x);
  std::cout << "iter\t" << "x\t\t" << "raiz\n";

  int iter = 0;
  int max_iter = 100;
  double r;
  double r_anterior;

  do {
    iter++;

    r_anterior = x;

    // Metodo de Steffensen
    double fx = f(x, nullptr);
    double fx2 = f(x + fx, nullptr);

    r = x - (fx * fx) / (fx2 - fx);
    x = r;

    std::cout << iter << "\t" << x << "\t\t" << r << "\n";

  } while(std::abs(r - r_anterior) > 1e-8 && iter < max_iter);

  std::cout << "\nRaiz encontrada = " << r << std::endl;

  gsl_root_fdfsolver_free(s);

  return 0;
}