import os

Number_of_files = 11

for i  in range(Number_of_files):
    os.system("mpirun -n 4 ./Project_4")

    directory = "../../Py_Scripts/Results/4E/WrittenFiles/"
    old_file = os.path.join(directory, "L_80_0.txt")
    new_file = os.path.join(directory, "L_80_" + str(i) + ".txt")
    os.rename(old_file, new_file)
