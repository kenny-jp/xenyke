# ifndef XKE_CORE_STREAMBUF_HPP
# define XKE_CORE_STREAMBUF_HPP

# include <xenyke/core/config.hpp>
# include <vector>

XKE_NAMESPACE_BEGIN

class streambuf
{
public:
    streambuf();
    ~streambuf();

    int overflow(char ch);
    void flush();

private:
    std::vector<char> buffer_;
    size_t pos_;
};

XKE_NAMESPACE_END

# endif //XKE_CORE_STREAMBUF_HPP
