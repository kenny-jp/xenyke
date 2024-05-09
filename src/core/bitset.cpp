# include <xenyke/core/bitset.hpp>
# include <xenyke/core/debug.hpp>

XKE_NAMESPACE_BEGIN

/*
 * Bit Impl
 */

Bit::Bit(bool value) noexcept :
    value_(value) {}

Bit::operator bool() const noexcept
{
    return value_;
}

Bit &Bit::operator&=(const Bit &other)
{
    value_ &= other.value_;
    return *this;
}

Bit &Bit::operator|=(const Bit &other)
{
    value_ |= other.value_;
    return *this;
}

Bit &Bit::operator^=(const Bit &other)
{
    value_ ^= other.value_;
    return *this;
}

Bit& Bit::operator~()
{
    value_ = !value_;
    return *this;
}

Bit operator&(const Bit& lhs, const Bit& rhs)
{
    Bit result{lhs};
    return result &= rhs;
}

Bit operator|(const Bit& lhs, const Bit& rhs)
{
    Bit result{lhs};
    return result |= rhs;
}

Bit operator^(const Bit& lhs, const Bit& rhs)
{
    Bit result{lhs};
    return result ^= rhs;
}


/*
 * Bitset Impl
 */

Bitset::Bitset() :
    bits_(0)
{
}

Bitset::Bitset(size_t nbBits) :
    bits_(nbBits, false)
{
}

Bit Bitset::get(size_t pos) const
{
    return bits_[pos];
}

void Bitset::init(size_t nbbits)
{
    bits_.resize(nbbits, false);
}

void Bitset::set()
{
    std::fill(bits_.begin(), bits_.end(), true);
}

void Bitset::set(size_t pos, bool value)
{
    *(bits_.end() - (pos + 1)) = value;
}

void Bitset::reset()
{
    std::fill(bits_.begin(), bits_.end(), false);
}

void Bitset::reset(size_t pos, bool value)
{
    *(bits_.end() - (pos + 1)) = !value;
}

size_t Bitset::size() const
{
    return bits_.size();
}

Bit Bitset::operator[](size_t pos)
{
    return bits_[pos];
}

bool Bitset::operator==(const Bitset &other) const
{
    return bits_ == other.bits_;
}

bool Bitset::operator!=(const Bitset &other) const
{
    return !(*this == other);
}

Bit Bitset::operator[](size_t pos) const
{
    return bits_[pos];
}

Bitset &Bitset::operator&=(const Bitset& other)
{
    size_t maxSize = std::min(size(), other.size());

    for (size_t i {0}; i < maxSize; ++i) {
        this->bits_[i] &= other.bits_[i];
    }

    return *this;
}

Bitset &Bitset::operator|=(const Bitset &other)
{
    size_t maxSize = std::min(size(), other.size());

    for (size_t i {0}; i < maxSize; ++i) {
        this->bits_[i] |= other.bits_[i];
    }

    return *this;
}

Bitset &Bitset::operator^=(const Bitset &other)
{
    size_t maxSize = std::min(size(), other.size());

    for (size_t i {0}; i < maxSize; ++i) {
        this->bits_[i] ^= other.bits_[i];
    }

    return *this;
}

Bitset& Bitset::operator~()
{
    for (Bit& b : bits_) {
        b = ~b;
    }
    return *this;
}

ostream& operator<<(ostream &os, const Bitset &bitset)
{
    os << "xke::Bitset(" << bitset.size() << "): ";
    for (const Bit& b : bitset.bits_) {
        os << b;
    }

    return os;
}

void xkeDebug(const Bitset& bitset)
{
    __xke_get_static_debug_t()() << bitset << xke::flush;
}

Bitset operator&(const Bitset &lhs, const Bitset &rhs)
{
    Bitset res(lhs);
    return res &= rhs;
}

Bitset operator|(const Bitset &lhs, const Bitset &rhs)
{
    Bitset res(lhs);
    return res |= rhs;
}

Bitset operator^(const Bitset &lhs, const Bitset &rhs)
{
    Bitset res(lhs);
    return res ^= rhs;
}

XKE_NAMESPACE_END
