/************************************************************************
��Ŀ���ƣ�PP��ý��
�ļ����ƣ�dataobject.h
��    �ܣ����ݿ����������
��    �ߣ�Kevin
�������ڣ�2006��03��14
�޸ļ�¼��
		
************************************************************************/

#ifndef  BATABASE_DATA_OBJECT_H
#define BATABASE_DATA_OBJECT_H


#include "mysqlconnection.h"
#include "../msgframe/connection_pool_t.h"
#include "mysqlrecordset.h"
#include "mysqlrow.h"
  
using namespace DB_TOOLKIT;
class CDataObject  
{ 
public:
	
	CDataObject();
	virtual ~CDataObject();
public:
	CDataObject(CConnectionPoolT<CMySQLConnection> *pPoolConns);
	void SetConnectionPool(CConnectionPoolT<CMySQLConnection> *pool);
	 const CConnectionPoolT<CMySQLConnection> * GetConnectionPool();
protected:
	CMySQLConnection* GetConnection();
	BOOL ReleaseConnection(CMySQLConnection *pConn);
    CConnectionPoolT<CMySQLConnection> * m_pPoolConns;
//////////////////////////////////////////////////////////////////////////
};


#endif
