/*
GRUPO 4.1 || AUTORES:
Santiago Julio Iglesias Portela : santiago.iglesias4@udc.es
Pablo Longueira Failde : pablo.longueira.failde@udc.es
Andrea Lama Muiño : a.lama1@udc.es
*/

#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#define UMBRAL 100
#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)

typedef void (*f)(int v[], int n);
typedef void (*f_cotas)(int n, double t);

void ordenarAux(int v[], int izq, int der);
//---------- ALGORTIMO ORDENACION POR INSERCION-------//
void ord_ins(int v[], int n)
{
    int x, j, i;
    for (i = 1; i < n; i++)
    {
        x = v[i];
        j = i - 1;
        while ((j >= 0) && (v[j] > x))
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}
//-----------FUNCIONES AUXILIARES---------/
void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v[], int n){
    int i;
    for (i = 0; i < n; i++)
    {
        v[i] = (rand() % (n+1));
    }
}


void ascendente(int v[], int n){
    int i;
    for (i = 0; i < n; i++)
    {
        v[i] = i;
    }
}

//Crea un vector ordenado descendentemente
void descendente(int v[], int n){
    int i;
    for (i = n; i > 0; i--)
    {
        v[n-i] = i-1;
    }
}

void listar_vector(int v[], int n)
{
    int i;
    printf("[");
    for (i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("]\n");
}
//----FUNCIONES DADAS POR LA PRÁCTICA-------//
void ord_rapida(int v [], int n) {

    ordenarAux(v, 0, n-1);
    if (UMBRAL > 1){
        ord_ins(v, n);
    }
}

void ordenarAux(int v[], int izq, int der){

    int pivote;
    int x;
    int i, j;
    if(izq + UMBRAL <= der ) {
        x = izq + rand() % (der - izq);
        pivote = v[x];
        SWAP(v[izq], v[x], int);;
        i = izq + 1;
        j = der;
        while (i <= j) {
            while (i <= der && v[i] < pivote) {
                i = i + 1;
            }
            while (v[j] > pivote) {
                j = j - 1;
            }
            if (i <= j) {
                SWAP(v[i], v[j], int);
                i = i + 1;
                j = j - 1;
            }
        }
        SWAP(v[izq], v[j], int);
        ordenarAux(v, izq, j - 1);
        ordenarAux(v, j + 1, der);
    }
}
//-----TEST------/
int ordenado(int v[], int n)
{
    int i;
    if (n<=1){
        return 1;
    }
    for(i=1; i < n; i++){
        if(v[i-1]>v[i]){
            return 0;
        }
    }
    return 1;
}

void calcular(f func, int v[], int n)
{
    int aux;

    aux = ordenado(v, n);
    if (aux == 0)
    {
        printf("Ordenado?: %d \n", ordenado(v, n));
        printf("Ordenamos");
        func(v, n);

        listar_vector(v, n);
        printf("Ordenado?: %d \n\n", ordenado(v, n));
    }
    else
    {
        printf("ordenado?:%d\n\n", ordenado(v, n));
    }
}
void test(f func)
{
    int v[25], k[20];

    printf("\tTEST\n");
    printf("Inicialización aleatoria\n");

    aleatorio(v, 25);
    listar_vector(v, 25);
    calcular(func, v, 25);
    aleatorio(k, 20);
    listar_vector(k, 20);
    calcular(func, k, 20);



    printf("Inicialización descendente\n");
    descendente(v, 25);
    listar_vector(v, 25);
    calcular(func, v, 25);

    descendente(k, 20);
    listar_vector(k, 20);
    calcular(func, k, 20);


    printf("Inicialización ascendente\n");
    ascendente(v, 25);
    listar_vector(v, 25);
    calcular(func, v, 25);

    ascendente(k, 20);
    listar_vector(k, 20);
    calcular(func, k, 20);

}
/* ============== FUNCIONES DE COTAS ============== */

//Cotas para el algoritmo de inserción

void cota_rapida_aleat(int n, double t)
{
    double t_sub, t_ajus, t_sob = 0;
    switch (UMBRAL){
    case 1 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / (n*log(n));
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);    
        break;
    case 10 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / (n*log(n));
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);
        break;
    case 100 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / (n*log(n));
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);
        break;
    default:
        printf("Introduce un umbral 1,10 o 100!");
        break;
    }
}

void cota_rapida_asc(int n, double t)
{
       double t_sub, t_ajus, t_sob = 0;
    switch (UMBRAL){
    case 1 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / pow(n,1.07);
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);    
        break;
    case 10 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / (n*log(n));
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);
        break;
    case 100 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / pow(n,1.15);
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);
        break;
    default:
        printf("Introduce un umbral 1,10 o 100!");
        break;
    }
}

void cota_rapida_desc(int n, double t)
{    double t_sub, t_ajus, t_sob = 0;
    switch (UMBRAL){
    case 1 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / pow(n,1.07);
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);    
        break;
    case 10 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / (n*log(n));
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);
        break;
    case 100 :
        t_sub = t / pow(n, 0.9);
        t_ajus = t / (n*log(n));
        t_sob = t / pow(n, 1.4);
        printf("%6d%17.5f%17.6f%17.6f%17.6f\n", n, t, t_sub, t_ajus, t_sob);
        break;
    default:
        printf("Introduce un umbral 1,10 o 100!");
        break;
    }
}

/* ============== FUNCIONES DE TIEMPOS ============== */
double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void tiempos(f alg, f init, f_cotas cotas){
    int i, j = 0;
    double t1, t2 = 0;
    double t_antes, t_despues, t_tot;
    int v[128000], k = 1000;

    for (i=2000; i<=128000; i*=2){
        init(v,i);

        t_antes = microsegundos();
        alg(v, i);
        t_despues = microsegundos();
        t_tot = t_despues - t_antes;

        if (t_tot<500) {	//UMBRAL DE CONFIANZA
            t_antes = microsegundos();
            for (j=0; j<k; j++) {
                init(v,i);
                alg(v,i);
            }
            t_despues = microsegundos();
            t1 = t_despues - t_antes;
            t_antes = microsegundos();
            for (j=0; j<k; j++)   //Descontamos la inicializacion del vector
                init(v,i);
            t_despues = microsegundos();
            t2 = t_despues - t_antes;
            t_tot = (t1-t2)/j;
            printf("(*)");
        } else {
            printf("   ");
        }
        cotas(i,t_tot);
    }
}

void calculoTiemposRapida()
{
    int i;
    f_cotas cotas[3] = {cota_rapida_aleat, cota_rapida_asc, cota_rapida_desc};

    printf("\nInicialización aleatoria\n");
    for (i = 0; i < 3; i++)
    {
        printf("%8s%17s%17s%17s%17s\n\n", "n", "t(n)",
               "t(n)/n^0.9", "t(n)/n*log(n)", "t(n)/n^1.4");
        tiempos(ord_rapida, aleatorio, cotas[0]);
        printf("\n");
    }

    printf("\nInicialización ascendente\n");
    for (i = 0; i < 3; i++)
    {
        printf("%8s%17s%17s%17s%17s\n", "n", "t(n)",
               "t(n)/n^0.9", "t(n)/n*log(n)", "t(n)/n^1.4");
        tiempos(ord_rapida, ascendente, cotas[1]);
        printf("\n");
    }

    printf("\nInicialización descendente\n");
    for (i = 0; i < 3; i++)
    {
        printf("%8s%17s%17s%17s%17s\n\n", "n", "t(n)",
               "t(n)/n^0.9", "t(n)/n*log(n)", "t(n)/n^1.4");
        tiempos(ord_rapida, descendente, cotas[2]);
        printf("\n");
    }
}

/* ============== MAIN ============== */
int main() {

    test(ord_rapida);
    printf("Ordenación rápida");
    inicializar_semilla();
    calculoTiemposRapida();

    return 0;
}
