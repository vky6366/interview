def binary_search(arr, left, right, target):
    while left<=right:
        mid = (left+right)//2
        if arr[mid] == target:
            return True
        elif arr[mid] < target:
            left = mid+1
        else:
            right = mid-1
        
    return False

def two_sum(arr, target):
    arr.sort()

    for i in range(len(arr)):
        complement = target - arr[i]
        if binary_search(arr, i+1, len(arr), complement):
            return True
    return False    


if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    target = 10
    print(two_sum(arr, target))