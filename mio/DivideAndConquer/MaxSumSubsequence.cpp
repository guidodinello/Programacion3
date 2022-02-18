/*
    Mediante la tecninca de Divide and Conquer.

    Dado una secuencia de enteros, encontrar la subsecuencia de mayor suma
    Hagalo en tiempo O(nlogn), siendo n la cantidad de enteros de la secuencia entrada.

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int maximo(int a, int b){
    if (a >= b) return a;
    else return b;
}

typedef int* ArrInt;

void impArray(ArrInt a, int ini, int fin){
    printf("A = [ ");
    for (int i=ini; i<=fin; i++)
        printf("%i ",a[i]);
    printf("]\n");
}

ArrInt ArrayRandom(int n){
    ArrInt nuevo = new int[n];
    srand(time(NULL));  //reiniciamos la semilla
    for (int i=0; i<n; i++) nuevo[i] = (rand()%501) - (rand()%501); //aleatorio entre 500 y 500 (-RAND_MAX y RAND_MAX)
    return nuevo;
}

struct Subsequence{
    int inicio;
    int fin;
    int suma;
};

Subsequence sub(int ini, int fin, int suma){
    Subsequence sol;
    sol.inicio = ini;
    sol.fin = fin;
    sol.suma = suma;
    return sol;
}

void expander(ArrInt a, Subsequence &izq, Subsequence der){
    int acum = 0;

    for (int i=izq.fin+1; i<=der.fin; i++){
        acum += a[i];
        if (acum > 0){
            izq.fin = i;
            izq.suma += acum;
            acum = 0;
        }
    }
}

void expandizq(ArrInt a, Subsequence izq, Subsequence &der){
    int acum = 0;

    for (int i=der.inicio-1; i>=der.fin; i--){
        acum += a[i];
        if (acum > 0){
            der.inicio = i;
            der.suma += acum;
            acum = 0;
        }
    }
}

Subsequence MaxSumSubsequence(ArrInt a, int ini, int fin){
    if (fin - ini == 0) return sub(ini, ini, a[ini]);
    else {
        int medio = trunc((fin - ini) / 2.0);
        Subsequence izq,der;
        izq = MaxSumSubsequence(a, ini, ini+medio);
        der = MaxSumSubsequence(a, medio+ini+1, fin);

        expander(a, izq, der);  // [...(izq)x)x)x)...(der)...]

        //-- medida de optimizacion --//
        if (izq.fin != der.fin) //si la primera expansion los hizo iguales ya sera solucion
        //----------------------------//
            expandizq(a, izq, der);  // [...(izq)...(x(x(x(der)...]

        int max = maximo(izq.suma, der.suma);

        if (max == der.suma)
            return sub(der.inicio, der.fin, der.suma);
        else 
            return sub(izq.inicio, izq.fin, izq.suma);
    }
}
/*
    Nuestra funcion cumple la relacion de recurrencia :
    T(1) <= c;
    T(n) <= 2T(n/2) + kn; n>1
    Luego T(n) es de orden O(nlogn)
*/

int main(){
    int size = 16;
    ArrInt arreglo = ArrayRandom(size);
    /*ArrInt arreglo = new int[size];
    arreglo[0] = -91;
    arreglo[1] = 234;
    arreglo[2] = -64;
    arreglo[3] = 311;
    arreglo[4] = -191;
    arreglo[5] = 305;
    arreglo[6] = -146;
    arreglo[7] = 111;
    arreglo[8] = 234;
    arreglo[9] = -195;
    arreglo[10] = -146;
    arreglo[11] = -81;
    arreglo[12] = -116;
    arreglo[13] = -219;
    arreglo[14] = 114;
    arreglo[15] = 122;*/
    Subsequence sol;

    printf("En el arreglo\n");
    impArray(arreglo, 0, size-1);

    sol = MaxSumSubsequence(arreglo, 0, size-1);

    printf("Maxima subsecuencia hallada\n");
    impArray(arreglo, sol.inicio, sol.fin);
    printf("De Suma = %i\n",sol.suma);

}