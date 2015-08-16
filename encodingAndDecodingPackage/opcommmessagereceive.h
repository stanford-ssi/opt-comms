/** Author : Charlie Chenye Zhu
 *           chenye@stanford.edu
 *
 *  Class for opcommMessageReceive, child class of opcommMessage
 *
 *  To be implemented
 */
#include "opcommmessage.h"

#ifndef OPCOMMMESSAGERECEIVE_H
#define OPCOMMMESSAGERECEIVE_H

class opcommMessageReceive : public opcommMessage {
    public:
        opcommMessageReceive();
        bool validateChecksum();
    private:

};

#endif // OPCOMMMESSAGERECEIVE_H
