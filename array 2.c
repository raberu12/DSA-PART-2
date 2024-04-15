#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int num[20];
	int count;
} arrListNum;

arrListNum getAllNegative(arrListNum A);
void display(arrListNum A);

int main() {
	
	arrListNum case1 = {{2, -1, 4, -7}, 4};
	arrListNum case2 = {{-1, -2, -3, -6, -8}, 5};
	arrListNum case3 = {{2, 1, 3, 4}, 4};
	
	arrListNum test1 = getAllNegative(case1);
	arrListNum test2 = getAllNegative(case2);
	arrListNum test3 = getAllNegative(case3);
	
	printf("Case 1: ");
	display(test1);
	printf("\nCase 2: ");
	display(test2);
	printf("\nCase 3: ");
	display(test3);

}

arrListNum getAllNegative(arrListNum A){
	
	int i;
	arrListNum retval = {{0},0};
	for(i = 0; i < A.count; i++){
		if(A.num[i] < 0){
			retval.num[retval.count] = A.num[i];
			retval.count++;
		}
	}
	return retval;
}

void display(arrListNum A){
	
	int i;
	printf("%d " , A.count);
	for(i = 0; i < A.count; i++){
		printf("%d ", A.num[i]);
	}
	
}
