#include <iostream>

#include <QtWidgets/QApplication>

#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>

#include "AudioTools/WidgetPairGrid.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WidgetPairGrid pairGrid;

    for (int i = 0; i < 10; ++i) {
        QString left_string = QString("Left: ") + QString::number(i, 10);
        QString right_string = QString("Right: ") + QString::number(i, 10);
        pairGrid.addPair(
                new QLabel(left_string),
                new QLabel(right_string)
        );
    }

    pairGrid.show();

    return app.exec();
}