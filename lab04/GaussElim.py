import numpy as np
def LUfactor(A):
    '''
    This function uses gauss elimination method to find LU factorization of a matrix A
    Input: A - a square matrix
    Output: L - Lower triangular matrix
            U - Upper triangular matrix
            A = LU
    '''
    assert A.shape[0] == A.shape[1], "Matrix A must be a square matrix"
    # size of the matrix, n x n
    n = A.shape[0] 
    # Gaussian elimination involves dividing the elements of a row by the diagonal element.
    # Convert the matrix to float to avoid integer division
    U = (A.copy()).astype(float) 
    L = np.eye(n,n)

    for k in range(n-1):
        assert(U[k][k] != 0), "Pivot element is zero. LU factorization is not possible"
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

