#include "utility.h"
#include <Preferences.h>
#include <WiFi.h>


using namespace charno::utility;

String WiFiUtil::ssid = "";
String WiFiUtil::password = "";
int32_t WiFiUtil::channel = 0;
uint8_t WiFiUtil::bssid[6] = {0,0,0,0,0,0};
uint32_t WiFiUtil::wifiTimeoutMillis = 0;
String WiFiUtil::hostname = "";
bool WiFiUtil::staticIp = false;
String WiFiUtil::ip = "";
String WiFiUtil::subnet = "";
String WiFiUtil::gateway = "";
String WiFiUtil::nameserver = "";
bool WiFiUtil::doNtp = false;
String WiFiUtil::ntpserver = "";
const uint8_t WiFiUtil::empty_bssid[6] = {0,0,0,0,0,0};

LogUtil::LogLevel LogUtil::logLevel = LogUtil::LogLevel::DEBUG;

String TimeUtil::timezone = "UTC";

String TimeUtil::getTimeString()
{
    time_t tp = time(nullptr);
    tm timeinfo;
    localtime_r(&tp, &timeinfo);

    char tmbuf[64];
    strftime(tmbuf, sizeof tmbuf, "%A, %B %d %Y %H:%M:%S", &timeinfo);
    return String(tmbuf);
}

void LogUtil::log(String message, String level, bool append){
    if(Serial)
    if(!append) {
        Serial.print("\n[" + TimeUtil::getTimeString() + "] " + level + ": ");
    }
    Serial.print(message);
}

void WiFiUtil::getNtpTime()
{
    LogUtil::info("Get time by NTP: ");
    configTime(0, 0, ntpserver.c_str());
    if(TimeUtil::timezone != "")
    {
        setenv("TZ", TimeUtil::timezone.c_str(), 1);  
        tzset();
    }
    tm timeinfo;
    getLocalTime(&timeinfo);
    LogUtil::info("done: " + TimeUtil::getTimeString(), true);
}

bool WiFiUtil::startWifi()
{
    if(WiFi.status() == WL_CONNECTED)
        return true;

    auto starttime = millis();
    LogUtil::info(String("Connecting to ") + ssid);

    // Set hostname if provided
    if(hostname != "")
    {
        WiFi.setHostname(WiFiUtil::hostname.c_str());
    }

    // Set static IP if provided
    if(staticIp)
    {
        IPAddress _ip; if(!_ip.fromString(ip)) _ip = IPAddress();
        IPAddress _gateway; if(!_ip.fromString(gateway)) _gateway = IPAddress();
        IPAddress _subnet; if(!_subnet.fromString(subnet)) _subnet = IPAddress();
        IPAddress _dns; if(!_dns.fromString(nameserver)) _dns = IPAddress();

        WiFi.config(_ip, _gateway, _subnet, _dns);
    }

    WiFi.begin(ssid.c_str(), password.c_str(), channel, memcmp(bssid, empty_bssid, 6) ? bssid : nullptr);

    while(WiFi.status() != WL_CONNECTED && (starttime + wifiTimeoutMillis > millis() || wifiTimeoutMillis == 0))
    {
        delay(100);
        LogUtil::info(".", true);
    }

    if(WiFi.status() != WL_CONNECTED)
    {
        LogUtil::error("Could not connect to WIFI!");
        WiFi.disconnect();
        return false;
    }
    WiFi.setAutoReconnect(true);

    LogUtil::info(" CONNECTED! IP: ", true);
    LogUtil::info(WiFi.localIP().toString(), true);

    if(doNtp)
    {
        getNtpTime();
    }
    
    return true;
}

bool TimeUtil::returnTrueEveryXSeconds(int32_t seconds)
{
    static unsigned long lastTime = 0;
    unsigned long currentTime = millis();

    if(lastTime + seconds*1000 > currentTime)
    {
        return false;
    }
    else
    {
        lastTime = currentTime;
        return true;
    }
}