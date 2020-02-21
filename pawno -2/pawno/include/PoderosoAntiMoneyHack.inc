/* Creditos a Poderoso Chefão
Como Usar:
Passo 1: Substitua GetPlayerMoney por PC_DarDinheiro
Passo 2: Substitua GetPlayerMoney por PC_GetarDinheiro
Passo 3: Substitua ResetPlayerMoney por PC_ResetarDinheiro
Passo 4: Adicione a função PC_AtualizarDinheiro(playerid); na public OnPlayerUpdate(playerid)
Extra: para escolher a versão que deseja utilizar Defina VERSAO_DO_SAMP (Defina 0 para 0.2x ou Defina 1 para 0.3b)
Creditos: Poderoso Chefão
native PC_DarDinheiro(playerid,Dinheiro);
native PC_SetarDinheiro(playerid,Dinheiro);
native PC_GetarDinheiro(playerid);
native PC_ResetarDinheiro(playerid);
native PC_AtualizarDinheiro(playerid);
*/
#include <a_samp>
#define VERSAO_DO_SAMP 0 // Defina 0 para 0.2x ou Defina 1 para 0.3b+
#if VERSAO_DO_SAMP == 1
stock PC_DarDinheiro(playerid,Dinheiro) return SetPVarInt(playerid,"dinheiro",GetPVarInt(playerid,"dinheiro")+Dinheiro);
stock PC_SetarDinheiro(playerid,Dinheiro) return SetPVarInt(playerid,"dinheiro",Dinheiro);
stock PC_GetarDinheiro(playerid) return GetPVarInt(playerid,"dinheiro");
stock PC_ResetarDinheiro(playerid) return SetPVarInt(player6id,"dinheiro",0);
stock ChefaoSetarDinheiro(playerid) { ResetPlayerMoney(playerid); GivePlayerMoney(playerid, GetPVarInt(playerid,"dinheiro")); }
stock PC_AtualizarDinheiro(playerid) if(GetPlayerMoney(playerid) != GetPVarInt(playerid,"dinheiro")) ChefaoSetarDinheiro(playerid);
#endif
#if VERSAO_DO_SAMP == 0
new PC_Dinheiro[MAX_PLAYERS];
stock PC_DarDinheiro(playerid,Dinheiro) return PC_Dinheiro[playerid] += Dinheiro;
stock PC_SetarDinheiro(playerid,Dinheiro) return PC_Dinheiro[playerid] = Dinheiro;
stock PC_GetarDinheiro(playerid) return PC_Dinheiro[playerid];
stock PC_ResetarDinheiro(playerid) return PC_Dinheiro[playerid] = 0;
stock ChefaoSetarDinheiro(playerid) { ResetPlayerMoney(playerid); GivePlayerMoney(playerid, PC_Dinheiro[playerid]); }
stock PC_AtualizarDinheiro(playerid) if(GetPlayerMoney(playerid) != PC_Dinheiro[playerid]) ChefaoSetarDinheiro(playerid);
#endif
