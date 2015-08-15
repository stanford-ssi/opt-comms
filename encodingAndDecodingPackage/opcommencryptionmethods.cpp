#include "opcommencryptionmethods.h"

class opcommMessage;

namespace opcommEncryptionMethods
{
    std::string encrypt_NoEncryptionMethod(const std::string &readableMessage){
        return readableMessage;
    }

    std::string decipher_NoEncryptionMedthod(const std::string &encryptedMessage){
        return encryptedMessage;
    }
}
