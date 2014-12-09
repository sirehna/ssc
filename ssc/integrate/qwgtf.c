/* qwgtf.f -- translated by f2c (version 20100827).
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

doublereal qwgtf_(real *x, real *omega, real *p2, real *p3, real *p4, integer 
	*integr)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal);

    /* Local variables */
    static real omx;

/* ***begin prologue  qwgtf */
/* ***refer to   qk15w */
/* ***routines called  (none) */
/* ***revision date 810101   (yymmdd) */
/* ***keywords  cos or sin in weight function */
/* ***author  piessens,robert, appl. math. & progr. div. - k.u.leuven */
/*           de doncker,elise,appl. math. * progr. div. - k.u.leuven */
/* ***end prologue  qwgtf */

/* ***first executable statement */
    omx = *omega * *x;
    switch (*integr) {
	case 1:  goto L10;
	case 2:  goto L20;
    }
L10:
    ret_val = cos(omx);
    goto L30;
L20:
    ret_val = sin(omx);
L30:
    return ret_val;
} /* qwgtf_ */

