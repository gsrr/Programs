#!/usr/sbin/dtrace -s

:mpt_sas:mptsas_accept_pkt:entry
{
	trace(execname);
	
	printf("\ncmd_cdblen:%d, " , args[1]->cmd_cdblen);
	printf("\ncmd_rqslen:%d, " , args[1]->cmd_rqslen);
	printf("\ncmd_privlen:%d, " , args[1]->cmd_privlen);
	printf("\ncmd_scblen:%d, " , args[1]->cmd_scblen);
	printf("\ncmd_cdb[0]:%d, " , args[1]->cmd_cdb[0]);
	printf("\ncmd_cdb[1]:%d, " , args[1]->cmd_cdb[1]);
	printf("\ncmd_cdb[2]:%d, " , args[1]->cmd_cdb[2]);
	printf("\ncmd_sq->count:%d" , args[1]->cmd_sg->count);
}

