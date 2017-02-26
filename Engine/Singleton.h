#pragma once
#include <assert.h>
template <typename T>
class Singleton
{
public:
	static T* getInstance()
	{
		return m_pInstance;
	}
	Singleton()
	{
		assert(!m_pInstance);
		int iOffset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
		m_pInstance = (T*)(this + iOffset);
	}
	~Singleton()
	{
		if (m_pInstance)
			m_pInstance = 0;
	}
private:
	static T* m_pInstance;
};
template <typename T> T* Singleton<T>::m_pInstance = 0;