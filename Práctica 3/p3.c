/*
AUTORES
Pablo Longueira Failde : pablo.longueira.failde@udc.es
Santiago Julio Iglesias Portela : santiago.iglesias4@udc.es
Andrea Lama Muiño : a.lama1@udc.es
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
struct nodo {
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;
typedef void (*f)(int e,arbol a);
typedef void (*f_cotas)(int n, double t);
/*----------FUNCIONES DADAS POR LA PRÁCTICA--------------*/
static struct nodo *crearnodo(int e) {
    struct nodo *p = malloc(sizeof(struct nodo));
    if (p == NULL) {
        printf("memoria agotada\n"); exit(EXIT_FAILURE);
    }
    p->elem = e;
    p->num_repeticiones = 1;
    p->izq = NULL;
    p->der = NULL;
    return p;
}
arbol insertar(int e, arbol a){ //esta mal
    if (a == NULL)
        return crearnodo(e);
    else if (e < a->elem)
        a->izq = insertar(e, a->izq);
    else if (e > a->elem)
        a->der = insertar(e, a->der);
    else if (e==a->elem)
        a->num_repeticiones++;

    return a;
}
/*--------------- FUNCIONES AUXILIARES -----------------*/
int max(int a,int b){
    int aux=0;
    if (a<b)
        return aux=b;//b>a
    else return aux=a;;//a>=b
    /* En caso de ser a mayor sale a, y si
        a y b son iguales sale a también*/
}
//Inicializa la semilla para los números aleatorios.
void inicializar_semilla()
{
    srand(time(NULL));
}

void aleatorio(int v[], int n)
{
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
    {
        v[i] = (rand() % m) - 1;
    }
}

/*----------------- FUNCIONES BASE  -------------------*/
arbol creararbol(){
    return NULL;
}
int esarbolvacio(arbol a){
    return a==NULL;
}
posicion buscar(int e, arbol a){
    if (a == NULL){
        return NULL;
    }
    else{
        if (e == a->elem){
            return a;
        }else{
            if (e < a->elem){
                return buscar(e, a->izq);
            }else return buscar(e, a->der);
        }
    }
}
arbol eliminararbol(arbol a){
    if(a!=NULL){
        eliminararbol(a->izq);
        eliminararbol(a->der);
        free(a);
        a = NULL;
    }
    return a;
}
posicion hijoizquierdo(arbol a){
    if (a!=NULL)
        return a->izq;
    else return 0;
}
posicion hijoderecho(arbol a){
    if (a!=NULL)
        return a->der;
    else return 0;
}
int elemento(posicion p){
    return p->elem;
}
int numerorepeticiones(posicion p){
    if (p!=NULL)
        return p->num_repeticiones;
    else return 0;
}
int altura(arbol a){
    if (a==NULL){
        return -1;
    }else if (a->der==NULL && a->izq==NULL){
        return 0;
    } else return 1 + max(altura(a->izq),altura(a->der));
}
void visualizar(arbol a){ //no saca el arbol
    if(a!=NULL){
        printf("(");
        visualizar(a->izq);
        printf(" %d ",a->elem);
        visualizar(a->der);
        printf(")");
        //printf(" (%d)\n",a->elem);
    }//else printf("().");
}
/*------- MEDICION DE TIEMPOS ----------*/

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
arbol tiemposIns(arbol a,int v[],int n,double *tiempo){
    double tantes,tdespues=0;
    int i;
    aleatorio(v,n);
    tantes=microsegundos();
    for ( i = 0; i < n; i++)
    {
        a=insertar(v[i],a);
    }
    tdespues=microsegundos();
    *tiempo=tdespues-tantes;
    return a;
}
double tiemposBus(arbol a,int v[],int n){
    double ttotal,t_bus,tantes,tdespues=0;
    int k=10000,j=0,i=0;
    aleatorio(v,n);
    tantes=microsegundos();
    for ( i = 0; i < n; i++)
    {
        buscar(v[i],a);

    }
    tdespues=microsegundos();
    ttotal=tdespues-tantes;
    if(ttotal<500){
        tantes=microsegundos();
        for(j=0; j<k; j++){
            buscar(v[i],a);
        }
        tdespues=microsegundos();
        t_bus=tdespues-tantes;
        ttotal=t_bus/k;
        printf("*");
    }

    return ttotal;
}
void calculoTiempos(){
    arbol a=creararbol();
    int i,j=0,n=256000,v[n];
    double arraytIns[6],arraytBus[6];
    printf("     n\t\t     t_ins\t\t t_bus\n");
    for ( i = 8000; i <=256000 ; i=i*2)
    {
        a=tiemposIns(a,v,i,&arraytIns[j]);
        arraytBus[j]=tiemposBus(a,v,i);
        a=eliminararbol(a);
        printf("%6d %20.2f %20.2f \n", i,arraytIns[j] , arraytBus[j] );
        j++;
    }
    printf("\n");
    j=0;
    printf("Inserción de n elementos: \n");
    printf("     n\t\t   t\t     t/n  \t  t/n^1.4\t t/n^1.7\n");
    for ( i = 8000; i <= 256000; i=i*2)
    {
        printf("%6d%14.2f%15.6f%16.8f%14.8f%14.8f\n",i,arraytIns[j]
                ,arraytIns[j]/i,
               arraytIns[j]/pow(i,1.4),
               arraytIns[j]/pow(i,1.7),
               arraytIns[j]/(i*log(i)));
        j++;
    }

    printf("\n");
    j=0;
    printf("Búsqueda de n elementos: \n");
    printf("     n\t\t   t\t      t/n  \t  t/n^1.41\t t/n^1.7\n");
    for ( i = 8000; i <= 256000; i=i*2)
    {
        printf("%6d%14.2f%15.6f%16.8f%14.8f%14.8f\n",i,arraytBus[j],
               arraytBus[j]/i,
               arraytBus[j]/pow(i,1.41),
               arraytBus[j]/pow(i,1.7),
               arraytBus[j]/(i*log(i)));
        j++;
    }
    printf("\n");
}
/*---------TEST PRUEBAS MINIMAS--------*/
void test(){
    arbol a= creararbol();
    printf("arbol vacio? :%d\n",esarbolvacio(a));
    visualizar(a);
    printf(" altura del arbol %d\n",altura(a));
    printf(" inserto un 3\n,\n inserto un 1 \n inserto un 2 \n");
    printf(" inserto un 5 \ninserto un 4 \n inserto un 5 \n");
    a=insertar(3,a);
    a=insertar(1,a);
    a=insertar(2,a);
    a=insertar(5,a);
    a=insertar(4,a);
    a=insertar(5,a);
    visualizar(a);
    printf(" altura del arbol %d\n",altura(a));
    printf(" busco 1 y encuentro 1 repetido: %d\n",
           numerorepeticiones(buscar(1,a)));
    printf(" busco 2 y encuentro 2 repetido: %d\n",
           numerorepeticiones(buscar(2,a)));
    printf(" busco 3 y encuentro 3 repetido: %d\n",
           numerorepeticiones(buscar(3,a)));
    printf(" busco 4 y encuentro 4 repetido: %d\n",
           numerorepeticiones(buscar(4,a)));
    printf(" busco 5 y encuentro 5 repetido: %d\n",
           numerorepeticiones(buscar(5,a)));
    printf(" busco 6 y encuentro 6 repetido: %d\n",
           numerorepeticiones(buscar(6,a)));
    printf(" altura del arbol %d\n",altura(a));
    printf(" borro todos los nodos liberando memoria:\n");
    a=eliminararbol(a);
    visualizar(a);
    printf(" altura del arbol %d\n",altura(a));
}
int main(){
    arbol a;
    test();
    inicializar_semilla();
    calculoTiempos();
    calculoTiempos();
    calculoTiempos();
    a=eliminararbol(a);
}
