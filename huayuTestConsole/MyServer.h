#pragma once
#include "iocpserver.h"
class CMyServer :
	public CIOCPServer
{
public:
	CMyServer(void);
	~CMyServer(void);

public:
	// 建立了一个新的连接
	virtual void OnConnectionEstablished(CIOCPContext *pContext, CIOCPBuffer *pBuffer);
	// 一个连接关闭
	virtual void OnConnectionClosing(CIOCPContext *pContext, CIOCPBuffer *pBuffer);
	// 在一个连接上发生了错误
	virtual void OnConnectionError(CIOCPContext *pContext, CIOCPBuffer *pBuffer, int nError);
	// 一个连接上的读操作完成
	virtual void OnReadCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer);
	// 一个连接上的写操作完成
	virtual void OnWriteCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer);
};

