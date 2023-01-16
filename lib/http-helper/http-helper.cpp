#include "http-helper.h"

bool postJson(const char* bearer_token, const char* url, const char* payload){
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
    if(httpResponseCode >= 200 && httpResponseCode < 300)
    {
        return true;
    }
    else{
        return false;
    }    
}

//ValueError: Could not find starting boundary b'--g8keeperzuul'    <<<<< when identical to boundary
//aiohttp.http_exceptions.InvalidHeader: 400, message='Invalid HTTP Header: --------------------------f0cda7068d225627'  <<< when extra "--" added  << required "\r\n\r\n" at end of media_content_id
/*
    This method will to do the same thing as test/upload_doorbell_snapshot.sh
*/
bool postBinary(const char* bearer_token, const char* url, String media_dirs_key, String filename, uint8_t* payload, size_t payload_size){
    
    httpclient.begin(wificlient, url);
    
    httpclient.setAuthorizationType("Bearer");
    httpclient.setAuthorization(bearer_token);

    // https://www.rfc-editor.org/rfc/rfc7578.html
    httpclient.addHeader("Content-Type", "multipart/form-data; boundary=g8keeperzuul");    // boundary prefixed with "--" and post-fixed with "\r\n"    

    // double CRLF necessary after "media_content_id"!
    String multipart_head = "--g8keeperzuul\r\n\
Content-Disposition: form-data; name=\"media_content_id\"\r\n\r\n\
media-source://media_source/"+media_dirs_key+"/.\r\n\
--g8keeperzuul\r\n\
Content-Disposition: form-data; name=\"file\"; filename=\""+filename+"\"\r\n\
Content-Type: image/jpeg\r\n\r\n";
    String multipart_tail = "\r\n--g8keeperzuul--\r\n";
    String postPayload = multipart_head;
    for (size_t n=0; n<payload_size; n=n+1024) {
      if (n+1024 < payload_size) {
        postPayload.concat(payload, 1024);
        payload += 1024;
      }
      else if (payload_size%1024>0) {
        size_t remainder = payload_size%1024;
        postPayload.concat(payload, remainder);
      }
    }   
    postPayload.concat(multipart_tail);    
    //Sprint(postPayload);
    int httpResponseCode = httpclient.POST(postPayload);
    
    if (httpResponseCode>0) {
      Sprint("HTTP Response code: ");
      Sprintln(httpResponseCode);
      String resp = httpclient.getString();
      Sprintln(resp);
    }
    else {
      Sprint("Error code: ");
      Sprintln(httpResponseCode);
    }

    // Free resources
    httpclient.end();
    if(httpResponseCode == 200)
    {
        return true;
    }
    else{
        return false;
    }
}