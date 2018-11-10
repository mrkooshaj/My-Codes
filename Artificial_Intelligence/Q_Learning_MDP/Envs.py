import gym
import sys
from math import pi


def make_env(env_id):
    if env_id == 'CartPole':
        env = gym.make('CartPole-v1')
        env = CartPole(env)
    if env_id == 'FrozenLake':
        env = gym.make('FrozenLake-v0')
        env = FrozenLake(env)
    return env


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


class CartPole(gym.Wrapper):
    def __init__(self, env):
        gym.Wrapper.__init__(self, env)

    def _step(self, action):
        state, reward, done, _ = self.env.step(action)
        x, x_dot, theta, theta_dot = state
        deg5 = pi / 72
        x = ctod(x, [-1.0, 0.0, +1.0])  # 4 states
        x_dot = ctod(x_dot, [0.0])  # 2 states
        theta = ctod(theta, [-2 * deg5, -1 * deg5, 0.0, +1 * deg5, +2 * deg5])  # 6 states
        theta_dot = ctod(theta_dot, [0.0])  # 2 states
        state = int(x + 4 * x_dot + 8 * theta + 48 * theta_dot)
        return state, reward, done

    def get_actions(self):
        return list(range(self.action_space.n))

    def get_num_states(self):
        return 96


class FrozenLake(gym.Wrapper):
    def __init__(self, env):
        gym.Wrapper.__init__(self, env)

    def _step(self, action):
        state, reward, done, _ = self.env.step(action)
        return state, reward, done

    def get_actions(self):
        return list(range(self.action_space.n))

    def get_num_states(self):
        return self.observation_space.n

    def render(self):
        row, col = self.unwrapped.s // self.unwrapped.ncol, self.unwrapped.s % self.unwrapped.ncol
        desc = self.unwrapped.desc.tolist()
        desc = [[c.decode('utf-8') for c in line] for line in desc]
        desc[row][col] = '@'
        if self.unwrapped.lastaction is not None:
            sys.stdout.write("  ({})\n".format(["Left", "Down", "Right", "Up"][self.unwrapped.lastaction]))
        else:
            sys.stdout.write("\n")
        sys.stdout.write("\n".join(''.join(line) for line in desc) + "\n")



