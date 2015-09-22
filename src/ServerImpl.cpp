//
//  ServerImpl.cpp
//  CanonHTTP
//
//  Created by Jeffrey Crouse on 8/26/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#include "ServerImpl.h"
#include <Poco/URI.h>
#include "ofApp.h"


// ------------------------------------
void CanonRequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp) {
    
    ofApp* app = (ofApp*)ofGetAppPtr();
    HTTPResponse::HTTPStatus code;
    string response;
    
    Poco::URI uri( req.getURI() );
    ofLogNotice("CanonRequestHandler") << uri.getPath();
    
    if(!app->camera.isConnected()) {
        code = HTTPResponse::HTTP_SERVICE_UNAVAILABLE;
        response = "Camera not connected";
    }
    else if( uri.getPath()=="/status") {
        code = HTTPResponse::HTTP_OK;
        
        if(app->camera.isRecordingMovie()) response = "RECORDING";
        else response = "READY";
    }
    else if(uri.getPath() == "/takePhoto") {
        
        string query = uri.getQuery();
        bool returnFile = ofStringTimesInString(query, "return=file")>0;
   
        app->camera.takePhoto();
        while(!app->camera.isPhotoNew()){
            ofSleepMillis(10);
        }
        
        string path = app->basename()+".jpg";
        ofLogNotice("CanonRequestHandler") << path;
        
        app->camera.savePhoto(path);
        
        if(ofFile::doesFileExist(path)) {
            if(returnFile) {
                resp.setStatus(HTTPResponse::HTTP_OK);
                resp.sendFile(path, "image/jpeg");
                return;
            } else {
                code = HTTPResponse::HTTP_OK;
                response = path;
            }
        } else {
            code = HTTPResponse::HTTP_BAD_REQUEST;
            response = "File did not save";
        }
       
    } else if(uri.getPath()=="/beginMovieRecording") {
        if(app->camera.isRecordingMovie()) {
            
            code = HTTPResponse::HTTP_SERVICE_UNAVAILABLE;
            response = "Already recording.";
            
        } else {
            app->camera.beginMovieRecording();
            
            code = HTTPResponse::HTTP_OK;
            response = "OK";
        }
        
    } else if(uri.getPath()=="/endMovieRecording") {
        if(app->camera.isRecordingMovie()) {
        
            app->camera.endMovieRecording();
            
            while (!app->camera.isMovieNew()) {
                ofSleepMillis(10);
            }
            
            string path = app->basename()+".mov";
            ofLogNotice() << path;
            app->camera.savePhoto(path);
            

            if(ofFile::doesFileExist(path)) {
                response = path;
                code = HTTPResponse::HTTP_OK;
            } else {
                code = HTTPResponse::HTTP_INTERNAL_SERVER_ERROR;
                response ="File did not save";
            }
            
        } else {
            
            code = HTTPResponse::HTTP_SERVICE_UNAVAILABLE;
            response = "not recording.";
            
        }
    } else if(uri.getPath()=="/recordVideo") {
        if(app->camera.isRecordingMovie()) {
            code = HTTPResponse::HTTP_INTERNAL_SERVER_ERROR;
            response ="Already Recording";
        } else {
            string query = uri.getQuery();
            
        }
    }
    else {
        code = HTTPResponse::HTTP_BAD_REQUEST;
        response = "Bad request!";
    }
    
    
    resp.setStatus(code);
    resp.setContentType("text/html");
    ostream& out = resp.send();
    out << response;
    out.flush();
}
