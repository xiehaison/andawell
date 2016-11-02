// Config.cpp: implementation of the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "inc.h"
#include "Config.h"
#define TMP_SHORT_LEN  256



int GetPrivateProfileInt(char* lpAppName, char* lpKeyName, int nDefault, char *lpFileName)
{
	int ret = -1;
	FILE *fp;	
	fp = fopen(lpFileName, "r");

	if (fp == NULL)
	{
		printf("Open Config File %s Failure\n",lpFileName);
		char ch;
		scanf("%c" , &ch);
	}
	else
	{
		bool FindKey = false;
		bool FindApp = false;
		bool HaveHL = true;
		char temp[TMP_SHORT_LEN];
		int i=0;
		memset(temp, 0, TMP_SHORT_LEN);	
		char ch = getc(fp);
		while(ch!=EOF)
		{
			if(ch == 10)
			{	
				if (FindKey == true)
				{
					ret = 1;
					break;
				}
				HaveHL = true;
				memset(temp, 0, TMP_SHORT_LEN);
				i=0;	
			}

			if ((ch != 10) && (ch != '[') && (ch != ']') && (ch != '=') && (ch != 32) && (HaveHL == true))
			{
				temp[i] = ch;
				i++;
			}

			if ((ch == ']')
				&& (FindApp == false))
			{
				if (strcmp(lpAppName, temp) == 0)
				{
					i=0;
					memset(temp, 0, TMP_SHORT_LEN);
					HaveHL = false;
					FindApp = true;
				}
			}
			if (FindApp == true)
			{
				if (ch == '=')
				{
					if (strcmp(lpKeyName, temp) == 0)
					{
						i = 0;
						memset(temp, 0, TMP_SHORT_LEN);
						HaveHL = true;
						FindKey = true;
					}
				}
			}
			ch = getc(fp);	
		}

		if (ret == 1)
		{
			ret = atoi(temp);
		}
		else if(ret == -1)
		{
			ret = nDefault;
		}

		fclose(fp);
	}

	return ret;
}


int GetPrivateProfileString(char* lpAppName, char* lpKeyName, char* lpDefault, char* lpReturnedString, unsigned int nSize, char* lpFileName)
{
	int ret = -1;
	FILE *fp;	
	fp = fopen(lpFileName, "r");
	
	if (fp == NULL)
	{
		printf("Open Config File %s Failure\n",lpFileName);
		char ch;
		scanf("%c" , &ch);
	}
	else
	{
		bool FindKey = false;
		bool FindApp = false;
		bool HaveHL = true;
		char temp[TMP_SHORT_LEN];
		int i=0;
		memset(temp, 0, TMP_SHORT_LEN);	
		char ch = getc(fp);
		while(ch != EOF)
		{
			if(ch == 10 || ch == 13 )
			{	
				if (FindKey == true)
				{
					ret = 1;
					break;
				}
				HaveHL = true;
				memset(temp, 0, TMP_SHORT_LEN);
				i=0;	
			}

			if ((ch != 10) && (ch != '[') && (ch != ']') && (ch != '=') && (ch != 32) && (HaveHL == true))
			{
				temp[i] = ch;
				i++;
			}

			if(ch == ']' && FindApp == false)
			{
				if (strcmp(lpAppName, temp)==0)
				{
					i = 0;
					memset(temp, 0, TMP_SHORT_LEN);
					HaveHL = false;
					FindApp = true;
				}
			}
			if (FindApp == true)
			{
				if (ch=='=')
				{
					if (strcmp(lpKeyName, temp)==0)
					{
						i = 0;
						memset(temp, 0, TMP_SHORT_LEN);
						HaveHL = true;
						FindKey = true;
					}
				}
			}
			ch = getc(fp);	
		}

		if (ret == 1)
		{
			if (strlen(temp) < nSize)
			{
				strcpy(lpReturnedString, temp);
				ret = strlen(temp);
			}
			else
			{
				strncpy(lpReturnedString, temp, nSize);
				lpReturnedString[nSize] = 0;
				ret = nSize;
			}
		}
		else if(ret == -1)
		{
			if (strlen(lpDefault) < nSize)
			{
				strcpy(lpReturnedString, lpDefault);
				ret = strlen(temp);
			}
			else
			{
				strncpy(lpReturnedString,lpDefault,nSize);
				lpReturnedString[nSize] = 0;
				ret = nSize;
			}
		}
		fclose(fp);
	}
	return ret;
}
