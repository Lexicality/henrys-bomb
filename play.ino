long AAutoCode1;
long AAutoCode2;
long AAutoCode3;
long AAutoCode4;
long AAutoCode5;
long AAutoCode6;
long AAutoCode7;
long AAutoCode8;
long AAutoCode9;
long DAutoCode1;
long DAutoCode2;
long DAutoCode3;
long DAutoCode4;
long DAutoCode5;
long DAutoCode6;
long DAutoCode7;
long DAutoCode8;
long DAutoCode9;

void play_setup()
{
	randomSeed(analogRead(0)); //Get floating data for random number generator from unused analog pin
	AAutoCode1 = random(10000000, 99999999);
	AAutoCode2 = random(10000000, 99999999);
	AAutoCode3 = random(10000000, 99999999);
	AAutoCode4 = random(10000000, 99999999);
	AAutoCode5 = random(10000000, 99999999);
	AAutoCode6 = random(10000000, 99999999);
	AAutoCode7 = random(10000000, 99999999);
	AAutoCode8 = random(10000000, 99999999);
	AAutoCode9 = random(10000000, 99999999);
	DAutoCode1 = random(10000000, 99999999);
	DAutoCode2 = random(10000000, 99999999);
	DAutoCode3 = random(10000000, 99999999);
	DAutoCode4 = random(10000000, 99999999);
	DAutoCode5 = random(10000000, 99999999);
	DAutoCode6 = random(10000000, 99999999);
	DAutoCode7 = random(10000000, 99999999);
	DAutoCode8 = random(10000000, 99999999);
	DAutoCode9 = random(10000000, 99999999);

	lcd.print("world, hello! test");

}

void play_loop()
{

}
