#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "World.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "Server/WorldSessionMgr.h"
#include "Configuration/Config.h"
#include <sstream>

namespace
{
    constexpr char const* WelcomeName = "Битва Титанов";
    constexpr char const* OptionLoginBoAEnable = "Login.BoA";
    constexpr char const* OptionLoginAnnounce = "Login.Announce";
}

class Player_Boa : public PlayerScript
{
public:
    Player_Boa() : PlayerScript("Player_Boa") { }

    void OnPlayerFirstLogin(Player* player) override
    {
        if (!player)
            return;

        bool const enableBoA = sConfigMgr->GetOption<bool>(OptionLoginBoAEnable, true, false);
        if (!enableBoA)
            return;

        bool const enableAnnounce = sConfigMgr->GetOption<bool>(OptionLoginAnnounce, true, false);
        if (enableAnnounce)
        {
            // Приветственное сообщение
            std::ostringstream ss;
            ss << "|cffFF0000[" << WelcomeName << "]|r Добро пожаловать на проект " << player->GetName() << "!";
            sWorldSessionMgr->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
        }

        // Загружаем стартовые предметы из базы данных
        GiveStarterItems(player);
    }

private:
    void GiveStarterItems(Player* player)
    {
        uint8 playerClass = player->getClass();

        // Запрос к базе данных для получения предметов для данного класса
        std::ostringstream query;
        query << "SELECT itemId, count FROM player_starter_items WHERE class = " << uint32(playerClass);
        QueryResult result = WorldDatabase.Query(query.str().c_str());

        if (!result)
        {
            LOG_ERROR("scripts", "Player_Boa: No starter items found for class {}", playerClass);
            return;
        }

        // Выдаем все предметы из базы данных
        do
        {
            Field* fields = result->Fetch();
            uint32 itemId = fields[0].Get<uint32>();
            uint32 count = fields[1].Get<uint8>();

            if (itemId > 0)
            {
                // Добавляем предмет игроку
                if (!player->AddItem(itemId, count))
                {
                    LOG_ERROR("scripts", "Player_Boa: Failed to add item {} (count: {}) to player {}", 
                        itemId, count, player->GetName());
                }
            }
        } while (result->NextRow());

        LOG_DEBUG("scripts", "Player_Boa: Starter items given to player {} (class: {})", 
            player->GetName(), playerClass);
    }
};

void AddSC_Player_Boa()
{
    new Player_Boa();
}
