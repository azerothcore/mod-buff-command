# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore
## mod-buff-command
### This is a module for [AzerothCore](http://www.azerothcore.org)
- Latest build status with azerothcore: [![Build Status](https://github.com/azerothcore/mod-buff-command/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/azerothcore/mod-buff-command)


- Description
- Configuration
- How to use
- Use database

### Description:
Add custom command .buff for self buff
With this command, all the spell id's specified in the table are applied to the character `world`.`player_buff`

### Configuration:
```ini
# Settings to control the .buff command
#
#    BuffCommand.Enable
#        Description: Enable the .buff command
#        Default:     1 - (Enabled)
#                     0 - (Disabled)

BuffCommand.Enable = 1

# Settings to control the cooldown of .buff command
#
#    BuffCommand.Cooldown
#        Description: Enable Cooldown for .buff command
#        Default:     120 - (Enabled)
#                     0 - (Disabled)

BuffCommand.Cooldown = 120
```

### How to use:
Change conf and change data in database

### Use databse:
```sql
`world`.`player_buff`
```

- `SpellID` - Spell number
- `Comment` - You comment


