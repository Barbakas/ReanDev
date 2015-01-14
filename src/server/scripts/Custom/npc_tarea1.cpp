/*
npc_tarea1.cpp

Bien, tu primera tarea. Deberás hacer en código un npc custom que tenga un gossip (menú).

- Cuando hagas click en el para abrirlo, te transforme en cerdo
- Debe tener dos opciones. Una de ellas, para ponerte en combate e iniciar una batalla con al menos 4 spell y 2 diálogos. La segunda opción, debe transportarte a Dalaran
- Cuando le lances un beso, te transformará en Angel
- Cuando le escupas, deberá matarte.

By Barbakas
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"


enum ScriptTexts //IDs in the creature_text Table
{
	//Neutral
	SAY_ANGEL_TRANSFORM = 0,	
	SAY_SPIT = 1,

	//Combat
	SAY_YELL_1 = 2,
	SAY_YELL_2 = 3,
	SAY_YELL_3 = 4,
	SAY_YELL_4 = 5,
	SAY_AGGRO = 6,
	SAY_BERSERK = 7,
	SAY_DEATH = 8,
	SAY_KILL = 9,
};

enum Spells
{	
	SPELL_PUMMEL		= 12555,
	SPELL_POISON_BOLT	= 24099,
	SPELL_UPPERCUT		= 39069,
	SPELL_KNOCKBACK		= 26027,
	//SPELL_FRENZY		= 23537,
	SPELL_BERSERK		= 32965,
};

enum Events
{
	EVENT_YELL = 1,
	EVENT_DAMAGE = 2,
	EVENT_KNOCKING = 3,
	EVENT_DOT = 4,
	EVENT_BERSERK = 5
};

enum Models
{
	MODEL_PIG				= 16358,
	MODEL_ANGEL				= 5233,
};

enum eEnums
{
	// any other constants
	FACTION_WORGEN = 24
};

//List of gossip item texts. Items will appear in the gossip window.
#define GOSSIP_FIGHT		"I'm looking for a fight"
#define GOSSIP_DALARAN		"Could you teleport me to Dalaran?"

class npc_tarea1 : public CreatureScript
{
public:
	npc_tarea1() :CreatureScript("npc_tarea1") {}

	struct Tarea1AI : public ScriptedAI
	{
		Tarea1AI(Creature* creature) : ScriptedAI(creature) {}		

		void Reset()
		{
			me->RestoreFaction();
		}

		void EnterCombat(Unit* who)
		{
			//Prepare the events
			events.Reset();
			events.ScheduleEvent(EVENT_YELL, 10000);
			events.ScheduleEvent(EVENT_DAMAGE, 5000);
			events.ScheduleEvent(EVENT_DOT, urand(10000, 20000));
			events.ScheduleEvent(EVENT_KNOCKING, 19000);
			events.ScheduleEvent(EVENT_BERSERK, 120000);

			//Say some stuff			
			Talk(SAY_AGGRO);
		}

		void UpdateAI(uint32 const diff)
		{
			if (!UpdateVictim() )
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_YELL:
					Talk(RAND(SAY_YELL_1, SAY_YELL_2, SAY_YELL_3, SAY_YELL_4));
					events.ScheduleEvent(EVENT_YELL, 20000);
					break;
				case EVENT_DAMAGE:
					DoCastVictim(SPELL_PUMMEL);
					events.ScheduleEvent(EVENT_DAMAGE, 5000);
					break;

				case EVENT_DOT:
					DoCastVictim(SPELL_POISON_BOLT);
					events.ScheduleEvent(EVENT_DOT, urand(10000, 20000));
					break;

				case EVENT_KNOCKING:
					DoCastVictim(RAND(SPELL_UPPERCUT, SPELL_KNOCKBACK));
					events.ScheduleEvent(EVENT_KNOCKING, 19000);
					break;

				case EVENT_BERSERK:
					DoCast(me, SPELL_BERSERK);
					Talk(SAY_BERSERK);
					break;

				}

			}
			
			DoMeleeAttackIfReady();
		
		}

		void ReceiveEmote(Player* player, uint32 uiTextEmote)
		{
			me->HandleEmoteCommand(uiTextEmote);

			switch (uiTextEmote)
			{
			case TEXT_EMOTE_KISS:
				Talk(SAY_ANGEL_TRANSFORM);
				player->SetDisplayId(MODEL_ANGEL);
				break;
			case TEXT_EMOTE_SPIT:
				if (player->isGossip()) player->PlayerTalkClass->ClearMenus();
				Talk(SAY_SPIT);
				me->DealDamage(player, 1000000);//kill (ugly way...)
				break;
			}
		}

	protected:
		EventMap events;

	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new Tarea1AI(creature);
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FIGHT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DALARAN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		
		player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());

		//Transformacion en cerdo
		player->SetDisplayId(MODEL_PIG);

		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 actions)
	{
		player->PlayerTalkClass->ClearMenus();

		if (actions == GOSSIP_ACTION_INFO_DEF + 1) //Fight
		{
			player->CLOSE_GOSSIP_MENU();

			creature->setFaction(FACTION_WORGEN);
			creature->AI()->AttackStart(player);

		}
		else if (actions == GOSSIP_ACTION_INFO_DEF + 2)//Dalaran
		{
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5804.585f, 624.726f, 647.780f, 1.820647f);
		}

		return true;
	}
};

void AddSC_npc_tarea1()
{
	new  npc_tarea1();
}