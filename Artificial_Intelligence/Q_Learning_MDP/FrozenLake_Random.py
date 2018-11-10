import time
import random
from envs import make_env

env = make_env('FrozenLake')  # create frozen lake environment
actions = env.get_actions()  # get a list of all possible actions
num_states = env.get_num_states()  # get number of states in environment (not used in this example)
episode_count = 0  # current episode number
while True:  # this loop runs episodes
    episode_count += 1
    print('\n=== Episode #' + str(episode_count) + ' ===')
    env.reset()  # environment must be reset after every episode
    env.render()
    score = 0  # total reward
    while True:  # this loop runs transitions
        time.sleep(0.2)
        a = random.choice(actions)  # choose randomly from list of actions
        state, reward, done = env.step(a)  # act in environment and receive result (state isn't used in this example)
        env.render()  # render current state of environment
        score += int(reward)  # reaching the goal has a reward of +1, all other transitions have no reward
        if done:  # done == True, indicates that the episode is over
            break
    if score == 1:  # print result of episode
        print('  (Success)')
    else:
        print('  (Failure)')



