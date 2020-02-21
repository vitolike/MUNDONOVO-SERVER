/*
*
*	-= P-STREAMER GERAL FUNÇÕES =-
*	Protioso Streamer
*	Autor: Protioso ([VGS]Protioso_OC)
*
*/

#include "PSF"
#include "P-STREAMER\PS_CONFIG_MAX_PLAYERS"

stock ps_PegarValorStr(str[], &ini)
{
	new
	    pos_e,
	    valor[16],
	    pf = ini,
		ts = strlen(str);

	for(new i = ini; i < ts; i++)
	{
	    if(str[i] != ',' && str[i] != ')')
	    {
	        pf++;
	    }
	    else
	    {
	        psf_CopiarStrL(valor, str, ini, pf);
			pos_e = strfind(valor, " ", true);
			if(pos_e != -1) strdel(valor, pos_e, pos_e+1);
	        ini = pf+1;
			return valor;
	    }
	}
	return valor;
}

stock PS_DefFloatInfoEs(info[], infoes, Float:valor)
{
	new propf[28];
	format(propf, 28, "PS_IE.%s.%d", info, infoes);
    setproperty(0, propf, _:valor);
}

stock Float:PS_PegarFloatInfoEs(info[], infoes)
{
	new propf[28];
	format(propf, 28, "PS_IE.%s.%d", info, infoes);
	return (!existproperty(0, propf)) ? 0.0 : Float:getproperty(0, propf);
}

#define PS_JogDefInt SetPVarInt

#define PS_JogPegarInt GetPVarInt

stock PS_AutenticarInclude(inc[])
{
	new propf[10];
	format(propf, 10, "PS:%s", inc);
    setproperty(0, propf, 1);
}

stock PS_IncludeAutenticado(inc[])
{
	new propf[10];
	format(propf, 10, "PS:%s", inc);
	return (!existproperty(0, propf)) ? 0 : getproperty(0, propf);
}

#define ps_IsPlayerConnected(%1) IsPlayerConnected(%1) && !IsPlayerNPC(%1)
