
#include "Bool.hpp"

void Bool::step() {
	bool a = inputs[A_INPUT].value > 1.0f;
	bool b = inputs[B_INPUT].value > 1.0f;
	outputs[AND_OUTPUT].value = a && b ? 5.0f : 0.0f;
	outputs[OR_OUTPUT].value = a || b ? 5.0f : 0.0f;
	outputs[XOR_OUTPUT].value = a ^ b ? 5.0f : 0.0f;

	outputs[NOT_OUTPUT].value = (inputs[NOT_INPUT].active && inputs[NOT_INPUT].value > 1.0f) ? 0.0f : 5.0f;
}

struct BoolWidget : ModuleWidget {
	static constexpr int hp = 3;

	BoolWidget(Bool* module) : ModuleWidget(module) {
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(assetPlugin(plugin, "res/Bool.svg")));
			addChild(panel);
		}

		addChild(Widget::create<ScrewSilver>(Vec(0, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto aInputPosition = Vec(10.5, 23.0);
		auto bInputPosition = Vec(10.5, 53.0);
		auto notInputPosition = Vec(10.5, 221.0);

		auto andOutputPosition = Vec(10.5, 86.0);
		auto orOutputPosition = Vec(10.5, 126.0);
		auto xorOutputPosition = Vec(10.5, 166.0);
		auto notOutputPosition = Vec(10.5, 254.0);
		// end generated by svg_widgets.rb

		addInput(Port::create<Port24>(aInputPosition, Port::INPUT, module, Bool::A_INPUT));
		addInput(Port::create<Port24>(bInputPosition, Port::INPUT, module, Bool::B_INPUT));
		addInput(Port::create<Port24>(notInputPosition, Port::INPUT, module, Bool::NOT_INPUT));

		addOutput(Port::create<Port24>(andOutputPosition, Port::OUTPUT, module, Bool::AND_OUTPUT));
		addOutput(Port::create<Port24>(orOutputPosition, Port::OUTPUT, module, Bool::OR_OUTPUT));
		addOutput(Port::create<Port24>(xorOutputPosition, Port::OUTPUT, module, Bool::XOR_OUTPUT));
		addOutput(Port::create<Port24>(notOutputPosition, Port::OUTPUT, module, Bool::NOT_OUTPUT));
	}
};

Model* modelBool = createModel<Bool, BoolWidget>("Bogaudio-Bool", "Bool",  "boolean logic", LOGIC_TAG);