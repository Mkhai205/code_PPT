#include "stdio.h"
#include "math.h"

int degreeOfPolynomial, numberOfPoints, numberOfCoefficients;
double x[100005], y[100005];
// Array X to store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
// Array Y to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
double X[11], Y[11];
double polynomialCoefficientsMatrix[11][12], interpolationCoefficients[11];

void enter_data(){
    printf("\nEnter the number of data pairs: ");
    scanf("%d", &numberOfPoints);
    
    // Input x-values
    printf("\nEnter the x-axis values:\n"); 
    for(int i=0; i<numberOfPoints; i++){
        scanf("%lf", &x[i]);
    }
    
    // Input y-values
    printf("\nEnter the y-axis values:\n"); 
    for(int i=0; i<numberOfPoints; i++){
        scanf("%lf", &y[i]);
    }
    
    // Enter the degree of polynomial
    printf("\nWhat degree of Polynomial do you want to use for the fit?\n");
    scanf("%d", &degreeOfPolynomial);
    numberOfCoefficients = degreeOfPolynomial + 1;
}

int file_data(){
    FILE *fp;
    char filename[] = "input_PI.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }
    fscanf(fp, "%d", &numberOfPoints);
    for(int i=0; i<numberOfPoints; i++){
        fscanf(fp, "%lf", &x[i]);
    }
    for(int i=0; i<numberOfPoints; i++){
        fscanf(fp, "%lf", &y[i]);
    }
    fscanf(fp, "%d", &degreeOfPolynomial);
    numberOfCoefficients = degreeOfPolynomial + 1;
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

void data_preprocessing(){
    // Consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    for(int i=0; i<2*degreeOfPolynomial+1; i++){
        X[i] = 0;
        for(int j=0; j<numberOfPoints; j++){
            X[i] = X[i] + pow(x[j],i); 
        }
    }
    // Consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    for(int i=0;i<degreeOfPolynomial+1;i++){    
        Y[i] = 0;
        for(int j=0;j<numberOfPoints;j++){ 
            Y[i] = Y[i] + pow(x[j],i)*y[j]; 
        }
    }
    // Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
    for(int i=0;i<=degreeOfPolynomial;i++){ 
        for(int j=0; j<=degreeOfPolynomial; j++){
            polynomialCoefficientsMatrix[i][j] = X[i+j];
        }
    }
    // Build the values of Y as the last column of polynomialCoefficientsMatrix(Normal Matrix but augmented)
    for(int i=0; i<=degreeOfPolynomial; i++){ 
        polynomialCoefficientsMatrix[i][degreeOfPolynomial+1] = Y[i];
    }
    // The number of coefficients in the augmented matrix
    printf("\nThe Augmented Matrix is as follows:\n");
    for(int i=0; i<numberOfCoefficients; i++){
        for(int j=0; j<numberOfCoefficients; j++){
            printf("%lf\t", polynomialCoefficientsMatrix[i][j]);
        }
        printf("|   %lf\n", polynomialCoefficientsMatrix[i][numberOfCoefficients]);
    }
}

void solve_by_gaussian(){
    // Solve the system of equations according to gaussian theory
    // Loop to perform the gauss elimination
    for(int i=0; i<numberOfCoefficients-1; i++){ 
        for(int k=i+1; k<numberOfCoefficients; k++){
            double tmp = polynomialCoefficientsMatrix[k][i]/polynomialCoefficientsMatrix[i][i];
            for(int j=0; j<=numberOfCoefficients; j++){
                polynomialCoefficientsMatrix[k][j] = polynomialCoefficientsMatrix[k][j] - tmp*polynomialCoefficientsMatrix[i][j];
            }
        }
    }
    // Back substitution
    for(int i=numberOfCoefficients-1; i>=0; i--){
        interpolationCoefficients[i] = polynomialCoefficientsMatrix[i][numberOfCoefficients];
        for(int j=numberOfCoefficients-1; j>i; j--){
            interpolationCoefficients[i] = interpolationCoefficients[i] - polynomialCoefficientsMatrix[i][j]*interpolationCoefficients[j];
        }
        interpolationCoefficients[i] = interpolationCoefficients[i]/polynomialCoefficientsMatrix[i][i];
    }
}

void output(){
    // Print the results
    printf("\nThe values of the coefficients are as follows:\n");
    for(int i=0; i<numberOfCoefficients; i++){
        printf("%c = %lf\n", 'a'+i, interpolationCoefficients[i]);
    }

    printf("\nThe fitted Polynomial is given by:\ny = ");
    for(int i=0; i<numberOfCoefficients; i++){
        printf("%lf", interpolationCoefficients[i]);
        if (i != 0)  printf("x^%d", i);
        if (i != numberOfCoefficients-1)  printf(" + ");
    }
    printf("\n\n-------------------------------------------------------------\n");
}

void file_output(){
    FILE *fp;
    char filename[] = "output_PI.txt";
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    for(int i=0; i<numberOfCoefficients; i++){
        fprintf(fp, "%.16lf\n", interpolationCoefficients[i]);
    }
    for(int i=0; i<numberOfPoints; i++){
        fprintf(fp, "%lf ", x[i]);
    }
    fprintf(fp, "\n");
    for(int i=0; i<numberOfPoints; i++){
        fprintf(fp, "%lf ", y[i]);
    }
    fclose(fp);
    printf("Write file successfully\n");
}

void polynomial_interpolation(){
    if(input()){
        data_preprocessing();
        solve_by_gaussian();
        output();
        file_output();
    }
}

int main(){
    polynomial_interpolation();
    return 0;
}