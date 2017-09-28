//
//  connect.cpp
//  panel
//

#include "connect.h"

string response;
int bots;



void getbots() {

    string count = post("https://website.com/abc/hub.php?count", "yeet=cunt");
    bots = atoi(count.c_str());
    
}




size_t writedata(void *ptr, size_t size, size_t nmemb, void *stream) {
    unsigned long numbytes = size*nmemb;
    char lastchar = *((char *) ptr + numbytes - 1);
    *((char *) ptr + numbytes - 1) = '\0';
    response.append((char *)ptr);
    response.append(1,lastchar);
    *((char *) ptr + numbytes - 1) = lastchar;
    return size*nmemb;
}

string post(const char* url, const char* postData) {
    
    response = "";
    
    CURL *curl;
    CURLcode curlc;
    curl = curl_easy_init();
    
    if (curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata);
        
        curlc = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
    }
    
    curl_global_cleanup();
    
    //cout << response << endl;
    
    return response;
}

bool cmpstr(string str, string str2) {
    if (str.find(str2) != std::string::npos)
        return true;
    else
        return false;
}
