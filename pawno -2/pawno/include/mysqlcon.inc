 /*  SA-MP Mysql Connect 2.0
 *
 *  (c) Copyright 2010, Christian David
 *
 */

#if defined _mysqlcon_included
	#endinput
#endif
#define _mysqlcon_included
#pragma library mysqlcon

#include <a_sampmysql>


forward MySQLConnect(sqlhost[], sqluser[], sqlpass[], sqldb[]);
forward MySQLDisconnect();
forward MySQLCheckConnection();
forward MySQLUpdateBuild(query[], sqlplayerid);
forward MySQLUpdateFinish(query[], sqlplayerid);
forward MySQLUpdatePlayerInt(query[], sqlplayerid, sqlvalname[], sqlupdateint);
forward MySQLUpdatePlayerIntSingle(sqlplayerid, sqlvalname[], sqlupdateint);
forward MySQLUpdatePlayerFlo(query[], sqlplayerid, sqlvalname[], Float:sqlupdateflo);
forward MySQLUpdatePlayerStr(query[], sqlplayerid, sqlvalname[], sqlupdatestr[]);
forward MySQLCheckAccount(sqlplayersname[]);
forward MySQLCheckAccountLocked(sqlplayerid);
forward MySQLCheckIPBanned(ip[]);
forward MySQLFetchAcctSingle(sqlplayerid, sqlvalname[], sqlresult[]);
forward MySQLFetchAcctRecord(sqlplayerid, sqlresult[]);
forward MySQLCreateAccount(newplayersname[], newpassword[]);
forward MySQLAddLoginRecord(sqlplayerid, ipaddr[]);
forward LerSQL();

enum SQLInfo
{
	Host[128],
	Login[128],
	Senha[128],
	Database[128],
};

new Mysql_Conf[SQLInfo];

public LerSQL()
{
        new arquivo25[256];
	    format(arquivo25, sizeof(arquivo25), "/Mysql_Conf/mysql.ini");
        strmid(Mysql_Conf[Host], dini_Get(arquivo25,"Host"), 0, strlen(dini_Get(arquivo25,"Host")), 255);
        strmid(Mysql_Conf[Login], dini_Get(arquivo25,"Login"), 0, strlen(dini_Get(arquivo25,"Login")), 255);
        strmid(Mysql_Conf[Senha], dini_Get(arquivo25,"Senha"), 0, strlen(dini_Get(arquivo25,"Senha")), 255);
        strmid(Mysql_Conf[Database], dini_Get(arquivo25,"Database"), 0, strlen(dini_Get(arquivo25,"Database")), 255);
        MySQLConnect(Mysql_Conf[Host],Mysql_Conf[Login],Mysql_Conf[Senha],Mysql_Conf[Database]);

}

public MySQLConnect(sqlhost[], sqluser[], sqlpass[], sqldb[]) // by Luk0r
{
	print("MYSQL: Attempting to connect to server...");
	samp_mysql_connect(sqlhost, sqluser, sqlpass);
	samp_mysql_select_db(sqldb);
	if(samp_mysql_ping()==0)
	{
		print("MYSQL: Database connection established.");
		return 1;
	}
	else
	{
		print("MYSQL: Connection error, retrying...");
		samp_mysql_connect(sqlhost, sqluser, sqlpass);
		samp_mysql_select_db(sqldb);
		if(samp_mysql_ping()==0)
		{
			print("MYSQL: Reconnection successful. We can continue as normal.");
			return 1;
		}
		else
		{
			print("MYSQL: Could not reconnect to server, terminating server...");
			SendRconCommand("exit");
			return 0;
		}
	}
}

public MySQLDisconnect() // by Luk0r
{
	samp_mysql_close();
	return 1;
}

public MySQLCheckConnection() // by Luk0r
{
	if(samp_mysql_ping()==0)
	{
		return 1;
	}
	else
	{
		print("MYSQL: Connection seems dead, retrying...");
		MySQLDisconnect();
		LerSQL();
		if(samp_mysql_ping()==0)
		{
			print("MYSQL: Reconnection successful. We can continue as normal.");
			return 1;
		}
		else
		{
			print("MYSQL: Could not reconnect to server, terminating server...");
			SendRconCommand("exit");
			return 0;
		}
	}
}

public MySQLUpdateBuild(query[], sqlplayerid) // by Luk0r
{
	new querylen = strlen(query);
	//new querymax = sizeof(query);
	new querymax = MAX_STRING;
	if (querylen < 1) format(query, querymax, "UPDATE players SET ");
	else if (querymax-querylen < 50) // make sure we're being safe here
	{
		// query is too large, send this one and reset
		new whereclause[32];
		format(whereclause, sizeof(whereclause), " WHERE id=%d", sqlplayerid);
		strcat(query, whereclause, querymax);
		samp_mysql_query(query);
		//if (DEBUG) SQLLog(query);
		format(query, querymax, "UPDATE players SET ");
	}
	else if (strfind(query, "=", true) != -1) strcat(query, ",", MAX_STRING);
	return 1;
}

public MySQLUpdateFinish(query[], sqlplayerid) // by Luk0r
{
	if (strcmp(query, "WHERE id=", false) == 0) samp_mysql_query(query);
	else
	{
		new whereclause[32];
		format(whereclause, sizeof(whereclause), " WHERE id=%d", sqlplayerid);
		strcat(query, whereclause, MAX_STRING);
		samp_mysql_query(query);
		format(query, MAX_STRING, "UPDATE players SET ");
	}
	return 1;
}

public MySQLUpdatePlayerInt(query[], sqlplayerid, sqlvalname[], sqlupdateint) // by Luk0r
{
	MySQLUpdateBuild(query, sqlplayerid);
	new updval[64];
	format(updval, sizeof(updval), "%s=%d", sqlvalname, sqlupdateint);
	strcat(query, updval, MAX_STRING);
	return 1;
}

public MySQLUpdatePlayerFlo(query[], sqlplayerid, sqlvalname[], Float:sqlupdateflo) // by Luk0r
{
/*	new query[128];
	format(query, sizeof(query), "UPDATE players SET %s=%f WHERE id=%d", sqlvalname, sqlupdateflo, sqlplayerid);
	samp_mysql_query(query);*/
	new flotostr[32];
	format(flotostr, sizeof(flotostr), "%f", sqlupdateflo);
	MySQLUpdatePlayerStr(query, sqlplayerid, sqlvalname, flotostr);
	return 1;
}

public MySQLUpdatePlayerStr(query[], sqlplayerid, sqlvalname[], sqlupdatestr[]) // by Luk0r
{
	MySQLUpdateBuild(query, sqlplayerid);
	new escstr[128];
	new updval[128];
	samp_mysql_real_escape_string(sqlupdatestr, escstr);
	format(updval, sizeof(updval), "%s='%s'", sqlvalname, escstr);
	strcat(query, updval, MAX_STRING);
	return 1;
}

public MySQLUpdatePlayerIntSingle(sqlplayerid, sqlvalname[], sqlupdateint) // by Luk0r
{
	new query[128];
	format(query, sizeof(query), "UPDATE players SET %s=%d WHERE id=%d", sqlvalname, sqlupdateint, sqlplayerid);
	samp_mysql_query(query);
	//if (DEBUG) SQLLog(query);
	return 1;
}

public MySQLCheckAccount(sqlplayersname[]) // by Luk0r
{
	new query[128];
	new escstr[MAX_PLAYER_NAME];
	samp_mysql_real_escape_string(sqlplayersname, escstr);
	format(query, sizeof(query), "SELECT id FROM players WHERE LOWER(Name) = LOWER('%s') LIMIT 1", escstr);
	samp_mysql_query(query);
	//if (DEBUG) SQLLog(query);
	samp_mysql_store_result();
	if (samp_mysql_num_rows()==0)
	{
		return 0;
	}
	else
	{
		new strid[32];
		new intid;
		samp_mysql_fetch_row(strid);
		intid = strval(strid);
		samp_mysql_free_result();
		return intid;
	}
}

public MySQLCheckAccountLocked(sqlplayerid)
{
	new query[64];
	new lockedboolstr[4];
	format(query, sizeof(query), "SELECT Locked FROM players WHERE id=%d LIMIT 1", sqlplayerid);
	samp_mysql_query(query);
	//if (DEBUG) SQLLog(query);
	samp_mysql_store_result();
	samp_mysql_fetch_row(lockedboolstr);
	if (strval(lockedboolstr) != 0)
	{
		samp_mysql_free_result();
		return 1;
	}
	samp_mysql_free_result();
	return 0;
}

public MySQLCheckIPBanned(ip[])
{
	new query[64];
	format(query, sizeof(query), "SELECT type FROM bans WHERE ip = '%s' AND inactive = 0 ORDER BY id DESC LIMIT 1", ip);
	samp_mysql_query(query);
	//if (DEBUG) SQLLog(query);
	samp_mysql_store_result();
	if (samp_mysql_num_rows() != 0)
	{
		new bantypestr[4];
		new bantypeint;
		samp_mysql_fetch_row(bantypestr);
		bantypeint = strval(bantypestr);
		samp_mysql_free_result();
		return bantypeint;
	}
	return 0;
}

public MySQLFetchAcctSingle(sqlplayerid, sqlvalname[], sqlresult[])
{
	new query[128];
	format(query, sizeof(query), "SELECT %s FROM players WHERE id = %d LIMIT 1", sqlvalname, sqlplayerid);
	samp_mysql_query(query);
	//if (DEBUG) SQLLog(query);
	samp_mysql_store_result();
	if(samp_mysql_fetch_row(sqlresult)==1)
	{
		samp_mysql_free_result();
		return 1;
	}
	return 0;
}

public MySQLFetchAcctRecord(sqlplayerid, sqlresult[]) // by Luk0r
{
	new query[64];
	format(query, sizeof(query), "SELECT * FROM players WHERE id = %d LIMIT 1", sqlplayerid);
	samp_mysql_query(query);
	//if (DEBUG) SQLLog(query);
	samp_mysql_store_result();
	if(samp_mysql_fetch_row(sqlresult)==1)
	{
		samp_mysql_free_result();
		return 1;
	}
	return 0;
}

public MySQLCreateAccount(newplayersname[], newpassword[]) // by Luk0r
{
	new query[128];
	new sqlplyname[64];
	new sqlpassword[64];
	samp_mysql_real_escape_string(newplayersname, sqlplyname);
	samp_mysql_real_escape_string(newpassword, sqlpassword);
	format(query, sizeof(query), "INSERT INTO players (Name, Password) VALUES ('%s', '%s')", sqlplyname, sqlpassword);
	samp_mysql_query(query);
	//if (DEBUG) SQLLog(query);
	new newplayersid = MySQLCheckAccount(newplayersname);
	if (newplayersid != 0)
	{
		return newplayersid;
	}
	return 0;
}

public MySQLAddLoginRecord(sqlplayerid, ipaddr[]) // by Luk0r
{
	new query[128];
	new escip[16];
	samp_mysql_real_escape_string(ipaddr, escip);
	format(query, sizeof(query), "INSERT INTO logins (time,ip,userid) VALUES (UNIX_TIMESTAMP(),'%s',%d)", escip, sqlplayerid);
	samp_mysql_query(query);
	//if (DEBUG) SQLLog(query);
	return 1;
}