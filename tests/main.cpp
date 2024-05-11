#include <xenyke/core/color.hpp>
#include <xenyke/core/debug.hpp>

int main()
{
    using namespace xke;

    xkeDebug() << "Size of ColorRgb: " << sizeof(ColorRgb) << '\n'
               << "Size of ColorRgba: " << sizeof(ColorRgba) << xke::flush;

    {
        ColorRgb r(ColorRgb::Red);
        ColorRgb g(ColorRgb::Green);
        ColorRgb b(ColorRgb::Blue);
        xkeDebug() << r << '\n';
        xkeDebug() << g << '\n';
        xkeDebug() << b << '\n';

    }

    {
        ColorRgba r(ColorRgba::Red);
        ColorRgba g(ColorRgba::Green);
        ColorRgba b(ColorRgba::Blue);
        xkeDebug() << r << '\n';
        xkeDebug() << g << '\n';
        xkeDebug() << b << '\n';
    }

    return 0;
}
