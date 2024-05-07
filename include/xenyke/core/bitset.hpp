# ifndef XKE_CORE_BITSET_HPP
# define XKE_CORE_BITSET_HPP

# include <xenyke/core/config.hpp>
# include <vector>

XKE_NAMESPACE_BEGIN

class Bit
{
public:
    Bit(bool value = false) noexcept : v_(value) {}
    operator bool() const noexcept { return v_; }

private:
    bool v_;
};

class Bitset
{
public:
    explicit Bitset(size_t nbBits);

    Bit get(size_t pos) const;
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

    void print();

private:
    std::vector<Bit> bits_;

};

Bitset operator&(const Bitset& lhs, const Bitset& rhs);
Bitset operator|(const Bitset& lhs, const Bitset& rhs);
Bitset operator^(const Bitset& lhs, const Bitset& rhs);

XKE_NAMESPACE_END

# endif //XKE_CORE_BITSET_HPP
