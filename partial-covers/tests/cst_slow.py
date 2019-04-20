#!/usr/bin/python

S = raw_input()
N = len(S)


def is_suffix(i, j):
    return j == N


def is_primitive_square(i, j):
    d = j - i
    if len(S) < j + d:
        return False
    if S[i:j] != S[j:j + d]:
        return False

    # is primitive
    for x in range(1, d):
        if d % x == 0 and S[i:i + d] * (d / x) == S[i:j]:
            return False

    return True


def is_explicit_node(i, j):
    # assume that i is first occurence
    lsub = set()
    for x in range(N - j):
        if S[i + x:j + x] == S[i:j]:
            lsub.add(S[i + x:j + x + 1])
    return len(lsub) > 1


def print_all_nodes_of_len(h):
    print "==", h, "=="
    subwords = set()
    checked = set()
    for i in range(N - h + 1):
        if S[i:i + h] not in checked:
            checked.add(S[i:i + h])
            if is_suffix(i, i + h):
                subwords.add(S[i:i + h] + "$")
            if is_explicit_node(i, i + h):
                subwords.add(S[i:i + h])
        if is_primitive_square(i, i + h):
            subwords.add(S[i:i + h])

    for s in subwords:
        print(s)


for i in range(N):
    print_all_nodes_of_len(i + 1)
