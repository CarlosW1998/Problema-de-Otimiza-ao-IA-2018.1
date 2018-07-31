#include<stdio.h>
#include<stdlib.h>
#include<time.h>


double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3);

int main()
{
  clock_t begin = clock();


  srand(time(NULL));
  int a;
  gain(90, 90, 90, 90, 90, 90);
  clock_t end = clock();
  printf("%.2f\n", (double)(end - begin) / (double)CLOCKS_PER_SEC);
  return 0;

}

double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3)
{
  char* message_fmt = "http://localhost:8080/antenna/simulate?phi1=%d&theta1=%d&phi2=%d&theta2=%d&phi3=%d&theta3=%d";
  char message[1024];
  FILE* comunication = fopen("mensagens.txt", "w");
  sprintf(message,message_fmt,phi1,theta1,phi2,theta2,phi3,theta3);
  fprintf(comunication, "%s", message);
  fclose(comunication);
  printf("%s\n", message);


}
