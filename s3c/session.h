///  Project : enem_cgi
///  File Name : session.h
///  Date :
///  Author : James Nzomo


#ifndef S3C_CGI_SESSION_H
#define S3C_CGI_SESSION_H

bool createSession(lkupMap session,lkupMap cookies);

void fillSession(string in,lkupMap &out)
{

	string tmpkey, tmpvalue;
	string *tmpstr = &tmpkey;
	register char* raw_in = (char*)in.c_str();
	if (raw_in==NULL) {
		out.clear();
		return;
	}
	while (*raw_in != '\0') {
		if (*raw_in==';') {
			if (tmpkey!="") {
				//out[urlDecode(tmpkey)] = urlDecode(tmpvalue);
				out[tmpkey] = tmpvalue;
			}
			tmpkey.clear();
			tmpvalue.clear();
			tmpstr = &tmpkey;
		} else if (*raw_in=='=') {
			tmpstr = &tmpvalue;
		} else {
			(*tmpstr) += (*raw_in);
		}
		raw_in++;
	}
	//enter the last pair to the map
	if (tmpkey!="") {
		//out[urlDecode(tmpkey)] = urlDecode(tmpvalue);
		out[tmpkey] = tmpvalue;
		tmpkey.clear();
		tmpvalue.clear();
	}
//    CLOSE_HDR
//    for(lkupMap::const_iterator it = out.begin(); it != out.end(); ++it)
        //cout <<";<br>"<<in<<","<< it->first << '=' << it->second << ";<br>";
}

bool loadSession(lkupMap &session,lkupMap cookies)
{
//    CLOSE_HDR
//    cout << cookies["s"];
    if(cookies["s"].empty()){
        createSession(session,cookies);
        session.clear();
        return true;
    }
    string data,ffname = "s/"+cookies["s"];
    ifstream session_file(ffname.c_str(),ios::in);
    //ifstream session_file("s/ses",ios::in);
    if (session_file.is_open())
    {
        while( session_file.good() )
          getline(session_file,data);

        session_file.close();
        fillSession(data,session);
    }
    else
        return false;
    return true;
}

bool saveSession(lkupMap session,lkupMap cookies)
{
    struct stat st;
    if(stat("s",&st) != 0){
        //cout << ", stat st != 0"<< endl;
        if(mkdir("s", 0755) != 0){
            //cout << ", mkdir s failed!"<< endl;
            return false;
        }
    }
    string ffname = "s/"+cookies["s"],data = "";
    ofstream session_file(ffname.c_str(),ios::out);
    //ofstream session_file("s/ses",ios::out);
    if (session_file.is_open())
    {
        for(lkupMap::const_iterator it = session.begin(); it != session.end(); ++it){
            data = it->first + "=" + it->second + ";";
            session_file << data;
            //session_file << it->first << "=" << it->second << ";";
        }
        session_file.close();
    }
    else{
        return false;
    }
//    for(lkupMap::const_iterator it = session.begin(); it != session.end(); ++it)
//    cout << it->first << '=' << it->second << ';';
    return true;
}

bool createSession(lkupMap session,lkupMap cookies)
{
    time_t secs = time(NULL);
    stringstream tmp;
    tmp <<secs<<rand_s(10);
    string ssn_name;
    tmp >> ssn_name;
    setCookie("s",ssn_name,"","",true,"","3600");
    return saveSession(session, cookies);
}

bool killSession(lkupMap cookies)
{
    if(!cookies["s"].empty())
        setCookie("s",cookies["s"],"","",true,"","0","Thu, 01 Jan 1970 00:00:00 GMT");
    //CLOSE_HDR
    string  ffname = "s/"+cookies["s"];
    return remove(ffname.c_str()) == 0?true:false;
}

#endif //S3C_CGI_SESSION_H
