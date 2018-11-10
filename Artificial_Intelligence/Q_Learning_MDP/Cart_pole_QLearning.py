import gym
import random
import math
import time
from Envs import make_env

env = make_env('CartPole')
actions = env.get_actions()
num_states = env.get_num_states()

Q = [[0 for i in range (len(actions))] for j in range(num_states)]

for i in range (num_states) :
    for j in range (len(actions)) :

        Q[i][j] = 0

def cont_state2dis_state(state):
    def ctod(x, ranges):
        n = len(ranges) - 1
        if x < ranges[0]:
            return 0
        if x >= ranges[-1]:
            return n + 1
        for i in range(n):
            if ranges[i] <= x < ranges[i + 1]:
                return i + 1
        assert False
    x, x_dot, theta, theta_dot = state
    deg5 = math.pi / 72
    x = ctod(x, [-1.0, 0.0, +1.0])  # 4 states
    x_dot = ctod(x_dot, [0.0])  # 2 states
    theta = ctod(theta, [-2 * deg5, -1 * deg5, 0.0, +1 * deg5, +2 * deg5])  # 6 states
    theta_dot = ctod(theta_dot, [0.0])  # 2 states
    dis_state = int(x + 4 * x_dot + 8 * theta + 48 * theta_dot)
    return dis_state



Alpha = 0.01
Gamma = 0.9
Epsilon = 1
Decrement = 0.00001

Reward_List = []
State_List = []

Last100 = [0 for i in range(100)]

for i in range (100):
    Last100[i] = 0.0

Episode_Num = 1

while True:

    Current = cont_state2dis_state(env.reset())
    Final_Reward = 0
    Done = False
    State_List = []

    Epsilon = Epsilon - Decrement


    # The Q-Table learning algorithm
    while not Done :

        rnd = random.uniform(0,1)
        if (rnd > Epsilon) :
            Action = Q[Current].index(max(Q[Current]))

        else:
            Action = random.choice(env.get_actions())

        Next,Reward,Done = env.step(Action)

        if (Done):
            Q[Current][Action] = (1 - Alpha) * Q[Current][Action] + Alpha * (Reward)
        else:
            Q[Current][Action] = (1-Alpha) * Q[Current][Action] + Alpha * (Reward + Gamma * max(Q[Next]))
        Current = Next
        Final_Reward += Reward
        State_List.append(Current)

    Reward_List.append(Final_Reward)
    for t in range (0,99):
        Last100[t] = Last100[t+1]
    Last100[99] = Final_Reward
    avg = 0
    for t in range (0,100):
        avg += Last100[t]
    avg /= 100

    print("Episode {} with epsilon = {} and final Reward r = {}. \n Last 100 Attempts Average is : {}".format(Episode_Num,Epsilon,Final_Reward ,avg))
    Episode_Num = Episode_Num + 1
    if avg > 400:
        break

while True:

    Current = cont_state2dis_state(env.reset())
    Final_Reward = 0
    Done = False
    State_List = []

    score = 0;

    while not Done:

        Action = Q[Current].index(max(Q[Current]))

        Next, Reward, Done = env.step(Action)

        env.render()

        score = score + int(Reward)

        Current = Next

print('Score:', '{:03}'.format(score))
