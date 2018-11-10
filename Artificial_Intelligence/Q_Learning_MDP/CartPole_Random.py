import time
import random
from envs import make_env

env = make_env('CartPole')  # create cart-pole environment
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
        time.sleep(0.017)
        a = random.choice(actions)  # choose randomly from list of actions
        state, reward, done = env.step(a)  # act in environment and receive result (state isn't used in this example)
        env.render()  # render current state of environment
        score += int(reward)  # every time-step has a reward of +1 in the cart-pole environment
        if done:  # done == True, indicates that the episode is over
            break
    print('Score:', '{:03}'.format(score))  # print total reward obtained in episode
