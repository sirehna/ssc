/* qawoe.f -- translated by f2c (version 20100827).
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

/* Table of constant values */

static integer c__4 = 4;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;

/* Subroutine */ int qawoe_(E_fp f, real *a, real *b, real *omega, integer *
	integr, real *epsabs, real *epsrel, integer *limit, integer *icall, 
	integer *maxp1, real *result, real *abserr, integer *neval, integer *
	ier, integer *last, real *alist__, real *blist, real *rlist, real *
	elist, integer *iord, integer *nnlog, integer *momcom, real *chebmo)
{
    /* System generated locals */
    integer chebmo_dim1, chebmo_offset, i__1, i__2;
    real r__1, r__2;

    /* Local variables */
    static integer k;
    static real a1, a2, b1, b2;
    static integer id, nev;
    static real area;
    extern /* Subroutine */ int qc25f_(E_fp, real *, real *, real *, integer *
	    , integer *, integer *, integer *, real *, real *, integer *, 
	    real *, real *, integer *, real *), qelg_(integer *, real *, real 
	    *, real *, real *, integer *);
    static real dres;
    static integer ksgn, nres;
    static real area1, area2, area12, small, erro12, defab1, defab2, width;
    static integer ierro;
    static real oflow;
    static integer ktmin, nrmax, nrmom;
    static real uflow;
    static logical noext;
    extern /* Subroutine */ int qpsrt_(integer *, integer *, integer *, real *
	    , real *, integer *, integer *);
    extern doublereal r1mach_(integer *);
    static integer iroff1, iroff2, iroff3;
    static real res3la[3], error1, error2, rlist2[52];
    static integer numrl2;
    static real defabs, domega, epmach, erlarg, abseps, correc, errbnd, 
	    resabs;
    static integer jupbnd;
    static logical extall;
    static real erlast, errmax;
    static integer maxerr;
    static real reseps;
    static logical extrap;
    static real ertest, errsum;

/* ***begin prologue  qawoe */
/* ***date written   800101   (yymmdd) */
/* ***revision date  830518   (yymmdd) */
/* ***category no.  h2a2a1 */
/* ***keywords  automatic integrator, special-purpose, */
/*             integrand with oscillatory cos or sin factor, */
/*             clenshaw-curtis method, (end point) singularities, */
/*             extrapolation, globally adaptive */
/* ***author  piessens,robert,appl. math. & progr. div. - k.u.leuven */
/*           de doncker,elise,appl. math. & progr. div. - k.u.leuven */
/* ***purpose  the routine calculates an approximation result to a given */
/*            definite integral */
/*            i = integral of f(x)*w(x) over (a,b) */
/*            where w(x) = cos(omega*x) or w(x) = sin(omega*x), */
/*            hopefully satisfying following claim for accuracy */
/*            abs(i-result).le.max(epsabs,epsrel*abs(i)). */
/* ***description */

/*        computation of oscillatory integrals */
/*        standard fortran subroutine */
/*        real version */

/*        parameters */
/*         on entry */
/*            f      - real */
/*                     function subprogram defining the integrand */
/*                     function f(x). the actual name for f needs to be */
/*                     declared e x t e r n a l in the driver program. */

/*            a      - real */
/*                     lower limit of integration */

/*            b      - real */
/*                     upper limit of integration */

/*            omega  - real */
/*                     parameter in the integrand weight function */

/*            integr - integer */
/*                     indicates which of the weight functions is to be */
/*                     used */
/*                     integr = 1      w(x) = cos(omega*x) */
/*                     integr = 2      w(x) = sin(omega*x) */
/*                     if integr.ne.1 and integr.ne.2, the routine */
/*                     will end with ier = 6. */

/*            epsabs - real */
/*                     absolute accuracy requested */
/*            epsrel - real */
/*                     relative accuracy requested */
/*                     if  epsabs.le.0 */
/*                     and epsrel.lt.max(50*rel.mach.acc.,0.5d-28), */
/*                     the routine will end with ier = 6. */

/*            limit  - integer */
/*                     gives an upper bound on the number of subdivisions */
/*                     in the partition of (a,b), limit.ge.1. */

/*            icall  - integer */
/*                     if dqawoe is to be used only once, icall must */
/*                     be set to 1.  assume that during this call, the */
/*                     chebyshev moments (for clenshaw-curtis integration */
/*                     of degree 24) have been computed for intervals of */
/*                     lenghts (abs(b-a))*2**(-l), l=0,1,2,...momcom-1. */
/*                     if icall.gt.1 this means that dqawoe has been */
/*                     called twice or more on intervals of the same */
/*                     length abs(b-a). the chebyshev moments already */
/*                     computed are then re-used in subsequent calls. */
/*                     if icall.lt.1, the routine will end with ier = 6. */

/*            maxp1  - integer */
/*                     gives an upper bound on the number of chebyshev */
/*                     moments which can be stored, i.e. for the */
/*                     intervals of lenghts abs(b-a)*2**(-l), */
/*                     l=0,1, ..., maxp1-2, maxp1.ge.1. */
/*                     if maxp1.lt.1, the routine will end with ier = 6. */

/*         on return */
/*            result - real */
/*                     approximation to the integral */

/*            abserr - real */
/*                     estimate of the modulus of the absolute error, */
/*                     which should equal or exceed abs(i-result) */

/*            neval  - integer */
/*                     number of integrand evaluations */

/*            ier    - integer */
/*                     ier = 0 normal and reliable termination of the */
/*                             routine. it is assumed that the */
/*                             requested accuracy has been achieved. */
/*                   - ier.gt.0 abnormal termination of the routine. */
/*                             the estimates for integral and error are */
/*                             less reliable. it is assumed that the */
/*                             requested accuracy has not been achieved. */
/*            error messages */
/*                     ier = 1 maximum number of subdivisions allowed */
/*                             has been achieved. one can allow more */
/*                             subdivisions by increasing the value of */
/*                             limit (and taking according dimension */
/*                             adjustments into account). however, if */
/*                             this yields no improvement it is advised */
/*                             to analyze the integrand, in order to */
/*                             determine the integration difficulties. */
/*                             if the position of a local difficulty can */
/*                             be determined (e.g. singularity, */
/*                             discontinuity within the interval) one */
/*                             will probably gain from splitting up the */
/*                             interval at this point and calling the */
/*                             integrator on the subranges. if possible, */
/*                             an appropriate special-purpose integrator */
/*                             should be used which is designed for */
/*                             handling the type of difficulty involved. */
/*                         = 2 the occurrence of roundoff error is */
/*                             detected, which prevents the requested */
/*                             tolerance from being achieved. */
/*                             the error may be under-estimated. */
/*                         = 3 extremely bad integrand behaviour occurs */
/*                             at some points of the integration */
/*                             interval. */
/*                         = 4 the algorithm does not converge. */
/*                             roundoff error is detected in the */
/*                             extrapolation table. */
/*                             it is presumed that the requested */
/*                             tolerance cannot be achieved due to */
/*                             roundoff in the extrapolation table, */
/*                             and that the returned result is the */
/*                             best which can be obtained. */
/*                         = 5 the integral is probably divergent, or */
/*                             slowly convergent. it must be noted that */
/*                             divergence can occur with any other value */
/*                             of ier.gt.0. */
/*                         = 6 the input is invalid, because */
/*                             (epsabs.le.0 and */
/*                              epsrel.lt.max(50*rel.mach.acc.,0.5d-28)) */
/*                             or (integr.ne.1 and integr.ne.2) or */
/*                             icall.lt.1 or maxp1.lt.1. */
/*                             result, abserr, neval, last, rlist(1), */
/*                             elist(1), iord(1) and nnlog(1) are set */
/*                             to zero. alist(1) and blist(1) are set */
/*                             to a and b respectively. */

/*            last  -  integer */
/*                     on return, last equals the number of */
/*                     subintervals produces in the subdivision */
/*                     process, which determines the number of */
/*                     significant elements actually in the */
/*                     work arrays. */
/*            alist  - real */
/*                     vector of dimension at least limit, the first */
/*                      last  elements of which are the left */
/*                     end points of the subintervals in the partition */
/*                     of the given integration range (a,b) */

/*            blist  - real */
/*                     vector of dimension at least limit, the first */
/*                      last  elements of which are the right */
/*                     end points of the subintervals in the partition */
/*                     of the given integration range (a,b) */

/*            rlist  - real */
/*                     vector of dimension at least limit, the first */
/*                      last  elements of which are the integral */
/*                     approximations on the subintervals */

/*            elist  - real */
/*                     vector of dimension at least limit, the first */
/*                      last  elements of which are the moduli of the */
/*                     absolute error estimates on the subintervals */

/*            iord   - integer */
/*                     vector of dimension at least limit, the first k */
/*                     elements of which are pointers to the error */
/*                     estimates over the subintervals, */
/*                     such that elist(iord(1)), ..., */
/*                     elist(iord(k)) form a decreasing sequence, with */
/*                     k = last if last.le.(limit/2+2), and */
/*                     k = limit+1-last otherwise. */

/*            nnlog  - integer */
/*                     vector of dimension at least limit, containing the */
/*                     subdivision levels of the subintervals, i.e. */
/*                     iwork(i) = l means that the subinterval */
/*                     numbered i is of length abs(b-a)*2**(1-l) */

/*         on entry and return */
/*            momcom - integer */
/*                     indicating that the chebyshev moments */
/*                     have been computed for intervals of lengths */
/*                     (abs(b-a))*2**(-l), l=0,1,2, ..., momcom-1, */
/*                     momcom.lt.maxp1 */

/*            chebmo - real */
/*                     array of dimension (maxp1,25) containing the */
/*                     chebyshev moments */

/* ***references  (none) */
/* ***routines called  qc25f,qelg,qpsrt,r1mach */
/* ***end prologue  qawoe */




/*            the dimension of rlist2 is determined by  the value of */
/*            limexp in subroutine qelg (rlist2 should be of */
/*            dimension (limexp+2) at least). */

/*            list of major variables */
/*            ----------------------- */

/*           alist     - list of left end points of all subintervals */
/*                       considered up to now */
/*           blist     - list of right end points of all subintervals */
/*                       considered up to now */
/*           rlist(i)  - approximation to the integral over */
/*                       (alist(i),blist(i)) */
/*           rlist2    - array of dimension at least limexp+2 */
/*                       containing the part of the epsilon table */
/*                       which is still needed for further computations */
/*           elist(i)  - error estimate applying to rlist(i) */
/*           maxerr    - pointer to the interval with largest */
/*                       error estimate */
/*           errmax    - elist(maxerr) */
/*           erlast    - error on the interval currently subdivided */
/*           area      - sum of the integrals over the subintervals */
/*           errsum    - sum of the errors over the subintervals */
/*           errbnd    - requested accuracy max(epsabs,epsrel* */
/*                       abs(result)) */
/*           *****1    - variable for the left subinterval */
/*           *****2    - variable for the right subinterval */
/*           last      - index for subdivision */
/*           nres      - number of calls to the extrapolation routine */
/*           numrl2    - number of elements in rlist2. if an appropriate */
/*                       approximation to the compounded integral has */
/*                       been obtained it is put in rlist2(numrl2) after */
/*                       numrl2 has been increased by one */
/*           small     - length of the smallest interval considered */
/*                       up to now, multiplied by 1.5 */
/*           erlarg    - sum of the errors over the intervals larger */
/*                       than the smallest interval considered up to now */
/*           extrap    - logical variable denoting that the routine is */
/*                       attempting to perform extrapolation, i.e. before */
/*                       subdividing the smallest interval we try to */
/*                       decrease the value of erlarg */
/*           noext     - logical variable denoting that extrapolation */
/*                       is no longer allowed (true value) */

/*            machine dependent constants */
/*            --------------------------- */

/*           epmach is the largest relative spacing. */
/*           uflow is the smallest positive magnitude. */
/*           oflow is the largest positive magnitude. */

/* ***first executable statement  qawoe */
    /* Parameter adjustments */
    --nnlog;
    --iord;
    --elist;
    --rlist;
    --blist;
    --alist__;
    chebmo_dim1 = *maxp1;
    chebmo_offset = 1 + chebmo_dim1;
    chebmo -= chebmo_offset;

    /* Function Body */
    epmach = r1mach_(&c__4);

/*         test on validity of parameters */
/*         ------------------------------ */

    *ier = 0;
    *neval = 0;
    *last = 0;
    *result = 0.f;
    *abserr = 0.f;
    alist__[1] = *a;
    blist[1] = *b;
    rlist[1] = 0.f;
    elist[1] = 0.f;
    iord[1] = 0;
    nnlog[1] = 0;
/* Computing MAX */
    r__1 = epmach * 50.f;
    if (*integr != 1 && *integr != 2 || *epsabs <= 0.f && *epsrel < dmax(r__1,
	    5e-15f) || *icall < 1 || *maxp1 < 1) {
	*ier = 6;
    }
    if (*ier == 6) {
	goto L999;
    }

/*           first approximation to the integral */
/*           ----------------------------------- */

    domega = dabs(*omega);
    nrmom = 0;
    if (*icall > 1) {
	goto L5;
    }
    *momcom = 0;
L5:
    qc25f_((E_fp)f, a, b, &domega, integr, &nrmom, maxp1, &c__0, result, 
	    abserr, neval, &defabs, &resabs, momcom, &chebmo[chebmo_offset]);

/*           test on accuracy. */

    dres = dabs(*result);
/* Computing MAX */
    r__1 = *epsabs, r__2 = *epsrel * dres;
    errbnd = dmax(r__1,r__2);
    rlist[1] = *result;
    elist[1] = *abserr;
    iord[1] = 1;
    if (*abserr <= epmach * 100.f * defabs && *abserr > errbnd) {
	*ier = 2;
    }
    if (*limit == 1) {
	*ier = 1;
    }
    if (*ier != 0 || *abserr <= errbnd) {
	goto L200;
    }

/*           initializations */
/*           --------------- */

    uflow = r1mach_(&c__1);
    oflow = r1mach_(&c__2);
    errmax = *abserr;
    maxerr = 1;
    area = *result;
    errsum = *abserr;
    *abserr = oflow;
    nrmax = 1;
    extrap = FALSE_;
    noext = FALSE_;
    ierro = 0;
    iroff1 = 0;
    iroff2 = 0;
    iroff3 = 0;
    ktmin = 0;
    small = (r__1 = *b - *a, dabs(r__1)) * .75f;
    nres = 0;
    numrl2 = 0;
    extall = FALSE_;
    if ((r__1 = *b - *a, dabs(r__1)) * .5f * domega > 2.f) {
	goto L10;
    }
    numrl2 = 1;
    extall = TRUE_;
    rlist2[0] = *result;
L10:
    if ((r__1 = *b - *a, dabs(r__1)) * .25f * domega <= 2.f) {
	extall = TRUE_;
    }
    ksgn = -1;
    if (dres >= (1.f - epmach * 50.f) * defabs) {
	ksgn = 1;
    }

/*           main do-loop */
/*           ------------ */

    i__1 = *limit;
    for (*last = 2; *last <= i__1; ++(*last)) {

/*           bisect the subinterval with the nrmax-th largest */
/*           error estimate. */

	nrmom = nnlog[maxerr] + 1;
	a1 = alist__[maxerr];
	b1 = (alist__[maxerr] + blist[maxerr]) * .5f;
	a2 = b1;
	b2 = blist[maxerr];
	erlast = errmax;
	qc25f_((E_fp)f, &a1, &b1, &domega, integr, &nrmom, maxp1, &c__0, &
		area1, &error1, &nev, &resabs, &defab1, momcom, &chebmo[
		chebmo_offset]);
	*neval += nev;
	qc25f_((E_fp)f, &a2, &b2, &domega, integr, &nrmom, maxp1, &c__1, &
		area2, &error2, &nev, &resabs, &defab2, momcom, &chebmo[
		chebmo_offset]);
	*neval += nev;

/*           improve previous approximations to integral */
/*           and error and test for accuracy. */

	area12 = area1 + area2;
	erro12 = error1 + error2;
	errsum = errsum + erro12 - errmax;
	area = area + area12 - rlist[maxerr];
	if (defab1 == error1 || defab2 == error2) {
	    goto L25;
	}
	if ((r__1 = rlist[maxerr] - area12, dabs(r__1)) > dabs(area12) * 
		1e-5f || erro12 < errmax * .99f) {
	    goto L20;
	}
	if (extrap) {
	    ++iroff2;
	}
	if (! extrap) {
	    ++iroff1;
	}
L20:
	if (*last > 10 && erro12 > errmax) {
	    ++iroff3;
	}
L25:
	rlist[maxerr] = area1;
	rlist[*last] = area2;
	nnlog[maxerr] = nrmom;
	nnlog[*last] = nrmom;
/* Computing MAX */
	r__1 = *epsabs, r__2 = *epsrel * dabs(area);
	errbnd = dmax(r__1,r__2);

/*           test for roundoff error and eventually */
/*           set error flag */

	if (iroff1 + iroff2 >= 10 || iroff3 >= 20) {
	    *ier = 2;
	}
	if (iroff2 >= 5) {
	    ierro = 3;
	}

/*           set error flag in the case that the number of */
/*           subintervals equals limit. */

	if (*last == *limit) {
	    *ier = 1;
	}

/*           set error flag in the case of bad integrand behaviour */
/*           at a point of the integration range. */

/* Computing MAX */
	r__1 = dabs(a1), r__2 = dabs(b2);
	if (dmax(r__1,r__2) <= (epmach * 100.f + 1.f) * (dabs(a2) + uflow * 
		1e3f)) {
	    *ier = 4;
	}

/*           append the newly-created intervals to the list. */

	if (error2 > error1) {
	    goto L30;
	}
	alist__[*last] = a2;
	blist[maxerr] = b1;
	blist[*last] = b2;
	elist[maxerr] = error1;
	elist[*last] = error2;
	goto L40;
L30:
	alist__[maxerr] = a2;
	alist__[*last] = a1;
	blist[*last] = b1;
	rlist[maxerr] = area2;
	rlist[*last] = area1;
	elist[maxerr] = error2;
	elist[*last] = error1;

/*           call subroutine qpsrt to maintain the descending ordering */
/*           in the list of error estimates and select the */
/*           subinterval with nrmax-th largest error estimate (to be */
/*           bisected next). */

L40:
	qpsrt_(limit, last, &maxerr, &errmax, &elist[1], &iord[1], &nrmax);
/* ***jump out of do-loop */
	if (errsum <= errbnd) {
	    goto L170;
	}
	if (*ier != 0) {
	    goto L150;
	}
	if (*last == 2 && extall) {
	    goto L120;
	}
	if (noext) {
	    goto L140;
	}
	if (! extall) {
	    goto L50;
	}
	erlarg -= erlast;
	if ((r__1 = b1 - a1, dabs(r__1)) > small) {
	    erlarg += erro12;
	}
	if (extrap) {
	    goto L70;
	}

/*           test whether the interval to be bisected next is the */
/*           smallest interval. */

L50:
	width = (r__1 = blist[maxerr] - alist__[maxerr], dabs(r__1));
	if (width > small) {
	    goto L140;
	}
	if (extall) {
	    goto L60;
	}

/*           test whether we can start with the extrapolation */
/*           procedure (we do this if we integrate over the */
/*           next interval with use of a gauss-kronrod rule - see */
/*           subroutine qc25f). */

	small *= .5f;
	if (width * .25f * domega > 2.f) {
	    goto L140;
	}
	extall = TRUE_;
	goto L130;
L60:
	extrap = TRUE_;
	nrmax = 2;
L70:
	if (ierro == 3 || erlarg <= ertest) {
	    goto L90;
	}

/*           the smallest interval has the largest error. */
/*           before bisecting decrease the sum of the errors */
/*           over the larger intervals (erlarg) and perform */
/*           extrapolation. */

	jupbnd = *last;
	if (*last > *limit / 2 + 2) {
	    jupbnd = *limit + 3 - *last;
	}
	id = nrmax;
	i__2 = jupbnd;
	for (k = id; k <= i__2; ++k) {
	    maxerr = iord[nrmax];
	    errmax = elist[maxerr];
	    if ((r__1 = blist[maxerr] - alist__[maxerr], dabs(r__1)) > small) 
		    {
		goto L140;
	    }
	    ++nrmax;
/* L80: */
	}

/*           perform extrapolation. */

L90:
	++numrl2;
	rlist2[numrl2 - 1] = area;
	if (numrl2 < 3) {
	    goto L110;
	}
	qelg_(&numrl2, rlist2, &reseps, &abseps, res3la, &nres);
	++ktmin;
	if (ktmin > 5 && *abserr < errsum * .001f) {
	    *ier = 5;
	}
	if (abseps >= *abserr) {
	    goto L100;
	}
	ktmin = 0;
	*abserr = abseps;
	*result = reseps;
	correc = erlarg;
/* Computing MAX */
	r__1 = *epsabs, r__2 = *epsrel * dabs(reseps);
	ertest = dmax(r__1,r__2);
/* ***jump out of do-loop */
	if (*abserr <= ertest) {
	    goto L150;
	}

/*           prepare bisection of the smallest interval. */

L100:
	if (numrl2 == 1) {
	    noext = TRUE_;
	}
	if (*ier == 5) {
	    goto L150;
	}
L110:
	maxerr = iord[1];
	errmax = elist[maxerr];
	nrmax = 1;
	extrap = FALSE_;
	small *= .5f;
	erlarg = errsum;
	goto L140;
L120:
	small *= .5f;
	++numrl2;
	rlist2[numrl2 - 1] = area;
L130:
	ertest = errbnd;
	erlarg = errsum;
L140:
	;
    }

/*           set the final result. */
/*           --------------------- */

L150:
    if (*abserr == oflow || nres == 0) {
	goto L170;
    }
    if (*ier + ierro == 0) {
	goto L165;
    }
    if (ierro == 3) {
	*abserr += correc;
    }
    if (*ier == 0) {
	*ier = 3;
    }
    if (*result != 0.f && area != 0.f) {
	goto L160;
    }
    if (*abserr > errsum) {
	goto L170;
    }
    if (area == 0.f) {
	goto L190;
    }
    goto L165;
L160:
    if (*abserr / dabs(*result) > errsum / dabs(area)) {
	goto L170;
    }

/*           test on divergence. */

L165:
/* Computing MAX */
    r__1 = dabs(*result), r__2 = dabs(area);
    if (ksgn == -1 && dmax(r__1,r__2) <= defabs * .01f) {
	goto L190;
    }
    if (.01f > *result / area || *result / area > 100.f || errsum >= dabs(
	    area)) {
	*ier = 6;
    }
    goto L190;

/*           compute global integral sum. */

L170:
    *result = 0.f;
    i__1 = *last;
    for (k = 1; k <= i__1; ++k) {
	*result += rlist[k];
/* L180: */
    }
    *abserr = errsum;
L190:
    if (*ier > 2) {
	--(*ier);
    }
L200:
    if (*integr == 2 && *omega < 0.f) {
	*result = -(*result);
    }
L999:
    return 0;
} /* qawoe_ */

