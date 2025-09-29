## install JDK

### 1. Uninstall the current JDK (OpenJDK 11)

Run the following commands to remove OpenJDK 11:

```bash
sudo apt-get remove --purge openjdk-11-*
sudo apt-get autoremove
```

This will remove OpenJDK 11 packages and clean up unnecessary dependencies.

---

### 2. Install the latest JDK

As of now, the latest long-term support (LTS) release is **OpenJDK 20** or **OpenJDK 21** (depending on release date). You can check the latest version available from the Ubuntu repositories or install directly from Oracle or AdoptOpenJDK.

#### Option A: Install latest OpenJDK from Ubuntu PPA (usually stable and tested)

You can add a PPA to get the latest OpenJDK:

```bash
sudo add-apt-repository ppa:openjdk-r/ppa
sudo apt-get update
sudo apt-get install openjdk-21-jdk
```

*(Replace `openjdk-21-jdk` with the version you want if different)*

---

#### Option B: Install latest OpenJDK from Ubuntu official repo (might not be the absolute latest)

Check available versions:

```bash
apt search openjdk
```

Then install, e.g.,

```bash
sudo apt-get install openjdk-21-jdk
```

---

### 3. Verify the installation

After installation, check the version:

```bash
java --version
javac --version
```

---

### 4. (Optional) Set default Java version if multiple installed

Use `update-alternatives` to configure:

```bash
sudo update-alternatives --config java
sudo update-alternatives --config javac
```

## Install Maven
Ubuntu:

```bash
# Update package index
sudo apt update

# Install Maven
sudo apt install maven -y

# Verify Maven installation
mvn -version

# Uninstall Maven when done once for all
sudo apt remove maven -y

# Remove unused dependencies
sudo apt autoremove -y
```

windows:

```bash
# Check scoop installed
# in your project folder
scoop install maven
# restart terminal and check maven installed
mvn -version
```


