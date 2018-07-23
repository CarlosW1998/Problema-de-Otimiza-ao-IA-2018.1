#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define Euler 2.7182818284590452353
double norm(double x)
{
  return x / 36.0 - 5.0;
}

double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3)
{
  double x = norm((double)phi1);
  double y = norm((double)theta1);
  double gain1 = sin(x) + cos(y);

  x = norm((double)phi2);
  y = norm((double)theta2);
  double gain2 = y*sin(x) - x*cos(y);

  x = norm((double)phi3);
  y = norm((double)theta3);
  double r = sqrt(x * x + y * y);
  double gain3 = sin(x * x + 3.0 * y * y) / (0.1 + r * r) + (x * x + 5 * y * y) * pow(Euler, (1.0 - r * r)) / 2.0;

  return 4.0 * gain1 + gain2 + 4.0 *gain3;
}


int main()
{
  printf("%.6f\n", gain(1, 1, 1, 1, 1, 1));
  return 0;

}
