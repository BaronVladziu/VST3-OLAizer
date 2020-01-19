#pragma once

#include <assert.h>
#include <queue>
#include "../JuceLibraryCode/JuceHeader.h"

class OLAizer {
private:
    int _samplingFrequency;
    int _windowLength = 0;
    float _jumpFloat = 0;
    float _diffFloat = 0;
    int _newWindowLength = 0;
    float _newJumpFloat = 0;
    float _newDiffFloat = 0;
    
    int _jump = 0;
    int _diff = 0;
    float* _window;
    std::queue<float> _buffer;
    int _sampleNumber = 0;

    void _updateParameters();

public:
    OLAizer(int samplingFrequency);
    ~OLAizer();
    float olaize(float inputSample);
    void updateWindowLength(float windowLengthMs);
    void updateJump(float jump);
    void updateDiff(float diff);
};
