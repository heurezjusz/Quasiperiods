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


for word, fname in [
    ('ababaabaab', 'example.in'),
    ('abc', 'hand1.in'),
    ('wololo', 'hand2.in'),
    ('abcabxabcd', 'hand3.in'),
    ('xabxac', 'hand4.in'),
    ('baeebcaebc', 'special1.in'),
    ('eccdeaaccc', 'special2.in'),
    ('adcbddadda', 'special3.in'),
    (cycle_word(1, 20), 'cycle1.in'),
    (cycle_word(1, 200), 'cycle2.in'),
    (cycle_word(7, 101), 'cycle3.in'),
    (cycle_word(23, 10), 'cycle4.in'),
    (cycle_word(3, 25), 'cycle5.in'),
    (random_word(5), 'random1.in'),
    (random_word(24), 'random2.in'),
    (random_word(256), 'random3.in'),
    (random_word(13) + cycle_word(1, 10), 'mix1.in'),
    (random_word(130) + cycle_word(13, 5), 'mix2.in'),
    (cycle_word(1, 13) + random_word(13), 'mix3.in'),
    (cycle_word(33, 10) + random_word(130), 'mix4.in'),
    (cycle_word(4, 100) + random_word(299), 'mix5.in'),
    (many_seeds(2), 'ababa2.in'),
    (many_seeds(5), 'ababa5.in'),
    (many_seeds(20), 'ababa20.in'),
    (many_seeds(100), 'ababa100.in'),
    (recursive(1), 'rec1.in'),
    (recursive(2), 'rec2.in'),
    (recursive(3), 'rec3.in'),
    (recursive(4), 'rec4.in'),
    (recursive(5), 'rec5.in'),
    (debug(500), 'debug1.in'),
]:
    with open(fname, 'w') as f:
        f.write(word + '\n')
