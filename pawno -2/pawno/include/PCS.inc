/*
*
*	-= PCS INCLUDE =-
*	Protioso Checkpoint Streamer
*
*	Autor: Protioso ([VGS]Protioso_OC)
*  	Primeira versão: 29 de janeiro de 2010 - 1.0
*   Atualizações:
*                   10 de julho de 2010 - 1.2 (versão em uso)
*
*/

#include "P-STREAMER\PCS\1.0#PCS_LIB\PCS_DPPFI"

/*Lista de funções do sistema PCS -----------------------------------------------------------------------------||

native pcs_CriarCheckpoint(Float:x, Float:y, Float:z, Float:tamanho, Float:raio_visualizacao, virtualworld = -1);
native pcs_CriarJogadorCheckpoint(playerid, Float:x, Float:y, Float:z, Float:tamanho, Float:raio_visualizacao, virtualworld = -1);
native pcs_AtualizarCheckpoint(pcsid, Float:x, Float:y, Float:z, Float:tamanho, Float:raio_visualizacao, virtualworld);
native pcs_DesativarCheckpoint(pcsid);

native pcs_PegarPosCheckpoint(pcsid, &Float:x, &Float:y, &Float:z);
native pcs_PegarVirtualWorldCheckpoint(pcsid);
native pcs_PegarTamanhoCheckpoint(pcsid);
native pcs_PegarRaioCheckpoint(pcsid);
native pcs_PegarCheckpointJogador(playerid);
native pcs_PegarCheckpointMostrado(playerid);
native pcs_JogadorNoCheckpoint(playerid, pcsid);
native pcs_CheckpointAtivo(pcsid)
native pcs_CriarCheckpointsDoArquivo(arquivo[]);

native pcs_JogadorEntrouCheckpoint(playerid, pcsid); // "callback"
native pcs_JogadorSaiuCheckpoint(playerid, pcsid); // "callback"

/------------------------------------------------------------------------------------------------------------||*/
