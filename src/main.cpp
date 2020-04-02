#include <fstream>
#include <typeinfo>
#include <cxxabi.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <imgui.h>
#include <imgui-SFML.h>
#include <nlohmann/json.hpp>

#include "log.h"
#include "resManager.h"
#include "animation/animation.h"

using json = nlohmann::json;
using namespace rl;

int main()
{
    setvbuf(stdout, nullptr, _IONBF, 0);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "CSGO");
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    sf::Color bgColor(0, 0, 0);

#ifdef _WIN32
    ResManager::setRootPath("C:/Users/Rish/Desktop/rish/dod");
#elif __APPLE__
    ResManager::setRootPath("/Users/roy4801/Desktop/Program/rish/dod/");
#endif

    Animation test("reimu-hover", 4, "assets/", "reimu-hover{}.png");
    test.setScale(sf::Vector2f(5.f, 5.f));

    std::ifstream aniFile("../assets/reimu-hover.ani");
    std::string aniContent((std::istreambuf_iterator<char>(aniFile)), (std::istreambuf_iterator<char>())); // read contents
    json j = json::parse(aniContent);
    // j << aniFile;
    auto name = j["name"].get<std::string>();
    int number = j["number"].get<int>();
    auto frames = j["frames"];
    std::string frameType = frames["type"];
    auto files = frames["separate"];
    std::vector<std::string> fileList = files;
    auto isLoop = j["loop"];
    // for(auto &f : fileList)
    //     std::cout << f << '\n';

    while (window.isOpen())
    {
        ///////////////////////////////////////
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        ///////////////////////////////////////
        // Update
        // ImGui
        ImGui::Begin("Debug");
            test.debugImGuiWidgets();
        ImGui::End();
        // Game Update

        ///////////////////////////////////////
        // Draw
        window.clear(bgColor); // Clear screen

        // OpenGL draws
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glColor4f(1.0, 0.0, 0.0, 0.5);
        glBegin(GL_TRIANGLES);
            glVertex2f(-0.5, -0.5);
            glVertex2f(0.0, 0.5);
            glVertex2f(0.5, -0.5);
        glEnd();

        // SFML Draws
        window.pushGLStates();
            window.draw(test);
        window.popGLStates();

        // imgui draws
        window.pushGLStates();
            ImGui::SFML::Render(window);
        window.popGLStates();

        // Update the window
        window.display();
    }
    ImGui::SFML::Shutdown();
}