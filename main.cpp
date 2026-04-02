#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem> 

using namespace std;

struct FileHeader  {
    char fileName[256];
    long long fileSize;
};

int main() {
    string srcDir = "./src";
    string packName = "data.dat";

    ofstream destFile(packName, ios::binary);
    if (!destFile.is_open()) {
        cout << "Cannot create package file." << endl;
        return 1;
    }

    if (!filesystem::exists(srcDir) || !filesystem::is_directory(srcDir)) {
        cout << "The src folder does not exist." << endl;
        return 1;
    }

    for(const auto& entry : filesystem::directory_iterator(srcDir)) {
        if(!filesystem::is_regular_file(entry)) continue;

        string filePath = entry.path().string();
        string fileName = entry.path().filename().string();
        long long size = filesystem::file_size(entry);

        FileHeader header = {0}; 
        snprintf(header.fileName, sizeof(header.fileName), "%s", fileName.c_str());
        header.fileSize = size;

        destFile.write((char*)&header, sizeof(header));

        ifstream srcFile(filePath, ios::binary);
        vector<char> buffer(size);
        srcFile.read(buffer.data(), size);  
        destFile.write(buffer.data(), size);

        srcFile.close();
        cout << "[Success] " << fileName << " (" << size << " bytes)\n";
    }

    destFile.close();
    cout << "Done!";
    return 0;
}