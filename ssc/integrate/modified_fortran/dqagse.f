      subroutine dqagse(f,obj,a,b,absolute_tolerance,relative_tolerance,max_nb_of_subintervals,result,estimate_of_absolute_error,nb_of_function_evaluations,
     *   error_code,left_end_points,right_end_points,integral_approximation,error_estimates,index_of_decreasingly_sorted_error,nb_of_subintervals)
c***begin prologue  dqagse
c***date written   800101   (yymmdd)
c***revision date  830518   (yymmdd)
c***category no.  h2a1a1
c***keywords  automatic integrator, general-purpose,
c             (end point) singularities, extrapolation,
c             globally adaptive
c***author  piessens,robert,appl. math. & progr. div. - k.u.leuven
c           de doncker,elise,appl. math. & progr. div. - k.u.leuven
c***purpose  the routine calculates an approximation result to a given
c            definite integral i = integral of f over (a,b),
c            hopefully satisfying following claim for accuracy
c            abs(i-result).le.max(absolute_tolerance,relative_tolerance*abs(i)).
c***description
c
c        computation of a definite integral
c        standard fortran subroutine
c        double precision version
c
c        parameters
c         on entry
c            f      - double precision
c                     function subprogram defining the integrand
c                     function f(x). the actual name for f needs to be
c                     declared e x t e r n a l in the driver program.
c
c            a      - double precision
c                     lower max_nb_of_subintervals of integration
c
c            b      - double precision
c                     upper max_nb_of_subintervals of integration
c
c            absolute_tolerance - double precision
c                     absolute accuracy requested
c            relative_tolerance - double precision
c                     relative accuracy requested
c                     if  absolute_tolerance.le.0
c                     and relative_tolerance.lt.max(50*rel.mach.acc.,0.5d-28),
c                     the routine will end with error_code = 6.
c
c            max_nb_of_subintervals  - integer
c                     gives an upperbound on the number of subintervals
c                     in the partition of (a,b)
c
c         on return
c            result - double precision
c                     approximation to the integral
c
c            estimate_of_absolute_error - double precision
c                     estimate of the modulus of the absolute error,
c                     which should equal or exceed abs(i-result)
c
c            nb_of_function_evaluations  - integer
c                     number of integrand evaluations
c
c            error_code    - integer
c                     error_code = 0 normal and reliable termination of the
c                             routine. it is assumed that the requested
c                             accuracy has been achieved.
c                     error_code.gt.0 abnormal termination of the routine
c                             the estimates for integral and error are
c                             less reliable. it is assumed that the
c                             requested accuracy has not been achieved.
c            error messages
c                         = 1 maximum number of subdivisions allowed
c                             has been achieved. one can allow more sub-
c                             divisions by increasing the value of max_nb_of_subintervals
c                             (and taking the according dimension
c                             adjustments into account). however, if
c                             this yields no improvement it is advised
c                             to analyze the integrand in order to
c                             determine the integration difficulties. if
c                             the position of a local difficulty can be
c                             determined (e.g. singularity,
c                             discontinuity within the interval) one
c                             will probably gain from splitting up the
c                             interval at this point and calling the
c                             integrator on the subranges. if possible,
c                             an appropriate special-purpose integrator
c                             should be used, which is designed for
c                             handling the type of difficulty involved.
c                         = 2 the occurrence of roundoff error is detec-
c                             ted, which prevents the requested
c                             tolerance from being achieved.
c                             the error may be under-estimated.
c                         = 3 extremely bad integrand behaviour
c                             occurs at some points of the integration
c                             interval.
c                         = 4 the algorithm does not converge.
c                             roundoff error is detected in the
c                             extrapolation table.
c                             it is presumed that the requested
c                             tolerance cannot be achieved, and that the
c                             returned result is the best which can be
c                             obtained.
c                         = 5 the integral is probably divergent, or
c                             slowly convergent. it must be noted that
c                             divergence can occur with any other value
c                             of error_code.
c                         = 6 the input is invalid, because
c                             absolute_tolerance.le.0 and
c                             relative_tolerance.lt.max(50*rel.mach.acc.,0.5d-28).
c                             result, estimate_of_absolute_error, nb_of_function_evaluations, nb_of_subintervals, integral_approximation(1),
c                             index_of_decreasingly_sorted_error(1) and error_estimates(1) are set to zero.
c                             left_end_points(1) and right_end_points(1) are set to a and b
c                             respectively.
c
c            left_end_points  - double precision
c                     vector of dimension at least max_nb_of_subintervals, the first
c                      nb_of_subintervals  elements of which are the left end points
c                     of the subintervals in the partition of the
c                     given integration range (a,b)
c
c            right_end_points  - double precision
c                     vector of dimension at least max_nb_of_subintervals, the first
c                      nb_of_subintervals  elements of which are the right end points
c                     of the subintervals in the partition of the given
c                     integration range (a,b)
c
c            integral_approximation  - double precision
c                     vector of dimension at least max_nb_of_subintervals, the first
c                      nb_of_subintervals  elements of which are the integral
c                     approximations on the subintervals
c
c            error_estimates  - double precision
c                     vector of dimension at least max_nb_of_subintervals, the first
c                      nb_of_subintervals  elements of which are the moduli of the
c                     absolute error estimates on the subintervals
c
c            index_of_decreasingly_sorted_error   - integer
c                     vector of dimension at least max_nb_of_subintervals, the first k
c                     elements of which are pointers to the
c                     error estimates over the subintervals,
c                     such that error_estimates(index_of_decreasingly_sorted_error(1)), ..., error_estimates(index_of_decreasingly_sorted_error(k))
c                     form a decreasing sequence, with k = nb_of_subintervals
c                     if nb_of_subintervals.le.(max_nb_of_subintervals/2+2), and k = max_nb_of_subintervals+1-nb_of_subintervals
c                     otherwise
c
c            nb_of_subintervals   - integer
c                     number of subintervals actually produced in the
c                     subdivision process
c
c***references  (none)
c***routines called  d1mach,dqelg,dqk21,dqpsrt
c***end prologue  dqagse
c
      double precision a,abseps,estimate_of_absolute_error,left_end_points,area,area1,area12,area2,a1,
     *  a2,b,right_end_points,b1,b2,correc,dabs,defabs,defab1,defab2,d1mach,dmax1,
     *  dres,error_estimates,epmach,absolute_tolerance,relative_tolerance,erlarg,erlast,errbnd,errmax,
     *  error1,error2,erro12,errsum,ertest,f,overflow,resabs,reseps,result,
     *  res3la,integral_approximation,rlist2,small,underflow
      integer id,error_code,ierro,index_of_decreasingly_sorted_error,iroff1,iroff2,iroff3,jupbnd,k,ksgn,
     *  ktmin,nb_of_subintervals,max_nb_of_subintervals,maxerr,nb_of_function_evaluations,nres,nrmax,numrl2
      logical extrap,noext
c
      dimension left_end_points(max_nb_of_subintervals),right_end_points(max_nb_of_subintervals),error_estimates(max_nb_of_subintervals),index_of_decreasingly_sorted_error(max_nb_of_subintervals),
     * res3la(3),integral_approximation(max_nb_of_subintervals),rlist2(52)
c
      integer save obj
      external f
c
c            the dimension of rlist2 is determined by the value of
c            limexp in subroutine dqelg (rlist2 should be of dimension
c            (limexp+2) at least).
c
c            list of major variables
c            -----------------------
c
c           left_end_points     - list of left end points of all subintervals
c                       considered up to now
c           right_end_points     - list of right end points of all subintervals
c                       considered up to now
c           integral_approximation(i)  - approximation to the integral over
c                       (left_end_points(i),right_end_points(i))
c           rlist2    - array of dimension at least limexp+2 containing
c                       the part of the epsilon table which is still
c                       needed for further computations
c           error_estimates(i)  - error estimate applying to integral_approximation(i)
c           maxerr    - pointer to the interval with largest error
c                       estimate
c           errmax    - error_estimates(maxerr)
c           erlast    - error on the interval currently subdivided
c                       (before that subdivision has taken place)
c           area      - sum of the integrals over the subintervals
c           errsum    - sum of the errors over the subintervals
c           errbnd    - requested accuracy max(absolute_tolerance,relative_tolerance*
c                       abs(result))
c           *****1    - variable for the left interval
c           *****2    - variable for the right interval
c           nb_of_subintervals      - index for subdivision
c           nres      - number of calls to the extrapolation routine
c           numrl2    - number of elements currently in rlist2. if an
c                       appropriate approximation to the compounded
c                       integral has been obtained it is put in
c                       rlist2(numrl2) after numrl2 has been increased
c                       by one.
c           small     - length of the smallest interval considered up
c                       to now, multiplied by 1.5
c           erlarg    - sum of the errors over the intervals larger
c                       than the smallest interval considered up to now
c           extrap    - logical variable denoting that the routine is
c                       attempting to perform extrapolation i.e. before
c                       subdividing the smallest interval we try to
c                       decrease the value of erlarg.
c           noext     - logical variable denoting that extrapolation
c                       is no longer allowed (true value)
c
c            machine dependent constants
c            ---------------------------
c
c           epmach is the largest relative spacing.
c           underflow is the smallest positive magnitude.
c           overflow is the largest positive magnitude.
c
c***first executable statement  dqagse
      epmach = d1mach(4)
      write(*,*) 'dqagse.f 218: error_code = ', error_code
c
c            test on validity of parameters
c            ------------------------------
      error_code = 0
      nb_of_function_evaluations = 0
      nb_of_subintervals = 0
      result = 0.0d+00
      estimate_of_absolute_error = 0.0d+00
      left_end_points(1) = a
      right_end_points(1) = b
      integral_approximation(1) = 0.0d+00
      error_estimates(1) = 0.0d+00
      if(absolute_tolerance.le.0.0d+00.and.relative_tolerance.lt.dmax1(0.5d+02*epmach,0.5d-28))
     *   error_code = 6
      write(*,*) 'dqagse.f 233: error_code = ', error_code
      if(error_code.eq.6) go to 999
      write(*,*) 'dqagse.f 235: error_code = ', error_code
c
c           first approximation to the integral
c           -----------------------------------
c
      underflow = d1mach(1)
      overflow = d1mach(2)
      ierro = 0
      write(*,*) 'dqagse.f 243: error_code = ', error_code
      call dqk21(f,obj,a,b,result,estimate_of_absolute_error,defabs,resabs)
      write(*,*) 'dqagse.f 245: error_code = ', error_code
c
c           test on accuracy.
c
      dres = dabs(result)
      errbnd = dmax1(absolute_tolerance,relative_tolerance*dres)
      nb_of_subintervals = 1
      integral_approximation(1) = result
      error_estimates(1) = estimate_of_absolute_error
      index_of_decreasingly_sorted_error(1) = 1
      if(estimate_of_absolute_error.le.1.0d+02*epmach*defabs.and.estimate_of_absolute_error.gt.errbnd) error_code = 2
      if(max_nb_of_subintervals.eq.1) error_code = 1
      if(error_code.ne.0.or.(estimate_of_absolute_error.le.errbnd.and.estimate_of_absolute_error.ne.resabs).or.
     *  estimate_of_absolute_error.eq.0.0d+00) go to 140
c
c           initialization
c           --------------
c
      rlist2(1) = result
      errmax = estimate_of_absolute_error
      maxerr = 1
      area = result
      errsum = estimate_of_absolute_error
      estimate_of_absolute_error = overflow
      nrmax = 1
      nres = 0
      numrl2 = 2
      ktmin = 0
      extrap = .false.
      noext = .false.
      iroff1 = 0
      iroff2 = 0
      iroff3 = 0
      ksgn = -1
      if(dres.ge.(0.1d+01-0.5d+02*epmach)*defabs) ksgn = 1
c
c           main do-loop
c           ------------
c
      do 90 nb_of_subintervals = 2,max_nb_of_subintervals
c
c           bisect the subinterval with the nrmax-th largest error
c           estimate.
c
        a1 = left_end_points(maxerr)
        b1 = 0.5d+00*(left_end_points(maxerr)+right_end_points(maxerr))
        a2 = b1
        b2 = right_end_points(maxerr)
        erlast = errmax
        call dqk21(f,obj,a1,b1,area1,error1,resabs,defab1)
        call dqk21(f,obj,a2,b2,area2,error2,resabs,defab2)
c
c           improve previous approximations to integral
c           and error and test for accuracy.
c
        area12 = area1+area2
        erro12 = error1+error2
        errsum = errsum+erro12-errmax
        area = area+area12-integral_approximation(maxerr)
        if(defab1.eq.error1.or.defab2.eq.error2) go to 15
        if(dabs(integral_approximation(maxerr)-area12).gt.0.1d-04*dabs(area12)
     *  .or.erro12.lt.0.99d+00*errmax) go to 10
        if(extrap) iroff2 = iroff2+1
        if(.not.extrap) iroff1 = iroff1+1
   10   if(nb_of_subintervals.gt.10.and.erro12.gt.errmax) iroff3 = iroff3+1
   15   integral_approximation(maxerr) = area1
        integral_approximation(nb_of_subintervals) = area2
        errbnd = dmax1(absolute_tolerance,relative_tolerance*dabs(area))
c
c           test for roundoff error and eventually set error flag.
c
        if(iroff1+iroff2.ge.10.or.iroff3.ge.20) error_code = 2
      write(*,*) ' A315 error_code = ', error_code
        if(iroff2.ge.5) ierro = 3
c
c           set error flag in the case that the number of subintervals
c           equals max_nb_of_subintervals.
c
        if(nb_of_subintervals.eq.max_nb_of_subintervals) error_code = 1
c
c           set error flag in the case of bad integrand behaviour
c           at a point of the integration range.
c
        if(dmax1(dabs(a1),dabs(b2)).le.(0.1d+01+0.1d+03*epmach)*
     *  (dabs(a2)+0.1d+04*underflow)) error_code = 4
c
c           append the newly-created intervals to the list.
c
      write(*,*) 'dqagse.f 331: error_code = ', error_code
        if(error2.gt.error1) go to 20
        left_end_points(nb_of_subintervals) = a2
        right_end_points(maxerr) = b1
        right_end_points(nb_of_subintervals) = b2
        error_estimates(maxerr) = error1
        error_estimates(nb_of_subintervals) = error2
        go to 30
   20   left_end_points(maxerr) = a2
        left_end_points(nb_of_subintervals) = a1
        right_end_points(nb_of_subintervals) = b1
        integral_approximation(maxerr) = area2
        integral_approximation(nb_of_subintervals) = area1
        error_estimates(maxerr) = error2
        error_estimates(nb_of_subintervals) = error1
c
c           call subroutine dqpsrt to maintain the descending ordering
c           in the list of error estimates and select the subinterval
c           with nrmax-th largest error estimate (to be bisected next).
c
   30   call dqpsrt(max_nb_of_subintervals,nb_of_subintervals,maxerr,errmax,error_estimates,index_of_decreasingly_sorted_error,nrmax)
c ***jump out of do-loop
        if(errsum.le.errbnd) go to 115
c ***jump out of do-loop
      write(*,*) 'dqagse.f 355: error_code = ', error_code
        if(error_code.ne.0) go to 100
        if(nb_of_subintervals.eq.2) go to 80
        if(noext) go to 90
        erlarg = erlarg-erlast
        if(dabs(b1-a1).gt.small) erlarg = erlarg+erro12
        if(extrap) go to 40
c
c           test whether the interval to be bisected next is the
c           smallest interval.
c
        if(dabs(right_end_points(maxerr)-left_end_points(maxerr)).gt.small) go to 90
        extrap = .true.
        nrmax = 2
   40   if(ierro.eq.3.or.erlarg.le.ertest) go to 60
c
c           the smallest interval has the largest error.
c           before bisecting decrease the sum of the errors over the
c           larger intervals (erlarg) and perform extrapolation.
c
        id = nrmax
        jupbnd = nb_of_subintervals
        if(nb_of_subintervals.gt.(2+max_nb_of_subintervals/2)) jupbnd = max_nb_of_subintervals+3-nb_of_subintervals
        do 50 k = id,jupbnd
          maxerr = index_of_decreasingly_sorted_error(nrmax)
          errmax = error_estimates(maxerr)
c ***jump out of do-loop
          if(dabs(right_end_points(maxerr)-left_end_points(maxerr)).gt.small) go to 90
          nrmax = nrmax+1
   50   continue
c
c           perform extrapolation.
c
   60   numrl2 = numrl2+1
        rlist2(numrl2) = area
        call dqelg(numrl2,rlist2,reseps,abseps,res3la,nres)
        ktmin = ktmin+1
        if(ktmin.gt.5.and.estimate_of_absolute_error.lt.0.1d-02*errsum) error_code = 5
        if(abseps.ge.estimate_of_absolute_error) go to 70
        ktmin = 0
        estimate_of_absolute_error = abseps
        result = reseps
        correc = erlarg
        ertest = dmax1(absolute_tolerance,relative_tolerance*dabs(reseps))
c ***jump out of do-loop
        if(estimate_of_absolute_error.le.ertest) go to 100
c
c           prepare bisection of the smallest interval.
c
   70   if(numrl2.eq.1) noext = .true.
        if(error_code.eq.5) go to 100
        maxerr = index_of_decreasingly_sorted_error(1)
        errmax = error_estimates(maxerr)
        nrmax = 1
        extrap = .false.
        small = small*0.5d+00
        erlarg = errsum
        go to 90
   80   small = dabs(b-a)*0.375d+00
        erlarg = errsum
        ertest = errbnd
        rlist2(2) = area
   90 continue
c
c           set final result and error estimate.
c           ------------------------------------
c
  100 if(estimate_of_absolute_error.eq.overflow) go to 115
      if(error_code+ierro.eq.0) go to 110
      if(ierro.eq.3) estimate_of_absolute_error = estimate_of_absolute_error+correc
      if(error_code.eq.0) error_code = 3
      if(result.ne.0.0d+00.and.area.ne.0.0d+00) go to 105
      if(estimate_of_absolute_error.gt.errsum) go to 115
      if(area.eq.0.0d+00) go to 130
      go to 110
  105 if(estimate_of_absolute_error/dabs(result).gt.errsum/dabs(area)) go to 115
c
c           test on divergence.
c
  110 if(ksgn.eq.(-1).and.dmax1(dabs(result),dabs(area)).le.
     * defabs*0.1d-01) go to 130
      if(0.1d-01.gt.(result/area).or.(result/area).gt.0.1d+03
     * .or.errsum.gt.dabs(area)) error_code = 6
      go to 130
c
c           compute global integral sum.
c
  115 result = 0.0d+00
      do 120 k = 1,nb_of_subintervals
         result = result+integral_approximation(k)
  120 continue
      estimate_of_absolute_error = errsum
  130 if(error_code.gt.2) error_code = error_code-1
  140 nb_of_function_evaluations = 42*nb_of_subintervals-21
  999 return
      end
