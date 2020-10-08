#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "rlutil.h"
#include "CustomHeader.h"

void sevenDaysRateLive();
void checkSpecificDayRate();
void checkHistoryLiveMainMenu();
void sevenDaysLiveTop();
void myHistoryTop();

void main()
{
    char SDRch;
    saveDefaultColor();
    checkHistoryLiveMainMenu();
SDRch:
    setColor(LIGHTGREEN);
    printf("\n     --> Input Option: ");
    resetColor();
    SDRch = getch();
    tolower(SDRch);
    if (SDRch == '1')
    {
        cls();
        sevenDaysRateLive();
    }
    else if (SDRch == '2')
    {
        cls();
        void checkSpecificDayRate();
    }
    else if (SDRch == 'm')
    {
        cls();
    }
    else if (SDRch == 'x')
    {
        exit(0);
    }
    else
    {
        wrongInput();
        goto SDRch;
    }
}

void sevenDaysRateLive()
{
    sevenDaysLiveTop();
    FILE *sevenHistoryFile;
    oneDayRate sevenDays[7];
    int errorCode;
    char tmp[128] = "https://free.currconv.com/api/v7/convert?apiKey=6cb174e127df4a1139f6&q=";
    char url[128] = "";
    char nDate[15] = "";
    char oDate[15] = "";
    char exID[8] = "";
    char sevenHistoryJSON[128] = "sevenDaysHistory.json";
    char sevenHistoryData[1024] = "";
sevenDaysEXID:
    printf(" Exchange ID: ");
    scanf("%s", &exID);
    errorCode = inputValidation(exID);
    if (errorCode == -1)
        goto sevenDaysEXID;

    replace_char(exID, '-', '_');
    previousDate(nDate, 8);
    previousDate(oDate, 1);
    sprintf(url, "%s%s&compact=ultra&date=%s&endDate=%s", tmp, exID, nDate, oDate);
    fetchJson(url, sevenHistoryJSON);
    errorCode = inputValidationLv4(sevenHistoryJSON);
    // Input Validation Lv. 4 (Final Level)
    if (errorCode == -1)
    {
        setColor(RED);
        printf("\n ERROR: Failed To Fetch API!\n");
        resetColor();
        exit(0);
    }
    else if (errorCode == -2)
    {
        wrongInput();
        goto sevenDaysEXID;
    }
    sevenHistoryFile = fopen(sevenHistoryJSON, "r");
    fscanf(sevenHistoryFile, "%s", &sevenHistoryData);
    fclose(sevenHistoryFile);
    for (int i = 0; i < 7; i++)
    {
        previousDate(sevenDays[i].date, i + 1);
        sevenDays[i].rate = specificDateRate(exID, sevenDays[i].date, sevenHistoryData);
    }
    for (int i = 0; i < 7; i++)
    {
        printf("%s  -  %.4lf\n", sevenDays[i].date, sevenDays[i].rate);
    }
}

void checkSpecificDayRate()
{
    // Waiting for json format. api server is down...
}

void checkHistoryLiveMainMenu()
{
    setColor(LIGHTCYAN);
    printf("     ___________________________________________\n");
    printf("    |                                           |\n");
    setColor(LIGHTCYAN);
    printf("    |");
    resetColor();
    printf("       1. Last 7 Days Rate");
    setColor(LIGHTCYAN);
    printf("                 |\n");
    printf("    |");
    resetColor();
    printf("       2. Check Specific Day Rate");
    setColor(LIGHTCYAN);
    printf("          |\n");
    printf("    |");
    resetColor();
    printf("       3. Currency Rate History Live");
    setColor(LIGHTCYAN);
    printf("       |\n");
    printf("    |");
    resetColor();
    printf("       M. Main Manu");
    setColor(LIGHTCYAN);
    printf("                        |\n");
    printf("    |");
    resetColor();
    printf("       X. Exit");
    setColor(LIGHTCYAN);
    printf("                             |\n");
    printf("    |___________________________________________|\n");
    resetColor();
}

void sevenDaysLiveTop()
{
    setColor(LIGHTRED);
    printf("\n                 ================================        \n");
    printf("                 ||   Last 7 Days Rate (Live)   ||        \n");
    printf("                 ================================       \n");
    setColor(LIGHTCYAN);
    printf("  ____________________________________________________________________\n");
    printf(" |                                                                    |\n");
    printf(" |                          INSTRUCTIONS                              |\n");
    printf(" |  Exchange ID: Which currency rate will be checked. (eg. USD-BDT)   |\n");
    printf(" |____________________________________________________________________|\n\n");
    resetColor();
}

void myHistoryTop()
{
    setColor(LIGHTRED);
    printf("\n               =======================================        \n");
    printf("               ||   Check Specific Day Rate (Live)   ||        \n");
    printf("               ========================================       \n");
    setColor(LIGHTCYAN);
    printf("  ____________________________________________________________________\n");
    printf(" |                                                                    |\n");
    printf(" |                          INSTRUCTIONS                              |\n");
    printf(" |  Exchange ID: Which currency rate will be checked. (eg. USD-BDT)   |\n");
    printf(" |  Date: Which day's rate will be checked. (eg. 2020-10-06)          |\n");
    printf(" |____________________________________________________________________|\n\n");
    resetColor();
}