/** Author: Charlie Chenye Zhu
 *          chenye@stanford.edu
 *
 *  Base class for both opcommMessageReceived and opcommMessageSent
 *
 *  Defines and implements the class constructor, operator =, ==, !=
 *  and external IO interfaces
 *
 *  Internally handles the encryptions and checksum related functions
 */
#include <vector>
#include <string>
#include <fstream>

#ifndef OPCOMMMESSAGE_H
#define OPCOMMMESSAGE_H

#include "opcommencryptionmethods.h"
#include "opcommchecksummethods.h"


class opcommMessage {
    public:
        // Enumeration Definition - 03 style
        enum ChecksumMethods{
            ChecksumMethodNone
        };

        enum EncryptionMethods{
            EncryptionMethodNone
        };

        enum MessageType{
            MessageReadable,
            MessageEncrypted,
            MessageEncryptedChecksum
        };

        // Constructor
        opcommMessage(EncryptionMethods enMethod = EncryptionMethodNone,
                      ChecksumMethods ckMethod = ChecksumMethodNone);

        // Operators
        inline bool operator == (opcommMessage &other){
            return ((encryption == other.getEncryptionMethod())
                    && (checksum == other.getChecksumMethod())
                    && (Helper_toString(containerMessageReadable).compare(other.messageToString(MessageReadable)) == 0));
        }

        inline bool operator != (opcommMessage &other){
            return ((encryption != other.getEncryptionMethod())
                     || (checksum != other.getChecksumMethod())
                     || (Helper_toString(containerMessageReadable).compare(other.messageToString(MessageReadable)) != 0));
        }

        opcommMessage& operator = (opcommMessage &other){
            encryption = other.getEncryptionMethod();
            checksum = other.getChecksumMethod();
            Helper_ReplaceMessageWith(other.messageToString(MessageReadable), containerMessageReadable);
            return *this;
        }

        // Public Utility Functions
        EncryptionMethods getEncryptionMethod();
        ChecksumMethods getChecksumMethod();

        std::string EncryptionMethodToString();
        std::string ChecksumMethodToString();

        // IO Functions
        // Standardized and unified IO interface for all message types
        void eraseMessage();

        void printMessage(MessageType messageType);
        void appendToMessage(MessageType messageType, const std::string &messageTrailing);
        void replaceMessageWith(MessageType messageType, const std::string &newMessage);

        bool writeMessageToFile(MessageType messageType, const std::string &outputFileName);
        bool appendMessageToFile(MessageType messageType, const std::string &outputFileName);
        bool readMessageFromFile_ReplacingExistingMessages(MessageType messageType, const std::string &inputFileName);

        bool writeMessageBitPatternToFile(MessageType messageType, const std::string &outputFileName);
        bool appendMessageBitPatternToFile(MessageType messageType, const std::string &outputFileName);
        bool readMessageBitPatternFromFile_ReplacingExistingMessages(MessageType messageType, const std::string &inputFileName);

        std::string messageToString(MessageType messageType);
        std::string messageToBitPattern(MessageType messageType);

    protected:
        // Static constants
        static const short phraseLength = 50;
        static unsigned char mask [CHAR_BIT];   // initialize in .cpp file

        // Helper functions (available for childrens)
        std::string convertCharToBit(unsigned char ch);
        unsigned char convertBitToChar(const std::string & bitPattern);

        // Member variables
        std::vector<unsigned char> containerMessageReadable;
        std::vector<unsigned char> containerMessageEncrypted;
        std::vector<unsigned char> containerMessageEncryptedChecksum;

        EncryptionMethods encryption;
        ChecksumMethods checksum;

    private:      
        // IO Helper Functions
        inline std::string Helper_IOErrorMessage_UnrecognizedMessageType(const std::string & functionName){
            std::string errorMessage = "Error : Unrecognized MessageType parameters passed into " + functionName + "\r\n\tPlease update the function.";
            return errorMessage;
        }

        void Helper_PrintMessage(const std::vector<unsigned char> & messageContainer);
        void Helper_AppendToMessage(const std::string &messageTrailing, std::vector<unsigned char> & messageContainer);
        void Helper_ReplaceMessageWith(const std::string &newMessage, std::vector<unsigned char> & messageContainer);

        bool Helper_WriteMessageToFile(const std::string &outputFileName, const std::vector<unsigned char> & messageContainer);
        bool Helper_AppendMessageToFile(const std::string &outputFileName, const std::vector<unsigned char> & messageContainer);
        bool Helper_ReadMessageFromFile_ReplacingExistingMessages(const std::string &inputFileName, std::vector<unsigned char> & messageContainer);

        bool Helper_WriteBitPatternToFile(const std::string &outputFileName, const std::vector<unsigned char> & messageContainer);
        bool Helper_AppendBitPatternToFile(const std::string &outputFileName, const std::vector<unsigned char> & messageContainer);
        // input file consists of 0s and 1s
        bool Helper_ReadBitPatternFromFile_ReplacingExistingMessages(const std::string &inputFileName, std::vector<unsigned char> & messageContainer);

        std::string Helper_toString(const std::vector<unsigned char> & messageContainer);
        std::string Helper_toBitPattern(const std::vector<unsigned char> & messageContainer);

        void Helper_PublishBitPatternToFile(std::ofstream &outputFile, const std::vector<unsigned char> & messageContainer);
        void Helper_PublishMessageToFile(std::ofstream &outputFile, const std::vector<unsigned char> & messageContainer);


        // Syncronization helper functions
        void getSyncFromMessageReadable();
        void getSyncFromMessageEncrypted();
        void getSyncFromMessageEncryptedChecksum();

        // -> Encryption
        void encryptMessage();
        void decryptMessage();

        // -> Checksum
        void addCheckSumOnEncrytedMessage();
        void removeCheckSumOnEncrytedMessage();
};


#endif // OPCOMMMESSAGE_H
