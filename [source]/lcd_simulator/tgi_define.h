#ifndef __TGI_DEFINE__
#define __TGI_DEFINE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef struct tagT_RECT {
	uint16_t left;
	uint16_t top;
	uint16_t right;
	uint16_t bottom;
} T_RECT,*T_LPRECT;

typedef struct tagT_POINT {
	uint16_t x;
	uint16_t y;
} T_POINT,*T_LPPOINT;

typedef struct tagT_SIZE {
	uint16_t cx;
	uint16_t cy;
} T_SIZE,*T_LPSIZE;

inline int ROUND(double x) { return (int)(x+0.5); };
inline int ABS(int x) { return x>0 ? x:-x; };
// inline int MAX(int x, int y) { return x>y ? x:y; };
#define MAX(x, y) ((x)>(y)? (x):(y))

#define POWER(X) ((x)*(x))
#endif