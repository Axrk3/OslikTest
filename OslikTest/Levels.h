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
	};
	void changeLevel(String map[]) {
		this->map = map;
	}
	String* getMap() {
		return map;
	}
	Texture dirt;
	Texture grass;
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
	"D               GD       G                                                     D",
	"D              GD        D                                                     D",
	"DGGGGGGGGGGGGGGDDGGGGGGGGDGGGGGGGGGGGGGG                                       D",
	"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDG                                      D",
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
	"D    GG           GG                                                           D",
	"D                                                                              D",
	"D                                                                              D",
	"DGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGD",
	"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD"
};
