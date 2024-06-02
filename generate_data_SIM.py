import random

def generate_single_iteration_method(numberOfEquations, error, numberOfIterations=1):
    with open("input_SIM_n.txt", 'w') as file1, open("input_SIM_e.txt", 'w') as file2, open("result_SIM.txt", "w") as file3:
        file1.write(f"{numberOfEquations}\n")
        file2.write(f"{numberOfEquations}\n")
        
        variables = [random.randint(-10, 10) for _ in range(numberOfEquations)]
        
        for i in range(numberOfEquations):
            sum = 0
            for j in range(numberOfEquations):
                if(i == j): coefficient = random.randint(1, 10)
                else: coefficient = random.uniform(-1, 1)
                file1.write(f"{coefficient}\n")
                file2.write(f"{coefficient}\n")
                
                sum += coefficient * variables[j]
            file1.write(f"{sum}\n")
            file2.write(f"{sum}\n")
            
        file1.write(f"{numberOfIterations}\n")
        file2.write(f"{error}\n")
        
        for i in range(numberOfEquations):
            file3.write(f"{variables[i]} ")
            
    file1.close()
    file2.close()
    print("--- Data generated successfully! ---")

if __name__ == "__main__":
    numberOfEquations = 4
    numberOfIterations = 5
    error = 0.005
    generate_single_iteration_method(numberOfEquations, error,numberOfIterations) 