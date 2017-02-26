#pragma once
class Data
{
public:
	//kontruktory i destruktory
	Data(char* _p = 0);
	Data(const Data&);
	~Data();
	//operatory przypisania
	char* operator = (char*);
	Data& operator=(const Data&);

	//operatory logiczne
	operator bool() const { return m_data != 0; }
	bool operator !() const { return !m_data; }

	//operatory wskaŸnikowe
	char& operator*() { return *m_data; }
	const char& operator*() const { return *m_data; }
	char* operator->() { return m_data; }

	//operatory rzutowania na "g³upi" wskaŸnik
	operator char* () { return m_data; }
	operator const char*() const { return m_data; }
private:
	char* m_data;
};

