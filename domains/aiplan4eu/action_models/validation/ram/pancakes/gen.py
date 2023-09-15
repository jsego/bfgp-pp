import random

def flip(arr, k):
    left = 0
    while left < k:
        arr[left], arr[k] = arr[k], arr[left]
        k -= 1
        left += 1

def max_index(arr, k):
    index = 0
    for i in range(k):
        if arr[i] > arr[index]:
            index = i
    return index

def pancake_sort(arr):
    n = len(arr)
    f_id = 1
    while n > 1:
        maxdex = max_index(arr, n)
        s = arr.copy()
        flip(arr, maxdex) # FLIP MAX
        s_prime = arr.copy()
        print_file(f_id, s, maxdex, s_prime, maxdex)
        f_id = f_id + 1
        s = arr.copy()
        flip(arr, n - 1) # FLIP ALL
        s_prime = arr.copy()
        print_file(f_id, s, n-1, s_prime, n-1)
        f_id = f_id + 1
        n -= 1

def print_file(file_id, s, ks, s_prime, ks_prime):
	outstr = f"[INSTANCE]: flip_{file_id}\n[DOMAIN]: pancake_sorting\n\n[OBJECTS]:"

	for i in range(len(s)):
		outstr += f"\np{i}:object"
	
	outstr += "\n\n[INIT]:"
	outstr += f"\n(action_flip(p{ks})=1)"
	for idx, v in enumerate(s):
		outstr += f"\n(vector(p{idx})={v})"
	
	outstr += "\n\n[GOAL]:"
	for idx, v in enumerate(s_prime):
		outstr += f"\n(vector(p{idx})={v})"
	outstr += "\n"
	
	with open(f"{file_id}.txt", "w") as f:
		f.write(outstr)
	

if __name__ == "__main__":
	#arreglo = [15, 8, 9, 1, 78, 30, 69, 4, 10]
	random.seed(1)
	arreglo = random.sample(range(1,100),50)
	pancake_sort(arreglo)
	print(arreglo)
