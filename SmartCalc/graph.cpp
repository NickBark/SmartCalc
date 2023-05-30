#include "graph.hpp"

Graph::Graph(QFrame* parent) : QFrame{parent} {}

void Graph::paintEvent(QPaintEvent* event) {
    QPainter p(this);
    drawImage(&p);
}

void Graph::drawImage(QPainter* pp) {
    Point ppp = {10, 30};
    pp->setPen(QColor(255, 0, 0));
    pp->drawRect(width() / 2 - 128, height() / 2 - 128, 256, 256);
    pp->drawLine(ppp.x, ppp.y, ppp.x + 100, ppp.y + 100);
}
