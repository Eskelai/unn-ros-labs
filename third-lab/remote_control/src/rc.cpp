#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "sstream"

using namespace std;

ros::Publisher v_pub;	//global variable for publishing data into emulator

double getRads(double deg){ //convert to radians
	const double pi = 3.14159265359;
	return (deg * pi) / 180;

}

void move(double dist, double spd, double angle){
	geometry_msgs::Twist v_msg;	//message with velocity data

	if(dist < 0)    //get the direction(forward/backward) and set the speed
		v_msg.linear.x = -spd;
	else
		v_msg.linear.x = spd;

	double tMove = dist/spd;    //calculate the amount of time needed to cover the distance

	double angSpd = getRads(angle/tMove);   //calculate necessary angular speed

	v_msg.angular.z = angSpd;  //set angular speed 

	//set other components that we don't need to zero
	v_msg.linear.y = 0;
	v_msg.linear.z = 0;
	v_msg.angular.x = 0;
	v_msg.angular.y = 0;

	double t0 = ros::Time::now().toSec();   //start counting time

	double cur_dist = 0.0;  //declare variable for our current distance and set it to zero

	ros::Rate loop_rate(100);   //set frequency

    if(dist == 0){  //in case we want to turn without moving somewhere
        double ang_spd = getRads(spd);
        v_msg.angular.z = ang_spd;  //get angular speed from desired speed
        double cur_ang = 0.0;   //declare current angle  

        v_msg.linear.x = 0; //set linear speed to zero to prevent turtle from going somewhere

        do{
            v_pub.publish(v_msg);   //publishing velocity data to emulator
		    double t1 = ros::Time::now().toSec();   //get time now
		    cur_ang = ang_spd * (t1 - t0);  //calculate current angle using speed and time of moving

		    ros::spinOnce();
		    loop_rate.sleep();

        } while(abs(cur_ang) < abs(getRads(angle)));

    } else {    //if we want to go straight or in an arc
        double d = abs(dist);

	    do{
		    v_pub.publish(v_msg);   //publishing velocity data
		    double t1 = ros::Time::now().toSec();   //getting time now
		    cur_dist = spd * (t1 - t0); //calculating current distance
		    //cout << "Distance " << cur_dist << ":" << d << endl;
		    ros::spinOnce();
		    loop_rate.sleep();
	    } while (abs(cur_dist) < d); 
    }

    //forcing robot to stop by publishing zero velocities

	v_msg.linear.x = 0;
	v_msg.angular.z = 0;
	v_pub.publish(v_msg);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "test_turtle");   //initialising node
	ros::NodeHandle n;  //creating nodehandle object for handling our publisher
	double dist = 0, spd = 0, angle = 0;

	v_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000); //initialising publisher with topic and size of queue

	ros::Rate loop_rate(10);    //setting frequency

	cout << "===TEST===\n\n";

	//starting test
	while(ros::ok()){
		cout << "Enter speed: ";
		cin >> spd;
		cout << "Enter distance: ";
		cin >> dist;
		cout << "Enter angle: ";
		cin >> angle;

	move(dist, spd, angle);
	}

    ros::spin();

    return 0;
}

