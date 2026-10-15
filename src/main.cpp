#include <iostream>

#include "global.hpp"
#include "wave.hpp"

class Engine : public ofBaseApp {

    public:

        ofCamera cam;
        float initialCamZoom = 0.45f;
        float initialCamBoom = -(525 / 2) + 150;
        float camZoom = initialCamZoom;
        float camSpeed = 3 / camZoom;
        float originalDt = dt;

        WaveObject wave = WaveObject(200, 1000);

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

                int padding = 50;

                // origin
                ofFill();
                ofSetColor(100);
                ofDrawSphere({-padding, -padding, 0}, 5);

                // axis lines
                ofDrawLine({-padding, -padding, 0}, {1500, -padding, 0}); ofDrawSphere({1500, -padding, 0}, 5);
                ofDrawLine({-padding, -padding, 0}, {-padding, 1500, 0}); ofDrawSphere({-padding, 1500, 0}, 5);
                ofDrawLine({-padding, -padding, 0}, {-padding, -padding, 500}); ofDrawSphere({-padding, -padding, 500}, 5);

                // box
                ofNoFill();
                ofDrawBox({625 - padding, 625 - padding, 50}, 1250, 1250, 100);

                wave.render();

             cam.end();

            // ========== //

            ofDisableDepthTest();
            ofSetColor(100);

            font.drawString(fpsStr, 10, 25);
            font.drawString(dtStr, 10, 45);

            font.drawString("frequency: " + ofToString(wave.frequency) + "hz", 10, 85);
            if (paused == true) font.drawString("[PAUSED]", 10, 125);

            font.drawString("P to pause", 10, HEIGHT - 85);
            font.drawString("WASD to move", 10, HEIGHT - 65);
            font.drawString("SCROLL to zoom", 10, HEIGHT - 45);
            font.drawString("RMB to reset cam", 10, HEIGHT - 25);
            font.drawString("< > to adjust frequency", 10, HEIGHT - 5);

        }

        void mouseScrolled(int x, int y, float scrollX, float scrollY) override {

            camZoom *= pow(1.1f, scrollY);
            camZoom = ofClamp(camZoom, 0.2f, 5.0f);

        }

        void mousePressed(int x, int y, int button) override {

            if (button == OF_MOUSE_BUTTON_RIGHT) {
                
                cam.setPosition(1, 1, 1);
                cam.boom(initialCamBoom);
                camZoom = initialCamZoom;

            }

        }

        void keyPressed(int key) override {

            if (key == '.') wave.frequency++;
            if (key == ',') wave.frequency--;

            if (wave.frequency < 0) wave.frequency = 0;

            if (key == 'p') {

                if (paused == false) {

                    dt = 0;
                    paused = true;

                } else {

                    dt = originalDt;
                    paused = false;

                }

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