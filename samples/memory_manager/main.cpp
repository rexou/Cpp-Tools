/*
** main.cpp for test utilities
** by le-cor_w aka rexou
*/

#include <iostream>

#include <Debug/memory_manager/memory_manager.hpp>

#define DEFAULT_LOGFILE_NAME "memory_leaks.report"

struct A
{
  A() {
    std::cout << "A::A()" << std::endl;
  }

  ~A() {
    std::cout << "A::~A" << std::endl;
  }

  A(const A &other) {
    (void)other;
    std::cout << "A::A(const A &)" << std::endl;
  }

  void foo() {
    std::cout << "void A::foo()" << std::endl;
  }
};

int main()
{
  if (!(Debug::MemoryManager::init(DEFAULT_LOGFILE_NAME)))
    return 1;

  A *_a = new A;
  A *__a = new A();
  A *___a = new A[2];

  (void)__a;

  delete _a;
  delete [] ___a;

  Debug::MemoryManager::report_leaks();
}
