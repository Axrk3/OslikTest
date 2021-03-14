#pragma once
#include "GameObjects.h"

class Level {
private:
	String* map;
	//������� � ���������� � ���
public:
	Level() {
		dirt.loadFromFile("dirt.jpg");
	};
	void changeLevel(String map[]) {
		this->map = map;
	}
	String* getMap() {
		return map;
	}
	Texture dirt;
};

static String map1[34] = {
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                             BB                                               B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B                                                                              B",
	"B  BB                                                                          B",
	"B                                                                              B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};
