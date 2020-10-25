#if !defined(GCM_H)
#define GCM_H

typedef unsigned int u_int;

#define ABS(a) ((a) < 0 ? -(a) : (a))

u_int gcm(u_int, u_int);
#endif