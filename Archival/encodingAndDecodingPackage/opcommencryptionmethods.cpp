/** Author : Charlie Chenye Zhu
 *           chenye@stanford.edu
 *
 *  Namespaces containing Encrytion and Decryption methods.
 *      Comsumed by opcommMessage class
 */

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
