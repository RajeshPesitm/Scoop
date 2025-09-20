import java.awt.BorderLayout;
import java.awt.Font;
import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;
import javax.swing.*;

public class FruitCounterGUI extends JFrame {
    private JLabel lblFruit;
    private JTextArea textAreaCounts;

    private AtomicInteger mangoCount = new AtomicInteger(0);
    private AtomicInteger orangeCount = new AtomicInteger(0);
    private AtomicInteger grapesCount = new AtomicInteger(0);

    private final String[] fruits = {"mango", "orange", "grapes"};
    private final Random random = new Random();

    private String fruitSlot = null; // single-slot buffer

    private final Object lock = new Object(); // for synchronization

    public FruitCounterGUI() {
        setTitle("Fruit Counter");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        lblFruit = new JLabel("Generated Fruit: ");
        lblFruit.setFont(new Font("Arial", Font.BOLD, 16));

        textAreaCounts = new JTextArea(5, 20);
        textAreaCounts.setEditable(false);
        textAreaCounts.setFont(new Font("Monospaced", Font.PLAIN, 14));
        JScrollPane scrollPane = new JScrollPane(textAreaCounts);

        setLayout(new BorderLayout());
        JPanel topPanel = new JPanel();
        topPanel.add(lblFruit);
        add(topPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);

        startThreads();
    }

    private void updateCounts() {
        textAreaCounts.setText(
                "Mango Count: " + mangoCount.get() + "\n" +
                "Orange Count: " + orangeCount.get() + "\n" +
                "Grapes Count: " + grapesCount.get()
        );
    }

    private void startThreads() {
        // Thread 1: Fruit Generator
        Thread generatorThread = new Thread(() -> {
            while (true) {
                synchronized (lock) {
                    while (fruitSlot != null) {
                        try {
                            lock.wait(); // wait for consumer to clear slot
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }

                    fruitSlot = fruits[random.nextInt(fruits.length)];
                    String currentFruit = fruitSlot;

                    // Update GUI with the generated fruit
                    SwingUtilities.invokeLater(() -> lblFruit.setText("Generated Fruit: " + currentFruit));

                    lock.notify(); // notify consumer
                }

                try {
                    Thread.sleep(500); // small pause before producing again
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        // Thread 2: Fruit Consumer
        Thread consumerThread = new Thread(() -> {
            while (true) {
                synchronized (lock) {
                    while (fruitSlot == null) {
                        try {
                            lock.wait(); // wait for fruit to be available
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }

                    String consumedFruit = fruitSlot;

                    // Simulate processing delay (1 to 4 seconds)
                    try {
                        Thread.sleep((1 + random.nextInt(4)) * 1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    // Count the fruit
                    switch (consumedFruit) {
                        case "mango" -> mangoCount.incrementAndGet();
                        case "orange" -> orangeCount.incrementAndGet();
                        case "grapes" -> grapesCount.incrementAndGet();
                    }

                    // Clear the slot
                    fruitSlot = null;

                    // Update counts in GUI
                    SwingUtilities.invokeLater(this::updateCounts);

                    lock.notify(); // notify generator
                }
            }
        });

        generatorThread.start();
        consumerThread.start();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            FruitCounterGUI gui = new FruitCounterGUI();
            gui.setVisible(true);
        });
    }
}
