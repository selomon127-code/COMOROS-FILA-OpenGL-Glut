// ============================================================
//  STUDENT 7 — Input Handling, Animation Timer, display(), main()
//  Name   :able
//  Branch : feature/abel-main-loop
//  File   : student7_main_loop.cpp
//  Role   : Integrating all student files, handling keyboard events,
//           and running the main GLUT loop.
//  NOTE   : This file contains main() and ties everything together.
// ============================================================

// ─────────────────────────────────────────────────────────────
//  Keyboard –  (Wind, Rotation, Scale)
// ─────────────────────────────────────────────────────────────
void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
    switch (key)
    {

    case '+': case '=': windSpeed = std::min(5.0f, windSpeed + 0.2f); break;
    case '-': case '_': windSpeed = std::max(0.0f, windSpeed - 0.2f); break;


    case 'R': flagRotation = fmodf(flagRotation + 5.f, 360.f); break;
    case 'r': flagRotation = fmodf(flagRotation - 5.f + 360.f, 360.f); break;


    case 'S': flagScaleFactor = std::min(2.5f, flagScaleFactor + 0.05f); break;
    case 's': flagScaleFactor = std::max(0.3f, flagScaleFactor - 0.05f); break;


    case 27: exit(0); break;
    }
    glutPostRedisplay();
}


void specialKey(int key, int /*x*/, int /*y*/)
{
    switch (key)
    {
    case GLUT_KEY_UP:    flagTY += 10.f; break;
    case GLUT_KEY_DOWN:  flagTY -= 10.f; break;
    case GLUT_KEY_LEFT:  flagTX -= 10.f; break;
    case GLUT_KEY_RIGHT: flagTX += 10.f; break;
    }
    glutPostRedisplay();
}

// ─────────────────────────────────────────────────────────────
//  Animation Timer
// ─────────────────────────────────────────────────────────────
void update(int value)
{
    waveOffset += 0.06f * windSpeed;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// ─────────────────────────────────────────────────────────────
//  Display Callback
// ─────────────────────────────────────────────────────────────
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, 0, WIN_H);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawBackground();
    drawFlag();
    drawFILA();

    glutSwapBuffers();
}

// ─────────────────────────────────────────────────────────────
//  Main Entry Point
// ─────────────────────────────────────────────────────────────
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL | GLUT_MULTISAMPLE);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Comoros Flag + FILA Logo [Group Project]");


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);


    g_trisFBody  = buildPath(PATH_F_BODY);
    g_trisFCross = buildPath(PATH_F_CROSSBAR);
    g_trisI      = buildPath(PATH_I);
    g_trisLA     = buildPath(PATH_LA);


    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
