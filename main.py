import subprocess
import matplotlib.pyplot as plt


# The number you want to pass as input to the bash script
numbers = [1, 10, 100, 1000, 10000, 100000, 100000]

seq_times = []
mpi_times = []


for number in numbers:
    # Run the .bash script and pass the number as an argument
    result = subprocess.run(['./main.bash', str(number)], capture_output=True, text=True)
    
    lines = result.stdout.splitlines()

    print(f"{lines[0]}, {number}")
    print(f"{lines[1]}, {number}")
    print()

    seq_values = lines[0].split(": ")[1].split(", ")
    mpi_values = lines[1].split(": ")[1].split(", ")

    seq_times.append(int(seq_values[2]))
    mpi_times.append(int(mpi_values[2]))

    # Capture and print the output

plt.plot(numbers, seq_times, color='blue', label='seq_times')  # Horizontal bars for number1
plt.plot(numbers, mpi_times, color='orange', label='mpi_times')  # Number 2 starts from the value of number 1

plt.xlabel('N')
plt.ylabel('Time')
plt.title('Growth of execution time with MPI and Sequence implementation of pi calculation')
plt.legend()
plt.show()
