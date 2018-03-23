#ifndef KARGATUM_BUFFCOMMAND_H
#define KARGATUM_BUFFCOMMAND_H

#include "ScriptPCH.h"
#include "AccountMgr.h"

class Kargatum_Buff
{
public:
	void LoadDB();

	typedef std::vector<uint32> Kargatum_Buff_Container;
	Kargatum_Buff_Container &GetBuffData() { return _Buff_Store; }

private:
	Kargatum_Buff_Container _Buff_Store;
};

#define sKargatum_Buff ACE_Singleton<Kargatum_Buff, ACE_Null_Mutex>::instance()

#endif