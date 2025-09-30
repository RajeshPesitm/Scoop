# Create Installer For your App

### 🔧 Step 1: Add Shade Plugin Inside `<plugins>`, Not Just `<pluginManagement>`

Your `pom.xml` should look like this commit:


### Cleanup
1. If you’re unsure about the package name, you can check with:
```bash
dpkg -l | grep goldsimulator
```
2. Remove the package:
```bash
sudo dpkg -r goldsimulator
```

Or, better:
```bash
sudo apt-get remove goldsimulator
```

This will remove the package but keep configuration files.

3. To remove package including configuration files:
```bash
sudo apt-get purge goldsimulator
```
Note: dpkg itself doesn’t resolve dependencies, so if the package installed dependencies, you might want to clean those up as well:
```bash
sudo apt-get autoremove
```

## ✅ Rebuild everything

Now that your `pom.xml` is updated:

```bash
mvn clean package
```
### 📦 So the file you're looking for is:

```
target/demo-1.0-SNAPSHOT.jar
```

✔ This **IS** the fat JAR now — it includes all dependencies.

---

## ✅ What to do now
create a folde /installer inside your project root and copy the existing fat JAR:

```bash
cp target/demo-1.0-SNAPSHOT.jar installer/
```

## there are two jar files, So confusing
Great — this is a common point of confusion, and I’ll explain it clearly.

---

### 🧠 You Have Two JAR Files in `target/`

Let's break them down:

#### ✅ 1. `demo-1.0-SNAPSHOT.jar`

* ✅ **This is the final, shaded JAR.**
* ✅ It contains **your code + all dependencies** (e.g. JFreeChart).
* 🔥 **This is the one you should use** for running, packaging, and distribution.

#### 🗂 2. `original-demo-1.0-SNAPSHOT.jar`

* 📦 This is the **unshaded JAR** (your code only, no dependencies).
* 💡 The `maven-shade-plugin` creates this as a backup before it overwrites the main `demo-1.0-SNAPSHOT.jar`.

---

#### ✅ So What Should You Do?

Use this JAR for everything:

```bash
target/demo-1.0-SNAPSHOT.jar
```

For example:

####  🛠 3.  Run it directly:

```bash
java -jar target/demo-1.0-SNAPSHOT.jar
```

#### 📥 4. Package it with `jpackage`:

```bash
cp target/demo-1.0-SNAPSHOT.jar installer/
```

---



```bash
jpackage \
  --type deb \
  --input installer \
  --dest installer/output \
  --name GoldSimulator \
  --main-jar demo-1.0-SNAPSHOT.jar \
  --main-class com.example.App \
  --icon installer/icon.png \
  --java-options '-Xmx512m' \
  --app-version 1.0 \
  --vendor "HobbyProject" \
  --description "Gold Price Simulation App with Live Chart"

```



###  5. Install the `.deb` package

```bash
sudo dpkg -i installer/output/goldsimulator_1.0_amd64.deb
```

---

### 🔍 6. Check installation
---

  🧠 Since JDK 17+, `jpackage` uses `/opt/<vendor>/<app-name>` structure by default unless overridden.

---

## ✅ Find the Real Install Path

Let’s check where it actually is:

### Run:

```bash
find /opt -type f -iname '*GoldSimulator*' 2>/dev/null
```

Or:

```bash
grep -i Exec /usr/share/applications/GoldSimulator.desktop
# try this also, otherwise
cat /opt/goldsimulator/lib/goldsimulator-GoldSimulator.desktop
```

That will show the **actual path to the binary**.

You might see something like:

```
Exec=/opt/HobbyProject/GoldSimulator/bin/GoldSimulator
```

---

## 🔧 Optionally: Make it Work in Terminal

If you want to be able to launch the app via terminal by just typing `GoldSimulator`, do this:

### 1. Find the binary path, e.g.:

```bash
/opt/HobbyProject/GoldSimulator/bin/GoldSimulator
```

### 2. Create a symlink in `/usr/local/bin`:

```bash
sudo ln -s /opt/HobbyProject/GoldSimulator/bin/GoldSimulator /usr/local/bin/GoldSimulator
```

### 3. Now run from anywhere:

```bash
GoldSimulator
```


### Optionally: Make it Work in current Terminal sesson
##### ✅ Option 3 (temporary): Use an alias

You can create a temporary shell alias if you don’t want to modify $PATH:
```bash
alias GoldSimulator='/opt/goldsimulator/bin/GoldSimulator'
```

This works only in the current terminal session.

---

## ✅ Summary of test results

| Feature                            | Status                               |
| ---------------------------------- | ------------------------------------ |
| GUI launches from Application Menu | ✅ Yes                                |
| App icon shown                     | ✅ Yes                                |
| All dependencies bundled           | ✅ Yes (fat JAR)                      |
| Terminal command works             | ❌ Not yet (can be fixed via symlink) |
| `.deb` installer built properly    | ✅ Yes                                |

---

Let me know if you'd like to:

* Package `.rpm` or `.exe`
* Customize the icon, launcher name, or install path
* Bundle a custom JRE (so Java isn’t required to be installed system-wide)

You're really close to being done with a professional-quality installer. 🚀

