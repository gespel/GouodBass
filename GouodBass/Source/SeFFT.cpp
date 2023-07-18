#include "SeFFT.h"

SeFFT::SeFFT(const double sampleRate) : forwardFFT{ fftOrder }, sampleRate{ sampleRate } 
{
}

std::array<float, SeFFT::fftSize * 2> SeFFT::getFFTData() const
{
    return fftData;
}


int SeFFT::getFFTSize() const
{
    return fftSize;
}

void SeFFT::pushNextSampleIntoFifo(float sample)
{
    if (fifoIndex == fftSize)
    {
        if (!nextFFTBlockReady)
        {
            std::fill(fftData.begin(), fftData.end(), 0.0f);
            std::copy(fifo.begin(), fifo.end(), fftData.begin());
            nextFFTBlockReady = true;
            forwardFFT.performFrequencyOnlyForwardTransform(fftData.data());
        }
        fifoIndex = 0;
    }
    fifo[fifoIndex++] = sample;
}

std::pair<double, double> SeFFT::calcFundamentalFrequencyWithAmplitude() const
{
    double max{ 0 };
    unsigned int targetBin{ 0 };
    auto data = getFFTData();

    for (unsigned int i = 0; i < getFFTSize(); ++i)
    {
        if (max < data[i])
        {
            max = data[i];
            targetBin = i;
        }
    }

    return std::make_pair((double)targetBin * sampleRate / (fftSize * 2), (double)(data[targetBin] / fftSize));
}

double SeFFT::calcFundamentalFrequency() const
{
    double max{ 0 };
    unsigned int targetBin{ 0 };
    auto data = getFFTData();

    for (unsigned int i = 0; i < getFFTSize(); ++i)
    {
        if (max < data[i])
        {
            max = data[i];
            targetBin = i;
        }
    }

    return (double)targetBin * sampleRate / (fftSize * 2);
}

