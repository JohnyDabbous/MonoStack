#ifndef SpeakerView_H
#define SpeakerView_H
#include "MonoStack.h"
#include <string>
class speakerView{
    public:
        speakerView(std::string file);
        ~speakerView();
        std::string getComplaints();
    private:
        std::string m_file;
};
#endif
