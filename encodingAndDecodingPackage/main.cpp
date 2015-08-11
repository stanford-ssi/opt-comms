#include <iostream>
#include <assert.h>
#include "opcommmessage.h"

using namespace std;

static const string textFile = "test.bitpattern";
static const string messageFile = "test.message";

int main() {
    opcommMessage testMessage;
    testMessage.appendToMessage("This is a test message");
    testMessage.printMessage();
    testMessage.appendToMessage(" ... continue...");
    cout << testMessage.toString() << endl;
    testMessage.writeBitPatternToFile(textFile);

    opcommMessage testMessageVersionTwo;
    testMessageVersionTwo.appendToMessage("It's me again");
    cout << testMessageVersionTwo.toString() << endl;
    testMessageVersionTwo.replaceMessageWith("My favourite song is Fight Song");
    testMessageVersionTwo.printMessage();
    testMessageVersionTwo.writeMessageToFile(messageFile);

    opcommMessage testMessageVersionThree;
    testMessageVersionThree.readBitPatternFromFile(textFile);
    cout << "Read from file " << textFile << ": " <<  testMessageVersionThree.toString() << endl;

    testMessageVersionThree.readMessageFromFile(messageFile);
    cout << "Read from file " << messageFile << ": " << testMessageVersionThree.toString();

    return 0;
}

