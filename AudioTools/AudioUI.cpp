//
// Created by Erik Sevre on 5/10/18.
//

#include "AudioUI.hpp"

AudioUI::AudioUI(QWidget *parent) : QWidget(parent)
{
    deviceSettingsTopGrid = new WidgetPairGrid;
    main_layout = new QVBoxLayout(this);
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

}






