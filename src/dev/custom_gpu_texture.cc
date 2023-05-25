#include "EDK3/dev/glew.h"
#include "dev/custom_gpu_texture.h"

namespace EDK3 {

    CustomGPUTexture::CustomGPUTexture() {
        id_ = 0;
        type_ = T_2D;
    }

    CustomGPUTexture::CustomGPUTexture(const CustomGPUTexture& other) {
        id_ = other.id_;
        type_ = other.type_;
    }

    CustomGPUTexture& CustomGPUTexture::operator=(const CustomGPUTexture& other) {
        id_ = other.id_;
        type_ = other.type_;
        return *this;
    }

    CustomGPUTexture::~CustomGPUTexture() {
        glDeleteTextures(1, &id_);
    }

    void CustomGPUTexture::init(Type t, Format internal_format, unsigned int width, unsigned int height, unsigned int depth) {
        Texture::init(t, internal_format, width, height, depth);
        glGenTextures(1, &id_);
        switch (t)
        {
            case EDK3::Texture::T_Invalid: return;
                break;
            case EDK3::Texture::T_1D: type_ = GL_TEXTURE_1D;
                break;
            case EDK3::Texture::T_2D: type_ = GL_TEXTURE_2D;
                break;
            case EDK3::Texture::T_3D: type_ = GL_TEXTURE_3D;
                break;
            case EDK3::Texture::T_CUBEMAP: type_ = GL_TEXTURE_CUBE_MAP;
                break;
        }
    }

    void CustomGPUTexture::set_data(const Format f, const EDK3::Type t, const void* data, unsigned int mipmap_LOD) {

        unsigned int intfrmt = 0;
        switch (format())
        {
        case Format::F_R:
            intfrmt = GL_RED;
            break;
        case Format::F_RG:
            intfrmt = GL_RG;
            break;
        case Format::F_RGB:
            intfrmt = GL_RGB;
            break;
        case Format::F_BGR:
            intfrmt = GL_BGR;
            break;
        case Format::F_BGRA:
            intfrmt = GL_BGRA;
            break;
        case Format::F_RGBA:
            intfrmt = GL_RGBA;
            break;
        case Format::F_DEPTH:
            intfrmt = GL_DEPTH_COMPONENT;
            break;
        case Format::F_DEPTH32:
            intfrmt = GL_DEPTH_COMPONENT32;
            break;
        }

        unsigned int frmt = 0;
        switch (f)
        {
            case Format::F_R:
                frmt = GL_RED;
                break;
            case Format::F_RG:
                frmt = GL_RG;
                break;
            case Format::F_RGB:
                frmt = GL_RGB;
                break;
            case Format::F_BGR:
                frmt = GL_BGR;
                break;
            case Format::F_BGRA:
                frmt = GL_BGRA;
                break;
            case Format::F_RGBA:
                frmt = GL_RGBA;
                break;
            case Format::F_DEPTH:
                frmt = GL_DEPTH_COMPONENT;
                break;
            case Format::F_DEPTH32:
                frmt = GL_DEPTH_COMPONENT32;
                break;
        }

        unsigned int type = 0;

        switch (t)
        {
            case EDK3::Type::T_BYTE: type = GL_BYTE; break;
            case EDK3::Type::T_UBYTE: type = GL_UNSIGNED_BYTE; break;
            case EDK3::Type::T_SHORT: type = GL_SHORT; break;
            case EDK3::Type::T_USHORT: type = GL_UNSIGNED_SHORT; break;
            case EDK3::Type::T_INT: type = GL_INT; break;
            case EDK3::Type::T_UINT: type = GL_UNSIGNED_INT; break;
            case EDK3::Type::T_FLOAT: type = GL_FLOAT; break;
            case EDK3::Type::T_DOUBLE: type = GL_DOUBLE; break;
        }

        glBindTexture(type_, id_);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_LSB_FIRST, 1);

        if (type_ == GL_TEXTURE_1D) {
            glTexImage1D(GL_TEXTURE_1D, mipmap_LOD, intfrmt, width(), 0, frmt, type, data);
        }
        else if (type_ == GL_TEXTURE_2D) {
            glTexImage2D(GL_TEXTURE_2D, mipmap_LOD, intfrmt, width(), height(),  0, frmt, type, data);
        }
        else if (type_ == GL_TEXTURE_3D) {
            glTexImage3D(GL_TEXTURE_3D, mipmap_LOD, intfrmt, width(), height(), depth(), 0, frmt, type, data);
        }
        else if (type_ == GL_TEXTURE_CUBE_MAP) {
            //glTexImage1D(GL_TEXTURE_CUBE_MAP, mipmap_LOD, intfrmt, width_, 0, frmt, type, data);
        }
        set_min_filter(F_NEAREST);
        set_mag_filter(F_NEAREST);
        set_wrap_s(W_REPEAT);
        set_wrap_t(W_REPEAT);
        set_wrap_r(W_REPEAT);
        generateMipmaps();
    }

    void CustomGPUTexture::bind(unsigned int textUnit) const {
        glActiveTexture(GL_TEXTURE0 + textUnit);
        glBindTexture(type_, id_);
    }

    unsigned int CustomGPUTexture::internal_id() const {
        return id_;
    }

    void CustomGPUTexture::set_min_filter(Filter f) {
        Texture::set_min_filter(f);
        glBindTexture(type_, id_);
        switch (f)
        {
            case EDK3::Texture::F_NEAREST:glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                break;
            case EDK3::Texture::F_LINEAR:glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                break;
            case EDK3::Texture::F_NEAREST_MIPMAP_NEAREST:glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                break;
            case EDK3::Texture::F_LINEAR_MIPMAP_NEAREST:glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                break;
            case EDK3::Texture::F_NEAREST_MIPMAP_LINEAR:glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                break;
            case EDK3::Texture::F_LINEAR_MIPMAP_LINEAR:glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                break;
            default:
                break;
        }
    }

    void CustomGPUTexture::set_mag_filter(Filter f) {
        Texture::set_mag_filter(f);
        glBindTexture(type_, id_);
        switch (f)
        {
            case EDK3::Texture::F_NEAREST:glTexParameteri(type_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                break;
            case EDK3::Texture::F_LINEAR:glTexParameteri(type_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                break;
        }
    }

    void CustomGPUTexture::set_wrap_s(Wrap c) {
        Texture::set_wrap_s(c);
        glBindTexture(type_, id_);
        switch (c)
        {
            case EDK3::Texture::W_REPEAT:glTexParameteri(type_, GL_TEXTURE_WRAP_S, GL_REPEAT);
                break;
            case EDK3::Texture::W_MIRRORED_REPEAT:glTexParameteri(type_, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                break;
            case EDK3::Texture::W_CLAMP_TO_EDGE:glTexParameteri(type_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                break;
            default:
                break;
        }
        
    }

    void CustomGPUTexture::set_wrap_t(Wrap c) {
        Texture::set_wrap_t(c);
        glBindTexture(type_, id_);
        switch (c)
        {
            case EDK3::Texture::W_REPEAT:glTexParameteri(type_, GL_TEXTURE_WRAP_T, GL_REPEAT);
                break;
            case EDK3::Texture::W_MIRRORED_REPEAT:glTexParameteri(type_, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
                break;
            case EDK3::Texture::W_CLAMP_TO_EDGE:glTexParameteri(type_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                break;
            default:
                break;
        }
    }

    void CustomGPUTexture::set_wrap_r(Wrap c) {
        Texture::set_wrap_r(c);
        glBindTexture(type_, id_);
        switch (c)
        {
            case EDK3::Texture::W_REPEAT:glTexParameteri(type_, GL_TEXTURE_WRAP_R, GL_REPEAT);
                break;
            case EDK3::Texture::W_MIRRORED_REPEAT:glTexParameteri(type_, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
                break;
            case EDK3::Texture::W_CLAMP_TO_EDGE:glTexParameteri(type_, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                break;
            default:
                break;
        }
    }

    void CustomGPUTexture::generateMipmaps() const {
        glBindTexture(type_, id_);
        glGenerateMipmap(type_);
    }


} //EDK3