#include <iostream>

#include <assert.h>

#include "PropertyHolder.hpp"

struct Vec2i
{
    int     x, y;

    Vec2i(int _x = 0, int _y = 0) :
        x(_x),
        y(_y)
    {
    }
};


std::ostream &operator<<(std::ostream &out, const Vec2i &v) {
    out << "{" << v.x << ", " << v.y << "}";

    return out;
}

int main()
{
    try
    {
        PropertyHolder<std::string> p;

        p.setValue<int>("Health", 10);
        p.setValue<Vec2i>("Position", {2, 1});

        assert(p.hasKey("Health"));
        assert(p.hasKey("Position"));

        std::cout << p.getValue<int>("Health") << std::endl;
        p.setValue<int>("Health", 42);
        std::cout << p.getValue<int>("Health") << std::endl;
        std::cout << p.getValue<int>("Position") << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

/* Output of this sample
[rexou@rx-comp Property]$ ./sample
10
{2, 1}
42
PropertyHolder::getValue<T>(const Key &) : Requested type T != Property's type (requested "Position" as type "int")
*/
