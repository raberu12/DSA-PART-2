#include<stdio.h>
#include<stdlib.h>

struct employee{
    int employeeID;
    char name[100];
    float salary;
};

void getInfo(struct employee * emp, int size);
void dispInfo(struct employee * emp, int size);

int main(){
    int size = 3;
    struct employee * emp;

    getInfo(emp, size);
    return 0;

}

void getInfo(struct employee * emp, int size){
    int i;
    
    struct employee wow;
    
    emp = &wow;
    
    for (i = 0; i < size; i++)
    {
        printf("\n\nEmployee %d ID: ", i+1);
        scanf("%d", &emp[i].employeeID);
        printf("\nEmployee %d name: ", i+1);
        scanf("%s", emp[i].name);
        printf("\nEmployee %d salary: ", i+1);
        scanf("%f", &emp[i].salary);
    }

    dispInfo(emp, size);
    
}

void dispInfo(struct employee * emp, int size){
    int i;

    for(i = 0; i < size; i++){
        printf("\n\nEmployee %d", i+1);
        printf("\nID: %d", emp[i].employeeID);
        printf("\nName: %s", emp[i].name);
        printf("\nSalary: %.2f", emp[i].salary);
    }

}
