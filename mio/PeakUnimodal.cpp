#include <stdio.h>
#include <math.h>

int FindPeak(int* a, int middle){
	printf("A.left=%i, A.middle=%i, A.right=%i\n",a[middle - 1],a[middle],a[middle + 1]);
	bool wata = a[middle - 1] < a[middle] > a[middle + 1];
	printf("wata %i \n",wata);
	if ( (middle + 1) >= 5 || (middle - 1) < 0 ||
		a[middle - 1] < a[middle] > a[middle + 1] ) {
		printf("1");
		return middle;
	}else if (a[middle - 1] > a[middle] > a[middle + 1]) {
		printf("2");
		return FindPeak(a, middle + 1);
	}else if (a[middle - 1] < a[middle] < a[middle + 1]) {
		printf("3");
		return FindPeak(a, middle - 1);
	}else {
		printf("what");
	return -1;
	}
}

int main(){
	int size = 5;
	int* A = new int[size];

	A[0] = 0;
	A[1] = 1;
	A[2] = 2;
	A[3] = 1;
	A[4] = 0;

/*
	A[0] = 5;
	A[1] = 4;
	A[2] = 3;
	A[3] = 2;
	A[4] = 1;
*/
/*
	A[0] = 0;
	A[1] = 1;
	A[2] = 2;
	A[3] = 3;
	A[4] = 4;
*/
/*
	A[0] = 4;
	A[1] = 5;
	A[2] = 3;
	A[3] = 2;
	A[4] = 1;
*/

	printf("Peak at %i\n",FindPeak(A, floor(size/2)));
}
