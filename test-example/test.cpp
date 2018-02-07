#include <iostream>
#include <fstream>
#include "fs-test.h"

using namespace std;
 
int main () {
	
	std::ofstream out;
	int i;

	cout << "\nCreating " << FS_FILES << " test files\n";
	
	for (i = 0; i < FS_FILES; i++){
		
	cout << string("./output/") + string(fsFiles[i].name) << "\n";		
	out.open (string("./output/") + string(fsFiles[i].name), std::ofstream::out | std::ofstream::binary);
	out.write((const char* ) fsFiles[i].data, fsFiles[i].size);	
	out.close();	
		
	}


   cout << "\n\n";


}
