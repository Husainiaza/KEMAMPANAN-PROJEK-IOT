/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/

//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

#include <WiFi.h>
#include <MQTT.h>

//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

//---Actuator and Relay  pin connection---
#define button   5

// ~~~~~~~~~~~~~~~~~~~~ PENTING ~~~~~~~~~~~~~~~~~~~~~~~~

//--- setting broker ----------
// ------ Sila edit nama atau ID ikut keperluan --------
#define Client_Id   "asmahtryiot12345"
#define NamaBroker  "broker.hivemq.com"
#define namaSSID    "IoT";
#define SSIDpwd     "iot@kksj2023";
// ~~~~~~~~~~~~~~~~~~~  TAMMAT   ~~~~~~~~~~~~~~~~~~~~~~~

//-----c.  - ISTIHAR  constant dan pembolehubah------------------------------

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
unsigned long lastMillis = 0;
//---Setting wifi  --
const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

//-----d. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

WiFiClient net;
MQTTClient client;

//##################  Seksyen 1 - TAMAT #############################

//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------

void setup() {
  pinMode(button,INPUT);
  Serial.begin(115200); // initialize serial

  WiFi.begin(ssid, pass);
  client.begin(NamaBroker, net);
  client.onMessage(messageReceived);

  connect();
  
}
//##################  Seksyen 2 - TAMAT #############################

//==============  Seksyen 3 - Fungsi Utama (LOOP) ===================
//-------------------------------------------------------------------
void loop() {

 client.loop();
 delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

// publish a message roughly every second.
  if (millis() - lastMillis > 5000) {
  lastMillis = millis();

    //------SENSOR 1-------------------------------------------------------------
       
  }

}

//##################  Seksyen 3 - TAMAT #############################
