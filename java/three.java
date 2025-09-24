import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;
import java.util.Random;

public class three {
    private static final int TOTAL_WORDS = 1000;
    private static final int BATCH_SIZE = 100;
    private static final int BUFFER_SIZE = 10;
    private static final int SLEEP_SECONDS = 5;

    private static final String[] fruits = {"apple", "banana", "mango", "grape", "orange"};

    private final String[] buffer = new String[BUFFER_SIZE];
    private int in = 0, out = 0;

    private final Semaphore emptySlots = new Semaphore(BUFFER_SIZE);
    private final Semaphore filledSlots = new Semaphore(0);

    private final ReentrantLock lock = new ReentrantLock();

    private int appleCount = 0, mangoCount = 0, grapeCount = 0;

    class Producer implements Runnable {
        private final Random rand = new Random();

        @Override
        public void run() {
            try {
                for (int i = 1; i <= TOTAL_WORDS; i++) {
                    String fruit = fruits[rand.nextInt(fruits.length)];

                    emptySlots.acquire();  // Wait for empty slot
                    lock.lock();
                    try {
                        buffer[in] = fruit;
                        in = (in + 1) % BUFFER_SIZE;
                    } finally {
                        lock.unlock();
                    }
                    filledSlots.release();  // Signal new item produced

                    if (i % BATCH_SIZE == 0) {
                        System.out.printf("👷 Producer: Generated %d fruits, sleeping %d seconds...\n", i, SLEEP_SECONDS);
                        Thread.sleep(SLEEP_SECONDS * 1000);
                    }
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.err.println("Producer interrupted");
            }
        }
    }

    class Consumer implements Runnable {
        @Override
        public void run() {
            try {
                for (int i = 1; i <= TOTAL_WORDS; i++) {
                    filledSlots.acquire();  // Wait for an item
                    String fruit;
                    lock.lock();
                    try {
                        fruit = buffer[out];
                        out = (out + 1) % BUFFER_SIZE;
                    } finally {
                        lock.unlock();
                    }
                    emptySlots.release();  // Signal a free slot

                    // Count fruits
                    if ("apple".equals(fruit)) appleCount++;
                    else if ("mango".equals(fruit)) mangoCount++;
                    else if ("grape".equals(fruit)) grapeCount++;
                }

                System.out.printf("👨 Consumer: Counted %d apples, %d mangoes, %d grapes.\n", appleCount, mangoCount, grapeCount);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.err.println("Consumer interrupted");
            }
        }
    }

    public void start() throws InterruptedException {
        Thread producerThread = new Thread(new Producer());
        Thread consumerThread = new Thread(new Consumer());

        producerThread.start();
        consumerThread.start();

        producerThread.join();
        consumerThread.join();

        System.out.println("✅ Done.");
    }

    public static void main(String[] args) throws InterruptedException {
        new three().start();
    }
}
