# include <xenyke/core/bitset.hpp>
# include <sstream>

XKE_NAMESPACE_BEGIN

Bitset::Bitset(size_t nbBits)
{
    bits_.resize(nbBits, false);
}

Bit Bitset::get(size_t pos) const
{
    return bits_[pos];
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
        const bool b = this->bits_[i] && other.bits_[i];
        this->bits_[i] = b;
    }

    return *this;
}

Bitset &Bitset::operator|=(const Bitset &other)
{
    for (size_t i {0}; i < other.size(); ++i) {
        const bool b = this->bits_[i] || other.bits_[i];
        if(i < other.size()) {
            this->bits_[i] = b;
        } else {
            this->bits_.pop_back();
        }
    }

    return *this;
}

Bitset &Bitset::operator^=(const Bitset &other)
{
    for (size_t i {0}; i < other.size(); ++i) {
        const bool b = this->bits_[i] != other.bits_[i];
        if(i < other.size()) {
            this->bits_[i] = b;
        } else {
            this->bits_.pop_back();
        }
    }

    return *this;
}

void Bitset::print()
{
    std::ostringstream oss;
    for(const auto& b : bits_) {
        oss << b;
    }
    // xkeDebug(oss.str());
}

Bitset operator&(const Bitset &lhs, const Bitset &rhs)
{
    Bitset res(lhs);
    res &= rhs;
    return res;
}

Bitset operator|(const Bitset &lhs, const Bitset &rhs)
{
    Bitset res(lhs);
    res |= rhs;
    return res;
}

Bitset operator^(const Bitset &lhs, const Bitset &rhs)
{
    Bitset res(lhs);
    res ^= rhs;
    return res;
}

XKE_NAMESPACE_END
