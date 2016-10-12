#pragma once
#include "atlstr.h"

class CAnsicUnicode
{
public:
	CAnsicUnicode();
	~CAnsicUnicode();

public:
	static CString Ansic2Unicode(char *p);
	static void CString2char(CString str,char p[]);
	static void Wchar2char(WCHAR wc,char c[]);
};
 
