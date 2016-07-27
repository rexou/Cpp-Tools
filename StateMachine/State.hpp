#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <memory>

#include "StateIdentifiers.hpp"

class StateMachine;
class Application;

class State
{
public:

  typedef std::unique_ptr<State> Ptr;

  State(const State &other) = delete;
  State &operator=(const State &other) = delete;
  State(StateMachine &states, Application *);
  virtual ~State();

  virtual void    draw() {};
  virtual bool    update(double dt) { return true; };

  virtual void    onInit() {};
  virtual void    onPause() {}
  virtual void    onResume() {}
  virtual void    onClose() {};

protected:

    void            requestStackPush(StateIdentifier id);
    void            requestStackPop();
    void            requestStackClear();

private:

  StateMachine                  *mStateMachine;
  Application                   *mApp;
};

#endif // __STATE_HPP__
