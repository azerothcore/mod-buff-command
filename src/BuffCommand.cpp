#include "BuffCommand.h"

void Kargatum_Buff::LoadDB()
{
	uint32 oldMSTime = getMSTime();
	_Buff_Store.clear();

	QueryResult result = WorldDatabase.PQuery("SELECT spellid FROM `player_buff`");
	if (!result)
	{
		sLog->outString(">> Загружено 0 баффов. Таблица `player_buff` возможно пустая.");
		sLog->outString();
		return;
	}

	do
	{
		uint32 id = result->Fetch()->GetInt32();
		_Buff_Store.push_back(id);

	} while (result->NextRow());

	sLog->outString(">> Загружено баффов %u за %u мс", uint32(_Buff_Store.size()), GetMSTimeDiffToNow(oldMSTime));
	sLog->outString();
}

class Kargatum_BuffCommand : public CommandScript
{
public:
	Kargatum_BuffCommand() : CommandScript("Kargatum_BuffCommand") {}

	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> commandTable = // Команды с нуля
		{
			{ "buff",				SEC_PLAYER,			false, &HandleBuffCommand,							"" }
		};

		return commandTable;
	}

	static bool HandleBuffCommand(ChatHandler *handler, const char *args)
	{
		Player *player = handler->GetSession()->GetPlayer();
		std::string arg_str = (char*)args;

		if (arg_str == "reload" && AccountMgr::IsGMAccount(player->GetSession()->GetSecurity()))
		{
			sLog->outString("Перезагрузка баффов...");
			sKargatum_Buff->LoadDB();
			handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `player_buff` |cFFFF0000перезагружена.|r");
			return true;
		}
		else
		{
			if (player->duel || player->GetMap()->IsBattleArena() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead(), player->IsInCombat() || player->IsInFlight())
			{
				handler->SendSysMessage("|cff6C8CD5#|r|cFFFF0000|r Сейчас невозможно это сделать!");
				handler->SetSentErrorMessage(true);
				return false;
			}

			player->RemoveAurasByType(SPELL_AURA_MOUNTED);

			Kargatum_Buff::Kargatum_Buff_Container& sn = sKargatum_Buff->GetBuffData();
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

	void OnStartup()
	{
		sLog->outString("Загрузка баффов...");
		sKargatum_Buff->LoadDB();
	}
};

void AddBuffCommandScripts()
{
	new Kargatum_BuffCommand();
	new Kargatum_BuffLoad();
}