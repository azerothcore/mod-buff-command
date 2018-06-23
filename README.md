# BuffCommand [![Build Status](https://travis-ci.org/Winfidonarleyan/BuffCommand-module.svg?branch=master)](https://travis-ci.org/Winfidonarleyan/BuffCommand-module)

### This is a module for [AzerothCore](http://www.azerothcore.org)

#### Features:
- This module add custom command .buff
- Buff self spells from table `player_buff`

### This module currently requires:
- AzerothCore v1.0.1+

### How to install
1. Simply place the module under the `modules` folder of your AzerothCore source folder.
2. Re-run cmake and launch a clean build of AzerothCore
3. Import the SQL manually to the right Database (world) or with the `db_assembler.sh` (if `include.sh` provided).
4. Edit table `world.player_buff`.
5. Done :)

### Usage
- Write to chat .buff (buff self spells)
- Write to chat .buff reload (reload table `player_buff`)

## Credits
* [Winfidonarleyan](https://github.com/Winfidonarleyan): (author of the module): 
* [BarbzYHOOL](https://github.com/barbzyhool): best guy
* [Talamortis](https://github.com/talamortis): almost best guy

AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
