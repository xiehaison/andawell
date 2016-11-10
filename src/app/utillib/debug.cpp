#include <time.h>
#include <sys/timeb.h>
#include <stdio.h>
#include "debug.h"

void dbgmsg(LPCTSTR DbgMessage,...)
{
	char buf[1024];
	memset(buf,0,1024);

	va_list args;
	va_start(args, DbgMessage);
	_vsnprintf (buf, sizeof(buf), DbgMessage, args);
        va_end(args);

	strcat(buf, "\n");
	char str[512];
	memset(str, 0, sizeof(str));
	strcat(str, buf);

	struct timeb tstruct;
	ftime( &tstruct );

        char abuf[1024];
        memset(abuf,0,1024);
        sprintf(abuf,"%s(%3u)=>%s",ctime(&tstruct.time),tstruct.millitm,buf);

	OutputDebugString(abuf);
}
