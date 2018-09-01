# Sirehna's Scientific Computing (SSC) framework

[![Build Status](https://travis-ci.org/Gjacquenot/ssc.svg?branch=master)](https://travis-ci.org/Gjacquenot/ssc)
[![codecov](https://codecov.io/gh/Gjacquenot/ssc/branch/master/graph/badge.svg)](https://codecov.io/gh/Gjacquenot/ssc)
[![](https://images.microbadger.com/badges/image/gjacquenot/ssc.svg)](https://microbadger.com/images/gjacquenot/ssc "ssc layers")
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

This package provides C++ utilities that are used in several projects at [Sirehna](http://sirehna.com).

To use `ssc` for your own program, you can pull the associated docker image:

    docker pull gjacquenot/ssc

To run all tests, you can run the following command:

    docker run gjacquenot/ssc /bin/bash -c "cd ssc/bin && ./run_all_tests"

To build `ssc`, you can pull the following image that contains all dependencies:

    docker pull gjacquenot/ssc_build

These two images are based on Debian 8 and use GCC/G++/GFortran 4.9.

## Description

This package contains:

- **csv_file_reader**:         Reads CSV (comma-separated values) text files in a
                               std::map.
- **data_source**:             Manage data transfers between computation modules with lazy
                               evaluation, forward- and backward-chaining.
- **decode_unit**:             Convert a string containing a physical unit to a conversion
                               factor to USI.
- **exception_handling**:      Custom exceptions, with debug data (file & line number) &
                               useful macros.
- **functors_for_optimizer**:  Simple computer algebra system.
- **functional_programming**:  For_each, etc.
- **generic_pimpl**:           Implementation of Herb Sutter's generic PIMPL
                               idiom.
- **geometry**:                Calculate shortest paths & loxodromes on geoids
                               & find if a point is inside a polygon defined on a
                               geoid.
- **integrate**:               Numerical integration of a scalar function on an
                               interval (not necessarily compact). Generic
                               interface.
- **interpolation**:           Perform 1D & 2D interpolation (piecewise constant, linear,
                               spline) with constant or variable step.
- **ipopt_interface**:         Interface to the IPOPT solver, to be used with
                               the `optimizer` module.
- **kinematics**:              Compute coordinate transform matrices between two
                               reference frames, minimizing the number of computations
                               (uses the `data_source` module & boost**:**:graph internally).
- **lpsolve_interface**:       Interface to use the linear programming solver
                               LP solve with the optimization module.
- **macros**:                  Useful macros for traces (eg. COUT on steroids) & unit
                               tests.
- **numeric**:                 Kahan sum, pairwise sum, almost_equal (within 4 ULP).
- **optimizer**:               Generic optimization module, with a simple
                               computer algebra system (`functors_for_optimizer`).
- **random_data_generator**:   Generate random test data, uniformly distributed,
                               between two values, excluding certain values, etc. Used
                               mainly for unit testing.
- **solver**:                  Integrate any ordinary differential equation, using
                               any stepper (RK4, RKCK, Euler...).
- **text_file_reader**:        Read the contents of one or several files into a
                               std::string.
- **websocket**:               Send & receive data through websockets in real
                               time. Client & server.
- **yaml_parser**:             Thin wrapper around yaml-cpp.
