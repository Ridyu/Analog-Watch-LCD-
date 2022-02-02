#pragma once
#include "tgi.h"
#include "TinyGraphicSimulator.h"

// C++ Scope
CSurface * g_lpSim;
unsigned char * getbuffer()
{
	return g_lpSim->GetBuffer();
}

// C++ Scope
void tgi_init()
{
	g_lpSim = new CTinyGraphicSimulator;
	g_lpSim->Create("LCD", SCREEN_WIDTH , SCREEN_HEIGHT , SCREEN_BPP); 
	tgi_open(getbuffer(), SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
}

// C++ Scope
void tgi_release()
{
	tgi_close();
	delete g_lpSim;
}
