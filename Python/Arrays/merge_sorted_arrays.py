def merge_sorted_arrays(arr1, arr2):
    n = len(arr1)
    m = len(arr2)

    merged = [0] * (n + m)

    for i in range(n):
        merged[i] = arr1[i]

    for j in range(m):
        merged[n+j] = arr2[j]

    merged.sort()

    for i in range(n):
        arr1[i] = merged[i]
    
    for j in range(m):
        arr2[j] = merged[n+j]

    return merged   

if __name__ == "__main__":
    arr1 = [1, 2, 3, 0, 0, 0]
    arr2 = [2, 5, 6]
    print(merge_sorted_arrays(arr1, arr2))
    print("after merge")
    print(arr1)
    print(arr2)