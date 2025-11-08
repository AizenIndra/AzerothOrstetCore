/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// This is where scripts' loading functions should be declared:
// void MyExampleScript()
void AddSC_Professions_NPC();
void AddSC_npc_trainer();
void AddSC_Enchat_npc_new();
void AddSC_Login_script();
void AddSC_DuelReset();
void AddSC_CustomTeleportOrCommand();
void AddSC_TemplateNPC();
void AddSC_npc_1v1arena();
void AddSC_DeathMatchkill();
void AddSC_NPC_RANK_VENDOR();
void AddSC_ServerMenuPlayerGossip();
void AddSC_npc_custom_boss();
void AddSC_RewardRangKillBoss();
void AddSC_CustomBossAnna();
void AddSC_UPDTStats();
void AddSC_DailyQuestReset();
void AddAutoReviveScripts();
void AddSC_hujal_teleport();
void AddSC_first_character_item_reward();
//WorldBosses
void AddSC_aliden();
void AddSC_alliance_boss();
void AddSC_anna();
void AddSC_CustomBossFalricScripts();
void AddSC_boss_galadriel();
void AddSC_orrig();
void AddSC_tolreos();
void AddSC_two();

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
    AddSC_Professions_NPC();
    AddSC_npc_trainer();
    AddSC_Enchat_npc_new(); 
    AddSC_Login_script();
    AddSC_DuelReset();
    AddSC_CustomTeleportOrCommand();
    AddSC_TemplateNPC();
    AddSC_npc_1v1arena();
    AddSC_DeathMatchkill();
    AddSC_NPC_RANK_VENDOR();
    AddSC_ServerMenuPlayerGossip();
    AddSC_npc_custom_boss();
    AddSC_RewardRangKillBoss();
    AddSC_CustomBossAnna();
    AddSC_UPDTStats();
    AddSC_DailyQuestReset();
    AddAutoReviveScripts();
    AddSC_hujal_teleport();
    AddSC_first_character_item_reward();
    //WorldBosses
    AddSC_aliden();
    AddSC_alliance_boss();
    AddSC_anna();
    AddSC_CustomBossFalricScripts();
    AddSC_boss_galadriel();
    AddSC_orrig();
    AddSC_tolreos();
    AddSC_two();
}
