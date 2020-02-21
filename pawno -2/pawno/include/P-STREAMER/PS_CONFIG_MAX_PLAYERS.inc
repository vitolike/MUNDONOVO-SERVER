/*
*
*	-= P-STREAMER =-
*	Protioso Streamer
*	Autor: Protioso ([VGS]Protioso_OC)
*   Obs.: o valor abaixo pode ser editado conforme sua necessidade!
*
*/

#if defined MAX_PLAYERS
	#undef MAX_PLAYERS
#endif
#if defined PS_MAX_PLAYERS
	#define MAX_PLAYERS PS_MAX_PLAYERS
#else
	#define MAX_PLAYERS 500
/* Seu servidor está mesmo com limite para 500
jogadores? Vamos racionalizar e aumentar a eficiência, caso você não use 500
abaixe este valor para a quantia máxima definida em seu server.cfg!
 Por exemplo, se seu servidor está limitado para apenas 50 jogadores não há
motivos para deixar em 500. Uma quantia de 450 em um loop para vários
elementos (objetos, pickups...) faz uma enorme diferença! */
#endif
