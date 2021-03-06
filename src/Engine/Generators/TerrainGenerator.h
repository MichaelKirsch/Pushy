//this class can be consultated mainly by chunk or other classes to get terrain information about a certain point in the world.
//using this class will ensure that everything will get generated uniformly. This class can be used to say where water should be
//generated too. the watergenerator and the wildlifePlantGenerator will be heavyly dependent on this class.
//set this generator once and then use it throuout your code

#pragma once

#include "StateMachine/Essential.h"
#include "FastNoise/FastNoise.h"
#include "Cube.h"
#include <bitset>

class TerrainGenerator {
public:
    TerrainGenerator(StateEssentials &es) : stateEssentials(es) {};

    enum CUBE_SIDES {
        up = 0, down, right, left, front, back, free_slot1, free_slot2
    };

    void setUpGenerator(float freqency = 0.0015f, int i_max_terrain_height = 50,
                        FastNoise::NoiseType noiseType = FastNoise::Simplex);

    std::vector<Cube> generateCubesBelow(glm::ivec3 &worldPos,glm::ivec3 &positionInChunk, int& chunksize);

    int getTerrain(int x, int y);

    ~TerrainGenerator() = default;

private:

    struct cube_pos_and_sides {
        glm::u8vec3 cubePosInChunk;
        glm::uint8 activeSides;
    };
    struct cube_id_and_rest {
        glm::uint16 cubeID;
        glm::uint16 notUsed;
    };
    StateEssentials &stateEssentials;
    FastNoise m_noise;
    int m_maxTerrainHeight;

    bool sideNeeded(int x_offset,int z_offset, glm::ivec3 &position, int& ownheight);
    void setFace(glm::uint8 &var, CUBE_SIDES face, bool status = true);

protected:
};




