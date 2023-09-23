#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

//----------------------------CONSTANTES DEFINIDAS---------------------------------
//Parametros modificables del juego
#define JUGADORES_MAX 10
#define INTENTOS_MAX 10
#define CIFRAS_NUM 5

//Colores
#define COLOR_VERDE 2
#define COLOR_AMARILLO 14
#define COLOR_BLANCO 7
#define COLOR_CELESTE 11
#define COLOR_ROJO 12

//-------------------------------STRUCTS------------------------------
struct Jugador
{
    char nombre[30];
    int intentos;
};


//----------------------------DECLARACION DE FUNCIONES---------------------------------
//Funciones de inicio del juego
void cargar_jugador(struct Jugador *jugador);
void saludo_e_instrucciones(char nombre[30]);
void generador_numero_random(int *numeroAdivinar);

//Funciones durante el juego
int juego_principal(struct Jugador *jugador);
void input_y_separar_cifras(int *numeroInput);

//Funciones de acierto
int acierto_completo(int *numeroAdivinar, int *numeroInput);
void acierto_num_iguales(int *input, int *numObjetivo);
void acierto_num_incluido(int *numObjetivo, int *input, int *posicion);

//Funciones del raking de jugadores
void limpieza_leaderboard(struct Jugador *leaderboard);
void altualizar_ranking(struct Jugador *jugador,struct Jugador *leaderboard); //Aca va a haber que pasarle como parametros el jugador y el arreglo de jugadores
void impresion_ranking(struct Jugador *leaderboard);//Aca va a haber que pasarle como parametro el arreglo de jugadores (el parametro esta mal puesto todavia)

//Funciones extras
void impresion_arreglo_numero(int *arregloNum);
void setColor(int color);



//------------------------------MAIN-------------------------------
int main(){
    srand(getpid()); //Semilla aleatoria para numero random
    
    //Cuando fucione para uno hay que hacer un arreglo de jugadores[JUGADORES_MAX] para el leaderboard, y hay que 
    //tener en cuenta lo de como vamos a acomodar el arreglo cuando entra un puntaje nuevo que debe
    //desplazar a los otros o no (Parecido al problema que hay con el Ej7Tp2)
    struct Jugador jugador;
    struct Jugador leaderboard[JUGADORES_MAX];
    limpieza_leaderboard(leaderboard);

    int op = 1; // Variable de opcion para saber si quiere jugar denuevo o no

    //Iterador de juego (Si juega nuevamente o no)
    do
    {
        //Titulo del juego
        printf("\t\t");
        setColor('G');
        printf("**** Adivina el numero! ****");
        setColor(COLOR_BLANCO);

        //Ingreso del jugador
        cargar_jugador(&jugador);

        //Aca el jugador juega y se ve si gano (se carga al ranking si es que su puntaje es sufiente) o no (no se carga al ranking pero si se imprime)
        if (juego_principal(&jugador) == 1)//Significa que gano
        {

            //Hay que hacer la cuenta INTENTOS_MAX - jugador.intentos para saber cuantos intentos utilizo, ya que es distinto de los intentos restantes
            jugador.intentos = INTENTOS_MAX - jugador.intentos;
            
            //Actualizo ranking
            altualizar_ranking(&jugador,leaderboard);
        }
        
        setColor(COLOR_AMARILLO);
        printf("\n\t\t---- FIN DE LA PARTIDA ----\n");
        //Impprimo el ranking
        impresion_ranking(leaderboard);
        setColor(COLOR_BLANCO);

        do
        {
            printf("\n\t---- Desea jugar denuevo? (0:No/1:Si) ----\n");
            scanf("%d",&op);
        } while (op!=1 && op!=0); //Validacion que unicamente pueda poner si o no

    } while (op==1); //Si quiere jugar denuevo itera

    printf("\n\n\t---- FIN DEL JUEGO, GRACIAS POR JUGAR! ----\n");
    sleep(5);
    return 0;
}


//------------------------------CARGAR JUGADOR (LLAMADA POR main)-------------------------------
void cargar_jugador(struct Jugador *jugador){
    char auxchar[30];
    printf("\n\nIngresa tu nombre!:\n");
    scanf(" %[^\n]s",auxchar);
    strcpy(jugador->nombre, auxchar);
    saludo_e_instrucciones(auxchar);
}


//----------------------------------SALUDO E INSTRUCCIONES (LLAMADA POR cargar_jugador)-----------------------------
void saludo_e_instrucciones(char nombre[30]){
    printf("\nBienvenido %s!\n", nombre);
    printf("Tendras %d intentos para poder decifrar un numero de %d cifras ingresando de a %d cifras, buena suerte!\n",INTENTOS_MAX,CIFRAS_NUM,CIFRAS_NUM);
}


//---------------------------GENERADOR NUMERO RANDOM A ADIVINAR (LLAMADA POR juego_principal)----------------------------------
void generador_numero_random(int *numeroAdivinar){

    //Para que la primera cifra del numero a adivinar no comience con 0
    numeroAdivinar[0] = (rand()%9)+1;

    //Resto del numero a adivinar
    for (int i = 1; i < CIFRAS_NUM; i++)
    {
        numeroAdivinar[i] = rand() % 10;
    }
}


//---------------------------PARTE PRINCIPAL DEL JUEGO (LLAMADA POR main)---------------------------------
int juego_principal(struct Jugador *jugador){
    jugador->intentos =  INTENTOS_MAX; //Inicializo los intentos
    int numeroAdivinar[CIFRAS_NUM]; //Arrglo del numero a adivinar
    generador_numero_random(numeroAdivinar); //Inicializo el numero random a adivinar
    int numeroInput[CIFRAS_NUM]; //Arrglo del numero ingresado por el usuario para cada intento
    
    //Se repite mientras el jugador tenga intentos disponibles o acierte al numero a adivinar
    do
    {
        input_y_separar_cifras(numeroInput);

        if (acierto_completo(numeroInput, numeroAdivinar)==0) //Acerto al numero
        {
            setColor(COLOR_VERDE);
            printf("\n\tFelicitaciones, acertaste al numero: ");
            impresion_arreglo_numero(numeroAdivinar);
            printf("!\n\t\tCantidad de intentos: %i\n", (INTENTOS_MAX - jugador->intentos)); 
            setColor(COLOR_BLANCO);

            return 1;//El jugador gano

        }else{ //No acerto al numero todavia
            jugador->intentos--;
            setColor(COLOR_ROJO);
            printf("\tX No era el numero, intentos restantes: %d  X\n",jugador->intentos);
            setColor(COLOR_BLANCO);

            acierto_num_iguales(numeroInput,numeroAdivinar);
            
            setColor(COLOR_CELESTE);
            printf("\n//Cheat de numero a adivinar: ");
            impresion_arreglo_numero(numeroAdivinar);
            setColor(COLOR_BLANCO);
            printf("\n");

        }
    } while (jugador->intentos>0);

    //Se acabaron los intentos del jugador
    setColor(COLOR_ROJO);
    printf("\tMala suerte, perdiste! :( el numero a adivinar era: ");
    impresion_arreglo_numero(numeroAdivinar);
    setColor(COLOR_BLANCO);
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
        int j=(CIFRAS_NUM-1); //Inicializo contador de ubicacion de digitos
        printf("\nIngrese un entero de exactamente 5 cifras:\n");
        scanf("%d", &num);

        temp = num;

        while (temp != 0) {
            arr[j] = temp % 10;
            temp /= 10;
            i++;
            j--;
        }

        if (i != CIFRAS_NUM) {
            setColor(COLOR_ROJO);
            printf("\tXX El numero ingresado no tiene exactamente 5 cifras, ingrese un numero valido XX\n");
            setColor(COLOR_BLANCO);
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


//--------------------------------ACIERTO PARCIAL DIGITOS IGUALES (LLAMADA POR juego_principal)----------------------------
void acierto_num_iguales(int *input, int *numObjetivo)
{
    int posiciones[CIFRAS_NUM];
    
    //Inicializo el arreglo de posiciones
    for (int i = 0; i < CIFRAS_NUM; i++){
        posiciones[i] = -1;
    }

    //Impresion de ambos numeros para checkear (Borrar desp)
    printf("\nDebugg:\n");
    impresion_arreglo_numero(input);
    printf("\n");
    impresion_arreglo_numero(numObjetivo);
    printf("\n");

    for (int i = 0; i < CIFRAS_NUM; i++)
    {
        //Checkeo si hay digitos en posiciones correctas
        if (input[i] == numObjetivo[i])
        {
            setColor(COLOR_VERDE);
            printf("El digito %d (%d* posicion) es correcto!\n",input[i],(i+1));
            setColor(COLOR_BLANCO);
        
        //Chequeo si el digito existe pero esta ubicado en otra posicion    
        }else{
            if(input[i] != numObjetivo[i]){
                for (int j = 0; j < CIFRAS_NUM; j++){ //o es un while?
                    if (posiciones[j] == -1){
                        posiciones[j] = i;
                        printf("posicion distinta:%d\n", posiciones[j]);
                        break;
                    }
                }
            }
        }
    }
    acierto_num_incluido(input, numObjetivo, posiciones);
}


//--------------------------------ACIERTO PARCIAL NUMERO IGUAL (LLAMADA POR juego_principal)----------------------------
void acierto_num_incluido(int *input, int *numObjetivo, int *posicion){
    int i = 0;
    while(posicion[i] != -1 && i < CIFRAS_NUM){
        printf("entro en num_incluido");
        for (int j = 0; j < CIFRAS_NUM; j++)
        {
            //Funca mal
            if (posicion[i] == j)
            {
                setColor(COLOR_AMARILLO);
                printf(" que es esto no se %d\n",input[i]);
                setColor(COLOR_BLANCO);
                break;
            }
        }
        i++;
    }
    
}


//--------------------------------IMPRESION ARREGLO NUMERO (LLAMADA POR juego_principal)----------------------------
void impresion_arreglo_numero(int *arregloNum){
    //Para imprimir el numero generado aleatoriamente o el ingresado por el usuario (segun que se pase por parametro)
    for (int i = 0; i < CIFRAS_NUM; i++)
    {
        printf("%i", arregloNum[i]);
    }
}


//--------------------------------LIMPIAR  (LLAMADA POR main)----------------------------
void limpieza_leaderboard(struct Jugador *leaderboard){
    for (int i = 0; i < JUGADORES_MAX; i++)
    {
        strcpy(leaderboard[i].nombre, "");
        leaderboard[i].intentos = INTENTOS_MAX;
    }
}


//--------------------------------ACTUALIZAR RANKING (LLAMADA POR main)----------------------------
void altualizar_ranking(struct Jugador *jugador,struct Jugador *leaderboard){
    int i;
    
    //Busco la posicion del ranking en donde debo colocar
    for ( i = 0; i < JUGADORES_MAX && jugador->intentos>leaderboard[i].intentos; i++);

    //Si se encuentra dentro de las primeras 10 posiciones acomodo a los demas para ponerlo
    if (i<JUGADORES_MAX)
    {
        //Desplazo a la derecha
        for (int j = JUGADORES_MAX-1; j > i; j--)
        {
            leaderboard[j].intentos = leaderboard[j-1].intentos;
            strcpy(leaderboard[j].nombre, leaderboard[j-1].nombre);
        }

        //Coloco el jugador en la posicion que quedo
        leaderboard[i].intentos = jugador->intentos;
        strcpy(leaderboard[i].nombre, jugador->nombre);
    }
    
}


//--------------------------------IMPRESION RANKING (LLAMADA POR main)----------------------------
void impresion_ranking(struct Jugador *leaderboard){
    printf("\n\t----- RANKING DE JUGADORES -----\n");
    for (int i = 0; i < JUGADORES_MAX; i++)
    {
        if (strcmp(leaderboard[i].nombre,"")!=0)
        {
            printf("%i* - %s (%i intentos)\n",(i+1), leaderboard[i].nombre, leaderboard[i].intentos); 
        }
    }
}


//--------------------------------CAMBIAR COLOR DE LA TERMINAL----------------------------
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}