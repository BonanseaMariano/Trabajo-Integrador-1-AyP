#include <stdio.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()

// función principal para encontrar el tiempo de ejecución de un programa en C
int main()
{
    //Para testear, no es parte del clock
    int check = 0;

    // para almacenar el tiempo de ejecución del código
    double cronometro = 0.0;

    clock_t inicio_cronometro = clock();

    // Aca en vez del sleep iria la parte de los intentos
    //sleep(3);
    do
    {
        printf("2+2=");
        scanf("%d", &check);
    } while (check != 4);
    


    clock_t fin_cronometro = clock();

    // calcula el tiempo transcurrido encontrando la diferencia (end - begin) y
    // dividiendo la diferencia por CLOCKS_PER_SEC para convertir a segundos
    cronometro += (double)(fin_cronometro - inicio_cronometro) / CLOCKS_PER_SEC;

    printf("\nEl tiempo transcurrido entre intentos fue de %.1f segundos", cronometro); 
    sleep(5);

    return 0;
}