#include <iostream>
#include<omp.h>

#define N 500000
#define chunk 100
#define show 100

void printArray(float *d);

int main() {
    std::cout << "Sumando Arreglos en paralelo!\n" << std::endl;
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    int chunks = chunk;

    double start = omp_get_wtime();

    #pragma omp parallel for \
        shared(a, b, c, chunks) private(i) \
        schedule(static, chunks)
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

        double end = omp_get_wtime();

    std::cout << "Tamaño de cada Array: " << N  << std::endl;
    std::cout << "Tiempo de procesamiento (suma paralela): " << (end - start) << " segundos\n";
    std::cout << "Hilos max disponibles: " << omp_get_max_threads() << "\n" << std::endl;
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo a: " << std::endl;
    printArray(a);
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo b: " << std::endl;
    printArray(b);
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo c: " << std::endl;
    printArray(c);
}

void printArray(float *d)
{
    for (int x = 0; x < show; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}
