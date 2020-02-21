/*
*
*	-= PBP INCLUDE =-
*	Protioso Barreiras Pontiagudas
*
*	Autor: Protioso ([VGS]Protioso_OC)
*  	Primeira versão: 23 de maio de 2010 - 1.0 (versão em uso)
*
*/

#include "PSO"

#define MAX_BARREIRAS 100
#define PBP_TEMPO_CHECAGEM 750 // Tempo em milisegundos.

/*Lista de funções do sistema PBP -----------------------------------------------------------------------------||

native pbp_CriarBarreira(Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, virtualword = -1);
native pbp_DestruirBarreira(pbpid);
native pbp_BarreiraExiste(pbpid);
native pbp_MudarPosBarreira(pbpid, Float:x, Float:y, Float:z);
native pbp_MudarRotBarreira(pbpid, Float:rx, Float:ry, Float:rz);
native pbp_MudarVWBarreira(pbpid, virtualworld);
native pbp_PegarPosBarreira(pbpid, &Float:x, &Float:y, &Float:z);
native pbp_PegarRotBarreira(pbpid, &Float:rx, &Float:ry, &Float:rz);
native pbp_PegarVWBarreira(pbpid);

/------------------------------------------------------------------------------------------------------------||*/

enum pbpdef
{
	PBP_VW,
	PBP_OID,
	Float:PBP_X,
	Float:PBP_Y,
	Float:PBP_Z,
	Float:PBP_RX,
	Float:PBP_RY,
	Float:PBP_RZ,
};

static
		PBP_Timer,
		PBP_Total,
		PBP_Barreiras[MAX_BARREIRAS][pbpdef];

#define pbp_ChecarTimerAd() if(!PBP_Timer) PBP_Timer = SetTimer("pbp_ChecarBarreiras", PBP_TEMPO_CHECAGEM, 1)
#define pbp_ChecarTimerRe() if(!PBP_Total){KillTimer(PBP_Timer); PBP_Timer = 0;}

forward pbp_ChecarBarreiras();

stock pbp_CriarBarreira(Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, virtualword = -1)
{
	new bid = pbp_ProcurarIDLivre();
	if(bid == -1)
	{
	    printf("[PBP]: Limite de barreiras (MAX_BARREIRAS = %d) foi excedido! Aumente o valor ou apague alguma...", MAX_BARREIRAS);
	    return 0;
	}
	PBP_Barreiras[bid][PBP_OID] = pso_CriarObjeto(2899, x, y, z, rx, ry, rz, PSO_RAIO_STREAM_PADRAO, virtualword);
	PBP_Barreiras[bid][PBP_X] = x;
	PBP_Barreiras[bid][PBP_Y] = y;
	PBP_Barreiras[bid][PBP_Z] = z;
	PBP_Barreiras[bid][PBP_RX] = rx;
	PBP_Barreiras[bid][PBP_RY] = ry;
	PBP_Barreiras[bid][PBP_RZ] = rz;
	PBP_Barreiras[bid][PBP_VW] = virtualword;
	pbp_ChecarTimerAd();
	PBP_Total++;
	return bid;
}

stock pbp_DestruirBarreira(pbpid)
{
	if(!PBP_Barreiras[pbpid][PBP_OID]) return 0;
	PBP_Total--;
    pso_RemoverObjeto(PBP_Barreiras[pbpid][PBP_OID]);
    PBP_Barreiras[pbpid][PBP_OID] = 0;
    pbp_ChecarTimerRe()
    return 1;
}

stock pbp_BarreiraExiste(pbpid)	return (!PBP_Barreiras[pbpid][PBP_OID]) ? 0 : 1;

stock pbp_MudarPosBarreira(pbpid, Float:x, Float:y, Float:z)
{
	if(!PBP_Barreiras[pbpid][PBP_OID]) return 0;
	PBP_Barreiras[pbpid][PBP_X] = x;
	PBP_Barreiras[pbpid][PBP_Y] = y;
	PBP_Barreiras[pbpid][PBP_Z] = z;
	return pso_MudarPosObjeto(PBP_Barreiras[pbpid][PBP_OID], x, y, z);
}

stock pbp_MudarRotBarreira(pbpid, Float:rx, Float:ry, Float:rz)
{
	if(!PBP_Barreiras[pbpid][PBP_OID]) return 0;
	PBP_Barreiras[pbpid][PBP_RX] = rx;
	PBP_Barreiras[pbpid][PBP_RY] = ry;
	PBP_Barreiras[pbpid][PBP_RZ] = rz;
	return pso_MudarRotObjeto(PBP_Barreiras[pbpid][PBP_OID], rx, ry, rz);
}

stock pbp_MudarVWBarreira(pbpid, virtualworld)
{
	if(!PBP_Barreiras[pbpid][PBP_OID]) return 0;
	PBP_Barreiras[pbpid][PBP_VW] = virtualworld;
	return pso_MudarVirtualWorldObjeto(PBP_Barreiras[pbpid][PBP_OID], virtualworld);
}

stock pbp_PegarPosBarreira(pbpid, &Float:x, &Float:y, &Float:z)
{
	if(!PBP_Barreiras[pbpid][PBP_OID])
	{
	    x = 0.0;
	    y = 0.0;
	    z = 0.0;
	}
	x = PBP_Barreiras[pbpid][PBP_X];
	y = PBP_Barreiras[pbpid][PBP_Y];
	z = PBP_Barreiras[pbpid][PBP_Z];
}

stock pbp_PegarRotBarreira(pbpid, &Float:rx, &Float:ry, &Float:rz)
{
	if(!PBP_Barreiras[pbpid][PBP_OID])
	{
	    rx = 0.0;
	    ry = 0.0;
	    rz = 0.0;
	}
	rx = PBP_Barreiras[pbpid][PBP_RX];
	ry = PBP_Barreiras[pbpid][PBP_RY];
	rz = PBP_Barreiras[pbpid][PBP_RZ];
}

stock pbp_PegarVWBarreira(pbpid)
{
	if(!PBP_Barreiras[pbpid][PBP_OID]) return 0;
	return PBP_Barreiras[pbpid][PBP_VW];
}

public pbp_ChecarBarreiras()
{
	new
	    pbpvluzes,
	    pbpvpneus,
	    pbpvpainel,
	    pbpvportas,
	    Float:pbpvx,
	    Float:pbpvy,
	    Float:pbpvz;
	    
	for(new v = 1; v < MAX_VEHICLES; v++)
	{
	    if(GetVehicleModel(v) != 0)
	    {
	        for(new b = 1; b <= PBP_Total; b++)
	        {
	            if(PBP_Barreiras[b][PBP_OID])
	            {
					if(PBP_Barreiras[b][PBP_VW] == -1 || GetVehicleVirtualWorld(v) == PBP_Barreiras[b][PBP_VW])
					{
					    GetVehiclePos(v, pbpvx, pbpvy, pbpvz);
					    if(PSO_EmRaio(pbpvx, pbpvy, pbpvz, PBP_Barreiras[b][PBP_X], PBP_Barreiras[b][PBP_Y], PBP_Barreiras[b][PBP_Z], 3.0))
					    {
							GetVehicleDamageStatus(v, pbpvpainel, pbpvportas, pbpvluzes, pbpvpneus);
							UpdateVehicleDamageStatus(v, pbpvpainel, pbpvportas, pbpvluzes, 15);
						}
					}
	            }
	        }
	    }
	}
}

stock pbp_ProcurarIDLivre()
{
	for(new b = 1; b < MAX_BARREIRAS; b++) if(!PBP_Barreiras[b][PBP_OID]) return b;
	return -1;
}
