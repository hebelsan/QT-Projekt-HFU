#ifndef CarCamView_HPP
#define CarCamView_HPP

#include <string>
#include "State.hpp"
#include "GlobalParams.hpp"
#include "InfoView.hpp"
#include "StartView.hpp"

class CarCamView : public State
{
private:
	CarCamView();
	PipeControl* pout;
	
public:
	static CarCamView* getInstance();
	virtual State* sendEvent(EventEnum, GlobalParams&);
	virtual std::string getName();
	virtual int getId();
};

#endif