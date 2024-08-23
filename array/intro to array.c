#include <stdio.h>
#include <stdlib.h>

int *getAllNegative(int arr[], int size);

int main() {
	
	int A[] = {2,-1,4,-7};
	int B[] = {-1,-2,-3,-6,-8};
	int C[] = {2,1,3,4};
	int sizeA = 4;
	int sizeB = 5;
	int sizeC = 4;
	int *D = getAllNegative(A, sizeA);
	int *E = getAllNegative(B, sizeB);
	int *F = getAllNegative(C, sizeC);
	
	int i = 0; 
	printf("Test Case 1: ");
	for(i = 0; i <= D[0]; i++){
		printf("%d ", D[i]);
	}
	printf("\nTest Case 2: ");
	for(i = 0; i <= E[0]; i++){
		printf("%d ", E[i]);
	}
	printf("\nTest Case 3: ");
	for(i = 0; i <= F[0]; i++){
		printf("%d ", F[i]);
	}

}

int *getAllNegative(int arr[], int size) {
	int temp[size];
	int count = 0;
	int x = 0;
	for(x = 0; x < size; x++) {
		if(arr[x] < 0) {
			temp[count] = arr[x];
			count++;
		}
	}
	int newsize = count + 1;
	int *retval = (int*)malloc(sizeof(int)*newsize);
	if(retval != NULL) {
		retval[0] = count;
		for(x = 0; x < count; x++) {
			retval[x+1] = temp[x];
		}
	}
	return retval;
}
