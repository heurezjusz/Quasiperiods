import random


def random_test(N):
    return ''.join(random.choice('ab') for _ in range(N))


def aaaaa(N):
    return 'a' * N


def presuf(s):
    n = len(s)
    s = '$' + s
    p = [0] * (n + 1)
    w = 0
    for i in xrange(2, n + 1):
        while w != 0 and s[i] != s[w + 1]:
            w = p[w]
        if s[i] == s[w + 1]:
            w += 1
        p[i] = w

    res = []
    w = n
    while w != 0:
        w = p[w]
        res.append(w)
    return res


def seed_test(N, seed):
    res = seed
    prefs = presuf(seed)
    while len(res) < N + 20:
        overlap = random.choice(prefs)
        res += seed[overlap:]
    return res[10:-10]


def short_aba(N):
    return seed_test(N, 100 * 'a' + 'b' + 100 * 'a')


def short_rec(N):
    return seed_test(N, rec(100))


def long_aba(N):
    return seed_test(N, (N // 10) * 'a' + 'b' + (N // 10) * 'a')


def long_rec(N):
    return seed_test(N, rec(N // 10))


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
    write_test('short_aba%s.in' % ID, short_aba(N))
    write_test('long_rec%s.in' % ID, long_rec(N))
    write_test('long_aba%s.in' % ID, long_aba(N))
    write_test('short_rec%s.in' % ID, short_rec(N))
