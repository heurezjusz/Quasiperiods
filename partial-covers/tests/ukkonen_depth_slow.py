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

    for s in subwords:
        print(s)


for i in range(N):
    print_all_nodes_of_len(i + 1)
