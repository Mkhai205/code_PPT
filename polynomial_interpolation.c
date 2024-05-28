#include "stdio.h"
#include "math.h"

int main(){
    // Declare the variables
    int i , j, k, degreeOfPolynomial, numberOfPoints;
    
    // Enter the data
    printf("\nEnter the number of data pairs: ");
    scanf("%d", &numberOfPoints);
    
    
    double x[numberOfPoints], y[numberOfPoints];
    // Input x-values
    printf("\nEnter the x-axis values:\n"); 
    for(i=0; i<numberOfPoints; i++){
        scanf("%lf", &x[i]);
    }
    
    // Input y-values
    printf("\nEnter the y-axis values:\n"); 
    for(i=0; i<numberOfPoints; i++){
        scanf("%lf", &y[i]);
    }
    
    // Enter the degree of polynomial
    printf("\nWhat degree of Polynomial do you want to use for the fit?\n");
    scanf("%d", &degreeOfPolynomial); 

    // Array X to store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    // Array Y to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    double X[2*degreeOfPolynomial+1], Y[degreeOfPolynomial+1];
    // Consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    for(i=0; i<2*degreeOfPolynomial+1; i++){
        X[i] = 0;
        for(j=0; j<numberOfPoints; j++){
            X[i] = X[i] + pow(x[j],i); 
        }
    }
    // Consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    for(i=0;i<degreeOfPolynomial+1;i++){    
        Y[i] = 0;
        for(j=0;j<numberOfPoints;j++){ 
            Y[i] = Y[i] + pow(x[j],i)*y[j]; 
        }
    }
    
    // B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
    double B[degreeOfPolynomial+1][degreeOfPolynomial+2], a[degreeOfPolynomial+1];
    // Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
    for(i=0;i<=degreeOfPolynomial;i++){ 
        for(j=0; j<=degreeOfPolynomial; j++){
            B[i][j] = X[i+j];
        }
    }
    // Build the values of Y as the last column of B(Normal Matrix but augmented)
    for(i=0; i<=degreeOfPolynomial; i++){ 
        B[i][degreeOfPolynomial+1] = Y[i]; 
    }
    

    // Solve the system of equations according to gaussian theory
    int numberOfCoefficients = degreeOfPolynomial + 1;
    printf("\nThe Augmented Matrix is as follows:\n");
    for(i=0; i<numberOfCoefficients; i++){
        for(j=0; j<numberOfCoefficients; j++){
            printf("%lf\t", B[i][j]);
        }
        printf("|   %lf\n", B[i][numberOfCoefficients]);
    }
    // Loop to perform the gauss elimination
    for(i=0; i<numberOfCoefficients-1; i++){ 
        for(k=i+1; k<numberOfCoefficients; k++){
            double tmp = B[k][i]/B[i][i];
            for(j=0; j<=numberOfCoefficients; j++){
                B[k][j] = B[k][j] - tmp*B[i][j];
            }
        }
    }
    // Back substitution
    for(i=numberOfCoefficients-1; i>=0; i--){ 
        a[i] = B[i][numberOfCoefficients];
        for(j=numberOfCoefficients-1; j>i; j--){
            a[i] = a[i] - B[i][j]*a[j];
        }
        a[i] = a[i]/B[i][i];
    }


    // Print the results
    printf("\nThe values of the coefficients are as follows:\n");
    for(i=0; i<numberOfCoefficients; i++){
        printf("%c = %lf\n", 'a'+i, a[i]);
    }

    printf("\nThe fitted Polynomial is given by:\ny = ");
    for(i=0; i<numberOfCoefficients; i++){
        printf("%lf", a[i]);
        if (i != 0)  printf("x^%d", i);
        if (i != numberOfCoefficients-1)  printf(" + ");
    }
    printf("\n\n-------------------------------------------------------------");
    return 0;
}