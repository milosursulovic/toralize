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

struct proxy_request
{
	uint8_t vn;
	uint8_t cd;
	uint16_t dstport;
	uint32_t dstip;
	unsigned char userid[8];
};

typedef struct proxy_request Req;

struct proxy_response
{
	uint8_t vn;
	uint8_t cd;
	uint16_t _;
	uint32_t __;
};

typedef struct proxy_response Res;