#include "main.h"
using namespace std;

// #define DEBUG // uncomment this to get a debug window and make sure that the system can get see the keys, otherwise program will disconnect from the console
			     // immediately after startup

int main(int argc, char* argv[]){

#ifndef DEBUG
	FreeConsole();
#endif

	bool active = true;
	int c=0;
	SHORT state;
	bool ctrlSet = false;
	bool specialKeySet = false;
	int timeout = 0;


	while(active){
		
		for(c=0x01;c<=0xFE;c++){
			SHORT rv = GetAsyncKeyState(c);

				if(rv & 1){ // on press button down

#ifdef DEBUG
				cout << c << endl;
#endif
					 switch(c){
						case VK_ADD:
							ctrlSet = true;
							timeout = 1000000;
							break;
						case 0x53:
							specialKeySet = true;
							break;
					  }

#ifdef DEBUG
					 cout << timeout << endl;
#endif
				}

				if(timeout>0){
					timeout--;

					if(specialKeySet == true && ctrlSet == true){
						system("start %windir%\\system32\\cmd.exe");
						specialKeySet=false;
						ctrlSet=false;
					}
				}

				else if(timeout==0){
					specialKeySet=false;
					ctrlSet=false;
				}

		}
	}
	return 0;
}