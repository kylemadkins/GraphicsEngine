#pragma once

#include <random>

struct Color {
	float r;
	float g;
	float b;
	float alpha;

	bool operator==(const Color& other) const {
		return r == other.r && g == other.g && b == other.b && alpha == other.alpha;
	}

	static Color random() {
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_real_distribution<float> distrib(0.0f, 1.0f);

		return Color{distrib(gen), distrib(gen), distrib(gen), 1.0f};
	}
};
