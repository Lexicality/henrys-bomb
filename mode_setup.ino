
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

const int maxInputs = 3;
char multiInput[maxInputs];
int numArmInputs;

void setup_setup()
{
	lcd.setCursor(0, 5);
	lcd.print("Program Mode");

	memset(multiInput, '0', maxInputs);

	setupStage = GameMode;
	hasShownMessage = false;
	isAllDone = false;

	numArmInputs = 0;
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


void setup_loop()
{
	if (isAllDone) return;

	char key;
	switch (setupStage) {
	case GameMode: {
		if (!hasShownMessage) {
			writeMultipleChoice("Pick a gamemode", "Butts", "Butts", "Butts", "Butts");
			hasShownMessage = true;
			return;
		}
		key = customKeypad.getKey();
		if (!key || !isLetterInput(key)) {
			return;
		}
		int gamemode = static_cast<int>(key);
		EEPROM.write(EPGamemode, gamemode);

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
		key = customKeypad.getKey();
		if (!key || !isLetterInput(key) || !(key == 'a' || key == 'b')) {
			return;
		}
		EEPROM.write(EPKeycardsEnabled, key == 'a' ? 1 : 0);

		// reset for the next stage
		setupStage = ArmTime;
		hasShownMessage = false;
		return;
	}
	case ArmTime: {
		if (!hasShownMessage) {
			writeHeader("What's your arm time?");
			hasShownMessage = true;
			return;
		}
		key = customKeypad.getKey();
		if (!key) {
			return;
		}
		// Avoid letters
		if (!isNumberInput(key)) {
			return;
		}
		// Add key to current inputs
		multiInput[numArmInputs] = key;
		numArmInputs += 1;

		lcd.setCursor(0, 2);
		lcd.write(multiInput, maxInputs);
		lcd.write(" seconds");

		if (numArmInputs < maxInputs) {
			return;
		}
		// all done

		int armTime = 0;
		// TODO: Transfer array of characters to actual number here
		EEPROM.write(EPArmLength, armTime);

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
