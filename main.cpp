#include <iostream> /// Knows the inputs/outputs
#include <fstream> /// Stream class to both read and write from/to files
#include <string> /// For things like std::string

using namespace std; /// Knows what namespace are defined (looks for cin and cout)

int main(){
    //initialize values
    int old_value = 0;
    int new_value = 0;
    cout << "This Program is to check if your File has been tampered with." << endl;
    int choice = 0;
    cout << "Option 1: Get Checksum for File and Save value into message.checksum" << endl;
    cout << "Option 2: If you know Checksum Value, Check here." << endl;
    cout << "Option 3: If you have message.checksum file save, Check here." << endl;
    cout << "(Run Option 1 if you do not have the checksum value or message.checksum)" << endl;
    cout << "Choose Option (1, 2, 3): ";
    cin >> choice;
    cout << endl;
    switch (choice) {
        case 1:
        {
            int fileLength =0;
            ifstream inputFile;
            inputFile.open("/home/luciouscurls/CLionProjects/checksum/cmake-build-debug/message.txt", ios::binary);

            //Get File Size
            inputFile.seekg(0, ios::end);
            int FileSize = inputFile.tellg();
            inputFile.seekg(0, ios::beg);
            char MyArray[FileSize];

            //Store into Array
            int i = 0;
            while (!inputFile.eof() && i < FileSize){
                inputFile.get(MyArray[i]);

                //cout << MyArray[i] << " : " << i << endl;
                i++;
            }
            inputFile.close();
            cout << "File Text and Ascii value" << endl;
            for(int i = 0; i < FileSize; i++){
                cout << MyArray[i] << " : " << (int)MyArray[i] << endl;
            }
            // Generate key for xorcipher
            int KEY[FileSize];
            for(int i = 0; i <= FileSize; i++){
                KEY[i] = 1 + (rand() % FileSize);
                // cout << KEY[i] << endl;
            }
            // Xor Algorithm and cast char to ascii value
            int Xor[FileSize];
            for(int i = 0; i <= FileSize; i++){
                Xor[i] = (int)MyArray[i] ^ KEY[i];
                // cout << Xor[i] << endl;
            }
            // Calculating and storing the checksum value
            int result = 0;
            for(int i = 0; i < FileSize; i++){
                result += Xor[i];
                //cout << result << endl;
            }
            cout << "CheckSum is: " << result << endl;
            ofstream checkfile ("/home/luciouscurls/CLionProjects/checksum/cmake-build-debug/message.checksum", ofstream::binary);
            checkfile << result;
            checkfile.close();
            cout << "Operation is completed" << endl;
            break;
        }
        case 2:
        {
            cout << "Enter OLD Checksum Value: ";
            cin >> old_value;
            cout << endl;
            cout << "Enter NEW Checksum Value: ";
            cin >> new_value;
            cout << endl;
            //Comparing value
            if (old_value != new_value){
                cout << "File has been Modified!" << endl;
            }
            else{
                cout << "File has NOT been Modified!" << endl;
            }

            break;
        }
        case 3:
        {
            string checksumFile;
            cout << "Enter Name of File. (EX: message.checksum)" << endl;
            cout << "File Must be located in CMakeFiles folder or you may give File path" << endl;
            cout << "File Name: ";
            cin >> checksumFile;
            cout << endl;
            //Open message.checksum and get value
            ifstream checkFile;
            checkFile.open(checksumFile, ios::binary);
            string stringint;
            getline(checkFile, stringint);

            cout << "Enter NEW Checksum Value: ";
            cin >> new_value;
            cout << endl;
            // Convert string to int
            //Comparing values
            if(new_value != std::stoi(stringint)){
                cout << "File has been Modified!" << endl;
            }
            else{
                cout << "File has NOT been Modified!" << endl;
            }
            checkFile.close();
            break;
        }

    }
    return 0;
}