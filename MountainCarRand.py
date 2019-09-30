# -*- coding: utf-8 -*-
"""
Created on Sun Sep 29 20:45:36 2019

@author: 52496
"""

import gym
environment = gym.make("MountainCar-v0")
MAX_NUM_EPISODES = 1000
STEPS_PER_EPISODE = 200

for episode in range(MAX_NUM_EPISODES):
    done=False
    obs = environment.reset()
    total_reward = 0.0
    step=0
    while not done:
        environment.render()
        action = environment.action_space.sample()
        next_state,reward,done,info=environment.step(action)
        total_reward += reward
        step += 1
        obs = next_state
    
    print("\n Episodio numero {} finalizado con {} iteraciones. Recompensa final ={}".format(episode,step,total_reward))
    
environment.close()