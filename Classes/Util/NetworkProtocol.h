//
//  NetworkProtocol.h
//  HelloWorld
//
//  Created by MrZhou on 14-7-15.
//
//

#ifndef HelloWorld_NetworkProtocol_h
#define HelloWorld_NetworkProtocol_h

struct LoginRequestData
{
    char username[32];
    char password[32];
    int  loginType;
};

struct AccountData
{
    char username[32];
    char password[32];
};

struct LoginResponseData
{
    int loginResult;  //登录结果0:失败 1:成功
    struct AccountData account;
};

#endif
