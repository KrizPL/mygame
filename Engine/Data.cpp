#include "Data.h"

Data::Data(char * _p)
{
	m_data = _p;
}

Data::Data(const Data &_d)
{
	m_data = _d.m_data;
}

Data::~Data()
{
	if (m_data)
	{
		delete[] m_data;
		m_data = 0;
	}
}

char * Data::operator=(char *p)
{
	m_data = p;
	return m_data;
}

Data & Data::operator=(const Data &d)
{
	m_data = d.m_data;
	return *this;
}
