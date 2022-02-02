#pragma once

#include "tinyptc.h"
#include "convert.h"

#include <stdio.h>
#include <math.h>
#include <windows.h>

class CSurface{
public:
	CSurface(){return;};
	~CSurface(){return;};
public:
	virtual int Create(char * windowname, int width, int height, int byte){return 0;};
public:
	virtual int GetBufferSize(){return 0;};
	virtual int GetColorByte(){return 0;}
	virtual unsigned char * GetBuffer(){return NULL;};
	virtual bool Paint(){return false;};
};

class CTinyGraphicSimulator : public CSurface
{
private:
	unsigned char * m_lpBuffer;
	int m_iSize;
	int m_iColorByte;
public:
	CTinyGraphicSimulator(void);
	~CTinyGraphicSimulator(void);
public:
	int Create(char * windowname, int width, int height, int byte);
	void Distroy();
	
	unsigned char * GetBuffer(){return m_lpBuffer;};		
	int GetBufferSize(){return m_iSize;};
	int GetColorByte(){return m_iColorByte;};
	bool Paint();

	//The InvalidateRect function adds a rectangle to the specified window's update region. The update region represents the portion of the window's client area that must be redrawn.
	bool Invaliddate(bool bErase){return false;};
};
