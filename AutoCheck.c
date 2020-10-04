#include <stdio.h>
#include <time.h>
#include "rlutil.h"
#include "CustomHeader.h"

int inputValidate(char[]);
void checkPrice(double, double, char[], char[], char[]);

typedef struct
{
    int num;
    char exc1[7];
    char exc2[7];
    char exc3[7];
    char exc4[7];
    char exc5[7];
    int round;
    long interval;
} AutoCheck;


int vali4(AutoCheck, char[]);

int main()
{
    AutoCheck info;
    char currType1[4] = "";
    char empty[4] = "";
    char currType2[4] = "";
    char time[128] = "";
    double nRate[5] = {0};
    double oRate[5] = {0};
    int c = 0;
    saveDefaultColor();
    char url[128] = "https://free.currconv.com/api/v7/convert?q=USD_BDT&compact=ultra&apiKey=6cb174e127df4a1139f6";
Start:
    printf("\n\nHow Many Exchange Rate Want to Auto Check? (MAX: 5)\n");
    printf("Input: ");
    scanf("%d", &info.num);
    for (int i = 1; i <= info.num; i++)
    {
    Input:
        printf("Exchange %d: ", i);
        switch (i)
        {
        case 1:
            scanf("%s", &info.exc1);
            if (inputValidate(info.exc1) == -1)
                goto Input;
            replace_char(info.exc1, '-', '_');
            break;
        case 2:
            scanf("%s", &info.exc2);
            if (inputValidate(info.exc2) == -1)
                goto Input;
            replace_char(info.exc2, '-', '_');
            break;
        case 3:
            scanf("%s", &info.exc3);
            if (inputValidate(info.exc3) == -1)
                goto Input;
            replace_char(info.exc3, '-', '_');
            break;
        case 4:
            scanf("%s", &info.exc4);
            if (inputValidate(info.exc4) == -1)
                goto Input;
            replace_char(info.exc4, '-', '_');
            break;
        case 5:
            scanf("%s", &info.exc5);
            if (inputValidate(info.exc5) == -1)
                goto Input;
            replace_char(info.exc5, '-', '_');
            break;
        }
    }

    printf("Rounds: ");
    scanf("%d", &info.round);
    printf("Interval (in Minutes): ");
    scanf("%ld", &info.interval);
    info.interval += info.interval * 60 * 1000;

    if (vali4(info, url) == -2)
        goto Start;
    
    for (int z = 0; z < info.round; z++)
    {
        switch (info.num)
        {
        case 5:
            c = 4;
            replace_url1(url, info.exc5);
            fetchJson(url, "currencyRate.json");
            nRate[c] = scanjson("currencyRate.json");
            strupr(strncpy(currType1, info.exc5, 3));
            strupr(strcpy(currType2, &info.exc5[4]));
            checkPrice(oRate[c], nRate[c], time, currType1, currType2);
            Sleep(1000);
        case 4:
            c = 3;
            replace_url1(url, info.exc4);
            fetchJson(url, "currencyRate.json");
            nRate[c] = scanjson("currencyRate.json");
            strupr(strncpy(currType1, info.exc4, 3));
            strupr(strcpy(currType2, &info.exc4[4]));
            checkPrice(oRate[c], nRate[c], time, currType1, currType2);
            Sleep(1000);
        case 3:
            c = 2;
            replace_url1(url, info.exc3);
            fetchJson(url, "currencyRate.json");
            nRate[c] = scanjson("currencyRate.json");
            strupr(strncpy(currType1, info.exc3, 3));
            strupr(strcpy(currType2, &info.exc3[4]));
            checkPrice(oRate[c], nRate[c], time, currType1, currType2);
            Sleep(1000);
        case 2:
            c = 1;
            replace_url1(url, info.exc2);
            fetchJson(url, "currencyRate.json");
            nRate[c] = scanjson("currencyRate.json");
            strupr(strncpy(currType1, info.exc2, 3));
            strupr(strcpy(currType2, &info.exc2[4]));
            checkPrice(oRate[c], nRate[c], time, currType1, currType2);
            Sleep(1000);
        case 1:
            c = 0;
            replace_url1(url, info.exc1);
            fetchJson(url, "currencyRate.json");
            nRate[c] = scanjson("currencyRate.json");
            strupr(strncpy(currType1, info.exc1, 3));
            strupr(strcpy(currType2, &info.exc1[4]));
            checkPrice(oRate[c], nRate[c], time, currType1, currType2);
            break;
        }

        // Interval
        Sleep(info.interval);

        // Copying Old Rate
        for (int m = 0; m < 5; m++)
            oRate[m] = nRate[m];
    }
    return 0;
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

void checkPrice(double oRate, double nRate, char time[], char currType1[], char currType2[])
{
    currTime(time);
    if (oRate != 0 && nRate > oRate)
    {
        setColor(LIGHTGREEN);
        printf("%s - %s-%s Price Increased!\n", time, currType1, currType2);
        printf("                      Old Rate: %.4lf\n", oRate);
        printf("                      New Rate: %.4lf\n", nRate);
        resetColor();
    }
    else if (nRate < oRate)
    {
        setColor(LIGHTRED);
        printf("%s - %s-%s Price Decreased!\n", time, currType1, currType2);
        printf("                      Old Rate: %.4lf\n", oRate);
        printf("                      New Rate: %.4lf\n", nRate);
        resetColor();
    }
    else
    {
        printf("%s - %s-%s %.4lf\n", time, currType1, currType2, nRate);
    }
}

int vali4(AutoCheck info, char url[])
{
    char currType1[4] = "";
    char currType2[4] = "";
    int nRate, c;
    
    switch (info.num)
    {
    case 5:
        c = 5;
        replace_url1(url, info.exc5);
        fetchJson(url, "currencyRate.json");
        nRate = scanjson("currencyRate.json");
        strupr(strncpy(currType1, info.exc5, 3));
        strupr(strcpy(currType2, &info.exc5[4]));
        if (nRate == -2)
        {
            setColor(RED);
            printf("\n ERROR: INVALID INPUT AT 'Exchange %d: %s-%s'! PLEASE TRY AGAIN!\n\n", c, currType1, currType2);
            resetColor();
            return -2;
        }
    case 4:
        c = 4;
        replace_url1(url, info.exc4);
        fetchJson(url, "currencyRate.json");
        nRate = scanjson("currencyRate.json");
        strupr(strncpy(currType1, info.exc4, 3));
        strupr(strcpy(currType2, &info.exc4[4]));
        if (nRate == -2)
        {
            setColor(RED);
            printf("\n ERROR: INVALID INPUT AT 'Exchange %d: %s-%s'! PLEASE TRY AGAIN!\n\n", c, currType1, currType2);
            resetColor();
            return -2;
        }
    case 3:
        c = 3;
        replace_url1(url, info.exc3);
        fetchJson(url, "currencyRate.json");
        nRate = scanjson("currencyRate.json");
        strupr(strncpy(currType1, info.exc3, 3));
        strupr(strcpy(currType2, &info.exc3[4]));
        if (nRate == -2)
        {
            setColor(RED);
            printf("\n ERROR: INVALID INPUT AT 'Exchange %d: %s-%s'! PLEASE TRY AGAIN!\n\n", c, currType1, currType2);
            resetColor();
            return -2;
        }
    case 2:
        c = 2;
        replace_url1(url, info.exc2);
        fetchJson(url, "currencyRate.json");
        nRate = scanjson("currencyRate.json");
        strupr(strncpy(currType1, info.exc2, 3));
        strupr(strcpy(currType2, &info.exc2[4]));
        if (nRate == -2)
        {
            setColor(RED);
            printf("\n ERROR: INVALID INPUT AT 'Exchange %d: %s-%s'! PLEASE TRY AGAIN!\n\n", c, currType1, currType2);
            resetColor();
            return -2;
        }
    case 1:
        c = 1;
        replace_url1(url, info.exc1);
        fetchJson(url, "currencyRate.json");
        nRate = scanjson("currencyRate.json");
        strupr(strncpy(currType1, info.exc1, 3));
        strupr(strcpy(currType2, &info.exc1[4]));
        if (nRate == -2)
        {
            setColor(RED);
            printf("\n ERROR: INVALID INPUT AT 'Exchange %d: %s-%s'! PLEASE TRY AGAIN!\n\n", c, currType1, currType2);
            resetColor();
            return -2;
        }
        break;
    }
    return 0;
}