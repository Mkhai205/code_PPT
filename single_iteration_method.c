#include "stdio.h"
#include "math.h"

int n, sll;
double Bo = 0, eps;
double Ax[101], Bx[100][100], g[100], x[100], x_temp[100];

void input(){
    printf("Enter the number of equations: ");
    scanf("%d", &n);
    printf("Enter the coefficients of the equation:\n");
    for (int i=0; i<n; i++){
        printf("The coefficients of equation %d: ", i+1);
        for(int j=0; j<=n; j++){
            scanf("%lf", &Ax[j]);
        }
        for(int j=0; j<n; j++){
            if(i == j) continue;
            Bx[i][j] = -Ax[j]/Ax[i];
        }
        g[i] = Ax[n]/Ax[i];
    }
    printf("\nEnter the number of iterations: ");
    scanf("%d", &sll);
}

void output(){
    printf("\n####################################\n");
    printf("Error: %.10lf\n", eps);
    printf("\nThe solution of the system of equations is:\n");
    for(int i=0; i<n; i++){
        printf("x[%d] = %.10lf +- %.10lf\n", i+1, x[i], eps);
    }
}

void convergence_conditions(){
    for(int i=0; i<n; i++){
        double max_temp = 0;
        for(int j=0; j<n; j++){
            max_temp += fabs(Bx[i][j]);
        }
        if(max_temp > Bo) Bo = max_temp;
    }
}


void error_assessment(){
    double max = 0, temp;
    for(int i=0; i<n; i++){
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

void repeat(int sll){
    if(sll == 0){
        error_assessment();
        return;
    }
    for(int i=0; i<n; i++){
        double sum = 0;
        for(int j=0; j<n; j++){
            sum += Bx[i][j]*x[j];
        }
        x_temp[i] = sum + g[i];
    }
    for(int i=0; i<n; i++){
        swap(&x[i], &x_temp[i]);
    }
    repeat(sll-1);
}

void single_iteration_method(){
    input();
    convergence_conditions();
    if(Bo >= 1){
        printf("The system of equations does not converge\n");
        return;
    }
    repeat(sll);
    output();
}

int main(){
    single_iteration_method();
    return 0;
}

