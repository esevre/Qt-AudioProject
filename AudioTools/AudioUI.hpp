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

    QHBoxLayout *controlButtonLayout = new QHBoxLayout;
    QGridLayout *levelsLayout = new QGridLayout;


    void setup_ui();
    void initial_setup();
    void populate_widgets();

private:
    void selectConstantQuality();
    void selectConstantBitrate();


public:
    QLabel *device_label = new QLabel;
    QComboBox *device_combo_box = new QComboBox;
    QLabel *codec_label = new QLabel;
    QComboBox *codec_combo_box = new QComboBox;
    QLabel *container_label = new QLabel;
    QComboBox *container_combo_box = new QComboBox;
    QLabel *sample_rate_label = new QLabel;
    QComboBox *sample_rate_combo_box = new QComboBox;
    QLabel *channels_label = new QLabel;
    QComboBox *channels_combo_box = new QComboBox;

    QRadioButton *constantQualityButton = new QRadioButton;
    QSlider *qualitySlider = new QSlider;
    QRadioButton *constantBitrateButton = new QRadioButton;
    QComboBox *bitrateComboBox = new QComboBox;

    QPushButton *outputButton = new QPushButton;
    QPushButton *recordButton = new QPushButton;
    QPushButton *pauseButton = new QPushButton;

    QLabel *levelLabel = new QLabel;
    AudioLevel *audioLevel = new AudioLevel;

    QSpacerItem *sliderSpacer = new QSpacerItem(40, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

};


#endif //AUDIOPROJECT_AUDIOUI_HPP