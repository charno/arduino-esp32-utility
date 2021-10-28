#pragma once
#include <Arduino.h>

namespace charno 
{ 
    namespace utility 
    {

        class TimeUtil
        {
            public:

                /**
                 * See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for timezones
                 */
                static String timezone;


                static String getTimeString();

                bool returnTrueEveryXSeconds(int32_t seconds);
        };

        class LogUtil
        {
            public:
                enum LogLevel
                {
                    DEBUG = 0,
                    INFO = 1,
                    WARN = 2,
                    ERROR = 3,
                    NONE = 4,
                };

                static LogLevel logLevel;

            private:
                static void log(String message, String level, bool append);

            public:
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

        }; // class WiFiUtil

    } // namespace utility
} // namespace charno