/****************************************************************************************************************************
  AsyncDNSServer_ESP32_W6100.h

  For ESP32_W6100 (ESP32 + W6100)

  AsyncDNSServer_ESP32_W6100 is a Async DNS Server library for the ESP32_W6100

  Based on and modified from ESPAsyncDNSServer Library (https://github.com/devyte/ESPAsyncDNSServer)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncDNSServer_ESP32_W6100
  Licensed under GPLv3 license

  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      10/01/2023 Initial coding for ESP32 + LwIP W6100. Sync with AsyncDNSServer_STM32
  *****************************************************************************************************************************/

#pragma once

#ifndef AsyncDNSServer_ESP32_W6100_h
#define AsyncDNSServer_ESP32_W6100_h

////////////////////////////////////////////////

#define ASYNC_DNS_SERVER_ESP32_W6100_VERSION      "AsyncDNSServer_ESP32_W6100 v1.0.0"

////////////////////////////////////////////////

#include <AsyncUDP_ESP32_W6100.h>
#include "AsyncDNSServer_ESP32_W6100_Debug.h"

#define DNS_QR_QUERY 0
#define DNS_QR_RESPONSE 1
#define DNS_OPCODE_QUERY 0

////////////////////////////////////////////////

enum class AsyncDNSReplyCode : unsigned char
{
  NoError = 0,
  FormError = 1,
  ServerFailure = 2,
  NonExistentDomain = 3,
  NotImplemented = 4,
  Refused = 5,
  YXDomain = 6,
  YXRRSet = 7,
  NXRRSet = 8
};

////////////////////////////////////////////////

class AsyncDNSServer
{
  public:
    AsyncDNSServer();
    void setErrorReplyCode(const AsyncDNSReplyCode &replyCode);
    void setTTL(const uint32_t ttl);

    // Returns true if successful, false if there are no sockets available
    bool start(const uint16_t port, const String &domainName, const IPAddress &resolvedIP);

    // stops the DNS server
    void stop();

  private:
    AsyncUDP _udp;
    uint16_t _port;
    String _domainName;
    unsigned char _resolvedIP[4];
    uint32_t _ttl;
    AsyncDNSReplyCode _errorReplyCode;

    void processRequest(AsyncUDPPacket &packet);
    void replyWithIP(AsyncUDPPacket &packet);
    void replyWithCustomCode(AsyncUDPPacket &packet);
};

////////////////////////////////////////////////

#include "AsyncDNSServer_ESP32_W6100_Impl.h"

#endif    // AsyncDNSServer_ESP32_W6100_h
