import numpy as np
def getdata(infile):

    # Open the file
    
    data = np.loadtxt(infile)
    x = data[:,0]
    y = data[:,1]

    # Return the data
    return x, y
    
def approx(x, y):
    # Calculate the coefficients of the quadratic function
    assert len(x) == len(y) 
    A = np.vstack([np.ones(len(x)), x, x**2]).T
    ATA = np.dot(A.T, A)
    ATy = np.dot(A.T, y)
    a = np.linalg.solve(ATA, ATy)
    return a
    
def plot(x=0, y=0, a=0, infile=""):

    x, y = getdata(infile)
    a = approx(x, y)
    import matplotlib.pyplot as plt
    # Plot the data
    plt.plot(x, y, 'o')
    # Plot the quadratic function
    yfit = a[0] + a[1]*x + a[2]*x**2

    plt.figure(figsize=(8, 6))
    plt.plot(x, y, 'o', label='Data', color='blue', markersize=8, alpha=0.7)

    # Plot the quadratic function
    plt.plot(x, yfit, '-', label='Quadratic Fit', color='red', linewidth=2)

    # Customize plot
    plt.title(infile[:-4] + ": Data and Least Squares Fit w/Quad. Poly.", fontsize=16)
    plt.xlabel("X", fontsize=14)
    plt.ylabel("Y", fontsize=14)
    plt.legend(loc='upper left', fontsize=12)
    plt.savefig(infile[:-4] + ".png", bbox_inches='tight')
    plt.close()

if  __name__ == "__main__":
    
    plot(infile="xydata1.dat")
    plot(infile="xydata2.dat")
    plot(infile="xydata3.dat")
    plot(infile="xydata4.dat")