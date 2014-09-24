Sirehna's Scientific Computing (SSC) framework
==============================================

This package provides utilities that were used in several projects at Sirehna
(MAROFF, EONAV, IRT Simulator):

- **csv_file_reader**:       Reads CSV (comma-separated values) text files in a
                             std::map.
- **data_source**:           Manage data transfers between computation modules with lazy
                             evaluation, forward- and backward-chaining.
- **decode_unit**:           Convert a sting containing a physical unit to a conversion
                             factor to USI.
- **exception_handling**:    Custom exceptions, with debug data (file & line number) &
                             useful macros.
- **interpolation**:         Perform 1D & 2D interpolation (piecewise constant, linear,
                             spline) with constant or variable step.
- **kinematics**:            Compute coordinate transform matrices between two
                             reference frames, minimizing the number of computations
                             (uses the data_source module & boost**:**:graph internally)
- **macros**:                Useful macros for traces (eg. COUT on steroids) & unit
                             tests.
- **numeric**:               Kahan sum, pairwise sum, almost_equal (within 4 ULP)
- **random_data_generator**: Generate random test data, uniformly distributed,
                             between two values, excluding certain values, etc. Used
                             mainly for unit testing.
- **solver**:                Integrate any ordinary differential equation, using
                             any stepper (RK4, RKCK, Euler...).
- **text_file_reader**:      Read the contents of one or several files into a
                             std::string.
- **yaml_parser**:           Thin wrapper arround yaml-cpp.
