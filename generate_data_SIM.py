import random

def generate_single_iteration_method(numberOfEquations, numberOfIterations=1, filename="input_SIM.txt"):
    with open("input_SIM.txt", 'w') as file:
        file.write(f"{numberOfEquations}\n")
        
        variables = [random.randint(-10, 10) for _ in range(numberOfEquations)]
        
        for i in range(numberOfEquations):
            sum = 0
            for j in range(numberOfEquations):
                if(i == j): coefficient = random.randint(1, 10)
                else: coefficient = random.uniform(-1, 1)
                file.write(f"{coefficient}\n")
                sum += coefficient * variables[j]
            file.write(f"{sum}\n")
            
        file.write(f"{numberOfIterations}\n")
        
        file.write(f"The result:\n")
        for i in range(numberOfEquations):
            file.write(f"x[{i+1}] = {variables[i]}\n")
    
    file.close()
    print(f"Data generated successfully and saved as file: {filename}!")

if __name__ == "__main__":
    numberOfEquations = 4
    numberOfIterations = 5
    filename = "input_SIM.txt"
    
    generate_single_iteration_method(numberOfEquations, numberOfIterations, filename)         