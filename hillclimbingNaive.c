#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define Euler 2.7182818284590452353
#define debug 1
double finalgain;
//Passa os 3 angulos, devolve o ganho
double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3);

//Encontra o melhor resultado
double hillclimbing();

int main()
{
  clock_t begin = clock();
  srand(time(NULL));
  int a;
  printf("%.2f\n", hillclimbing());
  clock_t end = clock();
  printf("%.2f\n", (double)(end - begin) / (double)CLOCKS_PER_SEC);
  return 0;

}

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

void recursionGenerate(int* modifyPath, int* finalPath, int a)
{
  if(a == 6)
  {
    double thisgain = gain(modifyPath[0], modifyPath[1], modifyPath[2], modifyPath[3], modifyPath[4], modifyPath[5]);
    if(thisgain > finalgain)
    {
      finalgain = thisgain;
      int b;
      for(b = 0; b < 6; b++) finalPath[b] = modifyPath[b];
    }
    return;
  }
  modifyPath[a] = (modifyPath[a] + 1 < 360)? modifyPath[a]+1 : 0;
  recursionGenerate(modifyPath, finalPath, a+1);
  modifyPath[a] = (modifyPath[a] - 1 >= 0)? modifyPath[a]-1 : 359;
  recursionGenerate(modifyPath, finalPath, a+1);
  modifyPath[a] = (modifyPath[a] - 1 >= 0)? modifyPath[a]-1 : 359;
  recursionGenerate(modifyPath, finalPath, a+1);
  modifyPath[a] = (modifyPath[a] + 1 < 360)? modifyPath[a]+1 : 0;
}


double hillclimbing()
{
  int pathbestgain[6], auxpath[6], a, random = 10000;
  double bestgain, previous;
  for(a = 0; a < 6; a++)
  {
    pathbestgain[a] = rand()%360;
    auxpath[a] = pathbestgain[a];
  }
  bestgain = gain(pathbestgain[0] ,pathbestgain[1], pathbestgain[2], pathbestgain[3], pathbestgain[4], pathbestgain[5]);
  finalgain = bestgain;
  while(random > 0)
  {
    if(rand()%1000 < random)
    {
      for(a = 0; a < 6; a++) auxpath[a] = rand()%360;
    }
    if(rand()%2) random--;
    previous = bestgain;
    recursionGenerate(auxpath, pathbestgain, 0);
    for(a = 0; a < 6; a++) auxpath[a] = pathbestgain[a];
    bestgain = finalgain;
  }
  for(a = 0; a < 3; a++)printf("%d %d\n", pathbestgain[a*2], pathbestgain[a*2+1]);
  return bestgain;
}
