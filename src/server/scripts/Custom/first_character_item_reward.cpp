#include "ScriptMgr.h"
#include "Player.h"
#include "DatabaseEnv.h"
#include "CharacterDatabase.h"
#include "Item.h"
#include <sstream>

class first_character_item_reward : public PlayerScript
{
public:
    first_character_item_reward() : PlayerScript("first_character_item_reward") {}

    void OnPlayerLogin(Player* player) override
    {
        uint32 accountId = player->GetSession()->GetAccountId();
        uint32 currentGuid = player->GetGUID().GetCounter();

        // Запрос первого персонажа на аккаунте по дате создания (creation_date)
        std::ostringstream queryFirstChar;
        queryFirstChar << "SELECT guid FROM characters WHERE account = " << accountId << " ORDER BY creation_date ASC LIMIT 1";
        QueryResult result = CharacterDatabase.Query(queryFirstChar.str().c_str());

        if (!result)
            return;

        Field* fields = result->Fetch();
        uint32 firstGuid = fields[0].Get<uint32>();

        // Проверяем, что текущий персонаж — первый созданный
        if (firstGuid != currentGuid)
            return;

        // Проверяем, выдавался ли уже предмет
        std::ostringstream queryCheck;
        queryCheck << "SELECT 1 FROM custom_first_item_rewards WHERE account = " << accountId;
        QueryResult check = CharacterDatabase.Query(queryCheck.str().c_str());

        if (check)
            return; // Уже получал

        // ID предмета для выдачи
        uint32 itemId = 34631;

        // Создаём и выдаём предмет
        if (Item* item = Item::CreateItem(itemId, 1))
        {
            if (player->AddItem(itemId, true))
            {
                // Записываем в базу факт выдачи предмета
                std::ostringstream queryInsert;
                queryInsert << "INSERT INTO custom_first_item_rewards (account, guid) VALUES (" << accountId << ", " << currentGuid << ")";
                CharacterDatabase.Execute(queryInsert.str().c_str());
            }
            else
            {
                delete item;
            }
        }
    }
};

void AddSC_first_character_item_reward()
{
    new first_character_item_reward();
}