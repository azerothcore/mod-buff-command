#ifndef KARGATUM_BUFFCOMMAND_H
#define KARGATUM_BUFFCOMMAND_H

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Player.h"
#include "Chat.h"
#include <vector>

class Kargatum_Buff
{
public:
	static Kargatum_Buff* instance();
	void LoadDB();

	typedef std::vector<uint32> Kargatum_Buff_Container;
	Kargatum_Buff_Container &GetBuffData() { return _buffStore; }

private:
	Kargatum_Buff_Container _buffStore;
};

#define sKargatumBuff Kargatum_Buff::instance()

#endif
