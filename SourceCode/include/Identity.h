#ifndef IDENTITY_H
#define IDENTITY_H
#include <string>

using namespace std;

class Identity
{
    public:
        Identity();

        bool CreateLogin(string username, string password);
        string GetPassword(string username);

    protected:

    private:
};

#endif // IDENTITY_H
