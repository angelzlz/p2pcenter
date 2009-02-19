 //
// MD5.h
//
#ifndef  MD_5_H
#define  MD_5_H
#include "../define/kwin32types.h"
#include "../misc/StringBuffer.h"
#include <stdio.h>
#include <string.h>

typedef LPCSTR LPCTSTR;

typedef union 
{
	BYTE	n[16];
	BYTE	b[16];
	DWORD	w[4];
} MD4, MD5;

void CreateMD5Hash(char szHash[33], BYTE* pData, DWORD dwLen);

class CMD5  
{
// Construction
public:
	CMD5();
	virtual ~CMD5();
	
// Attributes
public:
	DWORD	m_nCount[2];
	DWORD	m_nState[4];
	BYTE	m_nBuffer[64];

// Operations
public:
	void			Reset();
	void			Add(LPCVOID pData, DWORD nLength);
	void			Finish();
	void			GetHash(MD5* pHash);

public:
	static CString	HashToString(const MD5* pHash, BOOL bURN = FALSE);
	static BOOL		HashFromString(LPCTSTR pszHash, MD5* pMD5);
	static BOOL		HashFromURN(LPCTSTR pszHash, MD5* pMD5);

// Implementation
protected:
	void			Transform(BYTE* pBlock);
	void			Encode(BYTE* pOutput, DWORD* pInput, DWORD nLength);
	void			Decode(DWORD* pOutput, BYTE* pInput, DWORD nLength);
};

#endif


