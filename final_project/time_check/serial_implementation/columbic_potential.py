import numpy as np
from copy import deepcopy

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
    partial_charge = deepcopy(atomic_charge)
    partial_charge = np.array([0.0 if molecule_number[i] == molecule_number[j] else partial_charge[j] for j in range(no_of_atoms)])
    partial_charge = np.delete(partial_charge, i)
    distance_vector = position - position[i]
    distance_vector = np.delete(distance_vector, i, axis = 0)
    distance = np.linalg.norm(distance_vector, axis = 1)
    distance_cubed = self_charge * partial_charge / distance**3
    force = np.sum(distance_vector.T * distance_cubed, axis = 1)

    return force  
