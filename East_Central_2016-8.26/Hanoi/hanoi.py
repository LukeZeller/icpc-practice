while(True):
    t = []
    try:
        for i in range(3):
            t.append(input().split()[1:])
    except EOFError:
        break
    N = len(t[0]) + len(t[1]) + len(t[2])
    pos = [-1 for i in range(N)]
    for i in range(3):
        for k in t[i]:
            pos[int(k) - 1] = i
    S, I, F = 0, 1, 2
    steps = 0
    invalid = False
    #print(pos)
    for i in reversed(range(N)):
        #print(str(S) + " " + str(I) + " " + str(F))
        if pos[i] == I:
            invalid = True
            break
        if pos[i] == S:
            steps += 2**i
            tmp = F
            F = I
            I = tmp
        else:
            tmp = S
            S = I
            I = tmp
    if invalid:
        print("No")
    else:
        print(steps)
