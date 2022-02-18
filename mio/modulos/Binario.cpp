/*

    En este modulo se representaran numeros binarios de 30 digitos.
    a[0]=cant.de digitos<=31, a[1]=signo, a[2...i...a[0]]=digito i-esimo,
    1: negativo
    0: positivo 
    Recordar que el AND y el NOT son un conjunto logicamente completo

*/
#define size 32

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int abs(int x){
    if (x>=0)   return x;
    else return -x;
}

typedef unsigned int nat;

typedef nat* Binario;

// 13. 13/2=6+1, 6/2=3+0, 3/2=1+1, 1/2=0+1
// 13 = 1101
// -11. 11/2=5+1, 5/2=2+1, 2/2=1+0, 1/2=0+1
// 11 = 1011
// Ej. -23 devuelve b = [5,1, ; 1,0,1,1,1, ; 0,...,0]
// -23. 23/2=11+1, 11/2=5+1, 5/2=2+1, 2/2=1+0, 1/2=0+1
//  23 = 10111
Binario toBin(int x){
    Binario res = new nat[size];
    nat digito = 2;
    if (x >= 0) res[1] = 0;
    else res[1] = 1;
    x = abs(x);
    while (x != 0){
        res[digito] = x % 2;
        x /= 2;
        digito ++;
    }
    res[0] = digito - 2;
    return res;
}

int toInt(Binario b){
    int res = 0;
    nat base = 1;
    for (int i=2; i<=b[0]+1; i++){
        res += b[i] * base;
        base *= 2;
    }
    if (b[1] == 1)  res = -res;
    return res;
}

void mostrarBinario(Binario b){
    if (b[1] == 1)  printf("-");
    for (int i=b[0]+1; i>=2; i--)
        printf("%i",b[i]);
    printf("\n");
}

//  110011 ==> 011001
// shiftea n lugares a la derecha el binario, n>=0, deja 0 en los lugares nuevos
// mantiene los mismos digitos
void ShiftDer(Binario &b, int n){
    nat digito;
    nat ultimo_digito = b[0]+1;
    for (digito=2; digito+n <= ultimo_digito; digito++)
        b[digito] = b[digito + n];
    while (digito <= ultimo_digito){
        b[digito] = 0;
        digito++;
    }
}
// 110011 ==> 100110
// shiftea n lugares a la izquierda el binario, n>=0, deja 0 en los lugares nuevos
// mantiene los mismos digitos
void ShiftIzq(Binario &b, int n){
    nat digito;
    nat primer_digito = 2;
    nat ultimo_digito = b[0]+1;
    for (digito=ultimo_digito; digito-n >= primer_digito; digito--)
        b[digito] = b[digito - n];
    while (digito >= primer_digito){
        b[digito] = 0;
        digito--;
    }
}
void ShiftCircularIzq(Binario &b){
    nat aux = b[b[0]+1];
    ShiftIzq(b,1);
    b[2] = aux;
}
void ShiftCircularDer(Binario &b){
    nat aux = b[2];
    ShiftDer(b,1);
    b[b[0]+1] = aux;
}
//--------//
nat AND(nat x, nat y){
    if (x == 1 && y == 1)    return 1;
    else return 0;
}

nat NOT(nat x){
    if (x == 1) return 0;
    else return 1;
}

nat XOR(nat x, nat y){
    if (x == y) return 0;
    else return 1;
}

nat OR(nat x, nat y){
    if (x == 0 && y == 0)    return 1;
    else return 0;
}
//  NOR es el OR negado
//  NAND es el AND negado
//  XNOR complemento del XOR (xor negado)
//  IMPLY

//  se podria hacer con punteros a funcion y seleccionar si quiero and or etc
//  si digitos de x < digitos de y completa con 0's y viceversa
//  el digito del signo no tiene significado
Binario ANDbitabit(Binario x, Binario y){
    Binario res = new nat[size];
    nat digito = 2;
    nat max;
    if (x[0] < y[0]) max = y[0];
    else max = x[0];
    while (digito <= x[0]+1 && digito <= y[0]+1){
        res[digito] = AND(x[digito],y[digito]);
        digito ++;
    }
    while (digito <= max+1){
        res[digito] = 0;
        digito ++;
    }
    res[0] = max;
    return res;
}

Binario NOTbitabit(Binario x){
    return NULL;
}

Binario XORbitabit(Binario x, Binario y){
    return NULL;
}

Binario ORbitabit(Binario x, Binario y){
    return NULL;
}

Binario SumaBin(Binario x, Binario y){
    Binario suma = new nat[size];
    nat digito = 2;
    nat min, max; 
    if (x[0] < y[0]) {
        min = x[0];
        max = y[0];
        suma[0] = y[0];
    } else {
        min = y[0];
        max = x[0];
        suma[0] = x[0];
    }
    nat sum;
    nat carry = 0;
    while (digito <= min + 1){
        sum = x[digito] + y[digito] + carry;
        if (sum==3){
            carry = suma[digito] = 1;
        } else if (sum==0){
            carry = suma[digito] = 0;           
        } else if (sum==2){
            carry = 1;
            suma[digito] = 0;
        } else {
            carry = 0;
            suma[digito] = 1;
        }
        digito ++;
    }
    if (max == min && carry == 1){
        suma[0] ++;
        suma[digito] = 1;
    } else {
        nat res;
        while (digito <= max + 1){
            if (max == x[0]) {
                res = XOR(x[digito], carry);
                carry = AND(x[digito], carry);
            } else {
                res = XOR(y[digito], carry);
                carry = AND(y[digito], carry);
            }
            suma[digito] = res;
            digito ++;
        }
        if (carry == 1){
            suma[0] ++;
            suma[digito] = 1;
        }
    }
    suma[1] = x[1];
    return suma;
}

Binario MultBin(Binario a, Binario b){
    int bint = toInt(b);
    int sum = 0;
    Binario temp = toBin(toInt(a)); //copio a
    Binario aux;
    for (int i=1; i<bint; i++){
        aux = temp;
        temp = SumaBin(a,temp);
        delete [] aux;
    }
    return temp;
}

int main(){
    /*
    srand(time(NULL));
    Binario b1,b2,suma;
    int n1,n2,i, sumint;
    bool error = false;
    for (i=0;i<500 && !error;i++){
        n1 = (rand()%(30));
        n2 = (rand()%(30));
        b1 = toBin(n1);
        b2 = toBin(n2);
        suma = SumaBin(b1,b2);
        sumint = toInt(suma);
        printf("%i+%i = %i    == ",n1,n2,sumint);
        mostrarBinario(suma);
        if ((n1+n2) != sumint )  error = true;
    }
    */
    Binario b = toBin(15);
    Binario b2 = toBin(3);
    Binario m = MultBin(b,b2);
    mostrarBinario(m);
    printf("%i",toInt(m));

}