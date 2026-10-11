#include <iostream>

#include "global.hpp"
#include "wave.hpp"

class Engine : public ofBaseApp {

    public:

        ofCamera cam;
        float initialCamZoom = 0.45f;
        float initialCamBoom = -(525 / 2) + 200;
        float camZoom = initialCamZoom;
        float camSpeed = 3 / camZoom;

        WaveObject wave = WaveObject(20);

        void setup() override {
            
            ofSetWindowTitle("wave-equation");
            ofSetWindowPosition((ofGetScreenWidth() - WIDTH) / 2, (ofGetScreenHeight() - HEIGHT) / 2);
            font.load("../../fonts/Consolas.ttf", 15);
            ofBackground(20);

            ofEnableDepthTest();

            // ========== //

            cam.setPosition(1, 1, 1);
            cam.setNearClip(-5000);
            cam.lookAt({0, 0, 0});
            cam.rollDeg(120);
            cam.boom(initialCamBoom);
            cam.enableOrtho();

            // ========== //

        }

        void update() override {

            WIDTH = ofGetWindowWidth();
            HEIGHT = ofGetWindowHeight();

            if (ofGetKeyPressed('w')) cam.boom(camSpeed);
            if (ofGetKeyPressed('a')) cam.truck(-camSpeed);
            if (ofGetKeyPressed('s')) cam.boom(-camSpeed);
            if (ofGetKeyPressed('d')) cam.truck(camSpeed);

            wave.update();

        }

        void draw() override {

            static std::string fpsStr, dtStr;
            if (ofGetFrameNum() % 36 == 0) {

                fpsStr = "fps: " + ofToString(ofGetFrameRate(), 3);
                dtStr =  "dt: " + ofToString(dt, 6);

            } 

            // ========== //

            cam.begin(); ofScale(camZoom);

                // bounding box
                ofSetColor(255);
                ofNoFill();
                ofDrawBox({500, 500, 50}, 1000, 1000, 100);

                // origin
                ofFill();
                ofDrawSphere({0, 0, 0}, 5);

                // axis lines
                ofDrawLine({0, 0, 0}, {1500, 0, 0}); ofDrawSphere({1500, 0, 0}, 5);
                ofDrawLine({0, 0, 0}, {0, 1500, 0}); ofDrawSphere({0, 1500, 0}, 5);
                ofDrawLine({0, 0, 0}, {0, 0, 500});  ofDrawSphere({0, 0, 500}, 5);

                wave.render();

            cam.end();

            // ========== //

            ofDisableDepthTest();
            ofSetColor(100);
            font.drawString(fpsStr, 10, 25);
            font.drawString(dtStr, 10, 45);
            font.drawString("WASD to move", 10, HEIGHT - 65);
            font.drawString("SCROLL to zoom", 10, HEIGHT - 45);
            font.drawString("RMB to reset cam", 10, HEIGHT - 25);
            font.drawString("LMB to create waves", 10, HEIGHT - 5);

        }

        void mouseScrolled(int x, int y, float scrollX, float scrollY) override {

            camZoom *= pow(1.1f, scrollY);
            camZoom = ofClamp(camZoom, 0.2f, 2.5f);

        }

        void mousePressed(int x, int y, int button) override {

            if (button == OF_MOUSE_BUTTON_RIGHT) {
                
                cam.setPosition(1, 1, 1);
                cam.boom(initialCamBoom);
                camZoom = initialCamZoom;

            }

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