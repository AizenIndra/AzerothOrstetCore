#include "DBCStores.h"
#include "Define.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "NpcProfessionMgr.h"

class Professions_NPC : public CreatureScript
{
public:
    Professions_NPC() : CreatureScript("Professions_NPC") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!player || !creature)
            return true;

        sProfessionMgr->ReagentsMenu(player, creature);
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (!action || !player || !creature)
            return true;

        player->PlayerTalkClass->ClearMenus();
        switch (sender)
        {
            case GOSSIP_SENDER_MAIN: {
                player->GetSession()->SendListInventory(creature->GetGUID(), action);
            } break;
        }
        return true;
    }
};

class Professions_ : public CreatureScript
{
public:
    Professions_() : CreatureScript("Professions_") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!player || !creature)
            return true;

        sProfessionMgr->MainMenu(player);
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (!player || !creature)
            return true;

        player->PlayerTalkClass->ClearMenus();
        
        switch (sender)
        {
            case GOSSIP_SENDER_MAIN: {
                if (action == 0) {
                    CloseGossipMenuFor(player);
                }
                break;
            }
            case GOSSIP_SENDER_MAIN + 2: {
                switch (action) {
                    case 0: sProfessionMgr->MainMenu(player); break;    // Назад в главное меню
                    case 1: sProfessionMgr->SecondMenu(player); break;  // Secondary профессии
                    case 2: sProfessionMgr->PrimaryMenu(player); break; // Primary профессии
                    default: break;
                }
                break;
            }
            case GOSSIP_SENDER_MAIN + 3: {
                // action содержит skill ID профессии
                sProfessionMgr->CompleteLearnProfession(player, action);
                break;
            }
            default: break;
        }
        
        return true;
    }
};

void AddSC_Professions_NPC()
{
    new Professions_NPC();
    new Professions_();
}
