/*      driver for hybrd1 example. */


#include <stdio.h>
#include <math.h>
#include "cminpack.h"

typedef struct ParamType{

    int ParamOP0;
    int ParamOP1;
    int ParamOP2;
    int ParamOP3;

} Param;

Param pr;

int fcn(void *p, int n, const double *x, double *fvec, int iflag);

int main()
{
    int j, n, info, lwa;
    double tol, fnorm;
    double x[9], fvec[9], wa[180];

    n = 9;

/*      the following starting values provide a rough solution. */

    for (j=1; j<=9; j++)
    {
        x[j-1] = -1.;
    }

    lwa = 180;

    pr.ParamOP0=0;pr.ParamOP1=1;
    pr.ParamOP2=2;pr.ParamOP3=3;

/*      set tol to the square root of the machine precision. */
/*      unless high solutions are required, */
/*      this is the recommended setting. */

    tol = sqrt(dpmpar(1));
    info = hybrd1(fcn, 0, n, x, fvec, tol, wa, lwa);
    fnorm = enorm(n, fvec);

    printf("     final L2 norm of the residuals %15.7g\n", fnorm);
    printf("     exit parameter                 %10i\n", info);
    printf("     final approximates solution\n");
    for (j=1; j<=n; j++) printf("%s%15.7g",j%3==1?"\n     ":"", x[j-1]);
    printf("\n");

    return 0;
}

int fcn(void *p, int n, const double *x, double *fvec, int iflag)
{
/*      subroutine fcn for hybrd1 example. */

    int k;
    double one=pr.ParamOP1, temp, temp1, temp2, three=pr.ParamOP3, two=pr.ParamOP2, zero=pr.ParamOP0;

    for (k=1; k <= n; k++)
    {
        temp = (three - two*x[k-1])*x[k-1];
        temp1 = zero;
        if (k != 1) temp1 = x[k-1-1];
        temp2 = zero;
        if (k != n) temp2 = x[k+1-1];
        fvec[k-1] = temp - temp1 - two*temp2 + one;
    }
    return 0;
}
