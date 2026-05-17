// ============================================================
//  STUDENT 1 — Project Setup, Headers, Constants & Global State
//  Name   : Solomon (Group Owner)
//  Branch : feature/solomon-globals
//  File   : student1_globals.cpp
//  Role   : Project structure, window constants, and animation state.
// ============================================================

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include <GL/glu.h>

#ifndef CALLBACK
#define CALLBACK
#endif

#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

// ─────────────────────────────────────────────────────────────
//  Window and Layout Constants
// ─────────────────────────────────────────────────────────────
static const int WIN_W = 1100;
static const int WIN_H = 420;
static const float FLAG_SCALE = 0.88f;
static const int FILA_X0 = 320;
static const int FILA_Y0 = 0;
static const int FILA_W  = WIN_W - FILA_X0 - 10;
static const int FILA_H  = WIN_H;

// ─────────────────────────────────────────────────────────────
//  Animation & Interaction State
// ─────────────────────────────────────────────────────────────
float waveOffset      = 0.0f;
float windSpeed       = 1.0f;   // range [0.0 .. 5.0]
float flagRotation    = 0.0f;   // degrees
float flagScaleFactor = 1.0f;   // uniform scale
float flagTX = 0.0f, flagTY = 0.0f;

// ─────────────────────────────────────────────────────────────
//  Types for FILA Tessellation
// ─────────────────────────────────────────────────────────────
struct Vec2 { double x, y; };
typedef std::vector<Vec2> Contour;
typedef std::vector<Contour> Shape;

// ─────────────────────────────────────────────────────────────
//  SVG Bounding Box
// ─────────────────────────────────────────────────────────────
static const double SVG_MIN_X =  28.0;
static const double SVG_MIN_Y = 295.0;
static const double SVG_MAX_X = 592.0;
static const double SVG_MAX_Y = 505.0;
