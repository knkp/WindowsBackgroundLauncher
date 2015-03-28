#include "main.h"
using namespace std;

 #define DEBUG // uncomment this to get a debug window and make sure that the system can get see the keys, otherwise program will disconnect from the console
			     // immediately after startup

int main(int argc, char* argv[]){

#ifndef DEBUG
	FreeConsole();
#endif

	ifstream configFile;
	string line;
	string delimiter = "=";
	string CMD = "start ";
	int c=0;
	SHORT state;
	bool active = true;
	bool firstLine = true;
	bool firstSpace = true;
	bool ctrlSet = false;
	bool specialKeySet = false;
	int timeout = 0;
	int CTRLKEY = 0;
	int CMDKEY = 0;


	configFile.open("..\\WindowsBackgroundLauncher\\config.txt");

	if(configFile.is_open()){
		while(getline(configFile,line)){
			if(firstLine){// determine control key
				if(line[0] == '/' && line[1]=='/') // ignore commments, so first line becomes the first line below "//" in config.txt
					continue;

				CTRLKEY = (int)line[0]+64;
				firstLine=false;
			}
			else{
				if(line[0]=='/' && line[1]=='/') // ignore comments
					continue;
				CMDKEY=(int)line[0] - 32;
				line.erase(0,delimiter.length()+1);
				for(int i = 0; i< line.length();i++){
					if(line[i]==' '){
						if(firstSpace){
							firstSpace=false;
						}
						else {
							line[i]='\ ';
						}
					}
				}
				CMD.append(line);
			}
		}
	}




	while(active){
		
		for(c=0x01;c<=0xFE;c++){
			SHORT rv = GetAsyncKeyState(c);

				if(rv & 1){ // on press button down

#ifdef DEBUG
				cout << c << endl;
#endif
						if(c==CTRLKEY){
							ctrlSet = true;
							timeout = 3;
						}
						else if(c==CMDKEY){
							specialKeySet = true;
						}
					  }

#ifdef DEBUG
					 cout << timeout << endl;
#endif
				}

				if(timeout>0){
					timeout--;

					if(specialKeySet == true && ctrlSet == true){
						system(CMD.c_str());
						specialKeySet=false;
						ctrlSet=false;
					}
				}

				else if(timeout==0){
					specialKeySet=false;
					ctrlSet=false;
				}

		}
	
	return 0;
}