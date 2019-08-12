#include "Identity.h"
#include "SqliteDataBase.h"
#include <string>
#include <sstream>
#include "sha256.h"
#include <sqlite3.h>

static int callback1(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);

   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

Identity::Identity()
{
    //ctor
}

bool
Identity::CreateLogin(string username, string password)
{
    //  SqliteDataBase sqlitedb;

    //  get total count and format the CustID
    //  sqlitedb.SelectRecord("select max(ID) from NODEMSG;",callback1);
    //  encrypt password
    std::ostringstream ss;
    ss << username << password;

    string passwordHash = sha256(ss.str());

    //    char* sql = "INSERT INTO IDENTITY (CustID,Username,Password) VALUES ('custID','"+ username.c_str()+"','"+passwordHash.c_str()+"',  ); " ;

    //    sqlitedb.InsertRecord(sql);
}

string
Identity::GetPassword(string username)
{

}
