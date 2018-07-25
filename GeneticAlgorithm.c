#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define Euler 2.7182818284590452353


//Encontra o melhor resultado
double genericAlgorithm();

int main()
{
  clock_t begin = clock();


  srand(time(NULL));
  int a;
  genericAlgorithm();
  clock_t end = clock();


  //printf("%.2f\n", (double)(end - begin) / (double)CLOCKS_PER_SEC);
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
void sort(int** pop, double* cust, int size)
{
  int a, b;
  int* aux;
  double auxa;
  for(a = 0; a < size; a++)
  {
    for(b = a+1; b < size; b++)
    {
      if(cust[a] < cust[b])
      {
        aux = pop[a];
        auxa = cust[a];
        pop[a] = pop[b];
        cust[a] = cust[b];
        pop[b] = aux;
        cust[b] = auxa;
      }
    }
  }
}
void genereteDescendentes(int** pop, double* cust)
{
  int* desc1 = (int*)malloc(sizeof(int)*6);
  int* desc2 = (int*)malloc(sizeof(int)*6);
  int a;
  double auxdesc1, auxdesc2;
  for(a = 0; a < 6; a++)
  {
    if(rand()%5 == 0)
    {
      desc1[a] = pop[0][a];
      desc2[a] = pop[1][a];
    }
    else
    {
      desc1[a] = pop[1][a];
      desc2[a] = pop[0][a];
    }
  }
  for(a = 0; a < 6; a++)
  {
    printf("%d %d\n", desc1[a], desc2[a]);
  }
}
double genericAlgorithm()
{
  int a, b;
  int** popupation = (int**)malloc(sizeof(int*)*10), auxpop[6];
  double cust[10], auxcust;
  for(a = 0; a < 10; a++)
  {
    popupation[a] = (int*)malloc(sizeof(int)*6);
    for(b = 0; b <6; b++) popupation[a][b] = rand()%360;
    cust[a] = gain(popupation[a][0], popupation[a][1], popupation[a][2], popupation[a][3], popupation[a][4], popupation[a][5]);
  }
  sort(popupation, cust, 10);
  for(a = 0; a < 10; a++)
  {
    printf("%.2f - ", cust[a]);
    for(b = 0; b <6; b++) printf("%d  ", popupation[a][b]);
    printf("\n");
  }
  genereteDescendentes(popupation, cust);

  return -1;

}
