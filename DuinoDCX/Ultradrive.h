#ifndef ULTRADRIVE_H_
#define ULTRADRIVE_H_

#ifndef MAX_DEVICES
#define MAX_DEVICES 16
#endif

#ifndef PING_INTEVAL
#define PING_INTEVAL 1000
#endif

#ifndef TIMEOUT_TIME
#define TIMEOUT_TIME 20000
#endif

#ifndef SEARCH_INTEVAL
#define SEARCH_INTEVAL 5000
#endif

#ifndef RESYNC_INTEVAL
#define RESYNC_INTEVAL 5000
#endif

#define SEARCH_RESPONSE_LENGTH 26
#define PING_RESPONSE_LENGTH 25
#define PART_0_LENGTH 1015
#define PART_1_LENGTH 911

#define SEARCH_RESPONSE 0
#define PING_RESPONSE 4
#define DUMP_RESPONSE 16
#define DIRECT_COMMAND 32

#define ID_BYTE 4
#define COMMAND_BYTE 6
#define PARAM_COUNT_BYTE 7
#define CHANNEL_BYTE 8
#define PARAM_BYTE 9
#define DUMP_PART_BYTE 9
#define VALUE_HI_BYTE 10
#define VALUE_LOW_BYTE 11
#define PART_BYTE 12

#define COMMAND_START 240
#define TERMINATOR 247

#include <Arduino.h>
#include <Stream.h>
#include "aWOT.h"

struct HighByte {
  int part;
  int byte;
};

struct MiddleBit {
  int part;
  int byte;
  int index;
};

struct LowByte {
  int part;
  int byte;
};

struct DataLocation {
  LowByte low;
  MiddleBit middle;
  HighByte high;
};

class Ultradrive {
    struct Device {
      unsigned long lastResponse;
      byte response[SEARCH_RESPONSE_LENGTH];
    } devices[MAX_DEVICES];

  public:
    Ultradrive(HardwareSerial *serial, int rtsPin = 0, int ctsPin = 0);
    void enableFlowControl(bool enabled);
    void processIncoming(unsigned long now);
    void processOutgoing(Request* req);
    void writeDevice(Response* res);
    void writeDeviceStatus(Response* res);
    void writeDevices(Response* res);
    void setSelected(int deviceId);
    int getSelected();

  private:
    size_t write(const uint8_t *buffer, size_t size);
    bool requestToSend(int timeout);
    void endSend();
    void search();
    void setTransmitMode(int deviceId);
    void ping(int deviceId);
    void dump(int deviceId, int part);
    void readCommands(unsigned long now);
    void patchBuffer(int low, int high, DataLocation l);
    
    bool invalidateSync;
    byte dump0[PART_0_LENGTH];
    byte dump1[PART_1_LENGTH];
    byte pingResponse[PING_RESPONSE_LENGTH];
    unsigned long lastResync;
    unsigned long lastPing;
    int selectedDevice;

    HardwareSerial *serial;
    int rtsPin;
    int ctsPin;

    bool isFirstRun;
    bool flowControl;
    bool readingCommand;
    int serialRead;

    unsigned long lastSearch;
    unsigned long lastReconnect;

    byte serialBuffer[PART_0_LENGTH];
    byte serverBuffer[PART_0_LENGTH];

    static DataLocation setupLocations[22];
    static DataLocation inputLocations[4][62];
    static DataLocation outputLocations[6][74];

    static byte vendorHeader[5];
};

#endif
