
/*
** main.cpp for test utilities
** by le-cor_w aka rexou
*/

#include <iostream>

#include <memory_manager.hpp>

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

  A *basic_a = new A;
  A *basic_a2 = new A();
  A *array_a = new A[2];

  (void)basic_a;

  delete basic_a2;
  delete [] array_a;

  Debug::MemoryManager::report_leaks();
}
