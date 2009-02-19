#pragma once

#define BLOCK_LENGTH 64 *1024	// 64K
#define RESERVE_BLOCK_NUM	10  // ��ౣ��10��,������ղ���ɾ��

class CCacheBlock
{
public:
	CCacheBlock(void);
	virtual ~CCacheBlock(void);

public:
	DWORD m_dwStartPos;
	char  m_szData[BLOCK_LENGTH];
	DWORD m_dwLastVisit;
};

class CCacheFile
{
public:
	CCacheFile(void);
	virtual ~CCacheFile(void);
	void DeleteOverTimeBlock();
	void PushBlock( DWORD dwStartPos, char* pBuffer, DWORD dwLen);
	DWORD GetData(  DWORD dwStartPos, char* pBuffer, DWORD dwLen);	// noexist return 0;���㳤���ش��ڲ���

protected:
	map<CCacheBlock *, CCacheBlock *> m_Blocks;
};
