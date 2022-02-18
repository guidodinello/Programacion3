#include <stdio.h>

struct obj{
	int ident;
	char clase;
};

typedef obj ranking[3][4];

struct dupla{
	obj obj1;
	obj obj2;
};

typedef dupla matching[3]; 

void llenarCuadro(ranking a, int col, int fil, char x, int i){
	a[fil][col].ident = i;
	a[fil][col].clase = x;
}

void leerRanking(ranking a, char c){
	int pos;
	if (c != 'e') c == 'h';
	for (int i=0; i<3; i++) {
		printf("Ingrese el ranking de ");
		if (c == 'e') printf("hospitales ");
		else printf("estudiantes ");
		printf("para el ");
		if (c == 'e') printf("estudiante %i : ", i+1);
		else printf("hospital %i : ", i+1);
		scanf("%i", &pos);
		int unidades = pos % 10;
		int decenas = ((pos - unidades) / 10) % 10;
		int centenas = (pos - unidades - decenas*10) / 100;
		int arr[3] = {centenas,decenas,unidades};
		for (int j=1; j<4; j++){
			a[i][j].clase = c;
			a[i][j].ident = arr[j-1];
		}
		printf("\n");
	}
}

void mostrarRanking(ranking a){
	for (int i=0; i<3; i++) {
		printf("%c%i | ", a[i][0].clase, a[i][0].ident);
		for (int j=1; j<4; j++) {
			printf("%c%i ", a[i][j].clase, a[i][j].ident);
		}
		printf("\n");
	}
}

matching gs(ranking h, ranking e) {
	dupla libresH[3];
	int libre_cant = 3;
	for (int i=1; i<4; i++) {
		libres.obj1.clase = 'h';
		libres.obj1.ident = i;
		libres.obj2.clase = 'v';
		libres.obj2.ident = -1;
	}
	while ()
}

int main(){

	ranking hospitales, estudiantes;
	
	for (int i=0; i<3; i++) {
		llenarCuadro(hospitales, 0, i, 'h', i+1);
		llenarCuadro(estudiantes, 0, i, 'e', i+1);
	}
	char c = 'h';
	leerRanking(hospitales, c);
	//c = 'e';
	//leerRanking(estudiantes, c);

	mostrarRanking(hospitales);
	//mostrarRanking(estudiantes);
}