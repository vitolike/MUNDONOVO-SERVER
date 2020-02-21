//Include Criada Por Mateus_Matos

#define COR_VERDE          0x33AA33AA
forward AvisoAdmin(COLOR,const string[]);


new Admin[MAX_PLAYERS];
native MandarMensagemParaJogador(playerid, color, const message[]);
native MandarMensagemParaTodos(color, const message[]);

stock KcmD(param, cmdtext[])
{
    new string[128], pos, var;
    format(string, sizeof(string), "%s ", cmdtext);

    while((pos = strfind(string, " ", true)) != -1)
    {
        if(var == param) return string;
        var++;

        strdel(string, 0, pos + 1);
        if(strcmp(string, " ", true, pos) == 0) goto end;
    }

end:
    string[0] = '\0';
    return string;
}



stock ResetarPlayer(playerid,cmdtext[])
{
     new escolherid[256];
	 escolherid = KcmD(1, cmdtext);
	 if(!strlen(escolherid))
	  {
	    SendClientMessage(playerid,COR_VERDE,"Use /respawnplayer [ID]");
	    return 1;
      }
     SpawnPlayer(strval(escolherid));
     return 1;
}

stock PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)

{
    new Float:oldposx, Float:oldposy, Float:oldposz;
    new Float:tempposx, Float:tempposy, Float:tempposz;
    GetPlayerPos(playerid, oldposx, oldposy, oldposz);
    tempposx = (oldposx -x);
    tempposy = (oldposy -y);
    tempposz = (oldposz -z);
    if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) {
        return 1;
    }
    return 0;
}

public AvisoAdmin(COLOR,const string[])
{
    for(new i = 0; i < MAX_PLAYERS; i++) {
        if(IsPlayerConnected(i)) {
            if (Admin[i]) {
                SendClientMessage(i, COLOR, string);
                printf("%s", string);
            }
        }
    }
    return 1;
}

