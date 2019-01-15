#include "Particle.h"

#include "ot_api.h"
extern "C" {

    int8_t    otLinkGetChannel(otInstance *aInstance);
    uint16_t  otLinkGetPanId(otInstance *aInstance);     // type otPanId
    uint8_t   otThreadGetMasterKey(otInstance *aInstance);
    char     *otThreadGetNetworkName(otInstance *aInstance);

};


void loop() {

   int8_t myChannel = otLinkGetChannel(0);
   uint16_t myPanID = otLinkGetPanId(0);    // otPanId

   char myPanIDBuff[255];
   snprintf(myPanIDBuff, sizeof(myPanIDBuff), "0x%X", myPanID);   // put hex into myPanIDBuff

   uint8_t myMasterKey = otThreadGetMasterKey(0);
   char *myNetworkName = otThreadGetNetworkName(0);


   char myNetworkNameBuff[255];
   snprintf(myNetworkNameBuff, sizeof(myNetworkNameBuff), "%s", myNetworkName);   // network name as a string


   Particle.publish("----------------","-------------", 60, PRIVATE);    // just to show a space between samples
   delay(2000);
   Particle.publish("Particle Thread ","Connection Information", 60, PRIVATE);    // just to show a space between samples
   delay(2000);
   Particle.publish("My Channel: ", String(myChannel), 60, PRIVATE);  //shows printing an integer variable

   delay(2000);
   Particle.publish("Argon Pan ID: ", String(myPanIDBuff), 60, PRIVATE);  //shows printing an integer variable
   delay(2000);

   Particle.publish("My Master Key: ", String(myMasterKey), 60, PRIVATE);  //shows printing an integer variable
   delay(2000);
   Particle.publish("My Network Name: ", String(myNetworkNameBuff), 60, PRIVATE);  //shows printing an integer variable
   delay(2000);
   Particle.publish("----------------","-------------", 60, PRIVATE);    // just to show a space between samples
   delay(2000);
   Particle.publish("Generates the same info","every 60 seconds", 60, PRIVATE);    // just to show a space between samples

   delay(60000);  // wait 60 seconds before re-print
}
