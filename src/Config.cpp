/* Config

*/

/*
 *   Basic EEPROM structure
 *
 *   0-3   : Identifies EEPROM structure
 *            0 => AA
 *            1 => 55
 *            2 => AA
 *            3 => structure version 1-255 (0) if blanked
 *   4-99  : WLAN #1
 * 100-195 : WLAN #2
 * 
 *  Where WLAN:
 *   0 - 31 => SSID
 *  32 - 95 => WPA/2 password
 *  96 - 99 => Dotted quad IP of MQTT server
 * 
 */

/*
void showEeprom(int addr_from, int length){
  Serial.print("Reading EEPROM from ");
  Serial.println(addr_from);
  Serial.print(" for ");
  Serial.println(length);
  Serial.println(" bytes:");
  for (int i = 0; i < 12; ++i) {
    Serial.print(addr_from+i);
    Serial.print(": ");
    Serial.print(EEPROM.read(addr_from+i));
    Serial.print(" ");
    Serial.println(char(EEPROM.read(addr_from+i)));
  }
}

void writeEeprom(unsigned int index, String ssid, String pass, const unsigned int mqttIp[4]){
  unsigned int offset = 4 + (index * 96);
  unsigned int i;

  // Write signature
  EEPROM.write(0,0xAA);
  EEPROM.write(1,0x55);
  EEPROM.write(2,0xAA);
  EEPROM.write(3,0x01);

  // Clear EEPROM for this record/index
  for (int i = 0; i < 100; ++i) {
    EEPROM.write(offset+i, 0);
  }

  EEPROM.commit();

  Serial.println("Writing ESSID to EEPROM...");

  for (i = 0; i < ssid.length(); i++) {
    EEPROM.write(offset + i, ssid[i]);
    //Serial.print("Addr ");
    //Serial.print(offset+i);
    //Serial.print(": ");
    //Serial.println(ssid[i]);
  }
  //Serial.print(offset+i);
  EEPROM.write(offset+i,0);

  Serial.println("Writing Password to EEPROM...");
  for (i = 0; i < pass.length(); ++i) {
    EEPROM.write(offset + 32 + i, pass[i]);
  }
  EEPROM.write(offset+32+i,0);

  Serial.println("Writing MQTT IP to EEPROM...");
  for (i = 0; i < 4; ++i) {
    EEPROM.write(offset + 96 + i, mqttIp[i]);
  }
  EEPROM.write(offset+96+i,0);
  
  EEPROM.commit();
  Serial.println("Write EEPROM done!");
}


oolean Wlan::readWlanConfig(unsigned int index){
  unsigned int offset = 4 + (index * 96);

  Serial.print("Reading config profile #");
  Serial.println(index);

  this->wlanConfig[index].ssid = "";
  this->wlanConfig[index].pass = "";

  //Serial.print("Offset = ");
  //Serial.println(offset);

  //Serial.print("Value of byte 0 for this config is ");
  //Serial.println(EEPROM.read(offset));

  if (EEPROM.read(offset) != 0 && EEPROM.read(offset) != 255 ) {
    for (int i = 0; i < 32; ++i) {
      wlanConfig[index].ssid += char(EEPROM.read(offset + i));
    }
    Serial.print("SSID: ");
    Serial.println(wlanConfig[index].ssid);
    for (int i = 32; i < 96; ++i) {
      wlanConfig[index].pass += char(EEPROM.read(offset + i));
    }
    //Serial.print("Password: ");
    //Serial.println(wlanConfig[index].pass);

    unsigned int a[4];
    for (int i = 0; i < 4; ++i) {
      wlanConfig[index].ipaddr[0] = (uint8_t) char(EEPROM.read(offset + 96 + i));
      a[i] = char(EEPROM.read(offset + 96 + i));
    }
    wlanConfig[index].ipaddr = String(a[0])   +  "." +  String(a[1]) + "." + String(a[2]) + "." + String(a[3]);
    
    return true;
  }else{
    return false;
  }

}
*/
/*
  restoreConfig

  Read network config from EEPROM and 

  returns
  - true if config read
  - false if no config read
*/
/*
unsigned int eepromMapVersion = 0;
boolean Wlan::restoreConfig() {
    Serial.println("Reading EEPROM...");

    Serial.print("Checking for EEPROM map... ");
    if(EEPROM.read(0)==0xAA && EEPROM.read(1)==0x55 && EEPROM.read(2)==0xAA){
      eepromMapVersion = EEPROM.read(3);
      Serial.print("map version ");
      Serial.println(eepromMapVersion);
    }else{
      Serial.print("no map or unknown version");
      return false;
    }

    if(eepromMapVersion > 0){

      for (int i = 0; i < 2; ++i) {
        if(readWlanConfig(i) == true){

         
        }
      }
    }else{
      return false;
    }

    
    return true;
}

*/