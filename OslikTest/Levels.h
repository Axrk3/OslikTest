#pragma once
#include "GameObjects.h"

class Level {
private:
	String* map;
	//Массивы с предметами и НПС
public:
	Level() {};
	void changeLevel(String map[]) {
		this->map = map;
	}
	String* getMap() {
		return map;
	}
};


static String map1[34] = {
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                       BB            B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"B                                BB   B",
	"B                                     B",
	"B                                     B",
	"B                                     B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};
