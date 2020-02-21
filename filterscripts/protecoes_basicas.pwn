#include a_samp

/*
	Créditos: NicK - Criador do FilterScript
    --> Fórum SA-MP
    # Brasil Mega Trucker #
    
    -- Change LOG:
    07/11 - Lançamento Inicial
    08/11 - Adicionado: Anti-Armas, Anti Teleport por Mapa;
    16/11 - Adicionado Anti Nicks bugaveis. Opcional o uso. Necessário passar "HOST" para true
*/

new bool:ANTI_ARMAS = false; /*
		Ativamento do anti-armas, é necessário que você defina as armas
		Armas definidas por padrão: 35, 36, 38
		http://wiki.sa-mp.com/wiki/Weapons
		
		FALSE = DESATIVADO
		TRUE = ATIVADO
*/

new Nomes[][] = {"con", "aux"}; //Anti Nicks, Defina os nicks indevíduos aqui
new bool:HOST = false; /* 	false = LINUX
	  						true = WINDOWS */
public OnFilterScriptInit() {
	return 1;
}
public OnFilterScriptExit() {
	return 1;
}

/*
	Anti-Bot: Funcional em 95-100%
	Um pequeno estudo feito á muito tempo atrás.
	--
*/
public OnPlayerConnect(playerid) {
	if(IsPlayerNPC(playerid)) return 1; // Caso use NPCs.
	new SAMP[50];
	GetPlayerVersion(playerid, SAMP, sizeof(SAMP));
	if(HOST == true) { //Se usar Windows né rs... Linux não tem estes problemas :D
		new Nome[24];
		GetPlayerName(playerid, Nome, sizeof(Nome));
		for(new i; i < sizeof(Nomes); i++) {
			if(!strcmp(Nome, Nomes[i], true)) return BanEx(playerid, "Nick Indevíduo!");
		}
	}
	if(!strcmp(SAMP, "unknown", false)) return BanEx(playerid, "BOT");
	return 1;
}

/*
	Anti Fake Kill:
		Funcional contra anti-flooders de Kill,
  		ou armas que o player pode bem não estar.
  		Opcional: Uma parte que você pode tirar ou não, caso use sistemas de equipe. (Team)
    			 Funcionamento em torno de 80-90%
*/
public OnPlayerDeath(playerid, killerid, reason) {
	if(killerid == INVALID_PLAYER_ID) return 1;
	if(GetPVarInt(playerid, "Morte") > gettime()) return BanEx(playerid, "Fake Kill"); // Caso o valor armazenado seja ainda maior que o gettime() (Tempo Atual)
	if(playerid == killerid) return BanEx(playerid, "Fake Kill"); // Isso ocorre quando é usando o 'random' em alguns cheaters
//	if(!IsPlayerStreamedIn(killerid, playerid)) return Kick(playerid); // Caso falhe.
	if(GetPlayerTeam(playerid) != NO_TEAM)	// Caso você use sistema de Equipes
        if(GetPlayerTeam(playerid) == GetPlayerTeam(killerid))
            return BanEx(playerid, "Fake Kill");
	SetPVarInt(playerid, "Morte", gettime() + 2);
	return 1;
}

public OnPlayerUpdate(playerid) {
	SetPVarInt(playerid, "ESC", gettime()); // Apenas para checar se está de esc ou não. Lembrando que quando da esc, o OnPlayerUpdate não é mais chamado.
	/*
		Anti Car Spam: Funcional em 90%
		Funcionando em OnPlayerUpdate, é checado mais rápido se trocou de veículo.
		Em outros locais, pode não ser tão rápido, pois como por exemplo, não é feita a troca de status do player (OnPlayerStateChange)
	*/
	if(GetPlayerVehicleID(playerid) != 0) {
		if(GetPlayerVehicleID(playerid) != GetPVarInt(playerid, "Veiculo_Anterior")) {
			if(GetPVarInt(playerid, "Troca_Veiculo") > gettime()) return BanEx(playerid, "Car Spam");
			SetPVarInt(playerid, "Veiculo_Anterior", GetPlayerVehicleID(playerid));
			SetPVarInt(playerid, "Troca_Veiculo", gettime() + 2);
		}
	}
	/*
	    Anti Crash:
	    Não sei realmente o funcionamento, porém, uso, e não sofro com crashs.
	    Então digo que é funcional em torno de 90%
	    Créditos: http://forum.sa-mp.com/showpost.php?p=2610650&postcount=1
	*/
    if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new Float:vec[3];
        GetPlayerCameraFrontVector(playerid, vec[0], vec[1], vec[2]);
        new bool:possible_crasher = false;
        for (new i = 0; !possible_crasher && i < sizeof(vec); i++)
            if (floatabs(vec[i]) > 10.0)
                possible_crasher = true;

        if (possible_crasher)
            return 0; 
    }
    /*
		Anti Armas:
	    Necessário alterar "ANTI_ARMAS" para 'true' caso queira usa-lo.
	*/
	if(ANTI_ARMAS == true) {
		switch(GetPlayerWeapon(playerid)) {
			case 35, 36, 38: return Kick(playerid); // Kicka o jogador caso ele esteja com uma das armas.
		}
	}
	/*
	    Anti Teleport ao Mapa
	    Funcionabilidade: 100%
	    Não remova a linha da checagem de ESC mais acima.
	*/
	if(GetPVarInt(playerid, "ClickMapa") > gettime())
	    if(!IsPlayerInRangeOfPoint(playerid, 10.0, GetPVarFloat(playerid, "PX"), GetPVarFloat(playerid, "PY"), GetPVarFloat(playerid, "PZ"))) return Kick(playerid);
	new Float:Pos[3]; GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	SetPVarFloat(playerid, "PX", Pos[0]); SetPVarFloat(playerid, "PY", Pos[1]); SetPVarFloat(playerid, "PZ", Pos[2]);
	return 1;
}
/*
	Anti Teleport ao Mapa
	Continuação
*/
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	SetPVarInt(playerid, "ClickMapa", gettime() + 5);
	return 1;
}
/*
	Anti Crash:
	Este é outro anti-crash, que protege contra mods indevíduos em veículos.
	Funcionabilidade em 95-100%.
	Não consegui achar os créditos de quem fez este anti-crash.
*/

new legalmods[49][22] = {
        {400, 1024,1021,1020,1019,1018,1013,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {401, 1145,1144,1143,1142,1020,1019,1017,1013,1007,1006,1005,1004,1003,1001,0000,0000,0000,0000},
        {404, 1021,1020,1019,1017,1016,1013,1007,1002,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {405, 1023,1021,1020,1019,1018,1014,1001,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {410, 1024,1023,1021,1020,1019,1017,1013,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
        {415, 1023,1019,1018,1017,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {418, 1021,1020,1016,1006,1002,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {420, 1021,1019,1005,1004,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {421, 1023,1021,1020,1019,1018,1016,1014,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {422, 1021,1020,1019,1017,1013,1007,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {426, 1021,1019,1006,1005,1004,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {436, 1022,1021,1020,1019,1017,1013,1007,1006,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
        {439, 1145,1144,1143,1142,1023,1017,1013,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
        {477, 1021,1020,1019,1018,1017,1007,1006,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {478, 1024,1022,1021,1020,1013,1012,1005,1004,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {489, 1024,1020,1019,1018,1016,1013,1006,1005,1004,1002,1000,0000,0000,0000,0000,0000,0000,0000},
        {491, 1145,1144,1143,1142,1023,1021,1020,1019,1018,1017,1014,1007,1003,0000,0000,0000,0000,0000},
        {492, 1016,1006,1005,1004,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {496, 1143,1142,1023,1020,1019,1017,1011,1007,1006,1003,1002,1001,0000,0000,0000,0000,0000,0000},
        {500, 1024,1021,1020,1019,1013,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {516, 1021,1020,1019,1018,1017,1016,1015,1007,1004,1002,1000,0000,0000,0000,0000,0000,0000,0000},
        {517, 1145,1144,1143,1142,1023,1020,1019,1018,1017,1016,1007,1003,1002,0000,0000,0000,0000,0000},
        {518, 1145,1144,1143,1142,1023,1020,1018,1017,1013,1007,1006,1005,1003,1001,0000,0000,0000,0000},
        {527, 1021,1020,1018,1017,1015,1014,1007,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {529, 1023,1020,1019,1018,1017,1012,1011,1007,1006,1003,1001,0000,0000,0000,0000,0000,0000,0000},
        {534, 1185,1180,1179,1178,1127,1126,1125,1124,1123,1122,1106,1101,1100,0000,0000,0000,0000,0000},
        {535, 1121,1120,1119,1118,1117,1116,1115,1114,1113,1110,1109,0000,0000,0000,0000,0000,0000,0000},
        {536, 1184,1183,1182,1181,1128,1108,1107,1105,1104,1103,0000,0000,0000,0000,0000,0000,0000,0000},
        {540, 1145,1144,1143,1142,1024,1023,1020,1019,1018,1017,1007,1006,1004,1001,0000,0000,0000,0000},
        {542, 1145,1144,1021,1020,1019,1018,1015,1014,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {546, 1145,1144,1143,1142,1024,1023,1019,1018,1017,1007,1006,1004,1002,1001,0000,0000,0000,0000},
        {547, 1143,1142,1021,1020,1019,1018,1016,1003,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {549, 1145,1144,1143,1142,1023,1020,1019,1018,1017,1012,1011,1007,1003,1001,0000,0000,0000,0000},
        {550, 1145,1144,1143,1142,1023,1020,1019,1018,1006,1005,1004,1003,1001,0000,0000,0000,0000,0000},
        {551, 1023,1021,1020,1019,1018,1016,1006,1005,1003,1002,0000,0000,0000,0000,0000,0000,0000,0000},
        {558, 1168,1167,1166,1165,1164,1163,1095,1094,1093,1092,1091,1090,1089,1088,0000,0000,0000,0000},
        {559, 1173,1162,1161,1160,1159,1158,1072,1071,1070,1069,1068,1067,1066,1065,0000,0000,0000,0000},
        {560, 1170,1169,1141,1140,1139,1138,1033,1032,1031,1030,1029,1028,1027,1026,0000,0000,0000,0000},
        {561, 1157,1156,1155,1154,1064,1063,1062,1061,1060,1059,1058,1057,1056,1055,1031,1030,1027,1026},
        {562, 1172,1171,1149,1148,1147,1146,1041,1040,1039,1038,1037,1036,1035,1034,0000,0000,0000,0000},
        {565, 1153,1152,1151,1150,1054,1053,1052,1051,1050,1049,1048,1047,1046,1045,0000,0000,0000,0000},
        {567, 1189,1188,1187,1186,1133,1132,1131,1130,1129,1102,0000,0000,0000,0000,0000,0000,0000,0000},
        {575, 1177,1176,1175,1174,1099,1044,1043,1042,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {576, 1193,1192,1191,1190,1137,1136,1135,1134,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {580, 1023,1020,1018,1017,1007,1006,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {585, 1145,1144,1143,1142,1020,1019,1017,1013,1007,1006,1005,1004,1003,1001,1018,1023,0000,0000},
        {589, 1145,1144,1024,1020,1018,1017,1016,1013,1007,1006,1005,1004,1000,0000,0000,0000,0000,0000},
        {600, 1022,1020,1018,1017,1013,1007,1006,1005,1004,0000,0000,0000,0000,0000,0000,0000,0000,0000},
        {603, 1145,1144,1143,1142,1024,1023,1020,1019,1018,1017,1007,1006,1001,0000,0000,0000,0000,0000}
};


public OnVehicleMod(playerid, vehicleid, componentid) {
    new vehicleide = GetVehicleModel(vehicleid);
    new modok = islegalcarmod(vehicleide, componentid);
    if (!modok)
    {
        BanEx(playerid, "Crash");
        return 0;
    }
	return 1;
}
iswheelmodel(modelid) {
    new wheelmodels[17] = {1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1096,1097,1098};
    for(new i; i < sizeof(wheelmodels); i++)
    {
        if (modelid == wheelmodels[i])
            return true;
    }
    return false;
}

IllegalCarNitroIde(carmodel) {
    new illegalvehs[29] = { 581, 523, 462, 521, 463, 522, 461, 448, 468, 586, 509, 481, 510, 472, 473, 493, 595, 484, 430, 453, 452, 446, 454, 590, 569, 537, 538, 570, 449 };
    for(new i; i < sizeof(illegalvehs); i++) {
        if (carmodel == illegalvehs[i])
            return true;
    }
    return false;
}
stock illegal_nos_vehicle(PlayerID) {
    new carid = GetPlayerVehicleID(PlayerID);
    new playercarmodel = GetVehicleModel(carid);
    return IllegalCarNitroIde(playercarmodel);
}

stock islegalcarmod(vehicleide, componentid) {
    new modok = false;
    if ( (iswheelmodel(componentid)) || (componentid == 1086) || (componentid == 1087) || ((componentid >= 1008) && (componentid <= 1010))) {
        new nosblocker = IllegalCarNitroIde(vehicleide);
        if (!nosblocker)
            modok = true;
    } else {
        for(new I; I < sizeof(legalmods); I++) {
            if (legalmods[I][0] == vehicleide) {
                for(new J = 1; J < 22; J++) {
                    if (legalmods[I][J] == componentid)
                        modok = true;
                }
            }
        }
    }
    return modok;
}

/*
	Anti Floder de Pintura de veículo's próximos.
	Alguns servidores podem até sofrer certo lag com este atack de cheaters k
	Funcionabilidade em 100%
*/
public OnVehicleRespray(playerid, vehicleid, color1, color2) {
	if(GetPVarInt(playerid, "pintura_Recente") > gettime()) return Kick(playerid);
	SetPVarInt(playerid, "pintura_Recente", gettime() + 1);
	return 1;
}
/*
	Anti Floder de Spawns
	Funcionabilidade 95-100%
*/
public OnPlayerRequestSpawn(playerid) {
	if(GetPVarInt(playerid, "spawn_Tempo") > gettime()) return 0; // Retorno 0 (nulo) não irá exibir a mensagem ou spawnar diversas vezes. Você pode alterar por "Kick(playerid)"
	SetPVarInt(playerid, "spawn_Tempo", gettime() + 2);
	return 1;
}



stock KickEx(playerid, motivo[]) {
	new Msg[144]; format(Msg, sizeof(Msg), "{ff0000}Kickado do servidor, motivo: {ffffff}%s{ff0000}.", motivo);
	SendClientMessage(playerid, -1, Msg);
	SendClientMessage(playerid, -1, "{ff0000}Sistema de proteções by NicK.");
	SetTimerEx("Kickar", 150, false, "d", playerid);
	return 1;
}
forward Kickar(playerid); public Kickar(playerid) return Kick(playerid);

/*
	Atualizações podem vir mais a frente.
	Bugs, por favor informe: http://forum.sa-mp.com/member.php?u=171517
*/
