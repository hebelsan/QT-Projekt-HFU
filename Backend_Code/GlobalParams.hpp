#ifndef GlobalParams_HPP
#define GlobalParams_HPP

#include <string>
#include "State.hpp"
#include "PipeControl.hpp"

class State;

class GlobalParams
{
private:
	PipeControl* pout;
	std::string currentPlayFile;
	std::string subDir;
	std::vector<std::string>* dirContent;
	int seconds;
	int oldSeconds;
	FileManager fileManager;
	int currentSelect;
	unsigned int volume;
	State* oldState;
	GstPlayer player = GstPlayer(0, NULL);
	std::string mountpoint;
	
public:
	GlobalParams();
	void increaseVolume();
	void decreaseVolume();
	unsigned int getVolume();
	void setOldState(State*);
	State* getOldState();
	void setMountpoint(std::string);
	std::string getMountpoint();
	bool nextSelect();
	bool previousSelect();
	void loadSelection();
	void togglePlayer();
	std::string getCurrentDirectory();
	static void SecondsHandler(int, int*);
	static void EofHandler(GlobalParams*);
	void loadNextSong();
	void loadPreviousSong();
	void seek(int);
};

#endif
