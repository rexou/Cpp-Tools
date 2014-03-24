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
  //virtual bool    update(sf::Time dt) = 0;
  // update() return true if states beneath it should be updated, false otherwise (e.g update() will return false for a PauseState)
  virtual bool    update(double dt) { return true; }; // TODO : Replace this with the sfml timer instead of double dt
  //virtual bool    handleEvent(const sf::Event& event) = 0; // TODO : Remove the sfml dependency by creating a wrapper for events

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
