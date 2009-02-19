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
#ifndef __INI_FILE_H_
#define __INI_FILE_H_


#include "StringBuffer.h"

#include "Array.h"

using namespace KBASE;

/*���������*/
class CIniFile
{
//��������������
public:
	CIniFile();
	CIniFile(const char* sFileName);
	virtual ~CIniFile();

//����˽�����ݳ�Ա
protected:
	//�����нṹ
	struct LINE_ITEM
	{
		int 	nType;		//����
		CString	sName;		//����
		CString sValue;		//ֵ
	};
	CPtrArray   	m_arrayOfLine;	//��������ļ��е�������
	CString			m_sFileName;	//�����ļ�����
	int				m_nTotalSection;//��������
	bool			m_bAutoFlush;	//�Ƿ��Զ�ˢ�µ��ļ�?
	bool			m_bModified;	//�Ƿ��޸Ĺ�
	
//�ļ���������
public:
	//���³�ʼ��������
	void Reset(void);
	//���������ļ�,�ɹ�����0,ʧ�ܷ���С��0��ֵ
	int LoadFromFile(const char* sFileName);
	//ˢ�µ�ǰ������ļ���,�ɹ�����0,ʧ�ܷ�������0��ֵ
	int FlushToFile(void);

//������������������
private:
	//������������,ȡ�������к�
	int GetSectionIndex(int nStartLine, const char* sSectionName);
	//���������кż�����������,ȡ�������������к�
	int GetKeyIndex(int nSectionIndex, const char* sKeyName);
public:
	//ȡ����������
	int GetSectionCount(void);
	//ȡ����������
	CString GetSectionName(int nIndex);
	//ȡ��ָ������������������
	int GetKeyCount(const char* sSectionName);
	//ȡ������������
	CString GetKeyName(const char* sSectionName, int nIndex);
	//ɾ��һ��������
	int DelKey(const char* sSectionName, const char* sKeyName);
	//����һ������,��������ֵ,ʧ�ܷ���С��0��ֵ
	int AddSection(const char* sSectionName);
	//ɾ��һ������
	void DelSection(const char* sSectionName);
	
//������ֵ��������
public:
	//ȡ���������ֵ(�ַ���)
	CString GetString(const char* sSectionName, const char* sKeyName);
	//ȡ���������ֵ(����)
	int GetInt(const char* sSectionName, const char* sKeyName);
	//ȡ���������ֵ(����)
	bool GetBool(const char* sSectionName, const char* sKeyName);
	//�����������ֵ(�ַ���)
	void SetString(const char* sSectionName, const char* sKeyName, const char* sKeyValue);
	//�����������ֵ(����)
	void SetInt(const char* sSectionName, const char* sKeyName, int nKeyValue);
	//�����������ֵ(����)
	void SetBool(const char* sSectionName, const char* sKeyName, bool bKeyValue);
};

#endif
