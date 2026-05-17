// ============================================================
//  STUDENT 5 — Fabric Wave Engine + Flag Pole + Drop Shadow + Stripes
//  Name   : Melaku
//  Branch : feature/melaku-flag-wave
//  File   : melaku_flag_wave.cpp
//  Role   : Physics engine for waving effect, pole, and shadow rendering.
//  Depends on: student1–3 files
// ============================================================

// ─────────────────────────────────────────────────────────────
//  2D Fabric Wave Engine

// ─────────────────────────────────────────────────────────────
static void fabricWave(float nx, float ny,
                        float /*fW*/, float /*fH*/,
                        float& outDX, float& outDY)
{

    float amp          = nx * nx * 14.0f * windSpeed;
    float phase        = waveOffset - nx * 4.5f;
    float waveY_primary    = sinf(phase) * amp;


    float ampY               = nx * 5.0f * windSpeed;
    float waveY_secondary  = sinf(phase * 1.3f + ny * (float)M_PI) * ampY;
    float crumple          = sinf(phase * 2.7f + ny * 6.0f) * nx * 2.5f * windSpeed;
    float edgeWave         = cosf(waveOffset * 0.8f + ny * 3.5f) * nx * 3.5f * windSpeed;

    outDX = edgeWave * 0.3f;
    outDY = waveY_primary + waveY_secondary + crumple;
}

// ─────────────────────────────────────────────────────────────
//  Draw Pole, Shadow and Stripes
// ─────────────────────────────────────────────────────────────
static void drawPoleAndStripes(float FX, float FY, float FW, float FH,
                                int NX, int NY)
{
    // ── Flag pole ────────────────────────────
    glLineWidth(8);
    glBegin(GL_LINES);
    glColor3f(0.25f,0.25f,0.25f); glVertex2f(FX-8.f, FY-20.f);
    glColor3f(0.55f,0.55f,0.55f); glVertex2f(FX-8.f, FY+FH+20.f);
    glEnd();


    float ballCX = FX - 8.f;
    float ballCY = FY + FH + 22.f;
    float ballR  = 10.f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.9f, 0.3f);
    glVertex2f(ballCX - ballR*0.25f, ballCY + ballR*0.3f);
    for (int i=0;i<=60;i++){
        float a = 2.f*(float)M_PI*i/60;
        float t = (float)i/60;
        glColor3f(1.0f-t*0.5f, 0.9f-t*0.4f, 0.1f+t*0.1f);
        glVertex2f(ballCX + ballR*cosf(a), ballCY + ballR*sinf(a));
    }
    glEnd();


    struct Pt2 { float x, y; };
    std::vector<std::vector<Pt2>> grid(NY+1, std::vector<Pt2>(NX+1));
    for (int iy=0;iy<=NY;iy++){
        for (int ix=0;ix<=NX;ix++){
            float nx_=(float)ix/NX, ny_=(float)iy/NY;
            float bx=FX+nx_*FW, by=FY+ny_*FH;
            float dx,dy;
            fabricWave(nx_,ny_,FW,FH,dx,dy);
            grid[iy][ix]={bx+dx,by+dy};
        }
    }


    float shadowOff=7.0f;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    for (int iy=0;iy<NY;iy++){
        for (int ix=0;ix<NX;ix++){
            Pt2 bl=grid[iy][ix],br=grid[iy][ix+1];
            Pt2 tl=grid[iy+1][ix],tr=grid[iy+1][ix+1];
            glColor4f(0,0,0,0.18f); // ግልጽነት ያለው ጥቁር
            glBegin(GL_QUADS);
            glVertex2f(bl.x+shadowOff,bl.y-shadowOff);
            glVertex2f(br.x+shadowOff,br.y-shadowOff);
            glVertex2f(tr.x+shadowOff,tr.y-shadowOff);
            glVertex2f(tl.x+shadowOff,tl.y-shadowOff);
            glEnd();
        }
    }


    float sc[4][3]={
        {0.00f,0.18f,0.68f},
        {0.82f,0.08f,0.08f},
        {0.96f,0.96f,0.96f},
        {0.96f,0.80f,0.00f}
    };
    for (int s=0;s<4;s++){
        int iyMin=(s*NY)/4, iyMax=((s+1)*NY)/4;
        glColor3f(sc[s][0],sc[s][1],sc[s][2]);
        for (int iy=iyMin;iy<iyMax;iy++){
            glBegin(GL_QUAD_STRIP);
            for (int ix=0;ix<=NX;ix++){
                glVertex2f(grid[iy][ix].x,grid[iy][ix].y);
                glVertex2f(grid[iy+1][ix].x,grid[iy+1][ix].y);
            }
            glEnd();
        }
    }
}
