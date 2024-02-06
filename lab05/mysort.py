def quicksort(A, low=0, high=None):
    if high is None:
        high = len(A) - 1
    if low < high:
        p = partition(A, low, high)
        quicksort(A, low, p - 1)
        quicksort(A, p+1, high)
    return A

def partition(A, low, high):
    pivot = A[high]
    i = low
    for j in range(low, high):
        if A[j] <= pivot:
            A[i], A[j] = A[j], A[i]
            i = i+1
    A[i], A[high] = A[high], A[i]
    return i

def filesort():
    from read_input_file import read_input_file
    data2sort = read_input_file()
    sorted_array = quicksort(data2sort)

    fid = open("sorted.data", "w")
    for value in sorted_array:
        fid.write("%12.6e"%value)
        fid.write("\n")
    fid.close()

if __name__ == "__main__":
    filesort()
