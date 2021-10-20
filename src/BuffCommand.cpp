#include "ScriptMgr.h"
#include "BuffCommand.h"
#include "World.h"
#include "WorldSession.h"
#include "Config.h"

std::unordered_map<ObjectGuid, uint32> BuffCooldown;

Kargatum_Buff* Kargatum_Buff::instance()
{
    static Kargatum_Buff instance;
    return &instance;
}

void Kargatum_Buff::LoadDB()
{
	uint32 oldMSTime = getMSTime();
	_buffStore.clear();

	QueryResult result = WorldDatabase.PQuery("SELECT spellid FROM `player_buff`");
	if (!result)
	{
		sLog->outErrorDb(">> Loaded 0 buff. DB table `player_buff` is empty!");
		sLog->outString();
		return;
	}

	do
	{
		uint32 id = result->Fetch()->GetInt32();
		_buffStore.push_back(id);

	} while (result->NextRow());

	sLog->outString(">> Loaded %u buff in %u ms", uint32(_buffStore.size()), GetMSTimeDiffToNow(oldMSTime));
	sLog->outString();
}

class KargatumCS_BuffCOmmand : public CommandScript
{
public:
	KargatumCS_BuffCOmmand() : CommandScript("KargatumCS_BuffCOmmand") {}

	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> commandTable = // .commands
		{
			{ "buff",				SEC_PLAYER,			false, &HandleBuffCommand,	"" }
		};

		return commandTable;
	}

	static bool HandleBuffCommand(ChatHandler *handler, const char *args)
	{
		Player* player = handler->GetSession()->GetPlayer();
		std::string ArgStr = (char*)args;

        if (sConfigMgr->GetIntDefault("BuffCommand.Enable", 1) == 0) {
            handler->SendSysMessage("The command is currently disabled");
            handler->SetSentErrorMessage(true);
            return false;
        }

		if (sConfigMgr->GetIntDefault("BuffCommand.MinLevel", 80) > 0) {
			uint8 MinLevel  = sConfigMgr->GetIntDefault("BuffCommand.MinLevel", 80);
			if (player->getLevel() < sConfigMgr->GetIntDefault("BuffCommand.MinLevel", 80))
			{
				std::string MinLevelError = "You must be ";
				if (MinLevel != 80)
					MinLevelError += "atleast ";
				MinLevelError += "level " + std::to_string(MinLevel) + " to use this command.";
				handler->SendSysMessage((MinLevelError).c_str());
	            handler->SetSentErrorMessage(true);
				return false;
			}
		}

		if (ArgStr == "reload" && AccountMgr::IsAdminAccount(player->GetSession()->GetSecurity()))
		{
			sLog->outString("Re-Loading Player Buff data...");
			sKargatumBuff->LoadDB();
			handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Table|r `player_buff` |cFFFF0000re.|r");
			return true;
		}
		else
		{
			if (player->duel || player->GetMap()->IsBattleArena() || player->InBattleground() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead()|| player->IsInCombat() || player->IsInFlight() || player->HasStealthAura() || player->HasInvisibilityAura())
			{
				handler->SendSysMessage("You can not do it now");
				handler->SetSentErrorMessage(true);
				return false;
            }

            auto searchGUID = BuffCooldown.find(player->GetGUID());

            if (searchGUID == BuffCooldown.end())
                BuffCooldown[player->GetGUID()] = 0; // Leader GUID not found, initialize with 0

            if (sWorld->GetGameTime() - BuffCooldown[player->GetGUID()] < sConfigMgr->GetIntDefault("BuffCommand.Cooldown", 120) || sWorld->GetGameTime() == BuffCooldown[player->GetGUID()])
            {
                handler->SendSysMessage(("You have to wait atleast " + std::to_string(sConfigMgr->GetIntDefault("BuffCommand.Cooldown", 120)) + " seconds before using .buff again!").c_str());
                handler->SetSentErrorMessage(true);
				return false;
            }

            if (sWorld->GetGameTime() - BuffCooldown[player->GetGUID()] >= sConfigMgr->GetIntDefault("BuffCommand.Cooldown", 120)) {
            	BuffCooldown[player->GetGUID()] = sWorld->GetGameTime();
            }

            player->RemoveAurasByType(SPELL_AURA_MOUNTED);

			Kargatum_Buff::Kargatum_Buff_Container& sn = sKargatumBuff->GetBuffData();
			for (auto i : sn)
				player->CastSpell(player, i, true);

			return true;
		}
	}
};

class Kargatum_BuffLoad : public WorldScript
{
public:
	Kargatum_BuffLoad() : WorldScript("Kargatum_BuffLoad") {}

	void OnStartup() override
	{
		sLog->outString("Loading player buff command ...");
		sKargatumBuff->LoadDB();
	}
};

void AddBuffCommandScripts()
{
	new KargatumCS_BuffCOmmand();
	new Kargatum_BuffLoad();
}
