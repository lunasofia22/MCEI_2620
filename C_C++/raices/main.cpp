#include <iostream>
#include <iomanip>
#include <cmath> //libreria matematica
#include <gsl/gsl_roots.h> //libreria raices
#include <gsl/gsl_errno.h> //libreria para indicar diferentes estados

double f(double x, void *params) { //creacion funcion llamada f
  return x*x*x - 5*x +1; //funcion a hallar las raices
}

int main() {
  const gsl_root_fsolver_type *T; //creacion variable llamada T 
  gsl_root_fsolver *s; //creacion variable llamada s, solucionador de raices 
  gsl_function F; //creacion estructura llamada F 
  F.function = &f; //aqui se le dice a GSL la funcion F 
  F.params = nullptr; //indica que no vamos a usar parametros adicionales para la funcion F
  double x_lo = 0.0; //limite inferior del intervalo
  double x_hi = 1.0; //limite superior del intervalo
  T = gsl_root_fsolver_falsepos; //se le indica a GSL que se va a usar el metodo de Brent  
  s = gsl_root_fsolver_alloc(T); //creacion del solucionador 
  gsl_root_fsolver_set(s, &F, x_lo, x_hi); //se le da todo lo necesario a GSL
  std::cout << "iter\t" << "inf\t" << "sup\t" << "raiz\n"; //imprime encabezado de la tabla

  int status; //guarda estado del proceso 
  int iter = 0; //contador de iteraciones
  int max_iter = 100; //limite de iteraciones
  double r; //se guarda la raiz encontrada

  do {
	iter++; //aumenta numero de iteraciones
	status = gsl_root_fsolver_iterate(s); //Ejecuta la iteracion 
	r = gsl_root_fsolver_root(s); //obtiene la raiz encontrada
	x_lo = gsl_root_fsolver_x_lower(s); //nuevo limite inferior del intervalo
	x_hi = gsl_root_fsolver_x_upper(s); //nuevo limite superior del intervalo
	std::cout << iter << "\t" << x_lo << "\t" << x_hi << "\t" << r << "\n"; //muestra resultados
        status = gsl_root_test_interval( x_lo, x_hi, 0.0, 1e-8); //comprueba precision
  } while(status == GSL_CONTINUE && iter < max_iter);

  std::cout << "\nRaiz encontrada = " << r << std::endl; gsl_root_fsolver_free(s); //imprime valores en la tabla
  return 0;
}

