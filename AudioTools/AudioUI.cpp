//
// Created by Erik Sevre on 5/10/18.
//

#include "AudioUI.hpp"

AudioUI::AudioUI(QWidget *parent) : QWidget(parent)
{
    main_layout = new QVBoxLayout(this);
    deviceSettingsTopGrid = new WidgetPairGrid;
    encodingModeBox = new QGroupBox;
    encodingGridLayout = new QGridLayout(encodingModeBox);
    controlButtonLayout = new QHBoxLayout;
    levelsLayout = new QGridLayout;
    sliderSpacer = new QSpacerItem(40, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

    device_label = new QLabel;
    device_combo_box = new QComboBox;
    codec_label = new QLabel;
    codec_combo_box = new QComboBox;
    container_label = new QLabel;
    container_combo_box = new QComboBox;
    sample_rate_label = new QLabel;
    sample_rate_combo_box = new QComboBox;
    channels_label = new QLabel;
    channels_combo_box = new QComboBox;

    constantQualityButton = new QRadioButton;
    qualitySlider = new QSlider;
    constantBitrateButton = new QRadioButton;
    bitrateComboBox = new QComboBox;

    outputButton = new QPushButton;
    recordButton = new QPushButton;
    pauseButton = new QPushButton;

    levelLabel = new QLabel;
    audioLevel = new AudioLevel;

    setup_ui();
    populate_widgets();
}


void AudioUI::setup_ui()
{
    deviceSettingsTopGrid->addPair(device_label, device_combo_box);
    deviceSettingsTopGrid->addPair(codec_label, codec_combo_box);
    deviceSettingsTopGrid->addPair(container_label, container_combo_box);
    deviceSettingsTopGrid->addPair(sample_rate_label, sample_rate_combo_box);
    deviceSettingsTopGrid->addPair(channels_label, channels_combo_box);

    main_layout->addWidget(deviceSettingsTopGrid);

    encodingGridLayout->addWidget(constantQualityButton, 0, 0, 1, 2);
    encodingGridLayout->addItem(sliderSpacer, 1, 0, 1, 1);
    encodingGridLayout->addWidget(qualitySlider, 1, 1, 1, 1);
    encodingGridLayout->addWidget(constantBitrateButton, 2, 0, 1, 2);
    encodingGridLayout->addWidget(bitrateComboBox, 3, 1, 1, 1);

    main_layout->addWidget(encodingModeBox);

    controlButtonLayout->addWidget(outputButton);
    controlButtonLayout->addWidget(recordButton);
    controlButtonLayout->addWidget(pauseButton);

    main_layout->addLayout(controlButtonLayout);

    levelsLayout->addWidget(levelLabel, 0, 0, 1, 1);
    levelsLayout->addWidget(audioLevel, 0, 1, 1, 2);

    main_layout->addLayout(levelsLayout);

}

void AudioUI::populate_widgets() {

    device_label->setText(QLabel::tr("Device:"));
    device_combo_box->addItem(QComboBox::tr("Default"));
    codec_label->setText(QLabel::tr("Codec:"));
    codec_combo_box->addItem(QComboBox::tr("Default"));
    container_label->setText(QLabel::tr("Container:"));
    container_combo_box->addItem(QComboBox::tr("Default"));
    sample_rate_label->setText(QLabel::tr("Sample Rate:"));
    sample_rate_combo_box->addItem(QComboBox::tr("Default"));
    channels_label->setText(QLabel::tr("Channels:"));
    channels_combo_box->addItem(QComboBox::tr("Default"));

    encodingModeBox->setTitle(QGroupBox::tr("Encoding Mode"));
    constantQualityButton->setText(QRadioButton::tr("Constant Quality:"));
    qualitySlider->setOrientation(Qt::Horizontal);
    constantBitrateButton->setText(QRadioButton::tr("Constant Bitrate"));
    bitrateComboBox->addItem(QComboBox::tr("Default"));

    outputButton->setText(QPushButton::tr("Output"));
    recordButton->setText(QPushButton::tr("Record"));
    pauseButton->setText(QPushButton::tr( "Pause "));

    levelLabel->setText(QLabel::tr("Level:"));
    audioLevel->setLevel(0.5);
}






