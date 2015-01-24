#include "EdgeBuilder.h"

#include <cmath>
#include <time.h>
#include <stdlib.h>

bool EdgeBuilder::s_randomSeeded = false;

EdgeBuilder::EdgeBuilder()
{
    initializeRandom();
}
EdgeBuilder::EdgeBuilder(const EdgeBuilder& eb)
{
    initializeRandom();

    *this = eb;
}
EdgeBuilder::~EdgeBuilder()
{
}

EdgeBuilder& EdgeBuilder::operator=(const EdgeBuilder& eb)
{
    m_vertices = eb.m_vertices;

    return *this;
}

void EdgeBuilder::initializeRandom()
{
    if (!s_randomSeeded)
    {
        srand(time(0));
        s_randomSeeded = true;
    }
}

void EdgeBuilder::clear()
{
    m_vertices.clear();
}
void EdgeBuilder::addVertex(const Complex& v)
{
    m_vertices.push_back(v);
}

void EdgeBuilder::getEdgePoints(ComplexVector& points)
{
    addAllEdgePoints(points);
    restrictPointCountTo2Power(points);
}

void EdgeBuilder::addAllEdgePoints(ComplexVector& points)
{
    uint i;
    uint vertexCount;

    points.clear();

    vertexCount = m_vertices.size();

    if (vertexCount == 1)
    {
        points.push_back(m_vertices.front());
    }
    else if (vertexCount > 1)
    {
        for (i = 0; i < (vertexCount - 1); ++i)
            addEdgePoints(points, i, i + 1);

        addEdgePoints(points, vertexCount - 1, 0);
    }
}

void EdgeBuilder::addEdgePoints(ComplexVector& points, uint edgeStartVertex, uint edgeEndVertex)
{
//    ComplexVector edgePoints;

//    addEdgePoints(edgePoints, m_vertices[edgeStartVertex], m_vertices[edgeEndVertex]);

//    points.insert(points.end(), edgePoints.begin(), edgePoints.end());

    addEdgePoints(points, m_vertices[edgeStartVertex], m_vertices[edgeEndVertex]);
}
void EdgeBuilder::addEdgePoints(ComplexVector& points, const Complex& p1, const Complex& p2)
{
    int drow, dcol, i, e;
    int incR, incC, inc1, inc2;
    int row,col;

    int col1 = p1.real();
    int row1 = p1.imag();

    int col2 = p2.real();
    int row2 = p2.imag();

    //points.clear();

    drow = abs(row2 - row1);
    dcol = abs(col2 - col1);

    incR = 1;
    if(row2 < row1) incR = -1;
    incC = 1;
    if(col2 < col1) incC = -1;
    row = row1;
    col = col1;

    points.push_back(Complex(col, row));

    if(drow > dcol)
    {
        e = 2 * dcol - drow;
        inc1 = 2 * (dcol -drow);
        inc2 = 2 * dcol;
        for(i = 0; i < drow; ++i)
        {
            if(e >= 0)
            {
                col += incC;
                e += inc1;
            }
            else
            {
                e += inc2;
            }

            row += incR;

            points.push_back(Complex(col, row));
        }
    }
    else
    {
        e = 2 * drow - dcol;
        inc1 = 2 * (drow - dcol);
        inc2 = 2 * drow;
        for(i = 0; i < dcol; ++i)
        {
            if(e >= 0)
            {
                row += incR;
                e += inc1;
            }
            else
            {
                e += inc2;
            }

            col += incC;

            points.push_back(Complex(col, row));
        }
    }
}

void EdgeBuilder::restrictPointCountTo2Power(ComplexVector& points)
{
    int i;
    int removeCount;

    removeCount = (int)points.size() - pow(2, (int)log2(points.size()));

    for (i = 0; i < removeCount; ++i)
        points.erase(points.begin() + (rand() % points.size()));
}
