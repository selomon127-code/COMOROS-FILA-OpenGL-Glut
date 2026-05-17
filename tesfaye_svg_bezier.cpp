// ============================================================
//  STUDENT 2 — SVG Coordinate Mapper + Cubic Bézier Tessellator
//  Name   : Tesfaye
//  Branch : feature/tesfaye-svg-bezier
//  File   : tesfaye_svg_bezier.cpp
//  Role   : Mapping SVG data to OpenGL coordinates and curve math.
//  Depends on: student1_globals.cpp (Vec2, Contour, FILA_* constants)
// ============================================================

// ─────────────────────────────────────────────────────────────
//  Map SVG coords → Window coords
//  SVG uses top-left origin; OpenGL uses bottom-left → flip Y.
// ─────────────────────────────────────────────────────────────
static Vec2 svgToGL(double sx, double sy)
{
    double rangeX = SVG_MAX_X - SVG_MIN_X;
    double rangeY = SVG_MAX_Y - SVG_MIN_Y;
    double margin = 0.06;
    double drawW  = FILA_W * (1.0 - 2.0 * margin);
    double drawH  = FILA_H * (1.0 - 2.0 * margin);
    double scale  = std::min(drawW / rangeX, drawH / rangeY) * 0.75;
    double offX   = FILA_W * margin + (drawW - rangeX * scale) / 2.0;
    double offY   = FILA_H * margin + (drawH - rangeY * scale) / 2.0 - 40.0;

    double gx = FILA_X0 + offX + (sx - SVG_MIN_X) * scale;
    double gy = FILA_Y0 + offY + (SVG_MAX_Y - sy) * scale;
    return {gx, gy};
}

// ─────────────────────────────────────────────────────────────
//  Cubic Bézier Tessellation
//  Splits a cubic curve into `samples` line segments and appends
//  the resulting points to `out`.
// ─────────────────────────────────────────────────────────────
static void cubicBezier(Contour& out,
                         Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3,
                         int samples = 120)
{
    for (int i = 1; i <= samples; ++i)
    {
        double t  = (double)i / samples;
        double mt = 1.0 - t;
        double x  = mt*mt*mt*p0.x + 3*mt*mt*t*p1.x + 3*mt*t*t*p2.x + t*t*t*p3.x;
        double y  = mt*mt*mt*p0.y + 3*mt*mt*t*p1.y + 3*mt*t*t*p2.y + t*t*t*p3.y;
        out.push_back({x, y});
    }
}
