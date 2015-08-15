#include "opcommmessage.h"

#ifndef OPCOMMENCRYPTIONMETHODS_H
#define OPCOMMENCRYPTIONMETHODS_H

class opcommMessage;

namespace opcommEncryptionMethods
{
    std::string encrypt_NoEncryptionMethod (opcommMessage* currentMessage);
    std::string decipher_NoEncryptionMedthod (opcommMessage* currentMessage);
}

#endif // OPCOMMENCRYPTIONMETHODS_H
