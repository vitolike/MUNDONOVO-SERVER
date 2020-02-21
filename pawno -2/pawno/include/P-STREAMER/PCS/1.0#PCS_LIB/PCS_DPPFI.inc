/*
*
*	-= PCS DEFINIÇÃO PADRÃO PARA FUNÇÕES INICIAIS =-
*	Protioso Checkpoint Streamer
*	Autor: Protioso ([VGS]Protioso_OC)
*
*/

//      Configuração Geral
#include "P-STREAMER\PCS\PCS_CONFIG_GERAL"
//      P-Streamer Geral
#include "P-STREAMER\P-gFUNC\P-STREAMER_gFUNC"
//      Arquivos base
#include "P-STREAMER\PCS\1.0#PCS_LIB\#PCS_BASE\PCS_B.&1"
#include "P-STREAMER\PCS\1.0#PCS_LIB\#PCS_BASE\PCS_B.&DPB"
//      Arquivos para formulação padrão
#include "P-STREAMER\PCS\1.0#PCS_LIB\#PCS_ESTRUTURA\PCS_F.&FP"
#include "P-STREAMER\PCS\1.0#PCS_LIB\#PCS_ESTRUTURA\PCS_F.(FFD)"
#include "P-STREAMER\PCS\1.0#PCS_LIB\#PCS_ESTRUTURA\PCS_F.(FFJP)"
//-----------------------------------------------------------------------------|

public pcs_ChecarCheckpoints()
{
	new c;
	for(new j; j < MAX_PLAYERS; j++)
	{
		if(ps_IsPlayerConnected(j))
		{
			c = pcs_PegarProxCP(j);
 			if(!c)
			{
			    if(GetPVarInt(j, "PCS_ProxCP") > 0)
			    {
			        if(GetPVarInt(j, "PCS_JCP") > 0) CallLocalFunction("pcs_JogadorSaiuCheckpoint", "dd", j, GetPVarInt(j, "PCS_JCP"));
			        PCS_RetirarCheckpointJogador;
			    }
			}
			else
			{
				if(!IsPlayerInCheckpoint(j))
				{
					if(GetPVarInt(j, "PCS_JCP") == c)
					{
						CallLocalFunction("pcs_JogadorSaiuCheckpoint", "dd", j, c);
						SetPVarInt(j, "PCS_JCP", -1);
					}
					if(GetPVarInt(j, "PCS_ProxCP") != c)
					{
						SetPVarInt(j, "PCS_ProxCP", c);
						SetPlayerCheckpoint(j, PCS_Checkpoint[c][PCS_X], PCS_Checkpoint[c][PCS_Y], PCS_Checkpoint[c][PCS_Z], PCS_Checkpoint[c][PCS_Tamanho]);
						SetPVarInt(j, "PCS_JCP", -1);
					}
				}
				else
				{
				    if(!GetPVarInt(j, "PCS_JCP")) DisablePlayerCheckpoint(j);
					else if(GetPVarInt(j, "PCS_JCP") != c)
					{
						PCS_JogadorEntrandoCheckpoint;
					}
				}
			}
		}
		else
		{
			if(GetPVarInt(j, "PCS_ProxCP") > 0)
			{
				PCS_RetirarCheckpointJogador;
			}

		}
	}
	if(PCS_Total > 0) SetTimer("pcs_ChecarCheckpoints", PCS_TEMPO_CHECAGEM, 0);
}
