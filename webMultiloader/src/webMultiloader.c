#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "template.h"
#include "hb4x.h"
//#include "hb6x.h"
#include "rxtools.h"
#include "cakes.h"


unsigned short CRC16_2(unsigned char *buf, int len); //from http://www.ccontrolsys.com/w/How_to_Compute_the_Modbus_RTU_Message_CRC
int fixCRC(int slotOffset, int dataOffset, int dataLen, int crcOffset);
int writeNickname(char * nick);
int writeFilename(char * filename);

char NICKNAME[100]="DSiNick"; //limit 10 characters
char INSTALLERNAME[100]="code.bin";
const SLOT1=0xCD0;
const SLOT2=0xDD0;
const CODE_SIZE=7020;

int main(int argc, char *argv[]){

    char buf[52];      memset(&buf,0,52);
    char filename[52]; memset(&filename,0,52);
    int redo=1;
    int choice=-1;
    unsigned int msetforboss=0x00276F64; // string pointer gadgets
    unsigned int        mset=0x00276F96;
    unsigned int    custom4x=0x00295E0C;
    //unsigned int    custom6x=0x00295E0C;


    printf("webMultiloader v1.0\n");

    printf("\nMenu-----------------------------");
    printf("\n[1] Gateway   Launcher.dat     4x");
    printf("\n[2] Homebrew  Launcher.dat     4x");
    printf("\n[3] Homebrew  MsetForBoss.dat  4x");
    printf("\n[4] Homebrew  Mset.dat         4x");
    printf("\n[5] HB CFW    rxTools.dat      4x");
    printf("\n[6] Homebrew  -Custom Name-    4x");
    printf("\n[7] HB CFW    Cakes.dat        4x");
    //6x firmwares ommitted :/
    printf("\n[8] Reset     %s",NICKNAME);
    printf("\n[9] Reset     %s",INSTALLERNAME);
    printf("\n---------------------------------\n\n");

    while(redo){


        printf("Please enter menu number 1-8:");
        scanf("%d",&choice);
        redo=0;

        switch(choice){

        case 1:
            writeNickname(NICKNAME);
            break;
        case 2:
            memcpy(&code[SLOT1],&hb4x,0x200);
            writeNickname(NICKNAME);
            break;
        case 3:
            memcpy(&code[SLOT1],&hb4x,0x200);
            memcpy(&code[SLOT1+0x2c],&msetforboss,4);
            writeNickname(NICKNAME);
            break;
        case 4:
            memcpy(&code[SLOT1],&hb4x,0x200);
            memcpy(&code[SLOT1+0x2c],&mset,4);
            writeNickname(NICKNAME);
            break;
        case 5:
            memcpy(&code[SLOT1],&rxtools,0x200);
            memcpy(&code[SLOT1+0x2c],&custom4x,4);
            writeNickname(NICKNAME);
            break;
        case 6:
            printf("Please enter your custom filename.\n(limit 21 characters):");
            scanf("%s",&filename);
            memcpy(&code[SLOT1],&hb4x,0x200);
            memcpy(&code[SLOT1+0x2c],&custom4x,4);
            writeNickname(NICKNAME);
            writeFilename(filename);
            break;
        case 7:
            memcpy(&code[SLOT1],&cakes,0x200);
            memcpy(&code[SLOT1+0x2c],&custom4x,4);
            writeNickname(NICKNAME);
            writeFilename("Cakes.dat");
            break;
            /*        6x no worky, sad panda
        case 6:
            memcpy(&code[SLOT1],&hb6x,0x200);
            writeNickname(NICKNAME);
            break;
        case 7:
            printf("\nPlease enter your custom filename.\n(limit 22 characters):");
			all code except crc16_2 function by zoogie (nobody see this right :p)
			oh the rop stuff in the headers is mostly from various others, wintermute, gateway, drenn, roxas75, etc.
            scanf("%s",&filename);
            memcpy(&code[SLOT1],&hb6x,0x200);
            memcpy(&code[SLOT1+0x2c],&custom6x,4);
            writeNickname(NICKNAME);
            writeFilename(filename);
            break;
            */
        case 8:
            printf("Enter new nickname:");
            scanf("%s",&NICKNAME);
            printf("ok! ");
            redo=1;
            break;
        case 9:
            printf("Enter new loader filename:");
            scanf("%s",&INSTALLERNAME);
            printf("ok! ");
            redo=1;
            break;
        default:
            redo=1;
        }
    }


    fixCRC(SLOT1,0x00,0x70,0x72); //patch those crc's !!
    fixCRC(SLOT1,0x74,0x8A,0xFE);
    fixCRC(SLOT2,0x00,0x70,0x72);
    fixCRC(SLOT2,0x74,0x8A,0xFE);
    //printf("%X",CRC16(&wbuff[0xCD0],0x70));

    FILE *f=fopen(INSTALLERNAME,"wb");
    fwrite(&code,1,CODE_SIZE,f);
    fclose(f);

    printf("\nGenerated '%s',\nEnjoy!",INSTALLERNAME);

return 0;
}
unsigned short CRC16_2(unsigned char *buf, int len)
{

  unsigned short crc = 0xFFFF;
  int pos=0,i=8;

  for (pos = 0; pos < len; pos++)
  {
    crc ^= (unsigned short)buf[pos];  // XOR byte into least sig. byte of crc

    for (i = 8; i != 0; i--) {        // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
                                      // Note, this number has low and high bytes
                                      // swapped, so use it accordingly (or swap bytes)
  return crc;
}


int fixCRC(int slotOffset,int dataOffset, int dataLen, int crcOffset){

    unsigned char wbuff[dataLen];
    unsigned short crc=-1;
    dataOffset+=slotOffset;
    crcOffset+=slotOffset;

    crc=CRC16_2(&code[dataOffset],dataLen);
    memcpy(&code[crcOffset],&crc,2);

    return 0;
}

int writeNickname(char * nick){
    int nameOffset=SLOT2+0x6;
    char nameBuff[20]; memset(&nameBuff,0,20);
    short size=strlen(nick);
    int i=0;

    memcpy(nameBuff,nick,size);

    if(size>10){
        printf("\nThe entered string is longer than 10 character limit.");
        return 1;
    }
    for(i=0;i<20;i+=2){
        code[nameOffset+i]=nameBuff[i/2];
    }
  memcpy(&code[SLOT2+0x1A],&size,2); //fix name length
  return 0;

}

int writeFilename(char * filename){
    int nameOffset=SLOT2+0x1C;
    char nameBuff[52];
    memset(&nameBuff,0,52);
    short size=strlen(filename);
    int i=0;
    strcpy(nameBuff,"YS:/");
    strcat(nameBuff,filename);

    if(size>21){  //need to account for the ys:/ and a null terminator
        printf("\nThe entered filename is longer than 21 character limit.");
        return 1;
    }
    for(i=0;i<52;i+=2){
        code[nameOffset+i]=nameBuff[i/2];
    }
    //memcpy(&code[SLOT2+0x50],&size,2); this ruins the rop hack! :0
  return 0;
    

}
