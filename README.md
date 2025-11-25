# OS lab Index Table C Sec - Monday Batch

| Experiment No. | Simplified Experiment Title             | Date                |
| -------------- | --------------------------------------- | ------------------- |
| 1              | Process system calls (fork, exec, wait) | 15-09-2025 (Monday) |
| 2              | CPU scheduling algorithms               | 22-09-2025 (Monday) |
| 3              | Producer–consumer using semaphores      | 29-09-2025 (Monday) |
| 4              | Reader–writer IPC using FIFO            | 06-10-2025 (Monday) |
| 5              | Banker’s algorithm (deadlock avoidance) | 13-10-2025 (Monday) |
| 6              | Contiguous memory allocation            | 27-10-2025 (Monday) |
| 7              | Page replacement algorithms             | 03-11-2025 (Monday) |
| 8              | File organization techniques            | 24-11-2025 (Monday) |
| 9              | Linked file allocation                  | 01-12-2025 (Monday) |
| 10             | SCAN disk scheduling                    | 08-12-2025 (Monday) |

# OS lab Index Table C Sec - Wednesday Batch

| Experiment No. | Simplified Experiment Title             | Date                   |
| -------------- | --------------------------------------- | ---------------------- |
| 1              | Process system calls (fork, exec, wait) | 17-09-2025 (Wednesday) |
| 2              | CPU scheduling algorithms               | 24-09-2025 (Wednesday) |
| 3              | Producer–consumer using semaphores      | 08-10-2025 (Wednesday) |
| 4              | Reader–writer IPC using FIFO            | 15-10-2025 (Wednesday) |
| 5              | Banker’s algorithm (deadlock avoidance) | 29-10-2025 (Wednesday) |
| 6              | Contiguous memory allocation            | 05-11-2025 (Wednesday) |
| 7              | Page replacement algorithms             | 26-11-2025 (Wednesday) |
| 8              | File organization techniques            | 03-12-2025 (Wednesday) |
| 9              | Linked file allocation                  | 10-12-2025 (Wednesday) |
| 10             | SCAN disk scheduling                    | 17-12-2025 (Wednesday) |

1. Mermaid Markdown 
2. lucid Chart
🔗[website](https://www.lucidchart.com/pages)

# Experiment 1: Develop a c program to implement the Process system calls (fork (), exec(), wait(), create process,terminate process)

### Sequence Diagram

#### **Section 1: Forking the child process**

```mermaid
sequenceDiagram
    participant Parent
    participant Child

    Parent->>Child: fork() → create child process
    %% Describe child process without using Note inside alt
    Parent->>Child: Child process will run generate_fruits

    alt fork fails
        Parent->>Parent: perror("Fork failed")
        Parent->>Parent: exit(1)
    else fork succeeds
        Parent->>Child: Proceed with child execution
    end
```

---

#### **Section 2: Child generates fruits**

```mermaid
sequenceDiagram
    participant Child
    participant fruits.txt

    Child->>Child: Open "fruits.txt" for writing
    loop 1000 words
        Child->>Child: Generate random fruit
        Child->>fruits.txt: Write fruit
        alt every 100 words
            Child->>Child: Print "Generated 100 words, sleeping..."
            Child->>Child: sleep(5)
        end
    end
    Child->>Child: Close "fruits.txt"
    Child-->>Parent: exit(0)
```

---

#### **Section 3: Parent counts fruits**

```mermaid
sequenceDiagram
    participant Parent
    participant fruits.txt

    Parent->>Parent: wait() for child
    Parent->>Parent: Print "Child finished. Counting fruits..."
    Parent->>fruits.txt: Open file for reading
    loop for each word in file
        Parent->>Parent: Count apples, mangoes, grapes
    end
    Parent->>Parent: Close "fruits.txt"
    Parent->>Parent: Print counted results
```

### Flow Chart

```mermaid
flowchart TD
    A(Start main) --> B(fork called)
    
    B -->|fork fails| C(Print fork failed and exit)
    
    B -->|fork succeeds| D{pid == 0?}
    
    D -->|Yes| E(Child process starts)
    E --> F(Call generate_fruits)
    F --> G(Open fruits.txt for writing)
    G --> H(Generate random fruits and write to file)
    H --> I(Sleep every 100 words)
    I --> J(Close file)
    J --> K(Child exits)
    
    D -->|No| L(Parent process continues)
    L --> M(wait for child to finish)
    M --> N(Print Child finished. Counting fruits)
    N --> O(Open fruits.txt for reading)
    O --> P(Call count_fruits)
    P --> Q(Close file)
    Q --> R(Print counted results)
```

# Experiment 2: Process Scheduling
🔗[Process Scheduling](https://erpjietuniverse.in/virtual_lab/Operating_system/labs/exp2/theory.html)


# Experiment 3: Develop a C program to simulate producer-consumer problem using semaphores.

### Sequence Diagram

```mermaid
sequenceDiagram
    participant Producer
    participant Buffer
    participant Consumer

    loop for each fruit
        Producer->>empty_slots: sem_wait(empty_slots)  // Wait for empty slot
        Producer->>Buffer: pthread_mutex_lock()        // Lock buffer
        Producer->>Buffer: Add fruit to buffer
        Producer->>Buffer: pthread_mutex_unlock()      // Unlock buffer
        Producer->>filled_slots: sem_post(filled_slots) // Signal item available

        Note over Producer, Consumer: Producer sleeps every 100 items

        Consumer->>filled_slots: sem_wait(filled_slots) // Wait for item
        Consumer->>Buffer: pthread_mutex_lock()        // Lock buffer
        Consumer->>Buffer: Remove fruit from buffer
        Consumer->>Buffer: pthread_mutex_unlock()      // Unlock buffer
        Consumer->>empty_slots: sem_post(empty_slots)  // Signal slot free
        Consumer->>Consumer: Count fruit
    end

    Note over Producer, Consumer: Both threads continue until TOTAL_WORDS are processed

```

### Activity / Flow Chart
```mermaid
flowchart TD
    Start([Start Program]) --> Init([Initialize semaphores and mutex])

    Init --> ProducerStart([Start Producer Thread])
    Init --> ConsumerStart([Start Consumer Thread])

    %% Producer Loop
    ProducerStart --> ProdCheckLoop{Produced < TOTAL_WORDS?}
    ProdCheckLoop -->|Yes| ProdWaitEmpty(["sem_wait empty_slots"])
    ProdWaitEmpty --> ProdLock(["Lock buffer"])
    ProdLock --> ProdAdd(["Add fruit to buffer"])
    ProdAdd --> ProdUnlock(["Unlock buffer"])
    ProdUnlock --> ProdSignal(["sem_post filled_slots"])
    ProdSignal --> ProdSleep{Produced % BATCH_SIZE == 0?}
    ProdSleep -->|Yes| ProdSleepAction([Sleep for SLEEP_SECONDS])
    ProdSleep -->|No| ProdCheckLoop
    ProdSleepAction --> ProdCheckLoop
    ProdCheckLoop -->|No| ProducerEnd([Producer Thread Ends])

    %% Consumer Loop
    ConsumerStart --> ConsCheckLoop{Consumed < TOTAL_WORDS?}
    ConsCheckLoop -->|Yes| ConsWaitFilled(["sem_wait filled_slots"])
    ConsWaitFilled --> ConsLock(["Lock buffer"])
    ConsLock --> ConsRemove(["Remove fruit from buffer"])
    ConsRemove --> ConsUnlock(["Unlock buffer"])
    ConsUnlock --> ConsSignal(["sem_post empty_slots"])
    ConsSignal --> CountFruit(["Count fruit"])
    CountFruit --> ConsCheckLoop
    ConsCheckLoop -->|No| ConsumerEnd([Consumer Thread Ends and Print Counts])

    %% End
    ProducerEnd --> JoinThreads([Wait for threads to finish])
    ConsumerEnd --> JoinThreads
    JoinThreads --> Destroy([Destroy semaphores and mutex])
    Destroy --> End([Program Ends])
```

# Experiment 4: Inter Process Communication using mkfifo
### Sequence Diagram
```mermaid
sequenceDiagram
    participant WriterProcess
    participant FIFO
    participant ReaderProcess

    Note over FIFO: FIFO created using mkfifo()

    WriterProcess->>FIFO: open(FIFO, O_WRONLY)
    loop generate data (e.g., price updates)
        WriterProcess->>FIFO: write(data)  // write current price to FIFO
        Note over WriterProcess: GUI update optional (ignored)
        WriterProcess->>WriterProcess: sleep(1s) // simulate periodic updates
    end
    WriterProcess->>FIFO: close()  // Writer finished

    ReaderProcess->>FIFO: open(FIFO, O_RDONLY)
    loop read data
        FIFO->>ReaderProcess: read(data)  // read price from FIFO
        ReaderProcess->>ReaderProcess: process/display data
    end
    ReaderProcess->>FIFO: close()  // Reader finished
```

### Activity / Flow Chart
```mermaid
flowchart TD
    Start([Start Program]) --> MkFifo([Create FIFO using mkfifo])

    %% Writer Process
    MkFifo --> WriterStart([Start Writer Process])
    WriterStart --> WriterOpen([open FIFO for writing])
    WriterOpen --> WriterLoop{More data to write?}
    WriterLoop -->|Yes| WriteData([write data to FIFO])
    WriteData --> Sleep([sleep 1 second])
    Sleep --> WriterLoop
    WriterLoop -->|No| WriterClose([close FIFO])

    %% Reader Process
    MkFifo --> ReaderStart([Start Reader Process])
    ReaderStart --> ReaderOpen([open FIFO for reading])
    ReaderOpen --> ReaderLoop{More data to read?}
    ReaderLoop -->|Yes| ReadData([read data from FIFO])
    ReadData --> ProcessData([process/display data])
    ProcessData --> ReaderLoop
    ReaderLoop -->|No| ReaderClose([close FIFO])

    %% End
    WriterClose --> End([Program Ends])
    ReaderClose --> End
```

# Experiment 5: Bankers Algorithm
🔗[PPT: Bankers Page 23 to 29](https://drive.google.com/file/d/1-MBdZEvuBj5Iqi06JaxODA-inlysQEdO/view)

# Experiment 6: Memory Allocation Techniques
🔗[Click Here](https://erpjietuniverse.in/virtual_lab/Operating_system/labs/exp7/theory.html)

# Experiment 7: Page Replacement Algorithms
🔗[Click Here](https://erpjietuniverse.in/virtual_lab/Operating_system/labs/exp8/theory.html)

# Experiment 8: Directory organisation techniques
🔗[Scroll Page 19 to 21](https://drive.google.com/file/d/1LJbQ8V3Xr6lJXIb1tV0b9kafynorp9mr/view?usp=classroom_web&authuser=0)

# Experiment 9: Linked file allocation strategies
🔗[Scroll page 16 to 26](https://drive.google.com/file/d/1jE84lI4pmz7K-bp7GF_PnGA-bdQuWESm/view?usp=classroom_web&authuser=0)

# Experiment 10: Disck Sheduling algorithms
🔗[Click Here](https://erpjietuniverse.in/virtual_lab/Operating_system/labs/exp10/theory.html)