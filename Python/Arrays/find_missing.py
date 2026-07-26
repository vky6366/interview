def find_missing(arr):
    n = len(arr) +1

    total = n * (n+1)//2

    actual_sum = sum(arr)
    
    result = total - actual_sum
    return result



if __name__ == "__main__":
    arr = [1, 2, 3, 5, 6, 7, 8, 9]
    print(find_missing(arr))
