#pragma once
#include <cmath>
#include <vector>
#include "imgui/imgui.h"
#include "sdk/Bayonetta.hpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class WorldVisualizer {
public:
    static Matrix3x3 CreateRotationMatrix(float pitchRad, float yawRad, float rollRad);

    static Vec3 RotatePoint(const Vec3& point, const Vec3& center, const Matrix3x3& rotation);

    static bool IsValidScreenPos(float x, float y, float w);

    static bool WorldToScreen(const Vec3& worldPos, ImVec2& screenPos);

    static void SetViewProjectionMatrix(const Matrix4x4& matrix);

    static void SetDrawList(ImDrawList* list = nullptr);

    static ImDrawList* GetDrawList();

    static void DrawWorldLine(const Vec3& start, const Vec3& end, ImU32 color = IM_COL32(255, 255, 255, 255), float thickness = 1.0f);

    static void DrawWorldTriangle(const Vec3& p0, const Vec3& p1, const Vec3& p2, ImU32 color, float thickness);

    static void DrawWorldFilledTriangle(const Vec3& p0, const Vec3& p1, const Vec3& p2, ImU32 color);

    static void DrawWorldSphere(const Vec3& center, float radius, ImU32 color = IM_COL32(255, 255, 255, 128), int segments = 32, float thickness = 1.0f, const Matrix3x3* rot = nullptr);

    static void DrawWorldFilledSphere(const Vec3& center, float radius, ImU32 color = IM_COL32(255, 255, 255, 128));

    static void DrawWorldCapsule(const Vec3& start, const Vec3& end, float radius, ImU32 color = IM_COL32(255, 255, 255, 128), int segments = 32, float thickness = 1.0f, const Matrix3x3* rot = nullptr);

    static void DrawWorldBox(const Vec3& min, const Vec3& max, ImU32 color = IM_COL32(255, 255, 255, 255), float thickness = 1.0f);

    static void DrawWorldPoint(const Vec3& pos, float size = 3.0f, ImU32 color = IM_COL32(255, 0, 0, 255));

    static void DrawWorldText(const Vec3& pos, const char* text, ImU32 color = IM_COL32(255, 255, 255, 255));

    static void DrawWorldArrow(const Vec3& start, const Vec3& end, ImU32 color = IM_COL32(255, 255, 255, 255), float thickness = 1.0f, float arrowSize = 10.0f);

    static void DrawWorldPolyline(const std::vector<Vec3>& points, ImU32 color = IM_COL32(255, 255, 255, 255), float thickness = 1.0f, bool closed = false);

    static void DrawWorldGrid(const Vec3& center, float size, int divisions = 10, ImU32 color = IM_COL32(128, 128, 128, 255), float thickness = 1.0f);

private:
    static ImDrawList* currentDrawList;
    static Matrix4x4 viewProjectionMatrix;
};
