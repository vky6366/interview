def is_duplicate(arr):
    n = len(arr)

    seen = set()

    idx = 0

    for i in range(n):
        if arr[i] not in seen:
            seen.add(arr[i])
            arr[idx] = arr[i]
            idx += 1

    
    return idx


if __name__ == "__main__":
    arr = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6]
    n = is_duplicate(arr)
    print(n)
    for i in range(n):
        print(arr[i], end=" ")
