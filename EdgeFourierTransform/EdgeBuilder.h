#ifndef EDGEBUILDER_H
#define EDGEBUILDER_H

#include "Fourier.h"

class EdgeBuilder
{
private:

    ComplexVector m_vertices;

    static bool s_randomSeeded;

public:

    EdgeBuilder();
    EdgeBuilder(const EdgeBuilder& eb);
    ~EdgeBuilder();

    EdgeBuilder& operator=(const EdgeBuilder& eb);

    void clear();
    void addVertex(const Complex& v);

    void getEdgePoints(ComplexVector& points);

private:

    void initializeRandom();

    void addAllEdgePoints(ComplexVector& points);
    void addEdgePoints(ComplexVector& points, uint edgeStartVertex, uint edgeEndVertex);
    void addEdgePoints(ComplexVector& points, const Complex& p1, const Complex& p2);
    void restrictPointCountTo2Power(ComplexVector& points);
};

#endif // EDGEBUILDER_H
