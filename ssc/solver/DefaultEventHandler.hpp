/*
 * DefaultEventHandler.hpp
 *
 * \date 21 mars 2014
 * \author cec
 */

#ifndef DEFAULTEVENTHANDLER_HPP_
#define DEFAULTEVENTHANDLER_HPP_

namespace ssc
{
    namespace solver
    {
        class DefaultEventHandler
        {
            public:
                bool detected_state_events() const
                {
                    return false;
                }

                void locate_event()
                {
                }

                void run_event_actions()
                {
                }
        };
    }
}

#endif /* DEFAULTEVENTHANDLER_HPP_ */
