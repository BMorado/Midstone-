#pragma once



//created enum for easy tower identification and switch use 
enum TowerType {

	none = 0,
	circle = 1,
	triangle = 2,
	square = 3,
	hexagon = 4,
	octogon = 5,
	star = 6,
	diamond = 7,
	circlenone = 10,
	circlecircle = 11,
	circletriangle = 12,
	circlesquare = 13,
	circlehexagon = 14,
	circleoctogon = 15,
	circlestar = 16,
	circlediamond = 17,
	trianglenone = 20,
	trianglecircle = 21,
	triangletriangle = 22,
	trianglesquare = 23,
	trianglehexagon = 24,
	triangleoctogon = 25,
	trianglestar = 26,
	trianglediamond = 27,
	squarenone = 30,
	squarecircle = 31,
	squaretriangle = 32,
	squaresquare = 33,
	squarehexagon = 34,
	squareoctogon = 35,
	squarestar = 36,
	squarediamond = 37,
	hexagonnone = 40,
	hexagoncircle = 41,
	hexagontriangle = 42,
	hexagonsquare = 43,
	hexagonhexagon = 44,
	hexagonoctogon = 45,
	hexagonstar = 46,
	hexagondiamond = 47,
	octogonnone = 50,
	octogoncircle = 51,
	octogontriangle = 52,
	octogonsquare = 53,
	octogonhexagon = 54,
	octogonoctogon = 55,
	octogonstar = 56,
	octogondiamond = 57,
	starnone = 60,
	starcircle = 61,
	startriangle = 62,
	starsquare = 63,
	starhexagon = 64,
	staroctogon = 65,
	starstar = 66,
	stardiamond = 67,
	diamondnone = 70,
	diamondcircle = 71,
	diamondtriangle = 72,
	diamondsquare = 73,
	diamondhexagon = 74,
	diamondoctogon = 75,
	diamondstar = 76,
	diamonddiamond = 77,
	
};


// assigns each word a int value for easier readability 
enum CellState {
	OPEN_SPACE = 0,
	ENEMY_PATH = -1,
	SPAWN_POINT = -2,
	TOWER = 3,
	END_POINT = -4
};
