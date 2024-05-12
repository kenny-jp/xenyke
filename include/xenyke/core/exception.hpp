# ifndef XKE_CORE_EXCEPTION_HPP
# define XKE_CORE_EXCEPTION_HPP

# include <xenyke/core/config.hpp>
# include <exception>
# include <format>

# define __xke_throw(STR) throw Exception(STR)
# define __xke_throw_fmt(STR, ...) throw Exception(STR, __VA_ARGS__)

XKE_NAMESPACE_BEGIN

class Exception : public std::exception
{
public:
    explicit Exception(const std::string& msg) :
        msg_(std::move(std::string("XKEException:: " + msg).c_str())){}

    template<class... Args>
    explicit Exception(std::format_string<Args...> msg, Args&&... args) :
        msg_(std::move(std::string("XKEException:: " + std::format(msg, std::forward<Args>(args)...)).c_str())) {}

    virtual const char* what() const noexcept override { return msg_; }

private:
    const char* msg_;

};

XKE_NAMESPACE_END

# endif //XKE_CORE_EXCEPTION_HPP
