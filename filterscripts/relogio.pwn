#include <a_samp>
 
static i_ServerSeconds;
static i_ServerMinutes;
static i_ServerHours;
static i_ServerDays;
static i_ServerMonths;
static i_ServerYears;
 
new Text:txtTimeDisp;
new Text:txtDateDisp;
 
forward ProcessGameTime();
public ProcessGameTime()
{
        new string[128];
        gettime(i_ServerHours, i_ServerMinutes, i_ServerSeconds);
        getdate(i_ServerYears, i_ServerMonths, i_ServerDays);
        format(string, sizeof string, "%02d:%02d:%02d", i_ServerHours, i_ServerMinutes, i_ServerSeconds);
        TextDrawSetString(txtTimeDisp, string);
        format(string, sizeof string, "%02d/%02d/%04d", i_ServerDays, i_ServerMonths, i_ServerYears);
        TextDrawSetString(txtDateDisp, string);
        SetWorldTime(i_ServerHours);
        for(new i = 0; i < MAX_PLAYERS; i++)SetPlayerTime(i, i_ServerHours, i_ServerMinutes);
}
 
public OnFilterScriptInit()
{
        txtTimeDisp = TextDrawCreate(632.0,25.0,"--:--:--");
        TextDrawUseBox(txtTimeDisp, 0);
        TextDrawFont(txtTimeDisp, 3);
        TextDrawSetShadow(txtTimeDisp,0);
        TextDrawSetOutline(txtTimeDisp,2);
        TextDrawBackgroundColor(txtTimeDisp,0x000000FF);
        TextDrawColor(txtTimeDisp,0xFFFFFFFF);
        TextDrawAlignment(txtTimeDisp,3);
        TextDrawLetterSize(txtTimeDisp,0.5,1.5);
 
        txtDateDisp = TextDrawCreate(620.0,5.0,"00/00/0000");
        TextDrawUseBox(txtDateDisp, 0);
        TextDrawFont(txtDateDisp, 3);
        TextDrawSetShadow(txtDateDisp,0);
        TextDrawSetOutline(txtDateDisp,2);
        TextDrawBackgroundColor(txtDateDisp,0x000000FF);
        TextDrawColor(txtDateDisp,0xFFFFFFFF);
        TextDrawAlignment(txtDateDisp,3);
        TextDrawLetterSize(txtDateDisp,0.5,1.5);
 
        ProcessGameTime();
        SetTimer("ProcessGameTime", 1000, 1);
        return 1;
}
 
public OnFilterScriptExit()
{
        TextDrawHideForAll(txtTimeDisp);
        TextDrawDestroy(txtTimeDisp);
        TextDrawHideForAll(txtDateDisp);
        TextDrawDestroy(txtDateDisp);
        return 1;
}
 
public OnPlayerSpawn(playerid)
{
        TextDrawShowForPlayer(playerid,txtTimeDisp);
        TextDrawShowForPlayer(playerid,txtDateDisp);
        return 1;
}
 
public OnPlayerDeath(playerid, killerid, reason)
{
        TextDrawHideForPlayer(playerid,txtTimeDisp);
        TextDrawHideForPlayer(playerid,txtDateDisp);
        return 1;
}