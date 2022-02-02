#include "TinyGraphicSimulator.h"

CTinyGraphicSimulator::CTinyGraphicSimulator(void)
{
	m_lpBuffer = NULL;
	m_iSize = 0;
}

CTinyGraphicSimulator::~CTinyGraphicSimulator(void)
{	
	Distroy();
}

int CTinyGraphicSimulator::Create(char * windowname, int width, int height, int byte)
{
	m_iColorByte = byte;
	m_iSize = width*height*byte;
	m_lpBuffer = new unsigned char[m_iSize];
	
	if (!ptc_open(windowname, width, height))
	{
		if(m_lpBuffer)
		{
			delete [] m_lpBuffer;
			m_lpBuffer = NULL;
		}
		return (1);
	}
	
	return 0;
}

void CTinyGraphicSimulator::Distroy()
{
//	while (!ptc_process_events()) ;
	ptc_close();
	if(m_lpBuffer)
	{
		delete [] m_lpBuffer;
		m_lpBuffer = NULL;
		m_iSize = 0;
	}
}

bool CTinyGraphicSimulator::Paint()
{	
	int ret;
	do{
          ret =  ptc_update(m_lpBuffer);

    }while(ret != 1);

	return true;
}


