#!/bin/bash
g++ --std=c++11 graph_to_cnf.cpp input.cpp -o main1
g++ --std=c++11 cnf_to_output.cpp input.cpp -o main2
exit 0