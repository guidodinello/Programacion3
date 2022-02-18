#include <stdio.h>

void cuantas(int materias, float prom, int notas, float objetivo){
	while (prom < objetivo){
		materias ++;
		prom = float(prom*(materias-1))/float(materias) + float(notas)/float(materias);
		//printf("promedio = %f con %i materias de %i\n",prom,materias,notas);
	}
	printf("Se necesitan %i materias mas con nota de %i para llegar a un promedio de %f\n",(materias-21),notas,prom);
}

int main(){
	int materias = 21;
	float prom = 6.41;
	int notas;
	float objetivo;

	printf("Cual es tu nota objetivo: \n");
	scanf("%f", &objetivo);
	printf("con notas de : \n");
	scanf("%i", &notas);

	cuantas(materias, prom, notas, objetivo);
	if (notas < 12) cuantas(materias, prom, notas+1, objetivo);
	if (objetivo < 12) cuantas(materias, prom, notas, objetivo+1);
	if (objetivo < 11) cuantas(materias, prom, notas, objetivo+2);	
}