#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "StateIdentifiers.hpp"
#include "State.hpp"

class Application;

class StateMachine
{
public:

    enum Action
    {
        Push,
        Pop,
        Clear
    };

    explicit StateMachine(Application *);

    template <typename T>
    void                registerState(StateIdentifier id);
    
    void                update(double dt);
    void                draw();

    void                pushState(StateIdentifier id);
    void                popState();
    void                clearStates();

    bool                isEmpty() const;

private:
    State::Ptr			    createState(StateIdentifier id);
    void				    applyPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action action, StateIdentifier id = StateIdentifier());
        Action                    action;
        StateIdentifier           stateIdentifier;
    };

private:
    std::vector<State::Ptr>                                           mStack;
    std::vector<PendingChange>                                        mPendingList;
    Application                                                       *mApp;
    std::map<StateIdentifier, std::function<State::Ptr()>>            mFactories;
};

template <typename T>
void StateMachine::registerState(StateIdentifier id)
{
  mFactories[id] = [this] ()
  {
    return State::Ptr(new T(*this, mApp));
  };
}

#endif // __STATE_MACHINE__
