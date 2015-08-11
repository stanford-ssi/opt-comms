/** Author: Charlie Chenye Zhu
 *          chenye@stanford.edu
 *
 *  Base class for both opcommMessageReceived and opcommMessageSent
 *  Defines and implements the constructors, as well as a few util functions
 */
#include "opcommmessage.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <string>
#include <assert.h>

using namespace std;

unsigned char opcommMessage::mask[] = {128, 64, 32, 16, 8, 4, 2, 1};

opcommMessage::opcommMessage() {}

void opcommMessage::printMessage(){
    cout << toString() << endl;
}

void opcommMessage::appendToMessage(const string& message){
    copy(message.begin(), message.end(), back_inserter(messageContainer));
}

void opcommMessage::replaceMessageWith(const string &newMessage){
    eraseMessage();
    copy(newMessage.begin(), newMessage.end(), back_inserter(messageContainer));
}

void opcommMessage::eraseMessage(){
    messageContainer.clear();
}

bool opcommMessage::readMessageFromFile(const string &inputFileName) {
    ifstream inputFile(inputFileName.c_str(), fstream::in);
    if (inputFile.is_open()){
        eraseMessage();
        string line;
        while (getline(inputFile, line)){
            line += '\n';
            appendToMessage(line);
        }
        inputFile.clear();
        inputFile.close();
        return true;
    } else {
        cout << "Unable to read message from file " << inputFileName << endl;
        inputFile.clear();
        inputFile.close();
        return false;
    }
}

void opcommMessage::publishMessageToFile(ofstream &outputFile) {
    outputFile << toString();
}

bool opcommMessage::appendMessageToFile(const string &outputFileName) {
    ofstream outputFile(outputFileName.c_str(), fstream::out | fstream::app);
    if (outputFile.is_open()){
        outputFile << endl;
        publishMessageToFile(outputFile);
        outputFile.clear();
        outputFile.close();
        return true;
    } else{
        cout << "Unable to append message to file " << outputFileName << endl;
        outputFile.clear();
        outputFile.close();
        return false;
    }
}

bool opcommMessage::writeMessageToFile(const string &outputFileName) {
    ofstream outputFile(outputFileName.c_str(), fstream::out | fstream::trunc);
    if (outputFile.is_open()){
        publishMessageToFile(outputFile);
        outputFile.clear();
        outputFile.close();
        return true;
    } else{
        cout << "Unable to write message to file " << outputFileName << endl;
        outputFile.clear();
        outputFile.close();
        return false;
    }
}

bool opcommMessage::readBitPatternFromFile(const string &inputFileName) {
    ifstream inputFile(inputFileName.c_str(), fstream::in);
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile,line)){
            unsigned short counter = 0;
            unsigned short totalLength = line.length();
            unsigned char character;

            while (totalLength - counter >= CHAR_BIT){
                character = convertBitToChar(line.substr(counter, CHAR_BIT));
                counter = counter + CHAR_BIT;
                messageContainer.push_back(character);
            }

            if (totalLength > counter){
                character = convertBitToChar(line.substr(counter));
                messageContainer.push_back(character);
            }
        }
        inputFile.clear();
        inputFile.close();
        return true;
    } else {
        cout << "Unable to read bit pattern from file " << inputFileName << endl;
        inputFile.clear();
        inputFile.close();
        return false;
    }
}

bool opcommMessage::appendBitPatternToFile(const string &outputFileName) {
    ofstream outputFile(outputFileName.c_str(), fstream::out | fstream::app);
    if (outputFile.is_open()){
        outputFile << endl;
        publishBitPatternToFile(outputFile);
        outputFile.clear();
        outputFile.close();
        return true;
    } else{
        cout << "Unable to append bit pattern to file " << outputFileName << endl;
        outputFile.clear();
        outputFile.close();
        return false;
    }
}

bool opcommMessage::writeBitPatternToFile(const string &outputFileName) {
    ofstream outputFile(outputFileName.c_str(), fstream::out | fstream::trunc);
    if (outputFile.is_open()){
        publishBitPatternToFile(outputFile);
        outputFile.clear();
        outputFile.close();
        return true;
    } else{
        cout << "Unable to write bit pattern to file " << outputFileName << endl;
        outputFile.clear();
        outputFile.close();
        return false;
    }
}

void opcommMessage::publishBitPatternToFile(ofstream &outputFile){
    short counter = 0;
    for (vector<unsigned char>::iterator it = messageContainer.begin(); it != messageContainer.end(); ++ it){
        outputFile << convertCharToBit(*it);
        counter ++;
        if (counter == phraseLength){
            outputFile << endl;
            counter = 0;
        }
    }
}

string opcommMessage::toString(){
    string messageString(messageContainer.begin(), messageContainer.end());
    return messageString;
}

string opcommMessage::convertCharToBit(unsigned char ch){
    string bitPattern = "";
    for (size_t i = 0; i < CHAR_BIT; i++){
        if (ch & mask[i])
            bitPattern += '1';
        else
            bitPattern += '0';
    }
    return bitPattern;
}

unsigned char opcommMessage::convertBitToChar(const string &bitPattern) {
    assert(bitPattern.length() <= CHAR_BIT);

    unsigned char character = 0;
    for (size_t  i = 0; i < bitPattern.length(); i ++)
        if (bitPattern[i] == '1')
            character += mask[i];
    return character;
}
