/*

    Usando la estrategia de Divide and Conquer
    Devolver un booleano que indique si un arreglo ordenado ascendentemente y sin repetidos es magico.
    Es decir existe a[i]=i. El arreglo posee n enteros.
    Hagalo en tiempo O(logn)

*/

#include <stdio.h>
#include <stdlib.h> //rand
#include <math.h>   //trunc
#include <time.h>   //time

typedef int* ArrInt;

/*
    Ejemplo: A de tamanio 6, es decir [0 1 2 3 4 5]
    P(Magico) = P(a[0]=0) + P(a[0]!=0)P(a[1]=1) + ... = Sumatoria (j=0 a size-1) P(a[i]!=i)^j * P(a[i]=i)

    Si el tamanio es 1. Mi arreglo quedara a[0] = x.
    Con un rango = 2, para el primer elemento hay :
    1 forma de ser 2. 2-0
    2 formas de ser 1. 1-0 y 2-1
    3 formas de ser 0. 2-2 , 1-1 y 0-0
    2 formas de ser -1. 1-2 y 0-1
    1 forma de ser -2. 0-2
    P(a[0]=0) = 3/9 = 0.3333...
    Por lo anterior, si rango=2 y tamanio=1, entonces P(Magico) = 0.333
    Sin embargo, empiricamente da 0.56
    Con un rango = 1, para el primer elemento hay :
    1 forma de ser 1. 1-0
    2 formas de ser 0. 1-1 y 0-0
    1 forma de ser -1. 0-1
    P(a[0]=0) = 2/4 = 0.5
    Por lo anterior, si rango=1 y tamanio=1, entonces P(Magico) = 0.5
    Sin embargo, empiricamente da 0.69
*/
void mostrarArreglo(ArrInt A, int n, char nom){
    printf("%c = [ ",nom);
    for (int i=0;i<n;i++)   printf("{%i}%i ",i,A[i]);
    printf("]\n");
}
ArrInt ArrayRandom(int n, int rango, int seed){
    ArrInt nuevo = new int[n];
    srand(time(NULL)+seed);  //reiniciamos la semilla
    nuevo[0] = (rand()%(rango+1)) - (rand()%(rango+1)); //aleatorio entre -rango y rango
    for (int i=1; i<n; i++) nuevo[i] = nuevo[i-1] + (rand()%(rango+1)); // esto me permite que esten en orden creciente y no se repitan x+ant>x y x+ant!=x si ant>0.
    return nuevo;   
    //valores menores del rango hacen mas probable encontrar un arreglo magico
}

bool esMagicoRec(ArrInt a, int ini, int fin){
    int medio = trunc((fin - ini) / 2.0);
    if (fin - ini == 0) return a[ini+medio] == ini+medio;
    else {
        if (a[ini+medio] > ini+medio)   return esMagicoRec(a,ini,ini+medio);
        else if (a[ini+medio] < ini+medio)   return esMagicoRec(a,ini+medio+1,fin);
        else /*(a[ini+medio] == ini+medio)*/ return true;
    } 
}
bool esMagico(ArrInt a, int n){
    return esMagicoRec(a,0,n-1);
}

int main(){
    int size = 1;
    bool esMagic;
    int cont;
    int rango = 1;
    double prom = 0;
    int cota = 10000;

    for (int i=0; i<cota; i++){
        cont = 0;
        do {
            ArrInt arreglo = ArrayRandom(size, rango, cont+i);
            esMagic = esMagico(arreglo, size);

         //   mostrarArreglo(arreglo, size, 'A');
        /*
            printf("El arreglo ");
            mostrarArreglo(arreglo, size, 'A');
            if (!esMagic) printf("no ");
            printf("es magico\n");
        */
            delete [] arreglo;
        
            cont ++;
        } while (!esMagic);
    //    printf("Tomo %i iteraciones encontrar un arreglo magico\n",cont);
     //   printf("Probabilidad Empirica = %f\n",1.0/cont);
        prom += 1.0/cont;
    }
    printf("Promedio de las Probabilidades Empiricas = %f\n",prom/cota);
}