// include this for logging (production logging) and debugging (no production)
//

#include "buildConfig.h"
#include "Mqtt.h"

#ifdef INCLUDE_DEBUG
    #include <RemoteDebug.h>
    extern RemoteDebug Debug;
#endif

class Mlog{
    public:
        enum Level {disabled=0, errors, warning, info, debug, verbose};
        Mlog(void);
        void begin(char *);
        void begin(char *, Mqtt *);
        void log(const char*);
        void log(String);
        void log(Level, String);
        /*void logf(char *str, ...);*/
        void setMqttClient(Mqtt *);
        void startRemoteDebug();
        void handle();
    private:
        char * mqttTopicLog;
        char * deviceId;
        char * generalBuffer;
        Mqtt * mqttClient = 0;
        Level level = warning;
        
};

