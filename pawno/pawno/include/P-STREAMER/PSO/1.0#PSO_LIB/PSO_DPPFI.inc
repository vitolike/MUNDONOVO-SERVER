/*
*
*	-= PSO DEFINIÇÃO PADRÃO PARA FUNÇÕES INICIAIS =-
*	Protioso Streamer de Objetos
*	Autor: Protioso ([VGS]Protioso_OC)
*
*/

//      Configuração Geral
#include "P-STREAMER\PSO\PSO_CONFIG_GERAL"
//      P-Streamer Geral
#include "P-STREAMER\P-gFUNC\P-STREAMER_gFUNC"
//      Arquivos base
#include "P-STREAMER\PSO\1.0#PSO_LIB\#PSO_BASE\PSO_B.&1"
#include "P-STREAMER\PSO\1.0#PSO_LIB\#PSO_BASE\PSO_B.&DPB"
//      Arquivos para formulação padrão
#include "P-STREAMER\PSO\1.0#PSO_LIB\#PSO_ESTRUTURA\PSO_F.&FP"
#include "P-STREAMER\PSO\1.0#PSO_LIB\#PSO_ESTRUTURA\PSO_F.(FFD)"
#include "P-STREAMER\PSO\1.0#PSO_LIB\#PSO_ESTRUTURA\PSO_F.(FFJP)"
#include "P-STREAMER\PSO\1.0#PSO_LIB\#PSO_ESTRUTURA\PSO_F.FFR"
//-----------------------------------------------------------------------------|

public PSO_ChecarObjetos()
{
		new	Float:psojpos[3];
	#if PSO_ORDEM_TIMER
		for(new j; j < MAX_PLAYERS; j++)
		{
			if(!PSO_Jogador[j][PSO_JS])
			{
				if(ps_IsPlayerConnected(j))
	 			{
	 			    GetPlayerPos(j, psojpos[0], psojpos[1], psojpos[2]);
					for(new o = 1; o < PSO_DefGeral[PSO_NumObjetos]+1; o++)
					{
		    			if(PSO_Objetos[o][PSO_S])
		    			{
	#else
		for(new o = 1; o < PSO_DefGeral[PSO_NumObjetos]+1; o++)
		{
   			if(PSO_Objetos[o][PSO_S])
   			{
				for(new j; j < MAX_PLAYERS; j++)
				{
					if(!PSO_Jogador[j][PSO_JS])
					{
						if(ps_IsPlayerConnected(j))
			 			{
			 			    GetPlayerPos(j, psojpos[0], psojpos[1], psojpos[2]);
	#endif
						if(PSO_EmRaio(psojpos[0], psojpos[1], psojpos[2], PSO_Objetos[o][PSO_Pos][0], PSO_Objetos[o][PSO_Pos][1], PSO_Objetos[o][PSO_Pos][2], PSO_Objetos[o][PMS_RaioStream]))
		                {
							if(PSO_Objetos[o][PSO_VW] != -1)
							{
								if(GetPlayerVirtualWorld(j) != PSO_Objetos[o][PSO_VW])
								{
									if(PSO_Jogador[j][PSO_OID][o] != 0)
									{
										PSO_RETIRAR_OBJETO_JOGADOR(j, o);
									}
									continue;
								}
							}
							if(PSO_Objetos[o][PSO_JID] == -1 || j == PSO_Objetos[o][PSO_JID])
							{
							    #if PSO_MULTI_SCRIPTS
									if(PS_JogPegarInt(j, "PSO_TotalObjetos") < MAX_OBJETOS_JOGADOR && !PSO_Jogador[j][PSO_OID][o])
								#else
									if(PSO_Jogador[j][PSO_TotalObjetos] < MAX_OBJETOS_JOGADOR && !PSO_Jogador[j][PSO_OID][o])
								#endif
								{
						            PSO_Jogador[j][PSO_OID][o] = CreatePlayerObject(j, PSO_Objetos[o][PSO_ModeloID], PSO_Objetos[o][PSO_Pos][0], PSO_Objetos[o][PSO_Pos][1], PSO_Objetos[o][PSO_Pos][2],
									PSO_Objetos[o][PSO_Pos][3], PSO_Objetos[o][PSO_Pos][4], PSO_Objetos[o][PSO_Pos][5]);
									#if PSO_MULTI_SCRIPTS
										PS_JogDefInt(j, "PSO_TotalObjetos", PS_JogPegarInt(j, "PSO_TotalObjetos")+1);
									#else
									    PSO_Jogador[j][PSO_TotalObjetos]++;
									#endif
								}
								if(PSO_Objetos[o][PSO_M] > 0.0)
								{
								    if(!PSO_Jogador[j][PSO_Ms][o])
								    {
									    MovePlayerObject(j, PSO_Jogador[j][PSO_OID][o], PSO_Objetos[o][PSO_Pos][6], PSO_Objetos[o][PSO_Pos][7], PSO_Objetos[o][PSO_Pos][8], PSO_Objetos[o][PSO_M]);
	                                    PSO_Jogador[j][PSO_Ms][o] = true;
									}
								}
							}
							else
							{
								if(PSO_Jogador[j][PSO_OID][o] != 0)
								{
								    #pragma tabsize 0
									PSO_RETIRAR_OBJETO_JOGADOR(j, o);
								}
							}
						}
						else
						{
						    if(PSO_Jogador[j][PSO_JS]) continue;
							#if PSO_CONSERVAR_OBJETOS
							    #if PSO_MULTI_SCRIPTS
						    		if(PSO_Jogador[j][PSO_OID][o] != 0 && PS_JogPegarInt(j, "PSO_TotalObjetos") == MAX_OBJETOS_JOGADOR
									&& PSO_DefGeral[PSO_NumObjetos] > MAX_OBJETOS_JOGADOR)
								#else
						    		if(PSO_Jogador[j][PSO_OID][o] != 0 && PSO_Jogador[j][PSO_TotalObjetos] == MAX_OBJETOS_JOGADOR
									&& PSO_DefGeral[PSO_NumObjetos] > MAX_OBJETOS_JOGADOR)
								#endif
						    #else
						    	if(PSO_Jogador[j][PSO_OID][o] != 0 && PSO_DefGeral[PSO_NumObjetos] > MAX_OBJETOS_JOGADOR)
						    #endif
							{
								PSO_RETIRAR_OBJETO_JOGADOR(j, o);
							}
						}
					}
				}
			}
		}
	}
}
