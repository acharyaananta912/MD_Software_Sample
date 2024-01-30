def sqrt_newton(x,s=1.0,kmax=10,printshow=False):

    for k in range(kmax):
        if printshow:
            print("Before iteration %s, s = %20.15f" % (k,s))
        s = 0.5*(s + x/s);
    return s

def sqrt_secant(x, s=1, t=1, kmax=10, printshow=False):

    for k in range(kmax):
        if printshow:
            print("Before iteration %s, s=%20.15f" % (k,s))
        s = (x + s*t)/(s + t)
    return s

if __name__ == "__main__":
    
    print("Using Newton Square Root Method:")
    s = sqrt_newton(15,4,10,True);

    print("Using Secant Square Root Method:")

    s = sqrt_secant(15,3,4,10,True)
