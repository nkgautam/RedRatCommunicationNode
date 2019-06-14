#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()
{
    //ctor
    rc = sqlite3_open("redrat.db", &db);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

bool
SqliteDataBase::CreateTable(char* sql)
{
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      //fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return false;
   } else {
      //fprintf(stdout, "Table created successfully\n");
      return true;
   }

}

bool
SqliteDataBase::InsertRecord(char* sql)
{
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      //fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return false;
   } else {
      //fprintf(stdout, "Table created successfully\n");
      return true;
   }

}

SqliteDataBase::~SqliteDataBase()
{
    sqlite3_close(db);
}

