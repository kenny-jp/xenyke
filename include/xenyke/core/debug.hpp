# ifndef XKE_CORE_DEBUG_HPP
# define XKE_CORE_DEBUG_HPP

#include <algorithm>
#include <cmath>
# include <xenyke/core/config.hpp>
# include <vector>

XKE_NAMESPACE_BEGIN

class __debug_streambuf
{
public:
    __debug_streambuf() :
        buffer_(XKE_DEBUG_STREAMBUF_SIZE), pos_(0) {}

    ~__debug_streambuf()
    {
        flush();
    }

    int overflow(char ch)
    {
        if (ch != EOF) {
            if (pos_ < buffer_.size() - 1) {
                buffer_[pos_++] = static_cast<char>(ch);
            } else {
                flush();
                buffer_[pos_++] = static_cast<char>(ch);
            }
            return  ch;
        } else {
            flush();
            return ch;
        }
    }

private:
    void flush()
    {
        if (pos_ > 0) {
            __xke_write_stdout(buffer_.data(), pos_);
            pos_ = 0;
        }
    }

    std::vector<char> buffer_;
    size_t pos_;
};

struct floating_point_precision
{
    floating_point_precision(int precision) : value(precision) {}

private:
    int value;
    friend class __debug_ostream;
};


enum __debug_ostream_flags : int32_t
{
    BoolAlpha   = 1L << 0,
    Dec         = 1L << 1,
    Hex         = 1L << 2,
    Oct         = 1L << 3,
};

static constexpr __debug_ostream_flags boolalpha = __debug_ostream_flags::BoolAlpha;
static constexpr __debug_ostream_flags noboolalpha = static_cast<__debug_ostream_flags>(~boolalpha);

XKE_INLINE_CONSTEXPR __debug_ostream_flags
operator&(__debug_ostream_flags a, __debug_ostream_flags b)
{ return __debug_ostream_flags(static_cast<int32_t>(a) & static_cast<int32_t>(b)); }

XKE_INLINE_CONSTEXPR __debug_ostream_flags
operator|(__debug_ostream_flags a, __debug_ostream_flags b)
{ return __debug_ostream_flags(static_cast<int32_t>(a) | static_cast<int32_t>(b)); }

XKE_INLINE_CONSTEXPR __debug_ostream_flags
operator^(__debug_ostream_flags a, __debug_ostream_flags b)
{ return __debug_ostream_flags(static_cast<int32_t>(a) ^ static_cast<int32_t>(b)); }

XKE_INLINE_CONSTEXPR __debug_ostream_flags
operator~(__debug_ostream_flags a)
{ return __debug_ostream_flags(~static_cast<int32_t>(a)); }

XKE_INLINE const __debug_ostream_flags&
operator|=(__debug_ostream_flags& a, __debug_ostream_flags b)
{ return a = a | b; }

XKE_INLINE const __debug_ostream_flags&
operator&=(__debug_ostream_flags& a, __debug_ostream_flags b)
{ return a = a | b; }

XKE_INLINE const __debug_ostream_flags&
operator^=(__debug_ostream_flags& a, __debug_ostream_flags b)
{ return a = a ^ b; }


class __debug_ostream
{
public:
    __debug_ostream() : floating_point_precision_(-1) {}

    __debug_ostream& operator<<(const char* str)
    {
        while (*str != '\0') {
            buff_.overflow(*str++);
        }

        return *this;
    }

    __debug_ostream& operator<<(bool b)
    {
        if ((flags_ & __debug_ostream_flags::BoolAlpha) == flags_) {
            static constexpr const char* True = "true";
            static constexpr const char* False = "false";
            operator<<(b ? True : False);
        } else {
            operator<<(static_cast<int>(b));
        }

        return *this;
    }

    template<class T_> requires std::is_signed_v<T_> && std::is_integral_v<T_>
    __debug_ostream& operator<<(T_ n)
    {
        char strbuff[32];
        int length = snprintf(strbuff, sizeof(strbuff), "%lld", static_cast<long long>(n));
        for (int i {0}; i < length; ++i) {
            buff_.overflow(strbuff[i]);
        }
        return *this;
    }

    template<class T_> requires std::is_unsigned_v<T_> && std::is_integral_v<T_>
    __debug_ostream& operator<<(T_ n)
    {
        char strbuff[32];
        int length = snprintf(strbuff, sizeof(strbuff), "%llu", static_cast<unsigned long long>(n));
        for (int i {0}; i < length; ++i) {
            buff_.overflow(strbuff[i]);
        }
        return *this;
    }

    template<class T_> requires std::is_floating_point_v<T_>
    __debug_ostream& operator<<(T_  p)
    {
        char strbuff[64];
        int length;
        if (floating_point_precision_ >= 0) {
            length = snprintf(strbuff, sizeof(strbuff), "%.*f", floating_point_precision_, p);
        } else {
            length = snprintf(strbuff, sizeof(strbuff), "%G", p);
            auto rit = std::reverse_iterator<char*>(std::end(strbuff));
            auto it = std::find(rit, std::reverse_iterator<char*>(std::begin(strbuff)), '0');
            *it = '\0';
        }

        for (int i {0}; i < length && strbuff[i] != '\0'; ++i) {
            buff_.overflow(strbuff[i]);
        }
        return *this;
    }

    __debug_ostream& operator<<(floating_point_precision p)
    {
        floating_point_precision_ = p.value;
        return *this;
    }

    __debug_ostream& operator<<(__debug_ostream_flags flag)
    {
        flags_ &= flag;
        return *this;
    }



private:
    __debug_streambuf buff_;
    __debug_ostream_flags flags_;
    int floating_point_precision_;
};



class __debug
{
public:
    __debug_ostream& operator()()
    {
        return os_;
    }

    template<class... Args>
    __debug_ostream& operator()(std::format_string<Args...> fmt, Args&&... args)
    {
        const std::string str = std::format(fmt, std::forward<Args>(args)...);
        os_ << str.c_str();
        return os_;
    }

private:
    __debug_ostream os_;
};

__debug& __get_static_debug_t()
{
    static __debug debug;
    return debug;
}

XKE_NAMESPACE_END

xke::__debug_ostream& xkeDebug()
{
    return xke::__get_static_debug_t()();
}

template<class... Args>
xke::__debug_ostream& xkeDebug(std::format_string<Args...> fmt, Args&&... args)
{
    return xke::__get_static_debug_t()(fmt, std::forward<Args>(args)...);
}


# endif //XKE_CORE_DEBUG_HPP
