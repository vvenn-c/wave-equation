#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#include "global.hpp"

class WaveObject {

    private:

        std::vector<std::vector<float>> U; // scalar field
        std::vector<std::vector<float>> V; // velocity field(?)
        float c; // speed of propogation

        int div; // number of discrete elements in the field per axis
        int ds; // unit size of each division

        float getLaplacian(int x, int y);
        float damping(int x, int y);

        ofMesh mesh;

    public:

        WaveObject(int resolution, float speedOfPropogation);

        void update();
        void render();

        int frequency = 0;

};