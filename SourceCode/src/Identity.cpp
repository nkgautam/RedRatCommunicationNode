#include "Identity.h"
#include "SqliteDataBase.h"
#include <string>
#include <sstream>
#include "sha256.h"

Identity::Identity()
{
    //ctor
}

bool
Identity::CreateID(string username, string password)
{
    SqliteDataBase sqlitedb;

    //get total count and format the CustID
    sqlitedb.SelectRecord("select max(ID) from NODEMSG;");
    //encrypt password
    std::ostringstream ss;
    ss << username << password;

    string passwordHash = sha256(ss.str());

    char* sql = "INSERT INTO IDENTITY (CustID,Username,Password) VALUES ('custID','"+ username.c_str()+"','"+passwordHash.c_str()+"',  ); " ;

    sqlitedb.InsertRecord(sql);
}

string
Identity::GetID(string username)
{

}
