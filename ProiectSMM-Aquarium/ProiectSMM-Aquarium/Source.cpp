#include <GL/glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include "Mesh.h"
#include "ObjLoader.h"
#include "WaterFrameBuffer.h"
#include "ShadowFrameBuffer.h"
#include "Skybox.h"

Mesh InitSandMesh(const Texture& texture)
{
    std::vector<float> vertices =
    {
        // Vertex coords         //tex coords   // Normals         //
         -10.0f,  0.0f,  0.5f,     0.0f, 0.0f,   0.0f,  0.0f,  1.0f, //0  0 //front
          10.0f,  0.0f,  0.5f,     1.0f, 0.0f,   0.0f,  0.0f,  1.0f, //1  1
          10.0f,  0.5f,  0.5f,     1.0f, 1.0f,   0.0f,  0.0f,  1.0f, //2  2
         -10.0f,  0.5f,  0.5f,     0.0f, 1.0f,   0.0f,  0.0f,  1.0f, //3  3

         -10.0f,  0.0f, -7.5f,     1.0f, 0.0f,   0.0f,  0.0f, -1.0f, //4  4 //back
         -10.0f,  0.5f, -7.5f,     1.0f, 1.0f,   0.0f,  0.0f, -1.0f, //5  5
          10.0f,  0.5f, -7.5f,     0.0f, 1.0f,   0.0f,  0.0f, -1.0f, //6  6
          10.0f,  0.0f, -7.5f,     0.0f, 0.0f,   0.0f,  0.0f, -1.0f, //7  7

          10.0f,  0.5f,  0.5f,     1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  8 //top
         -10.0f,  0.5f,  0.5f,     0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  9
         -10.0f,  0.5f, -7.5f,     0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  10
          10.0f,  0.5f, -7.5f,     1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  11

         -10.0f,  0.0f,  0.5f,     0.0f, 1.0f,   0.0f, -1.0f,  0.0f, //0  12 //bottom
          10.0f,  0.0f,  0.5f,     1.0f, 1.0f,   0.0f, -1.0f,  0.0f, //1  13
         -10.0f,  0.0f, -7.5f,     0.0f, 0.0f,   0.0f, -1.0f,  0.0f, //4  14
          10.0f,  0.0f, -7.5f,     1.0f, 0.0f,   0.0f, -1.0f,  0.0f, //7  15

         -10.0f,  0.0f,  0.5f,     1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //0  16 //left side
         -10.0f,  0.5f,  0.5f,     1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //3  17
         -10.0f,  0.0f, -7.5f,     0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //4  18
         -10.0f,  0.5f, -7.5f,     0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //5  19

          10.0f,  0.0f,  0.5f,     0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //1  20 //right side
          10.0f,  0.5f,  0.5f,     0.0f, 1.0f,   1.0f,  0.0f,  0.0f, //2  21
          10.0f,  0.5f, -7.5f,     1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //6  22
          10.0f,  0.0f, -7.5f,     1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //7  23
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,//front
        2, 3, 0,

        4, 7, 6,//back
        6, 5, 4,

        9, 8, 11,//top
        11, 10, 9,

        12, 13, 15,//bottom
        15, 14, 12,

        16, 18, 19,//left side
        19, 17, 16,

        20, 23, 22,//right side
        22, 21, 20
    };

    return Mesh(vertices, indices, texture);
}
Mesh InitAquariumBaseMesh(const Texture& texture)
{
    std::vector<float> vertices =
    {     /*****************  FLOOR  ********************/
        // Vertex coords         // tex coords    // Normals
         -10.0f,  0.0f,  0.5f,       0.0f, 0.0f,   0.0f,  0.0f,  1.0f, //0  0 //front
          10.0f,  0.0f,  0.5f,       1.0f, 0.0f,   0.0f,  0.0f,  1.0f, //1  1
          10.0f,  0.1f,  0.5f,       1.0f, 1.0f,   0.0f,  0.0f,  1.0f, //2  2
         -10.0f,  0.1f,  0.5f,       0.0f, 1.0f,   0.0f,  0.0f,  1.0f, //3  3

         -10.0f,  0.0f, -7.5f,       1.0f, 0.0f,   0.0f,  0.0f, -1.0f, //4  4 //back
         -10.0f,  0.1f, -7.5f,       1.0f, 1.0f,   0.0f,  0.0f, -1.0f, //5  5
          10.0f,  0.1f, -7.5f,       0.0f, 1.0f,   0.0f,  0.0f, -1.0f, //6  6
          10.0f,  0.0f, -7.5f,       0.0f, 0.0f,   0.0f,  0.0f, -1.0f, //7  7

          10.0f,  0.1f,  0.5f,       1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  8 //top
         -10.0f,  0.1f,  0.5f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  9
         -10.0f,  0.1f, -7.5f,       0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  10
          10.0f,  0.1f, -7.5f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  11

         -10.0f,  0.0f,  0.5f,       0.0f, 1.0f,   0.0f, -1.0f,  0.0f, //0  12 //bottom
          10.0f,  0.0f,  0.5f,       1.0f, 1.0f,   0.0f, -1.0f,  0.0f, //1  13
         -10.0f,  0.0f, -7.5f,       0.0f, 0.0f,   0.0f, -1.0f,  0.0f, //4  14
          10.0f,  0.0f, -7.5f,       1.0f, 0.0f,   0.0f, -1.0f,  0.0f, //7  15

         -10.0f,  0.0f,  0.5f,       1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //0  16 //left side
         -10.0f,  0.1f,  0.5f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //3  17
         -10.0f,  0.0f, -7.5f,       0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //4  18
         -10.0f,  0.1f, -7.5f,       0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //5  19

          10.0f,  0.0f,  0.5f,       0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //1  20 //right side
          10.0f,  0.1f,  0.5f,       0.0f, 1.0f,   1.0f,  0.0f,  0.0f, //2  21
          10.0f,  0.1f, -7.5f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //6  22
          10.0f,  0.0f, -7.5f,       1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //7  23


         /*****************  FRONT WALL  ********************/
         -10.3f,  0.0f,  0.8f,       0.0f, 0.0f,   0.0f,  0.0f,  1.0f, //0  24 //front
          10.3f,  0.0f,  0.8f,       1.0f, 0.0f,   0.0f,  0.0f,  1.0f, //1  25
          10.3f,  0.6f,  0.8f,       1.0f, 1.0f,   0.0f,  0.0f,  1.0f, //2  26
         -10.3f,  0.6f,  0.8f,       0.0f, 1.0f,   0.0f,  0.0f,  1.0f, //3  27

         -10.3f,  0.6f,  0.8f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  28 //top
          10.3f,  0.6f,  0.8f,       1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  29
          10.3f,  0.6f,  0.5f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  30
         -10.3f,  0.6f,  0.5f,       0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  31

          10.3f,  0.0f,  0.8f,       1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //1  32 //right side
          10.3f,  0.0f,  0.5f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //7  33
          10.3f,  0.6f,  0.5f,       0.0f, 1.0f,   1.0f,  0.0f,  0.0f, //6  34
          10.3f,  0.6f,  0.8f,       0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //2  35

         -10.3f,  0.0f,  0.5f,       1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //4  36 //left side
         -10.3f,  0.0f,  0.8f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //0  37
         -10.3f,  0.6f,  0.8f,       0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //3  38
         -10.3f,  0.6f,  0.5f,       0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //5  39

         -10.3f,  0.0f,  0.8f,       0.0f, 1.0f,   0.0f, -1.0f,  0.0f, //0  40 //bottom
          10.3f,  0.0f,  0.8f,       1.0f, 1.0f,   0.0f, -1.0f,  0.0f, //1  41
          10.3f,  0.0f,  0.5f,       1.0f, 0.0f,   0.0f, -1.0f,  0.0f, //7  42
         -10.3f,  0.0f,  0.5f,       0.0f, 0.0f,   0.0f, -1.0f,  0.0f, //4  43


         /*****************  RIGHT WALL  ********************/
          10.3f,  0.0f,  0.5f,       0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //0  44 //front
          10.3f,  0.0f, -7.5f,       1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //1  45
          10.3f,  0.6f, -7.5f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //2  46
          10.3f,  0.6f,  0.5f,       0.0f, 1.0f,   1.0f,  0.0f,  0.0f, //3  47

          10.3f,  0.6f,  0.5f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  48 //top
          10.3f,  0.6f, -7.5f,       1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  49
          10.0f,  0.6f, -7.5f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  50
          10.0f,  0.6f,  0.5f,       0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  51

          10.3f,  0.0f,  0.5f,       0.0f, 1.0f,   0.0f, -1.0f,  0.0f, //0  52 //bottom
          10.3f,  0.0f, -7.5f,       1.0f, 1.0f,   0.0f, -1.0f,  0.0f, //1  53
          10.0f,  0.0f, -7.5f,       1.0f, 0.0f,   0.0f, -1.0f,  0.0f, //7  54
          10.0f,  0.0f,  0.5f,       0.0f, 0.0f,   0.0f, -1.0f,  0.0f, //4  55


          /*****************  BACK WALL  ********************/
          -10.3f,  0.0f, -7.8f,       0.0f, 0.0f,   0.0f,  0.0f, -1.0f, //0  56 //front
           10.3f,  0.0f, -7.8f,       1.0f, 0.0f,   0.0f,  0.0f, -1.0f, //1  57
           10.3f,  0.6f, -7.8f,       1.0f, 1.0f,   0.0f,  0.0f, -1.0f, //2  58
          -10.3f,  0.6f, -7.8f,       0.0f, 1.0f,   0.0f,  0.0f, -1.0f, //3  59

          -10.3f,  0.6f, -7.8f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  60 //top
           10.3f,  0.6f, -7.8f,       1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  61
           10.3f,  0.6f, -7.5f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  62
          -10.3f,  0.6f, -7.5f,       0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  63

           10.3f,  0.0f, -7.8f,       1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //1  64 //right side
           10.3f,  0.0f, -7.5f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //7  65
           10.3f,  0.6f, -7.5f,       0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //6  66
           10.3f,  0.6f, -7.8f,       0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //2  67

          -10.3f,  0.0f, -7.5f,       1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //4  68 //left side
          -10.3f,  0.0f, -7.8f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //0  69
          -10.3f,  0.6f, -7.8f,       0.0f, 1.0f,   1.0f,  0.0f,  0.0f, //3  70
          -10.3f,  0.6f, -7.5f,       0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //5  71

          -10.3f,  0.0f, -7.8f,       0.0f, 1.0f,   0.0f, -1.0f,  0.0f, //0  72 //bottom
           10.3f,  0.0f, -7.8f,       1.0f, 1.0f,   0.0f, -1.0f,  0.0f, //1  73
           10.3f,  0.0f, -7.5f,       1.0f, 0.0f,   0.0f, -1.0f,  0.0f, //7  74
          -10.3f,  0.0f, -7.5f,       0.0f, 0.0f,   0.0f, -1.0f,  0.0f, //4  75

          /*****************  LEFT WALL  ********************/
          -10.3f, 0.0f,  0.5f,        0.0f, 0.0f,   -1.0f,  0.0f,  0.0f, //0  76 //front
          -10.3f, 0.0f, -7.5f,        1.0f, 0.0f,   -1.0f,  0.0f,  0.0f, //1  77
          -10.3f, 0.6f, -7.5f,        1.0f, 1.0f,   -1.0f,  0.0f,  0.0f, //2  78
          -10.3f, 0.6f,  0.5f,        0.0f, 1.0f,   -1.0f,  0.0f,  0.0f, //3  79

          -10.3f, 0.6f,  0.5f,        0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  80 //top
          -10.3f, 0.6f, -7.5f,        1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  81
          -10.0f, 0.6f, -7.5f,        1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  82
          -10.0f, 0.6f,  0.5f,        0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  83

          -10.3f, 0.0f,  0.5f,        0.0f, 1.0f,   0.0f, -1.0f,  0.0f, //0  84 //bottom
          -10.3f, 0.0f, -7.5f,        1.0f, 1.0f,   0.0f, -1.0f,  0.0f, //1  85
          -10.0f, 0.0f, -7.5f,        1.0f, 0.0f,   0.0f, -1.0f,  0.0f, //7  86
          -10.0f, 0.0f,  0.5f,        0.0f, 0.0f,   0.0f, -1.0f,  0.0f, //4  87
    };
    std::vector<unsigned int> indices =
    {
        /****  FLOOR  ****/
        0, 1, 2,//front
        2, 3, 0,

        4, 7, 6,//back
        6, 5, 4,

        9, 8, 11,//top
        11, 10, 9,

        12, 13, 15,//bottom
        15, 14, 12,

        16, 18, 19,//left side
        19, 17, 16,

        20, 23, 22,//right side
        22, 21, 20,


        /****  FRONT WALL  ****/
        24, 25, 26,//front
        26, 27, 24,

        28, 29, 30,//top
        30, 31, 28,

        32, 33, 34,//right side
        34, 35, 32,

        36, 37, 38,//left side
        38, 39, 36,

        40, 41, 42,//bottom
        42, 43, 40,


        /****  RIGHT WALL  ****/
        44, 45, 46,//front
        46, 47, 44,

        48, 49, 50,//top
        50, 51, 48,

        52, 53, 54,//bottom
        54, 55, 52,

        /****  BACK WALL  ****/
        56, 57, 58,//front
        58, 59, 56,

        60, 61, 62,//top
        62, 63, 60,

        64, 65, 66,//right side
        66, 67, 64,

        68, 69, 70,//left side
        70, 71, 68,

        72, 73, 74,//bottom
        74, 75, 72,

        /****  LEFT WALL  ****/
        76, 77, 78,//front
        78, 79, 76,

        80, 81, 82,//top
        82, 83, 80,

        84, 85, 86,//bottom
        86, 87, 84,
    };
    return Mesh(vertices, indices, texture);
}
Mesh InitFrontGlassPanel()
{
    //!! TEXTURE COORDS NOT CORRECT
    std::vector<float> vertices =
    {
        /*****************  FRONT PANEL  ********************/
        // Vertex coords         // tex coords    // Normals
        -10.15f,  0.6f,  0.7f,       0.0f, 0.0f,   0.0f,  0.0f,  1.0f, //0  0 //front
         10.15f,  0.6f,  0.7f,       1.0f, 0.0f,   0.0f,  0.0f,  1.0f, //1  1
         10.15f,  5.0f,  0.7f,       1.0f, 1.0f,   0.0f,  0.0f,  1.0f, //2  2
        -10.15f,  5.0f,  0.7f,       0.0f, 1.0f,   0.0f,  0.0f,  1.0f, //3  3

        -10.15f,  5.0f,  0.7f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  4 //top
         10.15f,  5.0f,  0.7f,       1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  5
         10.15f,  5.0f,  0.6f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  6
        -10.15f,  5.0f,  0.6f,       0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  7

         10.15f,  0.6f,  0.7f,       1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //1  8 //right side
         10.15f,  0.6f,  0.6f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //7  9
         10.15f,  5.0f,  0.6f,       0.0f, 1.0f,   1.0f,  0.0f,  0.0f, //6  10
         10.15f,  5.0f,  0.7f,       0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //2  11

        -10.15f,  0.6f,  0.6f,       1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //4  12 //left side
        -10.15f,  0.6f,  0.7f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //0  13
        -10.15f,  5.0f,  0.7f,       0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //3  14
        -10.15f,  5.0f,  0.6f,       0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //5  15

        -10.15f,  0.6f,  0.6f,       0.0f, 0.0f,   0.0f,  0.0f, -1.0f, //4  16 //back
         10.15f,  0.6f,  0.6f,       1.0f, 0.0f,   0.0f,  0.0f, -1.0f, //7  17
         10.15f,  5.0f,  0.6f,       1.0f, 1.0f,   0.0f,  0.0f, -1.0f, //6  18
        -10.15f,  5.0f,  0.6f,       0.0f, 1.0f,   0.0f,  0.0f, -1.0f, //5  19
    };
    std::vector<unsigned int> indices =
    {
        /****  FRONT PANEL  ****/
        0, 1, 2,//front
        2, 3, 0,

        4, 5, 6,//top
        6, 7, 4,

        8, 9, 10,//right side
        10, 11, 8,

        12, 13, 14,//left side
        14, 15, 12,

        16, 17, 18,//back
        18, 19, 16,
    };
    return Mesh(vertices, indices);
}
Mesh InitBackGlassPanel()
{
    std::vector<float> vertices = {
        /*****************  BACK PANEL  ********************/
         // Vertex coords         // tex coords    // Normals
         10.15f,  0.6f, -7.7f,       0.0f, 0.0f,   0.0f,  0.0f, -1.0f, //0  0 //front
        -10.15f,  0.6f, -7.7f,       1.0f, 0.0f,   0.0f,  0.0f, -1.0f, //1  1
        -10.15f,  5.0f, -7.7f,       1.0f, 1.0f,   0.0f,  0.0f, -1.0f, //2  2
         10.15f,  5.0f, -7.7f,       0.0f, 1.0f,   0.0f,  0.0f, -1.0f, //3  3

         10.15f,  5.0f, -7.7f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  4 //top
        -10.15f,  5.0f, -7.7f,       1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  5
        -10.15f,  5.0f, -7.6f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  6
         10.15f,  5.0f, -7.6f,       0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  7

        -10.15f,  0.6f, -7.7f,       1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //1  8 //right side
        -10.15f,  0.6f, -7.6f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //7  9
        -10.15f,  5.0f, -7.6f,       0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //6  10
        -10.15f,  5.0f, -7.7f,       0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //2  11

         10.15f,  0.6f, -7.6f,       1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //4  12 //left side
         10.15f,  0.6f, -7.7f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //0  13
         10.15f,  5.0f, -7.7f,       0.0f, 1.0f,   1.0f,  0.0f,  0.0f, //3  14
         10.15f,  5.0f, -7.6f,       0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //5  15

         10.15f,  0.6f, -7.6f,       0.0f, 0.0f,   0.0f,  0.0f,  1.0f, //4  16 //back
        -10.15f,  0.6f, -7.6f,       1.0f, 0.0f,   0.0f,  0.0f,  1.0f, //7  17
        -10.15f,  5.0f, -7.6f,       1.0f, 1.0f,   0.0f,  0.0f,  1.0f, //6  18
         10.15f,  5.0f, -7.6f,       0.0f, 1.0f,   0.0f,  0.0f,  1.0f, //5  19
    };
    std::vector<unsigned int> indices = {
        /****  BACK PANEL  ****/
        0, 1, 2,//front
        2, 3, 0,

        4, 5, 6,//top
        6, 7, 4,

        8, 9, 10,//right side
        10, 11, 8,

        12, 13, 14,//left side
        14, 15, 12,

        16, 17, 18,//back
        18, 19, 16,
    };
    return Mesh(vertices, indices);
}
Mesh InitRightGlassPanel()
{
    std::vector<float> vertices = {
        /*****************  RIGHT PANEL  ********************/
         // Vertex coords         // tex coords    // Normals
         10.15f,  0.6f,  0.6f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //0  0 //front
         10.15f,  0.6f, -7.6f,       1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //1  1
         10.15f,  5.0f, -7.6f,       0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //2  2
         10.15f,  5.0f,  0.6f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //3  3

         10.05f,  0.6f,  0.6f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //4  4 //back
         10.05f,  0.6f, -7.6f,       1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //7  5
         10.05f,  5.0f, -7.6f,       0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //6  6
         10.05f,  5.0f,  0.6f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //5  7

         10.15f,  5.0f,  0.6f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //3  8 //top
         10.15f,  5.0f, -7.6f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //2  9
         10.05f,  5.0f, -7.6f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //6  10
         10.05f,  5.0f,  0.6f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //5  11
    };
    std::vector<unsigned int> indices = {
        /****  RIGHT PANEL  ****/
        0, 1, 2,//front
        2, 3, 0,

        4, 5, 6,//back
        6, 7, 4,

        8, 9, 10,//top
        10, 11, 8,
    };
    return Mesh(vertices, indices);
}
Mesh InitLeftGlassPanel()
{
    std::vector<float> vertices = {
        /*****************  LEFT PANEL  ********************/
         // Vertex coords         // tex coords    // Normals
        -10.15f,  0.6f, -7.6f,       1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //0  0//front
        -10.15f,  0.6f,  0.6f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //1  1
        -10.15f,  5.0f,  0.6f,       1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, //2  2
        -10.15f,  5.0f, -7.6f,       0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //3  3

        -10.05f,  0.6f, -7.6f,       1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //4  4//back
        -10.05f,  0.6f,  0.6f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //7  5
        -10.05f,  5.0f,  0.6f,       1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //6  6
        -10.05f,  5.0f, -7.6f,       0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //5  7

        -10.15f,  5.0f, -7.6f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //3  8//top
        -10.15f,  5.0f,  0.6f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //2  9
        -10.05f,  5.0f,  0.6f,       1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //6  10
        -10.05f,  5.0f, -7.6f,       0.0f, 0.0f,   0.0f,  1.0f,  0.0f, //5  11
    };
    std::vector<unsigned int> indices = {
        /****  LEFT PANEL  ****/
        0, 1, 2,//front
        2, 3, 0,

        4, 5, 6,//back
        6, 7, 4,

        8, 9, 10,//top
        10, 11, 8,
    };
    return Mesh(vertices, indices);
}
Mesh InitLightCubeMesh()
{
    std::vector<float> vertices =
    {
        //      Vertex coords     //
         -1.0f,  0.0f,  0.5f,      0.0f, 0.0f,   0.0f,  0.0f,  0.0f,//0
          1.0f,  0.0f,  0.5f,      0.0f, 0.0f,   0.0f,  0.0f,  0.0f,//1  
          1.0f,  1.0f,  0.5f,      0.0f, 0.0f,   0.0f,  0.0f,  0.0f,//2  
         -1.0f,  1.0f,  0.5f,      0.0f, 0.0f,   0.0f,  0.0f,  0.0f,//3
         -1.0f,  0.0f, -0.5f,      0.0f, 0.0f,   0.0f,  0.0f,  0.0f,//4
         -1.0f,  1.0f, -0.5f,      0.0f, 0.0f,   0.0f,  0.0f,  0.0f,//5  
          1.0f,  1.0f, -0.5f,      0.0f, 0.0f,   0.0f,  0.0f,  0.0f,//6  
          1.0f,  0.0f, -0.5f,      0.0f, 0.0f,   0.0f,  0.0f,  0.0f,//7 
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,//front
        2, 3, 0,

        4, 7, 6,//back
        6, 5, 4,

        3, 2, 6,//top
        6, 5, 3,

        0, 1, 7,//bottom
        7, 4, 0,

        0, 4, 5,//left side
        5, 3, 0,

        1, 7, 6,//right side
        6, 2, 1
    };

    return Mesh(vertices, indices);
}
Mesh InitSurfaceWaterMesh()
{
    std::vector<float> vertices =
    {
        // Vertex coords          // tex coords   // Normals
        -10.05f,  4.5f,  0.6f,    1.0f, 1.0f,     0.0f,  1.0f,  0.0f, //0  0
         10.05f,  4.5f,  0.6f,    0.0f, 1.0f,     0.0f,  1.0f,  0.0f, //1  1
         10.05f,  4.5f, -7.6f,    0.0f, 0.0f,     0.0f,  1.0f,  0.0f, //2  2
        -10.05f,  4.5f, -7.6f,    1.0f, 0.0f,     0.0f,  1.0f,  0.0f, //3  3
    };
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        2, 3, 0
    };
    return Mesh(vertices, indices);
}
Mesh InitSideWaterMesh()
{
    std::vector<float> vertices =
    {
        /*****************  FRONT  ********************/
        // Vertex coords          // tex coords   // Normals
        -10.05f,  0.6f,  0.599f,    0.0f, 0.0f,     0.0f,  0.0f,  1.0f, //0  0
         10.05f,  0.6f,  0.599f,    1.0f, 0.0f,     0.0f,  0.0f,  1.0f, //1  1
         10.05f,  4.5f,  0.599f,    1.0f, 1.0f,     0.0f,  0.0f,  1.0f, //2  2
        -10.05f,  4.5f,  0.599f,    0.0f, 1.0f,     0.0f,  0.0f,  1.0f, //3  3

        /*****************  RIGHT  ********************/
         10.049f,  0.6f,  0.599f,    0.0f, 0.0f,     1.0f,  0.0f,  0.0f, //0  4
         10.049f,  0.6f, -7.599f,    1.0f, 0.0f,     1.0f,  0.0f,  0.0f, //1  5
         10.049f,  4.5f, -7.599f,    1.0f, 1.0f,     1.0f,  0.0f,  0.0f, //2  6
         10.049f,  4.5f,  0.599f,    0.0f, 1.0f,     1.0f,  0.0f,  0.0f, //3  7

         /*****************  BACK  ********************/
         10.05f,  0.6f, -7.599f,    0.0f, 0.0f,     0.0f,  0.0f, -1.0f, //0  8
        -10.05f,  0.6f, -7.599f,    1.0f, 0.0f,     0.0f,  0.0f, -1.0f, //1  9
        -10.05f,  4.5f, -7.599f,    1.0f, 1.0f,     0.0f,  0.0f, -1.0f, //2  10
         10.05f,  4.5f, -7.599f,    0.0f, 1.0f,     0.0f,  0.0f, -1.0f, //3  11

         /*****************  LEFT  ********************/
        -10.049f,  0.6f, -7.599f,    0.0f, 0.0f,    -1.0f,  0.0f, 0.0f, //0  12
        -10.049f,  0.6f,  0.599f,    1.0f, 0.0f,    -1.0f,  0.0f, 0.0f, //1  13
        -10.049f,  4.5f,  0.599f,    1.0f, 1.0f,    -1.0f,  0.0f, 0.0f, //2  14
        -10.049f,  4.5f, -7.599f,    0.0f, 1.0f,    -1.0f,  0.0f, 0.0f, //3  15
    };
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12
    };
    return Mesh(vertices, indices);
}
Mesh InitRock(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\stone.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);

}
Mesh InitStar(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\18762_Sunflower_Star_starfish_v1.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);

}
Mesh InitCoral(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\21485_Elkhorn_Coral_v1.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);

}
Mesh InitCoral2(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\20942_Staghorn_Coral_v1_NEW.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);
    //20942_Staghorn_Coral_v1_NEW
}
Mesh InitPlant1(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\Low Grass.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);

}

Mesh InitPlant2(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\10439_Corn_Field_v1_max2010_it2.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);

}

Mesh InitBasicFish(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\fish.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);
}
Mesh InitFancyFish(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\13007_Blue-Green_Reef_Chromis_v2_l3.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);
}
//Mesh InitBlueFish(const Texture& texture)
//{
//    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\13006_Blue_Tang_v1_l3.obj");
//    std::vector<unsigned int> indices;
//    for (unsigned int i = 0; i < vertices.size() / 8; i++)
//        indices.push_back(i);
//
//    return Mesh(vertices, indices, texture);
//}
Mesh InitGreenOrangeFish(const Texture& texture)
{
    std::vector<float> vertices = ObjLoader::Parse("resources\\models\\12999_Boesemani_Rainbow_v1_l2.obj");
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size() / 8; i++)
        indices.push_back(i);

    return Mesh(vertices, indices, texture);
}
enum class FishType
{
    BASIC,
    FANCY,
    BLUE,
    GREEN_ORANGE
};

struct FishCharacteristics
{
    FishType m_type;

    glm::vec3 position;
    glm::vec3 next_position;

    float scaling_factor;
    float speed;
    float trajectory_position;

    float x_path_distance;
    float height;
    float z_path_distance;

    FishCharacteristics(float scaling_factor, float speed, float x_path_distance,
        float height, float z_path_distance, float trajectory_position, FishType type)
        : scaling_factor(scaling_factor), speed(speed), x_path_distance(x_path_distance),
        height(height), z_path_distance(z_path_distance), trajectory_position(trajectory_position), m_type(type)
    {
        position = glm::vec3(0.0f);
        next_position = glm::vec3(0.0f);
    }

};
void CreateFishes(std::vector<FishCharacteristics>& fishes)
{
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 14.0f, 4.8f, 5.6f, -0.1f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 14.4f, 5.0f, 6.0f, -0.1f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 13.5f, 4.8f, 5.6f, 0.0f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 14.0f, 4.5f, 6.0f, 0.0f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 14.3f, 4.7f, 6.3f, 0.0f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 13.2f, 5.4f, 5.5f, 0.1f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 14.0f, 5.3f, 6.0f, 0.1f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 14.4f, 5.5f, 6.5f, 0.1f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 12.8f, 5.3f, 5.3f, 0.06f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 12.9f, 4.9f, 5.4f, 0.04f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 13.4f, 5.7f, 6.6f, -0.06f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, 14.0f, 5.4f, 6.0f, -0.1f, FishType::BASIC));

    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -15.0f, 3.3f, 5.6f, 0.9f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -15.4f, 3.5f, 6.0f, 0.9f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -14.5f, 3.3f, 5.6f, 1.0f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -15.0f, 3.0f, 6.0f, 1.0f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -15.3f, 3.2f, 6.3f, 1.0f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -14.2f, 3.9f, 5.5f, 1.1f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -15.0f, 3.8f, 6.0f, 1.1f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -15.4f, 4.0f, 6.5f, 1.1f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -13.8f, 3.8f, 5.3f, 1.06f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -13.9f, 3.4f, 5.4f, 1.04f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -14.4f, 4.2f, 6.6f, 0.94f, FishType::BASIC));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.005f, -15.0f, 3.9f, 6.0f, 0.9f, FishType::BASIC));

    fishes.emplace_back(FishCharacteristics(1.0f, 0.001f, -10.0f, 2.0f, 4.0f, 0.0f, FishType::FANCY));
    fishes.emplace_back(FishCharacteristics(1.0f, 0.001f, -10.0f, 2.0f, 4.0f, 2.0f, FishType::FANCY));
    fishes.emplace_back(FishCharacteristics(1.0f, 0.002f, 10.0f, 5.0f, 3.0f, -0.5f, FishType::BLUE));
    fishes.emplace_back(FishCharacteristics(0.5f, 0.002f, 16.0f, 7.0f, 6.5f, 1.0f, FishType::GREEN_ORANGE));
    fishes.emplace_back(FishCharacteristics(0.55f, 0.002f, -15.6f, 6.5f, 5.7f, 1.0f, FishType::FANCY));
    fishes.emplace_back(FishCharacteristics(1.2f, 0.002f, -7.0f, 2.0f, 3.0f, 2.0f, FishType::BLUE));
    fishes.emplace_back(FishCharacteristics(0.3f, 0.0035f, 15.0f, 7.5f, 6.0f, 0.0f, FishType::GREEN_ORANGE));
}


int main()
{
    /* Initializing the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Creating a window */
    int window_height = 800, window_width = 1850;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Aquarium", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /* initiaziting glew and reading the shader */
    glewInit();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //loading shaders
    Shader object_shader("resources\\shaders\\object.shader");//loading object shader, used for all objects
    object_shader.Bind();
    object_shader.SetUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);

    Shader light_shader("resources\\shaders\\lightSource.shader");//loading light shader, used for light sources 
    light_shader.Bind();
    light_shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    Shader glass_shader("resources\\shaders\\glass.shader");
    glass_shader.Bind();
    glass_shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    glass_shader.SetUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);

    Shader water_shader("resources\\shaders\\water.shader");
    water_shader.Bind();
    water_shader.SetUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);

    Shader shadow_shader("resources\\shaders\\shadowMap.shader");
    Shader shadowViewer_shader("resources\\shaders\\depthViewer.shader");

    // loading texture
    Texture sand_texture("resources\\textures\\sand.jpg");
    Texture wood_texture("resources\\textures\\wood.jpg");
    Texture basic_fish_texture("resources\\textures\\fish_texture.png");
    Texture fancy_fish_texture("resources\\textures\\13004_Bicolor_Blenny_v1_diff.jpg");
    //Texture blue_fish_texture("resources\\textures\\13006_Blue_Tang_v1_diff.jpg");
    Texture green_orange_fish_texture("resources\\textures\\12999_Boesemani_Rainbow_diff.jpg");
    Texture water_DuDv("resources\\textures\\waterDUDV.png");
    Texture water_NormalMap("resources\\textures\\waterNormalMap.png");
    Texture rock_texture("resources\\textures\\marine_rock_texture.jpg");
    Texture star_texture("resources\\textures\\orange_texture.jpg");
    Texture star_texture2("resources\\textures\\purple_texture.jpg");
    Texture coral_texture("resources\\textures\\purple_coral_texture.jpg");
    Texture coral2_texture("resources\\textures\\pink_coral_texture.jpg");
    Texture plant1_texture("resources\\textures\\algae_texture.jpg");
    Texture plant2_texture("resources\\textures\\algae_texture.jpg");

    // Initialize camera
    Camera camera(window_width, window_height, glm::vec3(0.0f, 15.0f, 30.0f));
    camera.SetPitch(-25.0f);
    float last_frame = 0.0f, delta_time;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, (window_width / 2), (window_height / 2));

    Renderer renderer;

    glEnable(GL_CLIP_DISTANCE0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.2f, 0.3f, 1.0f);

    //SKYBOX
    Skybox scene_skybox;

    //loading meshes
    Mesh sand = InitSandMesh(sand_texture);
    Mesh aquarium_base = InitAquariumBaseMesh(wood_texture);
    std::array<Mesh, 4> glass_panels = { InitFrontGlassPanel(), InitBackGlassPanel(), InitRightGlassPanel(), InitLeftGlassPanel() };
    Mesh light_cube = InitLightCubeMesh();
    Mesh basic_fish = InitBasicFish(basic_fish_texture);
    Mesh fancy_fish = InitFancyFish(fancy_fish_texture);
    //Mesh blue_fish = InitBlueFish(blue_fish_texture);
    Mesh green_orange_fish = InitGreenOrangeFish(green_orange_fish_texture);
    Mesh surface_water = InitSurfaceWaterMesh();
    Mesh side_water = InitSideWaterMesh();
    Mesh rock = InitRock(rock_texture);
    Mesh star = InitStar(star_texture);
    Mesh coral = InitCoral(coral_texture);
    Mesh coral2 = InitCoral2(coral2_texture);
    Mesh plant1 = InitPlant1(plant1_texture);
    Mesh plant2 = InitPlant2(plant1_texture);

    WaterFrameBuffer FBO(window_width, window_height);
    Texture reflection(FBO.GetReflectionTextureID());
    Texture refraction(FBO.GetRefractionTextureID());
    Texture depth_map(FBO.GetRefractionDepthTextureID());

    ShadowFrameBuffer Shadow_FBO(window_width, window_height);
    Texture shadow_depth_map(Shadow_FBO.GetShadowDepthTextureID());

    //general operations for models
    glm::vec3 aquarium_translation = glm::vec3(0.0f, 0.0f, 3.5f);//setting default translation for the whole aquarium
    glm::vec3 aquarium_scaling = glm::vec3(2.0f, 2.0f, 2.0f);
    float water_height = 4.5f * aquarium_scaling.y, wave_move_factor = 0.0f;
    surface_water.SetTexture(reflection);

    //fish movement
    std::vector<FishCharacteristics> fishes_charact;
    CreateFishes(fishes_charact);


    while (!glfwWindowShouldClose(window))
    {
        //getting delta time
        float current_frame = static_cast<float>(glfwGetTime());
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        //calculating new frame positions
        //glm::vec3 light_position = glm::vec3(-20.0f, glm::sin(current_frame) * 40.0f, glm::cos(current_frame) * 40.0f);
        glm::vec3 light_position = glm::vec3(-20.0f, 60.0f, 40.0f);

        for (auto& fish_charact : fishes_charact)
        {
            if (fish_charact.trajectory_position + fish_charact.speed > 360.0f)
                fish_charact.trajectory_position = 0.0f;
            else
                fish_charact.trajectory_position += fish_charact.speed;

            fish_charact.next_position = glm::vec3(glm::sin(fish_charact.trajectory_position) * fish_charact.x_path_distance,
                fish_charact.height,
                glm::cos(fish_charact.trajectory_position) * fish_charact.z_path_distance);
        }

        // Get light's perspective
        // --------------------------------------------------------------
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 60.1f, far_plane = 90.5f;
        lightProjection = glm::ortho(-90.0f, 90.0f, -90.0f, 90.0f, near_plane, far_plane);
        //lightProjection = glm::perspective(glm::radians(90.0f), (GLfloat)4000 / (GLfloat)4000, near_plane, far_plane);
        lightView = glm::lookAt(light_position, glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;

        //configuring general settings for shaders
        glass_shader.Bind();
        glass_shader.SetUniform3f("u_LightPosition", light_position.x, light_position.y, light_position.z);

        object_shader.Bind();
        object_shader.SetUniform3f("u_LightPosition", light_position.x, light_position.y, light_position.z);
        object_shader.SetUniformMat4f("u_LightProjection", lightSpaceMatrix);

        water_shader.Bind();
        water_shader.SetUniform3f("u_LightPosition", light_position.x, light_position.y, light_position.z);
        water_shader.SetUniform1f("u_ZNear", camera.GetNear());
        water_shader.SetUniform1f("u_ZFar", camera.GetFar());

        shadow_shader.Bind();
        shadow_shader.SetUniformMat4f("u_LightProjection", lightSpaceMatrix);

        //processing user input
        camera.ProcessInput(window, delta_time);

        Shadow_FBO.BindFrameBuffer();
        {
            renderer.Clear();
            glass_shader.Bind();
            glass_shader.SetUniform4f("u_ClipPlane", 0.0f, -1.0f, 0.0f, 100.0f);
            object_shader.Bind();
            object_shader.SetUniform4f("u_ClipPlane", 0.0f, -1.0f, 0.0f, 100.0f);

            // render skybox
            scene_skybox.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());

            //rendering the sand
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
                model = glm::translate(model, aquarium_translation);
                shadow_shader.Bind();
                shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
                sand.Draw(camera, shadow_shader, renderer);
            }
            //rendering aquarium base
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, aquarium_translation);
                shadow_shader.Bind();
                shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
                aquarium_base.Draw(camera, shadow_shader, renderer);
            }

            //rendering fish
            {
                for (auto& fish_charact : fishes_charact)
                {
                    float delta_x = fish_charact.next_position.x - fish_charact.position.x;
                    float delta_z = fish_charact.next_position.z - fish_charact.position.z;
                    float angle = atan2(delta_x, delta_z);

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, fish_charact.position);
                    model = glm::scale(model, glm::vec3(fish_charact.scaling_factor, fish_charact.scaling_factor,
                        fish_charact.scaling_factor));
                    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));

                    shadow_shader.Bind();
                    shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
                    switch (fish_charact.m_type)
                    {
                    case FishType::BASIC:
                        basic_fish.Draw(camera, shadow_shader, renderer);
                        break;
                    case FishType::FANCY:
                        fancy_fish.Draw(camera, shadow_shader, renderer);
                        break;
                    case FishType::BLUE:
                        //blue_fish.Draw(camera, shadow_shader, renderer);
                        break;
                    case FishType::GREEN_ORANGE:
                        green_orange_fish.Draw(camera, shadow_shader, renderer);
                        break;
                    }
                }
            }

            //rendering rock 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 0.6f, -8.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            rock.Draw(camera, shadow_shader, renderer);

            }

            //rendering rock 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-15.0f, 1.2f, -9.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            rock.Draw(camera, shadow_shader, renderer);

            }

            //rendering rock 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 0.6f, 2.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            rock.Draw(camera, shadow_shader, renderer);

            }

            //rendering rock 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 0.6f, -2.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            rock.Draw(camera, shadow_shader, renderer);

            }

            //rendering rock 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 1.2f, -2.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            rock.Draw(camera, shadow_shader, renderer);

            }

            //rendering rock 6
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 1.2f, -1.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            rock.Draw(camera, shadow_shader, renderer);

            }

            //rendering star 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+15.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            star.Draw(camera, shadow_shader, renderer);

            }
            //rendering star 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 1.95f, -2.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            star.Draw(camera, shadow_shader, renderer);

            }
            //rendering star 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 1.95f, 2.0f));
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            star.Draw(camera, shadow_shader, renderer);

            }

            //rendering coral 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+17.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral.Draw(camera, shadow_shader, renderer);

            }
            //rendering coral 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+13.0f, 1.2f, -9.3f));
            model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral.Draw(camera, shadow_shader, renderer);

            }
            //rendering coral 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-15.0f, 1.2f, -5.0f));
            model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral.Draw(camera, shadow_shader, renderer);

            }
            //rendering coral 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-11.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral.Draw(camera, shadow_shader, renderer);

            }
            //rendering coral 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(15.0f, 1.2f, 0.0f));
            model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral.Draw(camera, shadow_shader, renderer);

            }
            //rendering coral v2 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+17.0f, 0.9f, -5.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral2.Draw(camera, shadow_shader, renderer);

            }
            //rendering coralv2 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-14.5f, 0.9f, -3.0f));
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral2.Draw(camera, shadow_shader, renderer);

            }

            //rendering coral v2 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.8f, 1.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral2.Draw(camera, shadow_shader, renderer);

            }


            //rendering coral v2 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(10.0f, 0.8f, -9.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            coral2.Draw(camera, shadow_shader, renderer);

            }

            //rendering plant2 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, 3.0f));
            model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant2.Draw(camera, shadow_shader, renderer);

            }
            //rendering plant1 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.2f, -6.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant1.Draw(camera, shadow_shader, renderer);

            }

            //rendering plant1 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.5f, -10.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant1.Draw(camera, shadow_shader, renderer);

            }

            //rendering plant1 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-14.0f, 0.1f, -8.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant1.Draw(camera, shadow_shader, renderer);

            }

            //rendering plant1 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.5f, 0.5f, 0.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant1.Draw(camera, shadow_shader, renderer);

            }
            //rendering plant1 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, 3.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant1.Draw(camera, shadow_shader, renderer);

            }

            //rendering plant1 6
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, -2.5f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant1.Draw(camera, shadow_shader, renderer);

            }
            //rendering plant1 7
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, -6.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant1.Draw(camera, shadow_shader, renderer);

            }
            //rendering plant1 8
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(14.50f, 0.25f, -10.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            shadow_shader.Bind();
            shadow_shader.SetUniformMat4f("u_ModelMatrix", model);
            plant1.Draw(camera, shadow_shader, renderer);

            }
        }
        Shadow_FBO.UnbindFrameBuffer();

        //rendering for reflection texture
        FBO.BindReflectionFrameBuffer();
        {
            //the reflection needs an inverted image from above the water, so we move the camera before rendering
            float camera_moving_distance = 2 * (camera.GetPosition().y - water_height);
            camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - camera_moving_distance, camera.GetPosition().z));
            camera.SetPitch(-camera.GetPitch());

            renderer.Clear();
            glass_shader.Bind();
            glass_shader.SetUniform4f("u_ClipPlane", 0.0f, 1.0f, 0.0f, -water_height);
            object_shader.Bind();
            object_shader.SetUniform4f("u_ClipPlane", 0.0f, 1.0f, 0.0f, -water_height);

            // render skybox
            scene_skybox.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());

            //rendering the sand
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
                model = glm::translate(model, aquarium_translation);
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                sand.Draw(camera, object_shader, renderer);
            }
            //rendering aquarium base
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, aquarium_translation);
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                aquarium_base.Draw(camera, object_shader, renderer);
            }

            //rendering fish
            {
                for (auto& fish_charact : fishes_charact)
                {
                    float delta_x = fish_charact.next_position.x - fish_charact.position.x;
                    float delta_z = fish_charact.next_position.z - fish_charact.position.z;
                    float angle = atan2(delta_x, delta_z);

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, fish_charact.position);
                    model = glm::scale(model, glm::vec3(fish_charact.scaling_factor, fish_charact.scaling_factor,
                        fish_charact.scaling_factor));
                    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));

                    shadow_depth_map.Bind(1);
                    object_shader.Bind();
                    object_shader.SetUniformMat4f("u_ModelMatrix", model);
                    object_shader.SetUniform1i("shadowMap", 1);

                    switch (fish_charact.m_type)
                    {
                    case FishType::BASIC:
                        basic_fish.Draw(camera, object_shader, renderer);
                        break;
                    case FishType::FANCY:
                        fancy_fish.Draw(camera, object_shader, renderer);
                        break;
                    case FishType::BLUE:
                        //blue_fish.Draw(camera, object_shader, renderer);
                        break;
                    case FishType::GREEN_ORANGE:
                        green_orange_fish.Draw(camera, object_shader, renderer);
                        break;
                    }
                }
            }

            //rendering rock 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 0.6f, -8.0f));

            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-15.0f, 1.2f, -9.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 0.6f, 2.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 0.6f, -2.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 1.2f, -2.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 6
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 1.2f, -1.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering star 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+15.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }
            //rendering star 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 1.95f, -2.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }
            //rendering star 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 1.95f, 2.0f));
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }

            //rendering coral 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+17.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+13.0f, 1.2f, -9.3f));
            model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-15.0f, 1.2f, -5.0f));
            model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-11.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(15.0f, 1.2f, 0.0f));
            model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral v2 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+17.0f, 0.9f, -5.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral2.Draw(camera, object_shader, renderer);

            }
            //rendering coralv2 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-14.5f, 0.9f, -3.0f));
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral2.Draw(camera, object_shader, renderer);

            }

            //rendering coral v2 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.8f, 1.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral2.Draw(camera, object_shader, renderer);

            }


            //rendering coral v2 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(10.0f, 0.8f, -9.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral2.Draw(camera, object_shader, renderer);

            }

            //rendering plant2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, 3.0f));
            model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant2.Draw(camera, object_shader, renderer);

            }
            
            //rendering plant1 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.2f, -6.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.5f, -10.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-14.0f, 0.1f, -8.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.5f, 0.5f, 0.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, 3.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 6
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, -2.5f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 7
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, -6.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 8
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(14.50f, 0.25f, -10.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering light cube
            {
                glDisable(GL_CLIP_DISTANCE0);//the light cube should not be affected by the clipping

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, light_position);
                light_shader.Bind();
                light_shader.SetUniformMat4f("u_ModelMatrix", model);
                //light_cube.Draw(camera, light_shader, renderer);

                glEnable(GL_CLIP_DISTANCE0);
            }

            //rendering aquarium glass
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, aquarium_translation);
                glass_shader.Bind();
                glass_shader.SetUniformMat4f("u_ModelMatrix", model);

                //needed for good transparency, the positions will represent the centers of the panels
                std::array<glm::vec3, 6> glass_panels_positions =
                {
                    //front panel left                //front panel right
                    glm::vec3(-7.0f,  2.8f,  0.65f), glm::vec3(7.0f,  2.8f,  0.65f),//front panel
                    //back panel left                 //back panel right
                    glm::vec3(-7.0f,  2.8f, -7.65f), glm::vec3(7.0f,  2.8f, -7.65f),//back panel
                    glm::vec3(10.1f,  2.8f, -4.1f),//right panel
                    glm::vec3(-10.1f,  2.8f, -4.1f) //left panel
                };

                for (unsigned int panel_index = 0; panel_index < glass_panels_positions.size(); panel_index++)
                    glass_panels_positions[panel_index] += aquarium_translation;
                //determine draw order based on panel distance from camera
                std::array<std::pair<float, unsigned int>, 6> panels_distances_from_camera = //pair< distance from camera, panel index >
                {
                    std::make_pair(0.0f, 0), std::make_pair(0.0f, 0),
                    std::make_pair(0.0f, 1), std::make_pair(0.0f, 1),
                    std::make_pair(0.0f, 2),
                    std::make_pair(0.0f, 3)
                };

                std::array < std::pair<float, unsigned int>, 4> draw_order =
                {
                    std::make_pair(-1.0f, 0),
                    std::make_pair(-1.0f, 1),
                    std::make_pair(-1.0f, 2),
                    std::make_pair(-1.0f, 3)
                };
                //calculate distances
                for (unsigned int panel_index = 0; panel_index < panels_distances_from_camera.size(); panel_index++)
                {
                    panels_distances_from_camera[panel_index].first = glm::length(camera.GetPosition() - glass_panels_positions[panel_index]);

                    if (panels_distances_from_camera[panel_index].first < draw_order[panels_distances_from_camera[panel_index].second].first
                        || draw_order[panels_distances_from_camera[panel_index].second].first == -1.0f)
                        draw_order[panels_distances_from_camera[panel_index].second].first = panels_distances_from_camera[panel_index].first;
                }

                //sort the panels from furthest to closest
                std::sort(draw_order.begin(), draw_order.end(), [](const std::pair<float, unsigned int>& element1,
                    const std::pair<float, unsigned int>& element2) -> bool { return element1.first > element2.first; });

                for (unsigned int panel_index = 0; panel_index < glass_panels.size(); panel_index++)
                    glass_panels[draw_order[panel_index].second].Draw(camera, glass_shader, renderer);
            }

            //we move the camera back to the original position
            camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + camera_moving_distance, camera.GetPosition().z));
            camera.SetPitch(-camera.GetPitch());
        }
        FBO.UnbindFrameBuffer();

        //rendering for refraction texture
        FBO.BindRefractionFrameBuffer();
        {
            renderer.Clear();
            glass_shader.Bind();
            glass_shader.SetUniform4f("u_ClipPlane", 0.0f, -1.0f, 0.0f, water_height);
            object_shader.Bind();
            object_shader.SetUniform4f("u_ClipPlane", 0.0f, -1.0f, 0.0f, water_height);

            // render skybox
            scene_skybox.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());

            //rendering the sand
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
                model = glm::translate(model, aquarium_translation);
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                sand.Draw(camera, object_shader, renderer);
            }
            //rendering aquarium base
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, aquarium_translation);
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                aquarium_base.Draw(camera, object_shader, renderer);
            }

            //rendering fish
            {
                for (auto& fish_charact : fishes_charact)
                {
                    float delta_x = fish_charact.next_position.x - fish_charact.position.x;
                    float delta_z = fish_charact.next_position.z - fish_charact.position.z;
                    float angle = atan2(delta_x, delta_z);

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, fish_charact.position);
                    model = glm::scale(model, glm::vec3(fish_charact.scaling_factor, fish_charact.scaling_factor,
                        fish_charact.scaling_factor));
                    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
                    shadow_depth_map.Bind(1);
                    object_shader.Bind();
                    object_shader.SetUniformMat4f("u_ModelMatrix", model);
                    object_shader.SetUniform1i("shadowMap", 1);

                    switch (fish_charact.m_type)
                    {
                    case FishType::BASIC:
                        basic_fish.Draw(camera, object_shader, renderer);
                        break;
                    
                    case FishType::FANCY:
                        fancy_fish.Draw(camera, object_shader, renderer);
                        break;
                    case FishType::BLUE:
                        //blue_fish.Draw(camera, object_shader, renderer);
                        break;
                    case FishType::GREEN_ORANGE:
                        green_orange_fish.Draw(camera, object_shader, renderer);
                        break;
                    }
                }
            }

            //rendering rock 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 0.6f, -8.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }
            //rendering rock 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-15.0f, 1.2f, -9.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }
            //rendering rock 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 0.6f, 2.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 0.6f, -2.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 1.2f, -2.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }
            //rendering rock 6
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 1.2f, -1.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }
            //rendering star 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+15.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }
            //rendering star 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 1.95f, -2.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }
            //rendering star 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 1.95f, 2.0f));
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }
            //rendering coral 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+17.0f, 1.2f, -8.0f));

            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+13.0f, 1.2f, -9.3f));
            model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }

            //rendering coral 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-15.0f, 1.2f, -5.0f));
            model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }

            //rendering coral 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-11.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(15.0f, 1.2f, 0.0f));
            model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral v2 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+17.0f, 0.9f, -5.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral2.Draw(camera, object_shader, renderer);

            }

            //rendering coralv2 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-14.5f, 0.9f, -3.0f));
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral2.Draw(camera, object_shader, renderer);

            }
            //rendering coral v2 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.8f, 1.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral2.Draw(camera, object_shader, renderer);

            }
            //rendering coral v2 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(10.0f, 0.8f, -9.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral2.Draw(camera, object_shader, renderer);

            }

            //rendering plant2
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(19.0f, 0.5f, 3.0f));
                model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant2.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.2f, -6.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-18.0f, 0.5f, -10.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-14.0f, 0.1f, -8.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.5f, 0.5f, 0.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, 3.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 6
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, -2.5f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 7
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 0.5f, -6.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 8
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(14.50f, 0.25f, -10.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            plant1.Draw(camera, object_shader, renderer);

            }
        }
        FBO.UnbindFrameBuffer();

        //render to screen
        {
            renderer.Clear();
            glass_shader.Bind();
            glass_shader.SetUniform4f("u_ClipPlane", 0.0f, -1.0f, 0.0f, 100.0f);
            object_shader.Bind();
            object_shader.SetUniform4f("u_ClipPlane", 0.0f, -1.0f, 0.0f, 100.0f);

            // render skybox
            scene_skybox.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());

            //rendering the sand
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
                model = glm::translate(model, aquarium_translation);
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                sand.Draw(camera, object_shader, renderer);
            }

            //rendering aquarium base
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, aquarium_translation);
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                aquarium_base.Draw(camera, object_shader, renderer);
            }

            //rendering fish
            {
                for (auto& fish_charact : fishes_charact)
                {
                    float delta_x = fish_charact.next_position.x - fish_charact.position.x;
                    float delta_z = fish_charact.next_position.z - fish_charact.position.z;
                    float angle = atan2(delta_x, delta_z);

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, fish_charact.position);
                    model = glm::scale(model, glm::vec3(fish_charact.scaling_factor, fish_charact.scaling_factor,
                        fish_charact.scaling_factor));
                    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
                    shadow_depth_map.Bind(1);
                    object_shader.Bind();
                    object_shader.SetUniformMat4f("u_ModelMatrix", model);
                    object_shader.SetUniform1i("shadowMap", 1);

                    switch (fish_charact.m_type)
                    {
                    case FishType::BASIC:
                        basic_fish.Draw(camera, object_shader, renderer);
                        break;
                    case FishType::FANCY:
                        fancy_fish.Draw(camera, object_shader, renderer);
                        break;
                    case FishType::BLUE:
                        ///blue_fish.Draw(camera, object_shader, renderer);
                        break;
                    case FishType::GREEN_ORANGE:
                        green_orange_fish.Draw(camera, object_shader, renderer);
                        break;
                    }
                }
            }

            //rendering rock 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 0.6f, -8.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-15.0f, 1.2f, -9.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }
            //rendering rock 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 0.6f, 2.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }

            //rendering rock 4
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 0.6f, -2.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }
            //rendering rock 5
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 1.2f, -2.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }
            //rendering rock 6
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(19.0f, 1.2f, -1.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            rock.Draw(camera, object_shader, renderer);

            }
            //rendering star 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+15.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }
            //rendering star 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(-17.0f, 1.95f, -2.0f));
            model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }
            //rendering star 3
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(17.0f, 1.95f, 2.0f));
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, .0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            star.Draw(camera, object_shader, renderer);

            }
            //rendering coral 1
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+17.0f, 1.2f, -8.0f));
            model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 2
            {  glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, aquarium_translation);
            model = glm::translate(model, glm::vec3(+13.0f, 1.2f, -9.3f));
            model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
            model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shadow_depth_map.Bind(1);
            object_shader.Bind();
            object_shader.SetUniformMat4f("u_ModelMatrix", model);
            object_shader.SetUniform1i("shadowMap", 1);
            coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 3
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(-15.0f, 1.2f, -5.0f));
                model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                coral.Draw(camera, object_shader, renderer);

            }
            //rendering coral 4
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(-11.0f, 1.2f, -8.0f));
                model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                coral.Draw(camera, object_shader, renderer);

            }

            //rendering coral 5
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(15.0f, 1.2f, 0.0f));
                model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                coral.Draw(camera, object_shader, renderer);

            }
            //rendering coralv2 1
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(+17.0f, 0.9f, -5.0f));
                model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                coral2.Draw(camera, object_shader, renderer);

            }

            //rendering coralv2 2
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(-14.5f, 0.9f, -3.0f));
                model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                coral2.Draw(camera, object_shader, renderer);

            }

            //rendering coral v2 3
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(-18.0f, 0.8f, 1.0f));
                model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                coral2.Draw(camera, object_shader, renderer);

            }
            //rendering coral v2 4
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(10.0f, 0.8f, -9.0f));
                model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                coral2.Draw(camera, object_shader, renderer);

            }

            //rendering plant2
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(19.0f, 0.5f, 3.0f));
                model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant2.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 1
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(-18.0f, 0.2f, -6.0f));
                model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
                model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 2
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(-18.0f, 0.5f, -10.0f));
                model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
                model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 3
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(-14.0f, 0.1f, -8.0f));
                model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
                model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 4
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(17.5f, 0.5f, 0.0f));
                model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
                model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 5
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(19.0f, 0.5f, 3.0f));
                model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
                model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 6
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(19.0f, 0.5f, -2.5f));
                model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
                model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant1.Draw(camera, object_shader, renderer);

            }

            //rendering plant1 7
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(19.0f, 0.5f, -6.0f));
                model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
                model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant1.Draw(camera, object_shader, renderer);

            }
            //rendering plant1 8
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, aquarium_translation);
                model = glm::translate(model, glm::vec3(14.50f, 0.25f, -10.0f));
                model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
                model = glm::rotate(model, glm::radians(360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                shadow_depth_map.Bind(1);
                object_shader.Bind();
                object_shader.SetUniformMat4f("u_ModelMatrix", model);
                object_shader.SetUniform1i("shadowMap", 1);
                plant1.Draw(camera, object_shader, renderer);

            }
            //rendering light cube
            {
                glDisable(GL_CLIP_DISTANCE0);//the light cube should not be affected by the clipping

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, light_position);
                light_shader.Bind();
                light_shader.SetUniformMat4f("u_ModelMatrix", model);
                //light_cube.Draw(camera, light_shader, renderer);

                glEnable(GL_CLIP_DISTANCE0);
            }

            //rendering water
            {
                wave_move_factor += 0.05f * delta_time;
                if (wave_move_factor > 1)
                    wave_move_factor = 0.0f;

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, aquarium_translation);
                water_shader.Bind();
                water_shader.SetUniformMat4f("u_ModelMatrix", model);
                water_shader.SetUniform1f("u_WaveMoveFactor", wave_move_factor);
                refraction.Bind(1);
                water_DuDv.Bind(2);
                water_NormalMap.Bind(3);
                depth_map.Bind(4);
                water_shader.SetUniform1i("u_ReflectionTexture", 0);
                water_shader.SetUniform1i("u_RefractionTexture", 1);
                water_shader.SetUniform1i("u_DuDvMap", 2);
                water_shader.SetUniform1i("u_NormalMap", 3);
                water_shader.SetUniform1i("u_DepthMap", 4);

                water_shader.SetUniform1i("u_isSurface", 1);
                surface_water.Draw(camera, water_shader, renderer);

                model = glm::mediump_mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, aquarium_translation);
                water_shader.Bind();
                water_shader.SetUniformMat4f("u_ModelMatrix", model);
                water_shader.SetUniform1i("u_isSurface", 0);
                side_water.Draw(camera, water_shader, renderer);
            }

            //rendering aquarium glass
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model, aquarium_scaling);
                model = glm::translate(model, aquarium_translation);
                glass_shader.Bind();
                glass_shader.SetUniformMat4f("u_ModelMatrix", model);

                //needed for good transparency, the positions will represent the centers of the panels
                std::array<glm::vec3, 6> glass_panels_positions =
                {
                    //front panel left                //front panel right
                    glm::vec3(-7.0f,  2.8f,  0.65f), glm::vec3(7.0f,  2.8f,  0.65f),//front panel
                    //back panel left                 //back panel right
                    glm::vec3(-7.0f,  2.8f, -7.65f), glm::vec3(7.0f,  2.8f, -7.65f),//back panel
                    glm::vec3(10.1f,  2.8f, -4.1f),//right panel
                    glm::vec3(-10.1f,  2.8f, -4.1f) //left panel
                };

                for (unsigned int panel_index = 0; panel_index < glass_panels_positions.size(); panel_index++)
                    glass_panels_positions[panel_index] += aquarium_translation;
                //determine draw order based on panel distance from camera
                std::array<std::pair<float, unsigned int>, 6> panels_distances_from_camera = //pair< distance from camera, panel index >
                {
                    std::make_pair(0.0f, 0), std::make_pair(0.0f, 0),
                    std::make_pair(0.0f, 1), std::make_pair(0.0f, 1),
                    std::make_pair(0.0f, 2),
                    std::make_pair(0.0f, 3)
                };

                std::array < std::pair<float, unsigned int>, 4> draw_order =
                {
                    std::make_pair(-1.0f, 0),
                    std::make_pair(-1.0f, 1),
                    std::make_pair(-1.0f, 2),
                    std::make_pair(-1.0f, 3)
                };
                //calculate distances
                for (unsigned int panel_index = 0; panel_index < panels_distances_from_camera.size(); panel_index++)
                {
                    panels_distances_from_camera[panel_index].first = glm::length(camera.GetPosition() - glass_panels_positions[panel_index]);

                    if (panels_distances_from_camera[panel_index].first < draw_order[panels_distances_from_camera[panel_index].second].first
                        || draw_order[panels_distances_from_camera[panel_index].second].first == -1.0f)
                        draw_order[panels_distances_from_camera[panel_index].second].first = panels_distances_from_camera[panel_index].first;
                }

                //sort the panels from furthest to closest
                std::sort(draw_order.begin(), draw_order.end(), [](const std::pair<float, unsigned int>& element1,
                    const std::pair<float, unsigned int>& element2) -> bool { return element1.first > element2.first; });

                for (unsigned int panel_index = 0; panel_index < glass_panels.size(); panel_index++)
                    glass_panels[draw_order[panel_index].second].Draw(camera, glass_shader, renderer);
            }
        }

        //update fish positions
        for (auto& fish_charact : fishes_charact)
            fish_charact.position = fish_charact.next_position;

        // Swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}