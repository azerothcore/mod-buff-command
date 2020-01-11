#!/usr/bin/env bash

MOD_BUFF_COMMAND_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_BUFF_COMMAND_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_BUFF_COMMAND_ROOT"/conf/conf.sh" ]; then
    source $MOD_BUFF_COMMAND_ROOT"/conf/conf.sh"
fi
