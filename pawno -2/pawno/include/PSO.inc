/*
*
*	-= PSO INCLUDE =-
*	Protioso Streamer de Objetos
*
*	Autor: Protioso ([VGS]Protioso_OC)
*  	Primeira versão: 29 de janeiro de 2010 - 1.0 (versão em uso)
*
*/

#include "P-STREAMER\PSO\1.0#PSO_LIB\PSO_DPPFI"

/*Lista de funções do sistema PSO -----------------------------------------------------------------------------||

native pso_CriarObjeto(modeloid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:raio_stream = PSO_RAIO_STREAM_PADRAO, virtualword = -1);
native pso_CriarObjetoJogador(playerid, modeloid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:raio_stream = PSO_RAIO_STREAM_PADRAO, virtualword = -1);
native pso_RemoverObjeto(psoid);
native pso_MoverObjeto(psoid, Float:x, Float:y, Float:z, Float:velocidade);
native pso_PararMovimentoObjeto(psoid);
native pso_MudarPosObjeto(psoid, Float:x, Float:y, Float:z);
native pso_MudarRotObjeto(psoid, Float:rx, Float:ry, Float:rz);
native pso_MudarModeloObjeto(psoid, novo_modeloid);
native pso_MudarVirtualWorldObjeto(psoid, novo_virtualworld);
native pso_MudarRaioStreamObjeto(psoid, Float:novo_raiostream);
native pso_MudarJogadorIDObjeto(psoid, novo_playerid);
native pso_PegarPosObjeto(psoid, &Float:x, &Float:y, &Float:z);
native pso_PegarRotObjeto(psoid, &Float:rx, &Float:ry, &Float:rz);
native pso_PegarModeloObjeto(psoid);
native pso_PegarJogadorIDObjeto(psoid);
native pso_ObjetoAtivo(psoid);
native pso_PegarRaioStreamObjeto(psoid);
native pso_PegarVirtualWorldObjeto(psoid);
native pso_CriarObjetosDoArquivo(arquivo[]);

native pso_ObjetoMovido(psoid); // "callback"
native pso_ObjetoJogadorMovido(playerid, psoid); // "callback"

/------------------------------------------------------------------------------------------------------------||*/
