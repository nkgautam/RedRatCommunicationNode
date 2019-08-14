#include "ClientID.h"
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

using namespace std;

ClientID::ClientID()
{
    //clientID
}

string
ClientID::CreateID()
{
   id = GetRandomDigit() +  GetRandomDigit() +  GetRandomDigit() +"-"+
        GetRandomDigit() +  GetRandomDigit() +  GetRandomDigit() +"-"+
        GetRandomDigit() +  GetRandomDigit() +  GetRandomDigit() ;

   return id;
}

string
ClientID::GetID()
{
   return id;
}

string
ClientID::GetRandomDigit()
{
    //srand(time(NULL));
    //int value =  rand() % 10;
    int value = Random(1,9);
    //cout<< "value"<<value<<endl;
    char ch[] = "0";
    sprintf(ch, "%d", value);
    //char ch = (char) value;
    //cout<< "ch"<< ch<<endl;
    string str = GetString( ch[0]);
    //string str = "nnn";
    //cout<< "str"<< str<<endl;

    return str;
}

int
ClientID::Random(int min, int max)
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) );
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

string
ClientID::GetString(char x)
{
    //cout<<"x"<<x<<endl;
    string s(1, x);

    return s;
}
