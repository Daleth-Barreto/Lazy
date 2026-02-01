/*
 * LazyA Runtime - Simple HTTP Client Implementation
 * Using raw sockets for maximum portability
 */

#include "HTTPClient.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <iostream>

namespace lazya {
namespace http {

HTTPClient::HTTPClient() : timeoutSeconds_(30) {}

HTTPClient::~HTTPClient() {}

void HTTPClient::setTimeout(int seconds) {
    timeoutSeconds_ = seconds;
}

std::string HTTPClient::get(const std::string& url) {
    // Simple implementation for localhost:11434 (Ollama)
    // Parse URL to get host and path
    std::string host = "localhost";
    int port = 11434;
    std::string path = "/";
    
    if (url.find("http://localhost:11434") == 0) {
        path = url.substr(22); // Skip "http://localhost:11434"
    }
    
    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return "{\"error\": \"Failed to create socket\"}";
    }
    
    // Set timeout
    struct timeval tv;
    tv.tv_sec = timeoutSeconds_;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    
    // Resolve host
    struct hostent* server = gethostbyname(host.c_str());
    if (!server) {
        close(sock);
        return "{\"error\": \"Host not found\"}";
    }
    
    // Connect
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    memcpy(&addr.sin_addr.s_addr, server->h_addr, server->h_length);
    addr.sin_port = htons(port);
    
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return "{\"error\": \"Connection failed\"}";
    }
    
    // Send request
    std::ostringstream request;
    request << "GET " << path << " HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";
    request << "Connection: close\r\n";
    request << "\r\n";
    
    std::string req_str = request.str();
    send(sock, req_str.c_str(), req_str.length(), 0);
    
    // Read response
    std::string response;
    char buffer[4096];
    ssize_t bytes;
    
    while ((bytes = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        response += buffer;
    }
    
    close(sock);
    
    // Extract body (after \r\n\r\n)
    size_t body_start = response.find("\r\n\r\n");
    if (body_start != std::string::npos) {
        return response.substr(body_start + 4);
    }
    
    return response;
}

std::string HTTPClient::post(const std::string& url, 
                             const std::string& body,
                             const std::map<std::string, std::string>& headers) {
    // Parse URL
    std::string host = "localhost";
    int port = 11434;
    std::string path = "/";
    
    if (url.find("http://localhost:11434") == 0) {
        path = url.substr(22);
    }
    
    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return "{\"error\": \"Failed to create socket\"}";
    }
    
    // Set timeout
    struct timeval tv;
    tv.tv_sec = timeoutSeconds_;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    
    // Resolve and connect
    struct hostent* server = gethostbyname(host.c_str());
    if (!server) {
        close(sock);
        return "{\"error\": \"Host not found\"}";
    }
    
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    memcpy(&addr.sin_addr.s_addr, server->h_addr, server->h_length);
    addr.sin_port = htons(port);
    
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return "{\"error\": \"Connection failed\"}";
    }
    
    // Build request
    std::ostringstream request;
    request << "POST " << path << " HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";
    request << "Content-Type: application/json\r\n";
    request << "Content-Length: " << body.length() << "\r\n";
    
    // Add custom headers
    for (const auto& header : headers) {
        request << header.first << ": " << header.second << "\r\n";
    }
    
    request << "Connection: close\r\n";
    request << "\r\n";
    request << body;
    
    std::string req_str = request.str();
    send(sock, req_str.c_str(), req_str.length(), 0);
    
    // Read response
    std::string response;
    char buffer[4096];
    ssize_t bytes;
    
    while ((bytes = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        response += buffer;
    }
    
    close(sock);
    
    // Extract body
    size_t body_start = response.find("\r\n\r\n");
    if (body_start != std::string::npos) {
        return response.substr(body_start + 4);
    }
    

    return response;
}

} // namespace http
} // namespace lazya

// C interface
extern "C" {
    
char* http_get(const char* url) {
    lazya::http::HTTPClient client;
    std::string result = client.get(url);
    // Note: GET returns raw body, usually JSON API returns JSON object.
    // If we want raw text from a JSON field, that's caller's responsibility usually.
    // But for this demo, assume raw.
    return strdup(result.c_str());
}

char* http_post(const char* url, const char* body, const char* headers_json) {
    lazya::http::HTTPClient client;
    std::map<std::string, std::string> headers;
    // TODO: Parse headers_json if needed
    std::string result = client.post(url, body, headers);
    return strdup(result.c_str());
}

}


