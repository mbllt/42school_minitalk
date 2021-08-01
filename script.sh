#/bin/shell

./server > name_server &
export PID_SERVER=$(cat name_server |  bc -l)
./client $VAR_TEST $1 

kill $PID_SERVER
