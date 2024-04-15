#include <stdio.h>

void print2DArray(int rows, int columns, int arr[rows][columns]){
  printf("Array Values: \n");
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){ 
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}

int main(void){
  int rows, columns;
    
  printf("Enter number of rows: ");
  scanf("%d", &rows);
  printf("Enter number of columns: ");
  scanf("%d", &columns);

  int arr[rows][columns];

  printf("Enter values for the array: \n");
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
        scanf("%d", &arr[i][j]);
    }
  }

  print2DArray(rows, columns, arr); 
  return 0; 
}

