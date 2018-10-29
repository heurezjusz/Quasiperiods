import os
import string
import random
random.seed(42)


def random_word(n):
    return ''.join(random.choice(string.lowercase) for x in xrange(n))


def cycle_word(c, cn):
    return random_word(c) * cn


def debug(n):
    return ''.join(random.choice('abcde') for x in xrange(n))


def many_seeds(n):
    return 'a' * n + 'b' + 'a' * n + 'b' + 'a' * n


def recursive(n):
    if n <= 0:
        return 'a'
    return recursive(n - 1) + chr(ord('a') + n) + recursive(n - 1)


for word, fname, n in [
    ('abc', 'hand1.in', 2),
    ('wololo', 'hand2.in', 1),
    ('abcabxabcd', 'hand3.in', 2),
    ('xabxac', 'hand4.in', 1),
    ('aaaaaaaaaabcaaaaaabaa', 'hand5.in', 3),
    ('baeebcaebc', 'special1.in', 1),
    ('eccdeaaccc', 'special2.in', 1),
    ('adcbddadda', 'special3.in', 2),
    (cycle_word(1, 20), 'cycle1.in', 10),
    (cycle_word(1, 200), 'cycle2.in', 27),
    (cycle_word(7, 101), 'cycle3.in', 8),
    (cycle_word(23, 10), 'cycle4.in', 6),
    (cycle_word(3, 25), 'cycle5.in', 8),
    (random_word(5), 'random1.in', 1),
    (random_word(24), 'random2.in', 1),
    (random_word(256), 'random3.in', 2),
    (random_word(13) + cycle_word(1, 10), 'mix1.in', 3),
    (random_word(130) + cycle_word(13, 5), 'mix2.in', 6),
    (cycle_word(1, 13) + random_word(13), 'mix3.in', 3),
    (cycle_word(33, 10) + random_word(130), 'mix4.in', 18),
    (cycle_word(4, 100) + random_word(299), 'mix5.in', 2),
    (many_seeds(2), 'ababa2.in', 2),
    (many_seeds(5), 'ababa5.in', 3),
    (many_seeds(20), 'ababa20.in', 5),
    (many_seeds(100), 'ababa100.in', 21),
    (recursive(1), 'rec1.in', 1),
    (recursive(2), 'rec2.in', 2),
    (recursive(3), 'rec3.in', 3),
    (recursive(4), 'rec4.in', 4),
    (recursive(5), 'rec5.in', 5),
    (debug(500), 'debug1.in', 100),
]:
    with open(fname, 'w') as f:
        f.write("%s %d\n" % (word, n))
