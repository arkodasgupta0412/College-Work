import matplotlib.pyplot as plt
import csv

def load_and_process_data(filename):
    with open(filename) as datafile:
        data = list(csv.reader(datafile, delimiter=','))
        comparisons, execution_times = [], []
        
        for i in range(6):
            comp_list, time_list = [], []  
            for row in data:
                cmp_idx = 1 + i * 2
                et_idx = cmp_idx + 1
                comp_list.append(int(row[cmp_idx]))
                time_list.append(float(row[et_idx]))
            comparisons.append(comp_list)
            execution_times.append(time_list)
            
        return comparisons, execution_times

def plot_comparisons(n, comparisons, title):
    plt.figure(figsize=(10, 6))
    for i, name in enumerate(names):
        plt.plot(n, comparisons[i], color=colors[i], label=f"{name} Sort", linewidth=2)

    plt.xlabel("Array Size", fontsize=14)
    plt.ylabel("Number of Comparisons", fontsize=14)
    plt.title(title, fontsize=16)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=12)
    plt.tight_layout()
    plt.yscale('log')

    plt.show()


def plot_execution_times(n, execution_times, title):
    plt.figure(figsize=(10, 6))
    for i, name in enumerate(names):
        plt.plot(n, execution_times[i], color=colors[i], label=f"{name} Sort", linewidth=2)

    plt.xlabel("Array Size", fontsize=12)
    plt.ylabel("Execution Time (secs)", fontsize=12)
    plt.title(title, fontsize=14)
    plt.yscale('log') 
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=10)
    plt.tight_layout()
    plt.show()


n = [5000, 10000, 15000, 25000, 50000, 80000, 100000]
names = ["Bubble", "Insertion", "Selection", "Merge", "Heap", "Quick"]
colors = ["orange", "green", "blue", "red", "magenta", "black"]

# Menu
print("Sorting Algorithms Analysis\n")
print("Which one to plot?")
print("1. Sorted Array Data")
print("2. Reverse Sorted Array Data")
print("3. Unsorted Array Data")

choice = int(input(">>> "))

if choice == 1:
    comparisons, execution_times = load_and_process_data("sa_data.csv")
    plot_comparisons(n, comparisons, "Number of Comparisons by Sorting Algorithms (Sorted Array)")
    plot_execution_times(n, execution_times, "Execution Time of Sorting Algorithms (Sorted Array)")

elif choice == 2:
    comparisons, execution_times = load_and_process_data("rsa_data.csv")
    plot_comparisons(n, comparisons, "Number of Comparisons by Sorting Algorithms (Reverse Sorted Array)")
    plot_execution_times(n, execution_times, "Execution Time of Sorting Algorithms (Reverse Sorted Array)")

else:
    comparisons, execution_times = load_and_process_data("usa_data.csv")
    plot_comparisons(n, comparisons, "Number of Comparisons by Sorting Algorithms (Unsorted Array)")
    plot_execution_times(n, execution_times, "Execution Time of Sorting Algorithms (Unsorted Array)")
