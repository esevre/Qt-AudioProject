#include <iostream>

#include <QtWidgets/QApplication>

#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>

#include "AudioTools/AudioUI.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AudioUI myUI;

    myUI.show();


    return app.exec();
}