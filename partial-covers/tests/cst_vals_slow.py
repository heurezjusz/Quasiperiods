#!/usr/bin/python

S = raw_input()
N = len(S)
S += "$"


def is_suffix(i, j):
    return j == N


def is_explicit_node(i, j):
    lsub = set()
    d = j - i
    for x in range(N - d + 1):
        if S[x:x + d] == S[i:j]:
            lsub.add(S[x:x + d + 1])
    return len(lsub) > 1


def is_primitive_for_square(i, j):
    d = j - i
    if j + d > N:
        return False

    s = S[i:j]
    for n in range(1, d):
        if d % n == 0 and s[:n] * (d // n) == s:
            return False

    return 2 * s == S[i:j + d]


def print_cv_D(s):
    if s.endswith('$'):
        print len(s) - 1, 1,
        return

    covered, D = 0, 0
    last_pos = -N
    d = len(s)
    for i in range(N - d + 1):
        if S[i:i + d] == s:
            if i - last_pos >= d:
                D += 1

            covered += min(d, i - last_pos)
            last_pos = i

    print covered, D,


def print_all_nodes_of_len(h):
    print "==", h, "=="
    subwords = set()
    checked = set()
    for i in range(N - h, -1, -1):
        if S[i:i + h] not in checked:
            checked.add(S[i:i + h])
            if is_suffix(i, i + h):
                subwords.add(S[i:i + h + 1])
            if is_explicit_node(i, i + h):
                subwords.add(S[i:i + h])

        if is_primitive_for_square(i, i + h):
            subwords.add(S[i:i + h])

    for s in subwords:
        print_cv_D(s)
        print(s)


for i in range(N):
    print_all_nodes_of_len(i + 1)
print "== END =="
