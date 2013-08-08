///  Project : S3C CGI
///  File Name : cookie.h
///  Date :
///  Author : James Nzomo


#ifndef S3C_CGI_COOKIE_H
#define S3C_CGI_COOKIE_H

typedef map<string,string> lkupMap;

void initCookies(lkupMap &cookies)
{
	std::string tmpkey, tmpvalue;
	std::string *tmpstr = &tmpkey;
	register char* raw_ckie = getenv("HTTP_COOKIE");
	if (raw_ckie==NULL) {
		cookies.clear();
		return;
	}
	while (*raw_ckie != '\0') {
		if (*raw_ckie==';') {
			if (tmpkey!="") {
				cookies[urlDecode(tmpkey)] = urlDecode(tmpvalue);
			}
			tmpkey.clear();
			tmpvalue.clear();
			tmpstr = &tmpkey;
		} else if (*raw_ckie=='=') {
			tmpstr = &tmpvalue;
		} else {
			(*tmpstr) += (*raw_ckie);
		}
		raw_ckie++;
	}
	//enter the last pair to the map
	if (tmpkey!="") {
		cookies[urlDecode(tmpkey)] = urlDecode(tmpvalue);
		tmpkey.clear();
		tmpvalue.clear();
	}
}

string getCookie(string name)
{
    if(getenv("HTTP_COOKIE") == NULL)
        return "NULL";

    string val,ckenv = getenv("HTTP_COOKIE");

    int namePos = ckenv.find(name,0),
        valPos  = namePos + name.length() + 1,
        valLen = ckenv.find("; ",valPos) - valPos;

    //cout <<"namePos"<< namePos <<", valPos = "<< valPos<<", vaLen = "<<valLen<<"<br>";
    return (namePos  < 0)?"NULL":ckenv.substr(valPos,valLen);
}

void setCookie(string Name = "",        ///The NAME of the cookie. Should be presented like NAME=VALUE
               string Value = "",       ///VALUE of the cookie. Should be presented like NAME=VALUE
               string Comment = "",     ///Describes how the server intends to use the cookie.
               string CommentURL = "",  ///Same as above
               bool Discard = false,    ///Instructs the user agent to discard the cookie on termination.
               string Domain = "",      ///The domain for which the cookie is valid.
               string MaxAge = "3600",  ///Max-Age The lifetime of the cookie in seconds. Zero means the cookie is discarded immediately.
               string Expires = "",     ///Expiration date for the cookie
               string Path = "",        ///The URL path to which this cookie applies.
               string Ports = "\"80,8000\"",     ///The Ports to which a cookie may be returned in a Cookie request header.
                                        ///Note that the syntax REQUIREs quotes around the portlist

               bool Secure = false,        ///Directs the user agent to use only secure means to contact the origin server whenever it sends back this cookie
               string Version = "1")    ///The ver)
{
        string setcookie;

        setcookie += "Set-Cookie: ";
        setcookie += Name + "=" + Value + "; ";
        setcookie += "Comment=" + Comment + "; ";
        setcookie += "CommentURL=" + CommentURL + "; ";

        if(Discard)
            setcookie += "Discard; ";

        if(!Domain.empty())
            setcookie += "Domain=" + Domain + "; ";

        if(!MaxAge.empty())
            setcookie += "Max-Age=" + MaxAge + "; ";

        if(!Path.empty())
            setcookie += "Path=" + Path + "; ";

        if(!Ports.empty())
            setcookie += "Port=" + Ports + "; ";

        if(!Expires.empty())
            setcookie += "Expires=" + Expires + "; ";

        if(Secure)
            setcookie += "Secure; ";

        if(!Version.empty())
            setcookie += "Version=" + Version + "; ";

        cout<<setcookie<<endl;
}
#endif //S3C_CGI_COOKIE_H
