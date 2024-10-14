#include <fstream>
#include <sstream>
#include "SpeakerView.h"
#include <string>

speakerView::speakerView(std::string file){ //constructor
    m_file = file;
}

speakerView::~speakerView(){} //destructor

std::string speakerView::getComplaints(){
    monoStack<float> shortPpl(1, 'i'); //dynamically resizes so the initial size does not mean that match in this case
    int rows = 0;
    int cols = 0;
    std::string readValues = ""; //use this to copy the read values into fileValues
    std::string fileValues = "";
    std::string complaints = ""; //where I put the complaints after the operation - below will be the operation
    std::string s = "";
    std::ifstream readFile;
    readFile.open(this->m_file);
    if (readFile.is_open()){ //gets the amount of rows
        while (getline(readFile, readValues)){
            ++rows;
            fileValues += readValues + "\n";
        }
        readFile.close();
    }
    else{
        readValues += "Could not open file.";
        return readValues;
    }
    rows -= 2;
    std::stringstream stream(fileValues); //gets the amount of cols ignoring BEGIN and END
    while (stream >> s){
        if (s == "BEGIN" || s == "END"){
            continue;
        }
        if (s.find(",")){
            ++cols;
        }
    }
    cols /= rows; //gets the amount of rows
    float values[rows][cols];
    int i = 0;
    int j = 0;
    std::stringstream repeatStream(fileValues); //have to open a new string stream with the same input
    while ((repeatStream >> s) && i < rows){ //initializes the array with all the values of the string stream excluding BEGIN and END
        if (s == "BEGIN" || s == "END"){
            continue;
        }
        if (j == cols){
            ++i;
            j = 0;
        }
        values[i][j] = stof(s); //changes string to a float - from the string library
        ++j;
    }
    int max;
    int cantSee;
    int amountInRow;
    int amountInCol = 0;
    while (amountInCol < cols){ //does the whole procedure that produces the rows and columns with people who cant see
        max = 0;
        amountInRow = 0;
        cantSee = 0;
        while (amountInRow < rows){
            if (values[amountInRow][amountInCol] < max){
                cantSee++;
            }
            else{
                max = values[amountInRow][amountInCol];
                shortPpl.push(values[amountInRow][amountInCol]);
            }
            ++amountInRow;
        }
        complaints += "In column " + std::to_string(amountInCol) + " there are " + std::to_string(rows - cantSee) + " that can see. Their heights are: ";
        while (!(shortPpl.isEmpty())){ //empties the stack while returning the values
            complaints += std::to_string(shortPpl.pop()) + " "; //adds to complaints
        }
        complaints += "inches.\n";
        ++amountInCol; //increments
    }
    return complaints;
}