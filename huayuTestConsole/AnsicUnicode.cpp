#include "AnsicUnicode.h"

CAnsicUnicode::CAnsicUnicode()
{

}

CAnsicUnicode::~CAnsicUnicode()
{

}

void CAnsicUnicode::CString2char(CString str,char p[])
{
	//int len =WideCharToMultiByte(CP_ACP,0,str,-1,NULL,0,NULL,NULL);  
	//char *ptxtTemp =new char[len +1];  
	//WideCharToMultiByte(CP_ACP,0,str,-1,ptxtTemp,len,NULL,NULL );  
	//*p = *ptxtTemp;
	////...  
	//delete[] ptxtTemp;  
}

void CAnsicUnicode::Wchar2char(WCHAR wc,char c[])
{
	
	int iSize;   
	char* pszMultiByte;   
	iSize = WideCharToMultiByte(CP_ACP, 0, &wc, -1, NULL, 0, NULL, NULL);   
	pszMultiByte = (char*)malloc((iSize)/**sizeof(char)*/);   
	WideCharToMultiByte(CP_ACP, 0, &wc, -1, pszMultiByte, iSize, NULL, NULL);  
	
	strcmp(c,pszMultiByte);
	
	delete []pszMultiByte;
}