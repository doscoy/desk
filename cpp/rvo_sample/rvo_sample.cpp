// common sense c++ vol.3
// 何回 piyo って鳴くかな？
#include <iostream>


class HiyokoMan
{
public:
    HiyokoMan()
    {
        std::cout << "piyo" << std::endl;
    }

    HiyokoMan(const HiyokoMan& rhs)
    {
        std::cout << "piyo" << std::endl;
    }
};

HiyokoMan createHiyoko()
{
    return HiyokoMan();
}
int main()
{
    HiyokoMan h = createHiyoko();
    return 0;
}
