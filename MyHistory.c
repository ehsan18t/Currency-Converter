#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "rlutil.h"
#include "CustomHeader.h"

void myHistoryMainMenu();
void myHistoryTop();
void currencyConversionHistory();
void autoRateCheckingHistory();
void bestConversionPrice();
void bestAutoRate();

int main()
{
    char ch;
    saveDefaultColor();
myHistoryMainMenu:
    cls();
    myHistoryTop();
    myHistoryMainMenu();
    setColor(LIGHTGREEN);
    printf("\n     --> Input Option: ");
    resetColor();
    ch = getch();
    tolower(ch);
    if (ch == '1')
    {
        cls();
        hidecursor();
        currencyConversionHistory();
        showcursor();
    }
    else if (ch == '2')
    {
        cls();
        hidecursor();
        autoRateCheckingHistory();
        showcursor();
    }
    else if (ch == '3')
    {
        cls();
        hidecursor();
        bestConversionPrice();
        showcursor();
    }
    else if (ch == '4')
    {
        cls();
        hidecursor();
        bestAutoRate();
        showcursor();
    }
    else if (ch == 'm')
    {
        return 0;
    }
    else if (ch == 'x')
    {
        exit(0);
    }
    else
    {
        wrongInput();
        goto myHistoryMainMenu;
    } 
    return 0;
}

void myHistoryMainMenu()
{
    setColor(LIGHTCYAN);
    printf("  ______________________________________________________\n");
    printf(" |                                                      |\n");
    setColor(LIGHTCYAN);
    printf(" |");
    resetColor();
    printf("    1. Currency Conversion History");
    setColor(LIGHTCYAN);
    printf("                    |\n");
    printf(" |");
    resetColor();
    printf("    2. Automatic Rate Checking History");
    setColor(LIGHTCYAN);
    printf("                |\n");
    printf(" |");
    resetColor();
    printf("    3. Best Price from Conversion History");
    setColor(LIGHTCYAN);
    printf("             |\n");
    printf(" |");
    resetColor();
    printf("    4. Best Prices from Auto Rate Checking History");
    setColor(LIGHTCYAN);
    printf("    |\n");
    printf(" |");
    resetColor();
    printf("    M. Main Manu");
    setColor(LIGHTCYAN);
    printf("                                      |\n");
    printf(" |");
    resetColor();
    printf("    X. Exit");
    setColor(LIGHTCYAN);
    printf("                                           |\n");
    printf(" |______________________________________________________|\n");
    resetColor();
}

void myHistoryTop()
{
    setColor(LIGHTRED);
    printf("\n                 ====================        \n");
    printf("                 ||   My History   ||        \n");
    printf("                 ====================       \n");
    resetColor();
}

void currencyConversionHistory()
{
    setColor(LIGHTRED);
    printf("\n                   =====================================        \n");
    printf("                   ||   Currency Conversion History   ||        \n");
    printf("                   =====================================       \n");
    resetColor();
    FILE *currConvHistory;
    history data;
    char currConveHistoryLocation[128] = "History/CurrencyCalculationHistory.txt";
    currConvHistory = fopen(currConveHistoryLocation, "r");
    if (currConvHistory == NULL)
    {
        printf("Error!\n");
        exit(0);
    }

    printf("\n");
    printf("   Date         Time       Amount      Exchange ID     Exchange Rate      Total\n");
    printf("  ------       ------    ----------   -------------   ---------------    --------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %lf %s %lf %lf", &data.date, &data.time, &data.amount, &data.type, &data.rate, &data.total);
        printf("%s    %s     %.4lf        %s          %.4lf        %.4lf\n", data.date, data.time, data.amount, data.type, data.rate, data.total);
    }
    fclose(currConvHistory);
}

void autoRateCheckingHistory()
{
    setColor(LIGHTRED);
    printf("\n       =========================================        \n");
    printf("       ||   Automatic Rate Checking History   ||        \n");
    printf("       =========================================       \n");
    resetColor();
    FILE *currConvHistory;
    history data;
    char currConveHistoryLocation[128] = "History/AutoCheckerHistory.txt";
    currConvHistory = fopen(currConveHistoryLocation, "r");
    if (currConvHistory == NULL)
    {
        printf("Error!\n");
        exit(0);
    }

    printf("\n");
    printf("   Date         Time      Exchange ID     Exchange Rate\n");
    printf("  ------       ------    -------------   ---------------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %s %lf", &data.date, &data.time, &data.type, &data.rate);
        printf("%s    %s      %s          %.4lf\n", data.date, data.time, data.type, data.rate);
    }
    fclose(currConvHistory);
}

void bestConversionPrice()
{
    setColor(LIGHTRED);
    printf("\n                ============================================        \n");
    printf("                ||   Best Price From Conversion History   ||        \n");
    printf("                ============================================       \n");
    resetColor();
    int i = 0, flag = -1;
    FILE *currConvHistory;
    history data;
    // 20 different types exchange's highest price can be displayed
    history highest[20] = {"", "", "", 0, 0, 0};
    char currConveHistoryLocation[128] = "History/CurrencyCalculationHistory.txt";
    currConvHistory = fopen(currConveHistoryLocation, "r");
    if (currConvHistory == NULL)
    {
        printf("Error!\n");
        exit(0);
    }

    printf("\n");
    printf("   Date         Time       Amount      Exchange ID     Exchange Rate      Total\n");
    printf("  ------       ------    ----------   -------------   ---------------    --------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %lf %s %lf %lf", &data.date, &data.time, &data.amount, &data.type, &data.rate, &data.total);
        if (strcmp(data.type, highest[i].type) != 0)
        {
            flag = 0;
            for (int j = 0; j <= i; j++)
            {
                if (strcmp(data.type, highest[j].type) == 0)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0)
        {
            flag = -1;
            strcpy(highest[i].type, data.type);
            strcpy(highest[i].date, data.date);
            strcpy(highest[i].time, data.time);
            highest[i].amount = data.amount;
            highest[i].rate = data.rate;
            highest[i].total = data.total;
            i++;
        }
    }
    fclose(currConvHistory);
    for (int j = 0; j < i; j++)
    {
        printf("%s    %s     %.4lf        %s          %.4lf        %.4lf\n", highest[j].date, highest[j].time, highest[j].amount, highest[j].type, highest[j].rate, highest[j].total);
    }
}

void bestAutoRate()
{
    setColor(LIGHTRED);
    printf("\n    ================================================        \n");
    printf("    ||   Best Auto Rate Checking History Prices   ||        \n");
    printf("    ================================================       \n");
    resetColor();
    int i = 0, flag = -1;
    FILE *currConvHistory;
    history data;
    // 20 different types exchange's highest price can be displayed
    history highest[20] = {"", "", "", 0, 0, 0};
    char currConveHistoryLocation[128] = "History/AutoCheckerHistory.txt";
    currConvHistory = fopen(currConveHistoryLocation, "r");
    if (currConvHistory == NULL)
    {
        printf("Error!\n");
        exit(0);
    }

    printf("\n");
    printf("   Date         Time      Exchange ID     Exchange Rate\n");
    printf("  ------       ------    -------------   ---------------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %s %lf", &data.date, &data.time, &data.type, &data.rate);
        if (strcmp(data.type, highest[i].type) != 0)
        {
            flag = 0;
            for (int j = 0; j <= i; j++)
            {
                if (strcmp(data.type, highest[j].type) == 0)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0)
        {
            flag = -1;
            strcpy(highest[i].type, data.type);
            strcpy(highest[i].date, data.date);
            strcpy(highest[i].time, data.time);
            highest[i].rate = data.rate;
            i++;
        }
    }
    fclose(currConvHistory);
    for (int j = 0; j < i; j++)
    {
        printf("%s    %s      %s          %.4lf\n", highest[j].date, highest[j].time, highest[j].type, highest[j].rate);
    }
}
