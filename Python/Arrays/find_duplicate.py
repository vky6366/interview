def find_duplicate(arr):
    n = len(arr)

    seen = set()
    result = []

    for i in range(n):
        if arr[i] in seen:
            result.append(arr[i])
        else:
            seen.add(arr[i])
    
    return result

if __name__ == "__main__":
    arr = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6]
    print(find_duplicate(arr))