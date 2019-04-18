#include "hull.h"
#include <cstdio>
using namespace std;


Segment::Segment(int x1, int x2, int y1, int dx)
    : x1(x1), x2(x2), y1(y1), dx(dx) {}


int Segment::at(int x) const {
    return (x - x1) * dx + y1;
}


vector<Segment> hull;
int N, QEND;
int qi;


void qpush(Segment const& s, int x1, int x2) {
    if (qi != QEND && hull[qi].dx == s.dx && s.y1 == hull[qi].at(s.x1)) {
        hull[qi].x2 = x2;
        return;
    }

    qi--;
    hull[qi].x1 = x1;
    hull[qi].x2 = x2;
    hull[qi].y1 = s.at(x1);
    hull[qi].dx = s.dx;
}


int qfinish(int shift) {
    int size = QEND - qi;
    for (int i = 0; i < size; ++i)
        hull[shift + i] = hull[QEND - 1 - i];
    qi = QEND;
    return size;
}


inline int put_single(Segment const& seg, int shift) {
    int size = 0;

    if (seg.x1 > 1) {
        hull[shift] = Segment(1, seg.x1 - 1);
        size++;
    }

    hull[shift + size] = seg;
    size++;

    if (seg.x2 < N) {
        hull[shift + size] = Segment(seg.x2 + 1, N, seg.at(seg.x2));
        size++;
    }

    return size;
}


void print(int shift, int n) {
    for (int i = 0; i < n; ++i)
        printf("[%d %d - %d %d]", hull[i + shift].x1, hull[i + shift].y1,
               hull[i + shift].x2, hull[i + shift].at(hull[i + shift].x2));
    puts("");
}


#define seg_i1 hull[shift + i1]
#define seg_i2 hull[shift + i2 + n1]
int merge(int shift, int n1, int n2) {
    int i1 = 0, i2 = 0, x = 1, xend;

    // printf("MERGE %d %d %d\n>", shift, n1, n2);
    // print(shift, n1);
    // printf(">");
    // print(shift + n1, n2);

    while (i1 < n1 && i2 < n2) {
        xend = min(seg_i1.x2, seg_i2.x2);

        // printf("| x=%d i1=%d i2=%d\n", x, i1, i2);

        if (seg_i1.at(x) >= seg_i2.at(x)) {
            // printf("| 1 bigger ");
            if (seg_i1.at(xend) < seg_i2.at(xend)) {
                // printf("*");
                // printf("{%d-%d / %d-%d} ", seg_i1.at(0), seg_i2.at(0),
                //        seg_i2.dx, seg_i1.dx);
                xend =
                    ((seg_i1.at(0) - seg_i2.at(0)) / (seg_i2.dx - seg_i1.dx));
            }
            // printf("until %d\n", xend);
            qpush(seg_i1, x, xend);

        } else {
            // printf("| 2 bigger ");
            if (seg_i1.at(xend) > seg_i2.at(xend)) {
                // printf("*");
                xend =
                    ((seg_i1.at(0) - seg_i2.at(0)) / (seg_i2.dx - seg_i1.dx));
            }
            // printf("until %d\n", xend);

            qpush(seg_i2, x, xend);
        }

        // printf("|? ");
        // print(shift + i1, 1);
        // printf("|? ");
        // print(shift + n1 + i2, 1);

        // move forward
        x = xend + 1;
        if (seg_i1.x2 < x)
            i1++;
        if (seg_i2.x2 < x)
            i2++;
        // printf("|(fwd) x=%d i1=%d i2=%d\n", x, i1, i2);
    }

    // push rest & finish
    /*while (i1 < n1) {
        qpush(seg_i1, x, seg_i1.x2);
        x = seg_i1.x2 + 1;
        i1++;
    }
    while (i2 < n2) {
        qpush(seg_i2, x, seg_i2.x2);
        x = seg_i2.x2 + 1;
        i2++;
    }*/

    int size = qfinish(shift);
    // printf(">>> ");
    // print(shift, size);
    return size;
}


int create_hull(vector<Segment> const& seg, int from, int to, int shift) {
    if (from == to) {
        // printf("s%d\n", from);
        return put_single(seg[from], shift);
    }
    int avg = (from + to) / 2;
    int n1 = create_hull(seg, from, avg, shift);
    int n2 = create_hull(seg, avg + 1, to, shift + n1);

    // printf("[%d |%d| %d]\n", from, avg, to);

    return merge(shift, n1, n2);
}


void get_hull(int _N, vector<Segment> const& segments, vector<int>& result) {
    N = _N;
    result.resize(N + 1);
    hull.resize(max(2 * N, 16));
    QEND = qi = hull.size();

    int M = create_hull(segments, 0, segments.size() - 1, 0);
    for (int i = 0; i < M; ++i) {
        for (int pos = hull[i].x1; pos <= hull[i].x2; ++pos)
            result[pos] = hull[i].at(pos);
    }
}
