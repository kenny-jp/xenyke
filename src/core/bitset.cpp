# include <xenyke/core/bitset.hpp>
# include <xenyke/logger/debug.hpp>
# include <sstream>

XKE_NAMESPACE_BEGIN

Bitset::Bitset(size_t nbBits)
{
    bits.resize(nbBits, false);
}

void Bitset::set(size_t pos, bool value)
{
    // bits[pos] = value;
    *(bits.end() - (pos + 1)) = value;
}

size_t Bitset::size() const
{
    return bits.size();
}

Bit Bitset::operator[](size_t pos)
{
    return bits[pos];
}

Bit Bitset::operator[](size_t pos) const
{
    return bits[pos];
}

Bitset &Bitset::operator&=(const Bitset& other)
{
    for (size_t i {0}; i < other.size(); ++i) {
        const bool b = this->bits[i].v && other.bits[i].v;
        if(i < other.size()) {
            this->bits[i] = b;
        } else {
            this->bits.pop_back();
        }
    }

    return *this;
}

Bitset &Bitset::operator|=(const Bitset &other)
{
    for (size_t i {0}; i < other.size(); ++i) {
        const bool b = this->bits[i].v || other.bits[i].v;
        if(i < other.size()) {
            this->bits[i] = b;
        } else {
            this->bits.pop_back();
        }
    }

    return *this;
}

Bitset &Bitset::operator^=(const Bitset &other)
{
    for (size_t i {0}; i < other.size(); ++i) {
        const bool b = this->bits[i].v != other.bits[i].v;
        if(i < other.size()) {
            this->bits[i] = b;
        } else {
            this->bits.pop_back();
        }
    }

    return *this;
}

void Bitset::print()
{
    std::ostringstream oss;
    for(const auto& b : bits) {
        oss << b.v;
    }
    xkeDebug(oss.str());
}

XKE_NAMESPACE_END
