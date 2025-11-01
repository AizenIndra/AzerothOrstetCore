#include "Battlefield.h"
#include "BattlefieldMgr.h"
#include "Chat.h"
#include "Define.h"
#include "GossipDef.h"
#include "Language.h"
#include "Player.h"
#include "Translate.h"
#include "ScriptedGossip.h"
#include "CustomTeleport.h"
#include "ScriptMgr.h"
#include "DeathMatch.h"
#include "ArenaOnevsOne.h"
// #include "../DonatSysteme/DonatMgr.h" // Магазин - удален

using namespace Acore::ChatCommands;

/* ################  загрузка таблиц ################ */
void sCustomTeleport::LoadTeleportListContainer() {
    for (sCustomTeleport::TeleportList_Container::const_iterator itr = m_TeleportList_Container.begin(); itr != m_TeleportList_Container.end(); ++itr)
        delete *itr;

    m_TeleportList_Container.clear();

    QueryResult result = CharacterDatabase.Query("SELECT id, gossip_menu, faction, icon, name_RU, name_EN, map, position_x, position_y, position_z, orientation FROM server_menu_teleportlist ORDER BY id;");

    uint32 oldMSTime = getMSTime();
    uint32 count = 0;

    if (!result)
    {
        LOG_INFO("Custom.TeleportMaster", ">> TeleportMaster: Loaded 0 'teleportlist. DB table `server_menu_teleportlist` is empty!.");
        return;
    }

    do
    {
        Field* fields            = result->Fetch();
        TeleportListSTR* pTele   = new TeleportListSTR;
        pTele->id                = fields[0].Get<uint32>();
        pTele->gossip_menu       = fields[1].Get<uint8>();
        pTele->faction           = fields[2].Get<uint8>();
        pTele->icon              = fields[3].Get<std::string>();
        pTele->name_RU           = fields[4].Get<std::string>();
        pTele->name_EN           = fields[5].Get<std::string>();
        pTele->map               = fields[6].Get<uint16>();
        pTele->position_x        = fields[7].Get<float>();
        pTele->position_y        = fields[8].Get<float>();
        pTele->position_z        = fields[9].Get<float>();
        pTele->orientation       = fields[10].Get<float>();

        m_TeleportList_Container.push_back(pTele);
        ++count;
    } while (result->NextRow());

    LOG_INFO("Custom.TeleportMaster", ">> TeleportMaster: Loaded {} teleportlist in {} ms.", count, GetMSTimeDiffToNow(oldMSTime));
}

void sCustomTeleport::TeleportListMain(Player* player) {
    ClearGossipMenuFor(player);
    for (sCustomTeleport::TeleportList_Container::const_iterator itr = m_TeleportList_Container.begin(); itr != m_TeleportList_Container.end(); ++itr)
        if((*itr)->gossip_menu == 0) {
            // Формируем текст с иконкой в формате WoW
            std::string nameText = GetCustomText(player, (*itr)->name_RU, (*itr)->name_EN);
            std::string nameWithIcon = (*itr)->icon.empty() ? 
                nameText :
                (*itr)->icon + "t" + nameText;
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, nameWithIcon, GOSSIP_SENDER_MAIN + 4, (*itr)->id);
        }
    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, GetCustomText(player, RU_HOME_MENU_NO_ICON, EN_HOME_MENU_NO_ICON), GOSSIP_SENDER_MAIN, 0);
    player->PlayerTalkClass->GetGossipMenu().SetMenuId(123);
    player->PlayerTalkClass->SendGossipMenu(HeadMenu(player), player->GetGUID());
}

void sCustomTeleport::GetTeleportListAfter(Player* player, uint32 action, uint8 faction) {
    ClearGossipMenuFor(player);
    for (sCustomTeleport::TeleportList_Container::const_iterator itr = m_TeleportList_Container.begin(); itr != m_TeleportList_Container.end(); ++itr) {
        if((*itr)->gossip_menu != 0 && (*itr)->gossip_menu == action && ((*itr)->faction == faction || (*itr)->faction == 3)) {
            // Формируем текст с иконкой в формате WoW
            std::string nameText = GetCustomText(player, (*itr)->name_RU, (*itr)->name_EN);
            std::string nameWithIcon = (*itr)->icon.empty() ? 
                nameText :
                (*itr)->icon + "t" + nameText;
            
            AddGossipItemFor(player, GOSSIP_ICON_TAXI, nameWithIcon,
            GOSSIP_SENDER_MAIN + 5, (*itr)->id);
        }
    }
    AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, GetCustomText(player, RU_HOME_MENU_NO_ICON, EN_HOME_MENU_NO_ICON), GOSSIP_SENDER_MAIN, 1);
    player->PlayerTalkClass->SendGossipMenu(HeadMenu(player), player->GetGUID());
}

void sCustomTeleport::TeleportFunction(Player* player, uint32 i) {
    for (sCustomTeleport::TeleportList_Container::const_iterator itr = m_TeleportList_Container.begin(); itr != m_TeleportList_Container.end(); ++itr) {
        if((*itr)->id == i) {
            player->TeleportTo((*itr)->map, (*itr)->position_x, (*itr)->position_y, (*itr)->position_z, (*itr)->orientation);
            ChatHandler(player->GetSession()).PSendSysMessage(GetCustomText(player, RU_SUCCESS_TELEPORT, EN_SUCCESS_TELEPORT), GetCustomText(player, (*itr)->name_RU.c_str(), (*itr)->name_EN.c_str()));
            player->PlayerTalkClass->SendCloseGossip();
            break;
        }
    }
}

std::string sCustomTeleport::HeadMenu(Player* player) {
    std::stringstream ss;
    if(player->GetSession()->GetSessionDbLocaleIndex() == LOCALE_ruRU) {
        ss << "Телепортация по всему миру:\n\n";
        ss << "Выберите место назначения:";
    }
    else {
        ss << "Teleportation around the world:\n\n";
        ss << "Choose destination:";
    }
    return ss.str();
}

// Функции для работы со стоимостью телепортации удалены - телепортация бесплатна

class TeleportMaster : public CreatureScript
{
public:
    TeleportMaster() : CreatureScript("TeleportMaster") { }

    bool OnGossipHello(Player* player, Creature* /* creature */) {
        /* проверка на разрешение открыть спелл */
        if (!CanOpenMenu(player))
            sCustomTeleportMgr->TeleportListMain(player);
        return true;    
    }

    bool CanOpenMenu(Player* player) {
        if (player->IsInCombat() || player->IsInFlight() || player->GetMap()->IsBattlegroundOrArena()
            || player->HasStealthAura() || player->isDead() || (player->getClass() == CLASS_DEATH_KNIGHT && player->GetMapId() == 609 && !player->IsGameMaster() && !player->HasSpell(50977))) {
            ChatHandler(player->GetSession()).PSendSysMessage(GetCustomText(player, "Сейчас это невозможно.", "Now it is impossible"));
            return true;
        }
        return false;
    }
};


class CustomTeleport_World : public WorldScript
{
public:
    CustomTeleport_World() : WorldScript("CustomTeleport_World") { }

    void OnStartup() override
    {
        // создаем базу если не создано
        CharacterDatabase.DirectExecute(sCustomTeleportMgr->sql_teleportlist);

        // прогрузка телепорт мест
        LOG_INFO("Custom.TeleportMaster", ">> TeleportMaster: Loading teleport lists ...");
        sCustomTeleportMgr->LoadTeleportListContainer();        
    }
};

class CustomTeleport_command : public CommandScript
{
public:
    CustomTeleport_command() : CommandScript("CustomTeleport_command") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable ServerMenuTable =
        {
            {"reload", HandleReloadServerMenuCommand, SEC_ADMINISTRATOR, Console::No},
        };

        static ChatCommandTable JoinOloCommand =
        {
            {"olo", HandleJoinOloCommand, SEC_PLAYER, Console::No},
            {"solo", HandleJoinSoloCommand, SEC_PLAYER, Console::No},
        };

        static ChatCommandTable DeathmatchTable =
        {
            { "join", HandleJoinDmCommand, SEC_PLAYER, Console::No},
            { "visual", HandleChangeVisualCommand, SEC_PLAYER, Console::No},
            { "exit", HandleExitDmCommand, SEC_PLAYER, Console::No},
        };

        static ChatCommandTable VisualCommand =
        {
            { "off", HandleChangeVisualOffCommand, SEC_PLAYER, Console::No},
            { "on", HandleChangeVisualCommand, SEC_PLAYER, Console::No},
        };        

        static ChatCommandTable commandTable =
        {
            { "tpmaster", ServerMenuTable },
            // { "donat", ServerDonatSysteme }, // Магазин - удален
            { "join", JoinOloCommand },
            { "dm", DeathmatchTable },
            { "visual", VisualCommand },
        };
        return commandTable;
    }

    static bool HandleJoinDmCommand(ChatHandler* handler)
    {
        Player* targetPlayer = handler->GetSession()->GetPlayer();
        if (!targetPlayer)
            return true;

        DeathMatchMgr->AddPlayer(targetPlayer);
        return true;
    }

    static bool HandleChangeVisualOffCommand(ChatHandler* handler)
    {
        Player* targetPlayer = handler->GetSession()->GetPlayer();
        if (targetPlayer) {
            targetPlayer->RemoveAura(69960);
            targetPlayer->RemoveAura(60352);
            return true;
        } else {
            return false;
        }
    }

    static bool HandleChangeVisualCommand(ChatHandler* handler)
    {
        Player* targetPlayer = handler->GetSession()->GetPlayer();
        Player* plr = handler->getSelectedPlayer();

        if (!plr || !targetPlayer)
            return true;

        if (!plr->IsAlive() || !targetPlayer->IsAlive())
            return true;

        if (targetPlayer->IsInFlight() || targetPlayer->GetMap()->IsBattlegroundOrArena())
            return true;

        if (!plr->IsInWorld() || plr->IsDuringRemoveFromWorld() || plr->IsBeingTeleported())
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        } else {
            plr->CastSpell(targetPlayer, 69960, false); // nick
            plr->CastSpell(targetPlayer, 60352, false); // equip
            return true;
        }  
    }

    static bool HandleExitDmCommand(ChatHandler* handler)
    {
        Player* targetPlayer = handler->GetSession()->GetPlayer();
        if(!targetPlayer)
            return true;

        if (targetPlayer->IsDeathMatch())
            DeathMatchMgr->RemovePlayer(targetPlayer);
        return true;
    }

    static bool HandleJoinSoloCommand(ChatHandler* handler)
    {
        Player* targetPlayer = handler->GetSession()->GetPlayer();
        if(!targetPlayer)
            return true;

        if(targetPlayer->IsInFlight() || targetPlayer->GetMap()->IsBattlegroundOrArena())
            return true;
            
        ArenaOneMgr->JoinQueue(targetPlayer);
        return true;  
    }

    static bool HandleJoinOloCommand(ChatHandler* handler)
    {
        Player* targetPlayer = handler->GetSession()->GetPlayer();
        if(!targetPlayer)
            return true;

        if (targetPlayer->GetLevel() < sWorld->getIntConfig(CONFIG_WINTERGRASP_PLR_MIN_LVL))
            return true;

        if(targetPlayer->IsInFlight() || targetPlayer->GetMap()->IsBattlegroundOrArena())
            return true;

        Battlefield* wintergrasp = sBattlefieldMgr->GetBattlefieldByBattleId(BATTLEFIELD_BATTLEID_WG);
        if(wintergrasp->IsWarTime()) /* приглашаем на оло если началось уже */
            wintergrasp->InvitePlayerToWar(targetPlayer);
        else /* приглашаем в очередь */
            wintergrasp->InvitePlayerToQueue(targetPlayer);
        return true;
    }

    // Функция удалена - магазин полностью удален

    static bool HandleReloadServerMenuCommand(ChatHandler* handler)
    {
        LOG_INFO("Custom.TeleportMaster", ">> Reloading `server_menu_teleportlist` table.");
        sCustomTeleportMgr->LoadTeleportListContainer();
        handler->SendGlobalGMSysMessage("DB table `server_menu_teleportlist` reloaded.");
        return true;
    }
};

void AddSC_CustomTeleportOrCommand()
{
    new TeleportMaster();
    new CustomTeleport_World();
    new CustomTeleport_command();
}
