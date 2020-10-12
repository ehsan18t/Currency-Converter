#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "headers/rlutil.h"

typedef struct
{
    char date[12];
} myDate;

// Global variable declare
myDate sevenDate[7] = {""};

void myHistoryMainMenu();
void myHistoryTop();
void currencyConversionHistory();
void autoRateCheckingHistory();
void currencyConversionHistory7D();
void autoRateCheckingHistory7D();
void bestConversionPrice();
void bestConversionPrice7D();
void bestAutoRate();
void bestAutoRate7D();
void myHistoryEndOpt();
void myHistoryEndOpt2();

//
// Main Function
//
int myHistory()
{
    char ch, ch2;
    // Adding Last 7 Dates to the array
    for (int i = 0; i < 7; i++)
        previousDate(sevenDate[i].date, i);
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
        myHistoryEndOpt2();
    opt1:
        ch2 = getch();
        tolower(ch2);
        if (ch2 == 'b')
        {
            showcursor();
            goto myHistoryMainMenu;
        }
        else if (ch2 == 'h')
        {
            cls();
            bestConversionPrice();
            myHistoryEndOpt();
            hidecursor();
            goto opt1;
        }
        else if (ch2 == 'm')
        {
            showcursor();
            return 0;
        }
        else if (ch2 == 'x')
        {
            showcursor();
            exit(0);
        }
        else
        {
            wrongInput();
            goto opt1;
        }
    }
    else if (ch == '2')
    {
        cls();
        hidecursor();
        autoRateCheckingHistory();
        myHistoryEndOpt2();
    opt2:
        ch2 = getch();
        tolower(ch2);
        if (ch2 == 'b')
        {
            showcursor();
            goto myHistoryMainMenu;
        }
        else if (ch2 == 'h')
        {
            cls();
            bestAutoRate();
            myHistoryEndOpt();
            hidecursor();
            goto opt2;
        }
        else if (ch2 == 'm')
        {
            showcursor();
            return 0;
        }
        else if (ch2 == 'x')
        {
            showcursor();
            exit(0);
        }
        else
        {
            wrongInput();
            goto opt2;
        }
    }
    else if (ch == '3')
    {
        cls();
        hidecursor();
        currencyConversionHistory7D();
        myHistoryEndOpt2();
    opt3:
        ch2 = getch();
        tolower(ch2);
        if (ch2 == 'b')
        {
            showcursor();
            goto myHistoryMainMenu;
        }
        else if (ch2 == 'h')
        {
            cls();
            bestConversionPrice7D();
            myHistoryEndOpt();
            hidecursor();
            goto opt3;
        }
        else if (ch2 == 'm')
        {
            showcursor();
            return 0;
        }
        else if (ch2 == 'x')
        {
            showcursor();
            exit(0);
        }
        else
        {
            wrongInput();
            goto opt3;
        }
    }
    else if (ch == '4')
    {
        cls();
        hidecursor();
        autoRateCheckingHistory7D();
        myHistoryEndOpt2();
    opt4:
        ch2 = getch();
        tolower(ch2);
        if (ch2 == 'b')
        {
            showcursor();
            goto myHistoryMainMenu;
        }
        else if (ch2 == 'h')
        {
            cls();
            bestAutoRate7D();
            myHistoryEndOpt();
            hidecursor();
            goto opt4;
        }
        else if (ch2 == 'm')
        {
            showcursor();
            return 0;
        }
        else if (ch2 == 'x')
        {
            showcursor();
            exit(0);
        }
        else
        {
            wrongInput();
            goto opt4;
        }
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

//
// Major Functions
//

void currencyConversionHistory()
{
    setColor(LIGHTRED);
    printf("\n                    =====================================        \n");
    printf("                    ||   Currency Conversion History   ||        \n");
    printf("                    =====================================       \n");
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
    printf("    Date         Time       Amount      Exchange ID     Exchange Rate      Total\n");
    printf("   ------       ------    ----------   -------------   ---------------    --------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %lf %s %lf %lf", &data.date, &data.time, &data.amount, &data.type, &data.rate, &data.total);
        printf(" %s    %s     %.4lf        %s          %.4lf        %.4lf\n", data.date, data.time, data.amount, data.type, data.rate, data.total);
    }
    fclose(currConvHistory);
}

void autoRateCheckingHistory()
{
    setColor(LIGHTRED);
    printf("\n        =========================================        \n");
    printf("        ||   Automatic Rate Checking History   ||        \n");
    printf("        =========================================       \n");
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
    printf("    Date         Time      Exchange ID     Exchange Rate\n");
    printf("   ------       ------    -------------   ---------------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %s %lf", &data.date, &data.time, &data.type, &data.rate);
        printf(" %s    %s      %s          %.4lf\n", data.date, data.time, data.type, data.rate);
    }
    fclose(currConvHistory);
}

void currencyConversionHistory7D()
{
    setColor(LIGHTRED);
    printf("\n                ==============================================        \n");
    printf("                ||   Currency Conversion History (7 DAYS)   ||        \n");
    printf("                ==============================================       \n");
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
    printf("    Date         Time       Amount      Exchange ID     Exchange Rate      Total\n");
    printf("   ------       ------    ----------   -------------   ---------------    --------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %lf %s %lf %lf", &data.date, &data.time, &data.amount, &data.type, &data.rate, &data.total);
        for (int i = 0; i < 7; i++)
        {
            if (strcmp(sevenDate[i].date, data.date) == 0)
            {
                printf(" %s    %s     %.4lf        %s          %.4lf        %.4lf\n", data.date, data.time, data.amount, data.type, data.rate, data.total);
            }
        }
    }
    fclose(currConvHistory);
}

void autoRateCheckingHistory7D()
{
    setColor(LIGHTRED);
    printf("\n    ==================================================        \n");
    printf("    ||   Automatic Rate Checking History (7 DAYS)   ||        \n");
    printf("    ==================================================       \n");
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
    printf("    Date         Time      Exchange ID     Exchange Rate\n");
    printf("   ------       ------    -------------   ---------------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %s %lf", &data.date, &data.time, &data.type, &data.rate);
        for (int i = 0; i < 7; i++)
        {
            if (strcmp(sevenDate[i].date, data.date) == 0)
            {
                printf(" %s    %s      %s          %.4lf\n", data.date, data.time, data.type, data.rate);
            }
        }
    }
    fclose(currConvHistory);
}

void bestConversionPrice()
{
    setColor(LIGHTRED);
    printf("\n                 ============================================        \n");
    printf("                 ||   Best Price From Conversion History   ||        \n");
    printf("                 ============================================       \n");
    resetColor();
    int i = 0, flag = -1;
    FILE *currConvHistory;
    history data;
    // 100 different types exchange's highest price can be displayed
    history highest[100] = {"", "", "", 0, 0, 0};
    char currConveHistoryLocation[128] = "History/CurrencyCalculationHistory.txt";
    currConvHistory = fopen(currConveHistoryLocation, "r");
    if (currConvHistory == NULL)
    {
        printf("Error!\n");
        exit(0);
    }

    printf("\n");
    printf("    Date         Time       Amount      Exchange ID     Exchange Rate      Total\n");
    printf("   ------       ------    ----------   -------------   ---------------    --------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %lf %s %lf %lf", &data.date, &data.time, &data.amount, &data.type, &data.rate, &data.total);
        // Checking if exchange id (eg. USD-BDT) same or not if same
        // checking for higher rate.
        // 'i' is the array number
        if (strcmp(data.type, highest[i].type) == 0)
        {
            if (data.rate > highest[i].rate)
            {
                highest[i] = data;
                i++;
            }
        }
        else
        {
            // flag = 0 means, this data is not present in array.
            // So it will be added.
            flag = 0;
            // with this for loop we are checikng the whole array
            // for duplicate exchange id. If available checking for
            // higher rate.
            // If found any duplicate flag will be 1.
            for (int j = 0; j <= i; j++)
            {
                if (strcmp(data.type, highest[j].type) == 0)
                {
                    if (data.rate > highest[j].rate)
                        highest[j] = data;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                flag = -1;
                highest[i] = data;
                i++;
            }
        }
    }
    fclose(currConvHistory);
    for (int j = 0; j < i; j++)
    {
        printf(" %s    %s     %.4lf        %s          %.4lf        %.4lf\n", highest[j].date, highest[j].time, highest[j].amount, highest[j].type, highest[j].rate, highest[j].total);
    }
}
// All 'best prices' are being generated by same mechanism
void bestConversionPrice7D()
{
    setColor(LIGHTRED);
    printf("\n             =====================================================        \n");
    printf("             ||   Best Price From Conversion History (7 DAYS)   ||        \n");
    printf("             =====================================================       \n");
    resetColor();
    int i = 0, flag = -1, flag2;
    FILE *currConvHistory;
    history data;
    // 100 different types exchange's highest price can be displayed
    history highest[100] = {"", "", "", 0, 0, 0};
    char currConveHistoryLocation[128] = "History/CurrencyCalculationHistory.txt";
    currConvHistory = fopen(currConveHistoryLocation, "r");
    if (currConvHistory == NULL)
    {
        printf("Error!\n");
        exit(0);
    }

    printf("\n");
    printf("    Date         Time       Amount      Exchange ID     Exchange Rate      Total\n");
    printf("   ------       ------    ----------   -------------   ---------------    --------\n");
    while (!feof(currConvHistory))
    {
        flag2 = 0;
        fscanf(currConvHistory, "%s %s %lf %s %lf %lf", &data.date, &data.time, &data.amount, &data.type, &data.rate, &data.total);
        for (int k = 0; k < 7; k++)
        {
            if (strcmp(sevenDate[k].date, data.date) == 0)
            {
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 1)
        {
            if (strcmp(data.type, highest[i].type) == 0)
            {
                if (data.rate > highest[i].rate)
                {
                    highest[i] = data;
                    i++;
                }
            }
            else
            {
                flag = 0;
                for (int j = 0; j <= i; j++)
                {
                    if (strcmp(data.type, highest[j].type) == 0)
                    {
                        if (data.rate > highest[j].rate)
                            highest[j] = data;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    flag = -1;
                    highest[i] = data;
                    i++;
                }
            }
        }
    }
    fclose(currConvHistory);
    for (int j = 0; j < i; j++)
    {
        printf(" %s    %s     %.4lf        %s          %.4lf        %.4lf\n", highest[j].date, highest[j].time, highest[j].amount, highest[j].type, highest[j].rate, highest[j].total);
    }
}

void bestAutoRate()
{
    setColor(LIGHTRED);
    printf("\n     ====================================================        \n");
    printf("     ||   Best Price From Auto Rate Checking History   ||        \n");
    printf("     ====================================================       \n");
    resetColor();
    int i = 0, flag = -1;
    FILE *currConvHistory;
    history data;
    // 100 different types exchange's highest price can be displayed
    history highest[100] = {"", "", "", 0, 0, 0};
    char currConveHistoryLocation[128] = "History/AutoCheckerHistory.txt";
    currConvHistory = fopen(currConveHistoryLocation, "r");
    if (currConvHistory == NULL)
    {
        printf("Error!\n");
        exit(0);
    }

    printf("\n");
    printf("    Date         Time      Exchange ID     Exchange Rate\n");
    printf("   ------       ------    -------------   ---------------\n");
    while (!feof(currConvHistory))
    {
        fscanf(currConvHistory, "%s %s %s %lf", &data.date, &data.time, &data.type, &data.rate);
        if (strcmp(data.type, highest[i].type) == 0)
        {
            if (data.rate > highest[i].rate)
            {
                highest[i] = data;
                i++;
            }
        }
        else
        {
            flag = 0;
            for (int j = 0; j <= i; j++)
            {
                if (strcmp(data.type, highest[j].type) == 0)
                {
                    if (data.rate > highest[j].rate)
                        highest[j] = data;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                flag = -1;
                highest[i] = data;
                i++;
            }
        }
    }
    fclose(currConvHistory);
    for (int j = 0; j < i; j++)
    {
        printf(" %s    %s      %s          %.4lf\n", highest[j].date, highest[j].time, highest[j].type, highest[j].rate);
    }
}

void bestAutoRate7D()
{
    setColor(LIGHTRED);
    printf("\n =============================================================        \n");
    printf(" ||   Best Price From Auto Rate Checking History (7 DAYS)   ||        \n");
    printf(" =============================================================       \n");
    resetColor();
    int i = 0, flag = -1, flag2;
    FILE *currConvHistory;
    history data;
    // 100 different types exchange's highest price can be displayed
    history highest[100] = {"", "", "", 0, 0, 0};
    char currConveHistoryLocation[128] = "History/AutoCheckerHistory.txt";
    currConvHistory = fopen(currConveHistoryLocation, "r");
    if (currConvHistory == NULL)
    {
        printf("Error!\n");
        exit(0);
    }

    printf("\n");
    printf("    Date         Time      Exchange ID     Exchange Rate\n");
    printf("   ------       ------    -------------   ---------------\n");
    while (!feof(currConvHistory))
    {
        flag2 = 0;
        fscanf(currConvHistory, "%s %s %s %lf", &data.date, &data.time, &data.type, &data.rate);
        for (int k = 0; k < 7; k++)
        {
            if (strcmp(sevenDate[k].date, data.date) == 0)
            {
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 1)
        {
            if (strcmp(data.type, highest[i].type) == 0)
            {
                if (data.rate > highest[i].rate)
                {
                    highest[i] = data;
                    i++;
                }
            }
            else
            {
                flag = 0;
                for (int j = 0; j <= i; j++)
                {
                    if (strcmp(data.type, highest[j].type) == 0)
                    {
                        if (data.rate > highest[j].rate)
                            highest[j] = data;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    flag = -1;
                    highest[i] = data;
                    i++;
                }
            }
        }
    }
    fclose(currConvHistory);
    for (int j = 0; j < i; j++)
    {
        printf(" %s    %s      %s          %.4lf\n", highest[j].date, highest[j].time, highest[j].type, highest[j].rate);
    }
}

//
// Decoration Functions
//

// Headers UI
void myHistoryTop()
{
    setColor(LIGHTRED);
    printf("\n                 ====================        \n");
    printf("                 ||   My History   ||        \n");
    printf("                 ====================       \n");
    resetColor();
}

// Footer Options UI
void myHistoryEndOpt()
{
    printf("\n ====================================================");
    printf("\n ||    ");
    setColor(LIGHTMAGENTA);
    printf("[B]");
    setColor(YELLOW);
    printf(" Back     ");
    setColor(LIGHTMAGENTA);
    printf("[M]");
    setColor(YELLOW);
    printf(" Main Menu      ");
    setColor(LIGHTMAGENTA);
    printf("[X]");
    setColor(YELLOW);
    printf(" Exit    ");
    resetColor();
    printf("||\n ====================================================\n");
}

void myHistoryEndOpt2()
{
    printf("\n ===================================================================");
    printf("\n ||   ");
    setColor(LIGHTMAGENTA);
    printf("[B]");
    setColor(YELLOW);
    printf(" Back    ");
    setColor(LIGHTMAGENTA);
    printf("[H]");
    setColor(YELLOW);
    printf(" Highest Rate    ");
    setColor(LIGHTMAGENTA);
    printf("[M]");
    setColor(YELLOW);
    printf(" Main Menu     ");
    setColor(LIGHTMAGENTA);
    printf("[X]");
    setColor(YELLOW);
    printf(" Exit  ");
    resetColor();
    printf("||\n ===================================================================\n");
}

// Main Menu UI
void myHistoryMainMenu()
{
    setColor(LIGHTCYAN);
    printf("  ______________________________________________________\n");
    printf(" |                                                      |\n");
    setColor(LIGHTCYAN);
    printf(" |");
    resetColor();
    printf("    1. Currency Conversion History (FULL)");
    setColor(LIGHTCYAN);
    printf("             |\n");
    printf(" |");
    resetColor();
    printf("    2. Automatic Rate Checking History (FULL)");
    setColor(LIGHTCYAN);
    printf("         |\n");
    printf(" |");
    resetColor();
    printf("    3. Currency Conversion History (7 DAYS)");
    setColor(LIGHTCYAN);
    printf("           |\n");
    printf(" |");
    resetColor();
    printf("    4. Automatic Rate Checking History (7 DAYS)");
    setColor(LIGHTCYAN);
    printf("       |\n");
    printf(" |");
    resetColor();
    printf("    M. Main Menu");
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
