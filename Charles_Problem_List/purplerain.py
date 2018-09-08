def max_subarray(color):
    currPref = 0
    minPrefix = 0
    minPrefixIndex = 1
    toReturn = [0,0,0]
    for i in range(1, len(color)):
        currPref += color[i]
        if (currPref < minPrefix):
            minPrefix = currPref
            minPrefixIndex = i+1
        currDiff = currPref - minPrefix;
        if currDiff > toReturn[0]:
            toReturn[0] = currDiff
            toReturn[1] = minPrefixIndex
            toReturn[2] = i
    return toReturn

l = input()
arr1 = ['a']
arr2 = ['a']
for i in range(0, len(l)):
    if l[i] == 'B':
        arr1.append(1)
        arr2.append(-1)
    else:
        arr1.append(-1)
        arr2.append(1)

a = max_subarray(arr1)
b = max_subarray(arr2)

if (b[0] > a[0]):
    print("%d %d" % (b[1], b[2]))
elif (b[0] == a[0] and b[1] < a[1]):
    print("%d %d" % (b[1], b[2]))
elif (b[0] == a[0] and b[1] == a[1] and b[2] < a[2]):
    print("%d %d" % (b[1], b[2]))
else:
    print("%d %d" % (a[1], a[2]))