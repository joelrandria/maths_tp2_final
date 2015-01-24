#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include "Edge.h"

#include <QGraphicsView>

#include <vector>

class EdgeView : public QGraphicsView
{
    Q_OBJECT

private:

    std::vector<Edge*> m_edges;

public:

    explicit EdgeView(QWidget *parent = 0);
    ~EdgeView();

    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

    int edgeCount() const { return (int)m_edges.size(); }
    Edge* edge(int i) { return m_edges[i]; }
    void addEdge(Edge* edge);

private:

    void drawEdge(QPainter& painter, const Edge* edge, qreal width);

private slots:

    void onEdgePointsChanged(Edge* e);

signals:

    void mouseClicked(const QPoint& pos);

};

#endif // EDGEVIEW_H
