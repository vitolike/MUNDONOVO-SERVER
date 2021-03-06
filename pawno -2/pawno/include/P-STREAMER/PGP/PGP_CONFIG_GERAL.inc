/*
*
*	-= P-STREAMER =-
*	Protioso Streamer
*	Autor: Protioso ([VGS]Protioso_OC)
*   Obs.: os valores abaixo podem ser editados conforme sua necessidade!
*
*/

#if !defined PGP_MULTI_SCRIPTS
	#define PGP_MULTI_SCRIPTS 0
/* Para compartilhar informa��es com outros scripts.
Deixe em 1 para habilitar (recomendado) e 0 para desabilitar. */
#endif

#if !defined MAX_PGP
	#define MAX_PGP 2200
/* Limite de pickups (altere como preferir). */
#endif

#if !defined PGP_TEMPO_CHECAGEM
	#define PGP_TEMPO_CHECAGEM 1000
/* Tempo em milisegundos. */
#endif

#if !defined PGP_TEMPO_PEGAR_PICKUP
	#define PGP_TEMPO_PEGAR_PICKUP -1
/* Isto � o tempo que leva para avisar
NOVAMENTE que o jogador pegou a pickup (se ele j� est� nela)
Deixe em -1 para desativar (normal). Tempo em milisegundos.  */
#endif

#if !defined MAX_PGP3DTEXTLABEL_MSG
	#define MAX_PGP3DTEXTLABEL_MSG 128
/* Limite m�ximo de caracteres. */
#endif

#if !defined PGP_RAIO_STREAM_PADRAO
	#define PGP_RAIO_STREAM_PADRAO 50.0
/* Se voc� n�o identificar um valor para o
raio que a pickup aparecer� na fun��o pgp_AdicionarPickup, este valor ir� ser
usado para a nova pickup criada. */
#endif
