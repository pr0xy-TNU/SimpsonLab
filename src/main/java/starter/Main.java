package starter;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.stream.DoubleStream;
import java.util.stream.IntStream;

import javafx.scene.chart.XYChart;
import org.knowm.xchart.QuickChart;
import org.knowm.xchart.SwingWrapper;
import utils.Utils;

import static java.lang.Math.cos;

public class Main {

    //Вычислительнеые константы
    public static final double lambda = 1.0d;
    public static final double modernX = 2.0d;
    public static final double q = 2.0d;
    public static final double l = 2.0d;
    public static final double E = 2.71828;
    public static final double EPS = 1e-4;
    public static double xx = 0.0d;
    public static final int SCALE = 4;

    public static final double START = 0.0;
    public static final double END = 1.0;
    public static final int POINT_COUNT = 5;

    //Накопитель
    public static double accumulator = 0;

    //Разбиение
    public static double partition = 0.25;
    public static double limit = 3.0d;

    // ЛИсты для потроение графиков
    public static List<Double> listX;
    public static List<Double> listLambda;
    public static Random random;

    static {
        listX = new ArrayList<>();
        listLambda = new ArrayList<>();
        random = new Random();
    }


    public static void main(String[] args) {
        System.out.println("Hello world");

        initStorage();
        printStorage();
        //drawGraph();

       /* double a = 0.0, b = 1.0;
        double S;
        double I = 0.0;
        do {
            S = simpson(a, b);
            I += S;
            a = b;
            b += 1.0;
            //cout << "I = " << I << ";    b = " << b << endl;
            System.out.println("I = " + I + "; b = " + b);
        } while (Math.abs(S) < EPS);
        System.out.println("I = " + I);
        System.out.println("b = " + b + " (A)");*/

        calculateSimpson(START, END);
        //new Thread(Main::drawGraph);
    }


    public static double calculate(double u) {
        double P, F;
        // Логика прилоения
        P = PFunction(u);
        F = FFunction(u);
        double tempResult;
        if (u == 0.0) {
            return roundingOf(1 / 3);
        } else {
            return roundingOf(P * F * cos(modernX * u / lambda));
        }
    }


    public static double PFunction(double u) {
        double modernQ = 0.0d;
        modernQ = 2 * q * l * (
            ((lambda / u) - 2 * (lambda * lambda * lambda) / (u * u * u)) * Math.sin(u / lambda)
                + (2 * lambda / u * u) * cos(u / lambda));
        modernQ = roundingOf(modernQ);
        return modernQ;
    }

    public static double FFunction(double u) {
        double result;

        double shu = sh(u);
        double chu = ch(u);

        result = (shu + u * shu) / (u + shu * chu);

        return roundingOf(result);
    }

    public static void drawGraph() {
        //some draw
        org.knowm.xchart.XYChart chart = QuickChart
            .getChart(Utils.TITLE, Utils.X, Utils.LAMBDA, Utils.FUNCTION, listX, listLambda);
        new SwingWrapper<>(chart).displayChart();

    }

    public static double roundingOf(double number) {
        return new BigDecimal(number).setScale(SCALE, RoundingMode.UP).doubleValue();
        //return number;
    }

    public static double sh(double u) {
        //return roundingOf((Math.pow(E, u) - Math.pow(E, -u)) / 2);
        return (Math.pow(E, u) - Math.pow(E, -u)) / 2;
    }

    public static double ch(double u) {
        //return roundingOf((Math.pow(E, u) + Math.pow(E, -u)) / 2);
        return (Math.pow(E, u) + Math.pow(E, -u)) / 2;
    }

    public static void initStorage() {

        for (double i = 0.0, j = 0.0; i < 1.0; i += 0.25) {
            listX.add(i);
        }
    }


    public static void printStorage() {
        System.out.println("lambda");
        listLambda.forEach(item -> System.out.printf("%5.3f ", item));
        System.out.println();
        System.out.println("x");
        listX.forEach(item -> System.out.printf("%5.3f ", item));
        System.out.println();
    }

    public static double simpson(double a, double b) {
        int n = 1;
        double S1 = 0.0, SP = 0.0, S = 0.0;
        double h = 0.0, r = 0.0;

        S1 = fCos(a) + fCos(b);
        S = (S1 + 4 * f((a + b) / 2.0)) / 6.0;

        do {
            SP = S;
            n = 2 * n;
            h = (b - a) / (2 * n);
            System.out.println( b + " " + a);
            S = S1;
            for (int i = 1; i < n; i++) {
                S += 4 * f(a + (2 * i - 1) * h) + 2 * f(a + 2 * i * h);
            }
            S = h * (S + 4 * f(b - h)) / 3.0;

            r = Math.abs(S - SP) / 15.0;

        } while (r > EPS);
        return roundingOf(S);
    }

    public static double f(double u) {
        if (u == 0) {
            return 1 / (2 * lambda * lambda);
        } else {
            /*
            double up = 2 * (sh(u) + u * ch(u)) / (2 * u + sh(2 * u));
            double down = (1 - cos(u / lambda)) * cos(u * xx / lambda) / (u * u);
            */
            double temp = 2 * (sh(u) + u * ch(u)) / (2 * u + sh(2 * u));
            return temp * (1 - cos(u / lambda)) * cos(u * xx / lambda) / (u * u);
        }
    }

    public static double calculateSimpson(double start, double end) {
        double S = 0.0;
        double I = 0.0;
        double localStart = start;
        double localEnd = end;

        do {

            I += simpson(localStart, localEnd);
            localStart = end;
            localEnd += 1.0;
            System.out.printf("%3.3f\t%3.3f\n", I, end);

        } while (Math.abs(S) < E);

        return I;
    }

    public static double fCos(double u) {
        return Math.cos(u);
    }

}