#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <fmt/core.h>
#include <fmt/printf.h>

#include <imgui.h>

#include <core.h>

// TODO: set loop start end
// TODO: support flip

// Ref: https://www.sfml-dev.org/tutorials/2.5/graphics-transform.php

namespace rl {

class Animation : public sf::Transformable, public sf::Drawable
{
public:
    Animation();
    Animation(std::string texName, int count,
        std::string path, std::string fnameFmt,
        bool load=true);
    // TODO: impl
    void setInfo(std::string texName, int count, std::string path, std::string fnameFmt);
    void loadRes();

    // Main function
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    // the duration of the animation (second)
    float duration, reverseDuration;
    bool loop;
    bool reverse;

    bool isEnd();

    void resetFrame() { m_nowFrame = 0; }

    const sf::Sprite &getNowSprite() const { return m_nowFrame >= 0 && m_nowFrame < m_count ? *m_spriteVec[m_nowFrame] : empty; }
    int getNowFrame() { return m_nowFrame; }
    int getTotalFrame() { return m_count; }
private:
    // Texture attributes
    int m_count;             // Frame count
    mutable int m_nowFrame;  // Current frame
    std::string m_texName;   // Texture prefix
    std::string m_format;    // Filename format
    std::string m_path;      // Path to the files
    std::vector<std::shared_ptr<sf::Sprite>> m_spriteVec; // sprite storage
    sf::Sprite empty;
    //
    mutable sf::Clock m_clk; // clock
    bool ready; // is the animation ready
// For Debug ONLY
public:
    bool debugDrawFlag = false;

    void debugImGuiWindow()
    {
        ImGui::Begin(m_texName.c_str());
        debugImGuiWidgets();
        ImGui::End();
    }
    void debugImGuiWidgets()
    {
        ImGui::Checkbox("draw", &debugDrawFlag);
        // Position
        float pos[2] = {getPosition().x, getPosition().y};
        ImGui::DragFloat2("Position", pos, 1.f);
        setPosition(pos[0], pos[1]);
        // Rotate
        float rotate = getRotation();
        ImGui::SliderFloat("Rotate", &rotate, 0.f, 360.f);
        setRotation(rotate);
        // Origin
        float ori[2] = {getOrigin().x, getOrigin().y};
        ImGui::DragFloat2("Origin", ori, 1.f);
        setOrigin(ori[0], ori[1]);
    }

    mutable sf::CircleShape debugOrigCir;
    float debugCirRadius = 5.f;
    mutable sf::RectangleShape debugRect;
    float debugRectThick = 1.f;
};

}