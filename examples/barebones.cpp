///Barebones/jokers example. More serious ones to come soon, i promise!
#include <iostream>
#include <sys/stat.h>

#include <sc3/sc3.h>

int main()
{

    #ifdef __SC3_DEBUG__
        if (!log_file.is_open()){
            HTML_HDR;CLOSE_HDR;
            cout << "<h1 style='color:red'>LOGFILE ISNT OPEN</h1>" << endl;
            exit(0);
        }
    #endif
    //Send text File
    if(ap.Get["call"].c_str() == "TEXT")
    {
        TEXT_HDR
        CLOSE_HDR
        cout << "Hello World!!";
        exit(0);
    }
    
    //Send html File
    if(ap.Get["call"].c_str() == "HTML")
    {
        HTML_HDR;CLOSE_HDR;
        cout << "\
        <html>\
            <head>\
            </head>\
            <body>\
                <h1>HELLO WORLD!</h1>\
            </body>\
        </html>" << endl;
        exit(0);
    }
    
    //Send some Javascript File in CWD (e.g jay-es.js)
    if(ap.Get["call"].c_str() == "JS")
    {
            JS_HDR
            CLOSE_HDR
            string data;
            ifstream script("jay-es.js");
            if (script.is_open())
            {
                while ( script.good() ){
                    getline (script,data);
                    cout << data << endl;
                }
                script.close();
            }
            exit(0);
    }
    
    //Send a blank GIF
    if(ap.Get["call"].c_str() == "BLANK_GIF")
    {
        cout << "Content-disposition: inline; filename=\"blank.wbmp\""<<endl;
        cout << "Content-Type: image/vnd.wap.wbmp";
        cout << "Content-Length: 5";
        CLOSE_HDR
        cout << char(0) << char(0) << char(1) << char(1) << char(128);
        exit(0);
    }
    return 0;
}
