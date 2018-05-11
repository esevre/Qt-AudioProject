//
// Created by Erik Sevre on 5/10/18.
//

#include <iostream>

#include "AudioUI.hpp"

AudioUI::AudioUI(QWidget *parent) : QWidget(parent)
{
    main_layout = new QVBoxLayout(this);
    deviceSettingsTopGrid = new WidgetPairGrid(this);
    encodingModeBox = new QGroupBox(this);
    encodingGridLayout = new QGridLayout(encodingModeBox);
    controlButtonLayout = new QHBoxLayout;
    levelsLayout = new QGridLayout;
    sliderSpacer = new QSpacerItem(40, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

    device_label = new QLabel(this);
    device_combo_box = new QComboBox(this);
    codec_label = new QLabel(this);
    codec_combo_box = new QComboBox(this);
    container_label = new QLabel(this);
    container_combo_box = new QComboBox(this);
    sample_rate_label = new QLabel(this);
    sample_rate_combo_box = new QComboBox(this);
    channels_label = new QLabel(this);
    channels_combo_box = new QComboBox(this);

    constantQualityButton = new QRadioButton(this);
    qualitySlider = new QSlider(this);
    constantBitrateButton = new QRadioButton(this);
    bitrateComboBox = new QComboBox(this);

    outputButton = new QPushButton(this);
    recordButton = new QPushButton(this);
    pauseButton = new QPushButton(this);

    levelLabel = new QLabel(this);
    audioLevel = new AudioLevel(this);

    setup_ui();
    populate_widgets();
    initial_setup();

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

void AudioUI::populate_widgets()
{

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
    audioLevel->setLevel(0.0);
}


void AudioUI::initial_setup()
{
    selectConstantQuality();

}

void AudioUI::selectConstantQuality() {
    constantQualityButton->setChecked(true);
    qualitySlider->setEnabled(true);
    constantBitrateButton->setChecked(false);
    bitrateComboBox->setEnabled(false);
}

void AudioUI::selectConstantBitrate() {
    constantQualityButton->setChecked(false);
    qualitySlider->setEnabled(false);
    constantBitrateButton->setChecked(true);
    bitrateComboBox->setEnabled(true);

}

