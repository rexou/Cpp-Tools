#include <iostream>

#include "Observable.hpp"

void bar() {
	std::cout << "bar()" << std::endl;
}

void foo(int nb) {
	std::cout << "foo(" << nb << ")" << std::endl;
}

int main(int argc, char const *argv[]) {
	Observable<std::string> s;

	s.registerObserver("GREEN", bar);
	s.registerObserver("ORANGE", std::bind(foo, 42));
	s.registerObserver("RED", std::bind(foo, 12345));

	s.registerObserver("RED", [&] {
			std::cout << "Hello RED event" << std::endl;
		});

	s.notify("GREEN");
	s.notify("ORANGE");
	s.notify("RED");

	return 0;
}
