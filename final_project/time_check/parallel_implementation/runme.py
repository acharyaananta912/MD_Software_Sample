from mdrun import mdrun

print("Varied atoms with fixed box length and simulation time")
print("No of atoms, box length (nm), simulation time (ps), frames, cpu-time (s)")
mdrun(33, 20, 150)
mdrun(66, 20, 150)
mdrun(99, 20, 150)
print("\n")


print("fixed atoms varied simulation time")
print("No of atoms, box length (nm), simulation time (ps), frames, cpu-time (s)")
mdrun(99, 50, 500)
mdrun(99, 50, 1000)
mdrun(99, 50, 1500)
print("\n")