#include <cstdio>
#include "maxgap.h"

int main() {
    MaxGap mg, _mg;
    mg.init(8, -1, 0);
    _mg.init(8, -1, 3);
    mg.join(_mg);
    printf("%d correct: 3\n", mg.max_gap());

    _mg.init(8, -1, 7);
    mg.join(_mg);
    printf("%d correct: 4\n", mg.max_gap());

    _mg.init(8, -1, 5);
    mg.join(_mg);
    printf("%d correct: 3\n", mg.max_gap());
    
    _mg.init(8, -1, 1);
    mg.join(_mg);
    printf("%d correct: 2\n", mg.max_gap());
}
