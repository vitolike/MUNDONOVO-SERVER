#include <a_samp>

#define HOUSE_RENT "100"
#define HOUSE_COST "10000"

#define HOUSE_INTERIOR_ID ix,iy,iz,ii
#define HOUSE_INTERIOR_1 223.043991,1289.259888,1082.199951,1
#define HOUSE_INTERIOR_2 295.138977,1474.469971,1080.519897,15
#define HOUSE_INTERIOR_3 328.493988,1480.589966,1084.449951,15
#define HOUSE_INTERIOR_4 2262.83,-1137.71,1050.63,10
#define HOUSE_INTERIOR_5 2251.85,-1138.16,1050.63,9
#define HOUSE_INTERIOR_6 225.756989,1240.000000,1082.149902,2
#define HOUSE_INTERIOR_7 2451.77, -1699.80,1013.51,2
#define HOUSE_INTERIOR_8 385.803986,1471.769897,1080.209961,15
#define HOUSE_INTERIOR_9 2260.76,-1210.45,1049.02,10
#define HOUSE_INTERIOR_10 235.508994,1189.169897,1080.339966,3
#define HOUSE_INTERIOR_11 225.630997,1022.479980,1084.069946,7
#define HOUSE_INTERIOR_12 2807.63,-1170.15,1025.57,8
#define HOUSE_INTERIOR_13 -2158.72,641.29,1052.38,1

forward OnGameModeInit_script();
forward OnPlayerDisconnect_script(playerid,reason);
forward OnPlayerSpawn_script(playerid);
forward OnPlayerPickUpPickup_script(playerid,pickupid);
forward OnPlayerSelectedMenuRow_script(playerid,row);
forward OnPlayerExitedMenu_script(playerid);
forward OnPlayerCommandText_script(playerid,cmdtext[]);

#pragma unused AddStaticHouse

new string1[256];
new string2[256];
new string3[256];

stock Exist(file[])
{
	format(string1,255,"%s.snl",file);
	if (fexist(string1))
	{
		return 1;
	}
	else
	{
	    return 0;
	}
}


stock Save(file[], data[], value[])
{
	format(string1,255,"%s.snl",file);
	if (fexist(string1))
	{
		new File:handler;
		handler = fopen(string1,io_read);
		fread(handler,string2);
		fclose(handler);
		format(string3,255,"%s=",data);
		if (strfind(string2,string3) != -1)
		{
	        new p1 = strlen(string3);
	        new p2 = strfind(string2,string3)+p1;
	        new p3 = strfind(string2,";",true,p2);
	        strdel(string2,p2,p3);
	        p2 = strfind(string2,string3)+p1;
	        strins(string2,value,p2);
			handler = fopen(string1,io_write);
			fwrite(handler,string2);
			fclose(handler);
	    }
	    else
	    {
			handler = fopen(string1,io_append);
			format(string2,255,"%s=%s;",data,value);
			fwrite(handler,string2);
			fclose(handler);
		}
	}
	else
	{
		format(string1,255,"%s.snl",file);
		new File:handler = fopen(string1,io_write);
		fclose(handler);
		handler = fopen(string1,io_read);
		fread(handler,string2);
		fclose(handler);
		format(string3,255,"%s=",data);
		if (strfind(string2,string3) != -1)
		{
	        new p1 = strlen(string3);
	        new p2 = strfind(string2,string3)+p1;
	        new p3 = strfind(string2,";",true,p2);
	        strdel(string2,p2,p3);
	        p2 = strfind(string2,string3)+p1;
	        strins(string2,value,p2);
			handler = fopen(string1,io_append);
			fwrite(handler,string2);
			fclose(handler);
	    }
	    else
	    {
			handler = fopen(string1,io_append);
			format(string2,255,"%s=%s;",data,value);
			fwrite(handler,string2);
			fclose(handler);
		}

	}

}

stock Load(file[], data[])
{

	format(string1,255,"%s.snl",file);
	if (fexist(string1))
	{
	new File:handler = fopen(string1,io_read);
	fread(handler,string2);
	new p1 = strfind(string2,data);
	new p2 = strfind(string2,"=",true,p1)+1;
	new p3 = strfind(string2,";",true,p2);
	strdel(string2,p3,strlen(string2));
	strdel(string2,0,p2);
	}
	return string2;
}
stock exist(playerid)
{
	new file[256];
	GetPlayerName(playerid,file,255);
	format(string1,255,"%s.snl",file);
	if (fexist(string1))
	{
		return 1;
	}
	else
	{
	    return 0;
	}
}


stock save(playerid, data[], value[])
{
	new file[256];
	GetPlayerName(playerid,file,255);
	format(string1,255,"%s.snl",file);
	if (fexist(string1))
	{
		new File:handler;
		handler = fopen(string1,io_read);
		fread(handler,string2);
		fclose(handler);
		format(string3,255,"%s=",data);
		if (strfind(string2,string3) != -1)
		{
	        new p1 = strlen(string3);
	        new p2 = strfind(string2,string3)+p1;
	        new p3 = strfind(string2,";",true,p2);
	        strdel(string2,p2,p3);
	        p2 = strfind(string2,string3)+p1;
	        strins(string2,value,p2);
			handler = fopen(string1,io_write);
			fwrite(handler,string2);
			fclose(handler);
	    }
	    else
	    {
			handler = fopen(string1,io_append);
			format(string2,255,"%s=%s;",data,value);
			fwrite(handler,string2);
			fclose(handler);
		}
	}
	else
	{
		GetPlayerName(playerid,file,255);
		format(string1,255,"%s.snl",file);
		new File:handler = fopen(string1,io_write);
		fclose(handler);
		handler = fopen(string1,io_read);
		fread(handler,string2);
		fclose(handler);
		format(string3,255,"%s=",data);
		if (strfind(string2,string3) != -1)
		{
	        new p1 = strlen(string3);
	        new p2 = strfind(string2,string3)+p1;
	        new p3 = strfind(string2,";",true,p2);
	        strdel(string2,p2,p3);
	        p2 = strfind(string2,string3)+p1;
	        strins(string2,value,p2);
			handler = fopen(string1,io_append);
			fwrite(handler,string2);
			fclose(handler);
	    }
	    else
	    {
			handler = fopen(string1,io_append);
			format(string2,255,"%s=%s;",data,value);
			fwrite(handler,string2);
			fclose(handler);
		}

	}

}

stock load(playerid, data[])
{
	new file[256];
	GetPlayerName(playerid,file,255);
	format(string1,255,"%s.snl",file);
	if (fexist(string1))
	{
	new File:handler = fopen(string1,io_read);
	fread(handler,string2);
	new p1 = strfind(string2,data);
	new p2 = strfind(string2,"=",true,p1)+1;
	new p3 = strfind(string2,";",true,p2);
	strdel(string2,p3,strlen(string2));
	strdel(string2,0,p2);
	}
	return string2;
}

stock existx(playerid,x[])
{
	new file[256];
	GetPlayerName(playerid,file,255);
	format(string1,255,"%s.%s.snl",file,x);
	if (fexist(string1))
	{
		return 1;
	}
	else
	{
	    return 0;
	}
}


new IsHousePickup[200] = -1;
new Float:GetHouseX[200];
new Float:GetHouseY[200];
new Float:GetHouseZ[200];
new Float:GetHouseIX[200];
new Float:GetHouseIY[200];
new Float:GetHouseIZ[200];
new GetHouseII[200];
new GetPlayerHouse[200] = -1;

/*
 House Menu

 - Enter
 - Info
 - Rent
 - Unrent
 - Buy
 - Sell

*/

AddStaticHouse(Float:x,Float:y,Float:z,Float:ix,Float:iy,Float:iz,ii)
{
	AddStaticHouseEx(Float:x,Float:y,Float:z,Float:ix,Float:iy,Float:iz,ii);
}

AddStaticHouseEx(Float:x,Float:y,Float:z,Float:ix,Float:iy,Float:iz,ii)
{
	new pickup = CreatePickup(1273,2,x,y,z);
	IsHousePickup[pickup] = 1;
	GetHouseX[pickup] = x;
	GetHouseY[pickup] = y;
	GetHouseZ[pickup] = z;
	GetHouseIX[pickup] = ix;
	GetHouseIY[pickup] = iy;
	GetHouseIZ[pickup] = iz;
	GetHouseII[pickup] = ii;
	new file[256];
	format(file,255,"House%d.kihc",pickup);
	Save(file,"Owner","None");
	Save(file,"Rent",HOUSE_RENT);
	Save(file,"Cost",HOUSE_COST);
}
new Menu:HM;
new Menu:HE;
public OnGameModeInit()
{
/*
 House Menu

 - Enter - To Exit The house press ENTER
 - Info - Owner, Rent, Cost
 - Rent - Congrats for your new house.
 - Unrent - You have unrented your house.
 - Buy - Congrats for your new house.
 - Sell - You have sold your house successfully

*/

	HM = CreateMenu("House",1,100,200,75,0);
	AddMenuItem(HM,0,"Enter");
	AddMenuItem(HM,0,"Info");
	AddMenuItem(HM,0,"Rent");
	AddMenuItem(HM,0,"UnRent");
	AddMenuItem(HM,0,"Buy");
	AddMenuItem(HM,0,"Sell");

	HE = CreateMenu(" ",1,0,0,0,0);
	CallLocalFunction("OnGameModeInit_script","");
	print(" ----- ----- ----- ----- ----- ----- ");
	print(" KIHC has been successfully loaded.");
	print(" ----- ----- ----- ----- ----- ----- ");
}
#define OnGameModeInit OnGameModeInit_script
public OnPlayerPickUpPickup(playerid,pickupid)
{
	if(IsHousePickup[pickupid] != -1)
	{
	    ShowMenuForPlayer(HM,playerid);
		TogglePlayerControllable(playerid,0);
		GetPlayerHouse[playerid] = pickupid;
	}
	CallLocalFunction("OnPlayerPickUpPickup_script","ii",playerid,pickupid);
}

public OnPlayerCommandText(playerid,cmdtext[])
{
	if(strcmp("/build",cmdtext,true)==0)
	{
	    if(IsPlayerAdmin(playerid))
	    {
		    new Float:x,Float:y,Float:z;
			GetPlayerPos(playerid,x,y,z);
			CreateObject(1273,x,y,z,0,0,0);
			new string[256];
			format(string,255,"\r\nAddStaticHouse(%f,%f,%f,HOUSE_INTERIOR_%d);// place me in OnGameModeInit",x,y,z,1+random(12));
			new File:handler = fopen("Houses_List.txt",io_append);
			fwrite(handler,string);
			fclose(handler);
			return 1;
		}
	}
	CallLocalFunction("OnPlayerCommandText_script","is",playerid,cmdtext);
	return 0;
}
#define OnPlayerCommandText OnPlayerCommandText_script

#define OnPlayerPickUpPickup OnPlayerPickUpPickup_script
public OnPlayerDisconnect(playerid,reason)
{
	GetPlayerHouse[playerid] = -1;
	CallLocalFunction("OnPlayerDisconnect_script","i",playerid);
}
#define OnPlayerDisconnect OnPlayerDisconnect_script

public OnPlayerSelectedMenuRow(playerid,row)
{
	new Menu:menuid = GetPlayerMenu(playerid);
	if(menuid == HE)
	{
	    ShowMenuForPlayer(menuid,playerid);
	}
	if(menuid == HM)
	{
		new house[256];
		format(house,255,"House%d.kihc",GetPlayerHouse[playerid]);
		if(row == 0)
		{
		    if(strcmp(Load(house,"Owner"),"None",true)==0)
		    {
		        SetPlayerPos(playerid,GetHouseIX[GetPlayerHouse[playerid]],GetHouseIY[GetPlayerHouse[playerid]],GetHouseIZ[GetPlayerHouse[playerid]]);
		        SetPlayerInterior(playerid,GetHouseII[GetPlayerHouse[playerid]]);
		        ShowMenuForPlayer(HE,playerid);
		        SendClientMessage(playerid,0xFFFFFFAA,"House: Press ENTER to exit the house.");
		    }
			else if(strcmp(load(playerid,"House"),house)==0)
			{
		        SetPlayerPos(playerid,GetHouseIX[GetPlayerHouse[playerid]],GetHouseIY[GetPlayerHouse[playerid]],GetHouseIZ[GetPlayerHouse[playerid]]);
		        SetPlayerInterior(playerid,GetHouseII[GetPlayerHouse[playerid]]);
		        ShowMenuForPlayer(HE,playerid);
		        SendClientMessage(playerid,0xFFFFFFAA,"House: Press ENTER to exit the house.");
			}
			else
			{
			    SendClientMessage(playerid,0xFFFFFFAA,"House: You dont have the keys to enter the house.");
			}
			TogglePlayerControllable(playerid,1);
		}
		if(row ==  1)
		{
		    new string[256];
			SendClientMessage(playerid,0xFFFFFFAA," -----[[ House ]] ----- ");
			format(string,255,"   Owner: %s",Load(house,"Owner"));
			SendClientMessage(playerid,0xFFFFFFAA,string);
			format(string,255,"   Rent: %s",Load(house,"Rent"));
			SendClientMessage(playerid,0xFFFFFFAA,string);
			format(string,255,"   Cost: %s",Load(house,"Cost"));
			SendClientMessage(playerid,0xFFFFFFAA,string);
			SendClientMessage(playerid,0xFFFFFFAA," --------------------- ");
			TogglePlayerControllable(playerid,1);
		}
		if(row == 2)
		{
			if(strcmp(Load(house,"Owner"),"None",true)!=0)
			{
			    if(strval(Load(house,"Rent")) <= GetPlayerMoney(playerid))
			    {
					save(playerid,"House",house);
					SendClientMessage(playerid,0xFFFFFFAA,"House: Congrats for your new house.");

					new string[256];
					format(string,255,"%f",GetHouseIX[GetPlayerHouse[playerid]]);
					save(playerid,"X",string);
					format(string,255,"%f",GetHouseIY[GetPlayerHouse[playerid]]);
					save(playerid,"Y",string);
					format(string,255,"%f",GetHouseIZ[GetPlayerHouse[playerid]]);
					save(playerid,"Z",string);
					format(string,255,"%d",GetHouseII[GetPlayerHouse[playerid]]);
					save(playerid,"I",string);

					GivePlayerMoney(playerid,-strval(Load(house,"Rent")));
			    }
			    else
			    {
			        SendClientMessage(playerid,0xFFFFFFAA,"House: You dont have enough money.");
			    }
			}
			else
			{
			    SendClientMessage(playerid,0xFFFFFFAA,"House: This house has no owner.");
			}
			TogglePlayerControllable(playerid,1);
		}
		if(row == 3)
		{
			if(strcmp(load(playerid,"House"),house,true)==0)
			{
				save(playerid,"House","0");
				save(playerid,"X","0");
				save(playerid,"Y","0");
				save(playerid,"Z","0");
				save(playerid,"I","0");
			    SendClientMessage(playerid,0xFFFFFFAA,"House: You have successfully unrented this house.");
			}
			else
			{
			    SendClientMessage(playerid,0xFFFFFFAA,"House: You dont rent this house.");
			}
			TogglePlayerControllable(playerid,1);
		}
		if(row == 4)
		{
			if(strcmp(Load(house,"Owner"),"None",true)==0)
			{
			    if(strval(Load(house,"Cost")) <= GetPlayerMoney(playerid))
			    {
					new name[256];
					GetPlayerName(playerid,name,255);
			        Save(house,"Owner",name);
					save(playerid,"House",house);

					new string[256];
					format(string,255,"%f",GetHouseIX[GetPlayerHouse[playerid]]);
					save(playerid,"X",string);
					format(string,255,"%f",GetHouseIY[GetPlayerHouse[playerid]]);
					save(playerid,"Y",string);
					format(string,255,"%f",GetHouseIZ[GetPlayerHouse[playerid]]);
					save(playerid,"Z",string);
					format(string,255,"%d",GetHouseII[GetPlayerHouse[playerid]]);
					save(playerid,"I",string);
					
					SendClientMessage(playerid,0xFFFFFFAA,"House: Congrats for your new house.");
					GivePlayerMoney(playerid,-strval(Load(house,"Cost")));
			    }
			    else
			    {
			        SendClientMessage(playerid,0xFFFFFFAA,"House: You dont have enough money.");
			    }
			}
			else
			{
			    SendClientMessage(playerid,0xFFFFFFAA,"House: This house is not for sale.");
			}
			TogglePlayerControllable(playerid,1);
		}
		if(row == 5)
		{
			new name[256];
			GetPlayerName(playerid,name,255);
			if(strcmp(name,Load(house,"Owner"),true)==0)
			{
			    Save(house,"Owner","Nnne");
				save(playerid,"House","0");
				save(playerid,"X","0");
				save(playerid,"Y","0");
				save(playerid,"Z","0");
				save(playerid,"I","0");
				SendClientMessage(playerid,0xFFFFFFAA,"House: You have successfully sold this house.");
				GivePlayerMoney(playerid,strval(Load(house,"Cost")));
			}
			else
			{
			    SendClientMessage(playerid,0xFFFFFFAA,"House: You dont own this house.");
			}
			TogglePlayerControllable(playerid,1);
		}

	}
	CallLocalFunction("OnPlayerSelectedMenuRow_script","ii",playerid,row);
}
#define OnPlayerSelectedMenuRow OnPlayerSelectedMenuRow_script

public OnPlayerSpawn(playerid)
{
	if(exist(playerid)==1)
	{
		if(strcmp(load(playerid,"House"),"0",true)!=0)
		{
		    SetPlayerPos(playerid,floatstr(load(playerid,"X")),floatstr(load(playerid,"Y")),floatstr(load(playerid,"Z")));
		    SetPlayerInterior(playerid,strval(load(playerid,"I")));
		    new string[256];
		    format(string,255,"%s",load(playerid,"House"));
		    strdel(string,0,5);
		    GetPlayerHouse[playerid] = strval(string);
		    ShowMenuForPlayer(HE,playerid);
		}
	}
	CallLocalFunction("OnPlayerSpawn_script","i",playerid);
}
#define OnPlayerSpawn OnPlayerSpawn_script

public OnPlayerExitedMenu(playerid)
{
	new Menu:menuid = GetPlayerMenu(playerid);
	if(menuid == HE)
	{
        SetPlayerPos(playerid,GetHouseX[GetPlayerHouse[playerid]]+2,GetHouseY[GetPlayerHouse[playerid]]+2,GetHouseZ[GetPlayerHouse[playerid]]);
        SetPlayerInterior(playerid,0);
        GetPlayerHouse[playerid] = -1;
	}
	if(menuid == HM)
	{
	    TogglePlayerControllable(playerid,1);
        GetPlayerHouse[playerid] = -1;
	}
	CallLocalFunction("OnPlayerExitedMenu_script","i",playerid);
}
#define OnPlayerExitedMenu OnPlayerExitedMenu_script
