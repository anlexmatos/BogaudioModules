
#include "Switch44.hpp"

struct Switch44Widget : SwitchMatrixModuleWidget {
	static constexpr int hp = 10;

	Switch44Widget(Switch44* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SvgPanel *panel = new SvgPanel();
			panel->box.size = box.size;
			panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Switch44.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(0, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto mix11ParamPosition = Vec(17.7, 59.2);
		auto mix21ParamPosition = Vec(17.7, 115.7);
		auto mix31ParamPosition = Vec(17.7, 171.7);
		auto mix41ParamPosition = Vec(17.7, 227.7);
		auto mix12ParamPosition = Vec(49.7, 59.2);
		auto mix22ParamPosition = Vec(49.7, 115.7);
		auto mix32ParamPosition = Vec(49.7, 171.7);
		auto mix42ParamPosition = Vec(49.7, 227.7);
		auto mix13ParamPosition = Vec(81.7, 59.2);
		auto mix23ParamPosition = Vec(81.7, 115.7);
		auto mix33ParamPosition = Vec(81.7, 171.7);
		auto mix43ParamPosition = Vec(81.7, 227.7);
		auto mix14ParamPosition = Vec(113.7, 59.2);
		auto mix24ParamPosition = Vec(113.7, 115.7);
		auto mix34ParamPosition = Vec(113.7, 171.7);
		auto mix44ParamPosition = Vec(113.7, 227.7);

		auto in1InputPosition = Vec(15.0, 274.0);
		auto in2InputPosition = Vec(47.0, 274.0);
		auto in3InputPosition = Vec(79.0, 274.0);
		auto in4InputPosition = Vec(111.0, 274.0);

		auto out1OutputPosition = Vec(15.0, 318.0);
		auto out2OutputPosition = Vec(47.0, 318.0);
		auto out3OutputPosition = Vec(79.0, 318.0);
		auto out4OutputPosition = Vec(111.0, 318.0);
		// end generated by svg_widgets.rb

		createSwitch<InvertingIndicatorButton18>(mix11ParamPosition, module, Switch44::MIX11_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix21ParamPosition, module, Switch44::MIX21_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix31ParamPosition, module, Switch44::MIX31_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix41ParamPosition, module, Switch44::MIX41_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix12ParamPosition, module, Switch44::MIX12_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix22ParamPosition, module, Switch44::MIX22_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix32ParamPosition, module, Switch44::MIX32_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix42ParamPosition, module, Switch44::MIX42_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix13ParamPosition, module, Switch44::MIX13_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix23ParamPosition, module, Switch44::MIX23_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix33ParamPosition, module, Switch44::MIX33_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix43ParamPosition, module, Switch44::MIX43_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix14ParamPosition, module, Switch44::MIX14_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix24ParamPosition, module, Switch44::MIX24_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix34ParamPosition, module, Switch44::MIX34_PARAM);
		createSwitch<InvertingIndicatorButton18>(mix44ParamPosition, module, Switch44::MIX44_PARAM);

		addInput(createInput<Port24>(in1InputPosition, module, Switch44::IN1_INPUT));
		addInput(createInput<Port24>(in2InputPosition, module, Switch44::IN2_INPUT));
		addInput(createInput<Port24>(in3InputPosition, module, Switch44::IN3_INPUT));
		addInput(createInput<Port24>(in4InputPosition, module, Switch44::IN4_INPUT));

		addOutput(createOutput<Port24>(out1OutputPosition, module, Switch44::OUT1_OUTPUT));
		addOutput(createOutput<Port24>(out2OutputPosition, module, Switch44::OUT2_OUTPUT));
		addOutput(createOutput<Port24>(out3OutputPosition, module, Switch44::OUT3_OUTPUT));
		addOutput(createOutput<Port24>(out4OutputPosition, module, Switch44::OUT4_OUTPUT));
	}
};

Model* modelSwitch44 = createModel<Switch44, Switch44Widget>("Bogaudio-Switch44", "SWITCH44", "4x4 matrix mixer", "Mixer", "Polyphonic");
