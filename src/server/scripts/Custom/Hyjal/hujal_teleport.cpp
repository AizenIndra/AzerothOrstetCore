#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Chat.h"

using namespace std;

#define DEFAULT_MESSAGE 907
#define TELE_COST 0

struct Teleport
{
    uint32 menu_id;
    uint32 next_menu_id;
    uint8 icon;
    std::string name;
    uint32 cost;
    uint32 map;
    double x, y, z, o;
};

Teleport dData[] =
{
    { 1, 1, GOSSIP_ICON_TALK, "Выбери правильный лагерь Хиджала, но помни герой, что тут каждый сам за себя.", TELE_COST, 0, 0, 0, 0, 0 },
    { 1, 0, GOSSIP_ICON_TAXI, "Таверна Хиджала - Сияние рассвета", TELE_COST, 1, 5063, -2078.97, 1369.29, 5.96975 },
    { 1, 0, GOSSIP_ICON_TAXI, "Таверна Хиджала - Руины", TELE_COST, 1, 4970.97, -1743.45, 1342.04, 1.29307 },
    { 1, 0, GOSSIP_ICON_TAXI, "Таверна Хиджала - Пропасть", TELE_COST, 1, 5607.63, -3054.61, 1556.31, 2.04434 },
    { 1, 0, GOSSIP_ICON_TAXI, "Таверна Хиджала - Темный Мыс", TELE_COST, 1, 4518.5, -2490.53, 1130.75, 3.716 },
    { 1, 0, GOSSIP_ICON_TAXI, "Таверна Хиджала - Окраина Хиджала", TELE_COST, 1, 4216.3, -2918.71, 1094.54, 0.134588 },
    { 1, 0, GOSSIP_ICON_TAXI, "Таверна Хиджала - Лесопилка", TELE_COST,  1, 5289.57, -1537.27, 1366.23, 2.30076 },
    { 1, 0, GOSSIP_ICON_TAXI, "Даларан", TELE_COST,  571, 5809.55, 503.975, 657.526, 2.38338 },
};

class hujal_teleport : public CreatureScript
{
public:
    hujal_teleport() : CreatureScript("hujal_teleport") { }

    void GetMenu(Player* player, Creature* creature, uint32 menuId)
    {
        for (uint8 i = 0; i < (sizeof(dData) / sizeof(*dData)); i++)
        {
            if (dData[i].menu_id == menuId)
                AddGossipItemFor(player, dData[i].icon, dData[i].name, GOSSIP_SENDER_MAIN, i);
        }
        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        GetMenu(player, creature, 1);
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        uint32 menuData = dData[action].next_menu_id;
        if (menuData == 0)
        {
            player->TeleportTo(dData[action].map, dData[action].x, dData[action].y, dData[action].z, dData[action].o);
            ChatHandler(player->GetSession()).PSendSysMessage("Телепорт прошел успешно, будьте предельны внимательны!");
            menuData = dData[action].menu_id;
        }
        GetMenu(player, creature, menuData);
        return true;
    }
};

void AddSC_hujal_teleport()
{
    new hujal_teleport();
} 