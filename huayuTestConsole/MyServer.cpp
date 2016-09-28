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
	printf((" 接收到一个新的连接（%d）： %s \n"), 
		GetCurrentConnection(), ::inet_ntoa(pContext->addrRemote.sin_addr));

	SendText(pContext, pBuffer->buff, pBuffer->nLen);
}

void CMyServer::OnConnectionClosing(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
{
	printf((" 一个连接关闭！ \n") );
}

void CMyServer::OnConnectionError(CIOCPContext *pContext, CIOCPBuffer *pBuffer, int nError)
{
	printf((" 一个连接发生错误： %d \n "), nError);
}

void CMyServer::OnReadCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
{
	SendText(pContext, pBuffer->buff, pBuffer->nLen);
}

void CMyServer::OnWriteCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
{
	printf((" 数据发送成功！\n "));
}