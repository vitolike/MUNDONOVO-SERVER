 /*  SA-MP Mysql Connect 2.0
 *
 *  (c) Copyright 2010, Christian David
 *
 */

#if defined _mysqlvars_included
	#endinput
#endif
#define _mysqlvars_included
#pragma library mysqlvars

#include <mysqlcon>

forward SaveSQLSBizz(n);
forward SaveSQLBizz(n);
forward SaveSQLCar(idx);
forward SaveSQLAppt(a);
forward SaveSQLHouse(h);
forward SQLLog(string[]);
forward LoadSQLVehicleInfo();
forward LoadSQLSpamWords();
forward SaveSQLFamily(n);
forward LoadSQLFamilies();
forward LoadSQLFamilyGates();
forward LoadSQLObjects();
forward LoadSQLPoints();
forward LoadSQLCars();
forward LoadSQLGPS();
forward LoadSQLProperty();
forward LoadSQLApartments();
forward LoadSQLBizz();
forward LoadSQLSBizz();
