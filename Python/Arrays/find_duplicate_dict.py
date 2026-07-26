def find_duplicate(arr):
    n = len(arr)

    count = {}
    seen = {}

    for num in arr:
        count[num] = count.get(num,0)+1
    
    for key, value in count.items():
        if value > 1:
            seen[key] = value
    
    return seen

if __name__ == "__main__":
    arr = [1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4, 5, 6, 6, 6, 6]
    print(find_duplicate(arr))
