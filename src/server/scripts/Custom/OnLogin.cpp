#include "ScriptMgr.h"
#include "DatabaseEnv.h"
#include "SpellInfo.h"
#include "ObjectMgr.h"
#include "Item.h"
#include "Pet.h"
#include "ReputationMgr.h"
#include "Translate.h"
#include "ServerMenu/ServerMenuMgr.h"
#include "ChannelMgr.h"

const uint32 SPELL_DEMENTIA = 40874;

struct Event
{
        uint8 Events;
};

enum Enums
{
        FIRST_DELAY    = 5000,
        SECOND_DELAY   = 10000,
        THIRD_DELAY    = 15000,
        FOURTH_DELAY   = 20000
};

static std::map<ObjectGuid, Event> _events;

class Information_Server : public BasicEvent
{
public:
        Information_Server(Player* player) : _Plr(player) {}

        virtual bool Execute(uint64 /*time*/, uint32 /*diff*/) override
        {
            ObjectGuid pEvent;
            pEvent = _Plr->GetGUID();
            char const* icon_color;
            icon_color = "|TInterface\\GossipFrame\\Availablequesticon:15:15:|t|cffff9933 ";

            switch(_events[pEvent].Events)
            {
                case 0:
                    ChatHandler(_Plr->GetSession()).PSendSysMessage("{}Добро пожаловать на проект |cffffff4dБитва Титанов|r", icon_color);
                    _events[pEvent].Events = 1;
                    break;

                case 1:
                    ChatHandler(_Plr->GetSession()).PSendSysMessage("{}Мы желаем вам приятной игры на нашем проекте <3", icon_color);
                    _events[pEvent].Events = 5;
                    break;
            }
            return true;
        }
        Player* _Plr;
};

class Login_script : public PlayerScript
{
public:
    Login_script() : PlayerScript("Login_script") {}

    ChannelMgr* _channelMgr = nullptr;

    void OnPlayerUpdateZone(Player* player, uint32 newZone, uint32 newArea) override
	{
        if (!player || !newZone || !newArea)
            return;

        // Remove Dementia on updating zone for player
        if (player->HasAura(SPELL_DEMENTIA))
            player->RemoveAura(SPELL_DEMENTIA);
    }

    void OnPlayerMapChanged(Player *player) override
    {
        if (!player)
            return;

        Map *map = player->GetMap();
        if (!map)
            return;
            
        player->VerifiedRankBuff(map);
    }       

    void RemoveDementia(Player* player) 
    {
        if (!player)
            return;

        // Remove Dementia on player login
        if (player->HasAura(SPELL_DEMENTIA))
            player->RemoveAura(SPELL_DEMENTIA);
    }
    

    

    void OnPlayerFirstLogin(Player* player) override
    {
        player->m_Events.AddEvent(new Information_Server(player), player->m_Events.CalculateTime(FIRST_DELAY));
        player->m_Events.AddEvent(new Information_Server(player), player->m_Events.CalculateTime(SECOND_DELAY));
        player->m_Events.AddEvent(new Information_Server(player), player->m_Events.CalculateTime(THIRD_DELAY));
        player->m_Events.AddEvent(new Information_Server(player), player->m_Events.CalculateTime(FOURTH_DELAY));
    }

    void JoinCustomChannel(Player* player) 
    {
        if (!player)
            return;

        if (!_channelMgr)
            _channelMgr = ChannelMgr::forTeam(player->GetTeamId());

        if (_channelMgr)
        {
            if (Channel* channel = _channelMgr->GetJoinChannel("ПоискСпутников", 5))
                channel->JoinChannel(player->GetSession()->GetPlayer(), "ПоискСпутников");
        }
    }

    void OnPlayerLogin(Player* player) override
    {

        if (!player)
            return; 

        JoinCustomChannel(player);                 
            
        player->RankControlOnLogin();
        player->LoadPvPRank();
        
        RemoveDementia(player);
        sServerMenuMgr->VipMountLearn(player);
        
        if (!player->HasSpell(28698))
        player->learnSpell(28698);

        Map *map = player->GetMap();
        if (!map)
            return;
        player->VerifiedRankBuff(map);

        // выходные бонусы
        if (sServerMenuMgr->isDoubleDays()) {
            ChatHandler(player->GetSession()).PSendSysMessage(GetCustomText(player, RU_HOLIDAY_ONLOGIN, EN_HOLIDAY_ONLOGIN));
        }
    }
};

void AddSC_Login_script()
{
    new Login_script();
}
