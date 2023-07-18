/*
Created by Sten (Gespel) Heimbrodt

Inspired by Hallvard Jensen with some modifications
*/

#pragma once

#include <JuceHeader.h>

class SeFFT
{
private:
    static constexpr unsigned int fftOrder{ 12 };
    static constexpr unsigned int fftSize = 1 << fftOrder;
    
    juce::dsp::FFT forwardFFT;
    int fifoIndex = 0;
    std::array<float, fftSize> fifo;
    std::array<float, fftSize * 2> fftData;

    const double sampleRate;

public:
    SeFFT(const double sampleRate);
    std::array<float, fftSize * 2> getFFTData() const;
    int getFFTSize() const;
    double calcFundamentalFrequency() const;
    std::pair<double, double> calcFundamentalFrequencyWithAmplitude() const;
    void pushNextSampleIntoFifo(float sample);
    bool nextFFTBlockReady = false;
    
};

