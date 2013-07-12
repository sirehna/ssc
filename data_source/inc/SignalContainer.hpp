/*
 * SignalContainer.hpp
 *
 * \date 18 mars 2013, 17:52:42
 *  \author cec
 */

#ifndef SIGNALCONTAINER_HPP_
#define SIGNALCONTAINER_HPP_

/** \author cec
 *  \brief This class was created to store signals of different types
 *  \details It has the following responsibilities:
 *  - Store & retrieve signals by name
 *  - Convert a list of signal names (or all of its signals) to a vector of
 *    doubles (for Euler & RK integration)
 *  - Accept a visitor for serialization (eg. to an output file)
 *  \section ex1 Example
 *  \snippet data_source/unit_tests/src/SignalContainerTest.cpp SignalContainerTest example
 *  \section ex2 Expected output
 *  \snippet data_source/unit_tests/src/SignalContainerTest.cpp SignalContainerTest expected output
 */

class SignalContainer
{
    public:
        SignalContainer();
};

#endif /* SIGNALCONTAINER_HPP_ */
