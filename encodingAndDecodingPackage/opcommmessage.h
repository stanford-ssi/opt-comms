/** Author: Charlie Chenye Zhu
 *          chenye@stanford.edu
 *
 *  Base class for both opcommMessageReceived and opcommMessageSent
 *  Defines and implements the constructors, as well as a few util functions
 */
#include <vector>
#include <string>
#include <fstream>

#ifndef OPCOMMMESSAGE_H
#define OPCOMMMESSAGE_H

class opcommMessage {
    public:
        opcommMessage();

        void printMessage();
        void appendToMessage(const std::string &message);
        void replaceMessageWith(const std::string &newMessage);
        void eraseMessage();

        bool writeMessageToFile(const std::string &outputFileName);
        bool appendMessageToFile(const std::string &outputFileName);
        bool readMessageFromFile(const std::string &inputFileName);

        bool writeBitPatternToFile(const std::string &outputFileName);
        bool appendBitPatternToFile(const std::string &outputFileName);
        // input file consists of 0s and 1s
        bool readBitPatternFromFile(const std::string &inputFileName);

        std::string toString();

    protected:
        std::string convertCharToBit(unsigned char ch);
        unsigned char convertBitToChar(const std::string & bitPattern);

    private:
        std::vector<unsigned char> messageContainer;
        static const short phraseLength = 50;
        static unsigned char mask [CHAR_BIT];

        void publishBitPatternToFile(std::ofstream &outputFile);
        void publishMessageToFile(std::ofstream &outputFile);
};

#endif // OPCOMMMESSAGE_H
