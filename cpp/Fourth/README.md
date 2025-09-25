

## 🔄 Execution Flow

1. **Create the FIFO** (once):

   ```bash
   mkfifo goldrate
   ```
   **Compile the Programs**

   Use `gcc` (GNU C Compiler):

   ```bash
   gcc writer.c -o writer
   gcc reader.c -o reader
   ```


2. **Open two terminals:**

   * Terminal 1:

     ```bash
     ./reader
     ```

   * Terminal 2:

     ```bash
     ./writer
     ```

   This simulates real IPC with one process writing and the other reading.

---

## ✅ Bonus: Clean Up

After the experiment:

```bash
rm goldrate
```

## 💡 Tip: Run in Background (Optional)

If you're testing alone and want to run both in the same terminal:

```bash
./reader &   # run reader in background
./writer     # run writer
```


