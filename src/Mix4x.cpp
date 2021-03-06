
#include "Mix4x.hpp"

void Mix4x::sampleRateChange() {
	float sr = APP->engine->getSampleRate();
	for (int i = 0; i < 4; ++i) {
		_channels[i]->setSampleRate(sr);
	}
	_returnASL.setParams(sr, MixerChannel::levelSlewTimeMS, MixerChannel::maxDecibels - MixerChannel::minDecibels);
	_returnBSL.setParams(sr, MixerChannel::levelSlewTimeMS, MixerChannel::maxDecibels - MixerChannel::minDecibels);
}

void Mix4x::modulate() {
	for (int i = 0; i < 4; ++i) {
		_channels[i]->modulate();
	}
}

void Mix4x::processAll(const ProcessArgs& args) {
	if (!baseConnected()) {
		outputs[SEND_A_OUTPUT].setVoltage(0.0f);
		outputs[SEND_B_OUTPUT].setVoltage(0.0f);
		return;
	}

	Mix4ExpanderMessage* from = fromBase();
	Mix4ExpanderMessage* to = toBase();
	float sendA = 0.0f;
	float sendB = 0.0f;
	bool sendAActive = outputs[SEND_A_OUTPUT].isConnected();
	bool sendBActive = outputs[SEND_B_OUTPUT].isConnected();
	for (int i = 0; i < 4; ++i) {
		if (from->active[i]) {
			_channels[i]->next(from->preFader[i], from->postFader[i], sendAActive, sendBActive);
			to->postEQ[i] = _channels[i]->postEQ;
			sendA += _channels[i]->sendA;
			sendB += _channels[i]->sendB;
		}
		else {
			to->postEQ[i] = from->preFader[i];
		}
	}
	outputs[SEND_A_OUTPUT].setVoltage(_saturatorA.next(sendA));
	outputs[SEND_B_OUTPUT].setVoltage(_saturatorA.next(sendB));

	bool lAActive = inputs[L_A_INPUT].isConnected();
	bool rAActive = inputs[R_A_INPUT].isConnected();
	if (lAActive || rAActive) {
		float levelA = clamp(params[LEVEL_A_PARAM].getValue(), 0.0f, 1.0f);
		if (inputs[LEVEL_A_INPUT].isConnected()) {
			levelA *= clamp(inputs[LEVEL_A_INPUT].getVoltage() / 10.0f, 0.0f, 1.0f);
		}
		levelA = 1.0f - levelA;
		levelA *= Amplifier::minDecibels;
		_returnAAmp.setLevel(_returnASL.next(levelA));
		if (lAActive) {
			to->returnA[0] = _returnAAmp.next(inputs[L_A_INPUT].getVoltage());
		}
		else {
			to->returnA[0] = 0.0f;
		}
		if (rAActive) {
			to->returnA[1] = _returnAAmp.next(inputs[R_A_INPUT].getVoltage());
		}
		else {
			to->returnA[1] = to->returnA[0];
		}
	}

	bool lBActive = inputs[L_B_INPUT].isConnected();
	bool rBActive = inputs[R_B_INPUT].isConnected();
	if (lBActive || rBActive) {
		float levelB = clamp(params[LEVEL_B_PARAM].getValue(), 0.0f, 1.0f);
		levelB = 1.0f - levelB;
		levelB *= Amplifier::minDecibels;
		_returnBAmp.setLevel(_returnBSL.next(levelB));
		if (lBActive) {
			to->returnB[0] = _returnBAmp.next(inputs[L_B_INPUT].getVoltage());
		}
		else {
			to->returnB[0] = 0.0f;
		}
		if (rBActive) {
			to->returnB[1] = _returnBAmp.next(inputs[R_B_INPUT].getVoltage());
		}
		else {
			to->returnB[1] = to->returnB[0];
		}
	}
}

struct Mix4xWidget : ModuleWidget {
	static constexpr int hp = 15;

	Mix4xWidget(Mix4x* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SvgPanel *panel = new SvgPanel();
			panel->box.size = box.size;
			panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Mix4x.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 365)));

		// generated by svg_widgets.rb
		auto low1ParamPosition = Vec(18.5, 43.0);
		auto mid1ParamPosition = Vec(18.5, 89.0);
		auto high1ParamPosition = Vec(18.5, 135.0);
		auto a1ParamPosition = Vec(18.5, 180.0);
		auto preA1ParamPosition = Vec(30.0, 208.0);
		auto b1ParamPosition = Vec(18.5, 236.0);
		auto preB1ParamPosition = Vec(30.0, 264.0);
		auto low2ParamPosition = Vec(61.5, 43.0);
		auto mid2ParamPosition = Vec(61.5, 89.0);
		auto high2ParamPosition = Vec(61.5, 135.0);
		auto a2ParamPosition = Vec(61.5, 180.0);
		auto preA2ParamPosition = Vec(73.0, 208.0);
		auto b2ParamPosition = Vec(61.5, 236.0);
		auto preB2ParamPosition = Vec(73.0, 264.0);
		auto low3ParamPosition = Vec(104.5, 43.0);
		auto mid3ParamPosition = Vec(104.5, 89.0);
		auto high3ParamPosition = Vec(104.5, 135.0);
		auto a3ParamPosition = Vec(104.5, 180.0);
		auto preA3ParamPosition = Vec(116.0, 208.0);
		auto b3ParamPosition = Vec(104.5, 236.0);
		auto preB3ParamPosition = Vec(116.0, 264.0);
		auto low4ParamPosition = Vec(147.5, 43.0);
		auto mid4ParamPosition = Vec(147.5, 89.0);
		auto high4ParamPosition = Vec(147.5, 135.0);
		auto a4ParamPosition = Vec(147.5, 180.0);
		auto preA4ParamPosition = Vec(159.0, 208.0);
		auto b4ParamPosition = Vec(147.5, 236.0);
		auto preB4ParamPosition = Vec(159.0, 264.0);
		auto levelAParamPosition = Vec(190.5, 138.0);
		auto levelBParamPosition = Vec(190.5, 328.0);

		auto a1InputPosition = Vec(14.5, 290.0);
		auto b1InputPosition = Vec(14.5, 325.0);
		auto a2InputPosition = Vec(57.5, 290.0);
		auto b2InputPosition = Vec(57.5, 325.0);
		auto a3InputPosition = Vec(100.5, 290.0);
		auto b3InputPosition = Vec(100.5, 325.0);
		auto a4InputPosition = Vec(143.5, 290.0);
		auto b4InputPosition = Vec(143.5, 325.0);
		auto lAInputPosition = Vec(186.5, 62.0);
		auto rAInputPosition = Vec(186.5, 97.0);
		auto levelAInputPosition = Vec(186.5, 170.0);
		auto lBInputPosition = Vec(186.5, 252.0);
		auto rBInputPosition = Vec(186.5, 287.0);

		auto sendAOutputPosition = Vec(186.5, 24.0);
		auto sendBOutputPosition = Vec(186.5, 214.0);
		// end generated by svg_widgets.rb

		addParam(createParam<Knob16>(low1ParamPosition, module, Mix4x::LOW1_PARAM));
		addParam(createParam<Knob16>(mid1ParamPosition, module, Mix4x::MID1_PARAM));
		addParam(createParam<Knob16>(high1ParamPosition, module, Mix4x::HIGH1_PARAM));
		addParam(createParam<Knob16>(a1ParamPosition, module, Mix4x::A1_PARAM));
		addParam(createParam<IndicatorButtonGreen9>(preA1ParamPosition, module, Mix4x::PRE_A1_PARAM));
		addParam(createParam<Knob16>(b1ParamPosition, module, Mix4x::B1_PARAM));
		addParam(createParam<IndicatorButtonGreen9>(preB1ParamPosition, module, Mix4x::PRE_B1_PARAM));
		addParam(createParam<Knob16>(low2ParamPosition, module, Mix4x::LOW2_PARAM));
		addParam(createParam<Knob16>(mid2ParamPosition, module, Mix4x::MID2_PARAM));
		addParam(createParam<Knob16>(high2ParamPosition, module, Mix4x::HIGH2_PARAM));
		addParam(createParam<Knob16>(a2ParamPosition, module, Mix4x::A2_PARAM));
		addParam(createParam<IndicatorButtonGreen9>(preA2ParamPosition, module, Mix4x::PRE_A2_PARAM));
		addParam(createParam<Knob16>(b2ParamPosition, module, Mix4x::B2_PARAM));
		addParam(createParam<IndicatorButtonGreen9>(preB2ParamPosition, module, Mix4x::PRE_B2_PARAM));
		addParam(createParam<Knob16>(low3ParamPosition, module, Mix4x::LOW3_PARAM));
		addParam(createParam<Knob16>(mid3ParamPosition, module, Mix4x::MID3_PARAM));
		addParam(createParam<Knob16>(high3ParamPosition, module, Mix4x::HIGH3_PARAM));
		addParam(createParam<Knob16>(a3ParamPosition, module, Mix4x::A3_PARAM));
		addParam(createParam<IndicatorButtonGreen9>(preA3ParamPosition, module, Mix4x::PRE_A3_PARAM));
		addParam(createParam<Knob16>(b3ParamPosition, module, Mix4x::B3_PARAM));
		addParam(createParam<IndicatorButtonGreen9>(preB3ParamPosition, module, Mix4x::PRE_B3_PARAM));
		addParam(createParam<Knob16>(low4ParamPosition, module, Mix4x::LOW4_PARAM));
		addParam(createParam<Knob16>(mid4ParamPosition, module, Mix4x::MID4_PARAM));
		addParam(createParam<Knob16>(high4ParamPosition, module, Mix4x::HIGH4_PARAM));
		addParam(createParam<Knob16>(a4ParamPosition, module, Mix4x::A4_PARAM));
		addParam(createParam<IndicatorButtonGreen9>(preA4ParamPosition, module, Mix4x::PRE_A4_PARAM));
		addParam(createParam<Knob16>(b4ParamPosition, module, Mix4x::B4_PARAM));
		addParam(createParam<IndicatorButtonGreen9>(preB4ParamPosition, module, Mix4x::PRE_B4_PARAM));
		addParam(createParam<Knob16>(levelAParamPosition, module, Mix4x::LEVEL_A_PARAM));
		addParam(createParam<Knob16>(levelBParamPosition, module, Mix4x::LEVEL_B_PARAM));

		addInput(createInput<Port24>(a1InputPosition, module, Mix4x::A1_INPUT));
		addInput(createInput<Port24>(b1InputPosition, module, Mix4x::B1_INPUT));
		addInput(createInput<Port24>(a2InputPosition, module, Mix4x::A2_INPUT));
		addInput(createInput<Port24>(b2InputPosition, module, Mix4x::B2_INPUT));
		addInput(createInput<Port24>(a3InputPosition, module, Mix4x::A3_INPUT));
		addInput(createInput<Port24>(b3InputPosition, module, Mix4x::B3_INPUT));
		addInput(createInput<Port24>(a4InputPosition, module, Mix4x::A4_INPUT));
		addInput(createInput<Port24>(b4InputPosition, module, Mix4x::B4_INPUT));
		addInput(createInput<Port24>(lAInputPosition, module, Mix4x::L_A_INPUT));
		addInput(createInput<Port24>(rAInputPosition, module, Mix4x::R_A_INPUT));
		addInput(createInput<Port24>(levelAInputPosition, module, Mix4x::LEVEL_A_INPUT));
		addInput(createInput<Port24>(lBInputPosition, module, Mix4x::L_B_INPUT));
		addInput(createInput<Port24>(rBInputPosition, module, Mix4x::R_B_INPUT));

		addOutput(createOutput<Port24>(sendAOutputPosition, module, Mix4x::SEND_A_OUTPUT));
		addOutput(createOutput<Port24>(sendBOutputPosition, module, Mix4x::SEND_B_OUTPUT));
	}
};

Model* modelMix4x = createModel<Mix4x, Mix4xWidget>("Bogaudio-Mix4x", "MIX4X", "Expander for MIX4, adds EQs and sends", "Mixer", "Expander");
