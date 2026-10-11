#include <iostream>
#include <vector>

#include "global.hpp"

class WaveObject {

    private:

        // scalar field
        std::vector<std::vector<float>> U;

        int res, sideLength;
        int cellSize;

    public:

        WaveObject(int resolution) {

            this->res = resolution;
            this->cellSize = 1000 / this->res;
            this->sideLength = (1000 / this->cellSize) + 1;

            U.assign(this->sideLength, std::vector<float>(this->sideLength, 0.f));

        }

        void update();
        void render();

};