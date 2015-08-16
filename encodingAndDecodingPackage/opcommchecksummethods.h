/** Author : Charlie Chenye Zhu
 *           chenye@stanford.edu
 *
 *  Namespaces containing AddingChecksum and RemovingChecksum methods.
 *      Comsumed by opcommMessage class
 */
#include "opcommmessage.h"

#ifndef OPCOMMCHECKSUMMETHODS_H
#define OPCOMMCHECKSUMMETHODS_H

class opcommMessage;

namespace opcommChecksumMethods {

    extern std::string addChecksum_NoChecksumMethod (const std::string &encryptedMessage);
    extern std::string rmChecksum_NoChecksumMethod (const std::string &checksumMessage);

}

#endif // OPCOMMCHECKSUMMETHODS_H
