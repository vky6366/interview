def are_anagrams(arr1, arr2):
    if sorted(arr1) == sorted(arr2):
        return True
    return False
    
if __name__ == "__main__":
    s1 = "listen1"
    s2 = "silent"
    print(are_anagrams(s1, s2))