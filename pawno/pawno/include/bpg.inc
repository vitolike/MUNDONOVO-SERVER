/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                       *
*                                                                       *
*	        ******* Include - KveH *******                       		*
*                                                                       *
*	         Ken's 0.3c Vehicle Include Functions  (KveH)               *
*                                                                       *
*	            Autor: rjjj ou [iPs]Ken.	                            *
*	            Créditos á audifan00 á tudo relacionado á Neons.        *
*				Agradecimentos: [iPs] Team. 		                    *
*                                                                       *
*                                                                       *
*                                                                       *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "a_samp.inc"

#if defined _KveH_included
	#endinput
#endif
#define _KveH_included


#define StatusON true
#define StatusOFF false
#define Neon_Azul ((5))
#define Neon_Vermelho ((6))
#define Neon_Verde ((7))
#define Neon_Branco ((8))
#define Neon_Rosa ((9))
#define Neon_Amarelo ((10))


static VehiclePlateData[MAX_VEHICLES][30];
new bool:DefinedPlaca[MAX_VEHICLES];
new VehicleNeon[MAX_VEHICLES],VehicleNeon2[MAX_VEHICLES];
new VeiculoNeonCor[MAX_VEHICLES];

/*
Funções:


native SetVehiclePlate(vehicleid, textplate[]);
native GetVehiclePlate(vehicleid);
native SetVehicleLock(vehicleid, bool:status);
native SetVehicleEngine(vehicleid, bool:status);
native SetVehicleLigths(vehicleid, bool:status);
native SetVehicleCapo(vehicleid, bool:status);
native SetVehiclePortaMala(vehicleid, bool:status);
native SetVehicleNeon(vehicleid, cor, bool:status);
native GetVehicleLock(vehicleid);
native GetVehicleEngine(vehicleid);
native GetVehicleLigths(vehicleid);
native GetVehicleCapo(vehicleid);
native GetVehiclePortaMala(vehicleid);
native GetVehicleNeonColor(vehicleid);
*/


stock SetVehiclePlate(vehicleid, textplate[]){
    strmid(VehiclePlateData[vehicleid],textplate,false,strlen(textplate),30);
	SetVehicleNumberPlate(vehicleid,textplate);
	new Float:VeiculoX, Float:VeiculoY, Float:VeiculoZ;
 	GetVehiclePos(vehicleid, VeiculoX, VeiculoY, VeiculoZ);
 	SetVehicleToRespawn(vehicleid);
 	SetVehiclePos(vehicleid, VeiculoX, VeiculoY, VeiculoZ);
	DefinedPlaca[vehicleid] = true;
	return 1;
}

stock GetVehiclePlate(vehicleid){
	if(!DefinedPlaca[vehicleid])
	{
        strmid(VehiclePlateData[vehicleid],"XYZR 000",false,strlen("XYZR 000"),30);
	}
	return VehiclePlateData[vehicleid];
}

stock SetVehicleLock(vehicleid, bool:status){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	SetVehicleParamsEx(vehicleid, maquina, luzes, alarme, status, capota, portamala, objective);
	return 1;
}
stock SetVehicleEngine(vehicleid, bool:status){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	SetVehicleParamsEx(vehicleid, status, luzes, alarme, portas, capota, portamala, objective);
	return 1;
}
stock SetVehicleLigths(vehicleid, bool:status){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	SetVehicleParamsEx(vehicleid, maquina, status, alarme, portas, capota, portamala, objective);
	return 1;
}
stock SetVehicleCapo(vehicleid, bool:status){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	SetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, status, portamala, objective);
	return 1;
}
stock SetVehiclePortaMala(vehicleid, bool:status){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	SetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, status, objective);
	return 1;
}

stock GetVehicleLock(vehicleid){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	return portas;
}

stock GetVehicleEngine(vehicleid){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	return maquina;
}
stock GetVehicleLigths(vehicleid){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	return luzes;
}
stock GetVehicleCapo(vehicleid){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	return capota;
}
stock GetVehiclePortaMala(vehicleid){
	new maquina, luzes, alarme, portas, capota, portamala, objective;
	GetVehicleParamsEx(vehicleid, maquina, luzes, alarme, portas, capota, portamala, objective);
	return portamala;
}

stock SetVehicleNeon(vehicleid, cor, bool:status){
	if(!status) return ResetVehicleNeon(vehicleid);
	if(cor == Neon_Azul)
	{
	    VeiculoNeonCor[vehicleid] = Neon_Azul;
	    DestroyObject(VehicleNeon[vehicleid]);
	    DestroyObject(VehicleNeon2[vehicleid]);
	    VehicleNeon[vehicleid] = CreateObject(18648,0,0,0,0,0,0);
	    VehicleNeon2[vehicleid] = CreateObject(18648,0,0,0,0,0,0);
 		AttachObjectToVehicle(VehicleNeon[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	 	AttachObjectToVehicle(VehicleNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	}
	else if(cor == Neon_Vermelho)
	{
	    VeiculoNeonCor[vehicleid] = Neon_Vermelho;
	    DestroyObject(VehicleNeon[vehicleid]);
	    DestroyObject(VehicleNeon2[vehicleid]);
	    VehicleNeon[vehicleid] = CreateObject(18647,0,0,0,0,0,0);
	    VehicleNeon2[vehicleid] = CreateObject(18647,0,0,0,0,0,0);
 		AttachObjectToVehicle(VehicleNeon[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	 	AttachObjectToVehicle(VehicleNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	}
	else if(cor == Neon_Verde)
	{
	    VeiculoNeonCor[vehicleid] = Neon_Verde;
	    DestroyObject(VehicleNeon[vehicleid]);
	    DestroyObject(VehicleNeon2[vehicleid]);
	    VehicleNeon[vehicleid] = CreateObject(18649,0,0,0,0,0,0);
	    VehicleNeon2[vehicleid] = CreateObject(18649,0,0,0,0,0,0);
 		AttachObjectToVehicle(VehicleNeon[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	 	AttachObjectToVehicle(VehicleNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	}
	else if(cor ==  Neon_Branco)
	{
	    VeiculoNeonCor[vehicleid] = Neon_Branco;
	    DestroyObject(VehicleNeon[vehicleid]);
	    DestroyObject(VehicleNeon2[vehicleid]);
	    VehicleNeon[vehicleid] = CreateObject(18652,0,0,0,0,0,0);
	    VehicleNeon2[vehicleid] = CreateObject(18652,0,0,0,0,0,0);
 		AttachObjectToVehicle(VehicleNeon[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	 	AttachObjectToVehicle(VehicleNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	}
	else if(cor == Neon_Rosa)
	{
	    VeiculoNeonCor[vehicleid] = Neon_Rosa;
	    DestroyObject(VehicleNeon[vehicleid]);
	    DestroyObject(VehicleNeon2[vehicleid]);
	    VehicleNeon[vehicleid] = CreateObject(18651,0,0,0,0,0,0);
	    VehicleNeon2[vehicleid] = CreateObject(18651,0,0,0,0,0,0);
 		AttachObjectToVehicle(VehicleNeon[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	 	AttachObjectToVehicle(VehicleNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	}
	else if(cor == Neon_Amarelo)
	{
	    VeiculoNeonCor[vehicleid] = Neon_Amarelo;
	    DestroyObject(VehicleNeon[vehicleid]);
	    DestroyObject(VehicleNeon2[vehicleid]);
	    VehicleNeon[vehicleid] = CreateObject(18650,0,0,0,0,0,0);
	    VehicleNeon2[vehicleid] = CreateObject(18650,0,0,0,0,0,0);
 		AttachObjectToVehicle(VehicleNeon[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	 	AttachObjectToVehicle(VehicleNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	}
	return 1;
}

stock GetVehicleNeonColor(vehicleid){
	static SemNeon[10];
	if(VeiculoNeonCor[vehicleid] == Neon_Azul) format(SemNeon,10,"azul");
	else if(VeiculoNeonCor[vehicleid] == Neon_Vermelho) format(SemNeon,10,"vermelho");
	else if(VeiculoNeonCor[vehicleid] == Neon_Verde) format(SemNeon,10,"verde");
	else if(VeiculoNeonCor[vehicleid] == Neon_Branco) format(SemNeon,10,"branco");
	else if(VeiculoNeonCor[vehicleid] == Neon_Rosa) format(SemNeon,10,"rosa");
	else if(VeiculoNeonCor[vehicleid] == Neon_Amarelo) format(SemNeon,10,"amarelo");
	return SemNeon;
}

stock ResetVehicleNeon(vehicleid){
    DestroyObject(VehicleNeon[vehicleid]);
    DestroyObject(VehicleNeon2[vehicleid]);
	VeiculoNeonCor[vehicleid] = 0;
	return 1;
}