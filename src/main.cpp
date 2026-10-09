#include <iostream>

#include "global.hpp"

class Engine : public ofBaseApp {

    public:

        void setup() override {
            
            ofSetWindowTitle("of-project-template");
            ofSetWindowPosition((ofGetScreenWidth() - WIDTH) / 2, (ofGetScreenHeight() - HEIGHT) / 2);
            font.load("../../fonts/Consolas.ttf", 15);
            ofBackground(20);

            // ========== //

            

            // ========== //

        }

        void draw() override {

            static std::string fpsStr, dtStr;
            if (ofGetFrameNum() % 72 == 0) {

                fpsStr = "fps: " + ofToString(ofGetFrameRate(), 3);
                dtStr =  "dt: " + ofToString(dt, 6);

            } 

            // ========== //

            

            // ========== //

            ofSetColor(100);
            font.drawString(fpsStr, 10, 25);
            font.drawString(dtStr, 10, 45);

        }
};

int main() {

    ofSetLogLevel(OF_LOG_ERROR);
    ofGLWindowSettings settings;
    settings.setGLVersion(4, 6);
    settings.setSize(WIDTH, HEIGHT);
    ofCreateWindow(settings);
    ofRunApp(new Engine());

}