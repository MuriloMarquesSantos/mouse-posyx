#include "keyboard.h"
#include <windows.h>

#define NoSymbol 0

static LETTER_ACCENT_TO_LETTER AccentLettersToLetter[] = {
  {
    "áàãâä",
    0,
    0x41
  },
  {
    "ÁÀÃÂÄ",
    1,
    0x41
  },
  {
    "ćĉ",
    0,
    0x43
  },
  {
    "ĆĈ",
    1,
    0x43
  },
  {
    "éèẽêë",
    0,
    0x45
  },
  {
    "ÉÈẼÊË",
    1,
    0x45
  },
  {
    "ǵĝ",
    0,
    0x47
  },
  {
    "ǴĜ",
    1,
    0x47
  },
  {
    "ĥḧ",
    0,
    0x48
  },
  {
    "ĤḦ",
    1,
    0x48
  },
  {
    "íìĩîï",
    0,
    0x49
  },
  {
    "ÍÌĨÎÏ",
    1,
    0x49
  },

  {
    "ĵ",
    0,
    0x4a
  },
  {
    "Ĵ",
    1,
    0x4a
  },
  {
    "ḱ",
    0,
    0x4b
  },
  {
    "Ḱ",
    1,
    0x4b
  },
  {
    "ĺ",
    0,
    0x4c
  },
  {
    "Ĺ",
    1,
    0x4c
  },
  {
    "ḿ",
    0,
    0x4d
  },
  {
    "Ḿ",
    1,
    0x4d
  },
  {
    "ńǹñ",
    0,
    0x4e
  },
  {
    "ŃǸÑ",
    1,
    0x4e
  },
  {
    "óòõôö",
    0,
    0x4f
  },
  {
    "ÓÒÕÔÖ",
    1,
    0x4f
  },
  {
    "ṕ",
    0,
    0x50
  },
  {
    "Ṕ",
    1,
    0x50
  },

  {
    "ŕ",
    0,
    0x52
  },
  {
    "Ŕ",
    1,
    0x52
  },
  {
    "śŝ",
    0,
    0x53
  },
  {
    "ŚŜ",
    1,
    0x53
  },
  {
    "úùũûü",
    0,
    0x55
  },
  {
    "ÚÙŨÛÜ",
    1,
    0x55
  },
  {
    "ǘǜṽ",
    0,
    0x56
  },
  {
    "ǗǛṼ",
    1,
    0x56
  },
  {
    "ẍ",
    0,
    0x57
  },
  {
    "Ẍ",
    1,
    0x57
  },
  {
    "ẃẁŵẅ",
    0,
    0x58
  },
  {
    "ẂẀŴẄ",
    1,
    0x58
  },
  {
    "ỳỹŷÿ",
    0,
    0x59
  },
  {
    "ỲỸŶŸ",
    1,
    0x59
  },
  {
    "źẑ",
    0,
    0x5a
  },
  {
    "ŹẐ",
    1,
    0x5a
  },
  {
    NULL,
    0,
    NoSymbol
  }
};

static LETTER_ACCENT AccentLetters[] = {
  {
    "ẃéŕýúíóṕáśǵḱĺḉźćǘńḿẂÉŔÝÚÍÓṔÁŚǴḰĹḈŹĆǗŃḾ",
    ACUTE,
    0,
    1,
    0xDB,
    "ACUTE"
  },
  {
    "çÇ",
    CEDILLA,
    0,
    0,
    0xBA,
    "CEDILLA"
  },
  {
    "ŴÊŶÛÎÔÂŜĜĤĴẐĈŵêŷûîôâŝĝĥĵẑĉ",
    CIRCUMFLEX,
    1,
    1,
    0xDE,
    "CIRCUMFLEX"
  },
  {
    "ẅëẗÿüïöäḧẍẄËŸÜÏÖÄḦẌ",
    DIAERESIS,
    1,
    1,
    0x36,
    "DIAERESIS"
  },
  {
    "ẁèỳùìòàǜǹẀÈỲÙÌÒÀǛǸ",
    GRAVE,
    1,
    1,
    0xDB,
    "GRAVE"
  },
  {
    "ẽỹũĩõãṽñẼỸŨĨÕÃṼÑ",
    TILDE,
    0,
    1,
    0xDE,
    "TILDE"
  },
  {
    NULL,
    NOTHING,
    0,
    0,
    NoSymbol,
    "NOTHING"
  }
};

KeySym GetLetterFromAccent (char * Input, unsigned int * Return) {
  unsigned int Index = 0;

  while (AccentLettersToLetter[Index].AccentLetters != NULL) {
    if (strstr(AccentLettersToLetter[Index].AccentLetters, Input) != NULL) {
      printf("%s\n", AccentLettersToLetter[Index].AccentLetters);
      *Return = Index;
      return AccentLettersToLetter[Index].Letter;
    }
    Index++;
  }
  printf("return NULL\n");
  *Return = Index;
  return AccentLettersToLetter[Index].Letter;
}

ACCENT GetAccent (char * Input) {
  unsigned int Index = 0;

  printf("GetAccent Input = %s\n", Input);

  while(AccentLetters[Index].Letters != NULL) {
    printf("%s %s\n", AccentLetters[Index].Letters, Input);
    if (strstr(AccentLetters[Index].Letters, Input) != NULL) {
      printf("Accent returned: %d\n", AccentLetters[Index].Accent);
      return AccentLetters[Index].Accent;
    }
    Index++;
  }

  return AccentLetters[Index].Accent;
}

void TypeComplicatedLetter (KEYBOARD * this, char * Input) {
  unsigned int Index = 0;
  KeyCode Keycode;
  ACCENT Acc = GetAccent(Input);
  printf("Accent: %s\n", AccentLetters[Acc].Type);

  if (Acc == NOTHING) {
    printf("I dont know how to interpret this...\n");
    return;
  }

  INPUT InputCommand;
  memset(&InputCommand, 0, sizeof(InputCommand));
  InputCommand.type = INPUT_KEYBOARD;
  if (AccentLetters[Acc].Capitalized) {
    printf("Accent capitalized, pressing shift...\n");
    InputCommand.ki.wVk = 0x10; // shift
    InputCommand.ki.dwFlags = 0;
    SendInput(1, &InputCommand, sizeof(INPUT));
  }

  InputCommand.ki.wVk = AccentLetters[Acc].Keysym;
  InputCommand.ki.dwFlags = 0;
  printf("Pressing keycode: %d Acc %d\n", InputCommand.ki.wVk, Acc);
  SendInput(1, &InputCommand, sizeof(INPUT));
  

  InputCommand.ki.dwFlags = KEYEVENTF_KEYUP;
  printf("Releasing keycode: %d\n", InputCommand.ki.wVk);
  SendInput(1, &InputCommand, sizeof(INPUT));

  if (AccentLetters[Acc].Capitalized) {
    printf("Releasing Shift\n");
    InputCommand.ki.dwFlags = KEYEVENTF_KEYUP;
    InputCommand.ki.wVk = 0x10; // shift
    SendInput(1, &InputCommand, sizeof(INPUT));
  }

  if (AccentLetters[Acc].Composed) {
    printf("Entrei aqui...\n");
    Keycode = GetLetterFromAccent (Input, &Index);
    if (Keycode != NoSymbol) {
      if (AccentLettersToLetter[Index].Capitalized) {
        printf("Accent capitalized, pressing shift...\n");
        InputCommand.ki.wVk = 0x10; // shift
        InputCommand.ki.dwFlags = 0;
        SendInput(1, &InputCommand, sizeof(INPUT));
      }

      printf("Pressing Letter: %d\n", Keycode);
      InputCommand.ki.wVk = Keycode;
      InputCommand.ki.dwFlags = 0;
      SendInput(1, &InputCommand, sizeof(INPUT));
      InputCommand.ki.dwFlags = KEYEVENTF_KEYUP;
      SendInput(1, &InputCommand, sizeof(INPUT));
      printf("Releasing Letter: %d\n", Keycode);

      if (AccentLettersToLetter[Index].Capitalized) {
        InputCommand.ki.dwFlags = KEYEVENTF_KEYUP;
        InputCommand.ki.wVk = 0x10; // shift
        SendInput(1, &InputCommand, sizeof(INPUT));
        printf("Accent capitalized, releasing shift...\n");
      }
    } else {
      printf("I don't know how to handle this character %s\n", Input);
    }
  }

  printf("Finish...\n");
  return;
}

int IsLetterCapitalized(char * Input) {
  if (strlen(Input) == 1) {
    printf("Letter received to compare %c\n", Input[0]);
    printf("Input[0] >= A: %s\n", (Input[0] >= 'A' ? "True" : "False"));
    printf("Input[0] <= Z: %s\n", (Input[0] <= 'Z' ? "True" : "False"));
    printf("Value %d A: %d Z: %d\n", Input[0], 'A', 'Z');

    if (Input[0] >= 'A' && Input[0] <= 'Z') return 1;
    if (Input[0] >= '!' && Input[0] <= '+') {
      // treating special case in pt-br keyboard
      if (Input[0] == '\'') return 0;
      return 1;
    }

    if (Input[0] == '<') return 1;
    if (Input[0] == '_') return 1;

    if (Input[0] >= '>' && Input[0] <= '@') return 1;
    if (Input[0] >= '{' && Input[0] < '~') return 1;
    if (Input[0] == '^') return 1;
    if (Input[0] == ':') return 1;
  } else {
    // another enconding
    char * CapitalizedWithAccent = "ẂẀÉÈẼÊËŔÝỲỸŸÚÙŨÛÜÍÌĨÎÏÓÒÕÔÖṔÃÂÁÀÄŜŚǴĜĤḦĴḰĹḈŹẐẌĆĈǗǛṼŃǸÑḾ"; // found on my keyboards heh
    if (strstr(CapitalizedWithAccent, Input) != NULL) {
      return 1;
    }
  }
  return 0;
}

KeySym LatinStringToKeysym(char * Input) {
  if (Input[0] >= 'a' && Input[0] <= 'z') return 0x41 + Input[0] - 97;
  if (Input[0] >= 'A' && Input[0] <= 'Z') return 0x41 + Input[0] - 65;

  switch(Input[0]) {
    case '!':
    case '1':
      return 49;
    case '@':
    case '2':
      return 50;
    case '#':
    case '3':
      return 51;
    case '$':
    case '4':
      return 52;
    case '%':
    case '5':
      return 53;
    case '6':
    case '¨':
      return 53;
    case '&':
    case '7':
      return 55;
    case '*':
    case '8':
      return 56;
    case '(':
    case '9':
      return 57;
    case ')':
    case '0':
      return 48;
    case '-':
    case '_':
      return 189;
    case '+':
    case '=':
      return 187;

    case '\'':
    case '"':
      return 192;
    case '´':
    case '`':
      return 219;
    case '{':
    case '[':
      return 221;
    case '}':
    case ']':
      return 220;
    case '~':
    case '^':
      return 222;
    case '?':
    case '/':
      return 193;
    case ':':
    case ';':
      return 191;
    case '.':
    case '>':
      return 190;                        
    case ',':
    case '<':
      return 188;                        
    case '\\':
    case '|':
      return 226;                                          
    default:
      break;
  }

  return NoSymbol;
}


void TypeLetterWindows (KEYBOARD * this, char * Input) {
  printf("TypeLetterWindows begin\n");
  printf("Letter received: %s\n", Input);

  // special treatment when @ is sent
  if (Input == NULL) {
    char At = '@';
    Input = &At;
  }

  INPUT InputCommand;

  memset(&InputCommand, 0, sizeof(InputCommand));
  InputCommand.type = INPUT_KEYBOARD;

  if (strcmp(Input, "Backspace") == 0) {
    InputCommand.ki.wVk = 0x08;
  } else if (strcmp(Input, " ") == 0) {
    InputCommand.ki.wVk = 0x20;
  } else if (strcmp(Input, "\n") == 0) {
    InputCommand.ki.wVk = 0x0D;
  } else if (strlen(Input) == 1) {
  	printf("Valor: %d\n", Input[0]);

    if (IsLetterCapitalized (Input)) {
      printf("Capitalized!!\n");
      InputCommand.ki.wVk = 0x10; //shift
      SendInput(1, &InputCommand, sizeof(INPUT));
    }
    InputCommand.ki.wVk = LatinStringToKeysym(Input);

    if (InputCommand.ki.wVk == NoSymbol) {
      printf("I don't know how to interpret this command!\n");
      goto RELEASE_SHIFT;
    }
  } else if (strlen(Input) > 1) {
    TypeComplicatedLetter(this, Input);
    goto FINISH;
  }

  //pressing button
  SendInput(1, &InputCommand, sizeof(INPUT));

RELEASE_SHIFT:
  // release shift
  InputCommand.ki.wVk = 0x10; //shift
  InputCommand.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &InputCommand, sizeof(INPUT));
FINISH:  
  printf("TypeLetterWindows end\n");
}

void ReleaseKeyboardWindows (KEYBOARD * this) {
  free(this);
}

KEYBOARD * InitializeKeyboardDevice() {
  KEYBOARD * Keyboard = (KEYBOARD*)malloc(sizeof(KEYBOARD));

  Keyboard->TypeLetter = TypeLetterWindows;
  Keyboard->Release = ReleaseKeyboardWindows;

  return Keyboard;
}

