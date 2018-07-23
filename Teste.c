#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define Euler 2.7182818284590452353
#define debug 1
int finalgain;
//Passa os 3 angulos, devolve o ganho
double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3);

//Encontra o melhor resultado
double hillclimbing();

int main()
{
  srand(time(NULL));
  hillclimbing();
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
    if(debug)
    {
      int z;
      for(z = 0; z < 6; z++) printf("%d ", modifyPath[z]);
      printf("\n");
    }
    int thisgain = gain(modifyPath[0], modifyPath[1], modifyPath[2], modifyPath[3], modifyPath[4], modifyPath[5]);
    if(thisgain > finalgain)
    {
      finalgain = thisgain;
      int b;
      for(b = 0; b < 6; b++) finalPath[b] = modifyPath[b];
    }
    return;
  }
  modifyPath[a] += 1;
  recursionGenerate(modifyPath, finalPath, a+1);
  modifyPath[a] -=2;
  recursionGenerate(modifyPath, finalPath, a+1);
  modifyPath[a] += 1;
}


double hillclimbing()
{
  int pathbestgain[6], auxpath[6], a;
  double bestgain;
  for(a = 0; a < 6; a++)
  {
    pathbestgain[a] = rand()%360;
    auxpath[a] = pathbestgain[a];
  }
  if(debug){
    for(a = 0; a < 6; a++) printf("%d ", pathbestgain[a]);
    printf("\n\n");
  }
  bestgain = gain(pathbestgain[0] ,pathbestgain[1], pathbestgain[2], pathbestgain[3], pathbestgain[4], pathbestgain[5]);
  finalgain = bestgain;
  recursionGenerate(auxpath, pathbestgain, bestgain);

}
