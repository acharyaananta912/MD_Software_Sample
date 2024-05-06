from copy import deepcopy
import numpy as np

def update_cord_vel(position, velocity, dt):
    """
    Updates the position and velocity of the atoms
    """
    box_dimension = position.shape[1]
    new_position = position + velocity * dt
    new_position = new_position % box_dimension
    new_velocity = deepcopy(velocity)
    return new_position, new_velocity

def calculate_acceleration(position, velocity, dt, sigma, epsilon):
    """
    Calculates acceleration of the atoms based on the forces
    Forces are calculated based on the potential energy F = -dV/dr
    Potentials: VdW, Bond, Angle and colulombic potential

    """
    force = np.array([VdW_potential_gradient(position, i, sigma[atomtype[i]], epsilon[atomtype[i]], bonds) for i in range(no_of_atoms)]) # VdW potential
    force = force - BondPotentialGradient(position, bonds) # Bond potential
    force = force - AnglePotentialGradient(position, angles) # Angle potential
    force = np.array([columbic_force(position, i, atomic_charge) for i in range(no_of_atoms)]) # Columbic potential
    acceleration = np.transpose(np.transpose(force) / atomic_mass) # F = ma
    new_velocity = velocity + acceleration * dt # v = u + at
    return new_velocity, acceleration