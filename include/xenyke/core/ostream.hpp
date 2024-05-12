# ifndef XKE_CORE_OSTREAM_HPP
# define XKE_CORE_OSTREAM_HPP

# include <xenyke/core/streambuf.hpp>
# include <algorithm>

XKE_NAMESPACE_BEGIN

enum class ostream_flags : int32_t
{
    BoolAlpha   = 1L << 0,
    Dec         = 1L << 1,
    Hex         = 1L << 2,
    Oct         = 1L << 3,
    Endl        = 1L << 4,
    Flush       = 1L << 5
};

static constexpr ostream_flags boolalpha    = ostream_flags::BoolAlpha;
static constexpr ostream_flags noboolalpha  = static_cast<ostream_flags>(~static_cast<int32_t>(boolalpha));
static constexpr ostream_flags endl         = ostream_flags::Endl;
static constexpr ostream_flags flush        = ostream_flags::Flush;

XKE_INLINE_CONSTEXPR ostream_flags
operator&(ostream_flags a, ostream_flags b)
{ return ostream_flags(static_cast<int32_t>(a) & static_cast<int32_t>(b)); }

XKE_INLINE_CONSTEXPR ostream_flags
operator|(ostream_flags a, ostream_flags b)
{ return ostream_flags(static_cast<int32_t>(a) | static_cast<int32_t>(b)); }

XKE_INLINE_CONSTEXPR ostream_flags
operator^(ostream_flags a, ostream_flags b)
{ return ostream_flags(static_cast<int32_t>(a) ^ static_cast<int32_t>(b)); }

XKE_INLINE_CONSTEXPR ostream_flags
operator~(ostream_flags a)
{ return ostream_flags(~static_cast<int32_t>(a)); }

XKE_INLINE const ostream_flags&
operator|=(ostream_flags& a, ostream_flags b)
{ return a = a | b; }

XKE_INLINE const ostream_flags&
operator&=(ostream_flags& a, ostream_flags b)
{ return a = a | b; }

XKE_INLINE const ostream_flags&
operator^=(ostream_flags& a, ostream_flags b)
{ return a = a ^ b; }


struct floating_point_precision
{
    floating_point_precision(int precision) : value(precision) {}

private:
    int value;
    friend class ostream;
};

class ostream
{
public:
    ostream();

    template<class T_> requires std::is_signed_v<T_> && std::is_integral_v<T_>
    ostream& operator<<(T_ n)
    {
        char strbuff[32];
        int length = snprintf(strbuff, sizeof(strbuff), "%lld", static_cast<long long>(n));
        for (int i {0}; i < length; ++i) {
            buff_.overflow(strbuff[i]);
        }
        return *this;
    }

    template<class T_> requires std::is_unsigned_v<T_> && std::is_integral_v<T_>
    ostream& operator<<(T_ n)
    {
        char strbuff[32];
        int length = snprintf(strbuff, sizeof(strbuff), "%llu", static_cast<unsigned long long>(n));
        for (int i {0}; i < length; ++i) {
            buff_.overflow(strbuff[i]);
        }
        return *this;
    }

    template<class T_> requires std::is_floating_point_v<T_>
    ostream& operator<<(T_  p)
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

    ostream& operator<<(ostream_flags flag);
    ostream& operator<<(floating_point_precision p);
    ostream& operator<<(char c);
    ostream& operator<<(const char* str);
    ostream& operator<<(bool b);

private:
    streambuf buff_;
    ostream_flags flags_;
    int floating_point_precision_;
};

XKE_NAMESPACE_END

# endif //XKE_CORE_OSTREAM_HPP
