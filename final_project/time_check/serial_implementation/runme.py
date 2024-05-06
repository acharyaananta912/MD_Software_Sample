from mdrun import mdrun

print("Varied atoms with fixed box length and simulation time")
print("No of atoms, box length (nm), simulation time (ps), frames, cpu-time (s)")
mdrun(33, 20, 150)
mdrun(66, 20, 150)
mdrun(99, 20, 150)
print("\n")

print("Varied atoms and box length with fixed simulation time")
print("No of atoms, box length (nm), simulation time (ps), frames, cpu-time (s)")
mdrun(333, 50, 150)
mdrun(666, 50, 150)
mdrun(999, 50, 150)
print("\n")

print("fixed atoms varied simulation time")
print("No of atoms, box length (nm), simulation time (ps), frames, cpu-time (s)")
mdrun(333, 50, 500)
mdrun(333, 50, 1000)
mdrun(333, 50, 1500)
print("\n")




