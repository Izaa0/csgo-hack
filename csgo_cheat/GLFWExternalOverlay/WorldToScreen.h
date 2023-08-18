#pragma once
#include "datatypes.h"

void ConvertToRange(Vec2& Point)
{
    Point.X /= 1920.0f;
    Point.X *= 2.0f;
    Point.X -= 1.0f;

    Point.Y /= 1080.0f;
    Point.Y *= 2.0f;
    Point.Y -= 1.0f;


}


bool WorldToScreen(const Vec3 VecOrigin, Vec2& VecScreen, float* Matrix)
{
    Vec4 clipCoords = {};

    clipCoords.X = VecOrigin.X * Matrix[0] + VecOrigin.Y * Matrix[1] + VecOrigin.Z * Matrix[2] + Matrix[3];
    clipCoords.Y = VecOrigin.X * Matrix[4] + VecOrigin.Y * Matrix[5] + VecOrigin.Z * Matrix[6] + Matrix[7];
    clipCoords.W = VecOrigin.X * Matrix[12] + VecOrigin.Y * Matrix[13] + VecOrigin.Z * Matrix[14] + Matrix[15];

    if (clipCoords.W < 0.1f)
    {
        return false;
    }

    Vec3 NDC;
    NDC.X = clipCoords.X / clipCoords.W;
    NDC.Y = clipCoords.Y / clipCoords.W;

    VecScreen.X = (1920 / 2 * NDC.X) + (NDC.X + 1920 / 2);
    VecScreen.Y = (1080 / 2 * NDC.Y) + (NDC.Y + 1080 / 2);

    ConvertToRange(VecScreen);

    return true;
}