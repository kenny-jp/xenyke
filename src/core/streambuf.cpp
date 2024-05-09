# include <xenyke/core/streambuf.hpp>

XKE_NAMESPACE_BEGIN

streambuf::streambuf() :
    buffer_(XKE_DEBUG_STREAMBUF_SIZE), pos_(0)
{

}

streambuf::~streambuf()
{
    flush();
}

int streambuf::overflow(char ch)
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

void streambuf::flush()
{
    if (pos_ > 0) {
        __xke_write_stdout(buffer_.data(), pos_);
        __xke_write_stdout("\n", 1);
        pos_ = 0;
    }
}

XKE_NAMESPACE_END
