#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdint.h>

#define PROXY		"127.0.0.1"
#define PROXYPORT	9050
#define USERNAME	"toraliz"
#define REQSIZE		sizeof(struct proxy_request)
#define RESSIZE		sizeof(struct proxy_response)

struct proxy_request {
    uint32_t dstip;           
    uint16_t dstport;         
    uint8_t vn;               
    uint8_t cd;               
    unsigned char userid[8];  
};

typedef struct proxy_request Req;

struct proxy_response {
	uint32_t __;
	uint16_t _;
	uint8_t vn;
	uint8_t cd;
};


typedef struct proxy_response Res;

Req* request(const char*, const int);
int main(int, char**);