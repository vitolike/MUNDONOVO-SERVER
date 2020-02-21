/*
*
*	-= PSF DEFINIÇÃO PADRÃO PARA FUNÇÕES INICIAIS =-
*	Protioso String Funções
*	Autor: Protioso ([VGS]Protioso_OC)
*
*/

#include "a_samp"

//      Definição do usuário
#include "PSF\PSF_USER_DEF"
//      Arquivos base
#include "PSF\1.2F3#PSF_LIB\#PSF_B\PSF_B.&1"
#include "PSF\1.2F3#PSF_LIB\#PSF_B\PSF_P.&B"
#include "PSF\1.2F3#PSF_LIB\#PSF_B\PSF.&B"
//      Arquivos CODIFICAÇÃO
#include "PSF\1.2F3#PSF_LIB\#PSF_PCOD\PSF.&PE"
#include "PSF\1.2F3#PSF_LIB\#PSF_PCOD\#PSF-C_BASE\PSF_B.&PE"
//-----------------------------------------------------------------------------|
stock psf_PCODStr(str[MAX_PCOD_CHAR], taxa = TAXA_MEDIANA) _PCOD_COMPACTAR_FINAL;

stock psf_PCODNumero(numeral)
{
	new
		f_e[64],
	 	op;
	f_e = psf_IntStr(numeral);
	psf_mN(f_e);
    while(op < 5)
    {
        strins(f_e, psf_CharStr(psf_adT(f_e[op])), strlen(f_e));
        op++;
	}
	psf_mN(f_e);
	return strval(f_e);
}

stock psf_Filtrar(str[])
{
	new
		cE[256],
	    tfb = sizeof(FiltroB);
	strcat(cE, str);
	for(new c; c < tfb; c++)
	{
		if(psf_ParteExiste(cE, FiltroB[c]))
		{
			cE = psf_SubstituirChar(cE, FiltroB[c], FiltroF[c]);
		}
	}
	return cE;
}

stock psf_ReverterFiltro(str[])
{
	new
		cD[256],
	    tff = sizeof(FiltroF);
	strcat(cD, str);
	for(new c; c < tff; c++)
	{
		if(psf_ParteExiste(cD, FiltroF[c]))
		{
			cD = psf_SubstituirChar(cD, FiltroF[c], FiltroB[c]);
		}
	}
	return cD;
}

stock psf_FormatarStrTexto(str[])
{
	new
		cF[256],
	    tfn = sizeof(TfN);
	strcat(cF, str);
	for(new c; c < tfn; c++)
	{
		if(psf_ParteExiste(cF, TfN[c]))
		{
			cF = psf_SubstituirChar(cF, TfN[c], TfF[c], false);
		}
	}
	return cF;
}
