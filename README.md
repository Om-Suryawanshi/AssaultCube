# 🛠 AssaultCube Cheat DLL

A multifunction internal cheat (DLL) for **AssaultCube v1.2.0.2**, offering powerful in-game hacks like:

| Feature         | Description                                     |
|----------------|-------------------------------------------------|
| God Mode       | Infinite health, ammo, and armor                |
| Aimbot         | Aim assistance with optional smoothing          |
| ESP            | Draws enemy boxes, names, health, and distance  |
| Triggerbot     | Auto-shoots when crosshair is on an enemy       |
| No Recoil      | Removes weapon recoil by patching memory        |

---

## Demo
![Gameplay demo](img/demo.gif)

---

## 🎮 Game Download

➡️ Download **AssaultCube v1.2.0.2** here:  
**[https://github.com/assaultcube/AC/releases/tag/v1.2.0.2](https://github.com/assaultcube/AC/releases/tag/v1.2.0.2)**

---

## ⚙️ Setup & Build

### Requirements

- Visual Studio 2019+ (use **Win32** / **x86** build configuration)
- Windows 10+ with admin privileges for DLL injection

### Steps

1. Clone or download this repo.
2. Open the solution in Visual Studio.
3. Set **Platform** to **Win32**, and **Configuration** to **Release**.
4. Build the solution. The DLL will be located in `/Release/`.
5. Use any DLL injector (like Process Hacker or GH Injector) to inject the DLL into `ac_client.exe`.

---

## 💡 Console Commands

After injection, a console will appear. Type commands to toggle features:

- `god` → Toggle God Mode  
- `aim` → Toggle Aimbot  
- `esp` → Toggle ESP  
- `trigger` → Toggle Triggerbot  
- `recoil` → Toggle No Recoil  
- `enemy` → Print enemy info to console  
- `name` → Print your player name  
- `help` → Show command list  
- `exit` → Unload DLL and exit

---

## 🔧 Technical Overview

- **Memory Offsets**:  
  All player and weapon offsets are defined in `constants.cpp`.

- **Aimbot**:  
  Locks onto the nearest enemy to your crosshair each frame.

- **Triggerbot**:  
  Uses `Crosshair Ent` to check if an enemy is under your crosshair, and sets the shooting byte to `1`.

- **ESP**:  
  Projects entity positions to screen coordinates using the game’s view matrix.

- **No Recoil**:  
  NOPs the recoil function's instructions at runtime using `VirtualProtect`.

- **God Mode**:  
  Redirects the game's health, ammo, and armor updates to preserve values.

---

## ⚠️ Disclaimer

This is for **educational purposes only**.  
Using this cheat in online games may violate game rules or terms of service.  
**You are responsible for any consequences.**

---

## 📚 References

- [AssaultCube GitHub](https://github.com/assaultcube/AC)

---

## 🤝 Contributing

Want to improve this? Add new features or help optimize performance!

1. Fork this repo
2. Create a new branch (`git checkout -b feature-xyz`)
3. Commit your changes
4. Open a pull request

---

## 📜 License

This project is open for learning and experimentation. Do not redistribute it for malicious or commercial purposes.
