import queue

while True:
    try:
        N = int(input())
    except EOFError:
        break
    names = input().split(' ')

    line = queue.Queue()

    #White @ 0, Black @ 1

    O = [names[0], names[1]]
    D = [names[2], names[3]]

    # 0 if offense arrived first, 1 if defense arrived first
    order = [0, 0]

    for i in range(4, N):
        line.put(names[i])

    points = input()
    points = points[0] + points
    points += 'W' if points[-1] == 'B' else 'B'
    length = len(points)

    maxDyn = 1
    currLen = 0
    dyns = []

    for i in range(1, length):
        #print(O)
        #print(D)
        #print(currLen)
        ind = 0 if points[i] == 'W' else 1
        p_ind = 0 if points[i - 1] == 'W' else 1
        #print(ind)
        #print(order)
        if (ind == p_ind):
            currLen += 1
        else:
            if currLen == maxDyn:
                if order[1 - ind] == 0:
                    dyns += [[O[1 - ind], D[1 - ind]]]
                else:
                    dyns += [[D[1 - ind], O[1 - ind]]]
            elif currLen > maxDyn:
                maxDyn = currLen
                if order[1 - ind] == 0:
                    dyns = [[O[1 - ind], D[1 - ind]]]
                else:
                    dyns = [[D[1 - ind], O[1 - ind]]]
            currLen = 1
        line.put(D[1 - ind])
        D[1 - ind] = O[1 - ind]
        O[1 - ind] = line.get()
        order[1 - ind] = 1
        tmp = O[ind]
        O[ind] = D[ind]
        D[ind] = tmp
        order[ind] = 1 - order[ind]

    #print(dyns)

    for dyn in dyns:
        print(dyn[0] + " " + dyn[1])
