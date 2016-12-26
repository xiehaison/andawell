// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif


#include <time.h>
#include <sys/timeb.h>
#include <stdio.h>



void OutputLog(LPCTSTR DbgMessage,...)
{
	char buf[1024];
	memset(buf,0,1024);
	
	va_list args;
	va_start(args, DbgMessage);
	_vsnprintf (buf, sizeof(buf), DbgMessage, args);
	va_end(args);
	
    CTime now = CTime::GetCurrentTime();
    CString ss,s = now.Format("%c" );
    ss.Format("%s(%3u)=>%s\n",s, GetTickCount() % 1000, buf);

 //   char abuf[1024+512];
	//memset(abuf,0,1024+512);
	//sprintf(abuf,"%s(%3u)=>%s\n",strtime,GetTickCount()%1000,buf);
	//ofstream out("clientlog.tmp");
	//out << abuf << endl;
	//out.flush();
	//out.close();

	OutputDebugString(ss);
}
