#pragma once

#include <Rish/rlpch.h>

#include <Rish/Scene/Entity.h>
#include <Rish/Scene/Scene.h>
#include <queue>

#include "SceneMultiTargetPanel.h"

namespace rl{

class RL_API StatusBarPanel : public SceneMultiTargetPanel
{

public:
    StatusBarPanel() = default;
    StatusBarPanel(const Ref<Scene> &scene) : SceneMultiTargetPanel(scene) {}
    ~StatusBarPanel() override = default;

    void sendMessage(const std::string str);

    void onImGuiRender() override;

private:
    std::string m_message;
};

}

