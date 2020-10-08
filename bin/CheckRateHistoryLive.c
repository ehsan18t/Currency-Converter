#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "headers/rlutil.h"
#include "headers/CustomHeader.h"

void sevenDaysRateLive(int *);
void checkSpecificDayRate();
void checkHistoryLiveMainMenu();
void sevenDaysLiveTop();
void specDayTop();
void liveHistoryMainTop();

int main()
{
    char ch, ch2;
    int opt;
    saveDefaultColor();
SDRMenu:
    cls();
    liveHistoryMainTop();
    checkHistoryLiveMainMenu();
SDRch:
    setColor(LIGHTGREEN);
    printf("\n     --> Input Option: ");
    resetColor();
    ch = getch();
    tolower(ch);
    if (ch == '1')
    {
        cls();
        sevenDaysRateLive(&opt);
        if (opt == 1)
            goto SDRMenu;
        else if (opt == 2)
            return 0;
    }
    else if (ch == '2')
    {
        cls();
        void checkSpecificDayRate();
    }
    else if (ch == 'm')
    {
        cls();
    }
    else if (ch == 'x')
    {
        exit(0);
    }
    else
    {
        wrongInput();
        goto SDRch;
    }
}

void sevenDaysRateLive(int *opt)
{
    sevenDaysLiveTop();
    FILE *sevenHistoryFile;
    oneDayRate sevenDays[7];
    oneDayRate highest = {"", 0};
    int errorCode;
    char ch2;
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
        if (sevenDays[i].rate > highest.rate)
            highest = sevenDays[i];
    }
    hidecursor();
//
// Options print function here
//
askOpt:
    ch2 = getch();
    tolower(ch2);
    if (ch2 == 'c')
    {
        showcursor();
        *opt = 1;
    }
    else if (ch2 == 'm')
    {
        showcursor();
        *opt = 2;
    }
    else if (ch2 == 'h')
    {
        cls();
        printf("%s  -  %.4lf\n", highest.date, highest.rate);
        goto askOpt;
    }
    else if (ch2 == 'x')
    {
        showcursor();
        exit(0);
    }
    else
    {
        wrongInput();
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

void specDayTop()
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

void liveHistoryMainTop()
{
    setColor(LIGHTRED);
    printf("\n      =======================================        \n");
    printf("      ||   Currrency Rate History (Live)   ||        \n");
    printf("      =======================================       \n");
    setColor(LIGHTCYAN);
    resetColor();
}