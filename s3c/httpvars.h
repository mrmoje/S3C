///  Project : S3C CGI
///  File Name : httpvars.h
///  Date :
///  Author : James Nzomo

/*****************************************************************************
The MIT License

Copyright (c) 2007 Guy Rutenberg
Modified by James Nzomo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*****************************************************************************/

#ifndef S3C_CGI_HTTPVARS_H
#define S3C_CGI_HTTPVARS_H

#include "defs.h"

void initGet(lkupMap &Get)
{
	std::string tmpkey, tmpvalue;
	std::string *tmpstr = &tmpkey;
	register char* raw_get = getenv("QUERY_STRING");
	if (raw_get==NULL) {
		Get.clear();
		return;
	}
	while (*raw_get != '\0') {
		if (*raw_get=='&') {
			if (tmpkey!="") {
				Get[urlDecode(tmpkey)] = urlDecode(tmpvalue);
			}
			tmpkey.clear();
			tmpvalue.clear();
			tmpstr = &tmpkey;
		} else if (*raw_get=='=') {
			tmpstr = &tmpvalue;
		} else {
			(*tmpstr) += (*raw_get);
		}
		raw_get++;
	}
	//enter the last pair to the map
	if (tmpkey!="") {
		Get[urlDecode(tmpkey)] = urlDecode(tmpvalue);
		tmpkey.clear();
		tmpvalue.clear();
	}
//    dbg
//    for(lkupMap::const_iterator it = Post.begin(); it != Post.end(); ++it)
//    cout << it->first << '=' << it->second << ';';
//    exit(0);
}

void initPost(lkupMap &Post)
{
    std::string tmpkey, tmpvalue;
	std::string *tmpstr = &tmpkey;

    char* clen = getenv("CONTENT_LENGTH");

    if(clen == NULL){
        Post.clear();
        return;
    }

    char* raw_get;

    int len = atoi(clen);

    raw_get = (char*)malloc((size_t)len+1);  // allocate a buffer
    memset(raw_get, 0, (size_t)len+1);  // zero it out

    fread(raw_get,1,(size_t)len,stdin);  // get data

	if (raw_get==NULL) {
		Post.clear();
		return;
	}
	while (*raw_get != '\0') {
		if (*raw_get=='&') {
			if (tmpkey!="") {
				Post[urlDecode(tmpkey)] = urlDecode(tmpvalue);
			}
			tmpkey.clear();
			tmpvalue.clear();
			tmpstr = &tmpkey;
		} else if (*raw_get=='=') {
			tmpstr = &tmpvalue;
		} else {
			(*tmpstr) += (*raw_get);
		}
		raw_get++;
	}
	//enter the last pair to the map
	if (tmpkey!="") {
		Post[urlDecode(tmpkey)] = urlDecode(tmpvalue);
		tmpkey.clear();
		tmpvalue.clear();
	}
//    dbg
//    for(lkupMap::const_iterator it = Post.begin(); it != Post.end(); ++it)
//    cout << it->first << '=' << it->second << ';';
//    exit(0);
}

#endif //S3C_CGI_HTTPVARS_H
