import numpy as np

def VdW_potential_gradient(position, i, sigma, epsilon, atomtype, molecule_number):
    '''
    Calculates VdW potential gradient of atom pairs
    This is non-bonded interaction so only atoms which are not bonded are considered
    Self interaction is also not considered
    '''
    no_of_atoms = len(position)
    sig_temp = np.delete(np.array([sigma[atomtype[j]] for j in range(no_of_atoms)]), i)
    eps_temp = np.array([epsilon[atomtype[j]] for j in range(no_of_atoms)])
    for k in range(no_of_atoms):
        if molecule_number[i] == molecule_number[k]:
            eps_temp[k] = 0
    eps_temp = np.delete(eps_temp, i)
    distance_vector = position - position[i]
    distance_vector = np.delete(distance_vector, i, 0)
    distance = [np.linalg.norm(distance_vector, axis = 1)]
    r7 = eps_temp * (sig_temp**6)*  (1 / np.array(distance)) ** 7
    r13 = 2 * eps_temp * (sig_temp**12) * (1/ np.array(distance)) ** 13
    r7_vector = np.transpose(np.transpose(distance_vector) * r7)
    r13_vector = np.transpose(np.transpose(distance_vector) * r13)
    lennard_jones_force = 24.0 * (np.sum(r13_vector, axis=0) - np.sum(r7_vector, axis = 0))
    return lennard_jones_force