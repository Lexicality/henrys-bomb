	Long AAutoCode1
	Long AAutoCode2
	Long AAutoCode3
	Long AAutoCode4
	Long AAutoCode5
	Long AAutoCode6
	Long AAutoCode7
	Long AAutoCode8
	Long AAutoCode9
	Long DAutoCode1
	Long DAutoCode2
	Long DAutoCode3
	Long DAutoCode4
	Long DAutoCode5
	Long DAutoCode6
	Long DAutoCode7
	Long DAutoCode8
	Long DAutoCode9

void play_setup() {
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

void play_loop() {

}
