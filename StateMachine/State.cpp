#include "State.hpp"
#include "StateMachine.hpp"

State::State(StateMachine &states, Application *app) :
    mStateMachine(&states),
    mApp(app)
{
}

State::~State()
{
    onClose();
}

void State::requestStackPush(StateIdentifier stateID)
{
    mStateMachine->pushState(stateID);
}

void State::requestStackPop()
{
    mStateMachine->popState();
}

void State::requestStackClear()
{
    mStateMachine->clearStates();
}
