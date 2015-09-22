//
//  ServerImpl.h
//  CanonHTTP
//
//  Created by Jeffrey Crouse on 8/26/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>


using namespace Poco::Net;


class CanonRequestHandler : public HTTPRequestHandler {
public:
    CanonRequestHandler(){};
    void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp);
};


class CanonRequestHandlerFactory : public HTTPRequestHandlerFactory {
public:
    CanonRequestHandlerFactory(){}
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &) {
        return new CanonRequestHandler();
    }
};

