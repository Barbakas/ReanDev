/*
npc_tarea1.cpp

Blah Blah Blah


By Barbakas
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"


class npc_tarea1 : public CreatureScript
{
public:
	npc_tarea1() :CreatureScript("npc_tarea1") {}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->isInCombat())
		{
			player->GetSession()->SendNotification("You are in combat!");
			return false;
		}

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Combate", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Angel", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		
		player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());

		player->SetDisplayId(16358);

		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 actions)
	{
		//if (!player) return false;

		player->PlayerTalkClass->ClearMenus();

		if (actions == GOSSIP_ACTION_INFO_DEF + 1)
		{
			//player->SetDisplayId(16358);
			creature->MonsterSay("¡¡¡LUCHAAAA!!!",LANG_UNIVERSAL,0);
			player->CLOSE_GOSSIP_MENU();
		}
		else if (actions == GOSSIP_ACTION_INFO_DEF + 2)
		{
			player->SetDisplayId(25900);
			creature->MonsterSay("Angelito...", LANG_UNIVERSAL, 0);
			player->CLOSE_GOSSIP_MENU();
		}

		return true;
	}
};

void AddSC_npc_tarea1()
{
	new  npc_tarea1();
}