#include "sockutil.h"
#include <winsock2.h>

char* GetHostIP()
{
    char name[255];
    PHOSTENT hostinfo;
  
    if( gethostname ( name, sizeof(name)) == 0)
    {
        if((hostinfo = gethostbyname(name)) != NULL)
        {
            return inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
        }
    }
    return NULL;
}
