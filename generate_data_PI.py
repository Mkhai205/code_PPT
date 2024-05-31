import random
import math

def generate_polynomial_data(num_points, coefficients, x_range=(-10, 10), noise_std_dev=0.0, filename="input_PI.txt"):
    """Tạo bộ dữ liệu kiểm tra từ đa thức và ghi vào file.

    Args:
        num_points (int): Số lượng điểm dữ liệu.
        coefficients (list): Danh sách các hệ số của đa thức, từ bậc cao nhất đến bậc thấp nhất.
        x_range (tuple, optional): Khoảng giá trị cho x (min, max). Mặc định là (-5, 5).
        noise_std_dev (float, optional): Độ lệch chuẩn của nhiễu Gaussian thêm vào giá trị y. Mặc định là 0 (không nhiễu).
        filename (str, optional): Tên file để lưu dữ liệu. Mặc định là "input_PI.txt".
    """
    with open(filename, "w") as f:
        f.write(f"{num_points}\n")  # Ghi số lượng điểm dữ liệu

        # Tạo giá trị x (phân bố đều) và ghi vào file
        x_values = [random.uniform(*x_range) for _ in range(num_points)]
        for x in x_values:
            f.write(f"{x}\n")

        # Tạo giá trị y từ đa thức và thêm nhiễu (nếu có)
        for x in x_values:
            y = sum(coef * x**i for i, coef in enumerate(reversed(coefficients)))
            if noise_std_dev > 0:
                y += random.gauss(0, noise_std_dev)  # Thêm nhiễu Gaussian
            f.write(f"{y}\n")

        f.write(f"{len(coefficients) - 1}\n")  # Ghi bậc của đa thức
    f.close()
    
# Ví dụ sử dụng:
num_points = 100
coefficients = [1, 2, 1]  # Đa thức
noise_std_dev = 50  # Thêm nhiễu với độ lệch chuẩn
filename = "input_PI.txt"

generate_polynomial_data(num_points, coefficients, (-20, 20),noise_std_dev=noise_std_dev, filename=filename)
print(f"Đã tạo bộ dữ liệu kiểm tra và lưu vào file: {filename}")