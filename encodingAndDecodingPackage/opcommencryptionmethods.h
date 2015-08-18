/** Author : Charlie Chenye Zhu
 *           chenye@stanford.edu
 *
 *  Namespaces containing Encrytion and Decryption methods.
 *      Comsumed by opcommMessage class
 */
#include "opcommmessage.h"

#ifndef OPCOMMENCRYPTIONMETHODS_H
#define OPCOMMENCRYPTIONMETHODS_H

namespace opcommEncryptionMethods
{
    extern std::string encrypt_NoEncryptionMethod (const std::string &readableMessage);
    extern std::string decipher_NoEncryptionMedthod (const std::string &encryptedMessage);
}

#endif // OPCOMMENCRYPTIONMETHODS_H
