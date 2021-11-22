#include <stdio.h>
#include <math.h>
#include <sys/time.h>

/*

GRUPO 4.1 || AUTORES:
Santiago Julio Iglesias Portela : santiago.iglesias4@udc.es
Pablo Longueira Failde : pablo.longueira.failde@udc.es
Andrea Lama Muiño : a.lama1@udc.es

*/

/*============== FIB 1 ==============*/

int fib1(int n)
{
    int sol = 0;
    if (n < 2)
    {
        sol = n;
    }
    else
    {
        sol = fib1(n - 1) + fib1(n - 2);
    }
    return sol;
}

/*============== FIB 2 ==============*/

int fib2(int n)
{
    int i = 1, j = 0;
    for (int k = 0; k < n; k++)
    {
        j = i + j;
        i = j - i;
    }
    return j;
}

/*============== FIB 3 ==============*/
int fib3(int n)
{
    int i, j, k, h, t;
    i = 1;
    j = 0;
    k = 0;
    h = 1;
    t = 0;
    while (n > 0)
    {
        if ((n % 2) != 0)
        {
            t = j * h;
            j = (i * h) + (j * k) + t;
            i = (i * k) + t;
        }
        t = h * h;
        h = (2 * k * h) + t;
        k = (k * k) + t;
        n = n / 2;
    }
    return j;
}

/*============== FUNCIÓN AUX. PARA CABECERA ==============*/
void guiones(int i)
{
    while (i < 80)
    { //genera guiones.
        printf("-");
        i++;
    }
    printf("\n");
}

/*============== FUNCIÓN AUXILIAR PARA LA CABECERA ==============*/
void cabecera(char *alg)
{
    printf("\n\n%1s%8s%15s%15s%15s%15s\n",
           alg, "n", "t(n)", "SUB*", "AJUS*", "SOBRE*");
    guiones(0);
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

/*============== TABLA DE FIB 1 ==============*/
void timefib1()
{
    int k = 100000, n = 2, i;
    double ta, tb, tc, td, t, x, y, z, suma = 0.0, c = 0.0, cte;
    printf("\nMEDICIÓN DE TIEMPOS PARA EL ALGORITMO FIB1(N)\t");
    cabecera("FIB1(N)");
    while (n <= 32)
    {
        ta = microsegundos();
        fib1(n);
        tb = microsegundos();
        t = tb - ta; //tiempo que tarda en ejecutarse nuestro algoritmo.
        if (t < 500)
        {
            tc = microsegundos();
            for (i = 1; i <= k; i++)
            {
                fib1(n);
            }
            td = microsegundos();
            t = (td - tc) / k; //tiempo promedio de la 1era ejecución.
            printf("*");       //marca los tiempos inferiores a 500.
        }
        else
        {
            printf(" "); //alineamiento de texto.
        }
        x = t / pow(1.1, n);               //cota subestimada
        y = t / pow((1 + sqrt(5)) / 2, n); //cota ajustada
        z = t / pow(2, n);                 //cota sobreestimada
        suma = suma + y;                   //para saber la cte a la que tiende y.
        c = c + 1;                         //para saber la cte a la que tiende y.
        printf("%15i%15.6f%15.8f%15.8f%15.8f\n", n, t, x, y, z);
        n = n * 2;
    }
    cte = suma / c; //cte a la que tiende y.
    guiones(0);
    printf("%55s%1.6f \n", "CTE=", cte);
    guiones(0);
    printf("\nSUB* = 1.1^n \nAJUS* = (1+sqrt(5))/2 \nSOBRE* = 2^n \n");
}

/*============== TABLA DE FIB 2 ==============*/
void timefib2()
{
    double ta, tb, tf, x, y, z, c = 0.0, suma = 0.0, cte;
    int n = 1000, k = 100000, i;
    printf("\nMEDICIÓN DE TIEMPOS DEL ALGORITMO FIB2");
    cabecera("FIB2(N)");
    while (n <= 10000000)
    {
        ta = microsegundos();
        fib2(n);
        tb = microsegundos();
        tf = tb - ta;
        if (tf < 500)
        {
            ta = microsegundos();
            for (i = 1; i <= k; i++)
            {
                fib2(n);
            }
            tb = microsegundos();
            tf = (tb - ta) / k;
            printf("*"); //marca los tiempos menores de 500.
        }
        else
        {
            printf(" ");
        }
        x = tf / pow(n, 0.8);    //Cota subestimada
        y = tf / n;              //Cota ajustada
        z = tf / (n * log10(n)); //Cota sobreestimada
        suma = suma + y;         //para saber la cte a la que tiende y.
        c = c + 1;               //para saber la cte a la que tiende y.
        printf("%15i%15.6f%15.6f%15.8f%15.8f\n", n, tf, x, y, z);
        n = n * 10;
    }
    cte = suma / c; //cte a la que tiende la cota ajustada.
    guiones(0);
    printf("%55s%1.6f \n", "CTE=", cte);
    guiones(0);
    printf("\nSUB* = n^0.8 \nAJUS* = n \nSOBRE* = n*log10(n) \n");
}

/*============== TABLA DE FIB 3 ==============*/
void timefib3()
{
    double ta, tb, tf, x, y, z, c = 0.0, suma = 0.0, cte;
    int n = 1000, k = 100000, i;
    printf("\nMEDICIÓN DE TIEMPOS DEL ALGORITMO FIB3");
    cabecera("FIB3(N)");
    while (n <= 10000000)
    {
        ta = microsegundos();
        fib3(n);
        tb = microsegundos();
        tf = tb - ta;
        if (tf < 500)
        {
            ta = microsegundos();
            for (i = 1; i <= k; i++)
            {
                fib3(n);
            }
            tb = microsegundos();
            tf = (tb - ta) / k;
            printf("*"); //marca los tiempos menores de 500.
        }
        else
        {
            printf(" ");
        }
        x = tf / (sqrt(log10(n))); //Cota subestimada
        y = tf / log(n);           //Cota ajustada
        z = tf / pow(n, 0.5);      //COta sobreestimada
        suma = suma + y;           //Para saber la cte a la que tiende y.
        c = c + 1;                 //Para saber la cte a la que tiende y.
        printf("%15i%15.6f%15.6f%15.8f%15.8f\n", n, tf, x, y, z);
        n = n * 10;
    }
    cte = suma / c; //Constante a la que tiende la cota ajustada.
    guiones(0);
    printf("%55s%1.6f \n", "CTE=", cte);
    guiones(0);
    printf("\nSUB* = sqrt(log10(n)) \nAJUS* = log(n) \nSOBRE* = n^0.5  \n");
}

/*============== TEST ==============*/
void test()
{
    int n, m = 15;

    char test[5] = "TEST";
    char fib1char[5] = "FIB1";
    char fib2char[5] = "FIB2";
    char fib3char[5] = "FIB3";

    printf("%36s\n", test);
    printf("\n");
    printf("%19s%17s%17s", fib1char, fib2char, fib3char);
    printf("\n");

    for (n = 0; n <= m; n++)
    {
        printf("%17d", fib1(n));
        printf("%17d", fib2(n));
        printf("%17d", fib3(n));
        printf("\n");
    }
    guiones(0);
    guiones(0);
}
/*============== MAIN DE FIB.C ==============*/
int main()
{
    test();
    timefib1();
    timefib1();
    timefib1();
    timefib2();
    timefib2();
    timefib2();
    timefib3();
    timefib3();
    timefib3();
}