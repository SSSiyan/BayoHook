#include "WorldVisualizer.hpp"

ImDrawList* WorldVisualizer::currentDrawList = nullptr;
Matrix4x4 WorldVisualizer::viewProjectionMatrix;

void WorldVisualizer::SetViewProjectionMatrix(const Matrix4x4& matrix) {
    viewProjectionMatrix = matrix;
}

bool WorldVisualizer::IsValidScreenPos(float x, float y, float w) {
    if (w <= 0.0f) return false;

    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    float margin = 100.0f; // Allow some margin for off-screen drawing

    return x >= -margin && x <= displaySize.x + margin &&
        y >= -margin && y <= displaySize.y + margin;
}

bool WorldVisualizer::WorldToScreen(const Vec3& worldPos, ImVec2& screenPos) {
    float x = worldPos.x * viewProjectionMatrix.m[0][0] +
        worldPos.y * viewProjectionMatrix.m[1][0] +
        worldPos.z * viewProjectionMatrix.m[2][0] +
        viewProjectionMatrix.m[3][0];

    float y = worldPos.x * viewProjectionMatrix.m[0][1] +
        worldPos.y * viewProjectionMatrix.m[1][1] +
        worldPos.z * viewProjectionMatrix.m[2][1] +
        viewProjectionMatrix.m[3][1];

    float z = worldPos.x * viewProjectionMatrix.m[0][2] +
        worldPos.y * viewProjectionMatrix.m[1][2] +
        worldPos.z * viewProjectionMatrix.m[2][2] +
        viewProjectionMatrix.m[3][2];

    float w = worldPos.x * viewProjectionMatrix.m[0][3] +
        worldPos.y * viewProjectionMatrix.m[1][3] +
        worldPos.z * viewProjectionMatrix.m[2][3] +
        viewProjectionMatrix.m[3][3];

    // Perspective divide
    if (w <= 0.0001f) return false;

    float invW = 1.0f / w;
    x *= invW;
    y *= invW;

    // Convert from NDC to screen
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    screenPos.x = (x + 1.0f) * 0.5f * displaySize.x;
    screenPos.y = (1.0f - y) * 0.5f * displaySize.y;

    return true;
}

void WorldVisualizer::SetDrawList(ImDrawList* list) {
    currentDrawList = list;
}

ImDrawList* WorldVisualizer::GetDrawList() {
    if (!currentDrawList) {
        currentDrawList = ImGui::GetBackgroundDrawList();
    }
    return currentDrawList;
}

void WorldVisualizer::DrawWorldLine(const Vec3& start, const Vec3& end, ImU32 color, float thickness) {
    ImVec2 screenStart, screenEnd;
    if (WorldToScreen(start, screenStart) && WorldToScreen(end, screenEnd)) {
        GetDrawList()->AddLine(screenStart, screenEnd, color, thickness);
    }
}

void WorldVisualizer::DrawWorldTriangle(const Vec3& p0, const Vec3& p1, const Vec3& p2, ImU32 color, float thickness) {
    DrawWorldLine(p0, p1, color, thickness);
    DrawWorldLine(p1, p2, color, thickness);
    DrawWorldLine(p2, p0, color, thickness);
}

void WorldVisualizer::DrawWorldFilledTriangle(const Vec3& p0, const Vec3& p1, const Vec3& p2, ImU32 color) {
    ImVec2 screen0, screen1, screen2;
    if (WorldToScreen(p0, screen0) && WorldToScreen(p1, screen1) && WorldToScreen(p2, screen2)) {
        GetDrawList()->AddTriangleFilled(screen0, screen1, screen2, color);
    }
}

Matrix3x3 WorldVisualizer::CreateRotationMatrix(float pitchRad, float yawRad, float rollRad) {
    float cp = cosf(pitchRad), sp = sinf(pitchRad);
    float cy = cosf(yawRad), sy = sinf(yawRad);
    float cr = cosf(rollRad), sr = sinf(rollRad);

    Matrix3x3 rot;

    rot.m[0][0] = cy * cr + sy * sp * sr;
    rot.m[0][1] = sr * cp;
    rot.m[0][2] = sy * cr - cy * sp * sr;

    rot.m[1][0] = -cy * sr + sy * sp * cr;
    rot.m[1][1] = cr * cp;
    rot.m[1][2] = sr * sy + cy * sp * cr;

    rot.m[2][0] = -sy * cp;
    rot.m[2][1] = -sp;
    rot.m[2][2] = cy * cp;

    return rot;
}

Vec3 WorldVisualizer::RotatePoint(const Vec3& point, const Vec3& center, const Matrix3x3& rotation) {
    Vec3 local = { point.x - center.x, point.y - center.y, point.z - center.z };
    Vec3 rotated;
    rotated.x = local.x * rotation.m[0][0] + local.y * rotation.m[0][1] + local.z * rotation.m[0][2];
    rotated.y = local.x * rotation.m[1][0] + local.y * rotation.m[1][1] + local.z * rotation.m[1][2];
    rotated.z = local.x * rotation.m[2][0] + local.y * rotation.m[2][1] + local.z * rotation.m[2][2];
    return { rotated.x + center.x, rotated.y + center.y, rotated.z + center.z };
}

void WorldVisualizer::DrawWorldSphere(const Vec3& center, float radius, ImU32 color, int segments, float thickness, const Matrix3x3* rot) {
    Matrix3x3 rotation = rot ? *rot : Matrix3x3::Identity();

    const float angleStep = 2.0f * M_PI / segments;

    // XY plane circle
    for (int i = 0; i < segments; ++i) {
        float a1 = i * angleStep;
        float a2 = (i + 1) * angleStep;

        Vec3 p1 = { center.x + radius * cosf(a1), center.y + radius * sinf(a1), center.z };
        Vec3 p2 = { center.x + radius * cosf(a2), center.y + radius * sinf(a2), center.z };

        if (rot) {
            p1 = RotatePoint(p1, center, rotation);
            p2 = RotatePoint(p2, center, rotation);
        }

        DrawWorldLine(p1, p2, color, thickness);
    }

    // XZ plane circle
    for (int i = 0; i < segments; ++i) {
        float a1 = i * angleStep;
        float a2 = (i + 1) * angleStep;

        Vec3 p1 = { center.x + radius * cosf(a1), center.y, center.z + radius * sinf(a1) };
        Vec3 p2 = { center.x + radius * cosf(a2), center.y, center.z + radius * sinf(a2) };

        if (rot) {
            p1 = RotatePoint(p1, center, rotation);
            p2 = RotatePoint(p2, center, rotation);
        }

        DrawWorldLine(p1, p2, color, thickness);
    }

    // YZ plane circle
    for (int i = 0; i < segments; ++i) {
        float a1 = i * angleStep;
        float a2 = (i + 1) * angleStep;

        Vec3 p1 = { center.x, center.y + radius * cosf(a1), center.z + radius * sinf(a1) };
        Vec3 p2 = { center.x, center.y + radius * cosf(a2), center.z + radius * sinf(a2) };

        if (rot) {
            p1 = RotatePoint(p1, center, rotation);
            p2 = RotatePoint(p2, center, rotation);
        }

        DrawWorldLine(p1, p2, color, thickness);
    }
}

void WorldVisualizer::DrawWorldCapsule( const Vec3& start, const Vec3& end, float radius, ImU32 color, int segments, float thickness, const Matrix3x3* rot) {
    Matrix3x3 rotation = rot ? *rot : Matrix3x3::Identity();

    // Draw hemispheres at start and end
    WorldVisualizer::DrawWorldSphere(start, radius, color, segments, thickness, rot);
    WorldVisualizer::DrawWorldSphere(end, radius, color, segments, thickness, rot);

    // Draw cylinder edges
    Vec3 dir = end - start;
    float length = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (length <= 0.0001f) return;

    Vec3 axis = dir / length; // normalized axis

    // Generate a circle perpendicular to axis
    for (int i = 0; i < segments; ++i) {
        float angle1 = (float)i / segments * 2.0f * M_PI;
        float angle2 = (float)(i + 1) / segments * 2.0f * M_PI;

        // Circle in local XZ plane
        Vec3 offset1 = { radius * cosf(angle1), 0.0f, radius * sinf(angle1) };
        Vec3 offset2 = { radius * cosf(angle2), 0.0f, radius * sinf(angle2) };

        // Rotate offsets if a rotation is provided
        if (rot) {
            offset1 = WorldVisualizer::RotatePoint(offset1, Vec3{ 0,0,0 }, rotation);
            offset2 = WorldVisualizer::RotatePoint(offset2, Vec3{ 0,0,0 }, rotation);
        }

        // Connect start and end circles
        Vec3 p1_start = start + offset1;
        Vec3 p2_start = start + offset2;
        Vec3 p1_end = end + offset1;
        Vec3 p2_end = end + offset2;

        WorldVisualizer::DrawWorldLine(p1_start, p2_start, color, thickness); // bottom circle
        WorldVisualizer::DrawWorldLine(p1_end, p2_end, color, thickness);     // top circle
        WorldVisualizer::DrawWorldLine(p1_start, p1_end, color, thickness);   // vertical edge
    }
}


void WorldVisualizer::DrawWorldFilledSphere(const Vec3& center, float radius, ImU32 color) {
    ImVec2 screenPos;
    if (WorldToScreen(center, screenPos)) {
        GetDrawList()->AddCircleFilled(screenPos, radius, color);
    }
}

void WorldVisualizer::DrawWorldBox(const Vec3& min, const Vec3& max, ImU32 color, float thickness) {
    Vec3 corners[8];
    corners[0] = Vec3(min.x, min.y, min.z); // 0
    corners[1] = Vec3(max.x, min.y, min.z); // 1
    corners[2] = Vec3(max.x, max.y, min.z); // 2
    corners[3] = Vec3(min.x, max.y, min.z); // 3
    corners[4] = Vec3(min.x, min.y, max.z); // 4
    corners[5] = Vec3(max.x, min.y, max.z); // 5
    corners[6] = Vec3(max.x, max.y, max.z); // 6
    corners[7] = Vec3(min.x, max.y, max.z); // 7

    // Draw bottom face
    DrawWorldLine(corners[0], corners[1], color, thickness);
    DrawWorldLine(corners[1], corners[2], color, thickness);
    DrawWorldLine(corners[2], corners[3], color, thickness);
    DrawWorldLine(corners[3], corners[0], color, thickness);

    // Draw top face
    DrawWorldLine(corners[4], corners[5], color, thickness);
    DrawWorldLine(corners[5], corners[6], color, thickness);
    DrawWorldLine(corners[6], corners[7], color, thickness);
    DrawWorldLine(corners[7], corners[4], color, thickness);

    // Draw vertical edges
    DrawWorldLine(corners[0], corners[4], color, thickness);
    DrawWorldLine(corners[1], corners[5], color, thickness);
    DrawWorldLine(corners[2], corners[6], color, thickness);
    DrawWorldLine(corners[3], corners[7], color, thickness);
}

void WorldVisualizer::DrawWorldPoint(const Vec3& pos, float size, ImU32 color) {
    ImVec2 screenPos;
    if (WorldToScreen(pos, screenPos)) {
        GetDrawList()->AddCircleFilled(screenPos, size, color);
    }
}

void WorldVisualizer::DrawWorldText(const Vec3& pos, const char* text, ImU32 color) {
    ImVec2 screenPos;
    if (WorldToScreen(pos, screenPos)) {
        GetDrawList()->AddText(screenPos, color, text);
    }
}

void WorldVisualizer::DrawWorldArrow(const Vec3& start, const Vec3& end, ImU32 color, float thickness, float arrowSize) {
    ImVec2 screenStart, screenEnd;
    if (WorldToScreen(start, screenStart) && WorldToScreen(end, screenEnd)) {
        // Draw main line
        GetDrawList()->AddLine(screenStart, screenEnd, color, thickness);

        // Calculate arrow head
        ImVec2 dir = ImVec2(screenEnd.x - screenStart.x, screenEnd.y - screenStart.y);
        float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
        if (length > 0) {
            dir.x /= length;
            dir.y /= length;

            // Arrow head points
            ImVec2 arrowP1 =
                ImVec2(screenEnd.x - arrowSize * (dir.x * 0.8f + dir.y * 0.6f),
                    screenEnd.y - arrowSize * (dir.y * 0.8f - dir.x * 0.6f));
            ImVec2 arrowP2 =
                ImVec2(screenEnd.x - arrowSize * (dir.x * 0.8f - dir.y * 0.6f),
                    screenEnd.y - arrowSize * (dir.y * 0.8f + dir.x * 0.6f));

            GetDrawList()->AddLine(screenEnd, arrowP1, color, thickness);
            GetDrawList()->AddLine(screenEnd, arrowP2, color, thickness);
        }
    }
}

void WorldVisualizer::DrawWorldPolyline(const std::vector<Vec3>& points, ImU32 color, float thickness, bool closed) {
    if (points.size() < 2)
        return;

    for (size_t i = 0; i < points.size() - 1; ++i) {
        DrawWorldLine(points[i], points[i + 1], color, thickness);
    }

    if (closed && points.size() > 2) {
        DrawWorldLine(points.back(), points.front(), color, thickness);
    }
}

void WorldVisualizer::DrawWorldGrid(const Vec3& center, float size, int divisions, ImU32 color, float thickness) {
    float step = size / divisions;
    float half = size * 0.5f;

    // Draw lines parallel to X axis
    for (int i = 0; i <= divisions; ++i) {
        float offset = -half + i * step;
        Vec3 start, end;
        start.x = center.x - half;
        start.y = center.y;
        start.z = center.z + offset;
        end.x = center.x + half;
        end.y = center.y;
        end.z = center.z + offset;
        DrawWorldLine(start, end, color, thickness);
    }

    // Draw lines parallel to Z axis
    for (int i = 0; i <= divisions; ++i) {
        float offset = -half + i * step;
        Vec3 start, end;
        start.x = center.x + offset;
        start.y = center.y;
        start.z = center.z - half;
        end.x = center.x + offset;
        end.y = center.y;
        end.z = center.z + half;
        DrawWorldLine(start, end, color, thickness);
    }
}
