import gym
import random
from envs import make_env

env = make_env('FrozenLake')
actions = env.get_actions()
num_states = env.get_num_states()

Q = [[0 for i in range (len(actions))] for j in range(num_states)]

for i in range (num_states) :
    for j in range (len(actions)) :
        
        Q[i][j] = 0



Alpha = 0.01
Gamma = 0.99
Epsilon = 1
Decrement = 0.00001

num_episodes = 150000

Reward_List = []
State_List = []

Last100 = [0 for i in range(100)]

for i in range (100):
    Last100[i] = 0

Episode_Num = 1

while True:
    
    Current = env.reset()
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
        
        Q[Current][Action] = (1-Alpha) * Q[Current][Action] + Alpha * (Reward + Gamma * max(Q[Next]))
        Current = Next
        Final_Reward += Reward
    State_List.append(Current)

Reward_List.append(Final_Reward)
    for t in range (0,99):
        Last100[t] = Last100[t+1]
Last100[99] = Reward
    avg = 0
    for t in range (0,100):
        avg += Last100[t]
avg /= 100
    
    print("Episode {} with epsilon = {} and final Reward r = {}. \n Last 100 Attempts Average is : {}".format(Episode_Num,Epsilon,Final_Reward ,avg))
    Episode_Num = Episode_Num + 1
    if avg > 0.8:
        break

while True:
    
    
    print ("-----------------------")
    print ("And Now to Demonstrate Policy")
    
    Current = env.reset()
    Final_Reward = 0
    Done = False
    State_List = []
    
    score = 0;
    
    while not Done:
        
        Action = Q[Current].index(max(Q[Current]))
        
        if (Action == 0):
            print ("Left \n")
        elif (Action == 1):
            print ("Down \n")
        elif (Action == 2):
            print ("Right \n")
        elif (Action == 3):
            print ("Up\n ")
    
        env.render()
        
        
        Next, Reward, Done = env.step(Action)
        
        score = score + int(Reward)
        
    Current = Next

if (score == 1):
    print ("Success!")
    
    else:
        print ("Failure")
