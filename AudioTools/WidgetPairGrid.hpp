//
// Created by Erik Sevre on 5/10/18.
//

#ifndef AUDIOPROJECT_WIDGETPAIRGRID_HPP
#define AUDIOPROJECT_WIDGETPAIRGRID_HPP

#include <tuple>
#include <vector>

#include <QPainter>
#include <QWidget>
#include <QtWidgets/QGridLayout>


class WidgetPairGrid : public QWidget {
    using WidgetPointer = QWidget*;
    using WidgetPair = std::pair<WidgetPointer, WidgetPointer>;
    using PairVector = std::vector<WidgetPair>;
    using LayoutPointer = QGridLayout*;

public:
    explicit WidgetPairGrid(QWidget *parent=0);
    void addPair(WidgetPointer, WidgetPointer);

protected:
    void paintEvent(QPaintEvent *event) override;

    void setup_grid_layout();


private:
    PairVector pair_vector;
    LayoutPointer grid_layout;
    bool data_has_changed = true;

    int vertical_spacing = 5;
    int horizontal_spacing = 10;
};


#endif //AUDIOPROJECT_WIDGETPAIRGRID_HPP