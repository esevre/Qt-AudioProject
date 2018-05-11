//
// Created by Erik Sevre on 5/10/18.
//
//
//  todo: add slots and signals for event handling in the UI
//

#ifndef AUDIOPROJECT_AUDIOUI_HPP
#define AUDIOPROJECT_AUDIOUI_HPP

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QPushButton>


#include "AudioLevel.hpp"
#include "WidgetPairGrid.hpp"


class AudioUI : public QWidget {
public:
    explicit AudioUI(QWidget *parent=nullptr);


protected:
    QVBoxLayout *main_layout;
    WidgetPairGrid *deviceSettingsTopGrid;
    QGridLayout *encodingGridLayout;
    QGroupBox *encodingModeBox;
    QHBoxLayout *controlButtonLayout;
    QGridLayout *levelsLayout;

    QSpacerItem *sliderSpacer;

    void setup_ui();
    void initial_setup();
    void populate_widgets();

private:
    void selectConstantQuality();
    void selectConstantBitrate();


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

    QRadioButton *constantQualityButton;
    QSlider *qualitySlider;
    QRadioButton *constantBitrateButton;
    QComboBox *bitrateComboBox;

    QPushButton *outputButton;
    QPushButton *recordButton;
    QPushButton *pauseButton;

    QLabel *levelLabel;
    AudioLevel *audioLevel;

};


#endif //AUDIOPROJECT_AUDIOUI_HPP