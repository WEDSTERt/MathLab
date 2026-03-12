#define _USE_MATH_DEFINES
#include "stdio.h"
#include <stdlib.h>
#include <math.h>

typedef struct {
    double sum;     
    double error;   
} DoublErr;

typedef struct{
    double x;
    int ValElTel;
    double (*MathFunc) (double (*)(double*, int), int, double);
    double (*ResFunc) (double*, int);
} ValAFunc;



double PrSum(double* ArrTel, int N) {
    double t = 0;
    for (int i = 0; i < N; i++) t += ArrTel[i];
    return t;
}

double RevSum(double* ArrTel, int N) {
    double t = 0;
    for (int i = N-1; i >= 0; i--) t += ArrTel[i];
    return t;
}

double SlSum(double* ArrTel, int N) {
    DoublErr Res;
    Res.error = 0.0;
    Res.sum = 0.0;
    double d1, d2, error1, error2, s;
    for (int i = 0; i < N; i++) {
        double k = ArrTel[i];
        s = Res.sum;
        Res.sum = k + s;
        d1 = Res.sum - s;
        d2 = Res.sum - d1;
        error1 = k - d1;
        error2 = s - d2;
        Res.error = Res.error + error1 + error2;
    }
    return Res.sum + Res.error;
}


double Sin(double (*ResFunc)(double*, int), int N, double x) {
    x = fmod(x, 2 * M_PI);
    if (x > M_PI) x = x - 2 * M_PI;
    if (x < -M_PI) x = x + 2 * M_PI;
    double res = 0, ElTel = x, k;
    double* ArrTel = malloc(N * sizeof(double));
    if (ArrTel) {
        ArrTel[0] = ElTel;
        for (int i = 1; i < N; i ++) {
            k = (-1) * (x * x) / ((2 * (i)) * (2 * i + 1));
            ElTel = ElTel * k;
            ArrTel[i] = ElTel;
        }
        res = ResFunc(ArrTel, N);
    }
    free(ArrTel);
    return res;
}

double Cos(double (*ResFunc)(double*, int), int N, double x) {
    x = fmod(x, 2 * M_PI);
    if (x > M_PI) x = x - 2 * M_PI;
    if (x < -M_PI) x = x + 2 * M_PI;
    double ElTel = 1, k, res = 0;
    double* ArrTel = malloc(N * sizeof(double));
    if (ArrTel) {
        ArrTel[0] = ElTel;
        for (int i = 1; i < N ; i ++) {
            k = (x / (2 * i - 1)) * (x / (2 * i)) * (-1);
            ElTel = ElTel * k;
            ArrTel[i] = ElTel;
        }
        res = ResFunc(ArrTel, N);
        
    }
    free(ArrTel);
    return res;
}

double Exp(double (*ResFunc)(double*, int), int N, double x) {
    double ElTel = 1, k, res = 0;
    double* ArrTel = malloc(N * sizeof(double));
    if (ArrTel) {
        ArrTel[0] = ElTel;
        for (int i = 1; i < N; i++) {
            k = (x / (i));
            ElTel = ElTel * k;
            ArrTel[i] = ElTel;
        }
        res = ResFunc(ArrTel, N);

    }
    free(ArrTel);
    return res;
}

double NLog(double (*ResFunc)(double*, int), int N, double x) {
    double ElTel1, k, res = 0;
    double* ArrTel = malloc(N * sizeof(double));
    if (ArrTel) {

        x = (x - 1) / (x + 1);
        ElTel1 = x;
        for (int i = 0; i < N; i++) {
            ArrTel[i] = 2 * ElTel1;

            k = (2 * i + 1) * x * x / (2 * i + 3);
            ElTel1 = ElTel1 * k;
        }
        res = ResFunc(ArrTel, N);
    }
    free(ArrTel);
    return res;
}

double funcc(ValAFunc a) {
    double (*MathFunc) (double (*)(double*, int), int, double);
    double (*ResFunc)(double*, int);
    MathFunc = a.MathFunc;
    ResFunc = a.ResFunc;
    return MathFunc(ResFunc, a.ValElTel, a.x);
}


int main()
{
    ValAFunc Ind;
    double (*LibFunc) (double);
    LibFunc = sin;
    int UChoiseFunc, UsResFunc, UChoiseAct, N = 100;
    Ind.x = 10;
    Ind.ValElTel = N;
    Ind.MathFunc = Sin;
    Ind.ResFunc = PrSum;
    int flg = 1;
    while (flg) {
        printf("Enter 1 to select the function.\nEnter 2 to get the result.\nEnter 3 to get the all sum result.\nEnter 4 to enter a value.\nEnter 5 to enter a number of elements in the Taylor series.\nEnter another to exit: ");
        scanf_s("%d", &UChoiseAct);
        system("cls");
        switch (UChoiseAct)
        {
        case 1:
            printf("1 - sin, 2 - cos, 3 - exp, 4 - ln: ");
            scanf_s("%d", &UChoiseFunc);
            system("cls");
            switch (UChoiseFunc) {
            case 1:
                Ind.MathFunc = Sin;
                LibFunc = sin;
                break;
            case 2:
                Ind.MathFunc = Cos;
                LibFunc = cos;
                break;
            case 3:
                Ind.MathFunc = Exp;
                LibFunc = exp;
                break;
            case 4:
                Ind.MathFunc = NLog;
                LibFunc = log;
                break;
            }
            break;
        case 2:
            printf("Enter 1 for forward summation\nEnter 2 for reverse summation\nEnter 3 for 2Sum: ");
            scanf_s("%d", &UsResFunc);
            system("cls");
            switch (UsResFunc) {
            case 1:
                Ind.ResFunc = PrSum;
                break;
            case 2:
                Ind.ResFunc = RevSum;
                break;
            case 3:
                Ind.ResFunc = SlSum;
                break;
            default:
                Ind.ResFunc = PrSum;
            }
            system("cls");
            printf("My func\n%.20lf\nMath lib func\n%.20lf\n\n\n", funcc(Ind), LibFunc(Ind.x));
            break;
        case 3:
            Ind.ResFunc = PrSum;
            printf("My func\nforward summation:  %.20lf\n", funcc(Ind));
            Ind.ResFunc = RevSum;
            printf("reverse summation:  %.20lf\n", funcc(Ind));
            Ind.ResFunc = SlSum;
            printf("fast two sum:       %.20lf\nMath lib func:      %.20lf\n\n\n", funcc(Ind), LibFunc(Ind.x));
            break;
        case 4:
            printf("Enter the number: ");
            scanf_s("%lf", &Ind.x);
            system("cls");
            break;
        case 5:
            printf("Enter a number of elements in the Taylor: ");
            scanf_s("%d", &Ind.ValElTel);
            system("cls");
            break;
        default:
            flg = 0;
        }
    }
    return 0;
}
