// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?label=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("3dcoin://AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?amount=100&label=Some Example&message=Some Example Message&IS=1"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));
    QVERIFY(rv.message == QString("Some Example Message"));
    QVERIFY(rv.fUseInstantSend == 1);

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?amount=100&label=Some Example&message=Some Example Message&IS=Something Invalid"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));
    QVERIFY(rv.message == QString("Some Example Message"));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?IS=1"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend == 1);

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6?IS=0"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("3dcoin:AsC7D6FUAjrcCuHDeQ76Ao5dWTS9i7ZZu6"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);
}
