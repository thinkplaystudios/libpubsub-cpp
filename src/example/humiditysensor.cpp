/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    humiditysensor.cpp
 * @date    6/30/2015
 * @author  Peter Spiess-Knafl <dev@spiessknafl.at>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "HumiditySensor.h"
#include <pubsubcpp/connector/udpbroadcastserver.h>
#include <iostream>

using namespace std;
using namespace jsonrpc;

class Handler : public jsonrpc::IClientConnectionHandler
{
        virtual void HandleRequest(const std::string& request, std::string& retValue)
        {
            retValue = request + "a";
            cout << "received request" << endl;
        }

};

int main()
{
    Handler h;
    UdpBroadcastServer s(7777, "127.255.255.255");
    s.SetHandler(&h);

    s.StartListening();

    UdpBroadcastClient c(7777, "127.255.255.255");


    string result;
    c.SendRPCMessage("fooo", result);

    sleep(1);

    cout << "Result: " << result << endl;

    return 0;
}
