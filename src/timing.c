// --- Includes ---

// --- Variables ---

// --- Prototypes ---
	// --- Nap 1µs ---
	void Nap(int microsec){
		while (microsec--){
			volatile int nap = 6;	// sagt dem Compiler dass er an die Variable nichts ändern darf

			while (nap--){
				__asm("nop\n"		//Assembler Befehle
					  "nop\n"
					  "nop\n"
					  "nop\n"
					  "nop\n"
					  "nop\n");
			}
		}
	}

	// --- Delay ---
	void Delay(int millisec){
		while (millisec--)
			Nap(1000);
	}
