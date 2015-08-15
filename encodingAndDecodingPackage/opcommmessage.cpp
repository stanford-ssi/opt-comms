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
// Standardized and unified IO interface for all message types

void opcommMessage::eraseMessage(){
    this->containerMessageReadable.clear();
    this->containerMessageEncrypted.clear();
    this->containerMessageEncryptedChecksum.clear();
}

void opcommMessage::printMessage(MessageType messageType){
    switch (messageType) {
        case MessageReadable:
            Helper_PrintMessage(containerMessageReadable);
            break;
        case MessageEncrypted:
            Helper_PrintMessage(containerMessageEncrypted);
            break;
        case MessageEncryptedChecksum:
            Helper_PrintMessage(containerMessageEncryptedChecksum);
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("printMessage") << std::endl;
            break;
    }
}

void opcommMessage::appendToMessage(MessageType messageType, const std::string &messageTrailing){
    switch (messageType) {
        case MessageReadable:
            Helper_AppendToMessage(messageTrailing, containerMessageReadable);
            getSyncFromMessageReadable();
            break;
        case MessageEncrypted:
            Helper_AppendToMessage(messageTrailing, containerMessageEncrypted);
            getSyncFromMessageEncrypted();
            break;
        case MessageEncryptedChecksum:
            Helper_AppendToMessage(messageTrailing, containerMessageEncryptedChecksum);
            getSyncFromMessageEncryptedChecksum();
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("appendToMessage") << std::endl;
            break;
    }
}

void opcommMessage::replaceMessageWith(MessageType messageType, const std::string &newMessage){
    switch (messageType) {
        case MessageReadable:
            Helper_ReplaceMessageWith(newMessage, containerMessageReadable);
            getSyncFromMessageReadable();
            break;
        case MessageEncrypted:
            Helper_ReplaceMessageWith(newMessage, containerMessageEncrypted);
            getSyncFromMessageEncrypted();
            break;
        case MessageEncryptedChecksum:
            Helper_ReplaceMessageWith(newMessage, containerMessageEncryptedChecksum);
            getSyncFromMessageEncryptedChecksum();
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("replaceMessageWith") << std::endl;
            break;
    }
}


bool opcommMessage::writeMessageToFile(MessageType messageType, const std::string &outputFileName){
    bool result;
    switch (messageType) {
        case MessageReadable:
            result = Helper_WriteMessageToFile(outputFileName, containerMessageReadable);
            break;
        case MessageEncrypted:
            result = Helper_WriteMessageToFile(outputFileName, containerMessageEncrypted);
            break;
        case MessageEncryptedChecksum:
            result = Helper_WriteMessageToFile(outputFileName, containerMessageEncryptedChecksum);
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("writeMessageToFile") << std::endl;
            result = false;
            break;
    }
    return result;
}

bool opcommMessage::appendMessageToFile(MessageType messageType, const std::string &outputFileName){
    bool result;
    switch (messageType) {
        case MessageReadable:
            result = Helper_AppendMessageToFile(outputFileName, containerMessageReadable);
            break;
        case MessageEncrypted:
            result = Helper_AppendMessageToFile(outputFileName, containerMessageEncrypted);
            break;
        case MessageEncryptedChecksum:
            result = Helper_AppendMessageToFile(outputFileName, containerMessageEncryptedChecksum);
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("appendMessageToFile") << std::endl;
            result = false;
            break;
    }
    return result;
}

bool opcommMessage::readMessageFromFile_ReplacingExistingMessages(MessageType messageType, const std::string &inputFileName){
    bool result;
    switch (messageType) {
        case MessageReadable:
            result = Helper_ReadMessageFromFile_ReplacingExistingMessages(inputFileName, containerMessageReadable);
            if (result)
                getSyncFromMessageReadable();
            break;
        case MessageEncrypted:
            result = Helper_ReadMessageFromFile_ReplacingExistingMessages(inputFileName, containerMessageEncrypted);
            if (result)
                getSyncFromMessageEncrypted();
            break;
        case MessageEncryptedChecksum:
            result = Helper_ReadMessageFromFile_ReplacingExistingMessages(inputFileName, containerMessageEncryptedChecksum);
            if (result)
                getSyncFromMessageEncryptedChecksum();
            break;
        default:
            result = false;
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("readMessageFromFile_ReplacingExistingMessages") << std::endl;
            break;
    }
    return result;
}


bool opcommMessage::writeMessageBitPatternToFile(MessageType messageType, const std::string &outputFileName){
    bool result;
    switch (messageType) {
        case MessageReadable:
            result = Helper_WriteBitPatternToFile(outputFileName, containerMessageReadable);
            break;
        case MessageEncrypted:
            result = Helper_WriteBitPatternToFile(outputFileName, containerMessageEncrypted);
            break;
        case MessageEncryptedChecksum:
            result = Helper_WriteBitPatternToFile(outputFileName, containerMessageEncryptedChecksum);
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("writeMessageBitPatternToFile") << std::endl;
            result = false;
            break;
    }
    return result;
}

bool opcommMessage::appendMessageBitPatternToFile(MessageType messageType, const std::string &outputFileName){
    bool result;
    switch (messageType) {
        case MessageReadable:
            result = Helper_AppendBitPatternToFile(outputFileName, containerMessageReadable);
            break;
        case MessageEncrypted:
            result = Helper_AppendBitPatternToFile(outputFileName, containerMessageEncrypted);
            break;
        case MessageEncryptedChecksum:
            result = Helper_AppendBitPatternToFile(outputFileName, containerMessageEncryptedChecksum);
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("appendMessageBitPatternToFile") << std::endl;
            result = false;
            break;
    }
    return result;
}

bool opcommMessage::readMessageBitPatternFromFile_ReplacingExistingMessages(MessageType messageType, const std::string &inputFileName){
    bool result;
    switch (messageType) {
        case MessageReadable:
            result = Helper_ReadBitPatternFromFile_ReplacingExistingMessages(inputFileName, containerMessageReadable);
            if (result)
                getSyncFromMessageReadable();
            break;
        case MessageEncrypted:
            result = Helper_ReadBitPatternFromFile_ReplacingExistingMessages(inputFileName, containerMessageEncrypted);
            if (result)
                getSyncFromMessageEncrypted();
            break;
        case MessageEncryptedChecksum:
            result = Helper_ReadBitPatternFromFile_ReplacingExistingMessages(inputFileName, containerMessageEncryptedChecksum);
            if (result)
                getSyncFromMessageEncryptedChecksum();
            break;
        default:
            result = false;
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("readMessageBitPatternFromFile_ReplacingExistingMessages") << std::endl;
            break;
    }
    return result;
}


std::string opcommMessage::messageToString(MessageType messageType){
    switch (messageType) {
        case MessageReadable:
            return Helper_toString(containerMessageReadable);
            break;
        case MessageEncrypted:
            return Helper_toString(containerMessageEncrypted);
            break;
        case MessageEncryptedChecksum:
            return Helper_toString(containerMessageEncryptedChecksum);
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("messageToString") << std::endl;
            return "";
            break;
    }
}

std::string opcommMessage::messageToBitPattern(MessageType messageType){
    switch (messageType) {
        case MessageReadable:
            return Helper_toBitPattern(containerMessageReadable);
            break;
        case MessageEncrypted:
            return Helper_toBitPattern(containerMessageEncrypted);
            break;
        case MessageEncryptedChecksum:
            return Helper_toBitPattern(containerMessageEncryptedChecksum);
            break;
        default:
            std::cout << Helper_IOErrorMessage_UnrecognizedMessageType("messageToBitPattern") << std::endl;
            return "";
            break;
    }
}

// Private Helper Functions
void opcommMessage::Helper_PrintMessage(const std::vector<unsigned char> &messageContainer){
    std::cout << Helper_toString(messageContainer);
}

void opcommMessage::Helper_AppendToMessage(const std::string& messageTrailing, std::vector<unsigned char> &messageContainer){
    // Adding new line characters
    messageContainer.push_back('\r');
    messageContainer.push_back('\n');
    copy(messageTrailing.begin(), messageTrailing.end(), back_inserter(messageContainer));
}

void opcommMessage::Helper_ReplaceMessageWith(const std::string &newMessage, std::vector<unsigned char> &messageContainer){
    messageContainer.clear();
    copy(newMessage.begin(), newMessage.end(), back_inserter(messageContainer));
}

bool opcommMessage::Helper_ReadMessageFromFile_ReplacingExistingMessages(const std::string &inputFileName, std::vector<unsigned char> &messageContainer) {
    std::ifstream inputFile(inputFileName.c_str(), std::fstream::in);
    bool fileIsOpen = inputFile.is_open();
    if (fileIsOpen){
        eraseMessage();
        std::string line;
        unsigned int counter = 0;
        while (getline(inputFile, line)){
            if (counter == 0){
                Helper_ReplaceMessageWith(line, messageContainer);
            } else {
                Helper_AppendToMessage(line, messageContainer);
            }
            counter ++;
        }
    } else {
        std::cout << "Error: Unable to open " << "input" << " file " << inputFileName << "!" << std::endl;
    }
    inputFile.clear();
    inputFile.close();
    return fileIsOpen;
}

void opcommMessage::Helper_PublishMessageToFile(std::ofstream &outputFile, const std::vector<unsigned char> &messageContainer){
    outputFile << Helper_toString(messageContainer);
}

bool opcommMessage::Helper_AppendMessageToFile(const std::string &outputFileName, const std::vector<unsigned char> &messageContainer){
    std::ofstream outputFile(outputFileName.c_str(), std::fstream::out | std::fstream::app);
    bool fileIsOpen = outputFile.is_open();
    if (fileIsOpen){
        outputFile << std::endl;
        Helper_PublishMessageToFile(outputFile, messageContainer);
    } else {
        std::cout << "Error: Unable to open " << "output" << " file " << outputFileName << "!" << std::endl;
    }
    outputFile.clear();
    outputFile.close();
    return fileIsOpen;
}

bool opcommMessage::Helper_WriteMessageToFile(const std::string &outputFileName, const std::vector<unsigned char> &messageContainer){
    std::ofstream outputFile(outputFileName.c_str(), std::fstream::out | std::fstream::trunc);
    bool fileIsOpen = outputFile.is_open();
    if (fileIsOpen){
        Helper_PublishMessageToFile(outputFile, messageContainer);
    } else {
        std::cout << "Error: Unable to open " << "output"<< " file " << outputFileName << "!" << std::endl;
    }
    outputFile.clear();
    outputFile.close();
    return fileIsOpen;
}

bool opcommMessage::Helper_ReadBitPatternFromFile_ReplacingExistingMessages(const std::string &inputFileName, std::vector<unsigned char> &messageContainer) {
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
    } else {
        std::cout << "Error: Unable to open " << "input" << " file " << inputFileName << "!" << std::endl;
    }
    inputFile.clear();
    inputFile.close();
    return fileIsOpen;
}

bool opcommMessage::Helper_AppendBitPatternToFile(const std::string &outputFileName, const std::vector<unsigned char> &messageContainer){
    std::ofstream outputFile(outputFileName.c_str(), std::fstream::out | std::fstream::app);
    bool fileIsOpen = outputFile.is_open();
    if (fileIsOpen){
        outputFile << convertCharToBit('\r') << convertCharToBit('\n');
        outputFile << std::endl;
        Helper_PublishBitPatternToFile(outputFile, messageContainer);
    } else {
        std::cout << "Error: Unable to open " << "output" << " file " << outputFileName << "!" << std::endl;
    }
    outputFile.clear();
    outputFile.close();
    return fileIsOpen;
}

bool opcommMessage::Helper_WriteBitPatternToFile(const std::string &outputFileName, const std::vector<unsigned char> &messageContainer){
    std::ofstream outputFile(outputFileName.c_str(), std::fstream::out | std::fstream::trunc);
    bool fileIsOpen = outputFile.is_open();
    if (fileIsOpen){
        Helper_PublishBitPatternToFile(outputFile, messageContainer);
    } else {
        std::cout << "Error: Unable to open " << "output" << " file " << outputFileName << "!" << std::endl;
    }
    outputFile.clear();
    outputFile.close();
    return fileIsOpen;
}

void opcommMessage::Helper_PublishBitPatternToFile(std::ofstream &outputFile, const std::vector<unsigned char> &messageContainer){
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

std::string opcommMessage::Helper_toString(const std::vector<unsigned char> &messageContainer){
    std::string messageString(messageContainer.begin(), messageContainer.end());
    return messageString;
}

std::string opcommMessage::Helper_toBitPattern(const std::vector<unsigned char> &messageContainer){
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
            Helper_ReplaceMessageWith(opcommEncryptionMethods::encrypt_NoEncryptionMethod(messageToString(opcommMessage::MessageReadable)), this->containerMessageEncrypted);
            break;
    }
}

void opcommMessage::decryptMessage() {
    switch (this->encryption) {
        case EncryptionMethodNone:
            Helper_ReplaceMessageWith(opcommEncryptionMethods::decipher_NoEncryptionMedthod(messageToString(opcommMessage::MessageEncrypted)), this->containerMessageReadable);
            break;
    }
}

void opcommMessage::addCheckSumOnEncrytedMessage() {
    switch (this->checksum) {
        case ChecksumMethodNone:
            Helper_ReplaceMessageWith(opcommChecksumMethods::addChecksum_NoChecksumMethod(messageToString(opcommMessage::MessageEncrypted)), this->containerMessageEncryptedChecksum);
            break;
    }
}

void opcommMessage::removeCheckSumOnEncrytedMessage() {
    switch (this->checksum) {
        case ChecksumMethodNone:
            Helper_ReplaceMessageWith(opcommChecksumMethods::rmChecksum_NoChecksumMethod(messageToString(opcommMessage::MessageEncryptedChecksum)), this->containerMessageEncrypted);
            break;
    }
}
