def array_product(arr):
    n = len(arr)
    total_product = 1
    for i in range(n):
        total_product*= arr[i]

    result = []
    for i in range(n):
        result.append(total_product/arr[i])
    
    return result


if __name__ == "__main__":
    arr = [10, 3, 5, 6, 2]
    print(array_product(arr))


