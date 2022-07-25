#include <stdio.h> 

double newtonMethod(double x, double px, double qx) {
  return x - (px/qx);
}

double horner(double x, double *pxCoeficients, int size, double *out) {
  for(int i = 0; i < size; i++) {
    if(i == 0) {
      *out = *pxCoeficients;
      continue;
    }

    double parcel = *(out + i - 1) * x;

    *(out + i) = parcel + *(pxCoeficients + i);
  } 

  return *(out + (size - 1)); // last item of the array, represents px(x);
}


int main() {
  double guess = 1.5; // arbitrary initial x guess
  int functionDegree;

  scanf("%d", &functionDegree);

  double initialCoeficients[functionDegree + 1];

  for(int i = 0; i < functionDegree + 1; i++) 
    scanf("%lf", &initialCoeficients[i]);

  double partialCoeficients[functionDegree + 1]; // variable coeficient array resultant of the horner method
  double lastCoeficients[functionDegree];

  double px = 1; // arbitrary > error number
  double error = 0.000001; // 10^-5

  while(px > error) {
    printf("x = %.16f\n", guess);
    px = horner(guess, initialCoeficients, functionDegree + 1, partialCoeficients); // result of f(guess)
    
    for(int i = 0; i < functionDegree + 1; i++)
      printf(" b%d: %.16f ", functionDegree - i, partialCoeficients[i]);

    if(px < error) {
      printf("\nf(x) = %.16f\nf(x) < err\n", px);
      printf("Final Aproximation = %.16f\n", guess);
      break;
    }
    
    printf("\n");

    double qx = horner(guess, partialCoeficients, functionDegree, lastCoeficients); // result of f'(guess)
                                                                                    //
    for(int i = 0; i < functionDegree; i++)
      printf(" c%d: %.16f ", functionDegree - 1 - i, lastCoeficients[i]);

    printf("\nf(x) = %.16f\n", px);

    guess = newtonMethod(guess, px, qx); // next x guess approx
    printf("new x = %.16f\n\n", guess);
  }

  return 0;
}
