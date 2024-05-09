# include <xenyke/gl/texture.hpp>
# include <xenyke/core/debug.hpp>
# include <xenyke/gl/ext/gl.h>
# include "ext/stb_image.h"

XKE_NAMESPACE_BEGIN

Texture::Texture() noexcept : isLoaded_(false)
{

}

Texture::~Texture() noexcept
{

}

void Texture::destroy() noexcept
{
    glDeleteTextures(1, &id_);
}

void Texture::loadFromFile(const std::string &filename)
{
    uint8_t* data = stbi_load(filename.c_str(), &size_.x, &size_.y, &nrChannels_, 0);

    if (!data) {
        xkeDebug("Cannot load texture: {}", filename);
        isLoaded_ = false;
        return;
    }

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size_.x, size_.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
    isLoaded_ = true;
}

void Texture::use() const
{
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::stopUse() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::isLoaded() const
{
    return isLoaded_;
}

XKE_NAMESPACE_END
