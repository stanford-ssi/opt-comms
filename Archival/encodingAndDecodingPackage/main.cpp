#include <iostream>
#include <assert.h>
#include "opcommmessage.h"

using namespace std;

static const string textFile = "test.bitpattern";
static const string messageFile = "test.message";

// Tests
int main() {
    opcommMessage test(opcommMessage::EncryptionMethodNone, opcommMessage::ChecksumMethodNone);
    test.replaceMessageWith(opcommMessage::MessageReadable, "Hello");
    test.printMessage(opcommMessage::MessageEncrypted);
    cout << endl << "--------------------" << endl;
    test.printMessage(opcommMessage::MessageEncryptedChecksum);
    cout << endl << "-------------------" << endl;
    test.replaceMessageWith(opcommMessage::MessageEncrypted, "Bye");
    cout << test.messageToString(opcommMessage::MessageEncrypted) << " : " << test.messageToBitPattern(opcommMessage::MessageEncryptedChecksum) << endl << "----------------" << endl;
    test.writeMessageToFile(opcommMessage::MessageEncrypted, messageFile);
    test.eraseMessage();
    cout << "erase messages : " << test.messageToString(opcommMessage::MessageEncrypted) << endl << "-----------" << endl;
    test.readMessageFromFile_ReplacingExistingMessages(opcommMessage::MessageEncryptedChecksum, messageFile);
    test.printMessage(opcommMessage::MessageEncrypted);
    cout << endl << "-------------" << endl;
    test.appendToMessage(opcommMessage::MessageReadable, "Hello");
    test.printMessage(opcommMessage::MessageEncrypted);
    cout << endl << " ------------ " <<  endl;
    test.writeMessageBitPatternToFile(opcommMessage::MessageEncrypted, textFile);
    test.eraseMessage();
    cout << "erase messages : " << test.messageToString(opcommMessage::MessageEncrypted) << endl <<"-------------" << endl;
    test.readMessageBitPatternFromFile_ReplacingExistingMessages(opcommMessage::MessageEncryptedChecksum, textFile);
    test.printMessage(opcommMessage::MessageEncrypted);
    test.writeMessageToFile(opcommMessage::MessageEncryptedChecksum, messageFile);
    cout << endl <<"-------------" << endl;

    test.eraseMessage();
    test.readMessageFromFile_ReplacingExistingMessages(opcommMessage::MessageEncrypted, messageFile);
    test.printMessage(opcommMessage::MessageEncrypted);
    cout << endl;

    opcommMessage testTwo;
    test.eraseMessage();
    test.replaceMessageWith(opcommMessage::MessageReadable, "Hello");
    testTwo.replaceMessageWith(opcommMessage::MessageReadable, "Hello");

    assert (test == testTwo);
    cout << (test != testTwo) << endl;
    assert (false == (test != testTwo));

    testTwo.appendToMessage(opcommMessage::MessageEncrypted, "Bye");
    assert (test != testTwo);

    opcommMessage testThree = testTwo;
    std::cout << "TestTwo : " << testTwo.messageToString(opcommMessage::MessageReadable) << std::endl;
    std::cout << "TestThree : " << testThree.messageToString(opcommMessage::MessageReadable) << std::endl;

    return 0;
}

