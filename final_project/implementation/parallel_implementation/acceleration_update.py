import numpy as np
from copy import deepcopy

from bond_angle_potential import BondAnglePotGradient
from bond_length_potential import BondPotentialGradient
from columbic_potential import columbic_force
from vanderwaals import VdW_potential_gradient


def update_cord_vel(position, velocity, dt, box_dimension):
    """
    Updates the position and velocity of the atoms
    """
    new_position = position + velocity * dt
    new_position = new_position % box_dimension
    new_velocity = deepcopy(velocity)
    return new_position, new_velocity

def calculate_acceleration(position, velocity, dt, sigma, epsilon, atomtype, bonds, molecule_number, angles, atomic_mass, atomic_charge):
    """
    Calculates acceleration of the atoms based on the forces
    Forces are calculated based on the potential energy F = -dV/dr
    Potentials: VdW, Bond, Angle and colulombic potential

    """

    force = np.array([VdW_potential_gradient(position, i, sigma[atomtype[i]], epsilon[atomtype[i]], atomtype, molecule_number) for i in range(len(position))])
    force = force - BondPotentialGradient(position, bonds) # Bond potential
    force = force - BondAnglePotGradient(position, angles) # Bond angle potential
    force = force - np.array([columbic_force(position, i, atomic_charge, molecule_number) for i in range(len(position))]) # Columbic potential
    acceleration = np.transpose(np.transpose(force) / atomic_mass) # F = ma
    new_velocity = velocity + acceleration * dt # v = u + at
    return new_velocity, acceleration