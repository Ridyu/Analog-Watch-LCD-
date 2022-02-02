#include "tgi.h"
#include <stdlib.h>
#include <math.h>
#include<time.h>
uint8_t * g_offscreen = NULL;
T_RGB	g_color = {0};
uint8_t g_fontsize = 0;


long tgi_open(uint8_t * psurface, uint8_t width, uint8_t height, uint8_t bpp)
{			
	g_offscreen = psurface;	
	g_fontsize = FONT_SMALL_SIZE;
	T_RGB color = black;
	tgi_set_color(&black);
			
	return 0;
}

void tgi_close()
{

}
void tgi_digital()
{
	time_t now;
	struct tm timer;
	char ary[256];

	time(&now);
	localtime_s(&timer, &now);

	strftime(ary, sizeof(ary), "%A [%p] %I: %M: %S", &timer);
	tgi_set_text(30, 210, ary);
}


void tgi_set_color(uint8_t B, uint8_t G, uint8_t R)
{
	g_color.R = R;
	g_color.G = G;
	g_color.B = B;
}


void tgi_set_color(const T_RGB * rgb)
{
	g_color = *rgb;
}


long tgi_set_pixel(int x,int y)
{
	if(x < 0 || x > SCREEN_WIDTH) return 1;
	if(y < 0 || y > SCREEN_HEIGHT) return 1;
	
	set_surface(y,x);
	
	return 0;
}

void tgi_fill_all()
{	
	int i, j;
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			tgi_set_pixel(i, j);
		}
	}
}
void tgi_draw_vertical_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	int i;
	int length = ABS(y2 - y1);
	if (y2 > y1)
	{
		for (i = 0; i < length; i++)
		{
			tgi_set_pixel(x1, y1 + i);
		}
	}
	else 
	{
		for (i = 0; i < length; i++)
		{
			tgi_set_pixel(x1, y2 + i);
		}
	}
}
void tgi_draw_horizontal_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	int i;
	int length = ABS(x2 - x1);
	if (x2 > x1)
	{
		for (i = 0; i < length; i++)
		{
			tgi_set_pixel(x1 +i, y1);
		}
	}
	else
	{
		for (i = 0; i < length; i++)
		{
			tgi_set_pixel(x2 + i, y1);
		}
	}
}

long tgi_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	float y, m;
	int x,s,l;
	int dx, dy;
	int sy, ly;

	dx = x2 - x1;
	dy = y2 - y1;

	if (x2 > x1)
	{
		l = x2;
		s = x1;
		sy = y1;
		ly = y2;
	}
	else
	{
		l = x1;
		s = x2;
		sy = y2;
		ly = y1;
	}

	if (dx == 0)
		tgi_draw_vertical_line(s, sy, l, ly);
	else if (dy == 0)
		tgi_draw_horizontal_line(s, sy, l, ly);
	else {
		m = dy / (double)dx;
		for (x = s; x <= l; x++)
		{
			y = m*(x - s) + sy;
			tgi_set_pixel(x, ROUND(y));
		}
	}
	

	return 0;
}

void tgi_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{

	tgi_draw_line(x1,y1,x2,y2);
	tgi_draw_line(x3, y3, x2, y2);
	tgi_draw_line(x3, y3, x1, y1);
}
void tgi_draw_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	int x, y;
	for (x = x1; x <= x2; x++) {
		for (y = y1; y <= y2; y++) {
			if (x == x1 || x == x2) {
				tgi_set_pixel(x, y);
			}
			else {
				if (y == y1 || y == y2) {
					tgi_set_pixel(x, y);
				}
			}
		}
	}
}

void tgi_draw_circle(uint8_t x, uint8_t y, uint8_t r)
{
	int i, j;
	for (i = -r; i <= r; i++)
	{
		for (j = -r; j <= r; j++)
		{
			if (j*j + i*i == r*r) //if(j*j+i*i <= r*r) //if(j*j+i*i >= r*r)
				tgi_set_pixel(x + i, y + j);
		}
	}
}
void tgi_draw_circle2(int x0, int y0, int radius) 
{
	int x = 0;
	int y = radius;
	int dp = 1 - radius;
	do {
		if (dp < 0)
			dp = dp + 2 * (++x) + 3;
		else
			dp = dp + 2 * (++x) - 2 * (--y) + 5;

		tgi_set_pixel(x0 + x, y0 + y);
		tgi_set_pixel(x0 - x, y0 + y);
		tgi_set_pixel(x0 + x, y0 - y);
		tgi_set_pixel(x0 - x, y0 - y);
		tgi_set_pixel(x0 + y, y0 + x);
		tgi_set_pixel(x0 - y, y0 + x);
		tgi_set_pixel(x0 + y, y0 - x);
		tgi_set_pixel(x0 - y, y0 - x);
	} while (x < y);
}

void tgi_fill_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	int i, j;
	for (i = x1; i < x2; i++)
	{
		for (j = y1; j < y2; j++)
		{
			tgi_set_pixel(i, j);
		}
	}
}


//for font
long tgi_put_char(uint8_t x, uint8_t y, char c)
{
	if(g_fontsize == FONT_SMALL_SIZE)
		return tgi_put_char0(x,y,c);
		
	return 1;
}

long tgi_put_char0(uint8_t x, uint8_t y, char c)
{
	if(c < 0x20) return 1;	

	int cwidth = Font14x16_Width[c - 0x20];
	int cStart = HEIGHT_14x16 * (c - 0x20);

	if(x < 0 || x > SCREEN_WIDTH - cwidth) return 1;
	if(y < 0 || y > SCREEN_HEIGHT- HEIGHT_14x16) return 1;
	
	unsigned short line;
	int i, j;

	for(j=0; j<16; j++)
	{
		unsigned short indi = 0x8000;
		line = Font14x16_Bits[cStart + j];
		
		for(i=0; i<cwidth; i++)
		{
			if(line & indi) tgi_set_pixel(x+i, y+j);
			indi = indi >> 1;
		}
	}
	return 0;
}


void tgi_set_text(int x, int y, char *string)
{
	T_RECT r;

	r.left=x; 
	r.top=y; 
	r.right=SCREEN_WIDTH; 
	r.bottom= SCREEN_HEIGHT;	

	tgi_set_text0(r, string, 0);

}

void tgi_set_text0(T_RECT rect, char *string, int offset) //TEXT_ALIGN_LEFT
{
	int sx, ex; // start x, end x
	int sy;

	sx = rect.left + offset; 
	ex = rect.right - offset; 
	sy = rect.top + offset;
	
	int strLen = strlen(string);
	int cwidth = 0;

	
	int x = sx; int y = sy;
	char c;
	int i;
	for(i=0; i<strLen; i++)
	{
		c = string[i];
		switch(g_fontsize)
		{
		case FONT_SMALL_SIZE:
			cwidth = Font14x16_Width[c - 0x20] + 1;
			break;
		
		default:
			cwidth = Font14x16_Width[c - 0x20] + 1;
			break;
		}

		if(x+cwidth > ex) break;

		tgi_put_char(x, y, c);
		x += cwidth;
	}
}

void tgi_set_fontsize(uint8_t size)
{
	g_fontsize = size;
}


uint8_t g_surface_map[SCREEN_WIDTH*SCREEN_HEIGHT/8];  // 256 byte = 2048 bits.


void set_surface(uint8_t x, uint8_t y)
{	
	int map_idx = (SCREEN_WIDTH*y+x)/8;
	uint8_t map_offset = (SCREEN_WIDTH*y+x) % 8;


	g_surface_map[map_idx] |= ((uint8_t)(1)<<map_offset);
}

void clear_surface(uint8_t x, uint8_t y)
{	
	int map_idx = (SCREEN_WIDTH*y+x)/8;
	uint8_t map_offset = (SCREEN_WIDTH*y+x) % 8;
	uint8_t map_target = g_surface_map[map_idx];

	g_surface_map[map_idx] &= ~((uint8_t)(1)<<map_offset);
}

bool get_surface(uint8_t x, uint8_t y)
{	
	int map_idx = (SCREEN_WIDTH*y+x)/8;
	uint8_t map_offset = (SCREEN_WIDTH*y+x) % 8;
	uint8_t map_target = g_surface_map[map_idx];

	return (g_surface_map[map_idx] & ((uint8_t)(1)<<map_offset));
}


//for simulation 
#include "tinyptc.h"
void tgi_paint()
{
	int ret;
	tgi_convert(g_offscreen, NULL);
	do{
          ret =  ptc_update(g_offscreen);

    }while(ret != 1);
	
}



void tgi_convert(uint8_t *dev, uint8_t *buf)
{	
	int s_idx = 0;
	int e_idx = 0;
	int x = 0;
	int y = 0;	
	T_RGB rgb;

	for(int line = 0 ; line < SCREEN_HEIGHT; line++)
	{
		for(int s_idx = 0, e_idx = 0; s_idx < SCREEN_WIDTH*4 ; s_idx+=4, e_idx++)
		{
			if(get_surface(line,s_idx/4))
			{
				dev[line*SCREEN_WIDTH*4 + s_idx]   = g_color.R;
				dev[line*SCREEN_WIDTH*4 + s_idx+1] = g_color.G;
				dev[line*SCREEN_WIDTH*4 + s_idx+2] = g_color.B;
				dev[line*SCREEN_WIDTH*4 + s_idx+3] = 0;
			}
			else
			{												
				dev[line*SCREEN_WIDTH*4 + s_idx]     = 255;
				dev[line*SCREEN_WIDTH*4 + s_idx + 1] = 255;
				dev[line*SCREEN_WIDTH*4 + s_idx + 2] = 255;
				dev[line*SCREEN_WIDTH*4 + s_idx + 3] = 0;
			}
		}
	}
}

void move_circle()
{
	int i = 0;
	int a;

	double rad;
	double x = 100;
	double y = 100;

	double pi = 3.145926535;

	srand(0);

	while (1)
	{
		double dx, dy;

		if (i % 1000 == 0)
		{
			i = 0;
			a = rand() % 360;
			rad = (a*pi) / 180;
		}
		else if (i % 10 == 0)
		{
			dx = cos(rad);
			dy = sin(rad);
			x = x + dx;
			y = y + dy;
		}
		printf("%d, %d\n", x, y);
		tgi_draw_circle2(x, y, 10);
		tgi_paint();
		tgi_clear();
		i++;
	}
}
void set_surface_clear(uint8_t x, uint8_t y)
{
	int map_idx = (SCREEN_WIDTH*y + x) / 8;
	uint8_t map_iffset = (SCREEN_WIDTH*y + x) % 8;
	g_surface_map[map_idx] &= 0x00;
}

void tgi_clear()
{
	int i, j, idx;
	idx = 0;
	for (i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (j = 0; j < SCREEN_WIDTH; j++)
		{
			set_surface_clear(i, j);
		}
	}
}

void tgi_analog_design() {
	tgi_set_text(165, 20, "1");
	tgi_set_text(195, 50, "2");
	tgi_set_text(208, 92, "3");
	tgi_set_text(192, 140, "4");
	tgi_set_text(163, 170, "5");
	tgi_set_text(122, 180, "6");
	tgi_set_text(75, 168, "7");
	tgi_set_text(45, 135, "8");
	tgi_set_text(35, 93, "9");
	tgi_set_text(43, 46, "10");
	tgi_set_text(70, 20, "11");
	tgi_set_text(118, 5, "12");

	tgi_set_text(217, 31, "HAN");
	tgi_set_text(217, 41, "NAM");

	tgi_draw_circle2(125, 100, 5);
	tgi_draw_circle2(125, 100, 4);
	tgi_draw_circle2(125, 100, 3);
	tgi_draw_circle2(125, 100, 2);
	tgi_draw_circle2(125, 100, 1);
	tgi_draw_circle2(125, 100, 6);
	tgi_fill_rect(218, 23, 224, 31);
	tgi_fill_rect(242, 23, 248, 31);
	tgi_fill_rect(236, 15, 242, 23);
	tgi_fill_rect(224, 15, 230, 23);
	tgi_fill_rect(230, 6, 236, 15);
}

void tgi_digital_clock() {
	tgi_draw_rect(25, 205, 225, 230);
}