#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define Euler 2.7182818284590452353


//Encontra o melhor resultado
void genericAlgorithm();

int main()
{
  clock_t begin = clock();


  srand(time(NULL));
  int a;
  genericAlgorithm();
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
int* cross(int* path1, int* path2)
{
  int a;
  int* desc = (int*)malloc(sizeof(int)*6);
  for(a = 0; a < 6; a++)
  {
    if(rand()%6 == 0) desc[a] = path2[a];
    else desc[a] = path1[a];
  }
  if(rand()%200 == 0) desc[rand()%6] = rand()%360;
  return desc;
}
int* genereteDescendentes(int** pop, double* cust)
{
  int a, b = 999, c = 0;
  int* aux;
  for(a = 0; a < 50; a++)
  {
    aux = cross(pop[a], pop[a+1]);
    pop[b] = aux;
    cust[b] = gain(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5]);
    b--;
    aux = cross(pop[a+1], pop[a]);
    pop[b] = aux;
    cust[b] = gain(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5]);
    b--;
  }
}
void genericAlgorithm()
{
  int** population = (int**)malloc(sizeof(int*)*1000);
  double* cust = (double*)malloc(sizeof(double)*1000);
  int a, b, loop = 1000;
  for(a = 0; a < 1000; a++)
  {
    population[a] = (int*)malloc(sizeof(int)*6);
    for(b = 0; b < 6; b++)population[a][b] = rand()%360;
    cust[a] = gain(population[a][0], population[a][1], population[a][2], population[a][3], population[a][4], population[a][5]);
  }
  sort(population, cust, 1000);
  //for(a = 0; a < 1000; a++) printf("%.2f; ", cust[a]);
  while(loop != 0)
  {
    //printf("%.2f; ", cust[0]);
    genereteDescendentes(population, cust);
    sort(population, cust, 1000);
    loop--;
  }
  printf("%.2f : ", cust[0]);
  for(a = 0; a < 6; a++)printf("%d ", population[0][a]);
  printf("\n");
}
