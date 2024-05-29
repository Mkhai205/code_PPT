#include "stdio.h"
#include "math.h"

int numberOfEquations, numberOfIterations;
double Bo = 0, eps;
double Ax[101], Bx[100][100], g[100], x[100], x_temp[100];

void enter_data(){
    printf("Enter the number of equations: ");
    scanf("%d", &numberOfEquations);
    printf("Enter the coefficients of the equation:\n");
    for (int i=0; i<numberOfEquations; i++){
        printf("The coefficients of equation %d: ", i+1);
        for(int j=0; j<=numberOfEquations; j++){
            scanf("%lf", &Ax[j]);
        }
        for(int j=0; j<numberOfEquations; j++){
            if(i == j) continue;
            Bx[i][j] = -Ax[j]/Ax[i];
        }
        g[i] = Ax[numberOfEquations]/Ax[i];
    }
    printf("\nEnter the number of iterations: ");
    scanf("%d", &numberOfIterations);
}

int file_data(){
    FILE *fp;
    char filename[] = "input_SIM.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }
    fscanf(fp, "%d", &numberOfEquations);
    for(int i=0; i<numberOfEquations; i++){
        for(int j=0; j<=numberOfEquations; j++){
            fscanf(fp, "%lf", &Ax[j]);
        }
        for(int j=0; j<numberOfEquations; j++){
            if(i == j) continue;
            Bx[i][j] = -Ax[j]/Ax[i];
        }
        g[i] = Ax[numberOfEquations]/Ax[i];
    }
    fscanf(fp, "%d", &numberOfIterations);
    fclose(fp);
    printf("Read file successfully\n");
    return 1;
}

int input(){
    char choice, temp;
    while(1){
        printf("Do you want to enter data from the keyboard or from the file? (k/f): ");
        scanf("%c", &choice);
        scanf("%c", &temp);
        if(choice == 'k'){
            enter_data();
            return 1;
        } else if(choice == 'f'){
            return file_data();
        } else {
            printf("Invalid choice\n");
        }
    }
}

void output(){
    printf("\n###############################################\n");
    printf("Error: %.16lf\n", eps);
    printf("\nThe solution of the system of equations is:\n");
    for(int i=0; i<numberOfEquations; i++){
        printf("x[%d] = %.10lf +- %.16lf\n", i+1, x[i], eps);
    }
    printf("\n------------------------------------------------\n");
}

void convergence_conditions(){
    for(int i=0; i<numberOfEquations; i++){
        double max_temp = 0;
        for(int j=0; j<numberOfEquations; j++){
            max_temp += fabs(Bx[i][j]);
        }
        if(max_temp > Bo) Bo = max_temp;
    }
}

void error_assessment(){
    double max = 0, temp;
    for(int i=0; i<numberOfEquations; i++){
        temp = fabs(x[i] - x_temp[i]);
        if(temp > max) max = temp;
    }
    eps = Bo/(1-Bo)*max;
}

void swap(double *a, double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
}

void repeat(int n){
    if(n == 0){
        error_assessment();
        return;
    }
    for(int i=0; i<numberOfEquations; i++){
        double sum = 0;
        for(int j=0; j<numberOfEquations; j++){
            sum += Bx[i][j]*x[j];
        }
        x_temp[i] = sum + g[i];
    }
    for(int i=0; i<numberOfEquations; i++){
        swap(&x[i], &x_temp[i]);
    }
    repeat(n-1);
}

void single_iteration_method(){
    if(input()){
        convergence_conditions();
        if(Bo >= 1){
            printf("The system of equations does not converge\n");
            return;
        }
        repeat(numberOfIterations);
        output();
    }
}

int main(){
    single_iteration_method();
    return 0;
}

