#include "Particle.h"

#define OT_MASTER_KEY_SIZE 16

#include "ot_api.h"
#include "openthread/dataset.h"


extern "C" {

int8_t    otLinkGetChannel(otInstance *aInstance);
uint16_t  otLinkGetPanId(otInstance *aInstance);         // type otPanId
otMasterKey otThreadGetMasterKey(otInstance *aInstance);
char     *otThreadGetNetworkName(otInstance *aInstance);

};

void loop() {

        otInstance*  ot = ot_get_instance();

        int8_t myChannel = otLinkGetChannel(ot);
        uint16_t myPanID = otLinkGetPanId(ot); // otPanId

        char myPanIDBuff[255];
        snprintf(myPanIDBuff, sizeof(myPanIDBuff), "0x%02X", myPanID); // put hex into myPanIDBuff

// Begin Changes


/*

   uint8_t myMasterKey = otThreadGetMasterKey(ot);
   char myMasterKeyBuff[255];
   snprintf(myMasterKeyBuff, sizeof(myMasterKeyBuff), "%s\0", &myMasterKey);

 */

/*

        uint8_t myMasterKeyPointer= otThreadGetMasterKey(ot);
        const uint8_t *myMasterKey = &myMasterKeyPointer;
        char myMasterKeyBuff[255];

        // MasterKey is an array of 16 bytes (uint8_t)
        // Convert the array to a string of 32 characters hex digits

        for (unsigned i=0; i < sizeof(myMasterKey); i++) {
                snprintf(myMasterKeyBuff, sizeof(myMasterKeyBuff), "%s%02X", myMasterKeyBuff, myMasterKey[i]);
        }

 */


// Next Attempt

        constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
        const otMasterKey pKey = otThreadGetMasterKey(ot);
        const otMasterKey *key = &pKey;
        wchar_t szKey[OT_MASTER_KEY_SIZE * 2 + 1] = { 0 };
        for (uint8_t i = 0; i < OT_MASTER_KEY_SIZE; i++)
        {
                szKey[2 * i]     = hexmap[(key->m8[i] & 0xF0) >> 4];
                szKey[2 * i + 1] = hexmap[key->m8[i] & 0x0F];
        }


        char myMasterKeyBuff[255];
        wcstombs(myMasterKeyBuff, szKey, sizeof(myMasterKeyBuff));

// End changes

        char *myNetworkName = otThreadGetNetworkName(ot);
        char myNetworkNameBuff[255];
        snprintf(myNetworkNameBuff, sizeof(myNetworkNameBuff), "%s", myNetworkName); // network name as a string


        Particle.publish("----------------","-------------", 60, PRIVATE); // just to show a space between samples
        delay(2000);
        Particle.publish("Particle Thread ","Connection Information", 60, PRIVATE); // just to show a space between samples
        delay(2000);
        Particle.publish("My Channel: ", String(myChannel), 60, PRIVATE); //shows printing an integer variable

        delay(2000);
        Particle.publish("Argon Pan ID: ", String(myPanIDBuff), 60, PRIVATE); //shows printing an integer variable
        delay(2000);

        Particle.publish("My Master Key: ", String(myMasterKeyBuff), 60, PRIVATE); //shows printing an integer variable
        delay(2000);
        Particle.publish("My Network Name: ", String(myNetworkNameBuff), 60, PRIVATE); //shows printing an integer variable
        delay(2000);
        Particle.publish("----------------","-------------", 60, PRIVATE); // just to show a space between samples
        delay(2000);
        Particle.publish("Generates the same info","every 60 seconds", 60, PRIVATE); // just to show a space between samples

        delay(60000); // wait 60 seconds before re-print
}
