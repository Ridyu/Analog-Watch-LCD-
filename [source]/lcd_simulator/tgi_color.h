#ifndef _TINY_GRAPHIC_PALETTE_
#define _TINY_GRAPHIC_PALETTE_

typedef struct tagT_RGB {
	uint8_t R;
	uint8_t G;
	uint8_t B;	
} T_RGB,*LPT_RGB;

const T_RGB black			=  {0,   0  , 0};
const T_RGB white			=  {255, 255, 255};
const T_RGB red			=  {0,  0,   255};
const T_RGB green			=  {0,  255,   0};
const T_RGB blue			=  {255,   0,  0};
const T_RGB yellow			=  {255, 255,  0};

typedef unsigned long TCOLORREF;

#define TRGB(r,g,b)          ((TCOLORREF)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))
#define GetR(rgb)   ((unsigned char) (rgb))
#define GetG(rgb)   ((unsigned char) (((unsigned short) (rgb)) >> 8))
#define GetB(rgb)   ((unsigned char) ((rgb) >> 16))

#endif //_PALETTE_