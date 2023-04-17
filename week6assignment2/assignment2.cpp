#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream myfile("example.wav", ios::in | ios::binary);
    if (!myfile) {     // 만일 파일이 없으면 끝낸다. 
        cout << "cant read example.wav\n";
        return 666;
    }
    char header[44];
    myfile.read(header, 44);
   
    unsigned int* SampleRate; SampleRate = (unsigned int*)(header + 24); cout << "SampleRate = " << *SampleRate << endl;
    unsigned int* ByteRate; ByteRate = (unsigned int*)(header + 28); cout << "ByteRate = " << *ByteRate << endl;
    unsigned short* NumChannels; NumChannels = (unsigned short*)(header + 22); cout << "NumChannels = " << *NumChannels << endl;
    

    short data[1000];
    myfile.seekg(44);
    myfile.seekg(SampleRate[0] * 10 );
    myfile.read((char*)data, 1000);

    ofstream aaa("data.txt");
    float dt = 1. / SampleRate[0];
    for (int i = 0; i < 500; i++) {
        float t = i * dt;
        aaa << t << "   " << data[i * 2] << "   " << data[i * 2 + 1] << endl;
    }
    myfile.close();
    aaa.close();
}
