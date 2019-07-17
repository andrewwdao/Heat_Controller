/*------------------------------------------------------------*-
  Module SD card reader - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.00 - 15/02/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RFID125_init();
 *  bool hasID();  //check if there is any new ID by interrupt
 *  void RFID125_interrupt();
 *   
 *  PRIVATE FUNCTIONS CONTAIN:
 *  void GetID();
 *  long hexstr_to_value(unsigned char *str, unsigned int str_length);
 * 
 **** NOTE: - ESP32 DEVKIT V1 cannot use MMC bus to communicate with SD card
 *        even though MMC is faster than SPI
 *          - recursive functions must not have variable declaration
 * 
 * Connect the pure SD card to the following pins (SPI):
 *   SD Card | ESP32
 *    D2       -
 *    D3       SS - D5
 *    CMD      MOSI - D23
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK - D18
 *    VSS      GND
 *    D0       MISO - D19
 *    D1       -
 * 
 * Connect SD card module to the following pins (SPI):
 *   SD Card | ESP32
 *    CS       D5
 *    CLK      D18
 *    MOSI     D23
 *    MISO     D19
 *    VCC      5V  (Cannot use 3.3V because it has a 3.3V power regulator inside)
 *    GND      GND
 * 
 *  - Make long filename in SD card:
 *    make menuconfig --> Components config --> FAT filesystem support --> Long filename support in heap
 *  --> Current setting: short filename (<=8 characters) - a 8.3 filename 
 *  --> in a 8.3 filename system, file and directory names are uppercase!
 *  readmore: https://en.m.wikipedia.org/wiki/8.3_filename
 * 
 *  CAUTION:
 *   + in Windows (and many old OSs), the code for end of line is 2 characters, \r\n, in this order
 * 
 --------------------------------------------------------------*/
#ifndef _C1_SD_CARD_CPP
#define _C1_SD_CARD_CPP
#include "C1_SD_Card.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
//static void SD_updateDatabase(String);
static void SD_saveClass(String,String);
static bool SD_ACheck_save(String,String);
static void SD_renameFile(String,String);
// ------ Private variables -----------------------------------
static boolean SDfailed=false;

struct SDbuffer {
    String name;
    String mssv;
    String RFID;
    String Class;
};
typedef struct SDbuffer SDbuffer;
// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void SD_init() {
    SD.end();
    if(!SD.begin()){
        S_PRINTLN(F("SD failed to initialize!"));
        oled_SD_failed();
        SDfailed=true;
        while (!SW_midPressed());
        ESP.restart(); //do not allow program proceed if SD card is broken
        return;
    }//end if
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        S_PRINTLN(F("No SD card attached!"));
        oled_SD_failed();
        SDfailed=true;
        while (!SW_midPressed());
        ESP.restart(); //do not allow program proceed if SD card is broken
        return;
    } else {
        S_PRINT(F("SD Card connected! "));
        if ((cardType != CARD_MMC)&&
            (cardType != CARD_SD )&&
            (cardType != CARD_SDHC)) {
                S_PRINTLN(F("UNKNOWN Type! Please try other card"));
                oled_SD_failed();
                SDfailed=true;
                while (!SW_midPressed());
                ESP.restart(); //do not allow program proceed if SD card is broken
                return;
        }//end if
        #ifdef ESP32_DEBUG
        if(cardType == CARD_MMC){
            Serial.println(F("MMC Type"));
        } else if(cardType == CARD_SD){
            Serial.println(F("SDSC Type"));
        } else if(cardType == CARD_SDHC){
            Serial.println(F("SDHC Type"));
        }//end if else
        uint64_t cardSize = SD.cardSize() / (1024 * 1024);
        Serial.printf("SD Card Size: %lluMB\n", cardSize);
        #endif
        S_PRINTLN();
    }//end if else
}//end SD_init
//------------------------------- MODE 1: ATTENDANCE CHECKING ------------------------------
//------------------------------------------------------------------------------------------
//number of class, string array hold classes, mode location
void SD_getClass(String* cl, char* Cnum, String Cdir) {//RESTRICTED CLASSES BY MAX_CLASSES CONSTANT
    SD_init();
    if (SDfailed) {return;} //needed for every "make" function
    /////////////////////////////////////////////////
    File SD_classFile = SD.open(Cdir+"CLASSES.TXT", FILE_READ);
    if((!SD_classFile)&&(SD_classFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return;
    }//end if
    SD_classFile.seek(0); //point to the position of the first class in the file
    if (!SD_classFile.available()) {//if there is nothing in the file
        SD_classFile.close();
        return;
    }//end if
    *Cnum = 0; //have to be reset here!
    //RETURN CLASSES TO THE CORESPOND POINTER
    String classBuffer="";
    while(SD_classFile.available()){
        char SDtemp = SD_classFile.read();
        if (SDtemp =='\n') {//in Windows (and many old OSs), the code for end of line is 2 characters, \r\n, in this order
            *(cl+*Cnum) = classBuffer;
            classBuffer="";
            if (++(*Cnum)==MAX_CLASSES) {
                SD_classFile.close();
                return;
            }//end if
        } else if (SDtemp =='\r') { //safety method for \r\n of Windows-edited files
        } else { //end of a line
            classBuffer += SDtemp;
        }//end if else
    }//end while
    SD_classFile.close();
    return;
}//end SD_getClass
void SD_ACheck_make(String* SClass,char* NumClass, char ClassNum) {//string array hold classes, number of class, class number being chosen
    //*NumClass exists just for fun! (actually for compatible with delete function)
    oled_clear();
    File SD_chosenFile = SD.open(ACHECK_LOCATION+*(SClass+ClassNum)+".txt", FILE_READ);
    if((!SD_chosenFile)&&(SD_chosenFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return;
    }//end if
    if (!SD_chosenFile.available()) {//if there is nothing in the file
        SD_chosenFile.close();
        return;
    }//end if
    
    int numStu = (SD_chosenFile.size())/37;//total 11(67003FCA88|) + 9(B1509360|) + 15(name) +2(\r\n) = 37;
    
    //CHECK ATTENDANCE:
    String IDBuffer[numStu];
    int   IDprotect[numStu];
    SD_chosenFile.seek(0); //point to the position of the first class in the file
    while (SD_chosenFile.available()) { //for guarantee
        for (int numID=0;numID<numStu;numID++) {
            for (char Sadd=0;Sadd<10;Sadd++) { //10 first characters
                *(IDBuffer+numID) +=(char)SD_chosenFile.read();
            }//end for
            SD_chosenFile.seek((numID+1)*37); //point to the next row
        }//end for
    }//end while
    //now we have ID stored in IDBuffer
    int numStuLeft=numStu;
    while (numStuLeft) {
        oled_Acheck_make();//show waiting screen, no oled.display
        ID_PROTECTOR:
        oled_Acheck_remain(numStuLeft);//with number of students left
        ///////////////////////RFID PART ///////////////////////////
        while (1) {//check if ID is available
            if (hasID())       break; //continue the process
            if (SW_midPressed()) return;//cancel the process
        } //end while
        String StudentID = getID();
        singleBeep(100);
        ////////////////////////////////////////////////////////////
        for (int numID=0;numID<numStu;numID++) {
            if (StudentID == *(IDBuffer+numID)) {
                
                for (int Ifor=0;Ifor<(numStu-numStuLeft);Ifor++) {
                    if (IDprotect[Ifor]==numID) {
                        oled_Acheck_coincide();
                        delay(1500);
                        goto ID_PROTECTOR;
                    }//end if
                }//end for
                IDprotect[numStu-numStuLeft]=numID;//save pointer to compare later with other IDs
                
                SD_chosenFile.seek(numID*37+11); //point to the beginning of this row, omit the ID
                String StudentID, StudentName;
                for (char Sadd=0;Sadd<8;Sadd++) { //8 characters of MSSV
                    StudentID +=(char)SD_chosenFile.read();
                }//end for
                SD_chosenFile.read(); //omit the | character 
                for (char Sadd=0;Sadd<15;Sadd++) { //15 characters of name
                    StudentName +=(char)SD_chosenFile.read();
                }//end for
                oled_Acheck_makeDone(StudentName,StudentID);

                if (SD_ACheck_save(StudentID,*(SClass+ClassNum))) { //FUNCTION TO SAVE ID TO SDCARD!!! here
                    numStuLeft--; //one student is checked
                    //do sth else
                }//end if
                delay(1500);
                break;
            }//end if
        }//end for
    }//end while
    SD_chosenFile.close(); //done
    oled_ACheck_done();
    while (!SW_midPressed());
    return;
}//end SD_ACheck_make
static bool SD_ACheck_save(String StuID,String StuClass) {
    File SD_dataFile = SD.open(AWAIT_LOCATION+"DATA.TXT", FILE_APPEND);
    if((!SD_dataFile)&&(SD_dataFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return false;
    }//end if
    if ((SD_dataFile.print(StuID))   && //name of the class is store in CLASSES.TXT
        (SD_dataFile.print('|'))     &&
        (SD_dataFile.print(StuClass))&&
        (SD_dataFile.print('|'))     &&
        (SD_dataFile.print(RTC_getDay()))&&
        (SD_dataFile.print("\r\n"))) 
    {
        oled_Acheck_saved();S_PRINTLN(F("Saved!"));
        SD_dataFile.close();
        return true;
    } else {
        oled_Acheck_failed();S_PRINTLN(F("Failed!"));
        SD_dataFile.close();
        return false;
    }//end if else   
    return false;
}//end SD_ACheck_save
void SD_deleteClass(String* SClass, char* NumClass, char ClassNum, String Ddir) {
    SD_deleteFile(Ddir+"classes.txt"); //Delete file classes.txt
    SD_deleteFile(Ddir+*(SClass+ClassNum)+".txt"); //Delete file classes.txt

    File SD_classFile = SD.open(Ddir+"classes.txt", FILE_APPEND);//create a blank file
    if((!SD_classFile)&&(SD_classFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return;
    }//end if
    for (char adel=0;adel<(*NumClass);adel++) {
        if (adel!=ClassNum) {
            SD_classFile.print(*(SClass+adel));
            SD_classFile.print("\r\n");
        }//end if
    }//end for
    SD_classFile.close();
    return;   
}//end SD_ACheck_deleteClass
void SD_deleteAllClass(String Ddir) {
    String Class[MAX_CLASSES];
    for (char adel=0;adel<MAX_CLASSES;adel++){
        *(Class+adel)=VOID;
    }//end for
    char* numClass=(char*)malloc(1);
    SD_getClass(Class, numClass, Ddir);//string array hold classes, number of class, mode location
    SD_deleteFile(Ddir+"classes.txt"); //Delete file classes.txt
    SD.open(Ddir+"classes.txt", FILE_APPEND);//create a blank file
    for (char adel=0;adel<(*numClass);adel++) { //delete all database files
        SD_deleteFile(Ddir+*(Class+adel)+".txt");
    }//end for
    free(numClass);
    return;
}//end DeleteAllClass

//------------------------------- MODE 2: GET RFID INFO ------------------------------------
//------------------------------------------------------------------------------------------
void SD_updateDatabase(String* DClass, 
                       char* NumClass, 
                       char Dnum) 
{//recursive functions must not have declare
    oled_getRFID_init();
    SDbuffer buf;
    buf.Class=*(DClass+Dnum);

    File SD_File;
    int numOfStu=0;//real number of students in the file
    int stuDone=0; //number of students that have been added
    int stuDis=0; //number of students of the class, brand new nor has been interfere
  /////////////////////Count the number of students in this class
   //From ACLASS_LOCATION: /Import/
    SD_File = SD.open(ACLASS_LOCATION+buf.Class+".txt", FILE_READ);
    if((!SD_File)&&(SD_File.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return;
    }//end if
    SD_File.seek(0);//start from the beginning
    //-------------------------------
    //Start counting
    while(SD_File.available()) {
        char SDtemp = SD_File.read();
        if (SDtemp =='\n') { //end of a line
            numOfStu++;
        } //end a line
    }//end while
    SD_File.close();//after this we are already have 4 variable with SD_pointer to the latest character
    stuDis=numOfStu; //save here for display, but need to go through checking database before producing the last stuDis
   //From ACHECK_LOCATION: /Database/
    File SD_cFile = SD.open(ACHECK_LOCATION+"CLASSES.TXT", FILE_READ);
    if((!SD_cFile)&&(SD_cFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return;
    }//end if
    SD_cFile.seek(0); //point to the position of the first class in the file
    String cBuffer="";
    while(SD_cFile.available()){
        char SDtemp = SD_cFile.read();
        if (SDtemp =='\n') {//in Windows (and many old OSs), the code for end of line is 2 characters, \r\n, in this order
            if (buf.Class==cBuffer) {
                //if this class is existed in the database already, then count the number of students there too.
                File SD_chFile = SD.open(ACHECK_LOCATION+buf.Class+".txt", FILE_READ);
                if((!SD_chFile)&&(SD_chFile.isDirectory())) {
                    D_PRINTLN(F("File not found!"));
                    return;
                }//end if
                stuDone = (SD_chFile.size())/37; //total 11(67003FCA88|) + 9(B1509360|) + 15(name) +2(\r\n) = 37;
                //we will do not interfere with numOfStu here, only interfere with the display
                stuDis += stuDone; // = numOfStu + stuDone --> last stuDis is here
                SD_chFile.close();
                break;
            }//end if
            cBuffer="";
        } else if (SDtemp =='\r') { //safety method for \r\n of Windows-edited files
        } else { //end of a line
            cBuffer += SDtemp;
        }//end if else
    }//end while
    SD_cFile.close();
   ////////////////////
  //////////////////////////////////////////////////////////////////
    
    int lineBuf[numOfStu];
    bool doneBuf[numOfStu];
    unsigned char lCount=0;
  //////////////////////Save the position line of students in this class
    for (lCount=0;lCount<numOfStu;lCount++) { //set all flags to false, prepare for the main procedure
        doneBuf[lCount]=false;
    }//end for
    lCount=0; //ready for saving line Buffer
    lineBuf[0]=0; //first line
    SD_File = SD.open(ACLASS_LOCATION+buf.Class+".txt", FILE_READ);
    if((!SD_File)&&(SD_File.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return;
    }//end if
    SD_File.seek(0);//start from the beginning
    //-------------------------------
    //Start counting
    while(SD_File.available()) {
       char SDtemp = SD_File.read();
        if (SDtemp =='\n') { //end of a line
            if (SD_File.available()) {//prevent saving the last useless position
                lineBuf[++lCount]=SD_File.position();
            }//end if 
        } //end of a line
    }//end while
    SD_File.close();//after this we are already have 4 variable with SD_pointer to the latest character
  //////////////////////////////////////////////////////////////////

    uint8_t CurPointer=0; //from 0 to (numOfStu-1) 
    while (1) {
        
      //////////////////////Save current student information into buffers
        SD_File = SD.open(ACLASS_LOCATION+buf.Class+".txt", FILE_READ);
        if((!SD_File)&&(SD_File.isDirectory())) {
            D_PRINTLN(F("File not found!"));
            return;
        }//end if
        SD_File.seek(lineBuf[CurPointer]);

        buf.mssv=""; //have to be here
        buf.name=""; //have to be here
        uint8_t nameExtractPointer = 0;
        uint8_t chooseBuffer = 0;
        cBuffer = ""; //ExtractNameBuffer
        while(SD_File.available()) {
            char SDtemp = SD_File.read();
            //SD_pointer++;
            if (SDtemp =='\n') { //end of a line
                //no need to reset cBuffer and nameExtractPointer because these are local variables
                buf.name += cBuffer; //put the temporary buffer to the SD buffer (now save the remaining of the name)
                for (char numStr = buf.name.length(); numStr<15;numStr++) {
                    buf.name += ' ';
                }//end for
                chooseBuffer=0;
                break;
            } //end a line
            else if (SDtemp=='\r') {} //safety method for \r\n of Windows-edited files
            else if((chooseBuffer==0)&&(!(SDtemp=='|'))) {
                buf.mssv += SDtemp;
            }//end else
            else if((chooseBuffer==1)&&(!(SDtemp=='|'))) {
                /*NAME COMPRESSOR INCLUDED*/
                if (!(nameExtractPointer++)) { //if the letter is the first letter in a word
                    buf.name += SDtemp;//add the first letter into the buffer
                } else { // save those subsequence letters in a temporary string buffer
                    cBuffer += SDtemp;
                }//end else
                if (SDtemp==' ') { //a word is finished and not the last word (not the name)
                    buf.name += '.';//add a period between words
                    nameExtractPointer=0; //reset the word pointer
                    cBuffer=""; //not the last word (not the name) => delete the temporary buffer
                }//end if
            }//end else if
            else if (SDtemp=='|') {chooseBuffer++;}
        }//end while
        SD_File.close();//after this we are already have 4 variable with SD_pointer to the latest character
      //////////////////////Display student infor into the OLED (also number of students in class)
        static char mesBuf[9];
        for (uint8_t mtemp=0;mtemp<9;mtemp++) { //safety method for the screen
            mesBuf[mtemp]='\0';
        }//end for
        sprintf(mesBuf,"%d/%d",stuDis-stuDone,stuDis);
        oled_getRFID_info(buf.mssv,buf.name,mesBuf);
      //////////////////////
        //set boundaries for the switch
        //this will be reset everytime
        SW_setBoundaries(1,3,false); //min, max, loop enable
        SW_set(2);
        SW_enable();

        while (1) {//wait for user behaviors
            if (hasID()) {//if ID scanned
             ///////////////////////RFID PART ///////////////////////////
                buf.RFID = getID();
                singleBeep(100);
              //////////////////save ID and corresponding information into SD card
                //CAUTION!!!: files to attend have to be created by this system, not the computer!
                File SD_dtbFile = SD.open(ACHECK_LOCATION+buf.Class+".txt", FILE_APPEND);
                if((!SD_dtbFile)&&(SD_dtbFile.isDirectory())) {
                    D_PRINTLN(F("File not found!"));
                    return;
                }//end if
                ////////////////////////////////////////DO NOT DELETE THE BELOW!!! - FOR DEBUG PURPOSE
                    // if(SD_dtbFile.print(SD_RFIDBuffer))
                    // {D_PRINTLN(F("Appended!"));} else {D_PRINTLN(F("Append failed!"));}//end if else
                    // if(SD_dtbFile.print('|'))
                    // {D_PRINTLN(F("Appended!"));} else {D_PRINTLN(F("Append failed!"));}//end if else
    
                    // if(SD_dtbFile.print(SD_mssvBuffer))
                    // {D_PRINTLN(F("Appended!"));} else {D_PRINTLN(F("Append failed!"));}//end if else
                    // if(SD_dtbFile.print('|'))
                    // {D_PRINTLN(F("Appended!"));} else {D_PRINTLN(F("Append failed!"));}//end if else
    
                    // if(SD_dtbFile.print(SD_nameBuffer))
                    // {D_PRINTLN(F("Appended!"));} else {D_PRINTLN(F("Append failed!"));}//end if else
                    // if(SD_dtbFile.print('\n'))
                    // {D_PRINTLN(F("Appended!"));} else {D_PRINTLN(F("Append failed!"));}//end if else
                ////////////////////////////////////////DO NOT DELETE THE ABOVE!!! - FOR DEBUG PURPOSE
                if ((SD_dtbFile.print(buf.RFID))&&
                    (SD_dtbFile.print('|'))          &&
                    (SD_dtbFile.print(buf.mssv))&&
                    (SD_dtbFile.print('|'))          &&
                    (SD_dtbFile.print(buf.name))&&
                    (SD_dtbFile.print("\r\n"))) //to make it compatible with windows
                    {S_PRINTLN(F("Saved!"));oled_getRFID_status("Saved!");} 
                else{S_PRINTLN(F("Failed!"));oled_getRFID_status("Failed!");}
                //total 11(67003FCA88|) + 9(B1509360|) + 15(name) +2(\r\n) = 37;
                SD_dtbFile.close();
                doneBuf[CurPointer]=true;
                stuDone++;
              ////////////////if the whole class have been recorded
                if (stuDone==stuDis) { //stuDis is more precise here compared to numOfStu
                    SD_saveClass(buf.Class,"DONE!");
                    Frame1_ClasDel(ACLASS_LOCATION,DClass,NumClass,Dnum);//delete class
                    return;
                }//end if
              ////////////////move to the next stu if not done yet
                while (1) { //if not done yet
                    //just move down blindly
                    if (CurPointer==(numOfStu-1)) { //--> last not done stu
                       CurPointer=0; //point to the first not done stu
                    }//end if
                    else {CurPointer++;} //move to the next stu
                    ////////////////////////
                    if (!doneBuf[CurPointer]) {//if this one is not done yet
                        break;
                    }//end if
                }//end while
             ////////////////////////////////////////////////////////////
                delay(700); //for user to see the information
                break; //continue the process by breaking out of the while loop waiting for RFID
            }//end if
            if (SW_midPressed()) {//cancel the process
             /////////////////////// IF CANCEL THE PROCESS DURING ADD CLASS TIME
              //////////////saving and displaying students that successfully added into the class
                cBuffer = (String)mesBuf+" students left";
                SD_saveClass(buf.Class,cBuffer); //save the class name to the system
              /////////////////////save the remain students that didn't check in yet - use buffer file to sit between trasferation
                File rootFile = SD.open(ACLASS_LOCATION+buf.Class+".txt", FILE_READ);
                if((!rootFile)&&(rootFile.isDirectory())) {
                    D_PRINTLN(F("File not found!"));
                    return;
                }//end if
                SD_deleteFile(ACLASS_LOCATION+"buffer.txt"); //delete if existed, legacy of the void =)))
                File desFile = SD.open(ACLASS_LOCATION+"buffer.txt", FILE_APPEND);
                if((!desFile)&&(desFile.isDirectory())) {
                    D_PRINTLN(F("File not found!"));
                    return;
                }//end if
                for (int Fmove=0; Fmove<numOfStu;Fmove++) {
                    if (!doneBuf[Fmove]) {//not done yet
                        uint8_t lineChar=lineBuf[Fmove+1]-lineBuf[Fmove];
                        rootFile.seek(lineBuf[Fmove]);
                        for (uint8_t fMove=0;fMove<lineChar;fMove++) {
                            desFile.print((char)rootFile.read());
                        }//end for
                    }//end if 
                }//end for
                rootFile.close();desFile.close();
                SD_deleteFile(ACLASS_LOCATION+buf.Class+".txt");
                SD_renameFile(ACLASS_LOCATION+"buffer.txt", ACLASS_LOCATION+buf.Class+".txt");
             //////////////////////////////////////////////////////////////////
                return;
            }//end if
            if (SW_posChanged()) { //if use the move up or move down switches
                switch (SW_read()) {
                  /////////////////////// MOVED UP
                    case 1: { //switch moved up
                        while (1) {
                            //just move up blindly
                            if (!CurPointer) { //if CurPointer==0 --> first not done stu
                                CurPointer=numOfStu-1; //point to the last not done stu
                            }//end if
                            else {CurPointer--;} //move to the previous stu
                            ////////////////////////
                            if (!doneBuf[CurPointer]) {//if this one is not done yet
                                break;
                            }//end if
                        }//end while
                        break;
                    }
                  /////////////////////// MOVED DOWN
                    case 3: { //switch moved down
                        while (1) {
                            //just move down blindly
                            if (CurPointer==(numOfStu-1)) { //--> last not done stu
                                CurPointer=0; //point to the first not done stu
                            }//end if
                            else {CurPointer++;} //move to the next stu
                            ////////////////////////
                            if (!doneBuf[CurPointer]) {//if this one is not done yet
                                break;
                            }//end if
                        }//end while
                        break;
                    }
                }//end switch
                break; //continue the process by breaking out of the while loop waiting for RFID
            }//end if
        } //end while
    }//end while
}//end SD_updateDatabase

// check if this class existed in the database or not
bool SD_checkClass(String CLass) {
    File SD_cFile = SD.open(ACHECK_LOCATION+"classes.txt", FILE_READ);
    if((!SD_cFile)&&(SD_cFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return false;
    }//end if
    SD_cFile.seek(0); //start from the beginning
    String classBuf="";
    while(SD_cFile.available()) { //search for existed class
            char SDtemp = SD_cFile.read();
            if (SDtemp =='\n') { //end of a line
                if (classBuf==CLass) {SD_cFile.close();return true;} //if existed this class in the file already
                classBuf="";
            } //end a line
            else if (SDtemp=='\r') {} //safety method for \r\n of Windows-edited files
            else {
                classBuf += SDtemp;
            }//end else
    }//end while
    SD_cFile.close();
    return false;
}//end SD_checkClass

static void SD_saveClass(String clBuf,String mSTAT) {
  ///////////////////////check if there is existing this class  
    File SD_cFile = SD.open(ACHECK_LOCATION+"classes.txt", FILE_READ);
    if((!SD_cFile)&&(SD_cFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return;
    }//end if
    SD_cFile.seek(0); //start from the beginning
    String classBuf="";
    while(SD_cFile.available()) { //search for existed class
            char SDtemp = SD_cFile.read();
            if (SDtemp =='\n') { //end of a line
                if (classBuf==clBuf) {SD_cFile.close();S_PRINTLN(MES_CADD);oled_getRFID_end(mSTAT,MES_CADD);return;} //if existed this class in the file already
                classBuf="";
            } //end a line
            else if (SDtemp=='\r') {} //safety method for \r\n of Windows-edited files
            else {
                classBuf += SDtemp;
            }//end else
    }//end while
    SD_cFile.close();
  /////////////////////start add class if no existing of this class was found
    SD_cFile = SD.open(ACHECK_LOCATION+"classes.txt", FILE_APPEND);
    if((!SD_cFile)&&(SD_cFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return;
    }//end if
    if ((SD_cFile.print(clBuf))&& //name of the class is store in CLASSES.TXT
        (SD_cFile.print("\r\n"))) 
        {S_PRINTLN(MES_CADD);oled_getRFID_end(mSTAT,MES_CADD);} 
    else{S_PRINTLN(MES_CFAIL);oled_getRFID_end(mSTAT,MES_CFAIL);}
    SD_cFile.close();
  /////////////////////////////////////////////
}//end SD_saveClass
//------------------------------- MODE 4 + MODE 9: EXPORT DATA -----------------------------
//------------------------------------------------------------------------------------------
bool SD_moveDATA() {
    File rootFile = SD.open(AWAIT_LOCATION+"DATA.TXT", FILE_READ);
    if((!rootFile)&&(rootFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return false;
    }//end if
    File desFile = SD.open(SENT_LOCATION+"DATA.TXT", FILE_APPEND);
    if((!desFile)&&(desFile.isDirectory())) {
        D_PRINTLN(F("File not found!"));
        return false;
    }//end if
    rootFile.seek(0); //point to the position of the first letter in the file
    while (rootFile.available()) {
        desFile.print((char)rootFile.read());
    }//end while
    rootFile.close();
    SD_deleteFile(AWAIT_LOCATION+"DATA.TXT");
    return true;
}//SD_moveDATA
//------------------------------- MODE 10: CLEAR ALL SENT DATA SAVED IN SD CARD -------------------------------
//------------------------------------------------------------------------------------------
void SD_ClearSent() {
    SD_deleteFile(SENT_LOCATION+"DATA.TXT"); //Delete file data.txt
    SD.open(SENT_LOCATION+"DATA.TXT", FILE_APPEND);//create a blank file
}//ClearAll_sentData
//------------------------------------------------------------------------------------------
void SD_deleteFile(String path) {
    if(SD.remove(path)){
        D_PRINTLN(F("File deleted"));
    } else {
        D_PRINTLN(F("Delete failed"));
    }//end if else
}//end SD_deleteFile

static void SD_renameFile(String pathf, String patht) {
    //D_PRINTF("Renaming file %s to %s\n", path1, path2);
    if (SD.rename(pathf, patht)) {
        D_PRINTLN(F("File renamed"));
    } else {
        D_PRINTLN(F("Rename failed"));
    }//end if else
}//end SD_renameFile

// void SD_readfile(const char * path) {
//     File SDfile = SD.open(path, FILE_READ);
//     if((!SDfile)&&(SDfile.isDirectory())) {
//         D_PRINTLN(F("File not found!"));
//         return;
//     }//end if
//     while(SDfile.available()){
//         Serial.write(SDfile.read());
//     }//end while
//     SDfile.close();
// }//end SD_openfile

// void SD_writeFile(const char * path, const char * message) {
//     Serial.printf("Writing file: %s\n", path);
//     File SDfile = SD.open(path, FILE_WRITE);
//     if(!SDfile) {
//         D_PRINTLN(F("Failed to open file for writing"));
//         return;
//     }//end if
//     if(SDfile.print(message)){
//         S_PRINTLN(F("File written!"));
//     } else {
//         S_PRINTLN(F("Write failed!"));
//     }//end if else
//     SDfile.close();
// }//end SD_writeFile


// void SD_appendFile(const char * path, const char * message) {
//     File SDfile = SD.open(path, FILE_APPEND);
//     if((!SDfile)&&(SDfile.isDirectory())) {
//         D_PRINTLN(F("File not found!"));
//         return;
//     }//end if

//     if(SDfile.print(message)){
//         S_PRINTLN(F("Appended!"));
//     } else {
//         S_PRINTLN(F("Append failed!"));
//     }//end if else
//     SDfile.close();
// }//end SD_appendFile



// void SD_createDir(const char * path) {
//     D_PRINTF("Creating Dir: %s\n", path);
//     if(SD.mkdir(path)){
//         D_PRINTLN(F("Dir created"));
//     } else {
//         D_PRINTLN(F("mkdir failed"));
//     }//end if else
// }//end SD_createDir

// void SD_removeDir(const char * path) {
//     D_PRINTF("Removing Dir: %s\n", path);
//     if(SD.rmdir(path)){
//         D_PRINTLN(F("Dir removed"));
//     } else {
//         D_PRINTLN(F("rmdir failed"));
//     }//end if else
// }//end SD_removeDir



#endif //_C1_SD_CARD_CPP