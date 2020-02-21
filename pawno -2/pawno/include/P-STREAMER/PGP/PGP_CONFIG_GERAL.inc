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
/* Para compartilhar informações com outros scripts.
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
/* Isto é o tempo que leva para avisar
NOVAMENTE que o jogador pegou a pickup (se ele já está nela)
Deixe em -1 para desativar (normal). Tempo em milisegundos.  */
#endif

#if !defined MAX_PGP3DTEXTLABEL_MSG
	#define MAX_PGP3DTEXTLABEL_MSG 128
/* Limite máximo de caracteres. */
#endif

#if !defined PGP_RAIO_STREAM_PADRAO
	#define PGP_RAIO_STREAM_PADRAO 50.0
/* Se você não identificar um valor para o
raio que a pickup aparecerá na função pgp_AdicionarPickup, este valor irá ser
usado para a nova pickup criada. */
#endif
