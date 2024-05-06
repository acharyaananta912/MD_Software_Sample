import numpy as np
from numba import jit, prange

@jit(nopython = True, parallel = True)
def columbic_force(position, i, atomic_charge, molecule_number):

       '''
       Calculates columbic force between the atoms.
       This is non-bonded interaction following interactions are not considered:
       1. Self interaction
       2. Bonded interaction
       3. Angle interaction
       Formula: F = q1 * q2 * r^2
       where: q1, q2 = atomic charges
              r = distance between the atoms
       '''
       no_of_atoms = len(position)
       self_charge = atomic_charge[i]
       force = np.zeros(position.shape[1])  # Initialize force vector

       # Calculate forces only for non-bonded interactions
       for j in prange(no_of_atoms):
              if i != j and molecule_number[i] != molecule_number[j]:
                     r_vec = position[j] - position[i]
                     dist = np.linalg.norm(r_vec)
                     if dist > 0:  # Avoid division by zero
                            # Coulomb's law: F = k * q1 * q2 / r^2, here simplified to q1 * q2 / r^3 * r_vec
                            force_component = (self_charge * atomic_charge[j] / dist**3) * r_vec
                            force += force_component

       return force
