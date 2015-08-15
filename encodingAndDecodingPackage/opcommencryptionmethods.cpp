#include "opcommencryptionmethods.h"
#include <iostream>

class opcommMessage;

namespace opcommEncryptionMethods
{
    std::string encrypt_NoEncryptionMethod(opcommMessage *currentMessage){
        std::string readableMessage = currentMessage->messageReableToString();
        return readableMessage;
    }

    std::string decipher_NoEncryptionMedthod(opcommMessage *currentMessage){
        std::string encrypteMessage = currentMessage->messageEncryptedToString();
        return encrypteMessage;
    }
}
