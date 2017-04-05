#include <boost/sml.hpp>

// states
class Dead;
class Enstablish;
class Authenticate;
class Terminate;
class Network;

//events
// clang-format off
class Up {};
class Down {};
class Opened {};
class Success {};
class None {};
class Fail {};
class Down {};
class Closing {};
// clang-format on

// guards
//const auto

class PppSm
{
    auto operator()() const
    {
        // clang-format off
        return boost::sml::make_transitions_table(
            //|--------STATE--------|--------EVENT--------|--------GUARD--------|--------ACTION--------|--------TARGET--------|//
              *state<Dead>          + event<Up>                                                        = state<Establish>,
               state<Establish>     + event<Opened>                                                    = state<Authenticate>,
               state<Establish>     + event<Fail>                                                      = state<Dead>,
               state<Authenticate>  + event<Success>                                                   = state<Network>,
               state<Authenticate>  + event<None>                                                      = state<Network>,
               state<Authenticate>  + event<Fail>                                                      = state<Terminate>,
               state<Network>       + event<Close>                                                     = state<Terminate>,
               state<Terminate>     + event<Down>                                                      = state<Dead>
        );
        // clang-format on
    }
};