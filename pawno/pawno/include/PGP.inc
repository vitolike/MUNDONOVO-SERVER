/*
*
*	-= PGP INCLUDE =-
*	Protioso Gerenciamento de Pickups
*
*	Autor: Protioso ([VGS]Protioso_OC)
*  	Primeira versão: 10 de dezembro de 2008 - 1.0
* 	Atualizações: 15 de dezembro de 2008 - 1.15
*	 			  25 de janeiro de 2009 - 1.15D
*                 27 de janeiro de 2009 - 1.3
*                 29 de janeiro de 2010 - 1.4 (versão em uso)
*
*/

#include "P-STREAMER\PGP\1.4#PGP_LIB\PGP_DPPFI"

/*Lista de funções do sistema PGP -----------------------------------------------------------------------------||

native pgp_AdicionarPickup(PGP_Modeloid, tipo, Float:x, Float:y, Float:z, virtualworld = 0, Float:raio_stream = PGP_RAIO_STREAM_PADRAO);
native pgp_DestruirPickup(pgpid);
native pgp_RecriarPickup(pgpid);

native pgp_Anexar3DTextLabel(pgpid, msg[], cormsg, Float:eixoz_pickup = 0.50);
native pgp_Desanexar3DTextLabel(pgpid);
native pgp_Atualizar3DTextLabel(pgpid, msg[], cormsg);
native pgp_Atualizar3DTextLabelTodo(pgpid, msg[], cormsg, Float:eixoz_pickup = 0.50);

native pgp_RetirarPickup(pgpid);
native pgp_MudarRaioStream(pgpid, Float:novo_raio_stream);
native pgp_MudarVirtualWorld(pgpid, novo_virtualworld);
native pgp_MudarModelo(pgpid, novomodeloid);
native pgp_MudarTipo(pgpid, novotipo);
native pgp_DesativarPickup(pgpid);
native pgp_PickupPGPAtiva(pgpid);
native pgp_JogadorNaPickup(playerid, pgpid);
native pgp_JogadorEmPickupModelo(playerid, PGP_Modeloid);
native pgp_ModeloPickup(pgpid);
native pgp_PegarPickupJogador(playerid);
native pgp_PegarIDRaio(playerid);
native pgp_PickupExiste(pgpid);
native pgp_JogadorEstaEmPickup(playerid);
native pgp_PegarPosicaoPickup(pgpid, &Float:x, &Float:y, &Float:z);
native pgp_PegarVirtualWorld(pgpid);
native pgp_Pegar3DEixoZ(pgpid);
native pgp_Pegar3DCor(pgpid);
native pgp_PegarMSG3D(pgpid);
native pgp_PegarRaioStream(pgpid);
native pgp_CriarPickupsDoArquivo(arquivo[]);

native pgp_JogadorEmPickup(playerid, pgpid); // "callback"
native pgp_JogadorSaiuPickup(playerid, pgpid); // "callback"
native pgp_JogadorEntrouEmRaio(playerid, pgpid); // "callback"
native pgp_JogadorSaiuRaio(playerid, pgpid); // "callback"

/------------------------------------------------------------------------------------------------------------||*/
