# include <xenyke/core/ostream.hpp>

XKE_NAMESPACE_BEGIN

ostream::ostream() : flags_(ostream_flags(8)), floating_point_precision_(-1) {}

ostream &ostream::operator<<(ostream_flags flag)
{
    if (flag == ostream_flags::Endl) {
        buff_.overflow('\n');
        return *this;
    }
    else if (flag == ostream_flags::Flush) {
        buff_.overflow('\n');
        buff_.flush();
        return *this;
    }

    flags_ &= flag;
    return *this;
}

ostream &ostream::operator<<(floating_point_precision p)
{
    floating_point_precision_ = p.value;
    return *this;
}

ostream& ostream::operator<<(char c)
{
    buff_.overflow(c);
    return *this;
}

ostream& ostream::operator<<(const char* str)
{
    while (*str != '\0') {
        buff_.overflow(*str++);
    }

    return *this;
}

ostream& ostream::operator<<(bool b)
{
    if ((flags_ & ostream_flags::BoolAlpha) == flags_) {
        static constexpr const char* True = "true";
        static constexpr const char* False = "false";
        operator<<(b ? True : False);
    } else {
        operator<<(static_cast<int>(b));
    }

    return *this;
}

XKE_NAMESPACE_END
