#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <pthread.h>
#include <mutex>
#include <random>

using namespace std;

double a,b;
long int n, n_threads;

void *calcSum(void *ret)
{
  long int iter = n / n_threads;
  double* sum = (double *) ret;
  *sum = 0.0;
  default_random_engine generator(time(0));
  uniform_real_distribution<double> distribution(a, b);
  for (long int i = 0; i < iter; i++)
    {    
      double randomX = distribution(generator);
      double funcVal = sin(randomX) / randomX;
      *sum += funcVal;
    }
  return NULL;
}

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        cerr << "ERROR: Invalid number of arguments provided. Expected 5. Provided " << argc << endl;
        return 0;
    }

    cout.precision(18); 

    a = atof(argv[1]);
    b = atof(argv[2]);
    n = atoi(argv[3]);
    n_threads = atoi(argv[4]);

    double sumValues[20];
    pthread_t threads[20];
    for (long int i = 0; i < n_threads && i < 20; i++) {
      pthread_create(&threads[i], NULL, calcSum, (void *) &sumValues[i]);
    }

    
    for (long int i = 0; i < n_threads && i < 20; i++) {
      pthread_join(threads[i], NULL);
    }

    double sum = 0.0;
    for (long int i = 0; i < n_threads && i < 20; i++) {
      sum += sumValues[i];
    }
    double integral = (b - a) * (sum / n);
    cout << integral << endl;
    
    return 1;
}
