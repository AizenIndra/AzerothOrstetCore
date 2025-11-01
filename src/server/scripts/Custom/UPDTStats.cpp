#include "WorldSession.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "ScriptPCH.h"
#include "Mail.h"
#include "DatabaseEnv.h"
#include "CharacterDatabase.h"
#include "Log.h"
#include "StringFormat.h"
#include "Chat.h"
#include <SmartAI.h>

class UPDTStats : public CreatureScript
{
public:
	UPDTStats() : CreatureScript("ReforgeSpell") { }
	struct UPDTStatsAI : public ScriptedAI
	{
		UPDTStatsAI(Creature* creature) : ScriptedAI(creature) { }

		int SpellStamina = 80992;
		int SpellStrenght = 81103;
		int SpellAgility = 81048;
		int SpellIntelect = 80932;
		int SpellSpirit = 80876;
		int SpellDamage = 81158;
		int32* GetSpellIdCurrent(Player* pp, int type)
		{
			int32* STM = 0;
			switch (type)
			{
			case 1: //Stamina
			{
				int bs = 0;
				for (int i = 0; i < 55; i++)
				{
					if (pp->HasSpell(SpellStamina + bs))
					{
						if (bs == 54)
						{
							STM = new int32[3]{ SpellStamina + bs,54,0 };
							return STM;
						}
						STM = new int32[3]{ SpellStamina + bs,bs,GetPrice(bs,0) };
						return STM;
					}
					bs++;

				}
				STM = new int32[3]{ SpellStamina,-1,GetPrice(-1,0) };
				return STM;
			}
			break;
			case 2: //Strenght
			{
				
				int bs = 0;
				for (int i = 0; i < 55; i++)
				{
					if (pp->HasSpell(SpellStrenght + bs))
					{
						if (bs == 54)
						{
							STM = new int32[3]{ SpellStrenght + bs,54,0 };
							return STM;
						}
						STM = new int32[3]{ SpellStrenght + bs,bs,GetPrice(bs,0) };
						return STM;
					}
					bs++;

				}
				STM = new int32[3]{ SpellStrenght,-1,GetPrice(-1,0) };
				return STM;
			}
			break;
			case 3: //Agility
			{
				int bs = 0;
				for (int i = 0; i < 55; i++)
				{
					if (pp->HasSpell(SpellAgility + bs))
					{
						if (bs == 54)
						{
							STM = new int32[3]{ SpellAgility + bs,54,0 };
							return STM;
						}
						STM = new int32[3]{ SpellAgility + bs,bs,GetPrice(bs,0) };
						return STM;
					}
					bs++;

				}
				STM = new int32[3]{ SpellAgility,-1,GetPrice(-1,0) };
				return STM;
			}
			break;
			case 4: //Intelect
			{
				int bs = 0;
				for (int i = 0; i < 55; i++)
				{
					if (pp->HasSpell(SpellIntelect + bs))
					{
						if (bs == 54)
						{
							STM = new int32[3]{ SpellIntelect + bs,54,0 };
							return STM;
						}
						STM = new int32[3]{ SpellIntelect + bs,bs,GetPrice(bs,0) };
						return STM;
					}
					bs++;

				}
				STM = new int32[3]{ SpellIntelect,-1,GetPrice(-1,0) };
				return STM;
			}
			break;
			case 5: //Spirit
			{
				int bs = 0;
				for (int i = 0; i < 55; i++)
				{
					if (pp->HasSpell(SpellSpirit + bs))
					{
						if (bs == 54)
						{
							STM = new int32[3]{ SpellSpirit + bs,54,0 };
							return STM;
						}
						STM = new int32[3]{ SpellSpirit + bs,bs,GetPrice(bs,0) };
						return STM;
					}
					bs++;

				}
				STM = new int32[3]{ SpellSpirit,-1,GetPrice(-1,0) };
				return STM;
			}
			break;
			case 6: //Damage
			{
				int bs = 0;
				for (int i = 0; i < 35; i++)
				{
					if (pp->HasSpell(SpellDamage + bs))
					{
						if (bs == 34)
						{
							STM = new int32[3]{ SpellDamage + bs,34,0 };
							return STM;
						}
						STM = new int32[3]{ SpellDamage + bs,bs,GetPrice(bs,1) };
						return STM;
					}
					bs++;

				}
				STM = new int32[3]{ SpellDamage,-1,GetPrice(-1,1) };
				return STM;
			}
			break;
			}
			return nullptr;
		}
		int32 GetPrice(int Level, int type)
		{
			int tps1[] = { 5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58 };
			int tps2[] = { 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63 };

			if (type == 0)
			{
				return tps1[Level + 1];
			}
			else
			{
				return tps2[Level + 1];
			}
		}
		void UpgradingStats(Player* pp, int32 SpellID, int Level, uint32 Price)
		{
			if (pp->GetItemCount(73903) >= Price)
			{
				pp->DestroyItemCount(73903, Price, true);
				if (Level == -1)
				{
					pp->learnSpell(SpellID);
					ChatHandler(pp->GetSession()).PSendSysMessage("|cff44CC00[Чумный алхимический стол]|r: Успешное улучшение умений!");
				}
				else
				{
					if (SpellDamage + Level == SpellID && Level == 34)
					{
						ChatHandler(pp->GetSession()).PSendSysMessage("|cff44CC00[Чумный алхимический стол]|r: Вы получили максимальный уровень улучшения данного умения!");
						return;
					}
					if (Level == 54)
					{
						ChatHandler(pp->GetSession()).PSendSysMessage("|cff44CC00[Чумный алхимический стол]|r: Вы получили максимальный уровень улучшения данного умения!");
						return;
					}
					pp->removeSpell(SpellID, SPEC_MASK_ALL, false);
					pp->learnSpell(SpellID + 1);
					ChatHandler(pp->GetSession()).PSendSysMessage("|cff44CC00[Чумный алхимический стол]|r: Успешное улучшение умений!");
				}
				return;
			}
			else
			{
				int price = Price - pp->GetItemCount(73903);
				ChatHandler(pp->GetSession()).PSendSysMessage("|cff44CC00[Чумный алхимический стол]|r: К сожалению, у вас не хватает - {} осколков души.", std::to_string(price).c_str());
				return;
			}
		}
		int32 GetCalculateReturnSpirit(Player* pp)
		{
			int32* STM1 = GetSpellIdCurrent(pp, 1);
			int32* STM2 = GetSpellIdCurrent(pp, 2);
			int32* STM3 = GetSpellIdCurrent(pp, 3);
			int32* STM4 = GetSpellIdCurrent(pp, 4);
			int32* STM5 = GetSpellIdCurrent(pp, 5);
			int32* STM6 = GetSpellIdCurrent(pp, 6);
			int sum = 0;
			sum = sum + GetSum(pp, STM1[0]);
			sum = sum + GetSum(pp, STM2[0]);
			sum = sum + GetSum(pp, STM3[0]);
			sum = sum + GetSum(pp, STM4[0]);
			sum = sum + GetSum(pp, STM5[0]);
			sum = sum + GetSum(pp, STM6[0], 1);
			sum = sum * 0.7;
			return sum;

		}
		int32 GetSum(Player* pp, int32 SpellID, int type = 0)
		{
			if (type == 0)
			{
				int sum = 5;
				for (int i = 0; i < 55; i++)
				{
					if (pp->HasSpell(SpellID + i))
					{
						pp->removeSpell(SpellID+i,SPEC_MASK_ALL,false);
						if (i == 0)
							return 5;
						if (i > 0)
							sum = sum+sum+1;
						if (i == 54)
						return sum;
					}
				}
				return 0;
			}
			if (type == 1)
			{
				int sum = 10;
				for (int i = 0; i < 35; i++)
				{
					if (pp->HasSpell(SpellID + i))
					{
						pp->removeSpell(SpellID + i, SPEC_MASK_ALL, false);
						if (i == 0)
							return 10;
						if (i > 0)
							sum=sum+sum+1;
						if (i == 34)
						return sum;
					}
				}
				return 0;
			}
			return 0;
		}
		int32* GetQuests()
		{
			QueryResult idt = WorldDatabase.Query("SELECT COUNT(*) FROM quest_souls");
			int rez = (*idt)[0].Get<int16>();
			int32* rezult = new int32[rez];
			if (rez > 0)
			{
				QueryResult idt2 = WorldDatabase.Query("SELECT quest_id FROM quest_souls");
				Field* fields = idt2->Fetch();
				for (int i = 0; i < rez; i++)
				{
					rezult[i] = fields[0].Get<uint32>();
					idt2->NextRow();
				}
				return rezult;
			}
			else
			{
				rezult[0] = 0;
				return rezult;
			}
			rezult[0] = 0;
			return rezult;
		}
		int16 GetQuestCount() {
			QueryResult idt = WorldDatabase.Query("SELECT COUNT(*) FROM quest_souls");
			int16 rez = (*idt)[0].Get<int16>();
			return rez;
		}
		void sGossipHello(Player* player) override
		{   
			player->PlayerTalkClass->SendCloseGossip();
			ClearGossipMenuFor(player);
			AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_misc_note_02:30|tПолучить задание", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
			AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Achievement_bg_killxenemies_generalsroom:30|tХочу стать сильнее", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			player->TalkedToCreature(me->GetEntry(), me->GetGUID());
			SendGossipMenuFor(player, 400000, me->GetGUID());
		}

		void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
		{
			uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			player->PlayerTalkClass->SendCloseGossip();
			ClearGossipMenuFor(player);
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF + 1:
			{
				int32* STM = 0;
				std::stringstream msg;
				STM = GetSpellIdCurrent(player, 1);
				msg << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Выносливость " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				STM = GetSpellIdCurrent(player, 2);		
				std::stringstream msg2;
				msg2 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Силу "<< "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg2.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
				STM = GetSpellIdCurrent(player, 3);		
				std::stringstream msg3;
				msg3 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Ловкость " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg3.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
				STM = GetSpellIdCurrent(player, 4);		
				std::stringstream msg4;
				msg4 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Интелект " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg4.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
				STM = GetSpellIdCurrent(player, 5);	
				std::stringstream msg5;
				msg5 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Дух " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg5.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
				STM = GetSpellIdCurrent(player, 6);
				std::stringstream msg6;
				msg6 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Урон " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg6.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_sigil_mimiron:30|tВернуться в меню", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
				player->TalkedToCreature(me->GetEntry(), me->GetGUID());
				SendGossipMenuFor(player, 400000, me->GetGUID());
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 2:
			{
				if (player->GetItemCount(73903) >= 1)
				{
					int16 questCount = GetQuestCount();
					int32* res = GetQuests();
					if (questCount == 0)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("|cff44CC00[Чумный алхимический стол]|r: К сожалению разработчики ещё не добавили задания для вас.");
						return;
					}
					for (int i = 0; i < questCount; i++)
					{
						if (player->HasQuest(res[i]))
						{
							ChatHandler(player->GetSession()).PSendSysMessage("|cff44CC00[Чумный алхимический стол]|r: У вас уже есть активное задание, выполните его и получите новое!");
							return;
						}
					}
					player->DestroyItemCount(73903, 1, true);
					srand(time(NULL));
					uint32 quest_reward = res[(rand() % questCount)];
					Quest const* quest = sObjectMgr->GetQuestTemplate(quest_reward);
					player->AddQuest(quest, nullptr);
					return;
				}
				else
				{
					ChatHandler(player->GetSession()).PSendSysMessage("|cff44CC00[Чумный алхимический стол]|r: К сожалению у вас нет [Таинственного Осколка].");
					return;
				}
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 3:
			{
				int32* STM = GetSpellIdCurrent(player, 1);
				UpgradingStats(player, STM[0], STM[1], STM[2]);
				sGossipSelect(player, 400000, GOSSIP_ACTION_INFO_DEF + 1);
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 4:
			{
				int32* STM = GetSpellIdCurrent(player, 2);
				UpgradingStats(player, STM[0], STM[1], STM[2]);
				sGossipSelect(player, 400000, GOSSIP_ACTION_INFO_DEF + 1);
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 5:
			{
				int32* STM = GetSpellIdCurrent(player, 3);
				UpgradingStats(player, STM[0], STM[1], STM[2]);
				sGossipSelect(player, 400000, GOSSIP_ACTION_INFO_DEF + 1);
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 6:
			{
				int32* STM = GetSpellIdCurrent(player, 4);
				UpgradingStats(player, STM[0], STM[1], STM[2]);
				sGossipSelect(player, 400000, GOSSIP_ACTION_INFO_DEF + 1);
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 7:
			{
				int32* STM = GetSpellIdCurrent(player, 5);
				UpgradingStats(player, STM[0], STM[1], STM[2]);
				sGossipSelect(player, 400000, GOSSIP_ACTION_INFO_DEF + 1);
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 8:
			{
				int32* STM = GetSpellIdCurrent(player, 6);
				UpgradingStats(player, STM[0], STM[1], STM[2]);
				sGossipSelect(player, 400000, GOSSIP_ACTION_INFO_DEF + 1);
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 9:
			{
				sGossipHello(player);
			}
				break;
			case GOSSIP_ACTION_INFO_DEF + 10:
				break;
			default:
			{
				int32* STM = 0;
				std::stringstream msg;
				STM = GetSpellIdCurrent(player, 1);
				msg << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Выносливость " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				STM = GetSpellIdCurrent(player, 2);
				std::stringstream msg2;
				msg2 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Силу " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg2.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
				STM = GetSpellIdCurrent(player, 3);
				std::stringstream msg3;
				msg3 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Ловкость " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg3.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
				STM = GetSpellIdCurrent(player, 4);
				std::stringstream msg4;
				msg4 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Интелект " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg4.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
				STM = GetSpellIdCurrent(player, 5);
				std::stringstream msg5;
				msg5 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Дух " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg5.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
				STM = GetSpellIdCurrent(player, 6);
				std::stringstream msg6;
				msg6 << "|TInterface/ICONS/Spell_chargepositive:30|tУлучшить Урон " << "[" << std::to_string(STM[1] + 1) << " ур.] " << "Цена: " << STM[2] << " душ.";
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, msg6.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
				AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Inv_sigil_mimiron:30|tВернуться в меню", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
				player->TalkedToCreature(me->GetEntry(), me->GetGUID());
				SendGossipMenuFor(player, 400000, me->GetGUID());
			}
				break;
			}
		}
	};
	CreatureAI* GetAI(Creature* creature) const override
	{
		return new UPDTStatsAI(creature);
	}
	

};

void AddSC_UPDTStats()
{
	new UPDTStats;
}
