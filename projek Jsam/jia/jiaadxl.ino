/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/

//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

#include <WiFi.h>
#include <MQTT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

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
#define Client_Id   "id_anda  jia___"
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
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);


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
 
  Serial.begin(115200); // initialize serial
  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  client.onMessage(messageReceived);
  connect();

   if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

   accel.setRange(ADXL345_RANGE_16_G);
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
  if (millis() - lastMillis > 1000) {
  lastMillis = millis();

  //------SENSOR 1 -------------------------------------------------------------
    
    sensors_event_t event; 
  accel.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");

  client.publish("jia/x", String(event.acceleration.x));  
  client.publish("jia/y", String(event.acceleration.y));
  client.publish("jia/z", String(event.acceleration.z));
 
 //-----------end ----------------------------------
  }
}

//##################  Seksyen 3 - TAMAT #############################

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    "); 
 
  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 "); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 "); 
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 "); 
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 "); 
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 "); 
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 "); 
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 "); 
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 "); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 "); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 "); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 "); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 "); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 "); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 "); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 "); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 "); 
      break;
    default:
      Serial.print  ("???? "); 
      break;
  } 
  Serial.println(" Hz"); 
}

void displayRange(void)
{
  Serial.print ("Range:         +/- ");
 
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 "); 
      break;
    default:
      Serial.print  ("?? "); 
      break;
  } 
  Serial.println(" g"); 
}
