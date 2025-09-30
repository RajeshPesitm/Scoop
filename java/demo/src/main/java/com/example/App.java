package com.example;

import org.jfree.chart.*;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.data.xy.*;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class App extends JFrame {

    private int basePrice = 100000;
    private int currentPrice = basePrice;
    private int timeStep = 0;
    private final Random rand = new Random();

    private final JLabel writerLabel = new JLabel("Current Price: ₹100000");
    private final JTextField basePriceInput = new JTextField("100000", 10);
    private final JButton startButton = new JButton("Start Simulation");

    private final XYSeries series = new XYSeries("Gold Graph");
    private final Timer writerTimer;

    public App() {
        setTitle("Gold Rate Simulator");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 600);
        setLayout(new GridLayout(1, 2));

        // Define custom bold font
        Font boldFont = new Font("SansSerif", Font.BOLD, 16);

        // Writer Panel
        JPanel writerPanel = new JPanel();
        TitledBorder writerBorder = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.GRAY), "📤 Writer - Price Simulator");
        writerBorder.setTitleFont(boldFont);
        writerPanel.setBorder(writerBorder);
        writerPanel.setLayout(new GridLayout(5, 1));

        JLabel basePriceLabel = new JLabel("Enter Base Price:");
        basePriceLabel.setFont(boldFont);
        basePriceInput.setFont(boldFont);
        startButton.setFont(boldFont);
        writerLabel.setFont(boldFont);

        writerPanel.add(basePriceLabel);
        writerPanel.add(basePriceInput);
        writerPanel.add(startButton);
        writerPanel.add(writerLabel);

        // Reader Panel (Chart)
        JPanel readerPanel = new JPanel(new BorderLayout());
        TitledBorder readerBorder = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.GRAY), "📥 Reader - Price Graph");
        readerBorder.setTitleFont(boldFont);
        readerPanel.setBorder(readerBorder);

        XYSeriesCollection dataset = new XYSeriesCollection(series);
        JFreeChart chart = ChartFactory.createXYLineChart(
                "Gold Price Over Time",
                "Time (s)",
                "Price (₹)",
                dataset
        );

        XYPlot plot = chart.getXYPlot();
        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer(true, false);
        plot.setRenderer(renderer);

        // Set Y axis limits
        plot.getRangeAxis().setRange(80000, 110000);

        // Set chart fonts
        chart.getTitle().setFont(new Font("SansSerif", Font.BOLD, 18));
        plot.getDomainAxis().setLabelFont(boldFont);
        plot.getRangeAxis().setLabelFont(boldFont);
        plot.getDomainAxis().setTickLabelFont(boldFont);
        plot.getRangeAxis().setTickLabelFont(boldFont);

        ChartPanel chartPanel = new ChartPanel(chart);
        readerPanel.add(chartPanel, BorderLayout.CENTER);

        // Add panels to frame
        add(writerPanel);
        add(readerPanel);

        // Writer Timer - triggers every 1 second
        writerTimer = new Timer(1000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int deviation = rand.nextInt(501) + 500; // 500–1000
                int direction = rand.nextBoolean() ? 1 : -1;
                currentPrice += direction * deviation;

                if (currentPrice < 1) currentPrice = 1;

                writerLabel.setText("Current Price: ₹" + currentPrice);
                series.add(timeStep++, currentPrice);
            }
        });

        // Start Button Action
        startButton.addActionListener(e -> {
            try {
                basePrice = Integer.parseInt(basePriceInput.getText());
                currentPrice = basePrice;
                timeStep = 0;
                series.clear();
                writerLabel.setText("Current Price: ₹" + currentPrice);
                writerTimer.start();
                startButton.setEnabled(false);
                basePriceInput.setEnabled(false);
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(App.this, "Invalid base price");
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        // Set a nicer look & feel
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ignored) {}

        SwingUtilities.invokeLater(App::new);
    }
}

