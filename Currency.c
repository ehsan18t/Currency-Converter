#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "CustomHeader.h"
#include "rlutil.h"
// "rlutil.h" Custom header file to use colors efficiently in cross platform
// REF: https://github.com/tapio/rlutil

void saveOut(double, double, char[], char[]);

#define MAX_LINE 128

typedef struct
{
    double amount;
    char currType[8];
} currInput;

{
    char ch;
    char url[MAX_LINE] = "https://free.currconv.com/api/v7/convert?q=USD_BDT&compact=ultra&apiKey=6cb174e127df4a1139f6";
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

    strupr(strncpy(currType1, currInput.currType, 3));
    strupr(strcpy(currType2, &currInput.currType[4]));

    // Replacing '-' with '_' inside inputted currency type to match api url format.
    replace_char(currInput.currType, '-', '_');
    // creating api url according to user input
    replace_url1(url, currInput.currType);
    // Fetching API
    fetchJson(url, "currencyRate.json");
    // Scanning exchange rate
    rate = scanjson("currencyRate.json");

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

    // Console Output
    printf(" Current Rate: 1 %s = %.4lf %s\n", currType1, rate, currType2);
    setColor(LIGHTCYAN);
    printf(" Total: %.02lf %s\n", (rate * currInput.amount), currType2);
    setColor(LIGHTGREEN);
    printf(" Calculation: %.4lf %s x %.4lf %s = %.02lf %s\n", currInput.amount, currType1, rate, currType2, (rate * currInput.amount), currType2);
    resetColor();
    hidecursor();

ConfirmationEnd:
    // Options Menu
    endOpt();

    // Options working method
    ch = tolower(getch());
    if (ch == 'c')
    {
        showcursor();
        cls();
        goto start;
    }
    else if (ch == 's')
    {
        saveOut(currInput.amount, rate, currType1, currType2);
        goto ConfirmationEnd;
    }
    else if (ch == 'm')
    {
        showcursor();
        *x = 1;
    }
    else if (ch == 'x')
    {
        showcursor();
        exit(0);
    }

    return 0;
}

void saveOut(double amount, double rate, char currType1[], char currType2[])
{
    FILE *fptr;
    char buff[100] = "";
    char x[100] = "";
    sprintf(x, "Calculations/%.2lf_%s-%s", amount, currType1, currType2);
    timeName(buff, x);
    // opening file in writing mode
    fptr = fopen(x, "w");

    // exiting program
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    fprintf(fptr, "Current Rate: 1 %s = %.4lf %s\n", currType1, rate, currType2);
    fprintf(fptr, "Total: %.02lf %s\n", (rate * amount), currType2);
    fprintf(fptr, "Calculation: %.4lf %s x %.4lf %s = %.02lf %s\n", amount, currType1, rate, currType2, (rate * amount), currType2);
    fclose(fptr);
    setColor(LIGHTGREEN);
    printf("\n                            -> Operation Successful <-\n");
    resetColor();
}

void inst()
{
    setColor(LIGHTRED);
    printf(" \n                           ***************************\n");
    printf("                           **  Currency Conversion  **\n");
    printf("                           ***************************\n\n");
    setColor(LIGHTCYAN);
    printf("  ________________________________________________________________________________\n");
    printf(" |                                                                                |\n");
    printf(" |  USES: [AMOUNT] [CURRENT CURRENCY ID]-[CONVERT CURRENCY ID]                    |\n");
    printf(" |  EXAMPLES: 1 usd-bdt                                                           |\n");
    printf(" |            500 bdt-usd                                                         |\n");
    printf(" |            10 bdt-inr                                                          |\n");
    printf(" |  NOTES: '-' is used as 'to'                                                    |\n");
    printf(" |         All supported 'CURRENCY ID' can be found in 'Supported Currencies.txt' |\n");
    printf(" |________________________________________________________________________________|\n\n");
    resetColor();
}

void endOpt()
{
    printf("\n =================================================================================== ");
    printf("\n ||    ");
    setColor(LIGHTMAGENTA);
    printf("[C]");
    setColor(YELLOW);
    printf(" Continue     ");
    setColor(LIGHTMAGENTA);
    printf("[S]");
    setColor(YELLOW);
    printf(" Save Calculations      ");
    setColor(LIGHTMAGENTA);
    printf("[M]");
    setColor(YELLOW);
    printf(" Main Menu      ");
    setColor(LIGHTMAGENTA);
    printf("[X]");
    setColor(YELLOW);
    printf(" Exit    ");
    resetColor();
    printf("||\n ===================================================================================\n");
}