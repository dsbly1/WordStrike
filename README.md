# WordStrike

Console-based C++ word-guessing game — COSC 438 DEA, Object-Oriented Design  
**Damon Bly | Columbia College | June 2026**

---

## Architecture

Three-tier layered architecture with five GoF design patterns:

| Pattern | Location |
|---|---|
| Strategy | `DifficultyStrategy` + `EasyMode` / `MediumMode` / `HardMode` |
| Factory Method | `createStrategy()` in `main.cpp` |
| Observer | `IObserver` / `Game` / `FeedbackRenderer` |
| Singleton | `SessionManager` (Meyers Singleton) |
| Template Method | `applyRules()` in `DifficultyStrategy` |

---

## Build

```bash
make
```

Or manually:

```bash
g++ -std=c++17 -Wall -Wextra -o WordStrike \
    main.cpp Game.cpp EasyMode.cpp MediumMode.cpp HardMode.cpp \
    WordRepository.cpp Player.cpp HintEngine.cpp \
    SessionManager.cpp FeedbackRenderer.cpp
```

## Run

```bash
./WordStrike
```

## Commands

| Input | Action |
|---|---|
| Any word | Submit a guess |
| `hint` | Reveal one letter (if hints remain) |
| `quit` | End current round |
| `H` | View session history after a round |
| `P` | Play again |
| `Q` | Quit game |

## Difficulty

| Mode | Attempts | Hints | Word Length |
|---|---|---|---|
| Easy | 8 | 3 | 4–5 letters |
| Medium | 6 | 1 | 5–6 letters |
| Hard | 4 | 0 | 6–8 letters |
