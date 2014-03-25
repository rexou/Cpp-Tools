#include <cassert>

#include "StateMachine.hpp"

StateMachine::StateMachine(Application *app) :
    mStack(),
    mPendingList(),
    mApp(app),
    mFactories()
{
}


State::Ptr StateMachine::createState(StateIdentifier id)
{
    auto found = mFactories.find(id);
    assert(found != mFactories.end());

    return found->second();
}

void StateMachine::update(double dt)
//void StateMachine::update(sf::Time dt)
{
    // Iterate from top to bottom, stop as soon as update() returns false
    for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
    {
        if (!((*it)->update(dt)))
            break;
    }

    applyPendingChanges();
}

void StateMachine::draw()
{
    // Draw all active states from bottom to top
    for(State::Ptr& state : mStack)
        state->draw();
}

// TODO : remove SFML dependency
//void StateMachine::handleEvent(const sf::Event &event)
//{
//    for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
//    {
//        if (!(*it)->handleEvent(event))
//            break;
//    }
//
//    applyPendingChanges();
//}

void StateMachine::pushState(StateIdentifier id)
{
    mPendingList.push_back(PendingChange(Push, id));
    applyPendingChanges();
}

void StateMachine::popState()
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateMachine::clearStates()
{
    mPendingList.push_back(PendingChange(Clear));
}

bool StateMachine::isEmpty() const
{
    return mStack.empty();
}

void StateMachine::applyPendingChanges()
{
    for(PendingChange change : mPendingList)
    {
        switch(change.action)
        {
            case Push:
                if(!mStack.empty())
                {
                    mStack.back()->onPause();
                }
                mStack.push_back(createState(change.stateIdentifier));
                mStack.back()->onInit();
                break;

            case Pop:
                mStack.back()->onClose();
                mStack.pop_back();
                if(!mStack.empty())
                {
                    mStack.back()->onResume();
                }
                break;

            case Clear:
                mStack.clear();
            break;
        }
    }

    mPendingList.clear();
}



StateMachine::PendingChange::PendingChange(Action action, StateIdentifier stateID) :
    action(action),
    stateIdentifier(stateID)
{
}


