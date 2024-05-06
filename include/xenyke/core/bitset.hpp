# ifndef XKE_CORE_BITSET_HPP
# define XKE_CORE_BITSET_HPP

# include <xenyke/core/config.hpp>
# include <vector>

XKE_NAMESPACE_BEGIN

struct Bit
{
    bool v;

    Bit(bool value) : v(value) {}

    Bit& operator=(bool value)
    {
       this->v = value;
       return *this;
    }
};

class Bitset
{
public:
    explicit Bitset(size_t nbBits);

    void set(size_t pos, bool value = true);

    size_t size() const;

    Bit operator[](size_t pos);
    Bit operator[](size_t pos) const;

    Bitset& operator&=(const Bitset& other);
    Bitset& operator|=(const Bitset& other);
    Bitset& operator^=(const Bitset& other);

    void print();

private:
    std::vector<Bit> bits;

};

XKE_NAMESPACE_END

# endif //XKE_CORE_BITSET_HPP
