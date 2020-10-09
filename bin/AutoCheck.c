#include <stdio.h>
#include <time.h>
#include "headers/rlutil.h"

typedef struct
{
    char exc1[7];
    int round;
    long interval;
} AutoCheck;

void aTop();
int inputValidate(char[]);
void checkPrice(double, double, char[], char[], char[], char[]);
int vali4(AutoCheck, char[]);

void autoCheck()
{
    saveDefaultColor();
    aTop();
    AutoCheck info;
    char currType1[4] = "";
    char empty[4] = "";
    char currType2[4] = "";
    char time[20] = "";
    char date[20] = "";
    double nRate = 0;
    double oRate = 0;
    int c = 0;
    char AutoHisLoc[50] = "History/AutoCheckerHistory.txt";
    FILE *AutoHistory;
    char tmpAU[128] = "https://free.currconv.com/api/v7/convert?q=";
    char url[128] = "";
Input:
    printf("Exchange ID: ");
    scanf("%s", &info.exc1);
    if (inputValidate(info.exc1) == -1)
        goto Input;
    replace_char(info.exc1, '-', '_');

    printf("Rounds: ");
    scanf("%d", &info.round);
    printf("Interval (in Minutes): ");
    scanf("%ld", &info.interval);
    info.interval += info.interval * 60 * 1000;

    sprintf(url, "%s%s&compact=ultra&apiKey=6cb174e127df4a1139f6", tmpAU, info.exc1);

    printf("\n");
    printf("   Date         Time      Exchange ID     Exchange Rate\n");
    printf("  ------       ------    -------------   ---------------\n");

    if (vali4(info, url) == -2)
        goto Input;

    for (int i = 0; i < info.round; i++)
    {
        ifFolderNotExist("History");
        // Opening & closing file inside a loop
        // because interval could be long and
        // without closing file data won't save.
        AutoHistory = fopen(AutoHisLoc, "a+");
        fetchJson(url, "currencyRate.json");
        nRate = scanjson("currencyRate.json");
        strupr(strncpy(currType1, info.exc1, 3));
        strupr(strcpy(currType2, &info.exc1[4]));
        checkPrice(oRate, nRate, date, time, currType1, currType2);
        // Capturing History
        fprintf(AutoHistory, "%s    %s    %s-%s    %.4lf\n", date, time, currType1, currType2, nRate);
        // Interval
        if (i != info.round - 1)
            Sleep(info.interval);

        // Copying Old Rate
        for (int m = 0; m < 5; m++)
            oRate = nRate;
        fclose(AutoHistory);
    }
}

int inputValidate(char input[])
{ // Input Validation Lv. 1
    if (strlen(input) != 7)
    {
        wrongInput();
        return -1;
    }

    // Input Validation Lv. 2
    if (input[3] != '-')
    {
        wrongInput();
        return -1;
    }

    // Input Validation Lv. 3
    for (int i = 0, j = 4; i < 3; i++, j++)
    {
        if (!isalpha(input[i]) || !isalpha(input[j]))
        {
            wrongInput();
            return -1;
        }
    }
    return 0;
}

void checkPrice(double oRate, double nRate, char date[], char time[], char currType1[], char currType2[])
{
    currDate(date);
    currTime(time);
    if (oRate != 0 && nRate > oRate)
    {
        setColor(LIGHTGREEN);
        printf("%s    %s      %s-%s          %.4lf\n", date, time, currType1, currType2, nRate);
        system("IF EXIST \"bin\\sounds\\increase.wav\" powershell -c (New-Object Media.SoundPlayer \"bin\\sounds\\increase.wav\").PlaySync();");
        resetColor();
    }
    else if (nRate < oRate)
    {
        setColor(LIGHTRED);
        printf("%s    %s      %s-%s          %.4lf\n", date, time, currType1, currType2, nRate);
        system("IF EXIST \"bin\\sounds\\decrease.wav\" powershell -c (New-Object Media.SoundPlayer \"bin\\sounds\\decrease.wav\").PlaySync();");
        resetColor();
    }
    else
    {
        printf("%s    %s      %s-%s          %.4lf\n", date, time, currType1, currType2, nRate);
    }
}

int vali4(AutoCheck info, char url[])
{
    char currType1[4] = "";
    char currType2[4] = "";
    int nRate;
    fetchJson(url, "currencyRate.json");
    nRate = scanjson("currencyRate.json");
    strupr(strncpy(currType1, info.exc1, 3));
    strupr(strcpy(currType2, &info.exc1[4]));
    if (nRate == -2)
    {
        setColor(RED);
        printf("\n ERROR: INVALID INPUT AT 'Exchange ID: %s-%s'! PLEASE TRY AGAIN!\n\n", currType1, currType2);
        resetColor();
        return -2;
    }
    return 0;
}

void aTop()
{
    setColor(LIGHTRED);
    printf("\n                 ================================        \n");
    printf("                 ||   Automatic Rate Checker   ||        \n");
    printf("                 ================================       \n");
    setColor(LIGHTCYAN);
    printf("  ____________________________________________________________________\n");
    printf(" |                                                                    |\n");
    printf(" |                          INSTRUCTIONS                              |\n");
    printf(" |  Exchange ID: Which currency rate will be checked. (eg. USD-BDT)   |\n");
    printf(" |  Rounds: How many times currency rate will be checked.             |\n");
    printf(" |  Interval: How much wait before check again.                       |\n");
    printf(" |____________________________________________________________________|\n\n");
    resetColor();
}

void endOptAuto()
{
    printf("\n ===================================================== ");
    printf("\n ||    ");
    setColor(LIGHTMAGENTA);
    printf("[A]");
    setColor(YELLOW);
    printf(" Again     ");
    setColor(LIGHTMAGENTA);
    printf("[M]");
    setColor(YELLOW);
    printf(" Main Menu      ");
    setColor(LIGHTMAGENTA);
    printf("[X]");
    setColor(YELLOW);
    printf(" Exit    ");
    resetColor();
    printf("||\n =====================================================\n");
}