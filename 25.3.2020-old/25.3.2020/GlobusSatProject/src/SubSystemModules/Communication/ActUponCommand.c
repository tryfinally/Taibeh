#include <string.h>
#include <hal/errors.h>

#include "TRXVU.h"
#include "ActUponCommand.h"
#include "CommandDictionary.h"
#include "AckHandler.h"

int ActUponCommand(sat_packet_t *cmd)
{
	int err = 0;
	if (NULL == cmd){
		return E_NOT_INITIALIZED;
	}
printf("&&&&&&&&&&       === comamnd is %d %d\n", (int)cmd->cmd_type, (int)cmd->cmd_subtype);
	switch ((spl_command_type) cmd->cmd_type)
	{
	case trxvu_cmd_type:
		printf("trxvue cmd type       === comamnd is %d %d\n", (int)cmd->cmd_type, (int)cmd->cmd_subtype);
		err = trxvu_command_router(cmd);
		break;
	case eps_cmd_type:
		err = eps_command_router(cmd);
		break;
	case telemetry_cmd_type:
		err = telemetry_command_router(cmd);
		break;
	case filesystem_cmd_type:
		err = filesystem_command_router(cmd);
		break;
	case managment_cmd_type:
		err = managment_command_router(cmd);
		break;
	case ack_type: 								//this command is a ping function
		SendAckPacket(ACK_PING, cmd,NULL,0);
		break;
	}
	return err;
}


