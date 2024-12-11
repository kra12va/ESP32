/*

*/

#define DEBUG  // Раскоментировать при отладке
#include "Arduino.h"
#include <WiFi.h>
#include <WiFiAP.h>
#include <ArduinoJson.h>
#include "FS.h"
#include "FFat.h"
#include <TimerMs.h>
// (период, мс), (0 не запущен / 1 запущен), (режим: 0 период / 1 таймер)
TimerMs listen_bnt_tmr(150, 1, 0);


#include <WebServer.h>
WebServer HTTP(80);

#include <SimpleFTPServer.h>
FtpServer ftpSrv;  //set #define FTP_DEBUG in ESP8266FtpServer.h to see ftp verbose on serial

#include <ElegantOTA.h>  // прошивка по воздуху
unsigned long ota_progress_millis = 0; // для обновления по воздуху

#include "libs/configurator.h"




void setup() {

  Serial.begin(115200);
  
  listen_bnt_tmr.start();

  configurator MK;

  // Обработка HTTP-запросов
  HTTP_init();  
  FTP_server_init();
  ElegantOTA_init();
}

void loop() {
  HTTP.handleClient();
  ftpSrv.handleFTP();  //make sure in loop you call handleFTP()!!


}

