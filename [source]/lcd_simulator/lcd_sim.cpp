#pragma once
#include "lcd_sim.h"
#include<time.h>
#define MAX_TIME 10000 //ms
int cur_time = 0;
double pi = 3.141592;
int main(int argc, char * argv[])
{
	clock_t sclock, nclock;//sclock:시작, nclock:현재(1/1000초 시간)

	time_t now; //초단위 시각

	struct tm *timer; //date time 시각    

	sclock = clock();//시작 clock

	now = time(NULL);
	//time(&now);//초단위 시각

	timer = localtime(&now);//date time 시각

	tgi_init();	//필수 tgi 함수를 호출

	while (1)
	{
		double x1, y1;
		double x2, y2;
		double x3, y3;
		double rad;
		double theta1;
		double theta2;
		double theta3;

		tgi_analog_design();		//아날로그 디자인
		void tgi_digital_clock();		//디지털 사각형
		tgi_digital(); // 디지털 시계 구현

		theta1 = 90 - (6 * timer->tm_sec);
		rad = pi*theta1 / 180.0;

		x1 = 75 * cos(pi*theta1 / 180.0) + 125;
		y1 = 100 - 75 * sin(pi*theta1 / 180.0);

		theta2 = 90 - (6 * timer->tm_min);

		x2 = 60 * cos(pi*theta2 / 180.0) + 125;
		y2 = 100 - 60 * sin(pi*theta2 / 180.0);

		theta3 = 90 - (30 * timer->tm_hour);

		x3 = 45 * cos(pi*theta3 / 180.0) + 125;
		y3 = 100 - 45 * sin(pi*theta3 / 180.0);

		tgi_draw_line(125, 100, x1, y1);
		tgi_draw_line(125, 100, x2, y2);
		tgi_draw_line(125, 100, x3, y3);

		tgi_draw_circle2(125, 100, 100);	//시계 원
		tgi_draw_circle2(125, 100, 98);		//시계 원 안

		Sleep(1000);
		tgi_paint();
		timer->tm_sec++;
		tgi_clear();

		if (timer->tm_sec == 61)
		{
			timer->tm_sec = 0;
			timer->tm_min++;
		}
		else if (timer->tm_min == 61)
		{
			timer->tm_min = 0;
			timer->tm_hour++;
		}

	}

	tgi_release();
	return 0;
}