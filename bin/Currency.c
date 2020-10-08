#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "headers/rlutil.h"
// "rlutil.h" Custom header file to use colors efficiently in cross platform
// REF: https://github.com/tapio/rlutil

void cTop();
void endOpt();
void saveOut(double, double, char[], char[]);

#define MAX_LINE 256

typedef struct
{
    double amount;
    char currType[8];
} currInput;

// Main function of this c file
int CalculateCurrency()
{
    char ch;
    char tmpU[MAX_LINE] = "https://free.currconv.com/api/v7/convert?q=";
    char url[MAX_LINE] = "";
    saveDefaultColor();
start:
    cTop();
    currInput currInput;
    double rate = 0, total = 0;
    char currType1[4] = "", currType2[4] = "";
    char time[20] = "";
    char date[20] = "";
    char CurrHisLoc[50] = "History/CurrencyCalculationHistory.txt";
    FILE *CurrHistory;
    CurrHistory = fopen(CurrHisLoc, "a+");
Input:
    setColor(LIGHTGREEN);
    printf(" Input: ");
    setColor(LIGHTBLUE);
    scanf("%lf %[^\n]", &currInput.amount, &currInput.currType);
    resetColor();

    // Input Validation Lv. 1
    if (strlen(currInput.currType) != 7)
    {
        wrongInput();
        goto Input;
    }

    // Input Validation Lv. 2
    if (currInput.currType[3] != '-')
    {
        wrongInput();
        goto Input;
    }

    strupr(strncpy(currType1, currInput.currType, 3));
    strupr(strcpy(currType2, &currInput.currType[4]));

    // Input Validation Lv. 3
    for (int i = 0; i < 3; i++)
    {
        if (!isalpha(currType1[i]) || !isalpha(currType2[i]))
        {
            wrongInput();
            goto Input;
        }
    }

    // Replacing '-' with '_' inside inputted currency type to match api url format.
    replace_char(currInput.currType, '-', '_');
    // creating api url according to user input
    sprintf(url, "%s%s&compact=ultra&apiKey=6cb174e127df4a1139f6", tmpU, currInput.currType);
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
        // Input Validation Lv. 4 (Final Level)
        wrongInput();
        goto Input;
    }
    total = (rate * currInput.amount);
    // Console Output
    printf(" Current Rate: 1 %s = %.4lf %s\n", currType1, rate, currType2);
    setColor(LIGHTCYAN);
    printf(" Total: %.02lf %s\n", (rate * currInput.amount), currType2);
    setColor(LIGHTGREEN);
    // Generating Time & Date
    currDate(date);
    currTime(time);
    // Capturing History
    fprintf(CurrHistory, "%s    %s    %.4lf    %s-%s    %.4lf    %.4lf\n", date, time, currInput.amount, currType1, currType2, rate, total);
    printf(" Calculation: %.4lf %s x %.4lf %s = %.02lf %s\n", currInput.amount, currType1, rate, currType2, total, currType2);
    resetColor();
    fclose(CurrHistory);
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
        return 0;
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
    sprintf(x, "Calculations/%.2lf_%s-%s_", amount, currType1, currType2);
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

void cTop()
{
    setColor(LIGHTRED);
    printf("\n                      ============================        \n");
    printf("                      ||   Currency Converter   ||        \n");
    printf("                      ============================        \n");
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