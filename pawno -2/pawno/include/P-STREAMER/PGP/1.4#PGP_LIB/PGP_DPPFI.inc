/*
*
*	-= PGP DEFINIÇÃO PADRÃO PARA FUNÇÕES INICIAIS =-
*	Protioso Gerenciamento de Pickups
*	Autor: Protioso ([VGS]Protioso_OC)
*
*/

//      Configuração Geral
#include "P-STREAMER\PGP\PGP_CONFIG_GERAL"
//      P-Streamer Geral
#include "P-STREAMER\P-gFUNC\P-STREAMER_gFUNC"
//      Arquivos base
#include "P-STREAMER\PGP\1.4#PGP_LIB\#PGP_BASE\PGP_B.&1"
#include "P-STREAMER\PGP\1.4#PGP_LIB\#PGP_BASE\PGP_B.&DPB"
//      Arquivos para formulação padrão
#include "P-STREAMER\PGP\1.4#PGP_LIB\#PGP_ESTRUTURA\PGP_F.&FP"
#include "P-STREAMER\PGP\1.4#PGP_LIB\#PGP_ESTRUTURA\PGP_F.(FFD)"
#include "P-STREAMER\PGP\1.4#PGP_LIB\#PGP_ESTRUTURA\PGP_F.(FFJP)"
//-----------------------------------------------------------------------------|

public pgp_ChecarPickups()
{
	new bool:jproxpickup;
	for(new p=1; p < gNumPGP+1; p++)
	{
		if(pgp_PickupPGPAtiva(p))
		{
			jproxpickup = false;
			for(new j; j < MAX_PLAYERS; j++)
			{
				if(ps_IsPlayerConnected(j))
				{
				    if(IsPlayerInRangeOfPoint(j, PGP_PickupDef[p][PGP_RaioStream], PGP_PickupDef[p][PGP_X], PGP_PickupDef[p][PGP_Y], PGP_PickupDef[p][PGP_Z]))
				    {
				        if(GetPlayerVirtualWorld(j) == PGP_PickupDef[p][PGP_VW])
				        {
					        jproxpickup = true;
					        if(PGP_JogadorDef[j][PGP_PickProx] != p) pgp_JogadorEntrouRaio;
					        if(!PGP_PickupDef[p][PGP_SPICKUPS])	pgp_CriarPickup(p);
							if(PGP_PickupDef[p][PGP_S3DL] && !PGP_JogadorDef[j][PGP_V3DL][p]) pgp_Mostrar3DTextLabel(j, p);
							if(IsPlayerInRangeOfPoint(j, 1.0, PGP_PickupDef[p][PGP_X], PGP_PickupDef[p][PGP_Y], PGP_PickupDef[p][PGP_Z]))
							{
						        PGP_JogadorDef[j][PGP_JogadorPickup] = p;
								if(!PGP_JogadorDef[j][PGP_PegouPickup]) pgp_JogadorPegouPickup(j, p);
							}
							else
							{
							    if(PGP_JogadorDef[j][PGP_JogadorPickup] == p) pgp_SaindoPickup(j, p);
							}
						}
						else
						{
							if(PGP_JogadorDef[j][PGP_PickProx] == p) pgp_SaindoProxPickup(j, p);
						}
					}
					else
					{
						if(PGP_JogadorDef[j][PGP_PickProx] == p) pgp_SaindoProxPickup(j, p);
					}
				}
				else
				{
				    if(PGP_JogadorDef[j][PGP_PickProx] == p) pgp_SaindoProxPickup(j, p, false);
				}
			}
			#if PGP_MULTI_SCRIPTS
				if(!jproxpickup && PGP_PickupDef[p][PGP_SPICKUPS] && getproperty(0, "pgp_TotalPick") > MAX_PICKUPS) pgp_RetirarPickup(p);
			#else
				if(!jproxpickup && PGP_PickupDef[p][PGP_SPICKUPS] && pgp_TotalPick > MAX_PICKUPS) pgp_RetirarPickup(p);
			#endif
		}
	}
	if(pgp_Timer) SetTimer("pgp_ChecarPickups", PGP_TEMPO_CHECAGEM, 0);
}


