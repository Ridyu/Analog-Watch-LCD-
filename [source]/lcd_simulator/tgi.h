#ifndef _TINY_GRAPHIC_INTERFACE_
#define _TINY_GRAPHIC_INTERFACE_


#include "tgi_define.h"
#include "tgi_color.h"
#include "tgi_font.h"
#include "tgi_img.h"
#include "tgi_surface.h"

//tiny graphic interface
long tgi_open(uint8_t *psurface, uint8_t width, uint8_t height, uint8_t bpp);
void tgi_close();

//control
void tgi_set_color(const T_RGB * rgb);
void tgi_set_fontcolr(uint8_t R, uint8_t G, uint8_t B);
void tgi_set_color(uint8_t R, uint8_t G, uint8_t B);
void tgi_set_fontsize(uint8_t size); //FONT_SMALL_SIZE

//drawing
long tgi_set_pixel(int x,int y);
long tgi_set_pixel(T_POINT point);
void tgi_digital();
void tgi_digital_clock();
void tgi_analog_design();
long tgi_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void tgi_draw_vertical_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void tgi_draw_horizontal_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void tgi_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);
long tgi_draw_line(T_POINT start, T_POINT end);
void tgi_draw_rect(uint8_t l, uint8_t t, uint8_t r, uint8_t b);
long tgi_draw_rect(T_RECT rect);
void tgi_fill_rect(uint8_t l, uint8_t t, uint8_t r, uint8_t b);
void tgi_draw_circle(uint8_t x, uint8_t y, uint8_t r);
void tgi_draw_circle2(int x0, int y0, int radius);
long tgi_fill_rect(T_RECT rect);
void tgi_fill_all();

//character (ASCII 20~)
long tgi_put_char(uint8_t x, uint8_t y, char c);
long tgi_put_char0(uint8_t x, uint8_t y, char c);
long tgi_put_char1(uint8_t x, uint8_t y, char c);
long tgi_put_char2(uint8_t x, uint8_t y, char c);

//string
//TEXT_ALIGN_LEFT, TEXT_ALIGN_RIGHT, TEXT_ALIGN_CENTER
void tgi_set_text(int x, int y, char *string);
void tgi_set_text(T_RECT rect, char *string, int offset, int align); 
void tgi_set_text0(T_RECT rect, char *string, int offset);
void tgi_set_text1(T_RECT rect, char *string, int offset);
void tgi_set_text2(T_RECT rect, char *string, int offset);


//image
void tgi_draw_image(uint8_t imgid, int sx, int sy, int dx, int dy, int cx, int cy);

//display
void tgi_paint();


void tgi_draw_image();
void tgi_draw_logo();
void tgi_draw_alert();


//internal
void tgi_convert(uint8_t *src, uint8_t *dst );
void move_circle();
void tgi_clear();
void set_surface_clear(uint8_t x, uint8_t y);
void clear_surface(uint8_t x, uint8_t y);
bool get_surface(uint8_t x, uint8_t y);
void set_surface(uint8_t x, uint8_t y);

#endif //_TINY_GRAPHIC_INTERFACE_