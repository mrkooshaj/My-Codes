package com.company;

import com.company.Str.*;
import sun.security.krb5.internal.KRBSafe;

import javax.swing.*;
import java.util.ArrayList;
import java.util.Random;


public class Main
{
    public static Game game;
    public static Strategy[] trainSet;
    public static double[] trainSetWeight;
    public static int[] trainSetRepeat;

    public static void main(String[] args) throws Exception
    {
        setTrainsetDefault();
        setGame();

        System.out.println(game.score(DFA.loadFromFile("answer.txt")));

        System.exit(0);

        int start_pop = 30;

        int dfa_states = 8;

        DFA population[] = new DFA [start_pop];

        for (int j = 0; j < start_pop; j++)
        {
            int output_pop[] = new int[dfa_states];
            int pop_transitions[][] = new int[dfa_states][6];
            Random rnd = new Random();
            for (int i = 0; i < dfa_states; i++)
            {
                output_pop[i] = rnd.nextInt(6);
            }
            for (int i = 0; i < dfa_states; i++)
            {
                for (int k = 0; k < 6; k++)
                {
                    pop_transitions[i][k] = rnd.nextInt(dfa_states);
                }
            }

            DFA newpop = new DFA(output_pop,pop_transitions);

            population[j] = newpop;
        }

        DFA next_gen[] = new DFA[start_pop];

        double max_score = 0;

        double population_scores[] = new double[start_pop];

        DFA tempor = new DFA(population[0].outputs,population[1].transitions);





    while (1==1)
    {

        for (int t = 0; t < start_pop; t++)
        {
            population_scores[t] = game.score(population[t]);
        }

        for (int t = 0; t < start_pop; t++)
        {
            for (int s = 0; s < start_pop-1; s++)
            {
                if (population_scores[s] < population_scores[s+1])
                {
                    double temp = population_scores[s];
                    population_scores[s] = population_scores[s+1];
                    population_scores[s+1] = temp;
                    tempor = population[s];
                    population[s] = population[s+1];
                    population[s+1] = tempor;
                }
            }
        }

        double sum_of_scores = 0;

        System.out.println("------------------");

        for (int k = 0; k < start_pop; k++)
        {
            System.out.println(population_scores[k]);
            if (population_scores[0] > 750.0)
            {
                population[0].saveToFile("answer.txt");
                System.exit(0);
            }
            sum_of_scores = sum_of_scores + population_scores[k];
            if (max_score < population_scores[k])
            {
                max_score = population_scores[k];
            }
        }

        System.out.print("Max Score = ");
        System.out.println(max_score);

        double probs[] = new double[start_pop];
        probs[0] = population_scores[0]/sum_of_scores;
        for (int k = 1; k < start_pop; k++)
        {
            probs[k] = probs[k-1] + population_scores[k]/sum_of_scores;
        }

        for (int z = 3; z < start_pop; z++)
        {
            Random probab = new Random();
            double rndm1 = probab.nextInt(1001)/1000;
            double rndm2 = probab.nextInt(1001)/1000;

            int output_dfa1[] = new int[dfa_states];
            int dfa1_transitions[][] = new int[dfa_states][6];

            int output_dfa2[] = new int[dfa_states];
            int dfa2_transitions[][] = new int[dfa_states][6];

            if (rndm1 < probs[0])
            {
                //DFA firstdfa = new DFA(population[0].outputs,population[0].transitions);
                output_dfa1 = population[0].outputs;
                dfa1_transitions = population[0].transitions;
            }
            if (rndm2 < probs[0])
            {
                output_dfa2 = population[0].outputs;
                dfa2_transitions = population[0].transitions;
            }
            if (rndm1 > probs[start_pop-2])
            {
                output_dfa1 = population[start_pop-1].outputs;
                dfa1_transitions = population[start_pop-1].transitions;
            }
            if (rndm2 > probs[start_pop-2])
            {
                output_dfa2 = population[start_pop-1].outputs;
                dfa2_transitions = population[start_pop-1].transitions;
            }

            for (int k = 1; k < start_pop-1; k++)
            {
                if (rndm1 < probs[k] && rndm1 > probs[k-1])
                {
                    output_dfa1 = population[k].outputs;
                    dfa1_transitions = population[k].transitions;
                }
                if (rndm2 < probs[k] && rndm2 > probs[k-1])
                {
                    output_dfa2 = population[k].outputs;
                    dfa2_transitions = population[k].transitions;
                }
            }

            int output_gen[] = new int[dfa_states];
            int gen_transitions[][] = new int[dfa_states][6];


            for (int s = 0; s < dfa_states; s++)
            {
                if (s < dfa_states/2)
                {
                    output_gen[s] = output_dfa1[s];
                }
                else
                {
                    output_gen[s] = output_dfa2[s];
                }
            }

            for (int s = 0; s < dfa_states; s++)
            {
                for (int t = 0; t < 6; t++)
                {
                    if (s < dfa_states/2 && t < 3)
                    {
                        gen_transitions[s][t] = dfa1_transitions[s][t];
                    }
                    else if (s >= dfa_states/2 && t >= 3)
                    {
                        gen_transitions[s][t] = dfa1_transitions[s][t];
                    }
                    else
                    {
                        gen_transitions[s][t] = dfa2_transitions[s][t];
                    }
                }
            }

            Random mutation = new Random();

            int mutate = mutation.nextInt(3);

            if (mutate == 0)
            {
                int changeplace = mutation.nextInt(dfa_states);
                output_gen[changeplace] = (output_gen[changeplace] + 1) % 6;

                for (int s = 0; s < 6; s++)
                {
                    int changetable = mutation.nextInt(dfa_states);
                    gen_transitions[changetable][s] = (gen_transitions[changetable][s] + 1) % dfa_states;
                }
            }

            DFA new_gen = new DFA(output_gen,gen_transitions);

            next_gen[z] = new_gen;
        }

        for (int s = 0; s < 3; s++)
        {
            next_gen[s] = population[s];
        }

        for (int v = 0; v < start_pop; v++)
        {
            for (int s = 0; s < dfa_states; s++)
            {
                population[v].outputs[s] = next_gen[v].outputs[s];
            }
            for (int s = 0; s < dfa_states; s++)
            {
                for (int t = 0; t < 6; t++)
                {
                    population[v].transitions[s][t] = next_gen[v].transitions[s][t];
                }
            }
        }

    }



    }

    public static void setTrainsetDefault()
    {
        trainSet = new Strategy[17];
        trainSetWeight = new double[17];
        trainSetRepeat = new int[17];

        trainSet[0] = new Adaptive();
        trainSetWeight[0] = 3.0;
        trainSetRepeat[0] = 1;
        trainSet[1] = new AlwaysCooperate();
        trainSetWeight[1] = 2.0;
        trainSetRepeat[1] = 1;
        trainSet[2] = new AlwaysDefect();
        trainSetWeight[2] = 5.0;
        trainSetRepeat[2] = 10000;
        trainSet[3] = new AlwaysRandom();
        trainSetWeight[3] = 5.0;
        trainSetRepeat[3] = 10000;
        trainSet[4] = new Gradual();
        trainSetWeight[4] = 3.0;
        trainSetRepeat[4] = 1;
        trainSet[5] = new GrimTrigger();
        trainSetWeight[5] = 4.0;
        trainSetRepeat[5] = 1;
        trainSet[6] = new GrimTriggerSoft();
        trainSetWeight[6] = 3.0;
        trainSetRepeat[6] = 1;
        trainSet[7] = new GrudgeHolder();
        trainSetWeight[7] = 3.0;
        trainSetRepeat[7] = 1;
        trainSet[8] = new Pavlov();
        trainSetWeight[8] = 3.0;
        trainSetRepeat[8] = 1;
        trainSet[9] = new TitForTat();
        trainSetWeight[9] = 5.0;
        trainSetRepeat[9] = 1;
        trainSet[10] = new TitForTatExp();
        trainSetWeight[10] = 10.0;
        trainSetRepeat[10] = 5000;
        trainSet[11] = new TitForTatExpRemorse();
        trainSetWeight[11] = 10.0;
        trainSetRepeat[11] = 4000;
        trainSet[12] = new TitForTatHarsh();
        trainSetWeight[12] = 3.0;
        trainSetRepeat[12] = 1;
        trainSet[13] = new TitForTatPeace();
        trainSetWeight[13] = 10.0;
        trainSetRepeat[13] = 5000;
        trainSet[14] = new TitForTatSus();
        trainSetWeight[14] = 3.0;
        trainSetRepeat[14] = 3000;
        trainSet[15] = new TitForTwoTat();
        trainSetWeight[15] = 4.0;
        trainSetRepeat[15] = 1;
        trainSet[16] = new UpDown();
        trainSetWeight[16] = 1.0;
        trainSetRepeat[16] = 1;
    }

    public static void setGame()
    {
        game = new Game();
        int[][] p1playoffs = new int[6][];
        int[][] p2playoffs = new int[6][];
        for(int i=0; i<6; i++)
        {
            p1playoffs[i] = new int[6];
            p2playoffs[i] = new int[6];
        }

        for(int p1=0; p1<6; p1++)
            for(int p2=0; p2<6; p2++)
            {
                p1playoffs[p1][p2] = p1+2*(5-p2);
                p2playoffs[p1][p2] = p2+2*(5-p1);
            }

        game.set(p1playoffs, p2playoffs, 100, 20, trainSet, trainSetWeight, trainSetRepeat, 0.0);
    }


}
