/*
    Mediante la tecninca de Divide and Conquer.

    Para un arreglo B que cumple que sus elementos estan ordenados crecientemente y la diferencia entre ellos es constante.
    Sea A el arreglo resultado de eliminar un elemento de B, a excepcion del primero y del ultimo.
    Encuentre el elemento faltante en A, en tiempo O(logn).
    Siendo n el tamanio del arreglo A y ademas n es potencia de 2 mayor o igual a 2.

*/

#include <stdio.h>
#include <stdlib.h> //rand
#include <math.h>   //trunc
#include <time.h>   //time

#define size 9 //uso n de la forma 2^m + 1 pues no usaremos el arreglo desde 1

typedef int* ArrInt;

//devuelve arreglo de indices 1 a n
ArrInt Arreglo(int n){
    int* nuevo = new int[n+1];
    return nuevo;
}
void mostrarArreglo(ArrInt A, int n, char nom){
    printf("%c = [ ",nom);
    for (int i=1;i<=n;i++)   printf("%i ",A[i]);
    printf("]\n");
}
void LlenarArreglo(ArrInt A, int n, int ini, int dif){
    for (int i=1; i<=n; i++) A[i]=ini+(i-1)*dif;
}

int roof(float a){
    if (a - trunc(a) == 0) return trunc(a);
    else return trunc(a)+1; 
}
int aleatorio(int ini, int fin){
    srand(time(NULL));
    int aleatorio = rand();

    aleatorio = aleatorio % (fin-ini+1);   //random entre 0 y fin-ini
    aleatorio = aleatorio + ini;    //random entre ini y fin

    return aleatorio;
}

ArrInt eliminar(ArrInt A_aster, int indice, int n){
    ArrInt nuevo = new int[n];
    int contA = 1;
    int contA_aster = 1;
    while (contA_aster <= n) {
        if (contA_aster != indice)  nuevo[contA] = A_aster[contA_aster];
        else contA --;
        contA_aster ++;
        contA ++;
    }
    return nuevo;
}

int Encuentra_Rec(ArrInt A, int ini, int fin, int dif){
    if (fin - ini == 1) return A[ini]+dif;
    else {
        int medio = roof((fin - ini) / 2.0) + ini;
        if (A[ini]+dif*(medio - ini) == A[medio]) return Encuentra_Rec(A, medio, fin, dif);
        else return Encuentra_Rec(A, ini, medio, dif);
    }
}
int Encuentra(ArrInt A, int n){
    return Encuentra_Rec(A, 1, n, (A[n]-A[1])/n);   //A[1]+dif(n)=A[n]
}
/*
    Nuestra funcion cumple la relacion de recurrencia :
    T(2) <= c;
    T(n) <= T(n/2) + k; n>2
    Luego T(n) es de orden O(logn)
*/


int main(){
    ArrInt A_aster = Arreglo(size);
    LlenarArreglo(A_aster, size, 1, 23);
    mostrarArreglo(A_aster, size, 'B');

    int eliminar_ind = aleatorio(2,size-1); //ni el primero ni el ultimo pueden faltar
    ArrInt A = eliminar(A_aster, eliminar_ind, size);
    mostrarArreglo(A, size-1, 'A');

    int encontrado = Encuentra(A, size-1);
    printf("Falta %i\n",encontrado);
}

