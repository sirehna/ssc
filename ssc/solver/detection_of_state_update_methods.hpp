/*
 * detection_of_state_update_methods.hpp
 *
 * \date 21 mars 2014
 *      Author: cec
 */

#ifndef DETECTION_OF_STATE_UPDATE_METHODS_HPP_
#define DETECTION_OF_STATE_UPDATE_METHODS_HPP_

namespace ssc
{
    namespace solver
    {
        template <typename SystemType, bool has_update_methods>
        struct update
        {
            static void if_possible(SystemType& )
            {
            }
        };

        template <typename SystemType>
        struct update<SystemType,true>
        {
            static void if_possible(SystemType& sys)
            {
                sys.update_discrete_states();
            }
        };


        #define HAS(func, name)                                        \
            template<typename T, typename Sign>                                 \
            struct name                                                         \
            {                                                                   \
                typedef char yes[1];                                            \
                typedef char no [2];                                            \
                template <typename U, U> struct type_check;                     \
                template <typename _1> static yes &chk(type_check<Sign, &_1::func> *); \
                template <typename   > static no  &chk(...);                    \
                static bool const value = sizeof(chk<T>(0)) == sizeof(yes);     \
            }

        HAS(update_discrete_states, class_can_update_discrete_states);

        template <typename T>
        struct can
        {
            static const bool update_discrete_states = class_can_update_discrete_states<T,void(T::*)()>::value;
        };
    }
}

#endif /* DETECTION_OF_STATE_UPDATE_METHODS_HPP_ */
