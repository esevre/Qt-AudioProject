//
// Created by Erik Sevre on 5/10/18.
//

#ifndef AUDIOPROJECT_AUDIOUI_HPP
#define AUDIOPROJECT_AUDIOUI_HPP

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>

#include "WidgetPairGrid.hpp"

class AudioUI : public QWidget {
public:
    explicit AudioUI(QWidget *parent=nullptr);

    void setup_ui();
    void populate_widgets();

private:
    WidgetPairGrid *deviceSettingsTopGrid;
    QVBoxLayout *main_layout;

public:
    QLabel *device_label;
    QComboBox *device_combo_box;
    QLabel *codec_label;
    QComboBox *codec_combo_box;
    QLabel *container_label;
    QComboBox *container_combo_box;
    QLabel *sample_rate_label;
    QComboBox *sample_rate_combo_box;
    QLabel *channels_label;
    QComboBox *channels_combo_box;


};


#endif //AUDIOPROJECT_AUDIOUI_HPP