// include this for logging (production logging) and debugging (no production)
//

#define mlVerbose 5 
#define mlDebug 4
#define mlInfo 3
#define mlWarning 2
#define mlErrors 1

#include "buildConfig.h"
#include "coreDebug.h"

#include <Arduino.h>
#include "Mlog.h"

#include <PubSubClient.h> // need mqtt header
#include "wlan.h"         // defines ConnectedStatus enum
//#include "SoftwareSerial.h"


//#if DEBUG_USE_SOFTSERIAL == 1
//extern SoftwareSerial swSer1;
//#endif

#ifdef INCLUDE_DEBUG
  RemoteDebug Debug;
#endif

//#include "globals.h"

//
// Mlog - log to mqtt
//
// Send log message (to mqtt) - allowing the node to log events remotely
// in a 'syslog' type way (albeit to mqtt)
//
// Mlog requires a String contain the log message to be sent
//
// Mlog also sends the message to serial/remote console for debugging purposes
// is flags for this are enabled.
//

// Define template for logging topic. Simple sprintf substitution
const char *mqttTopicLogTemplate = "device/%s/log";

Mlog::Mlog(void){
    this->generalBuffer = new char[48];
}

void Mlog::begin(char * deviceIdPtr){
    this->begin(deviceIdPtr,0);
}

void Mlog::startRemoteDebug(){
    // Initialize RemoteDebug
#ifdef INCLUDE_DEBUG
	Debug.begin("RemoteDebug"); // Initialize the WiFi server

    Debug.setResetCmdEnabled(true); // Enable the reset command

	Debug.showProfiler(true); // Profiler (Good to measure times, to optimize codes)
	Debug.showColors(true); // Colors

    this->log("RemoteDebug started");
#endif
    // End off setup
}

void Mlog::begin(char * deviceIdPtr, Mqtt * mqttClientPtr){
    this->deviceId = deviceIdPtr;
    this->setMqttClient(mqttClientPtr);

    // Build a cstring with the logging topic
    this->mqttTopicLog = (char *)malloc(strlen(mqttTopicLogTemplate) + 7);
    sprintf(mqttTopicLog, mqttTopicLogTemplate, deviceId);

    // Send an initial log
    sprintf(generalBuffer,"%s - Starting mLog", this->deviceId);
    this->log(generalBuffer);
}

void Mlog::setMqttClient(Mqtt * mqttClientPtr){
    this->mqttClient = mqttClientPtr;
}


void Mlog::log(const char *msg)
{
    char *msgBuffer = NULL;
    //#ifdef INCLUDE_DEBUG
    //  if((state == CONNECTED)||(enableDebug)){
    //#else
    //  if(state == CONNECTED){
    //#endif
    const char *msgTemplate = "[%d] %s";
    msgBuffer = (char *)malloc(strlen(msg) + 14);
    sprintf(msgBuffer, msgTemplate, millis(), msg);

    #ifdef INCLUDE_DEBUG
        if (this->mqttClient){
            this->mqttClient->publish(mqttTopicLog, msgBuffer);
        }

        SER.print("[NO RMDBG] ");
        SER.println(msgBuffer);

        debugV("%s", msgBuffer);
    #endif
    if (msgBuffer)
    {
        free(msgBuffer);
    }
}

// Overloaded variant to support use of Arduino String
void Mlog::log(String msg)
{
    this->log(msg.c_str());
}

// Overloadedd variant to support setting message levels
void Mlog::log(Level msgLevel, String msg)
{
    if(msgLevel <= this->level){
        this->log(msg.c_str());
    }
}
/*
void Mlog::log(char *str, ...)
{
  int i, count=0, j=0, flag=0;
  char temp[ARDBUFFER+1];
  for(i=0; str[i]!='\0';i++)  if(str[i]=='%')  count++;

  va_list argv;
  va_start(argv, count);
  for(i=0,j=0; str[i]!='\0';i++)
  {
    if(str[i]=='%')
    {
      temp[j] = '\0';
      Serial.print(temp);
      j=0;
      temp[0] = '\0';

      switch(str[++i])
      {
        case 'd': Serial.print(va_arg(argv, int));
                  break;
        case 'l': Serial.print(va_arg(argv, long));
                  break;
        case 'f': Serial.print(va_arg(argv, double));
                  break;
        case 'c': Serial.print((char)va_arg(argv, int));
                  break;
        case 's': Serial.print(va_arg(argv, char *));
                  break;
        default:  ;
      };
    }
    else 
    {
      temp[j] = str[i];
      j = (j+1)%ARDBUFFER;
      if(j==0) 
      {
        temp[ARDBUFFER] = '\0';
        Serial.print(temp);
        temp[0]='\0';
      }
    }
  };
  Serial.println();
  return count + 1;
}
*/


void Mlog::handle(){
#ifdef INCLUDE_DEBUG
    Debug.handle();
#endif
}