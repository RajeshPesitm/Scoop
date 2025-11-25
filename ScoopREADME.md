## 🔧 Environment Setup (Windows)

To set up Java (JDK ) and MinGW (for C/C++), run:

```powershell
powershell -ExecutionPolicy Bypass -File setup-env.ps1
```

# 📁 Directory Structure (suggested)
```ardino
your-repo/
├── java/
│   └── HelloWorld.java
├── cpp/
│   └── hello.cpp
├── setup-env.ps1
└── README.md

```


# Copy/paste this to Bootstrap script file in your repo
```powershell
# setup-env.ps1
# Run with: powershell -ExecutionPolicy Bypass -File setup-env.ps1

Write-Host "Setting up environment using Scoop..."

# Install Scoop if not present
if (-not (Get-Command scoop -ErrorAction SilentlyContinue)) {
    Write-Host "Scoop not found. Installing Scoop..."
    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser -Force
    irm get.scoop.sh | iex
}

# Add required buckets
scoop bucket add main
scoop bucket add java
scoop bucket add versions

# Install tools

# Check for Java (javac is the compiler)
if (Get-Command javac -ErrorAction SilentlyContinue) {
    Write-Host "Java is already installed globally."
} else {
    scoop install openjdk
}

# Check for MinGW (use gcc or g++ as check)
if (Get-Command gcc -ErrorAction SilentlyContinue) {
    Write-Host "MinGW (gcc) is already installed globally."
} else {
    scoop install mingw
}



Write-Host "Setup complete. Please restart your terminal or source the updated path."

```


# To uninstall a package installed with **Scoop**, like `openjdk`, it's very simple:

---

### 🗑️ Uninstall a Package

```powershell
scoop uninstall openjdk
```

This will:

* Remove the `openjdk` binaries installed via Scoop.
* Clean up the environment variables (e.g., `PATH`) that Scoop added for it.
* Leave **any global/system JDK installations untouched**.

---

### 📦 Check What's Installed

To see what’s installed:

```powershell
scoop list
```

You’ll see something like:

```
Installed apps:
  git 2.42.0
  openjdk 17.0.9
  mingw 12.2.0
```

---

### 🧼 Optional Cleanup

After uninstalling, you can also run:

```powershell
scoop cleanup
```

This removes old versions or unused caches from Scoop’s storage.

---

### 🚫 Reminder

> **Uninstalling `openjdk` from Scoop only affects the Scoop-managed installation.**
> It will **not** uninstall or impact any system-wide JDK you have (e.g., in `C:\Program Files\Java`).

---

Let me know if you want to switch between multiple JDK versions with Scoop (totally doable too).
