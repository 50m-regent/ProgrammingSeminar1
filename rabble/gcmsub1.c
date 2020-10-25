#include "gcm.h"

u_int gcm(u_int l, u_int s) {
    u_int r;

    if ((l == 0) || (s == 0)) return 0;
    l = ABS(l);
    s = ABS(s);

    while (s != 0) {
        r = l % s;
        l = s;
        s = r;
    }

    return l;
}