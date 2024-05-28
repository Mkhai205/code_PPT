#include "stdio.h"
#include "math.h"

int numberOfEquations, numberOfIterations;
double Bo = 0, eps;
double Ax[101], Bx[100][100], g[100], x[100], x_temp[100];

void input(){
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

void output(){
    printf("\n####################################\n");
    printf("Error: %.10lf\n", eps);
    printf("\nThe solution of the system of equations is:\n");
    for(int i=0; i<numberOfEquations; i++){
        printf("x[%d] = %.10lf +- %.10lf\n", i+1, x[i], eps);
    }
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

void repeat(int numberOfIterations){
    if(numberOfIterations == 0){
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
    repeat(numberOfIterations-1);
}

void single_iteration_method(){
    input();
    convergence_conditions();
    if(Bo >= 1){
        printf("The system of equations does not converge\n");
        return;
    }
    repeat(numberOfIterations);
    output();
}

int main(){
    single_iteration_method();
    return 0;
}

