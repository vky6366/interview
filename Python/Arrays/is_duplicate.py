def is_duplicate(arr):
    n = len(arr)

    seen = set()

    for i in range(n):
        if arr[i] in seen:
            return True
        seen.add(arr[i])
    
    return False

if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1]
    print(is_duplicate(arr))