#include "wave.hpp"

void WaveObject::update() {

    

}

void WaveObject::render() {

    ofSetIcoSphereResolution(1);
    for (int x = 0; x <= 1000; x += cellSize) {
        for (int y = 0; y <= 1000; y += cellSize) {

            ofDrawIcoSphere({x, y, U[x / cellSize][y / cellSize]}, 2);

        }
    }

}