import numpy as np
def LUfactor(A):
    
    n = A.shape[0]
    U = A.copy()
    L = np.eye(n,n)

    for k in range(n-1):
        for j in range(k+1, n):
            L[j][k] = U[j][k]/U[k][k]
            for i in range(k,n):
                U[j][i] = U[j][i] - L[j][k]*U[k][i]
    return L,U

def determinant(A):
    L, U = LUfactor(A)
    n = L.shape[0]
    det_L = 1
    det_U = 1
    for i in range(n):
        det_L *= L[i][i]
        det_U *= U[i][i]
    return det_L * det_U

if __name__ == "__main__":

    A1 = np.array([[5,-1,2],
             [10,3,7],
             [15,17,19]])
    A2 = np.array([[4, 1, 0, 0],[1, 4, 1, 0],[0, 1, 4, 1],[0, 0, 1, 4]])
    A3 = np.array([[1,-2,-2,-3], [3,-9,0,-9], [-1,2,4,7], [-3,-6,26,2]])

    for A in [A1,A2,A3]:
        L,U = LUfactor(A)
        print("\nThe matrix A is: ",A)
        print("\nThe L is: ",L)
        print("\nU is: ",U)
        print("\nDeterminant is: ",determinant(A))
        print("\n")

