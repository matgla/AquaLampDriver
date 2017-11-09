#pragma once

class Fsm
{
public:
    template <typename State, typename Event>
    void process_event(const Event& event)
    {
        UNUSED(event);
        // action()
    }

    // template <typename State, State state, typename Event>
    // void action(const State& state, const Event& event)
    // {
    //     UNUSED(event);
    // }
};