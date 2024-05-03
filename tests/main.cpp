#include <xenyke/logger/debug.hpp>

using xke::logger::Level;

const char* getString(int n)
{
    return std::move(std::to_string(n).c_str());
}

int main()
{
    xkeDebug("Bonjour {}", "Kenny");



    return 0;
}
