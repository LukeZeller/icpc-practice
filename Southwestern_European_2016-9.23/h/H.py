D, H = input().split()
D, H = int(D), int(H)

part_map = dict()

def parts(N):
    if N == 0:
        yield []
    else:
        for part in parts(N - 1):
            yield [1] + part
            if part and (len(part) == 1 or part[1] > part[0]):
                yield [part[0] + 1] + part[1:]
        

def resort(part, ind):
    itr = ind
    while itr < D - 1 and part[itr + 1] > part[ind]:
        itr += 1
    part[itr], part[ind] = part[ind], part[itr]
    return part

def calc_val(part):
    global part_map

    if max(part) == 0:
        return 1

    t_part = tuple(part)
    if t_part in part_map:
        return part_map[t_part]

    ans = 0
    for i in range(D):
        if part[i] > 0:
            part_cpy = part[:]
            part_cpy[i] -= 1
            resort(part_cpy, i)
            ans += calc_val(part_cpy)
    part_map[t_part] = ans
    return ans

ans_list = set()

for part in parts(H - 1):
    if len(part) > D:
        continue
    part_transform = list(reversed(part)) + [0 for i in range(D - len(part))]
    ans = calc_val(part_transform)
    ans_list.add(ans)

sorted_ans_list = sorted(list(ans_list))
for val in sorted_ans_list:
    print(val)
