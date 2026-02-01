/*
 * LazyA Runtime - Simple HTTP Client
 * Minimal HTTP client for AI API calls
 */

#ifndef LAZY_HTTP_CLIENT_H
#define LAZY_HTTP_CLIENT_H

#include <string>
#include <map>

namespace lazya {
namespace http {

class HTTPClient {
public:
    HTTPClient();
    ~HTTPClient();
    
    // Simple GET request
    std::string get(const std::string& url);
    
    // POST request with JSON body
    std::string post(const std::string& url, 
                     const std::string& body,
                     const std::map<std::string, std::string>& headers = {});
    
    // Set timeout in seconds
    void setTimeout(int seconds);
    
private:
    int timeoutSeconds_;
};

} // namespace http
} // namespace lazya

// C interface for LazyA runtime
extern "C" {
    char* http_get(const char* url);
    char* http_post(const char* url, const char* body, const char* headers_json);
}

#endif // LAZY_HTTP_CLIENT_H
