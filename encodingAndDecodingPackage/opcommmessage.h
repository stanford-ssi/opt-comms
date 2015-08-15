/** Author: Charlie Chenye Zhu
 *          chenye@stanford.edu
 *
 *  Base class for both opcommMessageReceived and opcommMessageSent
 *
 *  Defines and implements the constructors, operator =, ==, !=
 *  and IO support
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
        // Enumeration Definition
        enum ChecksumMethods{
            ChecksumMethodNone
        };

        enum EncryptionMethods{
            EncryptionMethodNone
        };

        // Constructor
        opcommMessage(EncryptionMethods enMethod = EncryptionMethodNone,
                      ChecksumMethods ckMethod = ChecksumMethodNone);

        // Operators
        inline bool operator == (opcommMessage &other){
            return ((encryption == other.getEncryptionMethod())
                    && (checksum == other.getChecksumMethod())
                    && (messageReableToString().compare(other.messageReableToString()) == 0));
        }

        inline bool operator != (opcommMessage &other){
            return ((encryption != other.getEncryptionMethod())
                     || (checksum != other.getChecksumMethod())
                     || (messageReableToString().compare(other.messageReableToString()) != 0));
        }

        opcommMessage& operator = (opcommMessage &other){
            encryption = other.getEncryptionMethod();
            checksum = other.getChecksumMethod();
            replaceMessageReadableWith(other.messageReableToString());
            return *this;
        }

        // Public Utility Functions
        EncryptionMethods getEncryptionMethod();
        ChecksumMethods getChecksumMethod();

        std::string EncryptionMethodToString();
        std::string ChecksumMethodToString();

        // IO Functions
        void eraseMessage();

        // -> MessageReadable
        void printMessageReadable();
        void appendToMessageReadable(const std::string &messageTrailing);
        void replaceMessageReadableWith(const std::string &newMessage);

        bool writeMessageReadableToFile(const std::string &outputFileName);
        bool appendMessageReadableToFile(const std::string &outputFileName);
        bool readMessageReadableFromFile_ReplacingExistingMessages(const std::string &inputFileName);

        bool writeMessageReadableBitPatternToFile(const std::string &outputFileName);
        bool appendMessageReadableBitPatternToFile(const std::string &outputFileName);
        bool readMessageReadableBitPatternFromFile_ReplacingExistingMessages(const std::string &inputFileName);

        std::string messageReableToString();
        std::string messageReadableToBitPattern();

        // -> MessageEncrypted
        void printMessageEncrypted();
        void appendToMessageEncryped(const std::string &trailingMessage);
        void replaceMessageEncryptedWith(const std::string &newMessage);

        bool writeMesageEncryptedToFile(const std::string &outputFileName);
        bool appendMessageEncryptedToFile(const std::string &outputFileName);
        bool readMessageEncryptedFromFile_ReplacingExistingMessage(const std::string &inputFileName);

        bool writeMessageEncryptedBitPatternToFile(const std::string &outputFileName);
        bool appendMessageEncryptedBitPatternToFile(const std::string &outputFileName);
        bool readMessageEncryptedBitPatternFromFile_ReplacingExistingMessage(const std::string &inputFileName);

        std::string messageEncryptedToString();
        std::string messageEncryptedToBitPattern();

        // -> MessageEncryptedChecksum
        void printMessageEncryptedChecksum();
        void appendToMessageEncryptedChecksum(const std::string &trailingMessage);
        void replaceMessageEncryptedChecksumWith(const std::string &newMessage);

        bool writeMesageEncryptedChecksumToFile(const std::string &outputFileName);
        bool appendMessageEncryptedChecksumToFile(const std::string &outputFileName);
        bool readMessageEncryptedChecksumFromFile_ReplacingExistingMessage(const std::string &inputFileName);

        bool writeMessageEncryptedChecksumBitPatternToFile(const std::string &outputFileName);
        bool appendMessageEncryptedChecksumBitPatternToFile(const std::string &outputFileName);
        bool readMessageEncryptedChecksumBitPatternFromFile_ReplacingExistingMessage(const std::string &inputFileName);

        std::string messageEncryptedChecksumToString();
        std::string messageEncryptedChecksumToBitPattern();

    protected:
        // Static constants
        static const short phraseLength = 50;
        static unsigned char mask [CHAR_BIT];   // initialize in .cpp file

        // Helper functions (available for childrens)
        std::string convertCharToBit(unsigned char ch);
        unsigned char convertBitToChar(const std::string & bitPattern);

        // Member variables
        std::vector<unsigned char> messageReadable;
        std::vector<unsigned char> messageEncrypted;
        std::vector<unsigned char> messageEncryptedChecksum;

        EncryptionMethods encryption;
        ChecksumMethods checksum;

    private:      
        // IO Helper Functions
        void printMessage(const std::vector<unsigned char> & messageContainer);
        void appendToMessage(const std::string &messageTrailing, std::vector<unsigned char> & messageContainer);
        void replaceMessageWith(const std::string &newMessage, std::vector<unsigned char> & messageContainer);

        bool writeMessageToFile(const std::string &outputFileName, const std::vector<unsigned char> & messageContainer);
        bool appendMessageToFile(const std::string &outputFileName, const std::vector<unsigned char> & messageContainer);
        bool readMessageFromFile_ReplacingExistingMessages(const std::string &inputFileName, std::vector<unsigned char> & messageContainer);

        bool writeBitPatternToFile(const std::string &outputFileName, const std::vector<unsigned char> & messageContainer);
        bool appendBitPatternToFile(const std::string &outputFileName, const std::vector<unsigned char> & messageContainer);
        // input file consists of 0s and 1s
        bool readBitPatternFromFile_ReplacingExistingMessages(const std::string &inputFileName, std::vector<unsigned char> & messageContainer);

        std::string toString(const std::vector<unsigned char> & messageContainer);
        std::string toBitPattern(const std::vector<unsigned char> & messageContainer);        
        void publishBitPatternToFile(std::ofstream &outputFile, const std::vector<unsigned char> & messageContainer);
        void publishMessageToFile(std::ofstream &outputFile, const std::vector<unsigned char> & messageContainer);


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
