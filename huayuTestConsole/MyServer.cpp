#include "MyServer.h"
#include <stdio.h>
#include "tchar.h"

CMyServer::CMyServer(void)
{
}


CMyServer::~CMyServer(void)
{
}
void CMyServer::OnConnectionEstablished(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
{
	printf((" ���յ�һ���µ����ӣ�%d���� %s \n"), 
		GetCurrentConnection(), ::inet_ntoa(pContext->addrRemote.sin_addr));

	SendText(pContext, pBuffer->buff, pBuffer->nLen);
}

void CMyServer::OnConnectionClosing(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
{
	printf((" һ�����ӹرգ� \n") );
}

void CMyServer::OnConnectionError(CIOCPContext *pContext, CIOCPBuffer *pBuffer, int nError)
{
	printf((" һ�����ӷ������� %d \n "), nError);
}

void CMyServer::OnReadCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
{
	SendText(pContext, pBuffer->buff, pBuffer->nLen);
}

void CMyServer::OnWriteCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
{
	printf((" ���ݷ��ͳɹ���\n "));
}