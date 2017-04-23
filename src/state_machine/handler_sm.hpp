#pragma once

#include <cstring>

#include <boost/sml.hpp>

#include "logger.hpp"
#include "state_machine/helpers.hpp"
#include "stm32f10x_conf.h"

void *__dso_handle;
namespace sml = boost::sml;

namespace handler
{
const int MSG_BUFFER_SIZE = 100;

class Idle;
class Handle;
class Dispatch;
class GotPart;
class Failed;

class evGetMsg
{
  public:
    evGetMsg(const char *msg)
    {
        assert(strlen(msg) < MSG_BUFFER_SIZE);
        memcpy(&msg_, msg, strlen(msg));
    }

    char *get() const
    {
        return (char *)&msg_;
    }

  private:
    char msg_[MSG_BUFFER_SIZE];
};
// clang-format off
class evSuccess {};
class evComplete {};
class evFail {};
class evGotPart {};
// clang-format on

struct HandlerSm
{
    auto operator()() noexcept
    {
        logger_.info() << "No nie dziala\n";
        using namespace sml;
        // clang-format off
        return make_transition_table(
            //|---------STATE----------|-----------EVENT-----------|-------GUARD--------|-----------------ACTION------------------|--------TARGET----------|//
              *state<Idle>             + event<evGetMsg>                                / call(this, &HandlerSm::handle)          = state<Handle>
        );
        // clang-format on
    }
    Logger logger_{"HandlerSM\0"};

  private:
    void handle(const evGetMsg &msg)
    {
        logger_.info() << "Received msg: " << msg.get() << "\n";
    };
};

} // namespace handler
