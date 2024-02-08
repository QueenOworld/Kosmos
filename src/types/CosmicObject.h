#ifndef COSMIC_OBJECT_H
#define COSMIC_OBJECT_H

struct CosmicObject {
    CosmicObject(int x, int y, int z) {
        Hash = x + (y << 10) + (z << 20);
    }
    int Hash;
};

#endif