def generate_coordinates(position, time, outdir, molecule_number, atomtype, box_dimension):
    
    
    no_of_atoms = position.shape[0]
    fname = outdir + "/t" + str(time) + ".dump"
    f = open(fname, "w")
    f.write("ITEM: TIMESTEP\n")
    f.write(str(time)+"\n") #time step
    f.write("ITEM: NUMBER OF ATOMS\n")
    f.write(str(len(position))+"\n") # number of atoms
    f.write("ITEM: BOX BOUNDS pp pp pp\n") #pp = periodic BCs
    f.write("0 "+str(box_dimension[0])+"\n")
    f.write("0 "+str(box_dimension[1])+"\n")
    f.write("0 "+str(box_dimension[2])+"\n")
    f.write("ITEM: ATOMS id mol type x y z\n")
    for i in range(len(position)):
        f.write(str(i)+" "+str(molecule_number[i])+" "+str(atomtype[i])+" "+str(position[i][0])+" "+str(position[i][1])+" "+str(position[i][2])+"\n")
    f.close
