#ifndef AUTH_H
#define AUTH_H

#include <string>

enum UserRole
{
    UNKNOWN,
    PEMBELI,
    ADMIN
};

struct User
{
    std::string username;
    UserRole role = UNKNOWN;
};

int selectInitialRole();
User loginUser(UserRole role);
User signupUser();

#endif
