#pragma once
namespace Bengine {

	class FPSLimiter {
		
	public:
		FPSLimiter();
		void init(float maxFPS);

		void begin();

		void setMaxFPS(float maxFPS);

		// end will return the fps
		float end();
	private:

		void calculateFPS();

		float _frameTime;
		float _fps;
		float _maxFPS;
		unsigned int _startTicks;
	};




}