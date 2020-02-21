/*
*
*	-= P-STREAMER =-
*	Protioso Streamer
*	Autor: Protioso ([VGS]Protioso_OC)
*   Obs.: os valores abaixo podem ser editados conforme sua necessidade!
*
*/

#if !defined PMS_MULTI_SCRIPTS
	#define PMS_MULTI_SCRIPTS 0
/* Para compartilhar informações com outros scripts.
Deixe em 1 para habilitar (recomendado) e 0 para desabilitar. */
#endif

#if !defined PMS_MAX_MAPICON
	#define PMS_MAX_MAPICON 500
/* Limite de mapicons (altere como preferir). */
#endif

#if !defined PMS_VALOR_VISIVEL
	#define PMS_VALOR_VISIVEL 100
/* Máximo que o jogador pode ver. Não pode
ultrapassar passar o limite do SA-MP! */
#endif

#if !defined PMS_TEMPO_CHECAGEM
	#define PMS_TEMPO_CHECAGEM 1000
/* Tempo em milisegundos. */
#endif

#if !defined PMS_RAIO_STREAM_PADRAO
	#define PMS_RAIO_STREAM_PADRAO 80.0
/* Se você não identificar um valor para o
raio que o mapicon aparecerá nas funções para criar mapicon, este valor irá ser
usado para o novo mapicon criado. */
#endif
