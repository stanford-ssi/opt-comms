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

unsigned char opcommMessage::mask[] = {128, 64, 32, 16, 8, 4, 2, 1};

// Constructor
opcommMessage::opcommMessage(EncryptionMethods enMethod, ChecksumMethods ckMethod){
    this->encryption = enMethod;
    this->checksum = ckMethod;
}



// Utility functions
opcommMessage::EncryptionMethods opcommMessage::getEncryptionMethod(){
    return this->encryption;
}

opcommMessage::ChecksumMethods opcommMessage::getChecksumMethod(){
    return this->checksum;
}

std::string opcommMessage::EncryptionMethodToString(){
    switch (encryption){
        case opcommMessage::EncryptionMethodNone:
            return "None";
            break;
        default:
            return "Please update EncryptionMethodToString method";
            break;
    }
}

std::string opcommMessage::ChecksumMethodToString(){
    switch (checksum) {
        case opcommMessage::ChecksumMethodNone:
            return "None";
            break;
        default:
            return "Please update ChecksumMethodToString method";
            break;
    }
}

// IO Support

void opcommMessage::eraseMessage(){
    this->messageReadable.clear();
    this->messageEncrypted.clear();
    this->messageEncryptedChecksum.clear();
}

// MessageReadable
void opcommMessage::printMessageReadable(){
    printMessage(this->messageReadable);
}

void opcommMessage::appendToMessageReadable(const std::string &messageTrailing){
    appendToMessage(messageTrailing, this->messageReadable);
    getSyncFromMessageReadable();
}

void opcommMessage::replaceMessageReadableWith(const std::string &newMessage){
    replaceMessageWith(newMessage, this->messageReadable);
    getSyncFromMessageReadable();
}


bool opcommMessage::writeMessageReadableToFile(const std::string &outputFileName){
    bool result = writeMessageToFile(outputFileName, this->messageReadable);
    return result;
}

bool opcommMessage::appendMessageReadableToFile(const std::string &outputFileName){
    bool result = appendMessageToFile(outputFileName, this->messageReadable);
    return result;
}

bool opcommMessage::readMessageReadableFromFile_ReplacingExistingMessages(const std::string &inputFileName){
    bool result = readMessageFromFile_ReplacingExistingMessages(inputFileName, this->messageReadable);
    getSyncFromMessageReadable();
    return result;
}


bool opcommMessage::writeMessageReadableBitPatternToFile(const std::string &outputFileName){
    bool result = writeBitPatternToFile(outputFileName, this->messageReadable);
    return result;
}

bool opcommMessage::appendMessageReadableBitPatternToFile(const std::string &outputFileName){
    bool result = appendBitPatternToFile(outputFileName, this->messageReadable);
    return result;
}

bool opcommMessage::readMessageReadableBitPatternFromFile_ReplacingExistingMessages(const std::string &inputFileName){
    bool result = readBitPatternFromFile_ReplacingExistingMessages(inputFileName, this->messageReadable);
    getSyncFromMessageReadable();
    return result;
}



std::string opcommMessage::messageReableToString(){
    return toString(this->messageReadable);
}

std::string opcommMessage::messageReadableToBitPattern(){
    return toBitPattern(this->messageReadable);
}

// MessageEncrypted
void opcommMessage::printMessageEncrypted(){
    printMessage(this->messageEncrypted);
}

void opcommMessage::appendToMessageEncryped(const std::string &trailingMessage) {
    appendToMessage(trailingMessage, this->messageEncrypted);
    getSyncFromMessageEncrypted();
}

void opcommMessage::replaceMessageEncryptedWith(const std::string &newMessage){
    replaceMessageWith(newMessage, this->messageEncrypted);
    getSyncFromMessageEncrypted();
}


bool opcommMessage::writeMesageEncryptedToFile(const std::string &outputFileName){
    bool result = writeMessageToFile(outputFileName, this->messageEncrypted);
    return result;
}

bool opcommMessage::appendMessageEncryptedToFile(const std::string &outputFileName){
    bool result = appendMessageToFile(outputFileName, this->messageEncrypted);
    return result;
}

bool opcommMessage::readMessageEncryptedFromFile_ReplacingExistingMessage(const std::string &inputFileName){
    bool result = readMessageFromFile_ReplacingExistingMessages(inputFileName, this->messageEncrypted);
    getSyncFromMessageEncrypted();
    return result;
}


bool opcommMessage::writeMessageEncryptedBitPatternToFile(const std::string &outputFileName){
    bool result = writeBitPatternToFile(outputFileName, this->messageEncrypted);
    return result;
}

bool opcommMessage::appendMessageEncryptedBitPatternToFile(const std::string &outputFileName){
    bool result = appendBitPatternToFile(outputFileName, this->messageEncrypted);
    return result;
}

bool opcommMessage::readMessageEncryptedBitPatternFromFile_ReplacingExistingMessage(const std::string &inputFileName){
    bool result = readBitPatternFromFile_ReplacingExistingMessages(inputFileName, this->messageEncrypted);
    getSyncFromMessageEncrypted();
    return result;
}


std::string opcommMessage::messageEncryptedToString(){
    return toString(this->messageEncrypted);
}

std::string opcommMessage::messageEncryptedToBitPattern(){
    return toBitPattern(this->messageEncrypted);
}

// MessageEncryptedChecksum
void opcommMessage::printMessageEncryptedChecksum(){
    printMessage(this->messageEncryptedChecksum);
}

void opcommMessage::appendToMessageEncryptedChecksum(const std::string &trailingMessage){
    appendToMessage(trailingMessage, this->messageEncryptedChecksum);
    getSyncFromMessageEncryptedChecksum();
}

void opcommMessage::replaceMessageEncryptedChecksumWith(const std::string &newMessage){
    replaceMessageWith(newMessage, this->messageEncryptedChecksum);
    getSyncFromMessageEncryptedChecksum();
}


bool opcommMessage::writeMesageEncryptedChecksumToFile(const std::string &outputFileName){
    bool result = writeMessageToFile(outputFileName, this->messageEncryptedChecksum);
    return result;
}

bool opcommMessage::appendMessageEncryptedChecksumToFile(const std::string &outputFileName){
    bool result = appendMessageToFile(outputFileName, this->messageEncryptedChecksum);
    return result;
}

bool opcommMessage::readMessageEncryptedChecksumFromFile_ReplacingExistingMessage(const std::string &inputFileName){
    bool result = readMessageFromFile_ReplacingExistingMessages(inputFileName, this->messageEncryptedChecksum);
    getSyncFromMessageEncryptedChecksum();
    return result;
}


bool opcommMessage::writeMessageEncryptedChecksumBitPatternToFile(const std::string &outputFileName){
    bool result = writeBitPatternToFile(outputFileName, this->messageEncryptedChecksum);
    return result;
}

bool opcommMessage::appendMessageEncryptedChecksumBitPatternToFile(const std::string &outputFileName){
    bool result = appendBitPatternToFile(outputFileName, this->messageEncryptedChecksum);
    return result;
}

bool opcommMessage::readMessageEncryptedChecksumBitPatternFromFile_ReplacingExistingMessage(const std::string &inputFileName){
    bool result = readBitPatternFromFile_ReplacingExistingMessages(inputFileName, this->messageEncryptedChecksum);
    getSyncFromMessageEncryptedChecksum();
    return result;
}

std::string opcommMessage::messageEncryptedChecksumToString(){
    return toString(this->messageEncryptedChecksum);
}

std::string opcommMessage::messageEncryptedChecksumToBitPattern(){
    return toBitPattern(this->messageEncryptedChecksum);
}

// Private Helper Functions
void opcommMessage::printMessage(const std::vector<unsigned char> &messageContainer){
    std::cout << toString(messageContainer);
}

void opcommMessage::appendToMessage(const std::string& messageTrailing, std::vector<unsigned char> &messageContainer){
    messageContainer.push_back('\r');
    messageContainer.push_back('\n');
    copy(messageTrailing.begin(), messageTrailing.end(), back_inserter(messageContainer));
}

void opcommMessage::replaceMessageWith(const std::string &newMessage, std::vector<unsigned char> &messageContainer){
    messageContainer.clear();
    copy(newMessage.begin(), newMessage.end(), back_inserter(messageContainer));
}

bool opcommMessage::readMessageFromFile_ReplacingExistingMessages(const std::string &inputFileName, std::vector<unsigned char> &messageContainer) {
    std::ifstream inputFile(inputFileName.c_str(), std::fstream::in);
    bool fileIsOpen = inputFile.is_open();
    if (fileIsOpen){
        eraseMessage();
        std::string line;
        unsigned int counter = 0;
        while (getline(inputFile, line)){
            if (counter == 0){
                replaceMessageWith(line, messageContainer);
            } else {
                appendToMessage(line, messageContainer);
            }
            counter ++;
        }
    }
    inputFile.clear();
    inputFile.close();
    return fileIsOpen;
}

void opcommMessage::publishMessageToFile(std::ofstream &outputFile, const std::vector<unsigned char> &messageContainer){
    outputFile << toString(messageContainer);
}

bool opcommMessage::appendMessageToFile(const std::string &outputFileName, const std::vector<unsigned char> &messageContainer){
    std::ofstream outputFile(outputFileName.c_str(), std::fstream::out | std::fstream::app);
    bool fileIsOpen = outputFile.is_open();
    if (fileIsOpen){
        outputFile << std::endl;
        publishMessageToFile(outputFile, messageContainer);
    }
    outputFile.clear();
    outputFile.close();
    return fileIsOpen;
}

bool opcommMessage::writeMessageToFile(const std::string &outputFileName, const std::vector<unsigned char> &messageContainer){
    std::ofstream outputFile(outputFileName.c_str(), std::fstream::out | std::fstream::trunc);
    bool fileIsOpen = outputFile.is_open();
    if (fileIsOpen){
        publishMessageToFile(outputFile, messageContainer);
    }
    outputFile.clear();
    outputFile.close();
    return fileIsOpen;
}

bool opcommMessage::readBitPatternFromFile_ReplacingExistingMessages(const std::string &inputFileName, std::vector<unsigned char> &messageContainer) {
    std::ifstream inputFile(inputFileName.c_str(), std::fstream::in);
    bool fileIsOpen = inputFile.is_open();
    if (fileIsOpen){
        eraseMessage();
        std::string line;
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
    }
    inputFile.clear();
    inputFile.close();
    return fileIsOpen;
}

bool opcommMessage::appendBitPatternToFile(const std::string &outputFileName, const std::vector<unsigned char> &messageContainer){
    std::ofstream outputFile(outputFileName.c_str(), std::fstream::out | std::fstream::app);
    bool fileIsOpen = outputFile.is_open();
    if (fileIsOpen){
        outputFile << convertCharToBit('\r') << convertCharToBit('\n');
        outputFile << std::endl;
        publishBitPatternToFile(outputFile, messageContainer);
    }
    outputFile.clear();
    outputFile.close();
    return fileIsOpen;
}

bool opcommMessage::writeBitPatternToFile(const std::string &outputFileName, const std::vector<unsigned char> &messageContainer){
    std::ofstream outputFile(outputFileName.c_str(), std::fstream::out | std::fstream::trunc);
    bool fileIsOpen = outputFile.is_open();
    if (fileIsOpen){
        publishBitPatternToFile(outputFile, messageContainer);
    }
    outputFile.clear();
    outputFile.close();
    return fileIsOpen;
}

void opcommMessage::publishBitPatternToFile(std::ofstream &outputFile, const std::vector<unsigned char> &messageContainer){
    short counter = 0;
    for (std::vector<unsigned char>::const_iterator it = messageContainer.begin(); it != messageContainer.end(); ++ it){
        counter ++;
        if (counter > phraseLength){
            outputFile << std::endl;
            counter -= phraseLength;
        }
        outputFile << convertCharToBit(*it);
    }
}

std::string opcommMessage::toString(const std::vector<unsigned char> &messageContainer){
    std::string messageString(messageContainer.begin(), messageContainer.end());
    return messageString;
}

std::string opcommMessage::toBitPattern(const std::vector<unsigned char> &messageContainer){
    std::string bitPattern;
    for (std::vector<unsigned char>::const_iterator it = messageContainer.begin(); it != messageContainer.end(); ++ it){
        bitPattern += convertCharToBit(*it);
    }
    return bitPattern;
}

std::string opcommMessage::convertCharToBit(unsigned char ch){
    std::string bitPattern = "";
    for (size_t i = 0; i < CHAR_BIT; i++){
        if (ch & mask[i])
            bitPattern += '1';
        else
            bitPattern += '0';
    }
    return bitPattern;
}

unsigned char opcommMessage::convertBitToChar(const std::string &bitPattern) {
    assert(bitPattern.length() <= CHAR_BIT);

    unsigned char character = 0;
    for (size_t  i = 0; i < bitPattern.length(); i ++)
        if (bitPattern[i] == '1')
            character += mask[i];
    return character;
}

void opcommMessage::getSyncFromMessageReadable() {
    // Sequential Calls -- Order matters
    // Do NOT parallelize
    encryptMessage();
    addCheckSumOnEncrytedMessage();
}

void opcommMessage::getSyncFromMessageEncrypted() {
    // Interchangagable Steps
    // Can be parallelize if needed
    decryptMessage();
    addCheckSumOnEncrytedMessage();
}

void opcommMessage::getSyncFromMessageEncryptedChecksum() {
    // Sequential Calls -- Order matters
    // Do NOT parallelize
    removeCheckSumOnEncrytedMessage();
    decryptMessage();
}

void opcommMessage::encryptMessage() {
    switch (this->encryption) {
        case EncryptionMethodNone:
            replaceMessageWith(opcommEncryptionMethods::encrypt_NoEncryptionMethod(this), this->messageEncrypted);
            break;
    }
}

void opcommMessage::decryptMessage() {
    switch (this->encryption) {
        case EncryptionMethodNone:
            replaceMessageWith(opcommEncryptionMethods::decipher_NoEncryptionMedthod(this), this->messageReadable);
            break;
    }
}

void opcommMessage::addCheckSumOnEncrytedMessage() {
    switch (this->checksum) {
        case ChecksumMethodNone:
            replaceMessageWith(opcommChecksumMethods::addChecksum_NoChecksumMethod(this), this->messageEncryptedChecksum);
            break;
    }
}

void opcommMessage::removeCheckSumOnEncrytedMessage() {
    switch (this->checksum) {
        case ChecksumMethodNone:
            replaceMessageWith(opcommChecksumMethods::rmChecksum_noEncryptionMethod(this), this->messageEncrypted);
            break;
    }
}
