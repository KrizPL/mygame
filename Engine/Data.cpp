#include "Data.h"
#include <cstring>
Data::Data(char * _p)
	:refCount(1)
{
	m_data = _p;
}

Data::Data(char * _p, size_t s)
{
	m_data = new char[s];
	memcpy(m_data, _p, s);
	size = s;
}

Data::Data(const Data &_d)
{
	m_data = _d.m_data;
}

Data::~Data()
{
	if (m_data)
	{
		try {
			delete[] m_data;
		}
		catch(...)
		{ }
		m_data = 0;
	}
}

char * Data::operator=(char *p)
{
	m_data = p;
	return m_data;
}

Data & Data::operator=(const Data& d)
{
	m_data = d.m_data;
	return *this;
}
