import random


def random_test(N):
    return ''.join(random.choice('ab') for _ in range(N))


def aaaaa(N):
    return 'a' * N


def rec(N):
    res = 'a'
    i = 1
    while len(res) < N:
        res = res + chr(i + 97) + res
        i += 1
    return res


def write_test(fname, test):
    print 'writing %s...' % fname
    with open(fname, 'w') as f:
        f.write(test + '\n')


random.seed(42)

IDs = ['1e4', '3e4', '1e5', '3e5', '1e6']
Ns = [int(float(x)) for x in IDs]

for ID, N in zip(IDs, Ns):
    write_test('random%s.in' % ID, random_test(N))
    write_test('aaaaa%s.in' % ID, aaaaa(N))
    write_test('rec%s.in' % ID, rec(N))
