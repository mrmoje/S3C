///  Project : S3C CGI
///  File Name : nmcgi.h
///  Date :
///  Author : James Nzomo


#ifndef S3C_CGI_H
#define S3C_CGI_H

#include <iostream>
#include <map>
#include <new>
#include <fstream>
#include <string>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <json/json.h>

#ifdef __S3C_CGI_DEBUG__
            ofstream log_file("debug.log");

            class dual_stream : ostream{
            public:
                dual_stream(ostream& os1, ostream& os2) : os1(os1), os2(os2) {}

                template<class T>
                dual_stream& operator<<(const T &x) {
                    os1 << x;
                    os2 << x;
                    return *this;
                }
            private:
                ostream& os1;
                ostream& os2;
            }dout(std::cout,log_file);
            #define endl "\n"
            #define cout dout
#endif //__DEBUG__

#include "defs.h"
#include "helpers.h"
#include "cookie.h"
#include "httpvars.h"
#include "session.h"


//using namespace std;

class s3c_cgiApp{
    public:
    s3c_cgiApp(){initGet(Get);initPost(Post);initCookies(cookies);}
    void die(string msg = ""){ cout << msg; exit(0);}
    lkupMap Get,Post,session,cookies;
}ap;

#endif  //S3C_CGI_H
