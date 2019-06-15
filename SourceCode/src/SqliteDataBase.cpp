#include "SqliteDataBase.h"
#include "sqlite3.h"

SqliteDataBase::SqliteDataBase()
{
    //ctor
  OpenDataBase();

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
SqliteDataBase::OpenDataBase()
{
   rc = sqlite3_open("redrat.db", &db);
    if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   /*
    sql = "CREATE TABLE NODEMSG("  \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT ," \
      "SENDER           TEXT    ," \
      "JSON            TEXT     ," \
      "TIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP );";
      CreateTable(sql);
      */
}

bool
SqliteDataBase::CreateTable(char* sql)
{
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
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
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return false;
   } else {
      fprintf(stdout, "Record created successfully\n");
      return true;
   }

}

bool
SqliteDataBase::SelectRecord(char* sql)
{
    const char* data = "Callback function called";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return false;
   } else {
      fprintf(stdout, "Operation done successfully\n");
      return true;
   }
   } else {
      fprintf(stdout, "Operation done successfully\n");
      return true;
   }
}

bool
SqliteDataBase::DeleteRecord(char* sql)
{
    const char* data = "Callback function called";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return false;
   } else {
      fprintf(stdout, "Operation done successfully\n");
      return true;
   }
}

SqliteDataBase::~SqliteDataBase()
{
    sqlite3_close(db);
}

