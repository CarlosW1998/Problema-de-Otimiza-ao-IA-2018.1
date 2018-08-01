#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3);

int main()
{
  clock_t begin = clock();


  srand(time(NULL));
  int a;

  printf("%.2f\n", gain(90, 90, 90, 90, 90, 90));
  clock_t end = clock();
  printf("%.2f\n", (double)(end - begin) / (double)CLOCKS_PER_SEC);
  return 0;

}

// double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3)
// {
//   char* message_fmt = "http://localhost:8080/antenna/simulate?phi1=%d&theta1=%d&phi2=%d&theta2=%d&phi3=%d&theta3=%d";
//   char message[1024];
//   double result;
//   FILE* comunicationw = fopen("mensagens.txt", "w");
//   FILE* comunicationr = fopen("mensagens.txt", "r");
//   sprintf(message,message_fmt,phi1,theta1,phi2,theta2,phi3,theta3);
//   fprintf(comunicationw, "%s", message);
//   system("python request.py");
//   fscanf(comunicationr, "%.f", &result);
//   printf("%f\n", result);
//
// }
double gain(int phi1, int theta1, int phi2, int theta2, int phi3, int theta3)
{
    const char *message[1024];
    double result = 2.0;
    sprintf(message,"curl http://localhost:8080/antenna/simulate?phi1=%d\\&theta1=%d\\&phi2=%d\\&theta2=%d\\&phi3=%d\\&theta3=%d > temp.txt",phi1,theta1,phi2,theta2,phi3,theta3);
    system(message);
    FILE* arch = (FILE*)fopen("temp.txt", "r");
    fscanf(arch, "%s", message);
    sscanf(message, "%lf", &result);
    return result;

}
