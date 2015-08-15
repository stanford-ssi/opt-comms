#include "opcommchecksummethods.h"

class opcommMessage;

namespace opcommChecksumMethods {

    std::string addChecksum_NoChecksumMethod (opcommMessage* currentOpcommMessage){
        std::string encryptedMessage = currentOpcommMessage->messageEncryptedToString();
        return encryptedMessage;
    }

    std::string rmChecksum_noEncryptionMethod (opcommMessage* currentOpcommMessage){
        std::string checksumMessage = currentOpcommMessage->messageEncryptedChecksumToBitPattern();
        return checksumMessage;
    }

}
