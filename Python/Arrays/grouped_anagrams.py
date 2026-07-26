def anagrams(arr):
    res = []
    mp = {}

    for i in range(len(arr)):
        s = arr[i]
        s = ''.join(sorted(s))

        if s not in mp:
            mp[s] = len(res)
            res.append([])

        res[mp[s]].append(arr[i])

    return res


if __name__ == "__main__":
    arr = ['eat', 'tea', 'tan', 'ate', 'nat', 'bat']
    print(anagrams(arr))