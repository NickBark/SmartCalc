#ifndef GRAPH_H
#define GRAPH_H

#include "dependencies.hpp"

class Graph : public QFrame {
    Q_OBJECT

   public:
    explicit Graph(QFrame* parent = nullptr);

   protected:
    void paintEvent(QPaintEvent* event);
    void drawImage(QPainter* pp);

   signals:
};

#endif  // GRAPH_H
