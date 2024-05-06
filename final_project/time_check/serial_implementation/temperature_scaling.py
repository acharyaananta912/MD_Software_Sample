import numpy as np

def TempScale(temperature, velocity, atomic_mass, boltzmann_constant):

    """
    Scale the velocities based on the temperature.

    Parameters:
    - temperature (float): The desired temperature.
    - velocity (np.ndarray): The current velocities of the atoms.

    Returns:
    - np.ndarray: The scaled velocities.
    """
    no_of_atoms = velocity.shape[0]
    # Calculate the current temperature
    kinetic_energy = 0.5 * np.sum(atomic_mass*np.transpose(velocity**2))
    current_temperature = 2 * kinetic_energy / (3 * boltzmann_constant * no_of_atoms)
    temp_increase = (np.sqrt(temperature / current_temperature) - 1.0)*0.5 + 1.0

    # Scale the velocities
    scaled_velocity = temp_increase * velocity
   

    return scaled_velocity