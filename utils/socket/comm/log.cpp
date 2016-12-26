
#include "inc.h"
#include "log.h"
using namespace std;
char g_logFile[256] = "log";

void OutputLog(const char *fmt, ... )
{
    
    char temp[TIME_LEN] = {0};	
    struct tm *tt;
    
    time_t now_t = time(NULL);
    tt = localtime(&now_t);
    strftime(temp,sizeof(temp),"%F %T",tt);
    
    char szTraceInfo[ MAX_LOG_BUFFER_LEN ];        
    memset(szTraceInfo,0,sizeof(szTraceInfo));
    
    va_list ap;    
    va_start(ap, fmt);
    vsprintf(szTraceInfo, fmt, ap);
    va_end(ap);     
    
    ofstream outfile(g_logFile);
    outfile << temp << "=>" << szTraceInfo << endl; 
    cout << szTraceInfo << endl;
    outfile.flush();    
    outfile.close();
    return;
}

