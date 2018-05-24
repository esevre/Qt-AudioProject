//
// Created by Erik Sevre on 5/14/18.
//

#pragma once

#include <QAudioProbe>
#include <QVector>
#include <vector>
#include <algorithm>


qreal getPeakValue(const QAudioFormat& format);
//QVector<qreal> getBufferLevels(const QAudioBuffer& buffer);
std::vector<qreal> getBufferLevels(const QAudioBuffer& buffer);

//template <class T>
//QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);
template <class T>
std::vector<qreal> getBufferLevels(const T *buffer, int frames, int channels);



// This function returns the maximum possible sample value for a given audio format
qreal getPeakValue(const QAudioFormat& format)
{
    // Note: Only the most common sample formats are supported
    if (!format.isValid())
        return qreal(0);

    if (format.codec() != "audio/pcm")
        return qreal(0);

    switch (format.sampleType()) {
        case QAudioFormat::Unknown:
            break;
        case QAudioFormat::Float:
            if (format.sampleSize() != 32) // other sample formats are not supported
                return qreal(0);
            return qreal(1.00003);
        case QAudioFormat::SignedInt:
            if (format.sampleSize() == 32)
                return qreal(INT_MAX);
            if (format.sampleSize() == 16)
                return qreal(SHRT_MAX);
            if (format.sampleSize() == 8)
                return qreal(CHAR_MAX);
            break;
        case QAudioFormat::UnSignedInt:
            if (format.sampleSize() == 32)
                return qreal(UINT_MAX);
            if (format.sampleSize() == 16)
                return qreal(USHRT_MAX);
            if (format.sampleSize() == 8)
                return qreal(UCHAR_MAX);
            break;
    }

    return qreal(0);
}

// returns the audio level for each channel
std::vector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
    std::vector<qreal> values;

    if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;

    if (buffer.format().codec() != "audio/pcm")
        return values;

    int channelCount = buffer.format().channelCount();
    values.resize(static_cast<size_t>(channelCount));
    std::fill(values.begin(), values.end(), 0);
    //values.fill(0, channelCount);    // fill vector with zero values

    qreal peak_value = getPeakValue(buffer.format());
    if (qFuzzyCompare(peak_value, qreal(0)))
        return values;

    switch (buffer.format().sampleType()) {
        case QAudioFormat::Unknown:
        case QAudioFormat::UnSignedInt:
            if (buffer.format().sampleSize() == 32)
                values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
            if (buffer.format().sampleSize() == 16)
                values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
            if (buffer.format().sampleSize() == 8)
                values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
            for (double &value : values) {
                value = qAbs(value - peak_value / 2) / (peak_value / 2);
            }
            break;
        case QAudioFormat::Float:
            if (buffer.format().sampleSize() == 32) {
                values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
                for (double &value : values){
                    value /= peak_value;
                }
            }
            break;
        case QAudioFormat::SignedInt:
            if (buffer.format().sampleSize() == 32)
                values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
            if (buffer.format().sampleSize() == 16)
                values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
            if (buffer.format().sampleSize() == 8)
                values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
            for (double &value : values){
                value /= peak_value;
            }
            break;
    }

    return values;
}

template <class T>
std::vector<qreal> getBufferLevels(const T *buffer, int frames, int channels)
{
    std::vector<qreal> max_values(channels);
    std::fill(max_values.begin(), max_values.end(), 0);
    //max_values.fill(0, channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                //max_values.replace(j, value);
                max_values[j] = value;
        }
    }

    return max_values;
}

