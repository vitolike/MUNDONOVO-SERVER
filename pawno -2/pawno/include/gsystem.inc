#include <dof2>

#define dcmd(%1,%2,%3) if (!strcmp((%3)[1], #%1, true, (%2)) && ((((%3)[(%2) + 1] == '\0') && (dcmd_%1(playerid, ""))) || (((%3)[(%2) + 1] == ' ') && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1

/*cores*/
#define amarelo 0xFFFF00AA
#define verde 0x33FF33AA
#define vermelho 0xFF0000AA
#define vermelhoescuro 0xAA3333AA
#define branco 0xFFFFFFAA
#define rosa 0xCCFF00FFAA
#define azul 0x057ABDAA
#define cinza 0xC0C0C0AA
#define yellow 0xFFFF00AA
#define laranja 0xFFA500AA

stock HexToInt(string[])
{
    new i = 0;
    new cur = 1;
    new res = 0;
    for (i = strlen(string); i > 0; i--)
    {
        if (string[i-1] < 58) res = res + cur*(string[i-1] - 48); else res = res + cur*(string[i-1] - 65 + 10);
        cur = cur*16;
    }
    return res;
}

stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
    {
        if(strsrc[i] == delimiter || i == strlen(strsrc))
        {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

stock GangF(gang[])
{
	new file[128];
	format(file,128,"gangs/%s",gang);
	return file;
}

stock FormatGang(gang)
{
	new file[128];
	format(file,128,"gangs/%d.gang",gang);
	return file;
}

stock FormatTerri(gang)
{
	new file[128];
	format(file,128,"gangs/%d.terri",gang);
	return file;
}

stock IsPlayerInArea(playerid, Float:minx, Float:maxx, Float:miny, Float:maxy)
{
new Float:x, Float:y, Float:z;
GetPlayerPos(playerid, x, y, z);
if (x > minx && x < maxx && y > miny && y < maxy) return 1;
return 0;
}