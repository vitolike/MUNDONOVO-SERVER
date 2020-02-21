/*
	SA-MP MapAndreas Include
	Copyright © 2011 RyDeR`
*/

#if defined _MapAndreas_Included
	#endinput
#endif

#define _MapAndreas_Included

#define MAP_ANDREAS_MODE_NONE			0
#define MAP_ANDREAS_MODE_MINIMAL		1 // for future use
#define MAP_ANDREAS_MODE_FULL			2

native MapAndreas_Init(mode);
native MapAndreas_FindZ_For2DCoord(Float:X, Float:Y, &Float:Z);

stock GetPointZPos(Float: point_X, Float: point_Y, &Float: point_Z)
{
	if(!(-3000.0 < point_X < 3000.0 || -3000.0 < point_Y < 3000.0))
		return 0;
	
	static
		File: z_Map_File
	;
	if(!z_Map_File)
	{
		z_Map_File = fopen("SAfull.hmap", io_read);
		
		if(!z_Map_File)
			return 0;
	}
	new
		z_Data[2 char]
	;
	fseek(z_Map_File, (-6000 * (floatround(point_Y, point_Y <= 0.0 ? floatround_ceil : floatround_floor) - 3000) + floatround(point_X, point_X <= 0.0 ? floatround_ceil : floatround_floor) + 3000) * 2);
	fblockread(z_Map_File, z_Data, 2 char);
	
	point_Z = (z_Data[1 / 2] & 0x0000FFFF) * 0.01;
	return 1;	
}