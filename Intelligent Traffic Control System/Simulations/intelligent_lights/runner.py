#!/usr/bin/env python

import os
import sys
from math import sqrt

import random
from utils import communicate
#路径
if 'SUMO_HOME' in os.environ:
    tools = os.path.join(os.environ['SUMO_HOME'], 'tools')
    sys.path.append(tools)
else:
    sys.exit("please declare environment variable 'SUMO_HOME'")
import traci
from plexe import Plexe, ACC, CACC

VEHICLE_LENGTH = 4
DISTANCE = 6  # inter-vehicle distance
LANE_NUM = 12
PLATOON_SIZE = 1
SPEED = 16.6  # m/s
V2I_RANGE = 200 
PLATOON_LENGTH = VEHICLE_LENGTH * PLATOON_SIZE + DISTANCE * (PLATOON_SIZE - 1)
ADD_PLATOON_PRO = 0.3
ADD_PLATOON_STEP = 600
MAX_ACCEL = 2.6
#DECEL = SPEED**2/(2*(V2I_RANGE-25))  
#DECEL = 3.5
STOP_LINE = 15.0



def add_single_platoon(plexe, topology, step, lane):
    for i in range(PLATOON_SIZE):
        vid = "v.%d.%d.%d" %(step/ADD_PLATOON_STEP, lane, i)
        routeID = "route_%d" %lane   # route 0~11, one-to-one map with lane
        traci.vehicle.add(vid, routeID, departPos=str(100-i*(VEHICLE_LENGTH+DISTANCE)), departSpeed=str(5), departLane=str(lane%3), typeID="vtypeauto")        
        plexe.set_path_cacc_parameters(vid, DISTANCE, 2, 1, 0.5)
        plexe.set_cc_desired_speed(vid, SPEED)
        plexe.set_acc_headway_time(vid, 1.5)
        plexe.use_controller_acceleration(vid, False)
        plexe.set_fixed_lane(vid, lane%3, False)
        traci.vehicle.setSpeedMode(vid, 31)
        if i == 0:
            plexe.set_active_controller(vid, ACC)
            traci.vehicle.setColor(vid, (255,255,255, 255))  # red
            topology[vid] = {}
        else:
            plexe.set_active_controller(vid, CACC)
            traci.vehicle.setColor(vid, (200,200,0, 255)) # yellow
            topology[vid] = {"front": "v.%d.%d.%d" %(step/ADD_PLATOON_STEP, lane, i-1), "leader": "v.%d.%d.0" %(step/ADD_PLATOON_STEP, lane)}

def add_platoons(plexe, topology, step):
    for lane in range(LANE_NUM):    # lane 0~11
        if random.random() < ADD_PLATOON_PRO:
            add_single_platoon(plexe, topology, step, lane)

def main():
    sumo_cmd = ['sumo-gui', '--duration-log.statistics', '--tripinfo-output', 'intelligent_lights_output_file.xml', '-c', 'intelligent_traffic.sumo.cfg']
    traci.start(sumo_cmd)
    # 每次traci.simulationStep()之后都调用一次plexe 
    plexe = Plexe()
    traci.addStepListener(plexe)

    step = 0
    topology = {}

    while step < 360000:  # 1 hour       
        
        traci.simulationStep()

        if step % ADD_PLATOON_STEP == 0:  # add new platoon every X steps
            add_platoons(plexe, topology, step) 

        if step % 10 == 1:
            # simulate vehicle communication every 0.1s
            communicate(plexe, topology)
       
        step += 1


    traci.close()


if __name__ == "__main__":
    main()
