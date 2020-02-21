/*
*
*	-= PMS INCLUDE =-
*	Protioso MapIcon Streamer
*
*	Autor: Protioso ([VGS]Protioso_OC)
*  	Primeira versão: 29 de janeiro de 2010 - 1.0 (versão em uso)
*
*/

#include "P-STREAMER\PMS\1.0#PMS_LIB\PMS_DPPFI"

/*Lista de funções do sistema PMS -----------------------------------------------------------------------------||

native pms_CriarMapIcon(Float:x, Float:y, Float:z, modeloid, cor, Float:raio_visualizacao = PMS_RAIO_STREAM_PADRAO, virtualword = -1);
native pms_CriarMapIconJogador(playerid, Float:x, Float:y, Float:z, modeloid, cor, Float:raio_visualizacao = PMS_RAIO_STREAM_PADRAO, virtualword = -1);
native pms_RemoverMapIcon(pmsid);
native pms_ModeloValido(modeloid);
native pms_ColocarVirtualWorld(pmsid, virtualword);
native pms_ColocarModelo(pmsid, modeloid);
native pms_ColocarDistancia(pmsid, Float:distancia);
native pms_ColocarCor(pmsid, cor);
native pms_ColocarCoordenadas(pmsid, Float:x, Float:y, Float:z);
native pms_PegarVirtualWorldMapIcon(pmsid);
native pms_PegarCorMapIcon(pmsid);
native pms_PegarPosMapIcon(pmsid, &Float:x, &Float:y, &Float:z);
native pms_PegarRaioMapIcon(pmsid);
native pms_PegarModeloMapIcon(pmsid);
native pms_MapIconAtivo(pmsid);
native pms_CriarMapIconsDoArquivo(arquivo[]);

/------------------------------------------------------------------------------------------------------------||*/
