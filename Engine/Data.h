#pragma once
#include "Common.h"
class _EXPORT Data
{
public:
	//kontruktory i destruktory
	Data(char* _p = 0);
	Data(char* p, size_t s);
	Data(const Data&);
	~Data();
	//operatory przypisania
	char* operator = (char*);
	Data& operator=(const Data&);

	//operatory logiczne
	operator bool() const { return m_data != 0; }
	bool operator !() const { return !m_data; }

	//operatory wskaünikowe
	char& operator*() { return *m_data; }
	const char& operator*() const { return *m_data; }
	char* operator->() { return m_data; }

	//operatory rzutowania na "g≥upi" wskaünik
	operator char* () { return m_data; }
	operator const char*() const { return m_data; }

	size_t getSize() { return size; }
	void setSize(size_t p) { size = p; }
	void ResetCount() { refCount = 1; }
private:
	char* m_data;
	size_t size;
	int refCount;
};

