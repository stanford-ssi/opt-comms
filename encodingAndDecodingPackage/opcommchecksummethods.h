#include "opcommmessage.h"

#ifndef OPCOMMCHECKSUMMETHODS_H
#define OPCOMMCHECKSUMMETHODS_H

class opcommMessage;

namespace opcommChecksumMethods {

    std::string addChecksum_NoChecksumMethod (opcommMessage* currentOpcommMessage);
    std::string rmChecksum_noEncryptionMethod (opcommMessage* currentOpcommMessage);

}

#endif // OPCOMMCHECKSUMMETHODS_H
