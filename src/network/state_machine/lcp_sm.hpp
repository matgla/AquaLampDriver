#include <boost/sml.hpp>

// states
class Initial;
class Starting;
class Closed;
class Stopped;
class Closing;
class Stopping;
class RequestSent;
class AckReceived;
class AckSent;
class Opened;

//events
// clang-format off
class Up {};
class Down {};
class Open {};
class Close {};
class Timeout {};
class TimeoutExpired {};
class ConfigureRequestGood {};
class ConfigureRequestBad {};
class ConfigureAck {};
class ConfigureNak {};
class TerminateRequest {};
class TerminateAck {};
class UnknownCode {};
class ProtocolRejectPermitted {};
class ProtocolRejectCatastrophic {};
class EchoRequest {};
// clang-format on

// guards
//const auto

// actions
const auto layerUp = [] {};
const auto layerDown = [] {};
const auto layerStarted = [] {};
const auto layerFinished = [] {};
const auto initRestartCounter = [] {};
const auto zeroRestartCounter = [] {};
const auto sendConfigureReq = [] {};
const auto sendConfigureAck = [] {};
const auto sendTerminateReq = [] {};
const auto sendTerminateAck = [] {};
const auto sendCodeReject = [] {};
const auto sendEchoReply = [] {};

class LcpSm
{
    auto operator()() const
    {
        // clang-format off
        return boost::sml::make_transitions_table(
            //|--------STATE--------|------------EVENT---------------|--GUARD---|------------ACTION-------------|--------TARGET--------|//
              *state<Initial>       + event<Up>                                                                 = state<Closed>,
               state<Initial>       + event<Open>                               / layerStarted                  = state<Starting>,
               state<Initial>       + event<Close>                                                              = state<Initial>,

               state<Starting>      + event<Up>                                 / []() { initRestartCounter();
                                                                                         sendConfigureReq(); }  = state<RequestSent>,
               state<Starting>      + event<Open>                                                               = state<Starting>,
               state<Starting>      + event<Close>                              / layerFinished                 = state<Initial>,

               state<Closed>        + event<Down>                                                               = state<Initial>,
               state<Closed>        + event<Open>                               / []() { initRestartCounter();
                                                                                         sendConfigureReq(); }  = state<RequestSent>,
               state<Closed>        + event<Close>                                                              = state<Closed>,
               state<Closed>        + event<ConfigureRequestGood>               / sendTerminateAck              = state<Closed>,
               state<Closed>        + event<ConfigureRequestBad>                / sendTerminateAck              = state<Closed>,
               state<Closed>        + event<ConfigureAck>                       / sendTerminateAck              = state<Closed>,
               state<Closed>        + event<ConfigureNak>                       / sendTerminateAck              = state<Closed>,
               state<Closed>        + event<TerminateRequest>                   / sendTerminateAck              = state<Closed>,
               state<Closed>        + event<TerminateAck>                                                       = state<Closed>,
               state<Closed>        + event<UnknownCode>                        / sendCodeReject                = state<Closed>,
               state<Closed>        + event<ProtocolRejectPermitted>                                            = state<Closed>,
               state<Closed>        + event<ProtocolRejectCatastrophic>         / layerFinished                 = state<Closed>,
               state<Closed>        + event<EchoRequest>                                                        = state<Closed>,

               state<Stopped>       + event<Down>                               / layerStarted                  = state<Starting>,
               state<Stopped>       + event<Open>                                                               = state<Stopped>,
               state<Stopped>       + event<Close>                                                              = state<Closed>,
               state<Stopped>       + event<ConfigureRequestGood>               / []() { initRestartCounter();
                                                                                         sendConfigureReq();
                                                                                         sendConfigureAck(); }  = state<AckSent>,
               state<Stopped>       + event<ConfigureRequestBad>                / []() { initRestartCounter();
                                                                                         sendConfigureReq();
                                                                                         sendConfigureNak(); }  = state<RequestSent>,
               state<Stopped>       + event<ConfigureAck>                       / sendTerminateAck              = state<Stopped>,
               state<Stopped>       + event<ConfigureNak>                       / sendTerminateAck              = state<Stopped>,
               state<Stopped>       + event<TerminateRequest>                   / sendTerminateAck              = state<Stopped>,
               state<Stopped>       + event<TerminateAck>                                                       = state<Stopped>,
               state<Stopped>       + event<UnknownCode>                        / sendCodeReject                = state<Stopped>,
               state<Stopped>       + event<ProtocolRejectPermitted>                                            = state<Stopped>,
               state<Stopped>       + event<ProtocolRejectCatastrophic>         / layerFinished                 = state<Stopped>,
               state<Stopped>       + event<EchoRequest>                                                        = state<Stopped>,

               state<Closing>       + event<Down>                                                               = state<Initial>,
               state<Closing>       + event<Open>                                                               = state<Stopping>,
               state<Closing>       + event<Close>                                                              = state<Closing>,
               state<Closing>       + event<Timeout>                            / sendTerminateReq              = state<Closing>,
               state<Closing>       + event<TimeoutExpired>                     / layerFinished                 = state<Closed>,
               state<Closing>       + event<ConfigureRequestGood>                                               = state<Closing>,
               state<Closing>       + event<ConfigureRequestBad>                                                = state<Closing>,
               state<Closing>       + event<ConfigureAck>                                                       = state<Closing>,
               state<Closing>       + event<ConfigureNak>                                                       = state<Closing>,
               state<Closing>       + event<TerminateRequest>                   / sendTerminateAck              = state<Closing>,
               state<Closing>       + event<TerminateAck>                       / layerFinished                 = state<Closed>,
               state<Closing>       + event<UnknownCode>                        / sendCodeReject                = state<Closing>,
               state<Closing>       + event<ProtocolRejectPermitted>                                            = state<Closing>,
               state<Closing>       + event<ProtocolRejectCatastrophic>         / layerFinished                 = state<Closed>,
               state<Closing>       + event<EchoRequest>                                                        = state<Closing>,

               state<Stopping>      + event<Down>                                                               = state<Starting>,
               state<Stopping>      + event<Open>                                                               = state<Stopping>,
               state<Stopping>      + event<Close>                                                              = state<Closing>,
               state<Stopping>      + event<Timeout>                            / sendTerminateReq              = state<Stopping>,
               state<Stopping>      + event<TimeoutExpired>                     / layerFinished                 = state<Stopped>,
               state<Stopping>      + event<ConfigureRequestGood>                                               = state<Stopping>,
               state<Stopping>      + event<ConfigureRequestBad>                                                = state<Stopping>,
               state<Stopping>      + event<ConfigureAck>                                                       = state<Stopping>,
               state<Stopping>      + event<ConfigureNak>                                                       = state<Stopping>,
               state<Stopping>      + event<TerminateRequest>                   / sendTerminateAck              = state<Stopping>,
               state<Stopping>      + event<TerminateAck>                       / layerFinished                 = state<Stopped>,
               state<Stopping>      + event<UnknownCode>                        / sendCodeReject                = state<Stopping>,
               state<Stopping>      + event<ProtocolRejectPermitted>                                            = state<Stopping>,
               state<Stopping>      + event<ProtocolRejectCatastrophic>         / layerFinished                 = state<Stopped>,
               state<Stopping>      + event<EchoRequest>                                                        = state<Stopping>,

               state<RequestSent>   + event<Down>                                                               = state<Starting>,
               state<RequestSent>   + event<Open>                                                               = state<RequestAck>,
               state<RequestSent>   + event<Close>                              / []() { initRestartCounter();
                                                                                         sendTerminateAck(); }  = state<Closing>,
               state<RequestSent>   + event<Timeout>                            / sendConfigureReq              = state<RequestSent>,
               state<RequestSent>   + event<TimeoutExpired>                     / layerFinished                 = state<Stopped>,
               state<RequestSent>   + event<ConfigureRequestGood>               / sendConfigureAck              = state<AckSent>,
               state<RequestSent>   + event<ConfigureRequestBad>                / sendConfigureNak              = state<RequestSent>,
               state<RequestSent>   + event<ConfigureAck>                       / initRestartCounter            = state<AckReceived>,
               state<RequestSent>   + event<ConfigureNak>                       []() { initRestartCounter();
                                                                                       sendConfigureReq(); }    = state<RequestSent>,
               state<RequestSent>   + event<TerminateRequest>                   / sendTerminateAck              = state<RequestSent>,
               state<RequestSent>   + event<TerminateAck>                                                       = state<RequestSent>,
               state<RequestSent>   + event<UnknownCode>                        / sendCodeReject                = state<RequestSent>,
               state<RequestSent>   + event<ProtocolRejectPermitted>                                            = state<RequestSent>,
               state<RequestSent>   + event<ProtocolRejectCatastrophic>         / layerFinished                 = state<Stopped>,
               state<RequestSent>   + event<EchoRequest>                                                        = state<RequestSent>,

               state<AckReceived>   + event<Down>                                                               = state<Starting>,
               state<AckReceived>   + event<Open>                                                               = state<AckReceived>,
               state<AckReceived>   + event<Close>                              / []() { initRestartCounter();
                                                                                         sendTerminateAck(); }  = state<Closing>,
               state<AckReceived>   + event<Timeout>                            / sendConfigureReq              = state<RequestSent>,
               state<AckReceived>   + event<TimeoutExpired>                     / layerFinished                 = state<Stopped>,
               state<AckReceived>   + event<ConfigureRequestGood>               / []() { sendConfigureAck();
                                                                                         layerUp(); }           = state<Opened>,
               state<AckReceived>   + event<ConfigureRequestBad>                / sendConfigureNak              = state<AckReceived>,
               state<AckReceived>   + event<ConfigureAck>                       / sendConfigureReq              = state<RequestSent>,
               state<AckReceived>   + event<ConfigureNak>                       / sendConfigureReq              = state<RequestSent>,
               state<AckReceived>   + event<TerminateRequest>                   / sendTerminateAck              = state<RequestSent>,
               state<AckReceived>   + event<TerminateAck>                                                       = state<RequestSent>,
               state<AckReceived>   + event<UnknownCode>                        / sendCodeReject                = state<AckReceived>,
               state<AckReceived>   + event<ProtocolRejectPermitted>                                            = state<RequestSent>,
               state<AckReceived>   + event<ProtocolRejectCatastrophic>         / layerFinished                 = state<Stopped>,
               state<AckReceived>   + event<EchoRequest>                                                        = state<AckReceived>,

               state<AckSent>       + event<Down>                                                               = state<Starting>,
               state<AckSent>       + event<Open>                                                               = state<AckSent>,
               state<AckSent>       + event<Close>                              / []() { initRestartCounter();
                                                                                         sendTerminateAck(); }  = state<Closing>,
               state<AckSent>       + event<Timeout>                            / sendConfigureReq              = state<AckSent>,
               state<AckSent>       + event<TimeoutExpired>                     / layerFinished                 = state<Stopped>,
               state<AckSent>       + event<ConfigureRequestGood>               / sendConfigureAck              = state<AckSent>,
               state<AckSent>       + event<ConfigureRequestBad>                / sendConfigureNak              = state<RequestSent>,
               state<AckSent>       + event<ConfigureAck>                       / []() { initRestartCounter();
                                                                                         layerUp(); }           = state<Opened>,
               state<AckSent>       + event<ConfigureNak>                       / []() { initRestartCounter();
                                                                                         sendConfigureReq(); }  = state<AckSent>,
               state<AckSent>       + event<TerminateRequest>                   / sendTerminateAck              = state<RequestSent>,
               state<AckSent>       + event<TerminateAck>                                                       = state<AckSent>,
               state<AckSent>       + event<UnknownCode>                        / sendCodeReject                = state<AckSent>,
               state<AckSent>       + event<ProtocolRejectPermitted>                                            = state<AckSent>,
               state<AckSent>       + event<ProtocolRejectCatastrophic>         / layerFinished                 = state<Stopped>,
               state<AckSent>       + event<EchoRequest>                                                        = state<AckSent>,

               state<Opened>       + event<Down>                                / layerDown                     = state<Starting>,
               state<Opened>       + event<Open>                                                                = state<Opened>,
               state<Opened>       + event<Close>                              / []() { layerDown();
                                                                                        initRestartCounter();
                                                                                        sendTerminateAck(); }  = state<Closing>,
               state<Opened>       + event<ConfigureRequestGood>               / []() { layerDown();
                                                                                        sendConfigureReq();
                                                                                        sendConfigureAck(); }  = state<AckSent>,
               state<Opened>       + event<ConfigureRequestBad>                / []() { layerDown();
                                                                                        sendConfigureReq();
                                                                                        sendConfigureAck(); }  = state<RequestSent>,
               state<Opened>       + event<ConfigureAck>                       / []() { layerDown();
                                                                                        sendConfigureReq(); }  = state<RequestSent>,
               state<Opened>       + event<ConfigureNak>                       / []() { layerDown();
                                                                                        sendConfigureReq(); }  = state<RequestSent>,
               state<Opened>       + event<TerminateRequest>                   / []() { layerDown();
                                                                                        zeroRestartCounter();
                                                                                        sendTerminateAck(); }  = state<Stopping>,
               state<Opened>       + event<TerminateAck>                       / []() { layerDown();
                                                                                        sendTerminateAck(); }  = state<RequestSent>,
               state<Opened>       + event<UnknownCode>                        / sendCodeReject                = state<Opened>,
               state<Opened>       + event<ProtocolRejectPermitted>                                            = state<Opened>,
               state<Opened>       + event<ProtocolRejectCatastrophic>         / []() { layerDown();
                                                                                        initRestartCounter();
                                                                                        sendTerminateReq(); }  = state<Stopping>,
               state<Opened>       + event<EchoRequest>                        / sendEchoReply                 = state<Opened>,
        );
        // clang-format on
    }
};