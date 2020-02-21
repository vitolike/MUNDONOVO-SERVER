/*
*
*	-= PMS DEFINIÇÃO PADRÃO PARA FUNÇÕES INICIAIS =-
*	Protioso MapIcon Streamer
*	Autor: Protioso ([VGS]Protioso_OC)
*
*/

//      Configuração Geral
#include "P-STREAMER\PMS\PMS_CONFIG_GERAL"
//      P-Streamer Geral
#include "P-STREAMER\P-gFUNC\P-STREAMER_gFUNC"
//      Arquivos base
#include "P-STREAMER\PMS\1.0#PMS_LIB\#PMS_BASE\PMS_B.&1"
#include "P-STREAMER\PMS\1.0#PMS_LIB\#PMS_BASE\PMS_B.&DPB"
//      Arquivos para formulação padrão
#include "P-STREAMER\PMS\1.0#PMS_LIB\#PMS_ESTRUTURA\PMS_F.&FP"
#include "P-STREAMER\PMS\1.0#PMS_LIB\#PMS_ESTRUTURA\PMS_F.(FFD)"
#include "P-STREAMER\PMS\1.0#PMS_LIB\#PMS_ESTRUTURA\PMS_F.(FFJP)"
//-----------------------------------------------------------------------------|

public pms_ChecarJogadores()
{
	for(new i; i<MAX_PLAYERS; i++)
	{
		if(ps_IsPlayerConnected(i))
		{
			pms_ChecarMapIcons(i);
			if(!PMS_JMapIcon[i][PMS_JC]) PMS_JMapIcon[i][PMS_JC] = true;
		}
		else
		{
			if(PMS_JMapIcon[i][PMS_JC])
			{
				for(new m = 1; m <= PMS_DS[PMS_Total]; m++)
				{
					if(pms_MapIconAtivo(m))
					{
					    if(PMS_JMapIcon[i][PMS_MSD])
					    {
		                	PMS_JMapIcon[i][PMS_MC][m] = false;
		                   	RemovePlayerMapIcon(i, m);
						}
						else
						{
							#if PMS_MULTI_SCRIPTS
					        	if(PMS_JMapIcon[i][PMS_MC][m] && PS_JogPegarInt(i, "PMS_TMC") > PMS_VALOR_VISIVEL) pms_RetirarMapIcon(i, m);
					        #else
					        	if(PMS_JMapIcon[i][PMS_MC][m] && PMS_JMapIcon[i][PMS_TMC] > PMS_VALOR_VISIVEL) pms_RetirarMapIcon(i, m);
					        #endif
						}
				    }
	        	}
				PMS_JMapIcon[i][PMS_JC] = false;
				PMS_JMapIcon[i][PMS_MSD] = false;
				#if PMS_MULTI_SCRIPTS
					PS_JogDefInt(i, "PMS_TMC", 0);
				#else
				    PMS_JMapIcon[i][PMS_TMC] = 0;
				#endif
			}
		}
	}
}
