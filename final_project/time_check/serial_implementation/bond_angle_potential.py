import numpy as np

def BondAnglePotGradient(positions, angles):
    """
    Calculate the gradient of the bond angle potential for a set of atoms based on their positions.

    Parameters:
    - positions (np.ndarray): An array of shape (no_of_atoms, dimension) containing the position vectors of the atoms.
    - angles (list of tuples): A list of tuples, each containing the indices of three atoms forming an angle, the equilibrium angle, and the force constant (at1, at2, at3, eq_theta, k_theta).

    Returns:
    - np.ndarray: Gradient of the bond angle potential for each atom.
    """
    no_of_atoms, dimension = positions.shape
    grad_angle_pot = np.zeros([no_of_atoms, dimension])
    
    for angle in angles:
        at1, at2, at3 = map(int, angle[:3])
        eq_theta, k_theta = angle[3:]
        
        # Calculate vectors
        vec1 = positions[at1] - positions[at2]
        vec2 = positions[at3] - positions[at2]
        
        # Calculate norms of the vectors
        dist1 = np.linalg.norm(vec1)
        dist2 = np.linalg.norm(vec2)
        
        # Calculate dot product and angle
        dot_product = np.dot(vec1, vec2)
        cos_theta = dot_product / (dist1 * dist2)
        theta = np.arccos(max(min(cos_theta, 1), -1))  # Clamped to avoid domain errors
        
        # Calculate the gradient of potential
        factor = -2 * k_theta * (theta - eq_theta) / np.sqrt(1 - cos_theta**2) if cos_theta**2 < 1 else 0
        factor /= (dist1 * dist2)
        
        # Components of the gradient due to each vector
        grad1 = factor * (vec2 / dist1 - (dot_product / dist1**3) * vec1)
        grad2 = factor * (vec1 / dist2 - (dot_product / dist2**3) * vec2)
        
        # Apply gradient contributions to the respective atoms
        grad_angle_pot[at1] += grad1
        grad_angle_pot[at2] -= grad1 + grad2
        grad_angle_pot[at3] += grad2

    return grad_angle_pot
