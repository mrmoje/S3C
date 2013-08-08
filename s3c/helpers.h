///  Project : S3C CGI
///  File Name : helpers.h
///  Date :
///  Author : James Nzomo


#ifndef S3C_CGI_HELPERS_H
#define S3C_CGI_HELPERS_H

string num2str(int num){
    stringstream tmp;
    tmp << num;
    return tmp.str();
}

string rand_s(int len) {
    string s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "{}[]()$^?#~@+-*_!|";

    for (int i = 0; i < len; ++i) {
        srand(time(NULL));
        s+= alphanum[rand() % (sizeof(alphanum) - i)];
    }

    return s;
}

string str_replace(string ndl,string swap,string hay){
    int ndlPos;
    string tmp = "_|$ndl|_";
    bool zd = true;
    while(zd){
        ndlPos = hay.find(ndl);
        if(ndlPos != -1)hay.replace(ndlPos,ndl.length(),tmp);else zd = false;
    }
    ndl = tmp;
    zd = true;
    while(zd){
        ndlPos = hay.find(ndl);
        if(ndlPos != -1)hay.replace(ndlPos,ndl.length(),swap);else zd = false;
    }
    return hay;
}

string trim(string str)
{
    int i,j,start,end;

    //ltrim
    for (i=0; (str[i]!=0 && str[i]<=32); )
        i++;
    start=i;

    //rtrim
    for(i=0,j=0; str[i]!=0; i++)
        j = ((str[i]<=32)? j+1 : 0);
    end=i-j;
    str = str.substr(start,end-start);
    return str;
}

string ltrim(string str)
{
    int i,start;

    for (i=0; (str[i]!=0 && str[i]<=32); )
        i++;
    start=i;

    str = str.substr(start,str.length()-start);
    return str;
}

string rtrim(string str)
{
    int i,j,end;

    for(i=0,j=0; str[i]!=0; i++)
        j = ((str[i]<=32)? j+1 : 0);
    end=i-j;

    str = str.substr(0,end);
    return str;
}

string file_get_contents(string ffname){
    struct stat st;
    if(stat("s",&st) != 0)
        return "can't stat "+ffname;
//        return "";

    string data,tmp;
    ifstream disk_file(ffname.c_str());
    if (disk_file.is_open())
    {
        while ( disk_file.good() ){
            getline (disk_file,tmp);
            data += tmp + "\n";
        }
        disk_file.close();
    }else{
        return "can't open "+ffname;
        //return "";
    }
    return data;
}


std::string urlDecode(std::string str)
{
    //cout<<br<<str<<br;
	string temp;
	register int i;
	char tmp[5], tmpchar;
	strcpy(tmp,"0x");
	int size = str.size();
	for (i=0; i<size; i++) {
		if (str[i]=='%') {
			if (i+2<size) {
				tmp[2]=str[i+1];
				tmp[3] = str[i+2];
				tmp[4] = '\0';
				tmpchar = (char)strtol(tmp,NULL,0);
				temp+=tmpchar;
				i += 2;
				continue;
			} else {
				break;
			}
		} else if (str[i]=='+') {
			temp+=' ';
		} else {
			temp+=str[i];
		}
	}
//    cout<<br<<temp<<br;
//    exit(0);
	return temp;
}
#endif// S3C_CGI_HELPERS_H
