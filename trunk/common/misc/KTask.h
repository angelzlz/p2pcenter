/********************************************************************
	created:	2008/01/11
	created:	11:1:2008   15:49
	author:		Kevin
	
	purpose:	

	email:		kan8888.com@163.com
	msn:		fuwenke@gmail.com
	QQ:		799383417
	site:		opensource.kan8888.com
*********************************************************************/

#ifndef __KTASK_H_
#define __KTASK_H_

// δ���ر�˵���ģ���λ��Ϊ ����
class CKTask
{
public:
	CKTask()
	{
		m_dwCreateTime = GetTickCount();
	}

	CKTask(DWORD dwTimeOut, DWORD dwTimeOutMsg = 0)
	{
		m_dwCreateTime = GetTickCount();
		m_dwTimeOut = dwTimeOut;
		m_dwTimeOutMsg = dwTimeOutMsg;
	}

	void Init(DWORD dwTimeOut, DWORD dwTimeOutMsg = 0)
	{
		m_dwCreateTime = GetTickCount();
		m_dwTimeOut = dwTimeOut;
		m_dwTimeOutMsg = dwTimeOutMsg;
	}

	virtual ~CKTask(void)
	{
	}

	void Reset()
	{
		m_dwCreateTime = GetTickCount();
	}

	// nOffset ƫ����, ��λ������
	bool IsTimeOut(int nOffset = 0)
	{
		if ( (GetTickCount() - m_dwCreateTime) > (m_dwTimeOut + nOffset) )
			return true;
		else
			return false;
	}

private:
	// ����ʱ��
	DWORD m_dwCreateTime;
	// ��ʱʱ��
	DWORD m_dwTimeOut;
	// ��ʱ�󱣴��Ҫ���͵���ϢID
	DWORD m_dwTimeOutMsg;
};

#endif //__KTASK_H_
