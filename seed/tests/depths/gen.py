import os
import string
import random
random.seed(42)

def random_word(n):
    return ''.join(random.choice(string.lowercase) for x in xrange(n))

def cycle_word(c, cn):
    return random_word(c) * cn

for word, fname in [
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
 ]:
    with open(fname, 'w') as f:
        f.write(word + '\n')
