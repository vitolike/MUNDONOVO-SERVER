#include <a_samp>


#if defined MAX_VEHICLES

    #undef  MAX_VEHICLES
    #define MAX_VEHICLES 700 //change to your vehicles number

#endif

#if defined MAX_PLAYERS

    #undef  MAX_PLAYERS
    #define MAX_PLAYERS 50 //change to your player slot number

#endif



#define GREY                0xAFAFAFAA
#define WHITE               0xFFFFFFAA
#define CHAT1               0xF9B7FFAA
#define LIGHTBLUE           0xA9C4E4FF


#define MAX_TRUNK_SLOTS   5 // trunk slots


new vehTrunkCounter[MAX_VEHICLES] = 1;
new vehTrunk[MAX_VEHICLES][MAX_TRUNK_SLOTS];
new vehTrunkAmmo[MAX_VEHICLES][MAX_TRUNK_SLOTS];
new Float:vehTrunkArmour[MAX_VEHICLES];


new BigEar[MAX_PLAYERS];

new ScriptWeaponsUpdated[MAX_PLAYERS];

new ScriptWeapons[MAX_PLAYERS][13];


public OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128], idx, string[128];
    cmd = strtok(cmdtext, idx);
    
  if(!strcmp(cmd, "/trunk", true))
    {
      new x_nr[64], pname[20];
        x_nr = strtok(cmdtext, idx);
        
        GetPlayerName(playerid, pname, sizeof(pname));

        if(!strlen(x_nr))
        {
            SendClientMessage(playerid, WHITE, "HINT: /trunk [name]");
            SendClientMessage(playerid, WHITE, "Available names: info, putgun, takegun, putarmour, takearmour");
          if(IsPlayerAdmin(playerid))
          {
            SendClientMessage(playerid, WHITE, "You can /trunk frisk as an admin.");
          }
            return 1;
        }

        if(strcmp(x_nr,"info",true) == 0)
        {
            new counter = 0;
            new result;
            
            for(new i; i != MAX_VEHICLES; i++)
          {
            new dist = CheckPlayerDistanceToVehicle(3.5, playerid, i);
            if(dist)
            {
                result = i;
                counter++;
            }
          }

            switch(counter)
          {
            case 0:
                {
                SendClientMessage(playerid, GREY, "  No cars with trunk near you");
                }

                case 1:
                {
                if(IsPlayerInAnyVehicle(playerid))
                    {
                    SendClientMessage(playerid, GREY, " You can't open the trunk while you're in the car");
                        return 1;
                    }

                /*if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 440 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 456 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 498)
                    {
                    SendClientMessage(playerid, GREY, " This vehicle doesn't have the trunk !");
                    return 1;
                    }*/

                    SendClientMessage(playerid, LIGHTBLUE, "|_______ Vehicle Trunk _______|");
                    for(new slot = 1; slot != MAX_TRUNK_SLOTS; slot++)
                    {
                    new gunname[100];
                    if(vehTrunk[result][slot] != 0)
                      {
                        GetWeaponName(vehTrunk[result][slot], gunname, sizeof(gunname));
                        format(string, sizeof(string), "| Slot %i: %s (Ammo: %i)", slot, gunname, vehTrunkAmmo[result][slot]);
                        SendClientMessage(playerid, WHITE, string);
                      }
                      else
                      {
                        format(string, sizeof(string), "| Slot %i: Empty (Ammo: N/A)", slot);
                        SendClientMessage(playerid, WHITE, string);
                      }
                    }

                    format(string, sizeof(string), "| Body armour: %f%", vehTrunkArmour[result]);
                    SendClientMessage(playerid, WHITE, string);

                    format(string, sizeof(string), "* %s opens the trunk and checks what is inside.", pname);
                    ProxDetector(30.0, playerid, string, CHAT1, CHAT1, CHAT1, CHAT1, CHAT1);

                    return 1;
                }

                default:
            {
                    SendClientMessage(playerid, GREY, "  Found more then one car in range");
                    return 1;
                }
        }
          return 1;
        }
        else if(!strcmp(x_nr,"putgun",true))
        {
            new counter = 0;
            new result;

            for(new i; i != MAX_VEHICLES; i++)
            {
            new dist = CheckPlayerDistanceToVehicle(3.5, playerid, i);
            if(dist)
            {
                result = i;
                counter++;
            }
          }

            switch(counter)
            {
                case 0:
                {
                    SendClientMessage(playerid, GREY, "  No cars with trunk near you");
                }

                case 1:
            {
                    if(vehTrunkCounter[result] != (MAX_TRUNK_SLOTS-1))
                    {
                        if(IsPlayerInAnyVehicle(playerid))
                    {
                    SendClientMessage(playerid, GREY, " You can't open the trunk while you're in the car");
                    return 1;
                }

                        /*if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 440 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 456 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 498)
                        {
                        SendClientMessage(playerid, GREY, " This vehicle doesn't have the trunk !");
                        return 1;
                        }*/

                        new buffer[512];
                    new gunname[100];
                    new gunID = GetPlayerWeapon(playerid);
                    new gunAmmo = GetPlayerAmmo(playerid);

                        if(gunID != 0 && gunAmmo != 0)
                        {
                            GetWeaponName(gunID, gunname, sizeof(gunname));
                            vehTrunkCounter[result]++;
                            vehTrunk[result][vehTrunkCounter[result]] = gunID;
                            vehTrunkAmmo[result][vehTrunkCounter[result]] = gunAmmo;

                            format(buffer, sizeof(buffer), "You have put your %s (Ammo: %i) in the car's trunk.", gunname, gunAmmo);
                            SendClientMessage(playerid, WHITE, buffer);

                            RemovePlayerWeapon(playerid, gunID);

                            format(string, sizeof(string), "* %s opens car's trunk and puts a weapon there.", pname);
                            ProxDetector(30.0, playerid, string, CHAT1, CHAT1, CHAT1, CHAT1, CHAT1);
                            return 1;
                }
            }
              else
              {
                SendClientMessage(playerid, GREY, " Car's trunk is full");
                return 1;
              }
                }

                default:
            {
                    SendClientMessage(playerid, GREY, "  Found more then one car in range");
                    return 1;
                }
            }
        return 1;
        }
        else if(strcmp(x_nr,"takegun",true) == 0)
        {
            new counter = 0;
            new result;

            for(new i; i != MAX_VEHICLES; i++)
            {
                new dist = CheckPlayerDistanceToVehicle(3.5, playerid, i);
                if(dist)
                {
                    result = i;
                    counter++;
                }
            }

            switch(counter)
            {
            case 0:
            {
                SendClientMessage(playerid, GREY, "  No cars with trunk near you");
                return 1;
            }

                case 1:
            {
                    if(IsPlayerInAnyVehicle(playerid))
                    {
                        SendClientMessage(playerid, GREY, "  You can't open the trunk while you're in the car");
                        return 1;
                    }

                    /*if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 440 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 456 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 498)
                    {
                    SendClientMessage(playerid, GREY, " This vehicle doesn't have the trunk !");
                    return 1;
                    }*/

                    if(vehTrunkCounter[result] != 0)
                {
                        new buffer[512];
                        new gunName[100];

                        SafeGivePlayerWeapon(playerid, vehTrunk[result][vehTrunkCounter[result]], vehTrunkAmmo[result][vehTrunkCounter[result]]);

                        GetWeaponName(vehTrunk[result][vehTrunkCounter[result]], gunName, sizeof(gunName));

                        format(buffer, sizeof(buffer), "You've taken a %s (Ammo: %i) from the vehicle.", gunName, vehTrunkAmmo[result][vehTrunkCounter[result]]);
                    SendClientMessage(playerid, WHITE, buffer);

                        vehTrunk[result][vehTrunkCounter[result]] = '\0';
                    vehTrunkAmmo[result][vehTrunkCounter[result]] = '\0';
                    vehTrunkCounter[result]--;

                        format(string, sizeof(string), "* %s opens car's trunk and takes a weapon.", pname);
                    ProxDetector(30.0, playerid, string, CHAT1, CHAT1, CHAT1, CHAT1, CHAT1);
                    return 1;
                }
                else
                {
                SendClientMessage(playerid, GREY, "  Trunk is empty ! ");
                return 1;
              }
            }

                default:
            {
                    SendClientMessage(playerid, GREY, "  Found more then one car in range");
                    return 1;
                }
            }
        return 1;
        }
        else if(strcmp(x_nr,"putarmour",true) == 0)
        {
            new counter = 0;
            new result;

            for(new i; i != MAX_VEHICLES; i++)
            {
            new dist = CheckPlayerDistanceToVehicle(3.5, playerid, i);
            if(dist)
            {
                result = i;
                counter++;
            }
            }

            switch(counter)
            {
                case 0:
            {
                    SendClientMessage(playerid, GREY, "  No cars with trunk near you");
                    return 1;
                }

                case 1:
                {
                if(IsPlayerInAnyVehicle(playerid))
                {
                    SendClientMessage(playerid, GREY, "  You can't open the trunk while you're in the car");
                    return 1;
                }

                    /*if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 440 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 456 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 498)
                    {
                    SendClientMessage(playerid, GREY, " This vehicle doesn't have the trunk !");
                    return 1;
                    }*/

                    new Float:plyArmour;
                    GetPlayerArmour(playerid, plyArmour);

                    if(plyArmour != 0)
                    {
                    SafeSetPlayerArmour(playerid, 0);
                    vehTrunkArmour[result] = plyArmour;

                        format(string, sizeof(string), "* %s takes off his/her body armour and puts it into car trunk.", pname);
                    ProxDetector(30.0, playerid, string, CHAT1, CHAT1, CHAT1, CHAT1, CHAT1);
                    return 1;
                    }
                    else
                {
                    SendClientMessage(playerid, GREY, "  You haven't got any armour ");
                    return 1;
              }
                }

                default:
            {
                    SendClientMessage(playerid, GREY, "  Found more then one car in range");
                    return 1;
                }
            }
            return 1;
        }
        else if(strcmp(x_nr,"takearmour",true) == 0)
        {
            new counter = 0;
            new result;
              
            for(new i; i != MAX_VEHICLES; i++)
        {
            new dist = CheckPlayerDistanceToVehicle(3.5, playerid, i);
            if(dist)
            {
                result = i;
                counter++;
                }
          }

            switch(counter)
            {
            case 0:
            {
                SendClientMessage(playerid, GREY, "  No cars with trunk near you");
                return 1;
            }

                case 1:
            {
                    if(IsPlayerInAnyVehicle(playerid))
                    {
                        SendClientMessage(playerid, GREY, "  You can't open the trunk while you're in the car");
                        return 1;
                    }

                    /*if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 440 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 456 || GetVehicleModel(GetPlayerVehicleID(playerid)) != 498)
                    {
                    SendClientMessage(playerid, GREY, " This vehicle doesn't have the trunk !");
                    return 1;
                    }*/

