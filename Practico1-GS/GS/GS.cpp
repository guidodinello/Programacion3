#include <stdio.h>

 //let result = condition ? value1 : value2;

/*
int answer = (number >= 0 ? number : 0); 
=
if (number >= 0) {
      answer = number;
   }
   else
      answer = 0;
   }
*/

struct nodoLista{
	int man;
	nodoLista* sig;
}typedef *Lista;

void agregarLista(Lista &l, int ith_man){
	nodoLista* nuevo = new nodoLista;
	nuevo -> man = ith_man;
	nuevo -> sig = l;
	l = nuevo;
}

Lista crearLista(){
	return NULL;
}

typedef char *ArregloChars;     // arreglo de char
void leerChars(ArregloChars cs) { scanf("%s", cs); }

int main() {
	int n = 2;
	int Ranking[n][n];
	int Current[n];
	int ManPref[n][n];
	int WomanPref[n][n];
	int Next[n];
	Lista freeMan = crearLista();

	char restoLinea[MAX_LINEA + 1];
	char nom_comando[MAX_PALABRA];

	int cont_comandos = 0;
	bool salir = false;
	while (!salir) {
		// mostrar el prompt
		cont_comandos++;
		printf("%u>", cont_comandos);

		// leer el comando
		leerChars(nom_comando);

		// procesar el comando
		if (0 == strcmp(nom_comando, "Fin")) {
		salir = true;
		printf("Fin.\n");
		// comentario
		} else if (0 == strcmp(nom_comando, "")) {


		} else {
		printf("Comando no reconocido.\n");
		} // if
		fgets(restoLinea, MAX_LINEA + 1, stdin);
	} // while
	return 0;
} // main


/*
Inicializar todas las personas como libres
While (existe un hombre m libre que no se ha propuesto a todas las mujeres)
	Sea w la mujer de mayor preferencia para m a la cual todavia no se ha propuesto
	IF (w esta libre)
		(m,w) se emparejan
	ELSE 
		IF (w prefiere a m por sobre m' su pareja actual)
			(m,w) se emparejan
			m' queda libre
		endif
		IF (w prefiere a m' por sobre m)
		endif
	endif
endwhile
*/

