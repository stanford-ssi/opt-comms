#include <iostream>
#include <assert.h>
#include "opcommmessage.h"

using namespace std;

static const string textFile = "test.bitpattern";
static const string messageFile = "test.message";

// Tests
int main() {
    opcommMessage test(opcommMessage::EncryptionMethodNone, opcommMessage::ChecksumMethodNone);
    test.replaceMessageReadableWith("Hello");
    test.printMessageEncrypted();
    cout << endl << "--------------------" << endl;
    test.printMessageEncryptedChecksum();
    cout << endl << "-------------------" << endl;
    test.replaceMessageEncryptedWith("Bye");
    cout << test.messageEncryptedToString() << " : " << test.messageEncryptedChecksumToBitPattern() << endl << "----------------" << endl;
    test.writeMesageEncryptedToFile(messageFile);
    test.eraseMessage();
    cout << "erase messages : " << test.messageEncryptedToString() << endl << "-----------" << endl;
    test.readMessageEncryptedChecksumFromFile_ReplacingExistingMessage(messageFile);
    test.printMessageEncrypted();
    cout << endl << "-------------" << endl;
    test.appendToMessageReadable("Hello");
    test.printMessageEncrypted();
    cout << endl << " ------------ " <<  endl;
    test.writeMessageEncryptedBitPatternToFile(textFile);
    test.eraseMessage();
    cout << "erase messages : " << test.messageEncryptedToString() << endl <<"-------------" << endl;
    test.readMessageEncryptedChecksumBitPatternFromFile_ReplacingExistingMessage(textFile);
    test.printMessageEncrypted();
    test.writeMesageEncryptedChecksumToFile(messageFile);
    cout << endl <<"-------------" << endl;

    test.eraseMessage();
    test.readMessageEncryptedFromFile_ReplacingExistingMessage(messageFile);
    test.printMessageEncrypted();
    cout << endl;

    opcommMessage testTwo;
    test.eraseMessage();
    test.replaceMessageReadableWith("Hello");
    testTwo.replaceMessageReadableWith("Hello");

    assert (test == testTwo);
    cout << (test != testTwo) << endl;
    assert (false == (test != testTwo));

    testTwo.appendToMessageEncryped("Bye");
    assert (test != testTwo);

    opcommMessage testThree = testTwo;
    std::cout << "TestTwo : " << testTwo.messageReableToString() << std::endl;
    std::cout << "TestThree : " << testThree.messageReableToString() << std::endl;

    return 0;
}

