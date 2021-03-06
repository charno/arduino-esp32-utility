#pragma once
#include <Arduino.h>

namespace charno 
{ 
    namespace utility 
    {

        class ArduinoOTAUtil
        {
            public:
                static void setupArduinoOTA();
                static void otaLoopHandler();


        };

        class TimeUtil
        {
            public:

                class TickGenerator
                {
                        unsigned long lastTime = 0;
                        unsigned long tickMillis;
                    public:
                        TickGenerator(unsigned long tickMillis) : tickMillis(tickMillis) {}
                        bool checkTick();
                };

                /**
                 * See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for timezones
                 */
                static String timezone;


                static String getTimeString();

        };

        class LogUtil
        {
            public:
                enum LogLevel
                {
                    TRACE = 0,
                    DEBUG = 1,
                    INFO = 2,
                    WARN = 3,
                    ERROR = 4,
                    NONE = 5,
                };

                static LogLevel logLevel;
                static String udpHost;
                static uint16_t udpPort;

            private:
                static void log(String message, String level, bool append);

            public:
                static void trace(String message, bool append = false)
                {
                    if(logLevel <= LogLevel::TRACE) log(message, "TRACE", append);
                }

                static void debug(String message, bool append = false)
                {
                    if(logLevel <= LogLevel::DEBUG) log(message, "DEBUG", append);
                }

                static void info(String message, bool append = false)
                {
                    if(logLevel <= LogLevel::INFO) log(message, " INFO", append);
                }

                static void warn(String message, bool append = false)
                {
                    if(logLevel <= LogLevel::WARN) log(message, " WARN", append);
                }

                static void error(String message, bool append = false)
                {
                    if(logLevel <= LogLevel::ERROR) log(message, "ERROR", append);
                }

        }; // class Logger

        class WiFiUtil
        {
            public:
                // Mandatory WiFi settings
                static String ssid;
                static String password;

                // Optional WiFi settings
                static int32_t channel;
                static uint8_t bssid[6];
                static uint32_t wifiTimeoutMillis;

                // Hostname settings
                static String hostname;

                // Static IP settings
                static bool staticIp;
                static String ip;
                static String subnet;
                static String gateway;
                static String nameserver;

                // ntp settings
                static bool doNtp;
                static String ntpserver;
                


            private:

                static const uint8_t empty_bssid[];

                static void getNtpTime();

            public:
                static bool writeSettingsToFlash();

                static bool readSettingsFromFlash();

                static bool startWifi();

                static bool isConnected();
        }; // class WiFiUtil

    } // namespace utility
} // namespace charno