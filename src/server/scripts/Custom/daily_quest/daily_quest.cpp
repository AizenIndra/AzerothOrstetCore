#include "ScriptMgr.h"
#include "Player.h"
#include "DatabaseEnv.h"
#include "Chat.h"
#include "Log.h"
#include "World.h"
#include "Configuration/Config.h"

class DailyQuestReset : public WorldScript
{
public:
    DailyQuestReset() : WorldScript("DailyQuestReset") {
        LOG_INFO("module", "DailyQuestReset: The script has been successfully loaded. The server is up and running.");
         }

    void OnUpdate(uint32 /* diff */) override
    {
        ScheduleDailyQuestReset();
    }


private:
    void ScheduleDailyQuestReset()
    {
        // Проверяем текущее время
        time_t now = time(nullptr);
        tm* localtm = localtime(&now);

        int currentTimeHour = localtm->tm_hour;
        int currentTimeMin = localtm->tm_min;
        int currentTimeSec = localtm->tm_sec;

        int configTimeHour = sConfigMgr->GetOption<uint32>("DailyQuestReset.Hour", 6);
        int configTimeMinut = sConfigMgr->GetOption<uint32>("DailyQuestReset.Minute", 0);
        
        bool resetDaily;

        if (currentTimeHour == configTimeHour && currentTimeMin == configTimeMinut && currentTimeSec == 0) {
            resetDaily = true;
        } else {
            resetDaily = false;
        }

        if (resetDaily) {
            RemoveQuestsForAllPlayers();
            resetDaily = false;
        }
    }

    void RemoveQuestsForAllPlayers()
    {
        // Извлекаем список квестов из таблицы quest_daily_list
        std::vector<uint32> questIDs;
        QueryResult result = CharacterDatabase.Query("SELECT questid FROM quest_daily_list");

        if (result)
        {
            do
            {
                Field* fields = result->Fetch();
                uint32 questID = fields[0].Get<uint32>();
                questIDs.push_back(questID);
            } while (result->NextRow());
        }

        // Проверяем, есть ли квесты для удаления
        if (!questIDs.empty())
        {
            // Формируем список квестов для удаления
            std::string questIDList;
            for (size_t i = 0; i < questIDs.size(); ++i)
            {
                if (i > 0)
                    questIDList += ", ";
                questIDList += std::to_string(questIDs[i]);
            }

            // Удаляем квесты
            CharacterDatabase.Execute("DELETE FROM character_queststatus_rewarded WHERE quest IN (" + questIDList + ") AND active = 1");
        }
        else
        {
            LOG_INFO("module", "DailyQuestReset: not quest for delete.");
        }

        // Очистка других таблиц (если это нужно)
        CharacterDatabase.Execute("DELETE FROM account_instance_times");
        CharacterDatabase.Execute("DELETE FROM character_instance");
        CharacterDatabase.Execute("TRUNCATE TABLE instance");
    }
};

void AddSC_DailyQuestReset()
{
    new DailyQuestReset();
}