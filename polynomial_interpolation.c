#include "stdio.h"
#include "math.h"

int main(){
    // declare the variables
    int i,j,k,n,N;
    
    // enter the data
    printf("\nEnter the no. of data pairs to be entered: "); //To find the size of arrays that will store x,y, and z values
    scanf("%d", &N);
    
    double x[N], y[N];
    printf("\nEnter the x-axis values:\n"); //Input x-values
    for(i=0; i<N; i++){
        scanf("%lf", &x[i]);
    }
    
    printf("\nEnter the y-axis values:\n"); //Input y-values
    for(i=0; i<N; i++){
        scanf("%lf", &y[i]);
    }
   
    printf("\nWhat degree of Polynomial do you want to use for the fit?\n");
    scanf("%d", &n); // n is the degree of Polynomial 
    

    // calculate the normal matrix
    double X[2*n+1]; //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    for(i=0; i<2*n+1; i++){
        X[i] = 0;
        for(j=0; j<N; j++){
            X[i] = X[i] + pow(x[j],i); //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
        }
    }
    
    double B[n+1][n+2], a[n+1]; //B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
    for(i=0;i<=n;i++){ //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
        for(j=0; j<=n; j++){
            B[i][j] = X[i+j];
        }
    }

    double Y[n+1]; //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    for(i=0;i<n+1;i++){    
        Y[i] = 0;
        for(j=0;j<N;j++){ //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
            Y[i] = Y[i] + pow(x[j],i)*y[j]; 
        }
    }
    
    for(i=0; i<=n; i++){ //load the values of Y as the last column of B(Normal Matrix but augmented)
        B[i][n+1] = Y[i]; 
    }
    

    // Solve the system of equations in gaussian terms
    n = n+1; //n is made n+1 because the Gaussian Elimination part below was for n equations, 
            //but here n is the degree of polynomial and for n degree we get n+1 equations
    printf("\nThe Normal(Augmented Matrix) is as follows:\n");
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%lf\t", B[i][j]);
        }
        printf("|   %lf\n", B[i][n]);
    }

    for(i=0; i<n-1; i++){ //loop to perform the gauss elimination
        for(k=i+1; k<n; k++){
            double tmp = B[k][i]/B[i][i];
            for(j=0; j<=n; j++){
                B[k][j] = B[k][j] - tmp*B[i][j];
            }
        }
    }

    for(i=n-1; i>=0; i--){ // Back substitution
        a[i] = B[i][n];
        for(j=n-1; j>i; j--){
            a[i] = a[i] - B[i][j]*a[j];
        }
        a[i] = a[i]/B[i][i];
    }


    // Print the results
    printf("\nThe values of the coefficients are as follows:\n");
    for(i=0; i<n; i++){
        printf("%c = %lf\n", 'a'+i, a[i]);
    }

    printf("\nHence the fitted Polynomial is given by:\ny = ");
    for(i=0; i<n; i++){
        printf("%lf", a[i]);
        if (i != 0)  printf("x^%d", i);
        if (i != n-1)  printf(" + ");
    }
    printf("\n\n-------------------------------------------------------------");
    return 0;
}