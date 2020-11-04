#include <Rish/Script/EventBoxController.h>


namespace rl {

void EventBoxController::onCreate()
{

}

void EventBoxController::onDestroy()
{

}

void EventBoxController::onUpdate(Time dt)
{
    auto view = GetScene().m_registry.view<TransformComponent, BoxCollider2DComponent, SpriteRenderComponent>();

    for (auto ent : view)
    {
        auto entity = GetEntityByHandle(ent);
        auto &trans = entity.getComponent<TransformComponent>();
        auto &boxc = entity.getComponent<BoxCollider2DComponent>();
        auto &rend = entity.getComponent<SpriteRenderComponent>();
        if (boxc.isCollision)
        {
            // whoCollide List
            for(auto uuid : boxc.whoCollide)
            {
                // check NativeScript Exists
                auto collideEntity = GetScene().getEntityByUUID(uuid);
                if (collideEntity.hasComponent<NativeScriptComponent>() &&
                    entity.hasComponent<NativeScriptComponent>())
                {
                    // check Script Type
                    if(collideEntity.getComponent<NativeScriptComponent>().scriptName == "rl::PlayerController"
                       && entity.getComponent<NativeScriptComponent>().scriptName == "rl::EventBoxController")
                    {
                        auto playerCoordinate = collideEntity.getComponent<TransformComponent>().translate;
                        auto playerWh = collideEntity.getComponent<TransformComponent>().scale;
                        auto boxCoordinate = trans.translate;
                        auto boxWh = trans.scale;

                        if (boxCoordinate.y - boxCoordinate.y/2 - playerCoordinate.y + playerCoordinate.y/2 > 0  &&
                            std::min(playerCoordinate.x + playerWh.x/2 , boxCoordinate.x + boxWh.x/2) - std::max(playerCoordinate.x - playerWh.x/2, boxCoordinate.x - boxWh.x/2) >= boxWh.x/2)
                        {
                            rend.useTexture = true;
                            rend.useAsSubTexture = true;
                            rend.texturePath = "assets\\texture\\mario\\blocks.png";
                            rend.m_subSetting.type = SubTexture2DSetting::SubTextureCoordinate;
                            rend.m_subSetting.leftUpper = glm::vec2(145, 143);
                            rend.m_subSetting.size = glm::vec2(14, 14);
                            rend.loadSubTexture();
                        }
                    }
                }
            }
        }
    }
}
void EventBoxController::onImGuiRender()
{

}

}