#!/bin/bash
g++ -O3 --std=c++11 graph_to_cnf.cpp -o main1
g++ -O3 --std=c++11 cnf_to_output.cpp -o main2
exit 0