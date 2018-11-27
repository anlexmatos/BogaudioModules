
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

#include "bogaudio.hpp"
#include "dsp/analyzer.hpp"

using namespace bogaudio::dsp;

namespace bogaudio {

struct ChannelAnalyzer {
	SpectrumAnalyzer _analyzer;
	int _binsN;
	float* _bins;
	AveragingBuffer<float>* _averagedBins;
	const int _stepBufN;
	float* _stepBuf;
	int _stepBufI = 0;
	const int _workerBufN;
	float* _workerBuf;
	int _workerBufWriteI = 0;
	int _workerBufReadI = 0;
	bool _workerStop = false;
	std::mutex _workerMutex;
	std::condition_variable _workerCV;
	std::thread _worker;

	ChannelAnalyzer(
		SpectrumAnalyzer::Size size,
		SpectrumAnalyzer::Overlap overlap,
		SpectrumAnalyzer::WindowType windowType,
		float sampleRate,
		int averageN,
		int binSize
	)
	: _analyzer(size, overlap, windowType, sampleRate, false)
	, _binsN(size / binSize)
	, _bins(averageN == 1 ? new float[_binsN] {} : NULL)
	, _averagedBins(averageN == 1 ? NULL : new AveragingBuffer<float>(_binsN, averageN))
	, _stepBufN(size / overlap)
	, _stepBuf(new float[_stepBufN] {})
	, _workerBufN(size)
	, _workerBuf(new float[_workerBufN] {})
	, _worker(&ChannelAnalyzer::work, this)
	{
		assert(averageN >= 1);
		assert(binSize >= 1);
	}
	virtual ~ChannelAnalyzer();

	const float* getBins();
	float getPeak();
	void step(float sample);
	void work();
};

struct AnalyzerCore {
	enum Quality {
		QUALITY_ULTRA,
		QUALITY_HIGH,
		QUALITY_GOOD
	};

	enum Window {
		WINDOW_NONE,
		WINDOW_HAMMING,
		WINDOW_KAISER
	};

    int _nChannels;
	ChannelAnalyzer** _channels;
	int _averageN = 1;
	Quality _quality = QUALITY_GOOD;
	Window _window = WINDOW_KAISER;
	const SpectrumAnalyzer::Overlap _overlap = SpectrumAnalyzer::OVERLAP_2;
	const int _binAverageN = 2;
	std::mutex _channelsMutex;

	AnalyzerCore(int nChannels)
    : _nChannels(nChannels)
    , _channels(new ChannelAnalyzer*[_nChannels] {})
    {}
	virtual ~AnalyzerCore() {
		resetChannels();
        delete[] _channels;
	}

    void setParams(int averageN, Quality quality, Window window);
	void resetChannels();
	SpectrumAnalyzer::Size size();
	SpectrumAnalyzer::WindowType window();
	void stepChannel(int channelIndex, Input& input);
};

struct AnalyzerBase : Module {
    float _rangeMinHz = 0.0;
	float _rangeMaxHz = 0.0;
    AnalyzerCore _core;

    AnalyzerBase(int nChannels, int np, int ni, int no, int nl)
    : Module(np, ni, no, nl)
    , _core(nChannels)
    {}
};

struct AnalyzerDisplay : TransparentWidget {
	const int _insetAround = 2;
	const int _insetLeft = _insetAround + 12;
	const int _insetRight = _insetAround + 2;
	const int _insetTop = _insetAround + 13;
	const int _insetBottom = _insetAround + 9;

	const float _displayDB = 80.0;
	const float _positiveDisplayDB = 20.0;

	const float baseXAxisLogFactor = 1 / 3.321; // magic number.

	const NVGcolor _axisColor = nvgRGBA(0xff, 0xff, 0xff, 0x70);
	const NVGcolor _textColor = nvgRGBA(0xff, 0xff, 0xff, 0xc0);
	static constexpr int channelColorsN = 8;
	const NVGcolor _channelColors[channelColorsN] = {
		nvgRGBA(0x00, 0xff, 0x00, 0xd0),
		nvgRGBA(0xff, 0x00, 0xff, 0xd0),
		nvgRGBA(0xff, 0x80, 0x00, 0xd0),
		nvgRGBA(0x00, 0x80, 0xff, 0xd0),

		nvgRGBA(0xff, 0x00, 0x00, 0xd0),
		nvgRGBA(0xff, 0xff, 0x00, 0xd0),
		nvgRGBA(0x00, 0xff, 0xff, 0xd0),
		nvgRGBA(0xff, 0x80, 0x80, 0xd0)
	};

	AnalyzerBase* _module;
	const Vec _size;
	const Vec _graphSize;
	std::shared_ptr<Font> _font;
	float _xAxisLogFactor = baseXAxisLogFactor;

	AnalyzerDisplay(
		AnalyzerBase* module,
		Vec size
	)
	: _module(module)
	, _size(size)
	, _graphSize(_size.x - _insetLeft - _insetRight, _size.y - _insetTop - _insetBottom)
	, _font(Font::load(assetPlugin(plugin, "res/fonts/inconsolata.ttf")))
	{
	}

	void draw(NVGcontext* vg) override;
	void drawBackground(NVGcontext* vg);
	void drawHeader(NVGcontext* vg);
	void drawYAxis(NVGcontext* vg, float strokeWidth);
	void drawXAxis(NVGcontext* vg, float strokeWidth);
	void drawXAxisLine(NVGcontext* vg, float hz);
	void drawGraph(NVGcontext* vg, const float* bins, int binsN, NVGcolor color, float strokeWidth);
	void drawText(NVGcontext* vg, const char* s, float x, float y, float rotation = 0.0, const NVGcolor* color = NULL);
	int binValueToHeight(float value);
};

} // namespace bogaudio