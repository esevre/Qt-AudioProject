//
// Created by Erik Sevre on 5/10/18.
//

#include <QtGui/QPainter>

#include "WidgetPairGrid.hpp"



WidgetPairGrid::WidgetPairGrid(QWidget *parent)
        : QWidget(parent)
{
    grid_layout = new QGridLayout(this);

}

void WidgetPairGrid::addPair(
        WidgetPairGrid::WidgetPointer left_item,
        WidgetPairGrid::WidgetPointer right_item)
{
    pair_vector.push_back(WidgetPair(left_item, right_item));
    data_has_changed = true;
}

void WidgetPairGrid::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    setup_grid_layout();

}

void WidgetPairGrid::setup_grid_layout() {
    if (data_has_changed) {
        delete grid_layout; // delete old

        grid_layout = new QGridLayout(this);
        grid_layout->setVerticalSpacing(vertical_spacing);
        grid_layout->setHorizontalSpacing(horizontal_spacing);

        for (int i = 0; i < pair_vector.size(); ++i) {
            grid_layout->addWidget(pair_vector[i].first, i, 0);
            grid_layout->addWidget(pair_vector[i].second, i, 1);
        }
    }
    data_has_changed = false;
}












