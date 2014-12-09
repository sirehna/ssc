/* qk15w.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"
#include <stdio.h>

#define COUT(x) printf("in file %s, line %i: " #x " = %f\n", __FILE__, __LINE__, (double)x);
/* Table of constant values */

static integer c__4 = 4;
static integer c__1 = 1;
static doublereal c_b7 = 1.5;

/* Subroutine */ int qk15w_(E_fp f, E_fp w, integer *obj, doublereal *p1, doublereal *p2, doublereal *p3,
	doublereal *p4, integer *kp, doublereal *a, doublereal *b, doublereal *result, doublereal *abserr,
	doublereal *resabs, doublereal *resasc)
{
    /* Initialized data */

    static doublereal xgk[8] = { .9914553711208126f,.9491079123427585f,
	    .8648644233597691f,.7415311855993944f,.5860872354676911f,
	    .4058451513773972f,.2077849550078985f,0.f };
    static doublereal wgk[8] = { .02293532201052922f,.06309209262997855f,
	    .1047900103222502f,.1406532597155259f,.1690047266392679f,
	    .1903505780647854f,.2044329400752989f,.2094821410847278f };
    static doublereal wg[4] = { .1294849661688697f,.2797053914892767f,
	    .3818300505051889f,.4179591836734694f };

    /* System generated locals */
    doublereal r__1, r__2;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer j;
    static doublereal fc, fv1[7], fv2[7];
    static integer jtw;
    static doublereal absc, resg, resk, fsum, absc1, absc2, fval1, fval2;
    static integer jtwm1;
    static doublereal hlgth, centr, reskh, uflow;
    extern doublereal r1mach_(integer *);
    static doublereal epmach, dhlgth;

/* ***begin prologue  qk15w */
/* ***date written   810101   (yymmdd) */
/* ***revision date  830518   (mmddyy) */
/* ***category no.  h2a2a2 */
/* ***keywords  15-point gauss-kronrod rules */
/* ***author  piessens,robert,appl. math. & progr. div. - k.u.leuven */
/*           de doncker,elise,appl. math. & progr. div. - k.u.leuven */
/* ***purpose  to compute i = integral of f*w over (a,b), with error */
/*                           estimate */
/*                       j = integral of abs(f*w) over (a,b) */
/* ***description */

/*           integration rules */
/*           standard fortran subroutine */
/*           doublereal version */

/*           parameters */
/*             on entry */
/*              f      - doublereal */
/*                       function subprogram defining the integrand */
/*                       function f(x). the actual name for f needs to be */
/*                       declared e x t e r n a l in the driver program. */

/*              w      - doublereal */
/*                       function subprogram defining the integrand */
/*                       weight function w(x). the actual name for w */
/*                       needs to be declared e x t e r n a l in the */
/*                       calling program. */

/*              p1, p2, p3, p4 - doublereal */
/*                       parameters in the weight function */

/*              kp     - integer */
/*                       key for indicating the type of weight function */

/*              a      - doublereal */
/*                       lower limit of integration */

/*              b      - doublereal */
/*                       upper limit of integration */

/*            on return */
/*              result - doublereal */
/*                       approximation to the integral i */
/*                       result is computed by applying the 15-point */
/*                       kronrod rule (resk) obtained by optimal addition */
/*                       of abscissae to the 7-point gauss rule (resg). */

/*              abserr - doublereal */
/*                       estimate of the modulus of the absolute error, */
/*                       which should equal or exceed abs(i-result) */

/*              resabs - doublereal */
/*                       approximation to the integral of abs(f) */

/*              resasc - doublereal */
/*                       approximation to the integral of abs(f-i/(b-a)) */

/* ***references  (none) */
/* ***routines called  r1mach */
/* ***end prologue  qk15w */



/*           the abscissae and weights are given for the interval (-1,1). */
/*           because of symmetry only the positive abscissae and their */
/*           corresponding weights are given. */

/*           xgk    - abscissae of the 15-point gauss-kronrod rule */
/*                    xgk(2), xgk(4), ... abscissae of the 7-point */
/*                    gauss rule */
/*                    xgk(1), xgk(3), ... abscissae which are optimally */
/*                    added to the 7-point gauss rule */

/*           wgk    - weights of the 15-point gauss-kronrod rule */

/*           wg     - weights of the 7-point gauss rule */





/*           list of major variables */
/*           ----------------------- */

/*           centr  - mid point of the interval */
/*           hlgth  - half-length of the interval */
/*           absc*  - abscissa */
/*           fval*  - function value */
/*           resg   - result of the 7-point gauss formula */
/*           resk   - result of the 15-point kronrod formula */
/*           reskh  - approximation to the mean value of f*w over (a,b), */
/*                    i.e. to i/(b-a) */

/*           machine dependent constants */
/*           --------------------------- */

/*           epmach is the largest relative spacing. */
/*           uflow is the smallest positive magnitude. */

/* ***first executable statement  qk15w */
    epmach = r1mach_(&c__4);
    uflow = r1mach_(&c__1);

    centr = (*a + *b) * .5f;
    hlgth = (*b - *a) * .5f;
    dhlgth = dabs(hlgth);

/*           compute the 15-point kronrod approximation to the */
/*           integral, and estimate the error. */

    fc = (*f)(obj,&centr) * (*w)(&centr, p1, p2, p3, p4, kp);
    resg = wg[3] * fc;
    resk = wgk[7] * fc;
    *resabs = dabs(resk);
    for (j = 1; j <= 3; ++j) {
	jtw = j << 1;
	absc = hlgth * xgk[jtw - 1];
	absc1 = centr - absc;
	absc2 = centr + absc;
	fval1 = (*f)(obj,&absc1) * (*w)(&absc1, p1, p2, p3, p4, kp);
	fval2 = (*f)(obj,&absc2) * (*w)(&absc2, p1, p2, p3, p4, kp);
	fv1[jtw - 1] = fval1;
	fv2[jtw - 1] = fval2;
	fsum = fval1 + fval2;
	resg += wg[j - 1] * fsum;
	resk += wgk[jtw - 1] * fsum;
	*resabs += wgk[jtw - 1] * (dabs(fval1) + dabs(fval2));
/* L10: */
    }
    for (j = 1; j <= 4; ++j) {
	jtwm1 = (j << 1) - 1;
	absc = hlgth * xgk[jtwm1 - 1];
	absc1 = centr - absc;
	absc2 = centr + absc;
	const double xx1 = (*f)(obj,&absc1);
	const double xx2 = (*f)(obj,&absc2);
	fval1 = (*f)(obj,&absc1) * (*w)(&absc1, p1, p2, p3, p4, kp);
	fval2 = (*f)(obj,&absc2) * (*w)(&absc2, p1, p2, p3, p4, kp);
	fv1[jtwm1 - 1] = fval1;
	fv2[jtwm1 - 1] = fval2;
	fsum = fval1 + fval2;
	resk += wgk[jtwm1 - 1] * fsum;
	*resabs += wgk[jtwm1 - 1] * (dabs(fval1) + dabs(fval2));
/* L15: */
    }
    reskh = resk * .5f;
    *resasc = wgk[7] * (r__1 = fc - reskh, dabs(r__1));
    for (j = 1; j <= 7; ++j) {
	*resasc += wgk[j - 1] * ((r__1 = fv1[j - 1] - reskh, dabs(r__1)) + (
		r__2 = fv2[j - 1] - reskh, dabs(r__2)));
/* L20: */
    }
    *result = resk * hlgth;
    *resabs *= dhlgth;
    *resasc *= dhlgth;
    *abserr = (r__1 = (resk - resg) * hlgth, dabs(r__1));
    if (*resasc != 0.f && *abserr != 0.f) {
/* Computing MIN */
	d__1 = (doublereal) (*abserr * 200.f / *resasc);
	r__1 = 1.f, r__2 = pow_dd(&d__1, &c_b7);
	*abserr = *resasc * dmin(r__1,r__2);
    }
    if (*resabs > uflow / (epmach * 50.f)) {
/* Computing MAX */
	r__1 = epmach * 50.f * *resabs;
	*abserr = dmax(r__1,*abserr);
    }
    return 0;
} /* qk15w_ */

