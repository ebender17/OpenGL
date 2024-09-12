#pragma once

#include "GLCore/Renderer/Texture.h"

namespace GLCore {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D() override;

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }

        virtual void Bind(uint32_t slot = 0) const override;
    private:
        std::string path;
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_RendererID;
    };

}

