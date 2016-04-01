# Walking_Agent
In this repository, the source code of the walking agent is given. The code originally has been developed to test the Gazebo RoboCup plugin by comparing walking behavior in Gazebo with Simspark simulator. The same walking controller has been used for walking behavior of the FCPortugal team, and had also been tested in on a real NAO robot. 

# Discription
This agent can be run in both Gazebo and Simspark simulator. The implemented agent is also capable to walk or run using a Zero Moment Point (ZMP) based approach. The details of the walking approach can be be found in the article with the title of "Learning to Walk Fast: Optimized Hip Height Movement for Simulated and Real Humanoid Robots".
The presented code in this folder contains some base tools which can help the developers to start the implementation of their own humanoid soccer agent.

If you use this walking approach in your research, please cite the following paper in your contributed articles:

Shafii, N., Lau, N. and Reis, L.P., 2015. Learning to Walk Fast: Optimized Hip Height Movement for Simulated and Real Humanoid Robots. Journal of Intelligent & Robotic Systems, 80(3-4), pp.555-571.

If you use this walk engine in your Robocup team, Please cite the following FCPortugal_TDP in your team discription paper:

Lau, N., Reis, L.P., Shafii, N., Abdolmaleki, A., Ferreira, R. and Pereira, A., FC Portugal 3D Simulation Team: Team Description Paper 2015.

# How to Execute
For compiling the agent on your machine, use the makefile in the root folder and simply type "make". For spawning the agent with its default values on the simulator, run the compiled binary ./testAgent .

Available arguments to the binary:

--unum           The player Number

--teamname       The team Name

--host           The Network address of the simulator

# Acknowledgement
I would like to thank the FCPortugal3D team which the walk engine has been developed based on the FCPortugal team software.
