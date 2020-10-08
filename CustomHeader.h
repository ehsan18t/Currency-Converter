#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include "rlutil.h"
#include "bin/json/cJSON.h"
#include "bin/json/cJSON.c"
// cJSON REF: https://sourceforge.net/projects/cjson/

typedef struct
{
    char date[11];
    char time[9];
    char type[8];
    double amount;
    double rate;
    double total;
} history;

typedef struct
{
    char date[15];
    double rate;
} oneDayRate;

void timeName(char data[], char prefix[])
{
    time_t now = time(0);
    // Storing Current Time in 'data'
    strftime(data, 100, "%Y-%m-%d_%H-%M-%S.txt", localtime(&now));
    strcat(prefix, data);
}

void currTime(char data[])
{
    time_t now = time(0);
    strftime(data, 100, "%H:%M:%S", localtime(&now));
}

void currDate(char data[])
{
    time_t now = time(0);
    strftime(data, 100, "%Y-%m-%d", localtime(&now));
}

void wrongInput()
{
    setColor(RED);
    printf("\n ERROR: WRONG INPUT! PLEASE TRY AGAIN!\n\n");
    resetColor();
}

int inputValidation(char exID[])
{
    char p1[4];
    char p2[4];
    // Input Validation Lv. 1
    if (strlen(exID) != 7)
    {
        wrongInput();
        return -1;
    }

    // Input Validation Lv. 2
    if (exID[3] != '-')
    {
        wrongInput();
        return -1;
    }

    strupr(strncpy(p1, exID, 3));
    strupr(strcpy(p2, &exID[4]));

    // Input Validation Lv. 3
    for (int i = 0; i < 3; i++)
    {
        if (!isalpha(p1[i]) || !isalpha(p2[i]))
        {
            wrongInput();
            return -1;
        }
    }
    return 0;
}

// Input Validation Lv. 4
int inputValidationLv4(char jsonName[])
{
    char rate[30] = "", temp[30] = "";
    FILE *fp;

    fp = fopen(jsonName, "r");
    if (fp == NULL)
        return -1;
    fscanf(fp, "%s", &temp);
    fclose(fp);
    if (strcmp(temp, "{}") == 0)
    {
        remove(jsonName);
        return -2;
    }
    return 0;
}

// This function will generate a date(CurrentDate - minus).
// That means, if current Date is 7 OCT and minus = 7
// than it will generate 1 OCT and store in data.
void previousDate(char data[], int minus)
{
    time_t now = time(NULL) - (24 * 60 * 60 * minus);
    strftime(data, 100, "%Y-%m-%d", localtime(&now));
}

// JSON parser using cJSON.H & cJSON.c
// REF: https://sourceforge.net/projects/cjson/
double specificDateRate(char exID[], char date[], char data[])
{
    cJSON *root = cJSON_Parse(data);
    cJSON *format = cJSON_GetObjectItem(root, exID);
    double rate = cJSON_GetObjectItem(format, date)->valuedouble;
    return rate;
}

void replace_char(char *str, char oldChar, char newChar)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == oldChar)
        {
            str[i] = newChar;
        }
        i++;
    }
}

int check_char(char str[], char x)
{
    int flag = 0, i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == x)
            flag = 1;
        i++;
    }
    return flag;
}

// Could be use json parser library but that will be overkill for
// this small amount of work.
double scanjson(char jsonName[])
{
    int i = 11, j = 0;
    char rate[30] = "", temp[30] = "";
    FILE *fp;

    fp = fopen(jsonName, "r");
    if (fp == NULL)
        return -1;
    // Assigning first line of 'convert.json' into 'temp' array
    fscanf(fp, "%s", &temp);
    fclose(fp);
    remove(jsonName);
    // checking invalid input
    if (strcmp(temp, "{}") == 0)
        return -2;

    // Copying double from 'temp' to 'rate' as a string.
    // NOTE: First 10 index will always be character type because
    //       of json format, number type will start from index 11.
    while (temp[i] != '}')
    {
        rate[j] = temp[i];
        i++;
        j++;
    }
    // Converting 'rate' array into double using 'atof'
    // function from 'stdlib.h' and returning the value.
    return atof(rate);
}

// NOTE: This function will run in only Windows.
// Requirement: Internet Explorer 3 or higher or just urlmon.dll library.
//              (This library pre-built is into all Windows OS.)

void fetchJson(char url[], char destination[])
{
    // REF: https://www.go4expert.com/articles/download-file-using-urldownloadtofile-c-t28721/
    int i = 43, j = 0;
    // This is a free API. It has limit, maximum 100 request per hour.
    char buffer[256];

    // Replacing 'USD_BDT' with inputted currency types using 2 while loop.
    // Because in this case(index are known) this one seems more efficient than
    // recurrtion or any other pre-built function of C.

    HRESULT dl;

    typedef HRESULT(WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void *lpfnCB);
    URLDownloadToFileA_t xURLDownloadToFileA;
    xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");

    dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);

    // Print only error messege if occurs.
    if (dl == S_OK)
    {
    }
    else if (dl == E_OUTOFMEMORY)
    {
        setColor(RED);
        sprintf(buffer, "\n ERROR: Failed To Fetch API! \nREASON: Insufficient Memory!\n");
        printf(buffer);
        resetColor();
        exit(0);
    }
    else
    {
        setColor(RED);
        sprintf(buffer, "\n ERROR: Failed To Fetch API! \nREASON: Internet Connction not Available!\n");
        printf(buffer);
        resetColor();
        exit(0);
    }
}
