#include <iostream>
#include "SpeakerView.h"

int main(int agrc, char** argv){
    speakerView myView(argv[1]);
    std::cout << myView.getComplaints() << std::endl;
    return 0;
}