#include <iostream>

#include "State.hpp"

class IntroState : public State
{
  double total_time = 0.f;

public:

  IntroState(StateMachine &sm, Application *app) :
    State(sm, app)
  {}

  bool update(double dt) {
    total_time += dt;
    if (total_time > 10) {
      requestStackPop();
      requestStackPush(StateIdentifier::INTRO);
    }

    return true;
  }

  void draw() {
    std::cout << "IntroState::Draw() : TotalTime = " << total_time << std::endl;
  }
};

class Application
{
  StateMachine stateMachine;

public:

  Application() {
    stateMachine.registerState<IntroState>(StateIdentifier::INTRO);
  }
  
  void    init(StateIdentifier initial_state) {
    stateMachine.pushState(initial_state);
  }
    
  void    run() {
    while (!stateMachine.isEmpty()) {
    stateMachine.update(1); // TODO : Replace 1 with the real frametime
    stateMachine.draw();
    }
  }
};

int main() {
  Application app;

  app.init(StateIdentifier::INTRO);
  app.run();
}
