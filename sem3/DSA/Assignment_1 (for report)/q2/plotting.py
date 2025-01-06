import csv
import numpy as np
import matplotlib.pyplot as plt

csv_file_path = r"C:\Users\ABHIRUP\Desktop\code_playground\DSA_Assignments\Sem2_DSA\DSA-assignment\Assignment_1\fibonacci_data.csv"

n_values = []
times = []

with open(csv_file_path, 'r') as file:
    csv_reader = csv.reader(file)
    next(csv_reader, None)
    for row in csv_reader:
        try:
            n = int(row[0])
            time = float(row[1])
            n_values.append(n)
            times.append(time)
        except ValueError:
            print(f"Skipping invalid row: {row}")

n_values = np.array(n_values)
times = np.array(times)

plt.figure(figsize=(10, 6))
plt.plot(n_values, times, marker='o', linestyle='-', color='b', label='Time vs n')

plt.xlabel('n (input size)')
plt.ylabel('Fibonacci value')
plt.title('Fibonacci Graph')
plt.grid(True)
plt.legend()

plt.show()
