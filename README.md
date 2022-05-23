# unn-ros-labs

*Все команды производятся из корневой папки конкретной лаборатрной (прим: second-lab)*

# Подготовка
Ставим себе в линуксе пакет ROS https://wiki.ros.org/noetic/Installation/Ubuntu
Или не паримся и образ который он кидал (лучше не парится, в 4 лабе кучу всего доставлять пришлось)

# Second ROS lab
В отчете нужен скришот трех окон терминала

> setup.bash может быть заменён на setup.zsh или setup.sh в зависимости от оболочки
1. `source ./devel/setup.bash && roscore`
2. `source ./devel/setup.bash && rosrun talkers pbr`
3. `source ./devel/setup.bash && rosrun talkers scr`

# Third ROS lab
В отчете достаточно скрины с запуском в терминале и появившемся окошком

В плане практики указана след. команда для запуска `source ./devel/setup.bash && roslaunch remote_control rc_test.launch`, но она выдаёт ошибку
Рабочая команда: `source ./devel/setup.bash && roslaunch remote_control/launch/rc_test.launch`

# Fourth ROS lab
Отчёт делать по аналогии с тем, что он у себя в доке показывает. По сути просто пошаговый набор скринов

Запускать из `fourth-lab/catkin_ws`
В каждом терминале использовать
`source ./devel/setup.bash`
`export TURTLEBOT3_MODEL=waffle_pi`

У меня тут целая сборная солянка была из разных реп, иначе не запускалось
Кроме тех реп, которые он у себя в отчете юзает я еще скачивал в https://github.com/ROBOTIS-GIT/turtlebot3 `fourth-lab/catkin_ws/src/turtlebot3`

ROS пакет который ставили в самом начале походу имеет не всё что нужно. Доставляем

Для мапы:
`sudo apt install ros-noetic-slam-gmapping`

Для получения карты:
`sudo apt install ros-noetic-map-server`

Для навигации по карте:
`sudo apt install ros-noetic-move-base`
`sudo apt install ros-noetic-amcl`