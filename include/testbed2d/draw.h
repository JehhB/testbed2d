#ifndef TESTBED_DRAW_H
#define TESTBED_DRAW_H

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <box2d/box2d.h>

#define INITIAL_WINDOW_WIDTH 854
#define INITIAL_WINDOW_HEIGHT 640

struct GLRenderPoints;
struct GLRenderLines;
struct GLRenderTriangles;

struct Viewport
{
	Viewport()
	{
		width = INITIAL_WINDOW_WIDTH;
		height = INITIAL_WINDOW_HEIGHT;
		zoom = 1.0f;
		center.Set(0.0f, 0.0f);
	}

	int height;
	int width;
	float zoom;
	b2Vec2 center;

	b2Vec2 convertScreenToWorld(const b2Vec2 &ps);
	b2Vec2 convertWorldToScreen(const b2Vec2 &pw);
	void buildProjectionMatrix(float *m, float zBias);
};

class DebugDraw : public b2Draw
{
public:
	DebugDraw();
	~DebugDraw();

	void Create();
	void Destroy();

	void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

	void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

	void DrawCircle(const b2Vec2 &center, float radius, const b2Color &color) override;

	void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) override;

	void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;

	void DrawTransform(const b2Transform &xf) override;

	void DrawPoint(const b2Vec2 &p, float size, const b2Color &color) override;

	void DrawString(int x, int y, const char *string, ...);

	void DrawString(const b2Vec2 &p, const char *string, ...);

	void DrawAABB(b2AABB *aabb, const b2Color &color);

	void Flush();

	bool showUI;
	GLRenderPoints *points;
	GLRenderLines *lines;
	GLRenderTriangles *triangles;
	Viewport *viewport;
};

#endif
