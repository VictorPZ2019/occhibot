#include <iostream>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class RobotDriver
{
    private:

    ros::NodeHandle nh_;

    ros::Publisher cmd_vel_pub_;

    public:

    RobotDriver(ros::NodeHandle &nh)
    {
        nh_ = nh;

        cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/base_controller/command", 1);
    }

    bool driveKeyboard()
    {
       std::cout << "Escriba un comando y luego presione Intro \n"
       " Use 'w' para avanszar, 's' para retroceder,'a' para girar a la izquierda \n"
       "'d' para girar a la derecha, 'x' para detenerse, 'b' para salir. \n ";

       // Enviar comandos del tipo "twist"
       geometry_msgs::Twist base_cmd;

       char cmd[50];
       while(nh_.ok()){
           std::cin.getline(cmd,50);
           if(cmd[0]!='w' && cmd[0]!='a' && cmd[0]!='d' && cmd[0]!='s' && cmd[0]!='x' && cmd[0]!='b')
           {
               std::cout << "unknowm command:" << cmd << "\n";
               continue;
           }
           base_cmd.linear.x = base_cmd.linear.y = base_cmd.linear.z = 0;
           // Avanzar
           if(cmd[0]=='w'){
               base_cmd.linear.x =0.25;
               base_cmd.linear.y =0;
               base_cmd.angular.z =0;
           }
           // Retroceder
           else if(cmd[0]=='s'){
               base_cmd.linear.x =-0.25;
               base_cmd.linear.y =0;
               base_cmd.angular.z =0;
           }
           // Gire a la izquierda (guiñada) y avance al mismo tiempo
           else if(cmd[0]=='a'){
                base_cmd.linear.x =0.25;
                base_cmd.linear.y =0;
                base_cmd.angular.z =0.75;
            }
           // Gire a la derecha (guiñada) y avance al mismo tiempo
           else if(cmd[0]=='d'){
                base_cmd.linear.x =0.25;
                base_cmd.linear.y =0;
                base_cmd.angular.z =-0.75;
            }
           // Parar
           else if(cmd[0]=='x'){
                base_cmd.linear.x =0;
                base_cmd.linear.y =0;
                base_cmd.angular.z =0;
           }
           // Salir
           else if(cmd[0]=='b'){
               break;
           }
           // publica el comando ensamblado
           cmd_vel_pub_.publish(base_cmd);
       }
       return true;

    }
};

int main(int argc, char** argv)
{
    //init the ROS node
    ros::init(argc, argv, "robot_driver");
    ros::NodeHandle nh;

    RobotDriver driver(nh);
    driver.driveKeyboard();
}