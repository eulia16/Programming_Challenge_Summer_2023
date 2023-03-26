#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
This program will remain as simple as possible to allow for easy readability and succinctness
We will have several functions, each with seperate purposes, such as functions to return the generic information
for a USB, and then much more detailed versions, which will allow the user to select information they want to see 
specifically, many new lines are printed in between text to enhance readability of output.
*/



void printMenu();
void printFileInformation(FILE *file);
void performRequestedUserResponse(int userResponse);
void displayUserGenericSearchedData(int userResponse);
void displayUserSpecificSearchedData(int userResponse, char *returnValue);
char *getUserInputForSpecificUSB();
FILE *getAllGenericUSBInfo();
FILE *getAllVerboseUSBInfo();
FILE *getAllTreeViewGenericUSBInfo();
FILE *getSpecificUSBGenericInfo(char *vendorAndProdID);
FILE *getSpecificUSBSVerboseInfo(char *vendorAndProdID);
FILE *getSpecificUSBTreeViewInfo(char *vendorAndProdID);
FILE *getSpecificDeviceAttribute(char *deviceAttribute);
FILE *getUSBBussesDevices();


int main(void){

FILE *USBFileInterface;
int userResponse=0;
//print the menu to the user
printMenu();

//main for loop for programs actual functionality/allow constant user input/searching
for(;;){
//print prompt
printf("Please enter another request(Quit: -1, Menu: 0): ");
//scan user response
scanf("%d", &userResponse);
performRequestedUserResponse(userResponse);

}




return 0;
}

void printMenu(){
printf("Hello! There are various options you have to select for obtaining specific USB information in this program.\nThis program is essentially an abstraction of the linux command lsusb, and all of its related command line arguments,\nin essence, thise program is meant to make it easier to query for USB information through a menu like interface,\nrather than inherently knowing the commands for lsusb.\n");
printf("(-1): Quit.\n");
printf("(0):  Menu.\n");
printf("(1):  Generic USB Information(for every USB Device currently connected).\n");
printf("(2):  Verbose USB Information(for every USB Device currently connected).\n");
printf("(3):  Tree-View USB Information(for every USB Device currently connected).\n");
printf("(4):  Select Specific USB, obtain Generic USB information for selected USB.\n");
printf("(5):  Select Specific USB, obtain Verbose USB information for selected USB.\n");
printf("(6):  Select Specific USB, obtain Tree-View USB information for selected USB.\n");
printf("(7):  Search for information(by entering a string) regarding ALL USB devices selected.\n");
printf("(8):  Select Specific USB, Search for information(by entering a string) regarding ALL USB devices selected.\n");
printf("(9):  USB buses in use by the system and the devices currently connected to them.\n");
printf("\n\n\n");

}

void performRequestedUserResponse(int userResponse){

FILE *file; 

switch(userResponse){

    case -1:
    	    printf("Thank you for using the program, Cheerio!\n");
	    exit(0);
	    break;
    case 0:
    	    printMenu();
    	    break;
    case 1:
    	    //prints all of the generic USB information
    	    file = getAllGenericUSBInfo();
    	    printf("\n\n\n");
    	    printFileInformation(file);   
    	    printf("\n\n\n"); 
            //return system resources
            fclose(file);
    	    break;
    case 2: 
    	    //prints all of the verbose USB information
    	    file = getAllVerboseUSBInfo();
    	    printf("\n\n\n");
    	    printFileInformation(file);
    	    printf("\n\n\n");
    	    //return system resources
    	    fclose(file);
    	    break;
    case 3:	
    	    //prints all of the tree-view USB information
    	    file = getAllTreeViewGenericUSBInfo();
    	    printf("\n\n\n");
    	    printFileInformation(file);
    	    printf("\n\n\n");
    	    //return system resources
    	    fclose(file);
    	    break;
    	    //must add brackets arounf case statement as a new 'type' is being created(just initializing the char pointer)
    case 4: {

    	    char *returnValue;
    	    returnValue = getUserInputForSpecificUSB();
    	    file = getSpecificUSBGenericInfo(returnValue);
    	    printf("\n\n\n");
    	    printFileInformation(file);
    	    printf("\n\n\n");
    	    //return system resources
    	    free(returnValue);
    	    fclose(file);
    	    break;
    	    }
    	    
    case 5: {

    	    char *returnValue;
    	    returnValue = getUserInputForSpecificUSB();
    	    file = getSpecificUSBSVerboseInfo(returnValue);
    	    printf("\n\n\n");
    	    printFileInformation(file);
    	    printf("\n\n\n");
    	    //return system resources
    	    free(returnValue);
    	    fclose(file);
    	    break;
    	    }	 
    	    
    case 6: {

    	    char *returnValue;
    	    returnValue = getUserInputForSpecificUSB();
    	    file = getSpecificUSBTreeViewInfo(returnValue);
    	    printf("\n\n\n");
    	    printFileInformation(file);
    	    printf("\n\n\n");
    	    //return system resources
    	    free(returnValue);
    	    fclose(file);
    	    break;
    	    }	
    	    
    	    

    case 7: {
    	    printf("You have chosen to search for specific device information info across all USB devices, please enter a number between -1 and 3\nto determine what kind of device information you would like to search for\n(-1): Quit\n(0): Menu\n(1): All generic USB info with searching capabilities\n(2): All verbose USB info with searching capabilities\n(3): All tree-view USB info with searching capabilities\n");
    	    int userInput;
    	    printf("Enter a value...");
    	    //we must first get the input for the kind of generic information they would like to parse
    	    scanf("%d", &userInput);
    	    if(userInput == -1) exit(0);
    	    if(userInput == 0) printMenu();
    	    displayUserGenericSearchedData(userInput);
    	    
    	    break;
    	    }	
    	    
    case 8: {
    
            char *returnValue;
    	    returnValue = getUserInputForSpecificUSB();	    
    	    printf("You have chosen to search for specific USB device info, for one specidic USB, please enter a number between -1 and 3\nto determine what kind of device information you would like to search for\n(-1): Quit\n(0): Menu\n(1): Specific USB w/ generic USB info with searching capabilities\n(2): Specific USB w/ verbose USB info with searching capabilities\n(3): Specific USB w/ tree-view USB info with searching capabilities\n");
    	    int userInput;
    	    printf("Enter a value...");
    	    //we must first get the input for the kind of generic information they would like to parse
    	    scanf("%d", &userInput);
    	    
    	    if(userInput == -1) exit(0);
    	    if(userInput == 0) printMenu();
    	    displayUserSpecificSearchedData(userInput, returnValue);
    	    
    	    
    	    break;
    	    }	
    	       
    	    
    case 9: 
   	    file = getUSBBussesDevices();
   	    printf("\n\n\n");
   	    printFileInformation(file);
   	    printf("\n\n\n");
   	    //return system resources
    	    fclose(file);
    	    break;
    	          	       	       
    	    
    default: 
    	    printf("Please enter a valid number as specified in the menu, again to access the menu, enter the number 0.\n");
    	    break;

}

}


void displayUserSpecificSearchedData(int userResponse, char *specificDevice){


printf("You have selected to search for specific device information for a specific USB, based on your input you have selected one of the three generic USB information outputs to search for values in. You will be able to continue searching for the values you want until you choose to exit this part of the program.\n ");

for(;;){
char searchString[40] = "";
char command[50] = "";

//make it search for a specific device's attributes
strcpy(command, "lsusb -d ");
strcat(command, specificDevice);

printf("Enter a String you would like to search for: ");
scanf("%39s", searchString);

//generic
if(userResponse == 1){
strcat(command, " | grep ");
strcat(command, searchString);

}
//verbose
if(userResponse == 2){
strcat(command, " -v | grep ");
strcat(command, searchString);
}
//tree-view
if(userResponse == 3){
strcat(command, " -t | grep ");
strcat(command, searchString);
}

FILE *searchedValues = popen(command, "r");
printf("\n\n\n");
printFileInformation(searchedValues);
printf("\n\n\n");
//close file
fclose(searchedValues);

printf("Enter an number to choose what you would like to do next:\n(-1): Quit\n(0): Menu\n(1): Specific USB w/ generic USB info with searching capabilities\n(2): Specific USB w/ verbose USB info with searching capabilities\n(3): Specific USB w/ tree-view USB info with searching capabilities\n");
scanf("%d", &userResponse);
if(userResponse == -1){ break;}
if(userResponse == 0) printMenu();

}





}

void displayUserGenericSearchedData(int userResponse){

printf("You have selected to search for specific device information for ALL USB devices, based on your input you have selected one of the three generic USB information outputs to search for values in. You will be able to continue searching for the values you want until you choose to exit this part of the program.\n\n");

//loop until user quits
for(;;){
char searchString[40] = "";
char command[50] = "";
printf("Enter a String you would like to search for...");
scanf("%39s", searchString);

//generic
if(userResponse == 1){
strcpy(command, "lsusb | grep ");
strcat(command, searchString);

}
//verbose
if(userResponse == 2){
strcpy(command, "lsusb -v | grep ");
strcat(command, searchString);
}
//tree-view
if(userResponse == 3){
strcpy(command, "lsusb -t | grep ");
strcat(command, searchString);
}

FILE *searchedValues = popen(command, "r");
printf("\n\n\n");
printFileInformation(searchedValues);
printf("\n\n\n");
fclose(searchedValues);

printf("Enter an number to choose what you would like to do next:\n(-1): Quit\n(0): Menu\n(1): All generic USB info with searching capabilities\n(2): All verbose USB info with searching capabilities\n(3): All tree-view USB info with searching capabilities\n\n");

scanf("%d", &userResponse);
if(userResponse == -1){ break;}
if(userResponse == 0) printMenu();

}


}


char* getUserInputForSpecificUSB() {
    printf("Enter the Vendor and ProdID, if you need to see the generic USB display to see the USB you would like to get specific info about, enter 1, else enter 0:\n");
    int nextInt;
    scanf("%d", &nextInt);
    if (nextInt == 1) {
        FILE *file = getAllGenericUSBInfo();
        printFileInformation(file);
        printf("\n");
        //return system resources
        fclose(file);
    }
    char vendor[5];
    char prodID[5];

    //Prompt user for input, force 4 characters
    printf("Enter vendor (4 characters): ");
    scanf("%4s", vendor);
    //Prompt user for input, force 4 characters
    printf("Enter product ID (4 characters): ");
    scanf("%4s", prodID);
    //allocate memory the length of the char arrays and the colon and the terminating character
    char* result = malloc(strlen(vendor) + strlen(prodID) + 2);
    strcpy(result, vendor);
    strcat(result, ":");
    strcat(result, prodID);
    //don't forget null terminating character
    strcat(result, "\0");


    return result;
}


void printFileInformation(FILE *file){

char ch;
//print file contents
do {
        ch = fgetc(file);
        printf("%c", ch);
 
        // Checking if character is not EOF.
        // If it is EOF stop reading.
    } while (ch != EOF);
    
}


FILE *getAllGenericUSBInfo(){
FILE *genericUSBInfo = popen("lsusb","r");
return genericUSBInfo; 
}
FILE *getAllVerboseUSBInfo(){
FILE *genericUSBInfo = popen("lsusb -v","r");
return genericUSBInfo; 
}
FILE *getAllTreeViewGenericUSBInfo(){
FILE *genericUSBInfo = popen("lsusb -t","r");
return genericUSBInfo; 
}


FILE *getSpecificUSBGenericInfo(char *vendorAndProdID){

//we must concatenate the string on the end of the original command to search for a specific USB interface and obtain the generic info for it
char command[50] = "lsusb -d ";
strcat(command, vendorAndProdID);
FILE *genericUSBInfo = popen(command,"r");

return genericUSBInfo;
}



FILE *getSpecificUSBSVerboseInfo(char vendorAndProdID[]){

//we must concatenate the string on the end of the original command to search for a specific USB interface and obtain the generic info for it
char command[10] = "lsusb -d ";
char endCommand[4] = " -v";
char fullCommand[50] = "";
strcat(fullCommand, command);
strcat(fullCommand, vendorAndProdID);
strcat(fullCommand, endCommand);
printf("%s\n", fullCommand);
FILE *verboseUSBInfo = popen(fullCommand,"r");

return verboseUSBInfo;
}


FILE *getSpecificUSBTreeViewInfo(char vendorAndProdID[]){

//we must concatenate the string on the end of the original command to search for a specific USB interface and obtain the generic info for it
char command[10] = "lsusb -d ";
char endCommand[4] = " -t";
char fullCommand[50] = "";
strcat(fullCommand, command);
strcat(fullCommand, vendorAndProdID);
strcat(fullCommand, endCommand);
printf("%s\n", fullCommand);
FILE *treeViewUSBInfo = popen(fullCommand,"r");

return treeViewUSBInfo;
}

/*
//this method will have to call grep/search the specific file for the information the user wants to see
FILE *getSpecificDeviceAttribute(char deviceAttribute[]){


}
*/

//calls command line arg usb-devices to list the busses and the USB devices connected to them
FILE *getUSBBussesDevices(){

char command[14] = "usb-devices";
FILE *USBDeviceInfo = popen(command,"r");

return USBDeviceInfo;
}
