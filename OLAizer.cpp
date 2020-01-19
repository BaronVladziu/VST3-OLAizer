#include "OLAizer.h"

OLAizer::OLAizer(int samplingFrequency)
    : _samplingFrequency(samplingFrequency)
{
    _window = new float[48000];
    for (int i = 0; i < 48000; i++) {
        _window[i] = 1;
    }
}

OLAizer::~OLAizer() {
    delete[] _window;
}

void OLAizer::_updateParameters() {
    //Update window length
    if (_windowLength != _newWindowLength) {
        //Update
        _windowLength = _newWindowLength;

        //Create window function
        dsp::WindowingFunction<float> windowFunction(
            _windowLength, dsp::WindowingFunction<float>::hamming
        );

        //Clear window buffer
        for (int i = 0; i < _windowLength; i++) {
            _window[i] = 1;
        }

        //Save window to buffer
        windowFunction.multiplyWithWindowingTable(_window, _windowLength);

        //Reset depending parameters
        _jumpFloat = 0;
        _diffFloat = 0;
    }
    
    //Update jump
    if (_jumpFloat != _newJumpFloat) {
        //Update
        _jumpFloat = _newJumpFloat;
        _jump = int(_jumpFloat * _windowLength);
        
        //Reset depending parameters
        _diffFloat = 0;
    }

    //Update diff
    if (_diffFloat != _newDiffFloat) {
        //Update
        _diffFloat = _newDiffFloat;
        _diff = int(_diffFloat * _jump);

        //Reset buffer
        _buffer = std::queue<float>();
        for (int i = 0; i < _diff; i++) {
            _buffer.push(0.0f);
        }
    }
}
    
float OLAizer::olaize(float inputSample) {
    //Sanity check
    assert(inputSample >= -1.0);
    assert(inputSample <= 1.0);

    //Update parameters
    _updateParameters();

    //Get old sample
    float oldSample = 0.0f;
    if (!_buffer.empty()) {
        oldSample = _buffer.front();
    }

    //Make sure, sample number is correct
    if (_windowLength == 0) {
        _sampleNumber = 0;
    }
    else {
        while (_sampleNumber >= _windowLength) {
            _sampleNumber -= _windowLength;
        }
        while (_sampleNumber < 0) {
            _sampleNumber += _windowLength;
        }
    }

    //Find old sample number
    int oldSampleNumber = _sampleNumber - _diff;
    if (_windowLength == 0) {
        oldSampleNumber = 0;
    }
    else if (oldSampleNumber < 0) {
        oldSampleNumber += _windowLength;
    }
    
    //Find output sample value
    float outputSample = (
        inputSample * _window[_sampleNumber] + oldSample * _window[_sampleNumber - _diff]
        ) / (
            _window[_sampleNumber] + _window[_sampleNumber - _diff]
            );

    //Update sample number
    _sampleNumber++;

    //Update buffer
    if (!_buffer.empty()) {
        _buffer.pop();
        _buffer.push(inputSample);
    }

    return outputSample;
}

void OLAizer::updateWindowLength(float windowLengthMs) {
    //Sanity check
    assert(windowLengthMs > 0);

    //Update window length
    _newWindowLength = int(windowLengthMs * _samplingFrequency / 1000);
}

void OLAizer::updateJump(float jump) {
    //Sanity check
    assert(jump >= 0);
    assert(jump <= 1);

    //Update
    _newJumpFloat = jump;
}

void OLAizer::updateDiff(float diff) {
    //Sanity check
    assert(diff >= 0);
    assert(diff <= 1);

    //Update
    _newDiffFloat = diff;
}
