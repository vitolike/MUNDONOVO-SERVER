//		START

/*		drunk		*/
/*	        by: jyrno42	*/

/*
HELP USAGE:
native SetPlayerDrunk(playerid, type, time); // type - 1) normal - sobers up after UnSetPlayerDrunk(playerid) 2) timed - sobers up after time
native UnSetPlayerDrunk(playerid);
native ShowPlayerDrunkTime(playerid);
native HidePlayerDrunkTime(playerid)
native AddPlayerDrunkTime(playerid, time); // If Player isnt drunk yet he/she will be set drunk!
native GetPlayerDrunkTime(playerid); // return player drunktime

native SetPlayerHigh(playerid, type, time); // type - 1) normal - sobers up after UnSetPlayerHigh(playerid) 2) timed - sobers up after time
native UnSetPlayerHigh(playerid);
native AddPlayerHighTime(playerid, time); // If Player isnt high yet he/she will be set drunk! Adds time to players hightime.
native GetPlayerHighTime(playerid); // return player hightime

*/

//		FORWARDS

forward DrunkPlayer(playerid);
forward HighPlayer(playerid);
forward SoberUp(playerid, type);
forward DrunkTimeShow(playerid);

//		GLOBALS

new Drunk[MAX_PLAYERS];
new ShowDrunkDrawTimer[MAX_PLAYERS];

new Text: DrunkText[MAX_PLAYERS];
new Text: DrunkDraw[MAX_PLAYERS];
new Text: ShowDrunkDraw[MAX_PLAYERS];

new Text: HighText[MAX_PLAYERS];
new Text: High[MAX_PLAYERS];
new HighTimer[MAX_PLAYERS];

new DrunkType[MAX_PLAYERS];
new DrunkTime[MAX_PLAYERS];

new HighType[MAX_PLAYERS];
new HighTime[MAX_PLAYERS];

new hightextcolors[13][1] = {
	{0xAA3333AA},
	{0xFFFF00AA},
	{0xFF66FFAA},
	{0x0000BBAA},
	{0xFF9900AA},
	{0x33AA33AA},
	{0x800080AA},
	{0x9955DEEE},
	{0x33CCFFAA},
	{0xFF99AADD},
	{0x24FF0AB9},
	{0xFF0000AA},
	{0x4B00B0AA}
};

//		NATIVES

//		STOCKS

	//		DRUNK
	
stock SetPlayerDrunk(playerid, type, time)// 1 - normal, 2 - getting sober after [time] seconds
{
	DrunkText[playerid] = TextDrawCreate(500, 400, "You Are Drunk!");
	TextDrawShowForPlayer(playerid, DrunkText[playerid]);
	
	DrunkDraw[playerid] = TextDrawCreate(0, 0, "~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~ ");
	TextDrawUseBox(DrunkDraw[playerid], 1);
	TextDrawBoxColor(DrunkDraw[playerid], 0x00000022);
	TextDrawShowForPlayer(playerid, DrunkDraw[playerid]);
	
	DrunkType[playerid] = type;
	DrunkTime[playerid] = time;
	
	Drunk[playerid] = SetTimerEx("DrunkPlayer", 1000, 1, "i", playerid);
}

stock UnSetPlayerDrunk(playerid)
{
	KillTimer(Drunk[playerid]);
	if(GetPlayerVehicleID(playerid) == 0)
	{	
		ClearAnimations(playerid);
	}
	DrunkType[playerid] = 0;
	DrunkTime[playerid] = 0;	
	HidePlayerDrunkTime(playerid);
	TextDrawHideForPlayer(playerid, DrunkDraw[playerid]);	
	TextDrawSetString(DrunkText[playerid], "You sobered up!");
	SetTimerEx("SoberUp", 5000, 0, "ii", playerid, 1);
}

stock ShowPlayerDrunkTime(playerid)
{
	ShowDrunkDraw[playerid] = TextDrawCreate(500, 380, " ");
	TextDrawShowForPlayer(playerid, ShowDrunkDraw[playerid]);
	ShowDrunkDrawTimer[playerid] = SetTimerEx("DrunkTimeShow", 999, 1, "i", playerid);
}

stock HidePlayerDrunkTime(playerid)
{
	TextDrawHideForPlayer(playerid, ShowDrunkDraw[playerid]);
	KillTimer(ShowDrunkDrawTimer[playerid]);
}

stock AddPlayerDrunkTime(playerid, time)
{
	if(DrunkTime[playerid] == 0 && DrunkType[playerid] == 0)
	{
		SetPlayerDrunk(playerid, 2, 10);
		ShowPlayerDrunkTime(playerid);
	}
	DrunkTime[playerid] += (time);
}

stock GetPlayerDrunkTime(playerid)
{
	return DrunkTime[playerid];
}

	//		HIGH
stock SetPlayerHigh(playerid, type, time)// 1 - normal, 2 - getting sober after [time] seconds
{
	SetPlayerWeather(playerid, -66);
	HighText[playerid] = TextDrawCreate(500, 420, "You Are High!");
	TextDrawShowForPlayer(playerid, HighText[playerid]);
	
	HighType[playerid] = type;
	HighTime[playerid] = time*2;
	
	HighTimer[playerid] = SetTimerEx("HighPlayer", 500, 1, "i", playerid);	
}
stock UnSetPlayerHigh(playerid)
{
	SetPlayerWeather(playerid,3);
	TextDrawDestroy(High[playerid]);
	TextDrawSetString(HighText[playerid], "You sobered up!");
	SetTimerEx("SoberUp", 5000, 0, "ii", playerid, 2);

	HighType[playerid] = 0;
	HighTime[playerid] = 0;

	KillTimer(HighTimer[playerid]);
}

stock AddPlayerHighTime(playerid, time)
{
	if(HighTime[playerid] == 0 && HighType[playerid] == 0)
	{
		SetPlayerHigh(playerid, 2, 10);
	}
	HighTime[playerid] += (time);
}

stock GetPlayerHighTime(playerid)
{
	return HighTime[playerid];
}

//		PUBLICS

public DrunkPlayer(playerid)
{
	new playerVeh = GetPlayerVehicleID(playerid);
	
	new Float: vehZ, Float: pAng;
	
	new newZ, newpAng, Anim, arv;
	
	if(DrunkType[playerid] == 1)
	{	
		if(playerVeh != 0)
		{
			GetVehicleZAngle(playerVeh, vehZ);
		
			newZ = random(10) - 5;
	
			SetVehicleZAngle(playerVeh, (vehZ) + (newZ));
		}
		Anim = random(3);
		if(playerVeh == 0 && Anim == 1)
		{
			ApplyAnimation(playerid, "PED", "WALK_DRUNK", 4.0, 0, 1, 0, 0, 0);
		}
		GetPlayerFacingAngle(playerid, pAng);
	
		newpAng = random(10) - 5;
	
		SetPlayerFacingAngle(playerid, pAng+newpAng);
	}
	if(DrunkType[playerid] == 2)
	{
		DrunkTime[playerid]--;
		
		new v2rv;
		
		if(DrunkTime[playerid] < 30)
		{
			arv = 3;
			Anim = random(10);
			v2rv = 0x00000011;
		}
		if(DrunkTime[playerid] <= 60 && DrunkTime[playerid] > 30)
		{
			arv = 6;
			Anim = random(8);
			v2rv = 0x00000022;
		}		
		if(DrunkTime[playerid] > 60 && DrunkTime[playerid] <= 90)
		{
			arv = 12;
			Anim = random(6);	
			v2rv = 0x00000044;
		}
		if(DrunkTime[playerid] > 90 && DrunkTime[playerid] <= 120)
		{
			arv = 18;
			Anim = random(4);
			v2rv = 0x00000066;			
		}
		if(DrunkTime[playerid] > 120 && DrunkTime[playerid] <= 300)
		{
			arv = 21;
			Anim = random(3);
			v2rv = 0x00000077;
		}
		if(DrunkTime[playerid] > 300)
		{
			arv = 36;
			Anim = random(2);
			v2rv = 0x00000088;
		}
		
		TextDrawDestroy(DrunkDraw[playerid]);
		DrunkDraw[playerid] = TextDrawCreate(0, 0, "~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~  ~n~ ");
		TextDrawUseBox(DrunkDraw[playerid], 1);
		TextDrawBoxColor(DrunkDraw[playerid], v2rv);
		TextDrawShowForPlayer(playerid, DrunkDraw[playerid]);
		
		if(playerVeh != 0)
		{
			GetVehicleZAngle(playerVeh, vehZ);
		
			newZ = random(arv*2) - arv;
	
			SetVehicleZAngle(playerVeh, (vehZ) + (newZ));
		}
		if(playerVeh == 0 && Anim == 1)
		{
			ApplyAnimation(playerid, "PED", "WALK_DRUNK", 4.0, 0, 1, 0, 0, 0);
		}
		GetPlayerFacingAngle(playerid, pAng);
	
		newpAng = random(arv*2) - arv;
	
		SetPlayerFacingAngle(playerid, (pAng) + (newpAng) );		
		
		if(DrunkTime[playerid] <= 0)
		{
			UnSetPlayerDrunk(playerid);
		}
	}
	
	return 1;
}

public DrunkTimeShow(playerid)
{
	new promill[256];
	new Float: value;
	new Float: divisor = 100.0;
	value = floatdiv(DrunkTime[playerid], divisor);
	format(promill, sizeof(promill), "%.2f %% BAC", value);
	TextDrawSetString(ShowDrunkDraw[playerid], promill);
	return 1;
}

public HighPlayer(playerid)
{
	TextDrawDestroy(High[playerid]);
	new rx3 = random(600-50) + 50;
	new ry3 = random(440-50) + 50;
	High[playerid] = TextDrawCreate(rx3, ry3, ":)");
	TextDrawLetterSize(High[playerid], 5, 5);
	TextDrawColor(High[playerid], hightextcolors[random(14)][0]);	
	TextDrawShowForPlayer(playerid, High[playerid]);
	
	if(HighType[playerid] == 2)
	{
		HighTime[playerid]--;
		if(HighTime[playerid] <= 0)
		{
			UnSetPlayerHigh(playerid);
		}		
	}
	
	return 1;
}

public SoberUp(playerid,type)
{
	if(type == 1)
	{
		TextDrawHideForPlayer(playerid, DrunkText[playerid]);	
	}
	if(type == 2)
	{
		TextDrawHideForPlayer(playerid, HighText[playerid]);
	}
	return 1;
}

//		THE END