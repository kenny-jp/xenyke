# ifndef XKE_CORE_BITSET_HPP
# define XKE_CORE_BITSET_HPP

# include <xenyke/core/config.hpp>
# include <vector>

XKE_NAMESPACE_BEGIN

class ostream;

class Bit
{
public:
    Bit(bool value = false) noexcept;

    operator bool() const noexcept;

    Bit& operator&=(const Bit& other);
    Bit& operator|=(const Bit& other);
    Bit& operator^=(const Bit& other);
    Bit& operator~();

private:
    bool value_;
};

Bit operator&(const Bit& lhs, const Bit& rhs);

Bit operator|(const Bit& lhs, const Bit& rhs);

Bit operator^(const Bit& lhs, const Bit& rhs);

class Bitset
{
public:
    explicit Bitset();
    Bitset(size_t nbBits);

    Bit get(size_t pos) const;
    void init(size_t nbbits);
    size_t size() const;

    void set();
    void set(size_t pos, bool value = true);
    void reset();
    void reset(size_t pos, bool value = true);

    Bit operator[](size_t pos);
    Bit operator[](size_t pos) const;

    bool operator==(const Bitset& other) const;
    bool operator!=(const Bitset& other) const;

    Bitset& operator&=(const Bitset& other);
    Bitset& operator|=(const Bitset& other);
    Bitset& operator^=(const Bitset& other);
    Bitset& operator~();

    friend
    ostream& operator<<(ostream& os, const Bitset& bitset);

    friend
    void xkeDebug(const Bitset& bitset);

private:
    std::vector<Bit> bits_;

};

Bitset operator&(const Bitset& lhs, const Bitset& rhs);
Bitset operator|(const Bitset& lhs, const Bitset& rhs);
Bitset operator^(const Bitset& lhs, const Bitset& rhs);

XKE_NAMESPACE_END

# endif //XKE_CORE_BITSET_HPP
