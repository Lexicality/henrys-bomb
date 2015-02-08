
enum SetupStage {
	GameMode,
	KeyCard,
	CodeMethod,
	ArmCodeCount,
	DisarmCodeCount,
	Strobe,
	Piezos,
	ArmTime,
	Done
};

SetupStage setupStage;
bool hasShownMessage;
bool isAllDone;

void setup_setup()
{
	lcd.setCursor(0, 5);
	lcd.print("Program Mode");

	setupStage = GameMode;
	hasShownMessage = false;
	isAllDone = false;

	resetMultiInput();
}

const int maxInputs = 3;
char multiInput[maxInputs];

void resetMultiInput()
{
	memset(multiInput, '0', maxInputs);
}

uint8_t parseMultiInput()
{
	// Detect if the input is too big. TODO: Some kind of error message?
	if (multiInput[0] >= '2') { // Abuse that '1' < '2'
		if (multiInput[0] > '2') {
			return 0;
		} else if (multiInput[1] >= '5') {
			if (multiInput[1] > '5' || multiInput[2] > '5') {
				return 0;
			}
		}
	}
	// lazyness loop unrolling. It'll always be 3 due to 8 bit requirements
	uint8_t res = 0;
	res += (multiInput[0] - '0') * 100;
	res += (multiInput[1] - '0') * 10;
	res += (multiInput[2] - '0') * 1;

	return res;
}

uint8_t getMultiInput()
{
	char key = customKeypad.getKey();
	if (key == '#')
		return parseMultiInput();
	else if (!key || !isNumberInput(key))
		return 0;

	// Add key to current inputs
	for (int i = 0; i < maxInputs - 1; i++) {
		multiInput[i] = multiInput[i + 1];
	}
	multiInput[maxInputs - 1] = key;

	lcd.setCursor(0, 3);
	lcd.write(multiInput, maxInputs); // Write as buffer
	return 0;
}

void writeHeader(String message)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(message);
}

void writeMultipleChoice(String message, String a, String b, String c, String d)
{
	writeHeader(message);
	lcd.setCursor(0, 2);
	lcd.print("A: ");
	lcd.print(a);
	lcd.setCursor(11, 2);
	lcd.print("B: ");
	lcd.print(b);
	lcd.setCursor(0, 3);
	lcd.print("C: ");
	lcd.print(c);
	lcd.setCursor(11, 3);
	lcd.print("D: ");
	lcd.print(d);
}

void writeMultipleChoice(String message, String a, String b)
{
	writeHeader(message);
	lcd.setCursor(0, 2);
	lcd.print("A: ");
	lcd.print(a);
	lcd.setCursor(0, 3);
	lcd.print("B: ");
	lcd.print(b);
}

uint8_t getMultipleChoice(int num)
{
	char key = customKeypad.getKey();
	if (!key || !isLetterInput(key)) {
		return 0;
	}
	key -= 'a';
	if (key >= num)
		return 0;
	return key;
}


void setup_loop()
{
	if (isAllDone) return;

	char key;
	uint8_t res;
	switch (setupStage) {
	case GameMode: {
		if (!hasShownMessage) {
			writeMultipleChoice("Pick a gamemode", "Butts", "Butts", "Butts", "Butts");
			hasShownMessage = true;
			return;
		}

		res = getMultipleChoice(4);
		if (!res)
			return;
		EEPROM.write(EPGamemode, res);

		// reset for the next stage
		setupStage = KeyCard;
		hasShownMessage = false;
		lcd.clear();
		return;
	}
	case KeyCard: {
		if (!hasShownMessage) {
			writeMultipleChoice("Keycards enabled?", "Yes", "No");
			hasShownMessage = true;
			return;
		}

		res = getMultipleChoice(2);
		if (!res)
			return;
		EEPROM.write(EPKeycardsEnabled, res);

		// reset for the next stage
		setupStage = ArmTime;
		hasShownMessage = false;
		return;
	}
	case ArmTime: {
		if (!hasShownMessage) {
			writeHeader("How long to arm?");
			lcd.setCursor(0, 1);
			lcd.print("Press # to confirm");
			lcd.setCursor(0, 3);
			lcd.print("000 seconds");
			hasShownMessage = true;
			return;
		}

		res = getMultiInput();
		if (!res)
			return;
		EEPROM.write(EPArmLength, res);

		// reset for the next stage
		setupStage = CodeMethod;
		hasShownMessage = false;
		// TODO: Clear LCD
		return;
	}
	default: {
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Finished setup");
		isAllDone = true;
		// do something
	}
	}
	/*
	   FIXME: This is probably no longer necessary. (Probably?)

	   // Set game mode (A,B,C,D)
	   char gamemode;

	   // Set key cards (on/off)
	   int kcard;

	   // Set code method (Automatically generated/manual)
	   int codem;

	   // Set no. of activation codes (numeric 1-9)
	   int ACodeNum;

	   // Set no. of deactivation codes (numeric 1-9)
	   int DCodeNum;

	   // Set strobe (on/off)
	   int strobe;

	   // Set piezos (on/off)
	   int piezos;

	   // Commit all variables to EEPROM (byte no, value)
	   EEPROM.write(0, gamemode);
	   EEPROM.write(1, kcard);
	   EEPROM.write(2, codem);
	   EEPROM.write(3, ACodeNum);
	   EEPROM.write(4, DCodeNum);
	   EEPROM.write(5, strobe);
	   EEPROM.write(6, piezos);
	   */
}
