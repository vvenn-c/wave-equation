#include "wave.hpp"

ofColor inferno(float t) {

    t = ofClamp(t, 0.0f, 1.0f);

    static const ofFloatColor stops[] = {
        ofFloatColor(0.001f, 0.000f, 0.014f), // 0.00 near-black
        ofFloatColor(0.259f, 0.038f, 0.406f), // 0.17 deep purple
        ofFloatColor(0.578f, 0.148f, 0.404f), // 0.33 magenta-purple
        ofFloatColor(0.865f, 0.317f, 0.226f), // 0.50 red-orange
        ofFloatColor(0.987f, 0.645f, 0.040f), // 0.67 orange
        ofFloatColor(0.950f, 0.930f, 0.350f), // 0.83 yellow
        ofFloatColor(0.988f, 1.000f, 0.644f)  // 1.00 pale yellow
    };

    const int n = 7;
    float f = t * (n - 1);
    int i = std::min((int)f, n - 2);
    float frac = f - i;

    ofFloatColor c = stops[i].getLerped(stops[i + 1], frac);
    return ofColor(c);

}

WaveObject::WaveObject(int divisions, float speedOfPropogation) {

    this->div = divisions;
    this->ds = 1000 / this->div;

    this->c = speedOfPropogation;

    U.assign(this->div + 1, std::vector<float>(this->div + 1, 0.f));
    V.assign(this->div + 1, std::vector<float>(this->div + 1, 0.f));

    for (int i = 0; i <= div - 1; i++) {
        for (int j = 0; j <= div - 1; j++) {

            int a = i * (div + 1) + j;         // (i,   j)
            int b = (i + 1) * (div + 1) + j;   // (i+1, j)
            int c = (i + 1) * (div + 1) + j + 1; // (i+1, j+1)
            int d = i * (div + 1) + j + 1;     // (i,   j+1)

            mesh.addIndex(a); mesh.addIndex(b); mesh.addIndex(c);
            mesh.addIndex(a); mesh.addIndex(c); mesh.addIndex(d);

        }
    }

}

void WaveObject::update() {

    static float pos = 50;
    static float vel, acc;

    float timeNormalizer = (1.f / 144) * frequency;

    acc = -pos * 1;
    vel += acc * timeNormalizer;
    pos += vel * timeNormalizer;

    if (paused == false && frequency > 0) U[div - 30][75] = pos;
    if (paused == false && frequency > 0) U[div - 30][div - 75] = pos;

    ofSetColor(255);
    ofDrawSphere(div - 30, 75, 5);
    ofDrawSphere(div - 30, div - 75, 5);


    for (int i = 0; i <= div; i++) {
        for (int j = 0; j <= div; j++) {

            float A = (c * c) * getLaplacian(i, j) - damping(i, j) * V[i][j];            
            V[i][j] += A * dt;

        }
    }

    for (int i = 0; i <= div; i++) {
        for (int j = 0; j <= div; j++)
            U[i][j] += V[i][j] * dt;
    }

}

void WaveObject::render() {

    mesh.clearVertices();
    mesh.clearColors();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    for (int x = 0; x <= 1000; x += ds) {
        for (int y = 0; y <= 1000; y += ds) {

            int i = x / ds;
            int j = y / ds;
            
            mesh.addVertex({x, y, ofClamp(U[i][j], -50, 50)});

            float k = 1.5f;
            float color = abs(U[i][j] / 50) * k * k;
            mesh.addColor(inferno(color));

        }
    }

    mesh.draw();

}

float WaveObject::getLaplacian(int x, int y) {

    float u = U[x][y];
    float Ux1, Ux2, Uy1, Uy2;

    if (x < div) Ux1 = U[x + 1][y];
    else Ux1 = u;

    if (y < div) Uy1 = U[x][y + 1];
    else Uy1 = u;

    if (x > 0) Ux2 = U[x - 1][y];
    else Ux2 = u;

    if (y > 0) Uy2 = U[x][y - 1];
    else Uy2 = u;

    float dx = (Ux1 - 2 * u + Ux2) / (ds * ds);
    float dy = (Uy1 - 2 * u + Uy2) / (ds * ds);

    return dx + dy;

}

float WaveObject::damping(int x, int y) {

    const int thickness = 20;
    const float coeffDamping = 100.f;

    int dist = std::min({x, div - x, y, div - y});
    if (dist >= thickness) return 0.f;

    float t = (thickness - dist) / (float)thickness;
    return coeffDamping * t * t;

}