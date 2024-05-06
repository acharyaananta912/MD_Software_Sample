import os
import numpy as np
import time

from acceleration_update import calculate_acceleration
from temperature_scaling import TempScale
from acceleration_update import update_cord_vel
from generate_dumpfile import generate_coordinates

# parameters

no_of_atoms = 333
dimension = 3
len_each_dimension = 50.0 								# in Angstorm
boundary_condition = 1 					# Reflection
partial_charge = [0.41, -0.82] 			# charges of particles
initial_temperature = 500 				# initial temperature in K
mass = [1.0, 16.0] 						# mass of Hydrogen and mass of Oxygen 
dt = 0.0001                             # in ps

# constants

boltzman_constant = 0.8314459920816467
avogadro_number = 6.0221409e+26         # Avogagro constant (for kilomole)
electron_charge = 1.60217662E-19		# charge of electron (Columb)
columbic_force = 8.9875517923E9 * avogadro_number * 1E30 * ( electron_charge**2) / (1E24) # columbic force total

# Interaction params
# Source: Xin Bo Zhang et al. Fluid Phase Equilibria 262 (2007) 210–216 doi:10.1016/j.fluid.2007.09.005 

epsilon = [[3.24, 14.2723], [14.2723, 62.87]]
sigma = [[0.98,2.04845],[2.04845,3.1169]]
constant_length = 148000.0/2        # spring constant for bond length
bond_length = 0.9611                # H--O bond length for water
constant_angle =35300.0/2           # spring constant for bond angle of water
bond_angle = 109.47 * np.pi / 180.0 # bond angle of water in radian

# making cubic box
box_dimension = np.ones(dimension) * len_each_dimension

# initializing position and velocity for all the particles throught the length
np.random.seed(0)
position = np.random.rand(no_of_atoms, dimension) * len_each_dimension
velocity = np.random.rand(no_of_atoms, dimension) - 0.5

# making directory to store coordinates

outdir = "coordinates"
try: 
	os.mkdir(outdir)
except:
	pass


"""
Atomtypes: H--O--H
Water molecules are represented in this simulation, hence HOH always come together.
If number of atoms is not the multiple of 3, rest atoms will be H.

Bonds: Water molecule has H--O--H bonds hence there are two bonds for each molecules.
H--H bond, O--O bond and non-sequencial O--H bonds (as the coordinates are randomized 
they should have been accounted however) are not taken into account.

Angles: Consecutive H--O--H form angles. Other combinations are ignored


"""
# Assigning atomtypes to the atoms
atomtype = np.array([0, 1, 0] * (no_of_atoms// 3) + [0] * (no_of_atoms % 3))

# Assigning bonds between H--O--H
bonds = np.array([[i-1, i, bond_length, constant_length] for i in range(len(atomtype)) if atomtype[i] == 1] 
				 + [[i, i+1, bond_length, constant_length] for i in range(len(atomtype)-1) if atomtype[i] == 1])

# Assigning angles between H--O--H
angles = np.array([[i-1, i, i+1, bond_angle, constant_angle] for i in range(len(atomtype)) if atomtype[i] == 1 ])

# Assigning molecular number to the molecules
molecule_number = np.array([i for i in range(int(len(atomtype)/3)) for _ in range(3)])

"""
Hydrogen and Oxygen has different molecular mass and partial charge. Assigning those charges

"""
atomic_mass = np.array([mass[1] if atom == 1 else mass[0] for atom in atomtype])
atomic_charge = np.array([partial_charge[1] if atom == 1 else partial_charge[0] for atom in atomtype])


'''************************************************************************
**	    Variables above are the parameters for MD Simulation           	 **
**   Codes below uses functions based on theory of MD Simulation   	     **
**                                                                       **
************************************************************************'''

skip = 20
frames = 150
STEPS = skip * frames
start_time = time.time()
for i in range(STEPS):
	velocity, acceleration = calculate_acceleration(position, velocity, dt, sigma, epsilon, atomtype, bonds, molecule_number, angles, atomic_mass, atomic_charge)
	velocity = TempScale(initial_temperature, velocity, atomic_mass, boltzman_constant)
	position, velocity = update_cord_vel(position, velocity, dt, box_dimension)
	if i % skip == 0:
		generate_coordinates(position, int(i/skip), outdir, molecule_number, atomtype, box_dimension)
		print("Frame: ", int(i/skip))
end_time = time.time()
print("Time taken for simulation: ", (end_time - start_time), " seconds")