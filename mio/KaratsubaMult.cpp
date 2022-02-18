#include <stdio.h>
#include <math.h>

int recursive_mult(int x, int y, int n){
//‘(x<<y)’ is equivalent to multiplying x with 2^y (2 raised to power y). 
//‘(x>>y)‘ is equivalent to dividing x with 2^y. 

	if (n==1) return x*y;

	int x1,y1,x0,y0,p,x1_y1,x0_y0,sol;
/*
	x1 = (x<<int(n/2));
	y1 = (y<<int(n/2));

	x0 = (x>>int(n/2));
	y0 = (y>>int(n/2));
*/
	int x2,y2,d1,d2,d3,d4;
	if (n==4){

		x2 = (x-(x%10))/10;
		x1 = (x2-(x2%10))/10;
		y2 = (y-(y%10))/10;
		y1 = (y2-(y2%10))/10;

		d1 = x%10;
		d3 = y%10;
		d2 = ((x - d1)/10)%10;
		d4 = ((y - d3)/10)%10;
		x0 = d2*10+d1;
		y0 = d4*10+d3;		
	}
	if (n==2){
		x1 = (x-(x%10))/10;
		y1 = (y-(y%10))/10;

		x0 = x%10;
		y0 = y%10;

	}
printf("Para a=%i y b=%i y n=%i\n",x,y,n);
printf("x1=%i y x0=%i\n",x1,x0);
printf("y1=%i y y0=%i\n",y1,y0);


// ese n/2 es dudos si tengo 50 y 50 n seria 3
	p = recursive_mult(x1+x0, y1+y0,n/2);
	x1_y1 = recursive_mult(x1,y1,n/2);
	x0_y0 = recursive_mult(x0,y0,n/2);

printf("Para a=%i y b=%i y n=%i\n",x,y,n);
printf("x1_y1=%i\n",x1_y1);
printf("x0_y0=%i\n",x0_y0);
printf("p=%i\n",p);

//	sol = (x1_y1<<n) + ((p - x1_y1 - x0_y0)<<int(n/2)) + x0_y0;
	sol = (x1_y1*pow(10,n)) + ((p - x1_y1 - x0_y0)*pow(10,int(n/2))) + x0_y0;

printf("(x1_y1*(10^n))%d y ((p - x1_y1 - x0_y0)*(10^int(n/2)))=%d\n",(x1_y1*pow(10,n)),((p - x1_y1 - x0_y0)*pow(10,int(n/2))));

printf("Sol=%i\n",sol);

	return sol; 
}


int main(){
	int a,b,n;
/*
	printf("inserte dos numeros a multiplicar\n");
	scanf("%i",&a);
	scanf("%i",&b);
	printf("digitos de los numeros\n");
	scanf("%i",&n);
*/
	a=5256;
	b=3208;
	n=4;
	printf("a.b = %i\n", recursive_mult(a,b,n));
}
