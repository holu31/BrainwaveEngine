#include <ui/text.hpp>
#include <core/engine.hpp>

#include <stdexcept>

UI::Text::Text(std::string text, std::string fontPath){
    this->text = text;
    this->shader = new Render::Shaders("resources/shaders/text.vert",
                            	"resources/shaders/text.frag");;

    LOG(auto init_freetype = FT_Init_FreeType(&ft), \
        "FONT", "initialize freetype");
    if (init_freetype)
    {
        throw LOG(FT_Init_FreeType(&ft), "FONT-ERR", "could not init FreeType Library");
    }

    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
    {
        throw LOG(FT_New_Face(ft, fontPath.c_str(), 0, &face), "FONT-ERR", "failed to load font");
    }
    LOG(FT_Set_Pixel_Sizes(face, 0, 48), "FONT", "setting default pixel sizes");

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (int c = 0; c < text.length(); c++)
    {
        if (FT_Load_Char(face, text[c], FT_LOAD_RENDER))
        {
            LOG(FT_Load_Char(face, text[c], FT_LOAD_RENDER), "FONT-ERR", "failed to load symbol from font.");
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(text[c], character));
    }

    FT_Done_Face(face);
    LOG(FT_Done_FreeType(ft), "FONT", \
        "successful generate text & import font");  
}

void UI::Text::draw(){
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->shader->Bind();
    this->shader->setUniform("projection", projection);
    glUniform3f(glGetUniformLocation(shader->program, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    int x = pos.x;
    int y = pos.y;

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale.x;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale.y;

        float w = ch.Size.x * scale.x;
        float h = ch.Size.y * scale.y;
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * scale.x;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}