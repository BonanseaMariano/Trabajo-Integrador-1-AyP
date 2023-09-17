#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//----------------------------CONSTANTES DEFINIDAS---------------------------------
#define JUGADORES_MAX 10
#define INTENTOS_MAX 10
#define CIFRAS_NUM 5

//-------------------------------STRUCTS------------------------------
struct Jugador
{
    char nombre[30];
    int intentos;
};

//----------------------------DECLARACION DE FUNCIONES---------------------------------
void cargar_jugador(struct Jugador *jugador);
void saludo_e_instrucciones(char nombre[30]);
void generador_numero_random(int *numeroAdivinar);
void juego_principal(struct Jugador *jugador);
void input_y_separar_cifras(int *numeroInput);

void altualizar_ranking(struct Jugador *jugador,struct Jugador *jugadores); //Aca va a haber que pasarle como parametros el jugador y el arreglo de jugadores
void impresion_ranking(struct Jugador *jugadores);//Aca va a haber que pasarle como parametro el arreglo de jugadores

//------------------------------MAIN-------------------------------
int main(){
    srand(getpid()); //Semilla aleatoria para numero random
    
    //Cuando fucione para uno hay que hacer un arreglo de jugadores[JUGADORES_MAX] para el leaderboard, y hay que 
    //tener en cuenta lo de como vamos a acomodar el arreglo cuando entra un puntaje nuevo que debe
    //desplazar a los otros o no (Parecido al problema que hay con el Ej7Tp2)
    struct Jugador jugador;
    
    int op = 1; // Variable de opcion para saber si quiere jugar denuevo o no

    do
    {
        //Aca iria la parte inicial del juego

        printf("\t---- FIN DE LA PARTIDA ----\n");
        printf("\tRANKING DE JUGADORES:\n");
        //altualizar_ranking();
        //impresion_ranking();
        do
        {
            printf("\tFin del juego, desea jugar denuevo (0:No/1:Si)");
            scanf("%i",op);
        } while (op!=1||op!=0); //Validacion que unicamente pueda poner si o no

    } while (op!=0); //Si quiere jugar denuevo itera

    printf("\t---- FIN DEL JUEGO, GRACIAS POR JUGAR! ----\n");
    return 0;
}

//------------------------------CARGAR JUGADOR-------------------------------
void cargar_jugador(struct Jugador *jugador){
    char auxchar[30];
    //Es posible la validacion si se quiere
    printf("Ingresa tu nombre!:\n");
    scanf("%[^\n]s",auxchar);

    strcpy(jugador->nombre, auxchar);
    saludo_e_instrucciones(auxchar);
}

//----------------------------------SALUDO E INSTRUCCIONES-----------------------------
void saludo_e_instrucciones(char nombre[30]){
    printf("\tBienvenido %s\n!", nombre);
    printf("Tendras %d intentos para poder decifrar un numero de %d cifras ingresando de a %d cifras, buena suerte!\n",INTENTOS_MAX,CIFRAS_NUM,CIFRAS_NUM);
}

//---------------------------GENERADOR NUMERO RANDOM A ADIVINAR----------------------------------
void generador_numero_random(int *numeroAdivinar){
    for (int i = 0; i < CIFRAS_NUM; i++)
    {
        numeroAdivinar[i] = rand() % 10;
    }
}

//---------------------------PARTE PRINCIPAL DEL JUEGO---------------------------------
void juego_principal(struct Jugador *jugador){
    int numeroAdivar[CIFRAS_NUM]; //Arrglo del numero a adivinar
    generador_numero_random(numeroAdivar);
    int numeroInput[CIFRAS_NUM]; //Arrglo del numero ingresado por el usuario para cada intento
    jugador->intentos =  INTENTOS_MAX; //Inicializo los intentos
    input_y_separar_cifras(numeroInput);

}

//--------------------------------INPUT Y SEPARAR CIFRAS----------------------------
void input_y_separar_cifras(int *numeroInput){
    int num, temp, i;
    int arr[CIFRAS_NUM]; //Arrglo auxiliar del numero ingresado para su validacion

    do
    {
        i = 0; //Inicializo contador de cifras para validacion
        printf("Ingrese un entero de exactamente 5 cifras:\n");
        scanf("%d", &num);

        temp = num;

        while (temp != 0) {
            arr[i] = temp % 10;
            temp /= 10;
            i++;
        }

        if (i != CIFRAS_NUM) {
            printf("El numero ingresado no tiene exactamente 5 cifras, ingrese un numero valido.\n");
            return 1;
        }
    } while (i != CIFRAS_NUM);
    
    //Una vez paso la validacion lo asigno para pasar a la comparacion con el de adivinar | memcpy(arreglo_destino, arreglo_origen, tamano * sizeof(int));
    memcpy(numeroInput, arr, CIFRAS_NUM * sizeof(int));
}

//--------------------------------ACTUALIZAR RANKING----------------------------
void altualizar_ranking(struct Jugador *jugador,struct Jugador *jugadores){

}

//--------------------------------IMPRESION RANKING----------------------------
void impresion_ranking(struct Jugador *jugadores){
    
}