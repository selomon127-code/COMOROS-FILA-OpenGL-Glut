// ============================================================
//  STUDENT 6 — Green Triangle, Crescent, Stars, drawFlag(), Background
//  Name   :nicolas
//  Branch : feature/nicolas-flag-symbols
//  File   : student6_flag_symbols.cpp
//  Role   : Drawing flag symbols (moon, stars), the green triangle,
//           and the overall environment background.
//  Depends on: student1–5 files
// ============================================================

static void setColor(float r, float g, float b) { glColor3f(r,g,b); }


static void drawStar5(float cx, float cy, float outer, float inner, float tilt)
{
    const int N = 5;
    float vx[10], vy[10];
    for (int i=0; i<N; i++){
        float ao = tilt + 2.f * (float)M_PI * i / N;
        float ai = ao + (float)M_PI / N;
        vx[2*i]   = cx + outer * cosf(ao); vy[2*i]   = cy + outer * sinf(ao);
        vx[2*i+1] = cx + inner * cosf(ai); vy[2*i+1] = cy + inner * sinf(ai);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i=0; i<10; i++) glVertex2f(vx[i], vy[i]);
    glVertex2f(vx[0], vy[0]);
    glEnd();
}

static void drawCrescent(float cx, float cy, float R, float cutOff, float cutR)
{
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);


    glBegin(GL_TRIANGLE_FAN); glVertex2f(cx, cy);
    for (int i=0; i<=120; i++){ float a=2.f*(float)M_PI*i/120; glVertex2f(cx+R*cosf(a),cy+R*sinf(a)); }
    glEnd();

    glStencilFunc(GL_ALWAYS, 0, 0xFF);

    glBegin(GL_TRIANGLE_FAN); glVertex2f(cx+cutOff, cy);
    for (int i=0; i<=120; i++){ float a=2.f*(float)M_PI*i/120; glVertex2f(cx+cutOff+cutR*cosf(a),cy+cutR*sinf(a)); }
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    setColor(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(cx, cy);
    for (int i=0; i<=120; i++){ float a=2.f*(float)M_PI*i/120; glVertex2f(cx+R*cosf(a),cy+R*sinf(a)); }
    glEnd();
    glDisable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
}


static void drawFlag()
{
    const float FX = 30.0f * FLAG_SCALE;
    const float FY = 70.0f * FLAG_SCALE;
    const float FW = 440.0f * FLAG_SCALE;
    const float FH = 280.0f * FLAG_SCALE;
    const int   NX = 55, NY = 35;


    float pivotX = FX + FW*0.5f + flagTX;
    float pivotY = FY + FH*0.5f + flagTY;
    glPushMatrix();
    glTranslatef(pivotX, pivotY, 0.f);
    glRotatef(flagRotation, 0.f, 0.f, 1.f);
    glScalef(flagScaleFactor, flagScaleFactor, 1.f);
    glTranslatef(-pivotX + flagTX, -pivotY + flagTY, 0.f);


    drawPoleAndStripes(FX, FY, FW, FH, NX, NY);


    setColor(0.00f, 0.48f, 0.13f);
    float triWidth = FW * 0.45f;
    float triNX    = triWidth / FW;
    const int EDGE_STEPS = 80;

    struct Pt2 { float x, y; };
    auto wavedPt = [&](float nx_, float ny_) -> Pt2 {
        float bx=FX+nx_*FW, by=FY+ny_*FH, dx, dy;
        fabricWave(nx_, ny_, FW, FH, dx, dy);
        return {bx+dx, by+dy};
    };

    std::vector<Pt2> triPoly;

    for (int i=0; i<=EDGE_STEPS; i++)
        triPoly.push_back(wavedPt(0.f, 1.f-(float)i/EDGE_STEPS));
    for (int i=1; i<=EDGE_STEPS; i++){
        float t=(float)i/EDGE_STEPS;
        triPoly.push_back(wavedPt(t*triNX, 0.5f - t*0.5f)); // Bottom edge
    }
    for (int i=1; i<=EDGE_STEPS; i++){
        float t=(float)i/EDGE_STEPS;
        triPoly.push_back(wavedPt(triNX*(1.f-t), 0.5f + t*0.5f)); // Top edge
    }


    float cx_=0, cy_=0;
    for (auto& p:triPoly) { cx_+=p.x; cy_+=p.y; }
    cx_/=triPoly.size(); cy_/=triPoly.size();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx_, cy_);
    for (auto& p:triPoly) glVertex2f(p.x, p.y);
    glVertex2f(triPoly[0].x, triPoly[0].y);
    glEnd();


    float moonR  = triWidth * 0.33f;
    float moonCX = FX + moonR + 10.f * FLAG_SCALE;
    float moonCY = FY + FH * 0.5f;
    drawCrescent(moonCX, moonCY, moonR, moonR*0.4f, moonR*0.98f);

    float starOuter = moonR * 0.20f, starInner = starOuter * 0.40f;
    float startY    = moonCY - moonR * 0.6f;
    setColor(1, 1, 1);
    for (int i=0; i<4; i++)
        drawStar5(moonCX + moonR*0.3f, startY + i*(moonR*0.45f),
                  starOuter, starInner, -(float)M_PI/2.6f);

    glPopMatrix();
}


static void drawBackground()
{
    glBegin(GL_QUADS);
    glColor3f(0.72f, 0.85f, 0.96f); glVertex2f(0, WIN_H);
    glColor3f(0.72f, 0.85f, 0.96f); glVertex2f(WIN_W, WIN_H);
    glColor3f(0.97f, 0.94f, 0.88f); glVertex2f(WIN_W, 0);
    glColor3f(0.97f, 0.94f, 0.88f); glVertex2f(0, 0);
    glEnd();
}
