#pragma once

const int SizeY = 21;
const int SizeX = 10;
const int maxShipLength = 5;

const int playerMaxCAR = 1;
const int playerMaxBAT = 2;
const int playerMaxCRU = 3;
const int playerMaxDES = 4;

const int typesOfShips = 4;

const int baseX = 10; // 0-9
const int baseY = 10; // a-z


enum Bool {
	False = 0,
	True = 1
};

enum PlayerId {
	A = 0,
	B = 1
};

enum ShipType {
	CAR = 5, //The type automatically carries ship length
	BAT = 4,
	CRU = 3,
	DES = 2
};

enum PartState {
	NONE = 0,
	ONLINE = 1,
	OFFLINE = 2
};

enum Compass {
	N = 0,		//	  N	
	E = 1,		//	W   E
	S = 2,		//    S
	W = 3
};

enum Field {
	EMPTY = ' ',
	SHIP = '+',
	ENGINE = '%',
	CANNON = '!',
	RADAR = '@',
	DESTROYED = 'X',
	REEF = '#',
};