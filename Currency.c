#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "rlutil.h"

// "rlutil.h" Custom header file to use colors efficiently in cross platform
// REF: https://github.com/tapio/rlutil

void inst();
double scanjson();
void fetchJson(char x[], char y[]);

#define MAX_LINE 128

typedef struct
{
    double amount;
    char currType[8];
} currInput;


int main()
{
    char ch;
	saveDefaultColor();
    start:
    inst();
    currInput currInput;
    double rate = 0, total = 0;
    char currType1[4] = "", currType2[4] = "";
    Input:
    setColor(LIGHTGREEN);
    printf(" Input: ");
    setColor(LIGHTBLUE);
    scanf("%lf %s", &currInput.amount, &currInput.currType);
	resetColor();
    if (strcmp(currInput.currType, "") == 0)
    {
        setColor(RED);
        printf("\n ERROR: EMPTY INPUT! PLEASE TRY AGAIN!\n\n");
	    resetColor();
        goto Input;
    }
    
    strupr(strncpy(currType1, currInput.currType, 3));
    strupr(strcpy(currType2, &currInput.currType[4]));
    fetchJson(currType1, currType2);
    rate = scanjson();
    if (rate == -1)
    {
        setColor(RED);
        printf("\n ERROR: Failed To Fetch API!\n");
	    resetColor();
        exit(0);
    }
    else if (rate == -2)
    {
        setColor(RED);
        printf("\n ERROR: WRONG INPUT! PLEASE TRY AGAIN!\n\n");
	    resetColor();
        goto Input;
    }
    
    
    printf(" Current Rate: 1 %s = %.4lf %s\n", currType1, rate, currType2);
    setColor(LIGHTCYAN);
    printf(" Total: %.02lf %s\n", (rate * currInput.amount),currType2);
    setColor(LIGHTGREEN);
    printf(" Calculation: %.4lf %s x %.4lf %s = %.02lf %s\n", currInput.amount, currType1, rate, currType2, (rate * currInput.amount), currType2);
	resetColor();
	hidecursor();
    setColor(YELLOW);
    printf("\n    -> Press C to Continue or any other key to exit <-\n");
    resetColor();
    ch = getch();
    if (ch == 'c' || ch == 'C')
    {
	    showcursor();
        cls();
        goto start;
    }
    return 0;
}

// Could be use json parser library but that will be overkill for
// this small amount of work.
double scanjson()
{
    int i = 11, j = 0;
    char rate[30] = "", temp[30] = "";
    FILE *fp;

    fp = fopen("currencyRate.json", "r");
    if (fp == NULL)
        return -1;
    // Assigning first line of 'convert.json' into 'temp' array
    fscanf(fp, "%s", &temp);
    fclose(fp);
    remove ("currencyRate.json");
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

void fetchJson(char x[], char y[])
{
    // REF: https://www.go4expert.com/articles/download-file-using-urldownloadtofile-c-t28721/
    int i = 43, j = 0;
    // This is a free API. It has limit, maximum 100 request per hour.
    char url[MAX_LINE] = "https://free.currconv.com/api/v7/convert?q=USD_BDT&compact=ultra&apiKey=6cb174e127df4a1139f6";
    char destination[MAX_LINE] = "currencyRate.json";
    char buffer[MAX_LINE];

    // Replacing 'USD_BDT' with inputted currency types using 2 while loop.
    // Because in this case(index are known) this one seems more efficient than 
    // recurrtion or any other pre-built function of C.
    while (url[i] != '_')
    {
        url[i] = x[j];
        j++;
        i++;
    }
    i++;
    j = 0;
    while (url[i] != '&')
    {
        url[i] = y[j];
        j++;
        i++;
    }
    
    HRESULT    dl;
    
    typedef HRESULT (WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void * lpfnCB);
    URLDownloadToFileA_t xURLDownloadToFileA;
    xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");

    dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);
    
    // Print only error messege if occurs.
    if(dl == S_OK)
    {
    }
    else if(dl == E_OUTOFMEMORY) 
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
        sprintf( buffer, "\n ERROR: Failed To Fetch API! \nREASON: Internet Connction not Available!\n");
        printf(buffer);
	    resetColor();
        exit(0);
    }
}


void inst()
{
    setColor(LIGHTRED);
    printf(" \n                           ***************************\n");
    printf("                           **  Currency Conversion  **\n");
    printf("                           ***************************\n\n");
    setColor(LIGHTCYAN);
    printf(" ----------------------------------------------------------------------------------\n");
    printf(" |  USES: [AMOUNT] [CURRENT CURRENCY ID]-[CONVERT CURRENCY ID]                    |\n");
    printf(" |  EXAMPLES: 1 usd-bdt                                                           |\n");
    printf(" |            500 bdt-usd                                                         |\n");
    printf(" |            10 bdt-inr                                                          |\n");
    printf(" |  NOTES: '-' is used as 'to'                                                    |\n");
    printf(" |         All supported 'CURRENCY ID' can be found in 'Supported Currencies.txt' |\n");
    printf(" ----------------------------------------------------------------------------------\n\n");
	resetColor();
}