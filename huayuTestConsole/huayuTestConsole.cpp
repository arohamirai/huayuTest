#include "iostream"
#include "MyServer.h"
#include "IoControler.h"
#include "Camera.h"
#include "ProcessThread.h"
#include "Dbase.h"
#include "tchar.h"
#include "AnsicUnicode.h"
#include "Machine.h"
#include "BusManager.h"

#include "FlyCapture2.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace FlyCapture2;


//#define	TOTAL_MACHINE				10

HANDLE *g_pEventHandle ;	//�¼����������ֱ��ģ���������ͬ��
BOOL *g_work;				//ģ�鹤����־λ

bool isCameraExist(unsigned int serialNumber, FlyCapture2::CameraInfo *pCamInfo,unsigned int arraySize);

//*********************** ��װ���Ӻ��������ڻ�ȡ������Ϣ ***********************//
HHOOK g_kb_hook;
LRESULT CALLBACK kb_proc (int code, WPARAM wParam, LPARAM lParam)
{
	//printf((w==WM_KEYDOWN)?"����%c\n":"̧��%c\n",((PKBDLLHOOKSTRUCT)lParam)->vkCode);
	if(wParam == WM_KEYUP)		
	{
		TCHAR c = ((PKBDLLHOOKSTRUCT)lParam)->vkCode;
		PostThreadMessage(GetCurrentThreadId(),WM_CHAR,NULL,(LPARAM)c);
	}
	return CallNextHookEx (g_kb_hook, code, wParam, lParam);
}

void _tmain(int argc, _TCHAR* argv[])
{
	g_kb_hook = SetWindowsHookEx (WH_KEYBOARD_LL,kb_proc,GetModuleHandle(NULL),0);
	if (g_kb_hook == NULL )
	{
		printf("��װ���ӳ���\n");
		return ;
	};
	//if (argc < 2)	return;
	//if(_tcscmp(argv[1], _T("huayuTest")) != 0)	return;

	//*********************** �������� ***********************//
	

	//*********************** ��ʼ��ϵͳ ***********************//
	//						  �������ȷ��						//

	//						   ���ñ���							//
	
	int totalMachine = 0;
	unsigned int totalCam;
	std::vector<int> vecOKMachineID, vecNotOKMachineID;
	CDbase db;
	
	CString strSQL;

	db.connectDB();

	//��ȡ��̨����
	{
		_RecordsetPtr pRecordset;
		strSQL = _T("select count(*) as totalMachine from machineInfoTable");
		pRecordset = db.readBySet(strSQL);
		if ( pRecordset->GetRecordCount() == -1)
			return;
		totalMachine = (int)pRecordset->GetCollect((_variant_t)(_T("totalMachine")));
		g_pEventHandle = new HANDLE[totalMachine * LINEMODULES_PER_MACHINE];
		g_work = new BOOL[totalMachine * LINEMODULES_PER_MACHINE];

		pRecordset->Close();
		pRecordset = NULL;
		
		//��ȡ�������
		CBusManager bus;
		int e;
		e = bus.GetNumOfCameras(&totalCam);
		if (e != BUS_0K)	return;
	}

	//����̨�Ƿ�������
	if ( totalCam < totalMachine  * LINEMODULES_PER_MACHINE * CAMERAS_PER_LINEARMODULE)
	{
		//ĳЩ��̨�����ϣ��������ϻ�̨
		int *pMachaineID = NULL;
		bool *pbOKmachine = NULL;
		FlyCapture2::CameraInfo CamInfo ;
		unsigned int arrySize;
		pbOKmachine = new bool[totalMachine];
			
		//��ȡ���������������Ϣ
		CBusManager::DiscoverAllCameras(&CamInfo,&arrySize);

		//�Ȼ�ȡ���л�̨���
		_RecordsetPtr pRecordsetMachine;
		strSQL = _T("select machineID from machineInfoTable");
		pRecordsetMachine = db.readBySet(strSQL);
		//������̨
		if (!pRecordsetMachine->adoEOF)
		{
			int index = 0;
			pRecordsetMachine->MoveFirst();

			while(!pRecordsetMachine->adoEOF)
			{
				_RecordsetPtr pRecordsetCam;

				// ��ʼΪtrue
				pbOKmachine[index] = true;

				//���ݻ�̨��Ų��Ҷ�Ӧ���
				pMachaineID[index] = (int)pRecordsetMachine->GetCollect(_T("machineID"));
				strSQL.Format(_T("select cameraID from machineInfoTable where machineID =  %d"),pMachaineID[index]);
				pRecordsetCam = db.readBySet(strSQL);
				if (!pRecordsetCam && !pRecordsetCam->adoEOF)
				{
					pRecordsetCam->MoveFirst();
					while(!pRecordsetCam->adoEOF)
					{
						unsigned int serialNumber;
						bool exist;
							
						serialNumber= (unsigned int)pRecordsetCam->GetCollect(_T("cameraID"));
						exist = isCameraExist(serialNumber,&CamInfo,arrySize);
						pbOKmachine[index] = pbOKmachine[index] & exist;

						pRecordsetCam->MoveNext();
					}

					pRecordsetCam->Close();
					pRecordsetCam = NULL;
				}
				index++;
				pRecordsetMachine->MoveNext();
			}
		}


		pRecordsetMachine->Close();
		pRecordsetMachine = NULL;

		// ������������̨������飬����������Ϣ
		for (int i = 0; i < totalMachine; ++i)
		{
			if (pbOKmachine[i] == true)
			{
				vecOKMachineID.push_back(pMachaineID[i]);
			}
			else
			{
				vecNotOKMachineID.push_back(pMachaineID[i]);
			}
			delete []pMachaineID;
			delete []pbOKmachine;

			CString strNotOK = _T("");
			for (std::vector<int>::iterator it = vecNotOKMachineID.begin(); it != vecNotOKMachineID.end(); it++)
			{
				CString strTemp;
				strTemp.Format(_T("%d,"),*it);
				strNotOK =strNotOK + strTemp;
			}
			strNotOK = _T("���Ϊ��") + strNotOK + _T("�Ļ�̨ĳЩ������������������Ƿ���������������̨��");
			INT_PTR nResponse = ::MessageBox(NULL,strNotOK,_T("��ע��"),MB_OKCANCEL|MB_ICONQUESTION);
			if (nResponse == IDCANCEL)
				return;
		}
	}

	//						  IOģ������ȷ��						//
	/*
	 //add code here
	*/


	//*********************** �����������߳� ***********************//

	int totalOKMachine = vecOKMachineID.size();
	int totalLinearModule = 1;
	HANDLE *pThreadHandle = new HANDLE[totalOKMachine];		//�������߳̾��
	bool flag = false;
	
	for(int i = 0; i < totalOKMachine; ++i)
	{
		while(!flag)	{};

		_RecordsetPtr pRecordsetCam = NULL;
		CString strSQL;
		int cameraID0,cameraID1;

		strSQL.Format( _T("select cameraID from machineInfoTable where machineID = %d"),vecOKMachineID[i]);
		pRecordsetCam = db.readBySet(strSQL);
		if(!pRecordsetCam && !pRecordsetCam->adoEOF)
		{
			MessageBox(NULL,_T("��ѯ��̨�����Ϣʧ�ܣ�"),_T("����"),MB_OKCANCEL);
			return;
		}
		pRecordsetCam->MoveFirst();
		cameraID0 = pRecordsetCam->GetCollect(_T("cameraID")).intVal;
		pRecordsetCam->MoveNext();
		cameraID1 = pRecordsetCam->GetCollect(_T("cameraID")).intVal;

		CProcessThread *pProcessThread0,*pProcessThread1;
		pProcessThread0 = new CProcessThread();
		pProcessThread1 = new CProcessThread();

	
		pProcessThread0->createThread(pProcessThread0,NULL);
		pProcessThread1->createThread(pProcessThread1,NULL);

		if (!pProcessThread0->InitInstance() && !pProcessThread1->InitInstance())
		{
			return;
		}
	}

	//*********************** ����ͨ�ŷ��� ***********************//

	CMyServer server;
	CMyServer *pServer = &server;

	// ��������
	if(pServer->Start())
	{
		printf(" �����������ɹ�... \n");
	}
	else
	{
		printf(" ����������ʧ�ܣ�\n");
		return;
	}


	//*********************** ��Ϣѭ�� ***********************//
	BOOL bQuit = FALSE;
	MSG msg;
	while(!bQuit && ::GetMessage(&msg,NULL,0,0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
		switch (msg.message)
		{
			case WM_CHAR :			//������Ϣ
				{
					wprintf(_T("%c\n"),(TCHAR)msg.lParam);
					TCHAR c = (TCHAR)msg.lParam;

					switch(c)
					{
					case 'Q':
						bQuit = TRUE;
						break;
					default:
						break;
					}	
					
				}
			break;
		default:
			break;
		}

	}
	

	

	//						  �����˳�						//
	/*
	 //add code here
	*/

	// �ͷŹ���
	UnhookWindowsHookEx(g_kb_hook);


	//�رշ�����
	pServer->Shutdown();
	pServer = NULL;
	printf(" �������ر� \n ");


	// �ͷ��߳̾�����¼����
	/*for (int i = 0; i < totalThread; ++i)
	{
		CloseHandle(pThreadHandle[i]);
	}
	for (int i = 0; i < totalLinearModule; ++i)
	{
		CloseHandle(g_pEventHandle[i]);
	}*/

	//�Ͽ����ݿ�����
	db.disConnectDB();


}


bool isCameraExist(unsigned int serialNumber, FlyCapture2::CameraInfo *pCamInfo,unsigned int arraySize)
{
	for (int i = 0; i < arraySize; ++i)
	{
		if (serialNumber == pCamInfo[i].serialNumber) return true;
	}

	return false;
}