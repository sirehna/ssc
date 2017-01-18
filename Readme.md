# Sirehna's Scientific Computing (SSC) framework


[![build status](https://gitlab.sirehna.com/root/scientific_computing/badges/master/build.svg)](https://gitlab.sirehna.com/root/scientific_computing/commits/master)

## Description

This package provides utilities that were used in several projects at Sirehna
(MAROFF, EONAV, IRT Simulator):

- **csv_file_reader**:         Reads CSV (comma-separated values) text files in a
                               std::map.
- **data_source**:             Manage data transfers between computation modules with lazy
                               evaluation, forward- and backward-chaining.
- **decode_unit**:             Convert a sting containing a physical unit to a conversion
                               factor to USI.
- **exception_handling**:      Custom exceptions, with debug data (file & line number) &
                               useful macros.
- **functors_for_optimizer**:  Simple computer algebra system.
- **functional_programming**:  For_each, etc.
- **generic_pimpl**:           Implementation of Herb Sutter's generic PIMPL
                               idiom.
- **geometry**:                Calculate shortest paths & loxodromes on geoids
                               & find if a point is inside a polygon defined on a
                               geoids.
- **integrate**:               Numerical integration of a scalar function on an
                               interval (not necessarily compact). Generic
                               interface
- **interpolation**:           Perform 1D & 2D interpolation (piecewise constant, linear,
                               spline) with constant or variable step.
- **ipopt_interface**:         Interface to the IPOPT solver, to be used with
                               the 'optimizer' module
- **kinematics**:              Compute coordinate transform matrices between two
                               reference frames, minimizing the number of computations
                               (uses the data_source module & boost**:**:graph internally)
- **lpsolve_interface**:       Interface to use the linear programming solver
                               LP solve with the optimization module
- **macros**:                  Useful macros for traces (eg. COUT on steroids) & unit
                               tests.
- **numeric**:                 Kahan sum, pairwise sum, almost_equal (within 4 ULP)
- **optimizer**:               Generic optimization module, with a simple
                               computer algebra system (functors_for_optimizer)
- **quadpack**:                Use Gaussian quadrature to integrate scalar
                               functions numerically. Developped by Netlib in
                               Fortran.
- **random_data_generator**:   Generate random test data, uniformly distributed,
                               between two values, excluding certain values, etc. Used
                               mainly for unit testing.
- **solver**:                  Integrate any ordinary differential equation, using
                               any stepper (RK4, RKCK, Euler...).
- **text_file_reader**:        Read the contents of one or several files into a
                               std::string.
- **yaml_parser**:             Thin wrapper around yaml-cpp.

## GitLab CI

To create a GitLab runner and register it for SSC CI, you should enter on the
slave machine, that has docker

    sudo gitlab-ci-multi-runner register \
        --non-interactive \
        --url "https://gitlab.sirehna.com/ci" \
        --registration-token "xxxxxxxxxxxxxxxxxxxx" \
        --executor shell \
        --description "SSC VM Runner that triggers Docker"

You have to replace `registration-token` with the project token
