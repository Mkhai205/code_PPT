#include "stdio.h"
#include "math.h"
#include "string.h"

int numberOfEquations, numberOfIterations = 0, mode, idx = 0;
double Bo = 0, eps;
double Ax[101], Bx[100][100], g[100], x[20][100], epsPerIteration[100];

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
    if(mode == 1){
        printf("Enter the number of iterations: ");
        scanf("%d", &numberOfIterations);
    } else {
        printf("Enter the error: ");
        scanf("%lf", &eps);
    }
}

int file_data(){
    FILE *fp;
    char filename[256];
    if(mode == 1) strcpy(filename, "input_SIM_n.txt");
    else strcpy(filename, "input_SIM_e.txt");
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
    if(mode == 1) fscanf(fp, "%d", &numberOfIterations);
    else fscanf(fp, "%lf", &eps);
    fclose(fp);
    printf("Read file successfully\n");
    return 1;
}

int input(){
    char choice;
    do{
        printf("---------------------------------------------------------------\n");
        printf("Select the mode of operation:\n");
        printf("1.Calculated according to the number of iterations.\n");
        printf("2.Calculated according to the error.\n");
        printf("Enter the mode: ");
        scanf("%d", &mode);
        fflush(stdin);
        if(mode != 1 && mode != 2) printf("*** Invalid mode! ***\n");
    } while(mode != 1 && mode != 2);

    while(1){
        printf("Do you want to enter data from the keyboard or from the file? (k/f): ");
        scanf("%c", &choice);
        fflush(stdin);
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

void convergence_conditions(){
    for(int i=0; i<numberOfEquations; i++){
        double max_temp = 0;
        for(int j=0; j<numberOfEquations; j++){
            max_temp += fabs(Bx[i][j]);
        }
        if(max_temp > Bo) Bo = max_temp;
    }
}

double error_assessment(){
    double max = 0, temp;
    for(int i=0; i<numberOfEquations; i++){
        temp = fabs(x[idx+1][i] - x[idx][i]);
        if(temp > max) max = temp;
    }
    return Bo/(1-Bo)*max;
}

void repeat_n(int n){
    if(n == 0) return;
    for(int i=0; i<numberOfEquations; i++){
        double sum = 0;
        for(int j=0; j<numberOfEquations; j++){
            sum += Bx[i][j]*x[idx][j];
        }
        x[idx+1][i] = sum + g[i];
    }
    epsPerIteration[idx] = error_assessment();
    idx++;
    repeat_n(n-1);
}

void repeat_error(){
    for(int i=0; i<numberOfEquations; i++){
        double sum = 0;
        for(int j=0; j<numberOfEquations; j++){
            sum += Bx[i][j]*x[idx][j];
        }
        x[idx+1][i] = sum + g[i];
    }
    epsPerIteration[idx] = error_assessment();
    numberOfIterations++, idx++;
    if(epsPerIteration[idx-1] < eps) return;
    repeat_error();
}

void output(){
    printf("\n###############################################\n");
    printf("Bo = %.16lf\n", Bo);
    for(int i=0; i<numberOfIterations; i++){
        printf("Iteration %d: %.16lf\n", i+1, epsPerIteration[i]);
    }
    printf("\nThe solution of the system of equations is:\n");
    for(int i=0; i<numberOfEquations; i++){
        printf("x[%d] = %.10lf +- %.16lf\n", i+1, x[numberOfIterations-1][i], epsPerIteration[numberOfIterations-1]);
    }
    printf("\n------------------------------------------------\n");
}

void file_output(){
    FILE *fp;
    char filename[] = "output_SIM.txt";
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    for(int i=0; i<numberOfIterations; i++){
        for(int j=0; j<numberOfEquations; j++){
            fprintf(fp, "%.16lf ", x[i][j]);
        }
        fprintf(fp, "\n");
    }
    printf("Write file successfully\n");
}

void single_iteration_method(){
    if(input()){
        convergence_conditions();
        if(Bo >= 1){
            printf("The system of equations does not converge\n");
            return;
        }
        if(mode == 1) repeat_n(numberOfIterations);
        else repeat_error();
        output();
        file_output();
    }
}

int main(){
    single_iteration_method();
    return 0;
}