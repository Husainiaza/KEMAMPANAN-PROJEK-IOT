/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/

//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

#include <WiFi.h>
#include <MQTT.h>
#include <Wire.h>
#include "SparkFun_ENS160.h"

//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

#define relay01     26  // digital OUTPUT - RELAY 1
#define relay02     27  // digital OUTPUT - RELAY 2
#define buzzer      25  // digital OUTPUT - BUZZER
#define SensorDS18  15  // pin ke DS18B20 (ONEWIRE) sensor Suhu
#define sensorLDR   36  // analog INPUT   - Sensor Cahaya
#define sensorTilt  4   // digital Input  - Sensor Tilt
#define SensorVolt  35  // analog INPUT   - Sensor Voltan

// ~~~~~~~~~~~~~~~~~~~~ PENTING ~~~~~~~~~~~~~~~~~~~~~~~~
// ------ Sila edit nama atau ID ikut keperluan --------
#define Client_Id   "id_andaFarhan12344"
#define NamaBroker  "broker.emqx.io"
#define namaSSID    "IoT";
#define SSIDpwd     "iot@kksj2023";
// ~~~~~~~~~~~~~~~~~~~  TAMMAT   ~~~~~~~~~~~~~~~~~~~~~~~

//-----c.  - ISTIHAR  constant dan pembolehubah------------------------------
//---Penetapan nama Pembolehubah yg diumpukkan kepada satu nilai awal  --
const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
unsigned long lastMillis = 0;

//-----d. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

WiFiClient net;
MQTTClient client;
SparkFun_ENS160 myENS; 

int ensStatus; 

//##################  Seksyen 1 - TAMAT #############################
//--------------FUNCTION----------------------------

void connect() {
  Serial.print("sambungan ke wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.print("sambungan WiFi berjaya ..... ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Print the IP address

  Serial.print("sambungan ke broker MQTT : ");
  Serial.println(NamaBroker);

  Serial.print("\nconnecting...");
  while (!client.connect(Client_Id)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe("kksbj/buzzer");
  // -- tambah subcribe disini ---
 
}

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);
   Serial.println(payload);
  
  //==============================================================

  //==========================Relay Control ========================
    
  
  //   ----Tulis Kod Kawalan ( subsribe here ) -------

  //--------------------------- Relay Control --------------------
}

//###################################################
//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT); 
  pinMode(sensorTilt, INPUT);
  Wire.begin();
  Serial.begin(115200); // initialize serial
  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  client.onMessage(messageReceived);
  connect();

  if( !myENS.begin() )
	{
		Serial.println("Could not communicate with the ENS160, check wiring.");
		while(1);
	}

 	// Reset the indoor air quality sensor's settings.
	if( myENS.setOperatingMode(SFE_ENS160_RESET) )
		Serial.println("Ready.");

  	myENS.setOperatingMode(SFE_ENS160_STANDARD);
	ensStatus = myENS.getFlags();
	Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
	Serial.println(ensStatus);
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
  if (millis() - lastMillis > 2000) {
  lastMillis = millis();

  //------SENSOR 1 -------------------------------------------------------------
    if( myENS.checkDataStatus() )
	{
		Serial.print("Air Quality Index (1-5) : ");
		Serial.println(myENS.getAQI());

		Serial.print("Total Volatile Organic Compounds: ");
		Serial.print(myENS.getTVOC());
		Serial.println("ppb");

		Serial.print("CO2 concentration: ");
		Serial.print(myENS.getECO2());
		Serial.println("ppm");

	  Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
    Serial.println(myENS.getFlags());

		Serial.println();

  client.publish("farhan/AQI", String(myENS.getAQI()));  
  client.publish("farhan/TVOC", String(myENS.getTVOC()));
  client.publish("farhan/ECO2", String(myENS.getECO2()));
    
  if (myENS.getAQI() >3){
    digitalWrite(buzzer,HIGH);
  }

  else
    digitalWrite(buzzer,LOW);
 
 //-----------end ----------------------------------
  }
}
}

//##################  Seksyen 3 - TAMAT #############################
