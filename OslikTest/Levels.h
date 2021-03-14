#pragma once
#include "GameObjects.h"

class Level {
private:
	String* map;
	//Массивы с предметами и НПС
public:
	Level() {
		dirt.loadFromFile("dirt.png");
		grass.loadFromFile("grass.png");
		chestLeft.loadFromFile("chestLeft.png");
		chestRight.loadFromFile("chestRight.png");
	};
	void changeLevel(String map[]) {
		this->map = map;
	}
	String* getMap() {
		return map;
	}
	void changeBlock(int x, int y) {
		map[x][y] = ' ';
	}
	Texture dirt;
	Texture grass;
	Texture chestLeft;
	Texture chestRight;
};

static String map1[34] = {
	"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
	"D                                                                              D",
	"D                                                                              D",
	"D                                                                              D",
	"D                                                                              D",
	"D                                                                              D",
	"D                                                                              D",
	"D                                                                              D",
	"D                  G                                                           D",
	"D                 GD                                                           D",
	"D                GD                                                            D",
	"D               GD       G       CT                                            D",
	"D              GD        D                                                     D",
	"DGGGGGGGGGGGGGGDDGGGGGGGGDGGGGGGGGGGGGGG                                       D",
	"DDDDDDDDDDDDDDD  DDDDDDDD DDDDDDDDDDDDDDG                                      D",
	"D                                       DG                                     D",
	"D                                        DG                                    D",
	"D                                         DG                                   D",
	"D                                          DG                                  D",
	"D                                           DG                                 D",
	"D                                            DG                                D",
	"D                                             DG                               D",
	"D                                              DG                              D",
	"D                                               DG                             D",
	"D                                                DG                            D",
	"D                              G                  DG                           D",
	"D                             DD                   DG                          D",
	"D                                                   DG                         D",
	"D                                                    DG                        D",
	"D    GG           GG                                  DG                       D",
	"D                                                                              D",
	"D                                                                              D",
	"D                                                                              D",
	"DGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGD"
};
