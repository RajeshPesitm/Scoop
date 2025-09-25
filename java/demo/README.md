# Error
Ah, this error:

```
/usr/bin/java: symbol lookup error: /snap/core20/current/lib/x86_64-linux-gnu/libpthread.so.0: undefined symbol: __libc_pthread_init, version GLIBC_PRIVATE
```

is related to **a conflict between Snap-installed Java and your system’s libc (glibc) libraries**.

---

Yes, absolutely! You can **keep your OpenJDK 21 installation** and configure your system to use it **instead of the Snap-installed Java** by updating your `JAVA_HOME` and `PATH` environment variables.

---

### Here’s how to do it **temporarily (current terminal session only):**

```bash
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH
```

---

### To verify:

```bash
java -version
which java
```

You should see:

* Java version 21
* Java binary path like `/usr/lib/jvm/java-21-openjdk-amd64/bin/java`

---

### To make this **permanent** for your user, add the lines to your `~/.bashrc` or `~/.profile` file:

```bash
echo 'export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64' >> ~/.bashrc
echo 'export PATH=$JAVA_HOME/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

---

### Option 2: Run Terminal Outside VScode: This works


# About This Project:
Fourth experiment:
Great! Here's a step-by-step guide to **build and run the Java GUI gold rate simulator using Maven** in **Visual Studio Code (VS Code)** with the **Java Extension Pack** installed.

---

## ✅ What You'll Do

1. Create a Maven project in VS Code.
2. Add `JFreeChart` to `pom.xml`.
3. Add the Java GUI simulator code.
4. Run the GUI from VS Code.

---

## 🧰 Prerequisites

Make sure you have the following:

| Tool                                 | Installed?         |
| ------------------------------------ | ------------------ |
| ✅ **Java Extension Pack** in VS Code | ✅                  |
| ✅ JDK (Java 17+ recommended)         | ✅                  |
| ✅ Apache Maven                       | ✅                  |
| ✅ `jfreechart` dependency            | Will add via Maven |

---

## 📦 Step-by-Step Setup in VS Code

---

### ✅ 1. **Create a New Maven Project**

1. Open VS Code.
2. Open Command Palette: `Ctrl + Shift + P`
3. Type: `JAVA: Create JAVA Project`
4. Choose:

   * Archetype: `maven-archetype-quickstart`
   * Group ID: `com.example`
   * Artifact ID: `GoldRateSimulator`
5. Choose a folder to generate the project.

---

### ✅ 2. **Open the Project in VS Code**

After project creation:

* VS Code may ask: “Would you like to open the project?” → Click **Yes**
* You’ll see a standard Maven project layout:

  ```
  GoldRateSimulator/
  ├── src/
  │   └── main/
  │       └── java/
  │           └── com/
  │               └── example/
  │                   └── App.java
  ├── pom.xml
  ```

---


### ✅ 5. **Build and Run the Project**

#### ▶️ Run from Terminal:

```bash
mvn clean compile
mvn exec:java -Dexec.mainClass="com.example.App"
```

