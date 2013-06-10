      subroutine dqags(f,obj,a,b,absolute_tolerance,relative_tolerance,result,estimate_of_absolute_error,nb_of_function_evaluations,error_code,
     *   max_nb_of_subintervals,lenw,nb_of_subintervals,index_of_decreasingly_sorted_error,work)
c***begin prologue  dqags
c***date written   800101   (yymmdd)
c***revision date  830518   (yymmdd)
c***category no.  h2a1a1
c***keywords  automatic integrator, general-purpose,
c             (end-point) singularities, extrapolation,
c             globally adaptive
c***author  piessens,robert,appl. math. & progr. div. - k.u.leuven
c           de doncker,elise,appl. math. & prog. div. - k.u.leuven
c***purpose  the routine calculates an approximation result to a given
c            definite integral  i = integral of f over (a,b),
c            hopefully satisfying following claim for accuracy
c            abs(i-result).le.max(absolute_tolerance,relative_tolerance*abs(i)).
c***description
c
c        computation of a definite integral
c        standard fortran subroutine
c        double precision version
c
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
c                     error_code = 1 maximum number of subdivisions allowed
c                             has been achieved. one can allow more sub-
c                             divisions by increasing the value of max_nb_of_subintervals
c                             (and taking the according dimension
c                             adjustments into account. however, if
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
c                             extrapolation table. it is presumed that
c                             the requested tolerance cannot be
c                             achieved, and that the returned result is
c                             the best which can be obtained.
c                         = 5 the integral is probably divergent, or
c                             slowly convergent. it must be noted that
c                             divergence can occur with any other value
c                             of error_code.
c                         = 6 the input is invalid, because
c                             (absolute_tolerance.le.0 and
c                              relative_tolerance.lt.max(50*rel.mach.acc.,0.5d-28)
c                             or max_nb_of_subintervals.lt.1 or lenw.lt.max_nb_of_subintervals*4.
c                             result, estimate_of_absolute_error, nb_of_function_evaluations, nb_of_subintervals are set to
c                             zero.except when max_nb_of_subintervals or lenw is invalid,
c                             index_of_decreasingly_sorted_error(1), work(max_nb_of_subintervals*2+1) and
c                             work(max_nb_of_subintervals*3+1) are set to zero, work(1)
c                             is set to a and work(max_nb_of_subintervals+1) to b.
c
c         dimensioning parameters
c            max_nb_of_subintervals - integer
c                    dimensioning parameter for index_of_decreasingly_sorted_error
c                    max_nb_of_subintervals determines the maximum number of subintervals
c                    in the partition of the given integration interval
c                    (a,b), max_nb_of_subintervals.ge.1.
c                    if max_nb_of_subintervals.lt.1, the routine will end with error_code = 6.
c
c            lenw  - integer
c                    dimensioning parameter for work
c                    lenw must be at least max_nb_of_subintervals*4.
c                    if lenw.lt.max_nb_of_subintervals*4, the routine will end
c                    with error_code = 6.
c
c            nb_of_subintervals  - integer
c                    on return, nb_of_subintervals equals the number of subintervals
c                    produced in the subdivision process, detemines the
c                    number of significant elements actually in the work
c                    arrays.
c
c         work arrays
c            index_of_decreasingly_sorted_error - integer
c                    vector of dimension at least max_nb_of_subintervals, the first k
c                    elements of which contain pointers
c                    to the error estimates over the subintervals
c                    such that work(max_nb_of_subintervals*3+index_of_decreasingly_sorted_error(1)),... ,
c                    work(max_nb_of_subintervals*3+index_of_decreasingly_sorted_error(k)) form a decreasing
c                    sequence, with k = nb_of_subintervals if nb_of_subintervals.le.(max_nb_of_subintervals/2+2),
c                    and k = max_nb_of_subintervals+1-nb_of_subintervals otherwise
c
c            work  - double precision
c                    vector of dimension at least lenw
c                    on return
c                    work(1), ..., work(nb_of_subintervals) contain the left
c                     end-points of the subintervals in the
c                     partition of (a,b),
c                    work(max_nb_of_subintervals+1), ..., work(max_nb_of_subintervals+nb_of_subintervals) contain
c                     the right end-points,
c                    work(max_nb_of_subintervals*2+1), ..., work(max_nb_of_subintervals*2+nb_of_subintervals) contain
c                     the integral approximations over the subintervals,
c                    work(max_nb_of_subintervals*3+1), ..., work(max_nb_of_subintervals*3+nb_of_subintervals)
c                     contain the error estimates.
c
c***references  (none)
c***routines called  dqagse,xerror
c***end prologue  dqags
c
c
      double precision a,estimate_of_absolute_error,b,absolute_tolerance,relative_tolerance,f,result,work
      integer error_code,index_of_decreasingly_sorted_error,nb_of_subintervals,lenw,max_nb_of_subintervals,lvl,first_index_of_right_endpoints,first_index_of_integral_approximation,first_index_of_unsorted_error_estimate,nb_of_function_evaluations
      integer save obj
c
      dimension index_of_decreasingly_sorted_error(max_nb_of_subintervals),work(lenw)
c
      external f
c
c         check validity of max_nb_of_subintervals and lenw.
c
c***first executable statement  dqags
      error_code = 6
      nb_of_function_evaluations = 0
      nb_of_subintervals = 0
      result = 0.0d+00
      estimate_of_absolute_error = 0.0d+00
      if(max_nb_of_subintervals.lt.1.or.lenw.lt.max_nb_of_subintervals*4) go to 10
      write(*,*) 'dqags.f 173: error_code = ', error_code
c
c         prepare call for dqagse.
c
      first_index_of_right_endpoints = max_nb_of_subintervals+1
      first_index_of_integral_approximation = max_nb_of_subintervals+first_index_of_right_endpoints
      first_index_of_unsorted_error_estimate = max_nb_of_subintervals+first_index_of_integral_approximation
c
      write(*,*) 'obj = ', obj
      write(*,*) 'a = ', a
      write(*,*) 'b = ', b
      write(*,*) 'b = ', b
      write(*,*) 'dqags.f 181: error_code = ', error_code
      call dqagse(f,obj, a,b,absolute_tolerance,relative_tolerance,
	              max_nb_of_subintervals,result,estimate_of_absolute_error,
				  nb_of_function_evaluations,
				  error_code,
				  work(1),
				  work(first_index_of_right_endpoints),
				  work(first_index_of_integral_approximation),
				  work(first_index_of_unsorted_error_estimate),
				  index_of_decreasingly_sorted_error,
				  nb_of_subintervals)
      write(*,*) 'dqags.f 184: error_code = ', error_code
c
c         call error handler if necessary.
c
      lvl = 0
10    if(error_code.eq.6) lvl = 1
C      if(error_code.ne.0) call xerror(26habnormal return from dqags,26,error_code,lvl)
      write(*,*) 'dqags.f 189: error_code = ', error_code
      return
      end
