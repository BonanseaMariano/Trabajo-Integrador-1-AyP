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
int juego_principal(struct Jugador *jugador);
void input_y_separar_cifras(int *numeroInput);
int acierto_completo(int *numeroAdivinar, int *numeroInput);
void acierto_parcial(int *numeroAdivinar, int *numeroInput);

void impresion_arreglo_numero(int *arregloNum);

void altualizar_ranking(struct Jugador *jugador,struct Jugador *jugadores); //Aca va a haber que pasarle como parametros el jugador y el arreglo de jugadores
void impresion_ranking(struct Jugador *jugadores);//Aca va a haber que pasarle como parametro el arreglo de jugadores (el parametro esta mal puesto todavia)


//------------------------------MAIN-------------------------------
int main(){
    srand(getpid()); //Semilla aleatoria para numero random
    
    //Cuando fucione para uno hay que hacer un arreglo de jugadores[JUGADORES_MAX] para el leaderboard, y hay que 
    //tener en cuenta lo de como vamos a acomodar el arreglo cuando entra un puntaje nuevo que debe
    //desplazar a los otros o no (Parecido al problema que hay con el Ej7Tp2)
    struct Jugador jugador;
    
    int op = 1; // Variable de opcion para saber si quiere jugar denuevo o no

    //Iterador de juego (Si juega nuevamente o no)
    do
    {
        //Ingreso del jugador
        cargar_jugador(&jugador);

        //Aca el jugador juega y se ve si gano (se carga al ranking si es que su puntaje es sufiente) o no (no se carga al ranking pero si se imprime)
        if (juego_principal(&jugador) == 1)//Significa que gano
        {

            //Hay que hacer la cuenta INTENTOS_MAX - jugador.intentos para saber cuantos intentos utilizo, ya que es distinto de los intentos restantes
            jugador.intentos = INTENTOS_MAX - jugador.intentos;
            
            //altualizar_ranking();
        }
        
        printf("\t---- FIN DE LA PARTIDA ----\n");
        printf("\tRANKING DE JUGADORES:\n");
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


//------------------------------CARGAR JUGADOR (LLAMADA POR main)-------------------------------
void cargar_jugador(struct Jugador *jugador){
    char auxchar[30];
    //Es posible la validacion si se quiere
    printf("Ingresa tu nombre!:\n");
    scanf("%[^\n]s",auxchar);

    strcpy(jugador->nombre, auxchar);
    saludo_e_instrucciones(auxchar);
}

//----------------------------------SALUDO E INSTRUCCIONES (LLAMADA POR cargar_jugador)-----------------------------
void saludo_e_instrucciones(char nombre[30]){
    printf("\tBienvenido %s\n!", nombre);
    printf("Tendras %d intentos para poder decifrar un numero de %d cifras ingresando de a %d cifras, buena suerte!\n",INTENTOS_MAX,CIFRAS_NUM,CIFRAS_NUM);
}

//---------------------------GENERADOR NUMERO RANDOM A ADIVINAR (LLAMADA POR juego_principal)----------------------------------
void generador_numero_random(int *numeroAdivinar){
    for (int i = 0; i < CIFRAS_NUM; i++)
    {
        numeroAdivinar[i] = rand() % 10;
    }
}

//---------------------------PARTE PRINCIPAL DEL JUEGO (LLAMADA POR main)---------------------------------
int juego_principal(struct Jugador *jugador){
    jugador->intentos =  INTENTOS_MAX; //Inicializo los intentos
    int numeroAdivinar[CIFRAS_NUM]; //Arrglo del numero a adivinar
    generador_numero_random(numeroAdivinar); //Parametros por referencia, Inicializo el numero random a adivinar
    int numeroInput[CIFRAS_NUM]; //Arrglo del numero ingresado por el usuario para cada intento
    
    //Se repite mientras el jugador tenga intentos disponibles o acierte al numero a adivinar
    do
    {
        input_y_separar_cifras(numeroInput); //Parametros por referencia

        if (acierto_completo(numeroInput, numeroAdivinar)==0) //Le pego al numero
        {
            printf("\tFelicitaciones, acertaste al numero: ");
            impresion_arreglo_numero(numeroAdivinar);
            printf("!\n\tCantidad de intentos: %i\n", (INTENTOS_MAX - jugador->intentos)); //Hay que hacer la cuenta INTENTOS_MAX - jugador->intentos para saber cuantos intentos utilizo, ya que es distinto de los intentos restantes
            return 1;//El jugador gano

        }else{ //No le pego al numero todavia

            //Aca hay que poner una funcion que diga si acerto a algun numero misma posicion o numero pero en distinta posicion *******
            //acierto_parcial(numeroAdivinar,numeroInput);

            jugador->intentos--;
        }
    } while (jugador->intentos>0);

    //Aca ya es que se le acabaron los intentos
    printf("\tMala suerte, perdiste! el numero a adivinar era: ");
    impresion_arreglo_numero(numeroAdivinar);
    printf("\n");
    return 0; //El jugador perdio
}

//--------------------------------INPUT Y SEPARAR CIFRAS (LLAMADA POR juego_principal)----------------------------
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
        }
    } while (i != CIFRAS_NUM);
    
    //Una vez paso la validacion lo asigno para pasar a la comparacion con el de adivinar | memcpy(arreglo_destino, arreglo_origen, tamano * sizeof(int));
    memcpy(numeroInput, arr, CIFRAS_NUM * sizeof(int));
}

//--------------------------------ACIERTO COMPLETO (LLAMADA POR juego_principal)----------------------------
int acierto_completo(int *numeroAdivinar, int *numeroInput){
    //Comparacion principal (acierto del numero completo)
    for (int i = 0; i < CIFRAS_NUM; i++)
    {
        if (numeroAdivinar[i]!=numeroInput[i]) //Si existe al menos 1 numero no exactamente igual prendo la bandera
        {
            return 1;
        }
    }
    return 0;
}

//--------------------------------ACIERTO PARCIAL (LLAMADA POR juego_principal)----------------------------
void acierto_parcial(int *numeroAdivinar, int *numeroInput){

    //Aca hay que ver si acerto a algun numero misma posicion o numero pero en distinta posicion

}

//--------------------------------IMPRESION ARREGLO NUMERO (LLAMADA POR juego_principal)----------------------------
void impresion_arreglo_numero(int *arregloNum){
    //Para imprimir el numero generado aleatoriamente o el ingresado por el usuario (segun que se pase por parametro)
    for (int i = 0; i < CIFRAS_NUM; i++)
    {
        printf("%i", arregloNum[i]);
    }
}

//--------------------------------ACTUALIZAR RANKING (LLAMADA POR main)----------------------------
void altualizar_ranking(struct Jugador *jugador,struct Jugador *jugadores){

}

//--------------------------------IMPRESION RANKING (LLAMADA POR main)----------------------------
void impresion_ranking(struct Jugador *jugadores){
    
}
