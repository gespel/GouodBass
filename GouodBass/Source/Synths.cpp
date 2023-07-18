//
// Created by sten on 27.10.22.
//

#include "Synths.h"

Synth::Synth(double freq, double sampleRate) {
    this->freq = freq;
    this->sampleRate = sampleRate;
}

SineSynth::SineSynth(double freq, double sampleRate) : Synth(freq, sampleRate) {
    this->freq = freq;
    this->sampleRate = sampleRate;
}
double SineSynth::getSample() {
    this->phase += (this->freq / this->sampleRate) * 2.0 * 3.14159265;
    return sin(this->phase);
}
void SineSynth::setFrequency(double freq) {
    this->freq = freq;
}


SquareSynth::SquareSynth(double freq, double sampleRate) : Synth(freq, sampleRate) {
    this->freq = freq;
    this->sampleRate = sampleRate;
}
double SquareSynth::getSample() {
    this->phase += (this->freq / this->sampleRate) * 2.0 * 3.14159265;
    if(sin(this->phase) > 0) {
        return 0.5;
    }
    else if (sin(this->phase) < 0) {
        return -0.5;
    }
    return 0;
}
void SquareSynth::setFrequency(double freq) {
    this->freq = freq;
}

SawtoothSynth::SawtoothSynth(double freq, double sampleRate) : Synth(freq, sampleRate) {
    this->freq = freq;
    this->sampleRate = sampleRate;
}
double SawtoothSynth::getSample() {
    sample += this->freq/this->sampleRate;
    if(sample > 1) {
        sample = -1;
    }
    return sample;
}
void SawtoothSynth::setFrequency(double freq) {
    this->freq = freq;
}

WavetableSynth::WavetableSynth(double freq, double sampleRate, int wtSize) : Synth(freq, sampleRate) {
    this->freq = freq;
    this->sampleRate = sampleRate;
    this->tableSize = wtSize;
}
double WavetableSynth::getSample() {
    phaseIncrement = freq / sampleRate * tableSize;
    phase += phaseIncrement;
    return wavetable[static_cast<int>(phase) % tableSize];
}
void WavetableSynth::setWavetable(std::vector<double> wavetable) {
    this->wavetable = wavetable;
}
void WavetableSynth::generateRandomWavetable() {
    this->wavetable.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    for(int i = 0; i < this->tableSize; i++) {
        this->wavetable.push_back(dis(gen));
    }
}
void WavetableSynth::setFrequency(double freq) {
    this->freq = freq;
}
