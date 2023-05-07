#pragma once

#include <string>

namespace Core {

    struct Config {
        int m_msaa;
        bool m_vsync;
        bool m_resizable;

        int m_width;
        int m_height;

        std::string m_title;

        Config(std::string title = "Title",
                int width = 1280, int height = 900,
                int msaa = 2, bool vsync = true,
                bool resizable = true)
        {
            m_msaa = msaa;
            m_vsync = vsync;
            m_resizable = resizable;

            m_width = width;
            m_height = height;

            m_title = title;
        }
    };

}