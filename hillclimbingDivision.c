#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define Euler 2.7182818284590452353
double finalgain;
//Passa os 3 angulos, devolve o ganho
double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3);

//Encontra o melhor resultado
double hillclimbing();

int main()
{
  clock_t begin = clock();
  srand(time(NULL));
  printf("%.2f\n", hillclimbing());
  clock_t end = clock();
  printf("%.7f\n", (double)((end - begin) / (double)CLOCKS_PER_SEC));
  return 0;

}

double norm(double x)
{
  return x / 36.0 - 5.0;
}

double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3)
{
  const char *message[1024];
  double result = 2.0;
  sprintf(message,"curl -s http://localhost:8080/antenna/simulate?phi1=%d\\&theta1=%d\\&phi2=%d\\&theta2=%d\\&phi3=%d\\&theta3=%d > temp.txt",phi1,theta1,phi2,theta2,phi3,theta3);
  system(message);
  FILE* arch = (FILE*)fopen("temp.txt", "r");
  fscanf(arch, "%s", message);
  sscanf(message, "%lf", &result);
  fclose(arch);
  return result;
}

void recursionGenerate(int* modifyPath, int* finalPath, int a, int k)
{
  if(k == 2)
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
  recursionGenerate(modifyPath, finalPath, a+1, k+1);
  modifyPath[a] = (modifyPath[a] - 1 >= 0)? modifyPath[a]-1 : 359;
  recursionGenerate(modifyPath, finalPath, a+1, k+1);
  modifyPath[a] = (modifyPath[a] - 1 >= 0)? modifyPath[a]-1 : 359;
  recursionGenerate(modifyPath, finalPath, a+1, k+1);
  modifyPath[a] = (modifyPath[a] + 1 < 360)? modifyPath[a]+1 : 0;
}
void increase(int* myPath)
{
  int a, b, c, d, e, f;
  double currentGain;
  int aux = 5;
  for(a = myPath[0]-aux; a < myPath[0]+aux; a++)
  {
    for(b = myPath[1] -aux; b < myPath[1] +aux; b++)
    {
      for(c = myPath[2] -aux; c < myPath[2] + aux; c++)
      {
        for(d = myPath[3] - aux; d < myPath[3] + aux; d++)
        {
          for(e = myPath[4] - aux; e < myPath[4] + aux; e++)
          {
            for(f = myPath[5] - aux; f < myPath[5] + aux; f++)
            {
              currentGain = gain(a, b, c, d, e, f);
              if(currentGain > finalgain)
              {
                finalgain = currentGain;
                myPath[0] = a;
                myPath[1] = b;
                myPath[2] = c;
                myPath[3] = d;
                myPath[4] = e;
                myPath[5] = f;
              }
            }
          }
        }
      }
    }
  }
}

double hillclimbing()
{
  int pathbestgain[6], auxpath[6], a, random = 10000;
  double bestgain;
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
    recursionGenerate(auxpath, pathbestgain, 0, 0);
    for(a = 0; a < 6; a++) auxpath[a] = pathbestgain[a];
    bestgain = finalgain;
  }
  random = 10000;

  while(random > 0)
  {
    if(rand()%1000 < random)
    {
      for(a = 0; a < 6; a++) auxpath[a] = rand()%360;
    }
    if(rand()%2) random--;
    recursionGenerate(auxpath, pathbestgain, 2, 0);
    for(a = 0; a < 6; a++) auxpath[a] = pathbestgain[a];
    bestgain = finalgain;
  }

  random = 10000;

  while(random > 0)
  {
    if(rand()%1000 < random)
    {
      for(a = 0; a < 6; a++) auxpath[a] = rand()%360;
    }
    if(rand()%2) random--;
    recursionGenerate(auxpath, pathbestgain, 5, 0);
    for(a = 0; a < 6; a++) auxpath[a] = pathbestgain[a];
    bestgain = finalgain;
  }
  finalgain = bestgain;
  increase(pathbestgain);
  bestgain = finalgain;

  for(a = 0; a < 3; a++)printf("%d %d\n", pathbestgain[a*2], pathbestgain[a*2+1]);
  return bestgain;
}
