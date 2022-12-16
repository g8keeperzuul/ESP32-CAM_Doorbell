#include "http-helper.h"

int postJson(const char* bearer_token, const char* url, const char* payload){
    httpclient.begin(wificlient, url);

    httpclient.setAuthorizationType("Bearer");
    httpclient.setAuthorization(bearer_token); // assumed to be b64 encoded

    httpclient.addHeader("Content-Type", "application/json");    

    int httpResponseCode = httpclient.POST(payload);    
    if(httpResponseCode>0) {
      Sprint("HTTP Response code: ");
      Sprintln(httpResponseCode);
      String payload = httpclient.getString();
      Sprintln(payload);
    }
    else {
      Sprint("Error code: ");
      Sprintln(httpResponseCode);
    }  

    httpclient.end();
    return httpResponseCode;
}

/*
    This method will to do the same thing as test/upload_doorbell_snapshot.sh
*/
int postBinary(const char* bearer_token, const char* url, uint8_t* payload, size_t payload_size){
    
    httpclient.begin(wificlient, url);
    
    httpclient.setAuthorizationType("Bearer");
    httpclient.setAuthorization(bearer_token);
    
    httpclient.addHeader("Content-Type", "multipart/form-data; boundary=g8keeperzuul");

    String head = "--g8keeperzuul\r\nContent-Disposition: form-data; media_content_id=\"media-source://media_source/doorbell/.\"; file=\"doorbell_yyyymmddThhmmss.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String tail = "\r\n--g8keeperzuul--\r\n";
    String postPayload = head;
    for (size_t n=0; n<payload_size; n=n+1024) {
      if (n+1024 < payload_size) {
        postPayload = postPayload.concat(payload, 1024);
        payload += 1024;
      }
      else if (payload_size%1024>0) {
        size_t remainder = payload_size%1024;
        postPayload = postPayload.concat(payload, remainder);
      }
    }   
    postPayload = postPayload.concat(tail);    
    
    int httpResponseCode = httpclient.POST(postPayload);
    
    if (httpResponseCode>0) {
      Sprint("HTTP Response code: ");
      Sprintln(httpResponseCode);
      String payload = httpclient.getString();
      Sprintln(payload);
    }
    else {
      Sprint("Error code: ");
      Sprintln(httpResponseCode);
    }

    // Free resources
    httpclient.end();
    return httpResponseCode;
}