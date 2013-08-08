///  Project : S3C CGI
///  File Name : defs.h
///  Date :
///  Author : James Nzomo


#ifndef S3C_CGI_DEFS_H
#define S3C_CGI_DEFS_H

string  APP_CLIENT = "Sheria Sacco Ltd",
        APP_VER = "0.1",
        //APP_DOMAIN = "localhost",
        APP_DOMAIN = "www.sheriasacco.coop",
        APP_PATH = "/cgi-bin/",

#ifdef __S3C_CGI_DEBUG__
        APP_NAME = "essvrd",
#else
        APP_NAME = "essvr",
#endif

        APP_URL = "http://" + APP_DOMAIN + APP_PATH + APP_NAME + "?";

#define LCL_RDR(l) cout << "Location: "<< APP_URL << l << endl << endl;


#define HTML_HDR cout << "Content-Type:text/html;charset=iso-8859-1" << endl;
#define TEXT_HDR cout << "Content-Type:text/plain;charset=ASCII" << endl;
#define JS_HDR cout << "Content-Type:application/javascript;charset=ASCII" << endl;
#define LCN_HDR(l) cout << "Location: http://"<< l << endl << endl;
#define CLOSE_HDR cout << endl << endl;
#define BR cout << "<br/>" << endl;
#define br "<br/>"
#define bp system("beep");
#define dbg HTML_HDR  CLOSE_HDR  bp cout<<"debug"<<br;
//#define RAND_MAX 80

using namespace std;

typedef map<string,string> lkupMap;

#endif //S3C_CGI_DEFS_H
