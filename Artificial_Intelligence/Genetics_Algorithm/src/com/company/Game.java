package com.company;

import java.util.Random;


public class Game
{
    int[][] p1payoffs;
    int[][] p2payoffs;
    int count;
    int countOffset;
    int actions;
    double error;
    Random rand;

    public Strategy[] trainset;
    double[] trainsetWeight;
    int[] trainsetRepeat;

    public double p1score;
    public double p2score;

    public void set (int[][] newP1payoffs, int[][] newP2payoffs, int newCount, int newCountOffset, Strategy[] newTrainset, double[] newTrainsetWeight, int[] newTrainsetRepeat, double newError)
    {
        p1payoffs = newP1payoffs;
        p2payoffs = newP2payoffs;
        count = newCount;
        countOffset = newCountOffset;
        trainset = newTrainset;
        trainsetWeight = newTrainsetWeight;
        trainsetRepeat = newTrainsetRepeat;
        actions = p1payoffs.length;
        error = newError;
        rand = new Random();
        rand.setSeed(System.currentTimeMillis());
    }

    public void play(Strategy s1, Strategy s2)
    {
        s1.reset(p1payoffs, p2payoffs, count, 1);
        s2.reset(p1payoffs, p2payoffs, count, 2);

        p1score = 0;
        p2score = 0;

        int chosenCount = countOffset==0? count : rand.nextInt(countOffset*2) + count - countOffset;


        for(int i=0; i<chosenCount; i++)
        {
            int o1;
            o1 = s1.output();
            if(rand.nextDouble() < error)
                o1 = rand.nextInt(actions);


            int o2;
            o2 = s2.output();
            if(rand.nextDouble() < error)
                o2 = rand.nextInt(actions);

            p1score += p1payoffs[o1][o2];
            p2score += p2payoffs[o1][o2];

            s1.input(o2, p1payoffs[o1][o2], p2payoffs[o1][o2]);
            s2.input(o1, p1payoffs[o1][o2], p2payoffs[o1][o2]);
        }

        p1score = p1score / chosenCount;
        p2score = p2score / chosenCount;

    }

    public double score(Strategy s)
    {
        double result = 0;
        for(int i=0; i<trainset.length; i++)
        {
            double resultTemp = 0;
            for(int j=0; j<trainsetRepeat[i]; j++)
            {
                play(s, trainset[i]);
                resultTemp += p1score * trainsetWeight[i];
            }

            result += resultTemp/trainsetRepeat[i];
        }

        return result;
    }
}
