from typing import Counter
def top_k(arr, k):
    n = len(arr)

    mp = Counter(arr)
    print(mp)
    print("\n")

    lst = list(mp.items())
    print(lst)
    print("\n")

    lst.sort(key = lambda x:(x[1],x[0]), reverse = True)
    print(lst)
    print("\n")

    res = []

    for i in range(k):
        res.append(lst[i][0])
    
    return res
    
if __name__ == "__main__":
    arr = [3, 1, 4, 4, 5, 2, 6, 1]
    k = 2
    print(top_k(arr, k))