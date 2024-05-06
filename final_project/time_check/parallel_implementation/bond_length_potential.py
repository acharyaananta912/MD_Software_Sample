import numpy as np
from numba import jit, prange

@jit(nopython=True, parallel=True)
def BondPotentialGradient(position, bonds):
    """
    Bond potential is calculated using the formula:
    V = sum (k * (r - r0)^2)
    where:
    k = constant_length
    r = distance between the atoms
    r0 = bond_length

    Parameters:
    position: coordinates of the atoms (6 x 3)
    bonds: atom i, atom j, bond length, spring constant

    """
    no_of_atoms, dimension = position.shape
    grad_bond_pot = np.zeros((no_of_atoms, dimension))

    for bond_pair in range(len(bonds)):
        atom1, atom2 = int(bonds[bond_pair][0]), int(bonds[bond_pair][1])
        r12 = np.linalg.norm(position[atom1] - position[atom2])
        for dim in prange(dimension):
            grad_bond_pot[atom1][dim] += 2 * bonds[bond_pair][3] * (r12 - bonds[bond_pair][2]) * (position[atom1][dim] - position[atom2][dim]) / r12
            grad_bond_pot[atom2][dim] += 2 * bonds[bond_pair][3] * (r12 - bonds[bond_pair][2]) * (position[atom2][dim] - position[atom1][dim]) / r12
    
    return grad_bond_pot
