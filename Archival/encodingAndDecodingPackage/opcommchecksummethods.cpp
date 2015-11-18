/** Author : Charlie Chenye Zhu
 *           chenye@stanford.edu
 *
 *  Namespaces containing AddingChecksum and RemovingChecksum methods.
 *      Comsumed by opcommMessage class
 */
#include "opcommchecksummethods.h"

class opcommMessage;

namespace opcommChecksumMethods {

    std::string addChecksum_NoChecksumMethod (const std::string &encryptedMessage){
        return encryptedMessage;
    }

    std::string rmChecksum_NoChecksumMethod (const std::string &checksumMessage){
        return checksumMessage;
    }

}
